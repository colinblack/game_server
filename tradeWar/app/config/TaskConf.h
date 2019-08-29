#ifndef _TASK_CONF_H_
#define _TASK_CONF_H_

#include "Common.h"
#include "Kernel.h"
#include "Award.h"

enum ACHIEVEMENT_TYPE_ENUM {
	ACHIEVEMENT_TYPE_KILL_SOLDIER = 1,			// 歼敌高手
	ACHIEVEMENT_TYPE_ROB_RES,					// 掠夺大师
	ACHIEVEMENT_TYPE_KILL_FLY_SOLDIER,			// 空中霸主
	ACHIEVEMENT_TYPE_BOAT_RES,					// 金币商人
	ACHIEVEMENT_TYPE_ROB_WIN,					// 完美无瑕
	ACHIEVEMENT_TYPE_BUILD,						// 精英建筑师
	ACHIEVEMENT_TYPE_GATE_STAR,					// 星星收集达人
	ACHIEVEMENT_TYPE_KILL_DEF_SOLDIER,			// 装甲歼灭者
	ACHIEVEMENT_TYPE_UNLOCK_SOLDIER,			// 骠骑将军
	ACHIEVEMENT_TYPE_TOWER,						// 战斗工程师
	ACHIEVEMENT_TYPE_COLLECT,					// 极品镖师
	ACHIEVEMENT_TYPE_KILL_TRANSPORT_SOLDIER,	// 车辆毁灭者
	ACHIEVEMENT_TYPE_ROB_LOST,					// 濒临破产
	ACHIEVEMENT_TYPE_UPGRATE_SOLDIER,			// 训练高手
	ACHIEVEMENT_TYPE_MAX
};

enum TASK_TYPE_ENUM {
	TASK_TYPE_BUILDING = 101,					// 升级建筑
	TASK_TYPE_SOLDIER = 102,					// 升级士兵
	TASK_TYPE_BOAT = 103,						// 跑商
	TASK_TYPE_ROB_BOAT = 104,					// 截商
	TASK_TYPE_GATE = 105,						// 战役
	TASK_TYPE_DEFEND_TROOPS = 106,				// 布阵
	TASK_TYPE_ATTACK_TROOPS = 107,				// 布阵
	TASK_TYPE_GOVERNMENT_AFFAIRS = 108,			// 政务
	TASK_TYPE_DEFEND_TROOPS_ALL = 109,			// 一键布阵
	TASK_TYPE_CARD_STAR = 110					// 卡牌升星
};

enum TASK_GROUP {
	TASK_GROUP_ACHIVMENT = 1,
	TASK_GROUP_NORMAL = 2
};

struct TaskTarget {
	uint32_t type;
	uint32_t count;
	uint32_t id;
	uint32_t lv;

	TaskTarget(): type(0), count(0), id(0), lv(0) {
	}
};

struct TaskConfig {
	uint32_t id;				// 任务id
	byte type;					//
	vector<uint32_t> pre;		// 接任务条件
	vector<uint32_t> next;		// 后续任务
	vector<TaskTarget> targets;	// 任务目标
	Award rewards;   			// 奖励

	TaskConfig() : id(0), type(0) {
	}
};

enum TASK_STATUE {
	TASK_STATUE_DOING = 0,  // 进行中
	TASK_STATUE_DONE = 1,   // 完成
	TASK_STATUE_FINISH = 2  // 结束
};

class TaskConf {
public:
	static TaskConf* getInstance() {
		static TaskConf instance;
		return &instance;
	}
	virtual ~TaskConf();
	bool init(const string& path);
	const TaskConfig* getConfById(uint32_t id) const;
	const set<uint32_t>* getFirst() const;
	const TaskConfig* getAchievement(uint32_t type, uint32_t id) const;
	uint32_t getAchievementIndex(uint32_t type, uint32_t id) const;
protected:
	TaskConf();
private:
	map<uint32_t, TaskConfig> m_data;
	set<uint32_t> m_first;
	map<uint32_t, vector<uint32_t> > m_achievements;
};

#endif /* TASKCONF_H_ */
