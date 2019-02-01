/*
 * DataNewWorldAllianceRoom.h
 *
 *  Created on: 2014-9-17
 *      Author: Ralf
 */

#ifndef DATANEWWORLDALLIANCEROOM_H_
#define DATANEWWORLDALLIANCEROOM_H_

#include <math.h>
#include "Kernel.h"
#include "DataBase.h"
#include "NewWorldAllianceRoom.pb.h"
#include "DataNewWorld.h"
#include "DataNewWorldAllianceMap.h"

/**************tick time*******************/
#ifdef SG_16_VER
#define NEW_WORLD_ALLIANCE_ROOM_TICK 				3
#else
#define NEW_WORLD_ALLIANCE_ROOM_TICK 				7
#endif
/**************hero para*******************/
#define NEW_WORLD_ALLIANCE_ROOM_HERO_INDEX 			5
#define NEW_WORLD_ALLIANCE_ROOM_HERO_MIN			5
#define NEW_WORLD_ALLIANCE_ROOM_HERO_MIN_F			double(5)
#define NEW_WORLD_ALLIANCE_ROOM_HERO_TIME_1			600
/**************city para*******************/
#define NEW_WORLD_ALLIANCE_ROOM_CITY_NEUTRAL  		7
#define NEW_WORLD_ALLIANCE_ROOM_CITY_CAPITAL  		1
#define NEW_WORLD_ALLIANCE_ROOM_CITY_AID_CORE		3
#define NEW_WORLD_ALLIANCE_ROOM_CITY_AID_OTHER		68
#define NEW_WORLD_ALLIANCE_ROOM_CITY_AID			(NEW_WORLD_ALLIANCE_ROOM_CITY_CAPITAL+NEW_WORLD_ALLIANCE_ROOM_CITY_AID_CORE+NEW_WORLD_ALLIANCE_ROOM_CITY_AID_OTHER)
#define NEW_WORLD_ALLIANCE_ROOM_CITY 				(NEW_WORLD_ALLIANCE_ROOM_CITY_AID*NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE+NEW_WORLD_ALLIANCE_ROOM_CITY_NEUTRAL)
#define NEW_WORLD_ALLIANCE_ROOM_CITY_AID_SEQ		100
/**************npc para*******************/
#define NEW_WORLD_ALLIANCE_ROOM_CITY_NPC			5
#define NEW_WORLD_ALLIANCE_ROOM_CITY_NPC_TIME		600
/**************para define*******************/
#define NEW_WORLD_ALLIANCE_ROOM_HERO_LEVEL 		 	120
/**************hero define*******************/
#define NEW_WORLD_ALLIANCE_ROOM_HERO_RECOVER 		1000
enum NewWorldAllianceRoomProperty
{
	NewWorldAllianceRoomProperty_hp					= 0,
	NewWorldAllianceRoomProperty_attack				= 1,
	NewWorldAllianceRoomProperty_defence			= 2,
	NewWorldAllianceRoomProperty_speed				= 3,
	NewWorldAllianceRoomProperty_crit				= 4,
	NewWorldAllianceRoomProperty_anti_crit			= 5,
	NewWorldAllianceRoomProperty_crit_times			= 6,
	NewWorldAllianceRoomProperty_anti_crit_times	= 7,
	NewWorldAllianceRoomProperty_dodge				= 8,
	NewWorldAllianceRoomProperty_anti_dodge			= 9,
	NewWorldAllianceRoomProperty_block				= 10,
	NewWorldAllianceRoomProperty_anti_block			= 11,
	NewWorldAllianceRoomProperty_extra				= 12,
	NewWorldAllianceRoomProperty_anti_extra			= 13,
	NewWorldAllianceRoomProperty_reflect			= 14,
	NewWorldAllianceRoomProperty_anti_reflect		= 15,
	NewWorldAllianceRoomProperty_type_extra			= 16,
	NewWorldAllianceRoomProperty_anti_speed			= 17,
	NewWorldAllianceRoomProperty_explode			= 18,
	NewWorldAllianceRoomProperty_F_A_1				= 19,
	NewWorldAllianceRoomProperty_F_A_2				= 20,
	NewWorldAllianceRoomProperty_F_A_3				= 21,
	NewWorldAllianceRoomProperty_F_A_4				= 22,
	NewWorldAllianceRoomProperty_F_A_5				= 23,
	NewWorldAllianceRoomProperty_F_D_1				= 24,
	NewWorldAllianceRoomProperty_F_D_2				= 25,
	NewWorldAllianceRoomProperty_F_D_3				= 26,
	NewWorldAllianceRoomProperty_F_D_4				= 27,
	NewWorldAllianceRoomProperty_F_D_5				= 28,
	NewWorldAllianceRoomProperty_A_D_1				= 29,
	NewWorldAllianceRoomProperty_A_D_2				= 30,
	NewWorldAllianceRoomProperty_NB					= 31,
	NewWorldAllianceRoomProperty_hp_extra			= 32,
	NewWorldAllianceRoomProperty_anti_hp_extra		= 33,

	NewWorldAllianceRoomProperty_max
};
enum NewWorldAllianceRoomHeroJob
{
	NewWorldAllianceRoomHeroJob_warrior	= 0,
	NewWorldAllianceRoomHeroJob_shooter	= 1,
	NewWorldAllianceRoomHeroJob_wizard	= 2,

	NewWorldAllianceRoomHeroJob_max
};
enum NewWorldAllianceRoomHeroAttackResult
{
	NewWorldAllianceRoomHeroAttackResult_none			= 0,
	NewWorldAllianceRoomHeroAttackResult_attacker_win	= 1,
	NewWorldAllianceRoomHeroAttackResult_defender_win	= 2,
	NewWorldAllianceRoomHeroAttackResult_all_die		= 3,
};
/**************city define*******************/
enum NewWorldAllianceRoomCityType
{
	NewWorldAllianceRoomCityType_capital	= 0,
	NewWorldAllianceRoomCityType_core	  	= 1,
	NewWorldAllianceRoomCityType_small		= 2,
	NewWorldAllianceRoomCityType_neutral	= 3,

	NewWorldAllianceRoomCityType_max
};
/**************static define*******************/
#define NEW_WORLD_ALLIANCE_ROOM_ROAD					324
typedef map<unsigned, vector<unsigned> > NewWorldAllianceRoomRoadMap;
#define NEW_WORLD_ALLIANCE_ROOM_REDUCE 					double(0.65)
#define NEW_WORLD_ALLIANCE_ROOM_VISION_REDUCE 			double(0.8)
#define NEW_WORLD_ALLIANCE_ROOM_CITY_REDUCE 			double(0.5)
#define NEW_WORLD_ALLIANCE_ROOM_MOVE_LEVEL 				150
#define NEW_WORLD_ALLIANCE_ROOM_RUSH_MIN 				2
#define NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MIN 	35
#define NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MAX 	120
#define NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_BATTLE 		double(33)
#define NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_LAST 			50
#define NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_QUEUE 			20
#define NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_CLONE 			20
#define NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_RUSH 			10
#define NEW_WORLD_ALLIANCE_ROOM_COLLECTOTHER_KILL		50
/********************************************/
class DataNewWorldAllianceRoomHeroIndex {
public:
	unsigned int uid;
	unsigned int index;
	DataNewWorldAllianceRoomHeroIndex() {
		uid = 0;
		index = 0;
	}
	~DataNewWorldAllianceRoomHeroIndex() {
	}
	void Serialize(NewWorldAllianceRoom::NewWorldAllianceRoomHeroIndex *p) {
		p->set_uid(uid);
		p->set_index(index);
	}
	void Parse(const NewWorldAllianceRoom::NewWorldAllianceRoomHeroIndex &p) {
		uid = p.uid();
		index = p.index();
	}
	DataNewWorldAllianceRoomHeroIndex(unsigned uid1, unsigned index1)
	{
		uid = uid1;
		index = index1;
	}
	DataNewWorldAllianceRoomHeroIndex(const DataNewWorldAllianceRoomHeroIndex& node)
	{
		uid = node.uid;
		index = node.index;
	}
	void clear()
	{
		uid = index = 0;
	}
	DataNewWorldAllianceRoomHeroIndex& operator =(const DataNewWorldAllianceRoomHeroIndex& node)
	{
		uid = node.uid;
		index = node.index;
		return *this;
	}
	bool operator <(const DataNewWorldAllianceRoomHeroIndex& other) const
	{
		if(uid != other.uid)
			return uid < other.uid;
		else
			return index < other.index;
	}
	bool operator ==(const DataNewWorldAllianceRoomHeroIndex& other) const
	{
		if(uid == other.uid && index == other.index)
			return true;
		return false;
	}
	bool operator !=(const DataNewWorldAllianceRoomHeroIndex& other) const
	{
		if(uid == other.uid && index == other.index)
			return false;
		return true;
	}
};
class DataNewWorldAllianceRoomHero {
public:
	DataNewWorldAllianceRoomHeroIndex index;
	unsigned int aid;
	unsigned int hid;
	char name[32];
	unsigned int job;
	unsigned int level;
	unsigned int type;
	unsigned int cid;
	unsigned int mts;
	int hp;
	unsigned int kill;
	unsigned int seq;
	int property[NewWorldAllianceRoomProperty_max];
	unsigned buff;
	DataNewWorldAllianceRoomHero() {
		aid = 0;
		hid = 0;
		job = 0;
		level = 0;
		type = 0;
		cid = 0;
		mts = 0;
		hp = 0;
		kill = 0;
		seq = 0;
		memset(property, 0, sizeof(property));
		memset(name, 0, sizeof(name));
		buff = 0;
	}
	~DataNewWorldAllianceRoomHero() {
	}
	DataNewWorldAllianceRoomHero& operator =(const DataNewWorldAllianceRoomHero& node)
	{
		index = node.index;
		aid = node.aid;
		hid = node.hid;
		job = node.job;
		level = node.level;
		type = node.type;
		cid = node.cid;
		mts = node.mts;
		hp = node.hp;
		kill = node.kill;
		seq = node.seq;
		memcpy(property, node.property, sizeof(property));
		memcpy(name, node.name, sizeof(name));
		buff = node.buff;

		return *this;
	}
	void Serialize(NewWorldAllianceRoom::NewWorldAllianceRoomHero *p) {
		index.Serialize(p->mutable_index());
		p->set_aid(aid);
		p->set_hid(hid);
		p->set_name(string(name));
		p->set_job(job);
		p->set_level(level);
		p->set_type(type);
		p->set_cid(cid);
		p->set_mts(mts);
		p->set_hp(hp);
		p->set_kill(kill);
		p->set_seq(seq);
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			p->add_property(property[i]);
		p->set_buff(buff);

	}
	void Parse(const NewWorldAllianceRoom::NewWorldAllianceRoomHero &p) {
		index.Parse(p.index());
		aid = p.aid();
		hid = p.hid();
		job = p.job();
		level = p.level();
		type = p.type();
		cid = p.cid();
		mts = p.mts();
		hp = p.hp();
		kill = p.kill();
		seq = p.seq();
		if(p.property_size() <= NewWorldAllianceRoomProperty_max)
		{
			for (int i = 0; i < p.property_size(); ++i)
				property[i] = p.property(i);
		}
		memset(name, 0, sizeof(name));
		strncpy(name, p.name().c_str(), sizeof(name)-1);
		if(p.has_buff())
			buff = p.buff();
		else
			buff = 0;
	}
	void copy(DataNewWorldAllianceRoomHero &other)
	{
		if(other.property[NewWorldAllianceRoomProperty_hp] < property[NewWorldAllianceRoomProperty_hp])
			hp = min(max(0, hp - (property[NewWorldAllianceRoomProperty_hp] - other.property[NewWorldAllianceRoomProperty_hp]))
				,hp * other.property[NewWorldAllianceRoomProperty_hp] / property[NewWorldAllianceRoomProperty_hp]);
		hid = other.hid;
		aid = other.aid;
		job = other.job;
		level = other.level;
		if(level > NEW_WORLD_ALLIANCE_ROOM_HERO_LEVEL)
			level = NEW_WORLD_ALLIANCE_ROOM_HERO_LEVEL;
		if(level == 0)
			level = 1;
		memcpy(name, other.name, sizeof(name));
		memcpy(property, other.property, sizeof(property));

		other.level = level;
		other.hp = hp;
		other.buff = buff;
	}

	void recover()
	{
		if(hp == property[NewWorldAllianceRoomProperty_hp])
			return;
		else if(hp < property[NewWorldAllianceRoomProperty_hp] && hp >= 0)
		{
			double total = NEW_WORLD_ALLIANCE_ROOM_HERO_TIME_1;
			int add = (double)property[NewWorldAllianceRoomProperty_hp] * (double)NEW_WORLD_ALLIANCE_ROOM_TICK / total;
			if(add == 0)
				add = 1;
			hp += add;
			if(hp > property[NewWorldAllianceRoomProperty_hp])
				hp = property[NewWorldAllianceRoomProperty_hp];
		}
		else if(hp > property[NewWorldAllianceRoomProperty_hp])
			hp = property[NewWorldAllianceRoomProperty_hp];
		else
			hp = 0;

		return;
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
/********************************************/
class DataNewWorldAllianceRoomTower {
public:
	unsigned int uid;
	unsigned int dps;
	unsigned int hit;
	DataNewWorldAllianceRoomTower() {
		uid = 0;
		dps = 0;
		hit = 0;
	}
	~DataNewWorldAllianceRoomTower() {
	}
	void Serialize(NewWorldAllianceRoom::NewWorldAllianceRoomTower *p) {
		p->set_uid(uid);
		p->set_dps(dps);
		p->set_hit(hit);
	}
	void Parse(const NewWorldAllianceRoom::NewWorldAllianceRoomTower &p) {
		uid = p.uid();
		dps = p.dps();
		hit = p.hit();
	}
	void clear()
	{
		uid = dps = hit = 0;
	}
};
typedef map<DataNewWorldAllianceRoomHeroIndex, DataNewWorldAllianceRoomHero> NewWorldAllianceRoomHeroMap;
typedef set<pair<unsigned, DataNewWorldAllianceRoomHeroIndex> > NewWorldAllianceCityQueue;
class DataNewWorldAllianceRoomCity {
public:
	unsigned int cid;
	unsigned int aid;
	int countN;
	unsigned int npcts;
	NewWorldAllianceRoomHeroMap npc;
	NewWorldAllianceRoomHeroMap vision;
	DataNewWorldAllianceRoomTower tower;
	NewWorldAllianceCityQueue attacker, defender;
	int count[NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
	DataNewWorldAllianceRoomCity() {
		cid = 0;
		aid = 0;
		countN = 0;
		npcts = 0;
	}
	~DataNewWorldAllianceRoomCity() {
	}
	void Serialize(NewWorldAllianceRoom::NewWorldAllianceRoomCity *p) {
		p->set_cid(cid);
		p->set_aid(aid);
		p->set_countn(countN);
		p->set_npcts(npcts);
		for (NewWorldAllianceRoomHeroMap::iterator it = npc.begin(); it != npc.end(); ++it)
			it->second.Serialize(p->add_npc());
		for (NewWorldAllianceRoomHeroMap::iterator it = vision.begin(); it != vision.end(); ++it)
			it->second.Serialize(p->add_vision());
		tower.Serialize(p->mutable_tower());
	}
	void Parse(const NewWorldAllianceRoom::NewWorldAllianceRoomCity &p) {
		cid = p.cid();
		aid = p.aid();
		countN = p.countn();
		npcts = p.npcts();
		for (int i = 0; i < p.npc_size(); ++i)
		{
			DataNewWorldAllianceRoomHeroIndex temp;
			temp.Parse(p.npc(i).index());
			npc[temp].Parse(p.npc(i));
		}
		for (int i = 0; i < p.vision_size(); ++i)
		{
			DataNewWorldAllianceRoomHeroIndex temp;
			temp.Parse(p.vision(i).index());
			vision[temp].Parse(p.vision(i));
		}
		if(p.has_tower())
			tower.Parse(p.tower());
	}
	bool Fighting() const
	{
		return !attacker.empty();
	}
};
/************************************************************************************/
typedef map<unsigned int, DataNewWorldAllianceRoomCity> NewWorldAllianceRoomCityMap;
struct DataNewWorldAllianceRoomBattleChange
{
	unsigned cid, aid, battle;
	DataNewWorldAllianceRoomBattleChange()
	{
		cid = aid = battle = 0;
	}
};
typedef map<unsigned,DataNewWorldAllianceRoomBattleChange> NewWorldAllianceRoomChangeMap;
typedef vector<pair<pair<unsigned, unsigned>, unsigned> > NewWorldAllianceRoomResult;
typedef map<unsigned, map<unsigned, unsigned> > NewWorldAllianceRoomKill;
class DataNewWorldAllianceRoomBattle {
public:
	unsigned int rid;
	unsigned int level;
	unsigned int reward;
	unsigned int ts;
	vector<unsigned int> aid;
	NewWorldAllianceRoomHeroMap hero;
	NewWorldAllianceRoomCityMap city;
	NewWorldAllianceRoomChangeMap battlechange;
	map<unsigned, unsigned> aidmap;
	NewWorldAllianceRoomResult result;
	NewWorldAllianceRoomKill kill;
	DataNewWorldAllianceRoomBattle() {
		rid = 0;
		level = 0;
		reward = 0;
		ts = 0;
	}
	~DataNewWorldAllianceRoomBattle() {
	}
	void Serialize(NewWorldAllianceRoom::NewWorldAllianceRoomBattle *p) {
		p->set_rid(rid);
		p->set_level(level);
		p->set_reward(reward);
		p->set_ts(ts);
		for (vector<unsigned int>::iterator it = aid.begin(); it != aid.end();++it)
			p->add_aid(*it);
		for (NewWorldAllianceRoomHeroMap::iterator it = hero.begin(); it != hero.end(); ++it)
			it->second.Serialize(p->add_hero());
		for (NewWorldAllianceRoomCityMap::iterator it =	city.begin(); it != city.end(); ++it)
			it->second.Serialize(p->add_city());
	}
	void Parse(const NewWorldAllianceRoom::NewWorldAllianceRoomBattle &p) {
		rid = p.rid();
		level = p.level();
		reward = p.reward();
		ts = p.ts();
		for (int i = 0; i < p.aid_size(); ++i)
		{
			aid.push_back(p.aid(i));
			aidmap[p.aid(i)] = i;
		}
		for (int i = 0; i < p.hero_size(); ++i)
		{
			DataNewWorldAllianceRoomHeroIndex temp;
			temp.Parse(p.hero(i).index());
			hero[temp].Parse(p.hero(i));
		}
		for (int i = 0; i < p.city_size(); ++i)
			city[p.city(i).cid()].Parse(p.city(i));
	}
	void sync();
};
/************************************************************************************/
typedef map<unsigned int, DataNewWorldAllianceRoomBattle> NewWorldAllianceRoomMap;
class DataNewWorldAllianceRoom {
public:
	NewWorldAllianceRoomMap room;
	DataNewWorldAllianceRoom() {
	}
	~DataNewWorldAllianceRoom() {
	}
	void Serialize(NewWorldAllianceRoom::NewWorldAllianceRoom *p) {
		for (NewWorldAllianceRoomMap::iterator it = room.begin(); it != room.end(); ++it)
			it->second.Serialize(p->add_room());
	}
	void Parse(const NewWorldAllianceRoom::NewWorldAllianceRoom &p) {
		for (int i = 0; i < p.room_size(); ++i)
			room[p.room(i).rid()].Parse(p.room(i));
	}
	void sync() {
		for (NewWorldAllianceRoomMap::iterator it = room.begin(); it != room.end(); ++it)
			it->second.sync();
	}
};
/************************************************************************************/

class CDataNewWorldAllianceRoom : public DataBase
{
public:
	CDataNewWorldAllianceRoom(string path);
	virtual ~CDataNewWorldAllianceRoom();
	int Init();
	int Save();
	int Sig(int sig);

	unsigned GetTS(unsigned rid)
	{
		if(!m_data.room.count(rid))
			return 0;
		return m_data.room[rid].ts;
	}

	int GetResult(unsigned rid, NewWorldAllianceRoomResult* &p);
	int GetKill(unsigned rid, NewWorldAllianceRoomKill* &p);
	int GetAID(unsigned rid, vector<unsigned int>* &p);
	int GetWorld(unsigned rid, NewWorldAllianceRoomCityMap* &p);
	int GetCity(unsigned rid, unsigned cid, DataNewWorldAllianceRoomCity* &p);
	int GetHero(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, DataNewWorldAllianceRoomHero* &p);
	int GetAllHero(unsigned rid, NewWorldAllianceRoomHeroMap* &p);
	int GetChangeMap(unsigned rid, NewWorldAllianceRoomChangeMap* &p)
	{
		if(!m_data.room.count(rid))
			return R_ERR_PARAM;
		p =  &m_data.room[rid].battlechange;
		return 0;
	}
	int ClearChangeMap(unsigned rid)
	{
		if(!m_data.room.count(rid))
			return R_ERR_PARAM;
		m_data.room[rid].battlechange.clear();
		return 0;
	}

	int SetHero(unsigned rid, DataNewWorldAllianceRoomHero &hero, unsigned &seq);
	int Move(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned cid, bool leave, unsigned fly, unsigned &mts, unsigned &seq);
	int Change(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned type, unsigned &seq);
	int Clone(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq);
	int Rush(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, DataNewWorldAllianceRoomHero &other, DataNewWorldAllianceRoomHero &end, unsigned &seq);
	int Recover(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned num, unsigned &seq);
	int CollectOther(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq);
	int Explode(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq);

	int Buildyjt(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq);

	static inline unsigned getCapital(unsigned aidseq)
	{
		return (aidseq + 1) * NEW_WORLD_ALLIANCE_ROOM_CITY_AID_SEQ + NEW_WORLD_ALLIANCE_ROOM_CITY_CAPITAL;
	}
	static inline unsigned getCityType(unsigned cid)
	{
		if(cid <= NEW_WORLD_ALLIANCE_ROOM_CITY_AID_SEQ)
			return NewWorldAllianceRoomCityType_neutral;

		cid = cid % NEW_WORLD_ALLIANCE_ROOM_CITY_AID_SEQ;
		if(cid ==  NEW_WORLD_ALLIANCE_ROOM_CITY_CAPITAL)
			return NewWorldAllianceRoomCityType_capital;
		if(cid <=  NEW_WORLD_ALLIANCE_ROOM_CITY_AID_CORE + NEW_WORLD_ALLIANCE_ROOM_CITY_CAPITAL)
			return NewWorldAllianceRoomCityType_core;
		return NewWorldAllianceRoomCityType_small;
	}
	static inline bool isCapital(unsigned cid)
	{
		return getCityType(cid) == NewWorldAllianceRoomCityType_capital;
	}

	static inline bool isVision(DataNewWorldAllianceRoomHeroIndex index)
	{
		return index.uid < ADMIN_UID;
	}
	static inline bool isNPC(DataNewWorldAllianceRoomHeroIndex index)
	{
		return index.uid == ADMIN_UID;
	}
	static inline bool notHero(DataNewWorldAllianceRoomHeroIndex index)
	{
		return index.uid <= ADMIN_UID;
	}
	static inline bool isHero(DataNewWorldAllianceRoomHeroIndex index)
	{
		return IsValidUid(index.uid) && index.index < NEW_WORLD_ALLIANCE_ROOM_HERO_INDEX;
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
	static NewWorldAllianceRoomRoadMap m_roadmap;

public:
	void ShowCity(void);

private:
	void Restart();
	void Reward();
	void checkTick(unsigned rid);
	bool isValid(unsigned rid, DataNewWorldAllianceRoomHeroIndex index);
	bool notMoving(unsigned rid, DataNewWorldAllianceRoomHeroIndex index);
	bool notFront(unsigned rid, DataNewWorldAllianceRoomHeroIndex index);
	void queue(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned cid);
	DataNewWorldAllianceRoom m_data;
	unsigned m_index;

	void makeNPC(DataNewWorldAllianceRoomHero &hero, unsigned level)
	{
		unsigned job = hero.job % NewWorldAllianceRoomHeroJob_max;
		hero.index.uid = ADMIN_UID;
		hero.index.index = ADMIN_UID;
		hero.hid = job;
		hero.job = job;
		hero.level = level;
		int npcdefault = 0;
		for(int i=0;i<NEW_WORLD_HERO_NPC_DEFAULT;++i)
		{
			if(CDataNewWorld::npc_level[i] == level)
			{
				npcdefault = i;
				break;
			}
		}
		if(npcdefault >= NEW_WORLD_HERO_NPC_DEFAULT)
			npcdefault = 0;
		hero.type = NewWorldAllianceRoomHeroJob_shooter;
		hero.name[0] = 'N';hero.name[1] = 'P';hero.name[2] = 'C';hero.name[3] = 0;
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			hero.property[i] = CDataNewWorld::npc_property[job][npcdefault][i];
		hero.hp = hero.property[NewWorldAllianceRoomProperty_hp];
	}

	unsigned attacking(unsigned rid, DataNewWorldAllianceRoomHero &attacker, DataNewWorldAllianceRoomHero &defender, int &attackkill, int &defendkill)
	{
		//step 1: damage of type vs job
		//debug_log("----start----");
		//debug_log("attacker=%u,%u,city=%u,job=%u,type=%u,hp=%u,maxhp=%u,att=%u,def=%u",attacker.index.uid,attacker.index.index,attacker.cid,attacker.job,attacker.type,attacker.hp,attacker.property[NewWorldAllianceRoomProperty_hp],attacker.property[NewWorldAllianceRoomProperty_attack],attacker.property[NewWorldAllianceRoomProperty_defence]);
		//debug_log("defender=%u,%u,city=%u,job=%u,type=%u,hp=%u,maxhp=%u,att=%u,def=%u",defender.index.uid,defender.index.index,defender.cid,defender.job,defender.type,defender.hp,defender.property[NewWorldAllianceRoomProperty_hp],defender.property[NewWorldAllianceRoomProperty_attack],defender.property[NewWorldAllianceRoomProperty_defence]);
		if(attacker.hp > attacker.property[NewWorldAllianceRoomProperty_hp])
			attacker.hp = attacker.property[NewWorldAllianceRoomProperty_hp];
		if(defender.hp > defender.property[NewWorldAllianceRoomProperty_hp])
			defender.hp = defender.property[NewWorldAllianceRoomProperty_hp];

		bool mha = attacker.hp == attacker.property[NewWorldAllianceRoomProperty_hp];
		bool mhd = defender.hp == defender.property[NewWorldAllianceRoomProperty_hp];
		double ha = getHPEffect(attacker);
		double hd = getHPEffect(defender);
		bool ce = getCityEffect(rid, defender);
		bool visiona = isVision(attacker.index);
		bool visiond = isVision(defender.index);

		double typea = getTypeEffect(attacker, defender);
		double typed = getTypeEffect(defender, attacker);
		double dk1 = max(NEW_WORLD_ALLIANCE_ROOM_HERO_MIN_F, ((double)attacker.property[NewWorldAllianceRoomProperty_hp])*typed + (double)defender.property[NewWorldAllianceRoomProperty_type_extra]);
		double ak1 = max(NEW_WORLD_ALLIANCE_ROOM_HERO_MIN_F, ((double)defender.property[NewWorldAllianceRoomProperty_hp])*typea + (double)attacker.property[NewWorldAllianceRoomProperty_type_extra]);
		dk1 *= hd;
		ak1 *= ha;
		if(ce)
			dk1 *= NEW_WORLD_ALLIANCE_ROOM_CITY_REDUCE;
		/***********nerf vision***************/
		if(visiond)
			dk1 *= NEW_WORLD_ALLIANCE_ROOM_VISION_REDUCE;
		if(visiona)
			ak1 *= NEW_WORLD_ALLIANCE_ROOM_VISION_REDUCE;
		/*************************************/
		if(mhd)
			dk1 += double(defender.property[NewWorldAllianceRoomProperty_NB]);
		if(mha)
			ak1 += double(attacker.property[NewWorldAllianceRoomProperty_NB]);

		dk1 += getHPExtraEffect(defender, attacker);
		ak1 += getHPExtraEffect(attacker, defender);

		int dk1i = (int)dk1;
		int ak1i = (int)ak1;
		if(dk1i > attacker.hp)
			dk1i = attacker.hp;
		if(ak1i > defender.hp)
			ak1i = defender.hp;
		attacker.hp -= (dk1i + getTowerEffect(rid, defender));
		defender.hp -= ak1i;
		//debug_log("step1:attacker.hp=%u,defender.hp=%u",attacker.hp,defender.hp);

		attackkill = ak1i;
		defendkill = dk1i;

		if(attacker.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			defender.hp -= attacker.property[NewWorldAllianceRoomProperty_explode];
			if(attacker.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiond)
					defender.hp -= defender.property[NewWorldAllianceRoomProperty_hp] / 10;
				else
					defender.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}
		if(defender.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			attacker.hp -= defender.property[NewWorldAllianceRoomProperty_explode];
			if(defender.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiona)
					attacker.hp -= attacker.property[NewWorldAllianceRoomProperty_hp] / 10;
				else
					attacker.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}

		if(attacker.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN && defender.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			attacker.hp = defender.hp = 0;
			attacker.buff = defender.buff = 0;
			return NewWorldAllianceRoomHeroAttackResult_all_die;
		}
		else if(attacker.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			attacker.hp = 0;
			attacker.buff = 0;
			return NewWorldAllianceRoomHeroAttackResult_defender_win;
		}
		else if(defender.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			defender.hp = 0;
			defender.buff = 0;
			return NewWorldAllianceRoomHeroAttackResult_attacker_win;
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
			dpsd *= NEW_WORLD_ALLIANCE_ROOM_CITY_REDUCE;
			//debug_log("CityEffect:dpsd=%f",dpsd);
		}
		/***********nerf vision***************/
		if(visiona)
			dpsa *= NEW_WORLD_ALLIANCE_ROOM_VISION_REDUCE;
		if(visiond)
			dpsd *= NEW_WORLD_ALLIANCE_ROOM_VISION_REDUCE;
		/*************************************/

		//time=min(hp/dps)
		double timea = ((double)attacker.hp)/max(dpsd, double(1));
		double timed = ((double)defender.hp)/max(dpsa, double(1));
		double time = min(timea, timed);
		int dk2 = max(NEW_WORLD_ALLIANCE_ROOM_HERO_MIN_F, dpsd * time);
		int ak2 = max(NEW_WORLD_ALLIANCE_ROOM_HERO_MIN_F, dpsa * time);
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

		if(attacker.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			defender.hp -= attacker.property[NewWorldAllianceRoomProperty_explode];
			if(attacker.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiond)
					defender.hp -= defender.property[NewWorldAllianceRoomProperty_hp] / 10;
				else
					defender.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}
		if(defender.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			attacker.hp -= defender.property[NewWorldAllianceRoomProperty_explode];
			if(defender.isBuff(NewWorldHeroBuff_explode))
			{
				if(visiona)
					attacker.hp -= attacker.property[NewWorldAllianceRoomProperty_hp] / 10;
				else
					attacker.hp -= NEW_WORLD_HERO_EXPLODE;
			}
		}

		if(attacker.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN && defender.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			attacker.hp = defender.hp = 0;
			attacker.buff = defender.buff = 0;
			return NewWorldAllianceRoomHeroAttackResult_all_die;
		}
		else if(attacker.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			attacker.hp = 0;
			attacker.buff = 0;
			return NewWorldAllianceRoomHeroAttackResult_defender_win;
		}
		else if(defender.hp < NEW_WORLD_ALLIANCE_ROOM_HERO_MIN)
		{
			defender.hp = 0;
			defender.buff = 0;
			return NewWorldAllianceRoomHeroAttackResult_attacker_win;
		}

		return NewWorldAllianceRoomHeroAttackResult_all_die;
	}

	inline double getTypeEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		if(attacker.type == defender.job)
			return (double)(Math::GetRandomInt(40) + 10)/double(1000);
		return double(0);
	}
	static inline double getHPExtraEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		if(attacker.property[NewWorldAllianceRoomProperty_hp_extra] <= defender.property[NewWorldAllianceRoomProperty_anti_hp_extra])
			return double(0);
		return double(defender.hp) * double(attacker.property[NewWorldAllianceRoomProperty_hp_extra] - defender.property[NewWorldAllianceRoomProperty_anti_hp_extra]) / double(1000);
	}
	inline double getJobEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		if((attacker.job + 1)%NewWorldAllianceRoomHeroJob_max == defender.job)
			return double(1.05);
		return double(1.0);
	}
	inline double getRandomEffect()
	{
		return (double)(Math::GetRandomInt(200) + 900)/double(1000);
	}
	inline double getSpeedEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		return max(double(1), min(double(4),
			(double)attacker.property[NewWorldAllianceRoomProperty_speed]/double(100)
			* max(double(0.67), min(double(1), double(1)-(double)defender.property[NewWorldAllianceRoomProperty_anti_speed])/double(100))));
	}
	inline double getProtectEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		return max(double(0), double(1)
			- NEW_WORLD_ALLIANCE_ROOM_REDUCE * double(0.5) * min(double(1), max(double(0), (double)defender.property[NewWorldAllianceRoomProperty_block]
			      -(double)attacker.property[NewWorldAllianceRoomProperty_anti_block])/double(1000)))
			* max(double(0), double(1) - NEW_WORLD_ALLIANCE_ROOM_REDUCE * min(double(0.8), max(double(0),((double)defender.property[NewWorldAllianceRoomProperty_dodge]-(double)attacker.property[NewWorldAllianceRoomProperty_anti_dodge])
					/(double)CDataNewWorld::c_crit_dodge[defender.level-1])));
	}
	inline double getCritEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		return (double(1)
			+ NEW_WORLD_ALLIANCE_ROOM_REDUCE * min(double(0.8), max(double(0),
				((double)attacker.property[NewWorldAllianceRoomProperty_crit]-(double)defender.property[NewWorldAllianceRoomProperty_anti_crit])
					/(double)CDataNewWorld::c_crit_dodge[attacker.level-1]))
			* max(attacker.property[NewWorldAllianceRoomProperty_crit_times]
				  -defender.property[NewWorldAllianceRoomProperty_anti_crit_times],0)/double(1000));
	}
	inline double getAttackEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		return (double)CDataNewWorld::c_attack[attacker.level-1]
		   * (double)attacker.property[NewWorldAllianceRoomProperty_attack]/max(double(1), max((double)defender.property[NewWorldAllianceRoomProperty_defence]*double(0.8), (double)defender.property[NewWorldAllianceRoomProperty_defence]*double(1000-attacker.property[NewWorldAllianceRoomProperty_A_D_1])/double(1000)-double(attacker.property[NewWorldAllianceRoomProperty_A_D_2])));
	}
	inline double getLevelEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		return double(2)*(double)attacker.level/(double)(attacker.level+defender.level);
	}
	inline double getReflectEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		return double(0.5)*(double)max(attacker.property[NewWorldAllianceRoomProperty_reflect]-defender.property[NewWorldAllianceRoomProperty_anti_reflect],0)/double(1000);
	}
	inline double getExtraEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		return (double)max(0,attacker.property[NewWorldAllianceRoomProperty_extra]-defender.property[NewWorldAllianceRoomProperty_anti_extra]);
	}
	inline double getFEffect(const DataNewWorldAllianceRoomHero &attacker, const DataNewWorldAllianceRoomHero &defender)
	{
		for(unsigned i=NewWorldAllianceRoomProperty_F_A_1;i<=NewWorldAllianceRoomProperty_F_A_5;++i)
		{
			if(attacker.property[i])
				return (double)max(0,attacker.property[i]-defender.property[i+5]);
		}
		return double(0);
	}
	inline double getHPEffect(const DataNewWorldAllianceRoomHero &attacker)
	{
		return ((double)attacker.hp)/(double)attacker.property[NewWorldAllianceRoomProperty_hp];
	}
	bool getCityEffect(const DataNewWorldAllianceRoomHero &defender);

	inline unsigned getKill(int kill, int otherkill, unsigned aid, unsigned level, unsigned otherlevel)
	{
		if(level >= NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MIN && level <= NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MAX
		&& otherlevel >= NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MIN && otherlevel <= NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MAX)
			return NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_BATTLE * (double)kill / CDataNewWorld::kill_a[level - NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MIN]
			  + NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_BATTLE * (double)otherkill / CDataNewWorld::kill_a[otherlevel - NEW_WORLD_ALLIANCE_ROOM_KILL_REWARD_LEVEL_MIN];

		return 0;
	}

	bool getCityEffect(unsigned rid, const DataNewWorldAllianceRoomHero &defender)
	{
		unsigned enemy = 0, all = 0;
		if(m_roadmap.count(defender.cid))
		{
			for(vector<unsigned>::const_iterator it=m_roadmap[defender.cid].begin();it!=m_roadmap[defender.cid].end();++it)
			{
				++all;
				if(m_data.room[rid].city[*it].aid != m_data.room[rid].city[defender.cid].aid)
					++enemy;
			}
		}
		return enemy >= 4 || (enemy == all && enemy);
	}
	int getTowerEffect(unsigned rid, const DataNewWorldAllianceRoomHero &defender)
	{
		DataNewWorldAllianceRoomTower& tower = m_data.room[rid].city[defender.cid].tower;
		if(tower.uid)
		{
			if(tower.hit)
			{
				--tower.hit;
				unsigned dps = tower.dps;
				if(tower.hit == 0)
					tower.clear();
				return dps;
			}
		}
		return 0;
	}

	void addKill(unsigned rid, DataNewWorldAllianceRoomHero &killer, DataNewWorldAllianceRoomHero &otherhero, int kill, int otherkill)
	{
		if (kill < 0 || otherkill < 0)
			return ;

		kill = getKill(kill, otherkill, killer.aid, killer.level, otherhero.level);

		if (isHero(killer.index))
			killer.kill += kill;
		else if (isVision(killer.index))
		{
			DataNewWorldAllianceRoomHeroIndex index(killer.index.index, 0);
			if (m_data.room[rid].hero.count(index))
				m_data.room[rid].hero[index].kill += kill;
		}
	}
	void addKill(unsigned rid, DataNewWorldAllianceRoomHero &killer, int kill)
	{
		if (kill < 0)
			return ;

		if (isHero(killer.index))
			killer.kill += kill;
		else if (isVision(killer.index))
		{
			DataNewWorldAllianceRoomHeroIndex index(killer.index.index, 0);
			if (m_data.room[rid].hero.count(index))
				m_data.room[rid].hero[index].kill += kill;
		}
	}

};


#endif /* DATANEWWORLDALLIANCEROOM_H_ */
