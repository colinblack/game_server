/*
 * Formula.cpp
 *
 *  Created on: 2015年10月13日
 *      Author: asdf
 */

#include "Formula.h"
#include "Kernel.h"
#include "HeroConfig.h"
#include <algorithm>
using namespace std;

IBattleData::IBattleData(MapObject* pMo)
{
	ha = pMo->getHa();
	ma = pMo->getMa();
	hd = pMo->getHd();
	md = pMo->getMd();
	bp = pMo->getBp();
	bv = pMo->getBv();
	ebp = pMo->getEbp();
	ep = pMo->getEp();
	hep = pMo->getHep();
	mep = pMo->getMep();
	hr = pMo->getHr();
	ip = pMo->getIp();
	ta = pMo->getTa();
	he = pMo->getHe();
	ev = pMo->getEv();
	me = pMo->getMe();
	hm = 1; //攻击类型(物理攻击，魔法攻击)
	horm = 1; //损伤属性类型(减血，减魔)
	type = pMo->getType();
	level = pMo->getLevel();
	showIp = ip;
	showBp = bp;
	battleProf = pMo->getProf();
	levelRejectHurtRate = 0;
	critRate = 0;
	dodgeRate = 0;
	/*
	HeroConfig* hc = HeroConfig::getInstance();
	if (hc != NULL)
	{
		const HeroLevelProp* hlp = hc->getLevelProp(level);
		if (hlp != NULL)
		{
			levelRejectHurtRate = hlp->rejectHurtRate;
			critRate = hlp->critRate;
			dodgeRate = hlp->dodgeRate;
		}
		else
		{
			error_log("getLevelProp fail uid=%u race=%u ud=%u level=%u", pMo->getUid(), pMo->getRace(), pMo->getUD(), level);
		}
	}
	*/
}

bool CalDamage::draw100(int32_t num)
{
	return Math::GetRandomInt(100) < num;
}

uint32_t CalDamage::getDeductHp(MapObject* attacker, MapObject* defender, HurtPara& hurtPara)
{
	if (attacker == NULL)
	{
		debug_log("attacker_is_NULL");
		return 0;
	}
	if (defender == NULL)
	{
		debug_log("defender_is_NULL");
		return 0;
	}
	IBattleData bdAttacker(attacker);
	if (!bdAttacker.isInit())
	{
		error_log("init_attacker_fail");
		return 0;
	}
	//hurtPara.profHurtRate = hurtPara.isSkillHurt() ? 1.0 : attacker->getSkillSystem()->getProfHurtRate(defender);
	bdAttacker.ha *= hurtPara.hurtRate;
	IBattleData bdDefender(defender);
	if (!bdDefender.isInit())
	{
		error_log("init_defender_fail");
		return 0;
	}

	calHAttackHpByData(bdAttacker, bdDefender, hurtPara);

	return hurtPara.value;
}

/**
 * 物理攻击扣血
 * @param a 进攻方
 * @param b 防守方
 * @return
 *
 * 伤害=2*攻方物理攻击值*等级免伤系数（和防守方等级相关）/守方物理防御值*攻击方等级/（攻击方等级+防守方等级）
 */
void CalDamage::calHAttackHpByData(IBattleData& a, IBattleData& b, HurtPara& para, uint32_t factor)
{
	para.type = HEALTH_TYPE;
	if (para.isBuff)
	{
		para.value += para.hurtAdd;
		return;
	}
	para.value = a.ha + para.hurtAdd;
	return;
}
