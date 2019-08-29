/*
 * Building.h
 *
 *  Created on: 2015-8-26
 *      Author: Administrator
 */

#ifndef BUILDING_H_
#define BUILDING_H_

#include "Kernel.h"
#include "MapObject.h"
#include "DataBuilding.h"
#include "ProtocolInc.h"

#define TOWN_HALL_MAX_RES 1000
#define STORAGE_MAX_RES 198000

struct BuildingPos {
	uint32_t ud;
	int x;
	int y;
};
struct BuildingLayout {
	uint32_t id;
	uint32_t valid; //0:无效，1:有效
	string name;
	map<uint32_t, BuildingPos> pos;
};
class PropertyManager;
class Building: public MapObject {
public:
	Building();
	virtual ~Building();
public:
	virtual bool setData(const string & jsonData);
	virtual bool setData(const Json::Value & data);
	virtual bool saveData(bool isNew = false);
	virtual bool initHp();
	virtual bool initProduceTime();
	virtual bool onComplelete(uint32_t type);
	virtual bool isBase() {
		return getType() == BUILDING_ID_BASE;
	}
	virtual bool isDefense();
	virtual bool needProduce();
	virtual bool needRecove();
	virtual bool initCapacity(uint32_t ubTimeShift);
	virtual uint32_t getRecoveInter();
	virtual double getRecoveValue();
	virtual uint32_t getProduceInter();
	virtual double getProduceValue();
	virtual bool onMapObjectHurt(MapObject *pAttacker, uint32_t hurt);

	uint32_t getRecoveTime();
	bool getCenterPoint(int& cx, int& cy);
	bool sendPropChange();
	bool onRecove();
	bool needTimer();
	virtual bool isActive();
	virtual bool onProduce();
	virtual void setActive(bool flag) {
		m_isActive = flag;
	}
	static bool saveDataGeneral(uint32_t uid, PropertySets& m_data, bool isNew = false);
	static bool addOrSetBuilding(uint32_t uid, Json::Value& value, bool isNew = false);
	static bool delBuilding(uint32_t uid, uint32_t ud);
	void setPropertyManager(PropertyManager* pm) {
		m_pm = pm;
	}
	static uint32_t getResRateByLevel(uint32_t aLv, uint32_t bLv);
	virtual bool encode(IBuffer* buff);
	uint32_t getProduce();
	void setProduce(uint32_t res);
	bool addCapacity(uint32_t res);
public:
	virtual void doAi();
public:
	virtual void propsCalc();
	virtual void calcSpecialProps(PropertySets& props) {
	}
	virtual void getRateProps(PropertySets& props);
	virtual void getAddProps(PropertySets& props);
	virtual void resetTarget() {
		m_target.reset();
	}
	uint32_t getAvailableResource() {
		return m_available_resource;
	}
	float getProduceRatio() {
		return m_produceRatio;
	}
	void setAvailableResource(uint32_t resource) {
		m_available_resource = resource;
	}
	virtual void calcCombat();
	void setProduceRatio(float produceRatio) {
		m_produceRatio = produceRatio;
	}
	static Building* newBuildingByType(uint32_t type);
protected:
	bool m_isActive;
	uint32_t m_available_resource;
	TargetInfo m_target;
	PropertyManager * m_pm;
	float m_produceRatio;
};

#endif /* BUILDING_H_ */
