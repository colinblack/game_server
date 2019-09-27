/*
 * SoldierManager.h
 *
 *  Created on: 2016年5月11日
 *      Author: asdf
 */

#ifndef SOLDIERMANAGER_H_
#define SOLDIERMANAGER_H_

#include "Soldier.h"
#include "DataSoldier.h"
#include "ProtocolInc.h"
#include "Award.h"

class Player;
class SoldierManager {
public:
	SoldierManager();
	~SoldierManager();
public:
	bool doPacket(CNetPacket* packet);
	bool doQuerySoldierList(CNetPacket* packet);
	bool doSoldierUpgrade(CNetPacket* packet);
	bool doSoldierUpgradeFinishNow(CNetPacket* packet);
	bool doSoldierTrain(CNetPacket* packet);
	bool doSoldierTrainFast(CNetPacket* packet);
	bool doSoldierTrainFinishNow(CNetPacket* packet);
	bool doSoldierTrainList(CNetPacket* packet);
	bool doSoldierTrainSlotOpen(CNetPacket* packet);
	bool doSoldierStationQuery(CNetPacket* packet);
	bool doSoldierAllianceStationQuery(CNetPacket *packet);
	bool doSoldierStation(CNetPacket *packet);
	bool doSoldierStationDel(CNetPacket *packet);
	bool doSoldierAllianceStationAdd(CNetPacket *packet);
	bool doSoldierStrong(CNetPacket *packet);
	bool doSoldierStar(CNetPacket *packet);
	bool doSoldierSell(CNetPacket *packet);
	bool doBoxScore(CNetPacket *packet);
	bool doBoxReward(CNetPacket *packet);
	bool load(uint32_t uid);
	bool setSoldierData(vector<DataSoldier>& dh);
	bool setOneSoldier(uint32_t uid, uint32_t soldierUd, const string& data);
	bool addOneSoldier(uint32_t uid, uint32_t id, uint32_t count, const string& reason);
	bool unlockSoldier(uint32_t uid, uint32_t type);
	bool upgradeSoldier(uint32_t uid, uint32_t type);
	bool autoUnlockSoldier(uint32_t uid, uint32_t lv);
	bool existSoldier(uint32_t type);
	bool getSpawnSoldier(vector<pair<uint32_t, uint32_t> >& vSoldier);
	bool packInfo(IBuffer *buff);
	map<uint32_t, Soldier*>& getSoldier() {
		return m_soldiers;
	}
	Soldier* getSoldierByType(uint32_t type);
	Soldier* getSoldierByUd(uint32_t ud);
	uint32_t getSoldierCapacity();
	uint32_t getSoldierCount();
	void setPlayer(Player* player) {
		m_player = player;
	}
	bool onSoldierStarReward(uint32_t count, Award &award);
	uint32_t getInvalidCount(uint32_t type);
	bool onSoldierSell(byte ret);
	bool onBoxReward(byte ret);
	uint32_t calcStarCombat(uint32_t type, uint32_t f, uint32_t t);
	uint32_t calcLevelCombat(uint32_t color, uint32_t lv);
public:
	bool sendSoldierList();
	bool sendSoldierInfo(uint32_t ud);
public:
	bool checkSoldierNum(uint32_t type, uint32_t level, uint32_t count = 0);
private:
	void release();
private:
	Player* m_player;
	map<uint32_t, Soldier*> m_soldiers;
	uint32_t m_maxUd;
};

#endif /* SOLDIERMANAGER_H_ */
