/*
 * Hero.h
 *
 *  Created on: 2015-8-26
 *      Author: Administrator
 */

#ifndef HERO_H_
#define HERO_H_

#include "Kernel.h"
#include "MapObject.h"
#include "PropertyManager.h"
#include "ProtocolInc.h"

struct PathRlt;
class Hero: public MapObject
{
public:
	Hero();
	~Hero();
public:
	bool initFromMonster();
	bool isValidFighter()
	{
		return isChief() || isStation() || isFighter();
	}
	//是否是主将
	inline bool isChief()
	{
		return m_data[AP_STATUS].pui == 1;
	}
	//是否为驻将
	inline bool isStation()
	{
		return m_data[AP_HERO_BUNKER].pui > 0;
	}
	//是否设置为出战
	inline bool isFighter()
	{
		return m_data[AP_STATE].pui > 0;
	}
	inline void setChief()
	{
		m_data[AP_STATUS].pui = 1;
	}
	inline void unsetChief()
	{
		m_data[AP_STATUS].pui = 0;
	}
	inline uint32_t getRideStar()
	{
		return m_data[AP_RIDE_STAR].pui;
	}
	inline uint32_t getRideLevel()
	{
		return m_data[AP_RIDE_LEVEL].pui;
	}
	inline uint32_t getProf()
	{
		return m_data[AP_PROF].pui;
	}
	inline uint32_t getExp()
	{
		return m_data[AP_EXP].pui;
	}
	inline uint32_t getStateSlotId()
	{
		return m_data[AP_STATE].pui;
	}
	inline void setExp(uint32_t exp)
	{
		m_data[AP_EXP].pui = exp;
	}
	bool upExp(uint32_t exp, const string& code);
	inline uint32_t getTrainExp()
	{
		return m_data[AP_TRAIN_GAIN_EXP].pui;
	}
	inline void setTrainExp(uint32_t tgExp)
	{
		m_data[AP_TRAIN_GAIN_EXP].pui = tgExp;
	}
	inline void setFighter(uint32_t slotId)
	{
		m_data[AP_STATE].pui = slotId;
	}
	virtual bool encode(IBuffer* buffer);
	virtual bool saveData(bool isNew = false);
	virtual bool delData();
	virtual bool setData(const string& jsonData);
	virtual bool calcProps();
	virtual bool initProps();
	virtual bool onComplelete(uint32_t type);
	virtual bool onDie();
	static bool saveDataGeneral(uint32_t uid, PropertySets& m_data, bool isNew = false);
	static bool addOrSetHero(uint32_t uid, Json::Value& value, bool isNew);
	uint32_t getRecoveInter(uint32_t level, uint32_t clevel);
	float getRecoveValue();
	void setPropertyManager(PropertyManager* pm)
	{
		m_pm = pm;
	}
	void setCaptiveUid(uint32_t uid)
	{
		m_captiveUid = uid;
	}
	void calcCombat();
	void setOldHp(uint32_t hp)
	{
		m_oldHp = hp;
	}
	uint32_t getOldHp() const
	{
		return m_oldHp;
	}
	uint32_t getCaptiveUid() const
	{
		return m_captiveUid;
	}
	bool onRecoveEnergy();
	bool onRecove();
	bool needRecove();
	bool needTimer();
	bool resetCu();
	bool initActionTime();
	bool sendPropChange();
	uint32_t getPlayerBuildingLevel(uint32_t type);
	uint32_t getPlayerLevel();
	uint32_t getAddPoint();
	bool getTargetPoint(const Point & srcPoint, int & dx, int & dy);
	bool onTrainOver();
	bool onLevelUp();
	bool onPropChangeByPoint(uint32_t point, PropertySets& props);
	void setGuardRange(uint32_t range)
	{
		m_guard_range = range;
	}
	uint32_t getGuardRange() const
	{
		return m_guard_range;
	}
	bool isReturn() const
	{
		return m_isReturn;
	}
	void setReturn(bool flag)
	{
		m_isReturn = flag;
	}
	bool isBuddy()
	{
		return m_data[AP_BUDDY_POS].pi > 0;
	}
	void setBuddy(byte pos)
	{
		m_data[AP_BUDDY_POS].pi = pos;
	}
	uint32_t getBuddy()
	{
		return m_data[AP_BUDDY_POS].pi;
	}
	void resetEnergyTs();
	void costEnergy(uint32_t cost);
private:
	bool m_isReturn;
	uint32_t m_guard_range;
	PropertyManager* m_pm;
	uint32_t m_oldHp;		// 有些关卡战斗结束需要回复原血量
	uint32_t m_captiveUid;	// 俘虏
};

#endif /* HERO_H_ */
