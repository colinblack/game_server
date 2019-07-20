/*
 * DataRoleMapping.h
 *
 *  Created on: 2013-2-6
 *      Author: Administrator
 */

#ifndef DATA_ROLE_MAPPING_H_
#define DATA_ROLE_MAPPING_H_

#include "Kernel.h"

class CDataRoleMapping: public CDataBaseDBC {
public:
	CDataRoleMapping(int table = DB_ROLE_MAPPING) : CDataBaseDBC(table) {
	}
public:
	int AddMapping(const string &role_name, unsigned sid, unsigned uid);
	int GetMapping(const string &role_name, unsigned sid, unsigned &uid);
};

#endif /* DATAROLEMAPPING_H_ */
