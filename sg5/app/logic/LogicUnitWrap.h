/*
 * LogicUnitWrap.h
 *
 *  Created on: 2016-6-1
 *      Author: dawx62fac
 */

#ifndef LOGICUNITWRAP_H_
#define LOGICUNITWRAP_H_

#include "Kernel.h"
#include "DataInc.h"
#include "LogicUser.h"

class UserWrap
{
public:
	UserWrap(unsigned uid, bool isBase);

	void Save();  //

	unsigned Id() const; //Uid;
	unsigned VipLevel() const; //VIP等级
	unsigned TotalRecharge() const; //累计充值数
	unsigned RegisterTime() const;  //用户注册时间

	//校验序列ID和请求时间
	int CheckSession(unsigned lasttime, unsigned seqid, Json::Value& result);

	void AddGCBase(unsigned cnt, const std::string& reason, Json::Value& result); //能量单 免费发放的

	//设置国家，每一个用户只能设置一次
	void SetKingdom(unsigned kingdom, Json::Value& result);

	//获取指定时间段的充值积分
	int GetRechargePoint(const ActInfoConfig& config) const;
	unsigned GetRechargePoint(unsigned nStartTime, unsigned nEndTime) const;

	//判断时间范围内是否存在充值数大于等于N的
	bool IsHaveRechargeGoal(unsigned nStartTime, unsigned nEndTime, unsigned goal);

	//返回指定时间段内的，满足充值大于等于N的天数
	unsigned GetRechargeGoalDays(unsigned nStartTime, unsigned nEndTime, unsigned goal);

	//0--钻石，1--金币
	std::pair<unsigned, unsigned> GetCost(unsigned nStartTime, unsigned nEndTime) const;

	 //获取与参数同天时间的充值数
	unsigned GetSingleDayRecharge(unsigned day) const;

	 //获取与参数同天时间的消费数
	unsigned GetSingleDayConsume(unsigned day) const;

	//增加威望
	void AddProsper(int prosper, const std::string& reason, Json::Value& result);

	//增加经验
	void AddExp(int exp, const std::string& reason, Json::Value& result);

	//花费钻石或金币
	int CostAsset(int diamond, int coins, const std::string& reason, Json::Value& result);

	//增加钻石或金币
	void AddCashCoin(int cashs, int coins, const std::string& reason, Json::Value& result);

	//增加资源
	void AddResourceUniform(unsigned resource
			, const std::string& reason
			, Json::Value& result);
	void AddResource(unsigned r1, unsigned r2, unsigned r3, unsigned r4
			, const std::string& reason
			, Json::Value& result);

	void GetResource(map<unsigned, unsigned> & resource);
	void GetResourceMax(map<unsigned, unsigned> & resourcemax);

	//Stats 字段
	void SetUserStats(const Json::Value& stats);
	void GetUserStats(Json::Value& status) const;

	//Tech 字段
	void SetUserTech(const Json::Value& tech);
	void GetUserTech(Json::Value& tech) const;

	void GetUserGift();


	//////////////////////////////////////////////////////////////////////////

	int SetUserFlag(Json::Value & user_flag);
	
	int GetUserFlag(Json::Value &user_flag);
	
	//设置英雄训练队列
	int SetUserTrainQ(Json::Value & trainq);

	//获取英雄训练队列
	int GetUserTrainQ(Json::Value & trainq);

	//获取战魂
	unsigned GetBattleSpirits();

	//修改战魂
	void ChangeBattle(int battle, string reason);

	//增加器魂
	void AddWareSoul(int cnt, const std::string& op, Json::Value& result);

	void GetResource(Json::Value & result);
	//修改资源
	void ChangeResource(int r1, int r2, int r3, int r4, string reason, Json::Value & result);

	//获取威望
	unsigned GetProsper();

	//修改威望
	void ChangeProsper(int prosper, string reason, Json::Value & result);

	//能量增加
	unsigned GetEnergyBase();
	void AddEnergyBase(int gcbase, string reason, Json::Value & result);

	unsigned GetEnergyBuy();
	void AddEnergyBuy(int gcbuy, string reason, Json::Value & result);

	//获取用户等级
	int GetUserLevel();
	unsigned GetUserExp();

	//获取小兵研究
	void GetUserSoldierLevel(Json::Value & soldierlevel);

	//设置小兵研究
	void SetUserSoldierLevel(Json::Value & soldierlevel);

	//获取小兵训练队列
	void GetUserBarrackQ(Json::Value & barrackq);

	//设置小兵训练队列
	void SetUserBarrackQ(Json::Value & barrackq);

	//获取兵营
	void GetUserSoldier(Json::Value & soldier);

	//设置兵营
	void SetUserSoldier(Json::Value & soldier);

	//获取技能队列
	void GetUserSkillQ(Json::Value & skillq);

	//设置技能队列
	void SetUserSkillQ(Json::Value & skillq);

	void GetUserBuildQ(Json::Value & buildq);
	void SetUserBuildQ(Json::Value & buildq);
private:
	unsigned 	m_nUid;
	bool 		m_bBase; //获取用户基本信息的标志

	DataUser 	m_dataUser; //用户数据
};



#endif /* LOGICUNITWRAP_H_ */
