/*
 * NewServerRankManager.cpp
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#include "NewServerRankManager.h"
#include "PlayerManager.h"
#include "ActivityTimeManager.h"
#include "GiftBagConfig.h"
#include "LanguageConfig.h"
#include "WorldManager.h"
#include "ArenaRankManager.h"
#include <fstream>

NewServerRankManager::NewServerRankManager() {
	m_ts = 0;
	m_ranks.clear();
}

NewServerRankManager::~NewServerRankManager() {
}

bool NewServerRankManager::init() {
	string path = Config::GetValue(NEW_SERVER_DATA_PATH);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::NewServerRank msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	for (int i = 0; i < msg.ranks_size(); ++i) {
		uint32_t id = msg.ranks(i).id();
		NewServerRank &data = m_ranks[id];
		data.Parse(msg.ranks(i));
		debug_log("id=%u,ts=%u,ver=%u", data.id, data.ts, data.ver);
	}
	return true;
}

bool NewServerRankManager::save() {
	string path = Config::GetValue(NEW_SERVER_DATA_PATH);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}

	ProtoRankList::NewServerRank msg;
	map<uint32_t, NewServerRank>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		itr->second.Serialize(msg.add_ranks());
		debug_log("id=%u,ts=%u,ver=%u", itr->second.id, itr->second.ts, itr->second.ver);
	}

	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool NewServerRankManager::reset() {
	for (uint32_t type = NEW_SERVER_RANK_TYPE_SOLDIER; type < NEW_SERVER_RANK_TYPE_MAX; ++type) {
		uint32_t act_type = getActId(type);
		const ActivityTime *act = ActivityTimeManager::getInstance()->getActTime(act_type);
		if (act == NULL) {
			continue;
		}
		if (!act->IsOpen()) {
			continue;
		}
		NewServerRank &data = m_ranks[type];
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

bool NewServerRankManager::getData(uint32_t type, IBuffer *buff) {
	if (type == NEW_SERVER_RANK_TYPE_WORLD_BATTLE) {
		//return WorldManager::getInstance()->packetRank(buff);
		return ArenaRankManager::getInstance()->packetTop(buff, true);
	}
	NewServerRank &data = m_ranks[type];
	return data.Packet(buff);
}

bool NewServerRankManager::setData(uint32_t uid, uint32_t type, uint32_t v) {
	switch(type) {
	case NEW_SERVER_RANK_TYPE_SOLDIER:
		return addSoldier(uid, v);
	case NEW_SERVER_RANK_TYPE_EXP:
		return addExp(uid, v);
	case NEW_SERVER_RANK_TYPE_POWER:
		return addPower(uid, v);
	case NEW_SERVER_RANK_TYPE_TRANSPORT:
		return addTransport(uid, v);
	case NEW_SERVER_RANK_TYPE_CONSUME:
		return addConsume(uid, v);
	case NEW_SERVER_RANK_TYPE_GEM:
		return addGem(uid, v);
	case NEW_SERVER_RANK_TYPE_COINS:
		return addCoins(uid, v);
	}
	return false;
}

bool NewServerRankManager::addSoldier(uint32_t uid, uint32_t v) {
	if (!isValid(NEW_SERVER_RANK_TYPE_SOLDIER) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	NewServerRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	NewServerRank &transport_rank = m_ranks[NEW_SERVER_RANK_TYPE_SOLDIER];
	transport_rank.AddItem(data);
	return true;
}

bool NewServerRankManager::addExp(uint32_t uid, uint32_t v) {
	if (!isValid(NEW_SERVER_RANK_TYPE_EXP) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	NewServerRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	NewServerRank &exp_rank = m_ranks[NEW_SERVER_RANK_TYPE_EXP];
	exp_rank.AddItem(data);
	return true;
}

bool NewServerRankManager::addPower(uint32_t uid, uint32_t v) {
	if (!isValid(NEW_SERVER_RANK_TYPE_POWER) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	NewServerRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	NewServerRank &power_rank = m_ranks[NEW_SERVER_RANK_TYPE_POWER];
	power_rank.AddItem(data);
	return true;
}

bool NewServerRankManager::addTransport(uint32_t uid, uint32_t v) {
	if (!isValid(NEW_SERVER_RANK_TYPE_TRANSPORT) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	NewServerRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	NewServerRank &transport_rank = m_ranks[NEW_SERVER_RANK_TYPE_TRANSPORT];
	transport_rank.AddItem(data);
	return true;
}

bool NewServerRankManager::addConsume(uint32_t uid, uint32_t v) {
	if (!isValid(NEW_SERVER_RANK_TYPE_CONSUME) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	NewServerRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	NewServerRank &consume_rank = m_ranks[NEW_SERVER_RANK_TYPE_CONSUME];
	consume_rank.AddItem(data);
	return true;
}

bool NewServerRankManager::addGem(uint32_t uid, uint32_t v) {
	if (!isValid(NEW_SERVER_RANK_TYPE_GEM) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	NewServerRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	NewServerRank &consume_rank = m_ranks[NEW_SERVER_RANK_TYPE_GEM];
	consume_rank.AddItem(data);
	return true;
}

bool NewServerRankManager::addCoins(uint32_t uid, uint32_t v) {
	if (!isValid(NEW_SERVER_RANK_TYPE_COINS) || v == 0) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		error_log("load player error uid=%u", uid);
		return false;
	}
	const DataUser &user = player->getUserInfo();
	NewServerRankItem data;
	data.uid = uid;
	data.value = v;
	data.name = user.name;
	data.pic = user.figure_url;
	NewServerRank &coins_rank = m_ranks[NEW_SERVER_RANK_TYPE_COINS];
	coins_rank.AddItem(data);
	return true;
}

bool NewServerRankManager::onTimer() {
	if (CTime::GetDayInterval(m_ts, Time::GetGlobalTime()) != 0) {
		m_ts = Time::GetGlobalTime();
		reset();
		doReward(NEW_SERVER_RANK_TYPE_COINS, true);
	}
	map<uint32_t, NewServerRank>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		uint32_t act_type = getActId(itr->first);
		if (ActivityTimeManager::getInstance()->isEnd(act_type)) {
			doReward(itr->first, false);
		}
	}
	return true;
}

bool NewServerRankManager::doReward(uint32_t type, bool daily) {
	NewServerRank &rank_data = m_ranks[type];
	if (rank_data.reward) {
		return false;
	}
	if (daily && CTime::GetDayInterval(rank_data.ts, m_ts) == 0) {
		return false;
	}
	rank_data.reward = true;

	if (type == NEW_SERVER_RANK_TYPE_WORLD_BATTLE) {
		return doWorldBattleReward();
	}

	uint32_t rank = 1;
	list<NewServerRankItem>::iterator itr = rank_data.data.begin();
	for (; itr != rank_data.data.end(); ++itr, ++rank) {
		const NewServerRankConfig *cfg = NULL;
		if (daily) {
			uint32_t act_id = getActId(type);
			uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(act_id);
			cfg = GiftBagConfig::getInstance()->getNewSrvRank(type, rank, day - 2);
		} else {
			cfg = GiftBagConfig::getInstance()->getNewSrvRank(type, rank, 0);
		}
		if (cfg == NULL) {
			error_log("cfg error type=%u", type);
			continue;
		}
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(itr->uid);
		if (player == NULL) {
			continue;
		}
		string title = GET_LANG("new_server_rank_t");
		string em_key;
		String::Format(em_key, "new_server_rank_%u_c", type);
		string content;
		String::Format(content, GET_LANG(em_key).c_str(), rank);
		string reward = Award::Award2String(cfg->reward.get());
		player->getEmailManager()->addEmail(itr->uid, title, content, reward);
		BUSI_MISC("timelimit_act|rank_%u|%u|%u|%u", type, itr->uid, itr->value, Time::GetGlobalTime());
	}
	if (daily) {
		rank_data.Clear();
		rank_data.ts = m_ts;
	}
	debug_log("type=%u daily=%d", type, daily);
	return true;
}

bool NewServerRankManager::doWorldBattleReward() {
	const vector<uint32_t> &data = ArenaRankManager::getInstance()->getRankData();
	vector<uint32_t>::const_iterator itr = data.begin();
	uint32_t rank = 1;
	const NewServerRankConfig *cfg = NULL;
	for (; itr != data.end(); ++itr) {
		if (!IS_VALID_PLAYER_UID(*itr)) {
			continue;
		}
		cfg = GiftBagConfig::getInstance()->getNewSrvRank(NEW_SERVER_RANK_TYPE_WORLD_BATTLE, rank, 0);
		if (cfg == NULL) {
			continue;
		}
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(*itr);
		if (player == NULL) {
			continue;
		}
		string title = GET_LANG("new_server_rank_t");
		string em_key;
		String::Format(em_key, "new_server_rank_%u_c", NEW_SERVER_RANK_TYPE_WORLD_BATTLE);
		string content;
		String::Format(content, GET_LANG(em_key).c_str(), rank);
		string reward = Award::Award2String(cfg->reward.get());
		player->getEmailManager()->addEmail(*itr, title, content, reward);
		++rank;
	}
	return true;
}

bool NewServerRankManager::isValid(uint32_t type) {
	uint32_t act_type = getActId(type);
	const ActivityTime *act = ActivityTimeManager::getInstance()->getActTime(act_type);
	if (act == NULL) {
		error_log("act time not exists id=%u type=%u", act_type, type);
		return false;
	}
	return act->IsOpen();
}

uint32_t NewServerRankManager::getActId(uint32_t type) {
	switch (type) {
	case NEW_SERVER_RANK_TYPE_SOLDIER:
		return e_ActivityTypeSoldierRank;
	case NEW_SERVER_RANK_TYPE_EXP:
		return e_ActivityTypeExpRank;
	case NEW_SERVER_RANK_TYPE_POWER:
		return e_ActivityTypePowerRank;
	case NEW_SERVER_RANK_TYPE_TRANSPORT:
		return e_ActivityTypeTransportRank;
	case NEW_SERVER_RANK_TYPE_CONSUME:
		return e_ActivityTypeConsumeRank;
	case NEW_SERVER_RANK_TYPE_GEM:
		return e_ActivityTypeGemRank;
	case NEW_SERVER_RANK_TYPE_WORLD_BATTLE:
		return e_ActivityTypeWorldBattleRank;
	case NEW_SERVER_RANK_TYPE_COINS:
		return e_ActivityTypeCoinsRank;
	}
	return 0;
}
