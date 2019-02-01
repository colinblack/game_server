/*
 * HeroPropertyManager.cpp
 *
 *  Created on: 2018年7月9日
 *      Author: colin
 */

#include "HeroPropertyManager.h"
#include "ServerInc.h"

HeroAttr::HeroAttr()
{
	memset(val_, 0, sizeof(val_));
}

void HeroAttr::Clear()
{
	memset(val_, 0, sizeof(val_));
}

void HeroAttr::SetAttr(HeroProperty attr, unsigned val)
{
	val_[(int)attr] = val;
}

void HeroAttr::AddAttr(HeroProperty attr, unsigned val)
{
	val_[(int)attr] += val;
}

unsigned HeroAttr::GetAttr(HeroProperty attr) const
{
	return val_[(int)attr];
}

void HeroAttr::SetAllAttr(map<unsigned, double> & addition_percent, map<unsigned, unsigned> &addition_value,  unsigned heroid, unsigned level)
{
	if(level < 1)
	{
		throw runtime_error("level_error");
	}

	map<unsigned, unsigned> config_value;
	const Hero::HeroInfoList& heros = HeroCfgWrap().GetHeroByHeroId(heroid);
	config_value[HeroProperty_hp] =    heros.attr().levelattr(level-1).hp();
	config_value[HeroProperty_attack] = heros.attr().levelattr(level-1).att();
	config_value[HeroProperty_defend] = heros.attr().levelattr(level-1).def();
	config_value[HeroProperty_first] = heros.attr().levelattr(level-1).first();
	config_value[HeroProperty_hit] = heros.attr().hit();
	config_value[HeroProperty_dodge] = heros.attr().dodge();
	config_value[HeroProperty_crit_strike] = heros.attr().critstrike();
	config_value[HeroProperty_crit_resist] = heros.attr().critresist();
	config_value[HeroProperty_crit_rate] =  heros.attr().critrate();


	for(auto iter = config_value.begin(); iter != config_value.end(); ++iter)
	{
		unsigned value = iter->second;
		unsigned type = iter->first;
		if(addition_percent.count(type))
			value += static_cast<unsigned>(addition_percent[type] * value);
		if(addition_value.count(type))
			value += addition_value[type];

		SetAttr((HeroProperty)type, value);
	}

}
