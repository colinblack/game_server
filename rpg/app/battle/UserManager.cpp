/*
 * UserManager.cpp
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#include "UserManager.h"
#include "BattleInc.h"

UserManager::UserManager() {
}

UserManager::~UserManager() {
}

int UserManager::Process(uint32_t uid, logins::SQuery *req, logins::SQueryResult *resp) {
	bool is_new = false;

	if (!GetUid(req->username_, uid, is_new)) {
		return R_ERR_DATA;
	}

	if (!is_new) {
		CacheManager::Instance()->ActorLogin(uid);
	}

	resp->proxyId_ = LogicManager::ProxyId;
	resp->serverId_ = LogicManager::ServerId;
	resp->playerList_.clear();

	UserCache &cache = CacheManager::Instance()->GetUser(uid);

	if (cache.base_.uid == 0) {
		return R_SUCCESS;
	}

	dbs::TPlayer item;
	GetPlayerMsg(cache, &item);
	resp->playerList_.push_back(item);

	return R_SUCCESS;
}

int UserManager::Process(uint32_t uid, logins::SLogin *req, logins::SLoginResult *resp) {
	int ret = 0;
	bool is_new = false;
	if (!GetUid(req->username_, uid, is_new)) {
		return R_ERROR;
	}

	if (!is_new) {
		CacheManager::Instance()->ActorLogin(uid);
	}

	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (cache.base_.uid == 0) {
		is_new = true;
	}

	if (is_new && !AddBase(cache, req->username_)) {
		return R_ERROR;
	}

	DataBase &data = cache.base_;

	if (!is_new) {
		cache.base_.login_time = Time::GetGlobalTime();
	}

	if (is_new && data.role_num == 0) {
		if (!RoleManager::Instance()->AddRole(uid, 1, req->sex_, req->career_, req->name_)) {
			error_log("add role error uid=%u rid=1", uid);
			return R_ERROR;
		}
	}

	ret = DataBaseManager::Instance()->Set(data);
	if (0 != ret) {
		error_log("set base error ret=%d uid=%u", ret, uid);
		return R_ERROR;
	}

	CInternetAddress addr;
	addr.FromString(Config::GetValue("client_listen"));

	resp->gateHost_ = addr.IP;
	resp->gatePort_ = addr.Port;
	resp->token_ = "test";
	resp->proxyId_ = LogicManager::ProxyId;
	resp->serverId_ = LogicManager::ServerId;
	GetPlayerMsg(cache, &(resp->player_));

	return R_SUCCESS;
}

int UserManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerLoginData *resp) {
	resp->clear();
	resp->playerId_ = cache.uid_;
	resp->serverId_ = LogicManager::ServerId;
	resp->proxyId_ = LogicManager::ProxyId;
	resp->entityId_.id_ = cache.uid_;
	resp->entityId_.type_ = 1;
	resp->entityId_.proxy_ = LogicManager::ProxyId;
	resp->entityId_.server_ = LogicManager::ServerId;

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

int UserManager::Sync(const UserCache &cache, uint32_t cmd, dbs::TPlayer *resp) {
	GetPlayerMsg(cache, resp);
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

int UserManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerMoneyList *resp) {
	map<uint32_t, DataPay>::const_iterator itr = cache.pay_.begin();
	for (; itr != cache.pay_.end(); ++itr) {
		const DataPay &pay = itr->second;
		resp->moneys_[pay.id] = pay.num;
	}

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

bool UserManager::onLogin(uint32_t uid) {
	return true;
}

bool UserManager::ActorOffline(uint32_t uid) {
	return true;
}

bool UserManager::AddBase(UserCache &cache, const string &open_id) {
	if (cache.base_.uid != 0) {
		error_log("uid is exist uid=%u openid=%s", cache.uid_, open_id.c_str());
		return false;
	}

	DataBase &data = cache.base_;
	data.uid = cache.uid_;
	data.register_time = Time::GetGlobalTime();
	data.login_time = Time::GetGlobalTime();
	data.hang = 1;
	data.open_id = open_id;
	data.level = 1;

	int ret = DataBaseManager::Instance()->Add(data);
	if (0 != ret) {
		error_log("add base error uid=%u openid=%s", cache.uid_, open_id.c_str());
		return false;
	}

	return true;
}

bool UserManager::GetUid(const string &open_id, uint32_t &uid, bool &is_new) {
	CDataUserMapping dbUserMapping;
	uid = 0;
	is_new = false;
	int ret = dbUserMapping.GetMapping(open_id, LogicManager::ServerId, PT_TEST, uid);
	if (R_SUCCESS == ret) {
		return true;
	} else if (R_ERR_NO_DATA == ret) {
		if (!GetNextUid(uid)) {
			error_log("get next uid error openid=%s", open_id.c_str());
			return false;
		}
		ret = dbUserMapping.AddMapping(open_id, LogicManager::ServerId, PT_TEST, uid);
		if (0 != ret) {
			error_log("set user mapping error ret=%d openid=%s", ret, open_id.c_str());
			return false;
		}
		is_new = true;
		return true;
	} else {
		error_log("get user mapping error ret=%d openid=%s", ret, open_id.c_str());
		return false;
	}
}

bool UserManager::GetNextUid(uint32_t &uid) {
	uint64_t curr = 0;
	CDataIdCtrl dbIdCtrl;
	int ret = dbIdCtrl.GetId(KEY_UID_CTRL, LogicManager::ServerId, curr);
	if (0 != ret) {
		error_log("get id error ret=%d", ret);
		return false;
	}
	++curr;
	ret = dbIdCtrl.SetId(KEY_UID_CTRL, LogicManager::ServerId, curr);
	if (0 != ret) {
		error_log("set id error ret=%d", ret);
		return false;
	}
	uid = curr;
	return true;
}


bool UserManager::doTestLevel(uint32_t uid, uint32_t level) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	DataBase &data = cache.base_;
	data.level = level;
	DataBaseManager::Instance()->Set(data);
	static msgs::SLevelUp lv_msg;
	lv_msg.exp_ = data.exp;
	lv_msg.level_ = data.level;
	lv_msg.levelDt_ = Time::GetGlobalTime() * 1000LL;
	LogicManager::Instance()->SendMsg(uid, CMD_LEVEL_UP, &lv_msg);
	SkillManager::Instance()->AutoUnlock(cache, true);
	return true;
}

bool UserManager::AddExp(uint32_t uid, uint32_t exp) {
	if (exp == 0) {
		return false;
	}
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	bool lv_up = false;
	static msgs::SLevelUp lv_msg;
	static msgs::SAddExp msg;
	msg.exp_ = exp;
	msg.updateCode_ = 118;
	msg.addon_ = 0;
	DataBase &data = cache.base_;

	LevelCfgWrap cfgWrap;
	while (exp > 0) {
		const CfgLevel::Level &cfg = cfgWrap.Get(data.level);
		uint32_t need = cfg.exp() > data.exp ? cfg.exp() - data.exp : 0;
		if (exp > need) {
			data.level += 1;
			data.exp = 0;
			exp -= need;
			lv_up = true;
		} else {
			data.exp += exp;
			exp = 0;
		}
	}
	DataBaseManager::Instance()->Set(data);

	if (lv_up) {
		lv_msg.exp_ = data.exp;
		lv_msg.level_ = data.level;
		lv_msg.levelDt_ = Time::GetGlobalTime() * 1000LL;
		LogicManager::Instance()->SendMsg(uid, CMD_LEVEL_UP, &lv_msg);
		SkillManager::Instance()->AutoUnlock(cache, true);
		PropertyManager::Instance()->AddUser(uid);
	} else {
		LogicManager::Instance()->SendMsg(uid, CMD_ADD_EXP, &msg);
	}
	return true;
}

bool UserManager::AddMoney(uint32_t uid, uint32_t id, uint32_t num, const string &code) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}

	DataPay &pay = cache.pay_[id];
	uint32_t old = pay.num;

	pay.num += num;
	if (pay.uid == 0) {
		pay.uid = uid;
		pay.id = id;
		DataPayManager::Instance()->Add(pay);
	} else {
		DataPayManager::Instance()->Set(pay);
	}

	BUSI_COIN("[change pay log][uid=%u,id=%u,old=%u,now=%u,chg=%u,type=%s]", uid, id, old, pay.num, num, code.c_str());

	UpdateManager::Instance()->Money(uid, id, num, pay.num);

	return true;
}

bool UserManager::UseMoney(uint32_t uid, uint32_t id, uint32_t num, const string &code) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	DataPay &pay = cache.pay_[id];
	uint32_t old = pay.num;

	if (pay.num < num) {
		error_log("money is not enough uid=%u id=%u need=%u hold=%u", uid, id, num, old);
		return false;
	}

	pay.num -= num;

	if (pay.uid == 0) {
		pay.uid = uid;
		DataPayManager::Instance()->Add(pay);
	} else {
		DataPayManager::Instance()->Set(pay);
	}

	BUSI_COIN("[change pay log][uid=%u,id=%u,old=%u,now=%u,chg=%d,type=%s]", uid, id, old, pay.num, 0 - num, code.c_str());

	UpdateManager::Instance()->Money(uid, id, 0 - num, pay.num);

	return true;
}

uint32_t UserManager::GetMoney(uint32_t uid, uint32_t id) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return 0;
	}
	map<uint32_t, DataPay>::iterator itr = cache.pay_.find(id);
	return itr == cache.pay_.end() ? 0 : itr->second.num;
}

bool UserManager::AddItem(uint32_t uid, uint32_t id, uint32_t num, const string &code, uint32_t bag) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	uint32_t ud = 1;
	if (!cache.equip_.empty()) {
		ud = cache.equip_.rbegin()->first + 1;
	}
	ItemCfgWrap cfg_wrap;
	if (cfg_wrap.IsEquip(id)) {
		for (uint32_t i = 0; i < num; ++i, ++ud) {
			DataEquip equip;
			equip.uid = uid;
			equip.id = id;
			equip.num = 1;
			equip.bag = bag;
			equip.ts = Time::GetGlobalTime();
			equip.ud = ud;
			EquipsManager::Instance()->RandomAttr(equip);
			DataEquipManager::Instance()->Add(equip);
			cache.equip_[equip.ud] = equip;
			UpdateManager::Instance()->Bag(uid, 1, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=new,chg=1,count=1,code=%s", uid, ud, id, code.c_str());
		}
	} else if (cfg_wrap.IsMagic(id)) {
		for (uint32_t i = 0; i < num; ++i, ++ud) {
			DataEquip equip;
			equip.uid = uid;
			equip.id = id;
			equip.num = 1;
			equip.bag = bag;
			RuneManager::Instance()->addExt(equip.ext, 1);
			equip.ts = Time::GetGlobalTime();
			equip.ud = ud;
			DataEquipManager::Instance()->Add(equip);
			cache.equip_[equip.ud] = equip;
			UpdateManager::Instance()->Bag(uid, 1, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=new,chg=1,count=1,code=%s", uid, ud, id, code.c_str());
		}
	} else {
		map<uint32_t, DataEquip>::iterator itr = cache.equip_.begin();
		for (; itr != cache.equip_.end(); ++itr) {
			DataEquip &equip = itr->second;
			if (equip.bag != bag)
				continue;
			if (equip.id == id) {
				equip.num += num;
				DataEquipManager::Instance()->Set(equip);
				UpdateManager::Instance()->Bag(uid, 1, equip);
				BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=add,chg=%u,count=%u,code=%s", uid, ud, id, num, equip.num, code.c_str());
				return 0;
			}
		}

		DataEquip equip;
		equip.uid = uid;
		equip.id = id;
		equip.num = num;
		equip.bag = bag;
		equip.ts = Time::GetGlobalTime();
		equip.ud = ud;
		DataEquipManager::Instance()->Add(equip);
		cache.equip_[equip.ud] = equip;
		UpdateManager::Instance()->Bag(uid, num, equip);
		BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=new,chg=%u,count=%u,code=%s", uid, ud, id, num, equip.num, code.c_str());
	}
	return true;
}

bool UserManager::UseItem(uint32_t uid, uint32_t id, uint32_t num, const string &code) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	map<uint32_t, uint32_t> cost_map;
	map<uint32_t, DataEquip>::iterator itr = cache.equip_.begin();
	for (; itr != cache.equip_.end(); ++itr) {
		DataEquip &equip = itr->second;
		if(equip.bag!=1) continue;
		if (equip.id == id) {
			if (equip.num >= num) {
				cost_map[equip.ud] = num;
				num = 0;
			} else {
				cost_map[equip.ud] = equip.num;
				num -= equip.num;
			}
		}
	}
	if (num != 0) {
		error_log("equip not enough uid=%u id=%u num=%u", uid, id, num);
		return false;
	}

	map<uint32_t, uint32_t>::iterator costItr = cost_map.begin();
	for (; costItr != cost_map.end(); ++costItr) {
		DataEquip &equip = cache.equip_[costItr->first];
		uint32_t cost = costItr->second;
		if (equip.num > cost) {
			equip.num -= cost;
			DataEquipManager::Instance()->Set(equip);
			UpdateManager::Instance()->Bag(uid, 0 - cost, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=use,chg=%u,count=%u,code=%s", uid, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
		} else if (equip.num == cost) {
			equip.num = 0;
			DataEquipManager::Instance()->Del(equip);
			UpdateManager::Instance()->Bag(uid, 0 - cost, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=del,chg=%u,count=%u,code=%s", uid, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
		} else {
			return false;
		}
	}
	return true;
}

uint32_t UserManager::TryUseItem(uint32_t uid, uint32_t id, uint32_t num, const string &code) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return 0;
	}
	uint32_t use = 0;
	map<uint32_t, uint32_t> cost_map;
	map<uint32_t, DataEquip>::iterator itr = cache.equip_.begin();
	for (; itr != cache.equip_.end(); ++itr) {
		DataEquip &equip = itr->second;
		if (equip.id == id) {
			if (equip.num >= num) {
				cost_map[equip.ud] = num;
				num = 0;
			} else {
				cost_map[equip.ud] = equip.num;
				num -= equip.num;
			}
		}
	}

	map<uint32_t, uint32_t>::iterator costItr = cost_map.begin();
	for (; costItr != cost_map.end(); ++costItr) {
		DataEquip &equip = cache.equip_[costItr->first];
		uint32_t cost = costItr->second;
		if (equip.num > cost) {
			use += cost;
			equip.num -= cost;
			DataEquipManager::Instance()->Set(equip);
			UpdateManager::Instance()->Bag(uid, 0 - cost, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=use,chg=%u,count=%u,code=%s", uid, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
		} else if (equip.num == cost) {
			use += equip.num;
			equip.num = 0;
			DataEquipManager::Instance()->Del(equip);
			UpdateManager::Instance()->Bag(uid, 0 - cost, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=del,chg=%u,count=%u,code=%s", uid, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
		}
	}
	return use;
}

uint32_t UserManager::TryUseItemMulti(uint32_t uid, uint32_t id, uint32_t num, uint32_t multi, const string &code) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_ || num == 0 || multi == 0) {
		return 0;
	}

	uint32_t need = num * multi;
	uint32_t hold = 0;
	map<uint32_t, uint32_t> cost_map;
	map<uint32_t, DataEquip>::iterator itr = cache.equip_.begin();
	for (; itr != cache.equip_.end(); ++itr) {
		DataEquip &equip = itr->second;
		if (equip.id == id) {
			if (equip.num >= need) {
				cost_map[equip.ud] = need;
				need = 0;
				hold += need;
			} else {
				cost_map[equip.ud] = equip.num;
				need -= equip.num;
				hold += equip.num;
			}
		}
	}

	uint32_t can_use = hold / num;
	need = can_use * num;

	uint32_t use = 0;
	map<uint32_t, uint32_t>::iterator costItr = cost_map.begin();
	for (; costItr != cost_map.end(); ++costItr) {
		DataEquip &equip = cache.equip_[costItr->first];
		uint32_t cost = costItr->second;
		if (use >= need) {
			break;
		} else if (use + cost > need) {
			cost = need - use;
		}
		if (equip.num > cost) {
			use += cost;
			equip.num -= cost;
			DataEquipManager::Instance()->Set(equip);
			UpdateManager::Instance()->Bag(uid, 0 - cost, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=use,chg=%u,count=%u,code=%s", uid, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
		} else if (equip.num == cost) {
			use += equip.num;
			equip.num = 0;
			DataEquipManager::Instance()->Del(equip);
			UpdateManager::Instance()->Bag(uid, 0 - cost, equip);
			BUSI_EQUIP("uid=%u,id=%u,eqid=%d,act=del,chg=%u,count=%u,code=%s", uid, equip.ud, equip.id, 0 - cost, equip.num, code.c_str());
		}
	}
	return can_use;
}

bool UserManager::Reward(uint32_t uid, const Award &v, const string &code, uint32_t bag) {
	const map<uint32_t, uint32_t> &data = v.Data();
	map<uint32_t, uint32_t>::const_iterator itr = data.begin();
	uint32_t item = 0;
	uint32_t num = 0;
	for (; itr != data.end(); ++itr) {
		item = itr->first;
		num = itr->second;
		if (item == MONEY_EXP) {
			AddExp(uid, num);
		} else if (IS_MONEY(item)) {
			AddMoney(uid, item, num, code);
		} else {
			AddItem(uid, item, num, code, bag);
		}
	}

	return true;
}

bool UserManager::AddHangPower(UserCache &cache, uint32_t power) {
	if (cache.base_.hang_power >= 200) {
		return true;
	}

	cache.base_.hang_power = cache.base_.hang_power + power > 200 ? 200 : cache.base_.hang_power + power;
	DataBaseManager::Instance()->Set(cache.base_);
	LogicManager::Instance()->AddSync(CMD_HANG_POWER);
	return true;
}

bool UserManager::UseHangPower(UserCache &cache, uint32_t power) {
	if (power > static_cast<uint32_t>(cache.base_.hang_power)) {
		return false;
	}
	cache.base_.hang_power -= power;
	DataBaseManager::Instance()->Set(cache.base_);
	LogicManager::Instance()->AddSync(CMD_HANG_POWER);
	return true;
}

bool UserManager::CalcProperty(const UserCache &cache, byte rid, PropertySets &props) {
	PropertySets group;

	RoleManager::Instance()->CalcProperty(cache, rid, group); // 人物等级属性
	AdvanceManager::Instance()->CalcProperty(cache, rid, group);
	SkillManager::Instance()->CalcProperty(cache, rid, group);
	ShenQiManager::Instance()->CalcProperty(cache, rid, group);
	EquipsManager::Instance()->CalcProperty(cache, rid, group);
	ForgeManager::Instance()->CalcProperty(cache, rid, group);
	CardManager::Instance()->CalcProperty(cache, rid, group);
	PurifyManager::Instance()->CalcProperty(cache, rid, group);
	ReinCarnManager::Instance()->CalcProperty(cache, rid, group);
	RuneManager::Instance()->CalcProperty(cache, rid, group);
	PropertyCfg::calcGroupBase(group, props);
	PropertyCfg::calcGroupBasePercent(group, props);
	RoleSuitManager::Instance()->CalcProperty(cache, rid, group);
	TitleManager::Instance()->CalcProperty(cache, rid, group);
	TreasureManager::Instance()->CalcProperty(cache, group);

	return true;
}

uint32_t UserManager::GetGoldDiscount(uint32_t gold) {
	if (gold > 1000) {
		return static_cast<float>(gold) *0.9f;
	}
	return gold;
}

void UserManager::GetPlayerMsg(const UserCache &data, dbs::TPlayer *msg) {
	msg->clear();
	map<byte, DataRole>::const_iterator itr = data.role_.begin();
	for (; itr != data.role_.end(); ++itr) {
		if (itr->second.id != data.base_.main_role) {
			continue;
		}
		const DataRole& role = itr->second;
		msg->playerId_ = data.uid_;
		msg->sex_ = role.sex;
		msg->name_ = role.name;
		msg->career_ = role.career;
		msg->combat_ = role.combat;
		msg->maxCombat_ = role.combat;
		msg->level_ = data.base_.level;
		msg->exp_ = data.base_.exp;
		msg->careerLevel_ = data.m_reinCarnInfo.reinCarnLevel;
		msg->offlineDt_ = data.base_.offline_time * 1000LL;
		msg->gameDt_ = LogicManager::SecOpenTime * 1000LL;
		msg->hangLevel_ = data.base_.hang;
		break;
	}
}
