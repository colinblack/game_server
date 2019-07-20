/*
 * TreasureRecordManager.h
 *
 *  Created on: 2019年7月18日
 *      Author: Administrator
 */

#ifndef TREASURE_RECORD_MANAGER_H_
#define TREASURE_RECORD_MANAGER_H_

#include "BattleBaseInc.h"

#define MAX_TREASURE_RECORD_COUNT 20

class TreasureRecordManager: public CSingleton<TreasureRecordManager>, public DataLocal<MsgLocal::TreasureHuntRecords> {
private:
	friend class CSingleton<TreasureRecordManager> ;
	TreasureRecordManager();
	virtual ~TreasureRecordManager();
	map<uint32_t, list<dbs::TTreasureRecord> > m_records;
public:
	virtual bool Parse();
	virtual bool Serialize();
	bool Add(const UserCache &cache, uint32_t id, uint32_t type);
	bool Get(uint32_t type, vector<dbs::TTreasureRecord> &result);
};

#endif /* TREASURE_RECORD_MANAGER_H_ */
