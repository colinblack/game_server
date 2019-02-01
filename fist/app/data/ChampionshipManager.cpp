/*
 * ChampionshipManager.cpp
 *
 *  Created on: 2019年1月24日
 *      Author: colin
 */

#include "ChampionshipManager.h"
#include "DataInc.h"



vector<BattleDemoHero> PlayerItem::GetBattleDemo()
{
	vector<BattleDemoHero> hero;
	hero.reserve(2);
	for(int i = 0; i < hero_num; ++i)
	{
		vector<BattleDemoHeroSkill> skills;
		for(int j = 0; j < e_skill_max; ++j)
		{
			auto& skill = heros[i].skills[j];
			skills.push_back(BattleDemoHeroSkill(skill.id, skill.type, skill.mul, skill.hurt, skill.p_c, skill.p_a));
		}

		auto& attr = heros[i];
		hero.push_back(BattleDemoHero(attr.id, attr.hp, attr.att, attr.def, attr.crit,
							attr.acrit, attr.dodge, attr.adodge, attr.critt, attr.speed, attr.battlePower, skills));
	}

	return hero;
}


vector<BattleDemoItem> PlayerItem::GetBattleItem()
{
	vector<BattleDemoItem> item;
	item.reserve(2);
	for(int i = 0; i < 2; ++i)
	{
		if(props[i] == 0)
			continue;
		auto& cfg = ItemCfgWrap().GetPropsItem(props[i]);
		item.push_back(BattleDemoItem(props[i], cfg.type(), cfg.factor(), cfg.value(), cfg.turn()));
	}

	return item;
}

CommonGiftConfig::CommonModifyItem PlayerItem::GetConfigItem()
{
	CommonGiftConfig::CommonModifyItem cfg;
	for(int i = 0; i < 2; ++i)
	{
		if(props[i] == 0)
			continue;
		auto prop = cfg.add_props();
		prop->set_id(props[i]);
		prop->set_count(-1);
	}

	return cfg;
}
