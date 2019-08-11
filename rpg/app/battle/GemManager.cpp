/*
 * GemManager.cpp
 *
 *  Created on: 2019年8月6日
 *      Author: memory
 */

#include "GemManager.h"
#include "BattleInc.h"

GemManager::GemManager() {
}

GemManager::~GemManager() {
}

bool GemManager::FormatMsg(const DataForge &data, dbs::TPlayerEquip &msg) {
	msg.clear();
	msg.playerId_ = data.uid;
	msg.roleId_ = data.rid;
	msg.subtype_ = data.type;
	msg.strength_ = data.strength;
	msg.purify_ = data.purify;
	msg.zhulingLevel_ = data.zhulingLevel;
	msg.zhulingAdvance_ = data.zhulingAdvance;
	msg.extend_ = data.extend;
	msg.extendEx_ = "{}";
	return true;
}

// 将map转化为json 字符串  添加到已有的字符串中 没有就直接添加 gemUidSlot< gemSlot : Ud >
string GemManager::updateExtend(string &str, map<int32_t, int64_t> gemUidSlot,uint32_t uid,uint32_t rid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	static Json::Reader reader;
	static Json::FastWriter writer;
	Json::Value value;
	reader.parse(str, value);
	map<int32_t, int64_t> gemUidSlotAll;



	map<int32_t, int64_t>::iterator it = gemUidSlot.begin();
	for (; it != gemUidSlot.end(); ++it) {
		uint32_t ud = (uint32_t) it->second;// 把客户端发来的这个卸掉
		DataEquip& data = cache.equip_[ud]; // 获取装备数据
		gemUidSlotAll.insert(make_pair(it->first,it->second));
		// 更新消息265 - 271
		UpdateManager::Instance()->SetCode(UC_GemEmbed); // updateCode
		UserManager::Instance()->UseItem(uid, data.id, 1, "gem ");
		UpdateManager::Instance()->UpdateBagNow(cache.uid_); // 265-271

		map<uint32_t, DataEquip>::iterator it1 = cache.equip_.begin();
		for(; it1 != cache.equip_.end(); ++it1) {
			if(it1->second.bag == (BAG_ROLE_GEM + rid) && it1->second.id == data.id) {
				break;
			}
		}
		if(it1 == cache.equip_.end()) {
			UserManager::Instance()->AddItem(uid, data.id, 1, "gem",BAG_ROLE_GEM + rid);
		}else {
			DataEquip& wear = it1->second;
			wear.bag = (BAG_ROLE_GEM + rid);
			wear.num++;
			DataEquipManager::Instance()->Set(wear); // 改变下数据库中装备背包状态
			UpdateManager::Instance()->Bag(uid, -1, wear); // operType_
			UpdateManager::Instance()->UpdateBagNow(cache.uid_); // 265-271
		}
	}

	if (value.isMember("slotGems")) {
		// 先把str中的拿出来，加入到gemUidSlotAll中
		for (int32_t gemSlot = 1; gemSlot <= 4; ++gemSlot) {
			if ( value["slotGems"].isMember(String::i2s(gemSlot))) {
				uint32_t itemId = value["slotGems"][String::i2s(gemSlot)].asUInt();
				map<uint32_t, DataEquip>::iterator itrr = cache.equip_.begin();
				for(; itrr != cache.equip_.end(); ++itrr) {
					if(itrr->second.bag == (BAG_ROLE_GEM + rid) && itrr->second.id == itemId) {
						break;
					}
				}
				int64_t ud = itrr->first;
				gemUidSlotAll.insert(make_pair(gemSlot,ud));
			}
		}
	} else {
		value = Json::Value(Json::objectValue);
	}

	// 将所有穿戴的穿戴上
	map<int32_t, int64_t>::iterator itrr = gemUidSlotAll.begin();
	for (; itrr != gemUidSlotAll.end(); ++itrr) {
		uint32_t ud = (uint32_t) itrr->second;// 把客户端发来的这个卸掉
		DataEquip& data = cache.equip_[ud]; // 获取装备数据
		value["slotGems"][String::i2s(itrr->first)] = data.id;
		value["ra"] = Json::Value(Json::arrayValue);
//		value["ra"].append(0);
		str = writer.write(value);
	}

	return str;
}

// 升级相关处理  传来的是孔位数组 gemSlot[2,3]
string GemManager::upgrateExtend(string &str, vector<int32_t> gemSlot,uint32_t uid,uint32_t rid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	static Json::Reader reader;
	static Json::FastWriter writer;
	Json::Value value;
	if (value.isMember("slotGems")) {
		reader.parse(str, value);
	} else {
		value = Json::Value(Json::objectValue);
	}
	vector<int32_t>::iterator it = gemSlot.begin();
	for (; it != gemSlot.end(); ++it) {
		// 合成 ：TODO
		// 合成的时候 将低级删除  将高级合成后 改变
		uint32_t ud1 = 0;// 升级前 当前孔位宝石ud

		// 获取升级后的宝石 的 ud
		uint32_t ud2 = 0;// TODO
		DataEquip& data1 = cache.equip_[ud1]; // 获取装备孔位
		DataEquip& data2 = cache.equip_[ud2]; // 获取装备孔位
		UpdateManager::Instance()->DelBag(cache.uid_,data1.num,data1);
		UpdateManager::Instance()->SetCode(UC_ItemCompound); // updateCode
		UpdateManager::Instance()->ChgBag(cache.uid_, BAG_ALL, BAG_ROLE_GEM + rid, data2);
		UpdateManager::Instance()->UpdateBagNow(cache.uid_); // 265-271
	}
	str = writer.write(value);
	return str;
}

// 将map转化为json 字符串   卸下相关卡槽的宝石  gemSlot:2 卡槽位
string GemManager::DeleteExtend(string &str, int32_t gemSlot,uint32_t uid,uint32_t rid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	static Json::Reader reader;
	static Json::FastWriter writer;
	Json::Value value;
	reader.parse(str, value);
	uint32_t itemId = value["slotGems"][String::i2s(gemSlot)].asUInt();

	if(value.isMember("slotGems") && value["slotGems"].isMember(String::i2s(gemSlot))){
		value["slotGems"].removeMember(String::i2s(gemSlot));
		value["ra"] = Json::Value(Json::arrayValue);
	}


	str = writer.write(value);
	// 更新消息265 - 271
	map<uint32_t, DataEquip>::iterator it = cache.equip_.begin();
	for(; it != cache.equip_.end(); ++it) {
		if(it->second.bag == (BAG_ROLE_GEM + rid) && it->second.id == itemId ) {
			break;
		}
	}
	UpdateManager::Instance()->SetCode(UC_MoveItem); // updateCode
	useGemItem(cache, it->second, 1, "GemRemove");

	// 更新消息265 - 271
	UserManager::Instance()->AddItem(uid, itemId, 1, "gem",BAG_ALL);
	UpdateManager::Instance()->UpdateBagNow(cache.uid_); // 265-271

	str = writer.write(value);
	return str;
}

// 将字符串转换为vector
bool GemManager::String2Vector(vector<uint32_t> gemItemIdSlot, string str) {
	Json::Value value = Json::Value(Json::objectValue);
	Json::Reader reader;
	if (!str.empty() && !reader.parse(str, value)) {
		error_log("parse slotGems extend error ");
		return false;
	}

	for (uint32_t var = 0; var < 8; ++var) {
		if (value.isMember("slotGems") && value["slotGems"].isMember(String::i2s(var))) {
			uint32_t ItemId_ = value["slotGems"][String::i2s(var)].asInt();
			gemItemIdSlot.push_back(ItemId_);
		}
	}
	return true;
}

//1037 宝石 镶嵌/替换/一键替换
bool GemManager::Process(uint32_t uid, logins::CEmbedGemReq* req,logins::SEmbedGemResp* resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性 - 是否有该roleId
	if (!cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	// 循环遍历 客户端发来的map  gemUidSlot = {2: 16388, 3: 16388, 4: 16388} 在数据库中看是否存在 ，存在就带上宝石,并且给前端回消息
	map<int32_t, int64_t>::iterator it = req->gemUidSlot_.begin();
	for (; it != req->gemUidSlot_.end(); ++it) {
		if (0 == cache.equip_.count(it->second)) {
			error_log("equip uid:%d not exist", it->second);
			return R_ERROR;
		}
	}

	//先卸下：后装配


	// 更新数据库中宝石穿戴
	list<DataForge>::iterator itr = cache.forge_.begin();
	for (; itr != cache.forge_.end(); ++itr) {
		if (itr->rid != req->roleId_) {
			continue;
		}
		// 通过前端发来的数据类型，更新数据库，并且从数据库中获取 equipType(比如是靴子)
		if (req->equipType_ == itr->type) {
			DataForge & dataForge = *itr;

			dataForge.extend = updateExtend(dataForge.extend, req->gemUidSlot_,uid,req->roleId_);// 更新消息265-271
			DataForgeManager::Instance()->Set(dataForge); // 前提是一定激活了八个部位
			FormatMsg(dataForge,resp->tPlayerEquip_);
		} else {
			error_log("equipType :%d not exist", itr->type);
		}
	}

	// 更新战斗力
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}

// 1056 宝石 卸下
bool GemManager::Process(uint32_t uid, logins::CRemoveGemReq* req,logins::SRemoveGemResp* resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}

	// 更新数据库中宝石穿戴
	list<DataForge>::iterator itr = cache.forge_.begin();
	for (; itr != cache.forge_.end(); ++itr) {
		if (itr->rid != req->roleId_) {
			continue;
		}
		// 通过前端发来的数据类型，更新数据库，并且从数据库中获取 equipType(比如是靴子)
		if (req->equipType_ == itr->type) {
			DataForge & dataForge = *itr;
			dataForge.extend = DeleteExtend(dataForge.extend, req->gemSlot_,uid,req->roleId_);// 更新消息265-271
			DataForgeManager::Instance()->Set(dataForge); // 前提是一定激活了八个部位
			FormatMsg(dataForge,resp->tPlayerEquip_);
		} else {
			error_log("equipType :%d not exist", itr->type);
		}
	}

	// 更新战斗力
	PropertyManager::Instance()->AddUser(uid);
	return 0;
}

// 1057 激活宝石目标
bool GemManager::Process(uint32_t uid, logins::CctivateGemTargetReq* req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	return 0;
}

// 1120 宝石 升级/一键升级
bool GemManager::Process(uint32_t uid, logins::CUpgradeGemReq* req,logins::SUpgradeGemResp* resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	// 1、服务器收到客户端的消息后  1、去数据库验证合法性 - 是否有该roleId
	if (!cache.role_.count(req->roleId_)) {
		error_log("role_id:%d not exist", req->roleId_);
		return R_ERROR;
	}
	// 循环遍历 客户端发来的map  gemUidSlot = {2: 16388, 3: 16388, 4: 16388} 在数据库中看是否存在 ，存在就带上宝石,并且给前端回消息
	vector<int32_t>::iterator it = req->gemSlot_.begin();
	for (; it != req->gemSlot_.end(); ++it) {
		if (0 == cache.equip_.count(*it)) {
			error_log("equip uid:%d not exist", *it);
			return R_ERROR;
		}
	}

	// 更新
	list<DataForge>::iterator itr = cache.forge_.begin();
	for (; itr != cache.forge_.end(); ++itr) {
		if (itr->rid != req->roleId_) {
			continue;
		}
		// 通过前端发来的数据类型，更新数据库，并且从数据库中获取 equipType(比如是靴子)
		if (req->equipType_ == itr->type) {
			DataForge & dataForge = *itr;
			dataForge.extend = upgrateExtend(dataForge.extend, req->gemSlot_,uid,req->roleId_);// 更新消息265-271
			DataForgeManager::Instance()->Set(dataForge); // 前提是一定激活了八个部位
			FormatMsg(dataForge,resp->tPlayerEquip_);
		} else {
			error_log("equipType :%d not exist", itr->type);
		}
	}

	// 更新战斗力
	PropertyManager::Instance()->AddUser(uid);

	return 0;
}

// 计算战斗力
bool GemManager::CalcProperty(const UserCache &cache, byte rid,PropertySets &props) {
	// 从数据库缓存中拿到时装-套装的数据
	list<DataForge>::const_iterator itr = cache.forge_.begin();
	for (; itr != cache.forge_.end(); ++itr) {
		if (itr->rid != rid) {
			continue;
		}

		// 获取道具数据 从forge数据库中拿出 extend的string 转化为 json 拿出该条数据中所拥有的道具UID，再计算战斗力
		vector<uint32_t> gemItemIdSlot;
		if (!itr->extend.empty()) {
			String2Vector(gemItemIdSlot, itr->extend);
			vector<uint32_t>::const_iterator it = gemItemIdSlot.begin();
			for (; it != gemItemIdSlot.end(); ++it) {
				const CfgItem::Equip& cfg = ItemCfgWrap().GetEquip( (uint32_t)*it );
				PropertyCfg::setProps(cfg.attr(), 1.0, props);
			}
		}
	}
	PropertyCfg::showProps(cache.uid_, rid, props, "Gem Changed");
	return true;
}

bool GemManager::useGemItem(UserCache& cache, DataEquip equip, uint32_t cost, const string &code) {
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
