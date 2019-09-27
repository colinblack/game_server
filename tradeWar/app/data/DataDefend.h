/*
 * DataDefend.h
 *
 *  Created on: 2017年11月14日
 *      Author: Administrator
 */

#ifndef DATA_DEFEND_H_
#define DATA_DEFEND_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataDefend {
	uint32_t uid;
	uint32_t level;
	byte star;

	DataDefend() :
			uid(0), level(0), star(0) {
	}
};

class CDataDefend: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataDefend(int table = DB_DEFEND) : CDataBaseDBC(table) {
	}
	virtual ~CDataDefend() {
	}
	virtual void doRequest(CNetPacket* packet);

	int Add(const DataDefend &data);
	int Add(CNetPacket *packet);
	int Set(const DataDefend &data);
	int Set(CNetPacket *packet);
	int Del(uint32_t uid);
	int Del(CNetPacket *packet);
	int Get(uint32_t uid, uint32_t level, DataDefend &data);
	int Get(uint32_t uid, vector<DataDefend> &data);
};

#endif /* DATA_DEFEND_H_ */
