/*
 * DailyQuestConfig.cpp
 *
 *  Created on: 2017年12月27日
 *      Author: Administrator
 */

#include "DailyQuestConfig.h"

DailyQuestConfig::DailyQuestConfig()
{
}

DailyQuestConfig::~DailyQuestConfig()
{
}

bool DailyQuestConfig::init(const string &path)
{
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret)
	{
		error_log("read error!");
		return false;
	}
	Json::Reader reader;
	Json::Value content;
	if (!reader.parse(buffer, content))
	{
		error_log("parse error!mst=%s", reader.getFormatedErrorMessages().c_str());
		return false;
	}
	Json::Value &dailyDetail = content["dailyDetails"]["dailyDetail"];
	if (dailyDetail.isNull() || !dailyDetail.isArray())
	{
		error_log("dailyDetail error!");
		return false;
	}
	for (size_t i = 0; i < dailyDetail.size(); ++i)
	{
		Json::Value &item = dailyDetail[i];
		DailyQuestItem config;
		config.id = String::s2i(item["id"].asString(), 0);
		config.count = String::s2i(item["times"].asString(), 0);
		config.level = String::s2i(item["openLevel"].asString(), 0);
		config.score = String::s2i(item["lively"].asString(), 0);
		config.reward.Json2Award(item["data"]["reward"]);
		m_items.push_back(config);
	}

	Json::Value &dailyReward = content["dailyReward"]["reward"];
	if (dailyReward.isNull() || !dailyReward.isArray())
	{
		error_log("dailyReward error!");
		return false;
	}
	for (size_t i = 0; i < dailyReward.size(); ++i)
	{
		Json::Value &item = dailyReward[i];
		string idStr, livelyStr;
		if (!Json::GetString(item, "id", idStr))
		{
			continue;
		}
		if (!Json::GetString(item, "lively", livelyStr))
		{
			livelyStr.clear();
		}
		DailyQuestReward reward;
		reward.id = String::s2i(idStr, 0);
		reward.score = String::s2i(livelyStr, 0);
		if (item.isMember("data"))
		{
			reward.reward.Json2Award(item["data"]["reward"]);
		}
		m_reward.push_back(reward);
	}
	return true;
}

bool DailyQuestConfig::getItemIds(set<uint32_t> &ids)
{
	vector<DailyQuestItem>::const_iterator itr = m_items.begin();
	for (; itr != m_items.end(); ++itr)
	{
		ids.insert(itr->id);
	}
	return true;
}

const DailyQuestItem* DailyQuestConfig::getItem(uint32_t id) const
{
	vector<DailyQuestItem>::const_iterator itr = find(m_items.begin(), m_items.end(), id);
	if (itr != m_items.end())
	{
		return &(*itr);
	}
	return NULL;
}

const DailyQuestReward* DailyQuestConfig::getReward(uint32_t index) const
{
	return (m_reward.size() <= index) ? NULL : &(m_reward[index]);
}

const uint32_t DailyQuestConfig::getRewardSize() const
{
	return m_reward.size();
}
