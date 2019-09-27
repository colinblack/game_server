/*
 * DataNewWorldAllianceRoom.cpp
 *
 *  Created on: 2014-9-17
 *      Author: Ralf
 */

#include "DataNewWorldAllianceRoom.h"
#include "LogicAlliance.cpp"
#include <fstream>
#include <iostream>

NewWorldAllianceRoomRoadMap CDataNewWorldAllianceRoom::m_roadmap;

CDataNewWorldAllianceRoom::CDataNewWorldAllianceRoom(string path)
	: DataBase(path)
{
	m_msg = new NewWorldAllianceRoom::NewWorldAllianceRoom();
	vector<string> rlt;
	String::Split(path, '.', rlt);
	m_index = CTrans::STOI(*rlt.rbegin());
}

CDataNewWorldAllianceRoom::~CDataNewWorldAllianceRoom()
{}

int CDataNewWorldAllianceRoom::Init()
{
	if(m_roadmap.empty())
	{
		for(unsigned i=0;i<NEW_WORLD_ALLIANCE_ROOM_ROAD;++i)
		{
			m_roadmap[CDataNewWorld::road_map[i][0]].push_back(CDataNewWorld::road_map[i][1]);
			m_roadmap[CDataNewWorld::road_map[i][1]].push_back(CDataNewWorld::road_map[i][0]);
		}
	}

	int ret = Parse();
	if(ret)
		return ret;

	m_data.Parse(*(NewWorldAllianceRoom::NewWorldAllianceRoom *)m_msg);

	((NewWorldAllianceRoom::NewWorldAllianceRoom *)m_msg)->Clear();

	m_data.sync();

	return 0;
}
int CDataNewWorldAllianceRoom::Save()
{
	m_data.Serialize((NewWorldAllianceRoom::NewWorldAllianceRoom *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	//File::Write("/data/release/sgonline/debug", m_msg->DebugString());

	((NewWorldAllianceRoom::NewWorldAllianceRoom *)m_msg)->Clear();

	return 0;
}
void CDataNewWorldAllianceRoom::Restart()
{
	m_data.room.clear();
	unsigned now = Time::GetGlobalTime();
	CDataNewWorldAllianceMap gvgmap(MainConfig::GetAllServerPath(CONFIG_NEW_WORLD_ALLIANCE_MAP_DATA));
	if(gvgmap.Init() == 0)
	{
		const map<unsigned int, DataNewWorldAllianceMapAlliance>& gvg = gvgmap.GetAll();
		for(map<unsigned int, DataNewWorldAllianceMapAlliance>::const_iterator it=gvg.begin();it!=gvg.end();++it)
		{
			if(it->first % NEW_WORLD_ALLIANCE_MAP_ROOM_BALANCE == m_index)
			{
				unsigned rid = it->first;
				m_data.room[rid].rid = rid;
				m_data.room[rid].reward = it->second.reward;
				m_data.room[rid].level = it->second.level;
				m_data.room[rid].ts = now;
				for(unsigned i=0;i<NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE;++i)
					m_data.room[rid].aid.push_back(0);
				for(vector<unsigned int>::const_iterator iter=it->second.aid.begin();iter!=it->second.aid.end();++iter)
				{
					unsigned aid = *iter;
					if(!m_data.room[rid].aidmap.count(aid))
					{
						if(m_data.room[rid].aidmap.size() >= NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE)
							continue;

						unsigned seq = m_data.room[rid].aidmap.size();
						m_data.room[rid].aid[seq] = aid;
						m_data.room[rid].aidmap[aid] = seq;
					}
				}
				for(unsigned i=NEW_WORLD_ALLIANCE_ROOM_CITY_CAPITAL;i<=NEW_WORLD_ALLIANCE_ROOM_CITY_NEUTRAL;++i)
				{
					m_data.room[rid].city[i].cid = i;
					m_data.room[rid].city[i].aid = 0;
				}
				for(unsigned k=0;k<NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE;++k)
				{
					for(unsigned i=(k+1)*NEW_WORLD_ALLIANCE_ROOM_CITY_AID_SEQ+NEW_WORLD_ALLIANCE_ROOM_CITY_CAPITAL;i<=(k+1)*NEW_WORLD_ALLIANCE_ROOM_CITY_AID_SEQ+NEW_WORLD_ALLIANCE_ROOM_CITY_AID;++i)
					{
						m_data.room[rid].city[i].cid = i;
						m_data.room[rid].city[i].aid = m_data.room[rid].aid[k];
					}
				}
				for(NewWorldAllianceRoomCityMap::iterator it1=m_data.room[rid].city.begin();it1!=m_data.room[rid].city.end();++it1)
				{
					memset(it1->second.count, 0, sizeof(it1->second.count));
					it1->second.countN = NEW_WORLD_ALLIANCE_ROOM_CITY_NPC;
					it1->second.npcts = now;
					makeNPC(it1->second.npc[DataNewWorldAllianceRoomHeroIndex(ADMIN_UID,0)], m_data.room[rid].level);
				}
			}
		}
	}
	Save();
}
void CDataNewWorldAllianceRoom::Reward()
{
	CLogicAlliance logicAlliance;
	for(NewWorldAllianceRoomMap::iterator it=m_data.room.begin();it!=m_data.room.end();++it)
	{
		checkTick(it->first);
		map<unsigned, pair<unsigned, unsigned> > c;
		for(vector<unsigned int>::iterator iter=it->second.aid.begin();iter!=it->second.aid.end();++iter)
		{
			if(*iter)
				c[*iter] = pair<unsigned, unsigned>(0,0);
		}
		if(c.empty())
			continue;
		for(NewWorldAllianceRoomCityMap::iterator iter=it->second.city.begin();iter!=it->second.city.end();++iter)
		{
			if(c.count(iter->second.aid))
				c[iter->second.aid].first += 1;
		}
		for(NewWorldAllianceRoomHeroMap::iterator iter=it->second.hero.begin();iter!=it->second.hero.end();++iter)
		{
			if(c.count(iter->second.aid))
				c[iter->second.aid].second += iter->second.kill;
			if(it->second.kill[iter->second.aid].count(iter->second.index.uid))
				it->second.kill[iter->second.aid][iter->second.index.uid] += iter->second.kill;
			else
				it->second.kill[iter->second.aid][iter->second.index.uid] = iter->second.kill;
		}
		for(map<unsigned, pair<unsigned, unsigned> >::iterator iter=c.begin();iter!=c.end();++iter)
			it->second.result.push_back(pair<pair<unsigned, unsigned>, unsigned>(iter->second,iter->first));
		sort(it->second.result.begin(), it->second.result.end());
		const unsigned NEW_WORLD_ALLIANCE_MAP_REWARD[NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE][NEW_WORLD_ALLIANCE_MAP_REWARD_NUM + 1] = {
				{60,50,44,36,28,20,20},
				{48,39,32,25,19,12,12},
				{37,28,20,15,10,5,5}
		};
		unsigned k = 0;
		for(NewWorldAllianceRoomResult::reverse_iterator it1=it->second.result.rbegin();it1!=it->second.result.rend();++it1)
		{
			if(it1->second && it1->first.second)
				logicAlliance.ChangeResource(it1->second, 0, 0, 0, 0, NEW_WORLD_ALLIANCE_MAP_REWARD[k][it->second.reward], 0, "NewWorldAlliance");
			++k;
		}
	}
	Save();
}

void CDataNewWorldAllianceRoom::ShowCity(void){
	string file_path = MainConfig::GetAllServerPath("datalog/alliance_city.log");
	if (file_path.empty()){
		return;
	}
	ofstream out_log(file_path.c_str(), ios::app);
	if (!out_log.good()){
		return;
	}
	out_log << "================" << getpid() << "===========" << endl;
	NewWorldAllianceRoomMap::const_iterator it = m_data.room.begin();
	for(; it!=m_data.room.end(); ++it) {
		out_log << "rid=" << it->second.rid << endl;
		NewWorldAllianceRoomCityMap::const_iterator itr = it->second.city.begin();
		for(; itr!=it->second.city.end(); ++itr) {
			out_log << "cid=" << itr->second.cid
				<< ",aid=" << itr->second.aid
				<< ",countN=" << itr->second.countN
				<< ",count1=" << itr->second.count[0]
				<< ",count2=" << itr->second.count[1]
				<< ",count3=" << itr->second.count[2] << endl;
			out_log << " version:" << endl;
			NewWorldAllianceRoomHeroMap::const_iterator v_itr = itr->second.vision.begin();
			for(; v_itr!=itr->second.vision.end(); ++v_itr) {
				out_log << "  uid=" << v_itr->first.uid
					<< ",index=" << v_itr->first.index
					<< ",hid=" << v_itr->second.hid
					<< ",hp=" << v_itr->second.hp
					<< ",p=[";
				for (unsigned i=0; i<NewWorldAllianceRoomProperty_max; ++i){
					out_log << v_itr->second.property[i] << ",";
				}
				out_log << "],name=" << string(v_itr->second.name) << endl;
			}
			out_log << " attacker:" << endl;
			NewWorldAllianceCityQueue::const_iterator a_itr = itr->second.attacker.begin();
			for (; a_itr!=itr->second.attacker.end(); ++a_itr) {
				out_log << "  mts=" << a_itr->first
					<< ",uid=" << a_itr->second.uid
					<< ",index=" << a_itr->second.index << endl;
			}

			out_log << " defender:" << endl;
			NewWorldAllianceCityQueue::const_iterator d_itr = itr->second.defender.begin();
			for (; d_itr!=itr->second.defender.end(); ++d_itr) {
				out_log << "  mts=" << d_itr->first
					<< ",uid=" << d_itr->second.uid
					<< ",index=" << d_itr->second.index << endl;
			}
			out_log << " npc:" << endl;
			NewWorldAllianceRoomHeroMap::const_iterator n_itr = itr->second.npc.begin();
			for (; n_itr!=itr->second.npc.end(); ++n_itr) {
				out_log << "  uid=" << n_itr->first.uid
						<< ",index=" << n_itr->first.index
						<< ",c_hp=" << n_itr->second.hp
						<< ",m_hp=" << n_itr->second.property[0] << endl;
			}
		}
	}
}

int CDataNewWorldAllianceRoom::Sig(int sig)
{
	if(sig == SIGRTMIN)
		Restart();
	else if(sig == SIGRTMIN + 1)
		Reward();

	else if(sig == SIGRTMIN + 3)
		ShowCity();
	return 0;
}

int CDataNewWorldAllianceRoom::GetKill(unsigned rid, NewWorldAllianceRoomKill* &p)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;

	p = &m_data.room[rid].kill;
	return 0;
}
int CDataNewWorldAllianceRoom::GetResult(unsigned rid, NewWorldAllianceRoomResult* &p)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;

	p = &m_data.room[rid].result;
	return 0;
}
int CDataNewWorldAllianceRoom::GetAID(unsigned rid, vector<unsigned int>* &p)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;

	p = &m_data.room[rid].aid;
	return 0;
}
int CDataNewWorldAllianceRoom::GetWorld(unsigned rid,NewWorldAllianceRoomCityMap* &p)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	checkTick(rid);

	p = &m_data.room[rid].city;
	return 0;
}

int CDataNewWorldAllianceRoom::GetCity(unsigned rid, unsigned cid, DataNewWorldAllianceRoomCity* &p)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].city.count(cid))
		return R_ERR_PARAM;
	checkTick(rid);

	p = &m_data.room[rid].city[cid];
	return 0;
}
int CDataNewWorldAllianceRoom::GetAllHero(unsigned rid, NewWorldAllianceRoomHeroMap* &p)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	checkTick(rid);

	p = &m_data.room[rid].hero;
	return 0;
}
int CDataNewWorldAllianceRoom::GetHero(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, DataNewWorldAllianceRoomHero* &p)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	checkTick(rid);

	p = &m_data.room[rid].hero[index];
	return 0;
}

int CDataNewWorldAllianceRoom::SetHero(unsigned rid, DataNewWorldAllianceRoomHero &hero, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!isHero(hero.index))
		return R_ERR_PARAM;
	if(!m_data.room[rid].aidmap.count(hero.aid))
		return R_ERR_PARAM;
	checkTick(rid);

	if(m_data.room[rid].hero.count(hero.index))
	{
		if(m_data.room[rid].hero[hero.index].seq != seq)
			return R_ERR_DATA_LIMIT;
		m_data.room[rid].hero[hero.index].copy(hero);
		hero = m_data.room[rid].hero[hero.index];
	}
	else
	{
		hero.hp = hero.property[NewWorldAllianceRoomProperty_hp];
		hero.cid = getCapital(m_data.room[rid].aidmap[hero.aid]);
		hero.seq = hero.index.uid%100 + hero.index.index + 1;
		m_data.room[rid].hero[hero.index] = hero;
		if(!isCapital(hero.cid))
			++m_data.room[rid].city[hero.cid].count[m_data.room[rid].aidmap[hero.aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
	}

	++m_data.room[rid].hero[hero.index].seq;
	seq = m_data.room[rid].hero[hero.index].seq;

	return 0;
}
int CDataNewWorldAllianceRoom::Move(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned cid, bool leave, unsigned fly, unsigned &mts, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(!m_data.room[rid].city.count(cid))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	checkTick(rid);

	if(fly == 2)
	{
		if(m_data.room[rid].hero[index].aid != m_data.room[rid].city[cid].aid)
		{
			bool f = true;
			if(m_roadmap.count(cid))
			{
				for(vector<unsigned>::const_iterator it=m_roadmap[cid].begin();it!=m_roadmap[cid].end();++it)
				{
					if(m_data.room[rid].city[*it].aid == m_data.room[rid].hero[index].aid)
					{
						f = false;
						break;
					}
				}
			}
			if(f)
			{
				mts = m_data.room[rid].hero[index].mts;
				LOGIC_ERROR_RETURN_MSG("newworld_city_can_not_move");
			}
		}
	}
	else if(fly == 1)
	{
		if(m_data.room[rid].hero[index].aid != m_data.room[rid].city[cid].aid && !m_data.room[rid].city[cid].Fighting())
		{
			mts = m_data.room[rid].hero[index].mts;
			LOGIC_ERROR_RETURN_MSG("newworld_city_can_not_move");
		}
	}
	else if(!hasRoad(m_data.room[rid].hero[index].cid, cid))
	{
		mts = m_data.room[rid].hero[index].mts;
		LOGIC_ERROR_RETURN_MSG("newworld_city_can_not_move");
	}
	if(m_data.room[rid].hero[index].aid != m_data.room[rid].city[cid].aid && isCapital(cid))
	{
		mts = m_data.room[rid].hero[index].mts;
		LOGIC_ERROR_RETURN_MSG("newworld_city_can_not_move");
	}
	if(!isValid(rid, index))
	{
		mts = m_data.room[rid].hero[index].mts;
		LOGIC_ERROR_RETURN_MSG("newworld_hero_can_not_move");
	}
	if((((m_data.room[rid].city[m_data.room[rid].hero[index].cid].aid == m_data.room[rid].hero[index].aid
	&& m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.size())
	|| (m_data.room[rid].city[m_data.room[rid].hero[index].cid].aid != m_data.room[rid].hero[index].aid)) && !leave))
	{
		mts = m_data.room[rid].hero[index].mts;
		LOGIC_ERROR_RETURN_MSG("newworld_hero_can_not_move");
	}
	const static unsigned int precent = 5;
	if (m_data.room[rid].hero[index].hp < (m_data.room[rid].hero[index].property[NewWorldAllianceRoomProperty_hp] * precent / 100))
	{
		mts = m_data.room[rid].hero[index].mts;
		LOGIC_ERROR_RETURN_MSG("newworld_hero_hp_low_percent_5");
	}

	queue(rid, index, cid);
	mts = m_data.room[rid].hero[index].mts = m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK*2;
	m_data.room[rid].hero[index].cid = cid;

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
int CDataNewWorldAllianceRoom::Change(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned type, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	checkTick(rid);

	m_data.room[rid].hero[index].type = type;

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
int CDataNewWorldAllianceRoom::Clone(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	if(isCapital(m_data.room[rid].hero[index].cid))
		return R_ERR_LOGIC;
	checkTick(rid);

	DataNewWorldAllianceRoomHeroIndex vi = DataNewWorldAllianceRoomHeroIndex(0,0);
	if(!m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision.empty())
		vi.uid = m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision.rbegin()->first.uid + 1;
	vi.index = index.uid;

	m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision[vi] = m_data.room[rid].hero[index];
	m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision[vi].index = vi;
	m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision[vi].hp = m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision[vi].property[NewWorldAllianceRoomProperty_hp];
	m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision[vi].buff = 0;
	m_data.room[rid].city[m_data.room[rid].hero[index].cid].vision[vi].mts = Time::GetGlobalTime();

	++m_data.room[rid].city[m_data.room[rid].hero[index].cid].count[m_data.room[rid].aidmap[m_data.room[rid].hero[index].aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
	if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].aid != m_data.room[rid].hero[index].aid)
		m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(Time::GetGlobalTime(), vi));
	else
		m_data.room[rid].city[m_data.room[rid].hero[index].cid].defender.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(Time::GetGlobalTime(), vi));

	addKill(rid, m_data.room[rid].hero[index], NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_CLONE);

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
int CDataNewWorldAllianceRoom::Recover(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned num, unsigned &seq)
{
	if(!num)
		return 0;

	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	checkTick(rid);

	if(!notFront(rid, index))
	{
		LOGIC_ERROR_RETURN_MSG("newworld_fighting_can_not_recover");
	}
	if(m_data.room[rid].hero[index].hp >= m_data.room[rid].hero[index].property[NewWorldAllianceRoomProperty_hp])
	{
		LOGIC_ERROR_RETURN_MSG("newworld_full_can_not_recover");
	}

	m_data.room[rid].hero[index].hp += num * NEW_WORLD_ALLIANCE_ROOM_HERO_RECOVER;
	if(m_data.room[rid].hero[index].hp > m_data.room[rid].hero[index].property[NewWorldAllianceRoomProperty_hp])
		m_data.room[rid].hero[index].hp = m_data.room[rid].hero[index].property[NewWorldAllianceRoomProperty_hp];

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
int CDataNewWorldAllianceRoom::Explode(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	checkTick(rid);

	if(!notFront(rid, index))
	{
		LOGIC_ERROR_RETURN_MSG("newworld_fighting_can_not_explode");
	}

	m_data.room[rid].hero[index].addBuff(NewWorldHeroBuff_explode);

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
int CDataNewWorldAllianceRoom::CollectOther(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	checkTick(rid);

	addKill(rid, m_data.room[rid].hero[index], NEW_WORLD_ALLIANCE_ROOM_COLLECTOTHER_KILL);

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
int CDataNewWorldAllianceRoom::Rush(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, DataNewWorldAllianceRoomHero &other, DataNewWorldAllianceRoomHero &end, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	checkTick(rid);

	unsigned r = 0;
	unsigned cid = m_data.room[rid].hero[index].cid;
	bool rush_att = m_data.room[rid].hero[index].aid != m_data.room[rid].city[cid].aid;
	if(!isValid(rid, index))
	{
		LOGIC_ERROR_RETURN_MSG("newworld_fighting_can_not_rush");
	}
	if(!rush_att
	&& (m_data.room[rid].city[cid].attacker.size() <= NEW_WORLD_ALLIANCE_ROOM_RUSH_MIN
	|| m_data.room[rid].city[cid].defender.size() <= NEW_WORLD_ALLIANCE_ROOM_RUSH_MIN))
	{
		LOGIC_ERROR_RETURN_MSG("newworld_rush_min");
	}
	if(rush_att
	&& (m_data.room[rid].city[cid].attacker.size() <= NEW_WORLD_ALLIANCE_ROOM_RUSH_MIN
	|| m_data.room[rid].city[cid].defender.size() + m_data.room[rid].city[cid].countN  <= NEW_WORLD_ALLIANCE_ROOM_RUSH_MIN))
	{
		LOGIC_ERROR_RETURN_MSG("newworld_rush_min");
	}

	DataNewWorldAllianceRoomHero npc;
	NewWorldAllianceCityQueue &queue = rush_att ? m_data.room[rid].city[cid].defender : m_data.room[rid].city[cid].attacker;
	NewWorldAllianceCityQueue::iterator it=queue.begin();
	for(;it!=queue.end();++it)
	{
		++r;
		if(r <= NEW_WORLD_ALLIANCE_ROOM_RUSH_MIN)
			continue;
		if(isHero(it->second))
		{
			if(!notMoving(rid, it->second))
				continue;
		}
		break;
	}
	if(it == queue.end())
	{
		if(rush_att && m_data.room[rid].city[cid].countN > 0)
			makeNPC(npc, m_data.room[rid].level);
		else
		{
			LOGIC_ERROR_RETURN_MSG("newworld_rush_min");
		}
	}

	DataNewWorldAllianceRoomHero &attacker = rush_att ? m_data.room[rid].hero[index] : (it == queue.end() ? npc : (isHero(it->second)?m_data.room[rid].hero[it->second] : m_data.room[rid].city[cid].vision[it->second]));
	DataNewWorldAllianceRoomHero &defender = rush_att ? (it == queue.end() ? npc : (isHero(it->second)?m_data.room[rid].hero[it->second] : m_data.room[rid].city[cid].vision[it->second])) : m_data.room[rid].hero[index];
	other = rush_att ? defender : attacker;

	unsigned result = NewWorldAllianceRoomHeroAttackResult_none;

	int ak, dk;
	result = attacking(rid, attacker,defender,ak,dk);
	addKill(rid, attacker, defender, ak, dk);
	addKill(rid, defender, attacker, dk, ak);

	if(result == NewWorldAllianceRoomHeroAttackResult_attacker_win)
		end = attacker;
	else if(result == NewWorldAllianceRoomHeroAttackResult_defender_win)
		end = defender;

	for(int r=0;r<2;++r)
	{
		if((r && result == NewWorldAllianceRoomHeroAttackResult_attacker_win)
		|| (!r && result == NewWorldAllianceRoomHeroAttackResult_defender_win))
			continue;

		DataNewWorldAllianceRoomHero &loser = r?attacker:defender;
		if(isHero(loser.index))
		{
			--m_data.room[rid].city[cid].count[m_data.room[rid].aidmap[loser.aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
			if(m_data.room[rid].city[cid].aid != loser.aid)
				m_data.room[rid].city[cid].attacker.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));
			else
				m_data.room[rid].city[cid].defender.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));

			loser.cid = getCapital(m_data.room[rid].aidmap[loser.aid]);
			loser.mts = m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK;
		}
		else if(isVision(loser.index))
		{
			--m_data.room[rid].city[cid].count[m_data.room[rid].aidmap[loser.aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
			if(m_data.room[rid].city[cid].aid != loser.aid)
				m_data.room[rid].city[cid].attacker.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));
			else
				m_data.room[rid].city[cid].defender.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));

			m_data.room[rid].city[cid].vision.erase(loser.index);
		}
		else if(isNPC(loser.index))
		{
			if(m_data.room[rid].city[cid].countN > 0)
				--m_data.room[rid].city[cid].countN;
			else
				m_data.room[rid].city[cid].countN = 0;
			if(m_data.room[rid].city[cid].countN == 0)
				makeNPC(m_data.room[rid].city[cid].npc[DataNewWorldAllianceRoomHeroIndex(ADMIN_UID,0)], m_data.room[rid].level);
		}
	}

	addKill(rid, m_data.room[rid].hero[index], NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_RUSH);

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
void DataNewWorldAllianceRoomBattle::sync()
{
	for(NewWorldAllianceRoomCityMap::iterator it=city.begin();it!=city.end();++it)
	{
		memset(it->second.count, 0, sizeof(it->second.count));
		it->second.attacker.clear();
		it->second.defender.clear();
		for(NewWorldAllianceRoomHeroMap::iterator iter=it->second.vision.begin();iter!=it->second.vision.end();++iter)
		{
			it->second.count[aidmap[iter->second.aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE] += 1;
			if(iter->second.aid == it->second.aid)
				it->second.defender.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(iter->second.mts, iter->second.index));
			else
				it->second.attacker.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(iter->second.mts, iter->second.index));
		}
	}
	for(NewWorldAllianceRoomHeroMap::iterator it=hero.begin();it!=hero.end();++it)
	{
		city[it->second.cid].count[aidmap[it->second.aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE] += 1;
		if(it->second.aid == city[it->second.cid].aid)
			city[it->second.cid].defender.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(it->second.mts, it->second.index));
		else
			city[it->second.cid].attacker.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(it->second.mts, it->second.index));
	}
}

void CDataNewWorldAllianceRoom::checkTick(unsigned rid)
{
	//check tick first for sync
	unsigned now = Time::GetGlobalTime();
	if(now < m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK)
		return;

	m_data.room[rid].battlechange.clear();
	set<unsigned> changeset;

	bool fix = false;
	//tick
	while(now >= m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK)
	{
		//city
		for(NewWorldAllianceRoomCityMap::iterator it=m_data.room[rid].city.begin();it!=m_data.room[rid].city.end();++it)
		{
			DataNewWorldAllianceRoomCity &city = it->second;

			unsigned result = NewWorldAllianceRoomHeroAttackResult_none;
		//stage 1. attack : hero:hp,cid,status; city:attacker,defender, vision:hp, count123, countN, countV
			if(!city.attacker.empty() && (!city.defender.empty() || city.countN > 0))
			{
				DataNewWorldAllianceRoomHero &attacker = isHero(city.attacker.begin()->second)?
						m_data.room[rid].hero[city.attacker.begin()->second]:
						city.vision[city.attacker.begin()->second];
				DataNewWorldAllianceRoomHero &defender = (!city.defender.empty())?(isHero(city.defender.begin()->second)?
						m_data.room[rid].hero[city.defender.begin()->second]:
						city.vision[city.defender.begin()->second]):(city.npc.begin()->second);

				int ak, dk;
				result = attacking(rid, attacker,defender,ak,dk);
				addKill(rid, attacker, defender, ak, dk);
				addKill(rid, defender, attacker, dk, ak);

				for(int r=0;r<2;++r)
				{
					if((r && result == NewWorldAllianceRoomHeroAttackResult_attacker_win)
					|| (!r && result == NewWorldAllianceRoomHeroAttackResult_defender_win))
						continue;

					DataNewWorldAllianceRoomHero &loser = r?attacker:defender;
					if(isHero(loser.index))
					{
						--city.count[m_data.room[rid].aidmap[loser.aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
						if(city.aid != loser.aid)
							city.attacker.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));
						else
							city.defender.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));

						loser.cid = getCapital(m_data.room[rid].aidmap[loser.aid]);
						loser.mts = m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK;
					}
					else if(isVision(loser.index))
					{
						--city.count[m_data.room[rid].aidmap[loser.aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
						if(city.aid != loser.aid)
							city.attacker.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));
						else
							city.defender.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(loser.mts, loser.index));

						city.vision.erase(loser.index);
					}
					else if(isNPC(loser.index))
					{
						if(city.countN > 0)
							--city.countN;
						else
							city.countN = 0;
						makeNPC(loser, m_data.room[rid].level);
					}
				}
			}
		//stage 2. choose next : hero:status, city:attacker,defender, vision:status
			if((result && city.attacker.empty()) || !city.attacker.empty())
				changeset.insert(city.cid);
		//stage 3. occupy : mission; city:attacker, defender, npcts, countN, uid, aid, name; hero:status
			if(!city.attacker.empty() && city.defender.empty() && city.countN <= 0 && !isCapital(city.cid))
			{
				//debug_log("[occupy]city=%u",m_data.room[rid].city[i].cid);
				changeset.insert(city.cid);

				if(isHero(city.attacker.begin()->second))
				{
					city.aid = m_data.room[rid].hero[city.attacker.begin()->second].aid;
					addKill(rid, m_data.room[rid].hero[city.attacker.begin()->second], NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_LAST);
				}
				else
				{
					city.aid = city.vision[city.attacker.begin()->second].aid;
					addKill(rid, city.vision[city.attacker.begin()->second], NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_LAST);
				}
				city.tower.clear();
				city.npcts = m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK;
				for(NewWorldAllianceCityQueue::iterator iter=city.attacker.begin();iter!=city.attacker.end();++iter)
				{
					if(isHero(iter->second))
					{
						if(m_data.room[rid].hero[iter->second].aid == city.aid)
						{
							addKill(rid, m_data.room[rid].hero[iter->second], NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_QUEUE);
							city.defender.insert(*iter);
						}
					}
					else
					{
						if(city.vision[iter->second].aid == city.aid)
						{
							addKill(rid, city.vision[iter->second], NEW_WORLD_ALLIANCE_ROOM_KILL_ADD_QUEUE);
							city.defender.insert(*iter);
						}
					}
				}
				for(NewWorldAllianceCityQueue::iterator iter=city.defender.begin();iter!=city.defender.end();++iter)
					city.attacker.erase(*iter);
			}

			if(city.npcts + NEW_WORLD_ALLIANCE_ROOM_CITY_NPC_TIME < m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK)
			{
				//debug_log("++npc cid=%u,time=%u,npcts=%u,ts=%u",m_data.room[rid].city[i].cid,npctime,m_data.room[rid].city[i].npcts,m_data.room[rid].ts+NEW_WORLD_ALLIANCE_ROOM_TICK);
				city.npcts = m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK;
				if(city.countN > NEW_WORLD_ALLIANCE_ROOM_CITY_NPC || city.countN < 0)
					city.countN = 0;
				else if(city.countN < NEW_WORLD_ALLIANCE_ROOM_CITY_NPC)
					++city.countN;
			}

			if(city.countN < 0 || city.count[0] < 0 || city.count[1] < 0 || city.count[2] < 0)
			{
				if(city.countN < 0)
					city.countN = 0;
				fix = true;
			}
		}
		//hero
		for(NewWorldAllianceRoomHeroMap::iterator it=m_data.room[rid].hero.begin();it!=m_data.room[rid].hero.end();++it)
		{
			DataNewWorldAllianceRoomHero &hero = it->second;
		//stage 4. move & recover : hero:status,cid,next,hp; city: count123
			if(!m_data.room[rid].city[hero.cid].Fighting())
				hero.recover();
		}

		m_data.room[rid].ts += NEW_WORLD_ALLIANCE_ROOM_TICK;
	}

	if(fix)
		m_data.room[rid].sync();

	if(!changeset.empty())
	{
		for(set<unsigned>::iterator it=changeset.begin();it!=changeset.end();++it)
		{
			m_data.room[rid].battlechange[*it].cid = *it;
			m_data.room[rid].battlechange[*it].aid = m_data.room[rid].city[*it].aid;
			m_data.room[rid].battlechange[*it].battle = m_data.room[rid].city[*it].Fighting()?1:0;
		}
	}

	return;
}
bool CDataNewWorldAllianceRoom::isValid(unsigned rid, DataNewWorldAllianceRoomHeroIndex index)
{
	return notMoving(rid, index) && notFront(rid, index);
}
bool CDataNewWorldAllianceRoom::notMoving(unsigned rid, DataNewWorldAllianceRoomHeroIndex index)
{
	if(m_data.room[rid].hero[index].mts > Time::GetGlobalTime())
		return false;

	return true;
}
bool CDataNewWorldAllianceRoom::notFront(unsigned rid, DataNewWorldAllianceRoomHeroIndex index)
{
	NewWorldAllianceCityQueue::iterator it;
	if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].aid != m_data.room[rid].hero[index].aid)
	{
		if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.size() && (it = m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.begin())->second == index)
			return false;
		else if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.size()>1 && (++it)->second == index)
			return false;
		else if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.size()>2 && (++it)->second == index)
			return false;
	}
	else
	{
		if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.empty())
			return true;
		if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].defender.size() && (it = m_data.room[rid].city[m_data.room[rid].hero[index].cid].defender.begin())->second == index)
			return false;
		else if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].defender.size()>1 && (++it)->second == index)
			return false;
		else if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].defender.size()>2 && (++it)->second == index)
			return false;
	}

	return true;
}
void CDataNewWorldAllianceRoom::queue(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned cid)
{
	if(!isCapital(m_data.room[rid].hero[index].cid))
	{
		--m_data.room[rid].city[m_data.room[rid].hero[index].cid].count[m_data.room[rid].aidmap[m_data.room[rid].hero[index].aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
		if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].aid != m_data.room[rid].hero[index].aid)
			m_data.room[rid].city[m_data.room[rid].hero[index].cid].attacker.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(m_data.room[rid].hero[index].mts, index));
		else
			m_data.room[rid].city[m_data.room[rid].hero[index].cid].defender.erase(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(m_data.room[rid].hero[index].mts, index));
	}
	if(!isCapital(cid))
	{
		++m_data.room[rid].city[cid].count[m_data.room[rid].aidmap[m_data.room[rid].hero[index].aid]%NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE];
		if(m_data.room[rid].city[cid].aid != m_data.room[rid].hero[index].aid)
			m_data.room[rid].city[cid].attacker.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK*2, index));
		else
			m_data.room[rid].city[cid].defender.insert(pair<unsigned, DataNewWorldAllianceRoomHeroIndex>(m_data.room[rid].ts + NEW_WORLD_ALLIANCE_ROOM_TICK*2, index));
	}
}

int CDataNewWorldAllianceRoom::Buildyjt(unsigned rid, DataNewWorldAllianceRoomHeroIndex index, unsigned &seq)
{
	if(!m_data.room.count(rid))
		return R_ERR_PARAM;
	if(!m_data.room[rid].hero.count(index))
		return R_ERR_PARAM;
	if(m_data.room[rid].hero[index].seq != seq)
		return R_ERR_DATA_LIMIT;
	if(isCapital(m_data.room[rid].hero[index].cid))
		return R_ERR_LOGIC;
	checkTick(rid);

	if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].tower.uid)
		return R_ERR_LOGIC;
	if(m_data.room[rid].city[m_data.room[rid].hero[index].cid].aid != m_data.room[rid].hero[index].aid)
		return R_ERR_LOGIC;

	m_data.room[rid].city[m_data.room[rid].hero[index].cid].tower.uid = index.uid;
	m_data.room[rid].city[m_data.room[rid].hero[index].cid].tower.dps = 100;
	m_data.room[rid].city[m_data.room[rid].hero[index].cid].tower.hit = 100;

	addKill(rid, m_data.room[rid].hero[index], 10);

	++m_data.room[rid].hero[index].seq;
	seq = m_data.room[rid].hero[index].seq;

	return 0;
}
