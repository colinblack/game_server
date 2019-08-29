/*
 * TencentAsyncManager.cpp
 *
 *  Created on: 2016-3-18
 *      Author: Administrator
 */


#include "TencentAsyncManager.h"

bool TencentAsyncManager::addClient(TencentAsync* pClient)
{
	if(m_clients.find(pClient->getFd()) != m_clients.end())
	{
		error_log("error occured");
	}
	m_clients[pClient->getFd()] = pClient;
	return true;
}

bool TencentAsyncManager::removeClient(TencentAsync* pClient)
{
	map<uint32_t,TencentAsync*>::iterator it = m_clients.find(pClient->getFd());
	if(it == m_clients.end())
	{
		error_log("cannot find %s",pClient->getFd());
		return false;
	}
	m_clients.erase(it);
	return true;
}

bool TencentAsyncManager::sendData(uint32_t fd, IBuffer* pBuff){

	map<uint32_t,TencentAsync*>::iterator it = m_clients.find(fd);
	if(it == m_clients.end())
	{
		return false;
	}
	it->second->sendData(pBuff);
	return true;
}



