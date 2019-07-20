/*
 * CHATManager.h
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#ifndef CHAT_MANAGER_H_
#define CHAT_MANAGER_H_

#include "BattleBaseInc.h"

class ChatManager: public CSingleton<ChatManager> {
private:
	friend class CSingleton<ChatManager> ;
	ChatManager();
	~ChatManager();
	set<uint32_t> m_unknow;
public:
	bool Init();
	bool ActorLogin(uint32_t uid);
public:


public:
	int Process(uint32_t uid, chat::CSChatProxy *req);

public:

};

#endif /* CHAT_MANAGER_H_ */
