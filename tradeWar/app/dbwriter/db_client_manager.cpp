/*
 * db_client_manager.cpp
 *
 *  Created on: 2015-9-29
 *      Author: Administrator
 */

#include "db_client_manager.h"

bool DBClientManager::addClient(CDBClientAsync* pClient)
{
	if (m_clients.find(pClient->getFd()) != m_clients.end())
	{
		error_log("error occured");
	}

	m_clients[pClient->getFd()] = pClient;
	return true;
}

bool DBClientManager::removeClient(CDBClientAsync* pClient)
{
	map<uint32_t, CDBClientAsync*>::iterator it = m_clients.find(pClient->getFd());
	if (it == m_clients.end())
	{
		error_log("cannot find %s", pClient->getFd());
		return false;
	}
	m_clients.erase(it);
	return true;
}

bool DBClientManager::sendData(uint32_t fd, IBuffer* pBuff)
{

	map<uint32_t, CDBClientAsync*>::iterator it = m_clients.find(fd);
	if (it == m_clients.end())
	{
		error_log("cannot find clientAsync");
		return false;
	}

	it->second->sendData(pBuff);
	return true;
}

