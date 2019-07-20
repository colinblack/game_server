#ifndef _CLIENT_MANAGER_H_
#define _CLIENT_MANAGER_H_

#include "ClientAsync.h"
#include "Kernel.h"

class ClientManager: public CSingleton<ClientManager> {
private:
	friend class CSingleton<ClientManager> ;
	ClientManager() {
	}
	~ClientManager() {
	}
	map<uint32_t, ClientAsync*> m_clients;
public:
	bool AddClient(ClientAsync* pClient);
	bool DelClient(ClientAsync* pClient);
	bool SendData(CFirePacket *packet);
	void onlineLog();
};

#endif /* _CLIENT_MANAGER_H_ */
