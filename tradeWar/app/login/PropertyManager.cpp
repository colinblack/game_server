/*
 * PropertyManager.cpp
 *
 *  Created on: 2015-9-15
 *      Author: Administrator
 */

#include "PropertyManager.h"
#include "HeroConfig.h"
#include "BuildingConfig.h"
#include "EquipmentManager.h"
#include "SoldierConfig.h"
#include "SkillManager.h"
#include "Player.h"

PropertyManager::PropertyManager() :
		m_em(NULL), m_bm(NULL), m_skillManager(NULL)
{
}
PropertyManager::~PropertyManager()
{
}
// 计算英雄原始属性
bool PropertyManager::calcHeroOriProps(uint32_t buStar, const PropertySets& buProp, PropertySets& baseProp)
{
	PropertySets::const_iterator iter = buProp.begin();
	for (; iter != buProp.end(); ++iter)
	{
		int buIdx = iter->first;
		uint32_t buValue = iter->second.pui;
		PropertySets::iterator bIter = baseProp.find(buIdx);
		if (bIter == baseProp.end())
		{
			baseProp[buIdx].pui = 0;
		}
		switch (buIdx)
		{
		case AP_MAX_HP:
			baseProp[buIdx].pui += buValue + (0.06 * buValue + 80) * buStar;
			break;
		case AP_HD:
			baseProp[buIdx].pui += buValue + (0.06 * buValue + 10) * buStar;
			break;
		case AP_HA:
			baseProp[buIdx].pui += buValue + (0.06 * buValue + 8) * buStar;
			break;
		case AP_HR:
		case AP_EBP:
			baseProp[buIdx].pui += buValue + (0.06 * buValue + 2) * buStar;
			break;
		case AP_RP:
		case AP_SP:
		case AP_RANGE:
			baseProp[buIdx].pui += buValue;
			break;
		}
	}
	return true;
}

bool PropertyManager::calcHeroProps(uint32_t id, uint32_t level, uint32_t ud, uint32_t star, PropertySets& props)
{
	HeroConfig::getInstance()->getProps(id, level, props);

	//升星属性加成
	PropertySets starProps;
	HeroConfig::getInstance()->getStarProps(id, star, starProps);
	PropertyConfig::accumulateProps(starProps, props);

	//装备属性加成
	PropertySets addProps;
	getHeroAddProps(ud, props[AP_PROF].pui, 0, addProps);
	PropertyConfig::accumulateProps(addProps, props);

	return true;
}
bool PropertyManager::getHeroAddProps(uint32_t hud, byte prof, uint32_t rideId, PropertySets& props)
{
	return true;
}
bool PropertyManager::getHeroRateProps(uint32_t heroId, uint32_t hud, byte prof, PropertySets& props)
{
	return true;
}
bool PropertyManager::calcBuildingProps(uint32_t id, uint32_t level, uint32_t ud, uint32_t strong, PropertySets& props)
{
	PropertySets baseProps;
	BuildingConfig::getInstance()->getBaseProp(id, level, baseProps);
	PropertyConfig::accumulateProps(baseProps, props);
	return true;
}
bool PropertyManager::calcSoldierProps(uint32_t id, uint32_t level, uint32_t strong, PropertySets& props)
{
	if (!SoldierConfig::getInstance()->getSoldierConfig(id, level, props))
	{
		error_log("getSoldierConfig fail id=%u level=%u", id, level);
		return false;
	}
	return true;
}
bool PropertyManager::getBuildingAddProps(uint32_t bud, PropertySets& props)
{
	return true;
}
bool PropertyManager::getBuildingRateProps(uint32_t bud, PropertySets& props)
{
	return true;
}

