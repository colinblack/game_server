#include "ConfigWrap.h"
#include <math.h>

MapCfgWrap::MapCfgWrap() :
		cfg_(ConfigManager::Instance()->map_cfg_.m_config) {
}
const CfgMap::Map& MapCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->map_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("map id not exists %u", id);
		throw runtime_error("map id not exists");
	}
	return cfg_.maps(itr->second);
}

DungeonCfgWrap::DungeonCfgWrap() :
		cfg_(ConfigManager::Instance()->dungeon_cfg_.m_config) {
}
const CfgDungeon::DungeonItem& DungeonCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->dungeon_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("dungeon id not exists %u", id);
		throw runtime_error("dungeon id not exists");
	}
	return cfg_.dungeonconfig(itr->second);
}

MonsterCfgWrap::MonsterCfgWrap() :
		cfg_(ConfigManager::Instance()->monster_cfg_.m_config), plan_(ConfigManager::Instance()->monster_plan_cfg_.m_config) {
}
const CfgMonster::Monster& MonsterCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->monster_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("monster id not exists %u", id);
		throw runtime_error("monster id not exists");
	}
	return cfg_.monsters(itr->second);
}
const CfgMonster::Plan& MonsterCfgWrap::GetPlan(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->monster_plan_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("monster plan id not exists %u", id);
		throw runtime_error("monster plan id not exists");
	}
	return plan_.plans(itr->second);
}

SkillCfgWrap::SkillCfgWrap() :
		cfg_(ConfigManager::Instance()->skill_cfg_.m_config), mon_cfg_(ConfigManager::Instance()->skill_monster_cfg_.m_config) {
}
bool SkillCfgWrap::IsExist(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs1 = ConfigManager::Instance()->skill_cfg_Index;
	if (indexs1.find(id) != indexs1.end()) {
		return true;
	}
	const map<uint32_t, uint32_t> &indexs2 = ConfigManager::Instance()->skill_monster_cfg_Index;
	if (indexs2.find(id) != indexs2.end()) {
		return true;
	}
	return false;
}
bool SkillCfgWrap::IsSummon(const CfgSkill::Skill &cfg) {
	return cfg.type() == 14;
}
bool SkillCfgWrap::IsNormal(const CfgSkill::Skill &cfg) {
	return cfg.type() == 1;
}
bool SkillCfgWrap::IsSprint(const CfgSkill::Skill &cfg) {
	return cfg.type() == 24;
}
bool SkillCfgWrap::IsAddBuff(const CfgSkill::Skill &cfg) {
	return cfg.buff().size() > 0;
}
const CfgSkill::Skill& SkillCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->skill_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr != indexs.end()) {
		return cfg_.skills(itr->second);
	}
	const map<uint32_t, uint32_t> &indexs2 = ConfigManager::Instance()->skill_monster_cfg_Index;
	itr = indexs2.find(id);
	if (itr != indexs2.end()) {
		return mon_cfg_.skills(itr->second);
	}
	error_log("skill not exist %u", id);
	throw std::runtime_error("skill id not exist!");
}

const CfgSkill::Skill& SkillCfgWrap::GetById(uint32_t id) {
	SkillBaseCfgWrap baseWrap;

	int pre2Num = floor(id / 1000000);
	int pre3Num = floor(id / 100000);
	if (pre2Num <= 12 && pre3Num < 121) {
		int level = id % 10000000;
		level = level % 1000;
		if (!IsExist(id) && level > 1) {
			uint32_t first_id = static_cast<uint32_t>(id / 1000) * 1000 + 1;
			const CfgSkill::Skill &cfg = Get(first_id);
			const CfgSkill::Base &base = baseWrap.Get(cfg.serial());

			CfgSkill::Skill item;
			item.CopyFrom(cfg);
			item.set_id(id);
			item.set_level(level);
			item.set_unlock(baseWrap.calcLevelLimit(base, level));
			item.set_careerlevel(baseWrap.calcCareerLevel(level));
			if (IsSummon(item)) {
				item.set_hurt(90000000 + level);
			} else {
				item.set_hurt(item.hurt() + baseWrap.calcHurtAdd(base, level) * 1000);
			}
			item.set_cost(baseWrap.calcCost(base, level));
			ConfigManager::Instance()->AddSkill(item);
		}
	}
	return Get(id);
}
const CfgSkill::Skill& SkillCfgWrap::GetByLv(uint32_t serial, uint32_t lv, uint32_t id) {
	SkillBaseCfgWrap baseWrap;
	if (baseWrap.IsExist(serial)) {
		return GetById(id);
	}
	const map<uint32_t, map<uint32_t, uint32_t> > &indexs = ConfigManager::Instance()->skill_cfg_serial_Index;
	map<uint32_t, map<uint32_t, uint32_t> >::const_iterator itr = indexs.find(serial);
	if (itr == indexs.end()) {
		throw std::runtime_error("serial not exist");
	}
	map<uint32_t, uint32_t>::const_iterator it = itr->second.find(lv);
	if (it == itr->second.end()) {
		throw std::runtime_error("level not exist");
	}
	return cfg_.skills(it->second);
}
const CfgSkill::Skill& SkillCfgWrap::GetFirst(uint32_t serial) {
	const map<uint32_t, map<uint32_t, uint32_t> > &indexs = ConfigManager::Instance()->skill_cfg_serial_Index;
	map<uint32_t, map<uint32_t, uint32_t> >::const_iterator itr = indexs.find(serial);
	if (itr == indexs.end()) {
		throw std::runtime_error("serial not exist");
	}
	map<uint32_t, uint32_t>::const_iterator it = itr->second.find(1);
	if (it == itr->second.end()) {
		throw std::runtime_error("level not exist");
	}
	return cfg_.skills(it->second);
}

SkillBaseCfgWrap::SkillBaseCfgWrap() :
		cfg_(ConfigManager::Instance()->skill_base_cfg_.m_config) {
}
bool SkillBaseCfgWrap::IsExist(uint32_t id) {
	map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->skill_base_cfg_Index;
	return indexs.find(id) != indexs.end();
}
const CfgSkill::Base& SkillBaseCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->skill_base_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("skill base id not exists %u", id);
		throw runtime_error("skill base id not exists");
	}
	return cfg_.bases(itr->second);
}
uint32_t SkillBaseCfgWrap::calcHurtAdd(const CfgSkill::Base &cfg, uint32_t lv) {
	float inc = static_cast<float>(cfg.xishu()) / 10000;
	float n = ::ceil(static_cast<float>(lv) / 10.0f);
	float a = inc * (n + 4);
	return ::ceil((a + inc * 5) * n * 10 / 2 - (10 * n - lv) * a + cfg.hurtadd());
}
uint32_t SkillBaseCfgWrap::calcCost(const CfgSkill::Base &cfg, uint32_t lv) {
	return cfg.cost() * floor((lv - 1) / 10) + cfg.cost();
}
uint32_t SkillBaseCfgWrap::calcLevelLimit(const CfgSkill::Base &cfg, uint32_t lv) {
	if (lv == 1) {
		return cfg.unlocklevel();
	}
	uint32_t temp = lv > cfg.learnlevel() ? lv - cfg.learnlevel() : 0;
	if (temp > cfg.learnlevel()) {
		return lv > 80 ? 80 : lv;
	}
	if (lv > cfg.learnlevel()) {
		return lv;
	}
	return cfg.learnlevel();
}
uint32_t SkillBaseCfgWrap::calcCareerLevel(uint32_t lv) {
	return lv < 80 ? 0 : ceil(static_cast<float>(lv - 80) / 10.0f) + 2;
}

SceneCfgWrap::SceneCfgWrap() :
		cfg_(ConfigManager::Instance()->scene_cfg_.m_config) {
}
const CfgMap::Scene& SceneCfgWrap::Get(int32_t mapid) {
	const map<int32_t, uint32_t> &indexs = ConfigManager::Instance()->scene_cfg_Index;
	map<int32_t, uint32_t>::const_iterator itr = indexs.find(mapid);
	if (itr == indexs.end()) {
		error_log("map id not exists %u", mapid);
		throw runtime_error("map id not exists");
	}
	return cfg_.scenes(itr->second);
}
const CfgMap::Point& SceneCfgWrap::GetBossPoint(int32_t mapid, int32_t plan) {
	const CfgMap::Scene &cfg = Get(mapid);
	for (int i = 0; i < cfg.bosscenterpoints_size(); ++i) {
		if (cfg.bosscenterpoints(i).plan() == plan) {
			return cfg.bosscenterpoints(i).point();
		}
	}
	error_log("plan id not exists %u %u", mapid, plan);
	throw runtime_error("plan id not exists");
}

HangCfgWrap::HangCfgWrap() :
		cfg_(ConfigManager::Instance()->hang_cfg_.m_config), plan_(ConfigManager::Instance()->hang_plan_cfg_.m_config) {
}
const CfgHang::Hang& HangCfgWrap::Get(int32_t id) {
	if (id == 0)
		id = 1;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->hang_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("hang id not exists %u", id);
		throw runtime_error("hang id not exists");
	}
	return cfg_.hangs(itr->second);
}
const CfgHang::Plan& HangCfgWrap::GetPlan(int32_t id) {
	if (id == 0)
		id = 1;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->hang_plan_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("plan id not exists %u", id);
		throw runtime_error("plan id not exists");
	}
	return plan_.plans(itr->second);
}

LevelCfgWrap::LevelCfgWrap(): cfg_(ConfigManager::Instance()->level_cfg_.m_config),
		attr_(ConfigManager::Instance()->level_attr_cfg_.m_config) {
}
const CfgLevel::Level& LevelCfgWrap::Get(uint32_t id) {
	if (id == 0)
		id = 1;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->level_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("level id not exists %u", id);
		throw runtime_error("level id not exists");
	}
	return cfg_.levels(itr->second);
}
const CfgLevel::Attr& LevelCfgWrap::GetAttr(uint32_t id) {
	if (id == 0)
		id = 1;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->level_attr_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("level id not exists %u", id);
		throw runtime_error("level id not exists");
	}
	return attr_.levels(itr->second);
}

MissionCfgWrap::MissionCfgWrap(): cfg_(ConfigManager::Instance()->mission_cfg_.m_config) {
}
bool MissionCfgWrap::IsExist(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->mission_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	return itr != indexs.end();
}
const CfgMission::Mission& MissionCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->mission_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("mission id not exists %u", id);
		throw runtime_error("mission id not exists");
	}
	return cfg_.missions(itr->second);
}

AdvanceCfgWrap::AdvanceCfgWrap(): cfg_(ConfigManager::Instance()->advance_cfg_.m_config),
		dan_(ConfigManager::Instance()->advance_dan_cfg_.m_config) {
}
const CfgAdvance::Advance& AdvanceCfgWrap::Get(uint32_t type, uint32_t group, uint32_t star) {
	string key;
	String::Format(key, "%u_%u_%u", type, group, star);
	const map<string, uint32_t> &indexs = ConfigManager::Instance()->advance_cfg_Index;
	map<string, uint32_t>::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("advance not exists %s", key.c_str());
		throw runtime_error("advance not exists");
	}
	return cfg_.advances(itr->second);
}
const CfgAdvance::Dan& AdvanceCfgWrap::GetDan(uint32_t type, uint32_t level, uint32_t item) {
	string key;
	String::Format(key, "%u_%u", type, level);
	const map<string, list<uint32_t> > &indexs = ConfigManager::Instance()->advance_dan_cfg_Index;
	map<string, list<uint32_t> >::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("advance dan not exists %s", key.c_str());
		throw runtime_error("advance dan not exists");
	}
	list<uint32_t>::const_iterator it = itr->second.begin();
	for (; it != itr->second.end(); ++it) {
		const CfgAdvance::Dan& cfg = dan_.dans(*it);
		if (cfg.item() == item) {
			return cfg;
		}
	}
	error_log("advance dan not exists %s %u", key.c_str(), item);
	throw runtime_error("advance dan not exists");
}
const CfgAdvance::Dan& AdvanceCfgWrap::GetDanById(uint32_t type, uint32_t level, uint32_t id) {
	string key;
	String::Format(key, "%u_%u", type, level);
	const map<string, list<uint32_t> > &indexs = ConfigManager::Instance()->advance_dan_cfg_Index;
	map<string, list<uint32_t> >::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("advance dan not exists %s", key.c_str());
		throw runtime_error("advance dan not exists");
	}
	list<uint32_t>::const_iterator it = itr->second.begin();
	for (; it != itr->second.end(); ++it) {
		const CfgAdvance::Dan& cfg = dan_.dans(*it);
		if (cfg.id() == id) {
			return cfg;
		}
	}
	error_log("advance dan not exists %s %u", key.c_str(), id);
	throw runtime_error("advance dan not exists");
}
uint32_t AdvanceCfgWrap::GetDanCount(uint32_t type, uint32_t level) {
	string key;
	String::Format(key, "%u_%u", type, level);
	const map<string, list<uint32_t> > &indexs = ConfigManager::Instance()->advance_dan_cfg_Index;
	map<string, list<uint32_t> >::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		return 0;
	}
	return itr->second.size();
}

ItemCfgWrap::ItemCfgWrap(): item_(ConfigManager::Instance()->item_cfg_.m_config),
		equip_(ConfigManager::Instance()->equip_cfg_.m_config),
		gift_(ConfigManager::Instance()->gift_cfg_.m_config),
		attr_(ConfigManager::Instance()->equip_attr_cfg_.m_config),
		drop_(ConfigManager::Instance()->drop_cfg_.m_config){
}
bool ItemCfgWrap::IsItem(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->item_cfg_Index;
	return indexs.find(id) != indexs.end();
}
bool ItemCfgWrap::IsMagic(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->item_cfg_Index;
	if(indexs.find(id) != indexs.end()){
		const CfgItem::Item &itemCfg = GetItem(id);
		if(itemCfg.itemtype()==15){
			return true;
		}
	}
	return false;
}

bool ItemCfgWrap::IsTitle(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->item_cfg_Index;
	if(indexs.find(id) != indexs.end()){
		const CfgItem::Item &itemCfg = GetItem(id);
		if(itemCfg.itemtype()==11  && itemCfg.subtype() == 15){
			return true;
		}
	}
	return false;
}

bool ItemCfgWrap::IsEquip(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->equip_cfg_Index;
	return indexs.find(id) != indexs.end();
}

bool ItemCfgWrap::IsGift(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->gift_cfg_Index;
	return indexs.find(id) != indexs.end();
}
bool ItemCfgWrap::IsFixedGift(const CfgItem::Gift &cfg) {
	return cfg.subtype() == 1;
}
bool ItemCfgWrap::IsFixedRandomGift(const CfgItem::Gift &cfg) {
	return cfg.subtype() == 3;
}
bool ItemCfgWrap::IsRandomGift(const CfgItem::Gift &cfg) {
	return cfg.subtype() == 2;
}
bool ItemCfgWrap::IsSelectGift(const CfgItem::Gift &cfg) {
	return cfg.subtype() == 4;
}

const CfgItem::Item& ItemCfgWrap::GetItem(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->item_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		throw std::runtime_error("item id not exists");
	}
	return item_.items(itr->second);
}
const CfgItem::Equip& ItemCfgWrap::GetEquip(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->equip_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		throw std::runtime_error("equip id not exists");
	}
	return equip_.equips(itr->second);
}
const CfgItem::Gift& ItemCfgWrap::GetGift(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->gift_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		throw std::runtime_error("gift id not exists");
	}
	return gift_.gifts(itr->second);
}
TreasureCfgWrap::TreasureCfgWrap() :
		treasures(ConfigManager::Instance()->treasure_cfg_.m_config),
		hunt_(ConfigManager::Instance()->treasure_hunt_cfg_.m_config),
		hunt_base_(ConfigManager::Instance()->treasure_hunt_base_cfg_.m_config) {
}

bool TreasureCfgWrap::IsExist(uint32_t id) {
	if (ConfigManager::Instance()->treasure_cfg_index.count(id) == 0) {
		return false;
	} else {
		return true;
	}
}

const CfgTreasure::Treasure& TreasureCfgWrap::GetById(uint32_t id) {
	if(IsExist(id)) {
		return Get(id);
	} else {

		uint32_t type = (id - 100000) / 550 + 1;
		uint32_t level = ((id - 100000) % 550)/11 + 1;
		uint32_t star = ((id - 100000) % 550)%11 - 1;

		CfgTreasure::Treasure cfg;
		//获取一阶 0 星配置
		uint32_t id_0 = GetIdByType(type, 1, 0);
		uint32_t id_1 = GetIdByType(type, 1, 1);
		const CfgTreasure::Treasure& cfg_0 = GetById(id_0);
		//获取一阶 1 星配置
		const CfgTreasure::Treasure& cfg_1 = GetById(id_1);

		cfg.CopyFrom(cfg_1);
		for(int indx = 0; indx < cfg_0.attr_size(); ++indx) {
			int64_t num = cfg_0.attr(indx).num() + (cfg_1.attr(indx).num() - cfg_0.attr(indx).num()) * star;
					cfg.mutable_attr(indx)->set_num(num);
		}

		cfg.set_id(id);
		cfg.set_level(level);
		cfg.set_star(star);
		ConfigManager::Instance()->AddStreasure(cfg);
		return Get(id);
	}
}
uint32_t TreasureCfgWrap::GetIdByType(uint32_t type, uint32_t level, uint32_t star) {
	return (100000 + 550 * (type - 1) + (level - 1) * 11 + star + 1);
}
uint32_t TreasureCfgWrap::GetDanLimit(uint32_t type, uint32_t level, uint32_t star, uint32_t id) {
	uint32_t treasure_id = GetIdByType(type, level, star);
	const CfgTreasure::Treasure& treasure = GetById(treasure_id);
	for(int indx = 0; indx < treasure.dans().dans_size(); ++indx) {
		if(treasure.dans().dans(indx).item() == id) {
			return treasure.dans().dans(indx).num();
		}
	}
	error_log("GetDanLimit::type,%d, level,%d, star,%d, id,%d", type, level, star, id);
	throw std::runtime_error("Dan not exists");
}
uint32_t TreasureCfgWrap::GetDanId(uint32_t type, uint32_t level, uint32_t star, uint32_t index) {
	uint32_t id = GetIdByType(type, level, star);
	const CfgTreasure::Treasure& treasure = GetById(id);
	return treasure.dans().dans(index).item();
}
const CfgTreasure::Hunt& TreasureCfgWrap::GetHunt(uint32_t id) {
	map<uint32_t, uint32_t>& index = ConfigManager::Instance()->treasure_hunt_cfg_Index;
	map<uint32_t, uint32_t>::iterator itr = index.find(id);
	if(itr != index.end()) {
		return hunt_.hunts(itr->second);
	}
	error_log("treasure hunt id not exosts %u", id);
	throw std::runtime_error("treasure hunt id not exists");
}
const CfgTreasure::Hunt& TreasureCfgWrap::GetHuntByIndex(int id) {
	return hunt_.hunts(id);
}
const CfgTreasure::HuntBase& TreasureCfgWrap::GetHuntBase(uint32_t id){
	map<uint32_t, uint32_t>& index = ConfigManager::Instance()->treasure_hunt_base_cfg_Index;
	map<uint32_t, uint32_t>::iterator itr = index.find(id);
	if(itr != index.end()) {
		return hunt_base_.bases(itr->second);
	}
	error_log("treasure hunt baes id not exosts %u", id);
	throw std::runtime_error("treasure hunt base id not exists");
}

const CfgTreasure::Treasure& TreasureCfgWrap::Get(uint32_t id) {
	map<uint32_t, uint32_t>& index = ConfigManager::Instance()->treasure_cfg_index;
	map<uint32_t, uint32_t>::iterator it = index.find(id);
	if(it != index.end()) {
		return treasures.treasures(it->second);
	}
	error_log("Get::id,%d", id);
	throw std::runtime_error("Treasure id not exists");
}

const CfgItem::Attr& ItemCfgWrap::GetAttr(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->equip_attr_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		throw std::runtime_error("attr id not exists");
	}
	return attr_.attrs(itr->second);
}
const CfgItem::Drop& ItemCfgWrap::GetDrop(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->drop_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		throw std::runtime_error("attr id not exists");
	}
	return drop_.drops(itr->second);
}

ForgeCfgWrap::ForgeCfgWrap(): strengthen_(ConfigManager::Instance()->equip_strengthen_cfg_.m_config) {
}
const CfgForge::Strengthen& ForgeCfgWrap::GetStrengthen(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->equip_strengthen_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("strengthen id not exists %u %u", id, indexs.size());
		throw std::runtime_error("strengthen id not exists");
	}
	return strengthen_.strengthens(itr->second);
}


// fix by Memory
PurifyCfgWrap::PurifyCfgWrap(): cfg_(ConfigManager::Instance()->purify_cfg_.m_config){
}
const CfgPurify::Purify& PurifyCfgWrap::Get(uint32_t level) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->purify_cfg_Index;
	// 每10 级是取一个配置   比如 23级 取 21级
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(level);
	if (itr == indexs.end()) {
		error_log("purify indexId not exists %u", level);
		throw runtime_error("purify id not exists");
	}
	return cfg_.purifys(itr->second);
}

TitleCfgWrap::TitleCfgWrap(): cfg_(ConfigManager::Instance()->title_cfg_.m_config){
}
const CfgTitle::Title& TitleCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->title_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("title id not exists %u", id);
		throw runtime_error("title id not exists");
	}
	return cfg_.titles(itr->second);
}

bool TitleCfgWrap::isTitleExist(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->title_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		return false;
	} else {
		return true;
	}
}


const CfgPurify::Purify& PurifyCfgWrap::GetByLevel(uint32_t level) {
	if(isExist(level)) {
		return Get(level);
	}
	CfgPurify::Purify cfg;
	const CfgPurify::Purify& cfg_1 = Get(1);
	cfg.CopyFrom(cfg_1);
	cfg.set_level(level);
	for(int index = 0; index < cfg.useprops_size(); ++index) {
		uint32_t num = ((level-1)/10 + 1) * 300;
		cfg.mutable_useprops(index)->set_num(num);
	}
	for(int index = 0; index < cfg.attr_size(); ++index) {
		uint32_t data = cfg_1.attr(index).num() * level;
		cfg.mutable_attr(index)->set_num(data);
	}
	ConfigManager::Instance()->AddPurify(cfg);
	return  Get(level);
}

bool PurifyCfgWrap::isExist(uint32_t level) {
	map<uint32_t, uint32_t> &index = ConfigManager::Instance()->purify_cfg_Index;
	map<uint32_t, uint32_t>::iterator it = index.find(level);
	if(it != index.end()) {
		return true;
	} else {
		return false;
	}
}

CardCfgWrap::CardCfgWrap(): cards_(ConfigManager::Instance()->card_cfg_.m_config) {
}
const CfgCard::Card& CardCfgWrap::GetCard(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->card_attr_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("strengthen id not exists %u %u", id, indexs.size());
		throw std::runtime_error("card attr id not exists");
	}
	return cards_.cards(itr->second);
}

CardGroupWrap::CardGroupWrap(): cardGroups_(ConfigManager::Instance()->card_group_cfg_.m_config) {
}
const CfgCard::CardGroup& CardGroupWrap::GetCardGroup(uint32_t key) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->card_group_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("card group id not exists %u %u", key, indexs.size());
		throw std::runtime_error("card group id not exists");
	}
	return cardGroups_.groups(itr->second);
}


CardSuitWrap::CardSuitWrap(): suits_(ConfigManager::Instance()->card_suit_cfg_.m_config) {
}
const CfgCard::Suit& CardSuitWrap::GetSuit(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->card_suit_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("card suit id not exists %u %u", id, indexs.size());
		throw std::runtime_error("card suit id not exists");
	}
	return suits_.suits(itr->second);
}

const CfgCard::Suit& CardSuitWrap::GetSuitByCard(uint32_t cardId) {
	for(map<uint32_t, uint32_t>::iterator it =ConfigManager::Instance()->card_suit_cfg_Index.begin();it!=ConfigManager::Instance()->card_suit_cfg_Index.end();it++){
		for(int i=0;i<suits_.suits(it->second).include_size();i++){
			if(suits_.suits(it->second).include().Get(i) ==cardId){
				return suits_.suits(it->second);
			}
		}
	}
	throw std::runtime_error("card suit id not exists");
}

RoleSuitWrap::RoleSuitWrap():suits_(ConfigManager::Instance()->role_suit_cfg_.m_config) {
}

bool RoleSuitWrap::isSuitExist(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->role_suit_Index;
		map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
		if (itr == indexs.end()) {
			return false;
		} else {
			return true;
		}
}

const CfgSuit::Suit& RoleSuitWrap::GetSuit(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->role_suit_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("card suit id not exists %u %u", id, indexs.size());
		throw std::runtime_error("card suit id not exists");
	}
	return suits_.suits(itr->second);
}

RingWrap::RingWrap(): rings_(ConfigManager::Instance()->ring_cfg_.m_config) {
}

const CfgRing::Ring& RingWrap::GetRing(uint32_t level) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->ring_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(level);
	if (itr == indexs.end()) {
		error_log("ring level = %u not exists %u", level, indexs.size());
		throw std::runtime_error("ring id not exists");
	}
	return rings_.ring(itr->second);
}


ReinCarnWrap::ReinCarnWrap(): reincarns_(ConfigManager::Instance()->reincarn_cfg_.m_config) {
}
const CfgReinCarn::ReinCarn& ReinCarnWrap::GetReinCarn(uint32_t level) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->reincarn_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(level);
	if (itr == indexs.end()) {
		error_log("reincarn level = %u not exists %u", level, indexs.size());
		throw std::runtime_error("reincarn id not exists");
	}
	return reincarns_.reincarn(itr->second);
}



MagicWrap::MagicWrap(): magics_(ConfigManager::Instance()->role_magic_cfg_.m_config) {
}
const CfgMagic::Magic& MagicWrap::GetMagic(uint32_t level,uint32_t type) {
	uint32_t key =CFG_MAKE_KEY(level,type);
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->role_magic_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("magic level = %u color = %unot exists %u", level,type,indexs.size());
		throw std::runtime_error("reincarn id not exists");
	}
	return magics_.magics(itr->second);
}

MagicTowerWrap::MagicTowerWrap(): magicTowers_(ConfigManager::Instance()->magic_tower_cfg_.m_config) {
}
const CfgMagic::MagicTower& MagicTowerWrap::GetMagicTower(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->magic_tower_index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("magic tower id = %u not exists %u", id,indexs.size());
		throw std::runtime_error("magic tower id not exists");
	}
	return magicTowers_.magic_towers(itr->second);
}


CopyWrap::CopyWrap(): copys_(ConfigManager::Instance()->copy_cfg_.m_config) {
}
const CfgCopy::Copy& CopyWrap::GetCopy(uint32_t copyId) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->copy_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(copyId);
	if (itr == indexs.end()) {
		error_log("copyId  = %u not exists %u", copyId, indexs.size());
		throw std::runtime_error("copy id not exists");
	}
	return copys_.copys(itr->second);
}

BossWrap::BossWrap(): bosses_(ConfigManager::Instance()->boss_cfg_.m_config) {
}
const CfgBoss::Boss& BossWrap::GetBoss(uint32_t bossType) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->boss_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(bossType);
	if (itr == indexs.end()) {
		error_log("bossType  = %u not exists %u", bossType, indexs.size());
		throw std::runtime_error("boss id not exists");
	}
	return bosses_.boss(itr->second);
}

ActivityCfgWrap::ActivityCfgWrap(): daliyAct_(ConfigManager::Instance()->daily_act_cfg_.m_config),
	actives_(ConfigManager::Instance()->actives_cfg_.m_config){
}

bool ActivityCfgWrap::isActExist(uint32_t id) {
	map<uint32_t, uint32_t>::iterator it = ConfigManager::Instance()->daily_act_index.find(id);
	if(it != ConfigManager::Instance()->daily_act_index.end()) {
		return true;
	} else {
		return false;
	}
}

bool ActivityCfgWrap::isActiveExit(uint32_t active, uint32_t level) {
	map<uint32_t, map<uint32_t, uint32_t> >::iterator it = ConfigManager::Instance()->active_index.find(level);
	if(it != ConfigManager::Instance()->active_index.end()) {
		map<uint32_t, uint32_t>::iterator item = it->second.find(active);
		if(item != it->second.end()) {
			return true;
		}
	}
	return false;
}

uint32_t ActivityCfgWrap::GetActiveLimit(uint32_t id, uint32_t level) {
	map<uint32_t, map<uint32_t, uint32_t> >::iterator it = ConfigManager::Instance()->active_index.find(level);
	if(it != ConfigManager::Instance()->active_index.end()) {
		uint32_t index = 0;
		map<uint32_t, uint32_t>::iterator item = it->second.begin();
		for(; item != it->second.end(); ++item) {
			index++;
			if(id == index) {
				return item->first;
			}
		}
	}
	error_log("active id:%u is not exist", id);
	throw std::runtime_error("active id is not exist");
}

const CfgActivity::DaliyAct& ActivityCfgWrap::GetAct(uint32_t id) {
	if(!isActExist(id)) {
		error_log("act_id:%u is not exist", id);
		throw std::runtime_error("act_id is not exist");
	}
	uint32_t index = ConfigManager::Instance()->daily_act_index[id];
	return daliyAct_.daliy_act(index);
}

const CfgActivity::Active& ActivityCfgWrap::GetActive(uint32_t active, uint32_t level) {
	if(!isActiveExit(active, level)) {
		error_log("active:%u, level:%u is not exist", active, level);
		throw std::runtime_error("active cfg is not eixst");
	}
	uint32_t index = ConfigManager::Instance()->active_index[level][active];
	return actives_.active(index);
}
