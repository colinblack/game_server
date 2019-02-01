/*
 * LogicNewWorldBattle.cpp
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */

#include "LogicNewWorldBattle.h"

#define NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult) \
	const NewWorldBattleChangeMap &change = pData->GetChangeMap(); \
	if(!change.empty()) \
	{ \
		unsigned i = 0; \
		allresult["change"].resize(change.size()); \
		for(NewWorldBattleChangeMap::const_iterator it=change.begin();it!=change.end();++it) \
		{ \
			allresult["change"][i].resize(3u); \
			allresult["change"][i][0u] = it->second.cid; \
			allresult["change"][i][1u] = it->second.kingdom; \
			allresult["change"][i][2u] = it->second.battle; \
			++i; \
		} \
		pData->ClearChangeMap(); \
	} \


CLogicNewWorldBattle::CLogicNewWorldBattle() {
	// TODO Auto-generated constructor stub

}
CLogicNewWorldBattle::~CLogicNewWorldBattle() {
	// TODO Auto-generated destructor stub
}

CDataNewWorldBattle *CLogicNewWorldBattle::GetDataNewWorldBattle()
{
	GET_MEM_DATA_SEM(CDataNewWorldBattle, CONFIG_NEW_WORLD_BATTLE_DATA, sem_new_world_battle, false)
}

int CLogicNewWorldBattle::GetWorld(Json::Value &allresult)
{
	Json::Value &result = allresult["GetWorld"];

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	result.resize(NEW_WORLD_BATTLE_CITY);
	unsigned i = 0;
	const NewWorldBattleCityMap &world = pData->GetWorld();
	for(NewWorldBattleCityMap::const_iterator it=world.begin();it!=world.end();++it)
	{
		result[i]["id"]		 = it->second.city.cid;
		result[i]["kingdom"] = it->second.city.kingdom;
		result[i]["status"]	 = it->second.city.Fighting() ? 1 : 0;
		result[i]["damage"]  = it->second.city.damage;
		result[i]["extraKillTS"][0u] = it->second.city.extraKillTS[0];
		result[i]["extraKillTS"][1u] = it->second.city.extraKillTS[1];
		result[i]["extraKillTS"][2u] = it->second.city.extraKillTS[2];
		result[i]["extraKillTS"][3u] = it->second.city.extraKillTS[3];
		result[i]["tower"]["uid"] = it->second.city.tower.uid;
		result[i]["tower"]["dps"] = it->second.city.tower.dps;
		result[i]["tower"]["hit"] = it->second.city.tower.hit;
		++i;
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldBattle::GetCity(unsigned cid, Json::Value &allresult)
{
	Json::Value &result = allresult["GetCity"];

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	const NewWorldBattleCityBattle &city = pData->GetCity(cid);
	if(city.city.cid != cid)
	{
		error_log("GetCity fail, cid=%u",cid);
		return R_ERR_PARAM;
	}

	result["id"]		 = city.city.cid;
	result["kingdom"]	 = city.city.kingdom;
	result["battle"][0u] = city.city.count[0];
	result["battle"][1u] = city.city.count[1];
	result["battle"][2u] = city.city.count[2];
	result["battle"][3u] = city.city.count[3];
	result["battle"][4u] = city.city.countN;
	result["npcts"]		 = city.city.npcts;
	result["reward"]	 = city.city.reward;
	result["nextReward"] = city.city.nextReward;
	result["status"]	 = city.city.Fighting() ? 1 : 0;
	result["damage"]	 = city.city.damage;
	result["extraKillTS"][0u] = city.city.extraKillTS[0];
	result["extraKillTS"][1u] = city.city.extraKillTS[1];
	result["extraKillTS"][2u] = city.city.extraKillTS[2];
	result["extraKillTS"][3u] = city.city.extraKillTS[3];
	result["tower"]["uid"] = city.city.tower.uid;
	result["tower"]["dps"] = city.city.tower.dps;
	result["tower"]["hit"] = city.city.tower.hit;

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldBattle::GetBattle(unsigned cid, Json::Value &allresult)
{
	Json::Value &result = allresult["GetBattle"];

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	const NewWorldBattleCityBattle &city = pData->GetCity(cid);
	if(city.city.cid != cid)
	{
		error_log("GetCity fail, cid=%u",cid);
		return R_ERR_PARAM;
	}

	result["upts"] = pData->GetTS() + NEW_WORLD_BATTLE_TICK;
	result["battle"][0u] = city.city.count[0];
	result["battle"][1u] = city.city.count[1];
	result["battle"][2u] = city.city.count[2];
	result["battle"][3u] = city.city.count[3];
	result["battle"][4u] = city.city.countN;
	result["kingdom"]	 = city.city.kingdom;
	result["status"]	 = city.city.Fighting() ? 1 : 0;
	result["damage"]	 = city.city.damage;
	result["extraKillTS"][0u] = city.city.extraKillTS[0];
	result["extraKillTS"][1u] = city.city.extraKillTS[1];
	result["extraKillTS"][2u] = city.city.extraKillTS[2];
	result["extraKillTS"][3u] = city.city.extraKillTS[3];
	result["tower"]["uid"] = city.city.tower.uid;
	result["tower"]["dps"] = city.city.tower.dps;
	result["tower"]["hit"] = city.city.tower.hit;

	if(city.city.attacker.uid)
	{
		if(CDataNewWorldBattle::notHero(city.city.attacker))
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
			result["attacker1"]["property"].resize(NewWorldBattleProperty_max);
			for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
				result["attacker1"]["property"][i] = city.city.vision[city.city.attacker.index].property[i];
		}
		else
		{
			const NewWorldBattleHero &hero = pData->GetHero(city.city.attacker);
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
				result["attacker1"]["property"].resize(NewWorldBattleProperty_max);
				for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
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
		if(CDataNewWorldBattle::notHero(city.city.defender))
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
			result["defender1"]["property"].resize(NewWorldBattleProperty_max);
			for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
				result["defender1"]["property"][i] = city.city.vision[city.city.defender.index].property[i];
		}
		else
		{
			const NewWorldBattleHero &hero = pData->GetHero(city.city.defender);
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
				result["defender1"]["property"].resize(NewWorldBattleProperty_max);
				for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
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
		NewWorldBattleCityQueue::const_iterator it = city.attacker.begin();
		if(CDataNewWorldBattle::notHero(it->second))
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
			result["attacker2"]["property"].resize(NewWorldBattleProperty_max);
			for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
				result["attacker2"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldBattleHero &hero = pData->GetHero(it->second);
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
				result["attacker2"]["property"].resize(NewWorldBattleProperty_max);
				for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
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
		NewWorldBattleCityQueue::const_iterator it = city.defender.begin();
		if(CDataNewWorldBattle::notHero(it->second))
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
			result["defender2"]["property"].resize(NewWorldBattleProperty_max);
			for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
				result["defender2"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldBattleHero &hero = pData->GetHero(it->second);
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
				result["defender2"]["property"].resize(NewWorldBattleProperty_max);
				for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
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
		result["defender2"]["index"]	 = NEW_WORLD_BATTLE_CITY_VISION;
		result["defender2"]["job"]	 = (city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].job + 1) % NewWorldBattleHeroJob_max + 1;
		result["defender2"]["type"]	 = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].getType();
		result["defender2"]["heroID"] = CDataXML::Hero2Str((city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].job + 1) % NewWorldBattleHeroJob_max + 1);
		result["defender2"]["name"]	 = string("NPC");
		result["defender2"]["kingdom"]= city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].kingdom;
		result["defender2"]["level"]	 = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].level;
		result["defender2"]["hp"]	 = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].property[NewWorldBattleProperty_hp];
		result["defender2"]["property"].resize(NewWorldBattleProperty_max);
		for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
			result["defender2"]["property"][i] = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].property[i];
	}*/
	if(city.attacker.size() > 1)
	{
		NewWorldBattleCityQueue::const_iterator it = city.attacker.begin();
		++it;
		if(CDataNewWorldBattle::notHero(it->second))
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
			result["attacker3"]["property"].resize(NewWorldBattleProperty_max);
			for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
				result["attacker3"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldBattleHero &hero = pData->GetHero(it->second);
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
				result["attacker3"]["property"].resize(NewWorldBattleProperty_max);
				for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
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
		NewWorldBattleCityQueue::const_iterator it = city.defender.begin();
		++it;
		if(CDataNewWorldBattle::notHero(it->second))
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
			result["defender3"]["property"].resize(NewWorldBattleProperty_max);
			for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
				result["defender3"]["property"][i] = city.city.vision[it->second.index].property[i];
		}
		else
		{
			const NewWorldBattleHero &hero = pData->GetHero(it->second);
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
				result["defender3"]["property"].resize(NewWorldBattleProperty_max);
				for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
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
		result["defender3"]["index"]	 = NEW_WORLD_BATTLE_CITY_VISION;
		result["defender3"]["job"]	 = (city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].job + 2) % NewWorldBattleHeroJob_max + 1;
		result["defender3"]["type"]	 = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].getType();
		result["defender3"]["heroID"] = CDataXML::Hero2Str((city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].job + 2) % NewWorldBattleHeroJob_max + 1);
		result["defender3"]["name"]	 = string("NPC");
		result["defender3"]["kingdom"]= city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].kingdom;
		result["defender3"]["level"]	 = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].level;
		result["defender3"]["hp"]	 = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].property[NewWorldBattleProperty_hp];
		result["defender3"]["property"].resize(NewWorldBattleProperty_max);
		for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
			result["defender3"]["property"][i] = city.city.vision[NEW_WORLD_BATTLE_CITY_VISION].property[i];
	}*/

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldBattle::GetBattleList(unsigned cid, unsigned camp, Json::Value &allresult)
{
	Json::Value &result = allresult["GetBattleList"];

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	const NewWorldBattleCityBattle &city = pData->GetCity(cid);
	if(city.city.cid != cid)
	{
		error_log("GetCity fail, cid=%u",cid);
		return R_ERR_PARAM;
	}

	result.resize(0);
	const NewWorldBattleCityQueue &list = camp?city.attacker:city.defender;
	for(NewWorldBattleCityQueue::const_iterator it=list.begin();it!=list.end();++it)
	{
		Json::Value temp;
		if(CDataNewWorldBattle::notHero(it->second))
		{
			const NewWorldBattleHero &hero = city.city.vision[it->second.index];
			temp["vision"]		 = 1;
			temp["heroID"]		 = CDataXML::Hero2Str(hero.hid);
			temp["kingdom"]		 = hero.kingdom;
			temp["name"]		 = hero.name;
			temp["index"]		 = hero.index.index;
			temp["hp"]			 = hero.hp;
			temp["maxhp"]		 = hero.property[NewWorldBattleProperty_hp];
		}
		else
		{
			const NewWorldBattleHero &hero = pData->GetHero(it->second);
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
			temp["maxhp"]		 = hero.property[NewWorldBattleProperty_hp];
		}

		result.append(temp);
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldBattle::GetHero(unsigned uid, unsigned index, Json::Value &allresult)
{
	Json::Value &result = allresult["GetHero"];

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	NewWorldBattleHeroIndex heroindex(uid, index);
	const NewWorldBattleHero &hero = pData->GetHero(heroindex);
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
	result["property"].resize(NewWorldBattleProperty_max);
	for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
		result["property"][i] = hero.property[i];
	result["kill"]	 = hero.kill;

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldBattle::GetAllHero(unsigned uid,Json::Value &allresult)
{
	Json::Value &result = allresult["GetAllHero"];

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	result.resize(0);
	const NewWorldBattleHeroMap &heromap = pData->GetAllHero();
	for(unsigned i=0;i<NEW_WORLD_BATTLE_HERO_INDEX;++i)
	{
		NewWorldBattleHeroIndex index(uid,i);
		NewWorldBattleHeroMap::const_iterator hero = heromap.find(index);
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
			temp["property"].resize(NewWorldBattleProperty_max);
			for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
				temp["property"][i] = hero->second.property[i];
			temp["kill"]	 = hero->second.kill;
			result.append(temp);
		}
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldBattle::SetHero(unsigned uid, unsigned index, const Json::Value &para, Json::Value &allresult)
{
	Json::Value &result = allresult["SetHero"];

	int ret = 0;
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
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

	NewWorldBattleHero hero;
	hero.index.uid		= uid;
	hero.index.index	= index;
	hero.kingdom		= kingdom;
	hero.level			= level;
	hero.job			= (job - 1)%NewWorldBattleHeroJob_max;

	if(!heroid.empty())
		hero.hid		= CDataXML::Str2Hero(heroid);
	if(!name.empty())
		strncpy(hero.name, name.c_str(), sizeof(hero.name)-1);
	if(para.isMember("property") && para["property"].isArray() && para["property"].size()<=NewWorldBattleProperty_max)
	{
		for(unsigned i=0;i<para["property"].size();++i)
			hero.property[i] = para["property"][i].asUInt();
		/*
		hero.property[NewWorldBattleProperty_hp] = CDataNewWorldBattle::getAttDefHP(hero.property[NewWorldBattleProperty_hp]);
		hero.property[NewWorldBattleProperty_attack] = CDataNewWorldBattle::getAttDefHP(hero.property[NewWorldBattleProperty_attack]);
		hero.property[NewWorldBattleProperty_defence] = CDataNewWorldBattle::getAttDefHP(hero.property[NewWorldBattleProperty_defence]);
		hero.property[NewWorldBattleProperty_extra] = CDataNewWorldBattle::getAttDefHP(hero.property[NewWorldBattleProperty_extra]);
		hero.property[NewWorldBattleProperty_anti_extra] = CDataNewWorldBattle::getAttDefHP(hero.property[NewWorldBattleProperty_anti_extra]);
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
	result["property"].resize(NewWorldBattleProperty_max);
	for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
		result["property"][i] = hero.property[i];

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldBattle::Move(unsigned uid, unsigned index, unsigned cid, bool leave, unsigned fly, Json::Value &allresult)
{
	Json::Value &result = allresult["Move"];

	int ret = 0;
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	unsigned status;
	ret = pData->Move(NewWorldBattleHeroIndex(uid, index), cid, leave, fly, status);
	result["status"] = status;
	if(ret)
	{
		if(ret != R_ERR_LOGIC)
			error_log("Move fail, uid=%u, index=%u, cid=%u, ret=%u",uid, index, cid, ret);
		return ret;
	}

	// modify by Cream
	// true == fly
	// 不消耗 r1
	if (!fly)
	{
		CLogicUser logicUser;
		DataUser dataUser;
		AUTO_LOCK_USER(uid)
		ret = logicUser.GetUserLimit(uid,dataUser);
		if(ret)
		{
			return ret;
		}
		int r1 = -CDataNewWorldBattle::GetMoveR1(dataUser.level);
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

	result["upts"] = pData->GetTS() + NEW_WORLD_BATTLE_TICK * 2;

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldBattle::Change(unsigned uid, unsigned index, unsigned type, Json::Value &allresult)
{
	int ret = 0;
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	ret = pData->Change(NewWorldBattleHeroIndex(uid, index), type);
	if(ret)
	{
		error_log("Change fail, uid=%u, index=%u, type=%u, ret=%u",uid, index, type, ret);
		return ret;
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldBattle::Clone(unsigned uid, unsigned index, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if(equipment.Try(uid, NEW_WORLD_BATTLE_CLONE_COST, equd, 1))
		return R_ERR_PARAM;

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	ret = pData->Clone(NewWorldBattleHeroIndex(uid, index));
	if(ret)
	{
		error_log("Clone fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}

	AUTO_LOCK_USER(uid)
	ret = equipment.UseEquipment(uid, NEW_WORLD_BATTLE_CLONE_COST, equd, 1, "NEW_WORLD_BATTLE_clone");
	if(ret)
	{
		error_log("NEW_WORLD_BATTLE_clone uid=%u, equd=%u", uid , equd);
		return R_ERR_DATA;
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
int CLogicNewWorldBattle::Recover(unsigned uid, unsigned index, unsigned equd, unsigned num, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if(equipment.Try(uid, NEW_WORLD_BATTLE_RECOVER_COST, equd, num))
		return R_ERR_PARAM;

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	ret = pData->Recover(NewWorldBattleHeroIndex(uid, index), num);
	if(ret)
	{
		error_log("Recover fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}

	AUTO_LOCK_USER(uid)
	ret = equipment.UseEquipment(uid, NEW_WORLD_BATTLE_RECOVER_COST, equd, num, "NEW_WORLD_BATTLE_recover");
	if(ret)
	{
		error_log("NEW_WORLD_BATTLE_recover uid=%u, equd=%u", uid , equd);
		return R_ERR_DATA;
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldBattle::Rush(unsigned uid, unsigned index, unsigned equd, bool fly, Json::Value &allresult)
{
	Json::Value &result = allresult["Rush"];

	int ret = 0;
	CLogicEquipment equipment;
	if(!fly && equipment.Try(uid, NEW_WORLD_BATTLE_RUSH_COST, equd, 1))
		return R_ERR_PARAM;

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	NewWorldBattleHero other, end;
	ret = pData->Rush(NewWorldBattleHeroIndex(uid, index), other, end);
	if(ret)
		return ret;

	if(!fly)
	{
		AUTO_LOCK_USER(uid)
		ret = equipment.UseEquipment(uid, NEW_WORLD_BATTLE_RUSH_COST, equd, 1, "NEW_WORLD_BATTLE_rush");
		if(ret)
		{
			error_log("NEW_WORLD_BATTLE_rush uid=%u, equd=%u", uid , equd);
			return R_ERR_DATA;
		}
	}

	result["other"]["vision"] = CDataNewWorldBattle::notHero(other.index)?1:0;
	result["other"]["uid"]	 = other.index.uid;
	result["other"]["index"]	 = other.index.index;
	result["other"]["job"]	 = other.getJob();
	result["other"]["type"]	 = other.getType();
	result["other"]["heroID"] = CDataXML::Hero2Str(other.hid);
	result["other"]["name"]	 = string(other.name);
	result["other"]["kingdom"]= other.kingdom;
	result["other"]["level"]	 = other.level;
	result["other"]["hp"]	 = other.hp;
	result["other"]["property"].resize(NewWorldBattleProperty_max);
	for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
		result["other"]["property"][i] = other.property[i];

	result["end"]["vision"] = CDataNewWorldBattle::notHero(end.index)?1:0;
	result["end"]["uid"]	 = end.index.uid;
	result["end"]["index"]	 = end.index.index;
	result["end"]["job"]	 = end.getJob();
	result["end"]["type"]	 = end.getType();
	result["end"]["heroID"] = CDataXML::Hero2Str(end.hid);
	result["end"]["name"]	 = string(end.name);
	result["end"]["kingdom"]= end.kingdom;
	result["end"]["level"]	= end.level;
	result["end"]["hp"]	 = end.hp;
	result["end"]["property"].resize(NewWorldBattleProperty_max);
	for(unsigned i=0;i<NewWorldBattleProperty_max;++i)
		result["end"]["property"][i] = end.property[i];

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldBattle::KillRank(string path)
{
	int ret = 0;
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	const NewWorldBattleHeroMap &heromap = pData->GetAllHero();
	map<unsigned, unsigned> herokill;
	map<unsigned, string> heroname;
	map<unsigned, unsigned> herokingdom;
	for(NewWorldBattleHeroMap::const_iterator it=heromap.begin();it!=heromap.end();++it)
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
				herokingdom[it->first.uid] = it->second.kingdom;
			}
			herokill[it->first.uid] += it->second.kill;
		}
	}
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
		rank[i]["kingdom"] = herokingdom[it->second];
		rank[i]["kill"] = it->first;
		rank[i]["level"] = user.level;
		rank[i]["exp"] = CDataNewWorldBattle::GetKillExp(it->first, user.level);

		++i;
		if(i == 100)
			break;
	}

	ret = File::Write(path, Json::ToString(rank));
	if(ret)
	{
		cout<<"write NewWorldBattle fail"<<endl;
		return ret;
	}

	return 0;
}

int CLogicNewWorldBattle::KillReward()
{
	int ret = 0;
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	const NewWorldBattleHeroMap &heromap = pData->GetAllHero();
	if(heromap.size() == 0)
		return 0;
	map<unsigned, unsigned> herokill;
	map<unsigned, unsigned> herokingdom;
	for(NewWorldBattleHeroMap::const_iterator it=heromap.begin();it!=heromap.end();++it)
	{
		if(it->second.kill)
		{
			if(!herokill.count(it->first.uid))
			{
				herokill[it->first.uid] = 0;
				herokingdom[it->first.uid] = it->second.kingdom;
			}
			herokill[it->first.uid] += it->second.kill;
		}
	}

	multimap<unsigned, unsigned> killhero;
	for(map<unsigned, unsigned>::iterator it=herokill.begin();it!=herokill.end();++it)
		killhero.insert(pair<unsigned, unsigned>(it->second, it->first));

	unsigned kingdom[4], result;
	pData->GetKillRewardResult(kingdom, result);
	int serverid = 0, domain = 0;
	Config::GetDB(domain);
	serverid = MainConfig::GetMergedDomain(domain);
	CLogicAllServerNewWorldBattle logicAllServerNewWorldBattle;
	logicAllServerNewWorldBattle.SetResult(serverid, result);

	unsigned i = 0;
	DataUser user;
	CLogicUser logicUser;
	CLogicUpdates logicUpdates;
	CLogicEquipment logicEquipment;
	for(multimap<unsigned, unsigned>::reverse_iterator it=killhero.rbegin();it!=killhero.rend();++it)
	{
		if(it->first == 0)
			break;

		AUTO_LOCK_USER(it->second)
		logicUser.GetUserLimit(it->second, user);
		unsigned exp = CDataNewWorldBattle::GetKillExp(it->first, user.level);
		user.point += exp;
		if(logicUser.SetUserLimit(it->second, user) == 0)
		{
			RESOURCE_LOG("[NEWWORLDBATTLEKILLREWARD][uid=%u,expchg=%u,exp=%u]",it->second, exp, user.point);
		}

		++i;
		Json::Value update, res;
		unsigned k = herokingdom[it->second];
		if(k >= 1 && k <= 4)
			k = kingdom[k-1];
		else
			k = 1;
		unsigned cr = CDataNewWorldBattle::GetKillRewardNew(i);
		unsigned cp = CDataNewWorldBattle::GetKillRewardP(it->first);
		unsigned count = (cr + cp) * k;
		if(count && logicEquipment.AddOneItem(it->second,NEW_WORLD_BATTLE_KILL_REWARD_NEW,count,"NEWWORLDBATTLEKILLREWARD",res) == 0)
		{
			update["ts"] = Time::GetGlobalTime();
			update["s"] = "NEWWORLDBATTLEKILLREWARD";
			update["rank"] = i;
			update["e"] = NEW_WORLD_BATTLE_KILL_REWARD_NEW;
			update["cr"] = cr;
			update["cp"] = cp;
			update["k"] = k;
			update["result"] = result;
			logicUpdates.AddUpdates(it->second,update,true);
		}
	}

	return 0;
}

int CLogicNewWorldBattle::Watch()
{
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
		return R_ERR_DATA;
	return pData->Watch();
}
int CLogicNewWorldBattle::Fix()
{
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
		return R_ERR_DATA;
	return pData->Fix();
}
int CLogicNewWorldBattle::Reset()
{
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
		return R_ERR_DATA;
	return pData->Reset();
}
int CLogicNewWorldBattle::Back()
{
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
		return R_ERR_DATA;
	return pData->Back();
}
int CLogicNewWorldBattle::Test(NewWorldBattleHero &attacker, unsigned hpa, NewWorldBattleHero &defender, unsigned hpd)
{
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
		return R_ERR_DATA;
	return pData->Test(attacker, hpa, defender, hpd);
}
int CLogicNewWorldBattle::Test(NewWorldBattleHero &attacker, NewWorldBattleHero &defender, unsigned &times)
{
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
		return R_ERR_DATA;
	float hpa = 100.0f, hpd = 100.0f;
	times = 0;
	do
	{
		++times;
		if(pData->Test(attacker, hpa, defender, hpd))
			return R_ERR_PARAM;
		hpa = 100.0f;
		hpd = (float)defender.hp / (float)defender.property[NewWorldBattleProperty_hp] * 100.0f;
	}while(defender.hp > 0);
	return 0;
}

int CLogicNewWorldBattle::Restart()
{
	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
		return R_ERR_DATA;
	return pData->Restart();
}


int CLogicNewWorldBattle::Double(unsigned uid, unsigned kingdom, unsigned cid, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if(equipment.Try(uid, NEW_WORLD_BATTLE_DOUBLE_COST, equd, 1))
		return R_ERR_PARAM;

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	ret = pData->Double(uid, kingdom, cid);
	if(ret)
	{
		error_log("Double fail, uid=%u, cid=%u, ret=%u",uid, cid, ret);
		return ret;
	}

	AUTO_LOCK_USER(uid)
	ret = equipment.UseEquipment(uid, NEW_WORLD_BATTLE_DOUBLE_COST, equd, 1, "NEW_WORLD_BATTLE_DOUBLE");
	if(ret)
	{
		error_log("NEW_WORLD_BATTLE_DOUBLE uid=%u, equd=%u", uid , equd);
		return R_ERR_DATA;
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}

int CLogicNewWorldBattle::CollectOther(unsigned uid, unsigned cid, unsigned equd, Json::Value &allresult)
{
	int ret = 0;
	CLogicEquipment equipment;
	if (equipment.Try(uid, NEW_WORLD_BATTLE_COLLECTOTHER_COST, equd, 1))
	{
		return R_ERR_PARAM;
	}

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	ret = pData->CollectOther(uid, cid);
	if (ret)
	{
		error_log("CollectOther fail, uid=%u, cid=%d, ret=%u", uid, cid, ret);
		return ret;
	}

	// 消耗道具
	AUTO_LOCK_USER(uid)
	ret = equipment.UseEquipment(uid, NEW_WORLD_BATTLE_COLLECTOTHER_COST, equd, 1, "NEW_WORLD_BATTLE_COLLECTOTHER");
	if (ret)
	{
		error_log("NEW_WORLD_BATTLE_COLLECTOTHER uid=%u, equd=%u", uid, equd);
		return R_ERR_DATA;
	}

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData, allresult)

	return 0;
}


int CLogicNewWorldBattle::Blink(unsigned uid, unsigned cid, unsigned equd, const Json::Value &freeHeroIndex, Json::Value &allresult)
{
	Json::Value &result = allresult["Blink"];
	int ret = 0;
	CLogicEquipment equip;

	if (equip.Try(uid, NEW_WORLD_BATTLE_BLINK_COST, equd, 1))
	{
		return R_ERR_PARAM;
	}

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle failed");
		return R_ERR_DATA;
	}

	unsigned heroIndex;
	unsigned status;
	unsigned i;

	for (i = 0; i < freeHeroIndex.size(); ++i)
	{
		heroIndex = freeHeroIndex[i].asUInt();
		ret = pData->Move(NewWorldBattleHeroIndex(uid, heroIndex), cid, false, 2, status);
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
		ret = equip.UseEquipment(uid, NEW_WORLD_BATTLE_BLINK_COST, equd, 1, "new_world_Blink");
		if (ret)
		{
			error_log("new_world_battle_Blink uid = %u, equd = %u", uid, equd);
			return R_ERR_DATA;
		}

	}

	result["upts"] = pData->GetTS() + NEW_WORLD_BATTLE_TICK * 2;
	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)

	return 0;
}

int CLogicNewWorldBattle::Buildyjt(unsigned uid, unsigned index, Json::Value &allresult)
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

	CDataNewWorldBattle *pData = GetDataNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataNewWorldBattle fail");
		return R_ERR_DATA;
	}

	ret = pData->Buildyjt(NewWorldBattleHeroIndex(uid, index));
	if(ret)
	{
		error_log("Buildyjt fail, uid=%u, index=%u, ret=%u",uid, index, ret);
		return ret;
	}

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
	ret = logicPay.ProcessOrderForBackend(uid, -20, 0, payData, "CDataBraveNewWorldBattle_Buildyjt",user_flag,bsave);
	if(ret)
		return ret;
	if(bsave)
		dataUser.user_flag = writer.write(user_flag);
	ret = logicUser.SetUser(uid, dataUser);
	if(ret)
		return ret;

	NEW_WORLD_BATTLE_PROCESS_CHANGE(pData,allresult)
	return 0;
}
