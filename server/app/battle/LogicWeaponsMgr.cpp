/*
 * LogicWeaponsMgr.cpp
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */


#include "ServerInc.h"

DBCWeaponWrap::DBCWeaponWrap(unsigned uid, unsigned id)
	: container_(DataWeaponMgr::Instance())
	, index_(container_->GetIndex(uid, id))
	, data_(container_->m_data->data[index_])
{
}

DBCWeaponWrap::DBCWeaponWrap(unsigned index)
	: container_(DataWeaponMgr::Instance())
	, index_(index)
	, data_(container_->m_data->data[index_])
{
}

const WeaponConfig::WeaponLvL& DBCWeaponWrap::CfgLVL() const
{
	return WeaponCfgWrap().LvL(data_.id, data_.level);
}

const WeaponConfig::WeaponItem& DBCWeaponWrap::CfgItem() const
{
	return WeaponCfgWrap().Item(data_.id);
}

void DBCWeaponWrap::Unlock()
{
	data_.Unlock();

	LogicHeroManager::Instance()->SyncUserHerosInfo(data_.uid);

	//todo 接入军工升级成就
    LogicAchievementManager::AchievementParam achievementparam;
	achievementparam.type = achievement_type_weaponlevel;

	LogicAchievementManager::Instance()->VerifyAchievementComplete(data_.uid, achievementparam);

	Save();
}

void DBCWeaponWrap::Cast(unsigned nMul)
{
	int16_t level = data_.level;
	data_.Cast(nMul);

	//兵器等级变化了
	if (data_.level > level)
	{
		LogicHeroManager::Instance()->SyncUserHerosInfo(data_.uid);

		//todo 接入军工升级成就
	    LogicAchievementManager::AchievementParam achievementparam;
		achievementparam.type = achievement_type_weaponlevel;

		LogicAchievementManager::Instance()->VerifyAchievementComplete(data_.uid, achievementparam);
	}

	Save();
}

void DBCWeaponWrap::SetLevel(unsigned level)
{
	data_.level = level;

	Save();
}

void DBCWeaponWrap::Reset()
{
	data_.level = 0;
	data_.cast = 0;

	Save();
}

/////////////////////////////////////////////////////////////////////////
DemoHeroProperty LogicWeaponsMgr::_Id2Property(unsigned id)
{
	int bit = id / 10;
	if (bit == 1)
	{
		return DemoHeroProperty_attack;
	}
	else if (bit == 2)
	{
		return DemoHeroProperty_defend;
	}
	else if (bit == 3)
	{
		return DemoHeroProperty_hp;
	}
	else
	{
		error_log("unknow_weapon_id: %d", id);
	}

	throw std::runtime_error("unknow_weapon_id");
}

void LogicWeaponsMgr::Online(unsigned uid)
{
	DataWeaponMgr::Instance()->Online(uid);

	LogicGemMgr::Instance()->Online(uid);
}

void LogicWeaponsMgr::Offline(unsigned uid)
{
	DataWeaponMgr::Instance()->Offline(uid);

	LogicGemMgr::Instance()->Offline(uid);
}

void LogicWeaponsMgr::Reset(unsigned uid)
{
	std::vector<unsigned> vIndexs;
	DataWeaponMgr::Instance()->GetIndexs(uid, vIndexs);

	for (size_t i = 0; i < vIndexs.size(); ++i)
	{
		DBCWeaponWrap(vIndexs[i]).Reset();
	}
}

void LogicWeaponsMgr::FullMessage(unsigned uid, User::Weapon* obj)
{
	std::vector<unsigned> vIndexs;
	DataWeaponMgr::Instance()->GetIndexs(uid, vIndexs);

	for (size_t i = 0; i < vIndexs.size(); ++i)
	{
		DBCWeaponWrap weapon(vIndexs[i]);

		weapon.Obj().FullMessage(obj->add_items());
	}
}

void LogicWeaponsMgr::SetBotPlayerData(unsigned uid, const BotConfig::BotPlayer* obj)
{
	if (NULL == obj) return ;

	for (int i = 0; i < obj->weapon_size(); i++)
	{
		DBCWeaponWrap(uid, obj->weapon(i).id()).SetLevel(obj->weapon(i).level());
	}
}

void LogicWeaponsMgr::GetHeroFightAttr(unsigned uid, HeroFightAttr& attr)
{
	attr.Clear();

	std::vector<unsigned> vIndexs;
	DataWeaponMgr::Instance()->GetIndexs(uid, vIndexs);

	for (size_t i = 0; i < vIndexs.size(); ++i)
	{
		DBCWeaponWrap weapon(vIndexs[i]);
		if (weapon.Obj().level > 0)
		{
			attr.AddAttr(_Id2Property(weapon.Obj().id), weapon.CfgLVL().value());
		}
	}
}

int LogicWeaponsMgr::Process(unsigned uid, ProtoWeapon::WeaponUnlockReq* req, ProtoWeapon::WeaponUnlockResp* resp)
{
	unsigned weapon_id = req->id();

	DBCWeaponWrap weaponWrap(uid, weapon_id);
	if (weaponWrap.Obj().IsNormal())
	{
		throw std::runtime_error("weapon_in_normal_status");
	}

	const WeaponConfig::WeaponItem& cfg = WeaponCfgWrap().Item(weapon_id);
	DBCUserBaseWrap user(uid);
	if (! user.IsPassNPC(cfg.unlock_pass(), cfg.pass_cnt()))
	{
		error_log("not_pass_specified_npc,uid=%u,id=%d,cnt:%d", uid, weapon_id, cfg.pass_cnt());
		throw std::runtime_error("not_pass_specified_npc");
	}

	std::string reason = "unlock_weapon_op";
	user.CostUserResource(cfg.unlock_coin(), cfg.unlock_wood(), 0, 0, reason);

	weaponWrap.Unlock();

	if (resp)
	{
		weaponWrap.Obj().FullMessage(resp->mutable_item());
		user.FullMessage(resp->mutable_resource());
	}

	return R_SUCCESS;
}

int LogicWeaponsMgr::Process(unsigned uid, ProtoWeapon::WeaponCastReq* req, ProtoWeapon::WeaponCastResp* resp)
{
	unsigned weapon_id = req->id();

	DBCWeaponWrap weaponWrap(uid, weapon_id);
	if (! weaponWrap.Obj().IsNormal())
	{
		throw std::runtime_error("weapon_need_unlock");
	}

	DBCUserBaseWrap user(uid);
	unsigned limit_lvl = LogicScienceMgr::Instance()->GetTypeValue(uid, S_TYPE_18, user.Obj().level);
	if (weaponWrap.Obj().level >= limit_lvl)
	{
		throw std::runtime_error("weapon_level_is_full");
	}

	//
	const WeaponConfig::WeaponLvL& lvlCfg = weaponWrap.CfgLVL();
	std::string reason = "weapon_cast_op";
	user.CostUserResource(0, 0, 0, lvlCfg.cost_iron(), reason);

	//
	std::vector<unsigned> vExtraAdd;
	user.VIPPower().WeaponProbAdd(vExtraAdd);
	unsigned nMul = GetWeaponCastMul(weapon_id, lvlCfg, vExtraAdd);//;

	weaponWrap.Cast(nMul);

	if (resp)
	{
		weaponWrap.Obj().FullMessage(resp->mutable_item());
		resp->set_multiple(nMul);
		user.FullMessage(resp->mutable_resource());
	}

	//提升军工外部接口
	UpgradeWeaponExternalInterface(uid, lvlCfg.cost_iron());

	return R_SUCCESS;
}

int LogicWeaponsMgr::UpgradeWeaponExternalInterface(unsigned uid, unsigned iron)
{
	//todo 接入每日任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_upgrade_weapon;
	dailymissionparam.subparam.push_back(iron);

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	return 0;
}

unsigned LogicWeaponsMgr::GetWeaponCastMul(unsigned id
		, const WeaponConfig::WeaponLvL& cfg
		, const std::vector<unsigned>& v_extra_prob)
{
	if (cfg.prob_size() != 4)
	{
		error_log("weapon_cast_cfg_error.id: %d, level: %d", id, cfg.lvl());
		throw std::runtime_error("weapon_cast_cfg_error");
	}

	const unsigned nMul[4] = {1, 2, 3, 5};
	int nTotal  = 0;
	for (int i = 0; i < cfg.prob_size(); i++)
	{
		if (v_extra_prob.size() > i)
		{
			nTotal += cfg.prob(i) + v_extra_prob[i];
		}
		else
		{
			nTotal += cfg.prob(i);
		}

	}

	int nRandomVal = Math::GetRandomInt(nTotal);
	for (int i = 0; i < cfg.prob_size(); i++)
	{
		int limit = (int)cfg.prob(i);
		if (v_extra_prob.size() > i)
		{
			limit += v_extra_prob[i];
		}

		if (nRandomVal < limit)
		{
			return nMul[i];
		}

		nRandomVal -= limit;
	}

	error_log("random_weapon_cast_mul_error. nRandomVal: %d", nRandomVal);
	throw std::runtime_error("random_weapon_cast_mul_error");
}
