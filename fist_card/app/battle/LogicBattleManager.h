/*
 * LogicBattleManager.h
 *
 *  Created on: 2018年7月12日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICBATTLEMANAGER_H_
#define APP_BATTLE_LOGICBATTLEMANAGER_H_

#include "ServerInc.h"
#include "GameAllManager.h"

class LogicBattleManager : public BattleSingleton, public CSingleton<LogicBattleManager>
{
private:
	friend class CSingleton<LogicBattleManager>;
	LogicBattleManager(){}
	struct RobotBattleItem
	{
		unsigned id;	//战斗id
		unsigned type;	//战斗类型

		RobotBattleItem(unsigned battleid, unsigned t) :id(battleid), type(t){}
	};

public:
	virtual void CallDestroy();
	virtual int OnInit();
	virtual void OnTimer1();

	//设置阵型
	int Process(unsigned uid, ProtoBattle::SetFormationReq* req, ProtoBattle::SetFormationResp* resp);
	//战斗
	int Process(unsigned uid, ProtoBattleBase::ProtoBattleReq* req, ProtoBattleBase::ProtoBattleResp* resp);
	//结束回合
	int Process(unsigned uid, ProtoBattle::ProtoTurnEndReq* req, ProtoBattle::ProtoTurnEndResp* resp);
	//pve战斗
	int Process(unsigned uid, ProtoBattle::ProtoPveBattleReq* req, ProtoBattle::ProtoPveBattleResp* resp);
	//排位赛匹配
	int Process(unsigned uid, ProtoBattle::ProtoMatchReq* req,  ProtoBattle::ProtoMatchResp* resp);
	//排位赛
	int Process(unsigned uid, ProtoBattle::ProtoGradeBattleReq* req, ProtoBattle::ProtoGradeBattleResp* resp);
	//刷新挑战玩家
	int Process(unsigned uid, ProtoBattle::ProtoRefreshReq* req, ProtoBattle::ProtoRefreshResp* resp);
	//挑战随机玩家
	int Process(unsigned uid, ProtoBattle::ProtoRandomUserReq* req, ProtoBattle::ProtoRandomUserResp* resp);
	//随机玩家复仇
	int Process(unsigned uid, ProtoBattle::ProtoRevengeReq* req, ProtoBattle::ProtoRevengeResp* resp);
	//挑战好友
	int Process(unsigned uid, ProtoBattle::ProtoFriendBattleReq* req, ProtoBattle::ProtoFriendBattleResp* resp);
	//踢馆
	int Process(unsigned uid, ProtoBattle::ProtoMartialClubBattleReq* req);
	//跨服踢馆, 从othuid所在服务器获取信息
	int Process(ProtoBattle::ProtoCSMartialClubBattleReq* req);
	//跨服踢馆, 开始比赛
	int Process(ProtoBattle::ProtoCSMartialClubBattleResp* req);
	//跨服踢馆同步武馆信息
	int Process(ProtoBattle::ProtoCSSynOthMartialInfo* req);
	//排位晋级奖励
	int Process(unsigned uid, ProtoBattle::UpgradeRewardReq* req, ProtoBattle::UpgradeRewardResp* resp);
	//排位每日奖励
	int Process(unsigned uid, ProtoBattle::DailyRewardReq* req, ProtoBattle::DailRewardResp* resp);
	//连胜分享奖励
	int Process(unsigned uid, ProtoBattle::WinStreakRewardReq* req, ProtoBattle::WinStreakRewardResp* resp);
	//升级分享奖励
	int Process(unsigned uid, ProtoBattle::UpgradeShareRewardReq* req, ProtoBattle::UpgradeShareRewardResp* resp);
	//战报
	int Process(unsigned uid, ProtoBattle::ProtoPost* msg);
	int FullMessage(unsigned uid, User::FriendInfo* msg);

	//获取阵型
	vector<unsigned>& GetFormation(unsigned uid)
	{
		return formation_[uid];
	}

	void AddRobot(unsigned battleid, unsigned type)
	{
		robot_.push_back(RobotBattleItem(battleid, type));
	}

	GameBase* GetGames(unsigned type)
	{
		if(games_.count(type) == 0 )
			return nullptr;
		return games_[type];
	}

private:
	//阵型
	map<unsigned, vector<unsigned>> formation_;
	unordered_map<unsigned, GameBase*> games_;
	deque<RobotBattleItem> robot_;
};


#endif /* APP_BATTLE_LOGICBATTLEMANAGER_H_ */
