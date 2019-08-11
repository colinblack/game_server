#include <pthread.h>
#include <time.h>
#include <sys/select.h>
#include <stdarg.h>
#include "BattleInc.h"
#include "ClientManager.h"
#include "BattleServer.h"

uint32_t LogicManager::GlobalTime = time(NULL);
uint32_t LogicManager::ServerId = 0;
uint32_t LogicManager::ProxyId = 68;
uint32_t LogicManager::SecOpenTime = 0;
uint32_t LogicManager::GlobalMilliTime = 0;
uint64_t LogicManager::StartMilliTime = 0;
bool LogicManager::IsClosed = false;
bool LogicManager::IsPreClosed = false;

#define PER_FRAME_TIME 10

void* TimerThread(void* arg) {
	CTcpChannel* pChannel = (CTcpChannel*) arg;
	struct timeval timeOut;
	timeOut.tv_sec = 0;
	timeOut.tv_usec = 50000;
	CFirePacket packet;
	packet.cmd = PROTOCOL_EVENT_SECOND_TIMER;
	CStaticBuffer<FP_SERVER_HEAD_SIZE> buf;
	packet.Encode(&buf);
	while (!LogicManager::IsClosed) {
		timeOut.tv_sec = 0;
		timeOut.tv_usec = 50000;
		if (select(0, NULL, NULL, NULL, &timeOut) == 0 && !LogicManager::IsClosed) {
			pChannel->SendData(&buf);
		}
	}
	return NULL;
}

template<class T, class G, class H>
static int ProcessAndReply(IBuffer* body) {
	int ret = 0;
	T* req = new T;
	CBufferReader reader(body);
	if (!req->decode(reader)) {
		error_log("decode error body=%s", body->ToString().c_str());
		delete req;
		return R_ERROR;
	}

	G* resp = new G;
	try {
		ret = H::Instance()->Process(LogicManager::Instance()->GetUid(), req, resp);
		if (0 != ret) {
			delete resp;
		} else {
			LogicManager::Instance()->SetReply(resp);
		}
	} catch (const std::exception& e) {
		LogicManager::Instance()->SetErrMsg(e.what());
		ret = R_ERROR;
	}
	delete req;
	return ret;
}

template<class T, class H>
static int ProcessNoReply(IBuffer* body) {
	int ret = 0;
	T* req = new T;
	CBufferReader reader(body);
	if (!req->decode(reader)) {
		error_log("decode error body=%s", body->ToString().c_str());
		delete req;
		return R_ERROR;
	}

	try {
		ret = H::Instance()->Process(LogicManager::Instance()->GetUid(), req);
	} catch (const std::exception& e) {
		LogicManager::Instance()->SetErrMsg(e.what());
		ret = R_ERROR;
	}
	delete req;
	return ret;
}

template<class T, class H>
static int MsgSend(const UserCache &cache, uint32_t cmd) {
	T resp;
	int ret = H::Instance()->Sync(cache, cmd, &resp);
	MsgPool::Instance()->Recycle();
	return ret;
}

LogicManager::LogicManager() {
	channel_id_ = 0;
	last_loop_time_ = 0;
	reply_ = NULL;
	curr_fd_ = -1;
	curr_ts_ = 0;
	curr_mts_ = 0;
	err_msg_.clear();
}

bool LogicManager::Init() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	StartMilliTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	ServerId = Config::GetIntValue(CONFIG_SRVID);
	SecOpenTime = Config::GetIntValue(CONFIG_OPENTIME);

	MsgPool::Instance()->Init();

	if (!BusiLogInit()) {
		error_log("busi log init failed");
		return false;
	}
	MissionManager::Instance()->Init();

	if(!CopyManager::Instance()->Init()){
		error_log("copy init failed");
		return false;
	}

	/**
	 if (!StringFilter::Init(Config::GetValue("string_filter_data"))) {
	 error_log("stringfilter init failed");
	 return false;
	 }
	 //人物属性
	 if (!PropertyCfg::getInstance()->init(Config::GetValue(CONFIG_PROPS_PATH))) {
	 error_log("properties init failed");
	 return false;
	 }
	 // 地图属性区域 安全区配置
	 if (!MapAreaManager::getInstance()->init(Config::GetValue(CONFIG_MAP_AREA_INFO))) {
	 error_log("init map area info failed ");
	 return false;
	 }
	 **/
	//地图
	if (!MapManager::Instance()->init()) {
		error_log("map init failed");
		return false;
	}

	if (!SkillControler::Instance()->init()) {
		error_log("skill init failed");
		return false;
	}

	//定时器线程
	CTcpChannel* pTimeChannel = BattleServer::Instance()->GetSelfClientChannel();
	pthread_t pid;
	if (pthread_create(&pid, NULL, TimerThread, (void*) pTimeChannel) != 0) {
		error_log("start time thread failed,%m");
		return false;
	}
	//启动寻路线程
	if (!PathManager::Instance()->init()) {
		error_log("path thread init failed");
		return false;
	}
	//启动异步DB连接
	if (!AsyncDBManager::Instance()->init(BattleServer::Instance())) {
		error_log("async db init failed");
		return false;
	}

	InitLocalData();

	RegProto();

	RegSync();

	return true;
}

bool LogicManager::InitLocalData() {
	TreasureRecordManager::Instance()->Init();
	LevelRewardRecordManager::Instance()->Init();
	return true;
}

bool LogicManager::SaveLocalData() {
	TreasureRecordManager::Instance()->Save();
	LevelRewardRecordManager::Instance()->Save();
	return true;
}

bool LogicManager::SendMsg(uint32_t uid, uint32_t cmd, const Msg *msg) {
	if (msg == NULL) {
		error_log("msg is null rid=%u", uid);
		return false;
	}
	static FdManager* pFdManager = FdManager::Instance();
	static BattleServer* pServer = BattleServer::Instance();

	uint32_t fd = 0;
	uint32_t ts = 0;
	uint32_t mts = 0;
	if (!pFdManager->getFd(uid, fd, ts, mts)) {
		error_log("find user %u failed", uid);
		return false;
	}
	static CFirePacket packet;
	packet.Clean();
	CBufferWriter writer(packet.GetBody());
	if (!msg->encode(writer)) {
		return false;
	}
	packet.ChannelId = channel_id_;
	packet.fd = fd;
	packet.time = ts;
	packet.microTime = mts;
	packet.cmd = PROTOCOL_ACCESS_ANSWER;
	packet.msgId = msg->msgId();
	packet.subCmd = cmd;
	if (!pServer->AddSend(&packet)) {
		error_log("send data error uid=%u cmd=%u msg=%d", uid, cmd, msg->msgId());
		return false;
	}
	debug_log("uid=%u,cmd=%u,mid=%d", uid, cmd, msg->msgId());
	return true;
}

void LogicManager::onExit() {
	IsPreClosed = true;
	SaveLocalData();
}

void LogicManager::Process(CFirePacket* packet) {
	if (packet->cmd < PROTOCOL_EVENT_BEGIN) {
		channel_id_ = packet->ChannelId;
	}
	switch (packet->cmd) {
	case PROTOCOL_ACCESS_TRANSFER:
		ClientProcess(packet);
		break;
	case PROTOCOL_ACCESS_COFFLINE:
		PreOffline(packet);
		break;
	case PROTOCOL_EVENT_OFFLINE:
		OfflineProcess(packet, "normal_kick");
		break;
	case PROTOCOL_EVENT_SECOND_TIMER:
		TimerProcess(packet);
		break;
	default:
		error_log("unknown cmd:%u", packet->cmd);
		break;
	}
}

void LogicManager::ClientProcess(CFirePacket* packet) {
	// TODO Client packet

	curr_fd_ = packet->fd;
	curr_ts_ = packet->time;
	curr_mts_ = packet->microTime;

	uint32_t uid = GetUid();

	int ret = dispatcher_.onMessage(packet->subCmd, packet->GetBody());
	if (0 != ret) {
		error_log("process error cmd=%u ret=%d code=%s", packet->subCmd, ret, err_msg_.c_str());
	}

	DoReply(packet->callback, ret);

	if (reply_ != NULL) {
		delete reply_;
		reply_ = NULL;
	}

	UpdateManager::Instance()->Send(uid);
	SkillManager::Instance()->SendChange(uid);

	MsgPool::Instance()->Recycle();

	DoSync();
}

void LogicManager::OfflineProcess(CFirePacket* packet, const string &reason) {
	//内部踢下线，比如用户在其他地方登录了
	if (packet->cmd == PROTOCOL_EVENT_OFFLINE) {
		CFirePacket rspPacket;
		rspPacket.ChannelId = channel_id_;
		rspPacket.cmd = PROTOCOL_ACCESS_LOFFLINE;
		rspPacket.fd = packet->fd;
		rspPacket.time = packet->time;
		rspPacket.microTime = packet->microTime;
		BattleServer::Instance()->AddSend(&rspPacket);
	}
	static FdManager* pFdManager = FdManager::Instance();
	uint32_t uid = 0;
	if (!pFdManager->getRole(packet->fd, packet->time, packet->microTime, uid)) {
		error_log("unknow connect:[%u,%u,%u]", packet->fd, packet->time, packet->microTime);
		return;
	}
	pFdManager->delMap(packet->fd, packet->time, packet->microTime);

	if (uid != 0) {
		//TODO Human offline logic
		UserManager::Instance()->ActorOffline(uid);
		CacheManager::Instance()->ActorOffline(uid);
		MapManager::Instance()->actorOffline(uid);
	}
	debug_log("role offline uid=%u", uid);
}

void LogicManager::TimerProcess(CFirePacket* packet) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	GlobalMilliTime = tv.tv_sec * 1000 + tv.tv_usec / 1000 - StartMilliTime;
	if (GlobalMilliTime - last_loop_time_ < PER_FRAME_TIME) {
		return;
	}

	MonsterManager::Instance()->onTimer();
	PathManager::Instance()->onTimer();
	MapManager::Instance()->onTimer();
	MapMoveManager::Instance()->onTimer();

	static uint32_t counter = 0;
	static uint32_t lastHour = 25;
	if (counter++ % 20 == 0) {
		Time::UpdateGlobalTime();
		GlobalTime = Time::GetGlobalTime();
		if(Time::GetHour(Time::GetGlobalTime()) != lastHour){
			lastHour = Time::GetHour(Time::GetGlobalTime());
			CopyManager::Instance()->onHour(lastHour);
			ActivityManager::Instance()->onHour(lastHour);
		}
		OnSecondTimer();
		DevilAngelManager::Instance()->onSecondTimer();
		AsyncDBManager::Instance()->onSecondTimer();
		DestoryManager::Instance()->onSecondTimer();
		PropertyManager::Instance()->onSecondTimer();
		ZhanLingManager::Instance()->onSecondTimer();
		CopyManager::Instance()->onSecondTimer();
		BuffControler::Instance()->onSecondTimer();
		NearEnemyManager::Instance()->onSecondTimer();
	}

	gettimeofday(&tv, NULL);
	last_loop_time_ = tv.tv_sec * 1000 + tv.tv_usec / 1000 - StartMilliTime;
	if (last_loop_time_ - GlobalMilliTime > 40) {
		info_log("timer run time = %u", last_loop_time_ - GlobalMilliTime);
	}
}

void LogicManager::PreOffline(CFirePacket* packet) {
	OfflineItem item;
	item.requestTime = GlobalTime;
	item.reqPacket = *packet;
	leave_list_.push_back(item);
}

void LogicManager::OnSecondTimer() {
	if (IsPreClosed) {
		static int c = 0;
		if (++c == 3) {
			IsClosed = true;
			BattleServer::Instance()->Close();
		}
	}
	static uint32_t i = 0;
	if (i++ % 60 == 0) {
		BUSI_ONLINE("%u", MapManager::Instance()->getHumans().size());
	}
	for (list<OfflineItem>::iterator it = leave_list_.begin(); it != leave_list_.end();) {
		if (GlobalTime - it->requestTime >= OFFLINE_DELAY) {
			OfflineProcess(&(it->reqPacket), "normal_offline");
			it = leave_list_.erase(it);
		} else {
			break;
		}
	}

	// 存储当天累计在线时长
//	uint32_t uid = GetUid();
	vector<uint32_t> uids;
	FdManager::Instance()->getAllUid(uids);
	for (vector<uint32_t>::iterator itr = uids.begin(); itr != uids.end(); ++itr) {
		CacheManager::Instance()->ActorOnline(*itr);
	}
}

bool LogicManager::BusiLogInit() {
	if (0 != CLog::create_inst("coin", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("equip", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	return true;
}

bool LogicManager::ForceKick(uint32_t uid, uint32_t rid, const string &reason) {
	FdManager* fdManager = FdManager::Instance();
	uint32_t fd;
	uint32_t time;
	uint32_t microTime;

	if (!fdManager->getFd(uid, fd, time, microTime)) {
		error_log("cannot find [%u-%u]'s fd info", uid, rid);
		return false;
	}

	CFirePacket packet;
	packet.cmd = PROTOCOL_EVENT_OFFLINE;
	packet.fd = fd;
	packet.time = time;
	packet.microTime = microTime;
	OfflineProcess(&packet, reason);

	return true;
}

bool LogicManager::BattleKick(uint32_t fd, uint32_t ts, uint32_t mts) {
	CFirePacket rspPacket;
	rspPacket.ChannelId = channel_id_;
	rspPacket.cmd = PROTOCOL_ACCESS_LOFFLINE;
	rspPacket.fd = fd;
	rspPacket.time = ts;
	rspPacket.microTime = mts;
	BattleServer::Instance()->AddSend(&rspPacket);
	return true;
}

void LogicManager::SetErrMsg(const string &msg) {
	err_msg_ = msg;
}

void LogicManager::SetReply(Msg *reply) {
	reply_ = reply;
}

uint32_t LogicManager::GetUid() {
	uint32_t uid = 0;
	FdManager::Instance()->getRole(curr_fd_, curr_ts_, curr_mts_, uid);
	return uid;
}

bool LogicManager::GetSession(uint32_t uid, int &verifycode, int &relogincode) {
	string skey;
	int ret = Session::GetValue(uid, SESSION_DATA, skey);
	if (0 != ret) {
		return false;
	}
	vector<string> skeyNode;
	CBasic::StringSplitTrim(skey, "|", skeyNode);
	if (skeyNode.size() != 3 || Convert::StringToUInt(skeyNode[0]) != uid) {
		return false;
	}
	relogincode = CTrans::STOI(skeyNode[1]);
	verifycode = CTrans::STOI(skeyNode[2]);
	return true;
}

bool LogicManager::SetSession(uint32_t uid, int &verifycode, int &relogincode) {
	verifycode = Math::GetRandomInt();
	relogincode = Math::GetRandomInt();
	string skey;
	String::Format(skey, "%u|%d|%d", uid, relogincode, verifycode);
	int ret = Session::SetValue(uid, SESSION_DATA, skey);
	if (0 != ret) {
		error_log("set session error uid=%u ret=%d", uid, ret);
		return false;
	}
	return true;
}

void LogicManager::RegProto() {
	dispatcher_.reg(CMD_RPC_LOGIN_QUERY, ProcessAndReply<logins::SQuery, logins::SQueryResult, UserManager>);
	dispatcher_.reg(CMD_RPC_LOGIN_LOGIN, ProcessAndReply<logins::SLogin, logins::SLoginResult, UserManager>);
	dispatcher_.reg(CMD_RPC_GAME_SAVECONFIG, ProcessNoReply<copy::CSSavePlayerConfig, UserManager>);

	dispatcher_.reg(CMD_RPC_LOGIN_LOGINGAME, ProcessNoReply<igameapp::SLoginGame, LogicManager>);
	dispatcher_.reg(CMD_RPC_GAME_QUERYGAMEDATA, ProcessNoReply<logins::SQueryGameData, LogicManager>);
	dispatcher_.reg(CMD_RPC_LOGIN_PING, ProcessAndReply<logins::SLoginPing, logins::SLoginPong, LogicManager>);

	dispatcher_.reg(CMD_RPC_MAP_MOVE, ProcessNoReply<logins::SRoleMove, MapManager>);
	dispatcher_.reg(CMD_RPC_HANG_ENTERHANG, ProcessNoReply<logins::SEnterHang, MapManager>);
	dispatcher_.reg(CMD_RPC_MAP_BACKTOCITY, ProcessNoReply<logins::SBackToCity, MapManager>);
	dispatcher_.reg(CMD_RPC_MAP_JUMP, ProcessNoReply<logins::SMapJump, MapManager>);
	dispatcher_.reg(CMD_RPC_MAP_TRANSFER, ProcessNoReply<logins::SMapTransfer, MapManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_RIDE, ProcessNoReply<logins::SAdvanceRide, MapManager>);

	dispatcher_.reg(CMD_RPC_HANG_BATCHCOMMITFIGHTRESULT, ProcessAndReply<logins::SBatchFightResultReq, logins::SBatchFightResultResp, HangManager>);
	dispatcher_.reg(CMD_RPC_HANG_CHALLENGEBOSS, ProcessNoReply<logins::SHangChallengeBoss, HangManager>);
	dispatcher_.reg(CMD_RPC_HANG_COMMITFIGHTRESULT, ProcessAndReply<logins::SFightResultReq, logins::SBatchFightResultResp, HangManager>);

	dispatcher_.reg(CMD_RPC_SKILL_USESKILL, ProcessNoReply<logins::SUseSkill, SkillManager>);
	dispatcher_.reg(CMD_RPC_SKILL_UPGRADESKILL, ProcessNoReply<logins::SUpgradeSkill, SkillManager>);
	dispatcher_.reg(CMD_RPC_SKILL_ONEKEYUPGRADESKILL, ProcessNoReply<logins::SUpgradeSkillAll, SkillManager>);

	dispatcher_.reg(CMD_RPC_MISSION_REQUEST, ProcessNoReply<logins::SMissionReq, MissionManager>);
	dispatcher_.reg(CMD_RPC_MISSION_COMMIT, ProcessNoReply<logins::SMissionCommit, MissionManager>);

	dispatcher_.reg(CMD_RPC_ADVANCE_ACTIVEADVANCE, ProcessNoReply<logins::SActiveAdvance, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_ADVANCE, ProcessAndReply<logins::SAdvanceReq, logins::SAdvanceResp, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_EATDAN, ProcessNoReply<logins::SAdvanceEatDan, AdvanceManager>);

	dispatcher_.reg(CMD_RPC_SHENQI_ACTIVESHENQIPIECE, ProcessNoReply<logins::SShenQiPiece, ShenQiManager>);
	dispatcher_.reg(CMD_RPC_SHENQI_ACTIVESHENQI, ProcessNoReply<logins::SShenQi, ShenQiManager>);

	dispatcher_.reg(CMD_RPC_EQUIPDECOMPOSE_DECOMPOSE, ProcessNoReply<logins::SBagDecompose, EquipsManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_EQUIP, ProcessNoReply<logins::SEquipEquip, EquipsManager>);
	dispatcher_.reg(CMD_RPC_BAG_OPENBAGGRID, ProcessNoReply<logins::SBagOpenGrid, EquipsManager>);
	dispatcher_.reg(CMD_RPC_BAG_USE, ProcessNoReply<logins::SBagUse, EquipsManager>);
	dispatcher_.reg(CMD_RPC_BAG_MOVEITEM, ProcessNoReply<logins::SBagMoveItem, EquipsManager>);
	dispatcher_.reg(CMD_RPC_BAG_GETOUTITEMS, ProcessNoReply<logins::SBagMoveItemAll, EquipsManager>);
	//宝物
	dispatcher_.reg(CMD_RPC_TREASUREADVANCE_ACTIVE, ProcessNoReply<logins::SActiveTreasure, TreasureManager>);
	dispatcher_.reg(CMD_RPC_TREASUREADVANCE_ADVANCE, ProcessNoReply<logins::STreasureAdvance, TreasureManager>);
	dispatcher_.reg(CMD_RPC_TREASUREADVANCE_EATDAN, ProcessNoReply<logins::STreasureEatDan, TreasureManager>);
	dispatcher_.reg(CMD_RPC_TREASURE_DRAW, ProcessAndReply<logins::STreasureDrawReq, logins::STreasureDrawResp, TreasureManager>);
	dispatcher_.reg(CMD_RPC_TREASURE_GETDRAWHIS, ProcessAndReply<logins::STreasureGetRewardHisReq, logins::STreasureGetRewardHisResp, TreasureManager>);

	// 锻造-精炼
	dispatcher_.reg(CMD_RPC_EQUIP_PURIFY,ProcessAndReply<logins::SPurifyReq,logins::SPurifyResp,PurifyManager>);
	// 称号
	dispatcher_.reg(CMD_RPC_TITLE_DRESSTITLE,ProcessNoReply<logins::STitleReq, TitleManager>);
	// 在线奖励
	dispatcher_.reg(CMD_RPC_WEAL_GETONLINEREWARD,ProcessNoReply<logins::COnlineRewardReq, OnlineRewardManager>);

	dispatcher_.reg(CMD_RPC_CHAT_CHAT, ProcessNoReply<chat::CSChatProxy, ChatManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_STRENGTHEN, ProcessAndReply<logins::SStrengthenReq, logins::SStrengthenResp, ForgeManager>);
	//图鉴
	dispatcher_.reg(CMD_RPC_CARD_ACTIVECARD, ProcessNoReply<card::CSCardActiveCard, CardManager>);
	dispatcher_.reg(CMD_RPC_CARD_UPSTAR, ProcessNoReply<logins::SCardUpStarReq, CardManager>);
	//境界，转生
	dispatcher_.reg(CMD_RPC_RING_ACTIVATE, ProcessNoReply<reincarn::CSRingActive, ReinCarnManager>);
	dispatcher_.reg(CMD_RPC_REINCARN_REINCARN, ProcessNoReply<reincarn::CSReinCarn, ReinCarnManager>);
	dispatcher_.reg(CMD_RPC_REINCARN_GETEXPBYITEMS, ProcessNoReply<reincarn::CSReinCarnGetExpByItems, ReinCarnManager>);
	dispatcher_.reg(CMD_RPC_REINCARN_GETEXPBYLEVEL, ProcessNoReply<reincarn::CSReinCarnGetExpByLevel, ReinCarnManager>);
	//符文
	dispatcher_.reg(CMD_RPC_MAGIC_OPENHOLE, ProcessNoReply<rune::CSMagicOpenHole, RuneManager>);
	dispatcher_.reg(CMD_RPC_MAGIC_LEARNMAGIC, ProcessNoReply<rune::CSMagicLearn, RuneManager>);
	dispatcher_.reg(CMD_RPC_MAGIC_UPGRADEMAGIC, ProcessNoReply<rune::CSMagicUpgrade, RuneManager>);
	dispatcher_.reg(CMD_RPC_MAGIC_DECOMPOSEMAGIC, ProcessNoReply<rune::CSMagicDecomPose, RuneManager>);
	//套装
	dispatcher_.reg(CMD_RPC_EQUIP_ACTIVESUITCOLLECT, ProcessNoReply<logins::SActiveSuitReq, RoleSuitManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_UNLOCKSUITCOLLECT, ProcessNoReply<logins::SUnlockSuitReq, RoleSuitManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_DRESSSUITCOLLECT, ProcessNoReply<logins::SDressSuitReq, RoleSuitManager>);

	// 时装
	dispatcher_.reg(CMD_RPC_FASHION_ACTIVEFASHION, ProcessAndReply<logins::CActiveFashionReq, msgs::SFashion, FashionManager>);
	dispatcher_.reg(CMD_RPC_FASHION_PUTON_FASHION, ProcessAndReply<logins::CPutOnFashionReq, logins::SPutOnFashionResp, FashionManager>);
	dispatcher_.reg(CMD_RPC_FASHION_GETOFF_FASHION, ProcessAndReply<logins::CGetOffFashionReq, logins::SGetOffFashionResp, FashionManager>);
	dispatcher_.reg(CMD_RPC_FASHION_ADVANCEFASHION, ProcessAndReply<logins::CAdvanceFashionReq, msgs::SFashion, FashionManager>);
	dispatcher_.reg(CMD_RPC_FASHION_ACTIVEFASHIONSUIT, ProcessAndReply<logins::CActiveFashionSuitReq, logins::SActiveFashionSuitResp, FashionManager>);

	// 宝石
	dispatcher_.reg(CMD_RPC_EQUIP_EMBEDGEM, ProcessAndReply<logins::CEmbedGemReq, logins::SEmbedGemResp, GemManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_REMOVEGEM, ProcessAndReply<logins::CRemoveGemReq, logins::SRemoveGemResp, GemManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_UPGRADEGEM, ProcessAndReply<logins::CUpgradeGemReq, logins::SUpgradeGemResp, GemManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_ACTIVATEGEMTARGET, ProcessNoReply<logins::CctivateGemTargetReq, GemManager>);

	//副本，BOSS
	dispatcher_.reg(CMD_RPC_COPY_ENTERREINCARNCOPY, ProcessNoReply<copy::CSEnterReincarnCopy, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_ENTERMAGICTOWERCOPY, ProcessNoReply<copy::CSEnterMagicTowerCopy, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_LEAVECOPY, ProcessNoReply<copy::CSLeaveCopy, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_QUICKFINISHREINCARNCOPY, ProcessNoReply<copy::CSQuickFinish, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_GOTREINCARNREWARDS, ProcessNoReply<copy::CSGotReward, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_LOTTERYMAGICTOWER, ProcessAndReply<copy::CSLotteryMagicTower,copy::SCLotteryMagicTowerResp, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_ENTERMATERIALCOPY, ProcessNoReply<copy::CSEnterMaterialCopy, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_QUICKFINISHMATERIALCOPY, ProcessNoReply<copy::CSQuickFinishMaterial, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_MOPMATERIALCOPY, ProcessNoReply<copy::CSMopMaterial, CopyManager>);
	dispatcher_.reg(CMD_RPC_BOSS_ENTERWORLDBOSS, ProcessNoReply<copy::CSEnterWorldBoss, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_ENTERTASKCOPY, ProcessNoReply<copy::CSEnterTaskCopy, CopyManager>);
	dispatcher_.reg(CMD_RPC_BOSS_GETWORLDBOSSLIST, ProcessNoReply<copy::CSGetWorldBossList, CopyManager>);
	dispatcher_.reg(CMD_RPC_BOSS_GETGODPLANELIST, ProcessNoReply<copy::CSGetGodPlaneList, CopyManager>);
	dispatcher_.reg(CMD_RPC_BOSS_ENTERGODPLANE, ProcessNoReply<copy::CSEnterGodPlane, CopyManager>);
	dispatcher_.reg(CMD_RPC_FIGHT_REVIVE, ProcessNoReply<copy::CSFightRevive, CopyManager>);
	dispatcher_.reg(CMD_RPC_COPY_ENTEREXPCOPY, ProcessNoReply<copy::CSEnterExpCopy, CopyManager>);

	dispatcher_.reg(CMD_RPC_COPY_ENTERPARTNERISLAND, ProcessNoReply<copy::CSEnterPartnerIslandCopy, CopyManager>);


	//组队
	dispatcher_.reg(CMD_RPC_TEAM_CREATETEAM, ProcessNoReply<team::CSCreateTeam, TeamManager>);
	dispatcher_.reg(CMD_RPC_TEAM_LEAVETEAM, ProcessNoReply<team::CSLeaveTeam, TeamManager>);
	dispatcher_.reg(CMD_RPC_TEAM_DISBANDTEAM, ProcessNoReply<team::CSDisBandTeam, TeamManager>);
	dispatcher_.reg(CMD_RPC_TEAM_CHECKMEMBERCOPY, ProcessAndReply<team::CSCheckMemCopy, team::SCCheckMemCopyResponse, TeamManager>);

	dispatcher_.reg(CMD_RPC_COPY_ENTERIMMORTALROADCOPY, ProcessNoReply<copy::CSEnterImmortalroadCopy, CopyManager>);

	//日常活动
	dispatcher_.reg(CMD_RPC_DAILYACTIVITY_GETACTIVITY, ProcessNoReply<logins::SGetActivityReq, ActivityManager>);
	dispatcher_.reg(CMD_RPC_DAILYACTIVITY_GETACTIVITYREWARD, ProcessNoReply<logins::SGetActivityRewardReq, ActivityManager>);
	//铸灵
	dispatcher_.reg(CMD_RPC_EQUIP_ZHULINGUPLEVEL, ProcessAndReply<logins::SzhulingUpLevelReq, logins::SzhulingUpLevelResp, ZhuLingManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_ZHULINGUPADVANCE, ProcessAndReply<logins::SzhulingUpAdvanceReq, logins::SzhulingUpAdvanceResp, ZhuLingManager>);
	dispatcher_.reg(CMD_RPC_EQUIP_OPENZHULING, ProcessNoReply<logins::SopenZhulingReq, ZhuLingManager>);
	//战灵
	dispatcher_.reg(CMD_RPC_SKILL_CLEANNUQI, ProcessNoReply<logins::SSkillCleanNuQi, ZhanLingManager>);
	dispatcher_.reg(CMD_RPC_ZHANLING_EQUIP_ZHANLING, ProcessNoReply<logins::SEquipZhanlingReq, ZhanLingManager>);
	dispatcher_.reg(CMD_RPC_ZHANLING_ADVANCEZHANLING, ProcessNoReply<logins::SAdvanceZhanlingReq, ZhanLingManager>);
	dispatcher_.reg(CMD_RPC_ZHANLING_LEARN_ZHANLING_SKILL, ProcessNoReply<logins::SLearnZhanlingSkillReq, ZhanLingManager>);
	//恶魔天使
	dispatcher_.reg(CMD_RPC_DEVILANGEL_DEVILANGELEQUIP, ProcessNoReply<logins::SDevilAngelequipReq, DevilAngelManager>);

	//每日签到
	dispatcher_.reg(CMD_RPC_SIGN_SIGNEVERYDAY, ProcessNoReply<logins::SPlayerSignEveryDayReq, RewardManager>);
	dispatcher_.reg(CMD_RPC_SIGN_GETSIGNEVERYDAYTARGETREWARD, ProcessNoReply<logins::SGetSignEverydayRwardReq, RewardManager>);

	//等级礼包
	dispatcher_.reg(CMD_RPC_LEVELREWARD_GETLEVELREWARD, ProcessNoReply<logins::SGetLevelRwardReq, RewardManager>);
	//圣装
	dispatcher_.reg(CMD_RPC_REINCARN_COMMITSHENGMISSION, ProcessNoReply<logins::SCommitShengMissionReq, ReinCarnShengManager>);
	dispatcher_.reg(CMD_RPC_REINCARN_REQUESTSHENGMISSION, ProcessNoReply<logins::SRequestShengMissionReq, ReinCarnShengManager>);

	//暗器
	dispatcher_.reg(CMD_RPC_TRUMP_ACTIVE, ProcessNoReply<logins::STrumpActiveReq, TrumpManager>);
	dispatcher_.reg(CMD_RPC_TRUMP_UPGRADE, ProcessNoReply<logins::STrumpUpgradeReq, TrumpManager>);
	dispatcher_.reg(CMD_RPC_TRUMP_ACTIVETRUMPSKILL, ProcessNoReply<logins::SActiveTrumpSkillReq, TrumpManager>);
	dispatcher_.reg(CMD_RPC_TRUMP_REQUESTMISSION, ProcessNoReply<logins::STrumpRequestMissionReq, TrumpManager>);
	dispatcher_.reg(CMD_RPC_TRUMP_UNLOCKTRUMP, ProcessNoReply<logins::SUnlockTrumpReq, TrumpManager>);
	//进阶
	dispatcher_.reg(CMD_RPC_ADVANCE_ONEKEYDRESS, ProcessNoReply<logins::SOneKeyDressReq, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_DRESS, ProcessNoReply<logins::SDressReq, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_STRENGTHEQUIP, ProcessNoReply<logins::SStrengthEquipReq, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_SHOP_RECYCLE, ProcessNoReply<logins::SRecycleReq, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_LEARNSKILL, ProcessNoReply<logins::SLearnSkillReq, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_ADVANCEAWAKEN, ProcessNoReply<logins::SAdvanceAwakenReq, AdvanceManager>);
	dispatcher_.reg(CMD_RPC_ADVANCE_ACTIVEADVANCETARGET, ProcessNoReply<logins::SActiveAdvanceTargetReq, AdvanceManager>);

	dispatcher_.reg(CMD_RPC_NEARENMEY_FIGHTENEMY, ProcessNoReply<logins::SNearenmeyFightenemyReq, NearEnemyManager>);
    dispatcher_.reg(CMD_RPC_NEARENMEY_BACKTOHANG, ProcessNoReply<logins::SNearenemyBacktoHangReq, NearEnemyManager>);
	dispatcher_.reg(CMD_RPC_TOPLIST_GETTOPLIST, ProcessAndReply<logins::SGetTopListReq, msgs::SToplist, ToplistManager>);
	//商城
	dispatcher_.reg(CMD_RPC_SHOP_BUY, ProcessNoReply<logins::SBuyReq, ShopManager>);
}

void LogicManager::RegSync() {
	synchronizer_.reg(CMD_PLAYER_LOGIN_DATA, MsgSend<msgs::SPlayerLoginData, UserManager>);
	synchronizer_.reg(CMD_PLAYER_PLAYER, MsgSend<dbs::TPlayer, UserManager>);
	synchronizer_.reg(CMD_SEND_PLAYER_MONEY_LIST, MsgSend<msgs::SPlayerMoneyList, UserManager>);
	synchronizer_.reg(CMD_PLAYER_CONFIG, MsgSend<dbs::TPlayerConfig, UserManager>);
	synchronizer_.reg(CMD_PLAYER_ROLE_LIST, MsgSend<msgs::SPlayerRoleList, RoleManager>);
	synchronizer_.reg(CMD_SERVER_INFO, MsgSend<msgs::SServerInfo, LogicManager>);
	synchronizer_.reg(CMD_PLAYER_ENTER_MAP, MsgSend<msgs::SPlayerEnterMap, MapManager>);
	synchronizer_.reg(CMD_ROLE_ENTER_MAP, MsgSend<msgs::SRoleEnterMap, MapManager>);
	synchronizer_.reg(CMD_ROLE_ENTER_MAP_END, MsgSend<msgs::SRoleEnterMapEnd, MapManager>);
	synchronizer_.reg(CMD_FIGHT_FLYING_UP, MsgSend<msgs::SFightFlyingUp, MapManager>);
	synchronizer_.reg(CMD_MAP_ENTERS, MsgSend<msgs::SMapEntityEnters, MapManager>);
	synchronizer_.reg(CMD_ROLE_COMBAT_DATA, MsgSend<msgs::SRoleCombatData, MapManager>);
	synchronizer_.reg(CMD_PLAYER_COMBAT_DATA, MsgSend<msgs::SPlayerCombatData, MapManager>);
	synchronizer_.reg(CMD_PLAYER_SKILL_INFO, MsgSend<msgs::SPlayerSkillInfo, SkillManager>);
	synchronizer_.reg(CMD_HANG_POWER, MsgSend<msgs::SHangPower, MapManager>);
	synchronizer_.reg(CMD_SEND_PLAYER_BAG_LIST, MsgSend<msgs::SPlayerBagList, EquipsManager>);
	synchronizer_.reg(CMD_SEND_PLAYER_BAG_ITEM_LIST, MsgSend<msgs::SPlayerBagItemList, EquipsManager>);
	synchronizer_.reg(CMD_SEND_PLAYER_MISSION_LIST, MsgSend<msgs::SPlayerMissionList, MissionManager>);
	synchronizer_.reg(CMD_PLAYER_ADVANCE_INFO, MsgSend<msgs::SPlayerAdvanceInfo, AdvanceManager>);
	synchronizer_.reg(CMD_PLAYER_ADVANCE_AWAKEN, MsgSend<msgs::SPlayerAdvanceAwakenInfo, AdvanceManager>);
	synchronizer_.reg(CMD_PLAYER_ADVANCE_TARGETS, MsgSend<msgs::SIntIntMap, AdvanceManager>);
	synchronizer_.reg(CMD_SHENQI_INFO, MsgSend<msgs::SShenqiInfo, ShenQiManager>);
	synchronizer_.reg(CMD_TREASURE_ADVANCE_INFO, MsgSend<msgs::STreasureAdvanceInfo, TreasureManager>);
	synchronizer_.reg(CMD_PLAYER_TREASURE_INFO, MsgSend<msgs::SPlayerTreasureInfo, TreasureManager>);
	synchronizer_.reg(CMD_PLAYER_EQUIPS, MsgSend<msgs::SPlayerEquipList, ForgeManager>);
	synchronizer_.reg(CMD_PLAYER_CARDGROUP, MsgSend<msgs::SCardGroup, CardManager>);
	synchronizer_.reg(CMD_ACHIEVEMENT, MsgSend<msgs::SInt, ReinCarnManager>);
	synchronizer_.reg(CMD_ACHIEVEMENT_CHAPTER, MsgSend<msgs::SInt, ReinCarnManager>);
	synchronizer_.reg(CMD_REINCARN_INFO, MsgSend<msgs::SReincarnInfo, ReinCarnManager>);
	synchronizer_.reg(CMD_PLAYER_CAREER_LEVEL, MsgSend<msgs::SInt, ReinCarnManager>);
	synchronizer_.reg(CMD_PLAYER_SUIT_COLLECTS, MsgSend<msgs::SPlayerSuitCollects, RoleSuitManager>);
	synchronizer_.reg(CMD_MAGIC_INFO, MsgSend<msgs::SMagicInfo, RuneManager>);
	synchronizer_.reg(CMD_ZHANLING_INFO, MsgSend<msgs::SZhanlingInfo, ZhanLingManager>);
	// 称号
	synchronizer_.reg(CMD_PLAYER_TITLE_INFO, MsgSend<msgs::SPlayerTitleInfo, TitleManager>);
	synchronizer_.reg(CMD_PLAYER_WEAR_TITLE, MsgSend<msgs::SIntIntMap, TitleManager>);
	// 在线奖励
	synchronizer_.reg(CMD_PLAYER_ONLINE_REWARD, MsgSend<msgs::SPlayerOnlineReward, OnlineRewardManager>);
	// 时装
	synchronizer_.reg(CMD_PLAYER_FASHION, MsgSend<msgs::SPlayerFashionInfo, FashionManager>);


	//副本，BOSS
	synchronizer_.reg(CMD_PLAYER_COPY_DATA_LIST, MsgSend<msgs::SPlayerCopyDataList, CopyManager>);
	synchronizer_.reg(CMD_LOTTERY_MAGIC_TOWER, MsgSend<msgs::SLotteryMagicTower, CopyManager>);
	synchronizer_.reg(CMD_BOSS_INFO, MsgSend<msgs::SBossList, CopyManager>);
	synchronizer_.reg(CMD_ENTITY_UPDATE, MsgSend<msgs::SEntityUpdate, CopyManager>);

	synchronizer_.reg(CMD_DAILY_ACTIVITY_INFO, MsgSend<msgs::SDailyActivityInfo, ActivityManager>);

	//铸灵
	synchronizer_.reg(CMD_PLAYER_ZHULING_OPEN_IFNO, MsgSend<msgs::SInts, ZhuLingManager>);
	//恶魔天使
	synchronizer_.reg(CMD_PLAYER_DEVILANGEL_DATE, MsgSend<msgs::SDevilAngelDate, DevilAngelManager>);
	synchronizer_.reg(CMD_PLAYER_SIGNEVERYDAY, MsgSend<msgs::SPlayerSignEveryDay, RewardManager>);
	synchronizer_.reg(CMD_PLAYER_LEVELREWARD, MsgSend<msgs::SPlayerLevelReward, RewardManager>);
	//圣装任务
	synchronizer_.reg(CMD_SHENG_INFO, MsgSend<msgs::SShengInfo, ReinCarnShengManager>);
	//暗器
	synchronizer_.reg(CMD_TRUMP_INFO, MsgSend<msgs::STrumpInfo, TrumpManager>);
	synchronizer_.reg(CMD_NEARENEMY_INFO, MsgSend<msgs::SNearEnemyInfo, NearEnemyManager>);
	//商城
	synchronizer_.reg(CMD_PLAYER_SHOP_INFO, MsgSend<msgs::SShopInfo, ShopManager>);
}

bool LogicManager::ActorLogin(uint32_t uid) {
	SkillManager::Instance()->ActorLogin(uid);
	MissionManager::Instance()->ActorLogin(uid);
	EquipsManager::Instance()->ActorLogin(uid);
	TreasureManager::Instance()->ActorLogin(uid);
	UserManager::Instance()->onLogin(uid);
	ZhanLingManager::Instance()->ActorLogin(uid);

	MapManager::Instance()->ActorLogin(uid);

	return true;
}

bool LogicManager::AfterLogin(uint32_t uid) {
	HangManager::Instance()->AfterLogin(uid);
	return true;
}

void LogicManager::AddSync(uint32_t cmd) {
	sync_cmds_.push_back(cmd);
}

void LogicManager::DoReply(uint32_t cb, uint32_t err) {
	static BattleServer* pServer = BattleServer::Instance();
	static CFirePacket packet;
	packet.Clean();
	if (reply_ != NULL) {
		CBufferWriter writer(packet.GetBody());
		if (!reply_->encode(writer)) {
			return;
		}
		packet.msgId = reply_->msgId();
	} else {
		packet.msgId = -1;
	}

	packet.fd = curr_fd_;
	packet.time = curr_ts_;
	packet.microTime = curr_mts_;
	packet.ChannelId = channel_id_;
	packet.cmd = PROTOCOL_ACCESS_ANSWER;
	packet.callback = cb;
	packet.errorCode = err;

	pServer->AddSend(&packet);
}

void LogicManager::DoSync() {
	if (sync_cmds_.empty()) {
		return;
	}
	int ret = 0;
	uint32_t uid = GetUid();
	const UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		error_log("cache not init uid=%u", uid);
		return;
	}
	static list<uint32_t>::iterator itr;
	for (itr = sync_cmds_.begin(); itr != sync_cmds_.end(); ++itr) {
		ret = synchronizer_.onSync(cache, *itr);
		if (0 != ret) {
			error_log("uid=%u,cmd=%u", uid, *itr);
		} else {
			debug_log("uid=%u,cmd=%u", uid, *itr);
		}
	}
	sync_cmds_.clear();
}

int LogicManager::Process(uint32_t uid, igameapp::SLoginGame *req) {
	uid = req->playerId_;
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		error_log("cache not init uid=%u", uid);
		return R_ERR_NO_DATA;
	}

	FdManager::Instance()->addMap(curr_fd_, curr_ts_, curr_mts_, cache.uid_);

	ActorLogin(cache.uid_);

	AddSync(CMD_SERVER_INFO);
	AddSync(CMD_PLAYER_LOGIN_DATA);
	AddSync(CMD_PLAYER_PLAYER);
	AddSync(CMD_PLAYER_ROLE_LIST);
	AddSync(CMD_SEND_PLAYER_BAG_LIST);
	AddSync(CMD_SEND_PLAYER_MONEY_LIST);
	AddSync(CMD_PLAYER_CONFIG);
	AddSync(CMD_SEND_PLAYER_BAG_ITEM_LIST);
	AddSync(CMD_ROLE_COMBAT_DATA);
	AddSync(CMD_PLAYER_COMBAT_DATA);
	AddSync(CMD_PLAYER_SKILL_INFO);
	AddSync(CMD_PLAYER_ENTER_MAP);
	AddSync(CMD_ROLE_ENTER_MAP);
	AddSync(CMD_ROLE_ENTER_MAP_END);
	AddSync(CMD_MAP_ENTERS);
	AddSync(CMD_TREASURE_ADVANCE_INFO);
	AddSync(CMD_PLAYER_CARDGROUP);
	AddSync(CMD_ACHIEVEMENT);
	AddSync(CMD_ACHIEVEMENT_CHAPTER);
	AddSync(CMD_REINCARN_INFO);
	AddSync(CMD_ZHANLING_INFO);
	AddSync(CMD_SEND_PLAYER_MISSION_LIST);
	AddSync(CMD_PLAYER_SUIT_COLLECTS);
	AddSync(CMD_MAGIC_INFO);
	AddSync(CMD_PLAYER_COPY_DATA_LIST);
	AddSync(CMD_BOSS_INFO);
	AddSync(CMD_LOTTERY_MAGIC_TOWER);
	AddSync(CMD_DAILY_ACTIVITY_INFO);
	AddSync(CMD_HANG_POWER);
	AddSync(CMD_PLAYER_TITLE_INFO); // 用户称号信息
	AddSync(CMD_PLAYER_WEAR_TITLE);
	AddSync(CMD_PLAYER_ONLINE_REWARD);// 在线奖励 4072
	AddSync(CMD_PLAYER_FASHION);// 时装

	AddSync(CMD_PLAYER_ZHULING_OPEN_IFNO);
	AddSync(CMD_PLAYER_DEVILANGEL_DATE);

	AddSync(CMD_SHENG_INFO);	//圣装任务

	AddSync(CMD_PLAYER_ADVANCE_AWAKEN); //进阶 觉醒
	AddSync(CMD_PLAYER_ADVANCE_TARGETS); //进阶羁绊


	//xxx 登录同步消息先发给客户端，然后处理AfterLogin
	UpdateManager::Instance()->Send(uid);
	DoSync();
	AfterLogin(cache.uid_);

	return 0;
}

int LogicManager::Process(uint32_t uid, logins::SLoginPing *req, logins::SLoginPong *resp) {
	resp->serverTs_ = StartMilliTime + GlobalMilliTime;
	resp->clientTs_ = req->clientTs_;

	return 0;
}

int LogicManager::Process(uint32_t uid, logins::SQueryGameData *req) {
	vector<int32_t>::iterator itr = req->cmds_.begin();
	Json::Value log;
	for (; itr != req->cmds_.end(); ++itr) {
		log.append(*itr);
		AddSync(*itr);
	}
	debug_log("%s", Json::ToString(log).c_str());
	return 0;
}

int LogicManager::Sync(const UserCache &c, uint32_t cmd, msgs::SServerInfo *resp) {
	resp->nowDt_ = StartMilliTime + GlobalMilliTime;
	resp->openDt_ = SecOpenTime * 1000;
	resp->preOpenDt_ = resp->openDt_;
	resp->worldLevel_ = 10;
	resp->offsetHour_ = -8;
	resp->antiAddiction_ = 1;
	resp->crossAOpenDt_ = resp->openDt_;
	resp->crossBOpenDt_ = resp->openDt_;
	resp->crossCOpenDt_ = resp->openDt_;
	if (!SendMsg(c.uid_, cmd, resp)) {
		return R_ERROR;
	}
	debug_log("nowDt_=%llu", resp->nowDt_);

	return R_SUCCESS;
}
