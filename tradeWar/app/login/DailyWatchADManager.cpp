/*
 * DailyWatchADManager.h
 *
 *  Created on: 2019年 2月 27日
 *      Author: next
 */
#include "DailyWatchADManager.h"
#include "PlayerManager.h"
#include "ProtocolUser.h"
#include "WatchADConfig.h"
#include "BoatConfig.h"

DailyWatchADManager::DailyWatchADManager() {
	m_data.data[0].id = FOREVER_WATCH_ID;
	m_data.data[1].id = DAILY_WATCH_ID;
	m_data.data[2].id = RANDOM_WATCH_ID;
}

DailyWatchADManager::~DailyWatchADManager() {

}

bool DailyWatchADManager::doPacket(CNetPacket *p) {
	switch (p->subCmd) {
	case PROTOCOL_SUBCMD_WATCH_INFO:
		getInfo(p);
		break;
	case PROTOCOL_SUBCMD_WATCH_REWARD:
		setWatchRewardInfo(p);
		break;
	}
	return true;
}

bool DailyWatchADManager::load(uint32_t uid) {
	CDataState dbc;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_WATCH_AD;
	int ret = dbc.GetState(data.uid, data.id, data.data);
	if (R_SUCCESS == ret) {
		Json::Value v;
		Json::Reader r;
		if (r.parse(data.data, v) && !v.isNull() && v.isObject()) {
			m_data.fromJson(v);
		}
	} else if (R_ERR_NO_DATA == ret) {
		ret = dbc.AddState(data.uid, data.id, "");
	} else {
		error_log("get state error uid=%u id=%u", data.uid, data.id);
		return false;
	}
	return true;
}

bool DailyWatchADManager::save() {
	Json::Value v = Json::Value(Json::objectValue);
	v = m_data.toJson();

	CDataState dbc;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_WATCH_AD;
	data.data = Json::ToString(v);
	int ret = dbc.SetState(data);
	if (R_SUCCESS != ret) {
		error_log("set state error uid=%d, id=%d", data.uid, data.id);
		return false;
	}
	return true;
}

bool DailyWatchADManager::DailyReset() {
	if (CTime::GetDayInterval(m_data.ts, LogicManager::GlobalTime) == 0) {
		return false;
	}
	m_data.ts = LogicManager::GlobalTime;

	m_data.data[DAILY_WATCH_ITEM].Count = 0;
	m_data.data[DAILY_WATCH_ITEM].ReadCount = 0;
	m_data.data[DAILY_WATCH_ITEM].RewardFlg = 0;
	m_data.data[DAILY_WATCH_ITEM].RandomFlg = 0;
	m_data.data[DAILY_WATCH_ITEM].RewardTs = 0;
	m_data.data[DAILY_WATCH_ITEM].RewardId = WatchADConfig::getInstance()->getDailyRewardID(0);

	m_data.data[RANDOM_WATCH_ITEM].Count = 0;
	m_data.data[RANDOM_WATCH_ITEM].ReadCount = 0;
	m_data.data[RANDOM_WATCH_ITEM].RewardFlg = 0;
	m_data.data[RANDOM_WATCH_ITEM].RandomFlg = 0;
	m_data.data[RANDOM_WATCH_ITEM].RewardTs = 0;
	m_data.data[RANDOM_WATCH_ITEM].RewardId = 0;
	save();
	return true;
}

bool DailyWatchADManager::push() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_AD);
	writer.AppendByte(PROTOCOL_SUBCMD_WATCH_INFO);
	writer.AppendByte(WATCH_AD_TYPE_COUNT);
	for (size_t i = 0; i < WATCH_AD_TYPE_COUNT; ++i) {
		writer.AppendByte(m_data.data[i].id);
		writer.AppendByte(m_data.data[i].ReadCount);
		writer.AppendByte(m_data.data[i].RewardFlg);
		writer.AppendByte(m_data.data[i].RewardId);
		writer.AppendByte(m_data.data[i].Count);
		writer.AppendUInt32(m_data.data[i].RewardTs);
		writer.AppendByte(m_data.data[i].RandomFlg);
	}

	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool DailyWatchADManager::getInfo(CNetPacket* p) {
	DailyReset();
	push();
	return true;
}
bool DailyWatchADManager::setWatchRewardInfo(CNetPacket* p) {
	CUserWatchADProtocol proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		onResp(PROTOCOL_SUBCMD_WATCH_REWARD, 1);
		return false;
	}
	if (proto.id >= WATCH_AD_TYPE_COUNT) {
		error_log("watch_AD id error id:%d", proto.id);
		onResp(PROTOCOL_SUBCMD_WATCH_REWARD, 1);
		return false;
	}

	DailyReset();

	switch (proto.type) {
	case WATCH_COUNT_ADD:
		m_data.data[proto.id].ReadCount++;
		if (isGetReward(proto.id)) {
			m_data.data[proto.id].RewardFlg = true;
		}
		save();
		onResp(PROTOCOL_SUBCMD_WATCH_REWARD, 0);
		push();
		break;
	case WATCH_REWARD_GET:
		if (rewardGet(proto.id)) {
			onResp(PROTOCOL_SUBCMD_WATCH_REWARD, 0);
		} else {
			onResp(PROTOCOL_SUBCMD_WATCH_REWARD, 1);
		}
		push();
		break;
	default:
		error_log("watch_AD type error type:%d", proto.type);
		onResp(PROTOCOL_SUBCMD_WATCH_REWARD, 1);
		return false;
	}
	BUSI_MISC("play|wechatad|%u|%u|%u|%u", m_player->getUid(), static_cast<uint32_t>(proto.type), static_cast<uint32_t>(proto.id), Time::GetGlobalTime());
	return true;
}

bool DailyWatchADManager::onResp(byte sub, byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_AD);
	writer.AppendByte(sub);
	writer.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;
}

bool DailyWatchADManager::isGetReward(uint32_t id) {
	bool flag = false;
	switch (id) {
	case FOREVER_WATCH_ITEM:
		if (m_data.data[id].Count == 0 && m_data.data[id].ReadCount >= WatchADConfig::getInstance()->getForeverLimit()) {
			flag = true;
		}
		break;
	case DAILY_WATCH_ITEM:
		if (m_data.data[id].Count < WatchADConfig::getInstance()->getDailyRewardSize() && m_data.data[id].ReadCount >= 1) {
			flag = true;
		}
		break;
	case RANDOM_WATCH_ITEM:
		if (m_data.data[id].Count < WatchADConfig::getInstance()->getRandomRewardSize()) {
			flag = true;
		}
		break;
	}
	return flag;
}

bool DailyWatchADManager::rewardGet(uint32_t id) {
	Award reward;
	AwardInfo reward_item;
	uint32_t rate;
	uint32_t count;
	string code = "Watch_AD_" + CTrans::ITOS(id);

	if (m_data.data[id].RewardFlg == false) {
		error_log("reward flg error, id:%d", id);
		return false;
	}

	switch (id) {
	case FOREVER_WATCH_ITEM:
		WatchADConfig::getInstance()->getForeverReward(reward);
		m_player->doReward(&reward, code);
		break;
	case DAILY_WATCH_ITEM:
		WatchADConfig::getInstance()->getDailyReward(m_data.data[id].RewardId, reward);
		m_player->doReward(&reward, code);
		m_data.data[id].RewardId = WatchADConfig::getInstance()->getDailyRewardID(m_data.data[id].RewardId);
		break;
	case RANDOM_WATCH_ITEM:
		rate = WatchADConfig::getInstance()->getRandomRewardRate(m_data.data[id].RewardId);
		count = CBoatConfig::getInstance()->getReward(1, m_player->getLevel());

		reward_item.type = AWARD_TYPE_R1;
		reward_item.count = uint32_t((count * rate) / 100.0);
		reward.add(reward_item);
		m_player->doReward(&reward, code);
		break;
	default:
		error_log("watchItem ID error, id:%d", id);
		return false;
	}
	m_data.data[id].ReadCount = 0;
	m_data.data[id].RewardFlg = false;
	m_data.data[id].Count++;
	m_data.data[id].RewardTs = LogicManager::GlobalTime;
	m_data.data[id].RandomFlg = 0;
	save();
	return true;
}

bool DailyWatchADManager::isSendRandomGift() {
	if (isCdTimeOut() && !m_data.data[RANDOM_WATCH_ITEM].RandomFlg
	&& WatchADConfig::getInstance()->isGetRandomReward()
	&& m_data.data[RANDOM_WATCH_ITEM].Count < WatchADConfig::getInstance()->getRandomRewardSize()) {
		m_data.data[RANDOM_WATCH_ITEM].RandomFlg = 1;
		m_data.data[RANDOM_WATCH_ITEM].RewardId = WatchADConfig::getInstance()->getRandomRewardID();
		save();
		return true;
	} else {
		return false;
	}
}

bool DailyWatchADManager::isCdTimeOut() {
	uint32_t cd;
	WatchADConfig::getInstance()->getRandomCdTime(m_data.data[RANDOM_WATCH_ITEM].Count, cd);
	if (m_data.data[RANDOM_WATCH_ITEM].RewardTs + cd <= LogicManager::GlobalTime) {
		return true;
	} else {
		return false;
	}
}

