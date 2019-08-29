/*
 * SevenDayTaskConfig.h
 *
 *  Created on: 2019年2月19日
 *      Author: Administrator
 */

#ifndef SEVEN_DAY_TASK_CONFIG_H_
#define SEVEN_DAY_TASK_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct SDTaskCondition {
	uint8_t type;
	uint8_t lv;
	uint32_t count;
	uint32_t multiple;
	SDTaskCondition() {
		type = 0;
		lv = 0;
		count = 0;
		multiple = 0;
	}
};
struct SDTaskItem {
	uint8_t id;
	uint8_t box;
	uint8_t card;
	SDTaskCondition condition;
	Award reward;
	SDTaskItem() {
		id = 0;
		box = 0;
		card = 0;
	}
};
struct SDTaskType {
	uint8_t id;
	vector<SDTaskItem> tasks;
	SDTaskType() {
		id = 0;
		tasks.clear();
	}
};
struct SDTask {
	byte day;
	vector<SDTaskType> types;
	SDTask() {
		day = 0;
	}
};

enum SDTaskId {
	SDTaskIdLogin = 1,
	SDTaskIdLevel = 2,
	SDTaskIdBettleGate = 3,
	SDTaskIdAddSoldier = 4,
	SDTaskIdSoldierScore = 5,
	SDTaskIdExp = 6,
	SDTaskIdZhengWu = 7,
	SDTaskIdPower = 8,
	SDTaskIdBuilding = 9,
	SDTaskIdBoat = 10,
	SDTaskIdBoss = 11,
	SDTaskIdSoldierColor = 12,
	SDTaskIdDefendGate = 13,
	SDTaskIdGem = 14,
	SDTaskIdArenaWin = 15,
	SDTaskIdArenaRank = 16
};

class SevenDayTaskConfig {
	SINGLETON_CLASS(SevenDayTaskConfig);
	vector<SDTask> m_data;
	map<byte, set<byte> > m_types;
public:
	bool init(const string &path);
	const SDTaskItem* getItem(byte day, byte type, byte id) const;
	const vector<SDTask>& getAll() const;
	bool checkOpen(byte type, byte day) const;
};

#endif /* SEVEN_DAY_TASK_CONFIG_H_ */
