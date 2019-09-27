/*
 * LogicManager.cpp
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#include "LogicManager.h"
#include "FdManager.h"
#include "LoginServer.h"
#include "PlayerManager.h"
#include "BattleManager.h"
#include "AdminManager.h"
#include "BuyGoodsManager.h"
#include "ChatManager.h"
#include "ChatManager.h"
#include "RankManager.h"
#include "SocialManager.h"
#include "AsyncDBManager.h"
#include "BoatManager.h"
#include "SystemMessage.h"
#include "ConfigInc.h"
#include "ActivityTimeManager.h"
#include "NewServerRankManager.h"
#include "AutoTransportManager.h"
#include "WorldManager.h"
#include "BossRankManager.h"
#include "ArenaRankManager.h"
#include "OtherServerManager.h"
#include "ActRankManager.h"

#define PER_FRAME_TIME 10

uint32_t LogicManager::GlobalTime = 0;
uint32_t LogicManager::GlobalMilliTime = 0;
uint64_t LogicManager::StartMilliTime = 0;
uint32_t LogicManager::lastLoopTime = 0;
uint32_t LogicManager::ServerId = 0;
uint32_t LogicManager::OpenTs = 0;

LogicManager::LogicManager() {
}

LogicManager::~LogicManager() {
}

bool LogicManager::init() {
	GlobalTime = time(NULL);
	struct timeval tv;
	gettimeofday(&tv, NULL);
	StartMilliTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	GlobalMilliTime = 0;
	ServerId = Config::GetIntValue("server_id");	//本login属于第几个区(服)
	OpenTs = Config::GetIntValue("server_open_ts");	//开服时间
	if (!busiInit()) {
		return false;
	}
	if (!configInit()) {
		return false;
	}
	if (ResourceManager::getMaxTLLimit() == 0) {
		error_log("ResourceManager getMaxTLLimit fail");
		return false;
	}
	if (ResourceManager::getTLRecoveInterval() == 0) {
		error_log("ResourceManager getTLRecoveInterval fail");
		return false;
	}
	RankManager::getInstance()->init();
	SystemMessage::getInstance()->init();
	NewServerRankManager::getInstance()->init();
	AutoTransportManager::getInstance()->init();
	WorldManager::getInstance()->init();
	BossRankManager::getInstance()->init();
	ArenaRankManager::getInstance()->init();
	ActRankManager::getInstance()->init();
	return true;
}

bool LogicManager::onExit() {
	SystemMessage::getInstance()->save();
	RankManager::getInstance()->save();
	NewServerRankManager::getInstance()->save();
	AutoTransportManager::getInstance()->save();
	WorldManager::getInstance()->save();
	BossRankManager::getInstance()->save();
	ArenaRankManager::getInstance()->save();
	ActRankManager::getInstance()->save();
	return true;
}

bool LogicManager::onReload() {
	ActivityTimeManager::getInstance()->reload();
	NewServerRankManager::getInstance()->reset();
	ActRankManager::getInstance()->reset();
	return true;
}

bool LogicManager::doPacket(CNetPacket* packet) {
	switch (packet->ptype) {
	case PROTOCOL_TYPE_ACCESS_TRANSFER:
	case PROTOCOL_TYPE_TEST:
	case PROTOCOL_TYPE_SERVER_ASYNC:
		doTransfer(packet);
		break;
	case PROTOCOL_TYPE_SECOND_TIMER:
		doTimerProcess(packet);
		break;
	case PROTOCOL_TYPE_LOGIN_TRANSFER:
		doLoginTransfer(packet);
		break;
	case PROTOCOL_TYPE_ACCESS_ANSWER:
		doAccessAnswer(packet);
		break;
	case PROTOCOL_TYPE_COFFLINE:
		doClientOffline(packet);
		break;
	case PROTOCOL_TYPE_BATTLE_ANSWER:
		doBattleAnswer(packet);
		break;
	case PROTOCOL_TYPE_ADMIN:
		doAdmin(packet);
		break;
	case PROTOCOL_TYPE_TRANSIT_ANSWER:
		doTransitAnswer(packet);
		break;
	case PROTOCOL_TYPE_ALL_SERVER_ANSWER:
		doAllServerAnswer(packet);
		break;
	default:
		break;
	}

	return true;
}

bool LogicManager::doClientOffline(CNetPacket* packet) {
	static FdManager * fdManager = FdManager::getInstance();
	uint32_t uid, rid;
	if (!fdManager->getRole(packet->fd, packet->stime, packet->mtime, uid, rid)) {
		error_log("unknow user fd stime mtime = [%u %u %u]", packet->fd, packet->stime, packet->mtime);
		return false;
	}
	packet->uid = uid;
	PlayerManager::getInstance()->offlineProcess(packet->uid, "client_offline");
	return true;
}

bool LogicManager::doHeartBeat(CNetPacket * packet) {
	CHeartBeatProtocol protocol;
	if (!protocol.Decode(&packet->body)) {
		error_log("CHeartBeatProtocol decode failed by uid=%u", packet->uid);
		return false;
	}
	uint32_t uid = packet->uid;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	GlobalMilliTime = tv.tv_sec * 1000 + tv.tv_usec / 1000 - StartMilliTime;
	Player * player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player != NULL) {
		player->setFrontReady(true);
		player->checkNextDay();
		SystemMessage::getInstance()->onHeartBeat(uid);
	}
	if (protocol.clientTime > GlobalMilliTime + 100) {
		error_log("uid=%u,clientTime=%u,gts=%u,StartMilliTime=%u", packet->uid, protocol.clientTime, GlobalMilliTime, StartMilliTime);
		PlayerManager::getInstance()->forceKick(uid, "acc_forcekick");
	}
	sendServerTime(uid);
	return true;
}

bool LogicManager::doAllianceBuilding(CNetPacket* packet) {
	return true;
}

bool LogicManager::sendToAllServer(CNetPacket* packet) {
	packet->ptype = PROTOCOL_TYPE_ALL_SERVER_TRANSFER;
	packet->fd = packet->uid;
	LoginServer::getInstance()->sendData(packet);
	return true;
}

bool LogicManager::doAllServerAnswer(CNetPacket* packet) {
	packet->uid = packet->fd;
	switch (packet->cmd)
	{
	case PROTOCOL_CMD_BOAT:
		PlayerManager::getInstance()->doPacket(packet);
		break;
	}
	debug_log("uid=%u,cmd=%u,subcmd=%u", packet->uid, static_cast<uint32_t>(packet->cmd), static_cast<uint32_t>(packet->subCmd));
	return true;
}

bool LogicManager::doBattleAnswer(CNetPacket* packet) {
	packet->uid = packet->fd;
	switch (packet->cmd) {
	case PROTOCOL_CMD_BATTLE:
		BattleManager::getInstance()->doBattlePacket(packet);
		break;
	case PROTOCOL_CMD_LOGIN:
	case PROTOCOL_CMD_VIDEO:
	case PROTOCOL_CMD_GATE:
	case PROTOCOL_CMD_GOD:
	case PROTOCOL_CMD_WARRIOR_GATE:
	case PROTOCOL_CMD_SKILL:
		PlayerManager::getInstance()->doPacket(packet);
		break;
	case PROTOCOL_CMD_MATCH:
		//MultiMatchManager::getInstance()->doBattlePacket(packet);
		break;
	case PROTOCOL_CMD_JOINT_OPERATION:
		//JointOperationManager::getInstance()->doBattlePacket(packet);
		break;
	case PROTOCOL_CMD_ALLIANCE_BATTLE:
		//LeagueBattleManager::getInstance()->doBattlePacket(packet);
		break;
	}
	return true;
}

bool LogicManager::doAccessAnswer(CNetPacket* packet) {
	FDINFO fdInfo;
	packet->uid = packet->fd;

	if (FdManager::getInstance()->getFdInfo(packet->uid, fdInfo)) {
		packet->fd = fdInfo.fd;
		packet->stime = fdInfo.time;
		packet->mtime = fdInfo.microTime;
		return LoginServer::getInstance()->sendData(packet);
	}
	return true;
}

bool LogicManager::doLoginTransfer(CNetPacket* packet) {
	return true;
}

bool LogicManager::doTransfer(CNetPacket* packet) {
	if (packet->cmd == PROTOCOL_CMD_LOGIN && packet->subCmd == PROTOCOL_SUBCMD_LOGIN) {
		PlayerManager::getInstance()->doLogin(packet);
		return true;
	}
	if (packet->ptype == PROTOCOL_TYPE_ACCESS_TRANSFER) {
		uint32_t uid, rid;
		if (!FdManager::getInstance()->getRole(packet->fd, packet->stime, packet->mtime, uid, rid)) {
			error_log("unknow user fd stime mtime=[%u %u %u] cmd=[%u %u]",
					packet->fd, packet->stime, packet->mtime, static_cast<uint32_t>(packet->cmd), static_cast<uint32_t>(packet->subCmd));
			return false;
		}
		packet->uid = uid;
	} else {
		packet->uid = packet->fd;
	}

	clientProcess(packet);

	return true;
}

void LogicManager::doTimerProcess(CNetPacket* pPacket) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	GlobalMilliTime = tv.tv_sec * 1000 + tv.tv_usec / 1000 - StartMilliTime;

	//抛弃挤压消息，避免消息阻塞引起的雪崩
	if (GlobalMilliTime - lastLoopTime < PER_FRAME_TIME) {
		info_log("timer process time out time=%u", GlobalMilliTime - lastLoopTime);
		return;
	}

	static uint32_t counter = 0;
	onTimer();

	//500毫秒一个tick
	if (counter++ % 2 == 0) {
		onSecondTimer();
	}

	gettimeofday(&tv, NULL);
	lastLoopTime = tv.tv_sec * 1000 + tv.tv_usec / 1000 - StartMilliTime;
	if (lastLoopTime - GlobalMilliTime > 40) {
		info_log("timer run time = %u", lastLoopTime - GlobalMilliTime);
	}
}

void LogicManager::onTimer() {
	if (LoginServer::IsReLoad) {
		LoginServer::IsReLoad = false;
		onReload();
	}
}

void LogicManager::onSecondTimer() {
	LogicManager::GlobalTime = time(NULL);
	Time::UpdateGlobalTime();
	PlayerManager::getInstance()->onSecondTimer();
	AsyncDBManager::getInstance()->printStat();
	CDataState::printStat();
	LoginServer::getInstance()->printStat();
	NewServerRankManager::getInstance()->onTimer();
	AutoTransportManager::getInstance()->onTimer();
	BossRankManager::getInstance()->onSecondTimer();
	ArenaRankManager::getInstance()->onSecondTimer();
	ActRankManager::getInstance()->onSecondTimer();
	static int counter = 0;
	if (++counter % 60 == 0) {
		BUSI_ONLINE("%u", FdManager::getInstance()->getFdCount());
	}
}

bool LogicManager::clientProcess(CNetPacket* pPacket) {
	switch (pPacket->cmd) {
	case PROTOCOL_CMD_LOGIN:
	case PROTOCOL_CMD_EQUIPMENT:
	case PROTOCOL_CMD_HERO:
	case PROTOCOL_CMD_BUILDING:
	case PROTOCOL_CMD_USER:
	case PROTOCOL_CMD_RESOURCE:
	case PROTOCOL_CMD_TASK:
	case PROTOCOL_CMD_EMAIL:
	case PROTOCOL_CMD_VIDEO:
	case PROTOCOL_CMD_GATE:
	case PROTOCOL_CMD_WARRIOR_GATE:
	case PROTOCOL_CMD_RIDE:
	case PROTOCOL_CMD_DAILY_TASK:
	case PROTOCOL_CMD_REWARD:
	case PROTOCOL_CMD_SKILL:
	case PROTOCOL_CMD_MISC:
	case PROTOCOL_CMD_INVITE:
	case PROTOCOL_CMD_SOLDIER:
	case PROTOCOL_CMD_HOME:
	case PROTOCOL_CMD_WORKER:
	case PROTOCOL_CMD_BOAT:
	case PROTOCOL_CMD_ARENA:
	case PROTOCOL_CMD_GOD:
	case PROTOCOL_CMD_CANNON:
	case PROTOCOL_CMD_BUILDING_TRAIN:
	case PROTOCOL_CMD_TROOPS:
	case PROTOCOL_CMD_DAILY_BUY:
	case PROTOCOL_CMD_RANDOM_QUEST:
	case PROTOCOL_CMD_ACTIVITY:
	case PROTOCOL_CMD_BOSS:
	case PROTOCOL_CMD_AD:
		PlayerManager::getInstance()->doPacket(pPacket);
		break;
	case PROTOCOL_CMD_BATTLE:
		BattleManager::getInstance()->doAccessPacket(pPacket);
		break;
	case PROTOCOL_CMD_ALLIANCE_BATTLE:
		//LeagueBattleManager::getInstance()->doAccessPacket(pPacket);
		break;
	case PROTOCOL_CMD_WORLD:
		WorldManager::getInstance()->doPacket(pPacket);
		break;
	case PROTOCOL_CMD_RANK:
		RankManager::getInstance()->doPacket(pPacket);
		break;
	case PROTOCOL_CMD_SOCIAL:
		break;
	case PROTOCOL_CMD_LEAGUE:
		break;
	case PROTOCOL_CMD_ALLIANCE_BUILDING:
		doAllianceBuilding(pPacket);
		break;
	case PROTOCOL_CMD_LOGIC:
		logicProcess(pPacket);
		break;
	case PROTOCOL_CMD_TRANSIT:
		BuyGoodsManager::getInstance()->doLoginRequest(pPacket);
		break;
	case PROTOCOL_CMD_MATCH:
		//MultiMatchManager::getInstance()->doAccessPacket(pPacket);
		break;
	case PROTOCOL_CMD_JOINT_OPERATION:
		//JointOperationManager::getInstance()->doAccessPacket(pPacket);
		break;
	case PROTOCOL_CMD_OTHSRV:
		OtherServerManager::getInstance()->doPacket(pPacket);
		break;
	default:
		break;
	}
	return true;
}

bool LogicManager::sendToAccess(CNetPacket * packet) {
	packet->ptype = PROTOCOL_TYPE_ACCESS_ANSWER;
	FDINFO fdInfo;
	if (FdManager::getInstance()->getFdInfo(packet->uid, fdInfo) && PlayerManager::getInstance()->isLoadComplete(packet->uid)) {
		packet->fd = fdInfo.fd;
		packet->stime = fdInfo.time;
		packet->mtime = fdInfo.microTime;
		return LoginServer::getInstance()->sendData(packet);
	}
	return false;
}

void LogicManager::sendAll(CNetPacket *packet) {
	packet->ptype = PROTOCOL_TYPE_ACCESS_ANSWER;
	vector<FDINFO> vecFd;
	FdManager::getInstance()->getAllFd(vecFd);
	for (vector<FDINFO>::iterator it = vecFd.begin(); it != vecFd.end(); ++it) {
		packet->fd = it->fd;
		packet->stime = it->time;
		packet->mtime = it->microTime;
		LoginServer::getInstance()->sendData(packet);
	}
}

bool LogicManager::sendToBattle(CNetPacket * packet) {
	packet->ptype = PROTOCOL_TYPE_BATTLE_TRANSFER;
	LoginServer::getInstance()->sendData(packet);
	return true;
}

bool LogicManager::sendToLogin(CNetPacket* pPacket) {
	pPacket->ptype = PROTOCOL_TYPE_SERVER_ASYNC;
	pPacket->fd = pPacket->uid;
	LoginServer::getInstance()->sendData(pPacket);
	return true;
}

bool LogicManager::transToBattle(CNetPacket * packet) {
	/*
	 packet->fd = packet->uid;
	 packet->ptype = PROTOCOL_TYPE_ACCESS_TRANSFER;
	 LoginServer::getInstance()->sendData(packet);
	 */
	return true;
}

bool LogicManager::doAdmin(CNetPacket* packet) {
	AdminManager::getInstance()->doAdmin(packet);
	return true;
}

bool LogicManager::sendServerTime(uint32_t uid) {
	CNetPacket sPacket;
	sPacket.uid = uid;
	CBufferWriter writer(&sPacket.body);
	writer.AppendByte(PROTOCOL_CMD_LOGIC);
	writer.AppendByte(PROTOCOL_RSP_SUBCMD_SERVER_TIME);
	writer.AppendUInt32(GlobalMilliTime);
	writer.AppendUInt32(GlobalTime);
	writer.AppendUInt32((GlobalTime + 86400 - OpenTs) / 86400);
	sendToAccess(&sPacket);
	return true;
}

uint32_t LogicManager::NextDayTime() {
	time_t next = LogicManager::GlobalTime + 3600 * 24;
	struct tm* mTm = localtime(&next);
	mTm->tm_hour = 0;
	mTm->tm_min = 0;
	mTm->tm_sec = 0;
	return mktime(mTm);
}

bool LogicManager::logicProcess(CNetPacket* pPacket) {
	if (pPacket->subCmd == PROTOCOL_SUBCMD_HEART_BEAT) {
		doHeartBeat(pPacket);
	}
	return true;
}

bool LogicManager::sendSystemMsg(uint32_t uid, const string& msg, ...) {
	static char buf[1024] = { 0 };
	va_list args;
	va_start(args, msg);
	vsnprintf(buf, sizeof(buf), msg.c_str(), args);
	va_end(args);
	static CNetPacket packet;
	packet.body.Clear();
	packet.ptype = PROTOCOL_TYPE_ACCESS_ANSWER;
	CBufferWriter writer(&packet.body);
	packet.uid = uid;
	writer.AppendByte(PROTOCOL_CMD_LOGIC);
	writer.AppendByte(PROTOCOL_RSP_SUBCMD_SYSTEM_TIPS);
	writer.AppendString(buf);
	writer.AppendByte(0);
	sendToAccess(&packet);
	return true;
}

bool LogicManager::busiInit() {
	if (0 != CLog::create_inst("login", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("misc", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("coin", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("equip", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("token", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("online", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("soldier", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	if (0 != CLog::create_inst("resource", Config::GetValue("log_busi").c_str())) {
		return false;
	}
	return true;
}

bool LogicManager::configInit() {
	if (!BuildingConfig::getInstance()->init()) {
		return false;
	}
	if (!EquipmentConfig::getInstance()->init(Config::GetValue(CONFIG_EQUIPMENT_COMMON))) {
		return false;
	}
	if (!HeroConfig::getInstance()->init()) {
		return false;
	}
	if (!TaskConf::getInstance()->init(Config::GetValue(CONFIG_TASK))) {
		return false;
	}
	if (!ExpConfig::getInstance()->init(Config::GetValue(CONFIG_EXP))) {
		return false;
	}
	if (!GateConfig::getInstance()->initDefend(Config::GetValue("defend_gate"))) {
		return false;
	}
	if (!GateConfig::getInstance()->initTrade(Config::GetValue("trade_config"))) {
		return false;
	}
	if (!LanguageConfig::getInstance()->init(Config::GetValue(CONFIG_LANGUAGE))) {
		return false;
	}
	if (!DailyQuestConfig::getInstance()->init(Config::GetValue(CONFIG_ACTIVENESS))) {
		return false;
	}
	if (!CSkillConfig::getInstance()->init(Config::GetValue(CONFIG_SKILLS))) {
		return false;
	}
	if (!VipConfig::getInstance()->init(Config::GetValue(CONFIG_SGVIP))) {
		return false;
	}
	if (!CFeteConfig::getInstance()->init(Config::GetValue(CONFIG_FETE))) {
		return false;
	}
	if (!SoldierConfig::getInstance()->init(Config::GetValue(CONFIG_SOLDIER))) {
		return false;
	}
	if (!GiftBagConfig::getInstance()->init(Config::GetValue(CONFIG_GIFT_BAG))) {
		return false;
	}
	if (!GiftBagConfig::getInstance()->initLuckyLottery(Config::GetValue("diamondDraw"))) {
		return false;
	}
	if (!GiftBagConfig::getInstance()->initfunctionUnlock(Config::GetValue("functionUnlock"))) {
		return false;
	}
	if (!GiftBagConfig::getInstance()->initFirstCharge(Config::GetValue("firstCharge"))) {
		return false;
	}
	if (!InviteConfig::getInstance()->init(Config::GetValue(CONFIG_INVITE))) {
		return false;
	}
	if (!CBoatConfig::getInstance()->init(Config::GetValue(CONFIG_RESOURCE_TRANSPORT))) {
		return false;
	}
	if (!CShopConfig::getInstance()->init()) {
		return false;
	}
	if (!CShareConfig::getInstance()->init(Config::GetValue(CONFIG_SHARE))) {
		return false;
	}
	if (!SevenDaysConfig::getInstance()->init(Config::GetValue("sevendays"))) {
		return false;
	}
	if (!SevenDaysConfig::getInstance()->initSign(Config::GetValue("dailysign"))) {
		return false;
	}
	if (!StrongConfig::getInstance()->init(Config::GetValue("strongconfig"))) {
		return false;
	}
	if (!DailyBuyConfig::getInstance()->init(Config::GetValue("dailybuy"))) {
		return false;
	}
	if (!PayConfig::getInstance()->init()) {
		return false;
	}
	if (!SpecialDiscountConfig::getInstance()->init()) {
		return false;
	}
	if (!RecyclingConfig::getInstance()->init(Config::GetValue("recycling"))) {
		return false;
	}
	if (!RandomQuestConfig::getInstance()->init(Config::GetValue("randomquest"))) {
		return false;
	}
	if (!ActivityTimeManager::getInstance()->init()) {
		return false;
	}
	if (!OpenServerConfig::getInstance()->init(Config::GetValue("open_server"))) {
		return false;
	}
	if (!WorldConfig::getInstance()->init(Config::GetValue("nworld"))) {
		return false;
	}
	if (!SevenDayTaskConfig::getInstance()->init(Config::GetValue("sevendaytask"))) {
		return false;
	}
	if (!BossConfig::getInstance()->init(Config::GetValue("boss"))) {
		return false;
	}
	if (!ArenaConfig::getInstance()->init(Config::GetValue("arena"))) {
		return false;
	}
	if (!WatchADConfig::getInstance()->init(Config::GetValue("advertise"))) {
		return false;
	}
	if (!GateEnemyConfig::getInstance()->init(Config::GetValue("gateenemy"))) {
		return false;
	}
	return true;
}

bool LogicManager::doTransitAnswer(CNetPacket* packet) {
	packet->uid = packet->mtime;
	if (packet->fd != 0) {
		PlayerManager::getInstance()->forceKick(packet->uid, "transit_fail");
		return false;
	}
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_TRANSIT_LOGIN:
		PlayerManager::getInstance()->doTencentUserInfo(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_BLUE_GET:
		PlayerManager::getInstance()->doGetBlueInfoAnswer(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_PAY_GET_TOKEN:
		PlayerManager::getInstance()->doPayGetTokenAnswer(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_BUY:
	case PROTOCOL_SUBCMD_TRANSIT_DELIVER:
	case PROTOCOL_SUBCMD_TRANSIT_BLUE_RENEW:
	case PROTOCOL_SUBCMD_TRANSIT_GET_BALANCE:
	case PROTOCOL_SUBCMD_TRANSIT_PAY:
	case PROTOCOL_SUBCMD_TRANSIT_GIFT_EXHANGE:
	case PROTOCOL_SUBCMD_TRANSIT_PER_ORDER:
		BuyGoodsManager::getInstance()->doTransitRequest(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_FRIEND_INFO:
		PlayerManager::getInstance()->doTencentFriendInfo(packet);
		break;
	}
	return true;
}

bool LogicManager::transToWorld(CNetPacket * packet) {
	return true;
}
