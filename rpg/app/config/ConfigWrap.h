/*
 * ConfigWrap.h
 *
 *  Created on: 2016-9-12
 *      Author: dawx62fac
 */

#ifndef USERCFGWRAP_H_
#define USERCFGWRAP_H_

#include "ConfigInc.h"
#include "ConfigManager.h"

class MapCfgWrap {
public:
	MapCfgWrap();
	const CfgMap::Map& Get(uint32_t id);
private:
	const CfgMap::Maps& cfg_;
};

class DungeonCfgWrap {
public:
	DungeonCfgWrap();
	const CfgDungeon::DungeonItem& Get(uint32_t id);
	uint32_t GetSize() {
		return cfg_.dungeonconfig_size();
	}
private:
	const CfgDungeon::Dungeon& cfg_;
};

class MonsterCfgWrap {
public:
	MonsterCfgWrap();
	const CfgMonster::Monster& Get(uint32_t id);
	const CfgMonster::Plan& GetPlan(uint32_t id);
private:
	const CfgMonster::Monsters& cfg_;
	const CfgMonster::Plans& plan_;
};

class SkillCfgWrap {
public:
	SkillCfgWrap();
	bool IsExist(uint32_t id);
	bool IsSummon(const CfgSkill::Skill &cfg);
	bool IsNormal(const CfgSkill::Skill &cfg);
	bool IsSprint(const CfgSkill::Skill &cfg);
	bool IsAddBuff(const CfgSkill::Skill &cfg);
	const CfgSkill::Skill& Get(uint32_t id);
	const CfgSkill::Skill& GetById(uint32_t id);
	const CfgSkill::Skill& GetByLv(uint32_t serial, uint32_t lv, uint32_t id);
	const CfgSkill::Skill& GetFirst(uint32_t serial);
private:
	const CfgSkill::Skills& cfg_;
	const CfgSkill::Skills& mon_cfg_;
};

class SkillBaseCfgWrap {
public:
	SkillBaseCfgWrap();
	bool IsExist(uint32_t id);
	const CfgSkill::Base& Get(uint32_t id);
	uint32_t calcHurtAdd(const CfgSkill::Base &cfg, uint32_t lv);
	uint32_t calcCost(const CfgSkill::Base &cfg, uint32_t lv);
	uint32_t calcLevelLimit(const CfgSkill::Base &cfg, uint32_t lv);
	uint32_t calcCareerLevel(uint32_t lv);
private:
	const CfgSkill::Bases& cfg_;
};

class SceneCfgWrap {
public:
	enum {
		SCENE_TYPE_CITY = 0,	//主城
		SCENE_TYPE_HANG = 2,		//挂机
		SCENE_TYPE_BOSS = 3		//BOSS
	};
	SceneCfgWrap();
	const CfgMap::Scene& Get(int32_t mapid);
	const CfgMap::Point& GetBossPoint(int32_t mapid, int32_t plan);
private:
	const CfgMap::Scenes& cfg_;
};

class HangCfgWrap {
public:
	HangCfgWrap();
	const CfgHang::Hang& Get(int32_t id);
	const CfgHang::Plan& GetPlan(int32_t id);
private:
	const CfgHang::Hangs& cfg_;
	const CfgHang::Plans& plan_;
};

class LevelCfgWrap {
public:
	LevelCfgWrap();
	const CfgLevel::Level& Get(uint32_t id);
	const CfgLevel::Attr& GetAttr(uint32_t id);
private:
	const CfgLevel::Levels& cfg_;
	const CfgLevel::Attrs& attr_;
};

class MissionCfgWrap {
public:
	MissionCfgWrap();
	bool IsExist(uint32_t id);
	const CfgMission::Mission& Get(uint32_t id);
private:
	const CfgMission::Missions& cfg_;
};

class AdvanceCfgWrap {
public:
	AdvanceCfgWrap();
	const CfgAdvance::Advance& Get(uint32_t type, uint32_t group, uint32_t star);
	const CfgAdvance::Dan& GetDan(uint32_t type, uint32_t level, uint32_t item);
	const CfgAdvance::Dan& GetDanById(uint32_t type, uint32_t level, uint32_t id);
	uint32_t GetDanCount(uint32_t type, uint32_t level);
private:
	const CfgAdvance::Advances& cfg_;
	const CfgAdvance::Dans& dan_;
};

class ItemCfgWrap {
public:
	ItemCfgWrap();
	bool IsItem(uint32_t id);
	bool IsEquip(uint32_t id);
	bool IsMagic(uint32_t id);
	bool IsTitle(uint32_t id);
	bool IsGift(uint32_t id);
	bool IsFixedGift(const CfgItem::Gift &cfg);
	bool IsRandomGift(const CfgItem::Gift &cfg);
	bool IsFixedRandomGift(const CfgItem::Gift &cfg);
	bool IsSelectGift(const CfgItem::Gift &cfg);
	const CfgItem::Item& GetItem(uint32_t id);
	const CfgItem::Equip& GetEquip(uint32_t id);
	const CfgItem::Gift& GetGift(uint32_t id);
	const CfgItem::Attr& GetAttr(uint32_t id);
	const CfgItem::Drop& GetDrop(uint32_t id);
private:
	const CfgItem::Items& item_;
	const CfgItem::Equips& equip_;
	const CfgItem::Gifts& gift_;
	const CfgItem::Attrs& attr_;
	const CfgItem::Drops& drop_;
};

class TreasureCfgWrap {
public:
	TreasureCfgWrap();
	bool IsExist(uint32_t id);
	const CfgTreasure::Treasure& GetById(uint32_t id);
	uint32_t GetIdByType(uint32_t type, uint32_t level, uint32_t star);
	uint32_t GetDanIndex(uint32_t type, uint32_t level, uint32_t star, uint32_t id);
	uint32_t GetDanLimit(uint32_t type, uint32_t level, uint32_t star, uint32_t id);
	uint32_t GetDanId(uint32_t type, uint32_t level, uint32_t star, uint32_t index);
	const CfgTreasure::Hunt& GetHunt(uint32_t id);
	const CfgTreasure::Hunt& GetHuntByIndex(int id);
	const CfgTreasure::HuntBase& GetHuntBase(uint32_t id);
private:
	const CfgTreasure::Treasure& Get(uint32_t id);
private:
	const CfgTreasure::Treasures& treasures;
	const CfgTreasure::Hunts& hunt_;
	const CfgTreasure::HuntBases& hunt_base_;
};

class ForgeCfgWrap {
public:
	ForgeCfgWrap();
	const CfgForge::Strengthen& GetStrengthen(uint32_t id);
private:
	const CfgForge::Strengthens& strengthen_;
};

class PurifyCfgWrap {
public:
	PurifyCfgWrap();
	const CfgPurify::Purify& Get(uint32_t level);
	const CfgPurify::Purify& GetByLevel(uint32_t level);
	bool isExist(uint32_t level);
private:
	const CfgPurify::Purifys& cfg_;
};

class TitleCfgWrap {
public:
	TitleCfgWrap();
	const CfgTitle::Title& Get(uint32_t id);
	bool isTitleExist(uint32_t id);
private:
	const CfgTitle::Titles& cfg_;
};


class CardCfgWrap {
public:
	CardCfgWrap();
	const CfgCard::Card& GetCard(uint32_t id);
private:
	const CfgCard::Cards& cards_;
};

class CardGroupWrap {
public:
	CardGroupWrap();
	const CfgCard::CardGroup& GetCardGroup(uint32_t key);
private:
	const CfgCard::CardGroups& cardGroups_;
};

class CardSuitWrap {
public:
	CardSuitWrap();
	const CfgCard::Suit& GetSuit(uint32_t id);
	const CfgCard::Suit& GetSuitByCard(uint32_t cardId);
private:
	const CfgCard::Suits& suits_;
};

class RoleSuitWrap {
public:
	RoleSuitWrap();
	bool isSuitExist(uint32_t id);
	const CfgSuit::Suit& GetSuit(uint32_t id);
	const CfgSuit::Suit& GetSuitByCard(uint32_t cardId);
private:
	const CfgSuit::Suits& suits_;
};

class RingWrap {
public:
	RingWrap();
	const CfgRing::Ring& GetRing(uint32_t level);
private:
	const CfgRing::Rings& rings_;
};


class ReinCarnWrap {
public:
	ReinCarnWrap();
	const CfgReinCarn::ReinCarn& GetReinCarn(uint32_t level);
private:
	const CfgReinCarn::ReinCarns& reincarns_;
};



class MagicWrap {
public:
	MagicWrap();
	const CfgMagic::Magic& GetMagic(uint32_t level,uint32_t type);
private:
	const CfgMagic::Magics& magics_;
};


class MagicTowerWrap {
public:
	MagicTowerWrap();
	const CfgMagic::MagicTower& GetMagicTower(uint32_t id);
private:
	const CfgMagic::MagicTowers& magicTowers_;
};


class CopyWrap {
public:
	CopyWrap();
	const CfgCopy::Copy& GetCopy(uint32_t copyId);
private:
	const CfgCopy::Copys& copys_;
};


class BossWrap {
public:
	BossWrap();
	const CfgBoss::Boss& GetBoss(uint32_t bossType);
private:
	const CfgBoss::Bosses& bosses_;
};

class ActivityCfgWrap {
public:
	ActivityCfgWrap();
	bool isActExist(uint32_t id);
	bool isActiveExit(uint32_t active, uint32_t level);
	uint32_t GetActiveLimit(uint32_t id, uint32_t level);
	const CfgActivity::DaliyAct& GetAct(uint32_t id);
	const CfgActivity::Active& GetActive(uint32_t active, uint32_t level);
private:
	const CfgActivity::DaliyActs& daliyAct_;
	const CfgActivity::Actives& actives_;
};

#endif /* USERCFGWRAP_H_ */
