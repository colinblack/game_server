/*
 * DataNewWorldAllianceMap.cpp
 *
 *  Created on: 2015-12-22
 *      Author: Ralf
 */

#include "DataNewWorldAllianceMap.h"
#include <fstream>
#include <iostream>


CDataNewWorldAllianceMap::CDataNewWorldAllianceMap(string path)
	: DataBase(path)
{
	m_msg = new NewWorldAllianceMap::NewWorldAllianceMap();
}
int CDataNewWorldAllianceMap::Init()
{
	int ret = Parse();
	if(ret)
		return ret;

	m_data.Parse(*(NewWorldAllianceMap::NewWorldAllianceMap *)m_msg);

	((NewWorldAllianceMap::NewWorldAllianceMap *)m_msg)->Clear();

	return 0;
}
int CDataNewWorldAllianceMap::Save()
{
	m_data.Serialize((NewWorldAllianceMap::NewWorldAllianceMap *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	//debug_log("%s",m_msg->DebugString().c_str());

	((NewWorldAllianceMap::NewWorldAllianceMap *)m_msg)->Clear();

	return 0;
}
int CDataNewWorldAllianceMap::Sig(int sig)
{
	if(sig == SIGRTMIN)
		Restart();

	return 0;
}
int CDataNewWorldAllianceMap::GetRoom(unsigned aid, unsigned &rid, unsigned &level, unsigned &reward)
{
	if(!IsAllianceId(aid))
		return R_ERR_PARAM;

	return m_data.GetRoom(aid, rid, level, reward);
}
int CDataNewWorldAllianceMap::Restart()
{
	vector<DataGVGARM> vec;
	string dataPath = MainConfig::GetAllServerPath("data/ascore");
	ifstream fin(dataPath.c_str());
	if (!fin.good()) {
		error_log("load %s fail", dataPath.c_str());
		m_data.Restart(vec);
		return 0;
	}

	while (!fin.eof() && fin.good()) {
		DataGVGARM temp;
		fin >> temp.aid >> temp.score >> temp.count >> temp.level;
		if(IsAllianceId(temp.aid))
			vec.push_back(temp);
	}

	m_data.Restart(vec);
	Save();
	return 0;
}

const map<unsigned int, DataNewWorldAllianceMapAlliance>& CDataNewWorldAllianceMap::GetAll()
{
	return m_data.alliance;
}

static bool DataGVGARMCompare(const DataGVGARM &left, const DataGVGARM &right)
{
	return left.score > right.score;
}
void DataNewWorldAllianceMap::Restart(vector<DataGVGARM> &vec)
{
	alliance.clear();
	sort(vec.begin(),vec.end(),DataGVGARMCompare);
	unsigned s = vec.size();
	unsigned r = s / NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE;
	unsigned y = s % NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE;
	unsigned rid = 1;
	unsigned rmax = r + (y ? 1 : 0);
	for(unsigned i=0;i<r;++i)
	{
		float level = 0.0f, count = 0.0f;
		alliance[rid].rid = rid;
		for(unsigned j=0;j<NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE;++j)
		{
			alliance[rid].aid.push_back(vec[i * NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE + j].aid);
			level += vec[i * NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE + j].level;
			count += vec[i * NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE + j].count;
		}
		alliance[rid].level = (unsigned)ceil(pow(level/count, 0.5f));
		alliance[rid].reward = (rid - 1) * NEW_WORLD_ALLIANCE_MAP_REWARD_NUM / rmax;
		++rid;
	}
	if(y)
	{
		float level = 0.0f, count = 0.0f;
		alliance[rid].rid = rid;
		for(unsigned j=0;j<y;++j)
		{
			alliance[rid].aid.push_back(vec[r * NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE + j].aid);
			level += vec[r * NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE + j].level;
			count += vec[r * NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE + j].count;
		}
		alliance[rid].level = (unsigned)ceil(pow(level/count, 0.5f));
		alliance[rid].reward = (rid - 1) * NEW_WORLD_ALLIANCE_MAP_REWARD_NUM / rmax;
	}
	BuildAidMap();
}
