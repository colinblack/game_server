/*
 * ActSevenDayTask.h
 *
 *  Created on: 2019年2月19日
 *      Author: Administrator
 */

#ifndef ACT_SEVEN_DAY_TASK_H_
#define ACT_SEVEN_DAY_TASK_H_

#include "ActivityUtil.h"

struct ActDataSDTask {
	byte type;
	map<byte, uint32_t> counts;
	ActDataSDTask() {
		type = 0;
		counts.clear();
	}
};
struct ActDataSDFlagType {
	vector<byte> flag;
	vector<uint32_t> curr;
	ActDataSDFlagType() {
		flag.clear();
		curr.clear();
	}
};
struct ActDataSDFlagDay {
	vector<ActDataSDFlagType> types;
	ActDataSDFlagDay() {
		types.clear();
	}
};

class ActSevenDayTask: public ActivityUtil {
public:
	ActSevenDayTask(uint32_t uid);
	bool doReward(uint32_t index);
	bool checkVer();
	bool loadData();
	bool saveData();
	bool encodeData(IBuffer *buff);
	bool loadTask(const Json::Value &v);
	bool loadFlag(const Json::Value &v);
	bool onLogin();
	bool onLevel();
	bool onBattleGate(uint32_t id);
	bool onAddSoldier(uint32_t cnt);
	bool onSolderScore(uint32_t cnt);
	bool onExp(uint32_t cnt);
	bool onBuilding(uint32_t cnt);
	bool onPower(uint32_t cnt);
	bool onZhengwu(uint32_t cnt);
	bool onBoat(uint32_t cnt);
	bool onBoss(uint32_t cnt);
	bool onSoldierColor();
	bool onDefendGate(uint32_t id);
	bool onGem();
	bool onArenaWin(uint32_t cnt);
	bool onArenaRank(uint32_t cnt);
	bool checkTask(byte type, uint32_t cnt, byte lv, bool lt = false);
	ActDataSDTask* getTask(byte type);
protected:
	uint32_t m_ver;
	map<byte, ActDataSDTask> m_task;
	vector<ActDataSDFlagDay> m_flag;
};

#endif /* ACT_SEVEN_DAY_TASK_H_ */
