/*
 * HeroConfig.cpp
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */
#include "HeroConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"

HeroConfig::HeroConfig()
{
}

HeroConfig::~HeroConfig()
{
}

bool HeroConfig::init()
{
	if (!initItem(Config::GetValue(CONFIG_HERO_COMMON)))
	{
		return false;
	}
	if (!initBorn(Config::GetValue(CONFIG_HERO_BORN)))
	{
		return false;
	}
	return true;
}

bool HeroConfig::initItem(const string & path)
{
	ConfigJson fileParser(path);
	if (!fileParser.Init())
	{
		return false;
	}
	const Json::Value *hero = fileParser.getMember("heroes.hero");
	if (hero == NULL || !hero->isArray())
	{
		error_log("hero error");
		return false;
	}
	for (size_t i = 0; i < hero->size(); ++i)
	{
		const Json::Value &item = hero->get(i, Json::nullValue);
		string idStr;
		if (!Json::GetString(item, "id", idStr) || idStr.empty())
		{
			error_log("id error");
			return false;
		}
		uint32_t id = CTrans::STOI(idStr.substr(1, idStr.length() - 1));
		HeroItemConfig& hic = m_mapItemConfig[id];
		if (!Json::GetUInt(item, "rp", hic.rp))
		{
			hic.rp = 0;
		}
		if (!Json::GetUInt(item, "sp", hic.sp))
		{
			hic.sp = 0;
		}
		if (!Json::GetUInt(item, "range", hic.range))
		{
			hic.range = 0;
		}
		if (!Json::GetUInt(item, "lockEq", hic.lockEq))
		{
			hic.lockEq = 0;
		}
		if (!Json::GetUInt(item, "lockEqNum", hic.lockEqNum))
		{
			hic.lockEqNum = 0;
		}
		if (!Json::GetUInt(item, "bornEquip", hic.bornEquipId))
		{
			hic.bornEquipId = 0;
		}
		if (!Json::GetUInt(item, "bornSkill", hic.bornSkillId))
		{
			hic.bornSkillId = 0;
		}
		parseArray(item["hp"], hic.hp);
		parseArray(item["ha"], hic.ha);
		parseArray(item["hd"], hic.hd);
		parseArray(item["tili"], hic.tl);
		parseArray(item["lvCost"], hic.lvCost);
		parseArray(item["starEqNum"], hic.starEqNum);
		parseArray(item["starHa"], hic.starha);
		parseArray(item["starHd"], hic.starhd);
		parseArray(item["starHp"], hic.starhp);
		parseArray(item["starTili"], hic.startl);
		parseArray(item["bornSkillLock"], hic.bornSkillLock);

		parseBorn(item["born"], hic.born);
	}
	return true;
}

bool HeroConfig::initBorn(const string & path)
{
	ConfigJson fileParser(path);
	if (!fileParser.Init())
	{
		return false;
	}
	const Json::Value *skill = fileParser.getMember("skill");
	if (skill == NULL || !skill->isArray())
	{
		error_log("skill error");
		return false;
	}
	for (size_t i = 0; i < skill->size(); ++i)
	{
		const Json::Value &item = skill->get(i, Json::nullValue);
		if (item.isNull() || !item.isObject())
		{
			continue;
		}
		HeroBornSkill s;
		Json::GetUInt(item, "id", s.id);
		parseArray(item["skills"], s.skills);
		m_mapBornSkill.push_back(s);
	}
	const Json::Value *equip = fileParser.getMember("equip");
	if (equip == NULL || !equip->isArray())
	{
		error_log("equip error");
		return false;
	}
	for (size_t i = 0; i < equip->size(); ++i)
	{
		const Json::Value &item = equip->get(i, Json::nullValue);
		if (item.isNull() || !item.isObject())
		{
			continue;
		}
		HeroBornEquipment e;
		e.id = item.get("id", 0).asUInt();
		parseArray(item["equips"], e.equips);
		m_mapBornEquipment.push_back(e);
	}
	return true;
}

bool HeroConfig::getProps(uint32_t id, uint32_t lv, PropertySets & props)
{
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return false;
	}
	lv = lv > 0 ? lv - 1 : lv;
	vector<uint32_t> &hp = itr->second.hp;
	props[AP_MAX_HP].pui = hp.size() > lv ? hp[lv] : (hp.empty() ? 0 : hp[hp.size() - 1]);
	vector<uint32_t> &ha = itr->second.ha;
	props[AP_HA].pui = ha.size() > lv ? ha[lv] : (ha.empty() ? 0 : ha[ha.size() - 1]);
	vector<uint32_t> &hd = itr->second.hd;
	props[AP_HD].pui = hd.size() > lv ? hd[lv] : (hd.empty() ? 0 : hd[hd.size() - 1]);
	vector<uint32_t> &tl = itr->second.tl;
	props[AP_MAX_ENERGY].pui = tl.size() > lv ? tl[lv] : (tl.empty() ? 0 : tl[tl.size() - 1]);
	props[AP_RP].pui = itr->second.rp;
	props[AP_SP].pui = itr->second.sp;
	props[AP_RANGE].pui = itr->second.range;
	return true;
}

bool HeroConfig::getStarProps(uint32_t id, uint32_t lv, PropertySets & props)
{
	if (lv == 0)
	{
		return false;
	}
	--lv;
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return false;
	}
	vector<uint32_t> &hp = itr->second.starhp;
	props[AP_MAX_HP].pui = hp.size() > lv ? hp[lv] : (hp.empty() ? 0 : hp[hp.size() - 1]);
	vector<uint32_t> &ha = itr->second.starha;
	props[AP_HA].pui = ha.size() > lv ? ha[lv] : (ha.empty() ? 0 : ha[ha.size() - 1]);
	vector<uint32_t> &hd = itr->second.starhd;
	props[AP_HD].pui = hd.size() > lv ? hd[lv] : (hd.empty() ? 0 : hd[hd.size() - 1]);
	vector<uint32_t> &tl = itr->second.startl;
	props[AP_MAX_ENERGY].pui = tl.size() > lv ? tl[lv] : (tl.empty() ? 0 : tl[tl.size() - 1]);
	props[AP_RP].pui = itr->second.rp;
	props[AP_SP].pui = itr->second.sp;
	props[AP_RANGE].pui = itr->second.range;
	return true;

}

uint32_t HeroConfig::getEnergy(uint32_t id, uint32_t lv)
{
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return 0;
	}
	lv = lv > 0 ? lv - 1 : lv;
	HeroItemConfig & item = itr->second;
	return item.tl.size() > lv ? item.tl[lv] : 0;
}

const HeroBornSkill* HeroConfig::getBorn(uint32_t id)
{
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return NULL;
	}
	return &(itr->second.born);
}

uint32_t HeroConfig::getLvCost(uint32_t id, uint32_t lv)
{
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return -1;
	}
	HeroItemConfig &hic = itr->second;
	if (hic.lvCost.size() <= lv)
	{
		return -1;
	}
	return hic.lvCost[lv];
}

bool HeroConfig::getUnLockEquip(uint32_t id, uint32_t &eqid, uint32_t &eqcnt)
{
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return false;
	}
	eqid = itr->second.lockEq;
	eqcnt = itr->second.lockEqNum;
	return true;
}

bool HeroConfig::getStartEquip(uint32_t id, uint32_t lv, uint32_t &eqid, uint32_t &eqcnt)
{
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return false;
	}
	const HeroItemConfig& hic = itr->second;
	if (hic.starEqNum.size() <= lv)
	{
		return false;
	}
	eqid = hic.lockEq;
	eqcnt = hic.starEqNum[lv];
	return true;
}

const vector<uint32_t>* HeroConfig::getHeroBornEquip(uint32_t id) const
{
	for (size_t i = 0; i < m_mapBornEquipment.size(); ++i)
	{
		if (id == m_mapBornEquipment[i].id)
		{
			return &(m_mapBornEquipment[i].equips);
		}
	}
	return NULL;
}

bool HeroConfig::getHeroBornSkill(uint32_t id, uint32_t star, vector<uint32_t> &skillId)
{
	map<uint32_t, HeroItemConfig>::iterator itr = m_mapItemConfig.find(id);
	if (itr == m_mapItemConfig.end())
	{
		return false;
	}
	const HeroItemConfig &item = itr->second;
	vector<uint32_t>::const_iterator it = item.bornSkillLock.begin();
	unsigned index = 0;
	for (; it != item.bornSkillLock.end(); ++it)
	{
		if (star >= *it)
		{
			++index;
		}
	}

	const vector<uint32_t> *bskill = NULL;
	for (size_t i = 0; i < m_mapBornSkill.size(); ++i)
	{
		if (item.bornSkillId == m_mapBornSkill[i].id)
		{
			bskill = &(m_mapBornSkill[i].skills);
			break;
		}
	}
	if (bskill == NULL)
	{
		return false;
	}
	for (it = bskill->begin(); it != bskill->end() && skillId.size() <= index; ++it)
	{
		skillId.push_back(*it);
	}
	return true;
}

uint32_t HeroConfig::getHeroBornEquipId(uint32_t id) const
{
	map<uint32_t, HeroItemConfig>::const_iterator itr = m_mapItemConfig.find(id);
	return itr == m_mapItemConfig.end() ? 0 : itr->second.bornEquipId;
}

uint32_t HeroConfig::getHeroBornSkillId(uint32_t id) const
{
	map<uint32_t, HeroItemConfig>::const_iterator itr = m_mapItemConfig.find(id);
	return itr == m_mapItemConfig.end() ? 0 : itr->second.bornSkillId;
}

bool HeroConfig::parseBorn(const Json::Value & value, HeroBornSkill &born)
{
	if (value.isNull() || !value.isObject())
	{
		return false;
	}
	Json::GetUInt(value, "id", born.id);
	parseArray(value["bornLock"], born.lock);
	return true;
}

