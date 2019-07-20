/*
 * ConfigManager.cpp
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */

#include "ConfigManager.h"

bool ConfigManager::m_init = true;

bool ConfigManager::Reload() {
	ConfigManager *temp = new ConfigManager;
	if (!m_init) {
		m_init = true;
		delete temp;
		return false;
	}
	delete temp;
	Destroy();
	temp = Instance();
	return true;
}

void ConfigManager::Init() {
	if (!m_init) {
		return;
	}
	map_cfg_Index.clear();
	for (int i = 0; i < map_cfg_.m_config.maps_size(); ++i) {
		map_cfg_Index.insert(make_pair(map_cfg_.m_config.maps(i).id(), i));
	}
	scene_cfg_Index.clear();
	for (int i = 0; i < scene_cfg_.m_config.scenes_size(); ++i) {
		scene_cfg_Index.insert(make_pair(scene_cfg_.m_config.scenes(i).id(), i));
	}
	skill_cfg_Index.clear();
	skill_cfg_serial_Index.clear();
	for (int i = 0; i < skill_cfg_.m_config.skills_size(); ++i) {
		skill_cfg_Index.insert(make_pair(skill_cfg_.m_config.skills(i).id(), i));
		map<uint32_t, uint32_t> &item = skill_cfg_serial_Index[skill_cfg_.m_config.skills(i).serial()];
		item[skill_cfg_.m_config.skills(i).level()] = i;
	}
	skill_base_cfg_Index.clear();
	for (int i = 0; i < skill_base_cfg_.m_config.bases_size(); ++i) {
		skill_base_cfg_Index.insert(make_pair(skill_base_cfg_.m_config.bases(i).id(), i));
	}
	skill_monster_cfg_Index.clear();
	for (int i = 0; i < skill_monster_cfg_.m_config.skills_size(); ++i) {
		skill_monster_cfg_Index.insert(make_pair(skill_monster_cfg_.m_config.skills(i).id(), i));
	}
	hang_plan_cfg_Index.clear();
	for (int i = 0; i < hang_plan_cfg_.m_config.plans_size(); ++i) {
		hang_plan_cfg_Index.insert(make_pair(hang_plan_cfg_.m_config.plans(i).id(), i));
	}
	hang_cfg_Index.clear();
	for (int i = 0; i < hang_cfg_.m_config.hangs_size(); ++i) {
		hang_cfg_Index.insert(make_pair(hang_cfg_.m_config.hangs(i).id(), i));
	}
	monster_cfg_Index.clear();
	for (int i = 0; i < monster_cfg_.m_config.monsters_size(); ++i) {
		monster_cfg_Index.insert(make_pair(monster_cfg_.m_config.monsters(i).id(), i));
	}
	monster_plan_cfg_Index.clear();
	for (int i = 0; i < monster_plan_cfg_.m_config.plans_size(); ++i) {
		monster_plan_cfg_Index.insert(make_pair(monster_plan_cfg_.m_config.plans(i).id(), i));
	}
	level_cfg_Index.clear();
	for (int i = 0; i < level_cfg_.m_config.levels_size(); ++i) {
		level_cfg_Index.insert(make_pair(level_cfg_.m_config.levels(i).id(), i));
	}
	level_attr_cfg_Index.clear();
	for (int i = 0; i < level_attr_cfg_.m_config.levels_size(); ++i) {
		level_attr_cfg_Index.insert(make_pair(level_attr_cfg_.m_config.levels(i).level(), i));
	}
	mission_cfg_Index.clear();
	for (int i = 0; i < mission_cfg_.m_config.missions_size(); ++i) {
		mission_cfg_Index.insert(make_pair(mission_cfg_.m_config.missions(i).id(), i));
	}
	advance_cfg_Index.clear();
	string advance_key;
	for (int i = 0; i < advance_cfg_.m_config.advances_size(); ++i) {
		advance_key.clear();
		const CfgAdvance::Advance &item = advance_cfg_.m_config.advances(i);
		String::Format(advance_key, "%u_%u_%u", item.type(), item.group(), item.star());
		advance_cfg_Index.insert(make_pair(advance_key, i));
	}

	// fix by memory
	purify_cfg_Index.clear();
	for (int i = 0; i < purify_cfg_.m_config.purifys_size(); ++i) {
		const CfgPurify::Purify &item = purify_cfg_.m_config.purifys(i);
		purify_cfg_Index.insert(make_pair(item.level(), i));
	}

	title_cfg_Index.clear();
	for (int i = 0; i < title_cfg_.m_config.titles_size(); ++i) {
		const CfgTitle::Title &item = title_cfg_.m_config.titles(i);
		title_cfg_Index.insert(make_pair(item.id(), i));
	}

	advance_dan_cfg_Index.clear();
	string advance_dan_key;
	for (int i = 0; i < advance_dan_cfg_.m_config.dans_size(); ++i) {
		advance_dan_key.clear();
		const CfgAdvance::Dan &item = advance_dan_cfg_.m_config.dans(i);
		String::Format(advance_dan_key, "%u_%u", item.type(), item.level());
		list<uint32_t> &pool = advance_dan_cfg_Index[advance_dan_key];
		pool.push_back(i);
	}
	item_cfg_Index.clear();
	for (int i = 0; i < item_cfg_.m_config.items_size(); ++i) {
		item_cfg_Index.insert(make_pair(item_cfg_.m_config.items(i).id(), i));
	}
	equip_cfg_Index.clear();
	for (int i = 0; i < equip_cfg_.m_config.equips_size(); ++i) {
		equip_cfg_Index.insert(make_pair(equip_cfg_.m_config.equips(i).id(), i));
	}
	gift_cfg_Index.clear();
	for (int i = 0; i < gift_cfg_.m_config.gifts_size(); ++i) {
		gift_cfg_Index.insert(make_pair(gift_cfg_.m_config.gifts(i).id(), i));
	}
	equip_attr_cfg_Pool.clear();
	equip_attr_cfg_Index.clear();
	for (int i = 0; i < equip_attr_cfg_.m_config.attrs_size(); ++i) {
		const CfgItem::Attr &item = equip_attr_cfg_.m_config.attrs(i);
		list<uint32_t> &group = equip_attr_cfg_Pool[item.group()];
		group.push_back(i);
		equip_attr_cfg_Index[item.id()] = i;
	}
	shenqi_cfg_Index.clear();
	for (int i = 0; i < shenqi_cfg_.m_config.shenqis_size(); ++i) {
		set<uint32_t> &items = shenqi_cfg_Index[shenqi_cfg_.m_config.shenqis(i).id()];
		items.insert(shenqi_cfg_.m_config.shenqis(i).item());
	}
	drop_cfg_Index.clear();
	for (int i = 0; i < drop_cfg_.m_config.drops_size(); ++i) {
		drop_cfg_Index[drop_cfg_.m_config.drops(i).id()] = i;
	}

	CfgItem::ShenQis &shenqi = const_cast<ConfigPB<CfgItem::ShenQis>&>(shenqi_cfg_).m_config;
	shenqi.Clear();

	bag_grid_cfg_Index.clear();
	for (int i = 0; i < bag_grid_cfg_.m_config.grids_size(); ++i) {
		map<uint32_t, uint32_t> &items = bag_grid_cfg_Index[bag_grid_cfg_.m_config.grids(i).type()];
		items[bag_grid_cfg_.m_config.grids(i).num()] = bag_grid_cfg_.m_config.grids(i).cost();
	}
	CfgBag::Grids &bagGrid = const_cast<ConfigPB<CfgBag::Grids>&>(bag_grid_cfg_).m_config;
	bagGrid.Clear();

	attr_def_cfg_Index.clear();
	for (int i = 0; i < attr_def_cfg_.m_config.attr_defs_size(); ++i) {
		map<uint32_t, uint32_t> &group = attr_def_cfg_Index[attr_def_cfg_.m_config.attr_defs(i).group()];
		group[attr_def_cfg_.m_config.attr_defs(i).type()] = i;
	}

	equip_strengthen_cfg_Index.clear();
	for (int i = 0; i < equip_strengthen_cfg_.m_config.strengthens_size(); ++i) {
		equip_strengthen_cfg_Index[equip_strengthen_cfg_.m_config.strengthens(i).id()] = i;
	}

	dungeon_cfg_Index.clear();
	for (int i = 0; i < dungeon_cfg_.m_config.dungeonconfig_size(); ++i) {
		dungeon_cfg_Index.insert(make_pair(dungeon_cfg_.m_config.dungeonconfig(i).id(), i));
	}
	
	treasure_cfg_index.clear();
	for(int i = 0; i < treasure_cfg_.m_config.treasures_size(); ++i) {
		treasure_cfg_index.insert(make_pair(treasure_cfg_.m_config.treasures(i).id(), i));
	}
	treasure_hunt_cfg_map.clear();
	treasure_hunt_cfg_Index.clear();
	for (int i = 0; i < treasure_hunt_cfg_.m_config.hunts_size(); ++i) {
		const CfgTreasure::Hunt &item = treasure_hunt_cfg_.m_config.hunts(i);
		map<uint32_t, list<int32_t> > &data = treasure_hunt_cfg_map[item.type()];
		list<int32_t> &pool = data[item.must()];
		pool.push_back(i);
		treasure_hunt_cfg_Index[item.id()] = i;
	}
	treasure_hunt_base_cfg_Index.clear();
	for (int i = 0; i < treasure_hunt_base_cfg_.m_config.bases_size(); ++i) {
		const CfgTreasure::HuntBase &item = treasure_hunt_base_cfg_.m_config.bases(i);
		treasure_hunt_base_cfg_Index[item.type()] = i;
	}
	card_attr_cfg_Index.clear();
	for (int i = 0; i < card_cfg_.m_config.cards_size(); ++i) {
		card_attr_cfg_Index.insert(make_pair(card_cfg_.m_config.cards(i).id(), i));
	}
	card_group_cfg_Index.clear();
	for (int i = 0; i < card_group_cfg_.m_config.groups_size(); ++i) {
		uint32_t key = CFG_MAKE_KEY(card_group_cfg_.m_config.groups(i).type(),card_group_cfg_.m_config.groups(i).groupid());
		card_group_cfg_Index.insert(make_pair(key, i));
	}
	card_suit_cfg_Index.clear();
	for (int i = 0; i < card_suit_cfg_.m_config.suits_size(); ++i) {
		card_suit_cfg_Index.insert(make_pair(card_suit_cfg_.m_config.suits(i).id(), i));
	}
	ring_cfg_Index.clear();
	for (int i = 0; i <ring_cfg_.m_config.ring_size(); ++i) {
		ring_cfg_Index.insert(make_pair(ring_cfg_.m_config.ring(i).level(), i));
	}
	reincarn_cfg_Index.clear();
	for (int i = 0; i < reincarn_cfg_.m_config.reincarn_size(); ++i) {
		reincarn_cfg_Index.insert(make_pair(reincarn_cfg_.m_config.reincarn(i).level(), i));
	}

	role_suit_Index.clear();
	for (int i = 0; i < role_suit_cfg_.m_config.suits_size(); ++i) {
		role_suit_Index.insert(make_pair(role_suit_cfg_.m_config.suits(i).id(), i));
	}
	role_magic_Index.clear();
	for (int i = 0; i < role_magic_cfg_.m_config.magics_size(); ++i) {
		uint32_t key = CFG_MAKE_KEY(role_magic_cfg_.m_config.magics(i).level(),role_magic_cfg_.m_config.magics(i).type());
		role_magic_Index.insert(make_pair(key, i));
	}

	copy_Index.clear();
	for (int i = 0; i < copy_cfg_.m_config.copys_size(); ++i) {
		copy_Index.insert(make_pair(copy_cfg_.m_config.copys(i).copyid(), i));
	}
	boss_Index.clear();
	for (int i = 0; i < boss_cfg_.m_config.boss_size(); ++i) {
		boss_Index.insert(make_pair(boss_cfg_.m_config.boss(i).bosstype(), i));
	}
	daily_act_index.clear();
	for(int i = 0; i < daily_act_cfg_.m_config.daliy_act_size(); ++i) {
		daily_act_index.insert(make_pair(daily_act_cfg_.m_config.daliy_act(i).actid(), i));
	}
	active_index.clear();
	for(int i = 0; i < actives_cfg_.m_config.active_size(); ++i) {
		map<uint32_t, uint32_t>& map = active_index[actives_cfg_.m_config.active(i).type()];
		map.insert(make_pair(actives_cfg_.m_config.active(i).limit(), i));
	}
	magic_tower_index.clear();
	for(int i = 0; i < magic_tower_cfg_.m_config.magic_towers_size(); ++i) {
		magic_tower_index.insert(make_pair(magic_tower_cfg_.m_config.magic_towers(i).id(), i));
	}
}

bool ConfigManager::AddSkill(const CfgSkill::Skill &v) {
	CfgSkill::Skills &skills = const_cast<ConfigPB<CfgSkill::Skills>&>(skill_cfg_).m_config;
	skills.add_skills()->CopyFrom(v);
	int i = skills.skills_size() - 1;
	if (i <= 0) {
		return false;
	}
	skill_cfg_Index[skills.skills(i).id()] = i;
	map<uint32_t, uint32_t> &item = skill_cfg_serial_Index[skills.skills(i).serial()];
	item[skills.skills(i).level()] = i;

	return true;
}

bool ConfigManager::AddStreasure(const CfgTreasure::Treasure &v) {
	CfgTreasure::Treasures &treasures = const_cast<ConfigPB<CfgTreasure::Treasures>&>(treasure_cfg_).m_config;
	treasures.add_treasures()->CopyFrom(v);
	int i = treasures.treasures_size() - 1;
	if(i <= 0) {
		return false;
	}
	treasure_cfg_index[treasures.treasures(i).id()] = i;
	return true;
}

// 添加
bool ConfigManager::AddPurify(const CfgPurify::Purify &v) {
	CfgPurify::Purifys &purifys = const_cast<ConfigPB<CfgPurify::Purifys>&>(purify_cfg_).m_config;
	purifys.add_purifys()->CopyFrom(v);
	int i = purifys.purifys_size() - 1;
	if(i <= 0) {
		return false;
	}
	purify_cfg_Index[purifys.purifys(i).level()] = i;
	return true;
}
