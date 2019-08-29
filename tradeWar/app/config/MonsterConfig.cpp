/*
 * MonsterConfig.cpp
 *
 *  Created on: 2016年1月26日
 *      Author: asdf
 */
#include "MonsterConfig.h"

MonsterConfig::MonsterConfig()
{

}
MonsterConfig::~MonsterConfig()
{

}

bool MonsterConfig::init(const string & path)
{
	return initJson(path);

	CMarkupSTL xmlConf;
	if(!xmlConf.Load(path.c_str()))
	{
		error_log("load_fail");
		return false;
	}
	if(!xmlConf.FindElem("content") )
	{
		error_log("find_node_content_fail");
		return false;
	}
	xmlConf.IntoElem();
	if(!xmlConf.FindElem("mosters") )
	{
		error_log("find_node_mosters_fail");
		return false;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("moster"))
	{
		string idStr = xmlConf.GetAttrib("id");
		string idInt = idStr.substr(1,idStr.length()-1);
		uint32_t id = CTrans::STOI(idInt);
		string type = xmlConf.GetAttrib("type");
		string prof = xmlConf.GetAttrib("prof");
		MonsterItemConfig& mic = m_mapItemConfig[id];
		mic.id = id;
		mic.type = CTrans::STOI(type);
		mic.prof = CTrans::STOI(prof);

		xmlConf.IntoElem();

		xmlConf.ResetMainPos();
		if(xmlConf.FindElem("sp"))
		{
			string spStr = xmlConf.GetData();
			mic.sp = CTrans::STOI(spStr.substr(1, spStr.length() - 2));
		}

		xmlConf.ResetMainPos();
		if(xmlConf.FindElem("range"))
		{
			string rangeStr = xmlConf.GetData();
			mic.range = CTrans::STOI(rangeStr.substr(1, rangeStr.length() - 2));
		}

		xmlConf.ResetMainPos();
		if(xmlConf.FindElem("hurtrate"))
		{
			string cat = DELETE_TOKEN(xmlConf.GetData());
			vector<string> vec;
			String::Split(cat.c_str(), ',', vec);
			uint32_t vecSize = vec.size();
			mic.hurtBuildingRatio = (vecSize == 4) ? CTrans::STOI(vec[0]) : RET_NO_EXIST_PROP;
			mic.hurtAirRatio = (vecSize == 4) ? CTrans::STOI(vec[1]) : RET_NO_EXIST_PROP;
			mic.hurtArmyRatio = (vecSize == 4) ? CTrans::STOI(vec[2]) : RET_NO_EXIST_PROP;
			mic.hurtNavyRatio = (vecSize == 4) ? CTrans::STOI(vec[3]) : RET_NO_EXIST_PROP;
		}

#define GET_MONSTER_ATTR_ARR(ATTR) \
		xmlConf.ResetMainPos(); \
		if(xmlConf.FindElem(#ATTR)) \
		{ \
			string cat = DELETE_TOKEN(xmlConf.GetData()); \
			vector<string> vec; \
			String::Split(cat.c_str(), ',', vec); \
			uint32_t vecSize = vec.size(); \
			mic.ATTR.reserve(128); \
			for(uint32_t i = 0; i < vecSize; ++i) \
			{ \
				mic.ATTR.push_back(CTrans::STOI(vec[i])); \
			} \
		}

		GET_MONSTER_ATTR_ARR(hp)
		GET_MONSTER_ATTR_ARR(ha)
		GET_MONSTER_ATTR_ARR(hd)
		GET_MONSTER_ATTR_ARR(ip)
		GET_MONSTER_ATTR_ARR(bp)
		GET_MONSTER_ATTR_ARR(bv)
		GET_MONSTER_ATTR_ARR(rp)

		xmlConf.OutOfElem();
	}
	return true;
}
bool MonsterConfig::initJson(const string & path){
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret){
		return false;
	}
	Json::Reader reader;
	Json::Value content;
	if (!reader.parse(buffer, content)){
		return false;
	}
	Json::Value &mosters = content["mosters"]["moster"];
	if (mosters.isNull() || !mosters.isArray()){
		return false;
	}
	for (size_t i=0; i<mosters.size(); ++i){
		Json::Value &item = mosters[i];
		string idStr;
		if (!Json::GetString(item, "id", idStr)){
			continue;
		}
		string typeStr;
		if (!Json::GetString(item, "type", typeStr)){
			typeStr.clear();
		}
		string profStr;
		if (!Json::GetString(item, "prof", profStr)){
			profStr.clear();
		}
		uint32_t id = CTrans::STOI(idStr);
		uint32_t type = CTrans::STOI(typeStr);
		uint32_t prof = CTrans::STOI(profStr);
		MonsterItemConfig& mic = m_mapItemConfig[id];
		mic.id = id;
		mic.type = type;
		mic.prof = prof;
		string spStr;
		if (Json::GetString(item, "sp", spStr)){
			mic.sp = CTrans::STOI(spStr.substr(1, spStr.length() - 2));
		}
		string rangeStr;
		if (Json::GetString(item, "range", rangeStr)){
			mic.range = CTrans::STOI(rangeStr.substr(1, rangeStr.length() - 2));
		}
		string hurtrateStr;
		if (Json::GetString(item, "hurtrate", hurtrateStr)){
			hurtrateStr = hurtrateStr.substr(1, hurtrateStr.length()-2);
			vector<string> vec;
			String::Split(hurtrateStr, ',', vec);
			uint32_t vecSize = vec.size();
			mic.hurtBuildingRatio = (vecSize == 4) ? CTrans::STOI(vec[0]) : RET_NO_EXIST_PROP;
			mic.hurtAirRatio = (vecSize == 4) ? CTrans::STOI(vec[1]) : RET_NO_EXIST_PROP;
			mic.hurtArmyRatio = (vecSize == 4) ? CTrans::STOI(vec[2]) : RET_NO_EXIST_PROP;
			mic.hurtNavyRatio = (vecSize == 4) ? CTrans::STOI(vec[3]) : RET_NO_EXIST_PROP;
		}

		parseArr(item, "hp", mic.hp);
		parseArr(item, "hd", mic.hd);
		parseArr(item, "ip", mic.ip);
		parseArr(item, "bp", mic.bp);
		parseArr(item, "bv", mic.bv);
		parseArr(item, "rp", mic.rp);
	}
	return true;
}
MonsterItemConfig* MonsterConfig::getItemConfig(uint32_t id)
{
	map<uint32_t,MonsterItemConfig>::iterator iter = m_mapItemConfig.find(id);
	return (iter != m_mapItemConfig.end()) ? &iter->second : NULL;
}
bool MonsterConfig::getMonsterConfig(uint32_t id, uint32_t level, PropertySets& props)
{
	MonsterItemConfig* mic = getItemConfig(id);
	if(mic == NULL)
	{
		error_log("mic is NULL id=%u", id);
		return false;
	}
	props[AP_PROF].pui = getProf(mic);
	props[AP_SP].pui = getSp(mic);
	props[AP_RANGE].pui = getRange(mic);
	props[AP_MAX_HP].pui = getHp(mic, level);
	props[AP_HA].pui = getHa(mic, level);
	props[AP_HD].pui = getHd(mic, level);
	props[AP_IP].pui = getIp(mic, level);
	props[AP_BP].pui = getBp(mic, level);
	props[AP_BV].pui = getBv(mic, level);
	props[AP_RP].pui = getRp(mic, level);

	return true;
}
uint32_t MonsterConfig::getSp(MonsterItemConfig* mic)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}
	return mic->sp;
}
uint32_t MonsterConfig::getRange(MonsterItemConfig* mic)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}
	return mic->range;
}
uint32_t MonsterConfig::getProf(MonsterItemConfig* mic)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}
	return mic->prof;
}
uint32_t MonsterConfig::getHp(MonsterItemConfig* mic, uint32_t level)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}

	vector<uint32_t>& hp = mic->hp;
	if(level > hp.size() || level == 0)
	{
		error_log("level out of limit size=%u level=%u", hp.size(), level);
		return 0;
	}
	return hp[level - 1];
}
uint32_t MonsterConfig::getHa(MonsterItemConfig* mic, uint32_t level)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}

	vector<uint32_t>& ha = mic->ha;
	if(level > ha.size() || level == 0)
	{
		error_log("level out of limit size=%u level=%u", ha.size(), level);
		return 0;
	}
	return ha[level - 1];
}
uint32_t MonsterConfig::getHd(MonsterItemConfig* mic, uint32_t level)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}

	vector<uint32_t>& hd = mic->hd;
	if(level > hd.size() || level == 0)
	{
		error_log("level out of limit size=%u level=%u", hd.size(), level);
		return 0;
	}
	return hd[level - 1];
}
uint32_t MonsterConfig::getIp(MonsterItemConfig* mic, uint32_t level)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}

	vector<uint32_t>& ip = mic->ip;
	if(level > ip.size() || level == 0)
	{
		error_log("level out of limit size=%u level=%u", ip.size(), level);
		return 0;
	}
	return ip[level - 1];
}
uint32_t MonsterConfig::getBp(MonsterItemConfig* mic, uint32_t level)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}

	vector<uint32_t>& bp = mic->bp;
	if(level > bp.size() || level == 0)
	{
		error_log("level out of limit size=%u level=%u", bp.size(), level);
		return 0;
	}
	return bp[level - 1];
}
uint32_t MonsterConfig::getBv(MonsterItemConfig* mic, uint32_t level)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}

	vector<uint32_t>& bv = mic->bv;
	if(level > bv.size() || level == 0)
	{
		error_log("level out of limit size=%u level=%u", bv.size(), level);
		return 0;
	}
	return bv[level - 1];
}
uint32_t MonsterConfig::getRp(MonsterItemConfig* mic, uint32_t level)
{
	if(mic == NULL)
	{
		error_log("mic is NULL");
		return 0;
	}

	vector<uint32_t>& rp = mic->rp;
	if(level > rp.size() || level == 0)
	{
		error_log("level out of limit size=%u level=%u", rp.size(), level);
		return 0;
	}
	return rp[level - 1];
}
bool MonsterConfig::parseArr(const Json::Value &item, const string &key, vector<uint32_t> &arr){
	string str;
	if (!Json::GetString(item, key.c_str(), str)){
		return false;
	}
	if (str.empty()) {
		return false;
	}
	str = str.substr(1, str.length()-2);
	vector<string> vec;
	String::Split(str, ',', vec);
	uint32_t vecSize = vec.size();
	arr.reserve(128);
	for(uint32_t i = 0; i < vecSize; ++i)
	{
		arr.push_back(CTrans::STOI(vec[i]));
	}
	return true;
}
