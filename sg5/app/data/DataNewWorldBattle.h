/*
 * DataNewWorldBattle.h
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#ifndef DATANEWWORLDBATTLE_H_
#define DATANEWWORLDBATTLE_H_

#include <math.h>
#include "Kernel.h"
#include "DataNewWorld.h"

/**************tick time*******************/
#ifdef SG_16_VER
#define NEW_WORLD_BATTLE_TICK 					3
#else
#define NEW_WORLD_BATTLE_TICK 					7
#endif
/**************hero para*******************/
#define NEW_WORLD_BATTLE_HERO 				50000
#define NEW_WORLD_BATTLE_HERO_INDEX 		5
#define NEW_WORLD_BATTLE_HERO_MIN			5
#define NEW_WORLD_BATTLE_HERO_MIN_F			double(5)
#define NEW_WORLD_BATTLE_HERO_TIME_1		600
/**************city para*******************/
#define NEW_WORLD_BATTLE_CITY_NEUTRAL  		7
#define NEW_WORLD_BATTLE_CITY_CAPITAL  		1
#define NEW_WORLD_BATTLE_CITY_KINGDOM_OTHER	71
#define NEW_WORLD_BATTLE_CITY_KINGDOM		(NEW_WORLD_BATTLE_CITY_CAPITAL+NEW_WORLD_BATTLE_CITY_KINGDOM_OTHER)
#define NEW_WORLD_BATTLE_CITY 				(NEW_WORLD_BATTLE_CITY_KINGDOM*3+NEW_WORLD_BATTLE_CITY_NEUTRAL)
#define NEW_WORLD_BATTLE_CITY_KINGDOM_SEQ	100
/**************npc para*******************/
#define NEW_WORLD_BATTLE_CITY_VISION		50
#define NEW_WORLD_BATTLE_CITY_VISION_NPC	(NEW_WORLD_BATTLE_CITY_VISION + 1)
#define NEW_WORLD_BATTLE_CITY_NPC			50
#define NEW_WORLD_BATTLE_CITY_NPC_TIME	600
#define NEW_WORLD_BATTLE_CITY_OCCUPY_NPC 5
/**************para define*******************/
#define NEW_WORLD_BATTLE_HERO_LEVEL 		 120
/**************hero define*******************/
#define NEW_WORLD_BATTLE_HERO_RECOVER 1000
enum NewWorldBattleProperty
{
	NewWorldBattleProperty_hp				= 0,
	NewWorldBattleProperty_attack			= 1,
	NewWorldBattleProperty_defence			= 2,
	NewWorldBattleProperty_speed			= 3,
	NewWorldBattleProperty_crit				= 4,
	NewWorldBattleProperty_anti_crit		= 5,
	NewWorldBattleProperty_crit_times		= 6,
	NewWorldBattleProperty_anti_crit_times	= 7,
	NewWorldBattleProperty_dodge			= 8,
	NewWorldBattleProperty_anti_dodge		= 9,
	NewWorldBattleProperty_block			= 10,
	NewWorldBattleProperty_anti_block		= 11,
	NewWorldBattleProperty_extra			= 12,
	NewWorldBattleProperty_anti_extra		= 13,
	NewWorldBattleProperty_reflect			= 14,
	NewWorldBattleProperty_anti_reflect		= 15,
	NewWorldBattleProperty_type_extra		= 16,
	NewWorldBattleProperty_anti_speed		= 17,
	NewWorldBattleProperty_explode			= 18,
	NewWorldBattleProperty_F_A_1			= 19,
	NewWorldBattleProperty_F_A_2			= 20,
	NewWorldBattleProperty_F_A_3			= 21,
	NewWorldBattleProperty_F_A_4			= 22,
	NewWorldBattleProperty_F_A_5			= 23,
	NewWorldBattleProperty_F_D_1			= 24,
	NewWorldBattleProperty_F_D_2			= 25,
	NewWorldBattleProperty_F_D_3			= 26,
	NewWorldBattleProperty_F_D_4			= 27,
	NewWorldBattleProperty_F_D_5			= 28,
	NewWorldBattleProperty_A_D_1			= 29,
	NewWorldBattleProperty_A_D_2			= 30,
	NewWorldBattleProperty_NB				= 31,
	NewWorldBattleProperty_hp_extra			= 32,
	NewWorldBattleProperty_anti_hp_extra	= 33,

	NewWorldBattleProperty_max
};
enum NewWorldBattleHeroJob
{
	NewWorldBattleHeroJob_warrior	= 0,
	NewWorldBattleHeroJob_shooter	= 1,
	NewWorldBattleHeroJob_wizard	= 2,

	NewWorldBattleHeroJob_max
};
enum NewWorldBattleHeroStatus
{
	NewWorldBattleHeroStatus_wait_defence	= 0,
	NewWorldBattleHeroStatus_defence  		= 1,
	NewWorldBattleHeroStatus_wait_attack	= 2,
	NewWorldBattleHeroStatus_attack			= 3,
	NewWorldBattleHeroStatus_wait_move		= 4,
	NewWorldBattleHeroStatus_move			= 5,

	NewWorldBattleHeroStatus_max
};
enum NewWorldBattleHeroAttackResult
{
	NewWorldBattleHeroAttackResult_none			= 0,
	NewWorldBattleHeroAttackResult_attacker_win	= 1,
	NewWorldBattleHeroAttackResult_defender_win	= 2,
	NewWorldBattleHeroAttackResult_all_die		= 3,
};
struct NewWorldBattleHeroIndex
{
	unsigned uid, index;
	NewWorldBattleHeroIndex()
	{
		uid = index = 0;
	}
	NewWorldBattleHeroIndex(unsigned uid1, unsigned index1)
	{
		uid = uid1;
		index = index1;
	}
	NewWorldBattleHeroIndex(const NewWorldBattleHeroIndex& node)
	{
		uid = node.uid;
		index = node.index;
	}
	void clear()
	{
		uid = index = 0;
	}
	NewWorldBattleHeroIndex& operator =(const NewWorldBattleHeroIndex& node)
	{
		uid = node.uid;
		index = node.index;
		return *this;
	}
	bool operator <(const NewWorldBattleHeroIndex& other) const
	{
		if(uid != other.uid)
			return uid < other.uid;
		else
			return index < other.index;
	}
	bool operator ==(const NewWorldBattleHeroIndex& other) const
	{
		if(uid == other.uid && index == other.index)
			return true;
		return false;
	}
	bool operator !=(const NewWorldBattleHeroIndex& other) const
	{
		if(uid == other.uid && index == other.index)
			return false;
		return true;
	}
};
struct NewWorldBattleHero
{
	NewWorldBattleHeroIndex index;
	unsigned seq, hid, kingdom, job, level, type, cid, status, next, ts;
	int hp;
	char name[32];
	int property[NewWorldBattleProperty_max];
	unsigned kill;
	NewWorldBattleHero()
	{
		seq = hid = kingdom = job = level = hp = type = cid = status = next = ts = 0;
		memset(name, 0, sizeof(name));
		memset(property, 0, sizeof(property));
		kill = 0;
	}
	bool copy(NewWorldBattleHero &other);
	bool recover(unsigned city)
	{
		if(hp == property[NewWorldBattleProperty_hp])
			return false;
		else if(hp < property[NewWorldBattleProperty_hp] && hp >= 0)
		{
			double total = NEW_WORLD_BATTLE_HERO_TIME_1;
			int add = (double)property[NewWorldBattleProperty_hp] * (double)NEW_WORLD_BATTLE_TICK / total;
			if(add == 0)
				add = 1;
			hp += add;
			if(hp > property[NewWorldBattleProperty_hp])
				hp = property[NewWorldBattleProperty_hp];
		}
		else if(hp > property[NewWorldBattleProperty_hp])
			hp = property[NewWorldBattleProperty_hp];
		else
			hp = 0;

		return true;
	}
	unsigned getJob() const
	{
		return job + 1;
	}
	unsigned getType() const
	{
		return type + 1;
	}
};
/**************city define*******************/
#define NEW_WORLD_BATTLE_DOUBLE_TIME 1800
#define NEW_WORLD_BATTLE_DAMAGE_MAX 50
enum NewWorldBattleCityType
{
	NewWorldBattleCityType_capital	= 0,
	NewWorldBattleCityType_small	= 1,

	NewWorldBattleCityType_max
};

struct NewWorldBattleTower
{
	unsigned uid, dps, hit;
	NewWorldBattleTower()
	{
		uid = dps = hit = 0;
	}
	void clear()
	{
		uid = dps = hit = 0;
	}
};
struct NewWorldBattleCity
{
	unsigned seq, cid, kingdom, damage, countV, countN, npcts, reward, nextReward, ts;
	int count[4];
	unsigned extraKillTS[4];
	NewWorldBattleHeroIndex attacker, defender;
	NewWorldBattleHero vision[NEW_WORLD_BATTLE_CITY_VISION_NPC];//1 for npc
	NewWorldBattleTower tower;
	NewWorldBattleCity()
	{
		seq = cid = kingdom = damage = countV = countN = npcts = reward = nextReward = ts = 0;
		memset(count,0,sizeof(count));
		memset(extraKillTS,0,sizeof(extraKillTS));
	}
	bool Fighting() const
	{
		switch(kingdom)
		{
		case 0:
			return count[0] > 0 || count[1] > 0 || count[2] > 0 || count[3] > 0;
		case 1:
			return count[1] > 0 || count[2] > 0 || count[3] > 0;
		case 2:
			return count[0] > 0 || count[2] > 0 || count[3] > 0;
		case 3:
			return count[0] > 0 || count[1] > 0 || count[3] > 0;
		case 4:
			return count[0] > 0 || count[1] > 0 || count[2] > 0;
		}
		return false;
	}
	bool bug() const
	{
		return count[0] < 0 || count[1] < 0 || count[2] < 0 || count[3] < 0;
	}
};
/**************data define*******************/
struct DataNewWorldBattle
{
	unsigned ts, changets, count;
	NewWorldBattleHero hero[NEW_WORLD_BATTLE_HERO];
	NewWorldBattleCity city[NEW_WORLD_BATTLE_CITY];
	DataNewWorldBattle()
	{
		count = changets = ts = 0;
	}
};
struct DataNewWorldBattleBattleChange
{
	unsigned cid, kingdom, battle;
	DataNewWorldBattleBattleChange()
	{
		cid = kingdom = battle = 0;
	}
};
struct DataNewWorldBattleChangeBattle
{
	DataNewWorldBattleBattleChange battle[NEW_WORLD_BATTLE_CITY];
	void clear()
	{
		memset(battle,0,sizeof(battle));
	}
};
/**************static define*******************/
typedef map<NewWorldBattleHeroIndex, NewWorldBattleHero> NewWorldBattleHeroMap;
typedef multimap<pair<unsigned, unsigned>, NewWorldBattleHeroIndex> NewWorldBattleCityQueue;
struct NewWorldBattleCityBattle
{
	NewWorldBattleCity city;
	NewWorldBattleCityQueue attacker, defender;
};
typedef map<unsigned, NewWorldBattleCityBattle> NewWorldBattleCityMap;
#define NEW_WORLD_BATTLE_ROAD 324
typedef map<unsigned, vector<unsigned> > NewWorldBattleRoadMap;
#define NEW_WORLD_BATTLE_REDUCE double(0.65)
#define NEW_WORLD_BATTLE_VISION_REDUCE double(0.8)
#define NEW_WORLD_BATTLE_CITY_REDUCE double(0.5)
#define NEW_WORLD_BATTLE_MOVE_LEVEL 150
#define NEW_WORLD_BATTLE_RUSH_MIN 2
#define NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MIN 35
#define NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MAX 120
#define NEW_WORLD_BATTLE_KILL_REWARD_KILL 3
#define NEW_WORLD_BATTLE_KILL_REWARD_P 4
typedef map<unsigned,DataNewWorldBattleBattleChange> NewWorldBattleChangeMap;
#define NEW_WORLD_BATTLE_KILL_ADD_BATTLE 	double(33)
#define NEW_WORLD_BATTLE_KILL_ADD_LAST 		50
#define NEW_WORLD_BATTLE_KILL_ADD_QUEUE 	20
#define NEW_WORLD_BATTLE_KILL_ADD_CLONE 	20
#define NEW_WORLD_BATTLE_KILL_ADD_RUSH 		10
#define NEW_WORLD_BATTLE_DOUBLE_KILL		50
#define NEW_WORLD_BATTLE_COLLECTOTHER_KILL	50
/********************************************/
class CDataNewWorldBattle
{
public:
	CDataNewWorldBattle();
	virtual ~CDataNewWorldBattle();
	int Init(const string &path, semdat sem=sem_new_world_battle);

	unsigned GetTS() { return m_ts; }

	const NewWorldBattleCityMap& GetWorld();
	const NewWorldBattleCityBattle& GetCity(unsigned cid);
	const NewWorldBattleHero&  GetHero(NewWorldBattleHeroIndex index);
	const NewWorldBattleHeroMap&  GetAllHero();
	const NewWorldBattleChangeMap& GetChangeMap(){return m_battlechange;}
	void ClearChangeMap(){m_battlechange.clear();}

	int SetHero(NewWorldBattleHero &hero, bool &fix);
	int Move(NewWorldBattleHeroIndex index, unsigned cid, bool leave, unsigned fly, unsigned &status);
	int Change(NewWorldBattleHeroIndex index, unsigned type);
	int Clone(NewWorldBattleHeroIndex index);
	int Rush(NewWorldBattleHeroIndex index, NewWorldBattleHero &other, NewWorldBattleHero &end);
	int Recover(NewWorldBattleHeroIndex index, unsigned num);
	int Double(unsigned uid, unsigned kingdom, unsigned cid);
	int CollectOther(unsigned uid, unsigned cid);

	int Buildyjt(NewWorldBattleHeroIndex index);

	static inline bool IsInCity(unsigned status)
	{
		return status != NewWorldBattleHeroStatus_wait_move && status != NewWorldBattleHeroStatus_move;
	}
	static inline bool CanMove(unsigned status)
	{
		return status != NewWorldBattleHeroStatus_wait_move
			&& status != NewWorldBattleHeroStatus_move
			&& status != NewWorldBattleHeroStatus_defence
			&& status != NewWorldBattleHeroStatus_attack;
	}
	static inline bool IsDefender(unsigned status)
	{
		return status == NewWorldBattleHeroStatus_wait_defence || status == NewWorldBattleHeroStatus_defence;
	}
	static inline bool IsAttacker(unsigned status)
	{
		return status == NewWorldBattleHeroStatus_wait_attack || status == NewWorldBattleHeroStatus_attack;
	}
	static inline bool IsFighting(unsigned status)
	{
		return status == NewWorldBattleHeroStatus_attack || status == NewWorldBattleHeroStatus_defence;
	}
	static inline bool IsReady(unsigned status)
	{
		return status == NewWorldBattleHeroStatus_wait_defence || status == NewWorldBattleHeroStatus_wait_attack || status == NewWorldBattleHeroStatus_move;
	}

	static inline unsigned getCapital(unsigned kingdom)
	{
		if(kingdom > 4 || kingdom < 1)
			return 1;
		if(kingdom == 4)
			kingdom = 0;
		return kingdom*NEW_WORLD_BATTLE_CITY_KINGDOM_SEQ + NEW_WORLD_BATTLE_CITY_CAPITAL;
	}
	static inline unsigned getCityType(unsigned cid)
	{
		cid = cid % NEW_WORLD_BATTLE_CITY_KINGDOM_SEQ;
		if(cid ==  NEW_WORLD_BATTLE_CITY_CAPITAL)
			return NewWorldBattleCityType_capital;
		return NewWorldBattleCityType_small;
	}
	static inline bool isCapital(unsigned cid)
	{
		return getCityType(cid) == NewWorldBattleCityType_capital;
	}
	static inline bool canAttack(unsigned cid)
	{
		unsigned type = getCityType(cid);
		return  type == NewWorldBattleCityType_small;
	}

	static inline bool isVision(NewWorldBattleHeroIndex index)
	{
		return index.uid < ADMIN_UID && index.index < NEW_WORLD_BATTLE_CITY_VISION;
	}
	static inline bool isNPC(NewWorldBattleHeroIndex index)
	{
		return index.uid == ADMIN_UID && index.index == NEW_WORLD_BATTLE_CITY_VISION;
	}
	static inline bool notHero(NewWorldBattleHeroIndex index)
	{
		return index.uid <= ADMIN_UID && index.index < NEW_WORLD_BATTLE_CITY_VISION_NPC;
	}
	static inline bool isHero(NewWorldBattleHeroIndex index)
	{
		return IsValidUid(index.uid) && index.index < NEW_WORLD_BATTLE_HERO_INDEX;
	}
	int PrintHero();
	int PrintCity();
	int Watch();
	int Fix();
	int Reset();
	int Back();
	int Test(NewWorldBattleHero &attacker, unsigned hpa, NewWorldBattleHero &defender, unsigned hpd);
	int Time();

	static int GetMoveR1(unsigned level);
	static unsigned GetKillExp(unsigned kill, unsigned level);
	static unsigned GetKillRewardNew(unsigned rank);
	static unsigned GetKillRewardP(unsigned kill);
	void GetKillRewardResult(unsigned kingdom[4], unsigned &result);

	int Restart();
	int CheckOver();
protected:
	int checkTick();
	int sync(DataNewWorldBattle * pdata);//must in lock
	void _fix(DataNewWorldBattle *pdata, unsigned ts);//must in lock

	static inline void makeNPC(NewWorldBattleHero &hero)
	{
		unsigned job = hero.job % NewWorldBattleHeroJob_max;
		unsigned type = NewWorldBattleHeroJob_shooter;
		hero.index.uid = ADMIN_UID;
		hero.index.index = NEW_WORLD_BATTLE_CITY_VISION;
		hero.seq = ADMIN_UID;
		hero.hid = job;
		hero.job = job;
		hero.level = NEW_WORLD_BATTLE_HERO_LEVEL;
		hero.type = type;
		hero.status = NewWorldBattleHeroStatus_defence;
		hero.name[0] = 'N';hero.name[1] = 'P';hero.name[2] = 'C';hero.name[3] = 0;
		for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
			hero.property[i] = CDataNewWorld::npc_property[job][NEW_WORLD_HERO_NPC_DEFAULT-1][i];
		hero.hp = hero.property[NewWorldBattleProperty_hp];
		hero.ts = hero.next = Time::GetGlobalTime();
	}

	inline unsigned attacking(NewWorldBattleHero &attacker, NewWorldBattleHero &defender, int &attackkill, int &defendkill)
	{
		//step 1: damage of type vs job
		//debug_log("----start----");
		//debug_log("attacker=%u,%u,city=%u,job=%u,type=%u,hp=%u,maxhp=%u,att=%u,def=%u",attacker.index.uid,attacker.index.index,attacker.cid,attacker.job,attacker.type,attacker.hp,attacker.property[NewWorldBattleProperty_hp],attacker.property[NewWorldBattleProperty_attack],attacker.property[NewWorldBattleProperty_defence]);
		//debug_log("defender=%u,%u,city=%u,job=%u,type=%u,hp=%u,maxhp=%u,att=%u,def=%u",defender.index.uid,defender.index.index,defender.cid,defender.job,defender.type,defender.hp,defender.property[NewWorldBattleProperty_hp],defender.property[NewWorldBattleProperty_attack],defender.property[NewWorldBattleProperty_defence]);
		if(attacker.hp > attacker.property[NewWorldBattleProperty_hp])
			attacker.hp = attacker.property[NewWorldBattleProperty_hp];
		if(defender.hp > defender.property[NewWorldBattleProperty_hp])
			defender.hp = defender.property[NewWorldBattleProperty_hp];

		bool mha = attacker.hp == attacker.property[NewWorldBattleProperty_hp];
		bool mhd = defender.hp == defender.property[NewWorldBattleProperty_hp];
		double ha = getHPEffect(attacker);
		double hd = getHPEffect(defender);
		bool ce = getCityEffect(defender);
		bool visiona = isVision(attacker.index);
		bool visiond = isVision(defender.index);

		double typea = getTypeEffect(attacker, defender);
		double typed = getTypeEffect(defender, attacker);
		double dk1 = max(NEW_WORLD_BATTLE_HERO_MIN_F, ((double)attacker.property[NewWorldBattleProperty_hp])*typed + (double)defender.property[NewWorldBattleProperty_type_extra]);
		double ak1 = max(NEW_WORLD_BATTLE_HERO_MIN_F, ((double)defender.property[NewWorldBattleProperty_hp])*typea + (double)attacker.property[NewWorldBattleProperty_type_extra]);
		dk1 *= hd;
		ak1 *= ha;
		if(ce)
			dk1 *= NEW_WORLD_BATTLE_CITY_REDUCE;
		/***********nerf vision***************/
		if(visiond)
			dk1 *= NEW_WORLD_BATTLE_VISION_REDUCE;
		if(visiona)
			ak1 *= NEW_WORLD_BATTLE_VISION_REDUCE;

		/*************************************/
		if(mhd)
			dk1 += double(defender.property[NewWorldBattleProperty_NB]);
		if(mha)
			ak1 += double(attacker.property[NewWorldBattleProperty_NB]);

		dk1 += getHPExtraEffect(defender, attacker);
		ak1 += getHPExtraEffect(attacker, defender);

		int dk1i = (int)dk1;
		int ak1i = (int)ak1;
		if(dk1i > attacker.hp)
			dk1i = attacker.hp;
		if(ak1i > defender.hp)
			ak1i = defender.hp;
		attacker.hp -= (dk1i + getTowerEffect(defender));
		defender.hp -= ak1i;
		//debug_log("step1:attacker.hp=%u,defender.hp=%u",attacker.hp,defender.hp);

		attackkill = ak1i;
		defendkill = dk1i;

		if(attacker.hp < NEW_WORLD_BATTLE_HERO_MIN)
			defender.hp -= attacker.property[NewWorldBattleProperty_explode];
		if(defender.hp < NEW_WORLD_BATTLE_HERO_MIN)
			attacker.hp -= defender.property[NewWorldBattleProperty_explode];

		if(attacker.hp < NEW_WORLD_BATTLE_HERO_MIN && defender.hp < NEW_WORLD_BATTLE_HERO_MIN)
		{
			attacker.hp = defender.hp = 0;
			return NewWorldBattleHeroAttackResult_all_die;
		}
		else if(attacker.hp < NEW_WORLD_BATTLE_HERO_MIN)
		{
			attacker.hp = 0;
			return NewWorldBattleHeroAttackResult_defender_win;
		}
		else if(defender.hp < NEW_WORLD_BATTLE_HERO_MIN)
		{
			defender.hp = 0;
			return NewWorldBattleHeroAttackResult_attacker_win;
		}

		//step 2: damage of attack
		double ja = getJobEffect(attacker, defender);
		double jd = getJobEffect(defender, attacker);
		double sa = getSpeedEffect(attacker, defender);
		double sd = getSpeedEffect(defender, attacker);
		double pa = getProtectEffect(attacker, defender);
		double pd = getProtectEffect(defender, attacker);
		double ca = getCritEffect(attacker, defender);
		double cd = getCritEffect(defender, attacker);
		double aa = getAttackEffect(attacker, defender);
		double ad = getAttackEffect(defender, attacker);
		double la = getLevelEffect(attacker, attacker);
		double ld = double(2) - la;
		double ra = getReflectEffect(attacker, defender);
		double rd = getReflectEffect(defender, attacker);
		double ea = getExtraEffect(attacker, defender);
		double ed = getExtraEffect(defender, attacker);
		double ma = getFEffect(attacker, defender);
		double md = getFEffect(defender, attacker);
		double fa = getRandomEffect();
		double fd = getRandomEffect();
		//temp value
		double tta = ja*sa*fa;
		double ttd = jd*sd*fd;
		double ta = ca*aa*la*tta;
		double td = cd*ad*ld*ttd;
		//dps=attack+reflect+extra
		double dpsa = pa*ta + ra*td + ea*tta + ma*tta;
		double dpsd = pd*td + rd*ta + ed*ttd + md*ttd;
		//dps effected by hp
		dpsa *= ha;
		dpsd *= hd;
		//debug_log("dpsa=%f,ja=%f,sa=%f,pa=%f,ca=%f,aa=%f,la=%f,ra=%f,ea=%f,fa=%f,ha=%f",dpsa,ja,sa,pa,ca,aa,la,ra,ea,fa,ha);
		//debug_log("dpsd=%f,jd=%f,sd=%f,pd=%f,cd=%f,ad=%f,ld=%f,rd=%f,ed=%f,fd=%f,hd=%f",dpsd,jd,sd,pd,cd,ad,ld,rd,ed,fd,hd);
		//dps effected by city
		if(ce)
		{
			dpsd *= NEW_WORLD_BATTLE_CITY_REDUCE;
			//debug_log("CityEffect:dpsd=%f",dpsd);
		}
		/***********nerf vision***************/
		if(visiona)
			dpsa *= NEW_WORLD_BATTLE_VISION_REDUCE;
		if(visiond)
			dpsd *= NEW_WORLD_BATTLE_VISION_REDUCE;
		/*************************************/

		//time=min(hp/dps)
		double timea = ((double)attacker.hp)/max(dpsd, double(1));
		double timed = ((double)defender.hp)/max(dpsa, double(1));
		double time = min(timea, timed);
		int dk2 = max(NEW_WORLD_BATTLE_HERO_MIN_F, dpsd * time);
		int ak2 = max(NEW_WORLD_BATTLE_HERO_MIN_F, dpsa * time);
		if(dk2 > attacker.hp)
			dk2 = attacker.hp;
		if(ak2 > defender.hp)
			ak2 = defender.hp;
		attacker.hp -= dk2;
		defender.hp -= ak2;
		//debug_log("step2:attacker.hp=%u,defender.hp=%u",attacker.hp,defender.hp);
		//debug_log("----end----");

		attackkill += ak2;
		defendkill += dk2;

		if(attacker.hp < NEW_WORLD_BATTLE_HERO_MIN)
			defender.hp -= attacker.property[NewWorldBattleProperty_explode];
		if(defender.hp < NEW_WORLD_BATTLE_HERO_MIN)
			attacker.hp -= defender.property[NewWorldBattleProperty_explode];

		if(attacker.hp < NEW_WORLD_BATTLE_HERO_MIN && defender.hp < NEW_WORLD_BATTLE_HERO_MIN)
		{
			attacker.hp = defender.hp = 0;
			return NewWorldBattleHeroAttackResult_all_die;
		}
		else if(attacker.hp < NEW_WORLD_BATTLE_HERO_MIN)
		{
			attacker.hp = 0;
			return NewWorldBattleHeroAttackResult_defender_win;
		}
		else if(defender.hp < NEW_WORLD_BATTLE_HERO_MIN)
		{
			defender.hp = 0;
			return NewWorldBattleHeroAttackResult_attacker_win;
		}

		return NewWorldBattleHeroAttackResult_all_die;
	}
	static inline double getTypeEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		if(attacker.type == defender.job)
			return (double)(Math::GetRandomInt(40) + 10)/double(1000);
		return double(0);
	}
	static inline double getJobEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		if((attacker.job + 1)%NewWorldBattleHeroJob_max == defender.job)
			return double(1.05);
		return double(1);
	}
	static inline double getRandomEffect()
	{
		return (double)(Math::GetRandomInt(200) + 900)/double(1000);
	}
	static inline double getSpeedEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		return max(double(1), min(double(4),
			(double)attacker.property[NewWorldBattleProperty_speed]/double(100)
			* max(double(0.67), min(double(1), double(1)-(double)defender.property[NewWorldBattleProperty_anti_speed])/double(100))));
	}
	static inline double getProtectEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		return max(double(0), double(1)
			- NEW_WORLD_BATTLE_REDUCE * double(0.5) * min(double(1), max(double(0), (double)defender.property[NewWorldBattleProperty_block]
			      -(double)attacker.property[NewWorldBattleProperty_anti_block])/double(1000)))
			* max(double(0), double(1) - NEW_WORLD_BATTLE_REDUCE * min(double(0.8), max(double(0),((double)defender.property[NewWorldBattleProperty_dodge]-(double)attacker.property[NewWorldBattleProperty_anti_dodge])
					/(double)CDataNewWorld::c_crit_dodge[defender.level-1])));
	}
	static inline double getCritEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		return (double(1)
			+ NEW_WORLD_BATTLE_REDUCE * min(double(0.8), max(double(0),
				((double)attacker.property[NewWorldBattleProperty_crit]-(double)defender.property[NewWorldBattleProperty_anti_crit])
					/(double)CDataNewWorld::c_crit_dodge[attacker.level-1]))
			* max(attacker.property[NewWorldBattleProperty_crit_times]
				  -defender.property[NewWorldBattleProperty_anti_crit_times],0)/double(1000));
	}
	static inline double getAttackEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		return (double)CDataNewWorld::c_attack[attacker.level-1]
		   * (double)attacker.property[NewWorldBattleProperty_attack]/max(double(1),max((double)defender.property[NewWorldBattleProperty_defence]*double(0.8), (double)defender.property[NewWorldBattleProperty_defence]*double(1000-attacker.property[NewWorldBattleProperty_A_D_1])/double(1000)-double(attacker.property[NewWorldBattleProperty_A_D_2])));
	}
	static inline double getLevelEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		return double(2)*(double)attacker.level/(double)(attacker.level+defender.level);
	}
	static inline double getReflectEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		return double(0.5)*(double)max(attacker.property[NewWorldBattleProperty_reflect]-defender.property[NewWorldBattleProperty_anti_reflect],0)/double(1000);
	}
	static inline double getExtraEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		return (double)max(0,attacker.property[NewWorldBattleProperty_extra]-defender.property[NewWorldBattleProperty_anti_extra]);
	}
	static inline double getFEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		for(unsigned i=NewWorldBattleProperty_F_A_1;i<=NewWorldBattleProperty_F_A_5;++i)
		{
			if(attacker.property[i])
				return (double)max(0,attacker.property[i]-defender.property[i+5]);
		}
		return double(0);
	}
	static inline double getHPEffect(const NewWorldBattleHero &attacker)
	{
		return ((double)attacker.hp)/(double)attacker.property[NewWorldBattleProperty_hp];
	}
	inline bool getCityEffect(const NewWorldBattleHero &defender)
	{
		unsigned enemy = 0, all = 0;
		if(m_roadmap.count(defender.cid))
		{
			for(vector<unsigned>::const_iterator it=m_roadmap[defender.cid].begin();it!=m_roadmap[defender.cid].end();++it)
			{
				++all;
				if(m_citymap[*it].city.kingdom != m_citymap[defender.cid].city.kingdom)
					++enemy;
			}
		}
		return enemy >= 4 || (enemy == all && enemy);
	}
	inline int getTowerEffect(const NewWorldBattleHero &defender)
	{
		DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
		if(pdata)
		{
			unsigned cityseq = m_citymap[defender.cid].city.seq;
			if(pdata->city[cityseq].tower.uid)
			{
				if(pdata->city[cityseq].tower.hit)
				{
					--pdata->city[cityseq].tower.hit;
					unsigned dps = pdata->city[cityseq].tower.dps;
					if(pdata->city[cityseq].tower.hit == 0)
						pdata->city[cityseq].tower.clear();
					return dps;
				}
			}
		}
		return 0;
	}
	static inline double getHPExtraEffect(const NewWorldBattleHero &attacker, const NewWorldBattleHero &defender)
	{
		if(attacker.property[NewWorldBattleProperty_hp_extra] <= defender.property[NewWorldBattleProperty_anti_hp_extra])
			return double(0);
		return double(defender.hp) * double(attacker.property[NewWorldBattleProperty_hp_extra] - defender.property[NewWorldBattleProperty_anti_hp_extra]) / double(1000);
	}
	inline bool hasRoad(unsigned cid1, unsigned cid2)
	{
		if(m_roadmap.count(cid1))
		{
			for(vector<unsigned>::const_iterator it=m_roadmap[cid1].begin();it!=m_roadmap[cid1].end();++it)
			{
				if(*it == cid2)
					return true;
			}
		}
		return false;
	}

	inline unsigned getKill(int kill, int otherkill, unsigned kingdom, unsigned level, unsigned otherlevel, unsigned cid, unsigned now)
	{
		double m = double(1), n = double(0);

		if(level >= NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MIN && level <= NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MAX
		&& otherlevel >= NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MIN && otherlevel <= NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MAX)
			n = NEW_WORLD_BATTLE_KILL_ADD_BATTLE * (double)kill / CDataNewWorld::kill_a[level - NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MIN]
			  + NEW_WORLD_BATTLE_KILL_ADD_BATTLE * (double)otherkill / CDataNewWorld::kill_a[otherlevel - NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MIN];

		if(kingdom >= 1 && kingdom <= 4 && m_citymap.count(cid) && m_citymap[cid].city.extraKillTS[kingdom-1] >= now)
			m = double(2);

		return m * n;
	}
	inline void addKill(NewWorldBattleHero &hero, NewWorldBattleHero &otherhero, int kill, int otherkill, unsigned now, DataNewWorldBattle * pdata)
	{
		if(kill < 0 || otherkill < 0)
			return;

		kill = getKill(kill, otherkill, hero.kingdom, hero.level, otherhero.level, hero.cid, now);

		if(isHero(hero.index))
			hero.kill += kill;
		else if(isVision(hero.index))
		{
			NewWorldBattleHeroIndex index(hero.seq, hero.index.uid - 1);
			if(m_heromap.count(index))
			{
				unsigned seq = m_heromap[index].seq;
				pdata->hero[seq].ts = now;
				pdata->hero[seq].kill += kill;
			}
		}
	}
	inline void addKill(NewWorldBattleHero &hero, int kill, unsigned now, DataNewWorldBattle * pdata)
	{
		if(kill < 0)
			return;

		if(isHero(hero.index))
			hero.kill += kill;
		else if(isVision(hero.index))
		{
			NewWorldBattleHeroIndex index(hero.seq, hero.index.uid - 1);
			if(m_heromap.count(index))
			{
				unsigned seq = m_heromap[index].seq;
				pdata->hero[seq].ts = now;
				pdata->hero[seq].kill += kill;
			}
		}
	}

	bool m_init;
	CShareMemory m_sh;
	unsigned m_ts;
	unsigned m_count;
	NewWorldBattleHeroMap m_heromap;
	NewWorldBattleCityMap m_citymap;
	static NewWorldBattleRoadMap m_roadmap;
	unsigned m_kingdomcityNum[4];

	NewWorldBattleChangeMap m_battlechange;
};

#endif /* DATANEWWORLDBATTLE_H_ */
