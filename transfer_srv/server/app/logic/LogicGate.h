/*
 * LogicGate.h
 *
 *  Created on: 2011-7-13
 *      Author: auto
 */

#ifndef __LOGIC_GATE_H__
#define __LOGIC_GATE_H__

#include "LogicInc.h"
#include <math.h>

#define BASE_SCORE 10000 // 每关基础分
#define LOSE_SCORE_ONE_GATE 1000 // 每关基础分
#define LOST_SCORE_BY_RESOURE 600 // 资源损失分
#define LOST_SCORE_BY_TIME 1 // 时间损失系数


#define MAX_RANK_COUNT 11 // 每关排行榜数量
#define GOBAL_RANK_COUNT 3// 全球排行的占几名
#define MAX_GATES 90
#define ONE_LEVEL_GATES 30 // 每级建筑有多少个关卡
#define BUY_DARE_TIMES_PER_GOLD -20 // 购买一次挑战次数需要多少钱
#define BUY_DARE_TIMES_PER_COUNT 5 // 购买一次挑战次数可以增加多少次
#define GATA_LEVEL_MAX 150

class CLogicGate
{
public:
	struct GataConfig
	{
		int cap; // 容量
		int r1;
		int r2;
		int r3;
		int r4;
		int gold;
		int baseid;

		void Clone(GataConfig& config) const
		{
			config.cap = cap;
			config.r1 = r1;
			config.r2 = r2;
			config.r3 = r3;
			config.r4 = r4;
			config.gold = gold;
			config.baseid = baseid;;
		}

		// 衰减
		void Reduce(int wintimes, double winRate, int level)
		{
			double reduceValue = pow(0.5, wintimes)*winRate;
			r1 *= reduceValue;
			r2 *= reduceValue;
			r3 *= reduceValue;
			r4 *= reduceValue;
			gold *= reduceValue;

			// const GataConfig& config = GetConfig(level);
			// if (config.)
		}
	};

public:

	int ActiveNewLevel(unsigned uid, int level, int buildingLevel, DataGate& data);
	int ResetStatus(unsigned uid, int level);
	int AddTimes(unsigned uid, int& timeleft, int& usecach);
	int GetGateRank(unsigned uid, int level, vector<DataRank>& outRankList); // 获得排名

	int AddGate(unsigned uid, const DataGate &data);
	int UpdateGate(DataGate &Gate);
	int GetGate(unsigned uid, int level, DataGate &gate);
	int GetGates(unsigned uid, vector<DataGate>& gates); // 获得关卡信息. 如果没有关卡. 会默认创建第一关

	int GetJsonGates(unsigned uid, Json::Value& result);


	int BeginGate(unsigned uid, int level, DataGate& data, int& timeleft);
	int UpdateGating(unsigned uid, int level, int useTime, int useResource, DataGate& data);
	int EndGate(unsigned uid, int level, int useTime, int useResource, int iswin, DataGate& data,
			int& hasNewGate, DataGate& newgate, GataConfig &reward, int buildingLevel);

	int RestartGate(unsigned uid, int level, DataGate& data);

public:
	int CreateGate(unsigned uid, int lastLevel, DataGate &data, int buildingLevel);

	static const GataConfig& GetConfig(int level);

	static void GetRewardJson(GataConfig& data, Json::Value& result);
	static void GetGateJson(DataGate& data, Json::Value& result);
	static void GetGateRankJson(DataRank& data, Json::Value& result);

	typedef vector<DataRank> VRankOfLvl;
	static const VRankOfLvl& GetGateRankOfLevel(int level);
	static int GetGateRankl(unsigned uid, int level);
public:
	static const GataConfig s_configs[MAX_GATES];
	static VRankOfLvl gateRanks[GATA_LEVEL_MAX];


private:
	static bool CheckLevel(int lastLevel, int buildingLevel);
	static bool IsLevelMax(int lastLevel);
	static int ResetGate(DataGate& data);

	// 闯关结束跟开始闯关前. 计算损失分.
	static int CaleLoseScore(DataGate& data);
	static int CaleBestScore(DataGate& data);

	int ReduceOneTime(unsigned uid, int& timeleft);

	int ActiveNewGate(unsigned uid, int level, DataGate& data, int buildingLevel);
	int IsGateExist(unsigned uid, int level);
};

#endif /* __LOGIC_GATE_H__ */
