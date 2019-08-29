/*
 * BossManager.h
 *
 *  Created on: 2019年2月25日
 *      Author: Administrator
 */

#ifndef BOSS_MANAGER_H_
#define BOSS_MANAGER_H_

#include "IManager.h"
#include "DataBoss.h"

class BossManager: public IManager {
public:
	BossManager();
	~BossManager();
	bool doPacket(CNetPacket *p);
	bool load(uint32_t uid);
	bool onLogin();
protected:
	bool save();
	bool push();
	bool reset();
	bool parseSoldier();
	bool parseShop();
	bool doResult(CNetPacket *p);
	bool doShop(CNetPacket *p);
	bool onResultResp(byte ret);
	bool onShopResp(byte ret);
private:
	DataBoss m_data;
	bool m_isNew;
	map<byte, map<uint32_t, uint32_t> > m_soldier;
	vector<uint32_t> m_shop;
};

#endif /* BOSS_MANAGER_H_ */
