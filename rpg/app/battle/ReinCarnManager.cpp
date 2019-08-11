/*
 * ReinCarnManager.cpp
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#include "ReinCarnManager.h"
#include "BattleInc.h"

ReinCarnManager::ReinCarnManager() {
}

ReinCarnManager::~ReinCarnManager() {
}

void ReinCarnManager::save(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return;
	}
	DataAttr attr;
	if (cache.m_reinCarnInfo.uid == 0) {
		cache.m_reinCarnInfo.uid = uid;
		cache.m_reinCarnInfo.type = TYPE_ATTR_REINCARN;
		cache.m_reinCarnInfo.gotLevel = 88;
		memcpy((void*) &attr, (const void*) &cache.m_reinCarnInfo, sizeof(DataAttr));
		DataAttrManager::Instance()->Add(attr);
	} else {
		memcpy((void*) &attr, (const void*) &cache.m_reinCarnInfo, sizeof(DataAttr));
		DataAttrManager::Instance()->Set(attr);
	}
}

bool ReinCarnManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	try {
		//境界属性
		RingWrap cfg_wrap;
		const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->ring_cfg_Index;
		map<uint32_t, uint32_t>::const_iterator itr = indexs.find(cache.m_reinCarnInfo.level);
		if (itr != indexs.end()) {
			const CfgRing::Ring &cfg = cfg_wrap.GetRing(cache.m_reinCarnInfo.level);
			PropertyCfg::setProps(cfg.attr(), 1.0, props);
		}
		//转生属性
		ReinCarnWrap cfg_wrap2;
		const map<uint32_t, uint32_t> &indexs2 = ConfigManager::Instance()->reincarn_cfg_Index;
		map<uint32_t, uint32_t>::const_iterator its = indexs2.find(cache.m_reinCarnInfo.reinCarnLevel);
		if (its != indexs.end()) {
			const CfgReinCarn::ReinCarn &cfg2 = cfg_wrap2.GetReinCarn(cache.m_reinCarnInfo.reinCarnLevel);
			PropertyCfg::setProps(cfg2.attr(), 1.0, props);
		}
	} catch (...) {
		return false;
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "reincarn");
	return true;
}

bool ReinCarnManager::onAddExp(uint32_t uid, uint32_t num) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	cache.m_reinCarnInfo.value += num;
	save(uid);
	LogicManager::Instance()->AddSync(CMD_ACHIEVEMENT);
	PropertyManager::Instance()->AddUser(uid);
	return true;
}

int ReinCarnManager::Process(uint32_t uid, reincarn::CSRingActive *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	RingWrap cfg_wrap;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->ring_cfg_Index;

	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(req->ringId);
	if (itr == indexs.end()) {
		error_log("id not exists id=%u", req->ringId);
		return R_ERROR;
	}
	const CfgRing::Ring &cfg = cfg_wrap.GetRing(req->ringId);
	if (cache.m_reinCarnInfo.value < cfg.exp()) {
		return R_ERROR;
	}
	cache.m_reinCarnInfo.level++;
	save(uid);
	LogicManager::Instance()->AddSync(CMD_ACHIEVEMENT);
	LogicManager::Instance()->AddSync(CMD_ACHIEVEMENT_CHAPTER);
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}

int ReinCarnManager::Process(uint32_t uid, reincarn::CSReinCarn *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	if (cache.m_reinCarnInfo.level < cache.m_reinCarnInfo.reinCarnLevel + 1) {
		return R_ERROR;
	}

	ReinCarnWrap cfg_wrap;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->reincarn_cfg_Index;

	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(cache.m_reinCarnInfo.reinCarnLevel + 1);
	if (itr == indexs.end()) {
		error_log("id not exists id=%u", cache.m_reinCarnInfo.reinCarnLevel + 1);
		return R_ERROR;
	}

	UpdateManager::Instance()->SetCode(UC_Reincarn);

	const CfgReinCarn::ReinCarn &cfg = cfg_wrap.GetReinCarn(cache.m_reinCarnInfo.reinCarnLevel + 1);
	string code = "rein_carn";
	if (!UserManager::Instance()->UseMoney(uid, MONEY_REINCARN_EXP, cfg.value(), code)) {
		return R_ERROR;
	}

	cache.m_reinCarnInfo.reinCarnLevel++;
	save(uid);

	LogicManager::Instance()->AddSync(CMD_PLAYER_CAREER_LEVEL);
	PropertyManager::Instance()->AddUser(uid);
	MissionManager::Instance()->onMission(uid, MT_REINCARNATION, cache.m_reinCarnInfo.reinCarnLevel);
	return 0;
}

int ReinCarnManager::Process(uint32_t uid, reincarn::CSReinCarnGetExpByItems *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	uint32_t addValue = 0;
	if (req->itemId == NORAML_DAN_ITEMID) {
		addValue = 30000;
	} else if (req->itemId == SUPER_DAN_ITEMID) {
		addValue = 300000;
	} else {
		error_log("error itemid  uid=%u id=%u", uid, req->itemId);
		return R_ERROR;
	}
	UpdateManager::Instance()->SetCode(UC_ReincarnExpDelItem);
	if (!UserManager::Instance()->UseItem(uid, req->itemId, 1, "reincarn_dan")) {
		error_log("use item error uid=%u item=%u", uid, req->itemId);
		return R_ERROR;
	}
	save(uid);
	string code = "rein_carn_exp_item";
	UserManager::Instance()->AddMoney(uid, MONEY_REINCARN_EXP, addValue, code);
	LogicManager::Instance()->AddSync(CMD_REINCARN_INFO);
	return 0;
}

int ReinCarnManager::Process(uint32_t uid, reincarn::CSReinCarnGetExpByLevel *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	//count检测
	if (cache.m_reinCarnInfo.gotCount >= 12) {
		return R_ERROR;
	}

	if (cache.base_.level < cache.m_reinCarnInfo.gotLevel) {
		return R_ERROR;
	}

	uint32_t addValue = 0;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->level_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(cache.m_reinCarnInfo.gotLevel);
	if (itr == indexs.end()) {
		error_log("id not exists uid=%u level=%u", uid, cache.m_reinCarnInfo.gotLevel);
		return R_ERROR;
	}
	LevelCfgWrap cfg_wrap;
	const CfgLevel::Level& cfg = cfg_wrap.Get(cache.m_reinCarnInfo.gotLevel);
	addValue = cfg.reincarnexp();
	cache.m_reinCarnInfo.gotLevel++;
	cache.m_reinCarnInfo.gotCount++;
	save(uid);
	string code = "rein_carn_exp_level";
	UpdateManager::Instance()->SetCode(UC_ReincarnExpDelLevel);
	UserManager::Instance()->AddMoney(uid, MONEY_REINCARN_EXP, addValue, code);
	LogicManager::Instance()->AddSync(CMD_REINCARN_INFO);
	return 0;
}

int ReinCarnManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SInt *resp) {
	if (cmd == CMD_PLAYER_CAREER_LEVEL) {
		resp->value_ = cache.m_reinCarnInfo.reinCarnLevel;
		LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	} else if (cmd == CMD_ACHIEVEMENT) {
		resp->value_ = cache.m_reinCarnInfo.value;
		LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	} else if (cmd == CMD_ACHIEVEMENT_CHAPTER) {
		resp->value_ = cache.m_reinCarnInfo.level;
		LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	}
	return 0;
}

int ReinCarnManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SReincarnInfo *resp) {
	resp->levelDelCount_ = 0;
	resp->hadGotLevel_ = cache.m_reinCarnInfo.gotLevel;
	resp->hadGotLevelCount_ = cache.m_reinCarnInfo.gotCount;
	if (cache.m_reinCarnInfo.normalItemCount) {
		resp->itemDelCount_.insert(make_pair(NORAML_DAN_ITEMID, cache.m_reinCarnInfo.normalItemCount));
	}
	if (cache.m_reinCarnInfo.superItemCount) {
		resp->itemDelCount_.insert(make_pair(SUPER_DAN_ITEMID, cache.m_reinCarnInfo.superItemCount));
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
