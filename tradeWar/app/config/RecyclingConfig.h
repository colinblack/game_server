/*
 * RecyclingConfig.h
 *
 *  Created on: 2018年11月28日
 *      Author: Administrator
 */

#ifndef RECYCLING_CONFIG_H_
#define RECYCLING_CONFIG_H_

#include "Kernel.h"

struct RecyclingItem {
	byte lv;
	uint16_t cost;
	uint16_t count;
	uint32_t res;
	vector<uint16_t> skill;

	RecyclingItem() {
		lv = 0;
		cost = 0;
		count = 0;
		res = 0;
	}
};

class RecyclingConfig {
SINGLETON_CLASS(RecyclingConfig);
	bool init(const string &path);
	const RecyclingItem* getItem(uint32_t lv) const;
	uint32_t getR1(uint32_t res);
private:
	map<byte, RecyclingItem> m_data;
};

#endif /* RECYCLING_CONFIG_H_ */
