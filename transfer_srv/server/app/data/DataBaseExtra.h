/*
 * DataBaseExtra.h
 *
 *  Created on: 2012-3-1
 *      Author: dada
 */

#ifndef DATABASEEXTRA_H_
#define DATABASEEXTRA_H_

#include "Kernel.h"

struct DataBaseExtra
{
	unsigned baseid;
	string updates;
	string building;
	string effect;
	string aiattack;
	string manoeuvre;
	string grower;
	string military;
	string hero;
	string recycle;
	string consume;
	string extra_data;
	//DataBaseExtra &operator=(const DataBaseExtra &baseExtra);
};

class CDataBaseExtra : public CDataBaseDBC
{
public:
	CDataBaseExtra(int table = DB_BASE_EXTRA) : CDataBaseDBC(table) {}

public:
	int AddBase(DataBaseExtra &base);
	int SetBase(const DataBaseExtra &base);
	int GetBase(unsigned baseid, DataBaseExtra &base);
	int RemoveBase(unsigned baseid);

	int SetExtraData(unsigned baseid, const string &extra_data);
	int GetExtraData(unsigned baseid, string &extra_data);
	int SetUpdates(unsigned baseid, const string &updates);
	int GetUpdates(unsigned baseid, string &updates);
	int SetMilitary(unsigned baseid, const string &military);
	int GetMilitary(unsigned baseid, string &military);
	int SetHero(unsigned baseid, const string &hero);
	int SetConsume(unsigned baseid, const string &consume);
	int GetConsume(unsigned baseid, string &consume);

};

#endif /* DATABASEEXTRA_H_ */
