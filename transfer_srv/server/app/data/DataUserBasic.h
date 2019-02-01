/*
 * DataUserBasic.h
 *
 *  Created on: 2011-7-8
 *      Author: dada
 */

#ifndef DATAUSERBASIC_H_
#define DATAUSERBASIC_H_

#include "Kernel.h"

struct DataUserBasic
{
	unsigned uid;
	int platform;
	int is_register_platform;
	string open_id;
	string name;
	int gender;
	string nation;
	string province;
	string city;
	string figure_url;
	int vip_type;
	int vip_level;
	string extra_data;
};

class CDataUserBasic : public CDataBaseDBC
{
public:
	CDataUserBasic(int table = DB_USER_BASIC) : CDataBaseDBC(table) {}

public:
	int AddUser(const DataUserBasic &user);
	int SetUser(const DataUserBasic &user);
	int GetUser(unsigned uid, int platform, DataUserBasic &user);
	int GetUserRegister(unsigned uid, DataUserBasic &user);
	int GetUserAll(unsigned uid, vector<DataUserBasic> &users);
	int RemoveUser(unsigned uid);

};

#endif /* DATAUSERBASIC_H_ */
