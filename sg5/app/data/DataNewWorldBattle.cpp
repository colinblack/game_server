/*
 * DataNewWorldBattle.cpp
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#include "DataNewWorldBattle.h"
#include "DataAllServerNewWorldBattle.h"

NewWorldBattleRoadMap CDataNewWorldBattle::m_roadmap;

bool NewWorldBattleHero::copy(NewWorldBattleHero &other)
{
	bool fix = false;

	if(other.property[NewWorldBattleProperty_hp] < property[NewWorldBattleProperty_hp])
		hp = min(max(0, hp - (property[NewWorldBattleProperty_hp] - other.property[NewWorldBattleProperty_hp]))
			,hp * other.property[NewWorldBattleProperty_hp] / property[NewWorldBattleProperty_hp]);
	hid = other.hid;
	if(kingdom != other.kingdom && other.kingdom)
	{
		kingdom = other.kingdom;
		cid = CDataNewWorldBattle::getCapital(kingdom);
		status = NewWorldBattleHeroStatus_wait_defence;
		next = 0;
		fix = true;
	}
	job = other.job;
	level = other.level;
	if(level > NEW_WORLD_BATTLE_HERO_LEVEL)
		level = NEW_WORLD_BATTLE_HERO_LEVEL;
	if(level == 0)
		level = 1;
	memcpy(name, other.name, sizeof(name));
	memcpy(property, other.property, sizeof(property));

	other.level = level;
	other.status = status;
	other.cid = cid;
	other.hp = hp;
	return fix;
}

CDataNewWorldBattle::CDataNewWorldBattle()
{
	m_init = false;

	m_ts = m_count = 0;
}

CDataNewWorldBattle::~CDataNewWorldBattle()
{}

int CDataNewWorldBattle::Init(const string &path, semdat sem)
{
	if(m_init)
		return 0;

	if(m_roadmap.empty())
	{
		for(unsigned i=0;i<NEW_WORLD_BATTLE_ROAD;++i)
		{
			m_roadmap[CDataNewWorld::road_map[i][0]].push_back(CDataNewWorld::road_map[i][1]);
			m_roadmap[CDataNewWorld::road_map[i][1]].push_back(CDataNewWorld::road_map[i][0]);
		}
	}

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataNewWorldBattle), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_NewWorldBattle_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata)
	{
		CAutoLock lock(&m_sh, true);

		if(!m_sh.HasInit())
		{
			memset(pdata, 0, sizeof(*pdata));

			unsigned now = Time::GetGlobalTime();
			for(unsigned k=0;k<=3;++k)
			{
				unsigned i = k ? (NEW_WORLD_BATTLE_CITY_KINGDOM * (k - 1) + NEW_WORLD_BATTLE_CITY_NEUTRAL) : 0;
				unsigned n = NEW_WORLD_BATTLE_CITY_KINGDOM * k + NEW_WORLD_BATTLE_CITY_NEUTRAL;
				unsigned j = NEW_WORLD_BATTLE_CITY_KINGDOM_SEQ * k + NEW_WORLD_BATTLE_CITY_CAPITAL;
				for(;i<n;++i,++j)
				{
					pdata->city[i].seq = i;
					pdata->city[i].cid = j;
					pdata->city[i].kingdom = k?k:4;
					pdata->city[i].countN = NEW_WORLD_BATTLE_CITY_NPC;
					pdata->city[i].npcts = now;
					pdata->city[i].ts = now;
				}
			}
			pdata->changets = now;
			pdata->ts = now;

			m_sh.SetInitDone();
		}
		sync(pdata);
	}
	else
		return R_ERR_DB;

	m_init = true;

	return 0;
}

const NewWorldBattleCityMap& CDataNewWorldBattle::GetWorld()
{
	checkTick();
	return m_citymap;
}
const NewWorldBattleCityBattle& CDataNewWorldBattle::GetCity(unsigned cid)
{
	checkTick();
	if(m_citymap.count(cid))
		return m_citymap[cid];
	else
		return m_citymap[0];
}
const NewWorldBattleHeroMap&  CDataNewWorldBattle::GetAllHero()
{
	checkTick();
	return m_heromap;
}
const NewWorldBattleHero&  CDataNewWorldBattle::GetHero(NewWorldBattleHeroIndex index)
{
	checkTick();
	if(isHero(index) && m_heromap.count(index))
		return m_heromap[index];
	else
		return m_heromap[NewWorldBattleHeroIndex(0, 0)];
}

int CDataNewWorldBattle::SetHero(NewWorldBattleHero &hero, bool &fix)
{
	checkTick();

	int ret = CheckOver();
	if(ret)
		return ret;

	if(!isHero(hero.index))
		return R_ERR_DB;

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	pdata->changets = now;

	if(m_heromap.count(hero.index))
	{
		fix = pdata->hero[m_heromap[hero.index].seq].copy(hero);
		pdata->hero[m_heromap[hero.index].seq].ts = now;
	}
	else
	{
		if(pdata->count == NEW_WORLD_BATTLE_HERO)
			return  R_ERR_DB;

		bool add = true;
		for(unsigned i=0;i<pdata->count;++i)
		{
			if(pdata->hero[i].index == hero.index)
			{
				fix = pdata->hero[i].copy(hero);
				pdata->hero[i].ts = now;
				add = false;
				break;
			}

		}
		if(add)
		{
			hero.seq = pdata->count;
			hero.hp = hero.property[NewWorldBattleProperty_hp];
			hero.cid = getCapital(hero.kingdom);
			if(hero.kingdom == 0)
				return  R_ERR_PARAM;
			if(hero.cid == 0)
				return  R_ERR_PARAM;
			hero.status = NewWorldBattleHeroStatus_wait_defence;
			hero.ts = now;

			pdata->hero[pdata->count] = hero;
			++pdata->count;

			pdata->city[m_citymap[hero.cid].city.seq].ts = now;
			/*20141114 change countN*/
			if(hero.kingdom)
				++pdata->city[m_citymap[hero.cid].city.seq].count[hero.kingdom-1];
			//debug_log("city=%u,count%u=%d,hero=%u,%u",hero.cid,hero.kingdom,pdata->city[m_citymap[hero.cid].city.seq].count[hero.kingdom-1],hero.index.uid,hero.index.index);
		}
	}

	return 0;
}
int CDataNewWorldBattle::Move(NewWorldBattleHeroIndex index, unsigned cid, bool leave, unsigned fly, unsigned &status)
{
	checkTick();

	int ret = CheckOver();
	if(ret)
		return ret;

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	if(!m_heromap.count(index))
	{
		status = m_heromap[index].status;
		return R_ERR_DB;
	}
	if(!m_citymap.count(cid))
	{
		status = m_heromap[index].status;
		return R_ERR_DB;
	}
	if(fly == 2)
	{
		if(m_heromap[index].kingdom != m_citymap[cid].city.kingdom)
		{
			bool f = true;
			if(m_roadmap.count(cid))
			{
				for(vector<unsigned>::const_iterator it=m_roadmap[cid].begin();it!=m_roadmap[cid].end();++it)
				{
					if(m_citymap[*it].city.kingdom == m_heromap[index].kingdom)
					{
						f = false;
						break;
					}
				}
			}
			if(f)
			{
				status = m_heromap[index].status;
				LOGIC_ERROR_RETURN_MSG("newworldbattle_city_can_not_move");
			}
		}
	}
	else if(fly == 1)
	{
		if(m_heromap[index].kingdom != m_citymap[cid].city.kingdom && !m_citymap[cid].city.Fighting())
		{
			status = m_heromap[index].status;
			LOGIC_ERROR_RETURN_MSG("newworldbattle_city_can_not_move");
		}
	}
	else if(!hasRoad(m_heromap[index].cid, cid))
	{
		status = m_heromap[index].status;
		LOGIC_ERROR_RETURN_MSG("newworldbattle_city_can_not_move");
	}

	if(!CanMove(m_heromap[index].status))
	{
		status = m_heromap[index].status;
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_can_not_move");
	}
	if((((m_citymap[m_heromap[index].cid].city.kingdom == m_heromap[index].kingdom
	&& m_citymap[m_heromap[index].cid].city.attacker.uid)
	|| (m_citymap[m_heromap[index].cid].city.kingdom != m_heromap[index].kingdom)) && !leave)
	/*|| (m_citymap[m_heromap[index].cid].city.kingdom == m_heromap[index].kingdom
	&& !m_citymap[m_heromap[index].cid].city.attacker.uid && leave)*/)
	{
		status = m_heromap[index].status;
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_can_not_move");
	}

	// 兵员低于5%时不能移动
	const static unsigned int precent = 5;
	if (m_heromap[index].hp < (m_heromap[index].property[NewWorldBattleProperty_hp] * precent / 100))
	{
		status = m_heromap[index].status;
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_hp_low_percent_5");
	}

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	unsigned seq = m_heromap[index].seq;
	if(!CanMove(pdata->hero[seq].status))
	{
		status = pdata->hero[seq].status;
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_can_not_move");
	}
	unsigned cityseq = m_citymap[pdata->hero[seq].cid].city.seq;
	if((((pdata->city[cityseq].kingdom == pdata->hero[seq].kingdom
	&& pdata->city[cityseq].attacker.uid)
	|| (pdata->city[cityseq].kingdom != pdata->hero[seq].kingdom)) && !leave)
	/*|| (pdata->city[cityseq].kingdom == pdata->hero[seq].kingdom
	&& !pdata->city[cityseq].attacker.uid && leave)*/)
	{
		status = pdata->hero[seq].status;
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_can_not_move");
	}

	if (pdata->hero[seq].hp < (pdata->hero[seq].property[NewWorldBattleProperty_hp] * precent / 100))
	{
		status = pdata->hero[seq].status;
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_hp_low_percent_5");
	}

	pdata->changets = now;

	unsigned nextseq = m_citymap[cid].city.seq;
	pdata->hero[seq].status = NewWorldBattleHeroStatus_wait_move;
	if(pdata->hero[seq].kingdom != pdata->city[nextseq].kingdom && isCapital(cid))
	{
		pdata->hero[seq].next = getCapital(pdata->hero[seq].kingdom);
		++pdata->city[nextseq].damage;
		pdata->city[nextseq].ts = now;
	}
	else
		pdata->hero[seq].next = cid;
	pdata->hero[seq].ts = now;

	status = NewWorldBattleHeroStatus_wait_move;

	//debug_log("city=%u,next=%u,hero=%u,%u",pdata->hero[seq].cid,cid,index.uid,index.index);
	return 0;
}
int CDataNewWorldBattle::Change(NewWorldBattleHeroIndex index, unsigned type)
{
	checkTick();

	int ret = CheckOver();
	if(ret)
		return ret;

	if(!m_heromap.count(index))
		return R_ERR_DB;

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	pdata->changets = now;

	pdata->hero[m_heromap[index].seq].type = type;
	pdata->hero[m_heromap[index].seq].ts = now;

	return 0;
}
int CDataNewWorldBattle::Clone(NewWorldBattleHeroIndex index)
{
	checkTick();

	int ret = CheckOver();
	if(ret)
		return ret;

	if(!m_heromap.count(index))
		return R_ERR_DB;
	if(!m_citymap.count(m_heromap[index].cid))
		return R_ERR_DB;

	if(m_citymap[m_heromap[index].cid].city.countV == NEW_WORLD_BATTLE_CITY_VISION)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_vision_full");
	}

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	if(isCapital(pdata->hero[m_heromap[index].seq].cid) || pdata->hero[m_heromap[index].seq].cid != m_heromap[index].cid)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_die");
	}

	unsigned seq = m_citymap[m_heromap[index].cid].city.seq;

	if(pdata->city[seq].countV > NEW_WORLD_BATTLE_CITY_VISION)
	{
		pdata->city[seq].countV = 0;
		for(unsigned count=0;count<NEW_WORLD_BATTLE_CITY_VISION;++count)
		{
			if(pdata->city[seq].vision[count].index.uid)
				++pdata->city[seq].countV;
		}
	}
	if(pdata->city[seq].countV == NEW_WORLD_BATTLE_CITY_VISION)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_vision_full");
	}

	for(unsigned count=0;count<NEW_WORLD_BATTLE_CITY_VISION;++count)
	{
		if(!pdata->city[seq].vision[count].index.uid)
		{
			pdata->city[seq].vision[count] = pdata->hero[m_heromap[index].seq];
			pdata->city[seq].vision[count].status = pdata->city[seq].kingdom == pdata->city[seq].vision[count].kingdom?
														NewWorldBattleHeroStatus_wait_defence:NewWorldBattleHeroStatus_wait_attack;
			pdata->city[seq].vision[count].index.uid = index.index + 1;
			pdata->city[seq].vision[count].index.index = count;
			pdata->city[seq].vision[count].seq = index.uid;
			pdata->city[seq].vision[count].ts = now;
			pdata->city[seq].vision[count].next = now;

			++pdata->city[seq].countV;
			/*20141114 change countN*/
			if(pdata->city[seq].vision[count].kingdom)
				++pdata->city[seq].count[pdata->city[seq].vision[count].kingdom-1];
			//debug_log("city=%u,count%u=%d,countV=%d,hero=%u,%u",pdata->city[seq].cid,pdata->city[seq].vision[count].kingdom,pdata->city[seq].count[pdata->city[seq].vision[count].kingdom-1],pdata->city[seq].countV,index.uid,index.index);

			pdata->city[seq].ts = now;
			pdata->changets = now;

			addKill(pdata->hero[m_heromap[index].seq], NEW_WORLD_BATTLE_KILL_ADD_CLONE, now, pdata);

			return 0;
		}
	}

	LOGIC_ERROR_RETURN_MSG("newworldbattle_vision_full");
}
int CDataNewWorldBattle::Rush(NewWorldBattleHeroIndex index, NewWorldBattleHero &other, NewWorldBattleHero &end)
{
	checkTick();

	int ret = CheckOver();
	if(ret)
		return ret;

	if(!m_heromap.count(index))
		return R_ERR_DB;
	if(!m_citymap.count(m_heromap[index].cid))
		return R_ERR_DB;

	unsigned r = 0;
	unsigned cid = m_heromap[index].cid;
	if(!CanMove(m_heromap[index].status))
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_fighting_can_not_rush");
	}
	if(m_heromap[index].kingdom == m_citymap[cid].city.kingdom
	&& (m_citymap[cid].attacker.size() <= NEW_WORLD_BATTLE_RUSH_MIN
	|| m_citymap[cid].defender.size() <= NEW_WORLD_BATTLE_RUSH_MIN))
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_rush_min");
	}
	if(m_heromap[index].kingdom != m_citymap[cid].city.kingdom
	&& (m_citymap[cid].attacker.size() <= NEW_WORLD_BATTLE_RUSH_MIN
	|| m_citymap[cid].defender.size() + m_citymap[cid].city.countN  <= NEW_WORLD_BATTLE_RUSH_MIN))
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_rush_min");
	}
	NewWorldBattleCityQueue &checkqueue = m_heromap[index].kingdom == m_citymap[cid].city.kingdom?m_citymap[cid].defender:m_citymap[cid].attacker;
	for(NewWorldBattleCityQueue::iterator sit=checkqueue.begin();sit!=checkqueue.end();++sit)
	{
		++r;
		if(index == sit->second)
		{
			LOGIC_ERROR_RETURN_MSG("newworldbattle_fighting_can_not_rush");
		}
		if(r >= NEW_WORLD_BATTLE_RUSH_MIN)
			break;
	}

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	unsigned heroseq = m_heromap[index].seq;
	cid = pdata->hero[heroseq].cid;
	unsigned cityseq = m_citymap[cid].city.seq;
	unsigned otherseq = 0;

	if(!CanMove(pdata->hero[heroseq].status))
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_fighting_can_not_rush");
	}

	bool rush_att = pdata->hero[heroseq].kingdom != pdata->city[cityseq].kingdom;
	NewWorldBattleHero npc;
	r = 0;
	NewWorldBattleCityQueue &queue = rush_att ? m_citymap[cid].defender : m_citymap[cid].attacker;
	NewWorldBattleCityQueue::iterator it=queue.begin();
	for(;it!=queue.end();++it)
	{
		++r;
		if(r <= NEW_WORLD_BATTLE_RUSH_MIN)
			continue;
		if(isHero(it->second))
		{
			otherseq = m_heromap[it->second].seq;
			if(!CanMove(pdata->hero[otherseq].status) ||  pdata->hero[otherseq].cid != cid || (rush_att ? (pdata->hero[otherseq].kingdom != pdata->city[cityseq].kingdom) : (pdata->hero[otherseq].kingdom == pdata->city[cityseq].kingdom)))
				continue;
		}
		else if(!pdata->city[cityseq].vision[it->second.index].index.uid || !CanMove(pdata->city[cityseq].vision[it->second.index].status) || (rush_att ? (pdata->city[cityseq].vision[it->second.index].kingdom != pdata->city[cityseq].kingdom) : (pdata->city[cityseq].vision[it->second.index].kingdom == pdata->city[cityseq].kingdom)))
			continue;
		break;
	}
	if(it == queue.end())
	{
		if(rush_att && pdata->city[cityseq].countN)
			makeNPC(npc);
		else
		{
			LOGIC_ERROR_RETURN_MSG("newworldbattle_rush_min");
		}
	}

	NewWorldBattleHero &attacker = rush_att ? pdata->hero[heroseq] : (it == queue.end() ? npc : (isHero(it->second) ? pdata->hero[otherseq] : pdata->city[cityseq].vision[it->second.index]));
	NewWorldBattleHero &defender = rush_att ? (it == queue.end() ? npc : (isHero(it->second) ? pdata->hero[otherseq] : pdata->city[cityseq].vision[it->second.index])) : pdata->hero[heroseq];
	other = rush_att ? defender : attacker;

	pdata->changets = now;
	pdata->city[cityseq].ts = now;
	unsigned result = NewWorldBattleHeroAttackResult_none;
	attacker.ts = now;
	defender.ts = now;

	int ak, dk;
	result = attacking(attacker,defender,ak,dk);
	addKill(attacker, defender, ak, dk, now, pdata);
	addKill(defender, attacker, dk, ak, now, pdata);

	if(result == NewWorldBattleHeroAttackResult_attacker_win)
		end = attacker;
	else if(result == NewWorldBattleHeroAttackResult_defender_win)
		end = defender;

	for(int r=0;r<2;++r)
	{
		if((r && result == NewWorldBattleHeroAttackResult_attacker_win)
		|| (!r && result == NewWorldBattleHeroAttackResult_defender_win))
			continue;

		NewWorldBattleHero &loser = r?attacker:defender;
		if(isHero(loser.index))
		{
			loser.cid = getCapital(loser.kingdom);
			loser.status = NewWorldBattleHeroStatus_wait_defence;
			/*20141114 change countN*/
			if(loser.kingdom)
			{
				--pdata->city[cityseq].count[loser.kingdom-1];
				//debug_log("[hero die]city=%u,count%u=%d,hero=%u,%u",pdata->city[cityseq].cid,loser.kingdom,pdata->city[cityseq].count[loser.kingdom-1],loser.index.uid,loser.index.index);
				++pdata->city[m_citymap[loser.cid].city.seq].count[loser.kingdom-1];
				//debug_log("[hero home]city=%u,count%u=%d,hero=%u,%u",loser.cid,loser.kingdom,pdata->city[m_citymap[loser.cid].city.seq].count[loser.kingdom-1],loser.index.uid,loser.index.index);
			}
		}
		else if(isVision(loser.index))
		{
			--pdata->city[cityseq].countV;
			if(pdata->city[cityseq].countV >= NEW_WORLD_BATTLE_CITY_VISION)
			{
				pdata->city[cityseq].countV = 0;
				for(unsigned count=0;count<NEW_WORLD_BATTLE_CITY_VISION;++count)
				{
					if(pdata->city[cityseq].vision[count].index.uid)
						++pdata->city[cityseq].countV;
				}
			}
			/*20141114 change countN*/
			if(loser.kingdom)
				--pdata->city[cityseq].count[loser.kingdom-1];
			//debug_log("[vision die]city=%u,count%u=%d,countV=%d,hero=%u,%u",pdata->city[cityseq].cid,loser.kingdom,pdata->city[cityseq].count[loser.kingdom-1],pdata->city[cityseq].countV,loser.index.uid,loser.index.index);

			memset(&(pdata->city[cityseq].vision[loser.index.index]),0,sizeof(NewWorldBattleHero));
		}
		else if(isNPC(loser.index))
		{
			--pdata->city[cityseq].countN;
			if(pdata->city[cityseq].countN >= NEW_WORLD_BATTLE_CITY_NPC)
				pdata->city[cityseq].countN = 0;
		}
	}

	addKill(pdata->hero[heroseq], NEW_WORLD_BATTLE_KILL_ADD_RUSH, now, pdata);

	return 0;
}

int CDataNewWorldBattle::Recover(NewWorldBattleHeroIndex index, unsigned num)
{
	if(!num)
		return 0;

	checkTick();

	int ret = CheckOver();
	if(ret)
		return ret;

	if(!m_heromap.count(index))
		return R_ERR_DB;
	if(IsFighting(m_heromap[index].status))
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_fighting_can_not_recover");
	}

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	unsigned seq = m_heromap[index].seq;
	if(IsFighting(pdata->hero[seq].status))
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_fighting_can_not_recover");
	}
	if(pdata->hero[seq].hp >= pdata->hero[seq].property[NewWorldBattleProperty_hp])
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_full_can_not_recover");
	}

	pdata->changets = now;

	pdata->hero[seq].hp += num * NEW_WORLD_BATTLE_HERO_RECOVER;
	if(pdata->hero[seq].hp > pdata->hero[seq].property[NewWorldBattleProperty_hp])
		pdata->hero[seq].hp = pdata->hero[seq].property[NewWorldBattleProperty_hp];
	pdata->hero[seq].ts = now;

	return 0;
}

int CDataNewWorldBattle::sync(DataNewWorldBattle *pdata)
{
	m_count = pdata->count;
	m_ts = pdata->ts;
	memset(m_kingdomcityNum, 0 , sizeof(m_kingdomcityNum));
	for(unsigned i=0;i<NEW_WORLD_BATTLE_CITY;++i)
	{
		if(pdata->city[i].kingdom)
			++m_kingdomcityNum[pdata->city[i].kingdom - 1];
		unsigned cid = pdata->city[i].cid;
		if(m_citymap[cid].city.ts != pdata->city[i].ts)
		{
			//debug_log("[sync city]cid=%u",pdata->city[i].cid);
			m_citymap[cid].city = pdata->city[i];
			m_citymap[cid].attacker.clear();
			m_citymap[cid].defender.clear();

			if(canAttack(cid) && pdata->city[i].Fighting())
			{
				//debug_log("[sync queue]cid=%u",pdata->city[i].cid);
				if(pdata->city[i].countV)
				{
					for(unsigned idata=0;idata<NEW_WORLD_BATTLE_CITY_VISION;++idata)
					{
						if(pdata->city[i].vision[idata].index.uid && IsReady(pdata->city[i].vision[idata].status))
						{
							pair<pair<unsigned, unsigned>, NewWorldBattleHeroIndex> queue(pair<unsigned, unsigned>(pdata->city[i].vision[idata].next,pdata->city[i].vision[idata].index.index),pdata->city[i].vision[idata].index);
							if(IsDefender(pdata->city[i].vision[idata].status))
								m_citymap[cid].defender.insert(queue);
							else if(IsAttacker(pdata->city[i].vision[idata].status))
								m_citymap[cid].attacker.insert(queue);
						}
					}
				}
			}
		}
	}
	for(unsigned j=0;j<pdata->count;++j)
	{
		NewWorldBattleHeroIndex index = pdata->hero[j].index;
		if(m_heromap[index].ts != pdata->hero[j].ts)
			m_heromap[index] = pdata->hero[j];

		unsigned cid = pdata->hero[j].cid;
		if(m_citymap[cid].city.Fighting()
		&& canAttack(cid)
		&& IsReady(pdata->hero[j].status))
		{
			pair<pair<unsigned, unsigned>, NewWorldBattleHeroIndex> queue(pair<unsigned, unsigned>(pdata->hero[j].next,pdata->hero[j].seq),index);
			if(IsDefender(pdata->hero[j].status))
			{
				//debug_log("[defend queue]city=%u,hero=%u,%u",cid,pdata->hero[j].index.uid,pdata->hero[j].index.index);
				m_citymap[cid].defender.insert(queue);
			}
			else if(IsAttacker(pdata->hero[j].status))
			{
				//debug_log("[attack queue]city=%u,hero=%u,%u",cid,pdata->hero[j].index.uid,pdata->hero[j].index.index);
				m_citymap[cid].attacker.insert(queue);
			}
			else
			{
				if(m_citymap[cid].city.kingdom == pdata->hero[j].kingdom)
				{
					//debug_log("[defend queue]city=%u,hero=%u,%u",cid,pdata->hero[j].index.uid,pdata->hero[j].index.index);
					m_citymap[cid].defender.insert(queue);
				}
				else
				{
					//debug_log("[attack queue]city=%u,hero=%u,%u",cid,pdata->hero[j].index.uid,pdata->hero[j].index.index);
					m_citymap[cid].attacker.insert(queue);
				}
			}
		}
	}

	return 0;
}

int CDataNewWorldBattle::checkTick()
{
	//check tick first for sync
	unsigned now = Time::GetGlobalTime();
	if(now < m_ts + NEW_WORLD_BATTLE_TICK)
		return 0;

	m_battlechange.clear();
	set<unsigned> changeset;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata)
	{
		CAutoLock lock(&(m_sh), true);

		//check tick again for lock
		if(now < pdata->ts + NEW_WORLD_BATTLE_TICK)
		{
			//debug_log("sync only ts=%u->%u,%u",m_ts,pdata->ts,pdata->changets);
			if(m_ts < pdata->changets || pdata->ts == pdata->changets || now < pdata->changets)
				sync(pdata);
			else
				m_ts = pdata->ts;
			return 0;
		}
		else if(m_ts != pdata->ts)
		{
			//debug_log("sync before ts=%u->%u,%u",m_ts,pdata->ts,pdata->changets);
			if(m_ts < pdata->changets || m_ts > pdata->ts)
				sync(pdata);
			else
				m_ts = pdata->ts;
		}

		//tick
		while(now >= pdata->ts + NEW_WORLD_BATTLE_TICK)
		{
			bool bugflag = false;
			//city
			for(unsigned i=0;i<NEW_WORLD_BATTLE_CITY;++i)
			{
				if(pdata->city[i].bug())
					bugflag = true;

				if(!canAttack(pdata->city[i].cid))
					continue;

				unsigned result = NewWorldBattleHeroAttackResult_none;
			//stage 1. attack : hero:hp,cid,status; city:attacker,defender, vision:hp, count123, countN, countV
				if(pdata->city[i].attacker.uid && pdata->city[i].defender.uid)
				{
					pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
					pdata->city[i].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;

					NewWorldBattleHero &attacker = isHero(pdata->city[i].attacker)?
							pdata->hero[m_heromap[pdata->city[i].attacker].seq]:
							pdata->city[i].vision[pdata->city[i].attacker.index];
					NewWorldBattleHero &defender = isHero(pdata->city[i].defender)?
							pdata->hero[m_heromap[pdata->city[i].defender].seq]:
							pdata->city[i].vision[pdata->city[i].defender.index];

					attacker.ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					defender.ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					int ak, dk;
					result = attacking(attacker,defender,ak,dk);
					addKill(attacker, defender, ak, dk, pdata->ts + NEW_WORLD_BATTLE_TICK, pdata);
					addKill(defender, attacker, dk, ak, pdata->ts + NEW_WORLD_BATTLE_TICK, pdata);

					for(int r=0;r<2;++r)
					{
						if((r && result == NewWorldBattleHeroAttackResult_attacker_win)
						|| (!r && result == NewWorldBattleHeroAttackResult_defender_win))
							continue;

						if(r)
							pdata->city[i].attacker.clear();
						else
							pdata->city[i].defender.clear();

						NewWorldBattleHero &loser = r?attacker:defender;
						if(isHero(loser.index))
						{
							loser.cid = getCapital(loser.kingdom);
							loser.status = NewWorldBattleHeroStatus_wait_defence;
							/*20141114 change countN*/
							if(loser.kingdom)
							{
								--pdata->city[i].count[loser.kingdom-1];
								//debug_log("[hero die]city=%u,count%u=%d,hero=%u,%u",pdata->city[i].cid,loser.kingdom,pdata->city[i].count[loser.kingdom-1],loser.index.uid,loser.index.index);
								++pdata->city[m_citymap[loser.cid].city.seq].count[loser.kingdom-1];
								//debug_log("[hero home]city=%u,count%u=%d,hero=%u,%u",loser.cid,loser.kingdom,pdata->city[m_citymap[loser.cid].city.seq].count[loser.kingdom-1],loser.index.uid,loser.index.index);
							}
						}
						else if(isVision(loser.index))
						{
							--pdata->city[i].countV;
							if(pdata->city[i].countV >= NEW_WORLD_BATTLE_CITY_VISION)
							{
								pdata->city[i].countV = 0;
								for(unsigned count=0;count<NEW_WORLD_BATTLE_CITY_VISION;++count)
								{
									if(pdata->city[i].vision[count].index.uid)
										++pdata->city[i].countV;
								}
							}
							/*20141114 change countN*/
							if(loser.kingdom)
								--pdata->city[i].count[loser.kingdom-1];
							//debug_log("[vision die]city=%u,count%u=%d,countV=%d,hero=%u,%u",pdata->city[i].cid,loser.kingdom,pdata->city[i].count[loser.kingdom-1],pdata->city[i].countV,loser.index.uid,loser.index.index);

							memset(&(pdata->city[i].vision[loser.index.index]),0,sizeof(NewWorldBattleHero));
						}
						else if(isNPC(loser.index))
						{
							--pdata->city[i].countN;
							if(pdata->city[i].countN >= NEW_WORLD_BATTLE_CITY_NPC)
								pdata->city[i].countN = 0;
							memset(&(pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION]),0,sizeof(NewWorldBattleHero));
							//debug_log("[npc die]city=%u,countN=%u",pdata->city[i].cid,pdata->city[i].countN);
						}
					}
				}
			//stage 2. choose next : hero:status, city:attacker,defender, vision:status
				for(int r=1;r>=0;--r)
				{
					if((r && result == NewWorldBattleHeroAttackResult_attacker_win)
					|| (!r && result == NewWorldBattleHeroAttackResult_defender_win))
						continue;

					if(!r && !pdata->city[i].attacker.uid)
						continue;

					NewWorldBattleHeroIndex &index = r?pdata->city[i].attacker:pdata->city[i].defender;
					NewWorldBattleCityQueue &queue = r?m_citymap[pdata->city[i].cid].attacker:m_citymap[pdata->city[i].cid].defender;
					for(NewWorldBattleCityQueue::iterator it=queue.begin();it!=queue.end();++it)
					{
						if(isHero(it->second))
						{
							unsigned seq = m_heromap[it->second].seq;
							if(IsReady(pdata->hero[seq].status) && pdata->hero[seq].cid == pdata->city[i].cid)
							{
								index = it->second;
								//debug_log("[choose hero]city=%u,r=%d,hero=%u,%u",pdata->city[i].cid,r,index.uid,index.index);
								pdata->hero[seq].status = r?NewWorldBattleHeroStatus_attack:NewWorldBattleHeroStatus_defence;
								pdata->hero[seq].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
								break;
							}
						}
						else if(isVision(it->second))
						{
							if(pdata->city[i].vision[it->second.index].index.uid && IsReady(pdata->city[i].vision[it->second.index].status))
							{
								index = it->second;
								//debug_log("[choose vision]city=%u,r=%d,hero=%u,%u",pdata->city[i].cid,r,index.uid,index.index);
								pdata->city[i].vision[it->second.index].status = r?NewWorldBattleHeroStatus_attack:NewWorldBattleHeroStatus_defence;
								break;
							}
						}
					}
					if(!index.uid)
					{
						if(pdata->city[i].countV)
						{
							for(unsigned v=0;v<NEW_WORLD_BATTLE_CITY_VISION;++v)
							{
								if(pdata->city[i].vision[v].index.uid
								&& IsReady(pdata->city[i].vision[v].status)
								&& ((r && pdata->city[i].vision[v].kingdom != pdata->city[i].kingdom)
								|| (!r && pdata->city[i].vision[v].kingdom == pdata->city[i].kingdom)))
								{
									index = pdata->city[i].vision[v].index;
									//debug_log("[choose vision]city=%u,r=%d,hero=%u,%u",pdata->city[i].cid,r,index.uid,index.index);
									pdata->city[i].vision[v].status = r?NewWorldBattleHeroStatus_attack:NewWorldBattleHeroStatus_defence;
									break;
								}
							}
						}
					}
					if(!index.uid && !r && pdata->city[i].countN)
					{
						if(pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION].index.uid)
						{
							pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION].status = NewWorldBattleHeroStatus_defence;
							index = pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION].index;
						}
						else
						{
							pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION].job = pdata->city[i].countN;
							makeNPC(pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION]);
							pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION].cid = pdata->city[i].cid;
							pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION].kingdom = pdata->city[i].kingdom;
							index = pdata->city[i].vision[NEW_WORLD_BATTLE_CITY_VISION].index;
						}
						//debug_log("[choose npc]city=%u,r=%d,hero=%u,%u",pdata->city[i].cid,r,index.uid,index.index);
					}
					if(index.uid)
					{
						pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
						pdata->city[i].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;

						if(!result)
							changeset.insert(pdata->city[i].cid);
					}
				}
			//stage 3. occupy : city:attacker, defender, npcts, countN, uid, kingdom, name; hero:status
				if(pdata->city[i].attacker.uid && !pdata->city[i].defender.uid)
				{
					//debug_log("[occupy]city=%u",pdata->city[i].cid);
					changeset.insert(pdata->city[i].cid);

					pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
					pdata->city[i].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					if(isHero(pdata->city[i].attacker))
						pdata->city[i].kingdom = pdata->hero[m_heromap[pdata->city[i].attacker].seq].kingdom;
					else
						pdata->city[i].kingdom = pdata->city[i].vision[pdata->city[i].attacker.index].kingdom;
					pdata->city[i].tower.clear();
					pdata->city[i].npcts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					pdata->city[i].countN = NEW_WORLD_BATTLE_CITY_OCCUPY_NPC;
					if(isHero(pdata->city[i].attacker))
					{
						pdata->hero[m_heromap[pdata->city[i].attacker].seq].status = NewWorldBattleHeroStatus_wait_defence;
						pdata->hero[m_heromap[pdata->city[i].attacker].seq].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					}
					addKill(pdata->hero[m_heromap[pdata->city[i].attacker].seq], NEW_WORLD_BATTLE_KILL_ADD_LAST, pdata->ts + NEW_WORLD_BATTLE_TICK, pdata);
					pdata->city[i].attacker.clear();
					for(NewWorldBattleCityQueue::iterator it=m_citymap[pdata->city[i].cid].attacker.begin();it!=m_citymap[pdata->city[i].cid].attacker.end();++it)
					{
						if(isHero(it->second))
						{
							unsigned seq = m_heromap[it->second].seq;
							if(IsInCity(pdata->hero[seq].status))
							{
								pdata->hero[seq].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
								if(pdata->hero[seq].kingdom == pdata->city[i].kingdom)
									pdata->hero[seq].status = NewWorldBattleHeroStatus_wait_defence;
								else
									pdata->hero[seq].status = NewWorldBattleHeroStatus_wait_attack;
								addKill(pdata->hero[seq], NEW_WORLD_BATTLE_KILL_ADD_QUEUE, pdata->ts + NEW_WORLD_BATTLE_TICK, pdata);
							}
						}
					}
					if(pdata->city[i].countV)
					{
						for(unsigned v=0;v<NEW_WORLD_BATTLE_CITY_VISION;++v)
						{
							if(pdata->city[i].vision[v].index.uid)
							{
								if(pdata->city[i].vision[v].kingdom == pdata->city[i].kingdom)
									pdata->city[i].vision[v].status = NewWorldBattleHeroStatus_wait_defence;
								else
									pdata->city[i].vision[v].status = NewWorldBattleHeroStatus_wait_attack;
								addKill(pdata->city[i].vision[v], NEW_WORLD_BATTLE_KILL_ADD_QUEUE, pdata->ts + NEW_WORLD_BATTLE_TICK, pdata);
							}
						}
					}
				}
				else if(pdata->city[i].defender.uid && !pdata->city[i].attacker.uid)
				{
					changeset.insert(pdata->city[i].cid);

					pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
					pdata->city[i].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					if(isHero(pdata->city[i].defender))
					{
						pdata->hero[m_heromap[pdata->city[i].defender].seq].status = NewWorldBattleHeroStatus_wait_defence;
						pdata->hero[m_heromap[pdata->city[i].defender].seq].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					}
					else if(isVision(pdata->city[i].defender))
					{
						pdata->city[i].vision[pdata->city[i].defender.index].status = NewWorldBattleHeroStatus_wait_defence;
					}
					else if(isNPC(pdata->city[i].defender))
					{
						pdata->city[i].vision[pdata->city[i].defender.index].status = NewWorldBattleHeroStatus_wait_defence;
					}
					pdata->city[i].defender.clear();
				}

				unsigned npctime = NEW_WORLD_BATTLE_CITY_NPC_TIME;
				if(pdata->city[i].npcts + npctime < pdata->ts + NEW_WORLD_BATTLE_TICK)
				{
					//debug_log("++npc cid=%u,time=%u,npcts=%u,ts=%u",pdata->city[i].cid,npctime,pdata->city[i].npcts,pdata->ts+NEW_WORLD_BATTLE_TICK);
					pdata->city[i].npcts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					if(pdata->city[i].countN < NEW_WORLD_BATTLE_CITY_NPC)
					{
						pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
						pdata->city[i].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
						++pdata->city[i].countN;
					}
					else if(pdata->city[i].countN > NEW_WORLD_BATTLE_CITY_NPC)
						pdata->city[i].countN = 0;
				}
			}
			//hero
			for(unsigned j=0;j<pdata->count;++j)
			{
			//stage 4. move & recover : hero:status,cid,next,hp; city: count123
				if(!pdata->city[m_citymap[pdata->hero[j].cid].city.seq].Fighting()
				&& !IsFighting(pdata->hero[j].status)
				&& pdata->hero[j].recover(pdata->hero[j].kingdom?m_kingdomcityNum[pdata->hero[j].kingdom-1]:NEW_WORLD_BATTLE_CITY_KINGDOM))
				{
					pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
					pdata->hero[j].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
				}
				if(pdata->hero[j].status == NewWorldBattleHeroStatus_wait_move)
				{
					pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
					pdata->hero[j].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					unsigned seq = m_citymap[pdata->hero[j].cid].city.seq;
					pdata->city[seq].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					/*20141114 change countN*/
					if(pdata->hero[j].kingdom)
					{
						--pdata->city[seq].count[pdata->hero[j].kingdom-1];
						//debug_log("[leave]city=%u,count%u=%d,hero=%u,%u",pdata->city[seq].cid,pdata->hero[j].kingdom,pdata->city[seq].count[pdata->hero[j].kingdom-1],pdata->hero[j].index.uid,pdata->hero[j].index.index);
					}
					if(pdata->hero[j].next && pdata->hero[j].next < NEW_WORLD_BATTLE_CITY_KINGDOM_SEQ*4)
						pdata->hero[j].cid = pdata->hero[j].next;
					pdata->hero[j].status = NewWorldBattleHeroStatus_move;
					unsigned newseq = m_citymap[pdata->hero[j].cid].city.seq;
					pdata->city[newseq].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					/*20141114 change countN*/
					if(pdata->hero[j].kingdom)
					{
						++pdata->city[newseq].count[pdata->hero[j].kingdom-1];
						//debug_log("[arrive]city=%u,count%u=%d,hero=%u,%u",pdata->city[newseq].cid,pdata->hero[j].kingdom,pdata->city[newseq].count[pdata->hero[j].kingdom-1],pdata->hero[j].index.uid,pdata->hero[j].index.index);
					}
					pdata->hero[j].next = pdata->ts + NEW_WORLD_BATTLE_TICK*2;
				}
				else if(pdata->hero[j].status == NewWorldBattleHeroStatus_move)
				{
					pdata->changets = pdata->ts + NEW_WORLD_BATTLE_TICK;
					pdata->hero[j].ts = pdata->ts + NEW_WORLD_BATTLE_TICK;
					unsigned seq = m_citymap[pdata->hero[j].cid].city.seq;
					if(pdata->city[seq].kingdom == pdata->hero[j].kingdom)
						pdata->hero[j].status = NewWorldBattleHeroStatus_wait_defence;
					else
						pdata->hero[j].status = NewWorldBattleHeroStatus_wait_attack;
				}
			}

			if(bugflag)
				_fix(pdata, pdata->ts + NEW_WORLD_BATTLE_TICK);

			pdata->ts += NEW_WORLD_BATTLE_TICK;

			//debug_log("sync after ts=%u->%u,%u",m_ts,pdata->ts,pdata->changets);
			if(m_ts < pdata->changets || pdata->ts == pdata->changets || now < pdata->changets)
				sync(pdata);
			else
				m_ts = pdata->ts;
		}
	}
	else
		return R_ERR_DB;

	if(!changeset.empty())
	{
		for(set<unsigned>::iterator it=changeset.begin();it!=changeset.end();++it)
		{
			m_battlechange[*it].cid = *it;
			m_battlechange[*it].kingdom = m_citymap[*it].city.kingdom;
			m_battlechange[*it].battle = m_citymap[*it].city.Fighting()?1:0;
		}
	}

	return 0;
}

int CDataNewWorldBattle::PrintHero()
{
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(Config::GetPath(CONFIG_NEW_WORLD_BATTLE_DATA).c_str(), sizeof(DataNewWorldBattle), SEM_ID(sem_new_world_battle,semgroup,semserver)))
	{
		cout<<"shm fail"<<endl;
		return R_ERR_DB;
	}

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		cout<<"address fail"<<endl;
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	cout<<"heros:"<<pdata->count<<endl;
	for(unsigned j=0;j<pdata->count;++j)
	{
		cout<<"uid:"<<pdata->hero[j].index.uid<<","<<pdata->hero[j].index.index
			<<" kingdom:"<<pdata->hero[j].kingdom<<" hid:"<<pdata->hero[j].hid
			<<" level:"<<pdata->hero[j].level<<" job:"<<pdata->hero[j].job
			<<" type:"<<pdata->hero[j].type<<" cid:"<<pdata->hero[j].cid
			<<" next:"<<pdata->hero[j].next<<" status:"<<pdata->hero[j].status
			<<" hp:"<<pdata->hero[j].hp<<" kill:"<<pdata->hero[j].kill
			<<endl;
	}

	return 0;
}
int CDataNewWorldBattle::PrintCity()
{
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(Config::GetPath(CONFIG_NEW_WORLD_BATTLE_DATA).c_str(), sizeof(DataNewWorldBattle), SEM_ID(sem_new_world_battle,semgroup,semserver)))
	{
		cout<<"shm fail"<<endl;
		return R_ERR_DB;
	}

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		cout<<"address fail"<<endl;
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	for(unsigned j=0;j<NEW_WORLD_BATTLE_CITY;++j)
	{
		cout<<"cid:"<<pdata->city[j].cid
			<<" kingdom:"<<pdata->city[j].kingdom
			<<" attacker:"<<pdata->city[j].attacker.uid<<","<<pdata->city[j].attacker.index
			<<" defender:"<<pdata->city[j].defender.uid<<","<<pdata->city[j].defender.index
			<<" count:"<<pdata->city[j].count[0]<<","<<pdata->city[j].count[1]<<","<<pdata->city[j].count[2]<<","<<pdata->city[j].count[3]
			<<","<<pdata->city[j].countV<<","<<pdata->city[j].countN
			<<" npcts:"<<pdata->city[j].npcts
			<<" reward:"<<pdata->city[j].reward<<","<<pdata->city[j].nextReward
			<<endl;
		for(unsigned i=0;i<NEW_WORLD_BATTLE_CITY_VISION;++i)
		{
			if(pdata->city[j].vision[i].index.uid)
				cout<<" seq:"<<pdata->city[j].vision[i].index.index
				<<" uid:"<<pdata->city[j].vision[i].seq<<","<<pdata->city[j].vision[i].index.uid-1
				<<" kingdom:"<<pdata->city[j].vision[i].kingdom<<" hid:"<<pdata->city[j].vision[i].hid
				<<" level:"<<pdata->city[j].vision[i].level<<" job:"<<pdata->city[j].vision[i].job
				<<" type:"<<pdata->city[j].vision[i].type<<" cid:"<<pdata->city[j].vision[i].cid
				<<" next:"<<pdata->city[j].vision[i].next<<" status:"<<pdata->city[j].vision[i].status
				<<" hp:"<<pdata->city[j].vision[i].hp<<endl;
		}
	}

	return 0;
}
int CDataNewWorldBattle::Watch()
{
	checkTick();

	for(NewWorldBattleHeroMap::iterator it=m_heromap.begin();it!=m_heromap.end();++it)
	{
		cout<<"uid:"<<it->second.index.uid<<","<<it->second.index.index
			<<" kingdom:"<<it->second.kingdom<<" hid:"<<it->second.hid
			<<" level:"<<it->second.level<<" job:"<<it->second.job
			<<" type:"<<it->second.type<<" cid:"<<it->second.cid
			<<" next:"<<it->second.next<<" status:"<<it->second.status
			<<" hp:"<<it->second.hp<<" kill:"<<it->second.kill
			<<endl;
	}
	for(NewWorldBattleCityMap::iterator it=m_citymap.begin();it!=m_citymap.end();++it)
	{
		cout<<"cid:"<<it->second.city.cid
			<<" kingdom:"<<it->second.city.kingdom
			<<" attacker:"<<it->second.city.attacker.uid<<","<<it->second.city.attacker.index
			<<" defender:"<<it->second.city.defender.uid<<","<<it->second.city.defender.index
			<<" count:"<<it->second.city.count[0]<<","<<it->second.city.count[1]<<","<<it->second.city.count[2]<<","<<it->second.city.count[3]
			<<","<<it->second.city.countV<<","<<it->second.city.countN
			<<" npcts:"<<it->second.city.npcts
			<<" reward:"<<it->second.city.reward<<","<<it->second.city.nextReward
			<<endl;
	}
	return 0;
}
int CDataNewWorldBattle::Fix()
{
	checkTick();

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	_fix(pdata, now);

	return 0;
}
void CDataNewWorldBattle::_fix(DataNewWorldBattle *pdata, unsigned ts)
{
	pdata->changets = ts;
	unsigned j=0;
	for(j=0;j<NEW_WORLD_BATTLE_CITY;++j)
	{
		pdata->city[j].ts = ts;
		memset(pdata->city[j].count,0,sizeof(pdata->city[j].count));
		pdata->city[j].countV = 0;
		for(unsigned count=0;count<NEW_WORLD_BATTLE_CITY_VISION;++count)
		{
			if(pdata->city[j].vision[count].index.uid)
			{
				++pdata->city[j].countV;
				if(pdata->city[j].vision[count].kingdom)
					++pdata->city[j].count[pdata->city[j].vision[count].kingdom-1];
				if(pdata->city[j].kingdom == pdata->city[j].vision[count].kingdom)
					pdata->city[j].vision[count].status = NewWorldBattleHeroStatus_wait_defence;
				else
					pdata->city[j].vision[count].status = NewWorldBattleHeroStatus_wait_attack;
			}
		}
		if(pdata->city[j].countN > NEW_WORLD_BATTLE_CITY_NPC)
			pdata->city[j].countN = 0;
	}
	for(j=0;j<pdata->count;++j)
	{
		if(!pdata->hero[j].kingdom)
			pdata->hero[j].kingdom = 1;
		if(!pdata->hero[j].cid || pdata->hero[j].cid > NEW_WORLD_BATTLE_CITY_KINGDOM_SEQ*4)
			pdata->hero[j].cid = getCapital(pdata->hero[j].kingdom);

		if(pdata->hero[j].kingdom)
			++pdata->city[m_citymap[pdata->hero[j].cid].city.seq].count[pdata->hero[j].kingdom-1];
		if(pdata->hero[j].kingdom == pdata->city[m_citymap[pdata->hero[j].cid].city.seq].kingdom)
			pdata->hero[j].status = NewWorldBattleHeroStatus_wait_defence;
		else
			pdata->hero[j].status = NewWorldBattleHeroStatus_wait_attack;
	}
	system("killall -12 CgiNewWorldBattle");
	exit(0);
}
int CDataNewWorldBattle::Reset()
{
	checkTick();

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	pdata->changets = now;
	unsigned j=0;
	for(j=0;j<NEW_WORLD_BATTLE_CITY;++j)
	{
		pdata->city[j].ts = now;
		for(unsigned count=0;count<NEW_WORLD_BATTLE_CITY_VISION_NPC;++count)
		{
			if(pdata->city[j].vision[count].index.uid)
			{
				pdata->city[j].vision[count].hp = 1;
				for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
					pdata->city[j].vision[count].property[i] = 1;
			}
		}
	}
	for(j=0;j<pdata->count;++j)
	{
		pdata->hero[j].ts = now;
		pdata->hero[j].hp = 1;
		for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
			pdata->hero[j].property[i] = 1;
	}
	return 0;
}
int CDataNewWorldBattle::Back()
{
	checkTick();

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	pdata->changets = now;
	unsigned j=0;
	for(j=0;j<NEW_WORLD_BATTLE_CITY;++j)
	{
		pdata->city[j].ts = now;
		memset(pdata->city[j].vision, 0, sizeof(pdata->city[j].vision));
		memset(pdata->city[j].count,0,sizeof(pdata->city[j].count));
		pdata->city[j].countN = pdata->city[j].countV = 0;
		pdata->city[j].npcts += 3600;
	}
	for(j=0;j<pdata->count;++j)
	{
		pdata->hero[j].ts = now;
		pdata->hero[j].cid = getCapital(pdata->hero[j].kingdom);
	}
	return 0;
}
int CDataNewWorldBattle::Test(NewWorldBattleHero &attacker, unsigned hpa, NewWorldBattleHero &defender, unsigned hpd)
{
	checkTick();
	if(!m_heromap.count(attacker.index) || !m_heromap.count(defender.index))
		return R_ERR_PARAM;
	attacker = m_heromap[attacker.index];
	defender = m_heromap[defender.index];
	attacker.hp = (double)attacker.property[NewWorldBattleProperty_hp]*(double)hpa/double(100);
	defender.hp = (double)defender.property[NewWorldBattleProperty_hp]*(double)hpd/double(100);
	attacker.kill = defender.kill = 0;
	int ak, dk;
	attacking(attacker,defender,ak,dk);
	addKill(attacker, defender, ak, dk, 0, NULL);
	addKill(defender, attacker, dk, ak, 0, NULL);
	return 0;
}
int CDataNewWorldBattle::Time()
{
	unsigned now = Time::GetGlobalTime();

	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(Config::GetPath(CONFIG_NEW_WORLD_BATTLE_DATA).c_str(), sizeof(DataNewWorldBattle), SEM_ID(sem_new_world_battle,semgroup,semserver)))
	{
		cout<<"shm fail"<<endl;
		return R_ERR_DB;
	}

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		cout<<"address fail"<<endl;
		return R_ERR_DB;
	}

	CAutoLock lock(&m_sh, true);

	if(pdata->ts > now)
		pdata->ts = now;
	pdata->changets = now;
	unsigned j=0;
	for(j=0;j<NEW_WORLD_BATTLE_CITY;++j)
	{
		if(pdata->city[j].ts > now)
			pdata->city[j].ts = now;
		if(pdata->city[j].npcts > now)
			pdata->city[j].npcts = now;
		for(unsigned count=0;count<NEW_WORLD_BATTLE_CITY_VISION_NPC;++count)
		{
			if(pdata->city[j].vision[count].ts > now)
				pdata->city[j].vision[count].ts = now;
			if(pdata->city[j].vision[count].next > now)
				pdata->city[j].vision[count].next = now;
		}
	}
	for(j=0;j<pdata->count;++j)
	{
		if(pdata->hero[j].ts > now)
			pdata->hero[j].ts = now;
		if(pdata->hero[j].next > now)
			pdata->hero[j].next = now;
	}

	return 0;
}

int CDataNewWorldBattle::GetMoveR1(unsigned level)
{
	if(level > NEW_WORLD_BATTLE_MOVE_LEVEL || !level)
		return 100000000;
	return CDataNewWorld::move_r1[level - 1];
}

unsigned CDataNewWorldBattle::GetKillExp(unsigned kill, unsigned level)
{
	if(!kill)
		return 0;
	if(level < NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MIN || level > NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MAX)
		return 0;

	level -= NEW_WORLD_BATTLE_KILL_REWARD_LEVEL_MIN;
	unsigned exp = 0;
	if(kill <= CDataNewWorld::kill_reward_kill[level][0])
		exp += (double)kill * (double)CDataNewWorld::kill_reward_p[level][0] / double(10000);
	else
	{
		exp += CDataNewWorld::kill_reward_kill[level][0] * (double)CDataNewWorld::kill_reward_p[level][0] / double(10000);
		if(kill <= CDataNewWorld::kill_reward_kill[level][1])
			exp += (double)(kill - CDataNewWorld::kill_reward_kill[level][0]) * (double)CDataNewWorld::kill_reward_p[level][1] / double(10000);
		else
		{
			exp += (double)(CDataNewWorld::kill_reward_kill[level][1] - CDataNewWorld::kill_reward_kill[level][0]) * (double)CDataNewWorld::kill_reward_p[level][1] / double(10000);
			if(kill <= CDataNewWorld::kill_reward_kill[level][2])
				exp += (double)(kill - CDataNewWorld::kill_reward_kill[level][1]) * (double)CDataNewWorld::kill_reward_p[level][2] / double(10000);
			else
			{
				exp += (double)(CDataNewWorld::kill_reward_kill[level][2] - CDataNewWorld::kill_reward_kill[level][1]) * (double)CDataNewWorld::kill_reward_p[level][2] / double(10000);
				exp += (double)(kill - CDataNewWorld::kill_reward_kill[level][2]) * (double)CDataNewWorld::kill_reward_p[level][3] / double(10000);
			}
		}
	}
	return exp;
}
unsigned CDataNewWorldBattle::GetKillRewardNew(unsigned rank)
{
	if(rank == 1)
		return 180;
	else if(rank <= 3)
		return 150;
	else if(rank <= 10)
		return 100;
	else if(rank <= 30)
		return 80;
	else if(rank <= 50)
		return 50;
	else if(rank <= 100)
		return 20;
	else
		return 0;
}
unsigned CDataNewWorldBattle::GetKillRewardP(unsigned kill)
{
	unsigned sum = 0;

	if(kill > 100)
		sum += 10;
	else
		return sum;

	if(kill > 160)
		sum += 10;
	else
		return sum;

	if(kill > 320)
		sum += 10;
	else
		return sum;

	if(kill > 800)
		sum += 10;
	else
		return sum;

	if(kill > 1500)
		sum += 10;

	return sum;
}
void CDataNewWorldBattle::GetKillRewardResult(unsigned kingdom[4], unsigned &result)
{
	unsigned cid = getCapital(4);
	if(m_citymap[cid].city.damage >= NEW_WORLD_BATTLE_DAMAGE_MAX)
	{
		result = e_NewWorldBattleResult_defend_win;
		kingdom[0] = kingdom[1] = kingdom[2] = 3;
		kingdom[3] = 1;
	}
	else
	{
		bool over = true;
		for(int i=1;i<=3;++i)
		{
			cid = getCapital(i);
			if(m_citymap[cid].city.damage < NEW_WORLD_BATTLE_DAMAGE_MAX)
			{
				over = false;
				break;
			}
		}
		if(over)
		{
			result = e_NewWorldBattleResult_attack_win;
			kingdom[0] = kingdom[1] = kingdom[2] = 1;
			kingdom[3] = 2;
		}
		else
		{
			result = e_NewWorldBattleResult_time_over;
			kingdom[0] = kingdom[1] = kingdom[2] = 2;
			kingdom[3] = 1;
		}
	}
}

int CDataNewWorldBattle::CheckOver()
{
	unsigned cid = getCapital(4);
	if(m_citymap[cid].city.damage >= NEW_WORLD_BATTLE_DAMAGE_MAX)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_over");
	}
	bool over = true;
	for(int i=1;i<=3;++i)
	{
		cid = getCapital(i);
		if(m_citymap[cid].city.damage < NEW_WORLD_BATTLE_DAMAGE_MAX)
		{
			over = false;
			break;
		}
	}
	if(over)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_over");
	}
	return 0;
}

int CDataNewWorldBattle::Restart()
{
	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	memset(pdata, 0, sizeof(*pdata));

	unsigned now = Time::GetGlobalTime();
	for(unsigned k=0;k<=3;++k)
	{
		unsigned i = k ? (NEW_WORLD_BATTLE_CITY_KINGDOM * (k - 1) + NEW_WORLD_BATTLE_CITY_NEUTRAL) : 0;
		unsigned n = NEW_WORLD_BATTLE_CITY_KINGDOM * k + NEW_WORLD_BATTLE_CITY_NEUTRAL;
		unsigned j = NEW_WORLD_BATTLE_CITY_KINGDOM_SEQ * k + NEW_WORLD_BATTLE_CITY_CAPITAL;
		for(;i<n;++i,++j)
		{
			pdata->city[i].seq = i;
			pdata->city[i].cid = j;
			pdata->city[i].kingdom = k?k:4;
			pdata->city[i].countN = NEW_WORLD_BATTLE_CITY_NPC;
			pdata->city[i].npcts = now;
			pdata->city[i].ts = now;
		}
	}
	pdata->changets = now;
	pdata->ts = now;

	return 0;
}

int CDataNewWorldBattle::Double(unsigned uid, unsigned kingdom, unsigned cid)
{
	checkTick();

	int ret = CheckOver();
	if(ret)
		return ret;

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	if(kingdom > 4 || kingdom < 1)
		return R_ERR_PARAM;

	if(!m_citymap.count(cid))
	{
		return R_ERR_DB;
	}

	unsigned index = 0;
	NewWorldBattleHeroIndex nindex;
	for (index = 0; index < NEW_WORLD_BATTLE_HERO_INDEX; ++index)
	{
		nindex = NewWorldBattleHeroIndex(uid, index);
		if (m_heromap.count(nindex))
		{
			break;
		}
	}

	if (NEW_WORLD_BATTLE_HERO_INDEX == index)
	{
		return R_ERR_DB;
	}

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	pdata->changets = now;

	unsigned cityseq = m_citymap[cid].city.seq;
	unsigned heroseq = m_heromap[nindex].seq;
	NewWorldBattleHero &hero = pdata->hero[heroseq];

	// 双倍杀敌时间叠加  modify by Cream
	if (pdata->city[cityseq].extraKillTS[kingdom - 1] < now)
	{
		pdata->city[cityseq].extraKillTS[kingdom - 1] = now + NEW_WORLD_BATTLE_DOUBLE_TIME;
	}
	else
	{
		pdata->city[cityseq].extraKillTS[kingdom - 1] += NEW_WORLD_BATTLE_DOUBLE_TIME;
	}

	pdata->city[cityseq].ts = now;

	// 增加功勋
	addKill(hero, NEW_WORLD_BATTLE_DOUBLE_KILL, now, pdata);
	hero.ts = now;

	return 0;
}

int CDataNewWorldBattle::CollectOther(unsigned uid, unsigned cid)
{
	int ret = 0;

	checkTick();

	ret = CheckOver();
	if (ret)
	{
		return ret;
	}

	if(!m_citymap.count(cid))
	{
		return R_ERR_DB;
	}

	unsigned index = 0;
	NewWorldBattleHeroIndex nindex;
	for (index = 0; index < NEW_WORLD_BATTLE_HERO_INDEX; ++index)
	{
		nindex = NewWorldBattleHeroIndex(uid, index);
		if (m_heromap.count(nindex))
		{
			break;
		}
	}

	if (NEW_WORLD_BATTLE_HERO_INDEX == index)
	{
		return R_ERR_DB;
	}


	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
	{
		++now;
	}

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh), true);

	unsigned heroseq = m_heromap[nindex].seq;
	NewWorldBattleHero &hero = pdata->hero[heroseq];

	pdata->changets = now;
	hero.ts = now;

	// 给一个武将增加功勋
	addKill(hero, NEW_WORLD_BATTLE_COLLECTOTHER_KILL, now, pdata);

	return 0;
}

int CDataNewWorldBattle::Buildyjt(NewWorldBattleHeroIndex index)
{
	checkTick();

	if(!m_heromap.count(index))
		return R_ERR_DB;
	if(!m_citymap.count(m_heromap[index].cid))
		return R_ERR_DB;

	if(m_citymap[m_heromap[index].cid].city.tower.uid)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_jyt_full");
	}
	if(m_citymap[m_heromap[index].cid].city.kingdom != m_heromap[index].kingdom)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_jyt_kingdom");
	}

	unsigned now = Time::GetGlobalTime();
	if(now == m_ts)
		++now;

	DataNewWorldBattle *pdata = (DataNewWorldBattle *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&(m_sh), true);

	if(isCapital(pdata->hero[m_heromap[index].seq].cid) || pdata->hero[m_heromap[index].seq].cid != m_heromap[index].cid)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_hero_die");
	}

	unsigned seq = m_citymap[m_heromap[index].cid].city.seq;
	if(pdata->city[seq].tower.uid)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_jyt_full");
	}
	if(pdata->city[seq].kingdom != pdata->hero[m_heromap[index].seq].kingdom)
	{
		LOGIC_ERROR_RETURN_MSG("newworldbattle_jyt_kingdom");
	}

	pdata->city[seq].tower.uid = index.uid;
	pdata->city[seq].tower.dps = 100;
	pdata->city[seq].tower.hit = 100;

	pdata->city[seq].ts = now;
	pdata->changets = now;

	addKill(pdata->hero[m_heromap[index].seq], 10, now, pdata);

	return 0;
}
