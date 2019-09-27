/*
 * StrongConfig.h
 *
 *  Created on: 2018年9月18日
 *      Author: Administrator
 */

#ifndef STRONG_CONFIG_H_
#define STRONG_CONFIG_H_

#include "Kernel.h"
struct StrongItem {
	uint32_t id;
	vector<uint32_t> cost;
	vector<uint32_t> reward;

	StrongItem():id(0) {
	}
};

struct StrongPower {
	byte color;
	vector<uint32_t> power;
	StrongPower() {
		color = 0;
	}
};

class StrongConfig {
	SINGLETON_CLASS(StrongConfig);
	bool init(const string &path);
	uint32_t getSoldierCost(uint32_t id, uint32_t lv);
	uint32_t getSoldierReward(uint32_t id, uint32_t lv);
	uint32_t getTower(uint32_t id, uint32_t lv);
	uint32_t getTowerLevelLimit(uint32_t lv);
	uint32_t getStrongPower(uint32_t color, uint32_t f, uint32_t t);
private:
	map<uint32_t, StrongItem> m_soldier;
	map<uint32_t, StrongItem> m_tower;
	vector<uint32_t> m_tower_level_limit;
	vector<StrongPower> m_strong_power;
};

#endif /* STRONG_CONFIG_H_ */
