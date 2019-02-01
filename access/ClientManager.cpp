#include "ClientManager.h"

void ClientManager::onlineLog(){
	unsigned t = m_clients.size();
	unsigned ts = time(0);
	if(t >= m_online + 47 || t + 47 <= m_online || ts >= m_ts + 60 || (!t && m_online) || (t && !m_online)){
		m_ts = ts;
		m_online = t;
		ONLINE_LOG("%u",m_online);
	}
}
bool ClientManager::addClient(CClientAsync* pClient){
	if(m_clients.find(pClient->getFd()) != m_clients.end()){
		LOG_ERROR("error occured");
	}


	m_clients[pClient->getFd()] = pClient;
	onlineLog();//ONLINE_LOG("%u",m_clients.size());
	return true;
}

bool ClientManager::removeClient(CClientAsync* pClient){
	map<uint32_t,CClientAsync*>::iterator it = m_clients.find(pClient->getFd());
	if(it == m_clients.end()){
		LOG_ERROR("cannot find %s",pClient->getRemoteIp());
		return false;
	}

	if(it->second->getTime() != pClient->getTime()
			|| it->second->getMicrotime() != pClient->getMicrotime()){
		LOG_ERROR("time mismatch [%u %u] [%u %u]",it->second->getTime(),it->second->getMicrotime(),pClient->getTime(),pClient->getMicrotime());
		return false;
	}

	m_clients.erase(it);

	onlineLog();//ONLINE_LOG("%u",m_clients.size());

	return true;
}

bool ClientManager::sendData(uint32_t fd,uint32_t time,uint32_t microTime,const string& data){
	map<uint32_t,CClientAsync*>::iterator it = m_clients.find(fd);
	if(it == m_clients.end()){
		return false;
	}

	if(it->second->getTime() != time || it->second->getMicrotime() != microTime){
		return false;
	}

	it->second->sendData(data);
	return true;
}
bool ClientManager::sendData(uint32_t fd,const string& data){
	map<uint32_t,CClientAsync*>::iterator it = m_clients.find(fd);
	if(it == m_clients.end()){
		return false;
	}

	it->second->sendData(data, false);
	return true;
}
bool ClientManager::sendAll(uint32_t srvId, const string& data)
{
	for(map<uint32_t,CClientAsync*>::iterator it = m_clients.begin(); it != m_clients.end(); ++it)
	{
		if(it->second->getsrvId() == srvId)
			it->second->sendData(data, false);
	}
	return true;
}


uint32_t ClientManager::getIp(uint32_t fd,uint32_t time,uint32_t microTime)
{
	map<uint32_t,CClientAsync*>::iterator it = m_clients.find(fd);
	if(it == m_clients.end()){
		return false;
	}

	if(it->second->getTime() != time || it->second->getMicrotime() != microTime){
		return false;
	}

	return it->second->getIp();
}

bool ClientManager::updateClientSrvId(uint32_t fd,uint32_t time,uint32_t microTime,uint32_t srvId)
{
	map<uint32_t,CClientAsync*>::iterator it = m_clients.find(fd);
	if(it == m_clients.end()){
		return false;
	}

	if(it->second->getTime() != time || it->second->getMicrotime() != microTime){
		return false;
	}

	it->second->setSrvId(srvId);
	return true;
}


bool ClientManager::battleClose(uint32_t fd){
	map<uint32_t,CClientAsync*>::iterator it = m_clients.find(fd);
	if(it == m_clients.end()){
		return false;
	}

	it->second->battleClose();
	return true;
}


