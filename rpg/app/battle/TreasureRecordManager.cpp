/*
 * TreasureRecordManager.cpp
 *
 *  Created on: 2019年7月18日
 *      Author: Administrator
 */

#include "TreasureRecordManager.h"
#include "BattleInc.h"

TreasureRecordManager::TreasureRecordManager() {
	m_path = Config::GetPath(CONFIG_TREASURE_RECORD);
}

TreasureRecordManager::~TreasureRecordManager() {
}

bool TreasureRecordManager::Parse() {
	for (int i = 0; i < m_msg.records_size(); ++i) {
		const MsgLocal::TreasureHuntRecord &msg = m_msg.records(i);
		dbs::TTreasureRecord item;
		item.id_ = msg.id();
		item.type_ = msg.type();
		item.treasureId_ = msg.treasureid();
		item.playerId_ = msg.playerid();
		item.name_ = msg.name();
		item.career_ = msg.career();
		item.level_ = msg.level();
		item.careerLevel_ = msg.careerlevel();
		item.drawDt_ = msg.drawdt() * 1000L;
		list<dbs::TTreasureRecord> &ver = m_records[item.type_];
		ver.push_back(item);
	}
	return true;
}

bool TreasureRecordManager::Serialize() {
	map<uint32_t, list<dbs::TTreasureRecord> >::iterator mitr = m_records.begin();
	list<dbs::TTreasureRecord>::iterator vitr;
	for (; mitr != m_records.end(); ++mitr) {
		list<dbs::TTreasureRecord> &ver = mitr->second;
		for (vitr = ver.begin(); vitr != ver.end(); ++vitr) {
			MsgLocal::TreasureHuntRecord *msg = m_msg.add_records();
			msg->set_id(vitr->id_);
			msg->set_type(vitr->type_);
			msg->set_treasureid(vitr->treasureId_);
			msg->set_playerid(vitr->playerId_);
			msg->set_name(vitr->name_);
			msg->set_career(vitr->career_);
			msg->set_level(vitr->level_);
			msg->set_careerlevel(vitr->careerLevel_);
			msg->set_drawdt(vitr->drawDt_ / 1000L);
		}
	}
	return true;
}

bool TreasureRecordManager::Add(const UserCache &cache, uint32_t id, uint32_t type) {
	list<dbs::TTreasureRecord> &ver = m_records[type];
	dbs::TTreasureRecord item;
	item.id_ = ver.size() + 1;
	item.type_ = type;
	item.treasureId_ = id;
	item.playerId_ = cache.uid_;
	item.level_ = cache.base_.level;
	item.careerLevel_ = cache.m_reinCarnInfo.reinCarnLevel;
	item.drawDt_ = Time::GetGlobalTime();
	map<byte, DataRole>::const_iterator itr = cache.role_.find(cache.base_.main_role);
	if (itr != cache.role_.end()) {
		const DataRole &role = itr->second;
		item.name_ = role.name;
	}
	ver.push_back(item);
	while (ver.size() > MAX_TREASURE_RECORD_COUNT) {
		ver.pop_front();
	}
	return true;
}

bool TreasureRecordManager::Get(uint32_t type, vector<dbs::TTreasureRecord> &result) {
	result.clear();
	const list<dbs::TTreasureRecord> &ver = m_records[type];
	list<dbs::TTreasureRecord>::const_iterator itr = ver.begin();
	for (; itr != ver.end(); ++itr) {
		result.push_back(*itr);
	}
	return true;
}
