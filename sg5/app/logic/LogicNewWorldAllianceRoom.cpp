/*
 * LogicNewWorldAllianceRoom.cpp
 *
 *  Created on: 2014-9-18
 *      Author: Ralf
 */

#include "LogicNewWorldAllianceRoom.h"

#define NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult) \
	NewWorldAllianceRoomChangeMap *change; \
	if(pData->GetChangeMap(rid, change) == 0) \
	{ \
		if(!change->empty()) \
		{ \
			unsigned i = 0; \
			allresult["change"].resize(change->size()); \
			for(NewWorldAllianceRoomChangeMap::const_iterator it=change->begin();it!=change->end();++it) \
			{ \
				allresult["change"][i].resize(3u); \
				allresult["change"][i][0u] = it->second.cid; \
				allresult["change"][i][1u] = it->second.aid; \
				allresult["change"][i][2u] = it->second.battle; \
				++i; \
			} \
			pData->ClearChangeMap(rid); \
		} \
	} \

CLogicNewWorldAllianceRoom::CLogicNewWorldAllianceRoom() {
	// TODO Auto-generated constructor stub

}
CLogicNewWorldAllianceRoom::~CLogicNewWorldAllianceRoom() {
	// TODO Auto-generated destructor stub
}

int CLogicNewWorldAllianceRoom::GetWorld(unsigned rid, Json::Value &allresult)
{
	Json::Value &result = allresult["GetWorld"];

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	result.resize(NEW_WORLD_ALLIANCE_ROOM_CITY);
	unsigned i = 0;
	NewWorldAllianceRoomCityMap *world;
	int ret = pData->GetWorld(rid, world);
	if(ret)
		return ret;
	for(NewWorldAllianceRoomCityMap::const_iterator it=world->begin();it!=world->end();++it)
	{
		result[i]["id"]		 = it->second.cid;
		result[i]["aid"] = it->second.aid;
		result[i]["status"]	 = it->second.Fighting() ? 1 : 0;
		result[i]["tower"]["uid"] = it->second.tower.uid;
		result[i]["tower"]["dps"] = it->second.tower.dps;
		result[i]["tower"]["hit"] = it->second.tower.hit;
		++i;
	}

	allresult["GetAID"].resize(0);
	vector<unsigned int> *aid;
	ret = pData->GetAID(rid, aid);
	if(ret)
		return ret;
	for(vector<unsigned int>::const_iterator it=aid->begin();it!=aid->end();++it)
		allresult["GetAID"].append(*it);

	allresult["Result"].resize(0);
	NewWorldAllianceRoomResult *res;
	ret = pData->GetResult(rid, res);
	if(ret)
		return ret;
	for(NewWorldAllianceRoomResult::const_iterator it=res->begin();it!=res->end();++it)
	{
		Json::Value temp;
		temp["aid"] = it->second;
		temp["city"] = it->first.first;
		temp["kill"] = it->first.second;
		allresult["Result"].append(temp);
	}

	allresult["Kill"].resize(0);
	NewWorldAllianceRoomKill *kill;
	ret = pData->GetKill(rid, kill);
	if(ret)
		return ret;
	for(NewWorldAllianceRoomKill::const_iterator it=kill->begin();it!=kill->end();++it)
	{
		Json::Value t;
		t["aid"] = it->first;
		t["kill"].resize(0);
		for(map<unsigned, unsigned>::const_iterator iter=it->second.begin();iter!=it->second.end();++iter)
		{
			Json::Value temp;
			temp["uid"] = iter->first;
			temp["kill"] = iter->second;
			t["kill"].append(temp);
		}
		allresult["Kill"].append(t);
	}

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::GetCity(unsigned rid, unsigned cid, Json::Value &allresult)
{
	Json::Value &result = allresult["GetCity"];

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	DataNewWorldAllianceRoomCity *city;
	int ret = pData->GetCity(rid, cid, city);
	if(ret)
		return ret;

	result["id"]		 = city->cid;
	result["aid"]	 = city->aid;
	result["battle"][0u] = city->count[0];
	result["battle"][1u] = city->count[1];
	result["battle"][2u] = city->count[2];
	result["battle"][3u] = city->countN;
	result["npcts"]		 = city->npcts;
	result["status"]	 = city->Fighting() ? 1 : 0;
	result["tower"]["uid"] = city->tower.uid;
	result["tower"]["dps"] = city->tower.dps;
	result["tower"]["hit"] = city->tower.hit;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::GetBattle(unsigned rid, unsigned cid, Json::Value &allresult)
{
	Json::Value &result = allresult["GetBattle"];

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	DataNewWorldAllianceRoomCity *city;
	int ret = pData->GetCity(rid, cid, city);
	if(ret)
		return ret;

	result["upts"] = pData->GetTS(rid) + NEW_WORLD_ALLIANCE_ROOM_TICK;
	result["battle"][0u] = city->count[0];
	result["battle"][1u] = city->count[1];
	result["battle"][2u] = city->count[2];
	result["battle"][3u] = city->countN;
	result["aid"]	 = city->aid;
	result["status"]	 = city->Fighting() ? 1 : 0;
	result["tower"]["uid"] = city->tower.uid;
	result["tower"]["dps"] = city->tower.dps;
	result["tower"]["hit"] = city->tower.hit;

	if(city->attacker.size())
	{
		NewWorldAllianceCityQueue::const_iterator it = city->attacker.begin();
		DataNewWorldAllianceRoomHero *hero;
		if(CDataNewWorldAllianceRoom::notHero(it->second))
			hero = &city->vision.find(it->second)->second;
		else
		{
			ret = pData->GetHero(rid, it->second, hero);
			if(ret)
				return ret;
		}
		result["attacker1"]["vision"] = CDataNewWorldAllianceRoom::notHero(it->second)?1:0;
		result["attacker1"]["uid"]	 = hero->index.uid;
		result["attacker1"]["index"]	 = hero->index.index;
		result["attacker1"]["job"]	 = hero->getJob();
		result["attacker1"]["type"]	 = hero->getType();
		result["attacker1"]["heroID"] = CDataXML::Hero2Str(hero->hid);
		result["attacker1"]["name"]	 = hero->name;
		result["attacker1"]["aid"]= hero->aid;
		result["attacker1"]["level"]	 = hero->level;
		result["attacker1"]["hp"]	 = hero->hp;
		result["attacker1"]["buff"]	 = hero->buff;
		result["attacker1"]["property"].resize(NewWorldAllianceRoomProperty_max);
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			result["attacker1"]["property"][i] = hero->property[i];
	}
	if(city->defender.size() || city->countN)
	{
		NewWorldAllianceCityQueue::const_iterator it = city->defender.begin();
		DataNewWorldAllianceRoomHero *hero;
		if(city->defender.empty())
			hero = &city->npc.begin()->second;
		else if(CDataNewWorldAllianceRoom::notHero(it->second))
			hero = &city->vision.find(it->second)->second;
		else
		{
			ret = pData->GetHero(rid, it->second, hero);
			if(ret)
				return ret;
		}
		result["defender1"]["vision"] = city->defender.empty()?0:(CDataNewWorldAllianceRoom::notHero(it->second)?1:0);
		result["defender1"]["uid"]	 = hero->index.uid;
		result["defender1"]["index"]	 = hero->index.index;
		result["defender1"]["job"]	 = hero->getJob();
		result["defender1"]["type"]	 = hero->getType();
		result["defender1"]["heroID"] = CDataXML::Hero2Str(hero->hid);
		result["defender1"]["name"]	 = hero->name;
		result["defender1"]["aid"]= hero->aid;
		result["defender1"]["level"]	 = hero->level;
		result["defender1"]["hp"]	 = hero->hp;
		result["defender1"]["buff"]	 = hero->buff;
		result["defender1"]["property"].resize(NewWorldAllianceRoomProperty_max);
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			result["defender1"]["property"][i] = hero->property[i];
	}
	if(city->attacker.size() > 1)
	{
		NewWorldAllianceCityQueue::const_iterator it = city->attacker.begin();
		++it;
		DataNewWorldAllianceRoomHero *hero;
		if(CDataNewWorldAllianceRoom::notHero(it->second))
			hero = &city->vision.find(it->second)->second;
		else
		{
			ret = pData->GetHero(rid, it->second, hero);
			if(ret)
				return ret;
		}
		result["attacker2"]["vision"] = CDataNewWorldAllianceRoom::notHero(it->second)?1:0;
		result["attacker2"]["uid"]	 = hero->index.uid;
		result["attacker2"]["index"]	 = hero->index.index;
		result["attacker2"]["job"]	 = hero->getJob();
		result["attacker2"]["type"]	 = hero->getType();
		result["attacker2"]["heroID"] = CDataXML::Hero2Str(hero->hid);
		result["attacker2"]["name"]	 = hero->name;
		result["attacker2"]["aid"]= hero->aid;
		result["attacker2"]["level"]	 = hero->level;
		result["attacker2"]["hp"]	 = hero->hp;
		result["attacker2"]["buff"]	 = hero->buff;
		result["attacker2"]["property"].resize(NewWorldAllianceRoomProperty_max);
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			result["attacker2"]["property"][i] = hero->property[i];
	}
	if(city->defender.size() > 1)
	{
		NewWorldAllianceCityQueue::const_iterator it = city->defender.begin();
		++it;
		DataNewWorldAllianceRoomHero *hero;
		if(CDataNewWorldAllianceRoom::notHero(it->second))
			hero = &city->vision.find(it->second)->second;
		else
		{
			ret = pData->GetHero(rid, it->second, hero);
			if(ret)
				return ret;
		}
		result["defender2"]["vision"] = CDataNewWorldAllianceRoom::notHero(it->second)?1:0;
		result["defender2"]["uid"]	 = hero->index.uid;
		result["defender2"]["index"]	 = hero->index.index;
		result["defender2"]["job"]	 = hero->getJob();
		result["defender2"]["type"]	 = hero->getType();
		result["defender2"]["heroID"] = CDataXML::Hero2Str(hero->hid);
		result["defender2"]["name"]	 = hero->name;
		result["defender2"]["aid"]= hero->aid;
		result["defender2"]["level"]	 = hero->level;
		result["defender2"]["hp"]	 = hero->hp;
		result["defender2"]["buff"]	 = hero->buff;
		result["defender2"]["property"].resize(NewWorldAllianceRoomProperty_max);
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			result["defender2"]["property"][i] = hero->property[i];
	}
	if(city->attacker.size() > 2)
	{
		NewWorldAllianceCityQueue::const_iterator it = city->attacker.begin();
		++it;
		++it;
		DataNewWorldAllianceRoomHero *hero;
		if(CDataNewWorldAllianceRoom::notHero(it->second))
			hero = &city->vision.find(it->second)->second;
		else
		{
			ret = pData->GetHero(rid, it->second, hero);
			if(ret)
				return ret;
		}
		result["attacker3"]["vision"] = CDataNewWorldAllianceRoom::notHero(it->second)?1:0;
		result["attacker3"]["uid"]	 = hero->index.uid;
		result["attacker3"]["index"]	 = hero->index.index;
		result["attacker3"]["job"]	 = hero->getJob();
		result["attacker3"]["type"]	 = hero->getType();
		result["attacker3"]["heroID"] = CDataXML::Hero2Str(hero->hid);
		result["attacker3"]["name"]	 = hero->name;
		result["attacker3"]["aid"]= hero->aid;
		result["attacker3"]["level"]	 = hero->level;
		result["attacker3"]["hp"]	 = hero->hp;
		result["attacker3"]["buff"]	 = hero->buff;
		result["attacker3"]["property"].resize(NewWorldAllianceRoomProperty_max);
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			result["attacker3"]["property"][i] = hero->property[i];
	}
	if(city->defender.size() > 2)
	{
		NewWorldAllianceCityQueue::const_iterator it = city->defender.begin();
		++it;
		++it;
		DataNewWorldAllianceRoomHero *hero;
		if(CDataNewWorldAllianceRoom::notHero(it->second))
			hero = &city->vision.find(it->second)->second;
		else
		{
			ret = pData->GetHero(rid, it->second, hero);
			if(ret)
				return ret;
		}
		result["defender3"]["vision"] = CDataNewWorldAllianceRoom::notHero(it->second)?1:0;
		result["defender3"]["uid"]	 = hero->index.uid;
		result["defender3"]["index"]	 = hero->index.index;
		result["defender3"]["job"]	 = hero->getJob();
		result["defender3"]["type"]	 = hero->getType();
		result["defender3"]["heroID"] = CDataXML::Hero2Str(hero->hid);
		result["defender3"]["name"]	 = hero->name;
		result["defender3"]["aid"]= hero->aid;
		result["defender3"]["level"]	 = hero->level;
		result["defender3"]["hp"]	 = hero->hp;
		result["defender3"]["buff"]	 = hero->buff;
		result["defender3"]["property"].resize(NewWorldAllianceRoomProperty_max);
		for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
			result["defender3"]["property"][i] = hero->property[i];
	}

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::GetBattleList(unsigned rid, unsigned cid, unsigned camp, Json::Value &allresult)
{
	Json::Value &result = allresult["GetBattleList"];

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	DataNewWorldAllianceRoomCity *city;
	int ret = pData->GetCity(rid, cid, city);
	if(ret)
		return ret;

	result.resize(0);
	const NewWorldAllianceCityQueue &list = camp?city->attacker:city->defender;
	for(NewWorldAllianceCityQueue::const_iterator it=list.begin();it!=list.end();++it)
	{
		Json::Value temp;
		if(CDataNewWorldAllianceRoom::notHero(it->second))
		{
			const DataNewWorldAllianceRoomHero &hero = city->vision.find(it->second)->second;
			temp["vision"]		 = 1;
			temp["heroID"]		 = CDataXML::Hero2Str(hero.hid);
			temp["aid"]		 = hero.aid;
			temp["name"]		 = hero.name;
			temp["index"]		 = hero.index.index;
			temp["hp"]			 = hero.hp;
			temp["maxhp"]		 = hero.property[NewWorldAllianceRoomProperty_hp];
		}
		else
		{
			DataNewWorldAllianceRoomHero *hero;
			ret = pData->GetHero(rid, it->second, hero);
			if(ret)
				return ret;
			temp["vision"]		 = 0;
			temp["heroID"]		 = CDataXML::Hero2Str(hero->hid);
			temp["aid"]		 = hero->aid;
			temp["name"]		 = hero->name;
			temp["index"]		 = hero->index.index;
			temp["hp"]			 = hero->hp;
			temp["maxhp"]		 = hero->property[NewWorldAllianceRoomProperty_hp];
		}

		result.append(temp);
	}

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::GetHero(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult)
{
	Json::Value &result = allresult["GetHero"];

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	DataNewWorldAllianceRoomHeroIndex heroindex(uid, index);
	DataNewWorldAllianceRoomHero *hero;
	int ret = pData->GetHero(rid, heroindex, hero);
	if(ret)
		return ret;

	result["uid"]		 = hero->index.uid;
	result["index"]		 = hero->index.index;
	result["heroId"]	 = CDataXML::Hero2Str(hero->hid);
	result["job"]	 	 = hero->getJob();
	result["type"]	 	 = hero->getType();
	result["level"]	 	 = hero->level;
	result["aid"]	 = hero->aid;
	result["cid"]	 	 = hero->cid;
	result["hp"]	 	 = hero->hp;
	result["mts"]	 = hero->mts;
	result["property"].resize(NewWorldAllianceRoomProperty_max);
	for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
		result["property"][i] = hero->property[i];
	result["kill"]	 = hero->kill;
	result["seq"]	 = hero->seq;
	result["buff"]	 = hero->buff;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::GetAllHero(unsigned rid, unsigned uid,Json::Value &allresult)
{
	Json::Value &result = allresult["GetAllHero"];

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	result.resize(0);
	NewWorldAllianceRoomHeroMap *heromap;
	int ret = pData->GetAllHero(rid, heromap);
	if(ret)
		return ret;
	for(unsigned i=0;i<NEW_WORLD_ALLIANCE_ROOM_HERO_INDEX;++i)
	{
		DataNewWorldAllianceRoomHeroIndex index(uid,i);
		NewWorldAllianceRoomHeroMap::const_iterator hero = heromap->find(index);
		if(hero != heromap->end())
		{
			Json::Value temp;
			temp["uid"]		 = hero->second.index.uid;
			temp["index"]	 = hero->second.index.index;
			temp["heroId"]	 = CDataXML::Hero2Str(hero->second.hid);
			temp["job"]	 	 = hero->second.getJob();
			temp["type"]	 = hero->second.getType();
			temp["level"]	 = hero->second.level;
			temp["aid"]	 = hero->second.aid;
			temp["cid"]	 	 = hero->second.cid;
			temp["hp"]	 	 = hero->second.hp;
			temp["mts"]	 = hero->second.mts;
			temp["property"].resize(NewWorldAllianceRoomProperty_max);
			for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
				temp["property"][i] = hero->second.property[i];
			temp["kill"]	 = hero->second.kill;
			temp["seq"]	 = hero->second.seq;
			temp["buff"]	 = hero->second.buff;
			result.append(temp);
		}
	}

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::SetHero(unsigned rid, unsigned uid, unsigned index, const Json::Value &para, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["SetHero"];

	int ret = 0;
	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	unsigned aid = 0;
	Json::GetUInt(para, "aid", aid);
	unsigned level = 0;
	Json::GetUInt(para, "level", level);
	unsigned job = 0;
	Json::GetUInt(para, "job", job);
	string name, heroid;
	Json::GetString(para, "name", name);
	Json::GetString(para, "heroId", heroid);

	DataNewWorldAllianceRoomHero hero;
	hero.index.uid		= uid;
	hero.index.index	= index;
	hero.aid		= aid;
	hero.level			= level;
	hero.job			= (job - 1)%NewWorldAllianceRoomHeroJob_max;

	if(!heroid.empty())
		hero.hid		= CDataXML::Str2Hero(heroid);
	if(!name.empty())
		strncpy(hero.name, name.c_str(), sizeof(hero.name)-1);
	if(para.isMember("property") && para["property"].isArray() && para["property"].size() <= NewWorldAllianceRoomProperty_max)
	{
		for(unsigned i=0;i<para["property"].size();++i)
			hero.property[i] = para["property"][i].asUInt();
	}

	ret = pData->SetHero(rid, hero, seq);
	if(ret)
	{
		error_log("SetHero fail, uid=%u, index=%u, ret=%u",hero.index.uid, hero.index.index, ret);
		return ret;
	}

	result["uid"]		 = hero.index.uid;
	result["index"]	 = hero.index.index;
	result["heroId"]	 = CDataXML::Hero2Str(hero.hid);
	result["job"]	 	 = hero.getJob();
	result["type"]	 = hero.getType();
	result["level"]	 = hero.level;
	result["aid"]	 = hero.aid;
	result["cid"]	 	 = hero.cid;
	result["hp"]	 	 = hero.hp;
	result["mts"]	 = hero.mts;
	result["property"].resize(NewWorldAllianceRoomProperty_max);
	for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
		result["property"][i] = hero.property[i];
	result["seq"]	 = seq;
	result["kill"]	 = hero.kill;
	result["buff"]	 = hero.buff;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldAllianceRoom::Move(unsigned rid, unsigned uid, unsigned index, unsigned cid, bool leave, unsigned fly, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["Move"];

	int ret = 0;
	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	unsigned mts;
	ret = pData->Move(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), cid, leave, fly, mts, seq);
	result["mts"] = mts;
	if(ret)
	{
		if(ret != R_ERR_LOGIC)
			error_log("Move fail, uid=%u, index=%u, cid=%u, ret=%u",uid, index, cid, ret);
		return ret;
	}

	result["upts"] = pData->GetTS(rid) + NEW_WORLD_ALLIANCE_ROOM_TICK * 2;
	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::Change(unsigned rid, unsigned uid, unsigned index, unsigned type, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["Change"];
	int ret = 0;
	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	ret = pData->Change(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), type, seq);
	if(ret)
	{
		error_log("Change fail, uid=%u, index=%u, type=%u, ret=%u",uid, index, type, ret);
		return ret;
	}
	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::Clone(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["Clone"];
	int ret = 0;

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	ret = pData->Clone(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), seq);
	if(ret)
	{
		error_log("Clone fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}
	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::Recover(unsigned rid, unsigned uid, unsigned index, unsigned num, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["Recover"];
	int ret = 0;

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	ret = pData->Recover(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), num, seq);
	if(ret)
	{
		error_log("Recover fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}
	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::Explode(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["Explode"];
	int ret = 0;

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	ret = pData->Explode(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), seq);
	if(ret)
	{
		error_log("Explode fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}
	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldAllianceRoom::Rush(unsigned rid, unsigned uid, unsigned index, bool fly, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["Rush"];

	int ret = 0;

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	DataNewWorldAllianceRoomHero other, end;
	ret = pData->Rush(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), other, end, seq);
	if(ret)
		return ret;

	result["other"]["vision"] = CDataNewWorldAllianceRoom::notHero(other.index)?1:0;
	result["other"]["uid"]	 = other.index.uid;
	result["other"]["index"]	 = other.index.index;
	result["other"]["job"]	 = other.getJob();
	result["other"]["type"]	 = other.getType();
	result["other"]["heroID"] = CDataXML::Hero2Str(other.hid);
	result["other"]["name"]	 = other.name;
	result["other"]["aid"]= other.aid;
	result["other"]["level"]	 = other.level;
	result["other"]["hp"]	 = other.hp;
	result["other"]["buff"]	 = other.buff;
	result["other"]["property"].resize(NewWorldAllianceRoomProperty_max);
	for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
		result["other"]["property"][i] = other.property[i];

	result["end"]["vision"] = CDataNewWorldAllianceRoom::notHero(end.index)?1:0;
	result["end"]["uid"]	 = end.index.uid;
	result["end"]["index"]	 = end.index.index;
	result["end"]["job"]	 = end.getJob();
	result["end"]["type"]	 = end.getType();
	result["end"]["heroID"] = CDataXML::Hero2Str(end.hid);
	result["end"]["name"]	 = end.name;
	result["end"]["aid"]= end.aid;
	result["end"]["level"]	= end.level;
	result["end"]["hp"]	 = end.hp;
	result["end"]["buff"]	 = end.buff;
	result["end"]["property"].resize(NewWorldAllianceRoomProperty_max);
	for(unsigned i=0;i<NewWorldAllianceRoomProperty_max;++i)
		result["end"]["property"][i] = end.property[i];

	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldAllianceRoom::CollectOther(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["CollectOther"];
	int ret = 0;

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	ret = pData->CollectOther(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), seq);

	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}


int CLogicNewWorldAllianceRoom::Blink(unsigned rid, unsigned uid, unsigned cid, const Json::Value &freeHeroIndex, Json::Value &allresult, const Json::Value &seq)
{
	Json::Value &result = allresult["Blink"];
	int ret = 0;

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData failed");
		return R_ERR_DATA;
	}

	unsigned heroIndex;
	unsigned mts, sq;
	unsigned i;

	for (i = 0; i < freeHeroIndex.size(); ++i)
	{
		heroIndex = freeHeroIndex[i].asUInt();
		sq = seq[i].asUInt();
		ret = pData->Move(rid, DataNewWorldAllianceRoomHeroIndex(uid, heroIndex), cid, false, 2, mts, sq);

		result["mts"][i] = mts;
		result["seq"][i] = sq;

		if (R_SUCCESS == ret)
		{
			result["index"][i] = heroIndex;
		}
	}

	if (ret && !result.isMember("index"))
	{
		return ret;
	}

	result["upts"] = pData->GetTS(rid) + NEW_WORLD_ALLIANCE_ROOM_TICK * 2;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData, allresult)

	return 0;
}

int CLogicNewWorldAllianceRoom::Buildyjt(unsigned rid, unsigned uid, unsigned index, Json::Value &allresult, unsigned &seq)
{
	Json::Value &result = allresult["Buildyjt"];
	int ret = 0;

	CDataNewWorldAllianceRoom *pData = GetData();
	if (NULL == pData)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	ret = pData->Buildyjt(rid, DataNewWorldAllianceRoomHeroIndex(uid, index), seq);
	if(ret)
	{
		error_log("Buildyjt fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}
	result["seq"] = seq;

	NEW_WORLD_ALLIANCE_ROOM_PROCESS_CHANGE(pData,allresult)
	return 0;
}
