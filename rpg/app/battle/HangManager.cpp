/*
 * HangManager.cpp
 *
 *  Created on: 2019年6月12日
 *      Author: Administrator
 */

#include "HangManager.h"
#include "BattleInc.h"

HangManager::HangManager() {
}

int HangManager::Process(uint32_t uid, logins::SBatchFightResultReq *req, logins::SBatchFightResultResp *resp) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}

	const CfgHang::Hang &hang = HangCfgWrap().Get(cache.base_.hang);

	resp->canRefreshElite_ = Math::GetRandomInt(100) < 80 ? true : false;

	MonsterCfgWrap cfg_wrap;
	uint32_t add_exp = 0;
	map<int32_t, int32_t>::iterator itr = req->monsters_.begin();
	for (; itr != req->monsters_.end(); ++itr) {
		const CfgMonster::Monster &cfg = cfg_wrap.Get(itr->first);
		add_exp += cfg.exp();
		if (cache.base_.hang_power < hang.power()) {
			if (cache.base_.hang_power + itr->second > hang.power()) {
				UserManager::Instance()->AddHangPower(cache, hang.power() - cache.base_.hang_power);
			} else {
				UserManager::Instance()->AddHangPower(cache, itr->second);
			}
		}
		MissionManager::Instance()->OnKillHangMonster(uid, itr->first, itr->second);
	}

	if (add_exp > 0) {
		UserManager::Instance()->AddExp(uid, add_exp);
	}

	MissionManager::Instance()->TestCheck(uid);
	return R_SUCCESS;
}

int HangManager::Process(uint32_t uid, logins::SFightResultReq *req, logins::SBatchFightResultResp *resp) {
	UpdateManager::Instance()->SetCode(UC_Hang);
	resp->canRefreshElite_ = Math::GetRandomInt(100) < 80 ? true : false;
	MonsterDrop(uid, req->monsterId_, req->killPoint_);
	MissionManager::Instance()->OnKillHangMonster(uid, req->monsterId_, 1);
	debug_log("uid=%u monster=%u", uid, req->monsterId_);
	return R_SUCCESS;
}

int HangManager::Process(uint32_t uid, logins::SHangChallengeBoss *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}

	if (!req->resetPoints_.empty()) {
		pHuman->setPos(req->resetPoints_.begin()->x, req->resetPoints_.begin()->y);
	}

	HangCfgWrap hangCfgWrap;
	MonsterCfgWrap monsterCfgWarp;

	const CfgHang::Plan &plan = hangCfgWrap.GetPlan(cache.base_.hang);

	Map *pMap = MapManager::Instance()->getMapInstance(0, plan.mapid());
	if (pMap == NULL) {
		error_log("get map error mid=%u", plan.mapid());
		return R_ERROR;
	}

	const CfgHang::Hang &hang = hangCfgWrap.Get(cache.base_.hang);
	const CfgMonster::Plan &monster_plan = monsterCfgWarp.GetPlan(hang.plan());
	const CfgMap::Point &point = SceneCfgWrap().GetBossPoint(monster_plan.mapid(), monster_plan.plan());

	if (!UserManager::Instance()->UseHangPower(cache, hang.power())) {
		error_log("power not enough hold=%u need=%u", cache.base_.hang_power, hang.power());
		return R_ERROR;
	}

	Point bpos;
	bpos.x = point.x() * pMap->getGridWidth() + pMap->getGridWidth() / 2;
	bpos.y = point.y() * pMap->getGridHeight() + pMap->getGridHeight() / 2;

	StdMonster *boss = new StdMonster();

	boss->init(monster_plan.boss(), 0, plan.mapid(), bpos);
	boss->setBelong(uid);
	boss->setNeedRecove(false);
	boss->setForce(FORCE_HOSTILE);

	if (!boss->recove()) {
		delete boss;
		return R_ERROR;
	}

	ZhanLingManager::Instance()->resetNuQi(uid);

	m_boss[uid] = monster_plan.boss();

	msgs::SHangLevelBoss msg;
	msg.bossId_ = monster_plan.boss();
	msg.point_.x = bpos.x;
	msg.point_.y = bpos.y;

	LogicManager::Instance()->SendMsg(uid, CMD_CREATE_HANG_LEVEL_BOSS, &msg);

	return R_SUCCESS;
}

bool HangManager::OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos) {
	map<uint32_t, uint32_t>::iterator itr = m_boss.find(uid);
	if (itr == m_boss.end()) {
		return false;
	}
	if (itr->second != monster_id) {
		return false;
	}
	m_boss.erase(uid);
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	cache.base_.hang += 1;
	DataBaseManager::Instance()->Set(cache.base_);

	UpdateManager::Instance()->SetCode(UC_AddDrop);

	MonsterDrop(uid, monster_id, diePos);

	msgs::SHangBossResult msg;
	msg.result_ = 1;
	msg.newHangLevel_ = cache.base_.hang;

	LogicManager::Instance()->SendMsg(uid, CMD_HANG_LEVEL_BOSS_RESULT, &msg);

	MissionManager::Instance()->OnKillHangMonster(uid, monster_id, 1);
	MissionManager::Instance()->OnHangLevel(uid);

	Human *pHuame = MapManager::Instance()->getHuman(uid);
	if (pHuame != NULL) {
		pHuame->doRecover();
	}

	return true;
}

bool HangManager::OnHumanDie(uint32_t uid) {
	map<uint32_t, uint32_t>::iterator itr = m_boss.find(uid);
	if (itr == m_boss.end()) {
		return false;
	}
	m_boss.erase(uid);

	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	msgs::SHangBossResult msg;
	msg.result_ = 0;
	msg.newHangLevel_ = cache.base_.hang;
	LogicManager::Instance()->SendMsg(uid, CMD_HANG_LEVEL_BOSS_RESULT, &msg);
	return true;
}

bool HangManager::MonsterDrop(uint32_t uid, uint32_t monster_id, const Point &diePos) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return false;
	}
	try {
		const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(monster_id);
		const CfgMonster::Monster &cfg = MonsterCfgWrap().Get(monster_id);

		Award reward;
		reward.Random(drop_cfg.randomreward(), drop_cfg.randomcount());

		msgs::SPlayerAutoDrop msg;
		msg.belongEntityId_ = pHuman->getEntityMsg();
		msg.dropPoint_.x = diePos.x;
		msg.dropPoint_.y = diePos.y;
		msg.type_ = 0;
		reward.Get(msg.items_);

		if (!reward.Format(drop_cfg.fixedreward(), 1)) {
			error_log("parse reward error");
			return false;
		}

		msgs::SItemAmount msg_item;
		for (int i = 0; i < drop_cfg.fixedreward_size(); ++i) {
			msg_item.itemCode_ = drop_cfg.fixedreward(i).item();
			msg_item.itemNum_ = drop_cfg.fixedreward(i).num();
			msg.items_.push_back(msg_item);
		}

		reward.Add(MONEY_EXP, cfg.exp());

		string code;
		String::Format(code, "hang_boss_%u", monster_id);
		if (!UserManager::Instance()->Reward(uid, reward, code)) {
			return false;
		}

		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_AUTO_DROP_BAG, &msg);
		return true;
	} catch (...) {
		return false;
	}
}

bool HangManager::GetHangMap(uint16_t hang, uint32_t &des_map, Point &des_pos) {
	HangCfgWrap hangCfgWrap;
	MonsterCfgWrap monsterCfgWarp;
	SceneCfgWrap sceneCfgWrap;
	const CfgHang::Hang &curr_hang_cfg = hangCfgWrap.Get(hang);
	const CfgMonster::Plan &curr_plan = monsterCfgWarp.GetPlan(curr_hang_cfg.plan());
	if (hang > 1) {
		const CfgHang::Hang &last_hang_cfg = hangCfgWrap.Get(hang - 1);
		const CfgMonster::Plan &last_plan = monsterCfgWarp.GetPlan(last_hang_cfg.plan());
		if (last_plan.mapid() != curr_plan.mapid()) {
			const CfgMap::Scene &cfg = sceneCfgWrap.Get(last_plan.mapid());
			for (int i = 0; i < cfg.passpoints_size(); ++i) {
				for (int j = 0; j < cfg.passpoints(i).passto_size(); ++j) {
					if (curr_plan.mapid() != cfg.passpoints(i).passto(j).mapid()) {
						continue;
					}
					des_pos.x = cfg.passpoints(i).passto(j).topoint().x();
					des_pos.y = cfg.passpoints(i).passto(j).topoint().y();
					des_map = curr_plan.mapid();
					return true;
				}
			}
		} else {
			const CfgMap::Point &point = sceneCfgWrap.GetBossPoint(last_plan.mapid(), last_plan.plan());
			Map *pMap = MapManager::Instance()->getMapInstance(0, last_plan.mapid());
			if (pMap == NULL) {
				return false;
			}
			des_pos.x = pMap->getGridWidth() * point.x();
			des_pos.y = pMap->getGridHeight() * point.y();
			des_map = last_plan.mapid();
			return true;
		}
	} else {
		des_pos.x = DEFAULT_HANG_X;
		des_pos.y = DEFAULT_HANG_Y;
		des_map = DEFAULT_HANG_MAP;
		return true;
	}
	return false;
}

bool HangManager::AfterLogin(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	OfflineReward(uid, cache.base_.hang, cache.base_.offline_time);
	return true;
}

bool HangManager::OfflineReward(uint32_t uid, uint32_t hang, uint32_t offlineTs) {
	uint32_t ts = 0, ts1 = 0, ts2 = 0;
	if (Time::GetGlobalTime() > offlineTs) {
		ts = Time::GetGlobalTime() - offlineTs;
	}
	if (ts < 120) {
		return false;
	}

	if (ts > 28800) {
		ts1 = 28800;
		ts2 = ts - 28800 > 43200 ? 43200 : ts - 28800;
	} else {
		ts1 = ts;
	}

	msgs::SHangOfflineReward msg;
	msg.clear();
	Award reward;
	HangCfgWrap wrap;
	ItemCfgWrap item_wrap;
	uint32_t drop_id = wrap.GetOnlineRewrad(hang);
	const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(drop_id);
	const CfgHang::Hang &hang_cfg = wrap.Get(hang);

	Award equips;
	Award temp;
	uint32_t equip_count = ts1 / 30 + ts2 / 30 * 0.8f;
	for (uint32_t i = 0; i < equip_count; ++i) {
		if (i % 120 == 0) {
			temp.Clear();
			temp.Random(drop_cfg.randomreward(), drop_cfg.randomcount());
			temp.Format(drop_cfg.fixedreward(), 1);
		}
		equips += temp;
	}

	int decompose = 0;
	map<uint32_t, uint32_t>::const_iterator itr = equips.Data().begin();
	for (; itr != equips.Data().end(); ++itr) {
		const CfgItem::Equip &equip_cfg = item_wrap.GetEquip(itr->first);
		reward.Format(equip_cfg.smeltaward(), itr->second);
		decompose += itr->second;
	}
	for (itr = reward.Data().begin(); itr != reward.Data().end(); ++itr) {
		msg.rewards_[itr->first] = itr->second;
	}

	float coin_speed = static_cast<float>(hang_cfg.coin()) / 3600.0f;
	float exp_speed = static_cast<float>(hang_cfg.exp()) / 3600.0f;

	uint32_t r_coin = coin_speed * ts1 + coin_speed * ts2 * 0.8;
	uint32_t r_exp = exp_speed * ts1 + coin_speed * ts2 * 0.8;

	reward.Add(MONEY_COIN, r_coin);
	reward.Add(MONEY_EXP, r_exp);

	UpdateManager::Instance()->SetCode(UC_OfflineReward);
	string code;
	String::Format(code, "hang_offline_reward_%u", ts);
	if (!UserManager::Instance()->Reward(uid, reward, code)) {
		return false;
	}

	msg.coin_ = r_coin;
	msg.exp_ = r_exp;
	msg.offlineTime_ = ts;
	msg.decomposeNum_ = decompose;

	LogicManager::Instance()->SendMsg(uid, CMD_HANG_OFFLINE_REWARD, &msg);

	return true;
}
