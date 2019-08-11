/*
 * ShopManager.cpp
 *
 * Created on: 2019年8月9日
 *
 * Author: next
 *
 * */

#include "BattleInc.h"
#include "ShopManager.h"

enum {
	SELL_DAY_LIMIT = 1,
	SELL_WEEK_LIMIT = 2,
	SELL_FOREVER_LIMIT = 3,
	SELL_WEEK_ACTIVE_LIMIT = 4,
};

ShopManager::ShopManager() {
}
bool ShopManager::addShopData(UserCache& cache, uint32_t id) {
	DataShop data;
	data.init(cache.uid_, TYPE_ATTR_SHOP_MALL, id);
	cache.shop_.insert(make_pair(data.id, data));
	ATTR_DB_ADD(data);
	return true;
}

bool ShopManager::resetshopdata(UserCache& cache) {
	return true;
}

int ShopManager::Process(uint32_t uid, logins::SBuyReq *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERROR;
	}

	const CfgShop::ShopCell cfg = ShopCfgWrap().get(req->id);
	if(cfg.item_id() != req->itemId || cfg.real_price() != req->realPrice) {
		error_log("buy data errorshopId:%u item_id:%u real price:%u", req->id, req->itemId, req->realPrice);
		return R_ERROR;
	}
	if(0 == cache.shop_.count(req->id)) {
		addShopData(cache, req->id);
	}
	//每日，每周数据更新
	resetshopdata(cache);
	DataShop& data = cache.shop_[req->id];

	if (!UserManager::Instance()->UseMoney(uid, MONEY_GOLD, req->realPrice, "shopping mall")) {
		return R_ERROR;
	}
	UserManager::Instance()->AddItem(uid, req->itemId, req->num, "admin");
	data.cnt++;
	data.ts = Time::GetGlobalTime();
	ATTR_DB_SET(data);

	return R_SUCCESS;
}

int ShopManager::Sync(const UserCache& cache, uint32_t cmd, msgs::SShopInfo* resp) {
	map<uint32_t, DataShop>::const_iterator it = cache.shop_.begin();
	for(; it != cache.shop_.end(); ++it) {
		const CfgShop::ShopCell& cfg = ShopCfgWrap().get(it->second.id);
		switch(cfg.limit_type()) {
		case SELL_DAY_LIMIT:
			resp->limitSellsDay_.insert(make_pair(cfg.id(), cfg.buy_limit() - it->second.cnt));
			break;
		case SELL_WEEK_LIMIT:
			resp->limitSellsWeek_.insert(make_pair(cfg.id(), cfg.buy_limit() - it->second.cnt));
			break;
		case SELL_FOREVER_LIMIT:
			resp->limitSellsForever_.insert(make_pair(cfg.id(), cfg.buy_limit() - it->second.cnt));
			break;
		case SELL_WEEK_ACTIVE_LIMIT:
			resp->limitSellsWeekActive_.insert(make_pair(cfg.id(), cfg.buy_limit() - it->second.cnt));
			break;
		default:
			break;
		}
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return R_SUCCESS;
}
