/*
 * BuildingCfgWrap.cpp
 *
 *  Created on: 2016-9-1
 *      Author: dawx62fac
 */

#include <stdexcept>


#include "BuildingCfgWrap.h"
#include "ConfigManager.h"



BuildCfgWrap::BuildCfgWrap()
	: cfg_(ConfigManager::Instance()->buildings.m_config)
{
	//cfg_ = ;
}

const Building::Buildings& BuildCfgWrap::BuildingCfg() const
{
	return cfg_;
}

const Building::Item& BuildCfgWrap::Item(unsigned buildid) const
{
	const std::map<unsigned, unsigned>& buildMap = ConfigManager::Instance()->m_mapBuildIndex;
	std::map<unsigned, unsigned>::const_iterator it = buildMap.find(buildid);
	if (it != buildMap.end())
	{
		int index = it->second;
		return cfg_.buildings(index);
	}
	else
	{
		error_log("build_id: %d", buildid);
		throw std::runtime_error("get_cfg_error");
	}
}

unsigned BuildCfgWrap::LevelLimit(unsigned buildid) const
{
	return (unsigned)Item(buildid).unlock_lvl();
}

unsigned BuildCfgWrap::UnlockTime(unsigned buildid) const
{
	return (unsigned)Item(buildid).unlock_time();
}

const Building::LvLs& BuildCfgWrap::LvLs(unsigned buildid, unsigned level) const
{
	const Building::Item& item = Item(buildid);

	//先在对应的位置匹配
	for (int i = level - 1; i < item.lvls_size(); ++i)
	{
		if (item.lvls(i).lvl() == level)
		{
			return item.lvls(i);
		}
	}

	for (int i = 0; i < level && i < item.lvls_size(); i++)
	{
		if (item.lvls(i).lvl() == level)
		{
			return item.lvls(i);
		}
	}

	error_log("build_id: %d, level: %d", buildid, level);
	throw std::runtime_error("get_cfg_error");
}

unsigned BuildCfgWrap::SpeedTime(unsigned buildid, unsigned level) const
{
	const Building::LvLs& lvls = LvLs(buildid, level);
	return lvls.accelerate_time() * lvls.upgrade_cd() / 100;
}

unsigned BuildCfgWrap::UpgradeTime(unsigned buildid, unsigned level) const
{
	const  Building::LvLs& lvls = LvLs(buildid, level);
	return lvls.upgrade_cd();
}



