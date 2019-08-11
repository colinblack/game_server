/*
 * LevelRewardRecordManager.h
 *
 *  Created on: 2019年7月22日
 *      Author: colin
 */

#ifndef APP_BATTLE_LEVELREWARDRECORDMANAGER_H_
#define APP_BATTLE_LEVELREWARDRECORDMANAGER_H_

#include "BattleBaseInc.h"

class LevelRewardRecordManager: public CSingleton<LevelRewardRecordManager>, public DataLocal<MsgLocal::LevelRewardRecords> {
private:
	friend class CSingleton<LevelRewardRecordManager> ;
	LevelRewardRecordManager();
	virtual ~LevelRewardRecordManager();
	map<uint32_t, map<uint32_t, int32_t> > m_records;
public:
	virtual bool Parse();
	virtual bool Serialize();


	bool Get(map<int32_t, int32_t>& rewards);
	bool Add(uint32_t careerLevel, uint32_t level, int32_t count);
	int32_t& GetCount(uint32_t careerLevel, uint32_t level);
	bool exist(uint32_t careerLevel, uint32_t level);
};


#endif /* APP_BATTLE_LEVELREWARDRECORDMANAGER_H_ */
