/*
 * ShopManager.h
 *
 * Created on: 2019年8月9日
 *
 * Author: next
 *
 * */

#ifndef _SHOP_MANAGER_H_
#define _SHOP_MANAGER_H_

#include "BattleBaseInc.h"

class ShopManager: public CSingleton<ShopManager>{
private:
	friend class CSingleton<ShopManager>;
	ShopManager();
public:
	bool addShopData(UserCache& cache, uint32_t id);
	bool resetshopdata(UserCache& cache);
public:
	int Process(uint32_t uid, logins::SBuyReq *req);
public:
	int Sync(const UserCache& cache, uint32_t cmd, msgs::SShopInfo* resp);
};

#endif /*_SHOP_MANAGER_H_*/
