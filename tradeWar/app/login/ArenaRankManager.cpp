/*
 * ArenaRankManager.cpp
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#include "ArenaRankManager.h"
#include "PlayerManager.h"
#include "ArenaConfig.h"
#include "LanguageConfig.h"
#include <fstream>

ArenaRankManager::ArenaRankManager() {
	m_flag = false;
}
ArenaRankManager::~ArenaRankManager() {
}
bool ArenaRankManager::init() {
	do {
		string path = Config::GetValue(ARENA_RANK_PATH);
		fstream input(path.c_str(), ios::in | ios::binary);
		if (!input.good()) {
			error_log("open file error path=%s", path.c_str());
			break;
		}
		ProtoRankList::ArenaRank msg;
		if (!msg.ParseFromIstream(&input)) {
			error_log("parse file error path=%s", path.c_str());
			break;
		}
		m_flag = msg.flag();
		for (int i = 0; i < msg.ranks_size(); ++i) {
			uint32_t uid = msg.ranks(i);
			if (IS_VALID_PLAYER_UID(uid)) {
				m_userHash.insert(make_pair(uid, m_ranks.size() + 1));
			}
			m_ranks.push_back(uid);
		}
	} while(false);
	m_ranks.resize(ARENA_RANK_MAX, 0);
	return true;
}
bool ArenaRankManager::save() {
	string path = Config::GetValue(ARENA_RANK_PATH);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::ArenaRank msg;
	msg.set_flag(m_flag);
	vector<uint32_t>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		msg.add_ranks(*itr);
	}
	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}
bool ArenaRankManager::onSecondTimer() {
	uint32_t ts = CTime::GetDayBeginTime(Time::GetGlobalTime()) + 75600;
	if (Time::GetGlobalTime() < ts) {
		if (m_flag) {
			m_flag = false;
		}
		return false;
	}
	if (m_flag) {
		return false;
	}
	m_flag = true;
	string title = GET_LANG("arena_t");
	for (size_t i = 0; i < m_ranks.size(); ++i) {
		uint32_t uid = m_ranks[i];
		if (!IS_VALID_PLAYER_UID(uid)) {
			continue;
		}
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
		if (player == NULL) {
			continue;
		}
		const Award *cfg = ArenaConfig::getInstance()->getRankReward(i + 1);
		if (cfg == NULL) {
			continue;
		}
		string reward = Award::Award2String(cfg->get());
		string content;
		String::Format(content, GET_LANG("arena_c").c_str(), i + 1);
		player->getEmailManager()->addEmail(uid, title, content, reward);
	}
	return true;
}
bool ArenaRankManager::setRank(uint32_t uid, uint32_t ouid, uint32_t r, uint32_t &sor, uint32_t &onr) {
	if (!IsValidArenaRank(r)) {
		error_log("rank error uid=%u ouid=%u rank=%u", uid, ouid, r);
		return false;
	}
	if (IS_VALID_PLAYER_UID(ouid) && m_ranks[r - 1] != ouid) {
		error_log("userid error uid=%u userid=%u rank=%u nuid=", uid, ouid, r, m_ranks[r]);
		return false;
	}
	sor = getUserRank(uid);
	onr = sor;
	if (sor > r) {
		m_ranks[r - 1] = uid;
		m_userHash[uid] = r;
		if (IsValidArenaRank(sor)) {
			if (IS_VALID_PLAYER_UID(ouid)) {
				m_ranks[sor - 1] = ouid;
				m_userHash[ouid] = sor;
			} else {
				m_ranks[sor - 1] = 0;
			}
		}
	}
	return true;
}
bool ArenaRankManager::doRefresh(uint32_t uid, vector<uint32_t> &ids) {
	static const uint32_t target_size = 5;
	ids.clear();
	uint32_t r = getUserRank(uid);
	if (r <= target_size) {
		for (uint32_t i = 0; i <= target_size; ++i) {
			if (m_ranks[i] == uid) {
				continue;
			}
			ids.push_back(i + 1);
			if (ids.size() >= target_size) {
				break;
			}
		}
		return true;
	}

	uint32_t x = 2;
	if (r < 100) {
		x = 0;
	} else if (r >= 100 && r < 600) {
		x = 1;
	}

	static const uint32_t zone_size = 6;
	static const uint32_t zone_count = 3;
	static uint32_t zone[zone_count][zone_size] = {
		{0, 1, 2, 3, 4, 5 },
		{0, 1, 4, 9, 16, 25 },
		{0, 1, 8, 27, 64, 125 }
	};
	for (uint32_t i = 0; i < zone_size - 1; ++i) {
		uint32_t t = zone[x][i] + Math::GetRandomInt(zone[x][i + 1] - zone[x][i]) + 1;
		uint32_t rr = r > t ? r - t : (r > zone[x][i] ? r - zone[x][i] : r);
		if (!IsValidArenaRank(rr) || m_ranks[rr - 1] == uid) {
			continue;
		}
		ids.push_back(rr);
	}
	return true;
}
bool ArenaRankManager::getUid(uint32_t id, uint32_t &uid) {
	if (id == 0 || id > m_ranks.size()) {
		return false;
	}
	uid = m_ranks[id - 1];
	return true;
}
bool ArenaRankManager::packetTop(IBuffer *buff, bool act) {
	if (buff == NULL) {
		return false;
	}
	uint32_t osize = buff->GetSize();
	PACKET_ENCODE_BEGIN(buff);
	if (act) {
		PACKET_ENCODE(UInt32, 0);
	} else {
		PACKET_ENCODE(Byte, 0);
	}
	uint32_t cnt = 0;
	uint32_t rank = 1;
	vector<uint32_t>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr, ++rank) {
		if (!IS_VALID_PLAYER_UID(*itr)) {
			continue;
		}
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(*itr);
		if (player == NULL) {
			continue;
		}
		PACKET_ENCODE(UInt32, *itr);
		if (!act) {
			PACKET_ENCODE(UInt32, player->getUserCombat());
		}
		PACKET_ENCODE(UInt32, rank);
		PACKET_ENCODE(String, player->getName());
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, player->getFig());
		PACKET_ENCODE(Byte, 0);
		if (++cnt >= 50) {
			break;
		}
	}
	uint32_t nsize = buff->GetSize();
	buff->SetSize(osize);
	if (act) {
		PACKET_ENCODE(UInt32, cnt);
	} else {
		PACKET_ENCODE(Byte, cnt);
	}
	buff->SetSize(nsize);
	debug_log("rank size=%u", cnt);
	return true;
}

uint32_t ArenaRankManager::getUserRank(uint32_t uid) const {
	map<unsigned, unsigned>::const_iterator itr = m_userHash.find(uid);
	if (itr == m_userHash.end()) {
		return ARENA_RANK_INVALID;
	}
	return itr->second;
}
