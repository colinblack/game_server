/*
 * DailyBuyManager.cpp
 *
 *  Created on: 2018年10月20日
 *      Author: Administrator
 */

#include "DailyBuyManager.h"
#include "PlayerManager.h"
#include "ProtocolUser.h"
#include "DailyBuyConfig.h"

DailyBuyManager::DailyBuyManager() {
	m_reset_ts = 0;
	m_refresh_times = 0;
}

DailyBuyManager::~DailyBuyManager() {
}

bool DailyBuyManager::doPacket(CNetPacket *p) {
	switch (p->subCmd) {
	case PROTOCOL_SUBCMD_DAILY_BUY_QUERY:
		doQuery(p);
		break;
	case PROTOCOL_SUBCMD_DAILY_BUY_BUY:
		doBuy(p);
		break;
	case PROTOCOL_SUBCMD_DAILY_BUY_REFRESH:
		doRefresh(p);
		break;
	}
	debug_log("uid=%u,cmd=%u,sub=%u", p->uid, static_cast<uint32_t>(p->cmd), static_cast<uint32_t>(p->subCmd));
	return true;
}

bool DailyBuyManager::load(uint32_t uid) {
	CDataState dbc;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_DAILY_BUY;
	int ret = dbc.GetState(data.uid, data.id, data.data);
	if (R_SUCCESS == ret) {
		Json::Value v;
		Json::Reader r;
		if (r.parse(data.data, v) && !v.isNull() && v.isObject()) {
			m_reset_ts = v.get("ts", 0).asUInt();
			m_refresh_times = v.get("rt", 0).asUInt();
			if (v.isMember("list") && v["list"].isArray()) {
				for (uint32_t i = 0; i < v["list"].size(); ++i) {
					DailyBuyItem item;
					if (item.fromJson(v["list"][i])) {
						m_data.insert(make_pair(item.id, item));
					}
				}
			}
			if (v.isMember("ids") && v["ids"].isArray()) {
				for (uint32_t i = 0; i < v["ids"].size(); ++i) {
					m_index.push_back(v["ids"][i].asUInt());
				}
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		ret = dbc.AddState(data.uid, data.id, "");
	} else {
		error_log("get state error uid=%u id=%u", data.uid, data.id);
		return false;
	}

	bool sync = reset();

	uint32_t len = DailyBuyConfig::getInstance()->getPoolLen();
	if (m_data.size() != len) {
		for (uint32_t i = 1; i <= len; ++i) {
			if (m_data.count(i)) {
				continue;
			}
			DailyBuyItem item;
			item.id = i;
			m_data.insert(make_pair(item.id, item));
			sync = true;
		}
	}
	if (sync) {
		save();
	}
	return 0;
}

bool DailyBuyManager::save() {
	Json::Value v = Json::Value(Json::objectValue);
	v["ts"] = m_reset_ts;
	v["rt"] = m_refresh_times;
	v["list"] = Json::Value(Json::arrayValue);
	map<byte, DailyBuyItem>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		v["list"].append(itr->second.toJson());
	}
	v["ids"] = Json::Value(Json::arrayValue);
	for (size_t i = 0; i < m_index.size(); ++i) {
		v["ids"].append(static_cast<uint32_t>(m_index[i]));
	}

	CDataState dbc;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_DAILY_BUY;
	data.data = Json::ToString(v);
	int ret = dbc.SetState(data);
	if (0 != ret) {
		error_log("set state error uid=%u id=%u", data.uid, data.id);
		return false;
	}
	return true;
}

bool DailyBuyManager::push() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_DAILY_BUY);
	writer.AppendByte(PROTOCOL_SUBCMD_DAILY_BUY_QUERY);
	writer.AppendUInt32(m_refresh_times);
	writer.AppendUInt32(m_index.size());
	vector<byte>::iterator itr = m_index.begin();
	for (; itr != m_index.end(); ++itr) {
		const DailyBuyItem &item = m_data[*itr];
		writer.AppendByte(item.id);
		writer.AppendByte(item.buy);
		writer.AppendByte(item.cost_type);
		writer.AppendUInt32(item.good_id);
		writer.AppendUInt32(item.good_count);
		writer.AppendUInt32(item.good_price);
		writer.AppendUInt32(item.good_discount);
		writer.AppendUInt32(item.refresh_ts);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool DailyBuyManager::reset() {
	if (LogicManager::GlobalTime - m_reset_ts < 14400) {
		return false;
	}
	m_reset_ts = LogicManager::GlobalTime;
	m_refresh_times = 0;
	return true;
}

bool DailyBuyManager::doQuery(CNetPacket *p) {
	reset();
	refresh(false);
	push();

	return true;
}

bool DailyBuyManager::doBuy(CNetPacket *p) {
	CUserDailyBuyProtocol proto;
	Award aresult;
	if (!proto.Decode(p->GetBody())) {
		error_log("decode error uid=%u", p->uid);
		onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 1, &aresult);
		return false;
	}
	map<byte, DailyBuyItem>::iterator itr = m_data.find(proto.id);
	if (itr == m_data.end()) {
		error_log("id error uid=%u id=%u", p->uid, static_cast<uint32_t>(proto.id));
		onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 1, &aresult);
		return false;
	}
	DailyBuyItem &item = itr->second;
	if (item.buy == 1) {
		error_log("buy flag error uid=%u id=%u", p->uid, static_cast<uint32_t>(proto.id));
		onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 1, &aresult);
		return false;
	}
	if (item.good_id == 0) {
		error_log("good id error uid=%u id=%u", p->uid, static_cast<uint32_t>(proto.id));
		onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 1, &aresult);
		return false;
	}
	if (item.good_count == 0) {
		error_log("good count error uid=%u id=%u", p->uid, static_cast<uint32_t>(proto.id));
		onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 1, &aresult);
		return false;
	}
	string code = "daily_buy_" + CTrans::ITOS(proto.id);

	if (item.cost_type == 0) {
		ResourceCost cost;
		cost.r1 = static_cast<float>(item.good_price) * (static_cast<float>(item.good_discount) / 100.0f);
		if (!m_player->getRm()->useResources(cost, code)) {
			error_log("cost uid=%u id=%u", p->uid, static_cast<uint32_t>(proto.id));
			onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 1, &aresult);
			return false;
		}
	} else {
		MoneyCost cost;
		cost.cash = static_cast<float>(item.good_price) * (static_cast<float>(item.good_discount) / 100.0f);
		if (!m_player->getRm()->useMoney(cost, code)) {
			error_log("cost error uid=%u id=%u", p->uid, static_cast<uint32_t>(proto.id));
			onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 1, &aresult);
			return false;
		}
	}

	item.buy = 1;
	save();

	Award reward;
	AwardInfo reward_item;
	reward_item.id = item.good_id;
	reward_item.type = item.good_type;
	reward_item.count = item.good_count;
	reward.add(reward_item);

	m_player->doReward(&reward, code, false, &aresult);

	push();

	onResp(PROTOCOL_SUBCMD_DAILY_BUY_BUY, 0, &aresult);

	return true;
}

bool DailyBuyManager::doRefresh(CNetPacket *p) {
	reset();
	MoneyCost cost;
	cost.cash = pow(2, m_refresh_times) * 20;
	if (!m_player->getRm()->useMoney(cost, "refresh_daily_buy_" + CTrans::ITOS(m_refresh_times + 1))) {
		error_log("cost error uid=%u", p->uid);
		onResp(PROTOCOL_SUBCMD_DAILY_BUY_REFRESH, 1);
		return false;
	}

	if (!refresh(true)) {
		error_log("refresh error uid=%u", p->uid);
		onResp(PROTOCOL_SUBCMD_DAILY_BUY_REFRESH, 1);
		return false;
	}
	m_refresh_times += 1;

	save();

	push();

	onResp(PROTOCOL_SUBCMD_DAILY_BUY_REFRESH, 0);

	return true;
}

bool DailyBuyManager::onResp(byte sub, byte ret, const Award *award) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_DAILY_BUY);
	writer.AppendByte(sub);
	writer.AppendByte(ret);
	if (award) {
		award->packetData(writer);
	}

	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;
}

bool DailyBuyManager::refresh(bool all) {
	bool sync = false;
	map<byte, DailyBuyItem>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		DailyBuyItem &item = itr->second;
		if (all || item.refresh_ts < LogicManager::GlobalTime) {
			AwardInfo good;
			uint32_t price = 0;
			uint32_t dis = 0;
			uint32_t cost_type = 0;
			uint32_t ts = 0;
			if (!DailyBuyConfig::getInstance()->refresh(m_player->getLevel(), item.id, good, price, dis, cost_type, ts)) {
				return false;
			}
			if (all || item.refresh_ts == 0) {
				item.refresh_ts = LogicManager::GlobalTime + ts;
			} else {
				uint32_t in = ts != 0 ? (LogicManager::GlobalTime - item.refresh_ts) % ts : 0;
				item.refresh_ts = LogicManager::GlobalTime + ts - in;
			}
			item.buy = 0;
			item.cost_type = cost_type;
			item.good_id = good.id;
			item.good_count = good.count;
			item.good_type = good.type;
			item.good_discount = dis;
			item.good_price = price;
			sync = true;
		}
	}
	if (sync) {
		m_index.clear();
		for (itr = m_data.begin(); itr != m_data.end(); ++itr) {
			DailyBuyItem &item = itr->second;
			if (item.id > 1) {
				m_index.push_back(item.id);
			}
		}
		random_shuffle(m_index.begin(), m_index.end());
		m_index.insert(m_index.begin(), 1);
		save();
	}
	return true;
}
