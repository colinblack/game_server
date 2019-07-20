/*
 * EquipsManager.cpp
 *
 *  Created on: 2019年6月12日
 *      Author: Administrator
 */

#include "EquipsManager.h"
#include "BattleInc.h"

EquipsManager::EquipsManager() {
}

bool EquipsManager::ActorLogin(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	cache.role_bag_.clear();
	map<uint32_t, DataEquip>::iterator itr = cache.equip_.begin();
	for (; itr != cache.equip_.end(); ++itr) {
		DataEquip &item = itr->second;
		if (IS_BAG_ROLE(item.bag)) {
			InitRoleBag(cache, item);
		}
	}
	return true;
}

bool EquipsManager::ActorCreate(uint32_t uid, uint32_t career) {
	return true;
}

bool EquipsManager::InitRoleBag(UserCache &cache, DataEquip &item) {
	if (item.bag <= BAG_ROLE) {
		return false;
	}
	int rid = item.bag - BAG_ROLE;
	map<byte, DataRole>::iterator itr = cache.role_.find(rid);
	if (itr == cache.role_.end()) {
		error_log("rid error uid=%u rid=%u", cache.uid_, rid);
		return false;
	}
	DataRole &role = itr->second;
	const CfgItem::Equip &cfg = ItemCfgWrap().GetEquip(item.id);
	if (cfg.career() != static_cast<uint32_t>(role.career)) {
		error_log("career error uid=%u rid=%u cfg=%u data=%u",
				cache.uid_, rid, cfg.career(), role.career);
		return false;
	}
	map<byte, uint32_t> &bag = cache.role_bag_[rid];
	map<byte, uint32_t>::iterator bagItr = bag.find(cfg.part());
	if (bagItr != bag.end()) {
		item.bag = BAG_ALL;
		DataEquipManager::Instance()->Set(item);
	} else {
		bag[cfg.part()] = item.ud;
		debug_log("uid=%u,rid=%u,part=%u,ud=%u", cache.uid_, rid, cfg.part(), item.ud);
	}
	return true;
}

bool EquipsManager::GetBagList(const UserCache &cache, int16_t type, bool multiRole, vector<msgs::SPlayerBag> &msg) {
	map<uint16_t, DataBagExtend>::const_iterator itr = cache.bag_extend_.find(type);
	uint16_t extendNum = 0;
	if (itr != cache.bag_extend_.end()) {
		extendNum = itr->second.num;
	}
	msgs::SPlayerBag item;
	if (multiRole) {
		for (short i = 1; i <= MAX_ROLE_COUNT; ++i) {
			item.clear();
			item.type_ = type + i;
			item.extendNum_ = extendNum;
			msg.push_back(item);
		}
	} else {
		item.clear();
		item.type_ = type;
		item.extendNum_ = extendNum;
		msg.push_back(item);
	}
	return true;
}

bool EquipsManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	map<byte, map<byte, uint32_t> >::const_iterator bagItr = cache.role_bag_.find(rid);
	if (bagItr == cache.role_bag_.end()) {
		return true;
	}

	Json::Reader reader;
	Json::Value extend;
	ItemCfgWrap cfg_wrap;
	map<uint32_t, DataEquip>::const_iterator itr;
	const map<byte, uint32_t> &bag = bagItr->second;
	map<byte, uint32_t>::const_iterator equipItr = bag.begin();
	for (;equipItr != bag.end(); ++equipItr) {
		itr = cache.equip_.find(equipItr->second);
		if (itr == cache.equip_.end()) {
			continue;
		}

		const DataEquip &equip = itr->second;
		const CfgItem::Equip &cfg = cfg_wrap.GetEquip(equip.id);
		PropertyCfg::setProps(cfg.attr(), 1.0, props);

		extend.clear();
		if (equip.ext.empty() || !reader.parse(equip.ext, extend) || !extend.isMember("attrs") || !extend["attrs"].isArray()) {
			continue;
		}

		for (size_t i = 0; i < extend["attrs"].size(); ++i) {
			uint32_t attr_id = 0;
			Json::GetUInt(extend["attrs"], i, attr_id);
			const CfgItem::Attr &attr = cfg_wrap.GetAttr(attr_id);
			PropertyCfg::setProps(attr.attr(), 1.0, props);
		}
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "equip");
	return true;
}

bool EquipsManager::RandomAttr(DataEquip &equip) {
	Json::Value value = Json::Value(Json::objectValue);
	Json::Reader reader;
	if (!equip.ext.empty() && !reader.parse(equip.ext, value)) {
		error_log("parse equip extend error uid=%u ud=%u ext=%s", equip.uid, equip.ud, equip.ext.c_str());
		return false;
	}

	const CfgItem::Equip &cfg = ItemCfgWrap().GetEquip(equip.id);
	uint32_t star = 0;
	if (!RandomStar(cfg, star)) {
		error_log("random star error uid=%u ud=%u ext=%s", equip.uid, equip.ud, equip.ext.c_str());
		return false;
	}

	if (star > 0) {
		value["star"] = star;
	}

	set<uint32_t> ids;
	if (!RandomSub(cfg, star, ids)) {
		error_log("random sub error uid=%u ud=%u ext=%s", equip.uid, equip.ud, equip.ext.c_str());
		return false;
	}
	if (ids.empty()) {
		return true;
	}

	if (!value.isMember("attr")) {
		value["attrs"] = Json::Value(Json::arrayValue);
	}
	set<uint32_t>::iterator itr = ids.begin();
	for (; itr != ids.end(); ++itr) {
		value["attrs"].append(*itr);
	}
	equip.ext = Json::ToString(value);

	return true;
}

bool EquipsManager::RandomStar(const CfgItem::Equip &cfg, uint32_t &star) {
	star = 0;
	if (cfg.starrate_size() == 0) {
		return true;
	} else if (cfg.starrate_size() == 1) {
		star = cfg.starrate(0).star();
		return true;
	}
	vector<uint32_t> rates;
	uint32_t sum_rate = 0;
	for (int i = 0; i < cfg.starrate_size(); ++i) {
		sum_rate += cfg.starrate(i).rate();
		rates.push_back(sum_rate);
	}
	uint32_t rate = Math::GetRandomInt(sum_rate == 0 ? 1 : sum_rate);
	for (size_t i = 0; i < rates.size(); ++i) {
		if (rate < rates[i]) {
			star = cfg.starrate(i).star();
			break;
		}
	}
	return true;
}

bool EquipsManager::RandomSub(const CfgItem::Equip &cfg, uint32_t star, set<uint32_t> &ids) {
	ids.clear();
	if (cfg.sub() == 0) {
		return true;
	}
	uint32_t num = cfg.color() > 3 ? cfg.color() - 3 : 0;
	if (num == 0) {
		return true;
	}

	const map<uint32_t, list<uint32_t> > &indexs = ConfigManager::Instance()->equip_attr_cfg_Pool;
	const map<uint32_t, list<uint32_t> >::const_iterator itr = indexs.find(cfg.sub());
	if (itr == indexs.end()) {
		return true;
	}
	const list<uint32_t> &group = itr->second;
	const CfgItem::Attrs attr_cfg = ConfigManager::Instance()->equip_attr_cfg_.m_config;

	vector<uint32_t> pool;

	list<uint32_t>::const_iterator gItr;
	for (gItr = group.begin(); gItr != group.end(); ++gItr) {
		const CfgItem::Attr &acfg = attr_cfg.attrs(*gItr);
		if (acfg.star() > star || !acfg.best()) {
			continue;
		}
		pool.push_back(*gItr);

	}
	for (gItr = group.begin(); gItr != group.end(); ++gItr) {
		if (pool.size() >= num) {
			break;
		}
		const CfgItem::Attr &acfg = attr_cfg.attrs(*gItr);
		if (!acfg.best()) {
			pool.push_back(*gItr);
		}
	}

	uint32_t max_star = 0;
	uint32_t max_star_index = 0;

	vector<uint32_t> rates;
	uint32_t rate_sum = 0;
	vector<uint32_t>::iterator pItr;
	for (pItr = pool.begin(); pItr != pool.end(); ++pItr) {
		const CfgItem::Attr &acfg = attr_cfg.attrs(*pItr);
		rate_sum += acfg.rate();
		rates.push_back(rate_sum);
		if (acfg.star() > max_star) {
			max_star = acfg.star();
			max_star_index = *pItr;
		}
	}

	//最大星级必出
	ids.insert(attr_cfg.attrs(max_star_index).id());

	uint32_t ctrl = 0;
	while (ids.size() < num && 100 > ctrl++) {
		uint32_t cur_rate = Math::GetRandomInt(rate_sum == 0 ? 1 : rate_sum);
		for (size_t i = 0; i < rates.size(); ++i) {
			if (cur_rate < rates[i]) {
				ids.insert(attr_cfg.attrs(pool[i]).id());
				break;
			}
		}
	}

	return true;
}

bool EquipsManager::OpenGift(uint32_t id, uint32_t num, uint32_t select, Award &data) {
	ItemCfgWrap cfg_wrap;
	const CfgItem::Gift &cfg = cfg_wrap.GetGift(id);
	if (cfg_wrap.IsFixedGift(cfg)) {
		return data.Format(cfg.reward(), num);
	}
	if (cfg_wrap.IsRandomGift(cfg)) {
		return RandomGift(cfg, num, data);
	}
	if (cfg_wrap.IsFixedRandomGift(cfg)) {
		data.Format(cfg.reward(), num);
		RandomExtend(cfg, num, data);
	}
	if (cfg_wrap.IsSelectGift(cfg)) {
		for (int i = 0; i < cfg.reward_size(); ++i) {
			if ((i+1) == select) {
				data.Add(cfg.reward(i).item(), cfg.reward(i).num() * num);
				return true;
			}
		}
		return false;
	}

	return true;
}

bool EquipsManager::RandomGift(const CfgItem::Gift &cfg, uint32_t num, Award &data) {
	uint32_t rate_sum = 0;
	vector<uint32_t> rates;
	for (int i = 0; i < cfg.reward_size(); ++i) {
		rate_sum += cfg.reward(i).rate();
		rates.push_back(rate_sum);
	}
	while (num > 0) {
		uint32_t rate = Math::GetRandomInt(rate_sum == 0 ? 1 : rate_sum);
		for (size_t i = 0; i < rates.size(); ++i) {
			if (rate < rates[i]) {
				data.Add(cfg.reward(i).item(), cfg.reward(i).num());
				break;
			}
		}
		--num;
	}
	return true;
}

bool EquipsManager::RandomExtend(const CfgItem::Gift &cfg, uint32_t num, Award &data) {
	uint32_t rate_sum = 0;
	vector<uint32_t> rates;
	for (int i = 0; i < cfg.extend_size(); ++i) {
		rate_sum += cfg.extend(i).rate();
		rates.push_back(rate_sum);
	}
	while (num > 0) {
		uint32_t rate = Math::GetRandomInt(rate_sum == 0 ? 1 : rate_sum);
		for (size_t i = 0; i < rates.size(); ++i) {
			if (rate < rates[i]) {
				data.Add(cfg.extend(i).item(), cfg.extend(i).num());
				break;
			}
		}
		--num;
	}
	return true;
}

bool EquipsManager::IsWear(const UserCache &cache, byte rid, byte type) {
	map<byte, map<byte, uint32_t> >::const_iterator itr = cache.role_bag_.find(rid);
	if (itr == cache.role_bag_.end()) {
		return false;
	}
	map<byte, uint32_t>::const_iterator bItr = itr->second.find(type);
	if (bItr == itr->second.end()) {
		return false;
	}
	return true;
}

const DataEquip& EquipsManager::GetEquipById(const UserCache &cache, uint32_t itemId) {
	map<uint32_t, DataEquip>::const_iterator it = cache.equip_.begin();
	for(; it != cache.equip_.end(); ++it) {
		if(it->second.id == itemId) {
			return it->second;
		}
	}
	error_log("user has not own item id:%d ", itemId);
	throw std::runtime_error("use not own this item");
}

int EquipsManager::Process(uint32_t uid, logins::SBagDecompose *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	vector<int64_t>::iterator it = req->uidList.begin();
	for(; it != req->uidList.end(); ++it) {
		if(cache.equip_.count(*it) == 0) {
			error_log("equip_ud error u=%u", *it);
			return R_ERROR;
		}
	}
	//装备ID和装备数量映射
	map<uint32_t, uint32_t> idMap;
	it = req->uidList.begin();
	for(; it != req->uidList.end(); ++it) {
		if(!idMap.count(cache.equip_[*it].id)) {
			idMap.insert(make_pair(cache.equip_[*it].id, 1));
		} else {
			idMap[cache.equip_[*it].id] += 1;
		}
	}

	map<uint32_t, uint32_t>::iterator iter = idMap.begin();
	for(; iter != idMap.end(); ++iter) {
		UpdateManager::Instance()->SetCode(UC_EquipDecompose);
		UserManager::Instance()->UseItem(uid, iter->first, iter->second, "Equip smelt");
	}
	Award SmeltRward;
	ItemCfgWrap cfg_wrap;
	iter = idMap.begin();
	for(; iter != idMap.end(); ++iter) {
		const CfgItem::Equip &cfg = cfg_wrap.GetEquip(iter->first);
		SmeltRward.Format(cfg.smeltaward(), iter->second);
	}

	UserManager::Instance()->Reward(uid, SmeltRward, "equip Smelt Rward");
	return R_SUCCESS;
}

int EquipsManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerBagList *resp) {
	resp->clear();
	GetBagList(cache, BAG_ALL, false, resp->bags_);
	GetBagList(cache, BAG_ROLE, true, resp->bags_);
	GetBagList(cache, BAG_CARD, false, resp->bags_);
	GetBagList(cache, BAG_ROLE_RUNE, true, resp->bags_);
	GetBagList(cache, BAG_TREASURE_EQUIP, false, resp->bags_);
	GetBagList(cache, BAG_TREASURE_DIANFENG, false, resp->bags_);
	GetBagList(cache, BAG_TREASURE_SANJIE, false, resp->bags_);

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}

	return 0;
}

int EquipsManager::Process(uint32_t uid, logins::SEquipEquip *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	if (cache.role_.find(req->roleId_) == cache.role_.end()) {
		error_log("role not exists uid=%u rid=%u", uid, req->roleId_);
		return R_ERROR;
	}
	UpdateManager::Instance()->SetCode(UC_MoveItem);

	ItemCfgWrap cfg_wrap;
	uint16_t bag_type = req->roleId_ + BAG_ROLE;
	map<uint32_t, DataEquip>::iterator addItr;
	map<uint32_t, DataEquip>::iterator subItr;
	map<byte, uint32_t>::iterator bagItr;

	map<uint32_t, DataEquip> &map_equip = cache.equip_;
	map<byte, uint32_t> &bag = cache.role_bag_[req->roleId_];

	bool chg = false;
	vector<int64_t>::iterator itr = req->uds_.begin();
	for (; itr != req->uds_.end(); ++itr) {
		addItr = map_equip.find(*itr);
		if (addItr == map_equip.end()) {
			continue;
		}
		DataEquip &wear = addItr->second;
		const CfgItem::Equip &cfg = cfg_wrap.GetEquip(wear.id);

		wear.bag = bag_type;
		DataEquipManager::Instance()->Set(wear);
		UpdateManager::Instance()->ChgBag(uid, BAG_ALL, bag_type, wear);

		bagItr = bag.find(cfg.part());
		if (bagItr != bag.end()) {
			subItr = map_equip.find(bagItr->second);
			if (subItr != map_equip.end()) {
				DataEquip &unwear = subItr->second;
				unwear.bag = BAG_ALL;
				DataEquipManager::Instance()->Set(unwear);
				UpdateManager::Instance()->ChgBag(uid, bag_type, BAG_ALL, unwear);
			}
		}

		bag[cfg.part()] = wear.ud;

		chg = true;
	}

	if (chg) {
		PropertyManager::Instance()->AddUser(uid);
	}

	return 0;
}

int EquipsManager::Process(uint32_t uid, logins::SBagOpenGrid *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	const map<uint32_t, map<uint32_t, uint32_t> > &indexs = ConfigManager::Instance()->bag_grid_cfg_Index;
	map<uint32_t, map<uint32_t, uint32_t> >::const_iterator cfgItr = indexs.find(req->bagType_);
	if (cfgItr == indexs.end()) {
		error_log("bag type not exists uid=%u type=%u", uid, req->bagType_);
		return R_ERROR;
	}

	DataBagExtend &grid_data = cache.bag_extend_[req->bagType_];

	uint32_t cost = 0;
	uint32_t cur = grid_data.num;
	const map<uint32_t, uint32_t> &cfg = cfgItr->second;
	map<uint32_t, uint32_t>::const_iterator costItr;
	for (uint32_t i = cur+1; i <= cur + req->gridNum_; ++i) {
		costItr = cfg.find(i);
		if (costItr == cfg.end()) {
			error_log("get cost error uid=%u type=%u num=%u", uid, req->bagType_, i);
			return R_ERROR;
		}
		cost += costItr->second;
	}

	UpdateManager::Instance()->SetCode(UC_OpenBagGrid);
	string code;
	String::Format(code, "open_grid_%u_%u", req->bagType_, req->gridNum_);
	if (!UserManager::Instance()->UseMoney(uid, MONEY_GOLD, cost, code)) {
		return R_ERROR;
	}

	grid_data.bag = req->bagType_;
	grid_data.num = cur + req->gridNum_;

	if (grid_data.uid == 0) {
		grid_data.uid = uid;
		DataBagExtendManager::Instance()->Add(grid_data);
	} else {
		DataBagExtendManager::Instance()->Set(grid_data);
	}
	UpdateManager::Instance()->BagExtend(uid, grid_data);

	debug_log("uid=%u,t=%d,id=%d,num=%d", req->bagType_, req->gridId_, req->gridNum_);

	return 0;
}

int EquipsManager::Process(uint32_t uid, logins::SBagUse *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	map<uint32_t, DataEquip>::iterator itr = cache.equip_.find(req->itemUid_);
	if (itr == cache.equip_.end()) {
		error_log("equip not exists uid=%u ud=%u", uid, req->itemUid_);
		return R_ERROR;
	}
	DataEquip &equip = itr->second;
	if (static_cast<int32_t>(equip.num) < req->itemNum_) {
		error_log("equip limit uid=%u ud=%u num=%u use=%u", uid, req->itemUid_, equip.num, req->itemNum_);
		return R_ERROR;
	}
	if (static_cast<int32_t>(equip.bag) != req->bagType_) {
		error_log("bag error uid=%u ud=%u bag=%u,%u ", uid, req->itemUid_, equip.bag, req->bagType_);
		return R_ERROR;
	}


	Award reward;
	ItemCfgWrap cfg_wrap;

	// fix by memory 背包中使用道具 判断了类型是不是称号  如果是发送消息激活
	if(cfg_wrap.IsTitle(equip.id)){
		const CfgItem::Item &cfg = ItemCfgWrap().GetItem(equip.id); // 通过id去获取单条数据
		uint32_t titleID  = cfg.data(); //称号限时

		if(UpdateManager::Instance()->S2CPlayerTitle(uid,titleID)){ // 1168-1075
			TitleManager::Instance()->ActiveTitle(uid, 1, titleID); // 激活称号，存入数据库
			PropertyManager::Instance()->AddUser(uid);	// 触发添加称号属性函数 CalcProperty
			UpdateManager::Instance()->roleTitle(uid, 1, titleID);  // 1167-1904
			UpdateManager::Instance()->roleShows(uid, titleID,true, TitleManager::Instance()->GetShowId()); // 952-956
		}
	}

	if (cfg_wrap.IsGift(equip.id)) {
		if (!OpenGift(equip.id, req->itemNum_, req->value_, reward)) {
			error_log("open gift error uid=%u ud=%u id=%u", uid, req->itemUid_, equip.id);
			return R_ERROR;
		}
	}
	UpdateManager::Instance()->SetCode(UC_UseItem);
	string code;
	String::Format(code, "bag_use_%u_%u", equip.id, req->itemNum_);
	if (!UserManager::Instance()->UseItem(uid, equip.id, req->itemNum_, code)){
		return R_ERROR;
	}
	UserManager::Instance()->Reward(uid, reward, code);
	debug_log("uid=%u", uid);
	return 0;
}

int EquipsManager::Process(uint32_t uid, logins::SBagMoveItem *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}

	if (req->toBagType_ == 0 || req->toBagType_ == req->fromBagType_) {
		error_log("to bag type error uid=%u", uid);
		return R_ERROR;
	}

	map<uint32_t, DataEquip>::iterator itr = cache.equip_.find(req->itemUid_);
	if (itr == cache.equip_.end()) {
		error_log("equip not exists uid=%u ud=%u", uid, req->itemUid_);
		return R_ERROR;
	}

	DataEquip &equip = itr->second;
	if (equip.bag != req->fromBagType_) {
		error_log("equip bag error uid=%u now=%u need=%u", uid, equip.bag, req->fromBagType_);
		return R_ERROR;
	}

	UpdateManager::Instance()->SetCode(UC_MoveItem);

	equip.bag = req->toBagType_;

	DataEquipManager::Instance()->Set(equip);

	UpdateManager::Instance()->ChgBag(uid, req->fromBagType_, req->toBagType_, equip);

	return 0;
}

int EquipsManager::Process(uint32_t uid, logins::SBagMoveItemAll *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}

	if (req->toBagType_ == 0 || req->toBagType_ == req->fromBagType_) {
		error_log("to bag type error uid=%u", uid);
		return R_ERROR;
	}

	list<uint32_t> uds;
	map<uint32_t, DataEquip>::iterator itr = cache.equip_.begin();
	for (; itr != cache.equip_.end(); ++itr) {
		DataEquip &equip = itr->second;
		if (equip.bag == req->fromBagType_) {
			uds.push_back(equip.ud);
		}
	}

	UpdateManager::Instance()->SetCode(UC_MoveItem);

	list<uint32_t>::iterator uItr = uds.begin();
	for (; uItr != uds.end(); ++uItr) {
		DataEquip &equip = cache.equip_[*uItr];
		equip.bag = req->toBagType_;
		DataEquipManager::Instance()->Set(equip);
		UpdateManager::Instance()->ChgBag(uid, req->fromBagType_, req->toBagType_, equip);
	}

	return 0;
}

int EquipsManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerBagItemList *resp) {
	map<uint32_t, msgs::SPlayerBagItemList> msgs;
	msgs::SPlayerItem item;
	map<uint32_t, DataEquip>::const_iterator itr = cache.equip_.begin();
	for (; itr != cache.equip_.end(); ++itr) {
		const DataEquip &equip = itr->second;
		if (equip.num == 0) {
			continue;
		}
		item.clear();
		item.itemUid_ = equip.ud;
		item.itemId_ = equip.id;
		item.itemNum_ = equip.num;
		item.bagType_ = equip.bag;
		item.createDt_ = equip.ts * 1000LL;
		item.extend_ = equip.ext;
		msgs::SPlayerBagItemList &msg = msgs[equip.bag];
		msg.bagType_ = equip.bag;
		msg.items_.push_back(item);
	}

	if (msgs.empty()) {
		msgs::SPlayerBagItemList &all = msgs[BAG_ALL];
		all.bagType_ = BAG_ALL;
		all.items_.clear();
		for (byte rid = 1; rid <= cache.base_.role_num; ++rid) {
			msgs::SPlayerBagItemList &role = msgs[BAG_ROLE + rid];
			role.bagType_ = BAG_ROLE + rid;
			role.items_.clear();
		}
	}

	map<uint32_t, msgs::SPlayerBagItemList>::iterator it = msgs.begin();
	for (; it != msgs.end(); ++it) {
		LogicManager::Instance()->SendMsg(cache.uid_, cmd, &(it->second));
	}
	return 0;
}

