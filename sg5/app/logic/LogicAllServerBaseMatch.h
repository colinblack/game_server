#ifndef _LOGIC_ALL_SERVER_BASE_MATCH_H_
#define _LOGIC_ALL_SERVER_BASE_MATCH_H_

#include "LogicInc.h"

class CLogicAllServerBaseMatch
{
public:
	static CDataAllServerBaseMatch* GetAllServerCDataBaseMatch();

	int GetBaseMatchInfo(unsigned aid, unsigned uid, Json::Value &data);
	int Apply(unsigned uid);
	int ReportResult(unsigned uid, int order, int damage);
	bool IsBaseMatchProtect(unsigned aid, unsigned uid);
	int GetApplyPlayers(unsigned aid, Json::Value &result);
	int GetRegularScore(unsigned aid, Json::Value &result);
	int Load(unsigned instid, unsigned uidBy, Json::Value &result);
	int Save(unsigned instid, DataUser &userBy, Json::Value &data, Json::Value &result, LoadType loadtype);
	int GetStage(int& stage);
	int RequestBaseMatch(const string &url, Json::Value &data, string cgi=CONFIG_ALLS_MATCH_SERVER_PATH, bool allserverrank=false);
};

#endif
