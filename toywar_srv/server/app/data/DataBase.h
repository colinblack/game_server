/*
 * DataBase.h
 *
 *  Created on: 2011-7-11
 *      Author: dada
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include "Kernel.h"

struct DataBase
{
	unsigned baseid;
	unsigned uid;
	int base_index;
	int type;
	string base_name;
	int seed;
	unsigned position;
	unsigned create_time;
	unsigned save_time;
	unsigned saveby_uid;
	unsigned protected_time;
	unsigned last_active_time;
	int status;
	int damage;
	int destroyed;
	uint64_t value;
	int attack_level;
	int bomb_level;
};

class CDataBase : public CDataBaseDBC
{
public:
	CDataBase(int table = DB_BASE) : CDataBaseDBC(table) {}

public:

	int AddBase(DataBase &base);
	int SetBase(const DataBase &base);
	int GetBase(unsigned baseid, DataBase &base);
	int RemoveBase(unsigned baseid);

	int SetActiveTime(unsigned baseid, unsigned last_active_time);
	int SetPosition(unsigned baseid, unsigned position);
	int GetPosition(unsigned baseid, unsigned &position);

};

#endif /* DATABASE_H_ */
