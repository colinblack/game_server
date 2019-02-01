/*
 * DataIdcard.h
 *
 *  Created on: 2018-3-13
 *      Author: Ralf
 */

#ifndef DataIdcard_H_
#define DataIdcard_H_

#include "Kernel.h"


class CDataIdcard : public CDataBaseDBC
{
public:
	CDataIdcard(int table = DB_IDCARD) : CDataBaseDBC(table) {}

public:
	int AddIdcard(const string &idcard, string& open_id);
	int GetAllIdcard(const string &idcard, set<string> &open_id);
};


#endif /* DataIdcard_H_ */
