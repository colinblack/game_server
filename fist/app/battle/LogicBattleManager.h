/*
 * LogicBattleManager.h
 *
 *  Created on: 2018年7月12日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICBATTLEMANAGER_H_
#define APP_BATTLE_LOGICBATTLEMANAGER_H_

#include "ServerInc.h"
#include "BattleDemo.h"

class LogicBattleManager : public BattleSingleton, public CSingleton<LogicBattleManager>
{
private:
	friend class CSingleton<LogicBattleManager>;
	LogicBattleManager(){}
	enum BattleType
	{
		e_battletype_pve				=  0, //打副本
		e_battletype_grade				=  1, //排位赛
		e_battletype_grade_robot		=  2, //排位赛打假人
		e_battletype_random				=  3, //随机玩家
		e_battletype_revenge			=  4, //随机玩家复仇
		e_battletype_friend	 			=  5, //挑战玩家
		e_battletype_martial 			=  6, //踢馆
		e_battletype_championship		=  7, //杯赛
		e_battletype_championship_robot	=  8, //杯赛打假人

		e_battletype_max
	};

	enum FriendBattleType
	{
		e_friendbattle_win	= 1, //胜利
		e_friendbattle_lose	= 2, //失败

		e_friendbattle_max
	};

public:
	virtual void CallDestroy() { Destroy();}

	int FullMessage(unsigned uid, User::FriendInfo* msg);
	void GetFormation(unsigned uid, vector<unsigned>& heros);
	//设置阵型
	int Process(unsigned uid, ProtoBattle::SetFormationReq* req, ProtoBattle::SetFormationResp* resp);

	//pve战斗
	int Process(unsigned uid, ProtoBattle::ProtoPveBattleReq* req, ProtoBattle::ProtoPveBattleResp* resp);

	//排位赛匹配
	int Process(unsigned uid, ProtoBattle::ProtoMatchReq* req,  ProtoBattle::ProtoMatchResp* resp);
	//排位赛
	int Process(unsigned uid, ProtoBattle::ProtoGradeBattleReq* req, ProtoBattle::ProtoGradeBattleResp* resp);

	//排位晋级奖励
	int Process(unsigned uid, ProtoBattle::UpgradeRewardReq* req, ProtoBattle::UpgradeRewardResp* resp);

	//排位每日奖励
	int Process(unsigned uid, ProtoBattle::DailyRewardReq* req, ProtoBattle::DailRewardResp* resp);

	//连胜分享奖励
	int Process(unsigned uid, ProtoBattle::WinStreakRewardReq* req, ProtoBattle::WinStreakRewardResp* resp);

	//升级分享奖励
	int Process(unsigned uid, ProtoBattle::UpgradeShareRewardReq* req, ProtoBattle::UpgradeShareRewardResp* resp);

	//挑战随机玩家
	int Process(unsigned uid, ProtoBattle::ProtoRandomUserReq* req, ProtoBattle::ProtoRandomUserResp* resp);

	//随机玩家复仇
	int Process(unsigned uid, ProtoBattle::ProtoRevengeReq* req, ProtoBattle::ProtoRevengeResp* resp);

	//刷新挑战玩家
	int Process(unsigned uid, ProtoBattle::ProtoRefreshReq* req, ProtoBattle::ProtoRefreshResp* resp);

	//战报
	int Process(unsigned uid, ProtoBattle::ProtoPost* msg);

	//挑战好友
	int Process(unsigned uid, ProtoBattle::ProtoFriendBattleReq* req, ProtoBattle::ProtoFriendBattleResp* resp);

	//踢馆
	int Process(unsigned uid, ProtoBattle::ProtoMartialClubBattleReq* req);

	//跨服踢馆
	int Process(ProtoBattle::ProtoCSMartialClubBattleReq* req);

	//跨服踢馆结果
	int Process(ProtoBattle::ProtoCSBattleResultReq* req);

private:

	//开始战斗
	bool StartBattle(unsigned uid, BattleType type, ProtoBattle::BattleCommon* req, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg);

	//和假玩家战斗
	bool StartRobotBattle(unsigned uid, BattleType type, ProtoBattle::BattleCommon* req, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg);

	//玩家自己战斗前准备
	void UserBattleInit(unsigned uid, ProtoBattle::BattleCommon* req, vector<BattleDemoHero>& team, vector<BattleDemoItem>& item, CommonGiftConfig::CommonModifyItem& cfg);

	//pve结算
	int PveAccount(unsigned uid, bool attackerWin, unsigned stageId, vector<unsigned>& heroId, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoPveBattleResp* msg);

	//英雄战斗信息
	int SetBatttleHero(unsigned uid, unsigned heroId, vector<BattleDemoHero>& hero);

	//npc战斗信息
	int SetBattleNpc(unsigned npcId, unsigned npclv, vector<BattleDemoHero>& npc);

	//英雄属性
	void FullHeroAttr(int idx, BattleDemoHero& hero, HeroInfo& res);

	//刷新挑战的玩家
	unsigned RefreshUser(unsigned uid);

	//选定挑战玩家
	unsigned SelectUser(unsigned uid, set<unsigned>& users);

	//随机挑战玩家奖励
	int RandomUserReward(unsigned uid, unsigned enemyUid, CommonGiftConfig::CommonModifyItem& cfg);


	//挑战好友奖励
	void FriendBattleReward(unsigned uid, bool attckerWin, vector<unsigned>& heros, CommonGiftConfig::CommonModifyItem& cfg, ProtoBattle::ProtoFriendBattleResp* msg);

	//踢馆
	bool StartMartialBattle(unsigned uid, ProtoBattle::ProtoMartialClubBattleReq *req, BattleType type,
									CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg);
	//跨服踢馆
	bool StartMartialCSBattle(ProtoBattle::ProtoCSMartialClubBattleReq* req, BattleType type,
									CommonGiftConfig::CommonModifyItem& cfg, ProtoBattleDemo::ProtoBattleDemo& msg);
	void SetMartialBattleItem(unsigned uid, unsigned martialGrade, vector<BattleDemoHero>& battleDemo);

private:
	//阵型
	map<unsigned, vector<unsigned>> formation_;
	//排位赛匹配玩家
	map<unsigned, OfflineResourceItem> enemy_;
	//排位赛假玩家
	map<unsigned, int> grade_robot_;
	//随机玩家信息
	map<unsigned, OfflineResourceItem> random_;
	//随机玩家复仇 userid=>enemyid
	map<unsigned, unsigned> revenge_;
	//随机npc
	map<unsigned, int> npc_;
	//好友
	map<unsigned, OfflineResourceItem> friend_;
};


#endif /* APP_BATTLE_LOGICBATTLEMANAGER_H_ */
