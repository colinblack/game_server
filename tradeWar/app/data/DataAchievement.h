/*
 * DataAchievement.h
 *
 *  Created on: 2018年8月11日
 *      Author:
 */

#ifndef _DATA_ACHIEVEMENT_H_
#define _DATA_ACHIEVEMENT_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataAchievement {
	uint32_t uid;
	uint32_t type;
	uint32_t id;
	uint32_t count;

	DataAchievement(): uid(0), type(0), id(0), count(0) {
	}
};

DECLARE_DBC_DATA_CLASS(CDataAchievement, DB_ACHIEVEMENT)
public:
	int AddAchievement(const DataAchievement& data);
	int GetAchievement(uint32_t uid, vector<DataAchievement>& data);
	int SetAchievement(const DataAchievement& data);
	int DelAchievement(uint32_t uid);

	virtual void doRequest(CNetPacket* packet);
	int RealAddAchievement(CNetPacket* packet);
	int RealSetAchievement(CNetPacket* packet);
	int RealDelAchievement(CNetPacket* packet);
DECLARE_DBC_DATA_CLASS_END

#endif /* _DATA_ACHIEVEMENT_H_ */
