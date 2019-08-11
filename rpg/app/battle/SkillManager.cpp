/*
 * SkillManager.cpp
 *
 *  Created on: 2019年6月11日
 *      Author: Administrator
 */

#include "SkillManager.h"
#include "BattleInc.h"

SkillManager::SkillManager() {
	m_oper = 0;
}

bool SkillManager::ActorLogin(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	SkillCfgWrap cfg_wrap;
	list<DataSkill>::iterator itr = cache.skill_.begin();
	for (; itr != cache.skill_.end(); ++itr) {
		try {
			const CfgSkill::Skill &cfg = cfg_wrap.GetFirst(itr->id);
			if (itr->lv <= 1) {
				itr->skill_id = cfg.id();
			} else {
				itr->skill_id = cfg.id() + itr->lv - 1;
			}
		} catch (...) {
			continue;
		}
	}
	return true;
}

bool SkillManager::AutoUnlock(UserCache &cache, bool sync) {
	const CfgSkill::Skills &cfgs = ConfigManager::Instance()->skill_cfg_.m_config;
	list<DataSkill>::iterator skill_itr;
	m_chgs.clear();
	m_oper = SKILL_ADD;
	for (byte rid = 1; rid <= cache.base_.role_num; ++rid) {
		map<byte, DataRole>::iterator itr = cache.role_.find(rid);
		if (itr == cache.role_.end()) {
			continue;
		}
		const DataRole &role = itr->second;
		for (int i = 0; i < cfgs.skills_size(); ++i) {
			const CfgSkill::Skill &cfg = cfgs.skills(i);
			if (cfg.career() != role.career
			|| cfg.level() != 1
			|| cfg.unlock() > static_cast<uint32_t>(cache.base_.level)) {
				continue;
			}
			DataSkill item;
			item.uid = cache.uid_;
			item.rid = rid;
			item.id = cfg.serial();
			item.lv = 1;
			item.skill_id = cfg.id();
			skill_itr = find(cache.skill_.begin(), cache.skill_.end(), item);
			if (skill_itr != cache.skill_.end()) {
				continue;
			}
			DataSkillManager::Instance()->Add(item);
			cache.skill_.push_back(item);
			m_chgs.push_back(item);
			Human *pHuman = MapManager::Instance()->getHuman(cache.uid_);
			if (pHuman != NULL) {
				pHuman->doAddSkill(item);
			}
			debug_log("unlock skill %u %u %u", cache.uid_, rid, item.id);
		}
	}
	if (!sync) {
		m_chgs.clear();
	}
	return true;
}

bool SkillManager::UnlockShenQi(UserCache &cache) {
	const CfgSkill::Skill &cfg = SkillCfgWrap().GetFirst(SKILL_SHENQI_BEGIN + cache.shenqi_.id);
	list<DataSkill>::iterator itr = cache.skill_.begin();
	for (; itr != cache.skill_.end(); ++itr) {
		if (itr->id == cfg.serial()) {
			error_log("skill is exists uid=%u id=%u serial=%u", cache.uid_, itr->id, cfg.serial());
			return false;
		}
	}

	DataSkill data;
	data.uid = cache.uid_;
	data.rid = 0;
	data.lv = 1;
	data.id = cfg.serial();
	data.skill_id = cfg.id();
	DataSkillManager::Instance()->Add(data);
	cache.skill_.push_back(data);

	m_oper = SKILL_ADD;
	m_chgs.push_back(data);

	debug_log("unlocke shenqi skill uid=%u serial=%u", cache.uid_, cfg.serial());
	return true;
}

bool SkillManager::UnlockZhanLing(UserCache &cache) {
	const CfgSkill::Skill &cfg = SkillCfgWrap().GetFirst(SKILL_ZHANLING_BEGIN);
	list<DataSkill>::iterator itr = cache.skill_.begin();
	for (; itr != cache.skill_.end(); ++itr) {
		if (itr->id == cfg.serial()) {
			error_log("skill is exists uid=%u id=%u serial=%u", cache.uid_, itr->id, cfg.serial());
			return false;
		}
	}

	DataSkill data;
	data.uid = cache.uid_;
	data.rid = 0;
	data.lv = 1;
	data.id = cfg.serial();
	data.skill_id = cfg.id();
	DataSkillManager::Instance()->Add(data);
	cache.skill_.push_back(data);
	Human *pHuman = MapManager::Instance()->getHuman(cache.uid_);
	if (pHuman != NULL) {
		pHuman->doAddSkill(data);
	}
	m_oper = SKILL_ADD;
	m_chgs.push_back(data);

	debug_log("unlocke zhanling skill uid=%u serial=%u", cache.uid_, cfg.serial());

	return true;
}

bool SkillManager::UnlockAdvance(UserCache &cache, uint32_t rid, uint32_t id) {
	const CfgSkill::Skill &cfg = SkillCfgWrap().GetById(id);
	list<DataSkill>::iterator itr = cache.skill_.begin();
	for (; itr != cache.skill_.end(); ++itr) {
		if (itr->id == cfg.id()) {
			error_log("skill is exists uid=%u id=%u serial=%u", cache.uid_, itr->id, cfg.serial());
			return false;
		}
	}

	DataSkill data;
	data.uid = cache.uid_;
	data.rid = rid;
	data.lv = 1;
	data.id = cfg.serial();
	data.skill_id = cfg.id();
	DataSkillManager::Instance()->Add(data);
	cache.skill_.push_back(data);
	Human *pHuman = MapManager::Instance()->getHuman(cache.uid_);
	if (pHuman != NULL) {
		pHuman->doAddSkill(data);
	}
	m_oper = SKILL_ADD;
	m_chgs.push_back(data);

	debug_log("unlocke Advance skill uid=%u rid=%u, serial:%u", cache.uid_, rid, cfg.serial());

	return true;
}

bool SkillManager::SendChange(uint32_t uid) {
	if (m_chgs.empty()) {
		return true;
	}

	msgs::SUpdateSkill msg;
	msg.oper_ = m_oper;
	dbs::TPlayerSkill item;
	vector<DataSkill>::iterator itr = m_chgs.begin();
	SkillCfgWrap cfgwrap;
	for (; itr != m_chgs.end(); ++itr) {
		if (uid != itr->uid) {
			continue;
		}
		item.playerId_ = itr->uid;
		item.skillSeries_ = itr->id;
		item.skillId_ = itr->skill_id;
		item.roleId_ = itr->rid;
		msg.skills_.push_back(item);
	}
	LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_SKILL_UPDATE, &msg);
	m_chgs.clear();
	return true;
}

bool SkillManager::UpgradeSkill(const UserCache &cache, DataSkill &data) {
	uint32_t cost = 0;
	uint32_t skill_lv = data.lv;
	uint32_t skill_id = data.skill_id;
	uint32_t coin = UserManager::Instance()->GetMoney(cache.uid_, MONEY_COIN);
	SkillCfgWrap cfg_warp;
	try {
		while (true) {
			const CfgSkill::Skill &cfg = cfg_warp.GetByLv(data.id, skill_lv + 1, skill_id + 1);

			if (cost + cfg.cost() > coin
			|| skill_lv + 1 > static_cast<uint32_t>(cache.base_.level)
			|| cfg.careerlevel() > static_cast<uint32_t>(cache.m_reinCarnInfo.reinCarnLevel)) {
				break;
			}

			cost += cfg.cost();
			skill_lv += 1;
			skill_id = cfg.id();
		}

		string code;
		String::Format(code, "skill_up_%u_%u_%u", data.id, data.lv, skill_lv);
		if (cost > 0 && !UserManager::Instance()->UseMoney(data.uid, MONEY_COIN, cost, code)) {
			error_log("use coin error uid=%u cost=%u", data.uid, cost);
			return false;
		}

		data.lv = skill_lv;
		data.skill_id = skill_id;

		DataSkillManager::Instance()->Set(data);
		Human *pHuman = MapManager::Instance()->getHuman(data.uid);
		if (pHuman != NULL) {
			pHuman->doAddSkill(data);
		}

		m_oper = SKILL_SET;
		m_chgs.push_back(data);
	} catch (const std::exception& e) {
		return false;
	}
	return true;
}

bool SkillManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	SkillCfgWrap cfg_wrap;
	list<DataSkill>::const_iterator itr = cache.skill_.begin();
	for (; itr != cache.skill_.end(); ++itr) {
		try {
			const CfgSkill::Skill &cfg = cfg_wrap.GetByLv(itr->id, itr->lv, itr->skill_id);
			PropertyCfg::setProps(cfg.attr(), 1, props);
		} catch (...) {
			continue;
		}
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "skill");
	return true;
}

int SkillManager::Process(uint32_t uid, logins::SUseSkill *req) {
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	vector<uint32_t> targets;
	vector<Identity>::iterator itr = req->oper_.seqEntity_.begin();
	for (; itr != req->oper_.seqEntity_.end(); ++itr) {
		targets.push_back(itr->id_);
	}
	if (!pHuman->doUseSkill(req->oper_.skillId_, targets, req->oper_.centerPoint_)) {
		error_log("uid=%u skill=%u tar=%u", uid, req->oper_.skillId_, targets.empty() ? 0 : targets.front());
		return R_ERROR;
	}
	debug_log("uid=%u skill=%u tar=%u num=%u", uid, req->oper_.skillId_, targets.empty() ? 0 : targets.front(), targets.size());
	return 0;
}

int SkillManager::Process(uint32_t uid, logins::SUpgradeSkill *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		error_log("cache not init uid=%u", uid);
		return R_ERROR;
	}
	SkillCfgWrap cfg_warp;
	const CfgSkill::Skill &cfg = cfg_warp.GetById(req->skillId_);
	DataSkill item;
	item.uid = uid;
	item.id = cfg.serial();
	item.rid = req->roleId_;
	list<DataSkill>::iterator itr = find(cache.skill_.begin(), cache.skill_.end(), item);
	if (itr == cache.skill_.end()) {
		error_log("skill not exists uid=%u rid=%u skid=%u", uid, req->roleId_, req->skillId_);
		return R_ERROR;
	}

	if (itr->lv >= cache.base_.level) {
		error_log("level limit uid=%u rid=%u skid=%u lv=%u blv=%u",
				uid, req->roleId_, req->skillId_, itr->lv, cache.base_.level);
		return R_ERROR;
	}

	if (!UpgradeSkill(cache, *itr)) {
		error_log("upgrage skill error uid=%u rid=%u skid=%u", uid, req->roleId_, req->skillId_);
		return R_ERROR;
	}

	MissionManager::Instance()->onMission(uid, MT_UPGRADE_SKILL, itr->lv);

	debug_log("uid=%u,skid=%u", uid, req->skillId_);

	return 0;
}

int SkillManager::Process(uint32_t uid, logins::SUpgradeSkillAll *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		error_log("cache not init uid=%u", uid);
		return R_ERROR;
	}

	uint32_t coin = UserManager::Instance()->GetMoney(cache.uid_, MONEY_COIN);
	uint32_t cost = 0;
	SkillCfgWrap cfg_warp;
	SkillBaseCfgWrap base_cfg_warp;
	map<uint32_t, DataSkill> temp;
	map<uint32_t, DataSkill>::iterator tItr;
	list<DataSkill>::iterator itr;

	for (itr = cache.skill_.begin(); itr != cache.skill_.end(); ++itr) {
		if (!base_cfg_warp.IsExist(itr->id)) {
			continue;
		}
		temp[itr->id] = *itr;
	}

	uint32_t ctrl = 0;
	while (true) {
		ctrl = 0;
		for (tItr = temp.begin(); tItr != temp.end(); ++tItr) {
			DataSkill &skill = tItr->second;
			try {
				const CfgSkill::Skill &cfg = cfg_warp.GetByLv(skill.id, skill.lv + 1, skill.skill_id + 1);
				if (cost + cfg.cost() > coin
				|| skill.lv + 1 > cache.base_.level
				|| cfg.careerlevel() > static_cast<uint32_t>(cache.m_reinCarnInfo.reinCarnLevel)) {
					continue;
				}
				skill.lv += 1;
				cost += cfg.cost();
				skill.skill_id = cfg.id();
				++ctrl;
			} catch(...) {
				continue;
			}
		}
		if (ctrl == 0) {
			break;
		}
	}

	string code = "skill_up_all";
	if (cost > 0 && !UserManager::Instance()->UseMoney(uid, MONEY_COIN, cost, code)) {
		error_log("use coin error uid=%u cost=%u", uid, cost);
		return R_ERROR;
	}

	Human *pHuman = MapManager::Instance()->getHuman(uid);

	for (itr = cache.skill_.begin(); itr != cache.skill_.end(); ++itr) {
		tItr = temp.find(itr->id);
		if (tItr == temp.end()) {
			continue;
		}
		if (itr->lv == tItr->second.lv) {
			continue;
		}
		itr->lv = tItr->second.lv;
		itr->skill_id = tItr->second.skill_id;

		DataSkillManager::Instance()->Set(*itr);

		if (pHuman != NULL) {
			pHuman->doAddSkill(*itr);
		}

		m_oper = SKILL_SET;
		m_chgs.push_back(*itr);

		MissionManager::Instance()->onMission(uid, MT_UPGRADE_SKILL, itr->lv);
	}

	return 0;
}

int SkillManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerSkillInfo *resp) {
	list<DataSkill>::const_iterator itr = cache.skill_.begin();
	SkillCfgWrap cfgwrap;
	for (; itr != cache.skill_.end(); ++itr) {
		dbs::TPlayerSkill item;
		item.playerId_ = cache.uid_;
		item.skillSeries_ = itr->id;
		item.skillId_ = itr->skill_id;
		item.roleId_ = itr->rid;
		resp->skills_.push_back(item);
	}
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}
