/*
 * WorldShopManager.h
 *
 *  Created on: 2018年12月25日
 *      Author: Administrator
 */

#ifndef _WORLD_SHOP_MANAGER_H_
#define _WORLD_SHOP_MANAGER_H_

#include "IManager.h"

#define WORLD_MAX_ATTACK_COUNT 7

class WorldShopManager: public IManager {
public:
	WorldShopManager();
	virtual ~WorldShopManager();
	virtual bool doPacket(CNetPacket *p);
	bool load(uint32_t uid);
	bool save();
	bool reset();
	bool buy(uint32_t id);
	bool getInfo(IBuffer *buff);
	bool useAttackCount();
	bool addAttackCount();
	uint32_t getAttackCount();
private:
	vector<uint16_t> m_data;
	uint32_t m_ts;
	uint32_t m_attack_count;
};

#endif /* _WORLD_SHOP_MANAGER_H_ */
