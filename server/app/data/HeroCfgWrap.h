/*
 * HeroCfgWrap.h
 *
 *  Created on: 2016-9-9
 *      Author: dawx62fac
 */

#ifndef HEROCFGWRAP_H_
#define HEROCFGWRAP_H_

//#include "ConfigInc.h"
#include "DataInc.h"

class HeroCfgWrap
{
public:
	HeroCfgWrap();

	const Hero::HeroInfoList& HeroCfg() const;
	const HeroAttackConfig::Attack& HeroAttack() const;

	const Hero::HeroInfo& HeroInfoCfg(unsigned hero_id) const;

	bool isHeroExistCfg(unsigned hero_id);

	uint64_t GetHeroMaxExpByLevel(unsigned level);

	const HeroAttackConfig::AttackBase& AttackBase(unsigned level) const;
	const HeroAttackConfig::Soldier& Soldier(unsigned h_lvl, unsigned s_lvl) const;

	void  GetHeroFightAttr(unsigned hero_id, unsigned h_lvl, unsigned s_lvl, HeroFightAttr& attr);
	/**
	 * 获取血量
	 */
	unsigned HeroBloodVol(unsigned h_lvl, unsigned s_lvl);
	/**
	 * 攻击
	 */
	unsigned HeroAttack(unsigned h_lvl, unsigned s_lvl);
	/**
	 * 防御
	 */
	unsigned HeroDefence(unsigned h_lvl, unsigned s_lvl);

	//募兵相关系数
	float GetRecruitRateFactor(unsigned s_lvl);
	float GetRecruitCostFactor(unsigned s_lvl);


private:
	unsigned GetAttribute(unsigned h_lvl, unsigned s_lvl, int index) const;

	//统， 勇
	unsigned GetHeroThain(const Hero::HeroInfo& hero_info);
	unsigned GetHeroNerve(const Hero::HeroInfo& hero_info);


	const Hero::HeroInfoList& cfg_hero_;
	const HeroAttackConfig::Attack& cfg_attack_;
};


#endif /* HEROCFGWRAP_H_ */
