/*
 * DataAlliance.h
 *
 *  Created on: 2011-9-19
 *      Author: dada
 */

#ifndef DATAALLIANCE_H_
#define DATAALLIANCE_H_

#include "Kernel.h"

struct DataAlliance
{
	unsigned alliance_id;
	int world;
	string name;
	int flag;
	unsigned leader_uid;
	unsigned create_time;
	int status;
	int level;
	uint64_t point;
	int rank;
	int member_count;
	unsigned enemy_alliance_id;
	string enemy_alliance_name;
	string description;
	string notice;
	string activity;
	string extra_data;
};

class CDataAlliance : public CDataBaseDBC
{
public:
	CDataAlliance(int table = DB_ALLIANCE) : CDataBaseDBC(table) {}

public:
	int AddAlliance(const DataAlliance &alliance);
	int SetAlliance(const DataAlliance &alliance);
	int GetAlliance(unsigned alliance_id, DataAlliance &alliance);
	int RemoveAlliance(unsigned alliance_id);

	int SetAllianceLimit(const DataAlliance &alliance);
	int GetAllianceLimit(unsigned alliance_id, DataAlliance &alliance);
	int AddPoint(unsigned alliance_id, int point);
	int GetWorld(unsigned alliance_id, int &world);
};

#endif /* DATAALLIANCE_H_ */
