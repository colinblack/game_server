/*
 * CarbonManager.h
 *
 *  Created on: 2013-5-13
 *      Author: lucky
 */

#ifndef CARBON_MANAGER_H_
#define CARBON_MANAGER_H_

#include "BattleBaseInc.h"
#include "Human.h"
#include "StdMonster.h"
#include "CarbonBase.h"

class CarbonManager: public CSingleton<CarbonManager> {
private:
	friend class CSingleton<CarbonManager> ;
	CarbonManager() {
	}
public:
	virtual ~CarbonManager() {
	}
	bool init();

public:
	CarbonBase* createCarbon(uint32_t type);
	CarbonBase* getCarbon(uint32_t entityId);
	bool addCarbon(uint32_t fbid, Human *pHuman);
	bool delCarbon(uint32_t entityId);
	bool enterCarbon(Human *pHuman, uint32_t fbid);
	bool leaveCarbon(uint32_t teamId, Human *pHuman);
	bool actorOffLine(Human *pHuman);
	bool actorLogin(uint32_t uid);
	bool actorQuitTeam(uint32_t teamId, Human *pHuman);
	bool actorJoinTeam(Human *pHuman);
	bool canAddCarbon(uint32_t fbId, Human *pHuman);
	bool onSecondTimer();
	bool canEnterCarbon(uint32_t fbId, Human *pHuman);
	bool canHumanEnterCarbon(uint32_t fbId, Human *pHuman);
	bool isEnterTimesEnough(int32_t fbId, Human *pHuman);
	bool onLogin(unsigned rid);
	bool doBuyEnterTimes(Human *pHuman, int32_t fubenId);
	bool onCarbonResult(uint32_t fbId, uint32_t mapId, bool win);
	bool onMapMoveObjectDie(MapMoveObject *pMo);
	uint32_t getCarbonTimes(uint32_t uid, byte fbId);

private:
	map<uint32_t, CarbonBase*> m_mapCarbon;							// map<fbInstanceId, CarbonBase*>

};

#endif /* CARBON_MANAGER_H_ */
