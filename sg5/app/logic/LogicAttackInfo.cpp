/*
 * LogicAttackInfo.cpp
 *
 *  Created on: 2017年6月1日
 *      Author: Administrator
 */

#include <fstream>
#include "LogicAttackInfo.h"

CLogicAttackInfo::CLogicAttackInfo(unsigned uid)
{
	m_uid = uid;
	m_hero.clear();
	m_building.clear();
	m_res.clear();
	m_attackts = 0;
}

CLogicAttackInfo::~CLogicAttackInfo()
{
}

int CLogicAttackInfo::GetInfo(Json::Value &result)
{
	int ret = 0;
	Json::Value &hero = result["hero"];
	hero = Json::Value(Json::arrayValue);
	hero.resize(0);
	Json::Value &building = result["building"];
	building = Json::Value(Json::arrayValue);
	building.resize(0);
	Json::Value &res = result["res"];
	res = Json::Value(Json::arrayValue);
	res.resize(4);
	for(size_t i=0; i<result["res"].size(); ++i)
	{
		result["res"][i] = 0;
	}
	result["attackts"] = 0;
	ret = Read(result);
	if (ret)
	{
		return ret;
	}
	return 0;
}

int CLogicAttackInfo::SetInfo(const Json::Value &data)
{
	if (data.isMember("building") && data["building"].isArray())
	{
		for (size_t i = 0; i < data["building"].size(); ++i)
		{
			if (!data["building"][i].isObject())
			{
				continue;
			}
			unsigned ud = 0;
			Json::GetUInt(data["building"][i], "ud", ud);
			int hp = 0;
			Json::GetInt(data["building"][i], "hp", hp);
			int res = 0;
			Json::GetInt(data["building"][i], "res", res);
			if (hp != 0 || res != 0)
			{
				AttackBuilding building(ud, hp, res);
				m_building.insert(make_pair(ud, building));
			}
		}
	}
	if (data.isMember("hero") && data["hero"].isArray())
	{
		for (size_t i = 0; i < data["hero"].size(); ++i)
		{
			if (!data["hero"][i].isObject())
			{
				continue;
			}
			unsigned ud = 0;
			Json::GetUInt(data["hero"][i], "ud", ud);
			int hp = 0;
			Json::GetInt(data["hero"][i], "hp", hp);
			if (hp != 0)
			{
				m_hero.insert(make_pair(ud, hp));
			}
		}
	}
	if (data.isMember("res") && data["res"].isArray())
	{
		for (size_t i = 0; i < data["res"].size(); ++i)
		{
			int count = 0;
			Json::GetInt(data["res"], i, count);
			if (count != 0)
			{
				m_res.insert(make_pair(i, count));
			}
		}
	}

	Json::GetUInt(data, "attackts", m_attackts);

	if (m_building.empty() && m_hero.empty() && m_res.empty() && m_attackts == 0)
	{
		return 0;
	}

	int ret = Save();
	if (ret)
	{
		error_log("[Save error][ret=%d,uid=%u]", ret, m_uid);
		return ret;
	}
	return 0;
}

int CLogicAttackInfo::ClearBuildingInfo()
{
	int ret = Save(true);
	if (ret)
	{
		error_log("[Save error][ret=%d,uid=%u]", ret, m_uid);
		return ret;
	}
	return 0;
}

int CLogicAttackInfo::Read(Json::Value &result)
{
	string dataPath;
	int ret = 0;
	ret = GetDataPath(dataPath);
	if (ret)
	{
		return ret;
	}
	ret = access(dataPath.c_str(), F_OK);
	if (ret == -1)
	{
		return 0;
	}
	fstream input(dataPath.c_str(), ios::in | ios::binary);
	if (!input)
	{
		error_log("create new %s", dataPath.c_str());
		return R_ERR_NO_DATA;
	}
	ProtoAttackInfo::ProtoAttackInfo protoData;
	protoData.ParseFromIstream(&input);
	for (unsigned i = 0; i < protoData.hero_size(); ++i)
	{
		unsigned ud = protoData.hero(i).ud();
		unsigned hp = protoData.hero(i).hp();
		if (hp > 0)
		{
			Json::Value temp;
			temp["ud"] = ud;
			temp["hp"] = hp;
			result["hero"].append(temp);
		}
	}
	for (unsigned i = 0; i < protoData.building_size(); ++i)
	{
		unsigned ud = protoData.building(i).ud();
		unsigned hp = protoData.building(i).hp();
		unsigned res = protoData.building(i).res();
		if (hp > 0 || res > 0)
		{
			Json::Value temp;
			temp["ud"] = ud;
			temp["hp"] = hp;
			temp["res"] = res;
			result["building"].append(temp);
		}
	}
	for (unsigned i = 0; i < protoData.res_size(); ++i)
	{
		unsigned id = protoData.res(i).id();
		unsigned c = protoData.res(i).count();
		result["res"][id] = c;
	}
	result["attackts"] = protoData.attackts();
	return 0;
}

int CLogicAttackInfo::Save(bool isclearbuilding)
{
	int ret = 0;
	string dataPath;
	ret = GetDataPath(dataPath);
	if (ret)
	{
		return ret;
	}
	ProtoAttackInfo::ProtoAttackInfo protoDataRead;
	protoDataRead.Clear();
	ret = access(dataPath.c_str(), F_OK);
	if (ret == 0)
	{
		fstream input(dataPath.c_str(), ios::in | ios::binary);
		if (!input)
		{
			error_log("create new %s", dataPath.c_str());
			return R_ERR_NO_DATA;
		}
		protoDataRead.ParseFromIstream(&input);
	}

	for (size_t i = 0; i < protoDataRead.building_size(); ++i)
	{
		unsigned ud = protoDataRead.building(i).ud();
		unsigned hp = protoDataRead.building(i).hp();
		unsigned res = protoDataRead.building(i).res();
		if (m_building.count(ud) == 0)
		{
			AttackBuilding buiding;
			m_building[ud] = buiding;
		}
		if (m_building[ud].hp < 0 && unsigned(0 - m_building[ud].hp) > hp)
		{
			m_building[ud].hp = 0;
		}
		else
		{
			m_building[ud].hp += hp;
		}

		if (m_building[ud].res < 0 && unsigned(0 - m_building[ud].res) > res)
		{
			m_building[ud].res = 0;
		}
		else
		{
			m_building[ud].res += res;
		}

		if (m_building[ud].res == 0 && m_building[ud].hp == 0)
		{
			m_building.erase(ud);
		}
	}

	for (size_t i = 0; i < protoDataRead.hero_size(); ++i)
	{
		unsigned ud = protoDataRead.hero(i).ud();
		unsigned hp = protoDataRead.hero(i).hp();
		if (m_hero.count(ud) == 0)
		{
			m_hero[ud] = hp;
		}
		else
		{
			if (m_hero[ud] < 0 && unsigned(0 - m_hero[ud]) > hp)
			{
				m_hero.erase(ud);
			}
			else
			{
				m_hero[ud] += hp;
			}
		}
	}

	for (size_t i = 0; i < protoDataRead.res_size(); ++i)
	{
		unsigned id = protoDataRead.res(i).id();
		unsigned resV = protoDataRead.res(i).count();
		if (m_res.count(id) == 0)
		{
			m_res[id] = resV;
		}
		else
		{
			if (m_res[id] < 0 && unsigned(0 - m_res[id]) > resV)
			{
				m_res[id] = 0;
			}
			else
			{
				m_res[id] += resV;
			}
		}
	}

	ProtoAttackInfo::ProtoAttackInfo protoDataWrite;
	for (map<unsigned, int>::const_iterator itr = m_hero.begin(); itr != m_hero.end(); ++itr)
	{
		ProtoAttackInfo::ProtoAttackHero *pHero = protoDataWrite.add_hero();
		pHero->set_ud(itr->first);
		pHero->set_hp(itr->second);
	}
	if (isclearbuilding)
		m_building.clear();
	for (map<unsigned, AttackBuilding>::const_iterator itr = m_building.begin(); itr != m_building.end(); ++itr)
	{
		ProtoAttackInfo::ProtoAttackBuilding *pBuilding = protoDataWrite.add_building();
		pBuilding->set_ud(itr->first);
		pBuilding->set_hp(itr->second.hp);
		pBuilding->set_res(itr->second.res);
	}
	for (map<unsigned, int>::const_iterator itr = m_res.begin(); itr != m_res.end(); ++itr)
	{
		ProtoAttackInfo::ProtoAttackRes *pRes = protoDataWrite.add_res();
		pRes->set_id(itr->first);
		pRes->set_count(itr->second);
	}
	protoDataWrite.set_attackts(m_attackts);

	fstream output(dataPath.c_str(), ios::out | ios::trunc | ios::binary);
	if (!output)
	{
		error_log("save new %s", dataPath.c_str());
		return R_ERR_NO_DATA;
	}
	protoDataWrite.SerializeToOstream(&output);
	return 0;
}

int CLogicAttackInfo::GetDataPath(string &dataPath)
{
	dataPath = Config::GetPath("data/attackinfo/");
	if (dataPath.empty())
	{
		error_log("[data path empty]");
		return R_ERR_DATA;
	}
	if (dataPath[dataPath.length() - 1] != '/')
	{
		dataPath.append("/");
	}
	dataPath.append(CTrans::ITOS(m_uid)).append(".dat");
	return 0;
}
