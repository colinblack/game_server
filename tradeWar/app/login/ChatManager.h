/*
 * ChatManager.h
 *
 *  Created on: 2016年4月26日
 *      Author: aaron
 *        Desc: 聊天相关
 */

#ifndef CHATMANAGER_H_
#define CHATMANAGER_H_
#include "Kernel.h"
class CChatPacket;
class CChatAsync;

class CChatManager
{
public:
	virtual ~CChatManager();
	static CChatManager *getInstance()
	{
		static CChatManager ins;
		return &ins;
	}
public:
	bool init(CPollThread *pPollThread, bool isMultiThread = true);
	void onReceive(CChatPacket *packet);
	void doChatPacket();
	void doProcess(CChatPacket *packet);
	void sendChat(CChatPacket *packet);
	void sendChat();
	void onLogin();
	void refresh();
	void sendAdvert(uint32_t uid, uint32_t key, const string &msg);
	void clearKey()
	{
		m_sessionKey = 0;
	}
	void doBroadCast(const string &msg);
	void onSecondTimer();
private:
	void onLoginRsp(CChatPacket *packet);

private:
	CChatManager();
private:
	CChatAsync *m_pChatChannel;
	list<CChatPacket *> m_recvQueue;
	list<CChatPacket *> m_sendQueue;
	ThreadMutex m_recvMutex;		//接收队列锁
	ThreadMutex m_sendMutex;		//发送队列锁
	uint32_t m_sessionKey;
	bool m_isMultiThread;
	uint32_t m_userId;
	uint32_t m_lastTime;
};

#endif /* CHATMANAGER_H_ */
