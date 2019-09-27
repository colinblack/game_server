/*
 * ActivityConfig.h
 *
 *  Created on: 2017-5-15
 *      Author: dawx62fac
 */

#ifndef ACTIVITYCONFIG_H_
#define ACTIVITYCONFIG_H_

#include "Kernel.h"

/**
 * 活动时间配置
 */
class ActInfoConfig
{
public:
	ActInfoConfig(const std::string& name = "")
		: name_(name)
	{

	}

	int init(const std::string& name)
	{
		name_ = name;
		return 0;
	}

	/**
	 * 活动是否开启
	 */
	bool IsActive() const
	{
		int now = Time::GetGlobalTime();
		return ((now <= EndTS()) && (now >= StartTS()));
	}

	bool IsLastDay() const {
		return (EndTS() - Time::GetGlobalTime()) < CTime::SECONDS_OF_DAY;
	}

	int StartTS() const
	{
		int value = 0;
		if(name_ == CONFIG_OPENSERVER_GIFT) {
			unsigned value = Config::GetIntValue("open_ts");
			return value;
		} else {
			if (Config::GetIntValue(value, "activity_" + name_ + "_begin_ts"))
			{
				return value;
			}
			throw std::runtime_error("not_config_start_ts");
		}
	}

	int EndTS() const
	{
		int value = 0;
		if(name_ == CONFIG_OPENSERVER_GIFT) {
			unsigned value = Config::GetIntValue("open_ts");
			value = value + 30 * 24 * 3600; //一个月
			return value;

		} else {
			if (Config::GetIntValue(value, "activity_" + name_ + "_end_ts"))
			{
				return value;
			}
			throw std::runtime_error("not_config_end_ts");
		}
	}

	int Version() const
	{
		int value = 0;
		if(name_ == CONFIG_OPENSERVER_GIFT) {
			return value;
		} else {
			if (Config::GetIntValue(value, "activity_" + name_ + "_ver"))
			{
				return value;
			}

			throw std::runtime_error("not_config_version");
		}
	}

	std::string Platform() const
	{
		std::string value;
		if(name_ == CONFIG_OPENSERVER_GIFT) {
			return "all";
		} else {
			if (Config::GetValue(value, "activity_" + name_ + "_pf"))
			{
				return value;
			}

			throw std::runtime_error("not_config_pf");
		}

	}

	std::string Type() const
	{
		std::string value;
		if (Config::GetValue(value, "activity_" + name_ + "_type"))
		{
			return value;
		}
		return "";
	}

	std::string GetName() const
	{
		return name_;
	}

	void full_act_info(Json::Value& result) const;
private:
	std::string name_;
};

void full_all_act_info(Json::Value& result);




#endif /* ACTIVITYCONFIG_H_ */
