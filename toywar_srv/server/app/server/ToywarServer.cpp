/*
 * ToywarServer.cpp
 *
 *  Created on: 2012-2-13
 *      Author: dada
 */
#include <pthread.h>
#include "ToywarServer.h"
#include "ToywarProtocol.h"

#include "AdAnalize.h"

#define SERVER_SESSION_TIMEOUT 60
#define SERVER_STAT_INTERVAL 300
static map<unsigned, unsigned> g_ForbidUserList;

#define BUSI_LOG(type,subtype,fmt,args...) CDataLog::DataLog(type,GetChannel(m_pReceivePacket->ChannelId)?GetChannel(m_pReceivePacket->ChannelId)->GetRemoteAddress()->ToString().c_str():"",subtype,fmt,##args)

static void OnExit() {
	CToywarServer::GetInstance()->Close();
}

static bool ParseAddress(vector<CInternetAddress> &vecAddress,
		const string &sAddress) {
	//printf("sAddress=%s\n",sAddress.c_str());
	if (sAddress.empty()) {
		return false;
	}
	vector<string> vecStrAddress;
	CBasic::StringSplitTrim(sAddress, ",", vecStrAddress);
	for (vector<string>::iterator itr = vecStrAddress.begin(); itr
			!= vecStrAddress.end(); itr++) {
		CInternetAddress address;
		if (address.FromString(*itr)) {
			vecAddress.push_back(address);
		}
	}
	return vecAddress.size() != 0;
}

CToywarServer::CToywarServer() {
	m_groupManager.SetGroupCallback(this);
}

CToywarServer *CToywarServer::GetInstance() {
	static CToywarServer server;
	return &server;
}

bool CToywarServer::Initialize() {

	if (!Kernel::Init()) {
		printf("[Kernel::Init fail][server=Toywar]\n");
		return false;
	}
	vector<CInternetAddress> listenAddress;
	if (!ParseAddress(listenAddress, Config::GetValue("server_listen"))) {
		printf("[ParseAddress fail]\n");
		return false;
	}
	int maxConn = TCP_SERVER_MAX_CONNECTIONS;
	Config::GetIntValue(maxConn, "server_max_conn");
	if (!CTcpServer::Initialize(listenAddress, maxConn)) {
		printf("[TcpServer::Initialize fail]\n");
		return false;
	}
	if (!System::InitDaemon(NULL, OnExit)) {
		printf("[System::InitDaemon fail][error=%d]\n", errno);
		return false;
	}

	return true;
}

void CToywarServer::OnReceive(CPacket *pPacket) {
	if (pPacket == NULL) {
		return;
	}

	const CTcpChannel *pChannel = GetChannel(pPacket->ChannelId);
	string remoteInfo;
	if (pChannel != NULL) {
		remoteInfo = pChannel->GetRemoteAddress()->ToString();
	}

#define ON_RECEIVE_ERROR_RETURN(error)	SendReply(pPacket, error); return ;

	/*\
	DATA_LOG("tcp", remoteInfo.c_str(), "recv", "%s",	\
				pPacket->ToString().c_str());	\
	SendReply(pPacket, error);	\
	return ;	\*/
	if(pPacket->MainProtocolType == 7 && pPacket ->SubProtocolType ==1)
	{
		OnMatch();
		return;
	}

	if (!IsValidUid(pPacket->UserId)) {
		error_log("[invalid_uid][uid=%u]", pPacket->UserId);
		SendReply(pPacket, R_ERR_PARAM);
		return;
	}

	//check session
	if (pPacket->ProtocolType != PROTOCOL_TYPE_LOGIN) {
		if (!m_sessionManager.GetSession(m_pReceivePacket->ChannelId,
				m_currSession)) {
			error_log("[session_not_exist][packet:%s]", pPacket->ToString().c_str());
			ON_RECEIVE_ERROR_RETURN(R_ERR_SESSION);
		}
		if (m_currSession.SessionKey != m_pReceivePacket->Key) {
			error_log("[session_key_mismatch][realkey=0x%08X,packet:%s]", m_currSession.SessionKey, pPacket->ToString().c_str());
			ON_RECEIVE_ERROR_RETURN(R_ERR_SESSION);
		}
		if (m_currSession.UserId != m_pReceivePacket->UserId) {
			error_log("[session_uid_mismatch][realuid=%u,packet:%s]", m_currSession.UserId, pPacket->ToString().c_str());
			ON_RECEIVE_ERROR_RETURN(R_ERR_SESSION);
		}
		if (!m_sessionManager.ActiveSession(m_pReceivePacket->ChannelId)) {
			error_log("[active_session_fail][sessionId=%d,uid=%u]", m_pReceivePacket->ChannelId, m_pReceivePacket->UserId);
			ON_RECEIVE_ERROR_RETURN(R_ERR_SESSION);
		}
	}

	//decode protocol
	IPacketReceive *pProtocol = NULL;
	bool unknowProcotol = false;
	if (pPacket->PacketType == PT_CSRequest) {
		//C->S请求
		switch (pPacket->ProtocolType) {
		case PROTOCOL_TYPE_LOGIN: {
			pProtocol = new CLoginRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_LOGOUT: {
			pProtocol = new CLogoutRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_REFRESH: {
			pProtocol = new CRefreshRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_UPDATAUSER: {
			pProtocol = new CUpdataUserRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_LIST: {
			pProtocol = new CGroupListRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_LIST_EXT: {
			pProtocol = new CGroupListRequestExtProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_CREATE: {
			pProtocol = new CGroupCreateRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_JOIN: {
			pProtocol = new CGroupJoinRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_EXIT: {
			pProtocol = new CGroupExitRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_READY: {
			pProtocol = new CGroupReadyProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_STAT: {
			pProtocol = new CGroupStatProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_UL: {
			pProtocol = new CGroupULProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_KICK: {
			pProtocol = new CGroupKickProtocol;
			break;
		}
		case PROTOCOL_TYPE_CC_TRANSFER_SUBMIT: {
			pProtocol = new CCcTransferSubmitRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_CHAT_SUBMIT: {
			pProtocol = new CChatSubmitRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_FORBID_CHAT: {
			pProtocol = new CForbidChatRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_UD: {
			pProtocol = new CGroupULProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_SELECT_HERO: {
			pProtocol = new CAFightHeroRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_GROUP_SELECT_HERO_STAT: {
			pProtocol = new CAFightHeroStatRequestProtocol;
			break;
		}
		case PROTOCOL_TYPE_CHIBI_WAR_ATTACK:
		{
			pProtocol = new CChibiWarAttackRequestProtocol();
			break;
		}
		case PROTOCOL_TYPE_CHIBI_WAR_SKILL:
		{
			pProtocol = new CChibiWarSkillRequestProtocol();
			break;
		}
		case PROTOCOL_TYPE_NEW_WORLD_BATTLE:
		{
			pProtocol = new CNewWorldBattleRequestProtocol();
			break;
		}
		case PROTOCOL_TYPE_NEW_WORLD_BATTLE_BATTLE:
		{
			pProtocol = new CNewWorldBattleBattleRequestProtocol();
			break;
		}
		case PROTOCOL_TYPE_ALLIANCE_HELP_NOTICE:
		{
			pProtocol = new CCAllianceHelpNoticeRequestProtocol();
			break;
		}
		default: {
			unknowProcotol = true;
			break;
		}
		}

	} else if (pPacket->PacketType == PT_SCReply) {
		//S->C答复
		switch (pPacket->ProtocolType) {
		case PROTOCOL_TYPE_GROUP_NOTIFY: {
			pProtocol = new CGroupNotifyReplyProtocol;
			break;
		}
		case PROTOCOL_TYPE_CC_TRANSFER_PUSH: {
			pProtocol = new CCcTransferPushReplyProtocol;
			break;
		}
		case PROTOCOL_TYPE_CHAT_PUSH: {
			pProtocol = new CChatPushReplyProtocol;
			break;
		}
		default: {
			unknowProcotol = true;
			break;
		}
		}
	}
	if (unknowProcotol) {
		error_log("[unexpect_packet][packet:%s,body=%s]", pPacket->ToString().c_str(), pPacket->ProtocolBody.ToString().c_str());
		ON_RECEIVE_ERROR_RETURN(R_ERR_PARAM);
	}
	if (pProtocol == NULL) {
		fatal_log("[heap_new_fail]");
		ON_RECEIVE_ERROR_RETURN(R_ERR_REFUSE);
	}
	if (!pProtocol->Decode(&pPacket->ProtocolBody)) {
		error_log("[decode_protocol_error][packet:%s,body=%s]", pPacket->ToString().c_str(), pPacket->ProtocolBody.ToString().c_str());
		ON_RECEIVE_ERROR_RETURN(R_ERR_PARAM);
	}

	//DATA_LOG("tcp", remoteInfo.c_str(), "recv", "%s&Protocol&%s", pPacket->ToString().c_str(), pProtocol->ToString().c_str());

	//process protocol
	OnProtocol(pPacket, pProtocol);

	delete pProtocol;

	return;
}

void CToywarServer::OnChannelClose(CTcpChannel *pChannel) {
	if (pChannel != NULL) {
		SessionData sessionData;
		if (m_sessionManager.GetSession(pChannel->GetChannelId(), sessionData)) {
			//DATA_LOG("tcp", pChannel->GetRemoteAddress()->ToString().c_str(), "close",
			//		"cid=%d&uid=%u", pChannel->GetChannelId(), sessionData.UserId);
			m_groupManager.RemoveUser(sessionData.UserId);
			m_userManager.RemoveUser(sessionData.UserId);
			m_sessionManager.RemoveSession(sessionData.SessionId);
			m_fightmatch.RemoveHaveMatchGroup(sessionData.UserId);

		}
	}
}

void CToywarServer::OnIdle() {
	vector<int> expiredSessions;
	m_sessionManager.GetExpiredSessions(expiredSessions, Time::GetGlobalTime()
			- ONLINE_TIMEOUT);
	for (vector<int>::iterator itr = expiredSessions.begin(); itr
			!= expiredSessions.end(); itr++) {
		CloseChannel(*itr);
	}
	static unsigned s_lastStatTime = 0;
	if (s_lastStatTime + SERVER_STAT_INTERVAL <= Time::GetGlobalTime()) {
		s_lastStatTime = Time::GetGlobalTime();
		info_log("[toyward_stat][sessions=%d]", m_sessionManager.GetSessionCount());
	}
}

bool CToywarServer::SendRequest(CPacket *pPacket, IPacketSend *pRequestProtocol) {
	if (pPacket == NULL || pRequestProtocol == NULL) {
		return false;
	}
	pPacket->ChannelId = m_userManager.GetSessionId(pPacket->UserId);

	if (pPacket->ChannelId < 0) {
		return false;
	}
	SessionData sessionData;
	if (!m_sessionManager.GetSession(pPacket->ChannelId, sessionData)) {
		return false;
	}
	pPacket->Key = sessionData.SessionKey;
	pPacket->PacketType = PT_SCRequest;
	pPacket->From = 0;
	pPacket->To = 0;
	pPacket->SequenceNo = 0;
	pPacket->RetryTime = 0;

	if (!SendData(pPacket, pRequestProtocol)) {
		return false;
	}
	return true;
}

bool CToywarServer::SendReply(CPacket *pPacket, byte result,
		IPacketSend *pReplyProtocol) {
	CPacket replyPacket;
	replyPacket.ChannelId = pPacket->ChannelId;
	replyPacket.PacketType = (EPacketType) (pPacket->PacketType | 0x1);
	replyPacket.From = pPacket->To;
	replyPacket.To = pPacket->From;
	replyPacket.SequenceNo = pPacket->SequenceNo;
	replyPacket.RetryTime = 0;
	replyPacket.UserId = pPacket->UserId;
	replyPacket.Key = pPacket->Key;
	replyPacket.ProtocolType = pPacket->ProtocolType;
	replyPacket.ProtocolFlag = 0;
	replyPacket.ProtocolResult = result;

	if (!SendData(&replyPacket, pReplyProtocol)) {
		return false;
	}
	return true;
}

void CToywarServer::OnProtocol(CPacket *pPacket, IPacketReceive *pProtocol) {
	int ret = 0;
	m_pReceivePacket = pPacket;
	m_pReceiveProtocol = pProtocol;
	m_pReplyProtocol = NULL;
	switch (pPacket->ProtocolType) {
	case PROTOCOL_TYPE_LOGIN: {
		ret = OnLogin();
		break;
	}
	case PROTOCOL_TYPE_LOGOUT: {
		ret = OnLogout();
		break;
	}
	case PROTOCOL_TYPE_REFRESH: {
		ret = OnRefresh();
		break;
	}
	case PROTOCOL_TYPE_UPDATAUSER: {
		ret = OnUpdataUser();
		break;
	}
	case PROTOCOL_TYPE_GROUP_LIST: {
		ret = OnGroupList();
		break;
	}
	case PROTOCOL_TYPE_GROUP_LIST_EXT: {
		ret = OnGroupListExt();
		break;
	}
	case PROTOCOL_TYPE_GROUP_CREATE: {
		ret = OnGroupCreate();
		break;
	}
	case PROTOCOL_TYPE_GROUP_JOIN: {
		ret = OnGroupJoin();
		break;
	}
	case PROTOCOL_TYPE_GROUP_EXIT: {
		ret = OnGroupExit();
		break;
	}
	case PROTOCOL_TYPE_GROUP_NOTIFY: {
		ret = OnGroupNotify();
		break;
	}
	case PROTOCOL_TYPE_GROUP_READY: {
		ret = OnGroupReady();
		break;
	}
	case PROTOCOL_TYPE_GROUP_STAT: {
		ret = OnGroupStat();
		break;
	}
	case PROTOCOL_TYPE_GROUP_UL: {
		ret = OnGroupUsers();
		break;
	}
	case PROTOCOL_TYPE_GROUP_KICK: {
		ret = OnKickGroup();
		break;
	}
	case PROTOCOL_TYPE_CC_TRANSFER_SUBMIT: {
		ret = OnCcTransferSubmit();
		break;
	}
	case PROTOCOL_TYPE_CC_TRANSFER_PUSH: {
		ret = OnCcTransferPush();
		break;
	}
	case PROTOCOL_TYPE_CHAT_SUBMIT: {
		ret = OnChatSubmit();
		break;
	}
	case PROTOCOL_TYPE_CHAT_PUSH: {
		ret = OnChatPush();
		break;
	}
	case PROTOCOL_TYPE_FORBID_CHAT: {
		ret = OnForbidChat();
		break;
	}
	case PROTOCOL_TYPE_GROUP_UD: {
		ret = OnGroupUserDelay();
		break;
	}
	case PROTOCOL_TYPE_GROUP_SELECT_HERO: {
		ret = OnSelectHero();
		break;
	}
	case PROTOCOL_TYPE_GROUP_SELECT_HERO_STAT:{
		ret = OnSelectHeroStat();
		break;
	}
	case PROTOCOL_TYPE_CHIBI_WAR_ATTACK:
	{
		ret = OnChibiWarAttackSubmit();
		break;
	}
	case PROTOCOL_TYPE_CHIBI_WAR_SKILL:
	{
		ret = OnChibiWarSkillSubmit();
		break;
	}
//	case PROTOCOL_TYPE_FIGHTMATCH_CHAT: {
//		ret = OnAddFightMatch();
//	}
//	case PROTOCOL_EVENT_SECOND_TIMER:{
//		ret = OnMatch();
//	}
	case PROTOCOL_TYPE_NEW_WORLD_BATTLE:
	{
		ret = OnNewWorldBattleSubmit();
		break;
	}
	case PROTOCOL_TYPE_NEW_WORLD_BATTLE_BATTLE:
	{
		ret = OnNewWorldBattleBattleSubmit();
		break;
	}
	case PROTOCOL_TYPE_ALLIANCE_HELP_NOTICE:
	{
		ret = OnAllianceHelpNotice();
		break;
	}
	default: {
		fatal_log("[unexpect_protocol][uid=%u,type=%d,mpn=%d,spn=%d,body=%u]",
				pPacket->UserId, (int)pPacket->PacketType, (int)pPacket->MainProtocolType,
				(int)pPacket->SubProtocolType, pPacket->ProtocolBody.GetSize());
		return;
	}
	}
	if (pPacket->IsRequest()) {
		if (ret == 0) {
			SendReply(pPacket, ret, m_pReplyProtocol);
		} else {
			SendReply(pPacket, ret);
		}
	}
	if (m_pReplyProtocol != NULL) {
		delete m_pReplyProtocol;
		m_pReplyProtocol = NULL;
	}
}

int CToywarServer::OnLogin() {
	int sessionId = m_userManager.GetSessionId(m_pReceivePacket->UserId);
	if (sessionId >= 0) {
		CloseChannel(sessionId);
	}
	CLoginRequestProtocol *pLoginRequest =
			(CLoginRequestProtocol *) m_pReceiveProtocol;
	SessionData sessionData;
	sessionData.SessionId = m_pReceivePacket->ChannelId;
	sessionData.UserId = m_pReceivePacket->UserId;
	if (!m_sessionManager.AddSession(sessionData)) {
		error_log("[add_session_fail][sessionid=%d,uid=%u]", m_pReceivePacket->ChannelId, m_pReceivePacket->UserId);
		return R_ERR_SESSION;
	}
	UserData user;
	user.UserId = sessionData.UserId;
	user.SessionId = sessionData.SessionId;
	user.Platform = pLoginRequest->Platform;
	user.Name = pLoginRequest->Name;
	user.Delay = 0;
	if (!m_userManager.AddUser(user)) {
		error_log("[add_user_fail][sessionid=%d,uid=%u]", sessionData.SessionId, sessionData.UserId);
		m_sessionManager.RemoveSession(sessionData.SessionId);
		return R_ERR_SESSION;
	}
	int ret = m_groupManager.JoinGroup(user.UserId, GT_USER, user.UserId);
	if (ret != 0) {
		error_log("[add_user_group_fail][ret=%d,uid=%u]", ret, sessionData.UserId);
	}
	CLoginReplyProtocol *pLoginReply = new CLoginReplyProtocol;
	m_pReplyProtocol = pLoginReply;
	pLoginReply->SessionKey = sessionData.SessionKey;
	pLoginReply->SecretKey = sessionData.SecretKey;

	BUSI_LOG("login","login","%u|%u|%u|%s",user.UserId,user.SessionId,user.Platform,user.Name.c_str());

	return 0;
}

int CToywarServer::OnLogout() {
	//不立刻关闭，等超时
	//	int sessionId = m_session.GetSessionId(m_pReceivePacket->UserId);
	//	if(sessionId < 0)
	//	{
	//		return R_ERR_SESSION;
	//	}
	//CloseChannel(sessionId);
	return 0;
}

int CToywarServer::OnRefresh() {
	CRefreshRequestProtocol *pRequest =
			(CRefreshRequestProtocol*) m_pReceiveProtocol;
	UserData user;
	if (m_userManager.GetUser(m_pReceivePacket->UserId, user)) {
		user.Delay = pRequest->delay;
		//fatal_log("DelayNum  uid=%d,Delay=%d",user.UserId,user.Delay);
		if (!m_userManager.AddUser(user)) {
			error_log("add user faile");
		}
	}

	CRefreshReplyProtocol* pReply = new CRefreshReplyProtocol;
	m_pReplyProtocol = pReply;
	pReply->ts = pRequest->ts;
	return 0;
}

int CToywarServer::OnUpdataUser() {
	CUpdataUserRequestProtocol *pUpdataUserRequest =
			(CUpdataUserRequestProtocol *) m_pReceiveProtocol;
	UserData user;
	if (!m_userManager.GetUser(m_pReceivePacket->UserId, user)) {
		error_log("[get user fail][uid=%u]", m_pReceivePacket->UserId);
		return R_ERR_SESSION;
	}

	user.Platform = pUpdataUserRequest->Platform;
	user.Name = pUpdataUserRequest->Name;
	if (!m_userManager.AddUser(user)) {
		error_log("OnUpdataUser AddUser error!");
		return R_ERR_SESSION;
	}

	BUSI_LOG("updatauser","updatauser","%u|%u|%u|%s",user.UserId,user.SessionId,user.Platform,user.Name.c_str());

	return 0;
}

int CToywarServer::OnGroupList() {
	CGroupListRequestProtocol *pGroupListRequest =
			(CGroupListRequestProtocol *) m_pReceiveProtocol;
	CGroupListReplyProtocol *pGroupListReply = new CGroupListReplyProtocol;
	m_pReplyProtocol = pGroupListReply;
	int ret = m_groupManager.GetGroupList((GroupType) pGroupListRequest->Type,
			pGroupListReply->Groups);
	if (ret != 0) {
		return ret;
	}
	return 0;
}

int CToywarServer::OnGroupListExt() {
	CGroupListRequestExtProtocol *pGroupListRequest =
			(CGroupListRequestExtProtocol *) m_pReceiveProtocol;
	CGroupListReplyExtProtocol *pGroupListReply =
			new CGroupListReplyExtProtocol;
	m_pReplyProtocol = pGroupListReply;
	pGroupListReply->Type = pGroupListRequest->Type;
	int ret = m_groupManager.GetGroupList((GroupType) pGroupListRequest->Type,
			pGroupListReply->Groups);
	if (ret != 0) {
		return ret;
	}
	return 0;
}

int CToywarServer::OnGroupUsers() {
	int ret;
	CGroupULProtocol* pGroupULRequest = (CGroupULProtocol*) m_pReceiveProtocol;

	if (pGroupULRequest->ToType != GT_COMBAT
		&& pGroupULRequest->ToType != GT_ALLIANCE_NEW_BATTLE
		&& pGroupULRequest->ToType != GT_FIGHT) {
		error_log("unexpected request [uid=%u,toid=%u]", m_pReceivePacket->UserId, pGroupULRequest->ToType);
		return R_ERR_PARAM;
	}

	CGroupULReplyProtocol* pGroupULReply = new CGroupULReplyProtocol;
	m_pReplyProtocol = pGroupULReply;
	pGroupULReply->ToType = pGroupULRequest->ToType;

	vector<uint32_t> toUsers;
	GroupData data;
	ret = m_groupManager.GetGroupData((GroupType) pGroupULRequest->ToType,
			pGroupULRequest->ToId, data);
	if (ret != 0) {
		return ret;
	}

	toUsers = data.Users;
	pGroupULReply->Users.resize(toUsers.size());
	int i = 0;
	for (vector<uint32_t>::const_iterator it = toUsers.begin(); it
			!= toUsers.end(); ++it) {
		m_userManager.GetUser(*it, pGroupULReply->Users[i++]);
	}

	return 0;
}

int CToywarServer::OnGroupUserDelay() {
	int ret;
	CGroupULProtocol* pGroupULRequest = (CGroupULProtocol*) m_pReceiveProtocol;

	if (pGroupULRequest->ToType != GT_COMBAT && pGroupULRequest->ToType != GT_FIGHT&& pGroupULRequest->ToType != GT_NATIONFIGHT && pGroupULRequest->ToType != GT_ALLIANCE_FIGHT)
	{
		error_log("unexpected request [uid=%u,toid=%u]", m_pReceivePacket->UserId, pGroupULRequest->ToType);
		return R_ERR_PARAM;
	}

	CGroupUDReplyProtocol* pGroupUDReply = new CGroupUDReplyProtocol;
	m_pReplyProtocol = pGroupUDReply;
	pGroupUDReply->ToType = pGroupULRequest->ToType;

	unsigned gid = pGroupULRequest->ToId;
	if ((GroupType) pGroupULRequest->ToType == GT_ALLIANCE_FIGHT)
	{
		gid = GET_ALLIANCE_FIGHT_GROUP_ID(pGroupULRequest->ToId, pGroupULRequest->Room);
	}
	vector<uint32_t> toUsers;
	GroupData data;
	ret = m_groupManager.GetGroupData((GroupType) pGroupULRequest->ToType, gid, data);
	if (ret != 0) {
		return ret;
	}

	toUsers = data.Users;
	pGroupUDReply->Users.resize(toUsers.size());
	int i = 0;
	for (vector<uint32_t>::const_iterator it = toUsers.begin(); it
			!= toUsers.end(); ++it) {
		m_userManager.GetUser(*it, pGroupUDReply->Users[i++]);
	}

	return 0;
}

int CToywarServer::OnGroupCreate() {
	CGroupCreateRequestProtocol *pGroupCreateRequest =
			(CGroupCreateRequestProtocol *) m_pReceiveProtocol;
	GroupInfo group;
	if (!StringFilter::Check(pGroupCreateRequest->Name)) {
		//return PR_ILLEGAL_PARAM;
	}
	group.Id = pGroupCreateRequest->Id;
	if ((GroupType) pGroupCreateRequest->Type == GT_FIGHT) {
		m_userManager.UpdateUser(pGroupCreateRequest->Id,
				pGroupCreateRequest->FightNum);
	}
	if ((GroupType) pGroupCreateRequest->Type == GT_ALLIANCE_FIGHT) {
		group.Id = GET_ALLIANCE_FIGHT_GROUP_ID(pGroupCreateRequest->Id, pGroupCreateRequest->AllianceFightRoom);
	}
	int ret = m_groupManager.CreateGroup(m_pReceivePacket->UserId, (GroupType) pGroupCreateRequest->Type, pGroupCreateRequest->Name,group);
	if (ret != 0) {
		return ret;
	}
	CGroupCreateReplyProtocol *pGroupCreateReply = new CGroupCreateReplyProtocol;
	m_pReplyProtocol = pGroupCreateReply;
	pGroupCreateReply->Id = group.Id;
	pGroupCreateReply->UserCount = group.UserCount;
	pGroupCreateReply->MaxCount = group.MaxCount;

	BUSI_LOG(GroupNames[pGroupCreateRequest->Type],"create","%u|%u|%d|%d",
			m_pReceivePacket->UserId,
			group.Id,
			group.UserCount,
			group.MaxCount);

	return 0;
}

int CToywarServer::OnGroupJoin() {
	CGroupJoinRequestProtocol *pGroupJoinRequest =
			(CGroupJoinRequestProtocol *) m_pReceiveProtocol;
	GroupInfo group;
	if ((GroupType) pGroupJoinRequest->Type == GT_FIGHT) {
		m_userManager.UpdateUser(m_pReceivePacket->UserId,
				pGroupJoinRequest->FightNum);
	}
	int ret = m_groupManager.JoinGroup(m_pReceivePacket->UserId,
			(GroupType) pGroupJoinRequest->Type, pGroupJoinRequest->Id, &group);
	if (ret != 0) {
		return ret;
	}
	CGroupJoinReplyProtocol *pGroupJoinReply = new CGroupJoinReplyProtocol;
	m_pReplyProtocol = pGroupJoinReply;
	pGroupJoinReply->Name = group.Name;
	pGroupJoinReply->UserCount = group.UserCount;
	pGroupJoinReply->MaxCount = group.MaxCount;

	BUSI_LOG(GroupNames[pGroupJoinRequest->Type],"join","%u|%u|%d|%d",
			m_pReceivePacket->UserId,
			group.Id,
			group.UserCount,
			group.MaxCount);

	return 0;
}

int CToywarServer::OnGroupExit() {
	CGroupExitRequestProtocol *pGroupExitRequest = (CGroupExitRequestProtocol *) m_pReceiveProtocol;

	unsigned gid = pGroupExitRequest->Id;
	if (pGroupExitRequest->Type == GT_ALLIANCE_FIGHT)
	{
		gid = GET_ALLIANCE_FIGHT_GROUP_ID(pGroupExitRequest->Id, pGroupExitRequest->AllianceFightRoom);
	}

	int ret = m_groupManager.ExitGroup2(m_pReceivePacket->UserId, (GroupType)pGroupExitRequest->Type, gid);
	if (GT_ALLIANCE_FIGHT == (GroupType)pGroupExitRequest->Type)
	{
		int releaseHid = -1;
		m_groupManager.ReleaseAllianceHero(m_pReceivePacket->UserId, gid, releaseHid);
		if (-1 != releaseHid)
		{
			GroupData data;
			int result = m_groupManager.GetGroupData(GT_ALLIANCE_FIGHT, gid, data);
			if (result == 0)
			{
				OnAllianceFightGroupEvent(m_pReceivePacket->UserId, data, -1, releaseHid);
			}
		}
	}

	BUSI_LOG(GroupNames[pGroupExitRequest->Type], "exit", "%u|%u", m_pReceivePacket->UserId, gid);
	return ret;
}

int CToywarServer::OnKickGroup() {
	int uid, ret;
	CGroupKickProtocol* pGroupKickRequest =
			(CGroupKickProtocol*) m_pReceiveProtocol;
	uid = pGroupKickRequest->UserId;
	ret = m_groupManager.ExitGroup(uid, (GroupType) pGroupKickRequest->ToType,
			pGroupKickRequest->ToId);
	if (ret != 0) {
		return ret;
	}

	UserData user;
	if (!m_userManager.GetUser(uid, user)) {
		return ret;
	}
	CGroupNotifyRequestProtocol groupNotifyRequest;
	groupNotifyRequest.Type = (GroupType) pGroupKickRequest->ToType;
	groupNotifyRequest.Id = pGroupKickRequest->ToId;
	groupNotifyRequest.Event = GE_EXIT;
	groupNotifyRequest.UserId = uid;
	groupNotifyRequest.UserName = user.Name;
	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_GROUP_NOTIFY;
	requestPacket.UserId = uid;

	SendRequest(&requestPacket, &groupNotifyRequest);

	BUSI_LOG(GroupNames[pGroupKickRequest->ToType],"kick","%u|%u|%u",
			m_pReceivePacket->UserId,
			pGroupKickRequest->ToId,
			pGroupKickRequest->UserId);

	return ret;
}

void CToywarServer::OnGroupEvent(GroupEvent event, unsigned uid, const GroupData &group)
{
	UserData user;
	if (!m_userManager.GetUser(uid, user)) {
		return;
	}
	CGroupNotifyRequestProtocol groupNotifyRequest;
	groupNotifyRequest.Type = group.Type;
	groupNotifyRequest.Id = group.Id;
	groupNotifyRequest.Event = event;
	groupNotifyRequest.UserId = uid;
	groupNotifyRequest.UserName = user.Name;
	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_GROUP_NOTIFY;
	const vector<uint32_t> users = group.Users; //SendRequest可能修改组用户，因此使用副本遍历
	for (vector<uint32_t>::const_iterator itr = users.begin(); itr
			!= users.end(); itr++) {
		if (*itr != uid) {
			requestPacket.UserId = *itr;
			SendRequest(&requestPacket, &groupNotifyRequest);
		}
	}
}

void CToywarServer::OnAllianceFightGroupEvent(unsigned uid, const GroupData &group, int heroId, int releaseHeroId)
{
	UserData user;
	if (!m_userManager.GetUser(uid, user)) {
		return;
	}
	CGroupNotifyRequestProtocol groupNotifyRequest;
	groupNotifyRequest.Type = group.Type;
	groupNotifyRequest.Id = group.Id;
	groupNotifyRequest.Event = GE_SELECT_ALLIANCE_HERO;
	groupNotifyRequest.UserId = uid;
	groupNotifyRequest.UserName = user.Name;
	groupNotifyRequest.HeroId = heroId;
	groupNotifyRequest.ReleaseHeroId = releaseHeroId;
	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_GROUP_NOTIFY;
	const vector<uint32_t> users = group.Users; //SendRequest可能修改组用户，因此使用副本遍历
	for (vector<uint32_t>::const_iterator itr = users.begin(); itr
			!= users.end(); itr++) {
		if (*itr != uid) {
			requestPacket.UserId = *itr;
			SendRequest(&requestPacket, &groupNotifyRequest);
		}
	}
}

void CToywarServer::OnGroupEvent(GroupEvent event, unsigned uid,
		const GroupData &group,unsigned groupA,unsigned groupB) {
	UserData user;
	if (!m_userManager.GetUser(uid, user)) {
		return;
	}
	CGroupNotifyRequestProtocol groupNotifyRequest;
	groupNotifyRequest.Type = group.Type;
	groupNotifyRequest.Id = group.Id;
	groupNotifyRequest.Event = event;
	groupNotifyRequest.UserId = uid;
	groupNotifyRequest.UserName = user.Name;
	groupNotifyRequest.GroupIdA = groupA;
	groupNotifyRequest.GroupIdB = groupB;
	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_GROUP_NOTIFY;
	const vector<uint32_t> users = group.Users; //SendRequest可能修改组用户，因此使用副本遍历
	for (vector<uint32_t>::const_iterator itr = users.begin(); itr
			!= users.end(); itr++) {
		if (*itr != uid) {
			requestPacket.UserId = *itr;
			SendRequest(&requestPacket, &groupNotifyRequest);
		}
	}
}

int CToywarServer::OnGroupNotify() {
	if (m_pReceivePacket->ProtocolResult != R_SUCCESS) {
		error_log("[group_notify_fail][uid=%u,result=%d]",
				m_pReceivePacket->UserId, (int)m_pReceivePacket->ProtocolResult);
	}
	return 0;
}

int CToywarServer::OnGroupReady() {
	int ret;
	CGroupReadyProtocol* pGroupReadyRequest =
			(CGroupReadyProtocol*) m_pReceiveProtocol;
	if (   (pGroupReadyRequest->ToType != GT_COMBAT && pGroupReadyRequest->ToType != GT_FIGHT && pGroupReadyRequest->ToType != GT_NATIONFIGHT && pGroupReadyRequest->ToType != GT_ALLIANCE_FIGHT)
		|| (pGroupReadyRequest->Event != GE_START &&pGroupReadyRequest->Event!= GE_MATCHING))
	{
		error_log("unexpected request [uid=%u,toid=%u]", m_pReceivePacket->UserId, pGroupReadyRequest->ToType);
		return R_ERR_PARAM;
	}

	unsigned gid = pGroupReadyRequest->ToId;
	if ((GroupType)pGroupReadyRequest->ToType == GT_ALLIANCE_FIGHT)
	{
		gid = GET_ALLIANCE_FIGHT_GROUP_ID(pGroupReadyRequest->ToId, pGroupReadyRequest->Room);
	}

	if((GroupType)pGroupReadyRequest->ToType == GT_FIGHT && (GroupEvent) pGroupReadyRequest->Event == GE_START)
	{
		GroupData data;
		ret = m_groupManager.GetGroupData((GroupType) pGroupReadyRequest->ToType, gid, data);
		if (ret != 0) {
			return ret;
		}

		unsigned gourpMatchId = m_groupManager.FindMatchGroupId(gid);
		if(gourpMatchId != 0)
		{
			GroupData dataMatch;
			ret = m_groupManager.GetGroupData((GroupType) pGroupReadyRequest->ToType,gourpMatchId, dataMatch);
			if (ret != 0) {
				return ret;
			}
			OnGroupEvent((GroupEvent)pGroupReadyRequest->Event, m_pReceivePacket->UserId, data,gid,gourpMatchId);
			OnGroupEvent((GroupEvent)pGroupReadyRequest->Event, m_pReceivePacket->UserId, dataMatch,gid,gourpMatchId);
		}
	}
	else
	{
		GroupData data;
		ret = m_groupManager.GetGroupData((GroupType) pGroupReadyRequest->ToType, gid, data);
		if (ret != 0) {
			return ret;
		}
		OnGroupEvent((GroupEvent)pGroupReadyRequest->Event, m_pReceivePacket->UserId, data);
		//info_log("team boss start:[%d,%d]",	pGroupReadyRequest->ToId,data.Users.size());
	}
	BUSI_LOG(GroupNames[pGroupReadyRequest->ToType],"start","%u|%u",
			m_pReceivePacket->UserId,
			gid);

	return 0;
}

int CToywarServer::OnGroupStat() {
	int ret;
	CGroupStatProtocol* pGroupStatRequest = (CGroupStatProtocol*) m_pReceiveProtocol;
	if (pGroupStatRequest->ToType != GT_COMBAT && pGroupStatRequest->ToType != GT_FIGHT && pGroupStatRequest->ToType != GT_NATIONFIGHT && pGroupStatRequest->ToType != GT_ALLIANCE_FIGHT) {
		error_log("unexpected request [uid=%u,toid=%u]", m_pReceivePacket->UserId, pGroupStatRequest->ToType);
		return R_ERR_PARAM;
	}
	unsigned gid = pGroupStatRequest->ToId;
	if (pGroupStatRequest->ToType == GT_ALLIANCE_FIGHT)
	{
		gid = GET_ALLIANCE_FIGHT_GROUP_ID(pGroupStatRequest->ToId, pGroupStatRequest->Room);
	}
	ret = m_groupManager.SetGroupStat((GroupType) pGroupStatRequest->ToType, gid, pGroupStatRequest->Stat);
	if(ret == 0)
	{
		if((GroupType) pGroupStatRequest->ToType == GT_FIGHT && pGroupStatRequest->Stat == 2)
		{
			OnAddFightMatch(gid);
		}
	}
	BUSI_LOG(GroupNames[pGroupStatRequest->ToType],"stat","%u|%u",m_pReceivePacket->UserId,gid);
	return ret;
}

int CToywarServer::OnCcTransferSubmit() {
	int ret;
	CCcTransferSubmitRequestProtocol *pCcSubmitRequest = (CCcTransferSubmitRequestProtocol *) m_pReceiveProtocol;
	if (pCcSubmitRequest->ToType != GT_USER
		&& pCcSubmitRequest->ToType!= GT_BATTLE
		&& pCcSubmitRequest->ToType != GT_COMBAT
		&& pCcSubmitRequest->ToType != GT_FIGHT
		&& pCcSubmitRequest->ToType != GT_NATIONFIGHT
		&& pCcSubmitRequest->ToType != GT_ALLIANCE_FIGHT
		&& pCcSubmitRequest->ToType != GT_ALLIANCE_NEW_BATTLE) {
		error_log("[unexpect_to_type][uid=%u,toid=%u]", m_pReceivePacket->UserId, pCcSubmitRequest->ToType);
		return R_ERR_PARAM;
	}
	unsigned gid = pCcSubmitRequest->ToId;
	vector<uint32_t> toUsers;
	if(pCcSubmitRequest->ToType == GT_FIGHT)
	{
		ret = GetFightGroupUser(pCcSubmitRequest->ToId,toUsers);
	}
	else
	{
		if (pCcSubmitRequest->ToType == GT_ALLIANCE_FIGHT)
		{
			gid = GET_ALLIANCE_FIGHT_GROUP_ID(pCcSubmitRequest->ToId, pCcSubmitRequest->allianceFightRoom);
		}
		ret = m_groupManager.GetGroupUsers(m_pReceivePacket->UserId,(GroupType) pCcSubmitRequest->ToType, gid, toUsers);
	}
	if (ret != 0) {
		return ret;
	}
	CCcTransferPushRequestProtocol ccPushRequest;
	ccPushRequest.FromUserId = m_pReceivePacket->UserId;
	ccPushRequest.ToType = pCcSubmitRequest->ToType;
	ccPushRequest.ToId = gid;
	ccPushRequest.Data.CopyFromBuffer(&pCcSubmitRequest->Data);
	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_CC_TRANSFER_PUSH;
	requestPacket.PacketFlag = m_pReceivePacket->PacketFlag;
	size_t failCount = 0;
	size_t totalCount = toUsers.size();
	for (vector<uint32_t>::const_iterator itr = toUsers.begin(); itr
			!= toUsers.end(); itr++) {
		if (*itr == m_pReceivePacket->UserId) {
			totalCount--;
		} else {
			requestPacket.UserId = *itr;
			if (!SendRequest(&requestPacket, &ccPushRequest)) {
				failCount++;
			}
		}
	}
	if (failCount > 0) {
		if (failCount == totalCount) {
			error_log("[cc_push_fail_all][fromuid=%u,totype=%u,toid=%u,usercount=%u,size=%u]",
					m_pReceivePacket->UserId, pCcSubmitRequest->ToType, pCcSubmitRequest->ToId,
					(unsigned)totalCount, ccPushRequest.Data.GetSize());
			return PR_PUSH_FAIL;
		} else {
			error_log("[cc_push_fail][fromuid=%u,totype=%u,toid=%u,totoluser=%u,fail=%u,size=%u]",
					m_pReceivePacket->UserId, pCcSubmitRequest->ToType, pCcSubmitRequest->ToId,
					(unsigned)totalCount, (unsigned)failCount, ccPushRequest.Data.GetSize());
		}
	} else if (totalCount == 0) {
		/*error_log("[cc_push_none][fromuid=%u,totype=%u,toid=%u,usercount=%d,size=%u]",
				m_pReceivePacket->UserId, pCcSubmitRequest->ToType, pCcSubmitRequest->ToId,
				(unsigned)toUsers.size(), ccPushRequest.Data.GetSize());*/
		return PR_PUSH_FAIL;
	}
	BUSI_LOG(GroupNames[pCcSubmitRequest->ToType],"cctr","%u|%u|%d|%d",
				m_pReceivePacket->UserId,pCcSubmitRequest->ToId,0,0);
	return 0;
}

int CToywarServer::OnCcTransferPush() {
	if (m_pReceivePacket->ProtocolResult != R_SUCCESS) {
		error_log("[cc_push_reply_fail][uid=%u,result=%d]",
				m_pReceivePacket->UserId, (int)m_pReceivePacket->ProtocolResult);
	}
	return 0;
}

int CToywarServer::OnChatSubmit() {
	int ret;
	CChatSubmitRequestProtocol *pChatSubmitRequest = (CChatSubmitRequestProtocol *) m_pReceiveProtocol;
	//add a logic for the system message which should not be filter
	//StringFilter::Replace(pChatSubmitRequest->Message);
	if (pChatSubmitRequest->ToType != GT_ALL) {
		StringFilter::Replace(pChatSubmitRequest->Message);
	}
	//	 add by aaron 20121114
	CDataForbidUser forbidUser;
	bool result = forbidUser.Init(Config::GetValue(CONFIG_FORBID_USER));
	if (result == true) {
		ret = forbidUser.GetUserList(g_ForbidUserList);
		if (0 == ret) {
			map<unsigned, unsigned>::iterator itr = g_ForbidUserList.find(
					m_pReceivePacket->UserId);
			if (itr != g_ForbidUserList.end()) {
				if (itr->second > Time::GetGlobalTime()) {
					if(pChatSubmitRequest->ToType == GT_NATION
					|| pChatSubmitRequest->ToType == GT_USER
					|| pChatSubmitRequest->ToType == GT_CHAT_CHANNEL
					|| pChatSubmitRequest->ToType == GT_CHAT_ALLIANCE )
					return PR_USER_FORBID;
				}
			}
		}
	}
	//	add by aaron 20121114
	if(pChatSubmitRequest->ToType != GT_USER
	&& pChatSubmitRequest->ToType != GT_ALL
	&& pChatSubmitRequest->ToType != GT_CHAT_CHANNEL
	&& pChatSubmitRequest->ToType != GT_CHAT_ALLIANCE
	&& pChatSubmitRequest->ToType != GT_NATION
	&& pChatSubmitRequest->ToType != GT_NATIONFIGHT
	&& pChatSubmitRequest->ToType != GT_CHIBI_WAR
	&& pChatSubmitRequest->ToType != GT_NEW_WORLD
	&& pChatSubmitRequest->ToType != GT_NEW_WORLD_BATTLE
	&& pChatSubmitRequest->ToType != GT_ALLIANCE_NEW_BATTLE)
	{
		error_log("[unexpect_to_type][uid=%u,toid=%u]", m_pReceivePacket->UserId, pChatSubmitRequest->ToType);
		return R_ERR_PARAM;
	}
	UserData user;
	if (!m_userManager.GetUser(m_pReceivePacket->UserId, user)) {
		error_log("[get_user_fail][uid=%u]", m_pReceivePacket->UserId);
		return R_ERR_SESSION;
	}
	vector<uint32_t> toUsers;
	ret = m_groupManager.GetGroupUsers(m_pReceivePacket->UserId,
			(GroupType) pChatSubmitRequest->ToType, pChatSubmitRequest->ToId,
			toUsers);
	if (ret != 0) {
		return ret;
	}
	/***add by ralf for ad******/
	if(pChatSubmitRequest->ToType == GT_CHAT_CHANNEL
	|| pChatSubmitRequest->ToType == GT_NATION
	|| pChatSubmitRequest->ToType == GT_CHAT_ALLIANCE
	|| pChatSubmitRequest->ToType == GT_USER
	|| (pChatSubmitRequest->ToType == GT_ALL && pChatSubmitRequest->ToId == PR_USER_FORBID_COLOR))
		OnAdAnalize(m_pReceivePacket->UserId,user.vip,user.lvl,pChatSubmitRequest->Message);
	/**************************/
	CChatPushRequestProtocol chatPushRequest;
	chatPushRequest.FromUserId = m_pReceivePacket->UserId;
	chatPushRequest.FromName = user.Name;
	chatPushRequest.ToType = pChatSubmitRequest->ToType;
	chatPushRequest.ToId = pChatSubmitRequest->ToId;
	chatPushRequest.Message = pChatSubmitRequest->Message;
	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_CHAT_PUSH;
	size_t failCount = 0;
	size_t totalCount = toUsers.size();
	for (vector<uint32_t>::const_iterator itr = toUsers.begin(); itr!= toUsers.end(); itr++) {
		if (*itr == m_pReceivePacket->UserId) {
			totalCount--;
		} else {
			requestPacket.UserId = *itr;
			if (!SendRequest(&requestPacket, &chatPushRequest)) {
				failCount++;
			}
		}
	}
	if (failCount > 0) {
		if (failCount == totalCount) {
			error_log("[chat_push_fail_all][fromuid=%u,totype=%u,toid=%u,usercount=%u,size=%u]",
					m_pReceivePacket->UserId, pChatSubmitRequest->ToType, pChatSubmitRequest->ToId,
					(unsigned)failCount, (unsigned)chatPushRequest.Message.size());
			return PR_PUSH_FAIL;
		} else {
			error_log("[chat_push_fail_all][fromuid=%u,totype=%u,toid=%u,totoluser=%u,fail=%u,size=%u]",
					m_pReceivePacket->UserId, pChatSubmitRequest->ToType, pChatSubmitRequest->ToId,
					(unsigned)totalCount, (unsigned)failCount, (unsigned)chatPushRequest.Message.size());
		}
	}
	CChatSubmitReplyProtocol *pChatSubmitReply = new CChatSubmitReplyProtocol;
	m_pReplyProtocol = pChatSubmitReply;
	pChatSubmitReply->Message = pChatSubmitRequest->Message;

	BUSI_LOG("chat","talk","%u|%u|%u|%s|%s",m_pReceivePacket->UserId,pChatSubmitRequest->ToType,pChatSubmitRequest->ToId,user.name.c_str(),pChatSubmitRequest->Message.c_str());
	if(pChatSubmitRequest->ToType == GT_NATION
	|| pChatSubmitRequest->ToType == GT_USER
	|| pChatSubmitRequest->ToType == GT_CHAT_CHANNEL
	|| pChatSubmitRequest->ToType == GT_CHAT_ALLIANCE )
		DATA_4399_LOG;

	return 0;
}

int CToywarServer::OnChatPush() {
	if (m_pReceivePacket->ProtocolResult != R_SUCCESS) {
		error_log("[chat_push_reply_fail][uid=%u,result=%d]",
				m_pReceivePacket->UserId, (int)m_pReceivePacket->ProtocolResult);
	}

	return 0;
}

int CToywarServer::OnForbidChat() {
	CForbidChatRequestProtocol *forbidChatRequest =
			(CForbidChatRequestProtocol *) m_pReceiveProtocol;
	g_ForbidUserList[forbidChatRequest->ForbidUid]
			= forbidChatRequest->ForbidTs;
	CDataForbidUser forbidUser;
	bool ret = forbidUser.Init(Config::GetValue(CONFIG_FORBID_USER));
	int result = forbidUser.update(forbidChatRequest->ForbidUid,
			forbidChatRequest->ForbidTs);
	if (0 != result) {
		error_log("update forbidts failed uid= %u",forbidChatRequest->ForbidUid);

		return result;
	}

	CForbidChatReplyProtocol *pForbidChatReply = new CForbidChatReplyProtocol;
	m_pReplyProtocol = pForbidChatReply;
	pForbidChatReply->Result = 0;
	pForbidChatReply->Message = "susseful";
	return 0;
}

int CToywarServer::OnAddFightMatch(unsigned groupId) {
	vector<uint32_t> Users;
	GroupData data;
	int ret = m_groupManager.GetGroupData(GT_FIGHT, groupId, data);
	if (ret != 0) {
		return ret;
	}
	int length = data.Users.size();
	int fightnum = 0;
	for (int i = 0; i < length; i++) {
		UserData userdata;
		m_userManager.GetUser(data.Users[i], userdata);
		fightnum += userdata.FightNum ;
	}
	int groupFightNum = fightnum;
//	fatal_log("groupid=%d , fightnum=%d ,jointime = %d ,ismatch=%d",groupId,groupFightNum,Time::GetGlobalTime(),0);
	m_fightmatch.AddWaitMatchGroup(groupId, groupFightNum);
	return 0;
}
void CToywarServer::OnMatch(){
//	map<int,WaitMatchGroup> waitmatchgroup = m_fightmatch.GetWaitGroup() ;
//	if(waitmatchgroup.size()!=0)
//	{
//		for(map<int,WaitMatchGroup>::iterator m1_Iter = waitmatchgroup.begin(); m1_Iter != waitmatchgroup.end( ); m1_Iter++)
//		{
//			fatal_log("groupid=%d , fightnum=%d ,jointime = %d ,ismatch=%d , size =%d",m1_Iter->second.GroupId,m1_Iter->second.FightNum,m1_Iter->second.JoinTime,m1_Iter->second.IsMatched,waitmatchgroup.size());
//		}
//	}
	map<int,int> matchGroup;
	m_fightmatch.MatchAll(matchGroup);
	for(map<int,int>::iterator iter = matchGroup.begin(); iter != matchGroup.end( ); iter++)
	{
		int groupId1 =iter->first;
		int groupId2 =iter->second;
		int groupid = groupId1 > groupId2 ? groupId2:groupId1;
		UserData user;
		GroupData groupdata;
		if (!m_userManager.GetUser(groupid, user)) {
			m_fightmatch.RemoveHaveMatchGroup(groupid);
			error_log("[get_user_fail][groupid=%u]", groupid);
			return ;
		}

		if (m_groupManager.GetGroupData(GT_FIGHT,groupid, groupdata) != 0) {
			m_fightmatch.RemoveHaveMatchGroup(groupid);
			return ;
		}

		CGroupNotifyRequestProtocol groupNotifyRequest;
		groupNotifyRequest.Type = groupdata.Type;
		groupNotifyRequest.Id = groupdata.Id;
		groupNotifyRequest.UserId = user.UserId;
		groupNotifyRequest.UserName = user.Name;
		groupNotifyRequest.Event = GE_START;
		groupNotifyRequest.GroupIdA = groupId1 > groupId2 ? groupId2:groupId1;
		groupNotifyRequest.GroupIdB = groupId1 > groupId2 ? groupId1:groupId2;
		CPacket requestPacket;
		requestPacket.ProtocolType = PROTOCOL_TYPE_GROUP_NOTIFY;
		requestPacket.UserId = user.UserId;
		SendRequest(&requestPacket, &groupNotifyRequest);
		m_fightmatch.RemoveHaveMatchGroup(groupId1);
		m_fightmatch.RemoveHaveMatchGroup(groupId2);

		m_groupManager.AddGroupMatch(groupId1,groupId2);
		map<int,WaitMatchGroup> waitmatchgroup = m_fightmatch.GetWaitGroup() ;
//		error_log("[matchsuccess][groupidA=%u||groupidB=%u||m_waitmatchgroups=%d]", groupId1,groupId2,waitmatchgroup.size());
	}
}


int CToywarServer::GetFightGroupUser(unsigned groupId,vector<uint32_t> &datauser){
	GroupData groupdata1;
	GroupData groupdata2;
	if(m_groupManager.GetGroupData(GT_FIGHT,groupId, groupdata1)==0)
	{
		for (vector<uint32_t>::const_iterator itr = groupdata1.Users.begin(); itr
					!= groupdata1.Users.end(); itr++)
		{
			datauser.push_back(*itr);
		}
	}

	uint32_t matchgroupid = m_groupManager.FindMatchGroupId(groupId);
	if(matchgroupid !=0)
	{
		if(m_groupManager.GetGroupData(GT_FIGHT,matchgroupid, groupdata2)==0)
		{
			for (vector<uint32_t>::const_iterator itr = groupdata2.Users.begin(); itr
						!= groupdata2.Users.end(); itr++)
			{
				datauser.push_back(*itr);
			}
		}
	}
	return 0;
}

int CToywarServer::OnSelectHero()
{
	CAFightHeroRequestProtocol *pAFightHeroRequest = (CAFightHeroRequestProtocol *) m_pReceiveProtocol;
	CAFightHeroReplyProtocol *pAFightHeroReply = new CAFightHeroReplyProtocol;
	m_pReplyProtocol = pAFightHeroReply;

	unsigned gid = GET_ALLIANCE_FIGHT_GROUP_ID(pAFightHeroRequest->groupId, pAFightHeroRequest->allianceFightRoom);
	int releaseHeroId = -1;
	int ret = m_groupManager.SelectAllianceHero(m_pReceivePacket->UserId,
			gid,
			pAFightHeroRequest->heroId,
			pAFightHeroReply->ower,
			releaseHeroId
			);

	//选将不成功，不广播消息
	if (0 != ret)
	{
		return 0;
	}

	GroupData data;
	ret = m_groupManager.GetGroupData(GT_ALLIANCE_FIGHT, gid, data);
	if (ret != 0)
	{
		error_log("[GetGroupData fail][uid=%u,gid=%u,heroId=%u]",m_pReceivePacket->UserId,gid,pAFightHeroRequest->heroId);
		return ret;
	}
	OnAllianceFightGroupEvent(m_pReceivePacket->UserId, data, pAFightHeroRequest->heroId, releaseHeroId);
	BUSI_LOG(GroupNames[pAFightHeroRequest->type],"selectHero","%u|%d",m_pReceivePacket->UserId,pAFightHeroRequest->heroId);
	return 0;
}

int CToywarServer::OnSelectHeroStat()
{
	CAFightHeroStatRequestProtocol *pAFightHeroStatRequest = (CAFightHeroStatRequestProtocol *) m_pReceiveProtocol;
	CAFightHeroStatReplyProtocol *pAFightHeroStatReply = new CAFightHeroStatReplyProtocol;
	m_pReplyProtocol = pAFightHeroStatReply;
	unsigned gid = GET_ALLIANCE_FIGHT_GROUP_ID(pAFightHeroStatRequest->groupId,pAFightHeroStatRequest->allianceFightRoom);
	m_groupManager.GetAllianceHeroStat(gid, pAFightHeroStatReply->heroMap);

	return 0;
}

void CToywarServer::OnAdAnalize(unsigned uid, const string &vip, const string &lvl, const string& msg)
{
	if(!AdAnalize::getFlag())
	{
		//debug_log("ad_error");
		return;
	}
	ChatMsg c;
	c.uid = uid;
	c.vip = vip;
	c.lvl = lvl;
	c.msg = msg;
	c.type = "chat";
	c.srvListen =Config::GetValue("server_listen");
	AdAnalize::getInstance()->sendData(c);
}

int CToywarServer::OnChibiWarAttackSubmit()
{
	CChibiWarAttackRequestProtocol* pRequest = (CChibiWarAttackRequestProtocol*)m_pReceiveProtocol;
	m_pReplyProtocol = NULL;

	GroupData data;
	int ret = m_groupManager.GetGroupData(GT_CHIBI_WAR, 1999999998, data);
	if (ret != 0) {
		return ret;
	}
	CChibiWarAttackReplyProtocol Request;
	Request.redbossblood = pRequest->redbossblood;
	Request.bluebossblood = pRequest->bluebossblood;
	Request.damage = pRequest->damage;
	Request.direction = pRequest->direction;
	Request.finish = pRequest->finish;
	Request.doublehurt = pRequest->doublehurt;

	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_CHIBI_WAR_ATTACK;
	const vector<uint32_t> users = data.Users;
	for (vector<uint32_t>::const_iterator itr = users.begin(); itr != users.end(); itr++) {
		requestPacket.UserId = *itr;
		SendRequest(&requestPacket, &Request);
	}
	BUSI_LOG("chibiwar","attackSubmit","%u|%u|%u|%d|%d",
			pRequest->redbossblood, pRequest->bluebossblood, pRequest->damage, pRequest->direction, pRequest->finish);
	return 0;
}

int CToywarServer::OnChibiWarSkillSubmit()
{
	CChibiWarSkillRequestProtocol* pRequest = (CChibiWarSkillRequestProtocol*)m_pReceiveProtocol;
	CChibiWarSkillReplyProtocol *pReply = new CChibiWarSkillReplyProtocol();
	m_pReplyProtocol = pReply;
	GroupData data;
	int ret = m_groupManager.GetGroupData(GT_CHIBI_WAR, 1999999998, data);
	if (ret != 0) {
		return ret;
	}
	CChibiWarSkillNodefyProtocol Request;
	Request.skill_type = pRequest->skill_type;
	Request.skill = pRequest->skill;
	Request.name = pRequest->name;
	Request.camp = pRequest->camp;

	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_CHIBI_WAR_SKILL_NODEFY;
	const vector<uint32_t> users = data.Users;
	for (vector<uint32_t>::const_iterator itr = users.begin(); itr != users.end(); itr++)
	{
		requestPacket.UserId = *itr;
		SendRequest(&requestPacket, &Request);
	}
	BUSI_LOG("chibiwar","skillSubmit","%u|%d|%d",
			m_pReceivePacket->UserId, pRequest->skill_type, pRequest->skill);
	return 0;
}

int CToywarServer::OnNewWorldBattleSubmit()
{
	CNewWorldBattleRequestProtocol* pRequest = (CNewWorldBattleRequestProtocol*)m_pReceiveProtocol;
	m_pReplyProtocol = NULL;

	GroupData data;
	int ret = m_groupManager.GetGroupData(GT_NEW_WORLD, 1999999998, data);
	if (ret != 0) {
		return ret;
	}
	CNewWorldBattleReplyProtocol Request;
	Request.cid = pRequest->cid;
	Request.kingdom = pRequest->kingdom;
	Request.battle = pRequest->battle;

	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_NEW_WORLD_BATTLE;
	const vector<uint32_t> users = data.Users;
	for (vector<uint32_t>::const_iterator itr = users.begin(); itr != users.end(); itr++) {
		requestPacket.UserId = *itr;
		SendRequest(&requestPacket, &Request);
	}
	BUSI_LOG("newworld","battle","%u|%u|%u",
			pRequest->cid, pRequest->kingdom, pRequest->battle);
	return 0;
}

int CToywarServer::OnNewWorldBattleBattleSubmit()
{
	CNewWorldBattleBattleRequestProtocol* pRequest = (CNewWorldBattleBattleRequestProtocol*)m_pReceiveProtocol;
	m_pReplyProtocol = NULL;

	GroupData data;
	int ret = m_groupManager.GetGroupData(GT_NEW_WORLD_BATTLE, 1999999998, data);
	if (ret != 0) {
		return ret;
	}
	CNewWorldBattleBattleReplyProtocol Request;
	Request.cid = pRequest->cid;
	Request.kingdom = pRequest->kingdom;
	Request.battle = pRequest->battle;

	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_NEW_WORLD_BATTLE_BATTLE;
	const vector<uint32_t> users = data.Users;
	for (vector<uint32_t>::const_iterator itr = users.begin(); itr != users.end(); itr++) {
		requestPacket.UserId = *itr;
		SendRequest(&requestPacket, &Request);
	}
	BUSI_LOG("newworldbattle","battle","%u|%u|%u",
			pRequest->cid, pRequest->kingdom, pRequest->battle);
	return 0;
}

int CToywarServer::OnAllianceHelpNotice()
{
	int ret = 0;
	CCAllianceHelpNoticeRequestProtocol *pRequest = (CCAllianceHelpNoticeRequestProtocol*)m_pReceiveProtocol;
	vector<uint32_t> toUsers;
	ret = m_groupManager.GetAllianceUsers(m_pReceivePacket->UserId,pRequest->ToId,toUsers);
	if (ret){
		return ret;
	}
	Json::Value user_name;
	user_name["name"] = "admin";
	user_name["viplv"] = 0;
	user_name["title"] = 0;
	user_name["gm"] = 0;
	user_name["kingdom"] = 1;
	user_name["vl"] = 0;
	user_name["vt"] = 0;
	user_name["job"] = 0;

	CChatPushRequestProtocol chatPushRequest;
	chatPushRequest.FromUserId = m_pReceivePacket->UserId;
	chatPushRequest.FromName = Json::ToString(user_name);
	chatPushRequest.ToType = GT_CHAT_ALLIANCE;
	chatPushRequest.ToId = pRequest->ToId;
	chatPushRequest.Message = pRequest->Message;
	CPacket requestPacket;
	requestPacket.ProtocolType = PROTOCOL_TYPE_CHAT_PUSH;
	for (vector<uint32_t>::const_iterator itr = toUsers.begin(); itr!= toUsers.end(); itr++) {
		requestPacket.UserId = *itr;
		SendRequest(&requestPacket, &chatPushRequest);
	}
	BUSI_LOG("alliancehelp","help","%u|%u|%s", m_pReceivePacket->UserId, pRequest->ToId, pRequest->Message.c_str());
	return 0;
}

int CToywarServer::GetAllianceNewBattleGroupUser(unsigned groupId,vector<uint32_t> &datauser)
{
	GroupData groupdata1;
	GroupData groupdata2;
	if(m_groupManager.GetGroupData(GT_ALLIANCE_NEW_BATTLE, groupId, groupdata1)==0)
	{
		vector<uint32_t>::const_iterator itr = groupdata1.Users.begin();
		for (; itr != groupdata1.Users.end(); itr++)
		{
			datauser.push_back(*itr);
		}
	}

	uint32_t matchgroupid = m_groupManager.FindMatchGroupId(groupId);
	if(matchgroupid !=0)
	{
		if(m_groupManager.GetGroupData(GT_ALLIANCE_NEW_BATTLE, matchgroupid, groupdata2)==0)
		{
			vector<uint32_t>::const_iterator itr = groupdata2.Users.begin();
			for (; itr != groupdata2.Users.end(); itr++)
			{
				datauser.push_back(*itr);
			}
		}
	}
	return 0;
}

