/*
 * DailyLoginManager.cpp
 *
 *  Created on: 2018年9月6日
 *      Author: rein
 */

#include "DailyLoginManager.h"
#include "PlayerManager.h"
#include "SevenDaysConfig.h"
#include "ProtocolUser.h"
#include "GiftBagConfig.h"

DailyLoginManager::DailyLoginManager() {
	m_sign_ts = 0;
}

DailyLoginManager::~DailyLoginManager() {
}

bool DailyLoginManager::doPacket(CNetPacket* packet) {
	return true;
}
bool DailyLoginManager::load(uint32_t uid) {
	CDataState dbc;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_ACTIVITY_LOGIN;
	int ret = dbc.GetState(data.uid, data.id, data.data);
	if (ret == 0) {
		Json::Reader reader;
		Json::Value v;
		if (reader.parse(data.data, v)) {
			if (v.isMember("r") && v["r"].isArray()) {
				for (size_t i = 0; i < v["r"].size(); ++i) {
					m_data.push_back(v["r"][i].asUInt());
				}
			}
			if (v.isMember("s") && v["s"].isArray()) {
				for (size_t i = 0; i < v["s"].size(); ++i) {
					m_sign.push_back(v["s"][i].asUInt());
				}
			}
			m_sign_ts = v.get("ts", 0).asUInt();
		}
	} else if (ret == R_ERR_NO_DATA) {
		dbc.AddState(data.uid, data.id, "");
	}

	uint32_t rewardCount = SevenDaysConfig::getInstance()->getCount();
	m_data.resize(rewardCount, 0);
	m_sign.resize(30, 0);
	return true;
}
bool DailyLoginManager::doReward(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	uint32_t id = m_player->getRegisterDay();
	Award award;

	const Award *cfg = SevenDaysConfig::getInstance()->getAward(id);
	if (cfg == NULL) {
		error_log("id error uid=%u id=%u", uid, id);
		onReward(1, 0, award);
		return false;
	}
	if (m_data.size() < id) {
		m_data.resize(id, 0);
	}
	if (m_data[id - 1] == 1) {
		error_log("reward flag error uid=%u id=%u", uid, id);
		onReward(1, 0, award);
		return false;
	}
	m_data[id - 1] = 1;

	saveData();

	Award reward;
	uint32_t reward_type = 0;
	for (vector<AwardInfo>::const_iterator itr = cfg->get().begin(); itr != cfg->get().end(); ++itr) {
		if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
			reward_type = AWARD_TYPE_BOX;
			GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
		} else {
			reward_type = itr->type;
			reward.add(*itr);
		}
	}

	m_player->doReward(&reward, "seven_day_" + CTrans::ITOS(id), false, &award);

	sendData();

	onReward(0, reward_type, reward);

	debug_log("uid=%u,id=%u", uid, id);

	return true;
}
bool DailyLoginManager::doSign(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	Award award;
	CUserDailySignProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		onSign(1, 0, award);
		return false;
	}
	uint32_t id = m_player->getRegisterDay();
	if (id < DAILY_SIGN_BEGIN_DAY) {
		error_log("id error uid=%u id=%u", uid, id);
		onSign(1, 0, award);
		return false;
	}

	resetSign();

	id = (id - DAILY_SIGN_BEGIN_DAY) % DAILY_SIGN_LOOP + 1;

	if (protocol.id > id) {
		error_log("id error uid=%u id=%u id=%u", uid, id, protocol.id);
		onSign(1, 0, award);
		return false;
	}
	const SignReward *cfg = SevenDaysConfig::getInstance()->getSign(id);
	if (cfg == NULL) {
		error_log("id error uid=%u id=%u", uid, id);
		onSign(1, 0, award);
		return false;
	}
	if (m_sign.size() < id) {
		m_sign.resize(id, 0);
	}
	if (m_sign[id - 1] == 1) {
		error_log("reward flag error uid=%u id=%u", uid, id);
		onSign(1, 0, award);
		return false;
	}
	m_sign[id - 1] = 1;

	saveData();

	Award reward;
	uint32_t reward_type = 0;
	for (vector<AwardInfo>::const_iterator itr = cfg->award.get().begin(); itr != cfg->award.get().end(); ++itr) {
		if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
			reward_type = AWARD_TYPE_BOX;
			if (cfg->type == 2) {
				reward_type = AWARD_TYPE_SOLDIER;
			}
			GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
		} else {
			reward_type = itr->type;
			reward.add(*itr);
		}
	}

	m_player->doReward(&reward, "daily_sign_" + CTrans::ITOS(id), false, &award);

	sendSign();

	onSign(0, reward_type, award);

	debug_log("uid=%u,id=%u", uid, id);

	return true;
}
bool DailyLoginManager::sendData() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_DAILY_LOGIN_INFO);
	writer.AppendUInt32(m_data.size());
	for (vector<uint32_t>::iterator itr = m_data.begin(); itr != m_data.end(); ++itr) {
		writer.AppendUInt32(*itr);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool DailyLoginManager::sendSign() {
	resetSign();
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_DAILY_SIGN_INFO);
	writer.AppendUInt32(m_sign.size());
	for (vector<byte>::iterator itr = m_sign.begin(); itr != m_sign.end(); ++itr) {
		writer.AppendUInt32(*itr);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool DailyLoginManager::saveData() {
	Json::Value v = Json::Value(Json::objectValue);

	v["r"] = Json::Value(Json::arrayValue);
	for (vector<uint32_t>::iterator itr = m_data.begin(); itr != m_data.end(); ++itr) {
		v["r"].append(*itr);
	}

	v["s"] = Json::Value(Json::arrayValue);
	for (vector<byte>::iterator itr = m_sign.begin(); itr != m_sign.end(); ++itr) {
		v["s"].append(static_cast<uint32_t>(*itr));
	}

	v["ts"] = m_sign_ts;

	CDataState dbc;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_ACTIVITY_LOGIN;
	data.data = Json::ToString(v);
	dbc.SetState(data);
	return true;
}
void DailyLoginManager::onReward(byte ret, uint32_t type, const Award &reward) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_DAILY_LOGIN_REWARD);
	writer.AppendByte(ret);
	writer.AppendUInt32(type);
	reward.packetData(writer);
	PlayerManager::getInstance()->sendToAccess(&sp);
}
void DailyLoginManager::onSign(byte ret, uint32_t type, const Award &award) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_DAILY_SIGN_REWARD);
	writer.AppendByte(ret);
	writer.AppendUInt32(type);
	award.packetData(writer);

	PlayerManager::getInstance()->sendToAccess(&sp);
}
void DailyLoginManager::resetSign() {
	uint32_t id = m_player->getRegisterDay();
	if (id < DAILY_SIGN_BEGIN_DAY) {
		return;
	}
	const DataUser &user = m_player->getUserInfo();
	uint32_t day = (id - DAILY_SIGN_BEGIN_DAY) / DAILY_SIGN_LOOP;
	uint32_t reset_ts = (day * DAILY_SIGN_LOOP + DAILY_SIGN_BEGIN_DAY - 1) * 86400 + CTime::GetDayBeginTime(user.register_time);
	if (m_sign_ts < reset_ts) {
		m_sign_ts = reset_ts;
		m_sign.clear();
		m_sign.resize(DAILY_SIGN_LOOP, 0);
	}
	debug_log("uid=%u day=%u reset_ts=%u id=%u rts=%u", user.uid, day, reset_ts, id, user.register_time);
}
