/*
 * DataRank.h
 *
 *  Created on: 2015-1-21
 *      Author: Ralf
 */

#ifndef DATARANK_H_
#define DATARANK_H_

#include "Kernel.h"

struct DataRank
{
	unsigned uid;
	unsigned level;
	unsigned dehp;
	string	 heroid;
	unsigned mcity;
	unsigned citylevel;
	unsigned part;
	unsigned soul;
	unsigned book;
	unsigned mac;
	DataRank()
	{
		uid = level = dehp = mcity = citylevel = part = soul = book = mac = 0;
	}
};

class CDataRank : public CDataBaseDBC
{
public:
	CDataRank(int table = DB_RANK) : CDataBaseDBC(table) {}

public:
	int AddRank(const DataRank &rank);
	int SetRank(unsigned uid, const DataRank &rank);
	int GetRank(unsigned uid, DataRank &rank);
	int ClearRank(unsigned uid);
};


#endif /* DATARANK_H_ */
