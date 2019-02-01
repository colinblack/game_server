/*
 * DataUserData.h
 *
 *  Created on: 2011-11-1
 *      Author: dada
 */

#ifndef DATAUSERDATA_H_
#define DATAUSERDATA_H_

#include "Kernel.h"

class CDataUserData : public CDataBaseDBC
{
public:
	CDataUserData(int table = DB_USER_DATA) : CDataBaseDBC(table) {}

public:
	int AddData(unsigned uid, const string &data);
	int SetData(unsigned uid, const string &data);
	int GetData(unsigned uid, string &data);
	int RemoveData(unsigned uid);

};

#endif /* DATAUSERDATA_H_ */
