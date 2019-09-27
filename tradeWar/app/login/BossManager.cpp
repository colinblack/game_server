/*
 * BossManager.cpp
 *
 *  Created on: 2019年2月25日
 *      Author: Administrator
 */

#include "BossManager.h"
#include "PlayerManager.h"
#include "BossConfig.h"
#include "BossRankManager.h"

BossManager::BossManager() {
	m_isNew = false;
}

BossManager::~BossManager() {
}

bool BossManager::doPacket(CNetPacket *p) {
	switch (p->subCmd) {
	case PROTOCOL_SUBCMD_BOSS_INFO:
		push();
		break;
	case PROTOCOL_SUBCMD_BOSS_RESULT:
		doResult(p);
		break;
	case PROTOCOL_SUBCMD_BOSS_SHOP:
		doShop(p);
		break;
	}
	return true;
}

bool BossManager::load(uint32_t uid) {
	int ret = 0;
	CDataBoss dbc;
	ret = dbc.Get(uid, m_data);
	if (R_SUCCESS != ret && R_ERR_NO_DATA != ret) {
		error_log("get boss error uid=%u ret=%d", uid, ret);
		return false;
	}
	if (R_ERR_NO_DATA == ret) {
		m_isNew = true;
		m_data.uid = uid;
	}
	parseSoldier();
	parseShop();
	if (reset()) {
		save();
	}
	return true;
}

bool BossManager::onLogin() {
	if(reset()) {
		save();
	}
	return true;
}

bool BossManager::save() {
	int ret = 0;
	Json::Value shop = Json::Value(Json::arrayValue);
	vector<uint32_t>::iterator sitr = m_shop.begin();
	for (; sitr != m_shop.end(); ++sitr) {
		shop.append(*sitr);
	}
	Json::Value soldier = Json::Value(Json::objectValue);
	map<byte, map<uint32_t, uint32_t> >::iterator itr = m_soldier.begin();
	for (; itr != m_soldier.end(); ++itr) {
		string k = CTrans::ITOS(itr->first);
		soldier[k] = Json::Value(Json::objectValue);
		map<uint32_t, uint32_t>::iterator citr = itr->second.begin();
		for (; citr != itr->second.end(); ++citr) {
			string kk = CTrans::ITOS(citr->first);
			soldier[k][kk] = citr->second;
		}
	}
	m_data.soldier = Json::ToString(soldier);
	m_data.shop = Json::ToString(shop);

	CDataBoss dbc;
	if (m_isNew) {
		m_isNew = false;
		ret = dbc.Add(m_data);
	} else {
		ret = dbc.Set(m_data);
	}
	if (0 != ret) {
		error_log("save boss error ret=%d uid=%u", ret, m_player->getUid());
		return false;
	}
	return true;
}

bool BossManager::push() {
	reset();
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_BOSS);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_BOSS_INFO);
	PACKET_ENCODE(Byte, m_data.curr_id);
	PACKET_ENCODE(UInt32, m_data.curr_hurt);
	PACKET_ENCODE(UInt32, m_data.total_hurt);
	if (!m_soldier.count(m_data.curr_id)) {
		PACKET_ENCODE(Byte, 0);
	} else {
		PACKET_ENCODE(Byte, m_soldier[m_data.curr_id].size());
		map<uint32_t,uint32_t>::iterator itr = m_soldier[m_data.curr_id].begin();
		for (; itr != m_soldier[m_data.curr_id].end(); ++itr) {
			PACKET_ENCODE(UInt32, itr->first);
			PACKET_ENCODE(UInt32, itr->second);
		}
	}
	if (!m_soldier.count(0)) {
		PACKET_ENCODE(Byte, 0);
	} else {
		PACKET_ENCODE(Byte, m_soldier[0].size());
		map<uint32_t,uint32_t>::iterator itr = m_soldier[0].begin();
		for (; itr != m_soldier[0].end(); ++itr) {
			PACKET_ENCODE(UInt32, itr->first);
			PACKET_ENCODE(UInt32, itr->second);
		}
	}
	uint32_t shop_size = BossConfig::getInstance()->getShopSize();
	PACKET_ENCODE(Byte, shop_size);
	for (size_t i = 0; i < shop_size; ++i) {
		if (i < m_shop.size()) {
			PACKET_ENCODE(UInt32, m_shop[i]);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	BossRankManager::getInstance()->encode(sp.GetBody());
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool BossManager::reset() {
	if (CTime::GetDayInterval(m_data.ts, Time::GetGlobalTime()) == 0) {
		return false;
	}
	if (m_soldier.count(0)) {
		m_soldier.erase(0);
	}
	m_data.ts = Time::GetGlobalTime();
	m_data.curr_hurt = 0;
	m_data.curr_id = 1;
	m_data.total_hurt = 0;
	m_shop.clear();
	return true;
}

bool BossManager::parseSoldier() {
	Json::Value v;
	Json::Reader r;
	if (!r.parse(m_data.soldier, v)) {
		return false;
	}
	Json::Value::Members members(v.getMemberNames());
	Json::Value::Members::iterator itr = members.begin();
	for (; itr != members.end(); ++itr) {
		string k = *itr;
		if (!v[k].isObject()) {
			continue;
		}
		byte ik = CTrans::STOI(k);
		map<uint32_t, uint32_t> &ss = m_soldier[ik];
		Json::Value::Members members1(v[k].getMemberNames());
		Json::Value::Members::iterator itr1 = members1.begin();
		for (; itr1 != members1.end(); ++itr1) {
			string kk = *itr1;
			uint32_t id = CTrans::STOI(kk);
			uint32_t cnt = 0;
			Json::GetUInt(v[k], kk.c_str(), cnt);
			ss.insert(make_pair(id, cnt));
		}
	}
	return true;
}

bool BossManager::parseShop() {
	Json::Value v;
	Json::Reader r;
	if (!r.parse(m_data.shop, v)) {
		return false;
	}
	if (!v.isArray()) {
		return false;
	}
	for (size_t i = 0; i < v.size(); ++i) {
		m_shop.push_back(v[i].asUInt());
	}
	return true;
}

bool BossManager::doResult(CNetPacket *p) {
	BossResultProto proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		return onResultResp(R_ERROR);
	}
	reset();
	if (m_data.curr_id != proto.id) {
		error_log("curr_id error uid=%u curr_id=%u id=%u", p->uid, m_data.curr_id, static_cast<uint32_t>(proto.id));
		return onResultResp(R_ERROR);
	}
	const BossConfigItem *cfg = BossConfig::getInstance()->getItem(m_data.curr_id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", p->uid, static_cast<uint32_t>(proto.id));
		return onResultResp(R_ERROR);
	}
	if (m_data.curr_hurt == 0 && proto.hurt >= cfg->hp) {
		map<uint32_t, uint32_t> &ss = m_soldier[m_data.curr_id];
		ss.clear();
		vector<pair<uint32_t, uint32_t> >::iterator itr = proto.soldier.begin();
		for (; itr != proto.soldier.end(); ++itr) {
			ss.insert(*itr);
		}
	}

	//记录所有消耗掉的士兵
	map<uint32_t, uint32_t> &ss = m_soldier[0];
	vector<pair<uint32_t, uint32_t> >::iterator itr = proto.soldier.begin();
	for (; itr != proto.soldier.end(); ++itr) {
		if (ss.count(itr->first)) {
			ss[itr->first] += itr->second;
		} else {
			ss[itr->first] = itr->second;
		}
	}
	bool dead = false;
	m_data.curr_hurt += proto.hurt;
	m_data.total_hurt += proto.hurt;
	if (m_data.curr_hurt >= cfg->hp) {
		m_data.curr_id += 1;
		m_data.curr_hurt = 0;
		m_player->doReward(&(cfg->reward), "boss_" + CTrans::ITOS(proto.id));
		dead = true;
	}

	save();
	onResultResp(R_SUCCESS);
	BossRankManager::getInstance()->addRank(m_player->getUid(), m_data.total_hurt, m_player->getName());
	m_player->getActManager()->addBoss(proto.hurt);
	BUSI_MISC("play|boss|%u|%u|%u|%u", m_player->getUid(), static_cast<uint32_t>(proto.id), dead ? 1u : 0u, Time::GetGlobalTime());
	return true;
}

bool BossManager::doShop(CNetPacket *p) {
	BossShopProto proto;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		return onShopResp(R_ERROR);
	}
	reset();
	uint32_t shop_id = proto.id;
	const BossConfigShop *cfg = BossConfig::getInstance()->getShop(shop_id);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", p->uid, shop_id);
		return onShopResp(R_ERROR);
	}
	uint32_t shop_size = BossConfig::getInstance()->getShopSize();
	if (m_shop.size() < shop_size) {
		m_shop.resize(shop_size, 0);
	}
	uint32_t &curr_count = m_shop[shop_id - 1];
	if (curr_count >= cfg->count) {
		error_log("count error uid=%u id=%u count=%u", p->uid, shop_id, curr_count);
		return onShopResp(R_ERROR);
	}
	string code = "boss_shop_" + CTrans::ITOS(shop_id);
	if (!m_player->getEm()->useBagItemByType(604u, cfg->require, code)) {
		error_log("cost error uid=%u id=%u count=%u", p->uid, shop_id, cfg->require);
		return onShopResp(R_ERROR);
	}
	curr_count += 1;
	m_player->doReward(&(cfg->reward), code);
	save();
	onShopResp(R_SUCCESS);
	BUSI_MISC("play|bossshop|%u|%u|%u", m_player->getUid(), shop_id, Time::GetGlobalTime());
	return true;
}

bool BossManager::onResultResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_BOSS);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_BOSS_RESULT);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool BossManager::onShopResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_BOSS);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_BOSS_SHOP);
	PACKET_ENCODE(Byte, ret);
	uint32_t shop_size = BossConfig::getInstance()->getShopSize();
	PACKET_ENCODE(Byte, shop_size);
	for (size_t i = 0; i < shop_size; ++i) {
		if (i < m_shop.size()) {
			PACKET_ENCODE(UInt32, m_shop[i]);
		} else {
			PACKET_ENCODE(UInt32, 0);
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
