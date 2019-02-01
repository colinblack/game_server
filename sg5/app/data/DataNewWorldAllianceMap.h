/*
 * DataNewWorldAllianceMap.h
 *
 *  Created on: 2015-12-22
 *      Author: Ralf
 */

#ifndef DATANEW_WORLD_ALLIANCEMAP_H_
#define DATANEW_WORLD_ALLIANCEMAP_H_

#include "Kernel.h"
#include <math.h>
#include "DataBase.h"
#include "NewWorldAllianceMap.pb.h"

#define NEW_WORLD_ALLIANCE_MAP_ROOM_ALLIANCE 3
#define NEW_WORLD_ALLIANCE_MAP_ROOM_BALANCE 10
#define NEW_WORLD_ALLIANCE_MAP_REWARD_NUM 6

struct DataGVGARM {
	unsigned aid,score,level,count;
	DataGVGARM() {
		aid = score = count = level = 0;
	}
};
/************************************************************************************/
class DataNewWorldAllianceMapAlliance {
public:
	unsigned int rid;
	unsigned int level;
	unsigned int reward;
	vector<unsigned int> aid;
	DataNewWorldAllianceMapAlliance() {
		rid = 0;
		level = 0;
		reward = 0;
	}
	~DataNewWorldAllianceMapAlliance() {
	}
	void Serialize(NewWorldAllianceMap::NewWorldAllianceMapAlliance *p) {
		p->set_rid(rid);
		p->set_level(level);
		p->set_reward(reward);
		for (vector<unsigned int>::iterator it = aid.begin(); it != aid.end();
				++it)
			p->add_aid(*it);
	}
	void Parse(const NewWorldAllianceMap::NewWorldAllianceMapAlliance &p) {
		rid = p.rid();
		level = p.level();
		reward = p.reward();
		for (int i = 0; i < p.aid_size(); ++i)
			aid.push_back(p.aid(i));
	}
};
class DataNewWorldAllianceMap {
public:
	map<unsigned int, DataNewWorldAllianceMapAlliance> alliance;
	map<unsigned, unsigned> aidmap;
	DataNewWorldAllianceMap() {
	}
	~DataNewWorldAllianceMap() {
	}
	void BuildAidMap()
	{
		aidmap.clear();
		for(map<unsigned, DataNewWorldAllianceMapAlliance>::iterator it=alliance.begin();it!=alliance.end();++it)
		{
			for(vector<unsigned int>::iterator iter = it->second.aid.begin(); iter != it->second.aid.end();++iter)
			{
				if(IsAllianceId(*iter))
					aidmap[*iter] = it->first;
			}
		}
	}
	void Serialize(NewWorldAllianceMap::NewWorldAllianceMap *p) {
		for (map<unsigned int, DataNewWorldAllianceMapAlliance>::iterator it =
				alliance.begin(); it != alliance.end(); ++it)
			it->second.Serialize(p->add_alliance());
	}
	void Parse(const NewWorldAllianceMap::NewWorldAllianceMap &p) {
		for (int i = 0; i < p.alliance_size(); ++i)
			alliance[p.alliance(i).rid()].Parse(p.alliance(i));

		BuildAidMap();
	}
	int GetRoom(unsigned aid, unsigned &rid, unsigned &level, unsigned &reward)
	{
		if(!aidmap.count(aid))
			return R_ERR_LOGIC;
		rid = aidmap[aid];
		level = alliance[rid].level;
		reward = alliance[rid].reward;
		return 0;
	}
	void Restart(vector<DataGVGARM> &vec);
};
/************************************************************************************/
class CDataNewWorldAllianceMap : public DataBase
{
public:
	CDataNewWorldAllianceMap(string path);
	virtual ~CDataNewWorldAllianceMap(){}
	int Init();
	int Save();
	int Sig(int sig);
	int GetRoom(unsigned aid, unsigned &rid, unsigned &level, unsigned &reward);
	int Restart();
	const map<unsigned int, DataNewWorldAllianceMapAlliance>& GetAll();

private:
	DataNewWorldAllianceMap m_data;
};

#endif /* DATAGVGMAP_H_ */
