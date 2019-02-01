/*
 * LogicActionManager.h
 *
 *  Created on: 2018年12月4日
 *      Author: colin
 */

#ifndef APP_BATTLE_LOGICACTIONMANAGER_H_
#define APP_BATTLE_LOGICACTIONMANAGER_H_
#include "ServerInc.h"

class LogicActionManager : public BattleSingleton, public CSingleton<LogicActionManager>
{
private:
	friend class CSingleton<LogicActionManager>;
	LogicActionManager(){};

public:
	virtual void CallDestroy() { Destroy();}
	virtual int OnInit();
	void Register();

	typedef google::protobuf::RepeatedPtrField<ProtoBattleBase::ProtoBattleInfo> BattleInfoPtr;
	int Process(unsigned battleid, unsigned cardid, const Cards::Action& cfg, BattleInfoPtr* msg);
	//流血
	int Blood(unsigned battleid, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);
	//反击
	int ShotBack(unsigned battleid, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);

	//处理持续性效果
	void DealBuff(unsigned battleid, GameTeam& attacker, unsigned mode);
	//复活
	int Revive(unsigned battleid, GameTeam& obj, BattleInfoPtr* msg);

private:
	//效果
	//基础伤害att_a:出牌方的攻击 , def_d: 未出牌方的防守
	double BaseHurt(double att_a, double def_d)
	{
		if(att_a * BDC_S(att_p) > def_d)
			return max(double(1), att_a - def_d);
		else
			return max(double(1), att_a * BDC_S(def_p));
	}

	//条件判断
	bool Condition(const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender);

	//是否命中
	bool IsHit(unsigned& c_hit, double adodge_a, double dodge_d);

	//数值处理
	double DataHandle(unsigned battleid, const Cards::Action& cfg);

	//是否暴击
	bool IsCrit(unsigned& c_n_c, unsigned n_c, double crit_a, double acrit_d);

	int BaseHurt(unsigned battleid, unsigned type, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg, bool basehurt, bool con=true);

	int Hurt(unsigned battleid, unsigned cardid, unsigned type, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);

	//修改属性
	int Modify(unsigned battleid, unsigned cardid, const Cards::Action& cfg,  GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);

	//叠加类型
	int Overly(unsigned battleid, unsigned uid, unsigned cardid, const Cards::Action&cfg);

	//连击
	int Batter(unsigned battleid, unsigned cardid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);
	//添加buff
	int AddBuff(unsigned battleid, unsigned cardid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);

	//获得行动点数
	int GainPoint(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, BattleInfoPtr* msg);

	//重置手牌
	int ResetHandCards(unsigned battleid, GameTeam& attacker, BattleInfoPtr* msg);

	//清除buff
	int ClearBuff(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);

	//免疫效果
	int DisableBuff(unsigned battleid, unsigned cardid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);

	//引爆
	int Bomb(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg);
	//伤害反弹
	int HurtBack(unsigned battleid, double dam, GameTeam& attacker, GameTeam& defender);

	//伤害转化
	int HurtTrans(unsigned battleid, double value, GameTeam& attacker, GameTeam& defender, ProtoBattleBase::ProtoBattleAttr* msg);

	//整蛊
	int TempCards(unsigned battleid, const Cards::Action& cfg, GameTeam& defender, BattleInfoPtr* msg);

	//抽卡
	int ExtraCards(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, BattleInfoPtr* msg);
};


#endif /* APP_BATTLE_LOGICACTIONMANAGER_H_ */
