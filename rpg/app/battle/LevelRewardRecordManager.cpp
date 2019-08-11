/*
 * LevelRewardRecordManager.cpp
 *
 *  Created on: 2019年7月22日
 *      Author: colin
 */

#include "LevelRewardRecordManager.h"
#include "BattleInc.h"


LevelRewardRecordManager::LevelRewardRecordManager() {
	m_path = Config::GetPath(CONFIG_LEVELREWARD_RECORD);
}

LevelRewardRecordManager::~LevelRewardRecordManager() {
}


bool LevelRewardRecordManager::Parse() {
	for (int i = 0; i < m_msg.records_size(); ++i) {
		const MsgLocal::LevelRewardRecord &msg = m_msg.records(i);
		m_records[msg.careerlevel()].insert(make_pair(msg.level(), msg.leftcount()));
	}
	return true;
}

bool LevelRewardRecordManager::Serialize() {
	map<uint32_t, map<uint32_t, int32_t> >::iterator mitr = m_records.begin();
	for(;mitr != m_records.end(); ++mitr){
		map<uint32_t, int32_t>::iterator it = mitr->second.begin();
		for(; it != mitr->second.end(); ++it)
		{
			MsgLocal::LevelRewardRecord *msg = m_msg.add_records();
			msg->set_careerlevel(mitr->first);
			msg->set_level(it->first);
			msg->set_level(it->second);
		}
	}

	return true;
}


bool LevelRewardRecordManager::Add(uint32_t careerLevel, uint32_t level, int32_t count){
	if(exist(careerLevel, level)){
		error_log("param exist, careerlevel:%u, level:%u", careerLevel, level);
		throw runtime_error("param exist");
	}

	m_records[careerLevel].insert(make_pair(careerLevel, level));

	return true;
}


int32_t& LevelRewardRecordManager::GetCount(uint32_t careerLevel, uint32_t level){
	if(!exist(careerLevel, level)){
		error_log("param invalid, careerlevel:%u, level:%u", careerLevel, level);
		throw runtime_error("param invalid");

	}
	return m_records[careerLevel][level];
}


bool LevelRewardRecordManager::exist(uint32_t careerLevel, uint32_t level)
{
	if(m_records.count(careerLevel) &&
			m_records[careerLevel].count(level)){
		return false;
	}

	return true;
}

bool LevelRewardRecordManager::Get(map<int32_t, int32_t>& rewards)
{
	map<uint32_t, map<uint32_t, int32_t> >::iterator mitr = m_records.begin();
	for(;mitr != m_records.end(); ++mitr){
		map<uint32_t, int32_t>::iterator it = mitr->second.begin();
		for(; it != mitr->second.end(); ++it){
			if(mitr->first > 0)
				rewards.insert(make_pair(mitr->first*10000 + it->first, it->second));
		}
	}

	return true;
}

