/*
 * LogicChampionshipManager.h
 *
 *  Created on: 2018年10月9日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICCHAMPIONSHIPMANAGER_H_
#define APP_BATTLE_LOGICCHAMPIONSHIPMANAGER_H_

#include "ServerInc.h"



class LogicChampionshipManager : public BattleSingleton, public CSingleton<LogicChampionshipManager>
{
private:
	struct ApplyRecord{
		unsigned uid;
		int coins;
		unsigned type;
		unsigned heroid;

		ApplyRecord(unsigned nUid, int nCoins, unsigned nType, unsigned nHeroid)
					: uid(nUid), coins(nCoins), type(nType), heroid(nHeroid)
		{
		}
	};

private:
	friend class CSingleton<LogicChampionshipManager>;

public:
	virtual void CallDestroy() { Destroy();}
	void OnTimer1();
	int OnInit()
	{
		for(int i = 1; i <= MEMORY_CHAMPIONSHIP_NUM; ++i)
			free_index_.insert(i);

		timer_cnt_ = 0;

		return R_SUCCESS;
	}

	//参加比赛
	int Process(unsigned uid, ProtoChampionship::ProtoJoinInMatchReq* req, ProtoChampionship::ProtoJoinInMatchResp* resp);
	//开始战斗
	int Process(unsigned uid, ProtoChampionship::ProtoStartBattleReq* req);


private:
	void AddUser(unsigned uid, unsigned coins, unsigned type, unsigned heroid)
	{
		match_user_.push_back(ApplyRecord(uid, coins, type, heroid));
	}

	unsigned GetFreeIndex()
	{
		if(free_index_.empty())
			return (unsigned)-1;

		return *(free_index_.begin());
	}

	unsigned CreateMatch()
	{
		unsigned i = GetFreeIndex();
		if(i == (unsigned)-1)
		{
			error_log("free index is empty");
			return (unsigned)-1;
		}
		free_index_.erase(i);
		return i;
	}

	void Clear(unsigned mid)
	{
		free_index_.insert(mid);
		rewards_.erase(mid);
	}

	vector<int> RandomRobots();

	//参加比赛
	int Apply();
	//预备
	int Ready(unsigned mid);

	//开始
	int Start(unsigned mid);

	//结束
	int Over(unsigned mid);

	//添加比赛
	int AddGame(unsigned attUid, unsigned attHero, unsigned defUid, unsigned defHero, unsigned& battleid);
	void GameProcess();
	void Turn(list<unsigned>& cur, list<unsigned>& next);


	//随机产生比赛机器人
	void RandomRobots(unsigned mid);

	void SetMessage(unsigned uid, unsigned battleid, unsigned heroid , ProtoChampionship::MatchUserInfoCPP* msg);

	int StartChampionship(unsigned battleid);
	int SatrtRobotBattle(unsigned battleid);

	int InitUserItem(unsigned uid, unsigned battleid, unsigned heroid);

	int InitNpcItem(unsigned uid, unsigned battleid, unsigned heroid);

	PlayerItem& GetData(unsigned uid, unsigned mid);

private:
	//每场杯赛对应的比赛集合 mid=>set
	deque<ApplyRecord> match_user_; //参加比赛所有的玩家队
	unordered_map<unsigned, list<ApplyRecord>> match_map_;//不同种类的杯赛的玩家
	unordered_map<unsigned, list<unsigned>> match_start_; //已经开始的比赛队列 mid=>battleid
	unordered_map<unsigned, int> rewards_;  //奖励(金币数)

	list<unsigned> turn_1_; //打到第一轮的比赛
	list<unsigned> turn_2_; //打到第二轮的比赛
	list<unsigned> turn_3_; //打到第三轮的比赛
	set<unsigned> free_index_;	//能用的索引
	unsigned timer_cnt_; //计时
};

#endif /* APP_BATTLE_LOGICCHAMPIONSHIPMANAGER_H_ */
