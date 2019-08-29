/*
 * ResourceManager.h
 *
 *  Created on: 2015-9-16
 *      Author: Administrator
 */

#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include "DataUserResource.h"
#include "DataPay.h"

class Player;
class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();
public:
	bool sendResourceList();
	bool load(uint32_t uid);
	bool onLogin();
	bool setUserResourceData(const DataUserResource & dur);
	bool setUserPayData(const DataPay & pay);
	bool doPacket(CNetPacket * packet);
	bool useResources(const ResourceCost & cost, const string & code);
	bool addResources(const ResourceCost & cost, const string & code);
	bool useMoney(const MoneyCost & cost, const string & code);
	bool addMoney(const MoneyCost & cost, const string & code);
	bool checkUseMoney(uint32_t coins, uint32_t cash);
	bool initMax();
	bool upR1(int32_t count, const string & code);
	bool upR2(int32_t count, const string & code);
	bool upR3(int32_t count, const string & code);
	bool upR1Rate(int32_t rate, const string & code);
	bool upR2Rate(int32_t rate, const string & code);
	bool upEnergy(int32_t energy, const string & code);
	bool upCash(int32_t cash, const string & code);
	bool upCoin(int32_t coin, const string & code);
	bool upLoyal(int32_t value, const string & code);
	bool updateResource(ResourceInfo & sInfo, const string & code);
	bool getResourceCapacity(uint32_t & cap);
	static uint32_t getMaxTLLimit();
	static uint32_t getTLRecoveInterval();
	bool isResourcesEnough(const ResourceCost & cost) const {
		return (m_ur.r1 >= cost.r1 && m_ur.r2 >= cost.r2 && m_ur.r3 >= cost.r3 && m_ur.r4 >= cost.r4 && m_ur.tl >= cost.tl);
	}
	bool isFull() const {
		return m_ur.r1 >= m_r1Max && m_ur.r2 >= m_r2Max;
	}
	bool isMoneyEnough(const MoneyCost & cost) const {
		return m_pay.cash >= cost.cash && m_pay.coins >= cost.coin;
	}
	bool isTLEnough(uint32_t tl) const {
		return m_ur.tl >= tl;
	}
	bool needTL() const {
		return m_ur.tl < m_tlMax;
	}
	uint32_t getTLMax() const {
		return m_tlMax;
	}
	DataUserResource* getResources() {
		return &m_ur;
	}
	DataPay* getPay() {
		return &m_pay;
	}
	void setPlayer(Player* player) {
		m_player = player;
	}
	uint32_t getR1Max() const {
		return m_r1Max;
	}
	uint32_t getR2Max() const {
		return m_r2Max;
	}
	void ResToCash(ResourceCost &res, uint32_t &cash);
private:
	bool doQueryResource(CNetPacket * packet);
	bool doUpdateResource(CNetPacket *packet);
	int32_t updateResourceInLimit(uint32_t & curRes, int32_t chgRes, uint32_t maxCap);
	uint32_t initTLMax();
	void checkValid();
private:
	DataUserResource m_ur;
	DataPay m_pay;
	Player * m_player;
	uint32_t m_r1Max;
	uint32_t m_r2Max;
	uint32_t m_tlMax;
};
#endif /* RESOURCE_MANAGER_H_ */
