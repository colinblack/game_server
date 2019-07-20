/*
 * SkillManager.h
 *
 *  Created on: 2019年6月11日
 *      Author: Administrator
 */

#ifndef SKILL_MANAGER_H_
#define SKILL_MANAGER_H_

#include "BattleBaseInc.h"

#define SHENQI_SKILL_BEGIN	(40000)

enum SKILL_OP {
	SKILL_ADD = 0,	//解锁
	SKILL_DEL = 1,	//删除
	SKILL_SET = 2,	//更新
};
class SkillManager: public CSingleton<SkillManager> {
private:
	friend class CSingleton<SkillManager>;
	SkillManager();
	~SkillManager();
	byte m_oper;
	vector<DataSkill> m_chgs;

public:
	bool ActorLogin(uint32_t uid);
	bool AutoUnlock(UserCache &cache, bool sync);
	bool UnlockShenQi(UserCache &cache);
	bool SendChange(uint32_t uid);
	bool UpgradeSkill(const UserCache &cache, DataSkill &data);
	bool CalcProperty(const UserCache &cache, byte rid, PropertySets &props);

public:
	int Process(uint32_t uid, logins::SUseSkill *req);
	int Process(uint32_t uid, logins::SUpgradeSkill *req);
	int Process(uint32_t uid, logins::SUpgradeSkillAll *req);

public:
	int Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerSkillInfo *resp);
};

#endif /* SKILL_MANAGER_H_ */
