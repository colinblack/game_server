#include <pthread.h>
#include <time.h>
#include <sys/select.h>
#include <stdarg.h>

#include "ServerInc.h"
#include "BattleServer.h"

uint32_t LogicManager::ServerId = 0;
uint32_t LogicManager::SecOpenTime = 0;
uint32_t LogicManager::GlobalMilliTime = 0;
uint64_t LogicManager::StartMilliTime = 0;
bool LogicManager::IsClosed = false;
bool LogicManager::IsPreClosed = false;
bool LogicManager::NeedReloadConfig = false;
int LogicManager::m_signum = 0;

#define PER_FRAME_TIME 10

LogicManager::LogicManager():m_fd(0),channelId(-1),m_timer(0),m_last_hour_ts(0), m_last_two_hour_ts(0), lastLoopTime(0),pReplyProtocol(NULL),needDelReply(true),dispatcher(ProtoManager::DisCardMessage){}

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
	m_last_two_hour_ts = m_last_hour_ts;
	m_timer = m_last_hour_ts % 60;
	unsigned base_buff = Config::GetIntValue(CONFIG_BASE);
	if(base_buff)
		DataSingletonBase::BASE_BUFF = base_buff;

	BattleServer* pServer = BattleServer::Instance();

	//定时器线程
	CTcpChannel* pTimeChannel = pServer->GetSelfClientChannel();
	pthread_t pid;
	if(pthread_create(&pid,NULL,TimerThread,(void*)pTimeChannel) != 0){
		error_log("start time thread failed,%m");
		return false;
	}
	info_log("time thread start,pid=%u",pid);

	if(!BattleConnect::InitThread()){
		error_log("start BattleConnect thread failed,%m");
		return false;
	}

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
		catch(const std::exception&)
		{
			error_log("DataSingleton Init error!");
			return false;
		}
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
		catch(const std::exception&)
		{
			error_log("MemorySingleton Init error!");
			return false;
		}
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
		catch(const std::exception&)
		{
			error_log("DataSingleton OnInit error!");
			return false;
		}
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
		catch(const std::exception&)
		{
			error_log("MemorySingleton OnInit error!");
			return false;
		}
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
		catch(const std::exception&)
		{
			error_log("BattleSingleton OnInit error!");
			return false;
		}
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
	CFirePacket* packet = new CFirePacket(PROTOCOL_ACCESS_SEND, delmsg);
	packet->ChannelId = channelId;
	packet->fd = fd;
	packet->m_msg = msg;
	return BattleServer::Instance()->AddSend(packet);
}
bool LogicManager::sendMsgBC(unsigned uid, Message* msg)
{
	return sendMsg(uid, msg, false);
}
bool LogicManager::sendMsg(unsigned uid, Message* msg, bool delmsg)
{
	if(CMI->IsNeedConnectByUID(uid))
	{
		CFirePacket* packet = new CFirePacket(PROTOCOL_EVENT_BATTLE_FORWARD, delmsg);
		packet->m_msg = msg;
		packet->fd = uid;
		BattleConnect::AddSend(Config::GetZoneByUID(uid), packet);
		return true;
	}

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
	string msgname = msg->GetTypeName();
	bool flag = sendMsgFD(fd, msg, delmsg);
	if(flag)
		debug_log("[MSGLOG][SEND]uid=%u,fd=%d,name=%s", uid, fd, msgname.c_str());
	else
		error_log("[send error]uid=%u,fd=%d,name=%s", uid, fd, msgname.c_str());
	return flag;
}
bool LogicManager::sendMsgGroup(set<unsigned>& uid, Message* msg, bool delmsg)
{
	if(channelId == -1)
	{
		if(delmsg)
			delete msg;
		return false;
	}

	set<unsigned> *fds = new set<unsigned>, del;
	for(set<unsigned>::iterator it=uid.begin();it!=uid.end();++it)
	{
		unsigned fd = Getfd(*it);
		if(fd == -1)
		{
			del.insert(*it);
			continue;
		}
		fds->insert(fd);
	}
	for(set<unsigned>::iterator it=del.begin();it!=del.end();++it)
		uid.erase(*it);
	if(fds->empty())
	{
		if(delmsg)
			delete msg;
		delete fds;
		return false;
	}

	CFirePacket* packet = new CFirePacket(PROTOCOL_ACCESS_GROUP_SEND, delmsg);
	packet->ChannelId = channelId;
	packet->m_msg = msg;
	packet->group = fds;

	string msgname = msg->GetTypeName();
	bool flag = BattleServer::Instance()->AddSend(packet);
	if(flag)
		debug_log("[MSGLOG][GROUP]name=%s", msgname.c_str());
	else
		error_log("[send error]name=%s", msgname.c_str());
	return flag;
}
bool LogicManager::broadcastMsg(Message* msg)
{
	if(channelId == -1)
	{
		delete msg;
		return false;
	}
	CFirePacket* packet = new CFirePacket(PROTOCOL_ACCESS_BROAD_CAST);
	packet->ChannelId = channelId;
	packet->m_msg = msg;

	string msgname = msg->GetTypeName();
	bool flag =  BattleServer::Instance()->AddSend(packet);
	if(flag)
		debug_log("[MSGLOG][BROADCAST]name=%s", msgname.c_str());
	else
		error_log("[send error]name=%s", msgname.c_str());
	return flag;
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
	case PROTOCOL_EVENT_BATTLE_CONNECT:
		battleProcess(packet);
		break;
	case PROTOCOL_EVENT_BATTLE_FORWARD:
		forwardProcess(packet);
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
		debug_log("[MSGLOG][RECV]kick not login, fd=%u, cmd=%s", packet->fd, packet->m_msg->GetTypeName().c_str());
		sendKickMsg(packet->fd, "not_login");
		return;
	}
	debug_log("[MSGLOG][RECV]uid=%u,fd=%d,name=%s", packet->uid, packet->fd, packet->m_msg->GetTypeName().c_str());

	ret = dispatcher.onMessage(packet->m_msg);

	if(ret != 0){
		error_log("client process failed, uid=%u, ret=%d, msg=%s, cmd=%s", packet->uid, ret, m_errmsg.c_str(), packet->m_msg->GetTypeName().c_str());
		ErrorRet::ErrorRet* reply = new ErrorRet::ErrorRet;
		reply->set_errorret(ret);
		reply->set_errormsg(m_errmsg);
		reply->set_requestmsg(packet->m_msg->GetTypeName());
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
		CFirePacket* rspPacket = new CFirePacket(PROTOCOL_ACCESS_ANSWER, needDelReply);
		rspPacket->fd = packet->fd;
		rspPacket->time = packet->time;
		rspPacket->microTime = packet->microTime;
		rspPacket->ChannelId = packet->ChannelId;
		rspPacket->m_msg = pReplyProtocol;

		string msgname =  pReplyProtocol->GetTypeName();
		if(!BattleServer::Instance()->AddSend(rspPacket))
			error_log("send rsp failed:uid=%u,fd=%d,name=%s", packet->uid, packet->fd, msgname.c_str());
		else
			debug_log("[MSGLOG][SEND]uid=%u,fd=%d,name=%s", packet->uid, packet->fd, msgname.c_str());

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
	debug_log("[MSGLOG][RECV]uid=%u,fd=%d,name=%s", uid, packet->fd, packet->m_msg->GetTypeName().c_str());

	string name;
	unsigned ts = msg->ts();
	if(ts - 300 > Time::GetGlobalTime() || ts + 300 < Time::GetGlobalTime())
		ret =  R_ERR_PARAM;
	if(ret != 0)
		error_log("deliver process failed, ret=%d",ret);

	Common::ReplyPay* reply = new Common::ReplyPay;
	reply->set_ret(ret);
	reply->set_name(name);
	CFirePacket* rspPacket = new CFirePacket(PROTOCOL_DELIVER);
	rspPacket->fd = packet->fd;
	rspPacket->time = packet->time;
	rspPacket->microTime = packet->microTime;
	rspPacket->ChannelId = packet->ChannelId;
	rspPacket->m_msg = reply;

	string msgname = reply->GetTypeName();
	if(!BattleServer::Instance()->AddSend(rspPacket))
		error_log("send rsp failed:uid=%u,fd=%d,name=%s", uid, packet->fd, msgname.c_str());
	else
		debug_log("[MSGLOG][SEND]uid=%u,fd=%d,name=%s", uid, packet->fd, msgname.c_str());

	if(ret == 0)
	{
		unsigned cash = msg->cash();
		if(UMI->IsOnline(uid))
		{
			unsigned index = BaseManager::Instance()->GetIndex(uid);
			DataBase &base = BaseManager::Instance()->m_data->data[index];
			COINS_LOG("[%s][uid=%u,ocash=%u,ncash=%u,chgcash=%d]", "DELIVER", uid, base.cash, base.cash+cash, cash);
			base.cash += cash;
			base.acccharge += cash;

			//@add oulong 20161009 首充
	//		if (base.acccharge >= 100 && base.first_recharge == 0)
	//		{
	//			//base.first_recharge = 1;
	//		}

			BaseManager::Instance()->m_data->MarkChange(index);

			LogicUserManager::Instance()->NotifyRecharge(uid, cash);

			DoDataManagerSave(uid);
		}
		else
		{
			AsynManager::Instance()->Add(uid, e_asyn_cash, cash);
			AsynManager::Instance()->Add(uid, e_asyn_accrecharge, cash);
		}
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
		reply->set_errorret(ret);
		reply->set_errormsg(m_errmsg);
		reply->set_requestmsg(packet->m_msg->GetTypeName());
		pReplyProtocol = reply;
		needDelReply = true;
	}

	if(pReplyProtocol != NULL){
		CFirePacket* rspPacket = new CFirePacket(PROTOCOL_ADMIN, needDelReply);
		rspPacket->fd = packet->fd;
		rspPacket->time = packet->time;
		rspPacket->microTime = packet->microTime;
		rspPacket->ChannelId = packet->ChannelId;
		rspPacket->m_msg = pReplyProtocol;

		if(!BattleServer::Instance()->AddSend(rspPacket))
			error_log("send rsp failed:[%u,%u,%u]",rspPacket->fd,rspPacket->time,rspPacket->microTime);

		pReplyProtocol = NULL;
	}
	needDelReply = true;
}

void LogicManager::botProcess(CFirePacket* packet){
	if(IsPreClosed)
		return;

	m_errmsg.clear();

	int ret = dispatcher.onMessage(packet->m_msg);

	/*if(packet->m_msg->GetTypeName() == "Bot.RequestLogin")
	{
		Bot::ReplyLogin* reply = new Bot::ReplyLogin;
		reply->set_ret(ret);
		pReplyProtocol = reply;
	}*/

	if(pReplyProtocol != NULL){
		CFirePacket* rspPacket = new CFirePacket(PROTOCOL_BOT, needDelReply);
		rspPacket->fd = packet->fd;
		rspPacket->time = packet->time;
		rspPacket->microTime = packet->microTime;
		rspPacket->ChannelId = packet->ChannelId;
		rspPacket->m_msg = pReplyProtocol;

		if(!BattleServer::Instance()->AddSend(rspPacket))
			error_log("send rsp failed:[%u,%u,%u]",rspPacket->fd,rspPacket->time,rspPacket->microTime);

		pReplyProtocol = NULL;
	}
	needDelReply = true;
}

void LogicManager::battleProcess(CFirePacket* packet){
	if(IsPreClosed)
		return;

	int ret = 0;
	m_errmsg.clear();

	ret = dispatcher.onMessage(packet->m_msg);

	if(ret != 0){
		error_log("battle process failed, cmd=%s ret=%d, msg=%s", packet->m_msg->GetTypeName().c_str(), ret, m_errmsg.c_str());
		/*禁止同步接口
		ErrorRet::ErrorRet* reply = new ErrorRet::ErrorRet;
		reply->set_errorret(ret);
		reply->set_errormsg(m_errmsg);
		reply->set_requestmsg(packet->m_msg->GetTypeName());
		pReplyProtocol = reply;
		needDelReply = true;
		*/
	}

	/*禁止同步接口
	if(pReplyProtocol != NULL){
		CFirePacket rspPacket(PROTOCOL_EVENT_BATTLE_CONNECT, needDelReply);
		rspPacket.fd = packet->fd;
		rspPacket.time = packet->time;
		rspPacket.microTime = packet->microTime;
		rspPacket.ChannelId = packet->ChannelId;
		rspPacket.m_msg = pReplyProtocol;

		if(!BattleServer::Instance()->SendData(&rspPacket))
			error_log("send rsp failed:[%u,%u,%u]",rspPacket.fd,rspPacket.time,rspPacket.microTime);

		pReplyProtocol = NULL;
	}
	*/
	pReplyProtocol = NULL;
	needDelReply = true;
}

void LogicManager::forwardProcess(CFirePacket* packet){
	if(IsPreClosed)
		return;

	unsigned uid = packet->fd;
	if(!CMI->IsNeedConnectByUID(uid))
		sendMsg(uid, packet->m_msg, false);
}
void LogicManager::heartProcess(CFirePacket* packet){
	//todo 此处是原来的心跳，应该无用
}

bool LogicManager::sendKickMsg(unsigned fd, string reason)
{
	if(channelId == -1 || fd == -1)
		return false;

	/*
	Common::Kick* m = new Common::Kick;
	m->set_reason(reason);
	sendMsgFD(fd, m);
	*/

	CFirePacket* packet = new CFirePacket(PROTOCOL_ACCESS_LOFFLINE);
	packet->fd = fd;
	packet->ChannelId = channelId;
	return BattleServer::Instance()->AddSend(packet);
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
		//队列离线处理
		LogicQueueManager::Instance()->Offline(uid);
		//删除定时任务管理器中该用户的任务
		//LogicRoutineManager::Instance()->Offline(uid);
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
		if(BattleServer::Instance()->IsChannelClosed(channelId))
			LogicManager::Instance()->ClearUser(false);

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
	BattleConnect::DestoryThread();
}

void LogicManager::RegProto()
{
	//登录
	dispatcher.registerMessageCallback<Common::Login>(ProtoManager::ProcessLogin);
	//读取别人数据
	dispatcher.registerMessageCallback<User::RequestOtherUser>(ProtoManager::ProcessNoReply<User::RequestOtherUser, UserManager>);
	//跨服读取别人数据
	dispatcher.registerMessageCallback<User::RequestOtherUserBC>(ProtoManager::ProcessNoReplyNoUID<User::RequestOtherUserBC, UserManager>);
	//新手
	dispatcher.registerMessageCallback<User::Tutorialstage>(ProtoManager::ProcessNoReply<User::Tutorialstage, UserManager>);
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

	//钻石消耗
	dispatcher.registerMessageCallback<User::CostCashReq>(ProtoManager::Process<User::CostCashReq, User::CostCashResp, LogicUserManager>);
	//体力购买
	dispatcher.registerMessageCallback<User::BuyPowerReq>(ProtoManager::Process<User::BuyPowerReq, User::BuyPowerResp, LogicUserManager>);
	//处理邀请好友链接
	dispatcher.registerMessageCallback<User::InviteActivityUrlReq>(ProtoManager::ProcessNoReply<User::InviteActivityUrlReq, LogicUserManager>);
	//跨服处理邀请好友链接
	dispatcher.registerMessageCallback<User::CSInviteActivityUrlReq>(ProtoManager::ProcessNoReplyNoUID<User::CSInviteActivityUrlReq, LogicUserManager>);
	//领取邀请奖励
	dispatcher.registerMessageCallback<User::GetInviteRewardReq>(ProtoManager::Process<User::GetInviteRewardReq, User::GetInviteRewardResp, LogicUserManager>);
	//领取邀请奖励
	dispatcher.registerMessageCallback<User::GetAddInviteRewardReq>(ProtoManager::Process<User::GetAddInviteRewardReq, User::GetAddInviteRewardResp, LogicUserManager>);
	//获取抽奖奖励
	dispatcher.registerMessageCallback<User::GetDrawRewardReq>(ProtoManager::Process<User::GetDrawRewardReq, User::GetDrawRewardResp, LogicUserManager>);
	//新手引导加经验
	dispatcher.registerMessageCallback<User::NewUserAddExpReq>(ProtoManager::Process<User::NewUserAddExpReq, User::NewUserAddExpResp, LogicUserManager>);

	dispatcher.registerMessageCallback<Common::ShutDown>(ProtoManager::ProcessNoReply<Common::ShutDown, UserManager>);
	//购买材料
	dispatcher.registerMessageCallback<User::BuyMaterialReq>(ProtoManager::Process<User::BuyMaterialReq, User::BuyMaterialResp, LogicPropsManager>);

	//GM
	dispatcher.registerMessageCallback<ProtoGM::GMCmdReq>(ProtoManager::ProcessNoReply<ProtoGM::GMCmdReq, LogicGM>);

	//通知系统
	dispatcher.registerMessageCallback<ProtoNotify::GetNotifyReq>(ProtoManager::Process<ProtoNotify::GetNotifyReq, ProtoNotify::GetNotifyResp, LogicNotifyManager>);

	//通用加速
	dispatcher.registerMessageCallback<User::SpeedUpReq>(ProtoManager::Process<User::SpeedUpReq, User::SpeedUpResp, LogicQueueManager>);

	//英雄购买
	dispatcher.registerMessageCallback<ProtoHero::BuyHeroReq>(ProtoManager::Process<ProtoHero::BuyHeroReq, ProtoHero::BuyHeroResp, LogicHeroManager>);
	//英雄升级
	dispatcher.registerMessageCallback<ProtoHero::UpgradeHeroByCoinReq>(ProtoManager::Process<ProtoHero::UpgradeHeroByCoinReq, ProtoHero::UpgradeHeroByCoinResp, LogicHeroManager>);
	//英雄升星
	dispatcher.registerMessageCallback<ProtoHero::UpGradeHeroStarReq>(ProtoManager::Process<ProtoHero::UpGradeHeroStarReq, ProtoHero::UpGradeHeroStarResp, LogicHeroManager>);
	//设置主将
	dispatcher.registerMessageCallback<ProtoHero::SetHeroReq>(ProtoManager::Process<ProtoHero::SetHeroReq, ProtoHero::SetHeroResp, LogicHeroManager>);
	//技能升级
	dispatcher.registerMessageCallback<ProtoHero::UpGradeHeroSkillReq>(ProtoManager::Process<ProtoHero::UpGradeHeroSkillReq, ProtoHero::UpGradeHeroSkillResp, LogicHeroManager>);
	//购买英雄分享奖励
	dispatcher.registerMessageCallback<ProtoHero::ProtoBuyHeroShareRewardReq>(ProtoManager::Process<ProtoHero::ProtoBuyHeroShareRewardReq, ProtoHero::ProtoBuyHeroShareRewardResp, LogicHeroManager>);
	//图鉴升级
	dispatcher.registerMessageCallback<ProtoHero::ActArchiveChipReq>(ProtoManager::Process<ProtoHero::ActArchiveChipReq, ProtoHero::ActArchiveChipResp, LogicHeroManager>);
	//图鉴奖励
	dispatcher.registerMessageCallback<ProtoHero::ArchiveRewardReq>(ProtoManager::Process<ProtoHero::ArchiveRewardReq, ProtoHero::ArchiveRewardResp, LogicHeroManager>);
	//龙珠激活
	dispatcher.registerMessageCallback<ProtoHero::ProtoActDragonBallReq>(ProtoManager::Process<ProtoHero::ProtoActDragonBallReq, ProtoHero::ProtoActDragonBallResp, LogicHeroManager>);
	//排位赛
	dispatcher.registerMessageCallback<ProtoBattle::ProtoGradeBattleReq>(ProtoManager::Process<ProtoBattle::ProtoGradeBattleReq, ProtoBattle::ProtoGradeBattleResp, LogicBattleManager>);
	//排位赛匹配
	dispatcher.registerMessageCallback<ProtoBattle::ProtoMatchReq>(ProtoManager::Process<ProtoBattle::ProtoMatchReq, ProtoBattle::ProtoMatchResp, LogicBattleManager>);
	//刷新挑战玩家
	dispatcher.registerMessageCallback<ProtoBattle::ProtoRefreshReq>(ProtoManager::Process<ProtoBattle::ProtoRefreshReq, ProtoBattle::ProtoRefreshResp, LogicBattleManager>);
	//挑战随机玩家
	dispatcher.registerMessageCallback<ProtoBattle::ProtoRandomUserReq>(ProtoManager::Process<ProtoBattle::ProtoRandomUserReq, ProtoBattle::ProtoRandomUserResp, LogicBattleManager>);
	//随机玩家复仇
	dispatcher.registerMessageCallback<ProtoBattle::ProtoRevengeReq>(ProtoManager::Process<ProtoBattle::ProtoRevengeReq, ProtoBattle::ProtoRevengeResp, LogicBattleManager>);
	//排位每日奖励
	dispatcher.registerMessageCallback<ProtoBattle::DailyRewardReq>(ProtoManager::Process<ProtoBattle::DailyRewardReq, ProtoBattle::DailRewardResp, LogicBattleManager>);
	//推荐好友
	dispatcher.registerMessageCallback<ProtoFriend::ProtoRecommendUserReq>(ProtoManager::Process<ProtoFriend::ProtoRecommendUserReq, ProtoFriend::ProtoRecommendUserResp, LogicFriendManager>);
	//获取好友信息
	dispatcher.registerMessageCallback<ProtoFriend::ProtoGetFriendsReq>(ProtoManager::ProcessNoReply<ProtoFriend::ProtoGetFriendsReq, LogicFriendManager>);
	//跨服获取好友信息
	dispatcher.registerMessageCallback<ProtoFriend::ProtoCSGetFriendsReq>(ProtoManager::ProcessNoReplyNoUID<ProtoFriend::ProtoCSGetFriendsReq, LogicFriendManager>);
	//加好友
	dispatcher.registerMessageCallback<ProtoFriend::ProtoConcernReq>(ProtoManager::ProcessNoReply<ProtoFriend::ProtoConcernReq, LogicFriendManager>);
	//跨服加好友
	dispatcher.registerMessageCallback<ProtoFriend::ProtoCSConcernReq>(ProtoManager::ProcessNoReplyNoUID<ProtoFriend::ProtoCSConcernReq, LogicFriendManager>);
	//删除好友
	dispatcher.registerMessageCallback<ProtoFriend::ProtoCancelConcernReq>(ProtoManager::ProcessNoReply<ProtoFriend::ProtoCancelConcernReq, LogicFriendManager>);
	//挑战好友
	dispatcher.registerMessageCallback<ProtoBattle::ProtoFriendBattleReq>(ProtoManager::Process<ProtoBattle::ProtoFriendBattleReq, ProtoBattle::ProtoFriendBattleResp, LogicBattleManager>);
	//赠送体力
	dispatcher.registerMessageCallback<ProtoFriend::ProtoDonatePowerReq>(ProtoManager::ProcessNoReply<ProtoFriend::ProtoDonatePowerReq, LogicFriendManager>);
	//跨服赠送体力
	dispatcher.registerMessageCallback<ProtoFriend::ProtoCSDonatePowerReq>(ProtoManager::ProcessNoReplyNoUID<ProtoFriend::ProtoCSDonatePowerReq, LogicFriendManager>);
	//开启武馆
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoOpenMartialClubReq>(ProtoManager::Process<ProtoMartialClub::ProtoOpenMartialClubReq, ProtoMartialClub::ProtoOpenMartialClubResp, LogicMartialClubManager>);
	//获取自己武馆中的英雄
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoGetOwnerClubReq>(ProtoManager::Process<ProtoMartialClub::ProtoGetOwnerClubReq, ProtoMartialClub::ProtoGetOwnerClubResp, LogicMartialClubManager>);
	//获取自己或者别人武馆中英雄信息
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoGetHeroReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoGetHeroReq, LogicMartialClubManager>);
	//跨服获取自己或者别人武馆中的英雄
	//设置武馆中的英雄
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoSetHeroReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoSetHeroReq, LogicMartialClubManager>);
	//跨服设置武馆中的英雄
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSSetHeroReq>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSSetHeroReq, LogicMartialClubManager>);
	//跨服设置武将返回给服务器信息
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSSetHeroToBattleReq>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSSetHeroToBattleReq, LogicMartialClubManager>);
	//获取武馆推荐邀请玩家
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoGetInviteUserReq>(ProtoManager::Process<ProtoMartialClub::ProtoGetInviteUserReq, ProtoMartialClub::ProtoGetInviteUserResp, LogicMartialClubManager>);
	//邀请玩家
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoInviteUserReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoInviteUserReq, LogicMartialClubManager>);
	//跨服邀请玩家
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSInviteUserReq>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSInviteUserReq, LogicMartialClubManager>);
	//获取自己武馆的收益
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoGetIncomeReq>(ProtoManager::Process<ProtoMartialClub::ProtoGetIncomeReq, ProtoMartialClub::ProtoGetIncomeResp, LogicMartialClubManager>);
	//获取兼职武馆收益
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoGetOtherIncomeReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoGetOtherIncomeReq, LogicMartialClubManager>);
	//踢馆
	dispatcher.registerMessageCallback<ProtoBattle::ProtoMartialClubBattleReq>(ProtoManager::ProcessNoReply<ProtoBattle::ProtoMartialClubBattleReq, LogicBattleManager>);
	//跨服踢馆发给battle
	dispatcher.registerMessageCallback<ProtoBattle::ProtoCSMartialClubBattleReq>(ProtoManager::ProcessNoReplyNoUID<ProtoBattle::ProtoCSMartialClubBattleReq, LogicBattleManager>);
	//推荐武馆
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoGetMartialClubReq>(ProtoManager::Process<ProtoMartialClub::ProtoGetMartialClubReq, ProtoMartialClub::ProtoGetMartialClubResp, LogicMartialClubManager>);
	//武馆升级
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoUpdateLevelReq>(ProtoManager::Process<ProtoMartialClub::ProtoUpdateLevelReq, ProtoMartialClub::ProtoUpdateLevelResp, LogicMartialClubManager>);
	//卸载自己武馆英雄
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoDelHeroReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoDelHeroReq, LogicMartialClubManager>);
	//跨服卸载自己武馆英雄
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSDelHeroReq>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSDelHeroReq, LogicMartialClubManager>);
	//卸载兼职武馆英雄
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoDelParttimerReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoDelParttimerReq, LogicMartialClubManager>);
	//跨服卸载兼职武馆英雄
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSDelParttimerReq>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSDelParttimerReq, LogicMartialClubManager>);
	//跨服卸载兼职武馆英雄返给服务器
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSDelParttimerToBattleReq>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSDelParttimerToBattleReq, LogicMartialClubManager>);
	//获取兼职武馆信息
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoGetPartTimeClubReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoGetPartTimeClubReq, LogicMartialClubManager>);
	//跨服获取兼职武馆信息
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSGetPartTimeClubReq>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSGetPartTimeClubReq, LogicMartialClubManager>);
	//跨服更新武馆英雄信息
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoCSMartialHeroInfo>(ProtoManager::ProcessNoReplyNoUID<ProtoMartialClub::ProtoCSMartialHeroInfo, LogicMartialHeroManager>);
	//改名
	dispatcher.registerMessageCallback<ProtoMartialClub::ProtoChangeNameReq>(ProtoManager::ProcessNoReply<ProtoMartialClub::ProtoChangeNameReq, LogicMartialClubManager>);
	//删除通知
	dispatcher.registerMessageCallback<ProtoNotify::PostRemove>(ProtoManager::ProcessNoReply<ProtoNotify::PostRemove, LogicPostManager>);

	//参加比赛
	dispatcher.registerMessageCallback<ProtoChampionship::ProtoJoinInMatchReq>(ProtoManager::Process<ProtoChampionship::ProtoJoinInMatchReq, ProtoChampionship::ProtoJoinInMatchResp, LogicChampionshipManager>);
	//卡牌升级
	dispatcher.registerMessageCallback<ProtoCards::ProtoUpdateCardReq>(ProtoManager::Process<ProtoCards::ProtoUpdateCardReq, ProtoCards::ProtoUpdateCardResp, LogicCardsManager>);
	//卡牌复制
	dispatcher.registerMessageCallback<ProtoCards::ProtoDupCardReq>(ProtoManager::Process<ProtoCards::ProtoDupCardReq, ProtoCards::ProtoDupCardResp, LogicCardsManager>);
	//删除卡牌
	dispatcher.registerMessageCallback<ProtoCards::ProtoDelCardReq>(ProtoManager::Process<ProtoCards::ProtoDelCardReq, ProtoCards::ProtoDelCardResp, LogicCardsManager>);
	//购买卡牌
	dispatcher.registerMessageCallback<ProtoCards::ProtoBuyCardReq>(ProtoManager::Process<ProtoCards::ProtoBuyCardReq, ProtoCards::ProtoBuyCardResp, LogicCardsManager>);

	/**************************** 卡牌战斗******************************/
	//设置阵型
	dispatcher.registerMessageCallback<ProtoBattle::SetFormationReq>(ProtoManager::Process<ProtoBattle::SetFormationReq, ProtoBattle::SetFormationResp, LogicBattleManager>);
	//战斗
	dispatcher.registerMessageCallback<ProtoBattleBase::ProtoBattleReq>(ProtoManager::Process<ProtoBattleBase::ProtoBattleReq, ProtoBattleBase::ProtoBattleResp, LogicBattleManager>);
	//pve战斗
	dispatcher.registerMessageCallback<ProtoBattle::ProtoPveBattleReq>(ProtoManager::Process<ProtoBattle::ProtoPveBattleReq, ProtoBattle::ProtoPveBattleResp, LogicBattleManager>);
	//结束回合
	dispatcher.registerMessageCallback<ProtoBattle::ProtoTurnEndReq>(ProtoManager::Process<ProtoBattle::ProtoTurnEndReq, ProtoBattle::ProtoTurnEndResp, LogicBattleManager>);

}

void LogicManager::RegMemoryManager()
{
	//下面的放在最前，顺序不要变
	m_memoryManager.push_back(ResourceManager::Instance());
	m_memoryManager.push_back(AsynManager::Instance());
	m_memoryManager.push_back(NotifyManager::Instance());
	m_memoryManager.push_back(UserGradeManager::Instance());
	m_memoryManager.push_back(PostManager::Instance());
	m_memoryManager.push_back(DataGameManager::Instance());

	//上面的放在最前，顺序不要变
}

void LogicManager::RegDataManager()
{
	m_dataManager.push_back(BaseManager::Instance());
	m_dataManager.push_back(DataGameActivityManager::Instance());
	m_dataManager.push_back(DataChargeHistoryManager::Instance());
	m_dataManager.push_back(DataItemManager::Instance());
	m_dataManager.push_back(DataHeroManager::Instance());
	m_dataManager.push_back(DataConcernManager::Instance());
	m_dataManager.push_back(DataMartialClubManager::Instance());
	m_dataManager.push_back(DataMartialHeroManager::Instance());
	m_dataManager.push_back(DataInviteManager::Instance());
	m_dataManager.push_back(DataDetachHeroManager::Instance());
	m_dataManager.push_back(DataCardsManager::Instance());
	m_dataManager.push_back(DataUnlockCardsManager::Instance());
}

void LogicManager::RegBattleManager()
{
	m_battleManager.push_back(LogicUserManager::Instance());
	m_battleManager.push_back(LogicNotifyManager::Instance());
	m_battleManager.push_back(LogicPropsManager::Instance());
	m_battleManager.push_back(LogicQueueManager::Instance());
	m_battleManager.push_back(LogicRoutineManager::Instance());
	m_battleManager.push_back(LogicHeroManager::Instance());
	m_battleManager.push_back(LogicBattleManager::Instance());
	m_battleManager.push_back(LogicFriendManager::Instance());
	m_battleManager.push_back(LogicOnhookManager::Instance());
	m_battleManager.push_back(LogicMartialClubManager::Instance());
	m_battleManager.push_back(LogicMartialHeroManager::Instance());
	m_battleManager.push_back(LogicPostManager::Instance());
	m_battleManager.push_back(LogicChampionshipManager::Instance());
	m_battleManager.push_back(LogicCardsManager::Instance());
	m_battleManager.push_back(LogicActionManager::Instance());

	//下面的放在最后，顺序不要变
	m_battleManager.push_back(UserManager::Instance());
	//上面的放在最后，顺序不要变
}

void LogicManager::RegActivityManager()
{
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
}

void LogicManager::CheckHour()
{
	m_timer = 0;

	if(LogicCommonUtil::GetHourByTime(Time::GetGlobalTime()) == 0)
		CheckDay();

	for(vector<ActivitySingletonBase*>::iterator it=m_activityManager.begin();it!=m_activityManager.end();++it)
	{
		try
		{
			if((*it)->IsOn())
				(*it)->OnHour();
		}
		catch(const std::exception&) {}
	}
	//每小时发一次在线挂机道具
	LogicOnhookManager::Instance()->OnhookOnlineProp();
	//在线武馆收益
	LogicMartialClubManager::Instance()->MartialOnlineIncome();

	if(Time::GetGlobalTime()- m_last_two_hour_ts >= 3600*2)
	{
		LogicUserGradeManager::Instance()->UserGradeRank();
		LogicUserGradeManager::Instance()->UserGradeResultRank();
		m_last_two_hour_ts = Time::GetGlobalTime();
	}
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
	//排位赛
	UserGradeManager::Instance()->NewSeason();
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
	case e_Sig_try_clear:
		TryClear();
		break;
	case e_Sig_print_info:
		LogicResourceManager::Instance()->Print();
		break;
	default:
		break;
	}
	m_signum = 0;
}
