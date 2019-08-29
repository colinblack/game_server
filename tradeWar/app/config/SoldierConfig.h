/*
 * SoldierConfig.h
 *
 *  Created on: 2016-4-14
 *      Author: Administrator
 */

#ifndef SOLDIER_CONFIG_H_
#define SOLDIER_CONFIG_H_

#include "Kernel.h"
#include "CommData.h"

struct SoldierItemConfig {
	uint32_t id;
	uint32_t type;				// 表示侠盗和护卫等
	uint32_t lockLevel;			// 解锁等级
	byte q;						// 品质
	byte space2;            	// 占格子数
	vector<uint32_t> repair_time;
	vector<uint32_t> research;
};

class SoldierConfig {
public:
	~SoldierConfig();
	static SoldierConfig* getInstance() {
		static SoldierConfig hc;
		return &hc;
	}
	bool init(const string& path);
	const SoldierItemConfig* getItemConfig(uint32_t id);
	bool getSoldierConfig(uint32_t id, uint32_t level, PropertySets& props);
	bool getSoldierUpgradeCost(uint32_t id, uint32_t level, ResourceCost& cost);
	bool getSoldierOriType(uint32_t id, uint32_t& oriType);
	bool isExist(uint32_t id);
	uint32_t GetSoldierRepairTime(uint32_t type, uint32_t level);
	uint32_t getLevelPower(byte color, uint32_t lv);
	bool getArrValue(const vector<uint32_t>& arr, uint32_t idx, uint32_t& value);
protected:
	SoldierConfig();

private:
	map<uint32_t, SoldierItemConfig> m_mapItemConfig;
	map<byte, vector<uint32_t> > m_levelPower;
};

#endif /* SOLDIER_CONFIG_H_ */
