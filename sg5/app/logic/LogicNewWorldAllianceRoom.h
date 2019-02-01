/*
 * LogicNewWorldAllianceRoom.h
 *
 *  Created on: 2014-9-18
 *      Author: Ralf
 */

#ifndef LOGICNEWWORLDALLIANCEROOM_H_
#define LOGICNEWWORLDALLIANCEROOM_H_

#include "LogicInc.h"
#include "LogicBase.h"
class CLogicNewWorldAllianceRoom  : public LogicBase<CDataNewWorldAllianceRoom> {
public:
	CLogicNewWorldAllianceRoom();
	virtual ~CLogicNewWorldAllianceRoom();

	int GetWorld(unsigned rid, Json::Value &allresult);
	int GetCity(unsigned rid, unsigned cid, Json::Value &allresult);
	int GetBattle(unsigned rid, unsigned cid, Json::Value &allresult);
	int GetBattleList(unsigned rid, unsigned cid, unsigned camp, Json::Value &allresult);
	int GetHero(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult);
	int GetAllHero(unsigned rid, unsigned uid, Json::Value &allresult);
	int SetHero(unsigned rid, unsigned uid, unsigned index, const Json::Value &para, Json::Value &allresult, unsigned &seq);

	int Move(unsigned rid, unsigned uid, unsigned index, unsigned cid, bool leave, unsigned fly, Json::Value &allresult, unsigned &seq);
	int Change(unsigned rid, unsigned uid, unsigned index, unsigned type, Json::Value &allresult, unsigned &seq);
	int Clone(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult, unsigned &seq);
	int Rush(unsigned rid, unsigned uid, unsigned index, bool fly, Json::Value &allresult, unsigned &seq);
	int Recover(unsigned rid, unsigned uid, unsigned index, unsigned num, Json::Value &allresult, unsigned &seq);
	int Explode(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult, unsigned &seq);

	int CollectOther(unsigned rid, unsigned uid, unsigned index, Json::Value &allresultk, unsigned &seq);
	int Blink(unsigned rid, unsigned uid, unsigned cid, const Json::Value &freeHeroIndex, Json::Value &allresult, const Json::Value &seq);

	int Buildyjt(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult, unsigned &seq);
};


#endif /* LOGICNEWWORLDALLIANCEROOM_H_ */
