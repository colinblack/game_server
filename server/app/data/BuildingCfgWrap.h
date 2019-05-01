/*
 * BuildingCfgWrap.h
 *
 *  Created on: 2016-9-1
 *      Author: dawx62fac
 */

#ifndef BUILDINGCFGWRAP_H_
#define BUILDINGCFGWRAP_H_

#include "ConfigInc.h"


class BuildCfgWrap
{
public:
	BuildCfgWrap();
	const Building::Buildings& BuildingCfg() const;

	//
	unsigned LevelLimit(unsigned buildid) const;
	unsigned UnlockTime(unsigned buildid) const;
	unsigned SpeedTime(unsigned buildid, unsigned level) const;
	unsigned UpgradeTime(unsigned buildid, unsigned level) const;
	const Building::Item& Item(unsigned buildid) const;
	const Building::LvLs& LvLs(unsigned buildid, unsigned level) const;

private:
	const Building::Buildings& cfg_;
};



#endif /* BUILDINGCFGWRAP_H_ */
