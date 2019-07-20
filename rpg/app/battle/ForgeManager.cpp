/*
 * ForgeManager.cpp
 *
 *  Created on: 2019年7月3日
 *      Author: Administrator
 */

#include "ForgeManager.h"
#include "BattleInc.h"

ForgeManager::ForgeManager() {
}

ForgeManager::~ForgeManager() {
}

bool ForgeManager::FormatMsg(const DataForge &data, dbs::TPlayerEquip &msg) {
	msg.clear();
	msg.playerId_ = data.uid;
	msg.roleId_ = data.rid;
	msg.subtype_ = data.type;
	msg.strength_ = data.strength;
	msg.purify_ = data.purify;
	msg.extend_ = "{}";
	msg.extendEx_ = "{}";
	return true;
}

bool ForgeManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	ForgeCfgWrap cfg_wrap;
	list<DataForge>::const_iterator itr = cache.forge_.begin();
	for (; itr != cache.forge_.end(); ++itr) {
		if (itr->rid != rid) {
			continue;
		}
		if (!EquipsManager::Instance()->IsWear(cache, rid, itr->type)) {
			continue;
		}
		if (itr->strength == 0) {
			continue;
		}
		const CfgForge::Strengthen &cfg = cfg_wrap.GetStrengthen(itr->strength);
		if (itr->type == 3 || itr->type == 4 || itr->type == 6 || itr->type == 7) {
			PropertyCfg::setProps(cfg.attr(), 1.0, props);
		} else {
			//攻击部位用生命上限转成攻击数
			for (int i = 0; i < cfg.attr_size(); ++i) {
				if (cfg.attr(i).type() == AP_MAXLIFE) {
					int key = 1001;
					props[key].pui += floor(static_cast<float>(cfg.attr(i).num()) / 13.5f);
					break;
				}
			}
		}
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "strength");
	return true;
}

int ForgeManager::Process(uint32_t uid, logins::SStrengthenReq *req, logins::SStrengthenResp *resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}

	dbs::TPlayerEquip msg;
	ForgeCfgWrap cfg_wrap;
	string code;
	uint16_t strength = 0;
	bool is_new = false;
	bool cost_error = false;
	bool is_chg = false;

	DataForge item;
	item.uid = uid;
	item.rid = req->roleId_;
	UpdateManager::Instance()->SetCode(UC_EquipStrengthen);
	list<DataForge>::iterator fItr;
	vector<int32_t>::iterator itr = req->equipType_.begin();
	for (; itr != req->equipType_.end(); ++itr) {
		cost_error = false;
		item.type = *itr;
		fItr = find(cache.forge_.begin(), cache.forge_.end(), item);
		if (fItr == cache.forge_.end()) {
			strength = 0;
			is_new = true;
		} else {
			strength = fItr->strength;
			is_new = false;
		}

		code.clear();
		String::Format(code, "equip_strength_%u_%u", *itr, strength + 1);
		const CfgForge::Strengthen &cfg = cfg_wrap.GetStrengthen(strength + 1);
		for (int i = 0; i < cfg.cost_size(); ++i) {
			if (!UserManager::Instance()->UseItem(uid, cfg.cost(i).item(), cfg.cost(i).num(), code)) {
				cost_error = true;
				break;
			}
		}

		if (cost_error) {
			continue;
		}

		if (is_new) {
			DataForge data;
			data.uid = uid;
			data.rid = req->roleId_;
			data.type = *itr;
			data.strength = 1;
			DataForgeManager::Instance()->Add(data);
			cache.forge_.push_back(data);
			FormatMsg(data, msg);
			resp->equip_.push_back(msg);
			is_chg = true;
		} else {
			fItr->strength += 1;
			DataForgeManager::Instance()->Set(*fItr);
			FormatMsg(*fItr, msg);
			resp->equip_.push_back(msg);
			is_chg = true;
		}
	}

	if (is_chg) {
		PropertyManager::Instance()->AddUser(uid);
	}
	//日常活动同步
	ActivityManager::Instance()->SyncActivity(cache, FORGE_ACTIVITY_TYPE);
	LogicManager::Instance()->AddSync(CMD_DAILY_ACTIVITY_INFO);
	return 0;
}

int ForgeManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerEquipList *resp) {
	list<DataForge>::const_iterator itr = cache.forge_.begin();
	dbs::TPlayerEquip msg;
	for (;itr != cache.forge_.end(); ++itr) {
		FormatMsg(*itr, msg);
		resp->equips_.push_back(msg);
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
