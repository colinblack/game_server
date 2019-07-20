/*
 * RoleManager.h
 *
 *  Created on: 2019年4月23日
 *      Author: Administrator
 */

#ifndef ROLE_MANAGER_H_
#define ROLE_MANAGER_H_

#include "BattleBaseInc.h"

class RoleManager: public CSingleton<RoleManager> {
private:
	friend class CSingleton<RoleManager> ;
	RoleManager();
	~RoleManager();

public:
	bool AddRole(uint32_t uid, uint32_t rid, int16_t sex, int16_t c, const string &n);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerRoleList *resp);

};

#endif /* ROLE_MANAGER_H_ */
