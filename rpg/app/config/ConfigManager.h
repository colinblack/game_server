/*
 * ConfigManager.h
 *
 *  Created on: 2016-8-22
 *      Author: Ralf
 */

#ifndef CONFIG_MANAGER_H_
#define CONFIG_MANAGER_H_

#include "Common.h"
#include "ConfigPB.h"
#include "ConfigInc.h"

/*
 *  配置文件管理器，增加新配置时，把新的pb文件加入ConfigInc.h，定义新的const成员，构造函数中写入配置文件名
 */
class ConfigManager : public CSingleton<ConfigManager>
{
private:
	friend class CSingleton<ConfigManager>;
	virtual ~ConfigManager(){}
	ConfigManager()
		:map_cfg_("maps.json")
		,scene_cfg_("scenes.json")
		,skill_cfg_("skills.json")
		,skill_base_cfg_("skill_bases.json")
		,skill_monster_cfg_("skill_monsters.json")
		,hang_plan_cfg_("hang_plans.json")
		,hang_cfg_("hangs.json")
		,monster_cfg_("monsters.json")
		,monster_plan_cfg_("monster_plans.json")
		,level_cfg_("levels.json")
		,level_attr_cfg_("career_attr.json")
		,mission_cfg_("missions.json")
		,advance_cfg_("advances.json")
		,purify_cfg_("equip_purify.json")
		,title_cfg_("t_title.json")
		,advance_dan_cfg_("advance_dans.json")
		,item_cfg_("items.json")
		,equip_cfg_("equips.json")
		,gift_cfg_("gifts.json")
		,equip_attr_cfg_("equip_attrs.json")
		,shenqi_cfg_("shenqis.json")
		,drop_cfg_("drops.json")
		,bag_grid_cfg_("bag_grids.json")
		,attr_def_cfg_("attr_defs.json")
		,equip_strengthen_cfg_("equip_strengthens.json")
		,dungeon_cfg_("Dungeonconfig.json")
		,treasure_cfg_("treasure.json")
		,treasure_hunt_cfg_("treasure_draw.json")
		,treasure_hunt_base_cfg_("treasure_base_draw.json")
		,card_cfg_("card_attr.json")
		,card_group_cfg_("card_group.json")
		,card_suit_cfg_("card_suit.json")
		,ring_cfg_("ring.json")
		,reincarn_cfg_("reincarn.json")
		,role_suit_cfg_("role_suit.json")
		,role_magic_cfg_("t_magic.json")
		,copy_cfg_("copy.json")
		,boss_cfg_("boss.json")
		,daily_act_cfg_("daily_act.json")
		,actives_cfg_("active.json")
		,magic_tower_cfg_("magic_towers.json")
	{
		Init();
	}

	void Init();
	static bool m_init;

public:
	static bool Reload();
	static void Fail(){m_init = false;}
	bool Inited(){return m_init;}
	bool AddSkill(const CfgSkill::Skill &v);
	bool AddStreasure(const CfgTreasure::Treasure &v);
	bool AddPurify(const CfgPurify::Purify &v);

	const ConfigPB<CfgMap::Maps> map_cfg_;
	const ConfigPB<CfgMap::Scenes> scene_cfg_;
	const ConfigPB<CfgSkill::Skills> skill_cfg_;
	const ConfigPB<CfgSkill::Bases> skill_base_cfg_;
	const ConfigPB<CfgSkill::Skills> skill_monster_cfg_;
	const ConfigPB<CfgHang::Plans> hang_plan_cfg_;
	const ConfigPB<CfgHang::Hangs> hang_cfg_;
	const ConfigPB<CfgMonster::Monsters> monster_cfg_;
	const ConfigPB<CfgMonster::Plans> monster_plan_cfg_;
	const ConfigPB<CfgLevel::Levels> level_cfg_;
	const ConfigPB<CfgLevel::Attrs> level_attr_cfg_;
	const ConfigPB<CfgMission::Missions> mission_cfg_;
	const ConfigPB<CfgAdvance::Advances> advance_cfg_;
	const ConfigPB<CfgPurify::Purifys> purify_cfg_;
	const ConfigPB<CfgTitle::Titles> title_cfg_;
	const ConfigPB<CfgAdvance::Dans> advance_dan_cfg_;
	const ConfigPB<CfgItem::Items> item_cfg_;
	const ConfigPB<CfgItem::Equips> equip_cfg_;
	const ConfigPB<CfgItem::Gifts> gift_cfg_;
	const ConfigPB<CfgItem::Attrs> equip_attr_cfg_;
	const ConfigPB<CfgItem::ShenQis> shenqi_cfg_;
	const ConfigPB<CfgItem::Drops> drop_cfg_;
	const ConfigPB<CfgBag::Grids> bag_grid_cfg_;
	const ConfigPB<CfgAttrDef::AttrDefs> attr_def_cfg_;
	const ConfigPB<CfgForge::Strengthens> equip_strengthen_cfg_;
	const ConfigPB<CfgDungeon::Dungeon> dungeon_cfg_;
	const ConfigPB<CfgTreasure::Treasures> treasure_cfg_;
	const ConfigPB<CfgTreasure::Hunts> treasure_hunt_cfg_;
	const ConfigPB<CfgTreasure::HuntBases> treasure_hunt_base_cfg_;
	const ConfigPB<CfgCard::Cards> card_cfg_;
	const ConfigPB<CfgCard::CardGroups> card_group_cfg_;
	const ConfigPB<CfgCard::Suits> card_suit_cfg_;
	const ConfigPB<CfgRing::Rings> ring_cfg_;
	const ConfigPB<CfgReinCarn::ReinCarns> reincarn_cfg_;
	const ConfigPB<CfgSuit::Suits> role_suit_cfg_;
	const ConfigPB<CfgMagic::Magics> role_magic_cfg_;
	const ConfigPB<CfgCopy::Copys> copy_cfg_;
	const ConfigPB<CfgBoss::Bosses> boss_cfg_;
	const ConfigPB<CfgActivity::DaliyActs> daily_act_cfg_;
	const ConfigPB<CfgActivity::Actives> actives_cfg_;
	const ConfigPB<CfgMagic::MagicTowers> magic_tower_cfg_;

	map<uint32_t, uint32_t> map_cfg_Index;
	map<int32_t,  uint32_t> scene_cfg_Index;
	map<uint32_t, map<uint32_t, uint32_t> > skill_cfg_serial_Index;
	map<uint32_t, uint32_t> skill_cfg_Index;
	map<uint32_t, uint32_t> skill_base_cfg_Index;
	map<uint32_t, uint32_t> skill_monster_cfg_Index;
	map<uint32_t, uint32_t> hang_plan_cfg_Index;
	map<uint32_t, uint32_t> hang_cfg_Index;
	map<uint32_t, uint32_t> monster_cfg_Index;
	map<uint32_t, uint32_t> monster_plan_cfg_Index;
	map<uint32_t, uint32_t> level_cfg_Index;
	map<uint32_t, uint32_t> level_attr_cfg_Index;
	map<uint32_t, uint32_t> mission_cfg_Index;
	map<string,   uint32_t> advance_cfg_Index;
	map<uint32_t,   uint32_t> purify_cfg_Index;
	map<uint32_t,   uint32_t> title_cfg_Index;
	map<string,   list<uint32_t> > advance_dan_cfg_Index;
	map<uint32_t, uint32_t> item_cfg_Index;
	map<uint32_t, uint32_t> equip_cfg_Index;
	map<uint32_t, uint32_t> gift_cfg_Index;
	map<uint32_t, list<uint32_t> > equip_attr_cfg_Pool;
	map<uint32_t, uint32_t> equip_attr_cfg_Index;
	map<uint32_t, set<uint32_t> > shenqi_cfg_Index;
	map<uint32_t, uint32_t> drop_cfg_Index;
	map<uint32_t, map<uint32_t, uint32_t> > bag_grid_cfg_Index;
	map<uint32_t, map<uint32_t, uint32_t> > attr_def_cfg_Index;
	map<uint32_t, uint32_t> equip_strengthen_cfg_Index;
	map<uint32_t, uint32_t> dungeon_cfg_Index;
	map<uint32_t, uint32_t> treasure_cfg_index;
	map<uint32_t, map<uint32_t, list<int32_t> > > treasure_hunt_cfg_map; // <type, <must <index>>>
	map<uint32_t, uint32_t> treasure_hunt_cfg_Index;
	map<uint32_t, uint32_t> treasure_hunt_base_cfg_Index;
	map<uint32_t, uint32_t> card_attr_cfg_Index;
	map<uint32_t, uint32_t> card_group_cfg_Index;
	map<uint32_t, uint32_t> card_suit_cfg_Index;
	map<uint32_t, uint32_t> ring_cfg_Index;
	map<uint32_t, uint32_t> reincarn_cfg_Index;
	map<uint32_t, uint32_t> role_suit_Index;
	map<uint32_t, uint32_t> role_magic_Index;
	map<uint32_t, uint32_t> copy_Index;
	map<uint32_t, uint32_t> boss_Index;
	map<uint32_t, uint32_t> daily_act_index;
	map<uint32_t, map<uint32_t, uint32_t> > active_index;
	map<uint32_t, uint32_t> magic_tower_index;
};

#endif /* CONFIG_MANAGER_H_ */
