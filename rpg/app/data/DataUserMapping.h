/*
 * DataUserMapping.h
 *
 *  Created on: 2013-2-2
 *      Author: Administrator
 */

#ifndef DATA_USER_MAPPING_H_
#define DATA_USER_MAPPING_H_

#include "Kernel.h"

class CDataUserMapping: public CDataBaseDBC {
public:
	CDataUserMapping(int table = DB_USER_MAPPING): CDataBaseDBC(table) {
	}
	int AddMapping(const string &openid, unsigned sid, unsigned platform, unsigned uid);
	int GetMapping(const string &openid, unsigned sid, unsigned platform, unsigned &uid);
};

#endif /* DATA_USER_MAPPING_H_ */
