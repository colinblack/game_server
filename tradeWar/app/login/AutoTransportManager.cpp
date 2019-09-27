/*
 * AutoTransportManager.cpp
 *
 *  Created on: 2018年12月12日
 *      Author: Administrator
 */

#include "AutoTransportManager.h"
#include "PlayerManager.h"
#include "BuildingConfig.h"
#include "Building.h"
#include "BoatManager.h"
#include <fstream>

AutoTransportManager::AutoTransportManager() {
}

AutoTransportManager::~AutoTransportManager() {
}

bool AutoTransportManager::init() {
	string path = Config::GetValue(AUTO_TRANSPORT_PATH);
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoAutoTransport::AutoTransport msg;
	if (!msg.ParseFromIstream(&input)) {
		error_log("parse file error path=%s", path.c_str());
		return false;
	}
	for (int i = 0; i < msg.datas_size(); ++i) {
		DataAutoTransportUser item;
		item.Parse(msg.datas(i));
		if (!IS_VALID_PLAYER_UID(item.uid)) {
			error_log("error uid %u", item.uid);
			continue;
		}
		if (item.ets < Time::GetGlobalTime()) {
			item.ets = Time::GetGlobalTime();
		}
		m_data.insert(make_pair(item.uid, item));
		bool exists = false;
		list<uint32_t>::iterator itr = m_train.begin();
		for (; itr != m_train.end(); ++itr) {
			if (item.ets == *itr) {
				exists = true;
				break;
			}
			if (item.ets < *itr) {
				break;
			}
		}
		if (!exists) {
			m_train.insert(itr, item.ets);
		}
		vector<uint32_t> &uids = m_runing[item.ets];
		uids.push_back(item.uid);
	}
	return true;
}

bool AutoTransportManager::save() {
	string path = Config::GetValue(AUTO_TRANSPORT_PATH);
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good()) {
		error_log("open file error path=%s", path.c_str());
		return false;
	}
	ProtoAutoTransport::AutoTransport msg;
	map<uint32_t, DataAutoTransportUser>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		itr->second.Serialize(msg.add_datas());
	}
	if (!msg.SerializePartialToOstream(&output)) {
		error_log("Serialize file error path=%s", path.c_str());
		return false;
	}
	return true;
}

bool AutoTransportManager::onTimer() {
	if (m_train.empty()) {
		return false;
	}
	uint32_t ts = m_train.front();
	if (ts > Time::GetGlobalTime()) {
		return false;
	}
	debug_log("ts=%u", ts);
	uint32_t next_ts = ts + AUTO_TRANSPORT_TIME;
	if (next_ts <= Time::GetGlobalTime()) {
		next_ts = Time::GetGlobalTime() + AUTO_TRANSPORT_TIME;
	}
	m_train.pop_front();
	if (!m_runing.count(ts)) {
		return false;
	}
	vector<uint32_t> &old_uids = m_runing[ts];
	vector<uint32_t> &new_uids = m_runing[next_ts];
	for (vector<uint32_t>::iterator itr = old_uids.begin(); itr != old_uids.end(); ++itr) {
		onFinish(*itr);
		onStart(*itr, next_ts);
		new_uids.push_back(*itr);
	}
	m_train.push_back(next_ts);
	m_runing.erase(ts);
	return true;
}

bool AutoTransportManager::onStart(uint32_t uid, uint32_t ets) {
	DataAutoTransportUser &data = m_data[uid];
	data.lost = 0;
	data.ets = ets;
	uint32_t res = 0;
	BuildingConfig::getInstance()->getProduce(BUILDING_ID_RESOURCE_R1, data.blv, res);
	res *= 2;

	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player != NULL) {
		player->getBoatManager()->autoTrain(ets, res);
	} else {
		if (data.lv >= AUTO_TRANSPORT_MIN_LEVEL) {
			CDataBoatTrain dbBoatTrain;
			DataBoatTrain train;
			train.uid = uid;
			train.id = MAX_MERCHANT_NUM;
			train.start_ts = ets - AUTO_TRANSPORT_TIME;
			train.end_ts = ets;
			train.total_res = res;
			train.level = data.lv;
			dbBoatTrain.Set(train);
		}
	}
	if (res == 0 || data.lv < AUTO_TRANSPORT_MIN_LEVEL) {
		return true;
	}

	CNetPacket asrvp;
	asrvp.uid = uid;
	CBufferWriter writer(asrvp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSPORT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSPORT_START);
	writer.AppendByte(MAX_MERCHANT_NUM);
	writer.AppendByte(data.lv);
	writer.AppendUInt32(uid);
	writer.AppendUInt32(res);
	writer.AppendUInt32(data.ets);
	LogicManager::getInstance()->sendToAllServer(&asrvp);
	return true;
}

bool AutoTransportManager::onFinish(uint32_t uid) {
	DataAutoTransportUser &data = m_data[uid];
	uint32_t p = 0;
	BuildingConfig::getInstance()->getProduce(BUILDING_ID_RESOURCE_R1, data.blv, p);
	p *= 2;
	uint32_t res = data.lost > p ? 0 : p - data.lost;
	if (PlayerManager::getInstance()->IsOnline(uid)) {
		Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
		if (player == NULL) {
			return false;
		}
		Building *buil = player->getBm()->getBuildingByType(BUILDING_ID_RESOURCE_R1);
		if (buil == NULL) {
			return false;
		}
		if (buil->addCapacity(res)) {
			player->sendBuildingInfo(buil->getUD());
		}
		return true;
	} else {
		data.res += res;
	}
	debug_log("uid=%u,res=%u,tres=%u", uid, res, data.res);
	return true;
}

bool AutoTransportManager::onRob(uint32_t uid, uint32_t res) {
	DataAutoTransportUser &data = m_data[uid];
	data.lost += res;
	return true;
}

bool AutoTransportManager::updateLevel(uint32_t uid) {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (player == NULL) {
		return false;
	}
	DataAutoTransportUser &data = m_data[uid];
	data.uid = uid;
	data.lv = player->getLevel();
	data.blv = player->getBm()->getBuildingLevel(BUILDING_ID_RESOURCE_R1);
	if (data.ets == 0) {
		uint32_t ets = Time::GetGlobalTime() + AUTO_TRANSPORT_TIME;
		onStart(uid, ets);
		vector<uint32_t> &new_uids = m_runing[ets];
		new_uids.push_back(uid);
		if (m_train.empty()) {
			m_train.push_back(ets);
		} else {
			if (m_train.back() != ets) {
				m_train.push_back(ets);
			}
		}
	}
	return true;
}

bool AutoTransportManager::getInfo(uint32_t uid, uint32_t &ets, uint32_t &res) {
	DataAutoTransportUser &data = m_data[uid];
	ets = data.ets;
	uint32_t pres = 0;
	BuildingConfig::getInstance()->getProduce(BUILDING_ID_RESOURCE_R1, data.blv, pres);
	res += pres * 2;
	return true;
}

uint32_t AutoTransportManager::getRes(uint32_t uid) {
	uint32_t res = 0x7FFFFFFF;
	bool not_exists = (m_data.count(uid) == 0);
	DataAutoTransportUser &data = m_data[uid];
	if (!not_exists) {
		res = data.res;
	}
	data.res = 0;
	return res;
}
