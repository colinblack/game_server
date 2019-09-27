/*
 * Soldier.cpp
 *
 *  Created on: 2016-4-14
 *      Author: Administrator
 */

#include "Soldier.h"
#include "CommData.h"
#include "SoldierConfig.h"
#include "PropertyManager.h"
#include "DataInc.h"
#include "StrongConfig.h"

Soldier::Soldier() : m_pm(NULL) {
	m_race = RACE_TYPE_SOLDIER;
}

Soldier::~Soldier() {
}

bool Soldier::encode(IBuffer* buffer) {
	static const uint32_t encodeAttrList[] = { AP_X, AP_Y, AP_TYPE, AP_UD, AP_LEVEL, AP_HP, AP_MAX_HP, AP_SP, AP_RP, AP_COUNT, AP_CU, AP_STAT, AP_STRONG, AP_STAR };
	static CStaticBuffer<MAX_ITEM_PACKET> tmpBuff;
	tmpBuff.Clear();
	PACK_PROPS(encodeAttrList, tmpBuff);
	CBufferWriter writer(buffer);
	writer.AppendUInt16(tmpBuff.GetSize());
	if (!buffer->AppendBuffer(&tmpBuff)) {
		return false;
	}
	return true;
}

bool Soldier::init() {
	PropertySets props;
	if (!SoldierConfig::getInstance()->getSoldierConfig(getType(), getLevel(), props)) {
		setProf(1);
		setMoveSpeed(180);
		setAttackRadius(200);
		setMaxHp(500000);
		setAttackSpeed(80);
		error_log("init_soldier_fail uid=%u ud=%u type=%u", getUid(), getUD(), getType());
		return false;
	} else {
		for (PropertySets::const_iterator iter = props.begin(); iter != props.end(); ++iter) {
			uint32_t idx = iter->first;
			const Property & prop = iter->second;
			setProperty(idx, prop);
		}
	}
	uint32_t oriType = 0;
	if (SoldierConfig::getInstance()->getSoldierOriType(getType(), oriType)) {
		setOriType(oriType);
	} else {
		error_log("getSoldierOriType fail uid=%u ud=%u type=%u", getUid(), getUD(), getType());
	}

	info_log("add soldier type:%d level:%d maxhp:%d hp:%d", getType(), getLevel(), getMaxHp(), getHp());
	setHp(getMaxHp());
	return true;
}

bool Soldier::setData(const string& jsonData) {
	Json::Value soldierData;
	Json::Reader reader;
	if (!reader.parse(jsonData, soldierData)) {
		error_log("soldier data json parse failed:%s", jsonData.c_str());
		return false;
	}
	uint32_t soldierType = 0;
	if (!Json::GetUInt(soldierData, "t", soldierType)) {
		error_log("must has field t,%s", jsonData.c_str());
		return false;
	}
	if (!SoldierConfig::getInstance()->isExist(soldierType)) {
		error_log("soldier not exist type=%u", soldierType);
		return false;
	}

	EXTRACT_JSON_INT(soldierData, "ud");
	EXTRACT_JSON_INT(soldierData, "l");
	EXTRACT_JSON_INT(soldierData, "t");
	EXTRACT_JSON_INT(soldierData, "cu");
	EXTRACT_JSON_INT(soldierData, "upts");
	EXTRACT_JSON_INT(soldierData, "count");
	EXTRACT_JSON_INT(soldierData, "s");
	EXTRACT_JSON_INT(soldierData, "star");

	return true;
}

bool Soldier::calcProps() {
	PropertySets props;
	m_pm->calcSoldierProps(getType(), getLevel(), getStrong(), props);
	PROPERTY_COMPOSITE(props, m_data);
	return true;
}

bool Soldier::saveData(bool isNew) {
	Json::Value value;

	PUSH_JSON_INT(value, AP_UD);			//ud
	PUSH_JSON_INT(value, AP_LEVEL);			//等级
	PUSH_JSON_INT(value, AP_TYPE);			//类型
	PUSH_JSON_INT(value, AP_COUNT);			//数量
	PUSH_JSON_INT(value, AP_CU);
	PUSH_JSON_INT(value, AP_UPTS);
	PUSH_JSON_INT(value, AP_STRONG);
	PUSH_JSON_INT(value, AP_STAR);

	if (!addOrSetSoldier(getUid(), value, isNew)) {
		error_log("addOrSetSoldier_fail");
		return false;
	}
	return true;
}

bool Soldier::onUpgradeOver() {
	setLevel(getLevel() + 1);
	//calcProps();
	return true;
}

bool Soldier::packetToBattle(CBufferWriter &bWriter) {
	PropertySets pro;
	if (!SoldierConfig::getInstance()->getSoldierConfig(getType(), getLevel(), pro)) {
		return false;
	}
	bWriter.AppendUInt32(pro.size() + 1);
	for (PropertySets::iterator itr = pro.begin(); itr != pro.end(); ++itr) {
		bWriter.AppendByte(itr->first);
		if (m_data.count(itr->first) > 0) {
			bWriter.AppendUInt32(m_data[itr->first].pui);
		} else {
			bWriter.AppendUInt32(0);
		}
	}
	bWriter.AppendByte(AP_STRONG);
	bWriter.AppendUInt32(getStrong());

	return true;
}

uint32_t Soldier::calcCombat(uint32_t type, uint32_t cnt) {
	const static uint32_t combat[5] = { 0u, 10u, 40u, 750u, 9000u };
	const SoldierItemConfig *cfg = SoldierConfig::getInstance()->getItemConfig(type);
	if (cfg == NULL) {
		return 0;
	}
	return cnt * (cfg->q < 5 ? combat[cfg->q] : 0);
}

bool Soldier::addOrSetSoldier(uint32_t uid, Json::Value& value, bool isNew) {
	Json::FastWriter writer;
	CDataSoldier dbData;
	DataSoldier data;
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
		if ((ret = dbData.AddSoldier(data.uid, data.id, data.data)) != 0) {
			error_log("AddSoldier_fail&uid=%u&id=%u&ret=%d", data.uid, data.id, ret);
			return false;
		}
	} else {
		if ((ret = dbData.SetSoldier(data.uid, data.id, data.data)) != 0) {
			error_log("SetSoldier_fail&uid=%u&id=%u&ret=%d", data.uid, data.id, ret);
			return false;
		}
	}

	return true;
}
