/*
 * DataUserBase.h
 *
 *  Created on: 2011-7-9
 *      Author: dada
 */

#ifndef DATAUSERBASE_H_
#define DATAUSERBASE_H_

#include "Kernel.h"

class CDataUserBase : public CDataBaseDBC
{
public:
	CDataUserBase(int table = DB_USER_BASE) : CDataBaseDBC(table) {}

public:
	int AddUserBase(unsigned uid, int base_index, unsigned baseid);
	int SetUserBase(unsigned uid, int base_index, unsigned baseid);
	int GetUserBase(unsigned uid, int base_index, unsigned &baseid);
	int GetUserBases(unsigned uid, map<int, unsigned> &bases);	//map: base_index -> baseid
	int RemoveUserBase(unsigned uid, int base_index);
	int RemoveUserBases(unsigned uid);
};

#endif /* DATAUSERBASE_H_ */
