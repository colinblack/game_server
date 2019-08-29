/*
 * DataUserMapping.h
 *
 *  Created on: 2015-9-9
 *      Author: Administrator
 */

#ifndef DATAUSERMAPPING_H_
#define DATAUSERMAPPING_H_

#include "Kernel.h"

class CDataUserMapping : public CDataBaseDBC
{
public:
	CDataUserMapping(int table = DB_USER_MAPPING) : CDataBaseDBC(table) {}
public:
	int AddMapping(unsigned serverId, unsigned platform, const string &openid, unsigned uid);
	int GetMapping(unsigned serverId, unsigned platform, const string &openid, unsigned &uid);
	int GetAllMapping(const string &openid, vector<pair<unsigned, unsigned> > &vUid);
	int RemoveMapping(const string &openid);
	int SetLastLogin(unsigned serverId, unsigned platform, const string &openid);
};

#endif /* DATAUSERMAPPING_H_ */
