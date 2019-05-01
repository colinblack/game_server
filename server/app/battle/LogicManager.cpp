#include <pthread.h>
#include <time.h>
#include <sys/select.h>
#include <stdarg.h>

#include "LogicManager.h"
#include "BattleServer.h"
#include "ProtoManager.h"

uint32_t LogicManager::ServerId = 0;
uint32_t LogicManager::SecOpenTime = 0;
uint32_t LogicManager::GlobalMilliTime = 0;
uint64_t LogicManager::StartMilliTime = 0;
bool LogicManager::IsClosed = false;
bool LogicManager::IsPreClosed = false;
bool LogicManager::NeedReloadConfig = false;
int LogicManager::m_signum = 0;

#define PER_FRAME_TIME 10

LogicManager::LogicManager():m_fd(0),channelId(-1),m_timer(0),m_last_hour_ts(0),lastLoopTime(0),pReplyProtocol(NULL),needDelReply(true),dispatcher(ProtoManager::DisCardMessage){}

void* TimerThread(void* arg){
	CTcpChannel* pChannel = (CTcpChannel*)arg;
	struct timeval timeOut;
	timeOut.tv_sec = 1;
	timeOut.tv_usec = 0;

	CFirePacket packet(PROTOCOL_EVENT_SECOND_TIMER);
	CStaticBuffer<PACKET_HEADER_SIZE> buf;
	packet.Encode(&buf);

	while(!LogicManager::IsClosed){
		timeOut.tv_sec = 1;
		timeOut.tv_usec = 0;

		if(select(0,NULL,NULL,NULL,&timeOut) == 0 && !LogicManager::IsClosed){
			pChannel->SendData(&buf);
		}
	}

	return NULL;
}
bool LogicManager::Initialize(){
	struct timeval tv;
	gettimeofday(&tv,NULL);
	StartMilliTime = tv.tv_sec * 1000 + tv.tv_usec/1000;
	ServerId = Config::GetIntValue(CONFIG_SRVID);
	SecOpenTime = Config::GetIntValue(CONFIG_OPENTIME);
	m_last_hour_ts = time(NULL);
	m_timer = m_last_hour_ts % 60;

	BattleServer* pServer = BattleServer::Instance();

	//定时器线程
	CTcpChannel* pTimeChannel = pServer->GetSelfClientChannel();
	pthread_t pid;
	if(pthread_create(&pid,NULL,TimerThread,(void*)pTimeChannel) != 0){
		error_log("start time thread failed,%m");
		return false;
	}
	info_log("time thread start,pid=%u",pid);

	if(!ConfigManager::Instance()->Inited())
	{
		error_log("ConfigManager Init error!");
		return false;
	}
	RegProto();
	RegDataManager();
	RegMemoryManager();
	RegBattleManager();
	RegActivityManager();

	int ret = 0;
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		try
		{
			ret = (*it)->Init();
			if(ret)
			{
				error_log("DataSingleton Init error!");
				return false;
			}
		}
		catch(const std::exception&) {}
	}
	for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
	{
		try
		{
			ret = (*it)->Init();
			if(ret)
			{
				error_log("MemorySingleton Init error!");
				return false;
			}
		}
		catch(const std::exception&) {}
	}

	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		try
		{
			ret = (*it)->OnInit();
			if(ret)
			{
				error_log("DataSingleton OnInit error!");
				return false;
			}
		}
		catch(const std::exception&) {}
	}
	for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
	{
		try
		{
			ret = (*it)->OnInit();
			if(ret)
			{
				error_log("MemorySingleton OnInit error!");
				return false;
			}
		}
		catch(const std::exception&) {}
	}
	for(vector<BattleSingleton*>::iterator it=m_battleManager.begin();it!=m_battleManager.end();++it)
	{
		try
		{
			ret = (*it)->OnInit();
			if(ret)
			{
				error_log("BattleSingleton OnInit error!");
				return false;
			}
		}
		catch(const std::exception&) {}
	}
	for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
	{
		try
		{
			(*it)->OnInit();
		}
		catch(const std::exception&) {}
	}

	return true;
}

bool  LogicManager::sendMsgFD(unsigned fd, Message* msg, bool delmsg)
{
	CFirePacket packet(PROTOCOL_ACCESS_SEND, delmsg);
	packet.ChannelId = channelId;
	packet.fd = fd;
	packet.m_msg = msg;
	return BattleServer::Instance()->SendData(&packet);
}
bool LogicManager::sendMsg(unsigned uid,Message* msg, bool delmsg)
{
	if(channelId == -1)
	{
		if(delmsg)
			delete msg;
		return false;
	}
	unsigned fd = Getfd(uid);
	if(fd == -1)
	{
		if(delmsg)
			delete msg;
		return false;
	}
	return sendMsgFD(fd, msg, delmsg);
}
bool LogicManager::sendMsgGroup(set<unsigned>& uid, Message* msg, bool delmsg)
{
	if(channelId == -1)
	{
		if(delmsg)
			delete msg;
		return false;
	}

	set<unsigned> fds;
	for(set<unsigned>::iterator it=uid.begin();it!=uid.end();++it)
	{
		unsigned fd = Getfd(*it);
		if(fd == -1)
			continue;
		fds.insert(fd);
	}
	if(fds.empty())
	{
		if(delmsg)
			delete msg;
		return false;
	}

	CFirePacket packet(PROTOCOL_ACCESS_GROUP_SEND, delmsg);
	packet.ChannelId = channelId;
	packet.m_msg = msg;
	packet.group = &fds;

	return BattleServer::Instance()->SendData(&packet);
}
bool LogicManager::broadcastMsg(Message* msg)
{
	if(channelId == -1)
	{
		delete msg;
		return false;
	}
	CFirePacket packet(PROTOCOL_ACCESS_BROAD_CAST);
	packet.ChannelId = channelId;
	packet.m_msg = msg;

	return BattleServer::Instance()->SendData(&packet);
}
void LogicManager::process(CFirePacket* packet)
{
	if(packet->cmd < PROTOCOL_ACCESS_LOFFLINE){
		channelId = packet->ChannelId;
		m_fd = packet->fd;
	}

	switch(packet->cmd){
	case PROTOCOL_ACCESS_TRANSFER:
		clientProcess(packet);
		break;
	case PROTOCOL_DELIVER:
		deliverProcess(packet);
		break;
	case PROTOCOL_ADMIN:
		adminProcess(packet);
		break;
	case PROTOCOL_ACCESS_HEARBEAT:
		heartProcess(packet);
		break;
	case PROTOCOL_ACCESS_COFFLINE:
		preOffline(packet);
		break;
	case PROTOCOL_BOT:
		botProcess(packet);
		break;
	case PROTOCOL_EVENT_SECOND_TIMER:
		timerProcess(packet);
		break;
	default:
		error_log("unknown cmd:%u",packet->cmd);
		break;
	}
}

void LogicManager::clientProcess(CFirePacket* packet){
	if(IsPreClosed)
		return;

	int ret = 0;
	packet->uid = Getuid(packet->fd);
	m_errmsg.clear();
	if(!IsValidUid(packet->uid) && packet->m_msg->GetTypeName() != "Common.Login")
	{
		info_log("kick not login, fd=%u, cmd=%s", packet->fd, packet->m_msg->GetTypeName().c_str());
		sendKickMsg(packet->fd, "not_login");
		return;
	}

	ret = dispatcher.onMessage(packet->m_msg);

	if(ret != 0){
		error_log("client process failed, uid=%u, ret=%d, msg=%s, cmd=%s", packet->uid, ret, m_errmsg.c_str(), packet->m_msg->GetTypeName().c_str());
		ErrorRet::ErrorRet* reply = new ErrorRet::ErrorRet;
		reply->set_error_ret(ret);
		reply->set_error_msg(m_errmsg);
		reply->set_request_msg(packet->m_msg->GetTypeName());
		pReplyProtocol = reply;
		needDelReply = true;
	}
	else if(IsValidUid(packet->uid))
	{
		unsigned index = BaseManager::Instance()->GetIndex(packet->uid);
		DataBase &base = BaseManager::Instance()->m_data->data[index];
		base.last_active_time = Time::GetGlobalTime();
	}

	if(pReplyProtocol != NULL){
		CFirePacket rspPacket(PROTOCOL_ACCESS_ANSWER, needDelReply);
		rspPacket.fd = packet->fd;
		rspPacket.time = packet->time;
		rspPacket.microTime = packet->microTime;
		rspPacket.ChannelId = packet->ChannelId;
		rspPacket.m_msg = pReplyProtocol;

		if(!BattleServer::Instance()->SendData(&rspPacket))
			error_log("send rsp failed:[%u,%u,%u]",rspPacket.fd,rspPacket.time,rspPacket.microTime);

		pReplyProtocol = NULL;
	}
	needDelReply = true;
}
void LogicManager::deliverProcess(CFirePacket* packet){
	if(IsPreClosed)
		return;

	int ret = 0;
	Common::Pay* msg = (Common::Pay*)packet->m_msg;
	unsigned uid = msg->uid();
	if(!UMI->IsOnline(uid))
		ret =  R_ERR_LOGIC;
	else
	{
		unsigned ts = msg->ts();
		if(ts - 300 > Time::GetGlobalTime() || ts + 300 < Time::GetGlobalTime())
			ret =  R_ERR_PARAM;
	}
	if(ret != 0)
		error_log("deliver process failed, ret=%d",ret);

	Common::ReplyPay* reply = new Common::ReplyPay;
	reply->set_ret(ret);
	CFirePacket rspPacket(PROTOCOL_DELIVER);
	rspPacket.fd = packet->fd;
	rspPacket.time = packet->time;
	rspPacket.microTime = packet->microTime;
	rspPacket.ChannelId = packet->ChannelId;
	rspPacket.m_msg = reply;

	if(!BattleServer::Instance()->SendData(&rspPacket))
		error_log("send rsp failed:[%u,%u,%u]",rspPacket.fd,rspPacket.time,rspPacket.microTime);

	if(ret == 0)
	{
		unsigned cash = msg->cash();
		unsigned index = BaseManager::Instance()->GetIndex(uid);
		DataBase &base = BaseManager::Instance()->m_data->data[index];
		COINS_LOG("[%s][uid=%u,ocash=%u,ncash=%u,chgcash=%d]", "DELIVER", uid, base.cash, base.cash+cash, cash);
		base.cash += cash;
		base.ticket += cash;
		base.acccharge += cash;

		//@add oulong 20161009 首充
		if (base.acccharge >= 100 && base.first_recharge == 0)
		{
			base.first_recharge = 1;
		}

		BaseManager::Instance()->m_data->MarkChange(index);
		GET_RMI(uid).AddPay(cash);

		LogicUserManager::Instance()->NotifyRecharge(uid, cash);

		DoDataManagerSave(uid);
	}
}
void LogicManager::adminProcess(CFirePacket* packet){
	if(IsPreClosed)
		return;

	int ret = 0;
	m_errmsg.clear();

	ret = dispatcher.onMessage(packet->m_msg);

	if(ret != 0){
		error_log("admin process failed, ret=%d, msg=%s",ret, m_errmsg.c_str());
		ErrorRet::ErrorRet* reply = new ErrorRet::ErrorRet;
		reply->set_error_ret(ret);
		reply->set_error_msg(m_errmsg);
		reply->set_request_msg(packet->m_msg->GetTypeName());
		pReplyProtocol = reply;
	}

	if(pReplyProtocol != NULL){
		CFirePacket rspPacket(PROTOCOL_ADMIN);
		rspPacket.fd = packet->fd;
		rspPacket.time = packet->time;
		rspPacket.microTime = packet->microTime;
		rspPacket.ChannelId = packet->ChannelId;
		rspPacket.m_msg = pReplyProtocol;

		if(!BattleServer::Instance()->SendData(&rspPacket))
			error_log("send rsp failed:[%u,%u,%u]",rspPacket.fd,rspPacket.time,rspPacket.microTime);

		pReplyProtocol = NULL;
	}
}
void LogicManager::botProcess(CFirePacket* packet){
	if(IsPreClosed)
		return;

	int ret = dispatcher.onMessage(packet->m_msg);

	if(packet->m_msg->GetTypeName() == "Bot.RequestLogin")
	{
		Bot::ReplyLogin* reply = new Bot::ReplyLogin;
		reply->set_ret(ret);
		pReplyProtocol = reply;
	}

	if(pReplyProtocol != NULL){
		CFirePacket rspPacket(PROTOCOL_BOT);
		rspPacket.fd = packet->fd;
		rspPacket.time = packet->time;
		rspPacket.microTime = packet->microTime;
		rspPacket.ChannelId = packet->ChannelId;
		rspPacket.m_msg = pReplyProtocol;

		if(!BattleServer::Instance()->SendData(&rspPacket))
			error_log("send rsp failed:[%u,%u,%u]",rspPacket.fd,rspPacket.time,rspPacket.microTime);

		pReplyProtocol = NULL;
	}

	m_errmsg.clear();
}

void LogicManager::heartProcess(CFirePacket* packet){
	//todo 此处是原来的心跳，应该无用
}

bool LogicManager::sendKickMsg(unsigned fd, string reason)
{
	if(channelId == -1 || fd == -1)
		return false;

	Common::Kick* m = new Common::Kick;
	m->set_reason(reason);
	sendMsgFD(fd, m);

	CFirePacket packet(PROTOCOL_ACCESS_LOFFLINE);
	packet.fd = fd;
	packet.ChannelId = channelId;
	return BattleServer::Instance()->SendData(&packet);
}
void LogicManager::forceKick(unsigned uid, string reason){
	sendKickMsg(Getfd(uid), reason);
	offline(uid);
	Eraseuid(uid);
}

void LogicManager::offline(unsigned uid)
{
	if(IsValidUid(uid)){
		//todo 此处是下线的逻辑处理
		UserManager::Instance()->UserOffLine(uid);
	}
}

void LogicManager::timerProcess(CFirePacket* packet)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	GlobalMilliTime = tv.tv_sec * 1000 + tv.tv_usec/1000 - StartMilliTime;

	//抛弃挤压消息，避免消息阻塞引起的雪崩
	if(GlobalMilliTime - lastLoopTime < PER_FRAME_TIME){
//		info_log("timer process time out time=%u",GlobalMilliTime - lastLoopTime);
		return;
	}

	if(IsPreClosed){
		static int c = 0;
		++c;
		if(c == 1)
			ClearUser(true);
		else if(c == 4){
			for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
			{
				try
				{
					if((*it)->IsOn())
						(*it)->OnExit();
				}
				catch(const std::exception&) {}
			}
			for(vector<BattleSingleton*>::iterator it=m_battleManager.begin();it!=m_battleManager.end();++it)
			{
				try
				{
					(*it)->OnExit();
				}
				catch(const std::exception&) {}
			}
			for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
			{
				try
				{
					(*it)->OnExit();
				}
				catch(const std::exception&) {}
			}
			for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
			{
				try
				{
					(*it)->OnExit();
				}
				catch(const std::exception&) {}
			}

			for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
			{
				try
				{
					(*it)->Exit();
				}
				catch(const std::exception&) {}
			}
			for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
			{
				try
				{
					(*it)->Exit();
				}
				catch(const std::exception&) {}
			}

			IsClosed = true;
			BattleServer::Instance()->Close();
		}
	}
	else
	{
		if(NeedReloadConfig)
		{
			NeedReloadConfig = false;
			if(ConfigManager::Reload())
			{
				info_log("ConfigManager Reload sucess!");
				OnReload();
			}
			else
				info_log("ConfigManager Reload fail!");
		}
		if(m_signum)
			CheckSig();

		++m_timer;
		unsigned now = Time::GetGlobalTime();
		if(CTime::IsDiffHour(m_last_hour_ts,now))
		{
			m_last_hour_ts = now;
			try
			{
				CheckHour();
			}
			catch(const std::exception& e)
			{
				error_log("err_msg: %s", e.what());
			}
		}
		if(m_timer % 60 == 0)
		{
			try
			{
				CheckMin();
			}
			catch(const std::exception& e)
			{
				error_log("err_msg: %s", e.what());
			}
		}
		for(list<pair<unsigned, unsigned> >::iterator it=m_leaveList.begin(); it!=m_leaveList.end();){
			if(OFFLINE_DELAY + it->first <= now){
				info_log("kick offline, uid=%u", it->second);
				offline(it->second);
				it = m_leaveList.erase(it);
			}
			else
				break;
		}

		for(vector<BattleSingleton*>::iterator it=m_battleManager.begin();it!=m_battleManager.end();++it)
		{
			try
			{
				(*it)->OnTimer1();
			}
			catch(const std::exception&) {}
		}
		for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
		{
			try
			{
				(*it)->OnTimer1();
			}
			catch(const std::exception&) {}
		}
		for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
		{
			try
			{
				(*it)->OnTimer1();
			}
			catch(const std::exception&) {}
		}

		for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
		{
			try
			{
				(*it)->Timer1();
			}
			catch(const std::exception&) {}
		}
		for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
		{
			try
			{
				(*it)->Timer1();
			}
			catch(const std::exception&) {}
		}

		if(m_timer % 3 == 0)
		{
			this->onTimer2();
		}
	}

	gettimeofday(&tv,NULL);
	lastLoopTime = tv.tv_sec * 1000 + tv.tv_usec/1000 - StartMilliTime;
	if(lastLoopTime - GlobalMilliTime > 40)
	{
		info_log("timer run time = %u",lastLoopTime - GlobalMilliTime);
	}
}

void LogicManager::preOffline(CFirePacket* packet)
{
	if(IsPreClosed)
		return;

	if(Getuid(packet->fd) == -1)
		return;

	info_log("kick pre offline, uid=%u, fd=%u", Getuid(packet->fd), packet->fd);
	m_leaveList.push_back(make_pair(Time::GetGlobalTime(), Getuid(packet->fd)));
	Erasefd(packet->fd);
}

int LogicManager::onTimer2()
{
	for(vector<BattleSingleton*>::iterator it=m_battleManager.begin();it!=m_battleManager.end();++it)
	{
		try
		{
			(*it)->OnTimer2();
		}
		catch(const std::exception&) {}
	}
	for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
	{
		try
		{
			(*it)->OnTimer2();
		}
		catch(const std::exception&) {}
	}
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		try
		{
			(*it)->OnTimer2();
		}
		catch(const std::exception&) {}
	}

	for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
	{
		try
		{
			(*it)->Timer2();
		}
		catch(const std::exception&) {}
	}
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		try
		{
			(*it)->Timer2();
		}
		catch(const std::exception&) {}
	}

	return 0;
}

LogicManager::~LogicManager()
{
	for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
	{
		try
		{
			(*it)->CallDestroy();
		}
		catch(const std::exception&) {}
	}
	for(vector<BattleSingleton*>::iterator it=m_battleManager.begin();it!=m_battleManager.end();++it)
	{
		try
		{
			(*it)->CallDestroy();
		}
		catch(const std::exception&) {}
	}
	for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
	{
		try
		{
			(*it)->CallDestroy();
		}
		catch(const std::exception&) {}
	}
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		try
		{
			(*it)->CallDestroy();
		}
		catch(const std::exception&) {}
	}
	ConfigManager::Instance()->Destroy();
}

void LogicManager::RegProto()
{
	//登录
	dispatcher.registerMessageCallback<Common::Login>(ProtoManager::ProcessLogin);
	//新手
	dispatcher.registerMessageCallback<User::Tutorial_stage>(ProtoManager::ProcessNoReply<User::Tutorial_stage, UserManager>);
	//起名
	dispatcher.registerMessageCallback<Common::ChangeName>(ProtoManager::Process<Common::ChangeName, Common::ReplyChangeName, UserManager>);
	/***********GM********************/
	//加钱
	dispatcher.registerMessageCallback<Admin::AddCash>(ProtoManager::ProcessNoUID<Admin::AddCash, Admin::ReplyAddCash, UserManager>);
	//批量加资源或道具
	dispatcher.registerMessageCallback<Admin::AsycAdd>(ProtoManager::ProcessNoUID<Admin::AsycAdd, Admin::AsycAddResp, UserManager>);
	//查询封号
	dispatcher.registerMessageCallback<Admin::RequestForbidTS>(ProtoManager::ProcessNoUID<Admin::RequestForbidTS, Admin::ReplyForbidTS, UserManager>);
	//封号
	dispatcher.registerMessageCallback<Admin::SetForbidTS>(ProtoManager::ProcessNoReplyNoUID<Admin::SetForbidTS, UserManager>);

	//背包购买
	dispatcher.registerMessageCallback<BagLogic::PurchaseBagReq>(ProtoManager::ProcessBagPurchase);
	/********装备商店相关**********/
	//刷新
	dispatcher.registerMessageCallback<EquipShopLogic::RefreshReq>(ProtoManager::Process<EquipShopLogic::RefreshReq, EquipShopLogic::RefreshResp, LogicEquipShopManager>);
	//极品刷新
	dispatcher.registerMessageCallback<EquipShopLogic::SuperRefreshReq>(ProtoManager::Process<EquipShopLogic::SuperRefreshReq, EquipShopLogic::SuperRefreshResp, LogicEquipShopManager>);
	//秒cd
	dispatcher.registerMessageCallback<EquipShopLogic::CutRefreshReq>(ProtoManager::Process<EquipShopLogic::CutRefreshReq, EquipShopLogic::CutRefreshResp, LogicEquipShopManager>);
	//装备购买
	dispatcher.registerMessageCallback<EquipShopLogic::PurchaseEquipReq>(ProtoManager::Process<EquipShopLogic::PurchaseEquipReq, EquipShopLogic::PurchaseEquipResp, LogicEquipShopManager>);
	/*******资源建筑*********/
	//建筑解锁
	dispatcher.registerMessageCallback<ProtoBuilding::BuildUnlockReq>(ProtoManager::Process<ProtoBuilding::BuildUnlockReq, ProtoBuilding::BuildUnlockResp, LogicBuildManager>);
	//建筑升级
	dispatcher.registerMessageCallback<ProtoBuilding::BuildUpgradeReq>(ProtoManager::Process<ProtoBuilding::BuildUpgradeReq, ProtoBuilding::BuildUpgradeResp, LogicBuildManager>);
	//建筑数据同步
	dispatcher.registerMessageCallback<ProtoBuilding::BuildSyncReq>(ProtoManager::Process<ProtoBuilding::BuildSyncReq, ProtoBuilding::BuildSyncResp, LogicBuildManager>);
	//免费加速
	dispatcher.registerMessageCallback<ProtoBuilding::BuildFreeSpeedReq>(ProtoManager::Process<ProtoBuilding::BuildFreeSpeedReq, ProtoBuilding::BuildSyncResp, LogicBuildManager>);
	//使用金色锤子立即完成
	dispatcher.registerMessageCallback<ProtoBuilding::BuildOverOnceReq>(ProtoManager::Process<ProtoBuilding::BuildOverOnceReq, ProtoBuilding::BuildOverOnceResp, LogicBuildManager>);
	//自动升级
	dispatcher.registerMessageCallback<ProtoBuilding::BuildAutoUpgradeReq>(ProtoManager::Process<ProtoBuilding::BuildAutoUpgradeReq, ProtoBuilding::BuildAutoUpgradeResp, LogicBuildManager>);
	//领取内政功勋
	dispatcher.registerMessageCallback<ProtoBuilding::BuildExploitReq>(ProtoManager::Process<ProtoBuilding::BuildExploitReq, ProtoBuilding::BuildExploitResp, LogicBuildManager>);
	//生产出的资源同步
	dispatcher.registerMessageCallback<ProtoBuilding::BuildResourceSyncReq>(ProtoManager::Process<ProtoBuilding::BuildResourceSyncReq, ProtoBuilding::BuildResourceSyncResq, LogicBuildManager>);
	//建筑队列解锁
	dispatcher.registerMessageCallback<ProtoBuilding::BuildUnlockQueueReq>(ProtoManager::Process<ProtoBuilding::BuildUnlockQueueReq, ProtoBuilding::BuildUnlockQueueResp, LogicBuildManager>);
	//进入副本战斗
	dispatcher.registerMessageCallback<ProtoPass::EnterFightReq>(ProtoManager::ProcessNoReply<ProtoPass::EnterFightReq, LogicNPCPassMgr>);
	//祭司
	dispatcher.registerMessageCallback<ProtoResource::FlamenReq>(ProtoManager::Process<ProtoResource::FlamenReq, ProtoResource::FlamemResp, LogicResourceManager>);
	//黑市cd
	dispatcher.registerMessageCallback<ProtoResource::CutBlackMarketCDReq>(ProtoManager::Process<ProtoResource::CutBlackMarketCDReq, ProtoResource::CutBlackMarketCDResp, LogicResourceManager>);
	//黑市兑换
	dispatcher.registerMessageCallback<ProtoResource::BMarketExchangeReq>(ProtoManager::Process<ProtoResource::BMarketExchangeReq, ProtoResource::BMarketExchangeResp, LogicResourceManager>);

	/*******争霸*********/
	//英雄
	dispatcher.registerMessageCallback<ProtoBattleField::RequestHero>(ProtoManager::Process<ProtoBattleField::RequestHero, ProtoBattleField::HeroState, WorldManager>);
	//移动
	dispatcher.registerMessageCallback<ProtoBattleField::RequestMove>(ProtoManager::Process<ProtoBattleField::RequestMove, ProtoBattleField::ReplyMove, WorldManager>);
	//停止
	dispatcher.registerMessageCallback<ProtoBattleField::RequestStop>(ProtoManager::ProcessNoReply<ProtoBattleField::RequestStop, WorldManager>);
	//国家
	dispatcher.registerMessageCallback<ProtoBattleField::RequestCityKingdom>(ProtoManager::Process<ProtoBattleField::RequestCityKingdom, ProtoBattleField::ReplyCityKingdom, WorldManager>);
	//人数
	dispatcher.registerMessageCallback<ProtoBattleField::RequestCityCount>(ProtoManager::Process<ProtoBattleField::RequestCityCount, ProtoBattleField::ReplyCityCount, WorldManager>);
	//进入城市
	dispatcher.registerMessageCallback<ProtoBattleField::RequestCity>(ProtoManager::ProcessNoNew<ProtoBattleField::RequestCity, ProtoBattleField::ReplyCity, WorldManager>);
	//进入关卡
	dispatcher.registerMessageCallback<ProtoBattleField::RequestGate>(ProtoManager::ProcessNoNew<ProtoBattleField::RequestGate, ProtoBattleField::ReplyCity, WorldManager>);
	//进入单挑
	dispatcher.registerMessageCallback<ProtoBattleField::RequestRush>(ProtoManager::ProcessNoNew<ProtoBattleField::RequestRush, ProtoBattleField::ReplyCity, WorldManager>);
	//进入竞技场
	dispatcher.registerMessageCallback<ProtoBattleField::RequestLadder>(ProtoManager::ProcessNoNew<ProtoBattleField::RequestLadder, ProtoBattleField::ReplyCity, WorldManager>);
	//离开城市
	dispatcher.registerMessageCallback<ProtoBattleField::QuitCity>(ProtoManager::ProcessNoReply<ProtoBattleField::QuitCity, WorldManager>);
	//离开关卡
	dispatcher.registerMessageCallback<ProtoBattleField::QuitGate>(ProtoManager::ProcessNoReply<ProtoBattleField::QuitGate, WorldManager>);
	//离开单挑
	dispatcher.registerMessageCallback<ProtoBattleField::QuitRush>(ProtoManager::ProcessNoReply<ProtoBattleField::QuitRush, WorldManager>);
	//离开竞技场
	dispatcher.registerMessageCallback<ProtoBattleField::QuitLadder>(ProtoManager::ProcessNoReply<ProtoBattleField::QuitLadder, WorldManager>);
	//排队列表
	dispatcher.registerMessageCallback<ProtoBattleField::RequestList>(ProtoManager::Process<ProtoBattleField::RequestList, ProtoBattleField::ReplyList, WorldManager>);
	//城市技能和阵形
	dispatcher.registerMessageCallback<ProtoBattleField::SkillOrShapeCity>(ProtoManager::ProcessNoReply<ProtoBattleField::SkillOrShapeCity, WorldManager>);
	//关卡技能和阵形
	dispatcher.registerMessageCallback<ProtoBattleField::SkillOrShapeGate>(ProtoManager::ProcessNoReply<ProtoBattleField::SkillOrShapeGate, WorldManager>);
	//单挑技能和阵形
	dispatcher.registerMessageCallback<ProtoBattleField::SkillOrShapeRush>(ProtoManager::ProcessNoReply<ProtoBattleField::SkillOrShapeRush, WorldManager>);
	//竞技场技能和阵形
	dispatcher.registerMessageCallback<ProtoBattleField::SkillOrShapeLadder>(ProtoManager::ProcessNoReply<ProtoBattleField::SkillOrShapeLadder, WorldManager>);
	//请求单挑
	dispatcher.registerMessageCallback<ProtoBattleField::StartRush>(ProtoManager::ProcessNoReply<ProtoBattleField::StartRush, WorldManager>);
	//释放幻影
	dispatcher.registerMessageCallback<ProtoBattleField::RequestVision>(ProtoManager::Process<ProtoBattleField::RequestVision, ProtoBattleField::ReplyVision, WorldManager>);
	//结束城市
	dispatcher.registerMessageCallback<ProtoBattleField::ImmediatelyCity>(ProtoManager::ProcessNoReply<ProtoBattleField::ImmediatelyCity, WorldManager>);
	//结束关卡
	dispatcher.registerMessageCallback<ProtoBattleField::ImmediatelyGate>(ProtoManager::ProcessNoReply<ProtoBattleField::ImmediatelyGate, WorldManager>);
	//结束单挑
	dispatcher.registerMessageCallback<ProtoBattleField::ImmediatelyRush>(ProtoManager::ProcessNoReply<ProtoBattleField::ImmediatelyRush, WorldManager>);
	//结束竞技场
	dispatcher.registerMessageCallback<ProtoBattleField::ImmediatelyLadder>(ProtoManager::ProcessNoReply<ProtoBattleField::ImmediatelyLadder, WorldManager>);
	//请求据点功勋任务信息
	dispatcher.registerMessageCallback<ProtoBattleField::RequestRewardInfo>(ProtoManager::Process<ProtoBattleField::RequestRewardInfo, ProtoBattleField::ReplyRewardInfo, WorldManager>);
	//领取据点奖励
	dispatcher.registerMessageCallback<ProtoBattleField::RequestHistoryReward>(ProtoManager::Process<ProtoBattleField::RequestHistoryReward, ProtoBattleField::ReplyHistoryReward, WorldManager>);
	//领取功勋奖励
	dispatcher.registerMessageCallback<ProtoBattleField::RequestKillReward>(ProtoManager::Process<ProtoBattleField::RequestKillReward, ProtoBattleField::ReplyKillReward, WorldManager>);
	//领取任务奖励
	//国家任务个人奖励
	dispatcher.registerMessageCallback<ProtoBattleField::RequestMissionPersonalReward>(ProtoManager::Process<ProtoBattleField::RequestMissionPersonalReward, ProtoBattleField::ReplyMissionPersonalReward, WorldManager>);
	//国家任务的国家奖励
	dispatcher.registerMessageCallback<ProtoBattleField::RequestMissionCountryReward>(ProtoManager::Process<ProtoBattleField::RequestMissionCountryReward, ProtoBattleField::ReplyMissionCountryReward, WorldManager>);
	//自动战斗
	dispatcher.registerMessageCallback<ProtoBattleField::RequestAuto>(ProtoManager::ProcessNoReply<ProtoBattleField::RequestAuto, WorldManager>);
	//随机据点奖励
	dispatcher.registerMessageCallback<ProtoBattleField::RequestBattleReward>(ProtoManager::Process<ProtoBattleField::RequestBattleReward, ProtoBattleField::ReplyBattleReward, WorldManager>);
	//城主信息
	dispatcher.registerMessageCallback<ProtoBattleField::RequestCityMaster>(ProtoManager::Process<ProtoBattleField::RequestCityMaster, ProtoBattleField::ReplyCityMaster, WorldManager>);
	//城主挑战
	dispatcher.registerMessageCallback<ProtoBattleField::StartCityBattle>(ProtoManager::ProcessNoReply<ProtoBattleField::StartCityBattle, WorldManager>);
	//城主奖励
	dispatcher.registerMessageCallback<ProtoBattleField::RequestCityReward>(ProtoManager::Process<ProtoBattleField::RequestCityReward, ProtoBattleField::ReplyCityReward, WorldManager>);
	//剧本战斗
	dispatcher.registerMessageCallback<ProtoBattleField::RequestFight>(ProtoManager::Process<ProtoBattleField::RequestFight, ProtoBattleField::ReplyFight, WorldManager>);
	/*******英雄*********/
	//英雄招募
	dispatcher.registerMessageCallback<ProtoHero::RecruitHeroReq>(ProtoManager::Process<ProtoHero::RecruitHeroReq, ProtoHero::RecruitHeroResp, LogicHeroManager>);
	//英雄解雇
	dispatcher.registerMessageCallback<ProtoHero::FireHeroReq>(ProtoManager::Process<ProtoHero::FireHeroReq, ProtoHero::FireHeroResp, LogicHeroManager>);
	//穿装备
	dispatcher.registerMessageCallback<ProtoHero::DressEquipReq>(ProtoManager::Process<ProtoHero::DressEquipReq, ProtoHero::DressEquipResp, LogicHeroManager>);
	//脱装备
	dispatcher.registerMessageCallback<ProtoHero::UnDressEquipReq>(ProtoManager::Process<ProtoHero::UnDressEquipReq, ProtoHero::UnDressEquipResp, LogicHeroManager>);
	//一键装备
	dispatcher.registerMessageCallback<ProtoHero::OneKeyDressReq>(ProtoManager::Process<ProtoHero::OneKeyDressReq, ProtoHero::OneKeyDressResp, LogicHeroManager>);
	//互换装备
	dispatcher.registerMessageCallback<ProtoHero::SwitchDressReq>(ProtoManager::Process<ProtoHero::SwitchDressReq, ProtoHero::SwitchDressResp, LogicHeroManager>);
	//使用募兵令
	dispatcher.registerMessageCallback<ProtoHero::UseRecruitPropReq>(ProtoManager::Process<ProtoHero::UseRecruitPropReq, ProtoHero::UseRecruitPropResp, LogicHeroManager>);
	//同步英雄的士兵数
	dispatcher.registerMessageCallback<ProtoHero::SyncSoldiersReq>(ProtoManager::Process<ProtoHero::SyncSoldiersReq, ProtoHero::SyncSoldiersResp, LogicHeroManager>);
	//装备洗练接口
	dispatcher.registerMessageCallback<ProtoHero::EquipSmeltReq>(ProtoManager::Process<ProtoHero::EquipSmeltReq, ProtoHero::EquipSmeltResp, LogicHeroManager>);
	dispatcher.registerMessageCallback<ProtoHero::EquipSmeltPropReq>(ProtoManager::Process<ProtoHero::EquipSmeltPropReq, ProtoHero::EquipSmeltPropResp, LogicHeroManager>);
	//打开装备洗练窗口
	dispatcher.registerMessageCallback<ProtoHero::OpenSmeltWindowReq>(ProtoManager::Process<ProtoHero::OpenSmeltWindowReq, ProtoHero::OpenSmeltWindowResp, LogicHeroManager>);
	//使用英雄经验道具
	dispatcher.registerMessageCallback<ProtoHero::UseHeroexpPropsReq>(ProtoManager::Process<ProtoHero::UseHeroexpPropsReq, ProtoHero::UseHeroexpPropsResp, LogicHeroManager>);
	//套装合成
	dispatcher.registerMessageCallback<ProtoHero::ComposeSuitReq>(ProtoManager::Process<ProtoHero::ComposeSuitReq, ProtoHero::ComposeSuitResp, LogicHeroManager>);

	/*科技*/
	//科技研究注资
	dispatcher.registerMessageCallback<ProtoScience::ScienceCapitalReq>(ProtoManager::Process<ProtoScience::ScienceCapitalReq, ProtoScience::ScienceCapitalResp, LogicScienceMgr>);
	//科技研究加速
	dispatcher.registerMessageCallback<ProtoScience::ScienceSpeedCdReq>(ProtoManager::Process<ProtoScience::ScienceSpeedCdReq, ProtoScience::ScienceSpeedCdResp, LogicScienceMgr>);

	//装备卖出
	dispatcher.registerMessageCallback<ProtoEquip::SoldEquipReq>(ProtoManager::Process<ProtoEquip::SoldEquipReq, ProtoEquip::SoldEquipResp, LogicEquipmentManager>);
	//打开回购窗口
	dispatcher.registerMessageCallback<ProtoEquip::OpenRepurchaseWindowReq>(ProtoManager::Process<ProtoEquip::OpenRepurchaseWindowReq, ProtoEquip::OpenRepurchaseWindowResp, LogicEquipmentManager>);

	//国战任务触发接口
	dispatcher.registerMessageCallback<ProtoMission::VerfifyMissonReq>(ProtoManager::ProcessNoReply<ProtoMission::VerfifyMissonReq, LogicMissionManager>);
	//世界移动任务触发接口
	dispatcher.registerMessageCallback<ProtoMission::VerifyWorldMoveMissionReq>(ProtoManager::ProcessNoReply<ProtoMission::VerifyWorldMoveMissionReq, LogicMissionManager>);

	//任务奖励领取接口
	dispatcher.registerMessageCallback<ProtoMission::GetMissionRewardReq>(ProtoManager::Process<ProtoMission::GetMissionRewardReq, ProtoMission::GetMissionRewardResp, LogicMissionManager>);

	/*黄钻礼包*/
	//新手礼包
	dispatcher.registerMessageCallback<ProtoYellowVip::GetNewerGiftReq>(ProtoManager::Process<ProtoYellowVip::GetNewerGiftReq, ProtoYellowVip::GetNewerGiftResp, LogicYellowVipManager>);
	//黄钻每日礼包
	dispatcher.registerMessageCallback<ProtoYellowVip::GetDailyGiftReq>(ProtoManager::Process<ProtoYellowVip::GetDailyGiftReq, ProtoYellowVip::GetDailyGiftResp, LogicYellowVipManager>);
	//年费黄钻每日礼包
	dispatcher.registerMessageCallback<ProtoYellowVip::GetYearDailyGiftReq>(ProtoManager::Process<ProtoYellowVip::GetYearDailyGiftReq, ProtoYellowVip::GetYearDailyGiftResp, LogicYellowVipManager>);
	//升级礼包
	dispatcher.registerMessageCallback<ProtoYellowVip::GetLevelGiftReq>(ProtoManager::Process<ProtoYellowVip::GetLevelGiftReq, ProtoYellowVip::GetLevelGiftResp, LogicYellowVipManager>);

	/*空间礼包*/
	//空间每日礼包
	dispatcher.registerMessageCallback<ProtoYellowVip::QQZoneGetDailyGiftReq>(ProtoManager::Process<ProtoYellowVip::QQZoneGetDailyGiftReq, ProtoYellowVip::QQZoneGetDailyGiftResp, LogicYellowVipManager>);
	//空间升级礼包
	dispatcher.registerMessageCallback<ProtoYellowVip::QQZoneGetLevelGiftReq>(ProtoManager::Process<ProtoYellowVip::QQZoneGetLevelGiftReq, ProtoYellowVip::QQZoneGetLevelGiftResp, LogicYellowVipManager>);

	//兵器
	//兵器解锁
	dispatcher.registerMessageCallback<ProtoWeapon::WeaponUnlockReq>(ProtoManager::Process<ProtoWeapon::WeaponUnlockReq, ProtoWeapon::WeaponUnlockResp, LogicWeaponsMgr>);
	//兵器铸造
	dispatcher.registerMessageCallback<ProtoWeapon::WeaponCastReq>(ProtoManager::Process<ProtoWeapon::WeaponCastReq, ProtoWeapon::WeaponCastResp, LogicWeaponsMgr>);

	//钻石消耗
	dispatcher.registerMessageCallback<User::CostCashReq>(ProtoManager::Process<User::CostCashReq, User::CostCashResp, LogicUserManager>);
	//领取首充奖励
	dispatcher.registerMessageCallback<ProtoReward::FirstRechargeReq>(ProtoManager::Process<ProtoReward::FirstRechargeReq, ProtoReward::FirstRechargeResp, LogicUserManager>);
	//整点/后勤奖励
	dispatcher.registerMessageCallback<ProtoReward::IntegralTimeReq>(ProtoManager::Process<ProtoReward::IntegralTimeReq, ProtoReward::IntegralTimeResp, LogicUserManager>);

	//累积登录
	dispatcher.registerMessageCallback<ProtoCumulation::CumulationRewardReq>(ProtoManager::Process<ProtoCumulation::CumulationRewardReq, ProtoCumulation::CumulationRewardResp, LogicCumulationLogicManager>);
	//vip礼包
	dispatcher.registerMessageCallback<ProtoReward::VIPReq>(ProtoManager::Process<ProtoReward::VIPReq, ProtoReward::VIPResp, LogicUserManager>);

	/*政务事件*/
	//打开政务事件窗口
	dispatcher.registerMessageCallback<ProtoGovernAffair::OpenAffairWindowReq>(ProtoManager::Process<ProtoGovernAffair::OpenAffairWindowReq, ProtoGovernAffair::OpenAffairWindowResp, LogicUserManager>);
	//领取政务奖励
	dispatcher.registerMessageCallback<ProtoGovernAffair::GetAffairRewardReq>(ProtoManager::Process<ProtoGovernAffair::GetAffairRewardReq, ProtoGovernAffair::GetAffairRewardResp, LogicUserManager>);
	//民忠兑换
	dispatcher.registerMessageCallback<ProtoGovernAffair::LoyalExchangeReq>(ProtoManager::Process<ProtoGovernAffair::LoyalExchangeReq, ProtoGovernAffair::LoyalExchangeResp, LogicUserManager>);

	/*竞技场*/
	//打开界面
	dispatcher.registerMessageCallback<ProtoPkField::PkFieldReq>(ProtoManager::Process<ProtoPkField::PkFieldReq, ProtoPkField::PkFieldResp, LogicPkFieldMgr>);
	//换一批
	dispatcher.registerMessageCallback<ProtoPkField::RefreshRivalReq>(ProtoManager::Process<ProtoPkField::RefreshRivalReq, ProtoPkField::RefreshRivalResp, LogicPkFieldMgr>);
	//竞技场领奖
	dispatcher.registerMessageCallback<ProtoPkField::PkRewardReq>(ProtoManager::Process<ProtoPkField::PkRewardReq, ProtoPkField::PkRewardResp, LogicPkFieldMgr>);
	//进入竞技场
	dispatcher.registerMessageCallback<ProtoPkField::EnterPkFieldReq>(ProtoManager::Process<ProtoPkField::EnterPkFieldReq, ProtoPkField::EnterPkFieldResp, LogicPkFieldMgr>);
	//竞技场战斗
	dispatcher.registerMessageCallback<ProtoPkField::StartPkReq>(ProtoManager::ProcessNoReply<ProtoPkField::StartPkReq, LogicPkFieldMgr>);
	//@end

	/*广结名士活动*/
	//打开活动窗口
	dispatcher.registerMessageCallback<ProtoNPCActivity::OpenNPCActivityWindowReq>(ProtoManager::Process<ProtoNPCActivity::OpenNPCActivityWindowReq, ProtoNPCActivity::OpenNPCActivityWindowResp, NPCActivity>);
	//领取事件奖励
	dispatcher.registerMessageCallback<ProtoNPCActivity::GetActiveAffairRewardReq>(ProtoManager::Process<ProtoNPCActivity::GetActiveAffairRewardReq, ProtoNPCActivity::GetActiveAffairRewardResp, NPCActivity>);
	//领取活力值奖励
	dispatcher.registerMessageCallback<ProtoNPCActivity::GetActiveValueRewardReq>(ProtoManager::Process<ProtoNPCActivity::GetActiveValueRewardReq, ProtoNPCActivity::GetActiveValueRewardResp, NPCActivity>);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//道具使用协议
	//礼包领取
	//普通礼包
	dispatcher.registerMessageCallback<User::OpenNormalGifgBagReq>(ProtoManager::Process<User::OpenNormalGifgBagReq, User::OpenGifgBagResp, LogicUserManager>);
	//幸运礼包
	dispatcher.registerMessageCallback<User::OpenLuckGifgBagReq>(ProtoManager::Process<User::OpenLuckGifgBagReq, User::OpenGifgBagResp, LogicUserManager>);
	//限时道具
	dispatcher.registerMessageCallback<User::UseTimeLimitPropReq>(ProtoManager::Process<User::UseTimeLimitPropReq, User::UseTimeLimitPropResp, LogicUserManager>);
	//洗练道具
	dispatcher.registerMessageCallback<User::UseUpdateSmeltPropReq>(ProtoManager::Process<User::UseUpdateSmeltPropReq, User::UseUpdateSmeltPropResp, LogicUserManager>);
	dispatcher.registerMessageCallback<User::UseSpecificSmeltPropReq>(ProtoManager::Process<User::UseSpecificSmeltPropReq, User::UseSpecificSmeltPropResp, LogicUserManager>);
	//@end

	//限时商店购买
	dispatcher.registerMessageCallback<ProtoActivity::LimitShopBuyReq>(ProtoManager::Process<ProtoActivity::LimitShopBuyReq, ProtoActivity::LimitShopBuyResp, LimitShop>);
	dispatcher.registerMessageCallback<ProtoActivity::LimitShopUserInfoReq>(ProtoManager::Process<ProtoActivity::LimitShopUserInfoReq, ProtoActivity::LimitShopUserInfoResp, LimitShop>);

	//军职系统
	dispatcher.registerMessageCallback<ProtoOfficial::ChallengeReq>(ProtoManager::Process<ProtoOfficial::ChallengeReq, ProtoOfficial::ChallengeResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::StartChallengeReq>(ProtoManager::ProcessNoReply<ProtoOfficial::StartChallengeReq, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::AppointDeputyReq>(ProtoManager::Process<ProtoOfficial::AppointDeputyReq, ProtoOfficial::AppointDeputyResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::ApplyJoinReq>(ProtoManager::Process<ProtoOfficial::ApplyJoinReq, ProtoOfficial::ApplyJoinResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::ApplyExitReq>(ProtoManager::Process<ProtoOfficial::ApplyExitReq, ProtoOfficial::ApplyExitResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::AgreeJoinReq>(ProtoManager::Process<ProtoOfficial::AgreeJoinReq, ProtoOfficial::AgreeJoinResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::SetNoticeReq>(ProtoManager::ProcessNoReply<ProtoOfficial::SetNoticeReq, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::OfficialInfoReq>(ProtoManager::Process<ProtoOfficial::OfficialInfoReq, ProtoOfficial::OfficialInfoResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::GetSalaryReq>(ProtoManager::Process<ProtoOfficial::GetSalaryReq, ProtoOfficial::GetSalaryResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::GetDepartmentRecordReq>(ProtoManager::Process<ProtoOfficial::GetDepartmentRecordReq, ProtoOfficial::GetDepartmentRecordResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::RefuseJoinReq>(ProtoManager::Process<ProtoOfficial::RefuseJoinReq, ProtoOfficial::RefuseJoinResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::GetPersonnelRecordReq>(ProtoManager::Process<ProtoOfficial::GetPersonnelRecordReq, ProtoOfficial::GetPersonnelRecordResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::GetPrivilegeRecordReq>(ProtoManager::Process<ProtoOfficial::GetPrivilegeRecordReq, ProtoOfficial::GetPrivilegeRecordResp, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::KickOutMemberReq>(ProtoManager::Process<ProtoOfficial::KickOutMemberReq, ProtoOfficial::KickOutMemberResp, LogicOfficialMgr>);
	//官员令
	dispatcher.registerMessageCallback<ProtoOfficial::PublishTokenReq>(ProtoManager::ProcessNoReply<ProtoOfficial::PublishTokenReq, LogicOfficialMgr>);
	dispatcher.registerMessageCallback<ProtoOfficial::RespondTokenReq>(ProtoManager::Process<ProtoOfficial::RespondTokenReq, ProtoOfficial::RespondTokenResp, LogicOfficialMgr>);
	//@end 军职系统

	//小煤窑
	dispatcher.registerMessageCallback<ProtoMine::MineInfoReq>(ProtoManager::Process<ProtoMine::MineInfoReq, ProtoMine::MineInfoResp, LogicMineMgr>);
	dispatcher.registerMessageCallback<ProtoMine::MineNormalOpenReq>(ProtoManager::Process<ProtoMine::MineNormalOpenReq, ProtoMine::MineOpenResp, LogicMineMgr>);
	dispatcher.registerMessageCallback<ProtoMine::MineKingdomOpenReq>(ProtoManager::Process<ProtoMine::MineKingdomOpenReq, ProtoMine::MineOpenResp, LogicMineMgr>);
	dispatcher.registerMessageCallback<ProtoMine::DonateNormalReq>(ProtoManager::Process<ProtoMine::DonateNormalReq, ProtoMine::DonateResp, LogicMineMgr>);
	dispatcher.registerMessageCallback<ProtoMine::DonateKingdomReq>(ProtoManager::Process<ProtoMine::DonateKingdomReq, ProtoMine::DonateResp, LogicMineMgr>);
	dispatcher.registerMessageCallback<ProtoMine::MineKingdomRewardReq>(ProtoManager::Process<ProtoMine::MineKingdomRewardReq, ProtoMine::MineKingdomRewardResp, LogicMineMgr>);
	dispatcher.registerMessageCallback<ProtoMine::MineRecordReq>(ProtoManager::Process<ProtoMine::MineRecordReq, ProtoMine::MineRecordResp, LogicMineMgr>);
	dispatcher.registerMessageCallback<ProtoMine::MineKingdomMinerRewardReq>(ProtoManager::Process<ProtoMine::MineKingdomMinerRewardReq, ProtoMine::MineKingdomMinerRewardResp, LogicMineMgr>);
	//@end 小煤窑

	//充值返现
	dispatcher.registerMessageCallback<ProtoActivity::CashBackInfoReq>(ProtoManager::Process<ProtoActivity::CashBackInfoReq, ProtoActivity::CashBackInfoResp, LogicCashBack>);
	dispatcher.registerMessageCallback<ProtoActivity::CashBackRewardReq>(ProtoManager::Process<ProtoActivity::CashBackRewardReq, ProtoActivity::CashBackRewardResp, LogicCashBack>);
	//@end 充值返现

	//摸金校尉
	dispatcher.registerMessageCallback<ProtoActivity::TouchGoldInfoReq>(ProtoManager::Process<ProtoActivity::TouchGoldInfoReq, ProtoActivity::TouchGoldInfo, LogicTouchGold>);
	dispatcher.registerMessageCallback<ProtoActivity::TouchGoldOnceReq>(ProtoManager::Process<ProtoActivity::TouchGoldOnceReq, ProtoActivity::TouchGoldResp, LogicTouchGold>);
	dispatcher.registerMessageCallback<ProtoActivity::TouchGoldAllReq>(ProtoManager::Process<ProtoActivity::TouchGoldAllReq, ProtoActivity::TouchGoldResp, LogicTouchGold>);
	dispatcher.registerMessageCallback<ProtoActivity::TouchGoldResetReq>(ProtoManager::Process<ProtoActivity::TouchGoldResetReq, ProtoActivity::TouchGoldInfo, LogicTouchGold>);
	dispatcher.registerMessageCallback<ProtoActivity::TouchGoldSwitchReq>(ProtoManager::Process<ProtoActivity::TouchGoldSwitchReq, ProtoActivity::TouchGoldInfo, LogicTouchGold>);
	dispatcher.registerMessageCallback<ProtoActivity::TouchGoldUnlockReq>(ProtoManager::Process<ProtoActivity::TouchGoldUnlockReq, ProtoActivity::TouchGoldResp, LogicTouchGold>);
	//@end 摸金校尉

	//超值钜惠
	dispatcher.registerMessageCallback<ProtoActivity::HugeDiscountInfoReq>(ProtoManager::Process<ProtoActivity::HugeDiscountInfoReq, ProtoActivity::HugeDiscountInfoResp, LogicHugeDiscount>);
	dispatcher.registerMessageCallback<ProtoActivity::HugeDiscountBuyReq>(ProtoManager::Process<ProtoActivity::HugeDiscountBuyReq, ProtoActivity::HugeDiscountBuyResp, LogicHugeDiscount>);
	//@end 超值钜惠

	//阅兵
	dispatcher.registerMessageCallback<ProtoHero::OpenParadeWindowReq>(ProtoManager::Process<ProtoHero::OpenParadeWindowReq, ProtoHero::OpenParadeWindowResp, LogicHeroManager>);
	dispatcher.registerMessageCallback<ProtoHero::ParadeReq>(ProtoManager::Process<ProtoHero::ParadeReq, ProtoHero::ParadeResp, LogicHeroManager>);

	//闯关送钻
	dispatcher.registerMessageCallback<ProtoActivity::PassActivityInfoReq>(ProtoManager::Process<ProtoActivity::PassActivityInfoReq, ProtoActivity::PassActivityInfoResp, LogicPassActivityMgr>);
	dispatcher.registerMessageCallback<ProtoActivity::PassActivityRewardReq>(ProtoManager::Process<ProtoActivity::PassActivityRewardReq, ProtoActivity::PassActivityRewardResp, LogicPassActivityMgr>);
	//@闯关送钻

	//迷雾战
	dispatcher.registerMessageCallback<ProtoFogGate::StartFogGateReq>(ProtoManager::ProcessNoReply<ProtoFogGate::StartFogGateReq, LogicFogGateManager>);

	//每日任务部分
	dispatcher.registerMessageCallback<ProtoDailyMission::RefreshDailyMissionReq>(ProtoManager::Process<ProtoDailyMission::RefreshDailyMissionReq, ProtoDailyMission::RefreshDailyMissionResp, LogicDailyMissionManager>);
	dispatcher.registerMessageCallback<ProtoDailyMission::CashRefreshMissionReq>(ProtoManager::Process<ProtoDailyMission::CashRefreshMissionReq, ProtoDailyMission::CashRefreshMissionResp, LogicDailyMissionManager>);
	dispatcher.registerMessageCallback<ProtoDailyMission::OpenDailyMissionWindowReq>(ProtoManager::Process<ProtoDailyMission::OpenDailyMissionWindowReq, ProtoDailyMission::OpenDailyMissionWindowResp, LogicDailyMissionManager>);
	dispatcher.registerMessageCallback<ProtoDailyMission::GetDailyMissionRewardReq>(ProtoManager::Process<ProtoDailyMission::GetDailyMissionRewardReq, ProtoDailyMission::GetDailyMissionRewardResp, LogicDailyMissionManager>);

	//部件系统
	//部件产出部分
	dispatcher.registerMessageCallback<ProtoComponent::ProduceReq>(ProtoManager::Process<ProtoComponent::ProduceReq, ProtoComponent::ProduceResp, LogicCompProduceManager>);
	dispatcher.registerMessageCallback<ProtoComponent::OneKeyProduceReq>(ProtoManager::Process<ProtoComponent::OneKeyProduceReq, ProtoComponent::OneKeyProduceResp, LogicCompProduceManager>);
	dispatcher.registerMessageCallback<ProtoComponent::CashProduceReq>(ProtoManager::Process<ProtoComponent::CashProduceReq, ProtoComponent::CashProduceResp, LogicCompProduceManager>);
	dispatcher.registerMessageCallback<ProtoComponent::OpenComponentWindowReq>(ProtoManager::Process<ProtoComponent::OpenComponentWindowReq, ProtoComponent::OpenComponentWindowResp, LogicCompProduceManager>);

	//部件实际使用部分
	dispatcher.registerMessageCallback<ProtoHero::LoadCompoReq>(ProtoManager::Process<ProtoHero::LoadCompoReq, ProtoHero::LoadCompoResp, LogicHeroManager>);
	dispatcher.registerMessageCallback<ProtoHero::UnLoadCompoReq>(ProtoManager::Process<ProtoHero::UnLoadCompoReq, ProtoHero::UnLoadCompoResp, LogicHeroManager>);
	dispatcher.registerMessageCallback<ProtoHero::StrengthenCompoReq>(ProtoManager::Process<ProtoHero::StrengthenCompoReq, ProtoHero::StrengthenCompoResp, LogicHeroManager>);
	dispatcher.registerMessageCallback<ProtoHero::OneKeyStrengthenCompoReq>(ProtoManager::Process<ProtoHero::OneKeyStrengthenCompoReq, ProtoHero::OneKeyStrengthenCompoResp, LogicHeroManager>);

	//成就系统
	//成就验证
	dispatcher.registerMessageCallback<ProtoAchievement::VerifyAchievementReq>(ProtoManager::ProcessNoReply<ProtoAchievement::VerifyAchievementReq, LogicAchievementManager>);
	//领取成就奖励
	dispatcher.registerMessageCallback<ProtoAchievement::GetAchievementRewardReq>(ProtoManager::Process<ProtoAchievement::GetAchievementRewardReq, ProtoAchievement::GetAchievementRewardResp, LogicAchievementManager>);

	//@end

	//洗练放送
	dispatcher.registerMessageCallback<ProtoActivity::SmeltInfoReq>(ProtoManager::Process<ProtoActivity::SmeltInfoReq, ProtoActivity::SmeltInfoResp, LogicSmeltActivity>);
	dispatcher.registerMessageCallback<ProtoActivity::SmeltRewardReq>(ProtoManager::Process<ProtoActivity::SmeltRewardReq, ProtoActivity::SmeltRewardResp, LogicSmeltActivity>);

	//僚机兑换
	dispatcher.registerMessageCallback<EquipShopLogic::ExchangeWingmanReq>(ProtoManager::Process<EquipShopLogic::ExchangeWingmanReq, EquipShopLogic::ExchangeWingmanResp, LogicEquipShopManager>);

	//好友系统
	dispatcher.registerMessageCallback<ProtoFriend::OpenFriendWindowReq>(ProtoManager::Process<ProtoFriend::OpenFriendWindowReq, ProtoFriend::OpenFriendWindowResp, LogicFriendManager>);
	dispatcher.registerMessageCallback<ProtoFriend::AddFriendReq>(ProtoManager::Process<ProtoFriend::AddFriendReq, ProtoFriend::AddFriendResp, LogicFriendManager>);
	dispatcher.registerMessageCallback<ProtoFriend::DelFriendReq>(ProtoManager::Process<ProtoFriend::DelFriendReq, ProtoFriend::DelFriendResp, LogicFriendManager>);
	dispatcher.registerMessageCallback<ProtoFriend::SendGiftReq>(ProtoManager::Process<ProtoFriend::SendGiftReq, ProtoFriend::SendGiftResp, LogicFriendManager>);
	dispatcher.registerMessageCallback<ProtoFriend::ReceivePrestigeRewardReq>(ProtoManager::Process<ProtoFriend::ReceivePrestigeRewardReq, ProtoFriend::ReceivePrestigeRewardResp, LogicFriendManager>);

	//通知系统
	dispatcher.registerMessageCallback<ProtoNotify::GetNotifyReq>(ProtoManager::Process<ProtoNotify::GetNotifyReq, ProtoNotify::GetNotifyResp, LogicNotifyManager>);

	//摇骰子活动
	dispatcher.registerMessageCallback<ProtoShakeDice::OpenShakeDiceWindowReq>(ProtoManager::Process<ProtoShakeDice::OpenShakeDiceWindowReq, ProtoShakeDice::OpenShakeDiceWindowResp, LogicShakeDiceActivity>);
	dispatcher.registerMessageCallback<ProtoShakeDice::EnterMapReq>(ProtoManager::Process<ProtoShakeDice::EnterMapReq, ProtoShakeDice::EnterMapResp, LogicShakeDiceActivity>);
	dispatcher.registerMessageCallback<ProtoShakeDice::RollDiceReq>(ProtoManager::Process<ProtoShakeDice::RollDiceReq, ProtoShakeDice::RollDiceResp, LogicShakeDiceActivity>);
	dispatcher.registerMessageCallback<ProtoShakeDice::ResetMapReq>(ProtoManager::Process<ProtoShakeDice::ResetMapReq, ProtoShakeDice::ResetMapResp, LogicShakeDiceActivity>);
	dispatcher.registerMessageCallback<ProtoShakeDice::PositionRewardReq>(ProtoManager::Process<ProtoShakeDice::PositionRewardReq, ProtoShakeDice::PositionRewardResp, LogicShakeDiceActivity>);
	dispatcher.registerMessageCallback<ProtoShakeDice::UnlockMapReq>(ProtoManager::Process<ProtoShakeDice::UnlockMapReq, ProtoShakeDice::UnlockMapResp, LogicShakeDiceActivity>);
	dispatcher.registerMessageCallback<ProtoShakeDice::ReceiveExtraRewardReq>(ProtoManager::Process<ProtoShakeDice::ReceiveExtraRewardReq, ProtoShakeDice::ReceiveExtraRewardResp, LogicShakeDiceActivity>);

	//充点小钱
	dispatcher.registerMessageCallback<ProtoActivity::OpenLittleChargeWindowReq>(ProtoManager::Process<ProtoActivity::OpenLittleChargeWindowReq, ProtoActivity::OpenLittleChargeWindowResp, LogicLittleChargeActivity>);
	dispatcher.registerMessageCallback<ProtoActivity::LittleChargeRewardReq>(ProtoManager::Process<ProtoActivity::LittleChargeRewardReq, ProtoActivity::LittleChargeRewardResp, LogicLittleChargeActivity>);

	//资源副本
	dispatcher.registerMessageCallback<ProtoResourceCopy::OpenGateWindowReq>(ProtoManager::Process<ProtoResourceCopy::OpenGateWindowReq, ProtoResourceCopy::OpenGateWindowResp, LogicResourceCopyManager>);
	dispatcher.registerMessageCallback<ProtoResourceCopy::BuyResourceCopyReq>(ProtoManager::Process<ProtoResourceCopy::BuyResourceCopyReq, ProtoResourceCopy::BuyResourceCopyResp, LogicResourceCopyManager>);

	//剧本战
	dispatcher.registerMessageCallback<ProtoOperaBattle::OpenOperaBattleWindowReq>(ProtoManager::Process<ProtoOperaBattle::OpenOperaBattleWindowReq, ProtoOperaBattle::OpenOperaBattleWindowResp, LogicOperaBattleManager>);
	dispatcher.registerMessageCallback<ProtoOperaBattle::StartOperaBattleReq>(ProtoManager::Process<ProtoOperaBattle::StartOperaBattleReq, ProtoOperaBattle::StartOperaBattleResp, LogicOperaBattleManager>);
	dispatcher.registerMessageCallback<ProtoOperaBattle::EndOperaBattleReq>(ProtoManager::Process<ProtoOperaBattle::EndOperaBattleReq, ProtoOperaBattle::EndOperaBattleResp, LogicOperaBattleManager>);
	dispatcher.registerMessageCallback<ProtoOperaBattle::ReceiveStarRewardReq>(ProtoManager::Process<ProtoOperaBattle::ReceiveStarRewardReq, ProtoOperaBattle::ReceiveStarRewardResp, LogicOperaBattleManager>);

	//杀敌活跃
	dispatcher.registerMessageCallback<ProtoActivity::OpenEnlivenKillWindowReq>(ProtoManager::Process<ProtoActivity::OpenEnlivenKillWindowReq, ProtoActivity::OpenEnlivenKillWindowResp, LogicEnlivenKillActivity>);
	dispatcher.registerMessageCallback<ProtoActivity::ReceiveDailyKillRewardReq>(ProtoManager::Process<ProtoActivity::ReceiveDailyKillRewardReq, ProtoActivity::ReceiveDailyKillRewardResp, LogicEnlivenKillActivity>);

	//机型试炼
	dispatcher.registerMessageCallback<ProtoModelTrial::OpenModelWindowReq>(ProtoManager::Process<ProtoModelTrial::OpenModelWindowReq, ProtoModelTrial::OpenModelWindowResp, LogicModelTrialManager>);
	dispatcher.registerMessageCallback<ProtoModelTrial::BuyFightTimesReq>(ProtoManager::Process<ProtoModelTrial::BuyFightTimesReq, ProtoModelTrial::BuyFightTimesResp, LogicModelTrialManager>);
	dispatcher.registerMessageCallback<ProtoModelTrial::StartTrialGateReq>(ProtoManager::Process<ProtoModelTrial::StartTrialGateReq, ProtoModelTrial::StartTrialGateResp, LogicModelTrialManager>);

	//跨国商人
	dispatcher.registerMessageCallback<ProtoCrossBusiness::BusinessOpenWindowReq>(ProtoManager::Process<ProtoCrossBusiness::BusinessOpenWindowReq, ProtoCrossBusiness::BusinessOpenWindowResp, LogicCrossBusinessManager>);
	dispatcher.registerMessageCallback<ProtoCrossBusiness::BusinessRefreshReq>(ProtoManager::Process<ProtoCrossBusiness::BusinessRefreshReq, ProtoCrossBusiness::BusinessRefreshResp, LogicCrossBusinessManager>);
	dispatcher.registerMessageCallback<ProtoCrossBusiness::BusinessPurchaseReq>(ProtoManager::Process<ProtoCrossBusiness::BusinessPurchaseReq, ProtoCrossBusiness::BusinessPurchaseResp, LogicCrossBusinessManager>);

	//偷袭珍珠港
	dispatcher.registerMessageCallback<ProtoAttackHarbor::OpenAttackWindowReq>(ProtoManager::Process<ProtoAttackHarbor::OpenAttackWindowReq, ProtoAttackHarbor::OpenAttackWindowResp, LogicAttackHarborManager>);
	dispatcher.registerMessageCallback<ProtoAttackHarbor::RecieveCountryRewardReq>(ProtoManager::Process<ProtoAttackHarbor::RecieveCountryRewardReq, ProtoAttackHarbor::RecieveCountryRewardResp, LogicAttackHarborManager>);

	//部件售卖活动
	dispatcher.registerMessageCallback<ProtoActivity::OpenSellComponentWindowReq>(ProtoManager::Process<ProtoActivity::OpenSellComponentWindowReq, ProtoActivity::OpenSellComponentWindowResp, LogicSellComponentActivity>);
	dispatcher.registerMessageCallback<ProtoActivity::BuyComponentReq>(ProtoManager::Process<ProtoActivity::BuyComponentReq, ProtoActivity::BuyComponentResp, LogicSellComponentActivity>);

	//@end

	dispatcher.registerMessageCallback<Bot::RequestLogin>(ProtoManager::ProcessNoReplyNoUID<Bot::RequestLogin, UserManager>);
	dispatcher.registerMessageCallback<Bot::RequestLogout>(ProtoManager::ProcessNoReplyNoUID<Bot::RequestLogout, UserManager>);
	dispatcher.registerMessageCallback<Bot::RequestMove>(ProtoManager::ProcessNoReplyNoUID<Bot::RequestMove, WorldManager>);
	dispatcher.registerMessageCallback<Bot::RequestCity>(ProtoManager::ProcessNoReplyNoUID<Bot::RequestCity, WorldManager>);

	dispatcher.registerMessageCallback<Common::ShutDown>(ProtoManager::ProcessNoReply<Common::ShutDown, UserManager>);
}

void LogicManager::RegMemoryManager()
{
	//下面这3个放在最前，顺序不要变
	m_memoryManager.push_back(ResourceManager::Instance());
	m_memoryManager.push_back(HeroPropertyManager::Instance());
	m_memoryManager.push_back(BattleFieldManager::Instance());
	//上面这3个放在最前，顺序不要变
	m_memoryManager.push_back(AsynManager::Instance());
	m_memoryManager.push_back(LadderManager::Instance());
	m_memoryManager.push_back(OfficialManager::Instance());
	m_memoryManager.push_back(MineManager::Instance());
	m_memoryManager.push_back(NotifyManager::Instance());
	m_memoryManager.push_back(MemoryOperaBattleManager::Instance());
	m_memoryManager.push_back(MemoryAttackHarborManager::Instance());
}

void LogicManager::RegDataManager()
{
	m_dataManager.push_back(DataBuildQueue::Instance());
	m_dataManager.push_back(DataBuildingManager::Instance());
	m_dataManager.push_back(EquipmentManager::Instance());
	m_dataManager.push_back(EquipShopManager::Instance());
	m_dataManager.push_back(BaseManager::Instance());
	m_dataManager.push_back(DataNPCPassMgr::Instance());
	m_dataManager.push_back(DataHeroManager::Instance());
	m_dataManager.push_back(DataScienceMgr::Instance());
	m_dataManager.push_back(DataMissionManager::Instance());
	m_dataManager.push_back(DataYellowVipManager::Instance());
	m_dataManager.push_back(DataWeaponMgr::Instance());
	m_dataManager.push_back(DataGemMgr::Instance());
	m_dataManager.push_back(DataCumulationLoginManager::Instance());
	m_dataManager.push_back(DataNPCActivityManager::Instance());
	m_dataManager.push_back(DataLimitShopMgr::Instance());
	m_dataManager.push_back(DataFogGateManager::Instance());
	m_dataManager.push_back(DataCashBackMgr::Instance());
	m_dataManager.push_back(DataDailyMissionManager::Instance());
	m_dataManager.push_back(BattleRewardManager::Instance());
	m_dataManager.push_back(DataTimeLimitPropMgr::Instance());
	m_dataManager.push_back(DataSmeltActivityMgr::Instance());
	m_dataManager.push_back(DataComponentManager::Instance());
	m_dataManager.push_back(DataProduceComponentManager::Instance());
	m_dataManager.push_back(DataAchievementManager::Instance());
	m_dataManager.push_back(DataTouchGoldMgr::Instance());
	m_dataManager.push_back(DataHugeDiscountMgr::Instance());
	m_dataManager.push_back(DataFriendManager::Instance());
	m_dataManager.push_back(DataFriendGiftManager::Instance());
	m_dataManager.push_back(DataShakeDiceManager::Instance());
	m_dataManager.push_back(DataResourceCopyManager::Instance());
	m_dataManager.push_back(DataOperaBattleManager::Instance());
	m_dataManager.push_back(DataModelTrialManager::Instance());
	m_dataManager.push_back(DataCrossBusinessManager::Instance());
	m_dataManager.push_back(DataSellComponentManager::Instance());
}

void LogicManager::RegBattleManager()
{
	m_battleManager.push_back(LogicBuildManager::Instance());
	m_battleManager.push_back(LogicEquipmentManager::Instance());
	m_battleManager.push_back(LogicEquipShopManager::Instance());
	m_battleManager.push_back(LogicHeroManager::Instance());
	m_battleManager.push_back(LogicScienceMgr::Instance());
	m_battleManager.push_back(LogicUserManager::Instance());
	m_battleManager.push_back(LogicMissionManager::Instance());
	m_battleManager.push_back(LogicYellowVipManager::Instance());
	m_battleManager.push_back(LogicWeaponsMgr::Instance());
	m_battleManager.push_back(LogicGemMgr::Instance());
	m_battleManager.push_back(LogicNPCPassMgr::Instance());
	m_battleManager.push_back(LogicCumulationLogicManager::Instance());
	m_battleManager.push_back(LogicPkFieldMgr::Instance());
	m_battleManager.push_back(LogicOfficialMgr::Instance());
	m_battleManager.push_back(LogicFogGateManager::Instance());
	m_battleManager.push_back(LogicMineMgr::Instance());
	m_battleManager.push_back(LogicPassActivityMgr::Instance());
	m_battleManager.push_back(LogicDailyMissionManager::Instance());
	m_battleManager.push_back(LogicTimeLimitPropMgr::Instance());
	m_battleManager.push_back(LogicComponentManager::Instance());
	m_battleManager.push_back(LogicCompProduceManager::Instance());
	m_battleManager.push_back(LogicAchievementManager::Instance());
	m_battleManager.push_back(LogicFriendManager::Instance());
	m_battleManager.push_back(LogicNotifyManager::Instance());
	m_battleManager.push_back(LogicResourceCopyManager::Instance());
	m_battleManager.push_back(LogicOperaBattleManager::Instance());
	m_battleManager.push_back(LogicModelTrialManager::Instance());
	m_battleManager.push_back(LogicCrossBusinessManager::Instance());
	m_battleManager.push_back(LogicAttackHarborManager::Instance());
	m_battleManager.push_back(LogicEliteMilitaryManager::Instance());

	//下面两个放在最后，顺序不要变
	m_battleManager.push_back(WorldManager::Instance());
	m_battleManager.push_back(UserManager::Instance());
	//上面两个放在最后，顺序不要变
}
void LogicManager::RegActivityManager()
{
	m_activityManager.push_back(NPCActivity::Instance());
	m_activityManager.push_back(LimitShop::Instance());
	m_activityManager.push_back(LogicCashBack::Instance());
	m_activityManager.push_back(LogicSmeltActivity::Instance());
	m_activityManager.push_back(LogicTouchGold::Instance());
	m_activityManager.push_back(LogicHugeDiscount::Instance());
	m_activityManager.push_back(LogicShakeDiceActivity::Instance());
	m_activityManager.push_back(LogicLittleChargeActivity::Instance());
	m_activityManager.push_back(LogicEnlivenKillActivity::Instance());
	m_activityManager.push_back(LogicSellComponentActivity::Instance());
}

bool LogicManager::IsDataManagerWorking()
{
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		if((*it)->IsWorking())
			return true;
	}
	return false;
}
bool LogicManager::IsDataManagerFull()
{
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		if((*it)->IsFull())
			return true;
	}
	return false;
}
bool LogicManager::IsDataManagerNeedClear()
{
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		if((*it)->IsNeedClear())
			return true;
	}
	return false;
}
bool LogicManager::IsMemoryManagerNeedClear()
{
	for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
	{
		if((*it)->IsNeedClear())
			return true;
	}
	return false;
}
void LogicManager::DoDataManagerSave(unsigned uid)
{
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		try
		{
			(*it)->DoSave(uid);
		}
		catch(const std::exception&) {}
	}

}
void LogicManager::DoDataManagerClear(unsigned uid)
{
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
	{
		try
		{
			(*it)->DoClear(uid);
		}
		catch(const std::exception&) {}
	}

}
void LogicManager::DoMemoryManagerClear(unsigned uid)
{
	for(vector<DataSingletonBase*>::iterator it=m_memoryManager.begin();it!=m_memoryManager.end();++it)
	{
		try
		{
			(*it)->DoClear(uid);
		}
		catch(const std::exception&) {}
	}
}

void LogicManager::Addfd(unsigned uid, unsigned fd)
{
	m_fdmap[fd] = uid;
	m_uidmap[uid] = fd;
}
void LogicManager::Erasefd(unsigned fd)
{
	if(m_fdmap.count(fd))
	{
		m_uidmap.erase(m_fdmap[fd]);
		m_fdmap.erase(fd);
	}
}
void LogicManager::Eraseuid(unsigned uid)
{
	if(m_uidmap.count(uid))
	{
		m_fdmap.erase(m_uidmap[uid]);
		m_uidmap.erase(uid);
	}
}
unsigned LogicManager::Getfd(unsigned uid)
{
	if(m_uidmap.count(uid))
		return m_uidmap[uid];
	return -1;
}
unsigned LogicManager::Getuid(unsigned fd)
{
	if(m_fdmap.count(fd))
		return m_fdmap[fd];
	return -1;
}

void LogicManager::EraseLeaveList(unsigned uid)
{
	for(list<pair<unsigned, unsigned> >::iterator it = m_leaveList.begin();it != m_leaveList.end();++it)
	{
		if(it->second == uid)
		{
			m_leaveList.erase(it);
			return;
		}
	}
}
void LogicManager::ClearUser(bool send)
{
	vector<unsigned> uids;
	UMI->GetOnlineUsers(uids);

	info_log("kick close %u", uids.size());
	for(vector<unsigned>::iterator it=uids.begin();it!=uids.end();++it)
	{
		if(send)
			sendKickMsg(Getfd(*it), "server_close");
		offline(*it);
	}

	m_fdmap.clear();
	m_uidmap.clear();
	m_leaveList.clear();
	channelId = -1;
	m_fd = -1;
}
unsigned LogicManager::GetOpenDays()
{
	return CTime::GetDayInterval(SecOpenTime, Time::GetGlobalTime());
}
void LogicManager::CheckSave(){
	debug_log("---------------------------");
	debug_log("CheckSave!");
	debug_log("---------------------------");
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
		(*it)->OnCheck();
}
void LogicManager::DataLog(){
	debug_log("---------------------------");
	for(vector<DataSingletonBase*>::iterator it=m_dataManager.begin();it!=m_dataManager.end();++it)
		(*it)->DebugLog();
	debug_log("---------------------------");
}
void LogicManager::TryClear()
{
	debug_log("---------------------------");
	debug_log("%s",IsDataManagerWorking()?"DataManager Working":"DataManager not Working");
	debug_log("%s",IsDataManagerNeedClear()?"DataManager Need Clear":"DataManager not Need Clear");
	vector<unsigned> uids;
	BaseManager::Instance()->TryClear(uids);
	debug_log("clear num: %u",uids.size());
	debug_log("---------------------------");
	debug_log("%s",IsMemoryManagerNeedClear()?"MemoryManager Need Clear":"MemoryManager not Need Clear");
	vector<unsigned> uids1;
	ResourceManager::Instance()->TryClear(uids1);
	debug_log("clear num: %u",uids1.size());
	debug_log("---------------------------");
}

void LogicManager::CheckMin()
{
	info_log("Online:%u",m_fdmap.size());

	User::ServerTime * msg = new User::ServerTime;
	msg->set_ts(now);
	broadcastMsg(msg);

	for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
	{
		try
		{
			if((*it)->IsOn())
				(*it)->OnMin();
		}
		catch(const std::exception&) {}
	}
	LogicAttackHarborManager::Instance()->OnMinute();
	WMI->OnMinute();
}
void LogicManager::CheckHour()
{
	m_timer = 0;

	if(LogicCommonUtil::GetHourByTime(Time::GetGlobalTime()) == 0)
	{
		CheckDay();
		LogicMineMgr::Instance()->OnDay();
	}

	for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
	{
		try
		{
			if((*it)->IsOn())
				(*it)->OnHour();
		}
		catch(const std::exception&) {}
	}
	WMI->OnHour();
	UMI->AddRefresh();

	//竞技场
	LogicPkFieldMgr::Instance()->OnHour();
	//官职系统
	LogicOfficialMgr::Instance()->OnHour();
}
void LogicManager::CheckDay()
{
	for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
	{
		try
		{
			(*it)->CheckDay();
		}
		catch(const std::exception&) {}
	}
	LogicUserManager::Instance()->EveryDayAction();
}
void LogicManager::OnReload()
{
	for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
	{
		try
		{
			(*it)->OnReload();
		}
		catch(const std::exception&) {}
	}
}

void LogicManager::CheckSig(){
	switch(m_signum)
	{
	case e_Sig_Save:
		CheckSave();
		break;
	case e_Sig_data_log:
		DataLog();
		break;
	case e_Sig_battle_log:
		WMI->BattleLog();
		break;
	case e_Sig_try_clear:
		TryClear();
		break;
	case e_Sig_print_info:
		LogicResourceManager::Instance()->Print();
		break;
	case e_Sig_battle_over:
		WMI->BattleOver();
		break;
	default:
		break;
	}
	m_signum = 0;
}
