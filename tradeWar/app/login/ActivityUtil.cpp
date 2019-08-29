/*
 * ActivityUtil.cpp
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#include "ActivityUtil.h"
#include "ActivityTimeManager.h"
#include "PlayerManager.h"
#include "NewServerRankManager.h"
#include "DataState.h"
#include "ConfigInc.h"
#include "SystemMessage.h"
#include "ActRankManager.h"
#include "ArenaRankManager.h"

ActivityUtil::ActivityUtil(uint32_t uid, uint32_t id): m_uid(uid), m_id(id), m_isNew(false), m_notify(false) {
	loadData();
	checkVer();
}

ActivityUtil::~ActivityUtil() {
}

bool ActivityUtil::doLottery(uint32_t cnt) {
	return false;
}

bool ActivityUtil::checkVer() {
	if (!ActivityTimeManager::getInstance()->isOpen(m_id)) {
		return false;
	}
	uint32_t ver = ActivityTimeManager::getInstance()->getVer(m_id);
	if (m_data.ver == ver) {
		return true;
	}
	m_data.ver = ver;
	m_data.Clear();
	return true;
}

bool ActivityUtil::loadData() {
	int ret = 0;
	CDataActivity dbc;
	ret = dbc.Get(m_uid, m_id, m_data);
	if (R_ERR_NO_DATA == ret) {
		m_isNew = true;
		m_data.uid = m_uid;
		m_data.id = m_id;
		m_data.Clear();
	} else if (0 != ret) {
		error_log("get data error uid=%u id=%u", m_uid, m_id);
		return false;
	}
	return true;
}

bool ActivityUtil::saveData() {
	int ret = 0;
	CDataActivity dbc;
	if (m_isNew) {
		ret = dbc.Add(m_data);
	} else {
		ret = dbc.Set(m_data);
	}
	if (0 != ret) {
		error_log("save data error uid=%u id=%u", m_uid, m_id);
		return false;
	}
	m_isNew = false;
	return true;
}

bool ActivityUtil::encodeData(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	PACKET_ENCODE(UInt32, ACTIVITY_DATA_LEN);
	for (int i = 0; i < ACTIVITY_DATA_LEN; ++i) {
		if (m_data.flag & (1u << i)) {
			PACKET_ENCODE(UInt32, 1);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	return true;
}

bool ActivityUtil::getRewardFlag(uint32_t index) {
	if (index > ACTIVITY_DATA_LEN) {
		return true;
	}
	return ((m_data.flag & (1u << index)) != 0);
}

bool ActivityUtil::setRewardFlag(uint32_t index) {
	if (index > ACTIVITY_DATA_LEN) {
		return false;
	}
	m_data.flag |= (1u << index);
	return true;
}

bool ActivityUtil::dailyReset() {
	if (CTime::GetDayInterval(Time::GetGlobalTime(), m_data.ts) == 0) {
		return false;
	}
	m_data.ts = Time::GetGlobalTime();
	m_data.Clear();
	return true;
}

uint32_t ActivityUtil::getChargeDay() {
	const ActivityTime *actTime = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (actTime == NULL || !actTime->IsOpen()) {
		return 0;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		return 0;
	}
	return player->getChargeHistoryManager()->getChargeDays(actTime->bts, actTime->ets);
}

uint32_t ActivityUtil::getDailyCharge() {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		return 0;
	}
	return player->getChargeHistoryManager()->getDailyCharge() / 10;
}

uint32_t ActivityUtil::getScore() {
	return m_data.score;
}

bool ActivityUtil::getLotteryResult(IBuffer *buff) {
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_lotteryId.size());
	for (unsigned i = 0; i < m_lotteryId.size(); ++i) {
		PACKET_ENCODE(UInt32, m_lotteryId[i]);
	}
	m_reward.packetData(writer);
	m_lotteryId.clear();
	m_reward.clear();
	return true;
}

bool ActivityUtil::addScore(uint32_t c) {
	m_data.score += c;
	return saveData();
}

bool ActivityUtil::setScore(uint32_t c) {
	m_data.score = c;
	return saveData();
}

bool ActivityUtil::parseReward(const Award &award) {
	m_normal.clear();
	m_box.clear();
	m_reward.clear();
	vector<AwardInfo>::const_iterator itr = award.get().begin();
	for (; itr != award.get().end(); ++itr) {
		if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
			GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, m_reward);
		} else {
			m_reward.add(*itr);
		}
	}
	for (itr = m_reward.get().begin(); itr != m_reward.get().end(); ++itr) {
		if (itr->type == AWARD_TYPE_SOLDIER || itr->type == AWARD_TYPE_SKILL) {
			m_box.add(*itr);
		} else {
			m_normal.add(*itr);
		}
	}
	return true;
}

bool ActivityUtil::getReward(IBuffer *buff) {
	CBufferWriter writer(buff);
	m_normal.packetData(writer);
	m_box.packetData(writer);
	m_normal.clear();
	m_box.clear();
	return true;
}

bool ActivityUtil::canReward() {
	return false;
}

bool ActivityUtil::getNotify() {
	return m_notify;
}
bool ActivityUtil::setNotify(bool f) {
	m_notify = f;
	return true;
}

bool ActNewSrvRankBase::doReward(uint32_t index) {
	if (!ActivityTimeManager::getInstance()->isOpen(m_id)) {
		error_log("act is close uid=%u id=%u index=%u", m_uid, m_id, index);
		return false;
	}
	if (index >= ACTIVITY_DATA_LEN) {
		error_log("param error uid=%u id=%u", m_uid, index);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u id=%u", m_uid, index);
		return false;
	}
	const NewServerRankConfig *cfg = reinterpret_cast<const NewServerRankConfig*>(getConfig(index + 1));
	if (cfg == NULL) {
		error_log("load cfg error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (m_daily) {
		dailyReset();
	}
	if (getRewardFlag(index)) {
		error_log("reward flag error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (!parseReward(cfg->reward)) {
		error_log("parse reward error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (m_data.score < cfg->require) {
		error_log("require error uid=%u id=%u index=%u score=%u require=%u rid=%u",
				m_uid, m_id, index, m_data.score, cfg->require, m_rank_id);
		return false;
	}
	if (!setRewardFlag(index)) {
		error_log("set flag error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (!saveData()) {
		error_log("save data error uid=%u id=%u", m_uid, index);
		return false;
	}
	string code = "act_rank_" + CTrans::ITOS(m_rank_id) + "_" + CTrans::ITOS(index);
	if (!player->doReward(&m_reward, code)) {
		error_log("reward error uid=%u id=%u", m_uid, index);
		return false;
	}
	return true;
}
bool ActNewSrvRankBase::encodeData(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	if (m_daily) {
		dailyReset();
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	if (m_new_srv) {
		NewServerRankManager::getInstance()->getData(m_rank_id, buff);
	} else {
		ActRankManager::getInstance()->getData(m_rank_id, buff);
	}
	PACKET_ENCODE(UInt32, m_data.score);
	PACKET_ENCODE(UInt32, 1);
	for (int i = 0; i < 1; ++i) {
		if (m_data.flag & (1u << i)) {
			PACKET_ENCODE(UInt32, 1);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	return true;
}
bool ActNewSrvRankBase::addScore(uint32_t c) {
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL || !act_time->IsOpen()) {
		return false;
	}
	if (m_delay && Time::GetGlobalTime() + Time::SECOND_OF_DAY >= act_time->ets) {
		return false;
	}
	if (m_daily) {
		dailyReset();
	}
	if (c == 0) {
		return false;
	}
	m_data.score += c;
	saveData();
	if (m_new_srv) {
		NewServerRankManager::getInstance()->setData(m_uid, m_rank_id, m_data.score);
	} else {
		ActRankManager::getInstance()->setData(m_uid, m_rank_id, m_data.score);
	}
	if (getNotify()) {
		return true;
	}
	if (!canReward()) {
		return true;
	}
	setNotify(true);
	set<uint32_t> ids;
	ids.insert(m_id);
	ActivityManager::sendAllData(m_uid, ids);
	return true;
}
bool ActNewSrvRankBase::setScore(uint32_t c) {
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL || !act_time->IsOpen()) {
		return false;
	}
	if (m_delay && Time::GetGlobalTime() + Time::SECOND_OF_DAY >= act_time->ets) {
		return false;
	}
	if (m_daily) {
		dailyReset();
	}
	m_data.score = c;
	saveData();
	if (m_new_srv) {
		NewServerRankManager::getInstance()->setData(m_uid, m_rank_id, m_data.score);
	} else {
		ActRankManager::getInstance()->setData(m_uid, m_rank_id, m_data.score);
	}
	if (getNotify()) {
		return true;
	}
	if (!canReward()) {
		return true;
	}
	setNotify(true);
	set<uint32_t> ids;
	ids.insert(m_id);
	ActivityManager::sendAllData(m_uid, ids);
	return true;
}
const void* ActNewSrvRankBase::getConfig(uint32_t index) {
	return GiftBagConfig::getInstance()->getNewSrvTar(m_rank_id, index, 0);
}
bool ActNewSrvRankBase::canReward() {
	return false;
	/*
	uint32_t index = 0;
	const NewServerRankConfig *cfg = reinterpret_cast<const NewServerRankConfig*>(getConfig(index + 1));
	if (cfg == NULL) {
		error_log("load cfg error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (getRewardFlag(index)) {
		return false;
	}
	return m_data.score >= cfg->require;
	*/
}

bool ActPowerRank::addScore(uint32_t c) {
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL || !act_time->IsOpen()) {
		return false;
	}
	if (m_delay && Time::GetGlobalTime() + Time::SECOND_OF_DAY >= act_time->ets) {
		return false;
	}
	if (m_daily) {
		dailyReset();
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		return false;
	}
	bool chg = false;
	if (m_data.flag == 0) {
		m_data.flag = player->getUserCombat();
		chg = true;
	} else {
		if (player->getUserCombat() > m_data.flag) {
			c = player->getUserCombat() - m_data.flag;
		} else {
			c = 0;
		}
	}
	if (c > m_data.score) {
		m_data.score = c;
		chg = true;
	}
	if (!chg) {
		return true;
	}
	saveData();
	if (m_new_srv) {
		NewServerRankManager::getInstance()->setData(m_uid, m_rank_id, m_data.score);
	} else {
		ActRankManager::getInstance()->setData(m_uid, m_rank_id, m_data.score);
	}
	if (getNotify()) {
		return true;
	}
	if (!canReward()) {
		return true;
	}
	setNotify(true);
	set<uint32_t> ids;
	ids.insert(m_id);
	ActivityManager::sendAllData(m_uid, ids);
	return true;
}

bool ActArenaRank::encodeData(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	ActRankManager::getInstance()->getData(m_rank_id, buff);
	m_data.score = ArenaRankManager::getInstance()->getUserRank(m_uid);
	PACKET_ENCODE(UInt32, m_data.score);
	PACKET_ENCODE(UInt32, 1);
	for (int i = 0; i < 1; ++i) {
		if (m_data.flag & (1u << i)) {
			PACKET_ENCODE(UInt32, 1);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	return true;
}

const void* ActNewSrvCoinsRank::getConfig(uint32_t index) {
	uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(m_id);
	return GiftBagConfig::getInstance()->getNewSrvTar(m_rank_id, index, day - 1);
}

ActSevenTask::ActSevenTask(uint32_t uid): ActivityUtil(uid, e_ActivityTypeSevenTask) {
	m_uid = uid;
	m_id = e_ActivityTypeSevenTask;
	loadData();
	checkVer();
}
bool ActSevenTask::doLevelReward(uint32_t type, uint32_t index) {
	checkVer();
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL) {
		error_log("get act time error id=%u", m_id);
		return false;
	}
	if (type == 0) {
		if (m_act_data.free_reward & (1u << index)) {
			error_log("reward flag error uid=%u id=%u", m_uid, index);
			return false;
		}
		const OpenServerConfigReward *cfg = OpenServerConfig::getInstance()->getReward(act_time->type, index + 1, type);
		if (cfg == NULL) {
			error_log("cfg error uid=%u id=%u", m_uid, index);
			return false;
		}
		if (m_act_data.score < (index + 1) * 1000) {
			error_log("require error uid=%u id=%u score=%u", m_uid, index, m_act_data.score);
			return false;
		}
		m_act_data.free_reward |= (1u << index);
		Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
		if (player == NULL) {
			error_log("load player error uid=%u id=%u", m_uid, index);
			return false;
		}
		Award reward;
		for (vector<AwardInfo>::const_iterator itr = cfg->reward.get().begin(); itr != cfg->reward.get().end(); ++itr) {
			if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
				GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
				continue;
			}
			reward.add(*itr);
		}
		player->doReward(&reward, "act_" + CTrans::ITOS(m_id) + "_" + CTrans::ITOS(type) + "_" + CTrans::ITOS(index));
	} else {
		if (m_act_data.buy_flag == 0) {
			error_log("buy flag error uid=%u id=%u", m_uid, index);
			return false;
		}
		if (m_act_data.buy_reward & (1u << index)) {
			error_log("reward flag error uid=%u id=%u", m_uid, index);
			return false;
		}
		const OpenServerConfigReward *cfg = OpenServerConfig::getInstance()->getReward(act_time->type, index + 1, type);
		if (cfg == NULL) {
			error_log("cfg error uid=%u id=%u", m_uid, index);
			return false;
		}
		if (m_act_data.score < (index + 1) * 1000) {
			error_log("require error uid=%u id=%u score=%u", m_uid, index, m_act_data.score);
			return false;
		}
		m_act_data.buy_reward |= (1u << index);
		Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
		if (player == NULL) {
			error_log("load player error uid=%u id=%u", m_uid, index);
			return false;
		}
		Award reward;
		for (vector<AwardInfo>::const_iterator itr = cfg->reward.get().begin(); itr != cfg->reward.get().end(); ++itr) {
			if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
				GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
				continue;
			}
			reward.add(*itr);
		}
		player->doReward(&reward, "act_" + CTrans::ITOS(m_id) + "_" + CTrans::ITOS(type) + "_" + CTrans::ITOS(index));
	}
	return true;
}
bool ActSevenTask::doQuestReward(bool daily, uint32_t id) {
	checkVer();
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL) {
		error_log("get act time error id=%u", m_id);
		return false;
	}
	if (daily) {
		const OpenServerConfigTask *cfg = OpenServerConfig::getInstance()->getDaily(act_time->type, id);
		if (cfg == NULL || cfg->require.empty() || cfg->reward.empty()) {
			error_log("cfg error uid=%u id=%u", m_uid, id);
			return false;
		}
		uint32_t require = cfg->require.front();
		for (int i = 0; i < ActSevenTaskDailyLen; ++i) {
			if (m_act_data.daily[i].id != id) {
				continue;
			}
			if (m_act_data.daily[i].count < require || m_act_data.daily[i].reward == 1) {
				error_log("cfg error uid=%u id=%u cnt=%u need=%u f=%u",
						m_uid, id, m_act_data.daily[i].count, require, static_cast<uint32_t>(m_act_data.daily[i].reward));
				return false;
			}
			m_act_data.daily[i].reward = 1;
			m_act_data.score += cfg->reward.front();
			return true;
		}
	} else {
		const OpenServerConfigTask *cfg = OpenServerConfig::getInstance()->getWeek(act_time->type, id);
		if (cfg == NULL || cfg->require.empty() || cfg->reward.empty() || id >= ActSevenTaskWeekLen) {
			error_log("cfg error uid=%u id=%u", m_uid, id);
			return false;
		}
		ActDataSevenTaskWeek &w = m_act_data.week[id];
		uint32_t c = 0;
		OpenServerConfig::getInstance()->getWeekClass(act_time->type, id, w.cnt, c);
		if (c <= w.lv) {
			error_log("level error uid=%u id=%u c=%u lv=%u", m_uid, id, c, w.lv);
			return false;
		}
		m_act_data.score += *(cfg->reward.begin() + w.lv);
		w.lv += 1;
		return true;
	}
	return false;
}
bool ActSevenTask::doBuyScore() {
	checkVer();
	MoneyCost cost;
	cost.cash = 80;
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u", m_uid);
		return false;
	}
	if (!player->getRm()->useMoney(cost, "act_" + CTrans::ITOS(m_id) + "_buy")) {
		error_log("use money error uid=%u", m_uid);
		return false;
	}
	m_act_data.score += 1000;
	saveData();
	return true;
}
bool ActSevenTask::doAddCount(uint32_t id, uint32_t count, bool daily) {
	checkVer();
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL) {
		error_log("get act time error id=%u", m_id);
		return false;
	}
	if (daily) {
		const OpenServerConfigTask *cfg = OpenServerConfig::getInstance()->getDaily(act_time->type, id);
		if (cfg == NULL || cfg->require.empty()) {
			error_log("cfg error uid=%u id=%u", m_uid, id);
			return false;
		}
		uint32_t require = cfg->require.front();
		for (int i = 0; i < ActSevenTaskDailyLen; ++i) {
			if (m_act_data.daily[i].id == id) {
				if (m_act_data.daily[i].count >= require) {
					return true;
				}
				m_act_data.daily[i].count += count;
				if (m_act_data.daily[i].count > require) {
					m_act_data.daily[i].count = require;
				}
				return true;
			}
		}
	} else {
		const OpenServerConfigTask *cfg = OpenServerConfig::getInstance()->getWeek(act_time->type, id);
		if (cfg == NULL || cfg->require.empty() || id >= ActSevenTaskWeekLen) {
			return false;
		}
		uint32_t require = cfg->require.back();
		if (m_act_data.week[id].cnt >= require) {
			return true;
		}
		m_act_data.week[id].cnt += count;
		if (m_act_data.week[id].cnt > require) {
			m_act_data.week[id].cnt = require;
		}
		return true;
	}
	return false;
}
bool ActSevenTask::doQuest(uint32_t quest, uint32_t cnt) {
	checkVer();
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL) {
		error_log("get act time error id=%u", m_id);
		return false;
	}
	bool chg = false;
	for (int i = 0; i < ActSevenTaskDailyLen; ++i) {
		const OpenServerConfigTask *cfg = OpenServerConfig::getInstance()->getDaily(act_time->type, m_act_data.daily[i].id);
		if (cfg == NULL || cfg->type != quest || cfg->require.empty()) {
			continue;
		}
		uint32_t require = cfg->require.front();
		if (m_act_data.daily[i].count >= require) {
			continue;
		}
		m_act_data.daily[i].count += cnt;
		if (m_act_data.daily[i].count > require) {
			m_act_data.daily[i].count = require;
		}
		chg = true;
	}
	for (int i = 0; i < ActSevenTaskWeekLen; ++i) {
		const OpenServerConfigTask *cfg = OpenServerConfig::getInstance()->getWeek(act_time->type, i);
		if (cfg == NULL || cfg->type != quest || cfg->require.empty()) {
			continue;
		}
		uint32_t require = cfg->require.back();
		if (m_act_data.week[i].cnt >= require) {
			continue;
		}
		m_act_data.week[i].cnt += cnt;
		if (m_act_data.week[i].cnt > require) {
			m_act_data.week[i].cnt = require;
		}
		chg = true;
	}
	if (chg) {
		saveData();
	}
	return chg;
}
bool ActSevenTask::setBuyFlag() {
	if (m_act_data.buy_flag == 1) {
		return false;
	}
	m_act_data.buy_flag = 1;
	saveData();
	return true;
}
bool ActSevenTask::checkVer() {
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL || !act_time->IsOpen()) {
		return false;
	}
	uint32_t ver = act_time->ver;
	if (m_act_data.ver != ver) {
		m_act_data.Clear();
		m_act_data.ver = ver;
	}
	if (CTime::GetDayInterval(m_act_data.ts, Time::GetGlobalTime()) != 0) {
		m_act_data.ts = Time::GetGlobalTime();
		set<uint32_t> ids;
		if (!OpenServerConfig::getInstance()->randomDaily(act_time->type, ids)) {
			error_log("randomDaily error");
		} else {
			int i = 0;
			for (set<uint32_t>::iterator itr = ids.begin(); itr != ids.end() && i < ActSevenTaskDailyLen; ++itr, ++i) {
				m_act_data.daily[i].id = *itr;
				m_act_data.daily[i].count = 0;
				m_act_data.daily[i].reward = 0;
			}
		}
		saveData();
	}
	return true;
}
bool ActSevenTask::loadData() {
	CDataState dbc;
	DataState data;
	data.uid = m_uid;
	data.id = PLAYER_DATA_STATE_SEVEN_TASK;
	int ret = dbc.GetState(data.uid, data.id, data.data);
	if (0 == ret) {
		Json::Value v;
		Json::Reader reader;
		if (reader.parse(data.data, v)) {
			m_act_data.buy_flag = v.get("f", 0).asUInt();
			m_act_data.score = v.get("s", 0).asUInt();
			m_act_data.ver = v.get("v", 0).asUInt();
			m_act_data.ts = v.get("t", 0).asUInt();
			m_act_data.free_reward = v.get("fr", 0).asUInt();
			m_act_data.buy_reward = v.get("br", 0).asUInt();
			if (v.isMember("w") && v["w"].isArray()) {
				for (size_t i = 0; i < v["w"].size() && i < ActSevenTaskWeekLen; ++i) {
					m_act_data.week[i].cnt = v["w"][i].get("c", 0).asUInt();
					m_act_data.week[i].lv = v["w"][i].get("l", 0).asUInt();
				}
			}
			if (v.isMember("d") && v["d"].isArray()) {
				for (size_t i = 0; i < v["d"].size() && i < ActSevenTaskDailyLen; ++i) {
					m_act_data.daily[i].id = v["d"][i].get("id", 0).asUInt();
					m_act_data.daily[i].count = v["d"][i].get("c", 0).asUInt();
					m_act_data.daily[i].reward = v["d"][i].get("r", 0).asUInt();
				}
			}
		}
		m_isNew = false;
	} else if (R_ERR_NO_DATA == ret) {
		m_isNew = true;
	} else {
		error_log("load data error uid=%u id=%u", m_uid, m_id);
		return false;
	}
	return true;
}
bool ActSevenTask::saveData() {
	int ret = 0;
	Json::Value v;
	v["f"] = m_act_data.buy_flag;
	v["s"] = m_act_data.score;
	v["v"] = m_act_data.ver;
	v["ts"] = m_act_data.ts;
	v["fr"] = m_act_data.free_reward;
	v["br"] = m_act_data.buy_reward;
	v["w"] = Json::Value(Json::arrayValue);
	v["d"] = Json::Value(Json::arrayValue);
	for (int i = 0; i < ActSevenTaskWeekLen; ++i) {
		v["w"][i]["c"] = m_act_data.week[i].cnt;
		v["w"][i]["l"] = m_act_data.week[i].lv;
	}
	for (int i = 0; i < ActSevenTaskDailyLen; ++i) {
		v["d"][i]["id"] = m_act_data.daily[i].id;
		v["d"][i]["c"] = m_act_data.daily[i].count;
		v["d"][i]["r"] = m_act_data.daily[i].reward;
	}
	CDataState dbc;
	DataState data;
	data.uid = m_uid;
	data.id = PLAYER_DATA_STATE_SEVEN_TASK;
	data.data = Json::ToString(v);
	if (m_isNew) {
		ret = dbc.AddState(data);
		m_isNew = false;
	} else {
		ret = dbc.SetState(data);
	}
	if (ret) {
		error_log("set data error uid=%u id=%u", m_uid, m_id);
		return false;
	}
	return true;
}
bool ActSevenTask::encodeData(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	checkVer();
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_id);
	PACKET_ENCODE(UInt32, m_act_data.ver);
	PACKET_ENCODE(UInt32, m_act_data.buy_flag);
	PACKET_ENCODE(UInt32, m_act_data.score);
	PACKET_ENCODE(UInt32, ActSevenTaskDailyLen);
	for (int i = 0; i < ActSevenTaskDailyLen; ++i) {
		PACKET_ENCODE(UInt32, m_act_data.daily[i].id);
		PACKET_ENCODE(UInt32, m_act_data.daily[i].count);
		PACKET_ENCODE(UInt32, m_act_data.daily[i].reward);
	}
	PACKET_ENCODE(UInt32, ActSevenTaskWeekLen);
	for (int i = 0; i < ActSevenTaskWeekLen; ++i) {
		PACKET_ENCODE(UInt32, m_act_data.week[i].cnt);
		PACKET_ENCODE(UInt32, m_act_data.week[i].lv);
	}
	PACKET_ENCODE(UInt32, m_act_data.free_reward);
	PACKET_ENCODE(UInt32, m_act_data.buy_reward);
	return true;
}

bool ActDailyBuyBag::doReward(uint32_t index) {
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL || !act_time->IsOpen()) {
		error_log("act is close uid=%u id=%u index=%u", m_uid, m_id, index);
		return false;
	}
	if (m_new_srv) {
		dailyReset();
	}
	if (m_data.flag == 1) {
		error_log("buy flag error uid=%u", m_uid);
		return false;
	}
	uint32_t day = act_time->type;
	if (m_new_srv) {
		day = act_time->OpenDay();
	}
	const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getDailyBuyBag(day, !m_new_srv);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", m_uid, day);
		return false;
	}
	if (!parseReward(cfg->award)) {
		error_log("parse award error uid=%u id=%u", m_uid, day);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u id=%u", m_uid, day);
		return false;
	}
	MoneyCost cost;
	cost.cash = cfg->require;
	string code = "act_daily_buy_bag_" + CTrans::ITOS(day);
	if (!player->getRm()->useMoney(cost, code)) {
		error_log("use money error uid=%u id=%u cost=%u", m_uid, day, cost.cash);
		return false;
	}
	m_data.flag = 1;
	if (!saveData()) {
		error_log("save data error uid=%u id=%u", m_uid, day);
		return false;
	}
	//第一天用开宝箱的形式
	Award reward_result;
	if (day == 1) {
		if (!player->doReward(&m_reward, code, false, &reward_result)) {
			error_log("reward error uid=%u id=%u", m_uid, day);
			return false;
		}
	} else {
		if (!player->doReward(&m_reward, code, true, &reward_result)) {
			error_log("reward error uid=%u id=%u", m_uid, day);
			return false;
		}
		m_normal.clear();
		m_box.clear();
	}
	SystemMessage::getInstance()->addTimeLimitBag(m_uid, cfg->award.get().front().id, &reward_result);
	BUSI_MISC("timelimit_act|dailybag|%u|%u|%u", m_uid, day, Time::GetGlobalTime());
	return true;
}
bool ActDailyBuyBag::encodeData(IBuffer *buff) {
	if (m_new_srv) {
		dailyReset();
	}
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	PACKET_ENCODE(UInt32, m_data.flag);
	PACKET_ENCODE(UInt32, 0);
	PACKET_ENCODE(UInt32, 0);
	return true;
}
bool ActDailyBuyBag::canReward() {
	return m_data.flag == 0;
}
bool ActDailyBuyBag::getReward(IBuffer *buff) {
	uint32_t rs = buff->GetSize();
	if (rs > 8) {
		buff->SetSize(rs - 8);
	}
	CBufferWriter writer(buff);
	m_normal.packetData(writer);
	m_box.packetData(writer);
	m_normal.clear();
	m_box.clear();
	return true;
}

bool ActDailyChargeEquip::doReward(uint32_t index) {
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL || !act_time->IsOpen()) {
		error_log("act is close uid=%u id=%u index=%u", m_uid, m_id, index);
		return false;
	}
	dailyReset();
	uint32_t day = act_time->type;
	if (m_new_srv) {
		day = act_time->OpenDay();
	}
	const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getDailyChargeEquip(day, index + 1, !m_new_srv);
	if (cfg == NULL) {
		error_log("cfg error uid=%u day=%u id=%u", m_uid, day, index);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (m_data.flag & (1u << index)) {
		error_log("flag error uid=%u id=%u", m_uid, index);
		return false;
	}
	uint32_t score = player->getChargeHistoryManager()->getDailyCharge();
	if (cfg->require > score) {
		error_log("require error uid=%u day=%u id=%u need=%u hold=%u", m_uid, day, index, cfg->require, score);
		return false;
	}
	if (!parseReward(cfg->award)) {
		error_log("parse reward error uid=%u id=%u", m_uid, index);
		return false;
	}
	m_data.flag |= 1u << index;
	if (!saveData()) {
		error_log("save data error uid=%u id=%u", m_uid, index);
		return false;
	}
	string code = "act_daily_charge_equip_" + CTrans::ITOS(day) + "_" + CTrans::ITOS(index);
	player->doReward(&m_reward, code);
	BUSI_MISC("timelimit_act|dailychargeequip|%u|%u|%u", m_uid, index + 1, Time::GetGlobalTime());
	return true;
}
bool ActDailyChargeEquip::encodeData(IBuffer *buff) {
	dailyReset();
	uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(m_id);
	uint32_t len = GiftBagConfig::getInstance()->getDailyChargeEquipSize(day, !m_new_srv);
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	PACKET_ENCODE(UInt32, getDailyCharge());
	PACKET_ENCODE(UInt32, len);
	for (uint32_t i = 0; i < len; ++i) {
		if (m_data.flag & (1u << i)) {
			PACKET_ENCODE(UInt32, 1);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	return true;
}
bool ActDailyChargeEquip::canReward() {
	dailyReset();
	uint32_t score = getDailyCharge();
	uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(m_id);
	uint32_t len = GiftBagConfig::getInstance()->getDailyChargeEquipSize(day, !m_new_srv);
	for (uint32_t i = 0; i < len; ++i) {
		const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getDailyChargeEquip(day, i + 1, !m_new_srv);
		if (cfg == NULL) {
			continue;
		}
		if (!getRewardFlag(i) && score >= cfg->require) {
			return true;
		}
	}
	return false;
}

bool ActDailyChargeCash::doReward(uint32_t index) {
	const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(m_id);
	if (act_time == NULL || !act_time->IsOpen()) {
		error_log("act is close uid=%u id=%u index=%u", m_uid, m_id, index);
		return false;
	}
	dailyReset();
	uint32_t day = act_time->type;
	if (m_new_srv) {
		day = act_time->OpenDay();
	}
	const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getDailyChargeCash(day, index + 1, !m_new_srv);
	if (cfg == NULL) {
		error_log("cfg error uid=%u day=%u id=%u", m_uid, day, index);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (m_data.flag & (1u << index)) {
		error_log("flag error uid=%u id=%u", m_uid, index);
		return false;
	}
	uint32_t score = player->getChargeHistoryManager()->getDailyCharge();
	if (cfg->require > score) {
		error_log("require error uid=%u day=%u id=%u need=%u hold=%u", m_uid, day, index, cfg->require, score);
		return false;
	}
	if (!parseReward(cfg->award)) {
		error_log("parse reward error uid=%u id=%u", m_uid, index);
		return false;
	}
	m_data.flag |= 1u << index;
	if (!saveData()) {
		error_log("save data error uid=%u id=%u", m_uid, index);
		return false;
	}
	string code = "act_daily_charge_cash_" + CTrans::ITOS(day) + "_" + CTrans::ITOS(index);
	if (!player->doReward(&m_reward, code)) {
		error_log("reward error uid=%u id=%u", m_uid, index);
		return false;
	}
	BUSI_MISC("timelimit_act|dailychargecash|%u|%u|%u", m_uid, index + 1, Time::GetGlobalTime());
	return true;
}
bool ActDailyChargeCash::encodeData(IBuffer *buff) {
	dailyReset();
	uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(m_id);
	uint32_t len = GiftBagConfig::getInstance()->getDailyChargeCashSize(day, !m_new_srv);
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	PACKET_ENCODE(UInt32, getDailyCharge());
	PACKET_ENCODE(UInt32, len);
	for (uint32_t i = 0; i < len; ++i) {
		if (m_data.flag & (1u << i)) {
			PACKET_ENCODE(UInt32, 1);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	return true;
}
bool ActDailyChargeCash::canReward() {
	dailyReset();
	uint32_t score = getDailyCharge();
	uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(m_id);
	uint32_t len = GiftBagConfig::getInstance()->getDailyChargeCashSize(day, !m_new_srv);
	for (uint32_t i = 0; i < len; ++i) {
		const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getDailyChargeCash(day, i + 1, !m_new_srv);
		if (cfg == NULL) {
			continue;
		}
		if (!getRewardFlag(i) && score >= cfg->require) {
			return true;
		}
	}
	return false;
}

bool ActContinueCharge::doReward(uint32_t index) {
	if (!ActivityTimeManager::getInstance()->isOpen(m_id)) {
		error_log("act is close uid=%u id=%u index=%u", m_uid, m_id, index);
		return false;
	}
	const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getContinueCharge(index + 1, !m_new_srv);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (getRewardFlag(index)) {
		error_log("flag error uid=%u id=%u", m_uid, index);
		return false;
	}
	uint32_t day = getChargeDay();
	if (day < cfg->require) {
		error_log("require error uid=%u id=%u need=%u hold=%u", m_uid, index, cfg->require, day);
		return false;
	}
	setRewardFlag(index);
	if (!saveData()) {
		error_log("save error uid=%u id=%u", m_uid, index);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (!parseReward(cfg->award)) {
		error_log("parse reward error uid=%u id=%u", m_uid, index);
		return false;
	}
	if (!player->doReward(&m_reward, "act_continue_charge_" + CTrans::ITOS(index))) {
		error_log("reward error uid=%u id=%u", m_uid, index);
		return false;
	}
	BUSI_MISC("timelimit_act|chargeday|%u|%u|%u", m_uid, index + 1, Time::GetGlobalTime());
	return true;
}
bool ActContinueCharge::encodeData(IBuffer *buff) {
	uint32_t day = getChargeDay();
	uint32_t len = GiftBagConfig::getInstance()->getContinueChargeSize(!m_new_srv);
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	PACKET_ENCODE(UInt32, day);
	PACKET_ENCODE(UInt32, len);
	for (uint32_t i = 0; i < len; ++i) {
		if (m_data.flag & (1u << i)) {
			PACKET_ENCODE(UInt32, 1);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	return true;
}
bool ActContinueCharge::canReward() {
	uint32_t day = getChargeDay();
	uint32_t len = GiftBagConfig::getInstance()->getContinueChargeSize(!m_new_srv);
	for (uint32_t i = 0; i < len; ++i) {
		const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getContinueCharge(i + 1, !m_new_srv);
		if (cfg == NULL) {
			continue;
		}
		if (!getRewardFlag(i) && day >= cfg->require) {
			return true;
		}
	}
	return false;
}

bool ActLuckyLottery::doReward(uint32_t index) {
	return false;
}

bool ActLuckyLottery::doLottery(uint32_t cnt) {
	if (!ActivityTimeManager::getInstance()->isOpen(m_id)) {
		error_log("act is close uid=%u id=%u count=%u", m_uid, m_id, cnt);
		return false;
	}
	m_lotteryId.clear();
	m_reward.clear();
	if (cnt != 1 && cnt != 10) {
		error_log("count error uid=%u count=%u", m_uid, cnt);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u", m_uid);
		return false;
	}
	uint32_t lottery_num = m_data.score;
	Award reward;
	for (unsigned i = 0; i < cnt; ++i) {
		int id = -1;
		if (lottery_num == GiftBagConfig::getInstance()->getLuckyLotteryLuckyCount()) {
			id = GiftBagConfig::getInstance()->getLuckyLotteryLuckyId();
			lottery_num = 0;
		} else {
			id = GiftBagConfig::getInstance()->randomLuckyLottery();
		}
		if (id == -1) {
			error_log("random error uid=%u", m_uid);
			return false;
		}
		const Award* cfg = GiftBagConfig::getInstance()->getLuckyLotteryReward(id - 1);
		if (cfg == NULL) {
			error_log("cfg error uid=%u id=%d", m_uid, id);
			return false;
		}
		vector<AwardInfo>::const_iterator itr = cfg->get().begin();
		for (; itr != cfg->get().end(); ++itr) {
			reward.add(*itr);
		}
		++lottery_num;
		m_lotteryId.push_back(id);
	}
	string code = "act_lucky_lottery";
	MoneyCost cost;
	if (cnt == 1) {
		cost.cash = GiftBagConfig::getInstance()->getLuckyLotteryCost(false);
		if (player->getEm()->checkItemEnough(603u, 1) && player->getEm()->useBagItemByType(603u, 1, code)) {
			cost.cash = 0;
		}
	} else {
		cost.cash = GiftBagConfig::getInstance()->getLuckyLotteryCost(true);
	}
	if (cost.cash > 0 && !player->getRm()->useMoney(cost, code)) {
		error_log("cost error uid=%u", m_uid);
		return false;
	}
	if (!parseReward(reward)) {
		error_log("parse reward error uid=%u", m_uid);
		return false;
	}
	if (!player->doReward(&m_reward, code, false, &m_reward)) {
		error_log("reward error uid=%u", m_uid);
		return false;
	}
	m_data.score = lottery_num;
	saveData();
	debug_log("uid=%u,len=%u", m_uid, m_lotteryId.size());
	BUSI_MISC("timelimit_act|luckylottery|%u|%u|%u", m_uid, cost.cash, Time::GetGlobalTime());
	return true;
}

bool ActLuckyLottery::encodeData(IBuffer *buff) {
	CBufferWriter writer(buff);
	PACKET_ENCODE(UInt32, m_data.id);
	PACKET_ENCODE(UInt32, m_data.ver);
	PACKET_ENCODE(UInt32, m_data.score);
	return true;
}
