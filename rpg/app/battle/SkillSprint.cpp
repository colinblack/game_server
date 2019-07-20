/*
 * SkillSprint.cpp
 *
 *  Created on: 2019年6月13日
 *      Author: Administrator
 */

#include "SkillSprint.h"
#include "BattleInc.h"

SkillSprint::SkillSprint() {
	m_type = SKILL_SPRINT;
}

SkillSprint::~SkillSprint() {
}

bool SkillSprint::doSkillHit(const SkillUseInfo &sinfo, MapMoveObject *caster, MapMoveObject *target, AttackInfo &ainfo) {
	const CfgSkill::Skill &cfg = SkillCfgWrap().GetById(sinfo.skillId);
	cfg.range();

	Point tpos;
	Point cpos;
	caster->getPos(cpos.x, cpos.y);
	target->getPos(tpos.x, tpos.y);

	int x = tpos.x;
	int y = tpos.y;

	uint32_t dis = MapMoveObject::getDistance(cpos.x, cpos.y, tpos.x, tpos.y);
	if (dis > cfg.range()) {
		dis = cfg.range();
	}

	uint32_t width = target->getBodyWidth();
	int fly = dis - width - cfg.range2() + 90;
	if (fly > 0) {
		float rad = atan2(tpos.y - cpos.y, tpos.x - cpos.x);
		x = cpos.x + cos(rad) * fly;
		y = cpos.y + sin(rad) * fly;
	}

	caster->moveStop();
	caster->setPos(x, y);

	msgs::SFightUpdate update;
	update.updateType_ = ATTR_UPDATE_POINT;
	update.updateData_.push_back(x);
	update.updateData_.push_back(y);
	caster->addFightUpdate(update);

	return true;
}
