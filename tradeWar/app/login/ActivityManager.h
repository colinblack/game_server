/*
 * ActivityManager.h
 *
 *  Created on: 2018年12月3日
 *      Author: Administrator
 */

#ifndef ACTIVITY_MANAGER_H_
#define ACTIVITY_MANAGER_H_

#include "IManager.h"
#include "ActivityUtil.h"

class ActivityManager: public IManager {
public:
	enum {
		ACT_RET_SUCESS = 0,
		ACT_RET_FAIL = 1
	};
	ActivityManager();
	virtual ~ActivityManager();
	bool onLogin();
	bool onCharge();
	bool onReload();
	bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool onTimer();
	bool addSoldier(uint32_t v);
	bool addExp(uint32_t v, int chg);
	bool addPower(uint32_t v, int chg);
	bool addGem(uint32_t v);
	bool addConsume(uint32_t v);
	bool addTransport(uint32_t v);
	bool addCoins(uint32_t v);
	bool addArena(uint32_t v);
	bool addSoldierScore(uint32_t v);
	bool addZhengWu(uint32_t v);
	bool addBuildingUp(uint32_t v);
	bool addBoss(uint32_t v);
	bool addDefendGate(uint32_t v);
	bool addBattleGate(uint32_t v);
	bool addTaskCount(uint32_t quest, uint32_t cnt);
	bool setBuyFlag();
	static bool sendAllData(uint32_t uid, const set<uint32_t> &ids);
protected:
	bool doGetData(CNetPacket *packet);
	bool doReward(CNetPacket *packet);
	bool doAddCount(CNetPacket *packet);
	bool doBuyScore(CNetPacket *packet);
	bool doQuestReward(CNetPacket *packet);
	bool doLevelReward(CNetPacket *packet);
	bool doLottery(CNetPacket *packet);
	bool doGetAllData(CNetPacket *packet);
	bool sendData(uint32_t id);
	ActivityUtil* loadActivity(uint32_t id);
private:
	map<uint32_t, ActivityUtil*> m_data;
	vector<uint32_t> m_charge_act;
};

#endif /* ACTIVITY_MANAGER_H_ */
