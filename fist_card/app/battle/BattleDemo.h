/*
 * BattleDemo.h
 *
 *  Created on: 2018年7月9日
 *      Author: Ralf
 */

#ifndef APP_BATTLE_BATTLEDEMO_H_
#define APP_BATTLE_BATTLEDEMO_H_


#include "Kernel.h"

/****************************************************************************/
class BattleDemoHeroSkill
{
private:
	unsigned 	_id;
	unsigned 	_type;		//类型 BattleDemoHeroSkillType
	double 		_s;			//伤害系数
	double 		_c;			//伤害固定值
	unsigned	_p_c;		//初始权重
	unsigned 	_p_a;		//增加权重
	unsigned	_p;			//当前权重

	void _impl();
public:
	BattleDemoHeroSkill(unsigned id, unsigned type, double s, double c, unsigned p_c, unsigned p_a);
	BattleDemoHeroSkill(const ProtoBattleDemo::ProtoBattleDemoHeroSkill& skill);
	unsigned id();
	unsigned type();
	double s();
	double c();
	unsigned p_c();
	unsigned p_a();
	unsigned p();

	void fullMsg(ProtoBattleDemo::ProtoBattleDemoHeroSkill *m);
	void fail();
	void succ();
};
/****************************************************************************/
class BattleDemoItem
{
private:
	unsigned _id;
	unsigned _type;		//类型 BattleDemoItemType
	double _s;			//系数
	double _c;			//常数
	int _turn;			//持续

	void _impl();
public:
	BattleDemoItem(unsigned id, unsigned type, double s, double c, unsigned turn);
	BattleDemoItem(const ProtoBattleDemo::ProtoBattleDemoItem& item);
	unsigned id();
	unsigned type();
	double s();
	double c();
	int turn();

	void fullMsg(ProtoBattleDemo::ProtoBattleDemoItem *m);
	bool nextTurn();
};
/****************************************************************************/
class BattleDemoHero
{
private:
	unsigned _id;
	double 	_hp;			//生命
	double 	_att;			//攻击
	double 	_def;			//防御
	unsigned 	_crit;		//暴击
	unsigned 	_a_crit;	//抗暴击
	unsigned 	_dodge;		//闪避
	unsigned 	_a_dodge;	//命中
	double 		_crit_t;	//暴击倍数
	unsigned	_speed;		//先手

	unsigned 	_power;		//怒气
	unsigned 	_c_hit;		//连续命中次数
	unsigned 	_c_n_c;		//连续未暴击次数
	double      _battle_power; //战力
	vector<BattleDemoHeroSkill> _skill;
	list<BattleDemoItem> _buff;

	void _impl();
	void randomItem(vector<BattleDemoItem>& item, ProtoBattleDemo::ProtoBattleDemoTurn* msg);
	void randomSkill(unsigned n_c, BattleDemoHero& defender, ProtoBattleDemo::ProtoBattleDemoTurn* msg);
	void clearBuff();
public:
	BattleDemoHero(unsigned id, double hp, double att, double def, int crit, int a_crit, int dodge, int a_dodge, double crit_t, unsigned speed
			,  double battlePower, vector<BattleDemoHeroSkill>& skill);
	BattleDemoHero(const ProtoBattleDemo::ProtoBattleDemoHero& hero);
	unsigned id();
	int hp();
	double att();
	double def();
	double crit();
	double a_crit();
	double dodge();
	double a_dodge();
	double crit_t();
	unsigned speed();
	unsigned power();
	void slow_power();
	unsigned c_hit();
	unsigned c_n_c();
	double  battlePower();
	void skills(vector<BattleDemoHeroSkill>& skills);

	void fullMsg(ProtoBattleDemo::ProtoBattleDemoHero *m);
	bool dead();
	void attacking(unsigned n_c, vector<BattleDemoItem>& item, BattleDemoHero& defender, ProtoBattleDemo::ProtoBattleDemoTurn* msg);
	void injure(double dam);
};
/****************************************************************************/
class BattleDemoTeam
{
private:
	vector<BattleDemoHero> _hero;
	vector<BattleDemoItem> _item;
	unsigned _level;

	unsigned _side;			//BattleDemoSide
	unsigned _speed;		//先手
	unsigned _n_c;			//必爆次数

	void _impl();
public:
	BattleDemoTeam(unsigned side, vector<BattleDemoHero>& hero, vector<BattleDemoItem>& item, unsigned level);
	BattleDemoTeam(unsigned side, const ProtoBattleDemo::ProtoBattleDemoTeam& team);
	unsigned level();
	unsigned n_c();
	unsigned side();
	unsigned speed();
	unsigned size();

	void fullMsg(ProtoBattleDemo::ProtoBattleDemoTeam *m);
	BattleDemoHero& hero(unsigned index);
	vector<BattleDemoItem>& item();
};
/****************************************************************************/
class BattleDemo
{
private:
	unsigned 		_index_a, _index_d;	//当前出场
	unsigned 		_turn;				//当前场次已进行回合
	BattleDemoTeam 	_att, _def;
	bool 			_attackerWin;
	unsigned		_attacking;			//当前攻击方
	ProtoBattleDemo::ProtoBattleDemo	_msg;

	void _impl();
public:
	BattleDemo(vector<BattleDemoHero>& attacker, vector<BattleDemoHero>& defender
			, vector<BattleDemoItem>& attitem, vector<BattleDemoItem>& defitem, unsigned attlv, unsigned deflv);
	BattleDemo(const ProtoBattleDemo::ProtoBattleDemo& demo);
	bool attackerWin();
	const ProtoBattleDemo::ProtoBattleDemo& msg();
};
/****************************************************************************/

#endif /* APP_BATTLE_BATTLEDEMO_H_ */
