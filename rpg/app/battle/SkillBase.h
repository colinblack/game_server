#ifndef _SKILL_BASE_H_
#define _SKILL_BASE_H_

#include "Kernel.h"
#include "MapMoveObject.h"
#include "Common.h"

struct SkillInfo {
	int id;
	int type;

	SkillInfo() {
		id = 0;
		type = 0;
	}
};

enum SKILL_TYPE {
	SKILL_UNKNOW = 0,
	SKILL_NORMAL = 1,		//普通攻击
	SKILL_SPRINT = 2,		//冲刺
	SKILL_SUMMON = 3,		//召唤
	SKILL_RUSH = 4,			//冲锋
	SKILL_MAX
};

class SkillBase {
public:
	SkillBase();
	virtual ~SkillBase();
public:
	virtual bool doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo);
	virtual bool caculateHurt(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo);
	virtual void getTargets(const SkillUseInfo &sinfo, MapMoveObject *caster, vector<uint32_t> &targets);
	virtual void doActorEffect(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target);
	virtual void doSceneEffect(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target);
	virtual void doEffect(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target);
	virtual int getType() const;
	virtual int getMaxLevel() const;

protected:
	short m_effectFlag; //0:scene 1:actor
	bool m_notAutoUse;
	bool m_magicLock;
	bool m_canUseOnFD;
	bool m_canUseOnDizzy;
	bool m_canbeDefault;
	bool m_isDelete;
	bool m_gainFlag; // true 增益 false减益
	int m_maxLevel;
	int m_type;
};

#endif
