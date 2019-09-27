/*
 * EquipmentConfig.h
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#ifndef EQUIPMENTCONFIG_H_
#define EQUIPMENTCONFIG_H_

#include "Kernel.h"
#include "CommData.h"
#include "Award.h"
#include "CommonConfig.h"

struct EquipConfigItem {
	uint32_t id;
	uint32_t power;
	uint16_t type;
	uint16_t color;
	uint16_t gem_type;
	uint16_t lv;

	EquipConfigItem(): id(0), power(0), type(0), color(0), gem_type(0), lv(0) {
	}
};

class EquipmentConfig {
public:
	~EquipmentConfig();
	static EquipmentConfig* getInstance() {
		static EquipmentConfig _ins;
		return &_ins;
	}
	bool init(const string &path);
	const EquipConfigItem* getItemConfig(uint32_t type);
	uint32_t getLevel(uint32_t type);
	uint32_t getGemId(uint16_t gem_type, uint16_t lv);
protected:
	EquipmentConfig();
private:
	template<typename T>
	inline bool getJsonValue(const Json::Value &v, T &d);
private:
	map<uint32_t, EquipConfigItem> m_data;
	map<uint16_t, set<uint32_t> > m_gem;
};
#endif /* EQUIPMENTCONFIG_H_ */
