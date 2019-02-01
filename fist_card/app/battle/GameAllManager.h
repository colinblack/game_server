/*
 * GameAllManager.h
 *
 *  Created on: 2018年11月27日
 *      Author: colin
 */

#ifndef APP_BATTLE_GAMEALLMANAGER_H_
#define APP_BATTLE_GAMEALLMANAGER_H_

#include "GameBase.h"

//打boss
class GamePve : public GameBase, public CSingleton<GamePve>
{
private:
	friend class CSingleton<GamePve>;
	GamePve(){}

public:
	virtual void CallDestroy() { Destroy();}

	int GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message);
	int InitNpcItem(unsigned uid, unsigned battleid, unsigned id);

	void GameEnd(unsigned battleid);

	unsigned StageId(unsigned uid)
	{
		return stageid_[uid];
	}

	unsigned SaveStageId(unsigned uid, unsigned id)
	{
		stageid_[uid] = id;
	}
private:
	//pve结算
	int PveAccount(unsigned uid, bool attackerWin, unsigned stageId, vector<unsigned>& heroId, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoPveBattleResult* msg);

private:
	unordered_map<unsigned, unsigned> stageid_; //玩家通过关卡id
};

//排位赛
class GameGrade : public GameBase, public CSingleton<GameGrade>
{
private:
	friend class CSingleton<GameGrade>;
	GameGrade(){}

public:
	virtual void CallDestroy(){Destroy();}
	int GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message);
	void GameEnd(unsigned battleid);

	int InitOthItem(unsigned uid, unsigned battleid, bool isUser);
	//匹配玩家
	unsigned MatchUser(unsigned uid, unsigned grade, int& index);

	void SetUser(unsigned uid, unsigned othUid)
	{
		real_user_[uid] = othUid;
	}
	void SetRobot(unsigned uid, unsigned index)
	{
		robot_[uid] = index;
	}

private:
	unordered_map<unsigned, unsigned> real_user_;   //真玩家
	unordered_map<unsigned, unsigned> robot_;  //机器人
};

//随机挑战玩家
class GameRandom : public GameBase, public CSingleton<GameRandom>
{
private:
	friend class CSingleton<GameRandom>;
	GameRandom(){}

	//选定挑战玩家
	unsigned SelectUser(unsigned uid, set<unsigned>& users);
	int RandomUserReward(unsigned uid, unsigned enemyUid, CommonGiftConfig::CommonModifyItem& cfg);

public:
	virtual void CallDestory(){Destroy();}
	int GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message);
	void GameEnd(unsigned battleid);

	//刷新挑战的玩家
	unsigned RefreshUser(unsigned uid);

	void SetRandom(unsigned uid, unsigned id)
	{
		random_[uid] = id;
	}

	unsigned Revenge(unsigned uid)
	{
		return revenge_[uid];
	}

private:
	unordered_map<unsigned, unsigned> random_;
	unordered_map<unsigned, unsigned> revenge_;
};

//挑战好友
class GameFriend : public GameBase, public CSingleton<GameFriend>
{
private:
	friend class CSingleton<GameFriend>;
	GameFriend(){}
	//挑战好友奖励
	void FriendBattleReward(unsigned uid, bool attckerWin, vector<unsigned>& heros,
			CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoFriendBattleResult* msg);
private:
	enum FriendBattleType
	{
		e_friendbattle_win	= 1, //胜利
		e_friendbattle_lose	= 2, //失败

		e_friendbattle_max
	};

public:
	virtual void CallDestory(){Destroy();}
	int GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message);
	void GameEnd(unsigned battleid);


	void SetFriend(unsigned uid, unsigned othuid)
	{
		friend_[uid] = othuid;
	}

private:
	unordered_map<unsigned, unsigned> friend_;
};


struct MartialBattleInfo
{
	unsigned mymGrde; //我武馆星级
	unsigned othuid;  //对方id
	unsigned othmGrade; //对方武馆星级
	unsigned othCoins;	//对方武馆金币收益
	unsigned othProtectTs; //对方武馆保护时间
	vector<HeroAttrItem> othAttr;	//对方英雄属性
	map<unsigned, unsigned> othProps; //对方武馆道具收益

	MartialBattleInfo()
		: mymGrde(0)
		, othuid(0)
		, othmGrade(0)
		, othCoins(0)
		, othProtectTs(0)
	{
	}

	MartialBattleInfo(unsigned myGrade, unsigned otherUid, unsigned othGrade, unsigned coins,
						unsigned ts, vector<HeroAttrItem>& othAttr, map<unsigned, unsigned>& props)
		: mymGrde(myGrade)
		, othuid(otherUid)
		, othmGrade(othGrade)
		, othCoins(coins)
		, othProtectTs(ts)
		, othAttr(std::move(othAttr))
		, othProps(props)
	{
	}

	MartialBattleInfo& operator=(const MartialBattleInfo& obj)
	{
		if(&obj != this)
		{
			mymGrde 		= obj.mymGrde;
			othuid  		= obj.othuid;
			othmGrade 		= obj.othmGrade;
			othCoins 		= obj.othCoins;
			othProtectTs 	= obj.othProtectTs;
			othAttr 		= std::move(obj.othAttr);
			othProps 		= std::move(obj.othProps);
		}
		return *this;
	}
};

//踢馆
class GameMartialClub : public GameBase, public CSingleton<GameMartialClub>
{
private:
	friend class CSingleton<GameMartialClub>;
	GameMartialClub(){}
	//战报
	void BattleReport(unsigned battleid);
	//同步对方武馆信息
	int SynOthMartialInfo(unsigned battleid);

public:
	virtual void CallDestory(){Destroy();}
	int GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message);
	void GameEnd(unsigned battleid);
	//初始化玩家信息
	int InitUserItem(unsigned uid, unsigned grade, unsigned battleid);
	int InitOthItem(unsigned uid, unsigned battleid, vector<HeroAttrItem>& info);

	void SetMartialBattleInfo(unsigned uid, MartialBattleInfo& info)
	{
		info_[uid] = info;
	}

	map<unsigned, unsigned> GetMartialClubProp(vector<unsigned>&& in);

private:
	unordered_map<unsigned, MartialBattleInfo> info_;
};

//参加比赛信息
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


//杯赛
class GameChampionship : public GameBase, public CSingleton<GameChampionship>
{
private:
	friend class CSingleton<GameChampionship>;
	GameChampionship(){
		for(int i = 1; i <= CHAMPIONSHIP_NUM; ++i)
			free_index_.insert(i);
	};
	vector<int> RandomRobots();
	void Turn(list<unsigned>& cur, list<unsigned>& next);

public:
	virtual void CallDestroy(){Destroy();}
	int GameStart(unsigned uid, unsigned battleid, const ProtoBattle::BattleCommonCPP& req, Message* message);
	void GameEnd(unsigned battleid);
	int InitUserItem(unsigned uid, unsigned battleid, unsigned heroid);
	int InitNpcItem(unsigned uid, unsigned battleid, unsigned heroid);

	void AddUser(unsigned uid, unsigned coins, unsigned type, unsigned heroid)
	{
		match_user_.push_back(ApplyRecord(uid, coins, type, heroid));
	}

	int Apply();
	int Ready(unsigned mid);
	bool Start(unsigned mid);
	int Over(unsigned mid);

	//添加比赛
	int AddGame(unsigned attUid, unsigned attHero, unsigned defUid, unsigned defHero, unsigned& battleid);
	void GameProcess();

	bool IsValid(unsigned mid)
	{
		return match_start_.count(mid) == 0 ? false : true;
	}

	list<ApplyRecord>& GetPlayers(unsigned mid)
	{
		return match_map_[mid];
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
};

#endif /* APP_BATTLE_GAMEALLMANAGER_H_ */
