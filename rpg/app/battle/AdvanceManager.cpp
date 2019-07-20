/*
 * AdvanceManager.cpp
 *
 *  Created on: 2019年6月22日
 *      Author: Administrator
 *  进阶模块
 */

#include "AdvanceManager.h"
#include "BattleInc.h"

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

	OnLevelUp(*itr);

	LogicManager::Instance()->AddSync(CMD_PLAYER_ADVANCE_INFO);

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

bool AdvanceManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	AdvanceCfgWrap cfg_wrap;
	list<DataAdvance>::const_iterator itr = cache.advance_.begin();
	for (; itr != cache.advance_.end(); ++itr) {
		if (itr->rid != rid) {
			continue;
		}
		const CfgAdvance::Advance &cfg = cfg_wrap.Get(itr->type, itr->level, itr->star);
		PropertyCfg::setProps(cfg.attr(), 1.0, props);

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
