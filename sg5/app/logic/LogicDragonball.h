#ifndef _LOGIC_DRAGONBALL_H_
#define _LOGIC_DRAGONBALL_H_

#include "LogicInc.h"

enum DragonballActivityStatus
{
	DragonballActivityStatus_none 	= 0,
	DragonballActivityStatus_attack = 1,
	DragonballActivityStatus_show 	= 2,

	DragonballActivityStatus_max,
};

class CLogicDragonball
{
public:
	int WhichDragonballHold(unsigned uid, unsigned &ballId, unsigned &ts, DragonballActivityStatus flag = DragonballActivityStatus_max);
	int GetDragonballs(Json::Value &data);
	int ViewAllDragonball(DragonballData &balls);
	bool EnableAttackForDragonball(unsigned ballid, unsigned level);
	int SnatchDragonball(unsigned ballid, unsigned snatchUid, string &snatchName,unsigned &preUid);
	int GetAllianceDragons(map<unsigned,AllianceBall>& allianceBalls);
	int PayAlliance(AllianceBall& aBall);
	int SetAlliance(AllianceBall& aBall);
	int ResetAlliance();
	DragonballActivityStatus IsDragonballActivityTs(void);
protected:
	CDataDragonball* GetCDataDragonball();
	static Json::Value m_ConfigValue;
	static bool m_bInit;
};

#endif
