/*
 * db_client_manager.h
 *
 *  Created on: 2015-9-29
 *      Author: Administrator
 */

#ifndef DB_CLIENT_MANAGER_H_
#define DB_CLIENT_MANAGER_H_

#include "Kernel.h"
#include "DBClient.h"

using namespace std;

class DBClientManager: public CSingleton<DBClientManager> {
private:
	friend class CSingleton<DBClientManager> ;
	DBClientManager() {
	}

public:
	~DBClientManager() {
	}

public:
	bool addClient(CDBClientAsync* pClient);
	bool removeClient(CDBClientAsync* pClient);
	bool sendData(uint32_t fd, IBuffer* pBuff);
private:
	map<uint32_t, CDBClientAsync*> m_clients; //fd-client
};

#endif /* DB_CLIENT_MANAGER_H_ */
