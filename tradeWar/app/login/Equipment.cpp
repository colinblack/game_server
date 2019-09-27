/*
 * Equipment.cpp
 *
 *  Created on: 2015-9-1
 *      Author: Administrator
 */

#include "Equipment.h"
#include "DataEquipment.h"

Equipment::Equipment() {
	m_race = RACE_TYPE_EQUIPMENT;
}

Equipment::~Equipment() {

}

bool Equipment::setData(const string& jsonData) {
	Json::Value eqData;
	Json::Reader reader;
	if (!reader.parse(jsonData, eqData)) {
		error_log("equipment data json parse failed:%s", jsonData.c_str());
		return false;
	}
	EXTRACT_JSON_INT(eqData, "ud");
	EXTRACT_JSON_INT(eqData, "t");
	EXTRACT_JSON_INT(eqData, "q");			//装备品质颜色
	EXTRACT_JSON_INT(eqData, "count");
	EXTRACT_JSON_INT(eqData, "s");			//强化等级
	EXTRACT_JSON_INT(eqData, "status");		//是否穿在身上
	EXTRACT_JSON_INT(eqData, "deadline");
	EXTRACT_JSON_INT(eqData, "hud");			//穿在哪个英雄身上
	EXTRACT_JSON_INT(eqData, "bud");			//镶嵌在哪个建筑身上
	EXTRACT_JSON_INT(eqData, "xi");
	EXTRACT_JSON_INT(eqData, "seud");		//宝石所属装备
	EXTRACT_JSON_INT(eqData, "sslot");		//镶嵌槽位
	EXTRACT_JSON_INT(eqData, "elock");		//装备开锁信息
	EXTRACT_JSON_INT(eqData, "lc");
	return true;
}

bool Equipment::encode(IBuffer* buffer) {
	static const uint32_t encodeAttrList[] = { AP_TYPE, AP_QUALITY, AP_STRONG, AP_STATUS, AP_UD,
	AP_DEADLINE, AP_HUD, AP_COUNT, AP_STONE_EUD, AP_STONE_SLOT, AP_EQUIP_LOCK, AP_LOCK_COUNT };
	static CStaticBuffer<MAX_ITEM_PACKET> tmpBuff;
	tmpBuff.Clear();
	CBufferWriter writer(&tmpBuff);
	PACKET_ENCODE(Byte, sizeof(encodeAttrList) / sizeof(uint32_t));
	for (uint32_t i = 0; i < sizeof(encodeAttrList) / sizeof(uint32_t); ++i) {
		PACKET_ENCODE(Byte, encodeAttrList[i]);
		PACKET_ENCODE(UInt32, m_data[encodeAttrList[i]].pui);
	}
	// 打包洗炼属性
	PACKET_ENCODE(Byte, 0);

	CBufferWriter outWriter(buffer);
	outWriter.AppendUInt16(tmpBuff.GetSize());
	buffer->AppendBuffer(&tmpBuff);

	return true;
}

bool Equipment::saveData(bool isNew) {
	Json::Value value;
	Json::FastWriter writer;
	CDataEquipment dbData;
	DataEquipment data;
	data.uid = getUid();
	data.id = m_data[AP_UD].pi;
	PUSH_JSON_INT(value, AP_UD);
	PUSH_JSON_INT(value, AP_STATUS);
	PUSH_JSON_INT(value, AP_TYPE);
	PUSH_JSON_INT(value, AP_UPTS);
	PUSH_JSON_INT(value, AP_COUNT);
	PUSH_JSON_INT(value, AP_STRONG);
	PUSH_JSON_INT(value, AP_QUALITY);
	PUSH_JSON_INT(value, AP_HUD);
	PUSH_JSON_INT(value, AP_STONE_EUD);
	PUSH_JSON_INT(value, AP_STONE_SLOT);
	PUSH_JSON_INT(value, AP_EQ_XI);
	PUSH_JSON_INT(value, AP_EQUIP_LOCK);
	PUSH_JSON_INT(value, AP_LOCK_COUNT);

	data.data = writer.write(value);
	if (data.data.empty()) {
		error_log("equipment_data_is_empty&uid=%u&id=%u", data.uid, data.id);
		return false;
	}
	int ret = 0;
	if (isNew) {
		ret = dbData.AddEquipment(data.uid, data.id, data.data);
	} else {
		ret = dbData.SetEquipment(data.uid, data.id, data.data);
	}
	if (0 != ret) {
		error_log("save error uid=%u id=%u ret=%d isnew=%d", data.uid, data.id, ret, isNew);
		return false;
	}
	return true;
}
