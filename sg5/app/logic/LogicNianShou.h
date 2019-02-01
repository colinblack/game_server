#ifndef _LOGIC_NIAN_SHOU_H_
#define _LOGIC_NIAN_SHOU_H_

#include "LogicInc.h"

class CLogicNianShou
{
public:
	static int GetNianShouArchive(unsigned bossId, Json::Value &data);
	static CDataNianShou* GetCDataNianShou();

	int GetNianShouInfo(unsigned uid, Json::Value &data, unsigned bossid, unsigned rewardid);
	int Load(unsigned bossId, unsigned uidBy, Json::Value &result);
	int Save(unsigned bossId, DataUser &userBy, Json::Value &data, Json::Value &result, LoadType loadtype);
	int ViewNianShou(unsigned uid, unsigned bossId, Json::Value &data);

	int ExportNianShouData(unsigned uid, unsigned bossId, const string &dir);

private:
	void rewardNianShou(unsigned uid, int bossId,unsigned damage,const vector<NianShouChallenger>& top,
			const NianShouChallenger &last);
};

#endif
