#ifndef _WX_CLIENT_MANAGER_H_
#define _WX_CLIENT_MANAGER_H_

#include <map>
#include "client_async.h"

using namespace std;

class ClientManager{
public:
	static ClientManager* getInstance(){
		static ClientManager cm;
		return &cm;
	}
	~ClientManager(){};
private:
	ClientManager():m_online(0),m_ts(0){}
	void onlineLog();
public:
	bool addClient(CClientAsync* pClient);
	bool removeClient(CClientAsync* pClient);
	bool sendData(uint32_t fd,uint32_t time,uint32_t microTime,const string& data);
	bool sendData(uint32_t fd,const string& data);
	bool sendAll(uint32_t srvId, const string& data);
	uint32_t getIp(uint32_t fd,uint32_t time,uint32_t microTime);
	bool battleClose(uint32_t fd);
	bool updateClientSrvId(uint32_t fd,uint32_t time,uint32_t microTime,uint32_t srvId);
private:
	map<uint32_t,CClientAsync*> m_clients;
	unsigned m_online, m_ts;
};



#endif
