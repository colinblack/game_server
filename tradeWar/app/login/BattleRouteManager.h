/*
 * BattleRouteManager.h
 *
 *  Created on: 2015-10-20
 *      Author: Administrator
 */

#ifndef BATTLEROUTEMANAGER_H_
#define BATTLEROUTEMANAGER_H_

#include "Kernel.h"
#include "ProtocolInc.h"

class BattleRouteManager
{
public:
	static BattleRouteManager* getInstance()
	{
		static BattleRouteManager rm;
		return & rm;
	}
	~BattleRouteManager();
private:
	BattleRouteManager();
public:
	bool addRoute(uint64_t routeKey,uint32_t fd);
	bool getRoute(uint64_t routeKey,uint32_t & fd);
	bool delRoute(uint64_t routeKey);

	bool addLoginRoute(uint32_t loginServerId, uint32_t fd);
	bool getLoginRoute(uint32_t loginServerId, uint32_t& fd);
	bool delLoginRoute(uint32_t loginServerId);

	bool addUserRoute(uint64_t battleId, uint32_t uid, uint32_t fd);
	bool getUserRoute(uint64_t battleId, uint32_t uid, uint32_t& fd);
	bool delUserRoute(uint64_t battleId, uint32_t uid);

private:
	map<uint64_t, uint32_t> m_route;//type-uid,fd
	map<uint32_t, uint32_t> m_LoginRoute;//login_serverid,fd
	map<uint64_t, map<uint32_t, uint32_t> > m_userRoute; // battleId -> uid -> fd
};

#endif /* BATTLEROUTEMANAGER_H_ */
