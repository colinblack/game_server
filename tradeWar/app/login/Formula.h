/*
 * Formula.h
 *
 *  Created on: 2015年10月13日
 *      Author: asdf
 */

#ifndef SERVERS_APP_MAPOBJ_FORMULA_H_
#define SERVERS_APP_MAPOBJ_FORMULA_H_
#include "Kernel.h"
#include "MapObject.h"
using std::vector;

class IBattleData
{
public:
	IBattleData(MapObject* pMo);
	bool isInit()
	{
		//return levelRejectHurtRate > 0 && critRate > 0 && dodgeRate > 0;
		return true;
	}
public:
	uint32_t ha; //物攻
	uint32_t ma; //魔攻
	uint32_t hd; //物防
	uint32_t md; //魔防
	uint32_t bp; //暴击
	uint32_t bv; //暴击倍数
	uint32_t ebp; //暴击闪避
	uint32_t ep; //总免伤百分比
	uint32_t hep; //物理免伤百分比
	uint32_t mep; //魔法免伤百分比
	uint32_t hr; //命中值
	uint32_t ip; //闪避
	uint32_t ta; //总伤害
	uint32_t he; //物理免伤值
	uint32_t ev; //总免伤值
	uint32_t me; //魔法免伤值

	uint32_t hm; //攻击类型(物理攻击，魔法攻击)
	uint32_t horm; //损伤属性类型(减血，减魔)
	uint32_t type; // 类型
	uint32_t level; //等级
	uint32_t showIp; //显示闪避值
	uint32_t showBp; //显示暴击值
	uint32_t battleProf; //战斗类型(海,陆,空)
	uint32_t levelRejectHurtRate; //等级免伤系数(伤血系数)(heroHD第一个元素)
	uint32_t critRate; // 暴击系数(heroHD第二个元素)
	uint32_t dodgeRate; // 闪避系数(heroHD第二个元素)
};
class HurtPara
{
public:
	uint32_t type; //攻击类型(物理攻击，魔法攻击)
	uint32_t flag; //暴击，闪避，物攻，魔攻，丢失
	uint32_t value; //伤害值
	uint32_t hurtAdd;
	float hurtRate;
	bool isSkill;
	float profHurtRate;
	bool isBuff;

	HurtPara() : type(0), flag(0), value(0), hurtAdd(0), hurtRate(1.0), isSkill(false), profHurtRate(1.0), isBuff(false)
	{
	}

	bool isSkillHurt()
	{
		return isSkill;
	}

	bool isBuffHurt()
	{
		return isBuff;
	}
};
class SkillData
{
public:
	uint16_t id;
	uint32_t hurt;
	float rate;

	SkillData() : id(0), hurt(0), rate(0.0)
	{

	}
};
class CalDamage
{
public:
	static uint32_t getDeductHp(MapObject* attacker, MapObject* defender, HurtPara& hurtPara);
	static uint32_t getDeductHp(MapObject *attacker, MapObject *defender, uint32_t skillId);
	static void calHAttackHpByData(IBattleData& attacker, IBattleData& defender, HurtPara& hurtPara, uint32_t factor = 1);
private:
	static HurtPara calMAttackHpByData(IBattleData& attacker, IBattleData& defender, uint32_t factor);
	static HurtPara calHAttackMpByData(IBattleData& attacker, IBattleData& defender, uint32_t factor);
	static HurtPara calMAttackMpByData(IBattleData& attacker, IBattleData& defender, uint32_t factor);
	static bool draw100(int32_t num);
private:
	static const uint32_t HEALTH_TYPE = 1; // 减血
	static const uint32_t MAGIC_TYPE = 2; // 减魔
	static const uint32_t HEALTH_HURT = 1;
	static const uint32_t MAGIC_HURT = 2;

	static const uint32_t FLAG_NONE = 0;
	static const uint32_t FLAG_IP = 1; // 闪避
	static const uint32_t FLAG_BP = 2; // 暴击
	static const uint32_t FLAG_HP = 3; // 物攻
	static const uint32_t FLAG_MP = 4; // 魔攻
	static const uint32_t FLAG_MISS = 5; // 丢失

	static const uint32_t MIN_EP_LEFT = 0;
};
// end of CalDamage
inline uint32_t calcWorldBattleGainExp(uint32_t heroHurt, uint32_t buildingHurt)
{
	uint32_t exp = (heroHurt > 200) ? (0.8 * pow(heroHurt, 1.0 / 3) + 0.2 * pow(buildingHurt, 1.0 / 3)) : 0;
	if (exp > 300)
	{
		exp = 300;
	}
	return exp;
}
#endif /* SERVERS_APP_MAPOBJ_FORMULA_H_ */
