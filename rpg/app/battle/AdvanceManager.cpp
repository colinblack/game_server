/*
 * AdvanceManager.cpp
 *
 *  Created on: 2019年6月22日
 *      Author: Administrator
 *
 */

#include "AdvanceManager.h"
#include "BattleInc.h"

#define HORSE_EQUIP_TYPE  30
#define WING_EQUIP_TYPE   31

AdvanceManager::AdvanceManager() {
}

AdvanceManager::~AdvanceManager() {
}

int AdvanceManager::Process(uint32_t uid, logins::SActiveAdvance *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	list<DataAdvance>::const_iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (static_cast<int32_t>(itr->rid) == req->roleId_
		&& static_cast<int32_t>(itr->type) == req->type_) {
			return R_ERROR;
		}
	}

	DataAdvance data;
	data.uid = uid;
	data.rid = req->roleId_;
	data.type = req->type_;
	data.level = 1;
	DataAdvanceManager::Instance()->Add(data);
	cache.advance_.push_back(data);

	OnLevelUp(data);

	//LogicManager::Instance()->AddSync(CMD_PLAYER_ADVANCE_INFO);
	UpdateManager::Instance()->SetCode(UC_Advance);
	UpdateManager::Instance()->Advance(uid, data);

	PropertyManager::Instance()->AddUser(uid);

	debug_log("uid=%u,rid=%d,tp=%d", uid, req->roleId_, req->type_);

	return 0;
}

int AdvanceManager::Process(uint32_t uid, logins::SAdvanceReq *req, logins::SAdvanceResp *resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	list<DataAdvance>::iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid == req->roleId_ && itr->type == req->type_) {
			break;
		}
	}
	if (itr == cache.advance_.end()) {
		error_log("advance not exist uid=%u rid=%u type=%u", uid, req->roleId_, req->type_);
		return R_ERROR;
	}

	UpdateManager::Instance()->SetCode(UC_Advance);

	const CfgAdvance::Advance &cfg = AdvanceCfgWrap().Get(itr->type, itr->level, itr->star);
	if (cfg.cost_item() != 0 && cfg.cost_num()) {
		string code;
		String::Format(code, "advance_%u_%u_%u", itr->type, itr->level, itr->star);
		if (!UserManager::Instance()->UseItem(uid, cfg.cost_item(), cfg.cost_num(), code)) {
			error_log("cost error uid=%u rid=%u type=%u", uid, req->roleId_, req->type_);
			return R_ERROR;
		}
	}

	if (itr->star == 10) {
		itr->star = 0;
		itr->level += 1;
		itr->bless = 0;
		OnLevelUp(*itr);
	} else {
		uint32_t bless = itr->bless + cfg.bless();
		if (bless > cfg.max_bless()) {
			itr->star += 1;
			itr->bless = bless - cfg.max_bless();
		} else {
			itr->bless = bless;
		}
	}

	DataAdvanceManager::Instance()->Set(*itr);

	UpdateManager::Instance()->Advance(uid, *itr);
	MissionManager::Instance()->onUpgrade(uid, itr->type, itr->level);
	PropertyManager::Instance()->AddUser(uid);

	MissionManager::Instance()->onSubMission(uid, MT_UPGRADE, req->type_, 1);
	debug_log("uid=%u,rid=%d,tp=%d,item=%u,b=%d", uid, req->roleId_, req->type_, req->itemId_, req->autoBuy_);

	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SAdvanceEatDan *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	list<DataAdvance>::iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid == req->roleId_ && itr->type == req->type_) {
			break;
		}
	}
	if (itr == cache.advance_.end()) {
		error_log("advance not exist uid=%u rid=%u type=%u", uid, req->roleId_, req->type_);
		return R_ERROR;
	}
	AdvanceCfgWrap cfg_wrap;
	const CfgAdvance::Dan &cfg = cfg_wrap.GetDan(itr->type, itr->level, req->itemId_);
	uint16_t *ptrDan = itr->GetDan(cfg.id());
	if (ptrDan == NULL) {
		error_log("advance dan not exist uid=%u rid=%u type=%u id=%u", uid, req->roleId_, req->type_, cfg.id());
		return R_ERROR;
	}
	if (*ptrDan >= cfg.total()) {
		error_log("advance dan limit uid=%u rid=%u type=%u id=%u", uid, req->roleId_, req->type_, cfg.id());
		return R_ERROR;
	}

	UpdateManager::Instance()->SetCode(UC_EatDan);

	string code;
	String::Format(code, "advance_%u_%u_%u", itr->type, itr->level, itr->star);
	uint32_t use = UserManager::Instance()->TryUseItem(uid, cfg.item(), cfg.total() - *ptrDan, code);
	if (use == 0) {
		error_log("cost error uid=%u rid=%u type=%u", uid, req->roleId_, req->type_);
		return R_ERROR;
	}

	*ptrDan += use;

	DataAdvanceManager::Instance()->Set(*itr);

	UpdateManager::Instance()->AdvanceDan(uid, *itr, cfg.id());

	PropertyManager::Instance()->AddUser(uid);

	debug_log("uid=%u,rid=%d,tp=%d,item=%u", uid, req->roleId_, req->type_, req->itemId_);

	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SOneKeyDressReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	list<DataAdvance>::iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid == req->roleId && itr->type == req->type) {
			break;
		}
	}
	if (itr == cache.advance_.end()) {
		error_log("advance not exist uid=%u rid=%u type=%u", uid, req->roleId, req->type);
		return R_ERROR;
	}
	vector<int64_t>::iterator it = req->uids.begin();
	for(; it != req->uids.end(); ++it) {
		if(!cache.equip_.count(*it)) {
			error_log("equip uid:%u not exist", *it);
			return R_ERROR;
		}
	}

	it = req->uids.begin();
	for(; it != req->uids.end(); ++it) {
		dress(cache, req->roleId, *it);
	}
	PropertyManager::Instance()->AddUser(uid);
	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SDressReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	if(!cache.role_.count(req->roleId)) {
		error_log("roleId not active:%u", req->roleId);
		return R_ERROR;
	}
	if(!cache.equip_.count(req->uid)) {
		error_log("equip uid:%u not exist", req->uid);
		return R_ERROR;
	}

	dress(cache, req->roleId, req->uid);

	PropertyManager::Instance()->AddUser(uid);

	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SStrengthEquipReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	if(0 == cache.equip_.count(req->uid)) {
		error_log("equip uid:%d not exist", req->uid);
		return R_ERROR;
	}

	uint16_t bag_type = req->roleId + BAG_ROLE * 2;
	if(bag_type != cache.equip_[req->uid].bag) {
		error_log("equip:%u not be equip by advance", req->uid);
		return R_ERROR;
	}
	DataEquip& data = cache.equip_[req->uid];
	UpdateManager::Instance()->SetCode(UC_StrengthAdvanceEquip);

	uint32_t level = getStrengthExt(data) + 1;

	const CfgItem::Equip& cfg = ItemCfgWrap().GetEquip(data.id);
	const CfgAdvance::EquipStrength& strength_cfg = AdvanceCfgWrap().getStrength(cfg.type(), cfg.part(), level);
	if (strength_cfg.consumid() != 0 && strength_cfg.consumcnt() != 0) {
		string code;
		String::Format(code, "advance strength:%u_%u_%u", cfg.type(), cfg.part(), level + 1);
		if (!UserManager::Instance()->UseItem(uid, strength_cfg.consumid(), strength_cfg.consumcnt(), code)) {
			error_log("cost error uid=%u rid=%u type=%u", uid, req->roleId, req->type);
			return R_ERROR;
		}
		UpdateManager::Instance()->UpdateBagNow(uid);
	}
	setStrengthExt(data, level);
	DataEquipManager::Instance()->Set(data);
	UpdateManager::Instance()->Bag(uid, 0, data);
	PropertyManager::Instance()->AddUser(uid);
	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SRecycleReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}

	Award SmeltRward;
	map<int64_t, int32_t>::iterator iter = req->items.begin();
	for(; iter != req->items.end(); ++iter) {
		UpdateManager::Instance()->SetCode(UC_Recycle);
		if(0 == cache.equip_.count(iter->first)) {
			continue;
		}
		DataEquip& data = cache.equip_[iter->first];
		if(!UserManager::Instance()->UseItem(uid, data.id, iter->second, "advance smelt")) {
			return R_ERROR;
		}
		if(ItemCfgWrap().IsEquip(data.id)) {
			const CfgItem::Equip &cfg = ItemCfgWrap().GetEquip(data.id);
			SmeltRward.Format(cfg.smeltaward(), iter->second);
		} else if(ItemCfgWrap().IsItem(data.id)) {
			const CfgItem::Item &cfg = ItemCfgWrap().GetItem(data.id);
			SmeltRward.Format(cfg.smeltaward(), iter->second);
		}

	}
	UpdateManager::Instance()->UpdateBagNow(uid);

	UserManager::Instance()->Reward(uid, SmeltRward, "recycle Rward");
	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SLearnSkillReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	list<DataAdvance>::iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid == req->roleId && itr->type == req->type) {
			break;
		}
	}
	if (itr == cache.advance_.end()) {
		error_log("advance not exist uid=%u rid=%u type=%u", uid, req->roleId, req->type);
		return R_ERROR;
	}
	const CfgAdvance::Advance &cfg = AdvanceCfgWrap().Get(itr->type, itr->level, itr->star);
	int index = 0;
	for(; index < cfg.skill_size(); ++index) {
		if(req->skillId == cfg.skill(index)) {
			break;
		}
	}
	if(index >= cfg.skill_size()) {
		error_log("skill:%u already lock", req->skillId);
		return R_ERROR;
	}
	SkillManager::Instance()->UnlockAdvance(cache, req->roleId, req->skillId);
	PropertyManager::Instance()->AddUser(uid);
	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SAdvanceAwakenReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	list<DataAdvance>::iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid == req->roleId && itr->type == req->type) {
			break;
		}
	}
	if (itr == cache.advance_.end()) {
		error_log("advance not exist uid=%u rid=%u type=%u", uid, req->roleId, req->type);
		return R_ERROR;
	}

	UpdateManager::Instance()->SetCode(UC_AdvanceAwakenMount);
	DataAdvance& data = *(itr);
	if(data.awaken_star >= AdvanceCfgWrap().GetMaxAwakenStar() && data.awaken_level >= AdvanceCfgWrap().GetMaxAwakenLevel()) {
		error_log("awaken already max level:%u star:%u", data.awaken_level, data.awaken_star);
		return R_ERROR;
	}
	if(data.awaken_star < AdvanceCfgWrap().GetMaxAwakenStar()) {
		data.awaken_star++;
	} else {
		data.awaken_star = 0;
		data.awaken_level++;
	}
	const CfgAdvance::Awaken &cfg = AdvanceCfgWrap().getAwaken(data.awaken_level, data.awaken_star, req->type);
	if (cfg.consume().id() != 0 && cfg.consume().num() != 0) {
		string code;
		String::Format(code, "advance_%u_%u_%u", itr->type, itr->level, itr->star);
		if (!UserManager::Instance()->UseItem(uid, cfg.consume().id(), cfg.consume().num(), code)) {
			error_log("cost error uid=%u rid=%u type=%u", uid, req->roleId, req->type);
			return R_ERROR;
		}
	}
	DataAdvanceManager::Instance()->Set(data);
	UpdateManager::Instance()->advanceAwaken(uid, data);
	PropertyManager::Instance()->AddUser(uid);

	debug_log("uid=%u,rid=%d,tp=%d,b=%d", uid, req->roleId, req->type, req->autoBuy);
	return R_SUCCESS;
}

int AdvanceManager::Process(uint32_t uid, logins::SActiveAdvanceTargetReq *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERROR;
	}
	if(!AdvanceCfgWrap().isExistAdvanceType(req->type)) {
		error_log("advance type %u error", req->type);
		return R_ERROR;
	}
	if(0 == cache.advance_target_.count(req->type)) {
		addDataTarget(cache, req->type);
	}

	DataAdvanceTarget& data = cache.advance_target_[req->type];
	const CfgAdvance::Target& cfg = AdvanceCfgWrap().getTarget(req->targetLevel, req->type);
	list<DataAdvance>::iterator it = cache.advance_.begin();
	for(; it != cache.advance_.end(); ++it) {
		if(it->level < cfg.advance()) {
			break;
		}
	}
	if(it == cache.advance_.end()) {
		error_log("davance level:%u not above limit:%u", it->level, req->targetLevel);
		return R_ERROR;
	}
	data.advance = req->targetLevel;
	ATTR_DB_SET(data);
	PropertyManager::Instance()->AddUser(uid);
	UpdateManager::Instance()->advanceTarget(uid, data);

	return true;
}

int AdvanceManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerAdvanceInfo *resp) {
	AdvanceCfgWrap cfg_warp;
	msgs::SAdvance item;
	list<DataAdvance>::const_iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		const CfgAdvance::Advance &cfg = cfg_warp.Get(itr->type, itr->level, itr->star);
		item.clear();
		item.roleId_ = itr->rid;
		item.type_ = itr->type;
		item.star_ = itr->star;
		item.level_ = itr->level;
		item.lastDayLevel_ = itr->last_level;
		item.bless_ = itr->bless;
		item.tmpBless_ = itr->tmp_bless;
		item.modelId_ = cfg.mode();
		uint32_t dan_num = cfg_warp.GetDanCount(itr->type, itr->level);
		for (uint32_t dan = 0; dan < dan_num; ++dan) {
			const uint16_t *ptr = itr->GetDan(dan);
			if (ptr != NULL) {
				item.dan_[dan] = *ptr;
			}
		}
		resp->advances_.push_back(item);
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}

int AdvanceManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerAdvanceAwakenInfo *resp) {
	msgs::SAdvanceAwaken item;
	list<DataAdvance>::const_iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {

		item.clear();
		item.roleId_ = itr->rid;
		item.type_ = itr->type;
		item.star_ = itr->awaken_star;
		item.level_ = itr->awaken_level;
		resp->awakens_.push_back(item);
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}

int AdvanceManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SIntIntMap *resp) {
	map<uint32_t, DataAdvanceTarget>::const_iterator it = cache.advance_target_.begin();
	for(; it != cache.advance_target_.end(); ++it) {
		resp->maps_.insert(make_pair(it->second.advance_type, it->second.advance));
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}

bool AdvanceManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	AdvanceCfgWrap cfg_wrap;
	list<DataAdvance>::const_iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid != rid) {
			continue;
		}
		const CfgAdvance::Advance &cfg = cfg_wrap.Get(itr->type, itr->level, itr->star);
		PropertyCfg::setProps(cfg.attr(), 1.0, props);
		const CfgAdvance::Awaken &awaken_cfg = cfg_wrap.getAwaken(itr->awaken_level, itr->awaken_star, itr->type);
		PropertyCfg::setProps(awaken_cfg.attr(), 1.0, props);
		uint32_t dan_count = cfg_wrap.GetDanCount(itr->type, itr->level);
		for (uint32_t did = 0; did < dan_count; ++did) {
			const uint16_t *ptr = itr->GetDan(did);
			if (ptr == NULL || *ptr == 0) {
				continue;
			}
			const CfgAdvance::Dan &dan = cfg_wrap.GetDanById(itr->type, itr->level, did);
			PropertyCfg::setProps(dan.attr(), (double)*ptr, props);
		}
	}

	map<uint32_t, DataEquip>::const_iterator it = cache.equip_.begin();
	for(; it != cache.equip_.end(); ++it) {
		if(IS_BAG_ADVANCE(it->second.bag)) {
			const CfgItem::Equip& cfg = ItemCfgWrap().GetEquip(it->second.id);
			PropertyCfg::setProps(cfg.attr(), 1.0, props);
			uint32_t level = getStrengthExt(*(const_cast<DataEquip*>(&it->second)));
			if(level > 0) {
				const CfgAdvance::EquipStrength& strength_cfg = AdvanceCfgWrap().getStrength(cfg.type(), cfg.part(), level);
				PropertyCfg::setProps(strength_cfg.attr(), 1.0, props);
			}
		}
	}

	map<uint32_t, DataAdvanceTarget>::const_iterator item = cache.advance_target_.begin();
	for(; item != cache.advance_target_.end(); ++item) {
		const CfgAdvance::Target& cfg = AdvanceCfgWrap().getTarget(item->second.advance, item->second.advance_type);
		PropertyCfg::setProps(cfg.attr(), 1.0, props);
	}

	PropertyCfg::showProps(cache.uid_, rid, props, "advance");
	return true;
}

bool AdvanceManager::GetEntityShows(const UserCache &cache, byte rid, map<int16_t, int32_t> &show) {
	AdvanceCfgWrap cfg_wrap;
	list<DataAdvance>::const_iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid != rid) {
			continue;
		}
		const CfgAdvance::Advance &cfg = cfg_wrap.Get(itr->type, itr->level, itr->star);
		uint16_t id = GetShowId(itr->type);
		if (id != 0) {
			show[id] = cfg.mode();
		}
	}
	return true;
}

uint16_t AdvanceManager::GetShowId(byte type) {
	static uint16_t show_ids[] = {1005,1004,1007,1006,1002};
	if (type >= sizeof(show_ids) / sizeof(uint16_t)) {
		return 0;
	}
	return show_ids[type];
}

void AdvanceManager::OnLevelUp(const DataAdvance &data) {
	Human *pHuman = MapManager::Instance()->getHuman(data.uid);
	if (pHuman == NULL) {
		return;
	}
	const CfgAdvance::Advance &cfg = AdvanceCfgWrap().Get(data.type, data.level, data.star);
	uint16_t id = GetShowId(data.type);
	if (id == 0) {
		return;
	}

	pHuman->setShow(id, cfg.mode());
}

bool AdvanceManager::setStrengthExt(DataEquip& data, uint32_t level) {
	static Json::Reader reader;
	static Json::FastWriter writer;
	Json::Value value;
	value = Json::Value(Json::objectValue);
	value["s"] = level;
	data.ext = writer.write(value);
	return true;
}

uint32_t AdvanceManager::getStrengthExt(DataEquip& data) {
	uint32_t level = 0;
	Json::Value value = Json::Value(Json::objectValue);
	Json::Reader reader;
	if (!data.ext.empty() && !reader.parse(data.ext, value)) {
		error_log("parse equip extend error uid=%u ud=%u ext=%s", data.uid, data.ud, data.ext.c_str());
		return false;
	}
	if(value.isMember("s")) {
		level = value["s"].asUInt();
	}
	return level;
}

bool AdvanceManager::dress(UserCache& cache, uint32_t rid, uint32_t ud) {
	DataEquip& wear = cache.equip_[ud];
	const CfgItem::Equip& cfg = ItemCfgWrap().GetEquip(wear.id);
	uint16_t bag_type = rid + (HORSE_EQUIP_TYPE == cfg.type() ? BAG_ADVANCE_HORSE : BAG_ADVANCE_WING);
	map<uint32_t, DataEquip>::iterator it = cache.equip_.begin();
	for(; it != cache.equip_.end(); ++it) {
		if(bag_type == it->second.bag) {
			const CfgItem::Equip& equip_cfg = ItemCfgWrap().GetEquip(it->second.id);
			if(cfg.part() == equip_cfg.part()) {
				break;
			}
		}
	}

	//先脱掉已穿戴的装备
	if (it != cache.equip_.end()) {
		DataEquip& unwear = it->second;
		//更新装备状态
		UpdateManager::Instance()->SetCode(UC_DressAdvanceEquip);
		UpdateManager::Instance()->Bag(cache.uid_, 0, unwear);
		UpdateManager::Instance()->UpdateBagNow(cache.uid_);
		unwear.bag = BAG_ALL;
		DataEquipManager::Instance()->Set(unwear);
		//更新装备状态
		UpdateManager::Instance()->SetCode(UC_MoveItem);
		UpdateManager::Instance()->ChgBag(cache.uid_, bag_type, BAG_ALL, unwear);
		UpdateManager::Instance()->UpdateBagNow(cache.uid_);
	}
	//穿戴装备
	wear.bag = bag_type;
	DataEquipManager::Instance()->Set(wear);
	//更新装备状态
	UpdateManager::Instance()->SetCode(UC_MoveItem);
	UpdateManager::Instance()->ChgBag(cache.uid_, BAG_ALL, bag_type, wear);
	UpdateManager::Instance()->UpdateBagNow(cache.uid_);
	//更新装备状态
	UpdateManager::Instance()->SetCode(UC_DressAdvanceEquip);
	UpdateManager::Instance()->Bag(cache.uid_, 0, wear);
	UpdateManager::Instance()->UpdateBagNow(cache.uid_);
	return true;
}

bool AdvanceManager::addDataTarget(UserCache& cache, uint32_t type) {
	DataAdvanceTarget data;
	data.init(cache.uid_, TYPE_ADVANCE_TARGET, type);
	cache.advance_target_.insert(make_pair(data.type, data));
	ATTR_DB_ADD(data);
	return true;
}
