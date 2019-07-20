/*
 * PurifyManager.cpp
 *
 *  Created on: 2019年7月3日
 *      Author: Administrator
 */

#include "PurifyManager.h"
#include "BattleInc.h"

PurifyManager::PurifyManager() {
}

PurifyManager::~PurifyManager() {
}

bool PurifyManager::CalcProperty(const UserCache &cache, byte rid,PropertySets &props) {
	PurifyCfgWrap cfg_wrap;
	list<DataForge>::const_iterator itr = cache.forge_.begin();
	for (; itr != cache.forge_.end(); ++itr) {
		if (itr->rid != rid) {
			continue;
		}
		if (!EquipsManager::Instance()->IsWear(cache, rid, itr->type)) {
			continue;
		}
		const CfgPurify::Purify& cfg = cfg_wrap.GetByLevel(itr->purify);
		// 0,1,2,5位置精炼时增加攻击力，其余精炼时增加生命和防御力
		// 每级增加攻击力50点，生命每级增加50*13.5，防御每级增加50/4点。
		if (itr->type == 3 || itr->type == 4 || itr->type == 6|| itr->type == 7) {
			props[1000].pui += floor(static_cast<float>( 50.0 * 13.5) * cfg.level());; // 生命值
			props[1002].pui += floor(static_cast<float>( 50.0 / 4.0) * cfg.level()); // 防御值
		}else {
			props[1001].pui += floor(50 * cfg.level()); // 攻击
		}
	}
//	PropertyCfg::setProps(cache.uid_, rid, props, "purify");
	PropertyCfg::showProps(cache.uid_, rid, props, "purify");


	return true;
}

// 消息处理
int PurifyManager::Process(uint32_t uid, logins::SPurifyReq *req,logins::SPurifyResp *resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}

	dbs::TPlayerEquip msg; // 消息结构
	PurifyCfgWrap cfg_wrap; // 读取配置类的对象
	string code;
	uint32_t purify = 0;
	bool is_new = false;
	bool cost_error = false;
	bool is_chg = false;

	DataForge item; // 数据库类的对象
	item.uid = uid; // 玩家UID
	item.rid = req->roleId_; // 客户端发来的 角色id
	UpdateManager::Instance()->SetCode(UC_EquipPurify);  // ??????????
	list<DataForge>::iterator fItr;  // list 迭代器  调试打印 p *fItr
	vector<int32_t>::iterator itr = req->equipType_.begin();
	for (; itr != req->equipType_.end(); ++itr) {
		cost_error = false;
		item.type = *itr;  //装备类型
		fItr = find(cache.forge_.begin(), cache.forge_.end(), item); // 在玩家数据中通过 uid roleId equipType 找到对应的那条
		// 第一次
		if (fItr == cache.forge_.end()) {
			purify = 0;
			is_new = true;
		} else {
			purify = fItr->purify; // 通过迭代器直接取到精炼数据
			is_new = false;
		}

		code.clear();
		String::Format(code, "equip_purify_%u_%u", *itr, purify + 1);
		const CfgPurify::Purify&cfg = cfg_wrap.GetByLevel(purify + 1); // 通过当前精炼等级获取下一级的配置
		for (int i = 0; i < cfg.useprops_size(); ++i) {
			// 使用道具
			if (!UserManager::Instance()->UseItem(uid, cfg.useprops(i).item(),
					cfg.useprops(i).num(), code)) {
				cost_error = true;
				break;
			}
		}
		if (cost_error) {
			continue;
		}
		// 第一次需要初始化的
		if (is_new) {
			DataForge data;
			data.uid = uid;
			data.rid = req->roleId_;
			data.type = *itr;
			data.purify = 1;
			DataForgeManager::Instance()->Add(data); // 向数据库中写入数据
			cache.forge_.push_back(data);
			ForgeManager::Instance()->FormatMsg(data, msg);
			resp->equip_.push_back(msg);
			is_chg = true;
		}
		// 将 purify 属性写入数据库
		else {
			fItr->purify += 1;
			DataForgeManager::Instance()->Set(*fItr);
			ForgeManager::Instance()->FormatMsg(*fItr, msg); // 组装消息结构
			resp->equip_.push_back(msg);
			is_chg = true;
		}
	}

	// 触发UserManagerz 中的属性增加
	if (is_chg) {
		PropertyManager::Instance()->AddUser(uid);
	}
	//日常活动同步
	ActivityManager::Instance()->SyncActivity(cache, PURIFY_ACTIVITY_TYPE);
	LogicManager::Instance()->AddSync(CMD_DAILY_ACTIVITY_INFO);
	return 0;
}
