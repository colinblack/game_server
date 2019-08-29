/*
 * ArenaManager.h
 *
 *  Created on: 2019年2月27日
 *      Author: Administrator
 */

#ifndef ARENA_MANAGER_H_
#define ARENA_MANAGER_H_

#include "IManager.h"
#include "DataInc.h"

struct DataArenaShop {
	byte id;
	uint32_t cnt;

	DataArenaShop() {
		id = 0;
		cnt = 0;
	}
};

class ArenaManager: public IManager {
public:
	enum {
		ARENA_ATT_FLAG = 1,  //attack
		ARENA_DEF_FLAG = 2   //defend
	};
	ArenaManager();
	virtual ~ArenaManager();
	bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool save();
	bool onLogin();
protected:
	bool push();
	bool reset();
	bool loadShop();
	bool loadTarget();
	bool doQuery(CNetPacket *packet);
	bool doBuyEnergy(CNetPacket *packet);
	bool doBeginAttack(CNetPacket *packet);
	bool doEndAttack(CNetPacket *packet);
	bool doGetRank(CNetPacket *packet);
	bool doRankReward(CNetPacket *packet);
	bool doGetShop(CNetPacket *packet);
	bool doShopBuy(CNetPacket *packet);
	bool doGetLog(CNetPacket *packet);
	bool doRefresh(CNetPacket *packet);
	bool doShopRefresh(CNetPacket *packet);
	bool onBeginAttackResp(byte ret, uint32_t uid, uint32_t r);
	bool onShopBuyResp(byte ret);
	bool onShopRefreshResp(byte ret);
	bool onEndAttackResp(byte ret, uint16_t from, uint16_t to);
	bool onBuyEnergyResp(byte ret);
	bool onCommonResp(byte sub, byte ret);
	bool onAttack(uint32_t uid, uint32_t r, bool win, const string &s, const string &t, const string &sd, const string &sk);
	bool packetErrTarget(IBuffer *buff, byte ret);
	bool packetTargets(IBuffer *buff);
	bool addLog(uint32_t uid, uint32_t ouid, byte ty, uint32_t fr, uint32_t to, bool win, const string &s, const string &t, const string &sd, const string &sk);
	bool refreshShop();
	bool packShop(IBuffer *buff);
	bool fixLogSize();
private:
	DataArena m_data;
	map<uint32_t, DataArenaLog> m_logs;
	vector<DataArenaShop> m_shops;
	vector<uint32_t> m_targets;
	bool m_new_data;
	uint32_t m_refresh_ts;
};

#endif /* ARENA_MANAGER_H_ */
