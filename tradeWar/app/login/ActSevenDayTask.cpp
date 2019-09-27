/*
 * ActSevenDayTask.cpp
 *
 *  Created on: 2019年2月19日
 *      Author: Administrator
 */

#include "ActSevenDayTask.h"
#include "ActivityTimeManager.h"
#include "PlayerManager.h"
#include "SevenDayTaskConfig.h"
#include "GiftBagConfig.h"
#include "ArenaRankManager.h"

ActSevenDayTask::ActSevenDayTask(uint32_t uid): ActivityUtil(uid, e_ActivityTypeSevenDayTask) {
	m_uid = uid;
	m_id = e_ActivityTypeSevenDayTask;
	m_ver = 0;
	loadData();
	checkVer();
}

bool ActSevenDayTask::doReward(uint32_t index) {
	uint32_t day = index / 10000;
	uint32_t type = index / 100 % 10;
	uint32_t id = index % 10;
	if (day < 1 || type < 1 || id < 1) {
		error_log("param error uid=%u day=%u type=%u id=%u", m_uid, day, type, id);
		return false;
	}
	if (m_flag.size() < day) {
		error_log("param error uid=%u day=%u type=%u id=%u", m_uid, day, type, id);
		return false;
	}
	if (m_flag[day - 1].types.size() < type) {
		error_log("param error uid=%u day=%u type=%u id=%u", m_uid, day, type, id);
		return false;
	}
	if (m_flag[day - 1].types[type - 1].flag.size() < id) {
		error_log("param error uid=%u day=%u type=%u id=%u", m_uid, day, type, id);
		return false;
	}
	if (m_flag[day - 1].types[type - 1].flag[id - 1] != 1) {
		error_log("param error uid=%u day=%u type=%u id=%u", m_uid, day, type, id);
		return false;
	}
	const SDTaskItem *cfg = SevenDayTaskConfig::getInstance()->getItem(day, type, id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u day=%u type=%u id=%u", m_uid, day, type, id);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		error_log("load player error uid=%u day=%u type=%u id=%u", m_uid, day, type, id);
		return false;
	}
	m_flag[day - 1].types[type - 1].flag[id - 1] = 2;
	saveData();
	string code;
	String::Format(code, "act_sevendaytask_%u_%u_%u", day, type, id);
	if (cfg->box > 0) {
		Award reward;
		uint32_t lv = player->getLevel();
		uint32_t boxId = (lv == 0 ? 1 : lv) * 1000 + cfg->box;
		GiftBagConfig::getInstance()->openAllLuckyBox(boxId, cfg->card, reward);
		m_box = reward;
		player->doReward(&reward, code, false);
	} else {
		parseReward(cfg->reward);
		m_box.clear();
		m_normal.clear();
		player->doReward(&m_reward, code);
	}

	BUSI_MISC("timelimit_act|sdtask|%u|%u_%u_%u|%u", m_uid, day, type, id, Time::GetGlobalTime());
	return true;
}

bool ActSevenDayTask::checkVer() {
	if (!ActivityTimeManager::getInstance()->isOpen(m_id)) {
		return false;
	}
	bool chg = false;
	uint32_t ver = ActivityTimeManager::getInstance()->getVer(m_id);
	if (m_ver != ver) {
		m_ver = ver;
		m_task.clear();
		m_flag.clear();
		chg = true;
	}
	const vector<SDTask> &cfg = SevenDayTaskConfig::getInstance()->getAll();
	if (m_flag.size() != cfg.size()) {
		m_flag.resize(cfg.size());
		chg = true;
	}
	vector<SDTask>::const_iterator itr = cfg.begin();
	size_t id1 = 0;
	for (; itr != cfg.end(); ++itr, ++id1) {
		if (m_flag[id1].types.size() != itr->types.size()) {
			m_flag[id1].types.resize(itr->types.size());
			chg = true;
		}
		size_t id2 = 0;
		vector<SDTaskType>::const_iterator it = itr->types.begin();
		for (; it != itr->types.end(); ++it, ++id2) {
			if (m_flag[id1].types[id2].flag.size() != it->tasks.size()) {
				m_flag[id1].types[id2].flag.resize(it->tasks.size(), 0);
				chg = true;
			}
			if (m_flag[id1].types[id2].curr.size() != it->tasks.size()) {
				m_flag[id1].types[id2].curr.resize(it->tasks.size(), 0);
				chg = true;
			}
			size_t id3 = 0;
			vector<SDTaskItem>::const_iterator it1 = it->tasks.begin();
			for (; it1 != it->tasks.end(); ++it1, ++id3) {
				if (!m_task.count(it1->condition.type)) {
					continue;
				}
				if (!m_task[it1->condition.type].counts.count(it1->condition.lv)) {
					continue;
				}
				m_flag[id1].types[id2].curr[id3] = m_task[it1->condition.type].counts[it1->condition.lv];
			}
		}
	}
	if (chg) {
		saveData();
	}
	return true;
}

bool ActSevenDayTask::loadData() {
	CDataState dbc;
	DataState data;
	data.uid = m_uid;
	data.id = PLAYER_DATA_STATE_SEVEN_DAY_TASK;
	int ret = dbc.GetState(data.uid, data.id, data.data);
	if (0 == ret) {
		Json::Value v;
		Json::Reader reader;
		if (reader.parse(data.data, v)) {
			m_ver = v.get("v", 0).asUInt();
			loadTask(v["t"]);
			loadFlag(v["f"]);
		}
		m_isNew = false;
	} else if (R_ERR_NO_DATA == ret) {
		m_isNew = true;
	} else {
		error_log("load data error uid=%u id=%u", m_uid, m_id);
		return false;
	}
	return true;
}

bool ActSevenDayTask::saveData() {
	Json::Value v;
	v["v"] = m_ver;
	v["t"] = Json::Value(Json::objectValue);
	map<byte, ActDataSDTask>::iterator itr = m_task.begin();
	for (; itr != m_task.end(); ++itr) {
		string k = Convert::IntToString(itr->first);
		v["t"][k] = Json::Value(Json::objectValue);
		map<byte, uint32_t>::iterator it = itr->second.counts.begin();
		for (; it != itr->second.counts.end(); ++it) {
			string kk = Convert::IntToString(it->first);
			v["t"][k][kk] = it->second;
		}
	}
	v["f"] = Json::Value(Json::arrayValue);
	for (size_t i = 0; i < m_flag.size(); ++i) {
		Json::Value dd = Json::Value(Json::arrayValue);
		for (size_t j = 0; j < m_flag[i].types.size(); ++j) {
			Json::Value tt = Json::Value(Json::arrayValue);
			for (size_t k = 0; k < m_flag[i].types[j].flag.size(); ++k) {
				tt.append(static_cast<uint32_t>(m_flag[i].types[j].flag[k]));
			}
			dd.append(tt);
		}
		v["f"].append(dd);
	}
	CDataState dbc;
	DataState data;
	data.uid = m_uid;
	data.id = PLAYER_DATA_STATE_SEVEN_DAY_TASK;
	data.data = Json::ToString(v);
	if (m_isNew) {
		m_isNew = false;
		dbc.AddState(data);
	} else {
		dbc.SetState(data);
	}
	return true;
}

bool ActSevenDayTask::encodeData(IBuffer *buff) {
	onLogin();
	onLevel();
	onSoldierColor();
	onGem();
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_id);
	PACKET_ENCODE(UInt32, m_ver);
	PACKET_ENCODE(Byte, m_flag.size());
	for (size_t i = 0; i < m_flag.size(); ++i) {
		PACKET_ENCODE(Byte, m_flag[i].types.size());
		for (size_t j = 0; j < m_flag[i].types.size(); ++j) {
			PACKET_ENCODE(Byte, m_flag[i].types[j].flag.size());
			for (size_t k = 0; k < m_flag[i].types[j].flag.size(); ++k) {
				PACKET_ENCODE(Byte, m_flag[i].types[j].flag[k]);
				PACKET_ENCODE(UInt32, m_flag[i].types[j].curr[k]);
			}
		}
	}
	return true;
}

bool ActSevenDayTask::loadTask(const Json::Value &v) {
	if (v.isNull() || !v.isObject()) {
		return true;
	}
	Json::Value::Members members(v.getMemberNames());
	Json::Value::Members::iterator itr = members.begin();
	for (; itr != members.end(); ++itr) {
		string k = *itr;
		ActDataSDTask task;
		task.type = CTrans::STOI(k);
		if (!v[k].isObject()) {
			continue;
		}
		Json::Value::Members cm(v[k].getMemberNames());
		Json::Value::Members::iterator it = cm.begin();
		for (; it != cm.end(); ++it) {
			string kk = *it;
			byte ik = Convert::StringToInt(kk);
			if (v[k][kk].isIntegral()) {
				task.counts[ik] = v[k][kk].asUInt();
			} else {
				task.counts[ik] = 0;
			}
		}
		m_task.insert(make_pair(task.type, task));
	}
	return true;
}

bool ActSevenDayTask::loadFlag(const Json::Value &v) {
	if (v.isNull() || !v.isArray()) {
		return true;
	}
	for (size_t i = 0; i < v.size(); ++i) {
		if (!v[i].isArray()) {
			continue;
		}
		ActDataSDFlagDay dd;
		for (size_t j = 0; j < v[i].size(); ++j) {
			if (!v[i][j].isArray()) {
				continue;
			}
			ActDataSDFlagType tt;
			for (size_t k = 0; k < v[i][j].size(); ++k) {
				if (v[i][j][k].isIntegral()) {
					tt.flag.push_back(v[i][j][k].asUInt());
				} else {
					tt.flag.push_back(0);
				}
			}
			dd.types.push_back(tt);
		}
		m_flag.push_back(dd);
	}
	return true;
}
bool ActSevenDayTask::onLogin() {
	if (checkTask(SDTaskIdLogin, 1, 0)) {
		saveData();
	}
	return true;
}
bool ActSevenDayTask::onLevel() {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		return false;
	}
	uint32_t lv = player->getLevel();
	ActDataSDTask *task = getTask(SDTaskIdLevel);
	if (task == NULL) {
		return false;
	}
	if (task->counts[0] < lv) {
		task->counts[0] = lv;
	}
	checkTask(SDTaskIdLevel, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onBattleGate(uint32_t id) {
	ActDataSDTask *task = getTask(SDTaskIdBettleGate);
	if (task == NULL) {
		return false;
	}
	if (task->counts[0] > id) {
		return false;
	}
	task->counts[0] = id;
	checkTask(SDTaskIdBettleGate, id, 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onAddSoldier(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdAddSoldier);
	if (task == NULL) {
		return false;
	}
	task->counts[0] += cnt;
	checkTask(SDTaskIdAddSoldier, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onSolderScore(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdSoldierScore);
	if (task == NULL) {
		return false;
	}
	if (task->counts[0] > cnt) {
		return false;
	}
	task->counts[0] = cnt;
	checkTask(SDTaskIdSoldierScore, cnt, 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onExp(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdExp);
	if (task == NULL) {
		return false;
	}
	if (task->counts[0] > cnt) {
		return false;
	}
	task->counts[0] = cnt;
	checkTask(SDTaskIdExp, cnt, 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onBuilding(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdBuilding);
	if (task == NULL) {
		return false;
	}
	task->counts[0] += cnt;
	checkTask(SDTaskIdBuilding, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onPower(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdPower);
	if (task == NULL) {
		return false;
	}
	task->counts[0] = cnt;
	checkTask(SDTaskIdPower, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onZhengwu(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdZhengWu);
	if (task == NULL) {
		return false;
	}
	task->counts[0] += cnt;
	checkTask(SDTaskIdZhengWu, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onBoat(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdBoat);
	if (task == NULL) {
		return false;
	}
	task->counts[0] += cnt;
	checkTask(SDTaskIdBoat, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onBoss(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdBoss);
	if (task == NULL) {
		return false;
	}
	task->counts[0] += cnt;
	checkTask(SDTaskIdBoss, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onSoldierColor() {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		return false;
	}
	ActDataSDTask *task = getTask(SDTaskIdSoldierColor);
	if (task == NULL) {
		return false;
	}
	map<byte, uint32_t> stat;
	const map<uint32_t, Soldier*> &soldiers = player->getSoldierManager()->getSoldier();
	map<uint32_t, Soldier*>::const_iterator itr = soldiers.begin();
	for (; itr != soldiers.end(); ++itr) {
		Soldier *p = itr->second;
		if (p == NULL) {
			continue;
		}
		uint32_t q = p->getQuality();
		if (stat.count(q)) {
			stat[q] += p->getCount();
		} else {
			stat[q] = p->getCount();
		}
	}
	bool chg = false;
	map<byte, uint32_t>::iterator it = stat.begin();
	for (; it != stat.end(); ++it) {
		if (!task->counts.count(it->first)) {
			task->counts[it->first] = it->second;
			checkTask(SDTaskIdSoldierColor, task->counts[it->first], it->first);
			chg = true;
		} else if (task->counts[it->first] < it->second) {
			task->counts[it->first] = it->second;
			checkTask(SDTaskIdSoldierColor, task->counts[it->first], it->first);
			chg = true;
		}
	}
	if (chg) {
		saveData();
	}
	return true;
}
bool ActSevenDayTask::onDefendGate(uint32_t id) {
	ActDataSDTask *task = getTask(SDTaskIdDefendGate);
	if (task == NULL) {
		return false;
	}
	if (task->counts[0] > id) {
		return false;
	}
	task->counts[0] = id;
	checkTask(SDTaskIdDefendGate, id, 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onGem() {
	ActDataSDTask *task = getTask(SDTaskIdGem);
	if (task == NULL) {
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(m_uid);
	if (player == NULL) {
		return false;
	}
	bool chg = false;
	map<byte, uint32_t> gem;
	player->getGemManager()->getGem(gem);
	map<byte, uint32_t>::iterator it = gem.begin();
	for (; it != gem.end(); ++it) {
		if (!task->counts.count(it->first)) {
			task->counts[it->first] = it->second;
			checkTask(SDTaskIdGem, task->counts[it->first], it->first);
			chg = true;
		} else if (task->counts[it->first] < it->second) {
			task->counts[it->first] = it->second;
			checkTask(SDTaskIdGem, task->counts[it->first], it->first);
			chg = true;
		}
	}
	if (chg) {
		saveData();
	}
	return true;
}
bool ActSevenDayTask::onArenaWin(uint32_t cnt) {
	ActDataSDTask *task = getTask(SDTaskIdArenaWin);
	if (task == NULL) {
		return false;
	}
	task->counts[0] += cnt;
	checkTask(SDTaskIdArenaWin, task->counts[0], 0);
	saveData();
	return true;
}
bool ActSevenDayTask::onArenaRank(uint32_t cnt) {
	if (cnt == 0) {
		return false;
	}
	ActDataSDTask *task = getTask(SDTaskIdArenaRank);
	if (task == NULL) {
		return false;
	}
	if (task->counts[0] < cnt) {
		return false;
	}
	task->counts[0] = cnt;
	checkTask(SDTaskIdArenaRank, cnt, 0, true);
	saveData();
	return true;
}
bool ActSevenDayTask::checkTask(byte type, uint32_t cnt, byte lv, bool lt) {
	bool chg = false;
	uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(m_id);
	for (uint32_t i = 0; i < day; ++i) {
		if (m_flag.size() <= i) {
			error_log("day error day=%u size=%u", day, m_flag.size());
			continue;
		}
		for (size_t j = 0; j < m_flag[i].types.size(); ++j) {
			for (size_t k = 0; k < m_flag[i].types[j].flag.size(); ++k) {
				if (m_flag[i].types[j].flag[k] != 0) {
					continue;
				}
				const SDTaskItem *cfg = SevenDayTaskConfig::getInstance()->getItem(i + 1, j + 1, k + 1);
				if (cfg == NULL) {
					error_log("cfg error day=%u type=%u id=%u", i, j, k);
					continue;
				}
				if (cfg->condition.type == type
				&& cfg->condition.lv == lv) {
					uint32_t require = cfg->condition.count;
					if (cfg->condition.multiple > 0) {
						require *= cfg->condition.multiple;
					}
					if (lt) {
						if (require >= cnt) {
							m_flag[i].types[j].flag[k] = 1;
						} else {
							require = cnt;
						}
					} else {
						if (require <= cnt) {
							m_flag[i].types[j].flag[k] = 1;
						} else {
							require = cnt;
						}
					}
					if (m_flag[i].types[j].curr.size() != m_flag[i].types[j].flag.size()) {
						m_flag[i].types[j].curr.resize(m_flag[i].types[j].flag.size(), 0);
					}
					m_flag[i].types[j].curr[k] = require;
					chg = true;
				}
			}
		}
	}
	return chg;
}
ActDataSDTask* ActSevenDayTask::getTask(byte type) {
	uint32_t day = ActivityTimeManager::getInstance()->getOpenDay(m_id);
	if (!SevenDayTaskConfig::getInstance()->checkOpen(type, day)) {
		return NULL;
	}
	if (m_task.count(type)) {
		return &(m_task[type]);
	}
	ActDataSDTask task;
	task.type = type;
	switch (type) {
	case SDTaskIdLevel:
	case SDTaskIdBettleGate:
	case SDTaskIdAddSoldier:
	case SDTaskIdSoldierScore:
	case SDTaskIdExp:
	case SDTaskIdBuilding:
	case SDTaskIdPower:
	case SDTaskIdZhengWu:
	case SDTaskIdBoat:
	case SDTaskIdBoss:
	case SDTaskIdDefendGate:
	case SDTaskIdArenaWin:
		task.counts[0] = 0;
		break;
	case SDTaskIdArenaRank:
		task.counts[0] = ARENA_RANK_INVALID;
		break;
	case SDTaskIdGem:
	case SDTaskIdSoldierColor:
		task.counts[1] = 0;
		task.counts[2] = 0;
		task.counts[3] = 0;
		task.counts[4] = 0;
		task.counts[5] = 0;
		break;
	}
	m_task.insert(make_pair(type, task));
	return &(m_task[type]);
}
