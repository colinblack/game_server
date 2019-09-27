/*
 * DataBattleGate.h
 *
 *  Created on: 2018年10月30日
 *      Author: Administrator
 */

#ifndef DATA_BATTLE_GATE_H_
#define DATA_BATTLE_GATE_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataBattleGate {
	uint32_t uid;
	uint32_t level;
	uint32_t score;
	uint32_t res;
	byte star;

	DataBattleGate() :
			uid(0), level(0), score(0), res(0), star(0) {
	}
};

class CDataBattleGate: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataBattleGate(int table = DB_BATTLE_GATE) : CDataBaseDBC(table) {
	}
	virtual ~CDataBattleGate() {
	}
	virtual void doRequest(CNetPacket* packet);

	int Add(const DataBattleGate &data);
	int Add(CNetPacket *packet);
	int Set(const DataBattleGate &data);
	int Set(CNetPacket *packet);
	int Del(uint32_t uid);
	int Del(CNetPacket *packet);
	int Get(uint32_t uid, uint32_t level, DataBattleGate &data);
	int Get(uint32_t uid, vector<DataBattleGate> &data);
};

#endif /* DATA_BATTLE_GATE_H_ */
