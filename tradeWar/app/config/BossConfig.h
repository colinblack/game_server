/*
 * BossConfig.h
 *
 *  Created on: 2019年2月25日
 *      Author: Administrator
 */

#ifndef BOSS_CONFIG_H_
#define BOSS_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct BossConfigItem {
	byte id;
	uint32_t hp;
	Award reward;

	BossConfigItem() {
		id = 0;
		hp = 0;
	}
};

struct BossConfigShop {
	byte id;
	uint32_t require;
	uint32_t count;
	Award reward;

	BossConfigShop() {
		id = 0;
		require = 0;
		count = 0;
	}
};

struct BossConfigRank {
	uint32_t f;
	uint32_t t;
	Award reward;

	BossConfigRank() {
		f = 0;
		t = 0;
	}
};

class BossConfig {
	SINGLETON_CLASS(BossConfig);
	map<byte, BossConfigItem> m_data;
	map<byte, BossConfigShop> m_shop;
	vector<BossConfigRank> m_rank;
	uint32_t m_rank_size;
public:
	bool init(const string &path);
	const BossConfigItem* getItem(byte id) const;
	const BossConfigShop* getShop(byte id) const;
	const Award* getRank(uint32_t r) const;
	uint32_t getRankSize() const;
	uint32_t getShopSize() const;
};

#endif /* BOSS_CONFIG_H_ */
