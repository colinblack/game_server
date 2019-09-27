/*
 * HeroConfig.h
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#ifndef HEROCONFIG_H_
#define HEROCONFIG_H_

#include "Kernel.h"
#include "CommData.h"

struct HeroBornSkill
{
	uint32_t id;
	vector<uint32_t> lock;
	vector<uint32_t> skills;
	HeroBornSkill(): id(0)
	{
		lock.clear();
		skills.clear();
	}
};

struct HeroBornEquipment
{
	byte id;
	vector<uint32_t> equips;
};

struct HeroItemConfig
{
	uint32_t id;
	uint32_t rp;
	uint32_t sp;
	uint32_t range;
	uint32_t lockEq;
	uint32_t lockEqNum;
	uint32_t bornSkillId;
	uint32_t bornEquipId;
	HeroBornSkill born;
	vector<uint32_t> hp;
	vector<uint32_t> ha;
	vector<uint32_t> hd;
	vector<uint32_t> tl;
	vector<uint32_t> starhp;
	vector<uint32_t> starha;
	vector<uint32_t> starhd;
	vector<uint32_t> startl;
	vector<uint32_t> lvCost;
	vector<uint32_t> starEqNum;
	vector<uint32_t> bornSkillLock;

	HeroItemConfig(): id(0), rp(0), sp(0), range(0), lockEq(0), lockEqNum(0), bornSkillId(0), bornEquipId(0)
	{
		hp.clear();
		ha.clear();
		hd.clear();
		starhp.clear();
		starha.clear();
		starhd.clear();
		tl.clear();
		lvCost.clear();
		starEqNum.clear();
		bornSkillLock.clear();
	}
};

class HeroConfig
{
private:
	HeroConfig();
public:
	~HeroConfig();
	static HeroConfig* getInstance()
	{
		static HeroConfig hc;
		return &hc;
	}
	bool init();
	bool initItem(const string & path);
	bool initBorn(const string & path);

	bool getProps(uint32_t id, uint32_t lv, PropertySets & props);
	bool getStarProps(uint32_t id, uint32_t lv, PropertySets & props);
	inline bool isExist(uint32_t id) const
	{
		return m_mapItemConfig.find(id) != m_mapItemConfig.end();
	}
	inline const HeroItemConfig* getItemConfig(uint32_t id) const
	{
		map<uint32_t, HeroItemConfig>::const_iterator itr = m_mapItemConfig.find(id);
		return itr != m_mapItemConfig.end() ? &(itr->second) : NULL;
	}
	inline bool isBornSkill(uint32_t id, uint32_t skill) const
	{
		map<uint32_t, HeroItemConfig>::const_iterator itr = m_mapItemConfig.find(id);
		if (itr == m_mapItemConfig.end())
		{
			return false;
		}
		return skill == itr->second.born.id;
	}
	uint32_t getEnergy(uint32_t id, uint32_t lv);
	const HeroBornSkill* getBorn(uint32_t id);
	uint32_t getLvCost(uint32_t id, uint32_t lv);
	bool getUnLockEquip(uint32_t id, uint32_t &eqid, uint32_t &eqcnt);
	bool getStartEquip(uint32_t id, uint32_t lv, uint32_t &eqid, uint32_t &eqcnt);
	const vector<uint32_t>* getHeroBornEquip(uint32_t id) const;
	bool getHeroBornSkill(uint32_t id, uint32_t star, vector<uint32_t> &skillId);
	uint32_t getHeroBornEquipId(uint32_t id) const;
	uint32_t getHeroBornSkillId(uint32_t id) const;
protected:
	bool parseBorn(const Json::Value & value, HeroBornSkill &born);
private:
	map<uint32_t, HeroItemConfig> m_mapItemConfig;
	vector<HeroBornEquipment> m_mapBornEquipment;
	vector<HeroBornSkill> m_mapBornSkill;
};

#endif /* HEROCONFIG_H_ */
