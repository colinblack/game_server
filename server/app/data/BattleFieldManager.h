/*
 * BattleFieldManager.h
 *
 *  Created on: 2016-8-18
 *      Author: Ralf
 */

#ifndef BATTLEFIELDMANAGER_H_
#define BATTLEFIELDMANAGER_H_

#include "Kernel.h"


#define IsValidCid(cid) ((cid > 0 && cid <= BATTLE_FIELD_CITY_NEUTRAL ) || (cid/BATTLE_FIELD_CITY_KINGDOM_SEQ > 0 && cid/BATTLE_FIELD_CITY_KINGDOM_SEQ <= SG17_KINGDOM && cid%BATTLE_FIELD_CITY_KINGDOM_SEQ > 0 && cid%BATTLE_FIELD_CITY_KINGDOM_SEQ <= BATTLE_FIELD_CITY_KINGDOM))

struct BattleFieldCity
{
	uint16_t cid;
	uint8_t kingdom;
	unsigned uid;
	char name[BASE_NAME_LEN];
	uint8_t reward;
	uint8_t next_reward;
	BattleFieldCity()
	{
		cid = 0;
		kingdom = reward = next_reward = 0;
		uid = 0;
		memset(name, 0, sizeof(name));
	}
	void SetMessage(ProtoBattleField::City* msg)
	{
		msg->set_cid(cid);
		msg->set_kingdom(kingdom);
		msg->set_uid(uid);
		if(uid)
			msg->set_name(name);
	}
	unsigned SetMessage(ProtoBattleField::ReplyCityMaster* msg)
	{
		msg->set_uid(uid);
		if(uid)
			msg->set_name(name);
		msg->set_reward(reward);
		msg->set_next_reward(next_reward);
		return uid;
	}
	void KingdomChange(uint8_t k)
	{
		kingdom = k;
		uid = 0;
		memset(name, 0, sizeof(name));
	}
	void ResetMaster()
	{
		uid = 0;
		memset(name, 0, sizeof(name));
	}
};
struct BattleFieldMisson
{
	uint16_t m1, m2;
	uint8_t m1status, m2status;
	BattleFieldMisson()
	{
		m1 = m2 = 0;
		m1status = m2status = 0;
	}

	void SetMessage(ProtoBattleField::Mission* msg)
	{
		msg->set_m1(m1);
		msg->set_m2(m2);
		msg->set_m1status(m1status);
		msg->set_m2status(m2status);
	}

	//是否可领取国战外奖励
	bool IsGetExpandTaskReward(unsigned task_no)
	{
		if (task_no < 1 || task_no > 2)
		{
			throw std::runtime_error("task_no_params_error");
		}

		uint8_t val[2] = {m1status, m2status};

		return (val[task_no - 1] == BattleFieldMissonStatus_attack_win)
				|| (val[task_no - 1] == BattleFieldMissonStatus_defend_win);
	}

	//是否可以领取奖励
	bool IsGetTaskReward(unsigned task_no)
	{
		if (task_no < 1 || task_no > 2)
		{
			throw std::runtime_error("task_no_params_error");
		}

		uint8_t val[2] = {m1status, m2status};

		return ((val[task_no - 1] == BattleFieldMissonStatus_attack_lose)
				|| (val[task_no - 1] == BattleFieldMissonStatus_defend_lose)
				|| (val[task_no - 1] == BattleFieldMissonStatus_defend_win)
				|| (val[task_no - 1] == BattleFieldMissonStatus_attack_win));
	}
};
struct BattleField
{
	BattleFieldCity city[BATTLE_FIELD_CITY];
	uint8_t history[BATTLE_FIELD_HISTORY][BATTLE_FIELD_CITY];
	BattleFieldMisson mission[SG17_KINGDOM];
	uint16_t reward[SG17_KINGDOM][BATTLE_FIELD_REWARD_R][BATTLE_FIELD_REWARD_R][2];
	unsigned ts;

	BattleField()
	{
		ts = 0;
		memset(reward, 0, sizeof(reward));
	}
	bool HasMission()
	{
		return mission[0].m1 && (mission[0].m1status == BattleFieldMissonStatus_defending || mission[0].m1status == BattleFieldMissonStatus_defend_over || mission[0].m1status == BattleFieldMissonStatus_attacking || mission[0].m1status == BattleFieldMissonStatus_attack_over);
	}

	void SetMessage(ProtoBattleField::Field* msg)
	{
		for(unsigned i=0;i<BATTLE_FIELD_CITY;++i)
			city[i].SetMessage(msg->add_city());
		for(unsigned i=0;i<SG17_KINGDOM;++i)
			mission[i].SetMessage(msg->add_mission());
	}
	void SetMessage(ProtoBattleField::ReplyRewardInfo* msg)
	{
		for(unsigned i=0;i<BATTLE_FIELD_HISTORY;++i)
		{
			for(unsigned j=0;j<BATTLE_FIELD_CITY;++j)
				msg->add_history(history[i][j]);
		}
		for(unsigned i=0;i<SG17_KINGDOM;++i)
			mission[i].SetMessage(msg->add_mission());
	}
	void SetMessage(ProtoBattleField::MissionState* msg)
	{
		for(unsigned i=0;i<SG17_KINGDOM;++i)
			mission[i].SetMessage(msg->add_mission());
	}

	void SyncHistory()
	{
		uint8_t* p = (uint8_t*)history;
		for(unsigned i=BATTLE_FIELD_HISTORY-1;i>0;--i)
			memcpy(p+i*BATTLE_FIELD_CITY, p+(i-1)*BATTLE_FIELD_CITY, sizeof(uint8_t)*BATTLE_FIELD_CITY);
		for(unsigned i=0;i<BATTLE_FIELD_CITY;++i)
			history[0][i] = city[i].kingdom;
		ts = Time::GetGlobalTime();
	}

	void SetMessage(ProtoBattleField::BattleReward *msg, unsigned kingdom, unsigned uid)
	{
		unsigned k = min(unsigned(SG17_KINGDOM), max(kingdom, unsigned(1))) - 1;
		unsigned r = uid % BATTLE_FIELD_REWARD_R;
		for(unsigned i=0;i<BATTLE_FIELD_REWARD_R;++i)
		{
			msg->add_c(reward[k][r][i][0]);
			msg->add_r(reward[k][r][i][1]);
		}
	}
	void SetMessage(ProtoBattleField::ResetBattleReward *msg)
	{
		for(unsigned k=0;k<SG17_KINGDOM;++k)
		{
			for(unsigned r=0;r<BATTLE_FIELD_REWARD_R;++r)
			{
				for(unsigned i=0;i<BATTLE_FIELD_REWARD_R;++i)
				{
					msg->add_c(reward[k][r][i][0]);
					msg->add_r(reward[k][r][i][1]);
				}
			}
		}
	}
};

typedef map<unsigned, set<unsigned> > BattleFieldRoadMap;
typedef map<unsigned, map<unsigned, list<uint16_t> > > BattleFieldCapitalRoadMap;

class BattleFieldManager : public MemorySingleton<BattleField, MEMORY_BATTLE>, public CSingleton<BattleFieldManager>
{
private:
	friend class CSingleton<BattleFieldManager>;
	BattleFieldManager(){};
	virtual ~BattleFieldManager(){}

	BattleFieldRoadMap m_roadmap;
	BattleFieldCapitalRoadMap m_capital;

	map<unsigned, uint16_t> m_cityMaster;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	static const unsigned road_map[BATTLE_FIELD_ROAD][2];

	static inline unsigned getCapital(unsigned kingdom)
	{
		if(kingdom > SG17_KINGDOM || kingdom < 1)
			return 1;
		return kingdom*BATTLE_FIELD_CITY_KINGDOM_SEQ + BATTLE_FIELD_CITY_CAPITAL;
	}
	static inline bool isCapital(unsigned cid)
	{
		return cid > BATTLE_FIELD_CITY_KINGDOM_SEQ && cid%BATTLE_FIELD_CITY_KINGDOM_SEQ == BATTLE_FIELD_CITY_CAPITAL;
	}
	static inline bool isNeutral(unsigned cid)
	{
		return cid <= BATTLE_FIELD_CITY_KINGDOM_SEQ;
	}
	static inline unsigned getCitySeq(uint16_t cid)
	{
		if(cid <= BATTLE_FIELD_CITY_KINGDOM_SEQ)
			return cid - 1;
		return BATTLE_FIELD_CITY_NEUTRAL + (cid/BATTLE_FIELD_CITY_KINGDOM_SEQ - 1)*BATTLE_FIELD_CITY_KINGDOM + cid%BATTLE_FIELD_CITY_KINGDOM_SEQ - 1;
	}
	inline bool hasRoad(uint16_t cid1, uint16_t cid2)
	{
		if(m_roadmap.count(cid1) && m_roadmap[cid1].count(cid2))
			return true;
		return false;
	}
	inline bool IsCityBesieged(uint16_t cid)
	{
		unsigned enemy = 0, all = 0;
		if(m_roadmap.count(cid))
		{
			for(set<unsigned>::const_iterator it=m_roadmap[cid].begin();it!=m_roadmap[cid].end();++it)
			{
				++all;
				if(m_data->city[getCitySeq(cid)].kingdom != m_data->city[getCitySeq(*it)].kingdom)
					++enemy;
			}
		}
		return enemy == all && enemy;
	}
	inline bool IsCityBesideEnemy(uint16_t cid)
	{
		if(m_roadmap.count(cid))
		{
			for(set<unsigned>::const_iterator it=m_roadmap[cid].begin();it!=m_roadmap[cid].end();++it)
			{
				if(m_data->city[getCitySeq(cid)].kingdom != m_data->city[getCitySeq(*it)].kingdom)
					return true;
			}
		}
		return false;
	}
	inline bool IsCityBesideKingdom(uint16_t cid, uint8_t kingdom)
	{
		if(m_roadmap.count(cid))
		{
			for(set<unsigned>::const_iterator it=m_roadmap[cid].begin();it!=m_roadmap[cid].end();++it)
			{
				if(kingdom == m_data->city[getCitySeq(*it)].kingdom)
					return true;
			}
		}
		return false;
	}
	unsigned GetRange(uint8_t kingdom, uint16_t cid)
	{
		return m_capital[kingdom][cid].size();
	}
	const list<uint16_t>& GetRoad(uint8_t kingdom, uint16_t cid)
	{
		return m_capital[kingdom][cid];
	}

	void OnDay();
	void OnCityReward();
	void KingdomChange(uint16_t cid, uint8_t k)
	{
		unsigned i = getCitySeq(cid);
		m_cityMaster.erase(m_data->city[i].uid);
		m_data->city[i].KingdomChange(k);
	}
	void ResetMaster(uint16_t cid)
	{
		unsigned i = getCitySeq(cid);
		m_cityMaster.erase(m_data->city[i].uid);
		m_data->city[i].ResetMaster();
	}
	uint16_t GetCityByMaster(unsigned uid)
	{
		if(m_cityMaster.count(uid))
			return m_cityMaster[uid];
		else
			return 0;
	}
	void SetMaster(uint16_t cid, unsigned uid)
	{
		m_cityMaster[uid] = cid;
		m_data->city[getCitySeq(cid)].uid = uid;
	}
};

#endif /* BATTLEFIELDMANAGER_H_ */
