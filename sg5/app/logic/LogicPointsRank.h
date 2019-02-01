/*
 * LogicPointRank.h
 *
 *  Created on: 2012-10-17
 *      Author: Administrator
 */

#ifndef LOGICPOINTRANK_H_
#define LOGICPOINTRANK_H_
#include "LogicInc.h"
class CLogicPointsRank {
public:
	CLogicPointsRank();
	virtual ~CLogicPointsRank();
	static CDataPointsRank* GetPointsRankData();
	int GetPointsRank(int unsigned uid, DataPoints vecPoints[]);
	int GetPointsRankJson(int unsigned uid, Json::Value &result);
	int UpdatePointsRank(int unsigned uid, const DataPoints &points);
	int RewardPointRank(void);
	int CleanRankList(void);

	//砸罐子跨服排行榜
	static CDataPointsRankAllServer* GetPointsRankAllServerData();
	int SetUser(int unsigned uid, unsigned pointsDay, unsigned pointsAll, string& name, unsigned& need);
	int ReplyUser(unsigned uid, unsigned pointsDay, unsigned pointsAll, string& name, Json::Value &result);
	int GetList(unsigned uid, Json::Value &result);
	int ReplyList(unsigned uid, Json::Value &result);
};
#endif /* LOGICPOINTRANK_H_ */
