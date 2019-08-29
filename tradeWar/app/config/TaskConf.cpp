#include "TaskConf.h"
#include "ConfigJson.h"

TaskConf::TaskConf() {
	m_data.clear();
	m_first.clear();
	m_achievements.clear();
}
TaskConf::~TaskConf() {
}
bool TaskConf::init(const string& path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *quest = fileParser.getMember("quests.quest");
	if (quest == NULL || !quest->isArray()) {
		error_log("quest error");
		return false;
	}
	bool idRepeat = false;
	for (size_t i = 0; i < quest->size(); ++i) {
		const Json::Value &item = quest->get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		TaskConfig xml;
		string idStr, preStr, typeStr;
		Json::GetString(item, "id", idStr);
		Json::GetString(item, "pre", preStr);
		Json::GetString(item, "type", typeStr);
		const Json::Value &elemValue = item.get("data", Json::Value(Json::nullValue));
		if (elemValue.isNull() || !elemValue.isObject()) {
			error_log("data error");
			return false;
		}
		if (elemValue.isMember("condition") && elemValue["condition"].isArray()) {
			for (size_t j = 0; j < elemValue["condition"].size(); ++j) {
				const Json::Value &condition = elemValue["condition"][j];
				TaskTarget tar;
				tar.type = condition.get("type", 0).asUInt();
				tar.count = condition.get("count", 0).asUInt();
				string cid = condition.get("id", "").asString();
				if (!cid.empty()) {
					tar.id = String::s2i(cid.at(0) == 'S' ? cid.substr(1) : cid, 0);
				}
				tar.lv = condition.get("lv", 0).asUInt();
				xml.targets.push_back(tar);
			}
		}
		xml.rewards.Json2Award(elemValue["reward"]);

		xml.id = String::s2i(idStr, 0);
		xml.type = String::s2i(typeStr, 0);

		if (xml.type > 2) {
			continue;
		}

		vector<string> preVec;
		String::Split(preStr, ',', preVec);
		if (!preVec.empty()) {
			for (vector<string>::iterator it = preVec.begin(); it != preVec.end(); ++it) {
				xml.pre.push_back(String::s2i(*it, 0));
			}
		} else {
			m_first.insert(xml.id);
		}
		if (m_data.find(xml.id) != m_data.end()) {
			error_log("task id already exist id=%u", xml.id);
			idRepeat = true;
		}
		m_data[xml.id] = xml;
	}
	if (idRepeat) {
		error_log("task id repeat");
		return false;
	}

	map<uint32_t, TaskConfig>::iterator iter = m_data.begin();
	for (; iter != m_data.end(); ++iter) {
		for (size_t i = 0; i < iter->second.pre.size(); ++i) {
			if (m_data.find(iter->second.pre[i]) != m_data.end()) {
				m_data[iter->second.pre[i]].next.push_back(iter->first);
			}
		}
	}

	for (set<uint32_t>::iterator itr = m_first.begin(); itr != m_first.end(); ++itr) {
		uint32_t curr = *itr;
		while (true) {
			if (curr == 0 || !m_data.count(curr)) {
				break;
			}
			const TaskConfig &cfg = m_data[curr];
			if (cfg.type != TASK_GROUP_ACHIVMENT || cfg.targets.empty()) {
				break;
			}
			uint32_t type = cfg.targets.begin()->type;
			vector<uint32_t> &ach = m_achievements[type];
			ach.push_back(curr);
			if (cfg.next.empty()) {
				break;
			}
			curr = cfg.next.front();
		}
	}

	map<uint32_t, vector<uint32_t> >::iterator aitr = m_achievements.begin();
	for (; aitr != m_achievements.end(); ++aitr) {
		vector<uint32_t> &ach = aitr->second;
		string log;
		for (vector<uint32_t>::iterator it = ach.begin(); it != ach.end(); ++it) {
			log += CTrans::ITOS(*it) + "_";
		}
		debug_log("type=%u,ids=%s", aitr->first, log.c_str());
	}

	return true;
}

const TaskConfig* TaskConf::getConfById(uint32_t id) const {
	map<uint32_t, TaskConfig>::const_iterator it = m_data.find(id);
	if (it != m_data.end()) {
		return &(it->second);
	}
	return NULL;
}

const set<uint32_t>* TaskConf::getFirst() const {
	return &m_first;
}

const TaskConfig* TaskConf::getAchievement(uint32_t type, uint32_t id) const {
	if (id < 1) {
		error_log("id error type=%u", type);
		return NULL;
	}
	map<uint32_t, vector<uint32_t> >::const_iterator itr = m_achievements.find(type);
	if (itr == m_achievements.end()) {
		return NULL;
	}
	if (itr->second.size() <= id - 1) {
		return NULL;
	}
	uint32_t tid = *(itr->second.begin() + id - 1);
	return getConfById(tid);
}

uint32_t TaskConf::getAchievementIndex(uint32_t type, uint32_t id) const {
	map<uint32_t, vector<uint32_t> >::const_iterator itr = m_achievements.find(type);
	if (itr == m_achievements.end()) {
		return 0;
	}
	uint32_t index = 1;
	vector<uint32_t>::const_iterator it = itr->second.begin();
	for (; it != itr->second.end(); ++it, ++index) {
		if (id == *it) {
			return index;
		}
	}
	return 0;
}
