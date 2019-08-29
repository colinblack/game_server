/*
 * BattleRouteManager.cpp
 *
 *  Created on: 2015-10-20
 *      Author: Administrator
 */

#include "BattleRouteManager.h"

BattleRouteManager::BattleRouteManager()
{

}

BattleRouteManager::~BattleRouteManager()
{

}

bool BattleRouteManager::addRoute(uint64_t routeKey,uint32_t fd)
{
	m_route[routeKey] = fd;
	return true;
}

bool BattleRouteManager::getRoute(uint64_t routeKey,uint32_t & fd)
{
	map<uint64_t,uint32_t>::iterator it = m_route.find(routeKey);
	if(it != m_route.end())
	{
		fd = it->second;
		return true;
	}
	return false;
}

bool BattleRouteManager::delRoute(uint64_t routeKey)
{
	map<uint64_t,uint32_t>::iterator it = m_route.find(routeKey);
	if(it != m_route.end())
	{
		m_route.erase(it);
	}
	return true;
}

bool BattleRouteManager::addLoginRoute(uint32_t loginServerId, uint32_t fd)
{
	map<uint32_t,uint32_t>::iterator it = m_LoginRoute.find(loginServerId);
	if(it == m_LoginRoute.end())
	{
		m_LoginRoute[loginServerId] = fd;
	}
	return true;
}

bool BattleRouteManager::getLoginRoute(uint32_t loginServerId, uint32_t & fd)
{
	map<uint32_t,uint32_t>::iterator it = m_LoginRoute.find(loginServerId);
	if(it != m_LoginRoute.end())
	{
		fd = it->second;
		return true;
	}
	else
	{
		error_log("getLoginRoute_fail&loginServerId=%u", loginServerId);
		return false;
	}
}

bool BattleRouteManager::delLoginRoute(uint32_t loginServerId)
{
	map<uint32_t,uint32_t>::iterator it = m_LoginRoute.find(loginServerId);
	if(it == m_LoginRoute.end())
	{
		m_LoginRoute.erase(it);
	}
	return true;
}
bool BattleRouteManager::addUserRoute(uint64_t battleId, uint32_t uid, uint32_t fd)
{
	m_userRoute[battleId][uid] = fd;
//	debug_log("battle_add_user_route battleId=%llu btype=%u buid=%u uid=%u fd=%u"
//			, battleId, U64_HIGH(battleId), U64_LOW(battleId), uid, fd);
	return true;
}
bool BattleRouteManager::getUserRoute(uint64_t battleId, uint32_t uid, uint32_t& fd)
{
	map<uint64_t, map<uint32_t, uint32_t> >::iterator bIter = m_userRoute.find(battleId);
	if(bIter != m_userRoute.end())
	{
		map<uint32_t, uint32_t>& userMap = bIter->second;
		map<uint32_t, uint32_t>::iterator uIter = userMap.find(uid);
		if(uIter != userMap.end())
		{
			fd = uIter->second;
			return true;
		}
	}
	return false;
}
bool BattleRouteManager::delUserRoute(uint64_t battleId, uint32_t uid)
{
	map<uint64_t, map<uint32_t, uint32_t> >::iterator bIter = m_userRoute.find(battleId);
	if(bIter != m_userRoute.end())
	{
		map<uint32_t, uint32_t>& userMap = bIter->second;
		map<uint32_t, uint32_t>::iterator uIter = userMap.find(uid);
		if(uIter != userMap.end())
		{
			debug_log("battle_del_user_route battleId=%llu btype=%u buid=%u uid=%u fd=%u"
					, battleId, U64_HIGH(battleId), U64_LOW(battleId), uid, uIter->second);
			userMap.erase(uIter);
		}
		if(userMap.empty())
		{
			m_userRoute.erase(bIter);
			debug_log("battle_del battleId=%llu btype=%u buid=%u"
					, battleId, U64_HIGH(battleId), U64_LOW(battleId));
		}
	}
	return true;
}
