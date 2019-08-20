/*
 * DataNewWorld.h
 *
 *  Created on: 2014-9-17
 *      Author: Ralf
 */

#ifndef DATANEWWORLD_H_
#define DATANEWWORLD_H_

#define DATA_NEW_WORLD_ENABLE 1

#include <math.h>
#include "Kernel.h"

class CBroadcastNewWorldBattle
{
public:
	CBroadcastNewWorldBattle();
	virtual ~CBroadcastNewWorldBattle();

public:
	int InitSocket();
	int LoginServer();
	int Close();
	int SubmitBattle(unsigned cid, unsigned kingdom, unsigned battle);
private:
	CSocket m_socket;
	uint32_t m_skey;
	string m_tcpserver;
	string m_serverid;
};

/**************tick time*******************/
#ifdef SG_16_VER
#define NEW_WORLD_TICK 					3
#else
#define NEW_WORLD_TICK 					7
#endif
#define NEW_WORLD_DOUBLE_TIME			(30 * 60)			// 30min
#define NEW_WORLD_CHALLENGE_TIME			(5 * 60)			// 5min
/**************hero para*******************/
#define NEW_WORLD_HERO 					50000
#define NEW_WORLD_HERO_INDEX 			10
#define NEW_WORLD_HERO_FREE_INDEX 		6
#define NEW_WORLD_HERO_MIN				5
#define NEW_WORLD_HERO_MIN_F			double(5)
#define NEW_WORLD_HERO_TIME_1			600
#define NEW_WORLD_HERO_TIME_2			480
#define NEW_WORLD_HERO_TIME_3			300
#define NEW_WORLD_HERO_TIME_CITY_3		4
#define NEW_WORLD_HERO_TIME_CITY_2		17
#define NEW_WORLD_HERO_EXPLODE			100
/**************city para*******************/
#define NEW_WORLD_CITY_NEUTRAL  		7
#define NEW_WORLD_CITY_CAPITAL  		1
#define NEW_WORLD_CITY_KINGDOM_CORE		3
#define NEW_WORLD_CITY_KINGDOM_OTHER	68
#define NEW_WORLD_CITY_KINGDOM			(NEW_WORLD_CITY_CAPITAL+NEW_WORLD_CITY_KINGDOM_CORE+NEW_WORLD_CITY_KINGDOM_OTHER)
#define NEW_WORLD_CITY 					(NEW_WORLD_CITY_KINGDOM*3+NEW_WORLD_CITY_NEUTRAL)
#define NEW_WORLD_CITY_KINGDOM_SEQ		100
/**************npc para*******************/
#define NEW_WORLD_CITY_VISION_BASE		70
#define NEW_WORLD_CITY_VISION			100
#define NEW_WORLD_CITY_VISION_NPC		(NEW_WORLD_CITY_VISION + 1)
#define NEW_WORLD_CITY_NPC				50u
#define NEW_WORLD_CITY_NPC_TIME_1		1800
#define NEW_WORLD_CITY_NPC_TIME_2		1500
#define NEW_WORLD_CITY_NPC_TIME_3		1200
#define NEW_WORLD_CITY_NPC_TIME_4		600
#define NEW_WORLD_CITY_NPC_TIME_5		300
#define NEW_WORLD_CITY_NPC_TIME_6		60
#define NEW_WORLD_CITY_NPC_CITY_1		50
#define NEW_WORLD_CITY_NPC_CITY_2		40
#define NEW_WORLD_CITY_NPC_CITY_3		30
#define NEW_WORLD_CITY_NPC_CITY_4		20
#define NEW_WORLD_CITY_NPC_CITY_5		10
#define NEW_WORLD_CITY_OCCUPY_NPC		5
/**************history para*******************/
#define NEW_WORLD_HISTORY 				24
/**************reward para*******************/
#define NEW_WORLD_REWARD 				5
/**************para define*******************/
#define NEW_WORLD_HERO_LEVEL 		 120
#define NEW_WORLD_HERO_DAY 	 		 218
#define NEW_WORLD_HERO_NPC_DEFAULT 	 47
/**************hero define*******************/
#define NEW_WORLD_HERO_RECOVER 1000
enum NewWorldProperty
{
	NewWorldProperty_hp					= 0,
	NewWorldProperty_attack				= 1,
	NewWorldProperty_defence			= 2,
	NewWorldProperty_speed				= 3,
	NewWorldProperty_crit				= 4,
	NewWorldProperty_anti_crit			= 5,
	NewWorldProperty_crit_times			= 6,
	NewWorldProperty_anti_crit_times	= 7,
	NewWorldProperty_dodge				= 8,
	NewWorldProperty_anti_dodge			= 9,
	NewWorldProperty_block				= 10,
	NewWorldProperty_anti_block			= 11,
	NewWorldProperty_extra				= 12,
	NewWorldProperty_anti_extra			= 13,
	NewWorldProperty_reflect			= 14,
	NewWorldProperty_anti_reflect		= 15,
	NewWorldProperty_type_extra			= 16,
	NewWorldProperty_anti_speed			= 17,
	NewWorldProperty_explode			= 18,
	NewWorldProperty_F_A_1				= 19,
	NewWorldProperty_F_A_2				= 20,
	NewWorldProperty_F_A_3				= 21,
	NewWorldProperty_F_A_4				= 22,
	NewWorldProperty_F_A_5				= 23,
	NewWorldProperty_F_D_1				= 24,
	NewWorldProperty_F_D_2				= 25,
	NewWorldProperty_F_D_3				= 26,
	NewWorldProperty_F_D_4				= 27,
	NewWorldProperty_F_D_5				= 28,
	NewWorldProperty_A_D_1				= 29,
	NewWorldProperty_A_D_2				= 30,
	NewWorldProperty_NB					= 31,
	NewWorldProperty_hp_extra			= 32,
	NewWorldProperty_anti_hp_extra		= 33,

	NewWorldProperty_max
};
enum NewWorldHeroJob
{
	NewWorldHeroJob_warrior	= 0,
	NewWorldHeroJob_shooter	= 1,
	NewWorldHeroJob_wizard	= 2,

	NewWorldHeroJob_max
};
enum NewWorldHeroStatus
{
	NewWorldHeroStatus_wait_defence	= 0,
	NewWorldHeroStatus_defence  	= 1,
	NewWorldHeroStatus_wait_attack	= 2,
	NewWorldHeroStatus_attack		= 3,
	NewWorldHeroStatus_wait_move	= 4,
	NewWorldHeroStatus_move			= 5,

	NewWorldHeroStatus_max
};
enum NewWorldHeroBuff
{
	NewWorldHeroBuff_explode				= 0,
	NewWorldHeroBuff_max					= 16,
};
enum NewWorldHeroAttackResult
{
	NewWorldHeroAttackResult_none			= 0,
	NewWorldHeroAttackResult_attacker_win	= 1,
	NewWorldHeroAttackResult_defender_win	= 2,
	NewWorldHeroAttackResult_all_die		= 3,
};
struct NewWorldHeroIndex
{
	unsigned uid, index;
	NewWorldHeroIndex()
	{
		uid = index = 0;
	}
	NewWorldHeroIndex(unsigned uid1, unsigned index1)
	{
		uid = uid1;
		index = index1;
	}
	NewWorldHeroIndex(const NewWorldHeroIndex& node)
	{
		uid = node.uid;
		index = node.index;
	}
	void clear()
	{
		uid = index = 0;
	}
	NewWorldHeroIndex& operator =(const NewWorldHeroIndex& node)
	{
		uid = node.uid;
		index = node.index;
		return *this;
	}
	bool operator <(const NewWorldHeroIndex& other) const
	{
		if(uid != other.uid)
			return uid < other.uid;
		else
			return index < other.index;
	}
	bool operator ==(const NewWorldHeroIndex& other) const
	{
		if(uid == other.uid && index == other.index)
			return true;
		return false;
	}
	bool operator !=(const NewWorldHeroIndex& other) const
	{
		if(uid == other.uid && index == other.index)
			return false;
		return true;
	}
};
struct NewWorldHero
{
	NewWorldHeroIndex index;
	unsigned seq, hid, kingdom, job, level, type, cid, status, next, ts;
	int hp;
	char name[32];
	char icon[64];
	int property[NewWorldProperty_max];
	unsigned kill, buff;
	unsigned inc_kill;
	NewWorldHero()
	{
		seq = hid = kingdom = job = level = hp = type = cid = status = next = ts = 0;
		memset(name, 0, sizeof(name));
		memset(icon, 0, sizeof(icon));
		memset(property, 0, sizeof(property));
		kill = buff = 0;
		inc_kill =0;
	}
	bool copy(NewWorldHero &other);
	bool recover(unsigned city)
	{
		if(hp == property[NewWorldProperty_hp])
			return false;
		else if(hp < property[NewWorldProperty_hp] && hp >= 0)
		{
			double total = NEW_WORLD_HERO_TIME_1;
			if(city <= NEW_WORLD_HERO_TIME_CITY_3)
				total = NEW_WORLD_HERO_TIME_3;
			else if(city <= NEW_WORLD_HERO_TIME_CITY_2)
				total = NEW_WORLD_HERO_TIME_2;
			int add = (double)property[NewWorldProperty_hp] * (double)NEW_WORLD_TICK / total;
			if(add == 0)
				add = 1;
			hp += add;
			if(hp > property[NewWorldProperty_hp])
				hp = property[NewWorldProperty_hp];
		}
		else if(hp > property[NewWorldProperty_hp])
			hp = property[NewWorldProperty_hp];
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
	bool isBuff(unsigned b)
	{
		return buff & (0x0001 << b) ;
	}
	void addBuff(unsigned b)
	{
		buff |= (0x0001 << b) ;
	}
	void delBuff(unsigned b)
	{
		buff &= (~(0x0001 << b)) ;
	}
};
/**************city define*******************/
enum NewWorldJMID
{
	e_JM_none		= 0,

	e_JM_1			= 1,//调虎离山
	e_JM_2			= 2,//十面埋伏
	e_JM_3			= 3,//瞒天过海
	e_JM_4			= 4,//空城计

	e_JM_max,
};
#define NEW_WORLD_BUY_NPC 500u
#define NEW_WORLD_JM_LEVEL 3

enum NewWorldCityType
{
	NewWorldCityType_capital	= 0,
	NewWorldCityType_core	  	= 1,
	NewWorldCityType_small		= 2,
	NewWorldCityType_neutral	= 3,

	NewWorldCityType_max
};
struct NewWorldTower
{
	unsigned uid, dps, hit;
	NewWorldTower()
	{
		uid = dps = hit = 0;
	}
	void clear()
	{
		uid = dps = hit = 0;
	}
};
struct NewWorldJM
{
	unsigned jm3ts, jm4ts;
	NewWorldJM()
	{
		jm3ts = jm4ts = 0;
	}
};
struct NewWorldCity
{
	unsigned seq, cid, uid, kingdom, countV, countN, npcts, reward, nextReward, ts;
	int count[3];
	char name[32];
	unsigned extraKillTS[3];
	unsigned rushTS[3];
	unsigned lastChallengeTS;
	NewWorldHeroIndex attacker, defender;
	NewWorldHero vision[NEW_WORLD_CITY_VISION_NPC];//1 for npc
	NewWorldTower tower;
	NewWorldJM jm;
	NewWorldCity()
	{
		seq = cid = uid = kingdom = count[0] = count[1] = count[2] = countV = countN = npcts = reward = nextReward = ts = 0;
		lastChallengeTS = 0;
		memset(extraKillTS, 0, sizeof(extraKillTS));
		memset(rushTS, 0, sizeof(rushTS));
		memset(name,0,sizeof(name));
	}
	void MakeReward();
	bool Fighting() const
	{
		switch(kingdom)
		{
		case 0:
			return count[0] > 0 || count[1] > 0 || count[2] > 0;
		case 1:
			return count[1] > 0 || count[2] > 0;
		case 2:
			return count[0] > 0 || count[2] > 0;
		case 3:
			return count[0] > 0 || count[1] > 0;
		}
		return false;
	}
	bool bug() const
	{
		return count[0] < 0 || count[1] < 0 || count[2] < 0;
	}
};
/**************mission define*******************/
enum NewWorldMissonStatus
{
	NewWorldMissonStatus_defend_lose		= 0,
	NewWorldMissonStatus_defend_win  		= 1,
	NewWorldMissonStatus_defending			= 2,
	NewWorldMissonStatus_defend_over		= 3,
	NewWorldMissonStatus_attack_lose		= 4,
	NewWorldMissonStatus_attack_win  		= 5,
	NewWorldMissonStatus_attacking			= 6,
	NewWorldMissonStatus_attack_over		= 7,
	NewWorldMissonStatus_attack_fast_over		= 8,
	NewWorldMissonStatus_attack_fast_win		= 9,

	NewWorldMissonStatus_max
};
struct NewWorldMisson
{
	unsigned defend, attack, defendStatus, attackStatus;
	NewWorldMisson()
	{
		defend = attack = defendStatus = attackStatus = 0;
	}
};
/**************data define*******************/
struct DataNewWorld
{
	unsigned ts, changets, count;
	NewWorldHero hero[NEW_WORLD_HERO];
	NewWorldCity city[NEW_WORLD_CITY];
	unsigned history[NEW_WORLD_HISTORY][NEW_WORLD_CITY];
	NewWorldMisson mission[3];
	DataNewWorld()
	{
		count = changets = ts = 0;
	}
};
struct DataNewWorldBattleChange
{
	unsigned cid, kingdom, battle;
	DataNewWorldBattleChange()
	{
		cid = kingdom = battle = 0;
	}
};
struct DataNewWorldCityChange
{
	unsigned cid, uid;
	DataNewWorldCityChange()
	{
		cid = uid = 0;
	}
};
struct DataNewWorldChange
{
	DataNewWorldBattleChange battle[NEW_WORLD_CITY];
	DataNewWorldCityChange city[NEW_WORLD_CITY];
	void clear()
	{
		memset(battle,0,sizeof(battle));
		memset(city,0,sizeof(city));
	}
};
struct DataNewWorldNPCTime
{
	unsigned NPCTime[3];
	DataNewWorldNPCTime(unsigned n1, unsigned n2, unsigned n3)
	{
		NPCTime[0] = n1;
		NPCTime[1] = n2;
		NPCTime[2] = n3;
	}
	DataNewWorldNPCTime()
	{
		NPCTime[0] = NPCTime[1] = NPCTime[2] = 900;
	}
	unsigned GetNPCTime(unsigned kingdom)
	{
		if(kingdom <= 3 && kingdom >= 1)
			return NPCTime[kingdom - 1];
		return 900;
	}
};
/**************static define*******************/
typedef map<NewWorldHeroIndex, NewWorldHero> NewWorldHeroMap;
typedef multimap<pair<unsigned, unsigned>, NewWorldHeroIndex> NewWorldCityQueue;
struct NewWorldCityBattle
{
	NewWorldCity city;
	NewWorldCityQueue attacker, defender;
};
typedef map<unsigned, NewWorldCityBattle> NewWorldCityMap;
#define NEW_WORLD_ROAD 324
typedef map<unsigned, vector<unsigned> > NewWorldRoadMap;
#define NEW_WORLD_MISSION_CITY 44
#define NEW_WORLD_REDUCE double(0.65)
#define NEW_WORLD_VISION_REDUCE double(0.8)
#define NEW_WORLD_CITY_REDUCE double(0.5)
#define NEW_WORLD_MOVE_LEVEL 150
#define NEW_WORLD_RUSH_MIN 2
#define NEW_WORLD_KILL_REWARD_LEVEL_MIN 35
#define NEW_WORLD_KILL_REWARD_LEVEL_MAX 120
#define NEW_WORLD_KILL_REWARD_KILL 3
#define NEW_WORLD_KILL_REWARD_P 4
typedef map<unsigned,DataNewWorldBattleChange> NewWorldChangeMap;
typedef map<unsigned,DataNewWorldNPCTime> NewWorldNPCTimeMap;
#define NEW_WORLD_KILL_ADD_BATTLE 		double(33)
#define NEW_WORLD_KILL_ADD_LAST 		50
#define NEW_WORLD_KILL_ADD_QUEUE 		20
#define NEW_WORLD_KILL_ADD_CLONE 		20
#define NEW_WORLD_KILL_ADD_RUSH 		10
#define NEW_WORLD_DOUBLE_KILL			50
#define NEW_WORLD_COLLECTOTHER_KILL		50
/********************************************/
class CDataNewWorld
{
public:
	CDataNewWorld();
	virtual ~CDataNewWorld();
	void SetTool(bool tool) { m_tool = tool; }
	int Init(const string &path, semdat sem=sem_new_world);

	unsigned GetTS() { return m_ts; }

	const NewWorldCityMap& GetWorld();
	const unsigned* GetHistory(unsigned index);
	const NewWorldMisson* GetMission();
	const NewWorldCityBattle& GetCity(unsigned cid);
	const NewWorldHero&  GetHero(NewWorldHeroIndex index);
	const NewWorldHeroMap&  GetAllHero();
	const NewWorldChangeMap& GetChangeMap(){return m_battlechange;}
	void ClearChangeMap(){m_battlechange.clear();}

	int SetHero(NewWorldHero &hero, bool &fix);
	int Move(NewWorldHeroIndex index, unsigned cid, bool leave, unsigned fly, unsigned &status);
	int Change(NewWorldHeroIndex index, unsigned type);
	int Clone(NewWorldHeroIndex index, bool issuper=false);
	int Rush(NewWorldHeroIndex index, NewWorldHero &other, NewWorldHero &end);
	int Recover(NewWorldHeroIndex index, unsigned num);
	int Explode(NewWorldHeroIndex index);

	int Challenge(unsigned uid, unsigned &olduid, unsigned cid, string &name, unsigned k);
	int SetChallengeTS(unsigned cid, int set, unsigned k);
	int Collect(unsigned uid, unsigned cid, unsigned &reward);
	int Double(unsigned uid, unsigned kingdom, unsigned cid);
	int rushTS(unsigned uid, unsigned kingdom, unsigned cid);
	int CollectOther(unsigned uid, unsigned cid);

	int Buildyjt(NewWorldHeroIndex index);

	int UseJM(unsigned uid, unsigned jm, unsigned lv, unsigned cid, unsigned kingdom);
	int jm1(unsigned jm, unsigned lv, unsigned cid, unsigned kingdom);
	int jm2(unsigned jm, unsigned lv, unsigned cid, unsigned kingdom);
	int jm3(unsigned jm, unsigned lv, unsigned cid, unsigned kingdom);
	int jm4(unsigned jm, unsigned lv, unsigned cid, unsigned kingdom);
	int BuyNPC(unsigned uid, unsigned cid, unsigned kingdom);

	int WorldReward();
	int CityReward();
	int StartMission();
	int StartMission1();
	int StartMission2();
	int EndMission();
	int KillReward();
	int change();

	static unsigned getFastMissionStartTime()
	{
	    time_t t = time(NULL);
	    struct tm * tm= localtime(&t);
	    tm->tm_hour = 20;
	    tm->tm_min = 0;
	    tm->tm_sec = 0;
	    return  mktime(tm);
	}

	static unsigned getFastMissionEndTime()
	{
	    time_t t = time(NULL);
	    struct tm * tm= localtime(&t);
	    tm->tm_hour = 20;
	    tm->tm_min = 30;
	    tm->tm_sec = 0;
	    return  mktime(tm);
	}

	static inline bool IsInCity(unsigned status)
	{
		return status != NewWorldHeroStatus_wait_move && status != NewWorldHeroStatus_move;
	}
	static inline bool CanMove(unsigned status)
	{
		return status != NewWorldHeroStatus_wait_move
			&& status != NewWorldHeroStatus_move
			&& status != NewWorldHeroStatus_defence
			&& status != NewWorldHeroStatus_attack;
	}
	static inline bool IsDefender(unsigned status)
	{
		return status == NewWorldHeroStatus_wait_defence || status == NewWorldHeroStatus_defence;
	}
	static inline bool IsAttacker(unsigned status)
	{
		return status == NewWorldHeroStatus_wait_attack || status == NewWorldHeroStatus_attack;
	}
	static inline bool IsFighting(unsigned status)
	{
		return status == NewWorldHeroStatus_attack || status == NewWorldHeroStatus_defence;
	}
	static inline bool IsReady(unsigned status)
	{
		return status == NewWorldHeroStatus_wait_defence || status == NewWorldHeroStatus_wait_attack || status == NewWorldHeroStatus_move;
	}

	static inline unsigned getCapital(unsigned kingdom)
	{
		if(kingdom > 3 || kingdom < 1)
			return 1;
		return kingdom*NEW_WORLD_CITY_KINGDOM_SEQ + NEW_WORLD_CITY_CAPITAL;
	}
	static inline unsigned getCityType(unsigned cid)
	{
		if(cid <= NEW_WORLD_CITY_KINGDOM_SEQ)
			return NewWorldCityType_neutral;

		cid = cid % NEW_WORLD_CITY_KINGDOM_SEQ;
		if(cid ==  NEW_WORLD_CITY_CAPITAL)
			return NewWorldCityType_capital;
		if(cid <=  NEW_WORLD_CITY_KINGDOM_CORE + NEW_WORLD_CITY_CAPITAL)
			return NewWorldCityType_core;
		return NewWorldCityType_small;
	}
	static inline bool isCapital(unsigned cid)
	{
		return getCityType(cid) == NewWorldCityType_capital;
	}
	static inline bool isCore(unsigned cid)
	{
		return getCityType(cid) == NewWorldCityType_core;
	}
	static inline bool isNeutral(unsigned cid)
	{
		return getCityType(cid) == NewWorldCityType_neutral;
	}
	static inline bool canAttack(unsigned cid)
	{
		unsigned type = getCityType(cid);
		return  type == NewWorldCityType_neutral || type == NewWorldCityType_small;
	}

	static inline bool isVision(NewWorldHeroIndex index)
	{
		return index.uid < ADMIN_UID && index.index < NEW_WORLD_CITY_VISION;
	}
	static inline bool isNPC(NewWorldHeroIndex index)
	{
		return index.uid == ADMIN_UID && index.index == NEW_WORLD_CITY_VISION;
	}
	static inline bool notHero(NewWorldHeroIndex index)
	{
		return index.uid <= ADMIN_UID && index.index < NEW_WORLD_CITY_VISION_NPC;
	}
	static inline bool isHero(NewWorldHeroIndex index)
	{
		return IsValidUid(index.uid) && index.index < NEW_WORLD_HERO_INDEX;
	}
	static inline bool isMissionOn(unsigned status)
	{
		return status == NewWorldMissonStatus_defending || status == NewWorldMissonStatus_defend_over || status == NewWorldMissonStatus_attacking || status == NewWorldMissonStatus_attack_over || status == NewWorldMissonStatus_attack_fast_over;
	}
	static inline bool isMissionIng(unsigned status)
	{
		return status == NewWorldMissonStatus_defending || status == NewWorldMissonStatus_attacking;
	}
	static inline bool isMissionWin(unsigned status)
	{
		return status == NewWorldMissonStatus_defend_win || status == NewWorldMissonStatus_attack_win || status == NewWorldMissonStatus_attack_over || status == NewWorldMissonStatus_attack_fast_over;
	}
	static inline bool isMissionLose(unsigned status)
	{
		return status == NewWorldMissonStatus_defend_lose || status == NewWorldMissonStatus_attack_lose || status == NewWorldMissonStatus_defend_over;
	}

	int PrintHero();
	int PrintCity();
	int Watch();
	int Fix();
	int Reset();
	int Back();
	int Test(NewWorldHero &attacker, unsigned hpa, NewWorldHero &defender, unsigned hpd);
	int Time();
	int FixOld();

	static int GetMoveR1(unsigned level);
	static unsigned GetKillExp(unsigned kill, unsigned level);
	static unsigned GetKillReward1(unsigned rank);
	static unsigned GetKillReward2(unsigned rank);
	static unsigned GetKillRewardNew(unsigned rank);

	static const unsigned c_crit_dodge[NEW_WORLD_HERO_LEVEL];
	static const unsigned c_attack[NEW_WORLD_HERO_LEVEL];

	static const unsigned npc_day_default[NEW_WORLD_HERO_DAY];
	static const unsigned npc_level[NEW_WORLD_HERO_NPC_DEFAULT];
	static const unsigned npc_property[3][NEW_WORLD_HERO_NPC_DEFAULT][NewWorldProperty_max];
	static const unsigned m_npctime[NEW_WORLD_CITY][4];

	static const unsigned road_map[NEW_WORLD_ROAD][2];
	static const int move_r1[NEW_WORLD_MOVE_LEVEL];

	static const unsigned kill_reward_kill[NEW_WORLD_KILL_REWARD_LEVEL_MAX-NEW_WORLD_KILL_REWARD_LEVEL_MIN+1][NEW_WORLD_KILL_REWARD_KILL];
	static const unsigned kill_reward_p[NEW_WORLD_KILL_REWARD_LEVEL_MAX-NEW_WORLD_KILL_REWARD_LEVEL_MIN+1][NEW_WORLD_KILL_REWARD_P];
	static const unsigned kill_a[NEW_WORLD_KILL_REWARD_LEVEL_MAX - NEW_WORLD_KILL_REWARD_LEVEL_MIN + 1];

	static const unsigned mission_city[3][3][NEW_WORLD_MISSION_CITY];

protected:
	int checkTick();
	int sync(DataNewWorld * pdata);//must in lock
	void _fix(DataNewWorld *pdata, unsigned ts);//must in lock

	static inline unsigned getNPCTime(unsigned cityNum)
	{
		if(cityNum > NEW_WORLD_CITY_NPC_CITY_1)
			return NEW_WORLD_CITY_NPC_TIME_1;
		else if(cityNum > NEW_WORLD_CITY_NPC_CITY_2)
			return NEW_WORLD_CITY_NPC_TIME_2;
		else if(cityNum > NEW_WORLD_CITY_NPC_CITY_3)
			return NEW_WORLD_CITY_NPC_TIME_3;
		else if(cityNum > NEW_WORLD_CITY_NPC_CITY_4)
			return NEW_WORLD_CITY_NPC_TIME_4;
		else if(cityNum > NEW_WORLD_CITY_NPC_CITY_5)
			return NEW_WORLD_CITY_NPC_TIME_5;

		return NEW_WORLD_CITY_NPC_TIME_6;
	}
	static inline void makeNPC(NewWorldHero &hero)
	{
		unsigned job = hero.job % NewWorldHeroJob_max;
		unsigned type = NewWorldHeroJob_shooter;//Math::GetRandomInt(3);
		unsigned day = min(NEW_WORLD_HERO_DAY - 1, max(0, CTime::GetDayInterval(Config::GetIntValue(CONFIG_OPEN_TS), Time::GetGlobalTime())));
		unsigned npcdefault = npc_day_default[day];

		hero.index.uid = ADMIN_UID;
		hero.index.index = NEW_WORLD_CITY_VISION;
		hero.seq = ADMIN_UID;
		hero.hid = job;
		hero.job = job;
		hero.level = npc_level[npcdefault];
		hero.type = type;
		hero.status = NewWorldHeroStatus_defence;
		hero.name[0] = 'N';hero.name[1] = 'P';hero.name[2] = 'C';hero.name[3] = 0;
		for(unsigned i=0;i<NewWorldProperty_max;++i)
			hero.property[i] = npc_property[job][npcdefault][i];
		hero.hp = hero.property[NewWorldProperty_hp];
		hero.ts = hero.next = Time::GetGlobalTime();
	}
public:
	static unsigned attacking(NewWorldHero &attacker, NewWorldHero &defender, int &attackkill, int &defendkill, bool ce = false, int towerEffect = 0)
	{
		//step 1: damage of type vs job
		//debug_log("----start----");
		//debug_log("attacker=%u,%u,city=%u,job=%u,type=%u,hp=%u,maxhp=%u,att=%u,def=%u",attacker.index.uid,attacker.index.index,attacker.cid,attacker.job,attacker.type,attacker.hp,attacker.property[NewWorldProperty_hp],attacker.property[NewWorldProperty_attack],attacker.property[NewWorldProperty_defence]);
		//debug_log("defender=%u,%u,city=%u,job=%u,type=%u,hp=%u,maxhp=%u,att=%u,def=%u",defender.index.uid,defender.index.index,defender.cid,defender.job,defender.type,defender.hp,defender.property[NewWorldProperty_hp],defender.property[NewWorldProperty_attack],defender.property[NewWorldProperty_defence]);
		if(attacker.hp > attacker.property[NewWorldProperty_hp])
			attacker.hp = attacker.property[NewWorldProperty_hp];
		if(defender.hp > defender.property[NewWorldProperty_hp])
			defender.hp = defender.property[NewWorldProperty_hp];

		bool mha = attacker.hp == attacker.property[NewWorldProperty_hp];
		bool mhd = defender.hp == defender.property[NewWorldProperty_hp];
		double ha = getHPEffect(attacker);
		double hd = getHPEffect(defender);
		bool visiona = isVision(attacker.index);
		bool visiond = isVision(defender.index);

		double typea = getTypeEffect(attacker, defender);
		double typed = getTypeEffect(defender, attacker);
		double dk1 = max(NEW_WORLD_HERO_MIN_F, ((double)attacker.property[NewWorldProperty_hp])*typed + (double)defender.property[NewWorldProperty_type_extra]);
		double ak1 = max(NEW_WORLD_HERO_MIN_F, ((double)defender.property[NewWorldProperty_hp])*typea + (double)attacker.property[NewWorldProperty_type_extra]);
		dk1 *= hd;
		ak1 *= ha;
		if(ce)
			dk1 *= NEW_WORLD_CITY_REDUCE;
		/***********nerf vision***************/
		if(visiond)
			dk1 *= NEW_WORLD_VISION_REDUCE;
		if(visiona)
			ak1 *= NEW_WORLD_VISION_REDUCE;
		/*************************************/
		if(mhd)
			dk1 += double(defender.property[NewWorldProperty_NB]);
		if(mha)
			ak1 += double(attacker.property[NewWorldProperty_NB]);

		dk1 += getHPExtraEffect(defender, attacker);
		ak1 += getHPExtraEffect(attacker, defender);

		int dk1i = (int)dk1;
		int ak1i = (int)ak1;
		if(dk1i > attacker.hp)
			dk1i = attacker.hp;
		if(ak1i > defender.hp)
			ak1i = defender.hp;
		attacker.hp -= (dk1i + towerEffect);
		defender.hp -= ak1i;

		//debug_log("----1----");
		//debug_log("uid=%u,hpa=%u,ak1=%u,ha=%f",attacker.index.uid,attacker.hp,ak1i,ha);
		//debug_log("uid=%u,hpd=%u,dk1=%u,hd=%f",attacker.index.uid,defender.hp,dk1i,hd);

		//debug_log("step1:attacker.hp=%u,defender.hp=%u",attacker.hp,defender.hp);

		attackkill = ak1i;
		defendkill = dk1i;

		if(attacker.hp < NEW_WORLD_HERO_MIN)
		{
			defender.hp -= attacker.property[NewWorldProperty_explode];
			if(attacker.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiond)
					defender.hp -= defender.property[NewWorldProperty_hp] / 10;
				else
					defender.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}
		if(defender.hp < NEW_WORLD_HERO_MIN)
		{
			attacker.hp -= defender.property[NewWorldProperty_explode];
			if(defender.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiona)
					attacker.hp -= attacker.property[NewWorldProperty_hp] / 10;
				else
					attacker.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}

		if(attacker.hp < NEW_WORLD_HERO_MIN && defender.hp < NEW_WORLD_HERO_MIN)
		{
			attacker.hp = defender.hp = 0;
			attacker.buff = defender.buff = 0;
			return NewWorldHeroAttackResult_all_die;
		}
		else if(attacker.hp < NEW_WORLD_HERO_MIN)
		{
			attacker.hp = 0;
			attacker.buff = 0;
			return NewWorldHeroAttackResult_defender_win;
		}
		else if(defender.hp < NEW_WORLD_HERO_MIN)
		{
			defender.hp = 0;
			defender.buff = 0;
			return NewWorldHeroAttackResult_attacker_win;
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
		//dps effected by city
		if(ce)
		{
			dpsd *= NEW_WORLD_CITY_REDUCE;
			//debug_log("CityEffect:dpsd=%f",dpsd);
		}
		/***********nerf vision***************/
		if(visiona)
			dpsa *= NEW_WORLD_VISION_REDUCE;
		if(visiond)
			dpsd *= NEW_WORLD_VISION_REDUCE;
		/*************************************/

		//time=min(hp/dps)
		double timea = ((double)attacker.hp)/max(dpsd, double(1));
		double timed = ((double)defender.hp)/max(dpsa, double(1));
		double time = min(timea, timed);
		int dk2 = max(NEW_WORLD_HERO_MIN_F, dpsd * time);
		int ak2 = max(NEW_WORLD_HERO_MIN_F, dpsa * time);
		if(dk2 > attacker.hp)
			dk2 = attacker.hp;
		if(ak2 > defender.hp)
			ak2 = defender.hp;
		attacker.hp -= dk2;
		defender.hp -= ak2;

		//debug_log("----2----");
		//debug_log("uid=%u,hpa=%u,ak2=%u,dpsa=%f,ja=%f,sa=%f,pa=%f,ca=%f,aa=%f,la=%f,ra=%f,ea=%f,fa=%f,ha=%f",attacker.index.uid,attacker.hp,ak2,dpsa,ja,sa,pa,ca,aa,la,ra,ea,fa,ha);
		//debug_log("uid=%u,hpd=%u,dk2=%u,dpsd=%f,jd=%f,sd=%f,pd=%f,cd=%f,ad=%f,ld=%f,rd=%f,ed=%f,fd=%f,hd=%f",attacker.index.uid,defender.hp,dk2,dpsd,jd,sd,pd,cd,ad,ld,rd,ed,fd,hd);

		//debug_log("step2:attacker.hp=%u,defender.hp=%u",attacker.hp,defender.hp);
		//debug_log("----end----");

		attackkill += ak2;
		defendkill += dk2;

		if(attacker.hp < NEW_WORLD_HERO_MIN)
		{
			defender.hp -= attacker.property[NewWorldProperty_explode];
			if(attacker.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiond)
					defender.hp -= defender.property[NewWorldProperty_hp] / 10;
				else
					defender.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}
		if(defender.hp < NEW_WORLD_HERO_MIN)
		{
			attacker.hp -= defender.property[NewWorldProperty_explode];
			if(defender.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiona)
					attacker.hp -= attacker.property[NewWorldProperty_hp] / 10;
				else
					attacker.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}

		if(attacker.hp < NEW_WORLD_HERO_MIN && defender.hp < NEW_WORLD_HERO_MIN)
		{
			attacker.hp = defender.hp = 0;
			attacker.buff = defender.buff = 0;
			return NewWorldHeroAttackResult_all_die;
		}
		else if(attacker.hp < NEW_WORLD_HERO_MIN)
		{
			attacker.hp = 0;
			attacker.buff = 0;
			return NewWorldHeroAttackResult_defender_win;
		}
		else if(defender.hp < NEW_WORLD_HERO_MIN)
		{
			defender.hp = 0;
			defender.buff = 0;
			return NewWorldHeroAttackResult_attacker_win;
		}

		return NewWorldHeroAttackResult_all_die;
	}
protected:
	static inline double getTypeEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		if(attacker.type == defender.job)
			return (double)(Math::GetRandomInt(40) + 10)/double(1000);
		return double(0);
	}
	static inline double getJobEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		if((attacker.job + 1)%NewWorldHeroJob_max == defender.job)
			return double(1.05);
		return double(1);
	}
	static inline double getRandomEffect()
	{
		return (double)(Math::GetRandomInt(200) + 900)/double(1000);
	}
	static inline double getSpeedEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		return max(double(1), min(double(4),
			(double)attacker.property[NewWorldProperty_speed]/double(100)
			* max(double(0.67), min(double(1), double(1)-(double)defender.property[NewWorldProperty_anti_speed])/double(100))));
	}
	static inline double getProtectEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		return max(double(0), double(1)
			- NEW_WORLD_REDUCE * double(0.5) * min(double(1), max(double(0), (double)defender.property[NewWorldProperty_block]
			      -(double)attacker.property[NewWorldProperty_anti_block])/double(1000)))
			* max(double(0), double(1) - NEW_WORLD_REDUCE * min(double(0.8), max(double(0),((double)defender.property[NewWorldProperty_dodge]-(double)attacker.property[NewWorldProperty_anti_dodge])
					/(double)c_crit_dodge[defender.level-1])));
	}
	static inline double getCritEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		return (double(1)
			+ NEW_WORLD_REDUCE * min(double(0.8), max(double(0),
				((double)attacker.property[NewWorldProperty_crit]-(double)defender.property[NewWorldProperty_anti_crit])
					/(double)c_crit_dodge[attacker.level-1]))
			* max(attacker.property[NewWorldProperty_crit_times]
				  -defender.property[NewWorldProperty_anti_crit_times],0)/double(1000));
	}
	static inline double getAttackEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		return (double)c_attack[attacker.level-1]
		   * (double)attacker.property[NewWorldProperty_attack]/max(double(1), max((double)defender.property[NewWorldProperty_defence]*double(0.8), (double)defender.property[NewWorldProperty_defence]*double(1000-attacker.property[NewWorldProperty_A_D_1])/double(1000)-double(attacker.property[NewWorldProperty_A_D_2])));
	}
	static inline double getLevelEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		return double(2)*(double)attacker.level/(double)(attacker.level+defender.level);
	}
	static inline double getReflectEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		return double(0.5)*(double)max(attacker.property[NewWorldProperty_reflect]-defender.property[NewWorldProperty_anti_reflect],0)/double(1000);
	}
	static inline double getExtraEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		return (double)max(0,attacker.property[NewWorldProperty_extra]-defender.property[NewWorldProperty_anti_extra]);
	}
	static inline double getFEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		for(unsigned i=NewWorldProperty_F_A_1;i<=NewWorldProperty_F_A_5;++i)
		{
			if(attacker.property[i])
				return (double)max(0,attacker.property[i]-defender.property[i+5]);
		}
		return double(0);
	}
	static inline double getHPEffect(const NewWorldHero &attacker)
	{
		return ((double)attacker.hp)/(double)attacker.property[NewWorldProperty_hp];
	}
	inline bool getCityEffect(const NewWorldHero &defender)
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
	inline int getTowerEffect(const NewWorldHero &defender)
	{
		DataNewWorld *pdata = (DataNewWorld *)m_sh.GetAddress();
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
	static inline double getHPExtraEffect(const NewWorldHero &attacker, const NewWorldHero &defender)
	{
		if(attacker.property[NewWorldProperty_hp_extra] <= defender.property[NewWorldProperty_anti_hp_extra])
			return double(0);
		return double(defender.hp) * double(attacker.property[NewWorldProperty_hp_extra] - defender.property[NewWorldProperty_anti_hp_extra]) / double(1000);
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
		double m = double(1), n = double(0), k = double(1);

		if(level >= NEW_WORLD_KILL_REWARD_LEVEL_MIN && level <= NEW_WORLD_KILL_REWARD_LEVEL_MAX
		&& otherlevel >= NEW_WORLD_KILL_REWARD_LEVEL_MIN && otherlevel <= NEW_WORLD_KILL_REWARD_LEVEL_MAX)
			n = NEW_WORLD_KILL_ADD_BATTLE * (double)kill / kill_a[level - NEW_WORLD_KILL_REWARD_LEVEL_MIN]
			  + NEW_WORLD_KILL_ADD_BATTLE * (double)otherkill / kill_a[otherlevel - NEW_WORLD_KILL_REWARD_LEVEL_MIN];

		if ((kingdom >= 1) && (kingdom <= 3) && (m_citymap.count(cid))
				&& (m_citymap[cid].city.extraKillTS[kingdom - 1] >= now))
			m = double(2);

		if ((kingdom >= 1) && (kingdom <= 3) && isMissionOn(m_mission[kingdom -1].attackStatus))
			k = double(1.5);

		return m * n * k;
	}
	inline void addKill(NewWorldHero &hero, NewWorldHero &otherhero, int kill, int otherkill, unsigned now, DataNewWorld *pdata)
	{
		if (kill < 0 || otherkill < 0)
			return ;

		kill = getKill(kill, otherkill, hero.kingdom, hero.level, otherhero.level, hero.cid, now);

		if (isHero(hero.index))
		{
			hero.kill += kill;
			if((hero.kingdom >= 1) && (hero.kingdom <= 3) &&isMissionOn(m_mission[hero.kingdom-1].attackStatus))
				hero.inc_kill += kill;
		}
		else if (isVision(hero.index))
		{
			NewWorldHeroIndex index(hero.seq, hero.index.uid - 1);
			if (m_heromap.count(index))
			{
				unsigned seq = m_heromap[index].seq;
				pdata->hero[seq].ts = now;
				pdata->hero[seq].kill += kill;
				if((hero.kingdom >= 1) && (hero.kingdom <= 3) && isMissionOn(m_mission[hero.kingdom-1].attackStatus))
					pdata->hero[seq].inc_kill += kill;
			}
		}
	}
	inline void addKill(NewWorldHero &hero, int kill, unsigned now, DataNewWorld *pdata)
	{
		if (kill < 0)
			return ;


		if (isHero(hero.index))
		{
			hero.kill += kill;
			if((hero.kingdom >= 1) && (hero.kingdom <= 3) && isMissionOn(m_mission[hero.kingdom-1].attackStatus))
				hero.inc_kill += kill;
		}
		else if (isVision(hero.index))
		{
			NewWorldHeroIndex index(hero.seq, hero.index.uid - 1);
			if (m_heromap.count(index))
			{
				unsigned seq = m_heromap[index].seq;
				pdata->hero[seq].ts = now;
				pdata->hero[seq].kill += kill;
				if((hero.kingdom >= 1) && (hero.kingdom <= 3) && isMissionOn(m_mission[hero.kingdom-1].attackStatus))
					pdata->hero[seq].inc_kill += kill;
			}
		}
	}

	bool m_init;
	bool m_tool;
	CShareMemory m_sh, m_shChange;
	unsigned m_ts;
	unsigned m_count;
	unsigned m_history[NEW_WORLD_HISTORY][NEW_WORLD_CITY];
	NewWorldMisson m_mission[3];
	NewWorldHeroMap m_heromap;
	NewWorldCityMap m_citymap;
	static NewWorldRoadMap m_roadmap;
	unsigned m_kingdomcityNum[3];
	static NewWorldNPCTimeMap m_npctimemap;

	NewWorldChangeMap m_battlechange;
};


#endif /* DATANEWWORLD_H_ */
