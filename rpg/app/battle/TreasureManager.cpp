/*
 * Treasure.cpp
 *
 *  Created on: 2019年7月2日
 *      Author: next
 */
#include "TreasureManager.h"
#include "BattleInc.h"

enum Max{
	MAX_LEVEL = 50,
	MAX_STAR = 10,
};

enum TreasureType {
	EXP_TYPE = 36,
};

enum DanCount {
	DAN_MAX_CNT = 2,
};

TreasureManager::TreasureManager() {
}

TreasureManager::~TreasureManager() {
}

int TreasureManager::Process(uint32_t uid, logins::SActiveTreasure *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERROR;
	}
	map<uint32_t, DataTreasure>::iterator itr = cache.treasure_.begin();
	for(; itr != cache.treasure_.end(); ++itr) {
		if(static_cast<int32_t>(itr->second.type) == req->type_) {
			error_log("Type:%d treasure is already exist", req->type_);
			return R_ERROR;
		}
	}

	DataTreasure data;
	data.uid = uid;
	data.type = req->type_;
	data.level = 1;
	data.star = 0;
	data.bless = 0;
	data.dan1 = 0;
	data.dan2 = 0;
	DataTreasureManager::Instance()->Add(data);
	cache.treasure_.insert(make_pair(data.type, data));

	UpdateManager::Instance()->Treasure(uid, data);

	debug_log("active Treasure uid=%u,type=%d", uid, req->type_);
	return 0;
}

int TreasureManager::Process(uint32_t uid, logins::STreasureAdvance *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	if(cache.treasure_.count(req->type_) == 0) {
		error_log("this type:%d Treasure not active", req->type_);
		return R_ERROR;
	}

	DataTreasure& data = cache.treasure_[req->type_];
	if(data.level >= MAX_LEVEL && data.star >= 1) {
		error_log("level:%d upgrade already max", data.level);
		return R_ERROR;
	}
	if(data.star == MAX_STAR) {
		data.level++;
		data.star = 0;
		DataTreasureManager::Instance()->Set(data);
		UpdateManager::Instance()->Treasure(uid, data);
		return 0;
	}
	const CfgItem::Item& item = ItemCfgWrap().GetItem(req->itemId_);
	if(item.subtype() != EXP_TYPE) {
		error_log("subType:%d error", item.subtype());
		return R_ERROR;
	}
	data.bless += item.data();
	uint32_t id = TreasureCfgWrap().GetIdByType(data.type, data.level, data.star + 1);
	const CfgTreasure::Treasure& cfg = TreasureCfgWrap().GetById(id);
	while(data.bless >= cfg.bless() && data.star < MAX_STAR) {
		data.bless = data.bless - cfg.bless();
		data.star++;
	}
	map<uint32_t, DataEquip>::const_iterator it = cache.equip_.begin();
	for(; it != cache.equip_.end(); ++it) {
		if(it->second.id == static_cast<uint32_t>(req->itemId_)) {
			break;
		}
	}
	if(it == cache.equip_.end()) {
		error_log("user not own this item:%d", req->itemId_);
		return R_ERROR;
	}
	UpdateManager::Instance()->SetCode(UC_TreasureAdvance);
	if(!UserManager::Instance()->UseItem(uid, req->itemId_, 1, "Treasure upgrade")) {
		error_log("UseItem error id:%d, num:%d", req->itemId_, 1);
		return R_ERROR;
	}

	PropertyManager::Instance()->AddUser(uid);

	DataTreasureManager::Instance()->Set(data);
	UpdateManager::Instance()->Treasure(uid, data);
	MissionManager::Instance()->onSubMission(uid, MT_ACTIVATE_TREASURE, req->type_, 1);
	MissionManager::Instance()->onSubMission(uid, MT_TREASURE_UPGRADE, req->type_, data.level);
	return 0;
}

int TreasureManager::Process(uint32_t uid, logins::STreasureEatDan *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	if(cache.treasure_.count(req->type_) == 0) {
		error_log("this type:%d Treasure not active", req->type_);
		return R_ERROR;
	}

	DataTreasure& treasure = cache.treasure_[req->type_];
	uint32_t cost = 0;
	uint32_t dan_num = 0;
	for(uint32_t index = 0; index < DAN_MAX_CNT; ++index) {
		uint32_t dan_id = TreasureCfgWrap().GetDanId(treasure.type, treasure.level, treasure.star, index);
		uint32_t limit = TreasureCfgWrap().GetDanLimit(treasure.type, treasure.level, treasure.star, dan_id);

		map<uint32_t, DataEquip>::iterator itr = cache.equip_.begin();
		for(; itr != cache.equip_.end(); ++itr) {
			if(itr->second.id == dan_id) {
				dan_num += cache.equip_[itr->second.ud].num;
				break;
			}
		}

		uint16_t *ptr = treasure.GetDan(index);
		if(*ptr + dan_num >= limit) {
			cost = limit - *ptr;
			*ptr = limit;
		} else {
			cost = dan_num;
			*ptr = *ptr + cost;
		}
		UpdateManager::Instance()->SetCode(UC_TreasureEatDan);
		if(!UserManager::Instance()->UseItem(uid, dan_id, cost, "treasure EatDan")) {
			return R_ERROR;
		}
		DataTreasureManager::Instance()->Set(treasure);
	}
	PropertyManager::Instance()->AddUser(uid);
	UpdateManager::Instance()->Treasure(uid, treasure);
	return 0;
}

int TreasureManager::Process(uint32_t uid, logins::STreasureDrawReq *req, logins::STreasureDrawResp *resp) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, TreasureHunt>::iterator itr = cache.m_treasure_hunt.find(req->type_);
	if (itr == cache.m_treasure_hunt.end()) {
		error_log("type not init uid=%u type=%u", uid, req->type_);
		return R_ERROR;
	}

	TreasureHunt &hunt = itr->second;

	DailyReset(hunt);

	switch (req->type_) {
	case TREASURE_HUNT_EQUIP:
		UpdateManager::Instance()->SetCode(UC_TreasureEquip);
		break;
	case TREASURE_HUNT_DIANFENG:
		UpdateManager::Instance()->SetCode(UC_TreasurePeak);
		break;
	case TREASURE_HUNT_SANJIE:
		UpdateManager::Instance()->SetCode(UC_TreasureThreeWorld);
		break;
	}

	resp->clear();
	if (!DoHunt(cache, req->type_, req->drewNum_, resp->drawIds_, resp->rewards_)) {
		error_log("hunt error uid=%u type=%u num=%u", uid, req->type_, req->drewNum_);
		return R_ERROR;
	}

	hunt.total_num += req->drewNum_;
	hunt.daily_num += req->drewNum_;
	DataAttr attr;
	hunt.ToAttr(attr);
	DataAttrManager::Instance()->Set(attr);

	UpdateManager::Instance()->Send(uid);
	SendHunt(hunt);

	debug_log("uid=%u,type=%u,num=%u", uid, req->type_, req->drewNum_);
	return 0;
}

int TreasureManager::Process(uint32_t uid, logins::STreasureGetRewardHisReq *req, logins::STreasureGetRewardHisResp *resp) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, TreasureHunt>::iterator itr = cache.m_treasure_hunt.find(req->type_);
	if (itr == cache.m_treasure_hunt.end()) {
		error_log("type not init %u", req->type_);
		return R_ERROR;
	}
	DailyReset(itr->second);
	TreasureRecordManager::Instance()->Get(req->type_, resp->records_);
	debug_log("uid=%u,type=%u", uid, req->type_);
	return 0;
}

int TreasureManager::Sync(const UserCache &cache, uint32_t cmd, msgs::STreasureAdvanceInfo *resp) {
	msgs::STreasureAdvanceSingle item;
	map<uint32_t, DataTreasure>::const_iterator itr = cache.treasure_.begin();
	for (; itr != cache.treasure_.end(); ++itr) {
		item.clear();
		item.type_ = itr->second.type;
		item.level_ = itr->second.level;
		item.star_ = itr->second.star;
		item.bless_ = itr->second.bless;
		uint32_t id = TreasureCfgWrap().GetIdByType(itr->second.type, itr->second.level, itr->second.star);
		const CfgTreasure::Treasure& cfg = TreasureCfgWrap().GetById(id);
		for(int i = 0; i < cfg.dans().dans_size(); ++i) {
			uint32_t id = TreasureCfgWrap().GetDanId(itr->second.type,itr->second.level, itr->second.star, i);
			const uint16_t* ptr = itr->second.GetDan(i);
			if(*ptr > 0) {
				item.danMap_.insert(make_pair(id, *ptr));
			}
		}
		resp->treasureMap_.insert(make_pair(item.type_, item));
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}

int TreasureManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerTreasureInfo *resp) {
	resp->clear();
	map<uint32_t, TreasureHunt>::const_iterator itr = cache.m_treasure_hunt.begin();
	msgs::SPlayerTreasure item;
	for (; itr != cache.m_treasure_hunt.end(); ++itr) {
		FormatHuntMsg(item, itr->second);
		resp->list_.push_back(item);
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}

bool TreasureManager::ActorLogin(uint32_t uid) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	InitHunt(cache);
	return true;
}

bool TreasureManager::InitHunt(UserCache &cache) {
	map<uint32_t, TreasureHunt>::iterator itr;
	for (uint32_t type = TREASURE_HUNT_EQUIP; type < TREASURE_HUNT_MAX; ++type) {
		itr = cache.m_treasure_hunt.find(type);
		if (itr != cache.m_treasure_hunt.end()) {
			DailyReset(itr->second);
			continue;
		}
		TreasureHunt draw;
		draw.uid = cache.uid_;
		draw.id = type;
		draw.ts = Time::GetGlobalTime();
		DataAttr attr;
		draw.ToAttr(attr);
		DataAttrManager::Instance()->Add(attr);
		cache.m_treasure_hunt[type] = draw;
	}
	return true;
}

bool TreasureManager::FormatHuntMsg(msgs::SPlayerTreasure &msg, const TreasureHunt &data) {
	msg.clear();
	msg.type_ = data.id;
	msg.drawNum_ = data.total_num;
	msg.useFreeNum_ = data.use_free;
	msg.todayNum_ = data.daily_num;
	msg.hasDraw50_ = data.has_fifty == 1;
	return true;
}

bool TreasureManager::DailyReset(TreasureHunt &data) {
	if (CTime::GetDayInterval(data.ts, Time::GetGlobalTime()) == 0) {
		return false;
	}
	data.daily_num = 0;
	data.ts = Time::GetGlobalTime();
	data.use_free = 0;
	return true;
}

bool TreasureManager::DoHunt(UserCache &cache, uint32_t type, uint32_t num, vector<int32_t> &ids, vector<int32_t> &items) {
	TreasureHunt &hunt = cache.m_treasure_hunt[type];
	uint32_t curr_num = hunt.total_num;
	uint32_t clv = cache.m_reinCarnInfo.reinCarnLevel;

	TreasureCfgWrap cfg_wrap;
	const CfgTreasure::HuntBase &cfg_base = cfg_wrap.GetHuntBase(type);

	const map<uint32_t, map<uint32_t, list<int32_t> > > &indexs = ConfigManager::Instance()->treasure_hunt_cfg_map;
	map<uint32_t, map<uint32_t, list<int32_t> > >::const_iterator itr = indexs.find(type);
	if (itr == indexs.end()) {
		error_log("config not the type %u", type);
		return false;
	}

	map<uint32_t, list<int32_t> > pools = itr->second;
	map<uint32_t, list<int32_t> >::iterator pItr;
	list<int32_t>::iterator it;
	for (pItr = pools.begin(); pItr != pools.end(); ++pItr) {
		list<int32_t> &pool = pItr->second;
		for (it = pool.begin(); it != pool.end();) {
			const CfgTreasure::Hunt &item = cfg_wrap.GetHuntByIndex(*it);
			if (item.career_level_min() > clv) {
				pool.erase(it++);
				continue;
			}
			if (item.career_level_max() > 0 && clv > item.career_level_max()) {
				pool.erase(it++);
				continue;
			}
			if (pItr->first != 0) {
				pools[0].push_back(*it);
			}
			++it;
		}
	}

	bool is_first_fifty = hunt.has_fifty == 0 && num == 50;

	Award reward;
	vector<uint32_t> records;
	for (uint32_t i = 0; i < num; ++i) {
		if (is_first_fifty && i == num - 1) {
			if (cfg_base.fifty() != 0) {
				const CfgTreasure::Hunt &item = cfg_wrap.GetHunt(cfg_base.fifty());
				if (!reward.IsExist(item.item())) {
					reward.Add(item.item(), item.num());
					break;
				}
			}
		}
		bool ret = true;
		uint32_t reward_id = 0;
		uint32_t reward_item = 0;
		uint32_t xiyou = 0;
		if (pools.count(curr_num)) {
			ret = DoRandom(pools[curr_num], reward, reward_id, reward_item, xiyou);
		} else {
			ret = DoRandom(pools[0], reward, reward_id, reward_item, xiyou);
		}
		if (!ret) {
			error_log("random error");
			return false;
		}
		ids.push_back(reward_id);
		items.push_back(reward_item);
		if (xiyou > 0) {
			records.push_back(reward_item);
		}
		curr_num += 1;
	}

	string code;
	String::Format(code, "treasure_hunt_%u_%u", type, num);

	if (num == 1 && hunt.use_free < cfg_base.free_num()) {
		hunt.use_free += 1;
	} else {
		uint32_t use_item = 0;
		uint32_t cost_num = cfg_base.cost_num() == 0 ? 1 : cfg_base.cost_num();
		if (cfg_base.cost_item() != 0) {
			use_item = UserManager::Instance()->TryUseItemMulti(cache.uid_, cfg_base.cost_item(), cost_num, num, code);
		}
		if (use_item < num) {
			uint32_t cost_gold = UserManager::Instance()->GetGoldDiscount(cfg_base.gold() * (num - use_item));
			if (!UserManager::Instance()->UseMoney(cache.uid_, MONEY_GOLD, cost_gold, code)) {
				return false;
			}
		}
	}
	reward.Add(MONEY_COIN, num * 10000);
	if (cfg_base.score_item() != 0) {
		reward.Add(cfg_base.score_item(), num);
	}
	uint32_t bag_type = BAG_ALL;
	switch (type) {
	case TREASURE_HUNT_EQUIP:
		bag_type = BAG_TREASURE_EQUIP;
		break;
	case TREASURE_HUNT_DIANFENG:
		bag_type = BAG_TREASURE_DIANFENG;
		break;
	case TREASURE_HUNT_SANJIE:
		bag_type = BAG_TREASURE_SANJIE;
		break;
	}
	if (!UserManager::Instance()->Reward(cache.uid_, reward, code, bag_type)) {
		return false;
	}

	if (is_first_fifty) {
		hunt.has_fifty = 1;
	}
	for (size_t i = 0; i < records.size(); ++i) {
		TreasureRecordManager::Instance()->Add(cache, records[i], type);
	}
	return true;
}

bool TreasureManager::DoRandom(const list<int32_t> &pool, Award &award, uint32_t &reward_id, uint32_t &reward_item, uint32_t &xiyou) {
	const CfgTreasure::Hunts &cfg = ConfigManager::Instance()->treasure_hunt_cfg_.m_config;
	vector<uint32_t> rates;
	uint32_t rate_sum = 0;
	list<int32_t>::const_iterator itr = pool.begin();
	for (; itr != pool.end(); ++itr) {
		const CfgTreasure::Hunt &item = cfg.hunts(*itr);
		rate_sum += item.rate();
		rates.push_back(rate_sum);
	}

	itr = pool.begin();
	uint32_t rate = Math::GetRandomInt(rate_sum == 0 ? 1 : rate_sum);
	for (size_t i = 0; i < rates.size() && itr != pool.end(); ++i, ++itr) {
		if (rate < rates[i]) {
			const CfgTreasure::Hunt &item = cfg.hunts(*itr);
			award.Add(item.item(), item.num());
			reward_id = item.id();
			reward_item = item.item();
			xiyou = item.xiyou();
			return true;
		}
	}
	return false;
}

bool TreasureManager::SendHunt(const TreasureHunt &data) {
	msgs::SPlayerTreasure msg;
	FormatHuntMsg(msg, data);
	LogicManager::Instance()->SendMsg(data.uid, CMD_PLAYER_TREASURE_ONE_INFO, &msg);
	return true;
}

bool TreasureManager::CalcProperty(const UserCache &cache, PropertySets &props) {
	map<uint32_t, DataTreasure>::const_iterator it = cache.treasure_.begin();
	for(; it != cache.treasure_.end(); ++it) {
		uint32_t id = TreasureCfgWrap().GetIdByType(it->second.type, it->second.level, it->second.star);
		const CfgTreasure::Treasure& cfg =TreasureCfgWrap().GetById(id);
		PropertyCfg::setProps(cfg.attr(), 1.0, props);

		for(uint32_t index = 0; index < DAN_MAX_CNT; ++index) {
			if(0 == it->second.star && 1 == it->second.level) {
				continue;
			}
			uint32_t dan_id = TreasureCfgWrap().GetDanId(it->second.type, it->second.level, it->second.star, index);
			const CfgItem::Item& dan_cfg = ItemCfgWrap().GetItem(dan_id);
			PropertyCfg::setProps(dan_cfg.attr(), (double)(*it->second.GetDan(index)), props);
		}
	}

	PropertyCfg::showProps(cache.uid_, -1, props, "Treasure");
	return true;
}

