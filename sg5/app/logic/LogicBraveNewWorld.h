/*
 * LogicBraveNewWorld.h
 *
 *  Created on: 2017-2-14
 *      Author: Ralf
 */

#ifndef LOGICBRAVENEWWORLD_H_
#define LOGICBRAVENEWWORLD_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicBraveNewWorld : public LogicBase<CDataBraveNewWorld>
{
public:
	CLogicBraveNewWorld(){}
	~CLogicBraveNewWorld(){}

	void CheckVersion();
	int GetSelf(unsigned uid, unsigned aid, unsigned lv, Json::Value &result);
	int GetMissionInfo(unsigned uid, Json::Value &result);
	int GetPoints(vector<BraveNewWorldPoint>& p, Json::Value &result);
	int GetOnePoint(BraveNewWorldPoint& p, Json::Value &result);
	int GetPointsLimit(vector<BraveNewWorldPoint>& p, Json::Value &result);
	int GetZones(vector<unsigned>& z, Json::Value &result);
	int GetHistory(unsigned uid, Json::Value &result);
	int GetFavourate(unsigned uid, Json::Value &result);
	int Collect(unsigned uid, unsigned seq, Json::Value &result);
	int StartAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result);
	int EndAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, vector<unsigned>& hp, Json::Value &result);
	int FastAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, bool cash1, Json::Value &result);
	int Move(unsigned uid, unsigned seq, BraveNewWorldPoint& p, unsigned ud, bool super, Json::Value &result);
	int Build(unsigned uid, unsigned seq, unsigned cash, BraveNewWorldPoint& p, Json::Value &result);
	int Defend(unsigned uid, unsigned seq, bool cash, BraveNewWorldPoint& p, unsigned hero, Json::Value &result);
	int RecoverPoint(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result);
	int RevcoverUser(unsigned uid, unsigned seq, bool cash, Json::Value &result);
	int Discard(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result);
	int JoinAlliance(unsigned uid, unsigned userid, unsigned aid, Json::Value &result);
	int SetFavourate(unsigned uid, unsigned seq, vector<BraveNewWorldPoint>& p, Json::Value &result);
	int Buy_hts(unsigned uid, unsigned seq, Json::Value &result);
	int Buy_bts(unsigned uid, unsigned seq, Json::Value &result);
	int Buy_bt(unsigned uid, unsigned seq, unsigned count, Json::Value &result);
	int CollectOne(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result);
	int AttackSelf(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result);
	int GetMission(unsigned uid, unsigned seq, unsigned type, Json::Value &result);
	int newWorldAwards(unsigned uid, unsigned index,  unsigned id, unsigned seq, Json::Value &result);
	int GetTarget(unsigned uid, unsigned userid, Json::Value &result);
	int getNewWorldBoss(Json::Value &result);
	int GetChongBangRank(unsigned uid, Json::Value & result);
    int MoBaiChongBangWangZhe(unsigned uid, unsigned chongbangid, unsigned uid2, unsigned seq, Json::Value & result);
    int GetKuaFuFengHuoRank(unsigned uid, Json::Value & result);
    static int GetRankName(unsigned uid, string &n);
private:
    static map<unsigned, string> m_rank_name;
};



#endif /* LOGICBRAVENEWWORLD_H_ */
