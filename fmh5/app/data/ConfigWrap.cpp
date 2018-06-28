/*
 * UserCfgWrap.cpp
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#include "ConfigWrap.h"

///////////////////////////////////////////////////////////////////////////
ActivityCfgWrap::ActivityCfgWrap()
	: cfg_(ConfigManager::Instance()->activity.m_config)
{
}

const User::ActivityItem& ActivityCfgWrap::GetItem(unsigned id) const
{
	for(int i = 0; i < cfg_.act_size(); ++i)
	{
		if (cfg_.act(i).id() == id)
		{
			return cfg_.act(i);
		}
	}

	error_log("unknown_activity_cfg. id: %u", id);
	throw std::runtime_error("unknown_activity_cfg");
}
//////////////////////////////////////////////////////////////////////////
