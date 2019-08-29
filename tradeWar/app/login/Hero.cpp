/*
 * Hero.cpp
 *
 *  Created on: 2015-8-27
 *      Author: Administrator
 */

#include "Hero.h"
#include "DataHero.h"
#include "HeroConfig.h"
#include "PlayerManager.h"
#include "Formula.h"
#include "MonsterConfig.h"

Hero::Hero() {
	m_pm = NULL;
	m_appear = 0;
	m_race = RACE_TYPE_HERO;
	m_captiveUid = 0;
	m_guard_range = 0;
	m_isReturn = false;
	m_oldHp = 0;
}
Hero::~Hero() {
}
bool Hero::setData(const string& jsonData) {
	Json::Value heroData;
	Json::Reader reader;
	if (!reader.parse(jsonData, heroData)) {
		error_log("hero data json parse failed:%s", jsonData.c_str());
		return false;
	}
	uint32_t heroType = 0;
	if (!Json::GetUInt(heroData, "t", heroType)) {
		error_log("must has field t,%s", jsonData.c_str());
		return false;
	}
	if (!HeroConfig::getInstance()->isExist(heroType)) {
		error_log("hero not exist type=%u", heroType);
		return false;
	}
	EXTRACT_JSON_INT(heroData, "ud");
	EXTRACT_JSON_INT(heroData, "l");
	EXTRACT_JSON_INT(heroData, "t");
	EXTRACT_JSON_INT(heroData, "bornlv");	//第一 个天生技
	EXTRACT_JSON_INT(heroData, "bornlv2");	//第二个天生技
	EXTRACT_JSON_INT(heroData, "bud");		//进驻要塞的ud
	EXTRACT_JSON_INT(heroData, "exp");
	EXTRACT_JSON_INT(heroData, "grade");
	EXTRACT_JSON_INT(heroData, "hp");
	EXTRACT_JSON_FLOAT(heroData, "pt");
	EXTRACT_JSON_INT(heroData, "cr");
	EXTRACT_JSON_INT(heroData, "cu");
	EXTRACT_JSON_INT(heroData, "upts");
	EXTRACT_JSON_INT(heroData, "q");
	EXTRACT_JSON_INT(heroData, "rs");
	EXTRACT_JSON_INT(heroData, "star");
	EXTRACT_JSON_INT(heroData, "status"); 	// 是否是主将
	EXTRACT_JSON_INT(heroData, "ctcd"); 	// 训练获得的经验值
	EXTRACT_JSON_INT(heroData, "spirit"); 	// 将灵
	EXTRACT_JSON_INT(heroData, "upslot");
	if (m_data[AP_UPGRADE_SLOT].pi > 10) {
		m_data[AP_UPGRADE_SLOT].pi = 0;
		saveData();
	}
	EXTRACT_JSON_INT(heroData, "state"); 	// 出战/非出战
	EXTRACT_JSON_INT(heroData, "rsci1");
	EXTRACT_JSON_INT(heroData, "rsci2");
	EXTRACT_JSON_INT(heroData, "cdt");
	EXTRACT_JSON_INT(heroData, "rl");
	EXTRACT_JSON_INT(heroData, "buddy");
	EXTRACT_JSON_INT(heroData, "jl");
	EXTRACT_JSON_INT(heroData, "ce");

	Json::GetUInt(heroData, "cuid", m_captiveUid);

	return true;
}
bool Hero::encode(IBuffer* buffer) {
	static const uint32_t encodeAttrList[] = { AP_X, AP_Y, AP_TYPE, AP_UD, AP_LEVEL, AP_HA, AP_MA, AP_HD, AP_MD, AP_IP, AP_BP,
	AP_BV, AP_SP, AP_RP, AP_EV, AP_EP, AP_HE, AP_HEP, AP_ME, AP_MEP, AP_TA, AP_HR, AP_RANGE,
	AP_HP, AP_MP, AP_MAX_HP, AP_MAX_MP, AP_CR, AP_STATUS, AP_HERO_BUNKER, AP_EXP,
	AP_STAR, AP_PT, AP_GRADE, AP_ZHEN, AP_BS_LVL, AP_BS_LVL2, AP_P1, AP_P2, AP_P3, AP_P4, AP_P5, AP_UPTS, AP_CR, AP_RIDE_STAR, AP_EBP,
	AP_PROF, AP_STATE, AP_RIDE_SCIENCE1, AP_RIDE_SCIENCE2, AP_COMBAT, AP_STAT, AP_CD_TIME, AP_RIDE_LEVEL, AP_BUDDY_POS, AP_ENERGY };

	static CStaticBuffer<MAX_ITEM_PACKET> tmpBuff;
	tmpBuff.Clear();
	PACK_PROPS(encodeAttrList, tmpBuff);

	CBufferWriter writer(buffer);
	writer.AppendUInt16(tmpBuff.GetSize());
	buffer->AppendBuffer(&tmpBuff);

	return true;
}
bool Hero::saveData(bool isNew) {
	Json::Value value;

	PUSH_JSON_INT(value, AP_UD);			//ud
	PUSH_JSON_INT(value, AP_HERO_BUNKER);	//bud
	PUSH_JSON_INT(value, AP_HP);			//血量
	PUSH_JSON_INT(value, AP_LEVEL);			//等级
	PUSH_JSON_INT(value, AP_TYPE);			//类型
	PUSH_JSON_INT(value, AP_STATUS);		//是否是主将
	PUSH_JSON_INT(value, AP_UPTS);
	PUSH_JSON_INT(value, AP_BS_LVL);
	PUSH_JSON_INT(value, AP_BS_LVL2);
	PUSH_JSON_INT(value, AP_GRADE);			//潜能阶
	PUSH_JSON_INT(value, AP_EXP);
	PUSH_JSON_INT(value, AP_CR);
	PUSH_JSON_INT(value, AP_CU);
	PUSH_JSON_INT(value, AP_RIDE_STAR);
	PUSH_JSON_INT(value, AP_RIDE_LEVEL);
	PUSH_JSON_INT(value, AP_STAR);
	PUSH_JSON_INT(value, AP_TRAIN_GAIN_EXP);
	PUSH_JSON_INT(value, AP_STATE);
	PUSH_JSON_INT(value, AP_RIDE_SCIENCE1);
	PUSH_JSON_INT(value, AP_RIDE_SCIENCE2);
	PUSH_JSON_INT(value, AP_UPGRADE_SLOT);
	PUSH_JSON_INT(value, AP_CD_TIME);
	PUSH_JSON_INT(value, AP_SPIRIT);
	PUSH_JSON_INT(value, AP_BUDDY_POS);
	PUSH_JSON_INT(value, AP_ENERGY);
	PUSH_JSON_INT(value, AP_CE);

	value["cuid"] = m_captiveUid;

	if (!addOrSetHero(getUid(), value, isNew)) {
		error_log("addOrSetHero_fail");
		return false;
	}
	return true;
}
bool Hero::delData() {
	int ret = 0;
	CDataHero dbData;
	if ((ret = dbData.RemoveOneHero(getUid(), getUD())) != 0) {
		error_log("RemoveOneHero_fail&uid=%u&id=%u&ret=%d", getUid(), getUD(), ret);
		return false;
	}
	debug_log("RemoveOneHero&uid=%u&id=%u&ret=%d", getUid(), getUD(), ret);
	return true;
}
bool Hero::saveDataGeneral(uint32_t uid, PropertySets& m_data, bool isNew) {
	Json::Value value;

	PropertySets::iterator iter = m_data.begin();
	for (; iter != m_data.end(); ++iter) {
		if (!PropertyConfig::setAttr(value, iter->first, iter->second)) {
			error_log("setAttr_fail&type=%u", iter->first);
			continue;
		}
	}

	int ret = addOrSetHero(uid, value, isNew);
	if (ret != 0) {
		error_log("addOrSetBuilding_fail");
		return false;
	}
	return true;
}
bool Hero::addOrSetHero(uint32_t uid, Json::Value& value, bool isNew) {
	Json::FastWriter writer;
	CDataHero dbData;
	DataHero data;
	data.uid = uid;
	if (!value.isMember("ud")) {
		error_log("no_exist_ud_in_data&uid=%u", data.uid);
		return false;
	}
	if (!Json::GetUInt(value, "ud", data.id)) {
		error_log("parse_value_fail uid=%u", data.uid);
		return false;
	}
	data.data = Json::FastWriter().write(value);
	if (data.data.empty()) {
		error_log("hero_data_is_empty&uid=%u&id=%u", data.uid, data.id);
		return false;
	}

	int ret = 0;
	if (isNew) {
		if ((ret = dbData.AddHero(data.uid, data.id, data.data)) != 0) {
			error_log("AddHero_fail&uid=%u&id=%u&ret=%d", data.uid, data.id, ret);
			return false;
		}
	} else {
		if ((ret = dbData.SetHero(data.uid, data.id, data.data)) != 0) {
			error_log("SetHero_fail&uid=%u&id=%u&ret=%d", data.uid, data.id, ret);
			return false;
		}
	}

	return true;
}

bool Hero::calcProps() {
	PropertySets props;
	m_pm->calcHeroProps(getType(), getLevel(), getUD(), getStar(), props);
	props[AP_MAX_MP].pui = 50;
	props[AP_MP].pui = 0;

	PROPERTY_COMPOSITE(props, m_data);

	if (IS_VALID_NPC_UID(getUid()))	// npc有将灵属性加成
			{
		setMaxHp(getMaxHp() + getSpirit() * 10);
		setHp(getMaxHp());
		setHa(getHa() + getSpirit());
		setHd(getHd() + getSpirit());
	}

	calcCombat();

	return true;
}
bool Hero::initProps() {
	PropertySets props;
	HeroConfig::getInstance()->getProps(getType(), getLevel(), props);
	return true;
}
void Hero::calcCombat() {
	/*
	 if (getMoveSpeed() == 0)
	 {
	 return;
	 }
	 uint32_t before = m_data[AP_COMBAT].pui;
	 int combat = 0.8 * getHa() + 0.6 * getHd() + 0.1 * getMaxHp() + 6 * (getIp() + getHr()) + 5.5 * (getBp() + getEbp()) + 0.01 * getAttackSpeed() * getHa() + 0.1 * (getMoveSpeed() - 60);
	 combat += m_pm->getSkillCombat(this->getUD());
	 */
	int combat = 0;
	m_data[AP_COMBAT].pui = combat > 0 ? combat : 0;
}
bool Hero::initFromMonster() {
	if (!MonsterConfig::getInstance()->getMonsterConfig(getType(), getLevel(), m_data)) {
		// 初始化属性失败就给默认属性
		setProf(1);
		setMoveSpeed(180);
		setAttackRadius(200);
		setMaxHp(5000);
		setAttackSpeed(100);
		setHa(100);
		setHd(100);
		error_log("init_attack_npc fail uid=%u ud=%u type=%u", getUid(), getUD(), getType());
	}

	setUserName("ATTACK_HERO");
	setHp(getMaxHp());
	return true;
}
bool Hero::onComplelete(uint32_t type) {
	return true;
}
bool Hero::onDie() {
	return true;
}
bool Hero::sendPropChange() {
	calcCombat();
	CNetPacket sPacket;
	sPacket.uid = getUid();
	CBufferWriter writer(&sPacket.body);
	writer.AppendByte(PROTOCOL_CMD_HERO);
	writer.AppendByte(PROTOCOL_RSP_SUBCMD_HERO_PROP_CHANGE);
	writer.AppendByte(0);
	encodePropsChange(&sPacket.body);
	if (!PlayerManager::getInstance()->sendToAccess(&sPacket)) {
		error_log("sendAccess_fail&uid=%u", getUid());
		return false;
	}
	return true;
}
bool Hero::onRecoveEnergy() {
	if (getEnergy() >= getMaxEnergy()) {
		return false;
	}
	const static uint32_t CD = 180;
	if (LogicManager::GlobalTime - getCe() >= CD) {
		uint32_t count = (LogicManager::GlobalTime - getCe()) / CD;
		setCe(getCe() + count * CD);
		setEnergy(getEnergy() + count > getMaxEnergy() ? getMaxEnergy() : getEnergy() + count);
		return true;
	}
	return false;
}

bool Hero::onRecove() {
	return true;
}
bool Hero::needRecove() {
	return getHp() < getMaxHp();
}
bool Hero::needTimer() {
	return needRecove() || (getCu() > 0 && getUpSlot() > 0) || getEnergy() < getMaxEnergy();
}
bool Hero::resetCu() {
	if (getCu() == 0) {
		return true;
	}
	uint32_t oldUpts = getUpts();
	uint32_t now = Time::GetGlobalTime();
	if (now > oldUpts) {
		uint32_t timeShift = now - oldUpts;
		setCu(timeShift >= getCu() ? 1 : getCu() - timeShift);
	}
	return true;
}
bool Hero::initActionTime() {
	uint32_t now = Time::GetGlobalTime();
	if (now < getUpts()) {
		setUpts(now);
		saveData();
		error_log("initActionTime fail");
		return false;
	}
	bool isContinue = false;
	bool needSave = false;
	if (getHp() < getMaxHp()) {
		uint32_t timeShift = now - getUpts();	//经过了多久
		uint32_t clevel = 0;
		uint32_t hpNeed = getMaxHp() - getHp();
		uint32_t hpNeedCount = hpNeed / (getRecoveValue() * getMaxHp()) + 0.5;
		uint32_t hpNeedInter = getRecoveInter(getLevel(), clevel);
		uint32_t timeNeed = hpNeedInter * hpNeedCount;
		if (timeNeed <= timeShift) {
			setTick(0);
			setHp(getMaxHp());
		} else {
			uint32_t hpAdd = getMaxHp() * getRecoveValue() * (timeShift / hpNeedInter);
			uint32_t tickLeft = hpNeedInter - timeShift % hpNeedInter;
			setTick(tickLeft);
			setHp(getHp() + hpAdd);
			setCr(std::min(hpNeedInter, timeNeed - timeShift));
		}
		needSave = true;
		isContinue = true;
	}
	if (getCu() > 0 && getUpSlot() > 0) // 需要升级
			{
		if (!needSave) {
			needSave = getCu() > 1;
		}
		if (getUpts() + getCu() > now) // 未升级完成
				{
			setCu(getCu() + getUpts() - now);
		} else // 训练完成
		{
			setCu(1);
		}
		isContinue = true;
	}
	if (getEnergy() < getMaxEnergy()) {
		isContinue = true;
	}
	if (needSave) {
		setUpts(now);
		saveData();
	}
	return isContinue;
}
uint32_t Hero::getRecoveInter(uint32_t level, uint32_t clevel) {
	uint32_t ret;
	int valuea = (15 + uint32_t(level / 10) * 5) * 60 - clevel * 60;
	int valueb = 8 * 60;
	if (valuea > valueb) {
		ret = valuea;
	} else {
		ret = valueb;
	}
	return (uint32_t) ret / 100;
}
float Hero::getRecoveValue() {
	return 0;
}
uint32_t Hero::getPlayerBuildingLevel(uint32_t type) {
	Player * player = PlayerManager::getInstance()->LoadExistPlayer(getUid());
	if (player) {
		return player->getBm()->getBuildingLevel(type);
	} else {
		return 0;
	}
}
uint32_t Hero::getPlayerLevel() {
	Player * player = PlayerManager::getInstance()->LoadExistPlayer(getUid());
	if (player) {
		return player->getLevel();
	} else {
		return 0;
	}
}
uint32_t Hero::getAddPoint() {
	/*
	 uint32_t addPoint = 0;
	 for (uint32_t i = 1; i < getStar(); ++i)
	 {
	 HeroDevelopItem item;
	 HeroConfig::getInstance()->getHeroDevelop(i, item);
	 addPoint += item.increment;
	 }
	 addPoint *= HeroConfig::getInstance()->getPoint(getType()) * 0.01;
	 addPoint += getGrade() * 0.1;
	 return addPoint;
	 */
	return 0;
}
bool Hero::onTrainOver() {
	string code;
	String::Format(code, "hero_train_over_%u", getUD());
	upExp(getTrainExp(), code);
	setTrainExp(0);
	setUpSlot(0);
	return true;
}
// 经验值变化是判断英雄是否升级
bool Hero::onLevelUp() {
	ExpConfig* pec = ExpConfig::getInstance();
	if (pec == NULL) {
		error_log("ExpConfig::getInstance is NULL");
		return false;
	}
	uint32_t nextLevel = pec->getNextHeroLevel(getLevel(), getExp());
	uint32_t playerLevel = getPlayerLevel();
	if (playerLevel == 0) {
		error_log("invalid param: playerLevel=%u", playerLevel);
		return false;
	}

	if (nextLevel > playerLevel) // 英雄等级不能超过玩家等级
			{
		nextLevel = playerLevel;
		uint32_t nextMaxExp = 0;
		if (ExpConfig::getInstance()->getHeroExp(nextLevel + 1, nextMaxExp)) {
			nextMaxExp -= 1;
		}
		setExp(nextMaxExp);
	}
	if (nextLevel > getLevel()) {
		setLevel(nextLevel);
		PlayerManager::getInstance()->onHeroLevelUp(getUid());
		PlayerManager::getInstance()->setPlayerPropChange(getUid());
		calcProps();
		setHp(getMaxHp());
		debug_log("uid=%u ud=%u level=%u maxhp=%u", getUid(), getUD(), getLevel(), getMaxHp());
	}

	return true;
}
bool Hero::onPropChangeByPoint(uint32_t point, PropertySets& props) {
	return true;
}

bool Hero::upExp(uint32_t exp, const string& code) {
	if (exp == 0) {
		return true;
	}
	m_data[AP_EXP].pui += exp;
	onLevelUp();
	saveData();
	Player * player = PlayerManager::getInstance()->LoadExistPlayer(getUid());
	if (player != NULL && !player->sendHeroInfo(getUD())) {
		error_log("sendHeroInfo fail uid=%u ud=%u", getUid(), getUD());
		return false;
	}
	BUSI_MISC("upExp code=%s|%u|%u|%u|%u|%u|", code.c_str(), getUid(), getUD(), exp, getExp(), getLevel());
	return true;
}

void Hero::resetEnergyTs() {
	if (getEnergy() + SPAWN_HERO_ENERGY >= getMaxEnergy()) {
		setCe(Time::GetGlobalTime());
	}
}

void Hero::costEnergy(uint32_t cost) {
	setEnergy(getEnergy() > cost ? getEnergy() - cost : 0);
}
