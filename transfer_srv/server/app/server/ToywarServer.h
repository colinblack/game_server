/*
 * ToywarServer.h
 *
 *  Created on: 2012-2-13
 *      Author: dada
 */

#ifndef TOYWARSERVER_H_
#define TOYWARSERVER_H_

#include "ServerInc.h"

class CToywarServer :
	public CTcpServer,
	public IGroupCallback
{
protected:
	CToywarServer();
public:
	static CToywarServer *GetInstance();
	bool Initialize();
	virtual void OnReceive(CPacket *pPacket);
	virtual void OnChannelClose(CTcpChannel *pChannel);
	virtual void OnIdle();
	bool SendRequest(CPacket *pPacket, IPacketSend *pRequestProtocol);
	bool SendReply(CPacket *pPacket, byte result, IPacketSend *pReplyProtocol = NULL);
protected:
	void OnProtocol(CPacket *pPacket, IPacketReceive *pProtocol);
public:
	int OnLogin();
	int OnLogout();
	int OnRefresh();
	int OnUpdataUser();
	int OnGroupList();
	int OnGroupListExt();
	int OnGroupCreate();
	int OnGroupJoin();
	int OnGroupExit();
	int OnGroupNotify();
	int OnGroupReady();
	int OnGroupUsers();
	int OnGroupStat();
	int OnKickGroup();
	virtual void OnGroupEvent(GroupEvent event, unsigned uid, const GroupData &group);
	int OnCcTransferSubmit();
	int OnCcTransferPush();
	int OnChatSubmit();
	int OnChatPush();
	int OnForbidChat();
	int OnGroupUserDelay();

protected:
	CSessionManager m_sessionManager;
	CUserManager m_userManager;
	CGroupManager m_groupManager;
	SessionData m_currSession;
	CPacket *m_pReceivePacket;
	IPacketReceive *m_pReceiveProtocol;
	IPacketSend *m_pReplyProtocol;
};

#endif /* TOYWARSERVER_H_ */
