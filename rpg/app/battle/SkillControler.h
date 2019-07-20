#ifndef SKILL_CONTROLER_H_
#define SKILL_CONTROLER_H_

#include "SkillBase.h"
#include "Common.h"
#include "StdMonster.h"

struct CollectInfo {
	uint32_t rid;
	uint32_t targetId;
	uint32_t startTime;
	uint32_t progressTime;
};

class SkillControler: public CSingleton<SkillControler> {
private:
	friend class CSingleton<SkillControler> ;
	SkillControler();

public:
	virtual ~SkillControler();
	bool init();
	bool initSkill(const CfgSkill::Skill &cfg);
	bool doUseSkill(MapMoveObject *caster, const vector<uint32_t> &targets, const SkillUseInfo &info, const Point &cen);
	bool objectHurt(MapMoveObject *caster, MapMoveObject *target, int32_t skid, const PropertySets &hurt);
	void caculateHurt(MapMoveObject *caster, MapMoveObject *target, AttackInfo &attackInfo, PropertySets &hurtProps);
	const SkillBase* getEntity(int id);

	static int getSkillType(const CfgSkill::Skill &cfg);

private:
	map<int32_t, SkillBase*> m_mapSkillEntities;            // map<skillid,entity>
	uint32_t m_attackId;
	msgs::SDoFights m_doFights;
};

#endif /* SKILL_CONTROLER_H_ */
