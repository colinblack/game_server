/*
 * HeroCfgWrap.cpp
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */

#include "HeroCfgWrap.h"
#include "ConfigManager.h"

HeroCfgWrap::HeroCfgWrap()
	: cfg_hero_(ConfigManager::Instance()->heroInfo.m_config)
	, cfg_attack_(ConfigManager::Instance()->heroAttacks.m_config)
{

}

const Hero::HeroInfoList& HeroCfgWrap::HeroCfg() const
{
	return cfg_hero_;
}

const HeroAttackConfig::Attack& HeroCfgWrap::HeroAttack() const
{
	return cfg_attack_;
}

const HeroAttackConfig::AttackBase& HeroCfgWrap::AttackBase(unsigned level) const
{
	for (int i = 0; i < cfg_attack_.attacks_size(); ++i)
	{
		if (cfg_attack_.attacks(i).hlevel() == level)
		{
			return cfg_attack_.attacks(i);
		}
	}

	error_log("cfg_error. hero_level: %d", level);
	throw std::runtime_error("not_config_hero_level_attribute");
}

const Hero::HeroInfo& HeroCfgWrap::HeroInfoCfg(unsigned hero_id) const
{
	if (!ConfigManager::Instance()->m_heroInfo.count(hero_id))
	{
		throw std::runtime_error("not_config_hero");
	}

	return ConfigManager::Instance()->GetHero(hero_id);
}

bool HeroCfgWrap::isHeroExistCfg(unsigned hero_id)
{
	if (!ConfigManager::Instance()->m_heroInfo.count(hero_id))
	{
		return false;
	}

	return true;
}

uint64_t HeroCfgWrap::GetHeroMaxExpByLevel(unsigned level)
{
	if (level >= cfg_hero_.heroexp_size())
	{
		level = cfg_hero_.heroexp_size();
		return cfg_hero_.heroexp(level - 1);
	}

	return cfg_hero_.heroexp(level) - 1;
}

//统， 勇
unsigned HeroCfgWrap::GetHeroThain(const Hero::HeroInfo& hero_info)
{
	if (hero_info.born_size() == 0)
	{
		error_log("cfg_hero_thain_error. hero: %d", hero_info.heroid());
		throw std::runtime_error("hero_thain_cfg_error");
	}
	return hero_info.born(0);
}

// 勇
unsigned HeroCfgWrap::GetHeroNerve(const Hero::HeroInfo& hero_info)
{
	if (hero_info.born_size() < 2)
	{
		error_log("cfg_hero_thain_error. hero: %d", hero_info.heroid());
		throw std::runtime_error("hero_thain_cfg_error");
	}

	return hero_info.born(1);
}

void  HeroCfgWrap::GetHeroFightAttr(unsigned hero_id, unsigned h_lvl, unsigned s_lvl, HeroFightAttr& result)
{
	result.Clear();

	//攻击，防御，血量
	result.SetAttr(DemoHeroProperty_hp,  GetAttribute(h_lvl, s_lvl, 2));
	result.SetAttr(DemoHeroProperty_attack, GetAttribute(h_lvl, s_lvl, 0));
	result.SetAttr(DemoHeroProperty_defend, GetAttribute(h_lvl, s_lvl, 1));

	//统和勇
	const Hero::HeroInfo& heroInfo = HeroInfoCfg(hero_id);
	result.SetAttr(DemoHeroProperty_int,  GetHeroThain(heroInfo));
	result.SetAttr(DemoHeroProperty_str,  GetHeroNerve(heroInfo));
}

const HeroAttackConfig::Soldier& HeroCfgWrap::Soldier(unsigned h_lvl, unsigned s_lvl) const
{
	const HeroAttackConfig::AttackBase& attackBase = AttackBase(h_lvl);
	for (int i = 0; i < attackBase.soldiers_size(); ++i)
	{
		if (attackBase.soldiers(i).slevel() == s_lvl)
		{
			return attackBase.soldiers(i);
		}
	}

	error_log("cfg_error. soldier_level: %d", s_lvl);
	throw std::runtime_error("not_config_soldier_level_attribute");
}

float HeroCfgWrap::GetRecruitRateFactor(unsigned s_lvl)
{
	if (s_lvl < 1 || s_lvl > cfg_hero_.recruit_rate_factor_size())
	{
		error_log("soldires_level_out_cfg. s_lvl:%u", s_lvl);
		std::runtime_error("soldires_level_out_cfg");
	}

	return cfg_hero_.recruit_rate_factor(s_lvl - 1);
}

float HeroCfgWrap::GetRecruitCostFactor(unsigned s_lvl)
{
	if (s_lvl < 1 || s_lvl > cfg_hero_.recruit_cost_factor_size())
	{
		error_log("soldires_level_out_cfg. s_lvl:%u", s_lvl);
		std::runtime_error("soldires_level_out_cfg");
	}

	return cfg_hero_.recruit_cost_factor(s_lvl - 1);
}

unsigned HeroCfgWrap::GetAttribute(unsigned h_lvl, unsigned s_lvl, int index) const
{
	const HeroAttackConfig::Soldier&  soldierCfg = Soldier(h_lvl, s_lvl);
	if (index < 0 || index > soldierCfg.property_size())
	{
		error_log("cfg_error. unknow_config_attribute h_lvl:%d, s_lvl:%d, index:%d"
				,h_lvl, s_lvl, index);
		throw std::runtime_error("unknow_config_attribute");
	}

	return soldierCfg.property(index);
}


unsigned HeroCfgWrap::HeroAttack(unsigned h_lvl, unsigned s_lvl)
{
	return GetAttribute(h_lvl, s_lvl, 0);
}

unsigned HeroCfgWrap::HeroDefence(unsigned h_lvl, unsigned s_lvl)
{
	return GetAttribute(h_lvl, s_lvl, 1);
}

unsigned HeroCfgWrap::HeroBloodVol(unsigned h_lvl, unsigned s_lvl)
{
	return GetAttribute(h_lvl, s_lvl, 2);
}



