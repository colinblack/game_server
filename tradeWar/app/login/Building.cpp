/*
 * Building.cpp
 *
 *  Created on: 2015-9-1
 *      Author: Administrator
 */

#include "Building.h"
#include "BuildingConfig.h"
#include "PlayerManager.h"


Building::Building() {
	m_race = RACE_TYPE_BUILDING;
	m_available_resource = 0;
	m_tick = 0;
	m_pm = NULL;
	m_isActive = true;
	m_produceRatio = 0;
}

Building::~Building() {
}

bool Building::setData(const Json::Value& data) {
	EXTRACT_JSON_UINT(data, "ud"); //1
	EXTRACT_JSON_UINT(data, "t");
	EXTRACT_JSON_UINT(data, "l");
	EXTRACT_JSON_INT(data, "x");
	EXTRACT_JSON_INT(data, "y");
	EXTRACT_JSON_UINT(data, "hp");
	EXTRACT_JSON_UINT(data, "status");
	EXTRACT_JSON_UINT(data, "upts");
	EXTRACT_JSON_UINT(data, "cb");
	EXTRACT_JSON_UINT(data, "cu");
	EXTRACT_JSON_UINT(data, "cr"); //11
	EXTRACT_JSON_UINT(data, "cp");
	EXTRACT_JSON_UINT(data, "st");
	EXTRACT_JSON_UINT(data, "bud");
	EXTRACT_JSON_UINT(data, "s");
	EXTRACT_JSON_UINT(data, "hs");
	return true;
}

bool Building::setData(const string& jsonData) {
	Json::Value data;
	Json::Reader reader;
	if (!reader.parse(jsonData, data)) {
		error_log("building data json parse failed:%s", jsonData.c_str());
		return false;
	}
	setData(data);
	return true;
}

void Building::propsCalc() {
	if (m_pm == NULL) {
		return;
	}
	PropertySets props;
	m_pm->calcBuildingProps(getType(), getLevel(), getUD(), getStrong(), props);

	calcSpecialProps(props);

	PROPERTY_COMPOSITE(props, m_data);
}

void Building::calcCombat() {
	//const HeroLevelProp* hlp = HeroConfig::getInstance()->getLevelProp(getLevel());
	//double critRatio = (hlp == NULL || hlp->critRate == 0) ? 0 : (getBp() / hlp->critRate);
	// 城防计算
	//int combat = 0.01 * getHa() * getAttackRadius() * getAttackSpeed() * 0.01 * (1 + critRatio) + getMaxHp() / 30 + getHd();
	int combat = 0.01 * getHa() * getAttackRadius() * getAttackSpeed() * 0.01 + getMaxHp() / 30 + getHd();
	m_data[AP_COMBAT].pui = combat > 0 ? combat : 0;
}

void Building::getRateProps(PropertySets & props) {
	props.clear();
	PropertySets tmpProps;
	//计算buff、科技等等属性加成
}

void Building::getAddProps(PropertySets & props) {
	props.clear();
	PropertySets tmpProps;
	//计算buff、科技等等属性加成
}

bool Building::saveData(bool isNew) {
	Json::Value value;
	PUSH_JSON_INT(value, AP_UD); //1
	PUSH_JSON_INT(value, AP_TYPE);
	PUSH_JSON_INT(value, AP_LEVEL);
	PUSH_JSON_INT(value, AP_X);
	PUSH_JSON_INT(value, AP_Y);
	PUSH_JSON_INT(value, AP_HP);
	PUSH_JSON_INT(value, AP_STATUS);
	PUSH_JSON_INT(value, AP_UPTS);
	PUSH_JSON_INT(value, AP_CB);
	PUSH_JSON_INT(value, AP_CU);
	PUSH_JSON_INT(value, AP_CR); //11
	PUSH_JSON_INT(value, AP_CP);
	PUSH_JSON_INT(value, AP_CAPACITY);
	PUSH_JSON_INT(value, AP_HERO_BUNKER);
	PUSH_JSON_INT(value, AP_STRONG);
	PUSH_JSON_INT(value, AP_WALL_HS);
	if (!addOrSetBuilding(getUid(), value, isNew)) {
		error_log("addOrSetBuilding_fail");
		return false;
	}
	return true;
}

void Building::doAi() {
}

bool Building::initHp() {
	if (m_data.find(AP_HP) == m_data.end()) {
		PropertySets::iterator iter = m_data.find(AP_MAX_HP);
		if (iter == m_data.end()) {
			error_log("cannot_find_max_hp&type=%u", getType());
			return false;
		}
		m_data.insert(make_pair(AP_HP, iter->second));
	}
	return true;
}
bool Building::initProduceTime() {
	return true;
}

bool Building::onComplelete(uint32_t type) {
	return true;
}

bool Building::saveDataGeneral(uint32_t uid, PropertySets& m_data, bool isNew) {
	Json::Value value;

	PropertySets::iterator iter = m_data.begin();
	for (; iter != m_data.end(); ++iter) {
		if (!PropertyConfig::setAttr(value, iter->first, iter->second)) {
			error_log("setAttr_fail&type=%u", iter->first);
			continue;
		}
	}

	int ret = addOrSetBuilding(uid, value, isNew);
	if (ret != 0) {
		error_log("addOrSetBuilding_fail");
		return false;
	}
	return true;
}

bool Building::addOrSetBuilding(uint32_t uid, Json::Value& value, bool isNew) {
	Json::FastWriter writer;
	DataBuilding data;
	data.uid = uid;
	if (!value.isMember("ud")) {
		error_log("no_exist_ud_in_data&uid=%u", data.uid);
		return false;
	}
	if (!Json::GetUInt(value, "ud", data.id)) {
		error_log("parse_value_fail");
		return false;
	}
	data.data = Json::FastWriter().write(value);
	if (data.data.empty()) {
		error_log("building_data_is_empty&uid=%u&id=%u", data.uid, data.id);
		return false;
	}

	CDataBuilding dbData;
	int ret = 0;
	if (isNew) {
		if ((ret = dbData.AddBuilding(data.uid, data.id, data.data)) != 0) {
			error_log("AddBuilding_fail&uid=%u&id=%u&ret=%d", data.uid, data.id, ret);
			return false;
		}
	} else {
		if ((ret = dbData.SetBuilding(data.uid, data.id, data.data)) != 0) {
			error_log("SetBuilding_fail&uid=%u&id=%u&ret=%d", data.uid, data.id, ret);
			return false;
		}
	}
	return true;
}

bool Building::delBuilding(uint32_t uid, uint32_t ud) {
	int ret = 0;
	CDataBuilding dbData;
	ret = dbData.RemoveOneBuilding(uid, ud);
	if (ret) {
		error_log("RemoveOneBuilding error uid=%u ud=%u ret=%d", uid, ud, ret);
		return false;
	}
	return true;
}

uint32_t Building::getResRateByLevel(uint32_t aLv, uint32_t bLv) {
	int temp = aLv - bLv;
	if (temp <= -3) {
		return 200;
	} else if (temp == -2) {
		return 150;
	} else if (temp == -1) {
		return 110;
	} else if (temp == 0) {
		return 100;
	} else if (temp == 1) {
		return 90;
	} else if (temp == 2) {
		return 50;
	} else if (temp == 3) {
		return 25;
	} else {
		return 5;
	}
}

bool Building::encode(IBuffer* buff) {
	static const uint32_t encodeAttrList[] = {
	AP_UD,
	AP_TYPE,
	AP_LEVEL,
	AP_X,
	AP_Y,
	AP_HP,
	AP_MAX_HP,
	AP_CB,
	AP_CU,
	AP_CR,
	AP_UPTS,
	AP_CAPACITY,
	AP_MAX_CAPACITY,
	AP_COMBAT,
	AP_STRONG,
	AP_CP,
	AP_MD};

	static CStaticBuffer<MAX_ITEM_PACKET> tmpBuff;
	tmpBuff.Clear();
	PACK_PROPS(encodeAttrList, tmpBuff);
	CBufferWriter writer(buff);
	writer.AppendUInt16(tmpBuff.GetSize());
	buff->AppendBuffer(&tmpBuff);
	return true;
}

uint32_t Building::getProduce() {
	uint32_t ts = LogicManager::GlobalTime > getCp() ? LogicManager::GlobalTime - getCp() : 0;

	uint32_t currCapacity = static_cast<double>(ts) * getProduceValue();

	debug_log("ts=%u,curr=%u,max=%u", ts, currCapacity, getMaxCapacity());

	return currCapacity > getMaxCapacity() ? getMaxCapacity() : currCapacity;
}

void Building::setProduce(uint32_t res) {
	double rate = getProduceValue();
	if (rate == 0) {
		return;
	}
	uint32_t ts = static_cast<double>(res) / rate;
	setCp(LogicManager::GlobalTime - ts);
	debug_log("ts=%u,res=%u,rate=%f,n=%u", ts, res, rate, LogicManager::GlobalTime);
	saveData();
}

bool Building::addCapacity(uint32_t res) {
	if (getCapacity() >= getMaxCapacity()) {
		return false;
	}
	if (getCapacity() + res > getMaxCapacity()) {
		setCapacity(getMaxCapacity());
	} else {
		setCapacity(getCapacity() + res);
	}
	saveData();
	return true;
}

bool Building::sendPropChange() {
	calcCombat();
	CNetPacket sPacket;
	sPacket.uid = getUid();
	CBufferWriter writer(&sPacket.body);
	writer.AppendByte(PROTOCOL_CMD_BUILDING);
	writer.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDING_PROP_CHANGE);
	writer.AppendInt32(getUid());
	writer.AppendInt32(getUD());
	encodePropsChange(&sPacket.body);
	if (!PlayerManager::getInstance()->sendToAccess(&sPacket)) {
		error_log("sendAccess_fail&uid=%u", getUid());
		return false;
	}
	return true;
}

bool Building::onRecove() {
	if (getHp() < getMaxHp()) //需要恢复
			{
		if (getCr() == 0) {
			uint32_t addHp = getRecoveInter() * getRecoveValue();
			if (getHp() + addHp >= getMaxHp()) {
				setHp(getMaxHp());
			} else {
				setHp(getHp() + addHp);
			}
			setCr(getRecoveInter());
		}
		setCr(getCr() - 1);
		return true;
	} else {
		return false;
	}
}

bool Building::needTimer() {
	return needRecove() || needProduce() || getCb() > 0 || getCu() > 0;
}

bool Building::onProduce() {
	return false;
}

bool Building::isActive() {
	return m_isActive;
}

uint32_t Building::getRecoveTime() {
	return (getMaxHp() - getHp()) / getRecoveValue();
}

bool Building::getCenterPoint(int& cx, int& cy) {
	uint32_t dx = 0;
	uint32_t dy = 0;
	if (!BuildingConfig::getInstance()->getFootprint(getType(), dx, dy)) {
		error_log("getFootprint fail type=%u", getType());
		return false;
	}
	cx = getX() + dx;
	cy = getY() + dy;

	return true;
}

uint32_t Building::getRecoveInter() {
	return 1; //1秒回一次
}

double Building::getRecoveValue() {
	return 0;
}

uint32_t Building::getProduceInter() {
	return 0;
}

double Building::getProduceValue() {
	uint32_t produce = 0;
	if (!BuildingConfig::getInstance()->getProduce(getType(), getLevel(), produce)) {
		error_log("get produce fail uid=%u type=%u", getUid(), getType());
		return 0;
	}
	double rate = static_cast<double>(produce) / 3600.0;
	debug_log("produce=%u,id=%u,lv=%u,rate=%f", produce, getType(), getLevel(), rate);
	return rate;
}

bool Building::onMapObjectHurt(MapObject *pAttacker, uint32_t hurt) {
	return false;
}

bool Building::needRecove() {
	return getHp() < getMaxHp();
}
bool Building::isDefense() {
	return false;
}

bool Building::needProduce() {
	return false;
}

bool Building::initCapacity(uint32_t ubTimeShift) {
	return false;
}

Building* Building::newBuildingByType(uint32_t type) {
	return new Building();
}
