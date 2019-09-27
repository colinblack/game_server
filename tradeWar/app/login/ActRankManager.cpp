/*
 * ActRankManager.cpp
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#include "ActRankManager.h"
#include "PlayerManager.h"
#include "ActivityTimeManager.h"
#include "GiftBagConfig.h"
#include "LanguageConfig.h"
#include "ArenaRankManager.h"
#include <fstream>

ActRankManager::ActRankManager() {
	m_ranks.clear();
}

ActRankManager::~ActRankManager() {
}

bool ActRankManager::init() {
	do {
		string path = Config::GetValue(ACT_RANK_PATH);
		fstream input(path.c_str(), ios::in | ios::binary);
		if (!input.good()) {
			error_log("open file error path=%s", path.c_str());
			break;
		}
		ProtoRankList::ActRank msg;
		if (!msg.ParseFromIstream(&input)) {
			error_log("parse file error path=%s", path.c_str());
			break;
		}
		for (int i = 0; i < msg.ranks_size(); ++i) {
			uint32_t id = msg.ranks(i).id();
			ActRank &data = m_ranks[id];
			data.Parse(msg.ranks(i));
		}
	} while (false);
	reset();
	return true;
}

bool ActRankManager::save() {
	string path = Config::GetValue(ACT_RANK_PATH);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::ActRank msg;
	map<uint32_t, ActRank>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		itr->second.Serialize(msg.add_ranks());
	}
	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool ActRankManager::reset() {
	for (uint32_t type = ACT_RANK_TYPE_SOLDIER; type < ACT_RANK_TYPE_MAX; ++type) {
		uint32_t act_type = getActId(type);
		const ActivityTime *act = ActivityTimeManager::getInstance()->getActTime(act_type);
		if (act == NULL) {
			continue;
		}
		if (!act->IsOpen()) {
			continue;
		}
		ActRank &data = m_ranks[type];
		if (data.ver != act->ver) {
			data.id = type;
			data.ts = Time::GetGlobalTime();
			data.ver = act->ver;
			data.reward = false;
			data.data.clear();
		}
	}
	return true;
}

bool ActRankManager::getData(uint32_t type, IBuffer *buff) {
	if (type == ACT_RANK_TYPE_ARENA) {
		return ArenaRankManager::getInstance()->packetTop(buff, true);
	}
	ActRank &data = m_ranks[type];
	return data.Packet(buff);
}

bool ActRankManager::setData(uint32_t uid, uint32_t type, uint32_t v) {
	switch(type) {
	case ACT_RANK_TYPE_SOLDIER:
		return addSoldier(uid, v);
	case ACT_RANK_TYPE_EXP:
		return addExp(uid, v);
	case ACT_RANK_TYPE_POWER:
		return addPower(uid, v);
	case ACT_RANK_TYPE_BOAT:
		return addTransport(uid, v);
	case ACT_RANK_TYPE_CONSUME:
		return addConsume(uid, v);
	}
	return false;
}

bool ActRankManager::addSoldier(uint32_t uid, uint32_t v) {
	if (!isValid(ACT_RANK_TYPE_SOLDIER) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	ActRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	ActRank &rank = m_ranks[ACT_RANK_TYPE_SOLDIER];
	rank.AddItem(data);
	return true;
}

bool ActRankManager::addExp(uint32_t uid, uint32_t v) {
	if (!isValid(ACT_RANK_TYPE_EXP) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	ActRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	ActRank &rank = m_ranks[ACT_RANK_TYPE_EXP];
	rank.AddItem(data);
	return true;
}

bool ActRankManager::addPower(uint32_t uid, uint32_t v) {
	if (!isValid(ACT_RANK_TYPE_POWER) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	ActRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	ActRank &rank = m_ranks[ACT_RANK_TYPE_POWER];
	rank.AddItem(data);
	return true;
}

bool ActRankManager::addTransport(uint32_t uid, uint32_t v) {
	if (!isValid(ACT_RANK_TYPE_BOAT) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	ActRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	ActRank &rank = m_ranks[ACT_RANK_TYPE_BOAT];
	rank.AddItem(data);
	return true;
}

bool ActRankManager::addConsume(uint32_t uid, uint32_t v) {
	if (!isValid(ACT_RANK_TYPE_CONSUME) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	ActRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	ActRank &rank = m_ranks[ACT_RANK_TYPE_CONSUME];
	rank.AddItem(data);
	return true;
}

bool ActRankManager::onSecondTimer() {
	map<uint32_t, ActRank>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		uint32_t act_type = getActId(itr->first);
		bool delay = getDelay(itr->first);
		const ActivityTime *act_time = ActivityTimeManager::getInstance()->getActTime(act_type);
		if (act_time == NULL || act_time->bts >= act_time->ets) {
			continue;
		}
		if (delay) {
			if (Time::GetGlobalTime() + Time::SECOND_OF_DAY < act_time->ets) {
				continue;
			}
		} else {
			if (Time::GetGlobalTime() < act_time->ets) {
				continue;
			}
		}
		doReward(itr->first);
	}
	return true;
}

bool ActRankManager::doReward(uint32_t type) {
	ActRank &rank_data = m_ranks[type];
	if (rank_data.reward) {
		return false;
	}
	rank_data.reward = true;
	if (type == ACT_RANK_TYPE_ARENA) {
		return doArenaReward();
	}
	uint32_t rank = 1;
	list<ActRankItem>::iterator itr = rank_data.data.begin();
	for (; itr != rank_data.data.end(); ++itr, ++rank) {
		const NewServerRankConfig *cfg = GiftBagConfig::getInstance()->getActRank(type, rank);
		if (cfg == NULL) {
			error_log("cfg error type=%u", type);
			continue;
		}
		if (cfg->require > itr->value) {
			error_log("require error type=%u rank=%u require=%u hold=%u uid=%u", type, rank, cfg->require, itr->value, itr->uid);
			continue;
		}
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(itr->uid);
		if (player == NULL) {
			continue;
		}
		string title = GET_LANG("act_rank_t");
		string em_key;
		String::Format(em_key, "act_rank_%u_c", type);
		string content;
		String::Format(content, GET_LANG(em_key).c_str(), rank);
		string reward = Award::Award2String(cfg->reward.get());
		player->getEmailManager()->addEmail(itr->uid, title, content, reward);
		BUSI_MISC("timelimit_act|actrank_%u|%u|%u|%u", type, itr->uid, itr->value, Time::GetGlobalTime());
	}
	return true;
}

bool ActRankManager::doArenaReward() {
	const vector<uint32_t> &data = ArenaRankManager::getInstance()->getRankData();
	uint32_t rank = 1;
	uint32_t value = 1;
	const NewServerRankConfig *cfg = NULL;
	vector<uint32_t>::const_iterator itr = data.begin();
	for (; itr != data.end(); ++itr, ++value) {
		if (!IS_VALID_PLAYER_UID(*itr)) {
			continue;
		}
		cfg = GiftBagConfig::getInstance()->getActRank(ACT_RANK_TYPE_ARENA, rank);
		if (cfg == NULL) {
			continue;
		}
		if (cfg->require < value) {
			error_log("require error type=%u rank=%u require=%u hold=%u uid=%u", ACT_RANK_TYPE_ARENA, rank, cfg->require, value, *itr);
			continue;
		}
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(*itr);
		if (player == NULL) {
			continue;
		}
		string title = GET_LANG("act_rank_t");
		string em_key;
		String::Format(em_key, "act_rank_%u_c", ACT_RANK_TYPE_ARENA);
		string content;
		String::Format(content, GET_LANG(em_key).c_str(), rank);
		string reward = Award::Award2String(cfg->reward.get());
		player->getEmailManager()->addEmail(*itr, title, content, reward);
		++rank;
	}
	return true;
}

bool ActRankManager::isValid(uint32_t type) {
	uint32_t act_type = getActId(type);
	bool delay = getDelay(type);
	const ActivityTime *act = ActivityTimeManager::getInstance()->getActTime(act_type);
	if (act == NULL) {
		error_log("act time not exists id=%u type=%u", act_type, type);
		return false;
	}
	if (delay) {
		if (!act->IsOpen()) {
			return false;
		}
		return (Time::GetGlobalTime() + Time::SECOND_OF_DAY < act->ets);
	}
	return act->IsOpen();
}

uint32_t ActRankManager::getActId(uint32_t type) {
	switch (type) {
	case ACT_RANK_TYPE_SOLDIER:
		return e_ActivityTypeSoldierRankNew;
	case ACT_RANK_TYPE_EXP:
		return e_ActivityTypeExpRankNew;
	case ACT_RANK_TYPE_POWER:
		return e_ActivityTypePowerRankNew;
	case ACT_RANK_TYPE_BOAT:
		return e_ActivityTypeBoatRankNew;
	case ACT_RANK_TYPE_CONSUME:
		return e_ActivityTypeConsumeRankNew;
	case ACT_RANK_TYPE_ARENA:
		return e_ActivityTypeArenaRankNew;
	}
	return 0;
}
bool ActRankManager::getDelay(uint32_t type) {
	switch (type) {
	case ACT_RANK_TYPE_SOLDIER:
	case ACT_RANK_TYPE_EXP:
	case ACT_RANK_TYPE_POWER:
	case ACT_RANK_TYPE_BOAT:
	case ACT_RANK_TYPE_CONSUME:
	case ACT_RANK_TYPE_ARENA:
		return true;
	}
	return false;
}
