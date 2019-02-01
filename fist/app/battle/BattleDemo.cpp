/*
 * BattleDemo.cpp
 *
 *  Created on: 2018年7月9日
 *      Author: Ralf
 */

#include "BattleDemo.h"

/****************************************************************************/
BattleDemoHeroSkill::BattleDemoHeroSkill(unsigned id, unsigned type, double s, double c, unsigned p_c, unsigned p_a)
	:_id(id)
	,_type(type)
	,_s(s)
	,_c(c)
	,_p_c(p_c)
	,_p_a(p_a)
	,_p(p_c)
{
	_impl();
}
BattleDemoHeroSkill::BattleDemoHeroSkill(const ProtoBattleDemo::ProtoBattleDemoHeroSkill& skill)
	:_id(skill.id())
	,_type(skill.type())
	,_s(skill.s())
	,_c(skill.c())
	,_p_c(skill.pc())
	,_p_a(skill.pa())
	,_p(skill.pc())
{
	_impl();
}
void BattleDemoHeroSkill::_impl()
{
	if(_type >= e_skill_max)
		throw runtime_error("skill_type_error");
}
unsigned BattleDemoHeroSkill::id()
{
	return _id;
}
unsigned BattleDemoHeroSkill::type()
{
	return _type;
}
double BattleDemoHeroSkill::s()
{
	return _s;
}
double BattleDemoHeroSkill::c()
{
	return _c;
}

unsigned BattleDemoHeroSkill::p_c()
{
	return _p_c;
}

unsigned BattleDemoHeroSkill::p_a()
{
	return _p_a;
}

unsigned BattleDemoHeroSkill::p()
{
	return _p;
}

void BattleDemoHeroSkill::fullMsg(ProtoBattleDemo::ProtoBattleDemoHeroSkill *m)
{
	m->set_id(id());
	m->set_type(type());
}
void BattleDemoHeroSkill::fail()
{
	_p += _p_a;
}
void BattleDemoHeroSkill::succ()
{
	_p = _p_c;
}
/****************************************************************************/
BattleDemoItem::BattleDemoItem(unsigned id, unsigned type, double s, double c, unsigned turn)
	:_id(id)
	,_type(type)
	,_s(s)
	,_c(c)
	,_turn(turn)
{
	_impl();
}
BattleDemoItem::BattleDemoItem(const ProtoBattleDemo::ProtoBattleDemoItem& item)
	:_id(item.id())
	,_type(item.type())
	,_s(item.s())
	,_c(item.c())
	,_turn(item.turn())
{
	_impl();
}
void BattleDemoItem::_impl()
{
	if(_type >= e_item_type_max)
		throw runtime_error("item_type_error");
}
unsigned BattleDemoItem::id()
{
	return _id;
}
unsigned BattleDemoItem::type()
{
	return _type;
}
double BattleDemoItem::s()
{
	return _s;
}
double BattleDemoItem::c()
{
	return _c;
}
int BattleDemoItem::turn()
{
	return _turn;
}

void BattleDemoItem::fullMsg(ProtoBattleDemo::ProtoBattleDemoItem *m)
{
	m->set_id(id());
	m->set_type(type());
}
bool BattleDemoItem::nextTurn()
{
	--_turn;
	if(_turn > 0)
		return true;
	return false;
}
/****************************************************************************/
BattleDemoHero::BattleDemoHero(unsigned id, double hp, double att, double def, int crit, int a_crit, int dodge, int a_dodge, double crit_t, unsigned speed
		,  double battlePower, vector<BattleDemoHeroSkill>& skill)
	:_id(id)
	,_hp(hp)
	,_att(att)
	,_def(def)
	,_crit(crit)
	,_a_crit(a_crit)
	,_dodge(dodge)
	,_a_dodge(a_dodge)
	,_crit_t(crit_t)
	,_speed(speed)
	,_power(0)
	,_c_hit(0)
	,_c_n_c(0)
	,_battle_power(battlePower)
{
	if(skill.size() != e_skill_max)
		throw runtime_error("skill_size_error");
	_skill = skill;

	_impl();
}
BattleDemoHero::BattleDemoHero(const ProtoBattleDemo::ProtoBattleDemoHero& hero)
	:_id(hero.id())
	,_hp(hero.hp())
	,_att(hero.att())
	,_def(hero.def())
	,_crit(hero.crit())
	,_a_crit(hero.acrit())
	,_dodge(hero.dodge())
	,_a_dodge(hero.adodge())
	,_crit_t(hero.critt())
	,_speed(hero.speed())
	,_power(0)
	,_c_hit(0)
	,_c_n_c(0)
	,_battle_power(hero.battlepower())
{
	if(hero.skill_size() != e_skill_max)
		throw runtime_error("skill_size_error");
	for(auto& e : hero.skill())
		_skill.push_back(BattleDemoHeroSkill(e));

	_impl();
}
void BattleDemoHero::_impl()
{
	if(int(_hp) <= 0 || int(_att) <= 0)
		throw runtime_error("hp_att_error");
	_a_crit = max(1u, _a_crit);
	_a_dodge = max(1u, _a_dodge);
}
unsigned BattleDemoHero::id()
{
	return _id;
}
int BattleDemoHero::hp()
{
	return int(_hp);
}
double BattleDemoHero::att()
{
	double s(0), c(0);
	for(auto& e : _buff)
	{
		switch(e.type())
		{
		case e_item_att:
			s += e.s();
			c += e.c();
			break;
		default:
			break;
		}
	}
	return _att * (double(1) + s) + c;
}
double BattleDemoHero::def()
{
	return _def;
}

double BattleDemoHero::battlePower()
{
	return _battle_power;
}

double BattleDemoHero::crit()
{
	return double(_crit);
}
double BattleDemoHero::a_crit()
{
	return double(_a_crit);
}
double BattleDemoHero::dodge()
{
	return double(_dodge);
}
double BattleDemoHero::a_dodge()
{
	return double(_a_dodge);
}
double BattleDemoHero::crit_t()
{
	return double(1) + _crit_t;
}
unsigned BattleDemoHero::speed()
{
	return _speed;
}
unsigned BattleDemoHero::power()
{
	return _power;
}
void BattleDemoHero::slow_power()
{
	_power += BDC_S(slow_power);
}
unsigned BattleDemoHero::c_hit()
{
	return _c_hit;
}
unsigned BattleDemoHero::c_n_c()
{
	return _c_n_c;
}

void BattleDemoHero::skills(vector<BattleDemoHeroSkill>& skills)
{
	skills = _skill;
}


void BattleDemoHero::fullMsg(ProtoBattleDemo::ProtoBattleDemoHero *m)
{
	m->set_id(id());
	m->set_hp(hp());
	m->set_att(att());
	m->set_def(def());
	m->set_battlepower((unsigned)battlePower());

	for(auto& e : _skill)
		e.fullMsg(m->add_skill());
}
bool BattleDemoHero::dead()
{
	return hp() <= 0;
}
void BattleDemoHero::attacking(unsigned n_c, vector<BattleDemoItem>& item, BattleDemoHero& defender, ProtoBattleDemo::ProtoBattleDemoTurn* msg)
{
	randomItem(item, msg);
	randomSkill(n_c, defender, msg);
	clearBuff();
}
void BattleDemoHero::randomItem(vector<BattleDemoItem>& item, ProtoBattleDemo::ProtoBattleDemoTurn* msg)
{
	//随机道具
	unsigned item_r = Math::GetRandomInt(e_item_full);
	if(item_r >= item.size())
	{
		msg->set_itemindex(e_item_max);
		return;
	}
	switch(item[item_r].type())
	{
	case e_item_hp:
		_hp += item[item_r].c();
		break;
	case e_item_power:
		_power += unsigned(item[item_r].c());
		break;
	case e_item_att:
		_buff.push_back(item[item_r]);
		break;
	}
	msg->set_itemindex(item_r);
}
void BattleDemoHero::randomSkill(unsigned n_c, BattleDemoHero& defender, ProtoBattleDemo::ProtoBattleDemoTurn* msg)
{
	//基础伤害
	double att_t(att()), basedam(0);
	if(att_t * BDC_S(att_p) > defender.def())
		basedam = max(double(1), att_t - defender.def());
	else
		basedam = max(double(1), att_t * BDC_S(def_p));

	//随机技能
	unsigned p = 0;
	for(auto& e : _skill)
		p += e.p();
	unsigned pi = Math::GetRandomInt(p);
	p = 0;
	unsigned skill_r = 0;
	bool t = false;
	for(auto& e : _skill)
	{
		if(t)
		{
			e.fail();
			continue;
		}
		p += e.p();
		if(pi < p)
		{
			e.succ();
			t = true;
		}
		else
		{
			e.fail();
			++skill_r;
		}
	}
	if(skill_r >= e_skill_max)
		throw runtime_error("skill_p_error");
	msg->set_skillindex(skill_r);

	//命中判断
	bool hit = false;
	if(skill_r == e_skill_3)
	{
		hit = true;
		++_c_hit;
	}
	else if(_c_hit >= BDC_S(dodge_c) && skill_r != e_skill_2)
	{
		hit = false;
		_c_hit = 0;
	}
	else
	{
		unsigned d = min(BDC_S(dodge_max), max(BDC_S(dodge_min), unsigned(BDC_S(dodge_p) * (dodge() / defender.a_dodge()) * double(100))));
		unsigned di = Math::GetRandomInt(100);
		if(di < d)
		{
			hit = true;
			++_c_hit;
		}
		else
		{
			hit = false;
			_c_hit = 0;
		}
	}
	if(hit)
	{
		//暴击判断
		bool bang = false;
		if(_c_n_c >= n_c)
		{
			bang = true;
			_c_n_c = 0;
		}
		else
		{
			unsigned c = min(BDC_S(crit_max), max(BDC_S(crit_min), unsigned(BDC_S(crit_p) * (crit() / defender.a_crit()) * double(100))));
			unsigned ci = Math::GetRandomInt(100);
			if(ci < c)
			{
				bang = true;
				_c_n_c = 0;
			}
			else
			{
				bang = false;
				++_c_n_c;
			}
		}
		msg->set_crit(bang);

		//伤害计算
		double dam = basedam * _skill[skill_r].s() + _skill[skill_r].c();
		if(bang)
			dam = dam * crit_t();
		defender.injure(dam);
		msg->set_skilldam(dam);

		//怒气增加
		_power += BDC_A(skill_power, skill_r);
	}

	//怒气技能判断
	if(_power >= 100)
	{
		_power = 0;
		double extradam = basedam * _skill[e_skill_3].s() + _skill[e_skill_3].c();
		defender.injure(extradam);
		msg->set_extradam(extradam);
	}

	//debug_log("ahp:%d, dhp:%d", hp(), defender.hp());
}
void BattleDemoHero::clearBuff()
{
	for(auto it=begin(_buff);it!=end(_buff);)
	{
		if(!it->nextTurn())
			it = _buff.erase(it);
		else
			++it;
	}
}
void BattleDemoHero::injure(double dam)
{
	_hp -= dam;
}
/****************************************************************************/
BattleDemoTeam::BattleDemoTeam(unsigned side, vector<BattleDemoHero>& hero, vector<BattleDemoItem>& item, unsigned level)
	:_side(side)
	,_level(level)
	,_speed(0)
	,_n_c(0)
{
	if(hero.empty())
		throw runtime_error("hero_size_error");
	if(item.size() > e_item_max)
		throw runtime_error("item_size_error");
	_item = item;
	_hero = hero;

	_impl();
}
BattleDemoTeam::BattleDemoTeam(unsigned side, const ProtoBattleDemo::ProtoBattleDemoTeam& team)
	:_side(side)
	,_level(team.level())
	,_speed(0)
	,_n_c(0)
{
	if(team.hero_size() == 0)
		throw runtime_error("hero_size_error");
	if(team.item_size() > e_item_max)
		throw runtime_error("item_size_error");
	for(auto& e : team.item())
		_item.push_back(BattleDemoItem(e));
	for(auto& e : team.hero())
		_hero.push_back(BattleDemoHero(e));

	_impl();
}
void BattleDemoTeam::_impl()
{
	for(auto& e : _hero)
		_speed += e.speed();

	unsigned li = 0;
	for(auto& e : BDC_S(crit_l))
	{
		if(_level <= e)
			break;
		++li;
	}
	if(li >= ConfigManager::Instance()->battleDemoConfig.m_config.crit_l_size())
		li = ConfigManager::Instance()->battleDemoConfig.m_config.crit_l_size() - 1;
	_n_c = BDC_A(crit_c, li);
}
unsigned BattleDemoTeam::level()
{
	return _level;
}
unsigned BattleDemoTeam::n_c()
{
	return _n_c;
}
unsigned BattleDemoTeam::side()
{
	return _side;
}
unsigned BattleDemoTeam::speed()
{
	return _speed;
}
unsigned BattleDemoTeam::size()
{
	return _hero.size();
}

void BattleDemoTeam::fullMsg(ProtoBattleDemo::ProtoBattleDemoTeam *m)
{
	for(auto& e : _hero)
		e.fullMsg(m->add_hero());
	for(auto& e : _item)
		e.fullMsg(m->add_item());
	 m->set_level(_level);
}
BattleDemoHero& BattleDemoTeam::hero(unsigned index)
{
	if(index >= size())
		throw runtime_error("hero_index_error");
	return _hero[index];
}
vector<BattleDemoItem>& BattleDemoTeam::item()
{
	return _item;
}
/****************************************************************************/
BattleDemo::BattleDemo(vector<BattleDemoHero>& attacker, vector<BattleDemoHero>& defender
		,  vector<BattleDemoItem>& attitem,  vector<BattleDemoItem>& defitem, unsigned attlv, unsigned deflv)
	:_index_a(0)
	,_index_d(0)
	,_turn(0)
	,_att(e_att, attacker, attitem, attlv)
	,_def(e_def, defender, defitem, deflv)
	,_attackerWin(false)
{
	_impl();
}
BattleDemo::BattleDemo(const ProtoBattleDemo::ProtoBattleDemo& demo)
	:_index_a(0)
	,_index_d(0)
	,_turn(0)
	,_att(e_att, demo.attacker())
	,_def(e_def, demo.defender())
	,_attackerWin(false)
{
	_impl();
}
bool BattleDemo::attackerWin()
{
	return _attackerWin;
}
const ProtoBattleDemo::ProtoBattleDemo& BattleDemo::msg()
{
	return _msg;
}
void BattleDemo::_impl()
{
	if(_att.speed() <= _def.speed())
	{
		_attacking = e_def;
		_att.hero(_index_a).slow_power();
	}
	else
	{
		_attacking = e_att;
		_def.hero(_index_d).slow_power();
	}

	_att.fullMsg(_msg.mutable_attacker());
	_def.fullMsg(_msg.mutable_defender());
	_msg.set_first(_attacking);

	while(_index_a < _att.size() && _index_d < _def.size())
	{
		_turn = 0;
		BattleDemoHero& att =  _att.hero(_index_a);
		BattleDemoHero& def =  _def.hero(_index_d);

		bool t = true;
		while(t)
		{
			if(_attacking)
			{
				def.attacking(_def.n_c(), _def.item(), att, _msg.add_turn());
				if(att.dead())
				{
					t = false;
					++_index_a;
				}
			}
			else
			{
				att.attacking(_att.n_c(), _att.item(), def, _msg.add_turn());
				if(def.dead())
				{
					t = false;
					++_index_d;
				}
			}
			ProtoBattleDemo::ProtoBattleDemoTurnInfo *info = _msg.add_info();
			info->set_ahp(att.hp());
			info->set_ap(att.power());
			info->set_dhp(def.hp());
			info->set_dp(def.power());

			_attacking = (_attacking + 1) % e_side_max;

			++_turn;
			if(t && _turn >= BDC_S(turn_max))
			{
				t = false;
				if(att.hp() <= def.hp())
					++_index_a;
				else
					++_index_d;
			}
		}
	}

	if(_index_a < _att.size())
		_attackerWin = true;
	_msg.set_attackerwin(_attackerWin);
}

unsigned BattleDemo::Turn()
{
	return _turn;
}

/****************************************************************************/

