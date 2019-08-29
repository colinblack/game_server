/*
 * ChatManager.cpp
 *
 *  Created on: 2016年4月26日
 *      Author: Administrator
 */

#include "ChatManager.h"
#include "ProtocolAdmin.h"
#include "ChatAsync.h"
#include "ChatPacket.h"
#include "poll_thread.h"

CChatManager::CChatManager() :
		m_pChatChannel(NULL), m_sessionKey(0), m_isMultiThread(false), m_userId(0), m_lastTime(0)
{

}

CChatManager::~CChatManager()
{
}

bool CChatManager::init(CPollThread *pPollThread, bool isMultiThread)
{
	if (!pPollThread)
	{
		return false;
	}
	m_isMultiThread = isMultiThread;
	m_pChatChannel = new CChatAsync(pPollThread);
	m_userId = 20000 + Config::GetIntValue("server_id");
	m_lastTime = time(NULL);
	return m_pChatChannel->init();
}

void CChatManager::onReceive(CChatPacket *packet)
{
	if (m_isMultiThread)
	{
		if (m_recvMutex.acquire() == 0)
		{
			m_recvQueue.push_back(packet);
			m_recvMutex.release();
		}
	}
	else
	{
		doProcess(packet);
	}
}

void CChatManager::doChatPacket()
{
	if (!m_isMultiThread)
	{
		return;
	}

	list<CChatPacket*> listRec;
	if (m_recvMutex.acquire() == 0)
	{
		listRec = m_recvQueue;
		m_recvQueue.clear();
		m_recvMutex.release();
	}

	CChatPacket *packet = NULL;
	for (list<CChatPacket*>::iterator it = listRec.begin(); it != listRec.end(); ++it)
	{
		packet = *it;
		doProcess(packet);
	}
}

void CChatManager::doProcess(CChatPacket *packet)
{
	if (packet->ProtocolType == PROTOCOL_TYPE_LOGIN)
	{
		onLoginRsp(packet);
	}

	delete packet;
}

void CChatManager::sendChat(CChatPacket *packet)
{
	if (m_isMultiThread)
	{
		if (m_sendMutex.acquire() == 0)
		{
			CChatPacket *sendPacket = new CChatPacket(*packet);
			m_sendQueue.push_back(sendPacket);
			m_sendMutex.release();
		}
	}
	else
	{
		CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> buffer;
		packet->Encode(&buffer);
		m_pChatChannel->sendData(&buffer);
	}
}

void CChatManager::sendChat()
{
	if (!m_isMultiThread)
	{
		return;
	}

	list<CChatPacket*> listSend;
	if (m_sendMutex.acquire() == 0)
	{
		listSend = m_sendQueue;
		m_sendQueue.clear();
		m_sendMutex.release();
	}

	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> buffer;
	CChatPacket *packet = NULL;
	for (list<CChatPacket*>::iterator it = listSend.begin(); it != listSend.end(); ++it)
	{
		buffer.Clear();
		packet = *it;
		packet->Encode(&buffer);
		bool isSucc = m_pChatChannel->sendData(&buffer);
		delete packet;

		if (!isSucc)
		{
			break;
		}
	}
}

void CChatManager::onLogin()
{
	CLoginSend loginSend;
	CChatPacket packet;
	packet.UserId = m_userId;
	packet.ProtocolType = PROTOCOL_TYPE_LOGIN;
	packet.MainProtocolType = 1;
	packet.SubProtocolType = 1;
	packet.PacketType = PT_CSRequest;
	packet.ProtocolBody.Clear();

	CLoginSend cloginsend;
	cloginsend.name = "{\"name\":\"admin\",\"hname\":\"\",\"hlvl\":0}";
	cloginsend.platform = 2;

	if (!cloginsend.Encode(&packet.ProtocolBody))
	{
		error_log(" body encode failed");
		return;
	}

	sendChat(&packet);
}

void CChatManager::refresh()
{
	CChatPacket packet;
	packet.ProtocolType = PROTOCOL_TYPE_CHAT_SUBMIT;
	packet.MainProtocolType = 3;
	packet.SubProtocolType = 1;
	packet.PacketType = PT_CSRequest;
	packet.Key = m_sessionKey;
	packet.UserId = m_userId;

	CRefreshRequestProtocol chatrequest;
	chatrequest.delay = 30;
	chatrequest.ts = 30;
	chatrequest.Encode(&packet.ProtocolBody);

	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> buffer;
	packet.Encode(&buffer);

	sendChat(&packet);
}

void CChatManager::onLoginRsp(CChatPacket *packet)
{
	CLoginReceive cloginrec;
	if (!cloginrec.Decode(&(packet->ProtocolBody)))
	{
		return;
	}

	m_sessionKey = cloginrec.SessionKey;
}

void CChatManager::doBroadCast(const string &msg)
{
	return;
	if (m_sessionKey == 0)
	{
		onLogin();
		return;
	}

	CChatPacket packet;
	packet.ProtocolType = PROTOCOL_TYPE_CHAT_SUBMIT;
	packet.MainProtocolType = 4;
	packet.SubProtocolType = 1;
	packet.PacketType = PT_CSRequest;
	packet.Key = m_sessionKey;
	packet.UserId = m_userId;

	CChatRequest chatrequest;
	chatrequest.Message = msg;
	chatrequest.ToId = 10000005;
	chatrequest.ToType = 1;
	chatrequest.Encode(&packet.ProtocolBody);

	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> buffer;
	packet.Encode(&buffer);

	sendChat(&packet);
}

void CChatManager::onSecondTimer()
{
	if (Time::GetGlobalTime() > m_lastTime + 30)
	{
		refresh();
		m_lastTime = Time::GetGlobalTime();
	}
}

