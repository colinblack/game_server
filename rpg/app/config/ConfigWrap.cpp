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
	if (itr != indexs.end()) {
		return cfg_.monsters(itr->second);
	}
	if (id > HANG_LOOP_BASE + HANG_MONSTER_ID_BASE && id <= HANG_MONSTER_ID_MAX) {
		int lv = id % HANG_MONSTER_ID_BASE;
		int index = (lv - 1) % HANG_LOOP_BASE;
		int idbase = HANG_MONSTER_ID_BASE + index + 1;
		itr = indexs.find(idbase);
		if (itr == indexs.end()) {
			error_log("monster id not exists %u", idbase);
			throw runtime_error("monster id not exists");
		}
		CfgMonster::Monster item;
		item.CopyFrom(cfg_.monsters(itr->second));
		int id56 = HANG_LOOP_BASE + HANG_MONSTER_ID_BASE;
		itr = indexs.find(id56);
		if (itr == indexs.end()) {
			error_log("monster id not exists %u", id56);
			throw runtime_error("monster id not exists");
		}
		const CfgMonster::Monster &cfg = cfg_.monsters(itr->second);
		item.set_id(id);
		item.set_attack(cfg.attack() + floor((id - HANG_LOOP_BASE) * 50));
		item.set_hp(cfg.hp() * pow(1.002, id - HANG_LOOP_BASE));
		item.set_defence(cfg.defence() * pow(1.002, id - HANG_LOOP_BASE));
		ConfigManager::Instance()->AddMonster(item);
		itr = indexs.find(id);
		if (itr != indexs.end()) {
			return cfg_.monsters(itr->second);
		}
	}
	error_log("monster id not exists %u", id);
	throw runtime_error("monster id not exists");
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


bool MonsterCfgWrap::GetPlansByMap(uint32_t mapId,vector<CfgMonster::Plan>& plans) {
	plans.clear();
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->monster_plan_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr;

	for(itr=indexs.begin();itr!=indexs.end();itr++){
		if(plan_.plans(itr->second).mapid()==mapId){
			plans.push_back(plan_.plans(itr->second));
		}
	}
	return true;
}


bool MonsterCfgWrap::GetPlansByMap(uint32_t mapId,map<uint32_t,vector<CfgMonster::Plan> >& plans) {
	plans.clear();
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->monster_plan_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr;
	for(itr=indexs.begin();itr!=indexs.end();itr++){
		if(plan_.plans(itr->second).mapid()==mapId){

			map<uint32_t,vector<CfgMonster::Plan> >::iterator its = plans.find(plan_.plans(itr->second).index());
			if(its == plans.end()){
				vector<CfgMonster::Plan> tmp;
				tmp.push_back(plan_.plans(itr->second));
				plans.insert(make_pair(plan_.plans(itr->second).index(),tmp));
			}else{
				its->second.push_back(plan_.plans(itr->second));
			}
		}
	}
	return true;
}


SkillCfgWrap::SkillCfgWrap() :
		cfg_(ConfigManager::Instance()->skill_cfg_.m_config),
		mon_cfg_(ConfigManager::Instance()->skill_monster_cfg_.m_config),
		buff_(ConfigManager::Instance()->buff_cfg_.m_config) {
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
bool SkillCfgWrap::IsZhanLing(const CfgSkill::Skill &cfg) {
	return cfg.type2() == 4;
}
bool SkillCfgWrap::IsRush(const CfgSkill::Skill &cfg) {
	return cfg.type() == 10;
}

bool SkillCfgWrap::GetBuffId(const CfgSkill::Skill &cfg, uint32_t &id) {
	size_t epos = cfg.buff().find("#");
	if (epos == string::npos) {
		return Convert::StringToUInt(id, cfg.buff());
	}
	return Convert::StringToUInt(id, cfg.buff().substr(0, epos));
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
			item.set_hurtadd(baseWrap.calcHurtAdd(base, level));
			if (IsSummon(item)) {
				item.set_hurt(90000000 + level);
			} else {
				item.set_hurt(base.hurt());
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
const CfgSkill::Buff& SkillCfgWrap::GetBuff(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->buff_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		throw std::runtime_error("buff not exist");
	}
	return buff_.buffs(itr->second);
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
const CfgHang::Hang& HangCfgWrap::Get(int32_t id){
	id = id == 0 ? 1 : id;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->hang_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr != indexs.end()) {
		return cfg_.hangs(itr->second);
	}
	int32_t base_id = GetBaseId(id);
	itr = indexs.find(base_id);
	if (itr == indexs.end()) {
		error_log("hang id not exists %u", base_id);
		throw runtime_error("hang id not exists");
	}

	int tempYu = (id - 1) % 5;
	int plan = (100021000 + floor(static_cast<float>(id - 2) / 5.0f) * 10000) + (tempYu == 0 ? 5 : tempYu);
	CfgHang::Hang item;
	item.CopyFrom(cfg_.hangs(itr->second));
	item.set_id(id);
	item.set_plan(plan);
	item.set_power(5);
	item.set_exp(20000 + id * 768);
	item.set_coin((200 + id) * (3600 / 30));
	ConfigManager::Instance()->AddHang(item);
	itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("hang id not exists %u", id);
		throw runtime_error("hang id not exists");
	}
	return cfg_.hangs(itr->second);
}
const CfgHang::Plan& HangCfgWrap::GetPlan(int32_t id) {
	id = id == 0 ? 1 : id;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->hang_plan_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr != indexs.end()) {
		return plan_.plans(itr->second);
	}
	int base_id = GetBaseId(id);
	itr = indexs.find(base_id);
	if (itr == indexs.end()) {
		error_log("hang plan id not exists %u", base_id);
		throw runtime_error("hang plan id not exists");
	}
	CfgHang::Plan item;
	item.CopyFrom(plan_.plans(itr->second));
	item.set_id(id);
	ConfigManager::Instance()->AddHangPlan(item);
	itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("hang plan id not exists %u", id);
		throw runtime_error("hang plan id not exists");
	}
	return plan_.plans(itr->second);
}
int32_t HangCfgWrap::GetBaseId(int32_t id) {
	return id - floor((id - 7) / 50) * 50;
}
int32_t HangCfgWrap::GetOnlineRewrad(int32_t id) {
	map<uint32_t, uint32_t> &cfg = ConfigManager::Instance()->hang_online_rewrad_;
	if (cfg.empty()) {
		ConstCfgWrap wrap;
		string v;
		if (!wrap.GetStr("HangOnlineEquipReward", v)) {
			return 0;
		}
		if (!ConstCfgWrap::ParseMap(v, cfg)) {
			return 0;
		}
	}
	if (cfg.empty()) {
		return 0;
	}
	map<uint32_t, uint32_t>::iterator itr = cfg.begin();
	for (; itr != cfg.end(); ++itr) {
		if (id <= itr->first) {
			return itr->second;
		}
	}
	return cfg.rbegin()->second;
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

const CfgMission::Mission& MissionCfgWrap::GetByShengId(uint32_t shengId) {
	for(int i = 0; i < cfg_.missions_size(); ++i) {
		if(shengId == cfg_.missions(i).shengid()) {
			return cfg_.missions(i);
		}
	}
	error_log("mission shengId not exists %u", shengId);
	throw runtime_error("mission shengId not exists");
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
		dan_(ConfigManager::Instance()->advance_dan_cfg_.m_config),
		strengths_(ConfigManager::Instance()->advance_strength_cfg_.m_config),
		awakens_(ConfigManager::Instance()->advance_awaken_cfg_.m_config),
		targets_(ConfigManager::Instance()->advance_target_cfg_.m_config){
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

const CfgAdvance::EquipStrength& AdvanceCfgWrap::getStrength(uint32_t type, uint32_t part, uint32_t level) {
	for(int i = 0; i < strengths_.strength_size(); ++i) {
		if(type == strengths_.strength(i).type() && part == strengths_.strength(i).part() && level == strengths_.strength(i).level()) {
			return strengths_.strength(i);
		}
	}
	error_log("advance strength not exists type:%u part:%u level:%u", type, part, level);
	throw runtime_error("advance strength not exists ");
}

const CfgAdvance::Awaken& AdvanceCfgWrap::getAwaken(uint32_t advance, uint32_t star, uint32_t type) {
	for(int i = 0; i < awakens_.awaken_size(); ++i) {
		if(advance == awakens_.awaken(i).advance() && star == awakens_.awaken(i).star() && type == awakens_.awaken(i).type()) {
			return awakens_.awaken(i);
		}
	}
	error_log("advance awaken not exists advance:%u star:%u type:%u", advance, star, type);
	throw runtime_error("advance awaken not exists ");
}

bool AdvanceCfgWrap::isExistAdvanceType(uint32_t type) {
	for(int i = 0; i < awakens_.awaken_size(); ++i) {
		if( type == awakens_.awaken(i).type()) {
			return true;
		}
	}
	return false;
}

const CfgAdvance::Target& AdvanceCfgWrap::getTarget(uint32_t advance, uint32_t type) {
	for(int i = 0; i < targets_.target_size(); ++i) {
		if(advance == targets_.target(i).advance() && type == targets_.target(i).type()) {
			return targets_.target(i);
		}
	}
	error_log("advance target not exists advance:%u type:%u", advance, type);
	throw runtime_error("advance target not exists ");
}

uint32_t AdvanceCfgWrap::GetMaxAwakenLevel() {
	int data = 0;
	for(int i = 0; i < awakens_.awaken_size(); ++i) {
		if(data < awakens_.awaken(i).advance()) {
			data = awakens_.awaken(i).advance();
		}
	}
	return data;
}

uint32_t AdvanceCfgWrap::GetMaxAwakenStar() {
	int data = 0;
	for(int i = 0; i < awakens_.awaken_size(); ++i) {
		if(data < awakens_.awaken(i).star()) {
			data = awakens_.awaken(i).star();
		}
	}
	return data;
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

bool ItemCfgWrap::IsFashion(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->item_cfg_Index;
	if(indexs.find(id) != indexs.end()){
		const CfgItem::Item &itemCfg = GetItem(id);
		if(itemCfg.itemtype()==16){
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
		//鑾峰彇涓�闃� 0 鏄熼厤缃�
		uint32_t id_0 = GetIdByType(type, 1, 0);
		uint32_t id_1 = GetIdByType(type, 1, 1);
		const CfgTreasure::Treasure& cfg_0 = GetById(id_0);
		//鑾峰彇涓�闃� 1 鏄熼厤缃�
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
		error_log("drop id not exists %u", id);
		throw std::runtime_error("drop id not exists");
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
	// 姣�10 绾ф槸鍙栦竴涓厤缃�   姣斿 23绾� 鍙� 21绾�
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(level);
	if (itr == indexs.end()) {
		error_log("purify indexId not exists %u", level);
		throw runtime_error("purify id not exists");
	}
	return cfg_.purifys(itr->second);
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

TitleCfgWrap::TitleCfgWrap(): cfg_(ConfigManager::Instance()->title_cfg_.m_config){
}
const CfgTitle::Title& TitleCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->title_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("title id not exists %u", id);
		throw runtime_error("title id not exists");
	}
	return cfg_.title(itr->second);
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

FashionCfgWrap::FashionCfgWrap(): cfg_(ConfigManager::Instance()->fashion_cfg_.m_config){
}
const CfgFashion::Fashion& FashionCfgWrap::GetFashionByIdAndLevel(uint32_t id,uint32_t level){
	uint32_t key =CFG_MAKE_KEY(level,id);
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->fashion_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("magic level = %u color = %u not exists %u", level,id,indexs.size());
		throw std::runtime_error("fashion  id and level is not exists");
	}
	return cfg_.fashions(itr->second);
}

FashionSuitCfgWrap::FashionSuitCfgWrap(): cfg_(ConfigManager::Instance()->fashion_suit_cfg_.m_config){
}
const CfgFashionSuit::FashionSuit& FashionSuitCfgWrap::GetFashionSuitByIdAndCount(uint32_t id,uint32_t count){
	uint32_t key =id * 1000 + count;
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->fashion_suit_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("magic count = %u id = %u not exists %u", count,id,indexs.size());
		throw std::runtime_error("fashionSuit  id and count is not exists");
	}
	return cfg_.fashion_suits(itr->second);
}

OnlineRewardCfgWrap::OnlineRewardCfgWrap():cfg_(ConfigManager::Instance()->online_reward_cfg_.m_config){
}
const CfgOnlineReward::OnlineReward& OnlineRewardCfgWrap::Get(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->online_reward_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		error_log("online_reward id not exists %u", id);
		throw runtime_error("online_reward id not exists");
	}
	return cfg_.onlinerewards(itr->second);
}

bool OnlineRewardCfgWrap::isOnlineRewardExist(uint32_t id) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->online_reward_cfg_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(id);
	if (itr == indexs.end()) {
		return false;
	} else {
		return true;
	}
}


CardCfgWrap::CardCfgWrap(): cards_(ConfigManager::Instance()->card_cfg_.m_config),
		stars_(ConfigManager::Instance()->card_stars_cfg_.m_config){
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

const CfgCard::Star& CardCfgWrap::GetStar(uint32_t color, uint32_t level) {
	for(int index = 0; index < stars_.star_size(); ++index) {
		if(color == stars_.star(index).color() && level == stars_.star(index).level()) {
			return stars_.star(index);
		}
	}
	error_log("get star error %d %d", color, level);
	throw std::runtime_error("get star error");
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


CardSuitWrap::CardSuitWrap(): suits_(ConfigManager::Instance()->card_suit_cfg_.m_config){
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


bool CopyWrap::GetCopyListByType(uint32_t type,vector<uint32_t> & copyIds){
	copyIds.clear();
	if(type==130){
		copyIds.push_back(901);
		return true;
	}
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->copy_Index;
	map<uint32_t, uint32_t>::const_iterator itr;
	for(itr=indexs.begin();itr!=indexs.end();itr++){
		if(copys_.copys(itr->second).type()==type){
			copyIds.push_back(copys_.copys(itr->second).copyid());
		}
	}
	if(copyIds.empty()){
		return false;
	}else{
		return true;
	}
}


const CfgCopy::Copy& CopyWrap::GetCopyByMapId(uint32_t mapId) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->copy_Index;
	map<uint32_t, uint32_t>::const_iterator itr;
	for(itr=indexs.begin();itr!=indexs.end();itr++){
		if(copys_.copys(itr->second).mapid()==mapId){
			return copys_.copys(itr->second);
		}
	}
	error_log("mapId  = %u not exists %u", mapId, indexs.size());
	throw std::runtime_error("copy id not exists");
}


bool CopyWrap::MapIsCopy(uint32_t mapId) {
	//浼欎即宀�
	if(mapId==200501||mapId==200502||mapId==200503||mapId==200504||mapId==200505){
		return true;
	}
	//绗︽枃濉�
	if(mapId==200401||mapId==200401||mapId==200401||mapId==200401||mapId==200401){
		return true;
	}
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->copy_Index;
	map<uint32_t, uint32_t>::const_iterator itr;
	for(itr=indexs.begin();itr!=indexs.end();itr++){
		if(copys_.copys(itr->second).mapid()==mapId){
			return true;
		}
	}
	return false;
}



BossWrap::BossWrap(): bosses_(ConfigManager::Instance()->boss_cfg_.m_config) {
}
const CfgBoss::Boss& BossWrap::GetBoss(uint32_t copyId) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->boss_Index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(copyId);
	if (itr == indexs.end()) {
		error_log("copyId  = %u not exists %u", copyId, indexs.size());
		throw std::runtime_error("boss id not exists");
	}
	return bosses_.boss(itr->second);
}

const CfgBoss::Boss& BossWrap::GetBossById(uint32_t bossId) {
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->boss_Index;
	for(map<uint32_t, uint32_t>::const_iterator itr =indexs.begin();itr!=indexs.end();itr++){
		if(bosses_.boss(itr->second).bossid()==bossId){
			return bosses_.boss(itr->second);
		}
	}
	error_log("bossId  = %u not exists %u", bossId, indexs.size());
	throw std::runtime_error("boss id not exists");
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

ZhuLingCfgWrap::ZhuLingCfgWrap(): zhuLings_(ConfigManager::Instance()->zhuLing_cfg.m_config),
		spets_(ConfigManager::Instance()->spet_cfg.m_config){
}

uint32_t ZhuLingCfgWrap::GetMaxZhuLinglevel() {
	uint32_t max_level = 0;
	for(int i = 0; i < zhuLings_.zhuling_size(); ++i) {
		max_level = (max_level > zhuLings_.zhuling(i).level()) ? max_level : zhuLings_.zhuling(i).level();
	}
	return max_level;
}

uint32_t ZhuLingCfgWrap::GetMaxZhuLingAdvance() {
	uint32_t max_advance = 0;
	for(int i = 0; i < zhuLings_.zhuling_size(); ++i) {
		max_advance = (max_advance > zhuLings_.zhuling(i).level()) ? max_advance : zhuLings_.zhuling(i).level();
	}
	return max_advance;
}

const CfgZhuLing::zhuLing& ZhuLingCfgWrap::GetZhuLing(uint32_t advance, uint32_t level) {
	map<uint32_t, map<uint32_t, uint32_t> >::iterator it = ConfigManager::Instance()->zhuLing_index.find(advance);
	if(it != ConfigManager::Instance()->zhuLing_index.end()) {
		map<uint32_t, uint32_t>::iterator item = it->second.find(level);
		if(item != it->second.end()) {
			return zhuLings_.zhuling(item->second);
		}
	}
	error_log("zhuLing advance:%u level:%u is not exist", advance, level);
	throw std::runtime_error("zhuLing advance&&level is not exist");
}

const CfgZhuLing::Spet& ZhuLingCfgWrap::GetSpet(uint32_t advance, uint32_t part) {
	map<uint32_t, map<uint32_t, uint32_t> >::iterator it = ConfigManager::Instance()->spet_index.find(advance);
	if(it != ConfigManager::Instance()->spet_index.end()) {
		map<uint32_t, uint32_t>::iterator item = it->second.find(part);
		if(item != it->second.end()) {
			return spets_.spets(item->second);
		}
	}
	error_log("spet advance:%u && part:%d is not exist", advance, part);
	throw std::runtime_error("spet id is not exist");
}

ZhanLingCfgWrap::ZhanLingCfgWrap(): cfg_(ConfigManager::Instance()->zhanling_base_cfg_.m_config) {
}
const CfgZhanLing::Base ZhanLingCfgWrap::GetBase(uint32_t lv) {
	for (int i = 0; i < cfg_.bases_size(); ++i) {
		if (lv == cfg_.bases(i).level()) {
			return cfg_.bases(i);
		}
	}
	throw std::runtime_error("zhan ling level not exists");
}


SignRewardsCfgWrap::SignRewardsCfgWrap() :
		signRwards_(ConfigManager::Instance()->sign_rewards_cfg_.m_config) {
}

const CfgSignRewards::signDaliyReward& SignRewardsCfgWrap::GetRewardsByIndex(
		uint32_t index) {
	if (index >= signRwards_.signdaliyrewards_size()) {
		error_log("signrewards index:%u is not exist", index);
		throw std::runtime_error("signrewards cfg index is not eixst");
	}

	return signRwards_.signdaliyrewards(index);
}

LevelRewardsCfgWrap::LevelRewardsCfgWrap() :
		levelRwards_(ConfigManager::Instance()->level_rewards_cfg_.m_config) {
}

const CfgSignRewards::levelTargetRewards& LevelRewardsCfgWrap::GetRewardByLevel(
		uint32_t careerLevel, uint32_t level) {
	if (ConfigManager::Instance()->level_reward_index.count(careerLevel) == 0
			|| ConfigManager::Instance()->level_reward_index[careerLevel].count(
					level) == 0) {
		error_log("level reward  careerlevel:%u or level: %u is not exist",
				careerLevel, level);
		throw std::runtime_error("level reward is not exist");
	}

	uint32_t index =
			ConfigManager::Instance()->level_reward_index[careerLevel][level];

	return levelRwards_.levelreward(index);
}

TrumpCfgWrap::TrumpCfgWrap() :
		trumps_(ConfigManager::Instance()->trump_info_cfg_.m_config) {

}


const CfgTrump::TrumpInfo& TrumpCfgWrap::GetTrumpsByLevel(uint32_t level) {
	if (ConfigManager::Instance()->trump_index.count(level) == 0) {
		error_log("trump cfg level=%u not exist", level);
		throw std::runtime_error("trump cfg level not exist");
	}

	uint32_t index = ConfigManager::Instance()->trump_index[level];

	return trumps_.trump(index);
}



TrumpSkillCfgWrap::TrumpSkillCfgWrap() :
		trump_skill_(ConfigManager::Instance()->trump_skill_cfg_.m_config) {
}

const CfgTrump::TrumpSkillInfo& TrumpSkillCfgWrap::GetTrumpsByStage(uint32_t stage)
{
	if (ConfigManager::Instance()->trump_skill_index.count(stage) == 0) {
		error_log("trump skill cfg stage=%u not exist", stage);
		throw std::runtime_error("trump skill cfg level not exist");
	}

	uint32_t index = ConfigManager::Instance()->trump_index[stage];

	return trump_skill_.trump_skill(index);
}

ShengMissionCfgWrap::ShengMissionCfgWrap(): shengMissions_(ConfigManager::Instance()->sheng_missions_cfg_.m_config) {
}

bool ShengMissionCfgWrap::isExistMission(uint32_t id) {
	return ConfigManager::Instance()->sheng_missions_index.count(id);
}

uint32_t ShengMissionCfgWrap::getLimitReinCarnLevel() {
	uint32_t miniLevel = shengMissions_.sheng_mission(0).reincarnlevel();
	for(int i = 0; i < shengMissions_.sheng_mission_size(); ++i) {
		if(miniLevel > shengMissions_.sheng_mission(i).reincarnlevel()) {
			miniLevel = shengMissions_.sheng_mission(i).reincarnlevel();
		}
	}
	return miniLevel;
}

const CfgReinCarnSheng::ShengMission& ShengMissionCfgWrap::getShengMission(int32_t part, uint32_t reinCarnLevel) {
	uint32_t miniLevel = shengMissions_.sheng_mission(0).reincarnlevel();
	for(int i = 0; i < shengMissions_.sheng_mission_size(); ++i) {
		if(part == shengMissions_.sheng_mission(i).part() &&
				reinCarnLevel == shengMissions_.sheng_mission(i).reincarnlevel()) {
			return shengMissions_.sheng_mission(i);
		}
	}
	error_log("shengMission:part:%d, reinCarnLevel:%d not exist", part, reinCarnLevel);
	throw std::runtime_error("shengMission is not exist");
}

const CfgReinCarnSheng::ShengMission& ShengMissionCfgWrap::getShengMission(uint32_t id) {
	map<uint32_t, uint32_t> index = ConfigManager::Instance()->sheng_missions_index;
	map<uint32_t, uint32_t>::iterator it = index.find(id);
	if(it != index.end()) {
		return shengMissions_.sheng_mission(it->second);
	}
	error_log("shengMission id is not exist");
	throw std::runtime_error("shengMission id is not exist");
}


PartnerIslandWrap::PartnerIslandWrap(): partnerIslands(ConfigManager::Instance()->partnerIsland_cfg_.m_config) {
}
const CfgPartnerIsland::PartnerIsland& PartnerIslandWrap::GetPartnerIsland(uint32_t type,uint32_t layer) {
	uint32_t key =CFG_MAKE_KEY(type,layer);
	const map<uint32_t, uint32_t> &indexs = ConfigManager::Instance()->partnerIsland_index;
	map<uint32_t, uint32_t>::const_iterator itr = indexs.find(key);
	if (itr == indexs.end()) {
		error_log("PartnerIslandWrap type = %u layer = %unot exists %u", type,layer,indexs.size());
		throw std::runtime_error("PartnerIsland not exists");
	}
	return partnerIslands.partner_islands(itr->second);
}

ShopCfgWrap::ShopCfgWrap(): shop_cell_(ConfigManager::Instance()->shop_cell_cfg_.m_config){
}

const CfgShop::ShopCell& ShopCfgWrap::get(uint32_t id) {
	map<uint32_t, uint32_t> &index = ConfigManager::Instance()->shop_cell_cfg_index;
	map<uint32_t, uint32_t>::iterator it = index.find(id);
	if(it != index.end()) {
		return shop_cell_.shop_cell(it->second);
	}
	error_log("shop cell:%u not exist", id);
	throw std::runtime_error("shop cell not exist");
}

MoneyCfgWrap::MoneyCfgWrap(): item_money_(ConfigManager::Instance()->item_money_cfg_.m_config){
}

bool MoneyCfgWrap::isMoneyType(uint32_t id) {
	return ConfigManager::Instance()->item_money_cfg_index.count(id);
}

const CfgMoney::ItemMoney& MoneyCfgWrap::get(uint32_t id) {
	map<uint32_t, uint32_t> &index = ConfigManager::Instance()->item_money_cfg_index;
	map<uint32_t, uint32_t>::iterator it = index.find(id);
	if(it != index.end()) {
		return item_money_.item_money(it->second);
	}
	error_log("money item:%u not exist", id);
	throw std::runtime_error("money item not exist");
}

ConstCfgWrap::ConstCfgWrap(): cfg_(ConfigManager::Instance()->const_cfg_.m_config) {
}
const CfgConst::Item& ConstCfgWrap::Get(const string &n) {
	const map<string, uint32_t> &indexs = ConfigManager::Instance()->const_cfg_Index;
	map<string, uint32_t>::const_iterator itr = indexs.find(n);
	if (itr == indexs.end()) {
		error_log("const id not exists %s", n.c_str());
		throw std::runtime_error("const id not exists");
	}
	return cfg_.consts(itr->second);
}
bool ConstCfgWrap::GetStr(const string &n, string &v) {
	try {
		const CfgConst::Item &cfg = Get(n);
		v = cfg.s();
		return true;
	} catch (...) {
		return false;
	}
}
bool ConstCfgWrap::ParseMap(const string &v, map<uint32_t, uint32_t> &m) {
	vector<string> items;
	CBasic::StringSplitTrim(v, "&", items);
	vector<string>::iterator itr = items.begin();
	for (; itr != items.end(); ++itr) {
		vector<string> node;
		CBasic::StringSplitTrim(*itr, "#", node);
		if (node.size() != 2) {
			continue;
		}
		uint32_t k = 0, v= 0;
		if (!Convert::StringToUInt(k, node[0])) {
			continue;
		}
		if (!Convert::StringToUInt(v, node[1])) {
			continue;
		}
		m[k] = v;
	}
	return true;
}
