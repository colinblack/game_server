/*
 * MonthGiftManager.cpp
 *
 *  Created on: 2019年1月2日
 *      Author: Administrator
 */

#include "MonthGiftManager.h"
#include "PlayerManager.h"
#include "ConfigInc.h"
#include "ProtocolInc.h"
#include "SystemMessage.h"

MonthGiftManager::MonthGiftManager() {
}

MonthGiftManager::~MonthGiftManager() {
}

bool MonthGiftManager::doPacket(CNetPacket* packet) {
	switch (packet->subCmd)
	{
	case PROTOCOL_SUBCMD_USER_MONTH_GIFT_INFO:
		push();
		break;
	case PROTOCOL_SUBCMD_USER_MONTH_GIFT_REWARD:
		doReward(packet);
		break;
	}
	return true;
}

bool MonthGiftManager::load(uint32_t uid) {
	CDataState dbc;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_MONTH_GIFT;
	int ret = dbc.GetState(data.uid, data.id, data.data);
	if (0 == ret) {
		Json::Value v;
		Json::Reader r;
		if (r.parse(data.data, v) && v.isArray()) {
			for (size_t i = 0; i < v.size(); ++i) {
				DataMonthGift item;
				item.id = v[i].get("id", 0).asUInt();
				item.end_ts = v[i].get("ets", 0).asUInt();
				item.reward_ts = v[i].get("rts", 0).asUInt();
				m_data.insert(make_pair(item.id, item));
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		ret = dbc.AddState(data.uid, data.id, "");
	} else {
		error_log("get state error uid=%u ret=%d", uid, ret);
		return false;
	}
	return true;
}

bool MonthGiftManager::save() {
	Json::Value v = Json::Value(Json::arrayValue);
	map<byte, DataMonthGift>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		const DataMonthGift &data = itr->second;
		Json::Value item;
		item["id"] = static_cast<uint32_t>(itr->first);
		item["ets"] = data.end_ts;
		item["rts"] = data.reward_ts;
		v.append(item);
	}
	CDataState dbc;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_MONTH_GIFT;
	data.data = Json::ToString(v);
	int ret = dbc.SetState(data);
	if (0 != ret) {
		error_log("set state error uid=%u ret=%d", data.uid, ret);
		return false;
	}
	return true;
}

bool MonthGiftManager::push() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_MONTH_GIFT_INFO);
	uint32_t len = VipConfig::getInstance()->getGiftSize();
	PACKET_ENCODE(UInt32, len);
	for (uint32_t i = 1; i <= len; ++i) {
		map<byte, DataMonthGift>::iterator itr = m_data.find(i);
		if (itr == m_data.end()) {
			PACKET_ENCODE(UInt32, 0);
		} else {
			if (itr->second.end_ts < Time::GetGlobalTime()) {
				PACKET_ENCODE(UInt32, MONTH_GIFT_FLAG_NONE);
			} else {
				int day = CTime::GetDayInterval(itr->second.reward_ts, Time::GetGlobalTime());
				if (day == 0) {
					PACKET_ENCODE(UInt32, MONTH_GIFT_FLAG_REWARD);
				} else {
					PACKET_ENCODE(UInt32, MONTH_GIFT_FLAG_BUY);
				}
			}
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool MonthGiftManager::buy(uint32_t id) {
	DataMonthGift &data = m_data[id];
	data.id = id;
	if (data.end_ts > Time::GetGlobalTime()) {
		data.end_ts = CTime::GetDayBeginTime(data.end_ts + 30 * 24 * 3600) + 86400;
	} else {
		data.end_ts = CTime::GetDayBeginTime(Time::GetGlobalTime() + 30 * 24 * 3600) + 86400;
	}
	save();
	push();
	SystemMessage::getInstance()->addDeserveBag(m_player->getUid(), id);
	return true;
}

bool MonthGiftManager::doReward(CNetPacket* packet) {
	CUserMonthGiftProtocol proto;
	Award result;
	Award box;
	uint32_t lv = m_player->getLevel();
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return onReward(R_ERROR, lv, result, box);
	}
	uint32_t id = proto.id + 1;
	//valid id?
	const MonthGiftConfigItem *cfg = VipConfig::getInstance()->getGift(id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", packet->uid, id);
		return onReward(R_ERROR, lv, result, box);
	}
	DataMonthGift &data = m_data[id];
	if (data.end_ts < Time::GetGlobalTime()) {
		return onReward(R_ERROR, lv, result, box);
	}
	if (0 == CTime::GetDayInterval(data.reward_ts, Time::GetGlobalTime())) {
		return onReward(R_ERROR, lv, result, box);
	}
	data.reward_ts = Time::GetGlobalTime();
	data.id = id;
	save();
	if (cfg->box > 0) {
		Award reward;
		uint32_t boxId = (lv == 0 ? 1 : lv) * 1000 + cfg->box;
		GiftBagConfig::getInstance()->openAllLuckyBox(boxId, 1, reward);
		m_player->doReward(&reward, "month_gift_" + CTrans::ITOS(id), false, &box);
	} else {
		Award reward;
		vector<AwardInfo>::const_iterator itr = cfg->reward.get().begin();
		for (; itr != cfg->reward.get().end(); ++itr) {
			if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
				GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
			} else {
				reward.add(*itr);
			}
		}
		m_player->doReward(&reward, "month_gift_" + CTrans::ITOS(id), false, &result);
	}
	onReward(R_SUCCESS, lv, result, box);
	push();
	BUSI_MISC("resident_act|monthbag|%u|%u|%u", m_player->getUid(), id, Time::GetGlobalTime());
	return true;
}

bool MonthGiftManager::onReward(byte ret, uint32_t lv, Award &reward, Award &box) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_MONTH_GIFT_REWARD);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(UInt32, lv);
	reward.packetData(writer);
	box.packetData(writer);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
