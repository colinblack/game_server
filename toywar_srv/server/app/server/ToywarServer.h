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
	void OnAdAnalize(unsigned uid, const string &vip, const string &lvl,  const string& msg);
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
	virtual void OnGroupEvent(GroupEvent event, unsigned uid,const GroupData &group,unsigned groupA,unsigned groupB);
	void OnAllianceFightGroupEvent(unsigned uid, const GroupData &group, int heroId, int releaseHeroId);
	int OnCcTransferSubmit();
	int OnCcTransferPush();
	int OnChatSubmit();
	int OnChatPush();
	int OnForbidChat();
	int OnGroupUserDelay();
	int OnAddFightMatch(unsigned groupId);
	void OnMatch();
	int SendMatchMessage(unsigned groupId,unsigned groupIdA,unsigned groupIdB);
	int GetFightGroupUser(unsigned groupId,vector<uint32_t> &datauser);
	int OnSelectHero();
	int OnSelectHeroStat();
	int OnChibiWarAttackSubmit();
	int OnChibiWarSkillSubmit();
	int OnNewWorldBattleSubmit();
	int OnNewWorldBattleBattleSubmit();
	int OnAllianceHelpNotice();
	int GetAllianceNewBattleGroupUser(unsigned groupId,vector<uint32_t> &datauser);
protected:
	CSessionManager m_sessionManager;
	CUserManager m_userManager;
	CGroupManager m_groupManager;
	SessionData m_currSession;
	CPacket *m_pReceivePacket;
	IPacketReceive *m_pReceiveProtocol;
	IPacketSend *m_pReplyProtocol;

	FightMatch m_fightmatch;
};

#endif /* TOYWARSERVER_H_ */
