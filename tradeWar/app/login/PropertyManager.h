/*
 * 负责各种属性的运算
 *
 *  Created on: 2015-9-15
 *      Author: Administrator
 */

#ifndef PROPERTYMANAGER_H_
#define PROPERTYMANAGER_H_

#include "Kernel.h"
#include "CommData.h"
#include "SkillManager.h"
#include "IManager.h"
#define PROPERTY_COMPOSITE(src,dest) \
	for(PropertySets::iterator it = src.begin(); it != src.end(); ++it){\
		int type = PropertyConfig::getDataType(it->first);\
		switch(type)\
		{\
		case DT_INT:\
			 dest[it->first].pi = it->second.pi;\
			 break;\
		case DT_FLOAT:\
			 dest[it->first].pf = it->second.pf;\
			 break;\
		case DT_UNSIGNED_INT:\
			 dest[it->first].pui = it->second.pui;\
			 break;\
		}\
	}

class EquipmentManager;
class BuildingManager;
class PropertyManager: public IManager
{
public:
	PropertyManager();
	~PropertyManager();
public:
	virtual bool doPacket(CNetPacket * packet)
	{
		return true;
	}
public:
	bool calcHeroOriProps(uint32_t buStar, const PropertySets& buProp, PropertySets& baseProp);
	bool calcHeroProps(uint32_t id, uint32_t level, uint32_t ud, uint32_t star, PropertySets& props);
	bool calcBuildingProps(uint32_t id, uint32_t level, uint32_t ud, uint32_t strong, PropertySets& props);
	bool calcSoldierProps(uint32_t id, uint32_t level, uint32_t strong, PropertySets& props);
	void setEm(EquipmentManager* em)
	{
		m_em = em;
	}
	void setBm(BuildingManager* bm)
	{
		m_bm = bm;
	}
	void setSkillManager(CSkillManager* pSm)
	{
		m_skillManager = pSm;
	}
	void setAllianceTechPropsAdd(map<uint32_t, PropertySets>& props)
	{
		m_allianceTechPropsAdd = props;
	}
	uint32_t getSkillCombat(uint16_t ud)
	{
		return m_skillManager->getCombat(ud);
	}
private:
	bool isValidAttr(uint32_t attr)
	{
		return attr < AP_MAX;
	}
	bool getHeroAddProps(uint32_t hud, byte prof, uint32_t rideId, PropertySets& props);
	bool getHeroRateProps(uint32_t heroId, uint32_t hud, byte prof, PropertySets& props);
	bool getBuildingAddProps(uint32_t bud, PropertySets& props);
	bool getBuildingRateProps(uint32_t bud, PropertySets& props);
private:
	EquipmentManager* m_em;
	BuildingManager* m_bm;
	map<uint32_t, PropertySets> m_allianceTechPropsAdd;	//联盟科技属性加成
	CSkillManager *m_skillManager;
};

#endif /* PROPERTYMANAGER_H_ */
