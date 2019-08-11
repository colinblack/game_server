/*
 * TrumpManager.cpp
 *
 *  Created on: 2019年7月25日
 *      Author: colin
 */

#include "TrumpManager.h"
#include "BattleInc.h"



const ActiveTrump TrumpManager::cost_[] = { { 310010007, 5000 }, { 310010008,
		10000 }, { 310010009, 20000 } };


TrumpManager::TrumpManager() {

}

uint32_t TrumpManager:: GetTrumpLevel(const DataEquip& data) {
	static Json::Reader reader;
	Json::Value value;
	reader.parse(data.ext, value);
	uint32_t star = 0;
	if (value.isMember("star"))
		star = value["star"].asUInt();

	uint32_t cjl = 0;
	if (value.isMember("cjl"))
		cjl = value["cjl"].asUInt();

	return ((cjl - 1) * 5 + star + 2);
}

uint32_t TrumpManager::GetTrumpStage(const DataEquip& data) {
	static Json::Reader reader;
	Json::Value value;
	reader.parse(data.ext, value);

	return value["cjl"].asUInt();
}



int TrumpManager::Process(uint32_t uid, logins::STrumpActiveReq* req) {
	uint32_t subtype = req->subtype;
	uint32_t id = req->id;

	try {
		UserCache& cache = CacheManager::Instance()->GetUser(uid);
		map<uint32_t, DataEquip>::iterator it = cache.equip_.begin();
		for(; it != cache.equip_.end(); ++it){
			if(it->second.id == static_cast<uint32_t>(req->id))
			{
				error_log("turmp acitve error, uid=%u,id=%u,id=%u,code=actived",
						uid, id);
				return R_ERROR;
			}
		}

		uint32_t cost = 0;
		if (id == cost_[0].id){
			cost = cost_[0].money;
		}
		else if (id == cost_[1].id){
			cost = cost_[1].money;
		}
		else if (id == cost_[2].id){
			cost = cost_[2].money;
		}

		ItemCfgWrap cfgWrap;
		const CfgItem::Equip &cfg = cfgWrap.GetEquip(id);
		if (cfg.part() != subtype) {
			error_log(
					"turmp acitve error, uid=%u,id=%u,subtype=%u,code=param error",
					uid, id, subtype);
			return R_ERROR;
		}

		UpdateManager::Instance()->SetCode(UC_TrumpActive);
		if (!UserManager::Instance()->UseMoney(uid, MONEY_GOLD, cost,
				"active trump")) {
			error_log("active trump cost error uid=%u", uid);
			return R_ERROR;
		}

		UserManager::Instance()->AddItem(uid, id, 1, "trump");
		cache.trump_.current_fight += 1;

		DataTrumpManager::Instance()->Set(cache.trump_);
		LogicManager::Instance()->AddSync(CMD_TRUMP_INFO);


	} catch (const exception& e) {
		error_log("trump active error, uid=%u,code=%s", uid, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int TrumpManager::Process(uint32_t uid, logins::STrumpUpgradeReq* req) {
	uint32_t count = req->count;
	try {
		UserCache& cache = CacheManager::Instance()->GetUser(uid);
		if (cache.trump_.unlock == 0) {
			error_log("trump upgrade failed, uid=%u, code=unlock", uid);
			return R_ERROR;
		}

		if (cache.trump_.current_fight <= 5) {
			error_log("trump upgrade failed, uid=%u, code=no_actived_trump",
					uid);
			return R_ERROR;
		}

		Json::Value value;
		static Json::Reader reader;
		static Json::FastWriter writer;
		map<uint32_t, uint32_t> trumps;
		map<uint32_t, DataEquip>::iterator it = cache.equip_.begin();
		for (; it != cache.equip_.end(); ++it) {
			if (IS_LAST_FOUR_TRUMP(it->second.id)) {
				uint32_t level = GetTrumpLevel(it->second);
				trumps.insert(make_pair(it->first, level));
			}
		}

		uint32_t minLevel = 0;
		TrumpCfgWrap trumpCfg;
		for (int i = 0; i < count; ++i) {
			minLevel = trumps.begin()->second;
			const CfgTrump::TrumpInfo& cfg = trumpCfg.GetTrumpsByLevel(
					minLevel + 1);
			if (!UserManager::Instance()->UseItem(uid, cfg.cost_item(),
					cfg.cost_count(), "trump upgrade")) {
				error_log("cost error uid=%u", uid);
				return R_ERROR;
			}

			map<uint32_t, uint32_t>::iterator it = trumps.begin();
			for (; it != trumps.end(); ++it) {
				const CfgTrump::TrumpInfo&cfg = trumpCfg.GetTrumpsByLevel(it->second + 1);
				reader.parse(cache.equip_[it->first].ext, value);
				value["star"] = cfg.star();
				value["cjl"] = cfg.stage();
				cache.equip_[it->first].ext = writer.write(value);
				DataEquipManager::Instance()->Set(cache.equip_[it->first]);
				UpdateManager::Instance()->SetCode(UC_UpgradeTrump);
			}
		}

	} catch (const exception& e) {
		error_log("trump upgrade error, uid=%u, code=%s", uid, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}


int TrumpManager::Process(uint32_t uid, logins::SActiveTrumpSkillReq* req) {
	uint32_t stage = req->level;
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	int index = 0;
	for (; index < cache.trump_.active_count; ++index) {
		if (stage == cache.trump_.active_map[index]) {
			error_log("skill actived, uid=%u", uid);
			return R_ERROR;
		}
	}

	set<uint32_t> trumps;
	map<uint32_t, DataEquip>::iterator it = cache.equip_.begin();
	for (; it != cache.equip_.end(); ++it) {
		if (IS_LAST_FOUR_TRUMP(it->second.id)) {
			uint32_t stage = GetTrumpStage(it->second);
			trumps.insert(stage);
		}
	}

	if (trumps.size() == 0) {
		error_log("trump not active, uid=%u", uid);
		return R_ERROR;
	}

	for (set<uint32_t>::iterator it = trumps.begin();
			it != trumps.end(); ++it) {
		if (*it < stage) {
			error_log("stage invalid, uid=%u", uid);
			return R_ERROR;
		}
	}

	cache.trump_.active_map[index] = stage;
	cache.trump_.active_count += 1;

	DataTrumpManager::Instance()->Set(cache.trump_);
	LogicManager::Instance()->AddSync(CMD_TRUMP_INFO);

	return R_SUCCESS;
}


int TrumpManager::Process(uint32_t uid, logins::STrumpRequestMissionReq* req){
	logins::SMissionReq  mession;
	mession.missionId_ = req->missionId;
	return MissionManager::Instance()->Process(uid, &mession);
}



int TrumpManager::Process(uint32_t uid, logins::SUnlockTrumpReq* req){
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(cache.trump_.unlock == 1)
	{
		error_log("trump unlocked: %u", uid);
		return R_ERROR;
	}

	cache.trump_.unlock = 1;
	DataTrumpManager::Instance()->Set(cache.trump_);
	LogicManager::Instance()->AddSync(CMD_TRUMP_INFO);

	return R_SUCCESS;
}


bool TrumpManager::CalcProperty(const UserCache &cache, byte rid,
		PropertySets &props) {

	try {
		set<uint32_t> trumps;
		map<uint32_t, DataEquip>::const_iterator it = cache.equip_.begin();
		for (; it != cache.equip_.end(); ++it) {
			if (IS_LAST_FOUR_TRUMP(it->second.id)) {
				uint32_t level = GetTrumpLevel(it->second);
				trumps.insert(level);
			}
		}

		double multiple = 1.0;
		if (trumps.size() == 4)
			multiple = 4.0;

		set<uint32_t>::iterator iter = trumps.begin();
		TrumpCfgWrap trumpCfg;
		for (; iter != trumps.end(); ++iter) {
			const CfgTrump::TrumpInfo& cfg = trumpCfg.GetTrumpsByLevel(*iter);
			PropertyCfg::setProps(cfg.attr(), multiple, props);
		}

		TrumpSkillCfgWrap trumpSkillCfg;
		for (int i = 0; i < cache.trump_.active_count; ++i) {
			const CfgTrump::TrumpSkillInfo& cfg =
					trumpSkillCfg.GetTrumpsByStage(cache.trump_.active_map[i]);
			PropertyCfg::setProps(cfg.attr(), 1.0, props);
		}
		PropertyCfg::showProps(cache.uid_, rid, props, "trump");

	} catch (const exception& e) {
		error_log("calcproperty error: uid=%u, code=%s", cache.uid_, e.what());
		return false;
	}

	return true;
}

int TrumpManager::Sync(const UserCache &cache, uint32_t cmd,
		msgs::STrumpInfo *resp) {
	resp->unlock_ = cache.trump_.unlock == 0 ? false : true;
	resp->curFight_ = cache.trump_.current_fight;

	for (int i = 0; i < cache.trump_.active_count; ++i) {
		resp->activeMap_.insert(make_pair(cache.trump_.active_map[i], true));
	}

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return true;
}


