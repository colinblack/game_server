#ifndef EMAIL_MANAGER_H_
#define EMAIL_MANAGER_H_

#include "DataEmail.h"
#include "IManager.h"

class EmailManager: public IManager {
public:
	EmailManager() {
	}
	~EmailManager() {
	}
	bool load(uint32_t uid);
	bool doPacket(CNetPacket * packet);
	bool addEmail(uint32_t uid, const string &title, const string &content, const string &attatch);
private:
	bool doQueryList(uint32_t type = 1);
	bool doDelete(CNetPacket* packet);
	bool doRead(CNetPacket* packet);
	bool doGet(CNetPacket* packet);
	bool doWrite(CNetPacket* packet);
	void sendDelete(uint32_t id);
	void onLoadRemoveEmail();
	bool updateEmail(const DataEmail &data);
private:
	vector<DataEmail> m_emails;
};

#endif /* EMAIL_MANAGER_H_ */
