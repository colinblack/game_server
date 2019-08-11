/*
 * ZhanLingManager.cpp
 *
 *  Created on: 2019年7月20日
 *      Author: Administrator
 */

#include "ZhanLingManager.h"
#include "BattleInc.h"
#include "MapDisplayObject.h"

ZhanLingManager::ZhanLingManager() {
	m_recover.clear();
}

ZhanLingManager::~ZhanLingManager() {
	m_recover.clear();
}

bool ZhanLingManager::ActorLogin(uint32_t uid) {
	return checkUnlock(uid);
}

bool ZhanLingManager::checkUnlock(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}

	if (cache.zhanling_.uid != 0) {
		const CfgZhanLing::Base& cfg = ZhanLingCfgWrap().GetBase(cache.zhanling_.dai);
		m_speed[uid] = ZHAN_LING_MAX_NUQI_SPEED + ZHAN_LING_MAX_NUQI_SPEED * cfg.speed() / 100;
		return false;
	}
	cache.zhanling_.uid = cache.uid_;
	cache.zhanling_.nuqi = ZHAN_LING_MAX_NUQI;
	cache.zhanling_.dai = 1;
	DataAttr attr;
	cache.zhanling_.ToAttr(attr);
	DataAttrManager::Instance()->Add(attr);
	SkillManager::Instance()->UnlockZhanLing(cache);
	m_recover[cache.uid_] = cache.zhanling_.nuqi;
	const CfgZhanLing::Base& cfg = ZhanLingCfgWrap().GetBase(cache.zhanling_.dai);
	m_speed[uid] = ZHAN_LING_MAX_NUQI_SPEED + ZHAN_LING_MAX_NUQI_SPEED * cfg.speed() / 100;
	LogicManager::Instance()->AddSync(CMD_ZHANLING_INFO);
	return true;
}

bool ZhanLingManager::onChangeMap(uint32_t uid) {
	return resetNuQi(uid);
}

bool ZhanLingManager::onSecondTimer() {
	static map<uint32_t, uint16_t>::iterator itr;
	for (itr = m_recover.begin(); itr != m_recover.end();) {
		uint16_t &nuqi = itr->second;
		if (nuqi + m_speed[itr->first] >= ZHAN_LING_MAX_NUQI) {
			nuqi = ZHAN_LING_MAX_NUQI;
			setNuQi(itr->first, nuqi);
			m_recover.erase(itr++);
			continue;
		}
		nuqi += m_speed[itr->first];
		updateNuQi(itr->first, nuqi);
		++itr;
	}
	return true;
}

bool ZhanLingManager::resetNuQi(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	cache.zhanling_.nuqi = ZHAN_LING_MAX_NUQI - ZHAN_LING_MAX_NUQI_SUB;
	m_recover[uid] = cache.zhanling_.nuqi;
	return true;
}

bool ZhanLingManager::setNuQi(uint32_t uid, uint32_t nuqi) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (cache.zhanling_.uid == 0) {
		return false;
	}
	cache.zhanling_.nuqi = nuqi;
	DataAttr attr;
	cache.zhanling_.ToAttr(attr);
	DataAttrManager::Instance()->Set(attr);
	updateNuQi(uid, nuqi);
	return true;
}

bool ZhanLingManager::updateNuQi(uint32_t uid, uint32_t nuqi) {
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return false;
	}

	msgs::SEntityUpdate msg;
	msg.clear();
	msg.entityId_ = pHuman->getEntityMsg();
	msg.updateType_ = ATTR_UPDATE_NUQI;
	msg.updateData_.push_back(nuqi);
	msg.updateData_.push_back(m_speed[uid]);
	LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UPDATE, &msg);
	return true;
}

bool ZhanLingManager::useNuQi(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (cache.zhanling_.uid == 0) {
		return false;
	}
	if (cache.zhanling_.nuqi < ZHAN_LING_MAX_NUQI) {
		return false;
	}
	cache.zhanling_.nuqi = 0;
	DataAttr attr;
	cache.zhanling_.ToAttr(attr);
	DataAttrManager::Instance()->Set(attr);
	m_recover[uid] = 0;
	return true;
}

bool ZhanLingManager::useZhanlingItem(UserCache& cache, DataEquip equip, uint32_t cost, const string &code) {
	if (equip.num > cost) {
		equip.num -= cost;
		DataEquipManager::Instance()->Set(equip);
		UpdateManager::Instance()->Bag(cache.uid_, 0 - cost, equip);
		BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=use,chg=%u,count=%u,code=%s", cache.uid_, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
	} else if (equip.num == cost) {
		equip.num = 0;
		DataEquipManager::Instance()->Del(equip);
		UpdateManager::Instance()->Bag(cache.uid_, 0 - cost, equip);
		BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=del,chg=%u,count=%u,code=%s", cache.uid_, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
	} else {
		error_log("not enough uid:%u id;%u", cache.uid_, equip.id);
		return false;
	}
	return true;
}

bool ZhanLingManager::CalcProperty(const UserCache &cache, PropertySets &props) {
//	const CfgZhanLing::Base& zhanling_cfg = ZhanLingCfgWrap().GetBase(cache.zhanling_.dai);
//	PropertyCfg::setProps(zhanling_cfg.attr(), 1.0, props);
//
//	map<uint32_t, DataEquip>::const_iterator it = cache.equip_.begin();
//	for(; it != cache.equip_.end(); ++it) {
//		if(BAG_ZHANLING_EQUIP == it->second.bag) {
//			const CfgItem::Equip& cfg = ItemCfgWrap().GetEquip(it->second.id);
//			PropertyCfg::setProps(cfg.attr(), 1.0, props);
//		}
//	}
//	PropertyCfg::showProps(cache.uid_, -1, props, "Treasure");
	return true;
}

int ZhanLingManager::Process(uint32_t uid, logins::SSkillCleanNuQi *req) {
	if (!useNuQi(uid)) {
		return R_ERROR;
	}
	return 0;
}

int ZhanLingManager::Process(uint32_t uid, logins::SEquipZhanlingReq *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERROR;
	}

	if(0 == cache.equip_.count(req->uid)) {
		error_log("equip uid:%u error", req->uid);
		return R_ERROR;
	}
	DataEquip& data = cache.equip_[req->uid];
	data.bag = BAG_ZHANLING_EQUIP;
	DataEquipManager::Instance()->Set(data);

	UpdateManager::Instance()->SetCode(UC_MoveItem);
	UpdateManager::Instance()->ChgBag(cache.uid_, BAG_ALL, BAG_ZHANLING_EQUIP, data);

	PropertyManager::Instance()->AddUser(uid);
	return R_SUCCESS;
}

int ZhanLingManager::Process(uint32_t uid, logins::SAdvanceZhanlingReq *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERROR;
	}
	cache.zhanling_.dai++;
	const CfgZhanLing::Base& cfg = ZhanLingCfgWrap().GetBase(cache.zhanling_.dai);
	map<uint32_t, DataEquip>::iterator it = cache.equip_.begin();
	for(; it != cache.equip_.end(); ++it) {
		if(BAG_ZHANLING_EQUIP == it->second.bag) {
			UpdateManager::Instance()->SetCode(UC_AdvanceZhanling);
			if(!useZhanlingItem(cache, it->second, 1, "zhanling advance")) {
				return R_ERROR;
			}
		}
	}
	DataAttr attr;
	cache.zhanling_.ToAttr(attr);
	DataAttrManager::Instance()->Set(attr);

	const CfgSkill::Skill& skill_cfg = SkillCfgWrap().GetById(cfg.skill());
	DataSkill data;
	data.uid = uid;
	data.rid = 0;
	data.lv = 1;
	data.id = skill_cfg.serial();
	data.skill_id = skill_cfg.id();
	DataSkillManager::Instance()->Add(data);
	cache.skill_.push_back(data);

	vector<DataSkill> skills;
	skills.push_back(data);
	//怒气恢复速度
	m_speed[uid] = ZHAN_LING_MAX_NUQI_SPEED * cfg.speed() / 100;

	UpdateManager::Instance()->skills(uid, 2, skills);
	LogicManager::Instance()->AddSync(CMD_ZHANLING_INFO);
	PropertyManager::Instance()->AddUser(uid);
	return R_SUCCESS;
}

int ZhanLingManager::Process(uint32_t uid, logins::SLearnZhanlingSkillReq *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERROR;
	}
	list<DataSkill>::iterator it = cache.skill_.begin();
	for(; it != cache.skill_.end(); ++it) {
		if(it->skill_id == req->skillId) {
			error_log("skill:%u already exist", req->skillId);
			return R_ERROR;
		}
	}
	const CfgZhanLing::Base& zhanling_cfg = ZhanLingCfgWrap().GetBase(cache.zhanling_.dai);
	const CfgSkill::Skill& skill_cfg = SkillCfgWrap().GetById(req->skillId);
	if(!SkillCfgWrap().IsZhanLing(skill_cfg)) {
		error_log("skill:%u not zhanling skill", req->skillId);
		return R_ERROR;
	}

	vector<DataSkill> skills;
	DataSkill data;
	data.uid = uid;
	data.rid = 0;
	data.lv = 1;
	data.id = skill_cfg.serial();
	data.skill_id = skill_cfg.id();
	DataSkillManager::Instance()->Add(data);
	cache.skill_.push_back(data);

	skills.push_back(data);
	UpdateManager::Instance()->skills(uid, 0, skills);
	PropertyManager::Instance()->AddUser(uid);
	return R_SUCCESS;
}

int ZhanLingManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SZhanlingInfo *resp) {
	if (cache.zhanling_.uid == 0) {
		return 0;
	}
	resp->dai_ = cache.zhanling_.dai;
	resp->mission_ = cache.zhanling_.mission;
	resp->deadline_ = cache.zhanling_.deadline;
	resp->adv_ = cache.zhanling_.adv;
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
