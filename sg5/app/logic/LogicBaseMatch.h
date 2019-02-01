#ifndef _LOGIC_BASE_MATCH_H_
#define _LOGIC_BASE_MATCH_H_

#include "LogicInc.h"

class CLogicBaseMatch
{
public:
	static CDataBaseMatch* GetCDataBaseMatch();

	int GetBaseMatchInfo(unsigned aid, unsigned uid, Json::Value &data);
	int Apply(unsigned uid);
	int ReportResult(unsigned uid, int order, int damage);
	bool IsBaseMatchProtect(unsigned aid, unsigned uid);
	int GetApplyPlayers(unsigned aid, Json::Value &result);
	int GetRegularScore(unsigned aid, Json::Value &result);
	int Load(unsigned instid, unsigned uidBy, Json::Value &result);
	int Save(unsigned instid, DataUser &userBy, Json::Value &data, Json::Value &result, LoadType loadtype);
	int GetStage(int& stage);
};

#endif
