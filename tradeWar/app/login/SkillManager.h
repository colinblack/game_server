/*
 * SkillManager.h
 *
 *  Created on: 2018年5月21日
 *      Author: Administrator
 */

#ifndef SKILL_MANAGER_H_
#define SKILL_MANAGER_H_

#include "IManager.h"
#include "DataSkill.h"

class CSkillManager: public IManager {
public:
	CSkillManager();
	virtual ~CSkillManager();
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool setSkill(const vector<DataSkill> &datas);
	bool onTimer();
	bool sendSkillToBattle(uint64_t battleId);
	bool checkSkill(uint32_t lvl, uint32_t count);
	bool checkBornSkill(uint32_t lvl, uint32_t count);
	uint32_t getCombat(uint16_t ud);
	bool addSkill(uint16_t id, uint32_t count, const string &reason);
	bool packSkill(IBuffer *buff);
private:
	bool doUpgrade(CNetPacket *packet);
	bool doQuery(CNetPacket *packet);
	bool doUse(CNetPacket *packet);
	bool doStatus(CNetPacket *packet);
	bool onResultResp(byte subCmd, byte ret);
	bool doSave(const DataSkill &skill, bool isNew);
	bool sendSkillUp(const DataSkill &skill);
	bool sendSkills();
private:
	map<uint16_t, DataSkill> m_data;
};

#endif /* SKILL_MANAGER_H_ */
