/*
 * LogicManager.h
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#ifndef LOGICMANAGER_H_
#define LOGICMANAGER_H_

#include "Kernel.h"
#include "ProtocolInc.h"
#include "EquipmentConfig.h"
#include "BuildingConfig.h"
#include "HeroConfig.h"
#include "ExpConfig.h"

class LogicManager {
public:
	static LogicManager* getInstance() {
		static LogicManager logicManager;
		return &logicManager;
	}
	~LogicManager();
private:
	LogicManager();
public:
	bool init();
	bool onExit();
	bool onReload();
	bool doPacket(CNetPacket* packet);
private:
	bool doTransfer(CNetPacket* packet);
	bool doLoginTransfer(CNetPacket* packet);
	bool doAccessAnswer(CNetPacket* packet);
	bool doBattleAnswer(CNetPacket* packet);
	bool doWorldAnswer(CNetPacket *packet);
	bool doAsyncDbAnswer(CNetPacket* packet);
	bool doTransitAnswer(CNetPacket* packet);
	bool doClientOffline(CNetPacket* packet);
	bool doHeartBeat(CNetPacket* packet);
	bool doAllianceBuilding(CNetPacket* packet);
	bool doAllServerAnswer(CNetPacket* packet);
public:
	void sendAll(CNetPacket *packet);
	bool sendToAccess(CNetPacket* pPacket);
	bool sendToBattle(CNetPacket* pPacket);
	bool sendToLogin(CNetPacket* pPacket);
	bool sendToAllServer(CNetPacket* packet);
	bool transToBattle(CNetPacket* pPacket);
	bool transToWorld(CNetPacket * packet);
	bool doAdmin(CNetPacket* packet);
	bool sendSystemMsg(uint32_t uid, const string& msg, ...);
private:
	bool clientProcess(CNetPacket* pPacket);
	bool offlineProcess(CNetPacket* packet, const string & reason);
	bool logicProcess(CNetPacket* pPacket);
	void doTimerProcess(CNetPacket* pPacket);
private:
	void onTimer();
	void onSecondTimer();
public:
	bool busiInit();
	bool configInit();
	bool sendServerTime(uint32_t uid);
	static uint32_t OpenDay() {
		return (GlobalTime + 86400 - OpenTs) / 86400;
	}
	static uint32_t NextDayTime();
public:
	static uint32_t GlobalTime;
	static uint32_t GlobalMilliTime;
	static uint64_t StartMilliTime;
	static uint32_t lastLoopTime;
	static uint32_t ServerId;
	static uint32_t OpenTs;
};

#endif /* LOGICMANAGER_H_ */
