/*
 * DataBraveNewWorld.cpp
 *
 *  Created on: 2017-2-14
 *      Author: Ralf
 */

#include "DataBraveNewWorld.h"
#include "ConfigManager.h"
#include "LogicUser.h"
#include "LogicPay.h"
#include "LogicUpdates.h"
#include "LogicCmdUnits.h"
#include "LogicAlliance.h"

const unsigned CDataBraveNewWorld::m_rect[BRAVE_NEW_WORLD_LEVEL][2][2] =
{
		{{0,0},{199,199}},
		{{10,10},{189,189}},
		{{20,20},{179,179}},
		{{30,30},{169,169}},
		{{40,40},{159,159}},
		{{50,50},{149,149}},
		{{60,60},{139,139}},
		{{70,70},{129,129}},
		{{80,80},{119,119}},
		{{90,90},{109,109}}
};
unsigned CDataBraveNewWorld::m_zone[BRAVE_NEW_WORLD_ZONE][2][2] =
{
		{{0,0},{1,1}},
		{{2,2},{3,3}},
		{{4,4},{5,5}},
		{{6,6},{7,7}},
		{{8,8},{9,9}},
		{{10,10},{11,11}},
		{{12,12},{13,13}},
		{{14,14},{15,15}},
		{{16,16},{17,17}},
		{{18,18},{19,19}},
		{{20,20},{21,21}},
		{{22,22},{23,23}},
		{{24,24},{25,25}},
		{{26,26},{27,27}},
		{{28,28},{29,29}},
		{{30,30},{31,31}},
		{{32,32},{33,33}},
		{{34,34},{35,35}},
		{{36,36},{37,37}},
		{{38,38},{39,39}},
		{{40,40},{41,41}},
		{{42,42},{43,43}},
		{{44,44},{45,45}},
		{{46,46},{47,47}},
		{{48,48},{49,49}},
		{{50,50},{51,51}},
		{{52,52},{53,53}},
		{{54,54},{55,55}},
		{{56,56},{57,57}},
		{{58,58},{59,59}},
		{{60,60},{61,61}},
		{{62,62},{63,63}},
		{{64,64},{65,65}},
		{{66,66},{67,67}},
		{{68,68},{69,69}},
		{{70,70},{71,71}},
		{{72,72},{73,73}},
		{{74,74},{75,75}},
		{{76,76},{77,77}},
		{{78,78},{79,79}},
		{{80,80},{81,81}},
		{{82,82},{83,83}},
		{{84,84},{85,85}}
};
unsigned CDataBraveNewWorld::m_user_point[BRAVE_NEW_WORLD_LEVEL] = {8, 10, 12, 13, 15, 18, 20, 22, 25, 30};
int CDataBraveNewWorld::m_user_money[BRAVE_NEW_WORLD_LEVEL] = {80000, 100000, 120000, 130000, 150000, 180000, 200000, 220000, 250000, 300000};

CDataBraveNewWorld::CDataBraveNewWorld(string path)
	: DataBase(path)
{
	m_msg = new BraveNewWorld::BraveNewWorld();

	m_material_type = 0;
}

int CDataBraveNewWorld::Init()
{
	const BraveNewWorldConfig::BraveNewWorldConfig& config = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config;

	if(config.p_limit_size() != BRAVE_NEW_WORLD_LEVEL)
	{
		error_log("p_limit_size");
		return R_ERR_PARAM;
	}
	for(unsigned i=0;i<BRAVE_NEW_WORLD_LEVEL;++i)
		m_user_point[i] = config.p_limit(i);

	if(config.m_limit_size() != BRAVE_NEW_WORLD_LEVEL)
	{
		error_log("m_limit_size");
		return R_ERR_PARAM;
	}
	for(unsigned i=0;i<BRAVE_NEW_WORLD_LEVEL;++i)
		m_user_money[i] = config.m_limit(i);

	if(config.area_size() != BRAVE_NEW_WORLD_ZONE)
	{
		error_log("area_size");
		return R_ERR_PARAM;
	}
	for(unsigned i=0;i<BRAVE_NEW_WORLD_ZONE;++i)
	{
		if(config.area(i).lu_size() != 2 || config.area(i).rd_size() != 2)
		{
			error_log("area_size:%u", i);
			return R_ERR_PARAM;
		}
		m_zone[i][0][0] = config.area(i).lu(0);
		m_zone[i][0][1] = config.area(i).lu(1);
		m_zone[i][1][0] = config.area(i).rd(0);
		m_zone[i][1][1] = config.area(i).rd(1);
	}

	int ret = Parse();
	if(ret && ret != R_ERR_NO_DATA)
		return ret;

	m_data.Parse(*(BraveNewWorld::BraveNewWorld *)m_msg);

	((BraveNewWorld::BraveNewWorld *)m_msg)->Clear();

	return 0;
}
int CDataBraveNewWorld::Save()
{
	m_data.Serialize((BraveNewWorld::BraveNewWorld *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	//debug_log("%s",m_msg->DebugString().c_str());

	((BraveNewWorld::BraveNewWorld *)m_msg)->Clear();

	return 0;
}
int CDataBraveNewWorld::Sig(int sig)
{
	if(sig == SIGRTMIN)
		CreateMap();
	else if(sig == SIGRTMIN + 1)
		OnDay();
	else if(sig == SIGRTMIN + 2)
		OnHour();
	else if(sig == SIGRTMIN + 3)
		OnHalfHour();

	return 0;
}

int CDataBraveNewWorld::getPointLevel(unsigned x, unsigned y)
{
	for(unsigned i=0;i<BRAVE_NEW_WORLD_LEVEL;++i)
	{
		if(x < m_rect[i][0][0] || x > m_rect[i][1][0] || y < m_rect[i][0][1] || y > m_rect[i][1][1])
			return i;
	}
	return BRAVE_NEW_WORLD_LEVEL;
}
BraveNewWorldPoint CDataBraveNewWorld::getRandPoint(unsigned level)
{
	unsigned x = 0, y = 0;
	if(level == 0 || level > BRAVE_NEW_WORLD_LEVEL)
		level = 1;
	--level;
	if(level == BRAVE_NEW_WORLD_LEVEL-1)
	{
		x = m_rect[level][0][0] + Math::GetRandomInt(m_rect[level][1][0] - m_rect[level][0][0] + 1);
		y = m_rect[level][0][1] + Math::GetRandomInt(m_rect[level][1][1] - m_rect[level][0][1] + 1);
	}
	else
	{
		if(Math::GetRandomInt(2))
		{
			x = m_rect[level][0][0] + Math::GetRandomInt(m_rect[level][1][0] - m_rect[level][0][0] + 1);
			if(Math::GetRandomInt(2))
				y = m_rect[level][0][1] + Math::GetRandomInt(m_rect[level + 1][0][1] - m_rect[level][0][1]);
			else
				y = m_rect[level + 1][1][1] + 1 + Math::GetRandomInt(m_rect[level][1][1] - m_rect[level + 1][1][1]);
		}
		else
		{
			y = m_rect[level][0][1] + Math::GetRandomInt(m_rect[level][1][1] - m_rect[level][0][1] + 1);
			if(Math::GetRandomInt(2))
				x = m_rect[level][0][0] + Math::GetRandomInt(m_rect[level + 1][0][0] - m_rect[level][0][0]);
			else
				x = m_rect[level + 1][1][0] + 1 + Math::GetRandomInt(m_rect[level][1][0] - m_rect[level + 1][1][0]);
		}
	}
	return BraveNewWorldPoint(x, y);
}
BraveNewWorldPoint CDataBraveNewWorld::getRandPointEmpty(unsigned level)
{
	BraveNewWorldPoint p;
	int k = 0;
	do
	{
		if(level >= 1 && level <= 3)
			level = Math::GetRandomInt(3) + 1;
		p = getRandPoint(level);
		++k;
		if(k > 500)
			throw runtime_error("getRandPointEmpty fail!");
	}
	while(m_data.city.count(p) || ConfigManager::Instance()->GetBraveNewWorldConfigPoint(p).type() == e_DataBraveNewWorldPointType_disable);
	return p;
}
int CDataBraveNewWorld::getZoneID(unsigned x, unsigned y)
{
	for(unsigned i=0;i<BRAVE_NEW_WORLD_ZONE;++i)
	{
		if(x >= m_zone[i][0][0] && x <= m_zone[i][1][0] && y >= m_zone[i][0][1] && y <= m_zone[i][1][1])
			return i + 1;
	}
	return 0;
}
int CDataBraveNewWorld::getZoneLevel(unsigned id)
{
	if(id == 0)
		return 0;
	else if(id <= BRAVE_NEW_WORLD_ZONE_1)
		return 1;
	else if(id <= BRAVE_NEW_WORLD_ZONE_1 + BRAVE_NEW_WORLD_ZONE_2)
		return 2;
	else if(id <= BRAVE_NEW_WORLD_ZONE_1 + BRAVE_NEW_WORLD_ZONE_2 + BRAVE_NEW_WORLD_ZONE_3)
		return 3;
	else if(id <= BRAVE_NEW_WORLD_ZONE)
		return 4;
	return 0;
}
int CDataBraveNewWorld::getZonePoints(unsigned id, set<BraveNewWorldPoint>& p)
{
	if(id <= BRAVE_NEW_WORLD_ZONE && id > 0)
	{
		--id;
		for(unsigned i=m_zone[id][0][0];i<=m_zone[id][1][0];++i)
		{
			for(unsigned j=m_zone[id][0][1];j<=m_zone[id][1][1];++j)
				p.insert(BraveNewWorldPoint(i, j));
		}
		return R_SUCCESS;
	}
	return R_ERR_PARAM;
}
void CDataBraveNewWorld::getBesidePoints(BraveNewWorldPoint&p, set<BraveNewWorldPoint>& b)
{
	unsigned x = p.first;
	unsigned y = p.second;
	if(x != 0)
	{
		b.insert(BraveNewWorldPoint(x-1, y));
		if(y != 0)
		{
			b.insert(BraveNewWorldPoint(x-1, y-1));
			b.insert(BraveNewWorldPoint(x, y-1));
		}
		if(y != BRAVE_NEW_WORLD_SIZE)
		{
			b.insert(BraveNewWorldPoint(x-1, y+1));
			b.insert(BraveNewWorldPoint(x, y+1));
		}
	}
	if(x != BRAVE_NEW_WORLD_SIZE)
	{
		b.insert(BraveNewWorldPoint(x+1, y));
		if(y != 0)
		{
			b.insert(BraveNewWorldPoint(x+1, y-1));
			b.insert(BraveNewWorldPoint(x, y-1));
		}
		if(y != BRAVE_NEW_WORLD_SIZE)
		{
			b.insert(BraveNewWorldPoint(x+1, y+1));
			b.insert(BraveNewWorldPoint(x, y+1));
		}
	}
}
void CDataBraveNewWorld::CreateMap()
{
	Proto2Json p2j;
	BraveNewWorldConfig::BraveNewWorldConfig *msg = new BraveNewWorldConfig::BraveNewWorldConfig;

	map<unsigned, vector<BraveNewWorldPoint> > all;
	for(unsigned i=0;i<BRAVE_NEW_WORLD_SIZE;++i)
	{
		for(unsigned j=0;j<BRAVE_NEW_WORLD_SIZE;++j)
		{
			unsigned l = getPointLevel(i, j);
			all[l].push_back(BraveNewWorldPoint(i, j));
		}
	}
	for(unsigned i=1;i<=BRAVE_NEW_WORLD_LEVEL;++i)
	{
		random_shuffle(all[i].begin(), all[i].end());
		int s = 0;
		for(vector<BraveNewWorldPoint>::iterator it=all[i].begin();it!=all[i].end();++it)
		{
			BraveNewWorldConfig::Point *p = msg->add_land();
			p->set_x(it->first);
			p->set_y(it->second);
			p->set_npc(Math::GetRandomInt(BRAVE_NEW_WORLD_NPC));
			switch(i)
			{
			case 1:
				if(s < 22)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(3);
				}
				else if(s < 22 + 53)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(2);
				}
				else if(s < 22 + 53 + 76)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(1);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 2:
				if(s < 30)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(4);
				}
				else if(s < 30 + 71)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(3);
				}
				else if(s < 30 + 71 + 102)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(2);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 3:
				if(s < 36)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(5);
				}
				else if(s < 36 + 84)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(4);
				}
				else if(s < 36 + 84 + 120)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(3);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 4:
				if(s < 31)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(6);
				}
				else if(s < 31 + 72)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(5);
				}
				else if(s < 31 + 72 + 104)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(4);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 5:
				if(s < 33)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(7);
				}
				else if(s < 33 + 77)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(6);
				}
				else if(s < 33 + 77 + 110)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(5);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 6:
				if(s < 32)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(8);
				}
				else if(s < 32 + 75)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(7);
				}
				else if(s < 32 + 75 + 108)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(6);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 7:
				if(s < 29)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(9);
				}
				else if(s < 29 + 68)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(8);
				}
				else if(s < 29 + 68 + 98)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(7);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 8:
				if(s < 24)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(10);
				}
				else if(s < 24 + 56)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(9);
				}
				else if(s < 24 + 56 + 80)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(8);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 9:
				if(s < 32)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(10);
				}
				else if(s < 32 + 75)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(9);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			case 10:
				if(s < 40)
				{
					p->set_type(e_DataBraveNewWorldPointType_resource);
					p->set_level(10);
				}
				else
				{
					p->set_type(e_DataBraveNewWorldPointType_empty);
					p->set_level(i);
				}
				break;
			default:
				error_log("CreateMap fail");
				return;
				break;
			}
			++s;

			unsigned l = getZoneLevel(getZoneID(*it));
			if(l)
			{
				p->set_type(e_DataBraveNewWorldPointType_zone);
				p->set_level(l);
			}
		}
	}

	for(int i=e_DataBraveNewWorldPointType_empty;i<=e_DataBraveNewWorldPointType_resource;++i)
	{
		for(int j=1;j<=BRAVE_NEW_WORLD_LEVEL;++j)
		{
			BraveNewWorldConfig::Property *p = msg->add_config();
			p->set_type(i);
			p->set_level(j);
			p->set_occupy(1);
			p->set_product(1);
			for(int k=0;k<BRAVE_NEW_WORLD_NPC;++k)
				p->add_npc(401);
		}
	}
	for(int i=1;i<=BRAVE_NEW_WORLD_ZONE_LEVEL;++i)
	{
		BraveNewWorldConfig::Property *p = msg->add_config();
		p->set_type(e_DataBraveNewWorldPointType_zone);
		p->set_level(i);
		p->set_occupy(1);
		p->set_product(1);
		for(int k=0;k<BRAVE_NEW_WORLD_NPC;++k)
			p->add_npc(401);
	}

	for(int i=1;i<=BRAVE_NEW_WORLD_ZONE_LEVEL;++i)
	{
		BraveNewWorldConfig::Zone *p = msg->add_zone();
		p->set_level(i);
		p->set_product(1);
	}

	for(int i=1;i<=BRAVE_NEW_WORLD_LEVEL-1;++i)
	{
		BraveNewWorldConfig::City *p = msg->add_city();
		p->set_level(i);
		p->set_need(1);
		p->set_time(100);
	}

	p2j.m_msg = msg;
	p2j.P2J();
	string path = "/data/release/sgonline/BraveNewWorldConfig_" + CTrans::ITOS(Time::GetGlobalTime()) + ".json";
	File::Write(path, p2j.SerializeJson());
}

int CDataBraveNewWorld::GetSelf(unsigned uid, unsigned aid, unsigned lv, Json::Value &result)
{
	if(!m_data.user.count(uid))
	{
		BraveNewWorldPoint p = getRandPointEmpty(1);
		m_data.user[uid].uid = uid;
		m_data.user[uid].seq = 0;
		m_data.user[uid].x = p.first;
		m_data.user[uid].y = p.second;
		m_data.user[uid].rts = Time::GetGlobalTime();
		m_data.user[uid].hts = 0;
		m_data.user[uid].pts = 0;
		m_data.user[uid].bts = 0;
		m_data.user[uid].bt = BRAVE_NEW_WORLD_BT;
		m_data.user[uid].tts = Time::GetGlobalTime();
		for(int i=0;i<BRAVE_NEW_WORLD_HP_USER;++i)
			m_data.user[uid].hp.push_back(BRAVE_NEW_WORLD_HP);
		m_data.user[uid].RandMission();
		m_data.city[p] = uid;
	}
	m_data.user[uid].aid = aid;
	m_data.user[uid].lv = lv;
	m_data.user[uid].GetJson(result);
	if(aid)
	{
		if(!m_data.alliance.count(aid))
		{
			m_data.alliance[aid].aid = aid;
			m_data.alliance[aid].RandMission();
		}
		m_data.alliance[aid].GetJson(result);
	}
	return 0;
}
int CDataBraveNewWorld::GetMissionInfo(unsigned uid, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;

	m_data.user[uid].mission.GetJson(result);

	result["alliance"].resize(0);
	if(m_data.alliance.count(m_data.user[uid].aid))
	{
		for(map<unsigned int, DataBraveNewWorldAllianceMission>::iterator it=m_data.alliance[m_data.user[uid].aid].mission.begin();it!=m_data.alliance[m_data.user[uid].aid].mission.end();++it)
		{
			Json::Value t;
			it->second.GetJson(t);
			int s = 0;
			if(it->second.m == false)
			{
				set<BraveNewWorldPoint> ps;
				getZonePoints(it->second.id, ps);
				for(set<BraveNewWorldPoint>::iterator iter=ps.begin();iter!=ps.end();++iter)
				{
					if(m_data.land[*iter].uid
					&& m_data.user[m_data.land[*iter].uid].aid == m_data.user[uid].aid
					&& m_data.city.count(*iter)
					&& m_data.user[m_data.city[*iter]].aid == m_data.user[uid].aid)
						++s;
				}
			}
			t["o"] = s;
			result["alliance"].append(t);
		}
	}

	return 0;
}
int CDataBraveNewWorld::GetPoints(vector<BraveNewWorldPoint>& p, Json::Value &result)
{
	result["lands"].resize(0);
	for(vector<BraveNewWorldPoint>::iterator it=p.begin();it!=p.end();++it)
	{
		Json::Value t;
		m_data.land[*it].GetJson(t);
		m_data.land[*it].GetDefLimit(t);
		if(m_data.city.count(*it))
			m_data.user[m_data.city[*it]].GetDefLimit(t);
		result["lands"].append(t);
	}
	return 0;
}
int CDataBraveNewWorld::GetOnePoint(BraveNewWorldPoint& p, Json::Value &result)
{
	m_data.land[p].GetJson(result);
	m_data.land[p].GetDef(result);
	if(m_data.city.count(p))
		m_data.user[m_data.city[p]].GetDef(result);
	return 0;
}
int CDataBraveNewWorld::GetPointsLimit(vector<BraveNewWorldPoint>& p, Json::Value &result)
{
	result["lands"].resize(0);
	for(vector<BraveNewWorldPoint>::iterator it=p.begin();it!=p.end();++it)
	{
		Json::Value t;
		m_data.land[*it].GetJsonLimit(t);
		m_data.land[*it].GetDefLimit(t);
		if(m_data.city.count(*it))
			m_data.user[m_data.city[*it]].GetDefLimit(t);
		result["lands"].append(t);
	}
	return 0;
}
int CDataBraveNewWorld::GetZones(vector<unsigned>& z, Json::Value &result)
{
	result["zones"].resize(0);
	for(vector<unsigned>::iterator it=z.begin();it!=z.end();++it)
	{
		Json::Value t;
		m_data.zone[*it].GetJson(t);
		result["zones"].append(t);
	}
	return 0;
}
int CDataBraveNewWorld::GetHistory(unsigned uid, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;

	result["his"].resize(0);
	for(list<DataBraveNewWorldHistory>::iterator it=m_data.user[uid].his.begin();it!=m_data.user[uid].his.end();++it)
	{
		Json::Value t;
		it->GetJson(t);
		result["his"].append(t);
	}
	return 0;
}
int CDataBraveNewWorld::GetFavourate(unsigned uid, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;

	result["fav"].resize(0);
	for(vector<DataBraveNewWorldFavourate>::iterator it=m_data.user[uid].fav.begin();it!=m_data.user[uid].fav.end();++it)
	{
		Json::Value t;
		it->GetJson(t);
		result["fav"].append(t);
	}
	return 0;
}

int CDataBraveNewWorld::Collect(unsigned uid, unsigned seq, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	unsigned ts = Time::GetGlobalTime();
	if(m_data.user[uid].rts + 60 > ts)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Collect_rts");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
		return ret;

	int m = getUserMoney(m_data.user[uid].lv), n = dataUser.type;
	do
	{
		unsigned ai = 0, ats = -1;
		for(unsigned i=1;i<=BRAVE_NEW_WORLD_ZONE_1;++i)
		{
			if(m_data.zone[i].aid == m_data.user[uid].aid)
			{
				if(m_data.zone[i].ts < ats)
				{
					ats = m_data.zone[i].ts;
					ai = i;
				}
			}
		}
		if(ai && ats + 60 <= ts)
		{
			n += min(300u, (ts - max(ats, m_data.user[uid].rts)) / 60) * ConfigManager::Instance()->GetBraveNewWorldConfigZone(getZoneLevel(ai)).product();
			if(n >= m)
			{
				n = m;
				break;
			}
		}

		ai = 0, ats = -1;
		for(unsigned i=BRAVE_NEW_WORLD_ZONE_1+1;i<=BRAVE_NEW_WORLD_ZONE_1+BRAVE_NEW_WORLD_ZONE_2;++i)
		{
			if(m_data.zone[i].aid == m_data.user[uid].aid)
			{
				if(m_data.zone[i].ts < ats)
				{
					ats = m_data.zone[i].ts;
					ai = i;
				}
			}
		}
		if(ai && ats + 60 <= ts)
		{
			n += min(300u, (ts - max(ats, m_data.user[uid].rts)) / 60) * ConfigManager::Instance()->GetBraveNewWorldConfigZone(getZoneLevel(ai)).product();
			if(n >= m)
			{
				n = m;
				break;
			}
		}

		ai = 0, ats = -1;
		for(unsigned i=BRAVE_NEW_WORLD_ZONE_1+BRAVE_NEW_WORLD_ZONE_2+1;i<=BRAVE_NEW_WORLD_ZONE_1+BRAVE_NEW_WORLD_ZONE_2+BRAVE_NEW_WORLD_ZONE_3;++i)
		{
			if(m_data.zone[i].aid == m_data.user[uid].aid)
			{
				if(m_data.zone[i].ts < ats)
				{
					ats = m_data.zone[i].ts;
					ai = i;
				}
			}
		}
		if(ai && ats + 60 <= ts)
		{
			n += min(300u, (ts - max(ats, m_data.user[uid].rts)) / 60) * ConfigManager::Instance()->GetBraveNewWorldConfigZone(getZoneLevel(ai)).product();
			if(n >= m)
			{
				n = m;
				break;
			}
		}

		ai = 0, ats = -1;
		for(unsigned i=BRAVE_NEW_WORLD_ZONE_1+BRAVE_NEW_WORLD_ZONE_2+BRAVE_NEW_WORLD_ZONE_3+1;i<=BRAVE_NEW_WORLD_ZONE;++i)
		{
			if(m_data.zone[i].aid == m_data.user[uid].aid)
			{
				if(m_data.zone[i].ts < ats)
				{
					ats = m_data.zone[i].ts;
					ai = i;
				}
			}
		}
		if(ai && ats + 60 <= ts)
		{
			n += min(300u, (ts - max(ats, m_data.user[uid].rts)) / 60) * ConfigManager::Instance()->GetBraveNewWorldConfigZone(getZoneLevel(ai)).product();
			if(n >= m)
			{
				n = m;
				break;
			}
		}

		for(set<BraveNewWorldPoint>::iterator it=m_data.user[uid].lands.begin();it!=m_data.user[uid].lands.end();++it)
		{
			if(m_data.land[*it].rts + 60 > ts)
				continue;
			n += min(300u, (ts - m_data.land[*it].rts) / 60) * ConfigManager::Instance()->GetBraveNewWorldConfigPointProperty(*it).product();
			m_data.land[*it].rts = ts;
			if(n >= m)
			{
				n = m;
				break;
			}
		}
	}while(0);
	m_data.user[uid].rts = ts;
	int on = n - dataUser.type;
	dataUser.type = n;
	ret = logicUser.SetUserLimit(uid,dataUser);
	if(ret)
		return ret;

	RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",uid,on,dataUser.type);

	result["seq"] = ++m_data.user[uid].seq;
	result["rts"] = ts;
	result["bnwm"] = n;
	return 0;
}
int CDataBraveNewWorld::StartAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	bool ic = m_data.city.count(p);
	bool isc = ic && m_data.city[p] == uid;
	bool ioc = ic && m_data.city[p] != uid;
	bool is = m_data.land[p].uid == uid;
	unsigned userid = ioc ? m_data.city[p] : m_data.land[p].uid;

	//点
	if(m_data.user[uid].lands.size() >= getUserPoint(m_data.user[uid].lv))
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_StartAttack_lv");
	}
	//烽火令
	int c = userid?2:1;
	if(!cash && (m_data.user[uid].bt + (Time::GetGlobalTime() - m_data.user[uid].tts)/1800) < c)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_StartAttack_bt");
	}
	//战斗
	if(m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_StartAttack_fid");
	}
	//联盟
	if(userid == uid
	|| (userid && m_data.user[userid].aid && m_data.user[uid].aid && m_data.user[uid].aid == m_data.user[userid].aid))
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_StartAttack_aid");
	}
	//州府
	unsigned zid = getZoneID(p);

	//todo 增加同一块州府只能占领一块地的判断
	bool check = CheckZonePoint(zid, uid);

	if (check)
	{
		LOGIC_ERROR_RETURN_MSG("zone_already_occupied");
	}

	if(zid && m_data.zone[zid].ts + 12*3600 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_StartAttack_zone");
	}
	//保护
	if(ioc && m_data.user[userid].pts + 3600 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_StartAttack_pts");
	}
	//位置
	if(!isc && !is)
	{
		bool f = false;
		set<BraveNewWorldPoint> b;
		getBesidePoints(p, b);
		for(set<BraveNewWorldPoint>::iterator it=b.begin();it!=b.end();++it)
		{
			if(m_data.land[*it].uid == uid || (m_data.city.count(*it) && m_data.city[*it] == uid))
			{
				f = true;
				break;
			}
		}
		if(!f)
		{
			LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_StartAttack_p");
		}
	}

	if(cash)
	{
		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -10*c, 0, payData, "CDataBraveNewWorld_StartAttack",user_flag,bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
	}
	else
	{
		m_data.user[uid].bt = min(24u, m_data.user[uid].bt + (Time::GetGlobalTime() - m_data.user[uid].tts)/1800) - c;
		m_data.user[uid].tts = Time::GetGlobalTime();
	}
	m_data.land[p].fid = uid;
	m_data.land[p].fts = Time::GetGlobalTime();

	if(!ioc)
		m_data.land[p].GetDef(result);
	else
		m_data.user[userid].GetDef(result);
	result["uid"] = userid;
	result["bt"] = m_data.user[uid].bt;
	result["tts"] = m_data.user[uid].tts;
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::EndAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, vector<unsigned>& hp, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	bool ic = m_data.city.count(p);
	bool isc = ic && m_data.city[p] == uid;
	bool ioc = ic && m_data.city[p] != uid;
	bool is = m_data.land[p].uid == uid;
	unsigned userid = ioc ? m_data.city[p] : m_data.land[p].uid;

	if(m_data.land[p].fid != uid || m_data.land[p].fts + BNW_ATTACK_MAX_TIME < Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_EndAttack_fid");
	}

	bool w = false;
	double gd = 0;
	int g = 0, t = 0, lm = 0, nm = 0, lh = 0, nh = 0;
	if(ioc)
	{
		if(hp.size() != BRAVE_NEW_WORLD_HP_USER)
		{
			LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_EndAttack_hp");
		}

		t = 2;
		for(int i=0;i<BRAVE_NEW_WORLD_HP_USER;++i)
		{
			if(i == BRAVE_NEW_WORLD_HP_USER - 1)
			{
				lh = m_data.user[userid].hp[i] - hp[i];
				nh = hp[i];
				if(m_data.user[userid].hp[i] > hp[i])
					gd += double(m_data.user[userid].hp[i] - hp[i]) / double(BRAVE_NEW_WORLD_HP) * double(0.7);
			}
			else if(i < BRAVE_NEW_WORLD_HP_USER - 1 && i >= BRAVE_NEW_WORLD_HP_USER - 4)
			{
				if(m_data.user[userid].hp[i] > hp[i])
					gd += double(m_data.user[userid].hp[i] - hp[i]) / double(BRAVE_NEW_WORLD_HP) * double(0.1);
			}
			m_data.user[userid].hp[i] = hp[i];
		}
		if(gd > 0)
		{
			gd *= double(0.6);
			CLogicUser logicUser;
			DataUser dataUser;
			AUTO_LOCK_USER(userid)
			int ret = logicUser.GetUserLimit(userid,dataUser);
			if(ret)
				return ret;
			g = min(dataUser.type, int(ceil(double(dataUser.type) * gd)));
			dataUser.type -= g;
			ret = logicUser.SetUserLimit(userid,dataUser);
			if(ret)
				return ret;

			lm = g;
			nm = dataUser.type;

			RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",userid,-g,dataUser.type);
		}
		if(hp[BRAVE_NEW_WORLD_HP_USER-1] == 0)
		{
			w = true;
			unsigned l = getPointLevel(p);
			if(l)
				--l;
			BraveNewWorldPoint k = getRandPointEmpty(l);
			m_data.city.erase(p);
			m_data.city[k] = userid;
			m_data.user[userid].x = k.first;
			m_data.user[userid].y = k.second;
			m_data.user[userid].pts = Time::GetGlobalTime();
			for(int i=0;i<BRAVE_NEW_WORLD_HP_USER;++i)
				m_data.user[userid].hp[i] = BRAVE_NEW_WORLD_HP;

			set<BraveNewWorldPoint> del;
			int d = 0;
			for(set<BraveNewWorldPoint>::iterator it=m_data.user[userid].lands.begin();it!=m_data.user[userid].lands.end();++it)
			{
				m_data.land[*it].Clear();
				del.insert(*it);
				++d;
				if(d >= 5)
					break;
			}
			for(set<BraveNewWorldPoint>::iterator it=del.begin();it!=del.end();++it)
				m_data.user[userid].lands.erase(*it);

			CLogicUpdates logicUpdates;
			Json::Value updates;
			updates["s"] = "BNWBASELOSS";
			updates["lose"] = d;
			updates["uid"] = uid;
			updates["ts"] = Time::GetGlobalTime();
			updates["x"] = k.first;
			updates["y"] = k.second;
			logicUpdates.AddUpdate(userid, updates);
		}
	}
	else
	{
		unsigned h = BRAVE_NEW_WORLD_HP;
		if(m_data.land[p].def)
		{
			if(hp.size() != 2)
			{
				LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_EndAttack_hp");
			}

			t = 1;
			lh = m_data.land[p].hp - hp[0];
			nh = hp[0];
			m_data.land[p].hp = hp[0];
			h = hp[1];
		}
		else
		{
			if(hp.size() != 1)
			{
				LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_EndAttack_hp");
			}

			t = 0;
			lh = BRAVE_NEW_WORLD_HP - hp[0];
			nh = hp[0];
			h = hp[0];
		}
		if(h == 0)
			w = true;
		if(BRAVE_NEW_WORLD_HP > h)
			g = int(ceil(double(ConfigManager::Instance()->GetBraveNewWorldConfigPointProperty(p).occupy()) * double(BRAVE_NEW_WORLD_HP - h) / double(BRAVE_NEW_WORLD_HP)));
		lm = g;
	}
	if(w)
	{
		if(m_data.land[p].uid)
			m_data.user[m_data.land[p].uid].lands.erase(p);
		m_data.land[p].uid = uid;
		m_data.land[p].rts = Time::GetGlobalTime();
		m_data.land[p].hero = 0;
		m_data.land[p].hp = 0;
		m_data.land[p].def = false;
		unsigned zid = getZoneID(p);
		if(zid && m_data.user[uid].aid && m_data.zone[zid].aid != m_data.user[uid].aid)
		{
			bool f = true;
			bool k = true;
			set<BraveNewWorldPoint> ps;
			getZonePoints(zid, ps);
			for(set<BraveNewWorldPoint>::iterator it=ps.begin();it!=ps.end();++it)
			{
				if(!m_data.city.count(*it) || m_data.user[m_data.city[*it]].aid != m_data.user[uid].aid)
					k = false;
				if(m_data.land[*it].uid == 0 || m_data.user[m_data.land[*it].uid].aid != m_data.user[uid].aid)
				{
					f = false;
					break;
				}
			}
			if(f)
			{
				m_data.zone[zid].aid = m_data.user[uid].aid;
				m_data.zone[zid].ts = Time::GetGlobalTime();
				if(k
				&& m_data.alliance.count(m_data.user[uid].aid)
				&& m_data.alliance[m_data.user[uid].aid].mission.count(zid)
				&& m_data.alliance[m_data.user[uid].aid].mission[zid].m == false)
					m_data.alliance[m_data.user[uid].aid].mission[zid].m = true;
			}
		}
		m_data.user[uid].lands.insert(p);

		unsigned mu = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().user();
		if(m_data.land[p].rc && m_data.user[uid].rl < mu)
		{
			unsigned c = min(mu - m_data.user[uid].rl, m_data.land[p].rc);
			m_data.user[uid].rl += c;
			CLogicEquipment loigcEquipment;
			loigcEquipment.AddOneItem(uid, BRAVE_NEW_WORLD_REWARD, c, "EndAttack", result["equip"], true);
			m_data.land[p].rc = 0;
		}

		//材料获得
		GetMaterial(uid, m_data.land[p],  result);

		if(m_data.user[uid].mission.m3 == e_DataBraveNewWorldMissionStat_uncomplete
		&& m_data.user[uid].mission.mx == p.first
		&& m_data.user[uid].mission.my == p.second)
			m_data.user[uid].mission.m3 = e_DataBraveNewWorldMissionStat_complete;
	}
	if(g)
	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUserLimit(uid,dataUser);
		if(ret)
			return ret;
		int on = dataUser.type;
		dataUser.type = min(getUserMoney(m_data.user[uid].lv), dataUser.type + g);
		on = dataUser.type - on;
		ret = logicUser.SetUserLimit(uid,dataUser);
		if(ret)
			return ret;

		RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",uid,on,dataUser.type);

		if(m_data.user[uid].mission.m2 != e_DataBraveNewWorldMissionStat_got2)
			m_data.user[uid].mission.m2 += g;
	}
	m_data.land[p].fid = 0;
	m_data.land[p].fts = 0;

	DataBraveNewWorldHistory his;
	his.uid = uid;
	his.type = t;
	his.x = p.first;
	his.y = p.second;
	his.lm = lm;
	his.nm = nm;
	his.lh = lh;
	his.nh = nh;
	his.ts = Time::GetGlobalTime();
	if(userid)
	{
		if(m_data.user[userid].his.size() >= 20)
			m_data.user[userid].his.pop_front();
		m_data.user[userid].his.push_back(his);
	}
	his.uid = userid;
	his.type += 3;
	if(m_data.user[uid].his.size() >= 20)
		m_data.user[uid].his.pop_front();
	m_data.user[uid].his.push_back(his);

	m_data.land[p].GetJson(result);
	m_data.land[p].GetDef(result);
	if(ioc)
		m_data.user[userid].GetDef(result);
	m_data.user[uid].mission.GetJson(result);
	if(m_data.alliance.count(m_data.user[uid].aid))
		m_data.alliance[m_data.user[uid].aid].GetJson(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::FastAttack(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, bool cash1, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	bool ic = m_data.city.count(p);
	bool isc = ic && m_data.city[p] == uid;
	bool ioc = ic && m_data.city[p] != uid;
	bool is = m_data.land[p].uid == uid;
	unsigned userid = ioc ? m_data.city[p] : m_data.land[p].uid;

	//玩家
	if(m_data.land[p].def || ioc)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_def");
	}
	//cd
	if(!cash1 && m_data.user[uid].bts + 300 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_bts");
	}
	//点
	if(m_data.user[uid].lands.size() >= getUserPoint(m_data.user[uid].lv))
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_lv");
	}
	//烽火令
	int c = userid?2:1;
	if(!cash && (m_data.user[uid].bt + (Time::GetGlobalTime() - m_data.user[uid].tts)/1800) < c)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_bt");
	}
	//战斗
	if(m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_fid");
	}
	//联盟
	if(userid == uid
	|| (userid && m_data.user[userid].aid && m_data.user[uid].aid && m_data.user[uid].aid == m_data.user[userid].aid))
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_aid");
	}
	//州府
	unsigned zid = getZoneID(p);

	//todo 增加同一块州府只能占领一块地的判断
	bool check = CheckZonePoint(zid, uid);

	if (check)
	{
		LOGIC_ERROR_RETURN_MSG("zone_already_occupied");
	}

	if(zid && m_data.zone[zid].ts + 12*3600 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_zone");
	}
	//位置
	if(!isc)
	{
		bool f = false;
		set<BraveNewWorldPoint> b;
		getBesidePoints(p, b);
		for(set<BraveNewWorldPoint>::iterator it=b.begin();it!=b.end();++it)
		{
			if(m_data.land[*it].uid == uid || (m_data.city.count(*it) && m_data.city[*it] == uid))
			{
				f = true;
				break;
			}
		}
		if(!f)
		{
			LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_FastAttack_p");
		}
	}

	if(cash || cash1)
	{
		int u = 0;
		if(cash)
			u += 10*c;
		if(cash1)
			u += min(5u, (m_data.user[uid].bts + 300 - Time::GetGlobalTime())/60 + 1);
		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -u, 0, payData, "CDataBraveNewWorld_FastAttack",user_flag,bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
	}
	else
	{
		if(!cash)
		{
			m_data.user[uid].bt = min(24u, m_data.user[uid].bt + (Time::GetGlobalTime() - m_data.user[uid].tts)/1800) - c;
			m_data.user[uid].tts = Time::GetGlobalTime();
		}
	}
	m_data.user[uid].bts = Time::GetGlobalTime();

	bool w = true;
	int g = ConfigManager::Instance()->GetBraveNewWorldConfigPointProperty(p).occupy();
	int t = 0, lm = g, nm = 0, lh = BRAVE_NEW_WORLD_HP, nh = 0;
	if(w)
	{
		if(m_data.land[p].uid)
			m_data.user[m_data.land[p].uid].lands.erase(p);
		m_data.land[p].uid = uid;
		m_data.land[p].rts = Time::GetGlobalTime();
		m_data.land[p].hero = 0;
		m_data.land[p].hp = 0;
		m_data.land[p].def = false;
		if(zid && m_data.user[uid].aid && m_data.zone[zid].aid != m_data.user[uid].aid)
		{
			bool f = true;
			bool k = true;
			set<BraveNewWorldPoint> ps;
			getZonePoints(zid, ps);
			for(set<BraveNewWorldPoint>::iterator it=ps.begin();it!=ps.end();++it)
			{
				if(!m_data.city.count(*it) || m_data.user[m_data.city[*it]].aid != m_data.user[uid].aid)
					k = false;
				if(m_data.land[*it].uid == 0 || m_data.user[m_data.land[*it].uid].aid != m_data.user[uid].aid)
				{
					f = false;
					break;
				}
			}
			if(f)
			{
				m_data.zone[zid].aid = m_data.user[uid].aid;
				m_data.zone[zid].ts = Time::GetGlobalTime();
				if(k
				&& m_data.alliance.count(m_data.user[uid].aid)
				&& m_data.alliance[m_data.user[uid].aid].mission.count(zid)
				&& m_data.alliance[m_data.user[uid].aid].mission[zid].m == false)
					m_data.alliance[m_data.user[uid].aid].mission[zid].m = true;
			}
		}
		m_data.user[uid].lands.insert(p);

		unsigned mu = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().user();
		if(m_data.land[p].rc && m_data.user[uid].rl < mu)
		{
			unsigned c = min(mu - m_data.user[uid].rl, m_data.land[p].rc);
			m_data.user[uid].rl += c;
			CLogicEquipment loigcEquipment;
			loigcEquipment.AddOneItem(uid, BRAVE_NEW_WORLD_REWARD, c, "EndAttack", result["equip"], true);
			m_data.land[p].rc = 0;
		}

		//材料获得
		GetMaterial(uid, m_data.land[p], result);

		if(m_data.user[uid].mission.m3 == e_DataBraveNewWorldMissionStat_uncomplete
		&& m_data.user[uid].mission.mx == p.first
		&& m_data.user[uid].mission.my == p.second)
			m_data.user[uid].mission.m3 = e_DataBraveNewWorldMissionStat_complete;
	}
	if(g)
	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUserLimit(uid,dataUser);
		if(ret)
			return ret;
		int on = dataUser.type;
		dataUser.type = min(getUserMoney(m_data.user[uid].lv), dataUser.type + g);
		on = dataUser.type - on;
		ret = logicUser.SetUserLimit(uid,dataUser);
		if(ret)
			return ret;

		RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",uid,on,dataUser.type);

		if(m_data.user[uid].mission.m2 != e_DataBraveNewWorldMissionStat_got2)
			m_data.user[uid].mission.m2 += g;
	}
	m_data.land[p].fid = 0;
	m_data.land[p].fts = 0;

	DataBraveNewWorldHistory his;
	his.uid = uid;
	his.type = t;
	his.x = p.first;
	his.y = p.second;
	his.lm = lm;
	his.nm = nm;
	his.lh = lh;
	his.nh = nh;
	his.ts = Time::GetGlobalTime();
	if(userid)
	{
		if(m_data.user[userid].his.size() >= 20)
			m_data.user[userid].his.pop_front();
		m_data.user[userid].his.push_back(his);
	}
	his.uid = userid;
	his.type += 3;
	if(m_data.user[uid].his.size() >= 20)
		m_data.user[uid].his.pop_front();
	m_data.user[uid].his.push_back(his);

	m_data.land[p].GetJson(result);
	result["bt"] = m_data.user[uid].bt;
	result["tts"] = m_data.user[uid].tts;
	result["bts"] = m_data.user[uid].bts;
	m_data.user[uid].mission.GetJson(result);
	if(m_data.alliance.count(m_data.user[uid].aid))
		m_data.alliance[m_data.user[uid].aid].GetJson(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}

bool CDataBraveNewWorld::CheckZonePoint(unsigned zid, unsigned uid)
{
	if (0 == zid)
	{
		return false;
	}

	//遍历用户占有的地块
	set<BraveNewWorldPoint>::iterator siter;
	unsigned othzid = 0;

	for(siter = m_data.user[uid].lands.begin(); siter != m_data.user[uid].lands.end(); ++siter)
	{
		othzid = getZoneID(siter->first, siter->second);

		if (othzid == zid)
		{
			return true;
		}
	}

	return false;
}

int CDataBraveNewWorld::Move(unsigned uid, unsigned seq, BraveNewWorldPoint& p, unsigned ud, bool super, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	BraveNewWorldPoint s = BraveNewWorldPoint(m_data.user[uid].x, m_data.user[uid].y);
	if(s == p)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Move_self");
	}
	if(m_data.city.count(p) || m_data.land[p].def)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Move_def");
	}
	if(!super && m_data.land[p].uid != uid)
	{
		if(m_data.land[p].uid == 0
		|| m_data.user[uid].aid == 0
		|| (m_data.user[m_data.land[p].uid].aid != m_data.user[uid].aid))
		{
			LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Move_uid");
		}
	}
	if((m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	|| (m_data.land[s].fid && m_data.land[s].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime()))
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Move_fid");
	}

	AUTO_LOCK_USER(uid)
	CLogicEquipment equipment;
	int ret = 0;
	if(super)
		ret = equipment.UseEquipment(uid, BRAVE_NEW_WORLD_ME_SUPER, ud, 1, "CDataBraveNewWorld_Move");
	else
	{
		unsigned c = max(abs(int(s.first) - int(p.first)), abs(int(s.second) - int(p.second))) / 5 + 1;
		ret = equipment.UseEquipment(uid, BRAVE_NEW_WORLD_ME, ud, c, "CDataBraveNewWorld_Move");
	}
	if(ret)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Move_ud");
	}

	m_data.city.erase(s);
	m_data.city[p] = uid;
	m_data.user[uid].x = p.first;
	m_data.user[uid].y = p.second;
	m_data.user[uid].pts = 0;

	unsigned zid = getZoneID(p);
	if(m_data.alliance.count(m_data.user[uid].aid) && m_data.alliance[m_data.user[uid].aid].mission.count(zid))
	{
		if(m_data.user[uid].mission.m1 == e_DataBraveNewWorldMissionStat_uncomplete)
			m_data.user[uid].mission.m1 = e_DataBraveNewWorldMissionStat_complete;
		if(m_data.alliance[m_data.user[uid].aid].mission[zid].m == false)
		{
			bool f = true;
			set<BraveNewWorldPoint> ps;
			getZonePoints(zid, ps);
			for(set<BraveNewWorldPoint>::iterator it=ps.begin();it!=ps.end();++it)
			{
				if(m_data.land[*it].uid == 0
				|| m_data.user[m_data.land[*it].uid].aid != m_data.user[uid].aid
				|| !m_data.city.count(*it)
				|| m_data.user[m_data.city[*it]].aid != m_data.user[uid].aid)
				{
					f = false;
					break;
				}
			}
			if(f)
				m_data.alliance[m_data.user[uid].aid].mission[zid].m = true;
		}
	}

	result["x"] = m_data.user[uid].x;
	result["y"] = m_data.user[uid].y;
	m_data.user[uid].mission.GetJson(result);
	if(m_data.alliance.count(m_data.user[uid].aid))
		m_data.alliance[m_data.user[uid].aid].GetJson(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::Build(unsigned uid, unsigned seq, bool cash, BraveNewWorldPoint& p, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(m_data.land[p].uid != uid)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Build_uid");
	}
	if(m_data.city.count(p) || m_data.land[p].def)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Build_def");
	}
	if(m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Build_fid");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	CLogicPay logicPay;
	DataPay payData;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
	if(ret)
		return ret;
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);
	ret = logicPay.ProcessOrderForBackend(uid, cash?-10:0, cash?0:-10, payData, "CDataBraveNewWorld_Build",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	m_data.land[p].def = true;
	m_data.land[p].hero = 0;
	m_data.land[p].hp = BRAVE_NEW_WORLD_HP;
	m_data.land[p].defts = Time::GetGlobalTime();

	m_data.land[p].GetJsonLimit(result);
	m_data.land[p].GetDef(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::Defend(unsigned uid, unsigned seq, bool cash, BraveNewWorldPoint& p, unsigned hero, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(m_data.land[p].uid != uid)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Defend_uid");
	}
	if(!m_data.land[p].def)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Defend_def");
	}
	if(m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Defend_fid");
	}

	if(cash)
	{
		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -50, 0, payData, "CDataBraveNewWorld_Defend",user_flag,bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
	}

	m_data.land[p].hero = hero;

	m_data.land[p].GetJsonLimit(result);
	m_data.land[p].GetDef(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::RecoverPoint(unsigned uid, unsigned seq, BraveNewWorldPoint& p, bool cash, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(m_data.land[p].uid != uid)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RecoverPoint_uid");
	}
	if(!m_data.land[p].def)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RecoverPoint_def");
	}
	if(m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RecoverPoint_fid");
	}
	if(m_data.land[p].hp == BRAVE_NEW_WORLD_HP)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RecoverPoint_hp");
	}
	if(!cash && m_data.user[uid].hts + 600 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RecoverPoint_hts");
	}

	if(cash)
	{
		int u = min(10u, (m_data.user[uid].hts + 600 - Time::GetGlobalTime())/60 + 1);

		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -u, 0, payData, "CDataBraveNewWorld_RecoverPoint",user_flag,bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
	}

	m_data.user[uid].hts = Time::GetGlobalTime();
	m_data.land[p].hp = BRAVE_NEW_WORLD_HP;

	m_data.land[p].GetJsonLimit(result);
	m_data.land[p].GetDef(result);
	result["hts"] = m_data.user[uid].hts;
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::RevcoverUser(unsigned uid, unsigned seq, bool cash, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	BraveNewWorldPoint p = BraveNewWorldPoint(m_data.user[uid].x, m_data.user[uid].y);
	if(m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RevcoverUser_fid");
	}
	bool f = true;
	for(vector<unsigned>::iterator it=m_data.user[uid].hp.begin();it!=m_data.user[uid].hp.end();++it)
	{
		if(*it != BRAVE_NEW_WORLD_HP)
		{
			f = false;
			break;
		}
	}
	if(f)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RevcoverUser_hp");
	}
	if(!cash && m_data.user[uid].hts + 600 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_RevcoverUser_hts");
	}

	if(cash)
	{
		int u = min(10u, (m_data.user[uid].hts + 600 - Time::GetGlobalTime())/60 + 1);

		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -u, 0, payData, "CDataBraveNewWorld_RevcoverUser",user_flag,bsave);
		if(ret)
			return ret;
		result["pointpay"].resize(0);
		result["pointpay"] = user_flag["user_pay"];
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
	}

	m_data.user[uid].hts = Time::GetGlobalTime();
	for(vector<unsigned>::iterator it=m_data.user[uid].hp.begin();it!=m_data.user[uid].hp.end();++it)
		*it = BRAVE_NEW_WORLD_HP;

	m_data.land[p].GetJsonLimit(result);
	m_data.user[uid].GetDef(result);
	result["hts"] = m_data.user[uid].hts;
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::Discard(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(m_data.land[p].uid != uid)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Discard_uid");
	}
	if(m_data.land[p].fid && m_data.land[p].fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Discard_fid");
	}
	if(m_data.land[p].def && m_data.land[p].hero)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Discard_def");
	}

	m_data.user[uid].lands.erase(p);
	m_data.land[p].Clear();

	m_data.land[p].GetJsonLimit(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::JoinAlliance(unsigned uid, unsigned userid, unsigned aid, Json::Value &result)
{
	if(!m_data.user.count(userid))
		return 0;

	if(userid != uid && m_data.user.count(uid))
	{
		if(aid == 0)
		{
			 if(m_data.user[uid].aid != m_data.user[userid].aid)
				 return R_ERR_LOGIC;
		}
		else
		{
			 if(aid != m_data.user[uid].aid)
				 return R_ERR_LOGIC;
		}
	}

	m_data.user[userid].aid = aid;

	return 0;
}
int CDataBraveNewWorld::SetFavourate(unsigned uid, unsigned seq, vector<BraveNewWorldPoint>& p, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(p.size() > 20)
		return R_ERR_PARAM;

	m_data.user[uid].fav.clear();
	for(vector<BraveNewWorldPoint>::iterator it=p.begin();it!=p.end();++it)
		m_data.user[uid].fav.push_back(DataBraveNewWorldFavourate(*it));

	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}

int CDataBraveNewWorld::Buy_hts(unsigned uid, unsigned seq, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(m_data.user[uid].hts + 600 < Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Buy_hts");
	}

	int u = min(10u, (m_data.user[uid].hts + 600 - Time::GetGlobalTime())/60 + 1);

	CLogicUser logicUser;
	DataUser dataUser;
	CLogicPay logicPay;
	DataPay payData;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
	if(ret)
		return ret;
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);
	ret = logicPay.ProcessOrderForBackend(uid, -u, 0, payData, "CDataBraveNewWorld_Buy_hts",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	m_data.user[uid].hts = 0;

	result["coins2"] = payData.cash;
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::Buy_bts(unsigned uid, unsigned seq, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(m_data.user[uid].bts + 300 < Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Buy_bts");
	}

	int u = min(5u, (m_data.user[uid].bts + 300 - Time::GetGlobalTime())/60 + 1);
	CLogicUser logicUser;
	DataUser dataUser;
	CLogicPay logicPay;
	DataPay payData;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
	if(ret)
		return ret;
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);
	ret = logicPay.ProcessOrderForBackend(uid, -u, 0, payData, "CDataBraveNewWorld_Buy_bts",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	m_data.user[uid].bts = 0;

	result["coins2"] = payData.cash;
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::Buy_bt(unsigned uid, unsigned seq, unsigned count, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	int c = min(24u, m_data.user[uid].bt + (Time::GetGlobalTime() - m_data.user[uid].tts)/1800);
	if(c + count > 24)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_Buy_bt");
	}

	int u = 10 * count;
	CLogicUser logicUser;
	DataUser dataUser;
	CLogicPay logicPay;
	DataPay payData;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid,dataUser);
	if(ret)
		return ret;
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value user_flag;
	bool bsave = false;
	reader.parse(dataUser.user_flag,user_flag);
	ret = logicPay.ProcessOrderForBackend(uid, -u, 0, payData, "CDataBraveNewWorld_Buy_bt",user_flag,bsave);
	if(ret)
		return ret;
	result["pointpay"].resize(0);
	result["pointpay"] = user_flag["user_pay"];
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	m_data.user[uid].bt += count;

	result["coins2"] = payData.cash;
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}
int CDataBraveNewWorld::CollectOne(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	if(m_data.land[p].uid != uid)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_CollectOne_uid");
	}
	if(m_data.land[p].rts + 60 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_CollectOne_rts");
	}

	CLogicUser logicUser;
	DataUser dataUser;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUserLimit(uid,dataUser);
	if(ret)
		return ret;

	int m = getUserMoney(m_data.user[uid].lv), n = dataUser.type;
	n += min(300u, (Time::GetGlobalTime() - m_data.land[p].rts) / 60) * ConfigManager::Instance()->GetBraveNewWorldConfigPointProperty(p).product();
	m_data.land[p].rts = Time::GetGlobalTime();
	if(n >= m)
		n = m;
	int on = n - dataUser.type;
	dataUser.type = n;
	ret = logicUser.SetUserLimit(uid,dataUser);
	if(ret)
		return ret;

	RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",uid,on,dataUser.type);

	result["seq"] = ++m_data.user[uid].seq;
	result["bnwm"] = n;
	return 0;
}
int CDataBraveNewWorld::AttackSelf(unsigned uid, unsigned seq, BraveNewWorldPoint& p, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	//玩家
	if(m_data.land[p].uid != uid)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_AttackSelf_uid");
	}
	//cd
	if(m_data.user[uid].bts + 300 > Time::GetGlobalTime())
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_AttackSelf_bts");
	}
	//烽火令
	int c = 1;
	if((m_data.user[uid].bt + (Time::GetGlobalTime() - m_data.user[uid].tts)/1800) < c)
	{
		LOGIC_ERROR_RETURN_MSG("CDataBraveNewWorld_AttackSelf_bt");
	}

	m_data.user[uid].bt = min(24u, m_data.user[uid].bt + (Time::GetGlobalTime() - m_data.user[uid].tts)/1800) - c;
	m_data.user[uid].tts = Time::GetGlobalTime();
	m_data.user[uid].bts = Time::GetGlobalTime();

	int g = ConfigManager::Instance()->GetBraveNewWorldConfigPointProperty(p).occupy(), t = 0, lm = 0, nm = 0, lh = 0, nh = 0;
	if(g)
	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(uid)
		int ret = logicUser.GetUserLimit(uid,dataUser);
		if(ret)
			return ret;
		int on = dataUser.type;
		dataUser.type = min(getUserMoney(m_data.user[uid].lv), dataUser.type + g);
		on = dataUser.type - on;
		ret = logicUser.SetUserLimit(uid,dataUser);
		if(ret)
			return ret;

		RESOURCE_LOG("[bnwm][uid=%u,chg=%d,bnwm=%u]",uid,on,dataUser.type);

		if(m_data.user[uid].mission.m2 != e_DataBraveNewWorldMissionStat_got2)
			m_data.user[uid].mission.m2 += g;
	}

	unsigned mu = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().user();

	if(m_data.land[p].rc && m_data.user[uid].rl < mu)
	{
		unsigned c = min(mu - m_data.user[uid].rl, m_data.land[p].rc);
		m_data.user[uid].rl += c;
		CLogicEquipment loigcEquipment;
		loigcEquipment.AddOneItem(uid, BRAVE_NEW_WORLD_REWARD, c, "EndAttack", result["equip"], true);
		m_data.land[p].rc = 0;
	}

	//材料获得
	GetMaterial(uid, m_data.land[p], result);

	if(m_data.user[uid].mission.m3 == e_DataBraveNewWorldMissionStat_uncomplete
	&& m_data.user[uid].mission.mx == p.first
	&& m_data.user[uid].mission.my == p.second)
		m_data.user[uid].mission.m3 = e_DataBraveNewWorldMissionStat_complete;
	unsigned zid = getZoneID(p);
	if(m_data.alliance.count(m_data.user[uid].aid) && m_data.alliance[m_data.user[uid].aid].mission.count(zid))
	{
		if(m_data.alliance[m_data.user[uid].aid].mission[zid].m == false)
		{
			bool f = true;
			set<BraveNewWorldPoint> ps;
			getZonePoints(zid, ps);
			for(set<BraveNewWorldPoint>::iterator it=ps.begin();it!=ps.end();++it)
			{
				if(m_data.land[*it].uid == 0
				|| m_data.user[m_data.land[*it].uid].aid != m_data.user[uid].aid
				|| !m_data.city.count(*it)
				|| m_data.user[m_data.city[*it]].aid != m_data.user[uid].aid)
				{
					f = false;
					break;
				}
			}
			if(f)
				m_data.alliance[m_data.user[uid].aid].mission[zid].m = true;
		}
	}

	result["bt"] = m_data.user[uid].bt;
	result["tts"] = m_data.user[uid].tts;
	result["bts"] = m_data.user[uid].bts;
	m_data.user[uid].mission.GetJson(result);
	if(m_data.alliance.count(m_data.user[uid].aid))
		m_data.alliance[m_data.user[uid].aid].GetJson(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}

int CDataBraveNewWorld::GetMaterial(unsigned uid, DataBraveNewWorldPoint & point, Json::Value & result)
{
	if (point.mcount)
	{
		//材料获得
		try
		{
			ScrollActivityUnit scrollunit(uid);
			scrollunit.GainMaterial(point.mtype, point.mcount);

			result["btype"] = point.mtype;
			result["bcount"] = point.mcount;
		}
		catch(runtime_error & e)
		{
			error_log("%s", e.what());
		}

		point.mcount = 0;
		point.mtype = 0;
	}

	return 0;
}

int CDataBraveNewWorld::GetMission(unsigned uid, unsigned seq, unsigned type, Json::Value &result)
{
	if(!m_data.user.count(uid))
		return R_ERR_PARAM;
	if(seq != m_data.user[uid].seq)
		return R_ERR_PARAM;

	unsigned c = 0;
	switch(type)
	{
	case e_DataBraveNewWorldMissionType_move:
		if(m_data.user[uid].mission.m1 == e_DataBraveNewWorldMissionStat_complete)
		{
			m_data.user[uid].mission.m1 = e_DataBraveNewWorldMissionStat_got;
			c = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.mission().m1();
		}
		break;
	case e_DataBraveNewWorldMissionType_coin:
		if(m_data.user[uid].mission.m2 != e_DataBraveNewWorldMissionStat_got2
		&& m_data.user[uid].mission.m2 >= ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.mission().user2())
		{
			m_data.user[uid].mission.m2 = e_DataBraveNewWorldMissionStat_got2;
			c = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.mission().m2();
		}
		break;
	case e_DataBraveNewWorldMissionType_occupy:
		if(m_data.user[uid].mission.m3 == e_DataBraveNewWorldMissionStat_complete)
		{
			m_data.user[uid].mission.m3 = e_DataBraveNewWorldMissionStat_got;
			c = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.mission().m3();
		}
		break;
	default:
		break;
	}
	if(c == 0)
		return R_ERR_LOGIC;

	CLogicEquipment().AddOneItem(uid, BRAVE_NEW_WORLD_USER_REWARD, c, "GetMission", result["equip"], true);

	m_data.user[uid].mission.GetJson(result);
	result["seq"] = ++m_data.user[uid].seq;
	return 0;
}

void CDataBraveNewWorld::OnDay()
{
	for(map<unsigned int, DataBraveNewWorldUser>::iterator it=m_data.user.begin();it!=m_data.user.end();++it)
	{
		it->second.rl = 0;
		it->second.RandMission();
	}

	CLogicAlliance logicAlliance;
	for(map<unsigned int, DataBraveNewWorldAlliance>::iterator it=m_data.alliance.begin();it!=m_data.alliance.end();++it)
	{
		try
		{
			unsigned c = 0;
			for(map<unsigned int, DataBraveNewWorldAllianceMission>::iterator iter=it->second.mission.begin();iter!=it->second.mission.end();++iter)
			{
				if(iter->second.m)
					++c;
			}
			if(c)
				c = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.mission().alliance(c-1);
			logicAlliance.ChangeResource(it->second.aid, 0, 0, 0, 0, c, 0, "BraveNewWorld");
		}
		catch(const std::exception& e)
		{}
		it->second.RandMission();
	}

	map<unsigned, vector<BraveNewWorldPoint> > points;
	set<BraveNewWorldPoint> del;
	for(map<BraveNewWorldPoint, DataBraveNewWorldPoint>::iterator it=m_data.land.begin();it!=m_data.land.end();++it)
	{
		try
		{
			it->second.rc = 0;
			unsigned type = ConfigManager::Instance()->GetBraveNewWorldConfigPoint(it->first).type();
			if(type == e_DataBraveNewWorldPointType_empty)
				points[(unsigned)ConfigManager::Instance()->GetBraveNewWorldConfigPoint(it->first).level()].push_back(it->first);
		}
		catch(const std::exception& e)
		{
			del.insert(it->first);
		}
	}
	for(set<BraveNewWorldPoint>::iterator it=del.begin();it!=del.end();++it)
		m_data.land.erase(*it);

	for(map<unsigned, vector<BraveNewWorldPoint> >::iterator it=points.begin();it!=points.end();++it)
	{
		if(it->first > ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().all_size()
		|| it->first > ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().one_size()
		|| it->first == 0)
			continue;
		unsigned m = min((unsigned)ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().all(it->first - 1), (unsigned)it->second.size());
		unsigned c = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().one(it->first - 1);
		random_shuffle(it->second.begin(), it->second.end());
		for(int i=0;i<m;++i)
			m_data.land[it->second[i]].rc = c;
	}

	Save();
}
void CDataBraveNewWorld::OnHour()
{
	map<unsigned, unsigned> s;
	map<unsigned, vector<BraveNewWorldPoint> > points;
	set<BraveNewWorldPoint> del;
	for(map<BraveNewWorldPoint, DataBraveNewWorldPoint>::iterator it=m_data.land.begin();it!=m_data.land.end();++it)
	{
		try
		{
			if(it->second.fid && it->second.fts + BNW_ATTACK_MAX_TIME > Time::GetGlobalTime())
				continue;

			unsigned l = ConfigManager::Instance()->GetBraveNewWorldConfigPoint(it->first).level();
			if(it->second.rc)
				++s[l];
			it->second.rc = 0;
			unsigned type = ConfigManager::Instance()->GetBraveNewWorldConfigPoint(it->first).type();
			if(type == e_DataBraveNewWorldPointType_empty)
				points[l].push_back(it->first);
		}
		catch(const std::exception& e)
		{
			del.insert(it->first);
		}
	}
	for(set<BraveNewWorldPoint>::iterator it=del.begin();it!=del.end();++it)
		m_data.land.erase(*it);

	for(map<unsigned, vector<BraveNewWorldPoint> >::iterator it=points.begin();it!=points.end();++it)
	{
		if(it->first > ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().all_size()
		|| it->first > ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().one_size()
		|| it->first == 0)
			continue;
		unsigned m = min(s[it->first], (unsigned)it->second.size());
		unsigned c = ConfigManager::Instance()->m_BraveNewWorldConfig.m_config.reward().one(it->first - 1);
		random_shuffle(it->second.begin(), it->second.end());
		for(int i=0;i<m;++i)
			m_data.land[it->second[i]].rc = c;
	}

	Save();
}

void CDataBraveNewWorld::OnHalfHour()
{
	//如果活动未开启，则不做处理
	ActInfoConfig actconfig(CONFIG_SCROLL_ACTIVITY);

	bool isactive = actconfig.IsActive();

	if (!isactive)
	{
		return ;
	}

	map<unsigned, vector<BraveNewWorldPoint> > points;
	set<BraveNewWorldPoint> del;

	int mtype = (m_material_type++)%3 + 1;

	for(map<BraveNewWorldPoint, DataBraveNewWorldPoint>::iterator it = m_data.land.begin();it != m_data.land.end(); ++it)
	{
		try
		{
			unsigned level = ConfigManager::Instance()->GetBraveNewWorldConfigPoint(it->first).level();

			//排除有古卷奇书的地块
			if(it->second.rc)
			{
				continue;
			}

			//todo 清除已经有ABC材料的地块
			if (it->second.mtype || it->second.mcount)
			{
				it->second.mtype = 0;
				it->second.mcount = 0;
			}

			unsigned type = ConfigManager::Instance()->GetBraveNewWorldConfigPoint(it->first).type();

			//在空闲地块或资源点上刷新材料
			if(type == e_DataBraveNewWorldPointType_empty || type == e_DataBraveNewWorldPointType_resource)
				points[level].push_back(it->first);
		}
		catch(const std::exception& e)
		{
			del.insert(it->first);
		}
	}

	for(set<BraveNewWorldPoint>::iterator it=del.begin();it!=del.end();++it)
		m_data.land.erase(*it);

	ScrollActivityConfigWrap scrollcfg;

	for(map<unsigned, vector<BraveNewWorldPoint> >::iterator it = points.begin(); it != points.end(); ++it)
	{
		//获取最大地块数
		unsigned max_landnum = scrollcfg.GetLandNum(mtype, it->first);
		unsigned max_matrialnum = scrollcfg.GetMaterialNum(mtype, it->first);

		//排除配置问题导致的一些异常数据
		if( 0 == max_landnum || 0 == max_matrialnum)
			continue;

		random_shuffle(it->second.begin(), it->second.end());

		//不同等级的地块数量
		for(int i = 0; i < max_landnum; ++i)
		{
			m_data.land[it->second[i]].mtype = mtype;
			m_data.land[it->second[i]].mcount = max_matrialnum;
		}
	}
}
