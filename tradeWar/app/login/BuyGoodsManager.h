#ifndef BUYGOODS_MANAGER_H_
#define BUYGOODS_MANAGER_H_

#include "Kernel.h"
#include "NetPacket.h"

class BuyGoodsManager {
private:
	BuyGoodsManager() {
	}
public:
	static BuyGoodsManager* getInstance() {
		static BuyGoodsManager _ins;
		return &_ins;
	}
	~BuyGoodsManager() {
	}
public:
	bool doTransitRequest(CNetPacket *packet);
	bool doLoginRequest(CNetPacket *packet);
	bool doGetBalance(CNetPacket *packet);
	bool doGetBalanceRes(CNetPacket *packet);
	bool doPay(CNetPacket *packet);
	bool doPayRes(CNetPacket *packet);
	bool doGiftExchange(CNetPacket *packet);
	bool doGiftExchangeRes(CNetPacket *packet);
	bool doAdminCharge(uint32_t uid, uint32_t cash, uint32_t itemid);
	bool doPerOrder(CNetPacket *packet);
	bool doPerOrderRes(CNetPacket *packet);
private:
	void onPay(uint32_t uid, uint32_t cash, uint32_t itemid);
};

#endif /* BUYGOODS_MANAGER_H_ */
