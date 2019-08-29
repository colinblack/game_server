/*
 * BuildingConfig.h
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#ifndef BUILDING_CONFIG_H_
#define BUILDING_CONFIG_H_

#include "Kernel.h"
#include "CommData.h"

enum RELY_BUILDING_TYPE {
	RELY_BUILDING_BUILDING = 1,
	RELY_BUILDING_GATE = 2
};

struct RelyBuilding {
	byte type;		// 依赖类型 1-建筑，2-关卡
	uint32_t id; 	// 依赖建筑id
	uint16_t level;	// 依赖建筑等级

	RelyBuilding() {
		type = 0;
		id = 0;
		level = 0;
	}
};
struct RelyBuildingAll {
	vector<RelyBuilding> data;
};
struct BuildingBuildCost {
	uint32_t r1;
	uint32_t r2;

	BuildingBuildCost() {
		r1 = 0;
		r2 = 0;
	}
};

struct BuildingItemConfig {
	uint32_t id;
	uint32_t group;
	uint32_t type;
	uint32_t color;
	vector<RelyBuildingAll> rely;	// 依赖的建筑
	vector<uint32_t> produce;		// 建筑资源产出
	vector<BuildingBuildCost> cost;	// 建筑等级-资源耗费
	vector<uint32_t> attribute;		// 拥有的格子数

	BuildingItemConfig(){
		id = 0;
		group = 0;
		type = 0;
		color = 0;
	}
};

class BuildingConfig {
public:
	~BuildingConfig();
	static BuildingConfig* getInstance() {
		static BuildingConfig bc;
		return &bc;
	}
	bool init();
	bool getProduce(uint32_t id, uint32_t lv, uint32_t& produce);
	bool getAttribute(uint32_t id, uint32_t lv, uint32_t& attribute);
	bool getFootprint(uint32_t id, uint32_t& dx, uint32_t& dy);
	bool getRelyBuildingGate(uint32_t gateid, map<uint32_t, uint32_t> &ids);
	bool getBaseProp(uint32_t id, uint32_t lv, PropertySets& sPropSets);
	const RelyBuildingAll* getRelyBuilding(uint32_t id, uint32_t lv);
	const BuildingBuildCost* getBuildCost(uint32_t id, uint32_t lv);
	const BuildingItemConfig* getItemConfig(uint32_t id);
	uint32_t getBuildingPower(uint32_t color, uint32_t lv);
protected:
	BuildingConfig();
private:
	bool initBuilding(const string& path);
	bool initBuildingData(const string& path);
	bool setBuildingTypeInt(const string& typeStr, unsigned& type);
	uint32_t getBuildingIdx(uint32_t id, uint32_t level) {
		return (id << 16) | (0x0000FFFF & level);
	}
	void parseProp(const Json::Value &item, const string &key, uint32_t &value);
	uint32_t GetUInt(const Json::Value &value);
private:
	//buildingId-level-props
	map<uint32_t, PropertySets> m_mapBasePropsConfig;
	map<uint32_t, BuildingItemConfig> m_mapItemConfig;
	map<uint32_t, map<uint32_t, uint32_t> > m_gateBuilding;
	map<byte, vector<uint32_t> > m_buildingPower;
};

#endif /* BUILDING_CONFIG_H_ */
