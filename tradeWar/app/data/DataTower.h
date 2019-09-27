/*
 * DataTower.h
 *
 *  Created on: 2018年8月1日
 *      Author: rein
 */

#ifndef _DATA_TOWER_H_
#define _DATA_TOWER_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataTower {
	uint32_t uid;
	uint32_t id;
	uint32_t level;
	uint32_t star;
};


DECLARE_DBC_DATA_CLASS(CDataTower, DB_TOWER)
	int AddTower(const DataTower& data);
	int GetTowers(uint32_t uid, vector<DataTower>& datas);
	int SetTower(const DataTower& data);
	int DelTower(uint32_t uid);

	virtual void doRequest(CNetPacket *packet);
	int RealAddTower(CNetPacket *packet);
	int RealSetTower(CNetPacket *packet);
	int RealDelTower(CNetPacket *packet);
DECLARE_DBC_DATA_CLASS_END

#endif /* _DATA_TOWER_H_ */
