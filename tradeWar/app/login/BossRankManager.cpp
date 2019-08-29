/*
 * BossRankManager.cpp
 *
 *  Created on: 2019年2月26日
 *      Author: Administrator
 */

#include "BossRankManager.h"
#include "BossConfig.h"
#include "ActivityTimeManager.h"
#include "PlayerManager.h"
#include "LanguageConfig.h"
#include <fstream>

BossRankManager::BossRankManager() {
	m_ts = 0;
	m_flag = false;
	m_ranks.clear();
}

BossRankManager::~BossRankManager() {
}

bool BossRankManager::init() {
	string path = Config::GetValue(BOSS_RANK_PATH);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::BossRank msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	m_ts = msg.ts();
	m_flag = msg.flag();
	for (int i = 0; i < msg.ranks_size(); ++i) {
		DataBossRank data;
		data.Parse(msg.ranks(i));
		m_ranks.push_back(data);
	}
	return true;
}

bool BossRankManager::save() {
	string path = Config::GetValue(BOSS_RANK_PATH);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoRankList::BossRank msg;
	msg.set_ts(m_ts);
	msg.set_flag(m_flag);
	list<DataBossRank>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		itr->Serialize(msg.add_ranks());
	}
	if (!msg.SerializeToOstream(&output)) {
		error_log("serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool BossRankManager::reset() {
	if (CTime::GetDayInterval(m_ts, Time::GetGlobalTime()) == 0) {
		return false;
	}
	m_ts = Time::GetGlobalTime();
	m_flag = false;
	m_ranks.clear();
	return true;
}

bool BossRankManager::addRank(uint32_t uid, uint64_t hurt, const string &name) {
	reset();
	if (!isValidTime()) {
		return true;
	}
	uint32_t rank_size = BossConfig::getInstance()->getRankSize();
	if (m_ranks.size() >= rank_size && m_ranks.back().hurt > hurt) {
		return false;
	}
	list<DataBossRank>::iterator iter = m_ranks.begin();
	for (; iter != m_ranks.end(); ++iter) {
		if (iter->uid == uid) {
			m_ranks.erase(iter);
			break;
		}
	}
	DataBossRank item;
	item.uid = uid;
	item.hurt = hurt;
	item.name = name;
	for (iter = m_ranks.begin(); iter != m_ranks.end() && (hurt <= iter->hurt); ++iter) {
	}
	m_ranks.insert(iter, item);
	if (m_ranks.size() > rank_size) {
		m_ranks.pop_back();
	}
	return true;
}

bool BossRankManager::encode(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	reset();
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt16, m_ranks.size());
	list<DataBossRank>::iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		PACKET_ENCODE(String, itr->name);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(UInt32, itr->hurt);
		PACKET_ENCODE(UInt32, itr->uid);
	}
	return true;
}

bool BossRankManager::onSecondTimer() {
	if (isValidTime()) {
		return true;
	}
	if (m_flag) {
		return true;
	}
	m_flag = true;
	list<DataBossRank>::iterator itr = m_ranks.begin();
	uint32_t rank = 0;

	string title = GET_LANG("boss_t");
	for (; itr != m_ranks.end(); ++itr) {
		++rank;
		const Award *cfg = BossConfig::getInstance()->getRank(rank);
		if (cfg == NULL) {
			continue;
		}
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(itr->uid);
		if (player == NULL) {
			continue;
		}
		string reward = Award::Award2String(cfg->get());
		string content;
		String::Format(content, GET_LANG("boss_c").c_str(), rank);
		player->getEmailManager()->addEmail(itr->uid, title, content, reward);
	}
	return true;
}

bool BossRankManager::isValidTime() {
	uint32_t ts = CTime::GetDayBeginTime(Time::GetGlobalTime());
	if (Time::GetGlobalTime() >= ts + 79200) {
		return false;
	}
	return true;
}
