/*
 * LogicNewWorld.cpp
 *
 *  Created on: 2014-9-18
 *      Author: Ralf
 */

#include "LogicNewWorld.h"
#include "LogicSyncLords.h"

#define LORD_EXPLOIT_PATH "../webroot/data/incrementExploit"

#define NEW_WORLD_PROCESS_CHANGE(pData,allresult) \
	const NewWorldChangeMap &change = pData->GetChangeMap(); \
	if(!change.empty()) \
	{ \
		unsigned i = 0; \
		allresult["change"].resize(change.size()); \
		for(NewWorldChangeMap::const_iterator it=change.begin();it!=change.end();++it) \
		{ \
			allresult["change"][i].resize(3u); \
			allresult["change"][i][0u] = it->second.cid; \
			allresult["change"][i][1u] = it->second.kingdom; \
			allresult["change"][i][2u] = it->second.battle; \
			++i; \
		} \
		pData->ClearChangeMap(); \
	} \

const unsigned COLLECT_EQUIP_ID[NEW_WORLD_REWARD-1] ={51001, 51002, 51003, 51004};
#ifdef SG_16_VER
const unsigned COLLECT_EQUIP_COUNT[NewWorldCityType_max-1] ={10, 5, 3};
#else
const unsigned COLLECT_EQUIP_COUNT[NewWorldCityType_max-1] ={10, 8, 5};
#endif

CLogicNewWorld::CLogicNewWorld() {
	// TODO Auto-generated constructor stub

}
CLogicNewWorld::~CLogicNewWorld() {
	// TODO Auto-generated destructor stub
}

CDataNewWorld *CLogicNewWorld::GetDataNewWorld()
{
	GET_MEM_DATA_SEM(CDataNewWorld, CONFIG_NEW_WORLD_DATA, sem_new_world,false)
}

int CLogicNewWorld::GetWorld(Json::Value &allresult)
{
	Json::Value &result = allresult["GetWorld"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	result.resize(NEW_WORLD_CITY);
	unsigned i = 0;
	const NewWorldCityMap &world = pData->GetWorld();
	for(NewWorldCityMap::const_iterator it=world.begin();it!=world.end();++it)
	{
		result[i]["id"]		 = it->second.city.cid;
		result[i]["kingdom"] = it->second.city.kingdom;
		result[i]["uid"]	 = it->second.city.uid;
		result[i]["name"]	 = string(it->second.city.name);
		result[i]["status"]	 = it->second.city.Fighting() ? 1 : 0;
		result[i]["extraKillTS"][0u] = it->second.city.extraKillTS[0];
		result[i]["extraKillTS"][1u] = it->second.city.extraKillTS[1];
		result[i]["extraKillTS"][2u] = it->second.city.extraKillTS[2];
		result[i]["rushTS"][0u] = it->second.city.rushTS[0];
		result[i]["rushTS"][1u] = it->second.city.rushTS[1];
		result[i]["rushTS"][2u] = it->second.city.rushTS[2];
		result[i]["tower"]["uid"] = it->second.city.tower.uid;
		result[i]["tower"]["dps"] = it->second.city.tower.dps;
		result[i]["tower"]["hit"] = it->second.city.tower.hit;
		result[i]["jm3ts"] = it->second.city.jm.jm3ts;
		result[i]["jm4ts"] = it->second.city.jm.jm4ts;
		++i;
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::GetHistory(unsigned index, Json::Value &allresult)
{
	Json::Value &result = allresult["GetHistory"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	const unsigned *history = pData->GetHistory(index);
	if(!history)
	{
		error_log("GetHistory fail, index=%u",index);
		return R_ERR_PARAM;
	}
	result.resize(NEW_WORLD_CITY);
	for(unsigned i=0;i<NEW_WORLD_CITY;++i)
		result[i] = history[i];

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::GetMission(Json::Value &allresult)
{
	Json::Value &result = allresult["GetMission"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	const NewWorldMisson *mission = pData->GetMission();
	if(!mission)
	{
		error_log("GetMission fail");
		return R_ERR_PARAM;
	}
	result.resize(3);
	for(unsigned i=0;i<3;++i)
	{
		result[i]["defend"]			 = mission[i].defend;
		result[i]["attack"]			 = mission[i].attack;
		result[i]["defendStatus"]	 = mission[i].defendStatus;
		result[i]["attackStatus"]	 = mission[i].attackStatus;
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorld::GetCity(unsigned cid, Json::Value &allresult)
{
	Json::Value &result = allresult["GetCity"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	const NewWorldCityBattle &city = pData->GetCity(cid);
	if(city.city.cid != cid)
	{
		error_log("GetCity fail, cid=%u",cid);
		return R_ERR_PARAM;
	}

	result["id"]		 = city.city.cid;
	result["kingdom"]	 = city.city.kingdom;
	result["uid"]		 = city.city.uid;
	result["name"]		 = city.city.name;
	result["battle"][0u] = city.city.count[0];
	result["battle"][1u] = city.city.count[1];
	result["battle"][2u] = city.city.count[2];
	result["battle"][3u] = city.city.countN;
	result["npcts"]		 = city.city.npcts;
	result["reward"]	 = city.city.reward;
	result["nextReward"] = city.city.nextReward;
	result["status"]	 = city.city.Fighting() ? 1 : 0;
	result["extraKillTS"][0u] = city.city.extraKillTS[0];
	result["extraKillTS"][1u] = city.city.extraKillTS[1];
	result["extraKillTS"][2u] = city.city.extraKillTS[2];
	result["rushTS"][0u] = city.city.rushTS[0];
	result["rushTS"][1u] = city.city.rushTS[1];
	result["rushTS"][2u] = city.city.rushTS[2];
	result["tower"]["uid"] = city.city.tower.uid;
	result["tower"]["dps"] = city.city.tower.dps;
	result["tower"]["hit"] = city.city.tower.hit;
	result["jm3ts"] = city.city.jm.jm3ts;
	result["jm4ts"] = city.city.jm.jm4ts;

	// 上一次城主挑战时间  modify by Cream
	// 由前端判断是否能够挑战城主
	result["lastChallengeTS"] = city.city.lastChallengeTS;

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::GetBattle(unsigned cid, Json::Value &allresult)
{
	Json::Value &result = allresult["GetBattle"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	const NewWorldCityBattle &city = pData->GetCity(cid);
	if(city.city.cid != cid)
	{
		error_log("GetCity fail, cid=%u",cid);
		return R_ERR_PARAM;
	}

	result["upts"] = pData->GetTS() + NEW_WORLD_TICK;
	result["battle"][0u] = city.city.count[0];
	result["battle"][1u] = city.city.count[1];
	result["battle"][2u] = city.city.count[2];
	result["battle"][3u] = city.city.countN;
	result["kingdom"]	 = city.city.kingdom;
	result["status"]	 = city.city.Fighting() ? 1 : 0;
	result["extraKillTS"][0u] = city.city.extraKillTS[0];
	result["extraKillTS"][1u] = city.city.extraKillTS[1];
	result["extraKillTS"][2u] = city.city.extraKillTS[2];
	result["rushTS"][0u] = city.city.rushTS[0];
	result["rushTS"][1u] = city.city.rushTS[1];
	result["rushTS"][2u] = city.city.rushTS[2];
	result["tower"]["uid"] = city.city.tower.uid;
	result["tower"]["dps"] = city.city.tower.dps;
	result["tower"]["hit"] = city.city.tower.hit;
	result["jm3ts"] = city.city.jm.jm3ts;
	result["jm4ts"] = city.city.jm.jm4ts;

	if(city.city.attacker.uid)
	{
		if(CDataNewWorld::notHero(city.city.attacker))
		{
			result["attacker1"]["vision"] = 1;
			result["attacker1"]["uid"]	 = city.city.vision[city.city.attacker.index].index.uid;
			result["attacker1"]["index"]	 = city.city.vision[city.city.attacker.index].index.index;
			result["attacker1"]["job"]	 = city.city.vision[city.city.attacker.index].getJob();
			result["attacker1"]["type"]	 = city.city.vision[city.city.attacker.index].getType();
			result["attacker1"]["heroID"] = CDataXML::Hero2Str(city.city.vision[city.city.attacker.index].hid);
			result["attacker1"]["name"]	 = string(city.city.vision[city.city.attacker.index].name);
			result["attacker1"]["kingdom"]= city.city.vision[city.city.attacker.index].kingdom;
			result["attacker1"]["level"]	 = city.city.vision[city.city.attacker.index].level;
			result["attacker1"]["hp"]	 = city.city.vision[city.city.attacker.index].hp;
			result["attacker1"]["buff"]	 = city.city.vision[city.city.attacker.index].buff;
			result["attacker1"]["property"].resize(NewWorldProperty_max);
			for(unsigned i=0;i<NewWorldProperty_max;++i)
				result["attacker1"]["property"][i] = city.city.vision[city.city.attacker.index].property[i];
		}
		else
		{
			const NewWorldHero &hero = pData->GetHero(city.city.attacker);
			if(hero.index == city.city.attacker)
			{
				result["attacker1"]["vision"] = 0;
				result["attacker1"]["uid"]	 = hero.index.uid;
				result["attacker1"]["index"]	 = hero.index.index;
				result["attacker1"]["job"]	 = hero.getJob();
				result["attacker1"]["type"]	 = hero.getType();
				result["attacker1"]["heroID"] = CDataXML::Hero2Str(hero.hid);
				result["attacker1"]["name"]	 = string(hero.name);
				result["attacker1"]["kingdom"]= hero.kingdom;
				result["attacker1"]["level"]	 = hero.level;
				result["attacker1"]["hp"]	 = hero.hp;
				result["attacker1"]["buff"]	 = hero.buff;
				result["attacker1"]["property"].resize(NewWorldProperty_max);
				for(unsigned i=0;i<NewWorldProperty_max;++i)
					result["attacker1"]["property"][i] = hero.property[i];
			}
			else
			{
				error_log("GetHero fail, uid=%u, index=%u",city.city.attacker.uid, city.city.attacker.index);
			}
		}
	}
	if(city.city.defender.uid)
	{
		if(CDataNewWorld::notHero(city.city.defender))
		{
			result["defender1"]["vision"] = 1;
			result["defender1"]["uid"]	 = city.city.vision[city.city.defender.index].index.uid;
			result["defender1"]["index"]	 = city.city.vision[city.city.defender.index].index.index;
			result["defender1"]["job"]	 = city.city.vision[city.city.defender.index].getJob();
			result["defender1"]["type"]	 = city.city.vision[city.city.defender.index].getType();
			result["defender1"]["heroID"] = CDataXML::Hero2Str(city.city.vision[city.city.defender.index].hid);
			result["defender1"]["name"]	 = string(city.city.vision[city.city.defender.index].name);
			result["defender1"]["kingdom"]= city.city.vision[city.city.defender.index].kingdom;
			result["defender1"]["level"]	 = city.city.vision[city.city.defender.index].level;
			result["defender1"]["hp"]	 = city.city.vision[city.city.defender.index].hp;
			result["defender1"]["buff"]	 = city.city.vision[city.city.defender.index].buff;
			result["defender1"]["property"].resize(NewWorldProperty_max);
			for(unsigned i=0;i<NewWorldProperty_max;++i)
				result["defender1"]["property"][i] = city.city.vision[city.city.defender.index].property[i];
		}
		else
		{
			const NewWorldHero &hero = pData->GetHero(city.city.defender);
			if(hero.index == city.city.defender)
			{
				result["defender1"]["vision"] = 0;
				result["defender1"]["uid"]	 = hero.index.uid;
				result["defender1"]["index"]	 = hero.index.index;
				result["defender1"]["job"]	 = hero.getJob();
				result["defender1"]["type"]	 = hero.getType();
				result["defender1"]["heroID"] = CDataXML::Hero2Str(hero.hid);
				result["defender1"]["name"]	 = string(hero.name);
				result["defender1"]["kingdom"]= hero.kingdom;
				result["defender1"]["level"]	 = hero.level;
				result["defender1"]["hp"]	 = hero.hp;
				result["defender1"]["buff"]	 = hero.buff;
				result["defender1"]["property"].resize(NewWorldProperty_max);
				for(unsigned i=0;i<NewWorldProperty_max;++i)
					result["defender1"]["property"][i] = hero.property[i];
			}
			else
			{
				error_log("GetHero fail, uid=%u, index=%u",city.city.defender.uid, city.city.defender.index);
			}
		}
	}
	if(city.attacker.size())
	{
		NewWorldCityQueue::const_iterator it = city.attacker.begin();
		if(CDataNewWorld::notHero(it->second))
		{
			result["attacker2"]["vision"] = 1;
			result["attacker2"]["uid"]	 = city.city.vision[it->second.index].index.uid;
			result["attacker2"]["index"]	 = city.city.vision[it->second.index].index.index;
			result["attacker2"]["job"]	 = city.city.vision[it->second.index].getJob();
			result["attacker2"]["type"]	 = city.city.vision[it->second.index].getType();
			result["attacker2"]["heroID"] = CDataXML::Hero2Str(city.city.vision[it->second.index].hid);
			result["attacker2"]["name"]	 = string(city.city.vision[it->second.index].name);
			result["attacker2"]["kingdom"]= city.city.vision[it->second.index].kingdom;
			result["attacker2"]["level"]	 = city.city.vision[it->second.index].level;
			result["attacker2"]["hp"]	 = city.city.vision[it->second.index].hp;
			result["attacker2"]["buff"]	 = city.city.vision[it->second.index].buff;
			result["attacker2"]["property"].resize(NewWorldProperty_max);
			for(unsigned i=0;i<NewWorldProperty_max;++i)
				result["attacker2"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldHero &hero = pData->GetHero(it->second);
			if(hero.index == it->second)
			{
				result["attacker2"]["vision"] = 0;
				result["attacker2"]["uid"]	 = hero.index.uid;
				result["attacker2"]["index"]	 = hero.index.index;
				result["attacker2"]["job"]	 = hero.getJob();
				result["attacker2"]["type"]	 = hero.getType();
				result["attacker2"]["heroID"] = CDataXML::Hero2Str(hero.hid);
				result["attacker2"]["name"]	 = string(hero.name);
				result["attacker2"]["kingdom"]= hero.kingdom;
				result["attacker2"]["level"]	 = hero.level;
				result["attacker2"]["hp"]	 = hero.hp;
				result["attacker2"]["buff"]	 = hero.buff;
				result["attacker2"]["property"].resize(NewWorldProperty_max);
				for(unsigned i=0;i<NewWorldProperty_max;++i)
					result["attacker2"]["property"][i] = hero.property[i];
			}
			else
			{
				error_log("GetHero fail, uid=%u, index=%u",city.city.attacker.uid, city.city.attacker.index);
			}
		}
	}
	if(city.defender.size())
	{
		NewWorldCityQueue::const_iterator it = city.defender.begin();
		if(CDataNewWorld::notHero(it->second))
		{
			result["defender2"]["vision"] = 1;
			result["defender2"]["uid"]	 = city.city.vision[it->second.index].index.uid;
			result["defender2"]["index"]	 = city.city.vision[it->second.index].index.index;
			result["defender2"]["job"]	 = city.city.vision[it->second.index].getJob();
			result["defender2"]["type"]	 = city.city.vision[it->second.index].getType();
			result["defender2"]["heroID"] = CDataXML::Hero2Str(city.city.vision[it->second.index].hid);
			result["defender2"]["name"]	 = string(city.city.vision[it->second.index].name);
			result["defender2"]["kingdom"]= city.city.vision[it->second.index].kingdom;
			result["defender2"]["level"]	 = city.city.vision[it->second.index].level;
			result["defender2"]["hp"]	 = city.city.vision[it->second.index].hp;
			result["defender2"]["buff"]	 = city.city.vision[it->second.index].buff;
			result["defender2"]["property"].resize(NewWorldProperty_max);
			for(unsigned i=0;i<NewWorldProperty_max;++i)
				result["defender2"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldHero &hero = pData->GetHero(it->second);
			if(hero.index == it->second)
			{
				result["defender2"]["vision"] = 0;
				result["defender2"]["uid"]	 = hero.index.uid;
				result["defender2"]["index"]	 = hero.index.index;
				result["defender2"]["job"]	 = hero.getJob();
				result["defender2"]["type"]	 = hero.getType();
				result["defender2"]["heroID"] = CDataXML::Hero2Str(hero.hid);
				result["defender2"]["name"]	 = string(hero.name);
				result["defender2"]["kingdom"]= hero.kingdom;
				result["defender2"]["level"]	 = hero.level;
				result["defender2"]["hp"]	 = hero.hp;
				result["defender2"]["buff"]	 = hero.buff;
				result["defender2"]["property"].resize(NewWorldProperty_max);
				for(unsigned i=0;i<NewWorldProperty_max;++i)
					result["defender2"]["property"][i] = hero.property[i];
			}
			else
			{
				error_log("GetHero fail, uid=%u, index=%u",city.city.attacker.uid, city.city.attacker.index);
			}
		}
	}/*
	else if(city.city.countN)
	{
		result["defender2"]["vision"] = 1;
		result["defender2"]["uid"]	 = ADMIN_UID;
		result["defender2"]["index"]	 = NEW_WORLD_CITY_VISION;
		result["defender2"]["job"]	 = (city.city.vision[NEW_WORLD_CITY_VISION].job + 1) % NewWorldHeroJob_max + 1;
		result["defender2"]["type"]	 = city.city.vision[NEW_WORLD_CITY_VISION].getType();
		result["defender2"]["heroID"] = CDataXML::Hero2Str((city.city.vision[NEW_WORLD_CITY_VISION].job + 1) % NewWorldHeroJob_max + 1);
		result["defender2"]["name"]	 = string("NPC");
		result["defender2"]["kingdom"]= city.city.vision[NEW_WORLD_CITY_VISION].kingdom;
		result["defender2"]["level"]	 = city.city.vision[NEW_WORLD_CITY_VISION].level;
		result["defender2"]["hp"]	 = city.city.vision[NEW_WORLD_CITY_VISION].property[NewWorldProperty_hp];
		result["defender2"]["property"].resize(NewWorldProperty_max);
		for(unsigned i=0;i<NewWorldProperty_max;++i)
			result["defender2"]["property"][i] = city.city.vision[NEW_WORLD_CITY_VISION].property[i];
	}*/
	if(city.attacker.size() > 1)
	{
		NewWorldCityQueue::const_iterator it = city.attacker.begin();
		++it;
		if(CDataNewWorld::notHero(it->second))
		{
			result["attacker3"]["vision"] = 1;
			result["attacker3"]["uid"]	 = city.city.vision[it->second.index].index.uid;
			result["attacker3"]["index"]	 = city.city.vision[it->second.index].index.index;
			result["attacker3"]["job"]	 = city.city.vision[it->second.index].getJob();
			result["attacker3"]["type"]	 = city.city.vision[it->second.index].getType();
			result["attacker3"]["heroID"] = CDataXML::Hero2Str(city.city.vision[it->second.index].hid);
			result["attacker3"]["name"]	 = string(city.city.vision[it->second.index].name);
			result["attacker3"]["kingdom"]= city.city.vision[it->second.index].kingdom;
			result["attacker3"]["level"]	 = city.city.vision[it->second.index].level;
			result["attacker3"]["hp"]	 = city.city.vision[it->second.index].hp;
			result["attacker3"]["buff"]	 = city.city.vision[it->second.index].buff;
			result["attacker3"]["property"].resize(NewWorldProperty_max);
			for(unsigned i=0;i<NewWorldProperty_max;++i)
				result["attacker3"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldHero &hero = pData->GetHero(it->second);
			if(hero.index == it->second)
			{
				result["attacker3"]["vision"] = 0;
				result["attacker3"]["uid"]	 = hero.index.uid;
				result["attacker3"]["index"]	 = hero.index.index;
				result["attacker3"]["job"]	 = hero.getJob();
				result["attacker3"]["type"]	 = hero.getType();
				result["attacker3"]["heroID"] = CDataXML::Hero2Str(hero.hid);
				result["attacker3"]["name"]	 = string(hero.name);
				result["attacker3"]["kingdom"]= hero.kingdom;
				result["attacker3"]["level"]	 = hero.level;
				result["attacker3"]["hp"]	 = hero.hp;
				result["attacker3"]["buff"]	 = hero.buff;
				result["attacker3"]["property"].resize(NewWorldProperty_max);
				for(unsigned i=0;i<NewWorldProperty_max;++i)
					result["attacker3"]["property"][i] = hero.property[i];
			}
			else
			{
				error_log("GetHero fail, uid=%u, index=%u",city.city.attacker.uid, city.city.attacker.index);
			}
		}
	}
	if(city.defender.size() > 1)
	{
		NewWorldCityQueue::const_iterator it = city.defender.begin();
		++it;
		if(CDataNewWorld::notHero(it->second))
		{
			result["defender3"]["vision"] = 1;
			result["defender3"]["uid"]	 = city.city.vision[it->second.index].index.uid;
			result["defender3"]["index"]	 = city.city.vision[it->second.index].index.index;
			result["defender3"]["job"]	 = city.city.vision[it->second.index].getJob();
			result["defender3"]["type"]	 = city.city.vision[it->second.index].getType();
			result["defender3"]["heroID"] = CDataXML::Hero2Str(city.city.vision[it->second.index].hid);
			result["defender3"]["name"]	 = string(city.city.vision[it->second.index].name);
			result["defender3"]["kingdom"]= city.city.vision[it->second.index].kingdom;
			result["defender3"]["level"]	 = city.city.vision[it->second.index].level;
			result["defender3"]["hp"]	 = city.city.vision[it->second.index].hp;
			result["defender3"]["buff"]	 = city.city.vision[it->second.index].buff;
			result["defender3"]["property"].resize(NewWorldProperty_max);
			for(unsigned i=0;i<NewWorldProperty_max;++i)
				result["defender3"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldHero &hero = pData->GetHero(it->second);
			if(hero.index == it->second)
			{
				result["defender3"]["vision"] = 0;
				result["defender3"]["uid"]	 = hero.index.uid;
				result["defender3"]["index"]	 = hero.index.index;
				result["defender3"]["job"]	 = hero.getJob();
				result["defender3"]["type"]	 = hero.getType();
				result["defender3"]["heroID"] = CDataXML::Hero2Str(hero.hid);
				result["defender3"]["name"]	 = string(hero.name);
				result["defender3"]["kingdom"]= hero.kingdom;
				result["defender3"]["level"]	 = hero.level;
				result["defender3"]["hp"]	 = hero.hp;
				result["defender3"]["buff"]	 = hero.buff;
				result["defender3"]["property"].resize(NewWorldProperty_max);
				for(unsigned i=0;i<NewWorldProperty_max;++i)
					result["defender3"]["property"][i] = hero.property[i];
			}
			else
			{
				error_log("GetHero fail, uid=%u, index=%u",city.city.attacker.uid, city.city.attacker.index);
			}
		}
	}/*
	else if(city.city.countN > 1)
	{
		result["defender3"]["vision"] = 1;
		result["defender3"]["uid"]	 = ADMIN_UID;
		result["defender3"]["index"]	 = NEW_WORLD_CITY_VISION;
		result["defender3"]["job"]	 = (city.city.vision[NEW_WORLD_CITY_VISION].job + 2) % NewWorldHeroJob_max + 1;
		result["defender3"]["type"]	 = city.city.vision[NEW_WORLD_CITY_VISION].getType();
		result["defender3"]["heroID"] = CDataXML::Hero2Str((city.city.vision[NEW_WORLD_CITY_VISION].job + 2) % NewWorldHeroJob_max + 1);
		result["defender3"]["name"]	 = string("NPC");
		result["defender3"]["kingdom"]= city.city.vision[NEW_WORLD_CITY_VISION].kingdom;
		result["defender3"]["level"]	 = city.city.vision[NEW_WORLD_CITY_VISION].level;
		result["defender3"]["hp"]	 = city.city.vision[NEW_WORLD_CITY_VISION].property[NewWorldProperty_hp];
		result["defender3"]["property"].resize(NewWorldProperty_max);
		for(unsigned i=0;i<NewWorldProperty_max;++i)
			result["defender3"]["property"][i] = city.city.vision[NEW_WORLD_CITY_VISION].property[i];
	}*/

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::GetBattleList(unsigned cid, unsigned camp, Json::Value &allresult)
{
	Json::Value &result = allresult["GetBattleList"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	const NewWorldCityBattle &city = pData->GetCity(cid);
	if(city.city.cid != cid)
	{
		error_log("GetCity fail, cid=%u",cid);
		return R_ERR_PARAM;
	}

	result.resize(0);
	const NewWorldCityQueue &list = camp?city.attacker:city.defender;
	for(NewWorldCityQueue::const_iterator it=list.begin();it!=list.end();++it)
	{
		Json::Value temp;
		if(CDataNewWorld::notHero(it->second))
		{
			const NewWorldHero &hero = city.city.vision[it->second.index];
			temp["vision"]		 = 1;
			temp["heroID"]		 = CDataXML::Hero2Str(hero.hid);
			temp["kingdom"]		 = hero.kingdom;
			temp["name"]		 = hero.name;
			temp["index"]		 = hero.index.index;
			temp["hp"]			 = hero.hp;
			temp["maxhp"]		 = hero.property[NewWorldProperty_hp];
		}
		else
		{
			const NewWorldHero &hero = pData->GetHero(it->second);
			if(hero.index != it->second)
			{
				error_log("GetHero fail, uid=%u, index=%u",hero.index.uid, hero.index.index);
				continue;
			}

			temp["vision"]		 = 0;
			temp["heroID"]		 = CDataXML::Hero2Str(hero.hid);
			temp["kingdom"]		 = hero.kingdom;
			temp["name"]		 = hero.name;
			temp["index"]		 = hero.index.index;
			temp["hp"]			 = hero.hp;
			temp["maxhp"]		 = hero.property[NewWorldProperty_hp];
		}

		result.append(temp);
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::GetHero(unsigned uid, unsigned index, Json::Value &allresult)
{
	Json::Value &result = allresult["GetHero"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	NewWorldHeroIndex heroindex(uid, index);
	const NewWorldHero &hero = pData->GetHero(heroindex);
	if(hero.index != heroindex)
	{
		error_log("GetHero fail, uid=%u, index=%u",hero.index.uid, hero.index.index);
		return R_ERR_PARAM;
	}

	result["uid"]		 = hero.index.uid;
	result["index"]		 = hero.index.index;
	result["heroId"]	 = CDataXML::Hero2Str(hero.hid);
	result["job"]	 	 = hero.getJob();
	result["type"]	 	 = hero.getType();
	result["level"]	 	 = hero.level;
	result["kingdom"]	 = hero.kingdom;
	result["cid"]	 	 = hero.cid;
	result["hp"]	 	 = hero.hp;
	result["status"]	 = hero.status;
	result["property"].resize(NewWorldProperty_max);
	for(unsigned i=0;i<NewWorldProperty_max;++i)
		result["property"][i] = hero.property[i];
	result["kill"]	 = hero.kill;
	result["buff"]	 = hero.buff;
	result["inc_kill"] = hero.inc_kill;

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::GetAllHero(unsigned uid,Json::Value &allresult)
{
	Json::Value &result = allresult["GetAllHero"];

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	result.resize(0);
	const NewWorldHeroMap &heromap = pData->GetAllHero();
	for(unsigned i=0;i<NEW_WORLD_HERO_INDEX;++i)
	{
		NewWorldHeroIndex index(uid,i);
		NewWorldHeroMap::const_iterator hero = heromap.find(index);
		if(hero != heromap.end())
		{
			Json::Value temp;
			temp["uid"]		 = hero->second.index.uid;
			temp["index"]	 = hero->second.index.index;
			temp["heroId"]	 = CDataXML::Hero2Str(hero->second.hid);
			temp["job"]	 	 = hero->second.getJob();
			temp["type"]	 = hero->second.getType();
			temp["level"]	 = hero->second.level;
			temp["kingdom"]	 = hero->second.kingdom;
			temp["cid"]	 	 = hero->second.cid;
			temp["hp"]	 	 = hero->second.hp;
			temp["status"]	 = hero->second.status;
			temp["property"].resize(NewWorldProperty_max);
			for(unsigned i=0;i<NewWorldProperty_max;++i)
				temp["property"][i] = hero->second.property[i];
			temp["kill"]	 = hero->second.kill;
			temp["buff"]	 = hero->second.buff;
			temp["inc_kill"] = hero->second.inc_kill;
			result.append(temp);
		}
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::SetHero(unsigned uid, unsigned index, const Json::Value &para, Json::Value &allresult)
{
	Json::Value &result = allresult["SetHero"];

	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	unsigned kingdom = 0;
	Json::GetUInt(para, "kingdom", kingdom);
	unsigned level = 0;
	Json::GetUInt(para, "level", level);
	unsigned job = 0;
	Json::GetUInt(para, "job", job);
	string name, heroid;
	Json::GetString(para, "name", name);
	Json::GetString(para, "heroId", heroid);

	NewWorldHero hero;
	hero.index.uid		= uid;
	hero.index.index	= index;
	hero.kingdom		= kingdom;
	hero.level			= level;
	hero.job			= (job - 1)%NewWorldHeroJob_max;

	if(!heroid.empty())
		hero.hid		= CDataXML::Str2Hero(heroid);
	if(!name.empty())
		strncpy(hero.name, name.c_str(), sizeof(hero.name)-1);
	if(para.isMember("property") && para["property"].isArray() && para["property"].size()<=NewWorldProperty_max)
	{
		for(unsigned i=0;i<para["property"].size();++i)
			hero.property[i] = para["property"][i].asUInt();
		/*
		hero.property[NewWorldProperty_hp] = CDataNewWorld::getAttDefHP(hero.property[NewWorldProperty_hp]);
		hero.property[NewWorldProperty_attack] = CDataNewWorld::getAttDefHP(hero.property[NewWorldProperty_attack]);
		hero.property[NewWorldProperty_defence] = CDataNewWorld::getAttDefHP(hero.property[NewWorldProperty_defence]);
		hero.property[NewWorldProperty_extra] = CDataNewWorld::getAttDefHP(hero.property[NewWorldProperty_extra]);
		hero.property[NewWorldProperty_anti_extra] = CDataNewWorld::getAttDefHP(hero.property[NewWorldProperty_anti_extra]);
		*/
	}

	bool fix = false;
	ret = pData->SetHero(hero, fix);
	if(ret)
	{
		error_log("SetHero fail, uid=%u, index=%u, ret=%u",hero.index.uid, hero.index.index, ret);
		return ret;
	}
	if(fix)
		pData->Fix();

	result["uid"]		 = hero.index.uid;
	result["index"]	 = hero.index.index;
	result["heroId"]	 = CDataXML::Hero2Str(hero.hid);
	result["job"]	 	 = hero.getJob();
	result["type"]	 = hero.getType();
	result["level"]	 = hero.level;
	result["kingdom"]	 = hero.kingdom;
	result["cid"]	 	 = hero.cid;
	result["hp"]	 	 = hero.hp;
	result["status"]	 = hero.status;
	result["property"].resize(NewWorldProperty_max);
	for(unsigned i=0;i<NewWorldProperty_max;++i)
		result["property"][i] = hero.property[i];
	result["buff"]	 	 = hero.buff;
	result["kill"]	 	 = hero.kill;
	result["inc_kill"]	 = hero.inc_kill;

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorld::Move(unsigned uid, unsigned index, unsigned cid, bool leave, unsigned fly, Json::Value &allresult)
{
	Json::Value &result = allresult["Move"];

	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	unsigned status;
	ret = pData->Move(NewWorldHeroIndex(uid, index), cid, leave, fly, status);
	result["status"] = status;
	if(ret)
	{
		if(ret != R_ERR_LOGIC)
			error_log("Move fail, uid=%u, index=%u, cid=%u, ret=%u",uid, index, cid, ret);
		return ret;
	}

	// true == fly 不需要消耗粮食
	if (!fly)
	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(uid)

		ret = logicUser.GetUserLimit(uid,dataUser);
		if(ret)
			return ret;
		int r1 = -CDataNewWorld::GetMoveR1(dataUser.level);
		int temp = dataUser.r1;
		temp = r1 + temp;
		if(temp < 0)
		{
			LOGIC_ERROR_RETURN_MSG("resource_error");
		}
		dataUser.r1 = temp;
		ret = logicUser.SetUserLimit(uid,dataUser);
		if (ret)
		{
			return ret;
		}
		result["r1"] = temp;
	}

	result["upts"] = pData->GetTS() + NEW_WORLD_TICK * 2;

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::Change(unsigned uid, unsigned index, unsigned type, Json::Value &allresult)
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->Change(NewWorldHeroIndex(uid, index), type);
	if(ret)
	{
		error_log("Change fail, uid=%u, index=%u, type=%u, ret=%u",uid, index, type, ret);
		return ret;
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::Clone(unsigned uid, unsigned index, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if(equipment.Try(uid, NEW_WORLD_CLONE_COST, equd, 1))
		return R_ERR_PARAM;

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->Clone(NewWorldHeroIndex(uid, index));
	if(ret)
	{
		error_log("Clone fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}

	{
		AUTO_LOCK_USER(uid)
		ret = equipment.UseEquipment(uid, NEW_WORLD_CLONE_COST, equd, 1, "new_world_clone");
		if(ret)
		{
			error_log("new_world_clone uid=%u, equd=%u", uid , equd);
			return R_ERR_DATA;
		}
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::Recover(unsigned uid, unsigned index, unsigned equd, unsigned num, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if(equipment.Try(uid, NEW_WORLD_RECOVER_COST, equd, num))
		return R_ERR_PARAM;

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->Recover(NewWorldHeroIndex(uid, index), num);
	if(ret)
	{
		error_log("Recover fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}

	{
		AUTO_LOCK_USER(uid)
		ret = equipment.UseEquipment(uid, NEW_WORLD_RECOVER_COST, equd, num, "new_world_recover");
		if(ret)
		{
			error_log("new_world_recover uid=%u, equd=%u", uid , equd);
			return R_ERR_DATA;
		}
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorld::Explode(unsigned uid, unsigned index, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if(equipment.Try(uid, NEW_WORLD_EXPLODE_COST, equd, 1))
		return R_ERR_PARAM;

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->Explode(NewWorldHeroIndex(uid, index));
	if(ret)
	{
		error_log("Explode fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}

	{
		AUTO_LOCK_USER(uid)
		ret = equipment.UseEquipment(uid, NEW_WORLD_EXPLODE_COST, equd, 1, "new_world_explode");
		if(ret)
		{
			error_log("new_world_explode uid=%u, equd=%u", uid , equd);
			return R_ERR_DATA;
		}
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::Rush(unsigned uid, unsigned index, unsigned equd, bool fly, Json::Value &allresult)
{
	Json::Value &result = allresult["Rush"];

	int ret = 0;
	CLogicEquipment equipment;
	if(!fly && equipment.Try(uid, NEW_WORLD_RUSH_COST, equd, 1))
		return R_ERR_PARAM;

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	NewWorldHero other, end;
	ret = pData->Rush(NewWorldHeroIndex(uid, index), other, end);
	if(ret)
		return ret;

	if(!fly)
	{
		AUTO_LOCK_USER(uid)
		ret = equipment.UseEquipment(uid, NEW_WORLD_RUSH_COST, equd, 1, "new_world_rush");
		if(ret)
		{
			error_log("new_world_rush uid=%u, equd=%u", uid , equd);
			return R_ERR_DATA;
		}
	}

	result["other"]["vision"] = CDataNewWorld::notHero(other.index)?1:0;
	result["other"]["uid"]	 = other.index.uid;
	result["other"]["index"]	 = other.index.index;
	result["other"]["job"]	 = other.getJob();
	result["other"]["type"]	 = other.getType();
	result["other"]["heroID"] = CDataXML::Hero2Str(other.hid);
	result["other"]["name"]	 = string(other.name);
	result["other"]["kingdom"]= other.kingdom;
	result["other"]["level"]	 = other.level;
	result["other"]["hp"]	 = other.hp;
	result["other"]["buff"]	 = other.buff;
	result["other"]["property"].resize(NewWorldProperty_max);
	for(unsigned i=0;i<NewWorldProperty_max;++i)
		result["other"]["property"][i] = other.property[i];

	result["end"]["vision"] = CDataNewWorld::notHero(end.index)?1:0;
	result["end"]["uid"]	 = end.index.uid;
	result["end"]["index"]	 = end.index.index;
	result["end"]["job"]	 = end.getJob();
	result["end"]["type"]	 = end.getType();
	result["end"]["heroID"] = CDataXML::Hero2Str(end.hid);
	result["end"]["name"]	 = string(end.name);
	result["end"]["kingdom"]= end.kingdom;
	result["end"]["level"]	= end.level;
	result["end"]["hp"]	 = end.hp;
	result["end"]["buff"]	 = end.buff;
	result["end"]["property"].resize(NewWorldProperty_max);
	for(unsigned i=0;i<NewWorldProperty_max;++i)
		result["end"]["property"][i] = end.property[i];

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorld::Challenge(unsigned uid, unsigned &olduid, unsigned cid, string &name, unsigned k)
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->Challenge(uid, olduid, cid, name, k);
	if(ret)
	{
		error_log("Challenge fail, uid=%u, cid=%u, ret=%u",uid, cid, ret);
		return ret;
	}

	if(IsValidUid(olduid))
	{
		CLogicUpdates logicUpdates;
		Json::Value updates;
		updates["s"] = "SUBBASELOSS";
		updates["name"] = name;
		updates["uid"] = uid;
		updates["ts"] = Time::GetGlobalTime();
		updates["cid"] = cid;
		logicUpdates.AddUpdate(olduid,updates);
	}

	olduid = uid;

	return 0;
}


// 1 : set challenge time
// 0 : reset challenge time
int CLogicNewWorld::SetChallengeTS(unsigned cid, int set, unsigned k)
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->SetChallengeTS(cid, set, k);
	if (ret)
	{
		error_log("SetStartChallengeTS fail");
		return ret;
	}

	return 0;
}


int CLogicNewWorld::Collect(unsigned uid, unsigned cid, Json::Value &allresult)
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	unsigned reward = 0;
	ret = pData->Collect(uid, cid, reward);
	if(ret)
	{
		error_log("Collect fail, uid=%u, cid=%u, ret=%u",uid, cid, ret);
		return ret;
	}

	unsigned cityType = CDataNewWorld::getCityType(cid);
	if(cid == 1)
		cityType = NewWorldCityType_capital;
	else if(cityType == NewWorldCityType_neutral)
		cityType = NewWorldCityType_core;

	CLogicEquipment logicEquip;
	//ret = logicEquip.AddOneItem(uid, /*COLLECT_EQUIP_ID[reward-1]*/4055, COLLECT_EQUIP_COUNT[cityType] * 15, "zhengbaReward", allresult["equipment"], true);
	vector<ItemAdd> vecEqs;
	vecEqs.push_back(ItemAdd(COLLECT_EQUIP_ID[reward-1], COLLECT_EQUIP_COUNT[cityType], "zhengbaReward"));
	vecEqs.push_back(ItemAdd(4055, COLLECT_EQUIP_COUNT[cityType], "zhengbaReward"));
	ret = logicEquip.AddItems(uid, vecEqs, allresult["equipment"], true);
	if (ret)
		return ret;

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorld::WorldReward()
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}
	pData->SetTool(true);

	ret = pData->WorldReward();
	if(ret)
	{
		error_log("WorldReward fail, ret=%u", ret);
		return ret;
	}

	return 0;
}
int CLogicNewWorld::CityReward()
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}
	pData->SetTool(true);

	ret = pData->CityReward();
	if(ret)
	{
		error_log("CityReward fail, ret=%u", ret);
		return ret;
	}

	return 0;
}
int CLogicNewWorld::StartMission()
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}
	pData->SetTool(true);

	ret = pData->StartMission2();
	if(ret)
	{
		error_log("StartMisson fail, ret=%u", ret);
		return ret;
	}

	return 0;
}
int CLogicNewWorld::EndMission()
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}
	pData->SetTool(true);

	ret = pData->EndMission();
	if(ret)
	{
		error_log("EndMisson fail, ret=%u", ret);
		return ret;
	}

	return 0;
}

int CLogicNewWorld::KillRank(string path)
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}
	pData->SetTool(true);

	const NewWorldHeroMap &heromap = pData->GetAllHero();
	map<unsigned, unsigned> herokill;
	map<unsigned, string> heroname;
	for(NewWorldHeroMap::const_iterator it=heromap.begin();it!=heromap.end();++it)
	{
		if(it->second.kill)
		{
			if(!herokill.count(it->first.uid))
			{
				herokill[it->first.uid] = 0;
				string name = it->second.name;
				vector<string> rlt;
				String::Split(name, '&', rlt);
				if (rlt.size() > 0)
					name = *(rlt.rbegin());
				heroname[it->first.uid] = name;
			}
			herokill[it->first.uid] += it->second.kill;
		}
	}

	//@add oulong 20160708
	try
	{
		CLogicLordExploit logicLordExplot(LORD_EXPLOIT_PATH);
		logicLordExplot.StatisticsIcrement(path, herokill, heroname);

	}
	catch (const std::exception& e) {
		error_log("%s", e.what());
	}
	//@end

	multimap<unsigned, unsigned> killhero;
	for(map<unsigned, unsigned>::iterator it=herokill.begin();it!=herokill.end();++it)
		killhero.insert(pair<unsigned, unsigned>(it->second, it->first));

	unsigned i = 0;
	DataUser user;
	CLogicUser logicUser;
	Json::Value rank;
	for(multimap<unsigned, unsigned>::reverse_iterator it=killhero.rbegin();it!=killhero.rend();++it)
	{
		if(it->first == 0)
			break;

		logicUser.GetUserLimit(it->second, user);
		rank[i]["uid"] = it->second;
		rank[i]["name"] = heroname[it->second];
		rank[i]["kingdom"] = user.kingdom;
		rank[i]["kill"] = it->first;
		rank[i]["level"] = user.level;
		rank[i]["exp"] = CDataNewWorld::GetKillExp(it->first, user.level);

		++i;
		if(i == 100)
			break;
	}

	ret = File::Write(path, Json::ToString(rank));
	if(ret)
	{
		cout<<"write NewWorld fail"<<endl;
		return ret;
	}

	return 0;
}

int CLogicNewWorld::KillReward()
{
	int ret = 0;
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}
	pData->SetTool(true);

	const NewWorldHeroMap &heromap = pData->GetAllHero();
	map<unsigned, unsigned> herokill;
	map<unsigned, unsigned> herokill_inc;
	map<unsigned, string> heroname;
	for(NewWorldHeroMap::const_iterator it=heromap.begin();it!=heromap.end();++it)
	{
		if(it->second.kill)
		{
			if(!herokill.count(it->first.uid))
			{
				herokill[it->first.uid] = 0;
				string name = it->second.name;
				vector<string> rlt;
				String::Split(name, '&', rlt);
				if (rlt.size() > 0)
					name = *(rlt.rbegin());
				heroname[it->first.uid] = name;
			}
			herokill[it->first.uid] += it->second.kill;
		}
		if(it->second.inc_kill)
		{
			if(!herokill_inc.count(it->first.uid))
				herokill_inc[it->first.uid] = 0;
			herokill_inc[it->first.uid] += it->second.inc_kill;
		}
	}

	multimap<unsigned, unsigned> killhero;
	for(map<unsigned, unsigned>::iterator it=herokill.begin();it!=herokill.end();++it)
		killhero.insert(pair<unsigned, unsigned>(it->second, it->first));

	//合区活动国战个人杀敌排行榜
	if((Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS)))
	{
		CLogicHequActivity WorldAttack;
		WorldAttack.UpdateNewWorldAttackRank(killhero, heroname);
	}

	unsigned i = 0;

	CLogicUpdates logicUpdates;
	CLogicEquipment logicEquipment;
	DataUser user;
	CLogicUser logicUser;
	for(multimap<unsigned, unsigned>::reverse_iterator it=killhero.rbegin();it!=killhero.rend();++it)
	{
		if(it->first == 0)
			break;

		AUTO_LOCK_USER(it->second)
		logicUser.GetUserLimit(it->second, user);
		unsigned exp = CDataNewWorld::GetKillExp(it->first, user.level);
		user.point += exp;
		if(logicUser.SetUserLimit(it->second, user) == 0)
		{
			RESOURCE_LOG("[NEWWORLDKILLREWARD][uid=%u,expchg=%u,exp=%u]",it->second, exp, user.point);
		}

		++i;
		if(i <= 100)
		{
			Json::Value update, res;
			/*
			vector<ItemAdd> items;
			ItemAdd t1, t2;
			t1.eqid = NEW_WORLD_KILL_REWARD_1;
			t1.count = CDataNewWorld::GetKillReward1(i);
			t1.reason = "NEWWORLDKILLREWARD";
			items.push_back(t1);
			t2.eqid = NEW_WORLD_KILL_REWARD_2;
			t2.count = CDataNewWorld::GetKillReward2(i);
			t2.reason = "NEWWORLDKILLREWARD";
			items.push_back(t2);
			if(logicEquipment.AddItems(it->second,items,res) == 0)
			{
				update["ts"] = Time::GetGlobalTime();
				update["s"] = "NEWWORLDKILLREWARD";
				update["rank"] = i;
				update["e1"] = t1.eqid;
				update["c1"] = t1.count;
				update["e2"] = t2.eqid;
				update["c2"] = t2.count;
				logicUpdates.AddUpdates(it->second,update,true);
			}
			*/
			unsigned count = CDataNewWorld::GetKillRewardNew(i);
			if(logicEquipment.AddOneItem(it->second,NEW_WORLD_KILL_REWARD_NEW,count,"NEWWORLDKILLREWARD",res) == 0)
			{
				update["ts"] = Time::GetGlobalTime();
				update["s"] = "NEWWORLDKILLREWARD";
				update["rank"] = i;
				update["e"] = NEW_WORLD_KILL_REWARD_NEW;
				update["c"] = count;
				logicUpdates.AddUpdates(it->second,update,true);
			}
		}
	}

	Json::Value reward_inc;
	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(pDataXML && pDataXML->GetWorldBattleKillRewards(reward_inc) == 0)
	{
		for(map<unsigned, unsigned>::iterator it=herokill_inc.begin();it!=herokill_inc.end();++it)
		{
			Json::Value result, update;
			vector<ItemAdd> vecEqs;
			for(unsigned i=0;i<=reward_inc.size();++i)
			{
				if(it->second < reward_inc[i]["kill"].asUInt())
					break;
				Json::Value::Members members(reward_inc[i]["reward"].getMemberNames());
				for (Json::Value::Members::iterator iter = members.begin(); iter != members.end(); ++iter)
				{
					string type = *iter;
					if(type.find("equip") != string::npos)
						vecEqs.push_back(ItemAdd(reward_inc[i]["reward"][*iter]["id"].asUInt(), reward_inc[i]["reward"][*iter]["c"].asUInt(), "KillReward"));
				}
			}
			if(!vecEqs.empty())
			{
				update["ts"] = Time::GetGlobalTime();
				update["s"] = "GetKillReward";
				update["kill"] = it->second;
				logicUpdates.AddUpdates(it->first, update, true);

				AUTO_LOCK_USER(it->first)
				logicEquipment.AddItems(it->first, vecEqs, result);
			}
		}
	}

	ret = pData->KillReward();
	if(ret)
	{
		cout<<"NewWorld KillReward fail"<<endl;
		return ret;
	}

	//@add oulong 20160708
	try
	{
		CLogicLordExploit logicLordExplot(LORD_EXPLOIT_PATH);
		logicLordExplot.Reset();
	}
	catch (const std::exception& e) {
		error_log("%s", e.what());
	}
	//@end

	return 0;
}

int CLogicNewWorld::Watch()
{
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
		return R_ERR_DATA;
	pData->SetTool(true);
	return pData->Watch();
}
int CLogicNewWorld::FixOld()
{
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
		return R_ERR_DATA;
	pData->SetTool(true);
	return pData->FixOld();
}
int CLogicNewWorld::Fix()
{
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
		return R_ERR_DATA;
	pData->SetTool(true);
	return pData->Fix();
}
int CLogicNewWorld::Reset()
{
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
		return R_ERR_DATA;
	pData->SetTool(true);
	return pData->Reset();
}
int CLogicNewWorld::Back()
{
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
		return R_ERR_DATA;
	pData->SetTool(true);
	return pData->Back();
}
int CLogicNewWorld::Test(NewWorldHero &attacker, unsigned hpa, NewWorldHero &defender, unsigned hpd)
{
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
		return R_ERR_DATA;
	pData->SetTool(true);
	return pData->Test(attacker, hpa, defender, hpd);
}
int CLogicNewWorld::Test(NewWorldHero &attacker, NewWorldHero &defender, unsigned &times)
{
	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
		return R_ERR_DATA;
	pData->SetTool(true);
	float hpa = 100.0f, hpd = 100.0f;
	times = 0;
	do
	{
		++times;
		if(pData->Test(attacker, hpa, defender, hpd))
			return R_ERR_PARAM;
		hpa = 100.0f;
		hpd = (float)defender.hp / (float)defender.property[NewWorldProperty_hp] * 100.0f;
	}while(defender.hp > 0);
	return 0;
}

int CLogicNewWorld::Double(unsigned uid, unsigned kingdom, unsigned cid, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if (equipment.Try(uid, NEW_WORLD_DOUBLE_COST, equd, 1))
	{
		return R_ERR_PARAM;
	}

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->Double(uid, kingdom, cid);

	if (ret)
	{
		error_log("Double fail uid=%u, kingdom=%u, cid=%u, ret=%u", uid, kingdom, cid, ret);
		return ret;
	}

	{
		AUTO_LOCK_USER(uid)

		ret = equipment.UseEquipment(uid, NEW_WORLD_DOUBLE_COST, equd, 1, "new_world_Double");
		if (ret)
		{
			error_log("new_world_Double uid=%u, equd=%u", uid, equd);
			return R_ERR_DATA;
		}

	}

	NEW_WORLD_PROCESS_CHANGE(pData, allresult);

	return 0;
}

int CLogicNewWorld::rushTS(unsigned uid, unsigned kingdom, unsigned cid, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if (equipment.Try(uid, NEW_WORLD_RUSHTS_COST, equd, 1))
	{
		return R_ERR_PARAM;
	}

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->rushTS(uid, kingdom, cid);

	if (ret)
	{
		error_log("rushTS fail uid=%u, kingdom=%u, cid=%u, ret=%u", uid, kingdom, cid, ret);
		return ret;
	}

	{
		AUTO_LOCK_USER(uid)

		ret = equipment.UseEquipment(uid, NEW_WORLD_RUSHTS_COST, equd, 1, "new_world_rushTS");
		if (ret)
		{
			error_log("new_world_rushTS uid=%u, equd=%u", uid, equd);
			return R_ERR_DATA;
		}

	}

	NEW_WORLD_PROCESS_CHANGE(pData, allresult);

	return 0;
}

int CLogicNewWorld::CollectOther(unsigned uid, unsigned cid, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if (equipment.Try(uid, NEW_WORLD_COLLECTOTHER_COST, equd, 1))
	{
		return R_ERR_PARAM;
	}

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->CollectOther(uid, cid);

	// 消耗道具
	{
		AUTO_LOCK_USER(uid)
		ret = equipment.UseEquipment(uid, NEW_WORLD_COLLECTOTHER_COST, equd, 1, "new_world_CollectOther");
		if(ret)
		{
			error_log("new_world_CollectOther uid=%u, equd=%u", uid , equd);
			return R_ERR_DATA;
		}
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}


int CLogicNewWorld::Blink(unsigned uid, unsigned cid, unsigned equd, const Json::Value &freeHeroIndex, Json::Value &allresult)
{
	Json::Value &result = allresult["Blink"];
	int ret = 0;

	CLogicEquipment equip;
	if (equip.Try(uid, NEW_WORLD_BLINK_COST, equd, 1))
	{
		return R_ERR_PARAM;
	}

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld failed");
		return R_ERR_DATA;
	}

	unsigned heroIndex;
	unsigned status;
	unsigned i;

	for (i = 0; i < freeHeroIndex.size(); ++i)
	{
		heroIndex = freeHeroIndex[i].asUInt();
		ret = pData->Move(NewWorldHeroIndex(uid, heroIndex), cid, false, 2, status);

		result["status"][i] = status;

		if (R_SUCCESS == ret)
		{
			result["index"][i] = heroIndex;
		}
	}

	if (ret && !result.isMember("index"))
	{
		return ret;
	}

	if (result.isMember("index"))
	{
		AUTO_LOCK_USER(uid)
		ret = equip.UseEquipment(uid, NEW_WORLD_BLINK_COST, equd, 1, "new_world_Blink");
		if (ret)
		{
			error_log("new_world_Blink uid = %u, equd = %u", uid, equd);
			return R_ERR_DATA;
		}
	}

	result["upts"] = pData->GetTS() + NEW_WORLD_TICK * 2;
	NEW_WORLD_PROCESS_CHANGE(pData, allresult)

	return 0;
}

int CLogicNewWorld::Buildyjt(unsigned uid, unsigned index, Json::Value &allresult)
{
	int ret = 0;
	{
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.GetPay(uid, payData);
		if(ret)
			return ret;
		if(payData.cash < 20)
			return R_ERR_LOGIC;

		CLogicUser logicUser;
		DataUser dataUser;
		ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::Value user_tech;
		reader.parse(dataUser.user_tech,user_tech);
		unsigned jyt = 0;
		Json::GetUInt(user_tech, "jyt", jyt);
		if(jyt == 0)
			return R_ERR_LOGIC;
	}

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->Buildyjt(NewWorldHeroIndex(uid, index));
	if(ret)
	{
		error_log("Buildyjt fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}

	{
		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -20, 0, payData, "CDataBraveNewWorld_Buildyjt",user_flag,bsave);
		if(ret)
			return ret;
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorld::UseJM(unsigned uid, unsigned jm, unsigned cid, unsigned kingdom, Json::Value &allresult)
{
	if(jm == 0 || jm >= e_JM_max)
		return R_ERR_PARAM;

	const unsigned cd[e_JM_max-1] = {3600, 3600, 10800, 10800};
	int lv = 0;

	int ret = 0;
	{
		CLogicUser logicUser;
		DataUser dataUser;
		ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::Value user_tech;
		reader.parse(dataUser.user_tech,user_tech);
		lv = user_tech["jm"][jm-1]["lv"].asInt();
		if(!user_tech.isMember("jm") || !user_tech["jm"].isArray() || user_tech["jm"].size() < jm
		|| lv == 0 || lv > NEW_WORLD_JM_LEVEL || user_tech["jm"][jm-1]["ts"].asUInt() + cd[jm-1] > Time::GetGlobalTime())
			return R_ERR_LOGIC;
	}

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->UseJM(uid, jm, lv, cid, kingdom);
	if(ret)
	{
		error_log("UseJM fail, uid=%u, jm = %u, ret=%u",uid, jm, ret);
		return ret;
	}

	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(uid)
		ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_tech;
		reader.parse(dataUser.user_tech,user_tech);
		user_tech["jm"][jm-1]["ts"] = Time::GetGlobalTime();
		dataUser.user_tech = writer.write(user_tech);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
		allresult["jm"] = user_tech["jm"];
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorld::BuyNPC(unsigned uid, unsigned cid, unsigned kingdom, Json::Value &allresult)
{
	int ret = 0;
	{
		CLogicPay logicPay;
		DataPay payData;
		ret = logicPay.GetPay(uid, payData);
		if(ret)
			return ret;
		if(payData.cash < 50)
			return R_ERR_LOGIC;
	}

	CDataNewWorld *pData = GetDataNewWorld();
	if (NULL == pData)
	{
		error_log("GetDataNewWorld fail");
		return R_ERR_DATA;
	}

	ret = pData->BuyNPC(uid, cid, kingdom);
	if(ret)
	{
		error_log("BuyNPC fail, uid=%u, ret=%u",uid, ret);
		return ret;
	}

	{
		CLogicUser logicUser;
		DataUser dataUser;
		CLogicPay logicPay;
		DataPay payData;
		AUTO_LOCK_USER(uid)
		ret = logicUser.GetUser(uid,dataUser);
		if(ret)
			return ret;
		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value user_flag;
		bool bsave = false;
		reader.parse(dataUser.user_flag,user_flag);
		ret = logicPay.ProcessOrderForBackend(uid, -50, 0, payData, "CDataBraveNewWorld_BuyNPC",user_flag,bsave);
		if(ret)
			return ret;
		if(bsave)
			dataUser.user_flag = writer.write(user_flag);
		ret = logicUser.SetUser(uid, dataUser);
		if(ret)
			return ret;
	}

	NEW_WORLD_PROCESS_CHANGE(pData,allresult)
	return 0;
}
