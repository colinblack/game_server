#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_

#include "DataTask.h"
#include "DataAchievement.h"
#include "IManager.h"
#include "TaskConf.h"

class TaskManager: public IManager {
public:
	TaskManager(): m_curr(0), m_sync(false) {
	}
	~TaskManager() {
	}
	bool load(uint32_t uid);
	virtual bool doPacket(CNetPacket* packet);
	void onRobRes(uint32_t res);
	void onTransportRes(uint32_t res);
	void onFullStar();
	void onUpgradeBuilding();
	void onStarNum(uint32_t star);
	void onUnlockSoldier(uint32_t cnt);
	void onProduceRes(uint32_t res);
	void onLostRes(uint32_t res);
	void onUpgradeSoldier();
	void onUpgradeTower();
	void onBattleGateOver();
	void onTroops();
	void onBoatStart();
	void onRandomQuest();
	void onSoldierUpgrade();
	void addTaskCurr(uint32_t type, uint32_t cnt);
private:
	bool doTaskSubmit(CNetPacket* packet);
	bool doTaskFinish(CNetPacket* packet);
	bool doTaskList(CNetPacket* packet);
	bool doTaskCount(CNetPacket* packet);
	bool onTaskCountResp(byte ret);
	bool onTaskSubmitResp(byte ret, const Award &award);
	bool initTask();
	bool checkCanAcceptTask(const TaskConfig &nextConfig);
	bool checkProgress(bool notice = true);
	uint32_t checkBuilding(const TaskTarget &tar);
	uint32_t checkSoldier(const TaskTarget &tar);
	uint32_t checkGate(const TaskTarget &tar);
	uint32_t checkAttackTroops(const TaskTarget &tar);
	uint32_t checkDefendTroops(const TaskTarget &tar);
	uint32_t checkCardStar(const TaskTarget & tar);
	bool sendTaskList();

	bool loadPreTask();
	bool addPreTask(uint32_t id);
	bool savePreTask(uint32_t id);

	bool loadAchievement();
	bool saveAchievement(const DataAchievement &data, bool isNew);
	bool initAchievement();
	bool addAchievement(uint32_t type, uint32_t count);
	bool checkAchievement(uint32_t type);
private:
	map<uint32_t, DataTask> m_tasks;
	map<uint32_t, DataAchievement> m_achievements;
	set<uint32_t> m_preTask;
	uint32_t m_curr;
	bool m_sync;
};

#endif /* _TASK_MANAGER_H_ */
