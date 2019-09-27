/*
 * OpenServerConfig.h
 *
 *  Created on: 2018年12月10日
 *      Author: Administrator
 */

#ifndef OPEN_SERVER_CONFIG_H_
#define OPEN_SERVER_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct OpenServerConfigTask {
	byte type;
	vector<uint32_t> require;
	vector<uint32_t> reward;

	OpenServerConfigTask() {
		type = 0;
		require.clear();
		reward.clear();
	}
};

struct OpenServerConfigReward {
	uint32_t id;
	Award reward;

	OpenServerConfigReward() {
		id = 0;
	}
};

class OpenServerConfig {
	SINGLETON_CLASS(OpenServerConfig);
	bool init(const string &path);
	bool parseTask(const Json::Value &v, vector<OpenServerConfigTask> &t);
	bool parseReward(const Json::Value &v, vector<OpenServerConfigReward> &t);
	bool randomDaily(uint32_t type, set<uint32_t> &ids);
	bool getWeekClass(uint32_t type, uint32_t id, uint32_t cnt, uint32_t &c);
	const OpenServerConfigTask* getDaily(uint32_t type, uint32_t id) const;
	const OpenServerConfigTask* getWeek(uint32_t type, uint32_t id) const;
	const OpenServerConfigReward* getReward(uint32_t type, uint32_t id, bool pay) const;
private:
	map<uint32_t, vector<OpenServerConfigTask> > m_daily;
	map<uint32_t, vector<OpenServerConfigTask> > m_week;
	map<uint32_t, vector<OpenServerConfigReward> > m_free;
	map<uint32_t, vector<OpenServerConfigReward> > m_pay;
};

#endif /* OPEN_SERVER_CONFIG_H_ */
