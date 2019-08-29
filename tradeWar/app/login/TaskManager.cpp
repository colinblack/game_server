#include "TaskManager.h"
#include "PlayerManager.h"
#include "ProtocolInc.h"

bool TaskManager::load(uint32_t uid) {
	m_tasks.clear();
	CDataTask cDataTask;
	vector<DataTask> datas;
	int ret = cDataTask.GetTasks(uid, datas);
	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA) {
		error_log("GetTasks fail uid=%u ret=%d", uid, ret);
		return false;
	}
	vector<DataTask>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr) {
		m_tasks.insert(make_pair(itr->id, *itr));
	}

	loadPreTask();

	initTask();

	loadAchievement();

	initAchievement();

	checkProgress(false);

	return true;
}

bool TaskManager::doPacket(CNetPacket* packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_TASK_LIST:
		doTaskList(packet);
		break;
	case PROTOCOL_SUBCMD_TASK_SUBMIT:
		doTaskSubmit(packet);
		break;
	case PROTOCOL_SUBCMD_TASK_FINISH:
		doTaskFinish(packet);
		break;
	case PROTOCOL_SUBCMD_TASK_COUNT:
		doTaskCount(packet);
		break;
	default:
		error_log("unknow_building_subcmd=%u", packet->subCmd);
		return false;
	}
	return true;
}

void TaskManager::onRobRes(uint32_t res) {
	addAchievement(ACHIEVEMENT_TYPE_ROB_RES, res);
	addTaskCurr(TASK_TYPE_ROB_BOAT, 1);
	checkProgress();
}
void TaskManager::onTransportRes(uint32_t res) {
	addAchievement(ACHIEVEMENT_TYPE_BOAT_RES, res);
	checkProgress();
}
void TaskManager::onFullStar() {
	addAchievement(ACHIEVEMENT_TYPE_ROB_WIN, 1);
	checkProgress();
}
void TaskManager::onUpgradeBuilding() {
	addAchievement(ACHIEVEMENT_TYPE_BUILD, 1);
	checkProgress();
}
void TaskManager::onStarNum(uint32_t star) {
	addAchievement(ACHIEVEMENT_TYPE_GATE_STAR, star);
	checkProgress();
}
void TaskManager::onUnlockSoldier(uint32_t cnt) {
	addAchievement(ACHIEVEMENT_TYPE_UNLOCK_SOLDIER, cnt);
	checkProgress();
}
void TaskManager::onProduceRes(uint32_t res) {
	addAchievement(ACHIEVEMENT_TYPE_COLLECT, res);
	checkProgress();
}
void TaskManager::onLostRes(uint32_t res) {
	addAchievement(ACHIEVEMENT_TYPE_ROB_LOST, res);
	checkProgress();
}
void TaskManager::onUpgradeSoldier() {
	addAchievement(ACHIEVEMENT_TYPE_UPGRATE_SOLDIER, 1);
	checkProgress();
}
void TaskManager::onUpgradeTower() {
	checkProgress();
}
void TaskManager::onBattleGateOver() {
	checkProgress();
}
void TaskManager::onTroops() {
	checkProgress();
}
void TaskManager::onBoatStart() {
	addTaskCurr(TASK_TYPE_BOAT, 1);
	checkProgress();
}
void TaskManager::onRandomQuest() {
	addTaskCurr(TASK_TYPE_GOVERNMENT_AFFAIRS, 1);
	checkProgress();
}

void TaskManager::onSoldierUpgrade() {
	checkProgress();
}

void TaskManager::addTaskCurr(uint32_t type, uint32_t cnt) {
	CDataTask dbc;
	for (map<uint32_t, DataTask>::iterator itr = m_tasks.begin(); itr != m_tasks.end(); ++itr) {
		DataTask &task = itr->second;
		if (task.status != TASK_STATUE_DOING) {
			continue;
		}
		const TaskConfig *cfg = TaskConf::getInstance()->getConfById(task.id);
		if (cfg == NULL) {
			continue;
		}
		if (cfg->targets.empty()) {
			continue;
		}
		const TaskTarget &tar = *(cfg->targets.begin());
		if (tar.type == type) {
			task.curr += cnt;
			if (task.curr >= tar.count) {
				task.status = TASK_STATUE_DONE;
			}
			dbc.SetTask(task);
			m_sync = true;
		}
	}
}
bool TaskManager::doTaskSubmit(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	Award award;
	CTaskSubmitProtocol cs;
	if (!cs.Decode(packet->GetBody())) {
		error_log("CTaskSubmitProtocol decode failed, uid=%u", uid);
		onTaskSubmitResp(1, award);
		return false;
	}
	const TaskConfig *config = TaskConf::getInstance()->getConfById(cs.id);
	if (config == NULL) {
		error_log("param error uid=%u cs_id=%u", uid, cs.id);
		onTaskSubmitResp(1, award);
		return false;
	}
	map<uint32_t, DataTask>::iterator itr = m_tasks.find(cs.id);
	if (itr == m_tasks.end()) {
		onTaskSubmitResp(1, award);
		return false;
	}
	DataTask &task = itr->second;

	if (task.status != TASK_STATUE_DONE) {
		error_log("status error uid=%u id=%u status=%u", task.uid, task.id, task.status);
		onTaskSubmitResp(1, award);
		return false;
	}

	if (!m_player->doReward(&(config->rewards), "quest", false, &award)) {
		error_log("doReward fail uid=%u id=%u status=%u", task.uid, task.id, task.status);
		onTaskSubmitResp(1, award);
		return false;
	}

//	if (!config->targets.empty() && m_achievements.count(config->targets.begin()->type)) {
//		m_achievements[config->targets.begin()->type].count = 0;
//		saveAchievement(m_achievements[config->targets.begin()->type], false);
//	}

	task.status = TASK_STATUE_FINISH;
	addPreTask(task.id);

	CDataTask dbTask;
	dbTask.DelTask(packet->uid, task.id);
	m_tasks.erase(itr);

	for (vector<uint32_t>::const_iterator it = config->next.begin(); it != config->next.end(); ++it) {
		const TaskConfig *nextConfig = TaskConf::getInstance()->getConfById(*it);
		if (nextConfig == NULL) {
			error_log("task not exist uid=%u,next_id=%u cs_id=%u", packet->uid, *it, cs.id);
			continue;
		}

		if (checkCanAcceptTask(*nextConfig)) {
			DataTask addTask;
			addTask.uid = packet->uid;
			addTask.id = nextConfig->id;
			addTask.type = nextConfig->type;
			dbTask.AddTask(addTask);
			if (!m_tasks.count(addTask.id)) {
				debug_log("add_task_1 uid=%u cs_id=%u add_id=%u type=%u", addTask.uid, cs.id, addTask.id, addTask.type);
				m_tasks.insert(make_pair(addTask.id, addTask));
			}
			debug_log("add_task_ok uid=%u cs_id=%u add_id=%u type=%u", addTask.uid, cs.id, addTask.id, addTask.type);
		} else {
			debug_log("add_task_fail uid=%u cs_id=%u add_id=%u type=%u", packet->uid, cs.id, nextConfig->id, nextConfig->type);
		}
	}

	debug_log("task_finish uid=%u cs_id=%u add_id=%u type=%u", packet->uid, cs.id, cs.id, config->type);

	checkProgress(false);

	sendTaskList();

	onTaskSubmitResp(0, award);

	return true;
}

bool TaskManager::doTaskFinish(CNetPacket* packet) {
	return true;
}

bool TaskManager::doTaskList(CNetPacket* packet) {
	sendTaskList();
	return true;
}

bool TaskManager::doTaskCount(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	CTaskCountProtocol cs;
	if (!cs.Decode(packet->GetBody())) {
		error_log("CTaskCountProtocol decode failed, uid=%u", uid);
		onTaskCountResp(1);
		return false;
	}

	bool check_flag = false;
	const TaskConfig *cfg = TaskConf::getInstance()->getConfById(m_curr);
	if (cfg != NULL
	&& !cfg->targets.empty()
	&& cfg->targets.front().type == cs.id
	&& m_tasks.count(m_curr)
	&& m_tasks[m_curr].status == TASK_STATUE_DOING) {
		m_tasks[m_curr].curr += cs.count;
		check_flag = true;
	}
	map<uint32_t, DataAchievement>::iterator itr = m_achievements.find(cs.id);
	if (itr != m_achievements.end()) {
//		error_log("achievement type not exists uid=%u type=%u", uid, cs.id);
//		onTaskCountResp(1);
//		return false;
		itr->second.count += cs.count;
		saveAchievement(itr->second, false);
		check_flag = true;
	}

	if (check_flag) {
		checkProgress();
	}

	onTaskCountResp(0);
	return true;
}

bool TaskManager::onTaskCountResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TASK);
	writer.AppendByte(PROTOCOL_SUBCMD_TASK_COUNT);
	writer.AppendByte(ret);

	return PlayerManager::getInstance()->sendToAccess(&sp);
}

bool TaskManager::onTaskSubmitResp(byte ret, const Award &award) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TASK);
	writer.AppendByte(PROTOCOL_SUBCMD_TASK_SUBMIT);
	writer.AppendByte(ret);
	const vector<AwardInfo> &awardInfo = award.get();
	writer.AppendUInt32(awardInfo.size());
	vector<AwardInfo>::const_iterator itr = awardInfo.begin();
	for (; itr != awardInfo.end(); ++itr) {
		writer.AppendByte(itr->type);
		writer.AppendUInt32(itr->id);
		writer.AppendUInt32(itr->count);
	}

	return PlayerManager::getInstance()->sendToAccess(&sp);
}

bool TaskManager::sendTaskList() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_TASK);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_TASK_LIST);
	selfWriter.AppendUInt32(m_tasks.size());
	map<uint32_t, DataTask>::iterator itr = m_tasks.begin();
	for (; itr != m_tasks.end(); ++itr) {
		const DataTask &task = itr->second;
		selfWriter.AppendUInt32(task.id);
		selfWriter.AppendUInt32(task.curr);
		selfWriter.AppendByte(task.status);
	}

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool TaskManager::initTask() {
	const set<uint32_t> *first = TaskConf::getInstance()->getFirst();
	if (first == NULL) {
		return false;
	}
	uint32_t uid = m_player->getUid();
	CDataTask dbTask;
	set<uint32_t>::const_iterator itr = first->begin();
	for (; itr != first->end(); ++itr) {
		if (m_tasks.count(*itr) || m_preTask.count(*itr)) {
			continue;
		}
		const TaskConfig *cfg = TaskConf::getInstance()->getConfById(*itr);
		if (cfg == NULL) {
			continue;
		}
		DataTask task;
		task.uid = uid;
		task.id = *itr;
		task.type = cfg->type;
		task.status = TASK_STATUE_DOING;
		dbTask.AddTask(task);
		m_tasks.insert(make_pair(task.id, task));
		debug_log("uid=%u,id=%u", m_player->getUid(), task.id);
	}

	return true;
}

bool TaskManager::checkProgress(bool notice) {
	CDataTask dbTask;
	for (map<uint32_t, DataTask>::iterator itr = m_tasks.begin(); itr != m_tasks.end(); ++itr) {
		DataTask &task = itr->second;
		if (task.status != TASK_STATUE_DOING) {
			continue;
		}
		const TaskConfig *cfg = TaskConf::getInstance()->getConfById(task.id);
		if (cfg == NULL) {
			continue;
		}
		if (cfg->targets.empty()) {
			continue;
		}

		uint32_t curr = 0;
		uint32_t condition = 0xFFFFFFFF;

		const TaskTarget &tar = *(cfg->targets.begin());
		if (m_achievements.count(tar.type)) {
			curr = m_achievements[tar.type].count;
			condition = tar.count;
			uint32_t aindex = TaskConf::getInstance()->getAchievementIndex(tar.type, task.id);
			if (aindex > 0 && aindex < m_achievements[tar.type].id) {
				task.curr = tar.count;
			}
		} else {
			switch (tar.type) {
			case TASK_TYPE_BUILDING:
				curr = checkBuilding(tar);
				condition = tar.lv;
				break;
			case TASK_TYPE_SOLDIER:
				curr = checkSoldier(tar);
				condition = tar.lv;
				break;
			case TASK_TYPE_BOAT:
				break;
			case TASK_TYPE_ROB_BOAT:
				break;
			case TASK_TYPE_GATE:
				curr = checkGate(tar);
				condition = tar.id;
				break;
			case TASK_TYPE_DEFEND_TROOPS:
				curr = checkDefendTroops(tar);
				condition = tar.count;
				break;
			case TASK_TYPE_ATTACK_TROOPS:
				curr = checkAttackTroops(tar);
				condition = tar.count;
				break;
			case TASK_TYPE_GOVERNMENT_AFFAIRS:
				break;
			case TASK_TYPE_DEFEND_TROOPS_ALL:
				condition = tar.count;
				m_curr = task.id;
				break;
			case TASK_TYPE_CARD_STAR:
				curr = checkCardStar(tar);
				condition = tar.lv;
				break;
			default:
				break;
			}
		}

		uint32_t old_curr = task.curr;

		if (task.curr < curr) {
			task.curr = curr;
		}
		if (task.curr >= condition) {
			task.status = TASK_STATUE_DONE;
		}

		if (task.status == TASK_STATUE_DONE || old_curr != task.curr) {
			dbTask.SetTask(task);
			m_sync = true;
		}
	}

	if (m_sync) {
		m_sync = false;
		if (notice) {
			sendTaskList();
		}
	}

	return true;
}

uint32_t TaskManager::checkBuilding(const TaskTarget &tar) {
	const BuildingItemConfig *cfg = BuildingConfig::getInstance()->getItemConfig(tar.id);
	if (cfg == NULL) {
		return 0;
	}

	if (cfg->type == BUILDING_TYPE_TOWER) {
		return m_player->getBm()->getTowerLevel(tar.id);
	}

	Building *p = m_player->getBm()->getBuildingByType(tar.id);
	if (p == NULL) {
		return 0;
	}
	return p->getLevel();
}

uint32_t TaskManager::checkSoldier(const TaskTarget &tar) {
	Soldier *p = m_player->getSoldierManager()->getSoldierByType(tar.id);
	if (p == NULL) {
		return 0;
	}
	return p->getLevel();
}

uint32_t TaskManager::checkGate(const TaskTarget &tar) {
	return m_player->getBattleGateMgr()->getCurr();
}

uint32_t TaskManager::checkAttackTroops(const TaskTarget &tar) {
	return m_player->getTroopsManager()->getAttackCount(0);
}

uint32_t TaskManager::checkDefendTroops(const TaskTarget &tar) {
	return m_player->getTroopsManager()->getDefendCount(0);
}

uint32_t TaskManager::checkCardStar(const TaskTarget & tar) {
	return m_player->getSoldierManager()->getSoldierByType(tar.id)->getStar();
}

bool TaskManager::checkCanAcceptTask(const TaskConfig &nextConfig) {
	if (nextConfig.pre.size() == 1) {
		return true;
	}

	for (vector<uint32_t>::const_iterator it = nextConfig.pre.begin(); it != nextConfig.pre.end(); ++it) {
		if (m_preTask.find(*it) == m_preTask.end()) {
			return false;
		}
	}

	return true;
}

bool TaskManager::loadPreTask() {
	uint32_t uid = m_player->getUid();
	CDataPreTask dbPreTask;
	vector<uint32_t> ids;
	int ret = dbPreTask.getPreTasks(uid, ids);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("getPreTasks error ret=%d uid=%u", ret, uid);
	}
	for (vector<uint32_t>::iterator itr = ids.begin(); itr != ids.end(); ++itr) {
		if (*itr != 0) {
			m_preTask.insert(*itr);
		}
	}
	return true;
}

bool TaskManager::addPreTask(uint32_t id) {
	m_preTask.insert(id);
	return savePreTask(id);
}

bool TaskManager::savePreTask(uint32_t id) {
	uint32_t uid = m_player->getUid();
	CDataPreTask dbPreTask;
	int ret = dbPreTask.addPreTask(uid, id);
	if (ret != 0) {
		error_log("addPreTask error ret=%d uid=%u", ret, uid);
	}
	return true;
}

bool TaskManager::loadAchievement() {
	uint32_t uid = m_player->getUid();
	CDataAchievement dbAchievement;
	vector<DataAchievement> data;
	dbAchievement.GetAchievement(uid, data);
	vector<DataAchievement>::iterator itr = data.begin();
	for (; itr != data.end(); ++itr) {
		m_achievements.insert(make_pair(itr->type, *itr));
	}

	return true;
}

bool TaskManager::saveAchievement(const DataAchievement &data, bool isNew) {
	CDataAchievement dbAchievement;
	if (isNew) {
		dbAchievement.AddAchievement(data);
	} else {
		dbAchievement.SetAchievement(data);
	}
	return true;
}

bool TaskManager::initAchievement() {
	for (size_t i = ACHIEVEMENT_TYPE_KILL_SOLDIER; i < ACHIEVEMENT_TYPE_MAX; ++i) {
		if (!m_achievements.count(i)) {
			DataAchievement data;
			data.uid = m_player->getUid();
			data.type = i;
			data.id = 1;
			m_achievements.insert(make_pair(data.type, data));
			checkAchievement(i);
			saveAchievement(m_achievements[i], true);
		} else {
			if (m_achievements[i].id == 0) {
				map<uint32_t, DataTask>::iterator itr = m_tasks.begin();
				for (; itr != m_tasks.end(); ++itr) {
					DataTask &task = itr->second;
					const TaskConfig *cfg = TaskConf::getInstance()->getConfById(task.id);
					if (cfg == NULL) {
						continue;
					}
					if (cfg->targets.empty()) {
						continue;
					}
					const TaskTarget &tar = *(cfg->targets.begin());
					if (tar.type != i) {
						continue;
					}
					m_achievements[i].id = TaskConf::getInstance()->getAchievementIndex(i, task.id);
					break;
				}
				if (m_achievements[i].id != 0) {
					checkAchievement(i);
					saveAchievement(m_achievements[i], false);
				}
			}
		}
	}
	return true;
}

bool TaskManager::addAchievement(uint32_t type, uint32_t count) {
	if (m_achievements.count(type)) {
		m_achievements[type].count += count;
		checkAchievement(type);
		saveAchievement(m_achievements[type], false);
	} else {
		DataAchievement data;
		data.type = type;
		data.count = count;
		data.uid = m_player->getUid();
		m_achievements.insert(make_pair(type, data));
		checkAchievement(type);
		saveAchievement(m_achievements[type], true);
	}
	return true;
}

bool TaskManager::checkAchievement(uint32_t type) {
	if (!m_achievements.count(type)) {
		return false;
	}
	DataAchievement &data = m_achievements[type];
	do {
		const TaskConfig *cfg = TaskConf::getInstance()->getAchievement(type, data.id);
		if (cfg == NULL) {
			return false;
		}
		if (cfg->targets.empty() || data.count < cfg->targets.begin()->count) {
			return false;
		}
		data.count -= cfg->targets.begin()->count;
		data.id += 1;
	} while (true);
	return true;
}

