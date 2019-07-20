/*
 * ShenQiManager.cpp
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#include "ShenQiManager.h"
#include "BattleInc.h"

ShenQiManager::ShenQiManager() {
}

ShenQiManager::~ShenQiManager() {
}

bool ShenQiManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	try {
		ItemCfgWrap cfg_wrap;
		const map<uint32_t, set<uint32_t> > &indexs = ConfigManager::Instance()->shenqi_cfg_Index;
		map<uint32_t, set<uint32_t> >::const_iterator itr;
		set<uint32_t>::iterator pieceItr;
		//已经激活的属性
		for (byte id = 1; id <= cache.shenqi_.id; ++id) {
			itr = indexs.find(id);
			if (itr == indexs.end()) {
				continue;
			}
			pieceItr = itr->second.begin();
			for (; pieceItr != itr->second.end(); ++pieceItr) {
				const CfgItem::Item &cfg = cfg_wrap.GetItem(*pieceItr);
				PropertyCfg::setProps(cfg.attr(), 1.0, props);
			}
		}

		//未激活的碎片属性
		byte next = cache.shenqi_.id + 1;
		itr = indexs.find(next);
		if (itr != indexs.end()) {
			for (size_t i = 0; i < itr->second.size(); ++i) {
				const uint32_t *ptr = cache.shenqi_.GetPiece(i);
				if (ptr == NULL || *ptr == 0) {
					continue;
				}
				const CfgItem::Item &cfg = cfg_wrap.GetItem(*ptr);
				PropertyCfg::setProps(cfg.attr(), 1.0, props);
			}
		}
	} catch (...) {
		return false;
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "shenqi");
	return true;
}

int ShenQiManager::Process(uint32_t uid, logins::SShenQiPiece *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	byte curr = cache.shenqi_.id + 1;

	const map<uint32_t, set<uint32_t> > &indexs = ConfigManager::Instance()->shenqi_cfg_Index;
	map<uint32_t, set<uint32_t> >::const_iterator itr = indexs.find(curr);
	if (itr == indexs.end()) {
		error_log("id not exists uid=%u id=%u", uid, curr);
		return R_ERROR;
	}
	const set<uint32_t> &items = itr->second;
	set<uint32_t>::const_iterator itemItr = items.find(req->itemId_);
	if (itemItr == items.end()) {
		error_log("item not exists uid=%u item=%u id=%u", uid, req->itemId_, curr);
		return R_ERROR;
	}

	uint32_t *ptr = NULL;
	for (size_t i = 0; i < items.size(); ++i) {
		ptr = cache.shenqi_.GetPiece(i);
		if (ptr == NULL) {
			continue;
		}
		if (static_cast<int32_t>(*ptr) == req->itemId_) {
			error_log("item is active uid=%u item=%u id=%u", uid, req->itemId_, curr);
			return R_ERROR;
		} else if (*ptr == 0) {
			break;
		}
	}
	if (ptr == NULL || *ptr != 0) {
		error_log("why uid=%u item=%u id=%u", uid, req->itemId_, curr);
		return R_ERROR;
	}

	UpdateManager::Instance()->SetCode(UC_ActiveShenqiPiece);

	string code;
	String::Format(code, "shenqi_piece_%u", curr);
	if (!UserManager::Instance()->UseItem(uid, req->itemId_, 1, code)) {
		error_log("use item error uid=%u item=%u", uid, req->itemId_);
		return R_ERROR;
	}

	*ptr = req->itemId_;

	if (cache.shenqi_.uid == 0) {
		cache.shenqi_.uid = uid;
		DataShenQiManager::Instance()->Add(cache.shenqi_);
	} else {
		DataShenQiManager::Instance()->Set(cache.shenqi_);
	}
	MissionManager::Instance()->onActivateShenqi(uid, req->itemId_);
	LogicManager::Instance()->AddSync(CMD_SHENQI_INFO);
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}

int ShenQiManager::Process(uint32_t uid, logins::SShenQi *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	byte curr = cache.shenqi_.id + 1;

	const map<uint32_t, set<uint32_t> > &indexs = ConfigManager::Instance()->shenqi_cfg_Index;
	map<uint32_t, set<uint32_t> >::const_iterator itr = indexs.find(curr);
	if (itr == indexs.end()) {
		error_log("id not exists uid=%u id=%u", uid, curr);
		return R_ERROR;
	}
	const set<uint32_t> &items = itr->second;
	bool full = true;
	uint32_t *ptr = NULL;
	for (size_t i = 0; i < items.size(); ++i) {
		ptr = cache.shenqi_.GetPiece(i);
		if (ptr == NULL || *ptr == 0) {
			full = false;
			break;
		}
	}
	if (!full) {
		error_log("piece is not full uid=%u id=%u", uid, curr);
		return R_ERROR;
	}

	cache.shenqi_.id = curr;
	cache.shenqi_.ClearPiece();

	DataShenQiManager::Instance()->Set(cache.shenqi_);

	LogicManager::Instance()->AddSync(CMD_SHENQI_INFO);

	SkillManager::Instance()->UnlockShenQi(cache);

	PropertyManager::Instance()->AddUser(uid);

	return 0;
}

int ShenQiManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SShenqiInfo *resp) {
	byte curr = cache.shenqi_.id + 1;

	const map<uint32_t, set<uint32_t> > &indexs = ConfigManager::Instance()->shenqi_cfg_Index;
	map<uint32_t, set<uint32_t> >::const_iterator itr = indexs.find(curr);
	if (itr != indexs.end()) {
		const set<uint32_t> &items = itr->second;
		const uint32_t *ptr = NULL;
		for (size_t i = 0; i < items.size(); ++i) {
			ptr = cache.shenqi_.GetPiece(i);
			if (ptr == NULL || *ptr == 0) {
				continue;
			}
			resp->actived_pieces_.push_back(*ptr);
		}
	}
	resp->cur_shenqi_ = cache.shenqi_.id;
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
