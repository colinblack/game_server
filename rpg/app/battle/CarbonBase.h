/*
 * CarbonBase.h
 *
 *  Created on: 2013-5-13
 *      Author: lucky
 */

#ifndef CARBON_BASE_H_
#define CARBON_BASE_H_

#include "BattleBaseInc.h"
#include "Human.h"

class CarbonBase {
public:
	CarbonBase();
	virtual ~CarbonBase();

public:
	virtual bool init(uint32_t fbId);
	virtual bool canEnterCarbon(Human *pHuman);
	virtual bool canAddCarbon(Human *pHuman);
	virtual bool enterCarbon(Human *pHuman);
	virtual bool leaveCarbon(Human *pHuman);
	virtual bool isEmpty();
	virtual bool addNewMonster();
	virtual bool getFromPos(uint32_t uid, Point &fromPoint);
	virtual bool actorLogin(Human *pHuman);
	virtual bool actorOffLine(Human *pHuman);
	virtual bool actorQuitTeam(uint32_t teamId, Human *pHuman);
	virtual bool actorJoinTeam(Human *pHuman);
	virtual bool doDestory();
	virtual bool doExit(Human *pHuman);
	virtual bool onSecondTimer();
	virtual bool onExit(Human *pHuman);
	virtual bool onDestory();
	virtual bool isTeamEmpty(uint32_t teamId);

public:
	bool isEverInCarbon(uint32_t rid) {
		return find(m_vecHumansEverIn.begin(), m_vecHumansEverIn.end(), rid) != m_vecHumansEverIn.end();
	}
	const vector<uint32_t> &getHumans() {
		return m_vecHumans;
	}
	uint32_t getCarbonId() {
		return m_carbonId;
	}
	uint32_t getMapId() {
		return m_mapId;
	}
	bool canRemove() {
		return m_vecHumans.empty();
	}

protected:
	uint16_t m_offlineActorCount;                    // 副本中途下线玩家数目
	uint32_t m_createTime;                           // 副本创建时间
	uint32_t m_carbonId;                             // 副本实例ID
	uint32_t m_mapId;
	uint32_t m_monsterIndex;
	vector<uint32_t> m_vecHumans;                    // 副本中玩家
	vector<uint32_t> m_vecHumansEverIn;              // 曾经进入过副本的玩家
	map<uint32_t, Point> m_mapFromPos;
};

#endif /* CARBON_BASE_H_ */
