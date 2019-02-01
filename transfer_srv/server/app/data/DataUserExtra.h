/*
 * DataUserExtra.h
 *
 *  Created on: 2012-3-1
 *      Author: dada
 */

#ifndef DATAUSEREXTRA_H_
#define DATAUSEREXTRA_H_

#include "Kernel.h"

struct DataUserExtra
{
	unsigned uid;
	int gate_left_times;
	int gate_extra_times;
	string stat;
	string wf_status;
	string lock;
	string technology;
	string quest;
	string bookmark;
	string extra_data;
	string eggdata;
};

class CDataUserExtra : public CDataBaseDBC
{

public:
	CDataUserExtra(int table = DB_USER_EXTRA) : CDataBaseDBC(table) {}

public:
	int AddUser(DataUserExtra &user);
	int SetUser(const DataUserExtra &user);
	int GetUser(unsigned uid, DataUserExtra &user);
	int RemoveUser(unsigned uid);

	int GetExtraData(unsigned uid, string &extra_data);
	int SetExtraData(unsigned uid, const string &extra_data);
	int GetStat(unsigned uid, string &stat);
	int SetStat(unsigned uid, const string &stat);

	int SetGateTimes(const DataUserExtra &user);
	int GetGateTimes(unsigned uid, DataUserExtra &user);
	int GetWfStatus(unsigned uid, string &wf_status);
	int SetWfStatus(unsigned uid, const string &sf_status);
	int SetBookmark(unsigned uid, const string &bookmark);
};

#endif /* DATAUSEREXTRA_H_ */
