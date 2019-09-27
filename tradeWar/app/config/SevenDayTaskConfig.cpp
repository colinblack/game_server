/*
 * SevenDayTaskConfig.cpp
 *
 *  Created on: 2019年2月19日
 *      Author: Administrator
 */

#include "SevenDayTaskConfig.h"
#include "ConfigJson.h"

SevenDayTaskConfig::SevenDayTaskConfig() {
	m_data.clear();
	m_types.clear();
}
SevenDayTaskConfig::~SevenDayTaskConfig() {

}
bool SevenDayTaskConfig::init(const string &path) {
	m_data.clear();
	m_types.clear();

	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *tasks = fileParser.getMember("tasks");
	if (tasks == NULL || !tasks->isArray()) {
		error_log("tasks error");
		return false;
	}
	for (size_t i = 0; i < tasks->size(); ++i) {
		const Json::Value &item = tasks->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		SDTask cfg;
		cfg.day = item.get("day", 0).asUInt();
		set<byte> &types = m_types[cfg.day];
		const Json::Value &data = item["data"];
		for (size_t k = 0; k < data.size(); ++k) {
			SDTaskType ctype;
			ctype.id = data[k].get("id", 0).asUInt();
			const Json::Value &task = data[k]["task"];
			for (size_t j = 0; j < task.size(); ++j) {
				SDTaskItem titem;
				titem.id = task[j].get("id", 0).asUInt();
				titem.box = task[j].get("box", 0).asUInt();
				titem.card = task[j].get("card", 0).asUInt();
				titem.reward.Json2Award(task[j]["reward"]);
				const Json::Value &condition = task[j]["condition"];
				titem.condition.type = condition.get("type", 0).asUInt();
				titem.condition.count = condition.get("count", 0).asUInt();
				titem.condition.lv = condition.get("level", 0).asUInt();
				titem.condition.multiple = condition.get("beishu", 0).asUInt();
				ctype.tasks.push_back(titem);
				types.insert(titem.condition.type);
			}
			cfg.types.push_back(ctype);
		}
		m_data.push_back(cfg);
	}
	return true;
}

const SDTaskItem* SevenDayTaskConfig::getItem(byte day, byte type, byte id) const {
	vector<SDTask>::const_iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		if (day != itr->day) {
			continue;
		}
		vector<SDTaskType>::const_iterator titr = itr->types.begin();
		for (; titr != itr->types.end(); ++titr) {
			if (type != titr->id) {
				continue;
			}
			vector<SDTaskItem>::const_iterator iitr = titr->tasks.begin();
			for (; iitr != titr->tasks.end(); ++iitr) {
				if (id != iitr->id) {
					continue;
				}
				return &(*iitr);
			}
		}
	}
	return NULL;
}

const vector<SDTask>& SevenDayTaskConfig::getAll() const {
	return m_data;
}

bool SevenDayTaskConfig::checkOpen(byte type, byte day) const {
	map<byte, set<byte> >::const_iterator itr = m_types.begin();
	for (; itr != m_types.end(); ++itr) {
		if (itr->first > day) {
			continue;
		}
		if (itr->second.count(type) > 0) {
			return true;
		}
	}
	return false;
}
