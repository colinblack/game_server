/*
 * VipManager.cpp
 *
 *  Created on: 2018年10月17日
 *      Author: Administrator
 */

#include "VipManager.h"
#include "PlayerManager.h"
#include "ProtocolUser.h"
#include "VipConfig.h"
#include "GiftBagConfig.h"
#include "SystemMessage.h"

VipManager::VipManager() {
	m_lv = 0;
}

VipManager::~VipManager() {
}

bool VipManager::doPacket(CNetPacket *p) {
	switch (p->subCmd) {
	case PROTOCOL_SUBCMD_USER_VIP_REWARD:
		doReward(p);
		break;
	}
	return true;
}

bool VipManager::load(uint32_t uid) {
	int ret = 0;
	CDataState dbc;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_VIP;

	ret = dbc.GetState(data.uid, data.id, data.data);
	if (R_SUCCESS == ret) {
		Json::Value v;
		Json::Reader reader;
		if (reader.parse(data.data, v) && !v.isNull() && v.isArray()) {
			for (size_t i = 0; i < v.size(); ++i) {
				VipData item;
				if (item.fromJson(v[i])) {
					m_data.insert(make_pair(item.lv, item));
				}
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		ret = dbc.AddState(data.uid, data.id, "");
	} else {
		error_log("get state error uid=%u id=%u", data.uid, data.id);
	}

	return true;
}

bool VipManager::onLogin() {
	uint32_t num = VipConfig::getInstance()->getSize();
	if (m_data.size() != num) {
		for (uint32_t i = 1; i <= num; ++i) {
			if (!m_data.count(i)) {
				VipData &item = m_data[i];
				item.lv = i;
			}
		}
	}

	reset();
	push();
	return true;
}

bool VipManager::save() {
	Json::Value v = Json::Value(Json::arrayValue);
	for (map<byte, VipData>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		v.append(it->second.toJson());
	}
	CDataState dbc;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_VIP;
	data.data = Json::ToString(v);
	dbc.SetState(data);
	return true;
}

bool VipManager::push() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_VIP_INFO);
	writer.AppendUInt32(m_data.size());
	for (map<byte, VipData>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		const VipData &item = it->second;
		writer.AppendUInt32(item.lv);
		writer.AppendUInt32(item.first);
		writer.AppendUInt32(item.reward_ts);
		writer.AppendUInt32(item.end_ts);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool VipManager::reset() {
	byte lv = 0;
	for (map<byte, VipData>::iterator it = m_data.begin(); it != m_data.end(); ++it) {
		VipData &item = it->second;
		if (item.lv > lv && item.end_ts > LogicManager::GlobalTime) {
			lv = item.lv;
		}
	}
	m_lv = lv;
	return true;
}

bool VipManager::buy(uint32_t id) {
	uint32_t ts = VipConfig::getInstance()->getTs(id);
	if (ts == 0) {
		return false;
	}
	VipData &item = m_data[id];
	if (item.end_ts >= LogicManager::GlobalTime) {
		item.end_ts += ts;
	} else {
		item.end_ts = CTime::GetDayBeginTime(LogicManager::GlobalTime) + ts;
	}
	item.first = 0;
	reset();
	save();
	push();
	SystemMessage::getInstance()->addBuyVip(m_player->getUid(), id);
	return true;
}

float VipManager::getRight(uint32_t type) {
	if (m_lv == 0) {
		return 0;
	}
	switch (type) {
	case VIP_RIGHT_HARVEST:
		return static_cast<float>(VipConfig::getInstance()->getHarvest(m_lv)) / 100.0f;
	case VIP_RIGHT_BOAT_RES:
		return static_cast<float>(VipConfig::getInstance()->getBoatRes(m_lv)) / 100.0f;
	case VIP_RIGHT_OFFLINE:
		return static_cast<float>(VipConfig::getInstance()->getOffline(m_lv)) / 100.0f;
	case VIP_RIGHT_LOOT_ADD:
		return static_cast<float>(VipConfig::getInstance()->getLootAdd(m_lv)) / 100.0f;
	case VIP_RIGHT_BOAT_TIMES:
		return VipConfig::getInstance()->getBoatTimes(m_lv);
	case VIP_RIGHT_CAPACITY:
		return static_cast<float>(VipConfig::getInstance()->getCapacity(m_lv)) / 100.0f;
	}
	return 0;
}

bool VipManager::doReward(CNetPacket *p) {
	uint32_t uid = p->uid;
	Award award;
	Award box;
	CUserVipRewardProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", uid);
		onRewardResp(1, 0, award, box);
		return false;
	}
	map<byte, VipData>::iterator itr = m_data.find(proto.id);
	if (itr == m_data.end()) {
		error_log("id not exists uid=%u id=%u", uid, proto.id);
		onRewardResp(1, 0, award, box);
		return false;
	}
	VipData &item = itr->second;
	if (CTime::GetDayInterval(item.reward_ts, LogicManager::GlobalTime) == 0) {
		error_log("had reward uid=%u id=%u", uid, proto.id);
		onRewardResp(1, 0, award, box);
		return false;
	}
	if (item.end_ts < LogicManager::GlobalTime) {
		error_log("times out uid=%u id=%u ets=%u", uid, proto.id, item.end_ts);
		onRewardResp(1, 0, award, box);
		return false;
	}
	const VipConfigItem* cfg = VipConfig::getInstance()->getItem(proto.id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", uid, proto.id);
		onRewardResp(1, 0, award, box);
		return false;
	}
	Award creward;
	if (item.first == 0) {
		item.first = 1;
		creward = cfg->first;
	} else {
		creward = cfg->award;
	}
	item.reward_ts = LogicManager::GlobalTime;
	save();
	if (!m_player->doReward(&creward, "vip_" + CTrans::ITOS(proto.id), false, &award)) {
		error_log("do reward error uid=%u id=%u", uid, proto.id);
		onRewardResp(1, 0, award, box);
		return false;
	}
	onRewardResp(0, proto.id, award, box);
	push();
	BUSI_MISC("resident_act|vipcard|%u|%u|%u", m_player->getUid(), proto.id, Time::GetGlobalTime());
	return true;
}

bool VipManager::onRewardResp(byte ret, byte lv, const Award &award, const Award &box) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_VIP_REWARD);
	writer.AppendByte(ret);
	writer.AppendUInt32(lv);
	award.packetData(writer);
	box.packetData(writer);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool VipManager::onBoxReward(uint32_t lv, uint32_t id, uint32_t count, Award *result) {
	uint32_t boxId = (lv == 0 ? 1 : lv) * 1000 + id;
	Award award;
	GiftBagConfig::getInstance()->openAllLuckyBox(boxId, count, award);
	m_player->doReward(&award, "vip_box_" + CTrans::ITOS(boxId), false, result);
	return true;
}
