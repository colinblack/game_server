/*
 * ArenaConfig.cpp
 *
 *  Created on: 2019年3月1日
 *      Author: Administrator
 */

#include "ArenaConfig.h"
#include "ConfigJson.h"

ArenaConfig::ArenaConfig() {
	m_shop_size = 0;
	m_shop_refresh_cost = 0;
}
ArenaConfig::~ArenaConfig() {
}
bool ArenaConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	if (!initShop(fileParser.getMember("shop_A"), ArenaCfgShopType_A)) {
		error_log("shop_A error");
		return false;
	}
	if (!initShop(fileParser.getMember("shop_B"), ArenaCfgShopType_B)) {
		error_log("shop_B error");
		return false;
	}
	const Json::Value *shop_size = fileParser.getMember("shop_size");
	if (shop_size == NULL || !shop_size->isIntegral()) {
		error_log("shop_size error");
		return false;
	}
	m_shop_size = shop_size->asUInt();
	const Json::Value *shop_refresh_cost = fileParser.getMember("shop_refresh_cost");
	if (shop_refresh_cost == NULL || !shop_refresh_cost->isIntegral()) {
		error_log("shop_refresh_cost error");
		return false;
	}
	m_shop_refresh_cost = shop_refresh_cost->asUInt();

	const Json::Value *ranks = fileParser.getMember("ranks");
	if (ranks == NULL || !ranks->isArray()) {
		error_log("ranks error");
		return false;
	}
	for (size_t i = 0; i < ranks->size(); ++i) {
		const Json::Value &item = ranks->get(i, Json::Value(Json::nullValue));
		if (item.isNull() && !item.isObject()) {
			continue;
		}
		string r = item.get("rank", "").asString();
		vector<string> rr;
		CBasic::StringSplitTrim(r, "-", rr);
		if (rr.size() != 2) {
			continue;
		}
		ArenaCfgRank cfg;
		cfg.from = CTrans::STOI(rr[0]);
		cfg.to = CTrans::STOI(rr[1]);
		cfg.reward.Json2Award(item["reward"]);
		m_ranks.push_back(cfg);
	}
	const Json::Value *npc = fileParser.getMember("npc");
	if (npc == NULL || !npc->isArray()) {
		error_log("npc error");
		return false;
	}
	for (size_t i = 0; i < npc->size(); ++i) {
		const Json::Value &item = npc->get(i, Json::Value(Json::nullValue));
		if (item.isNull() && !item.isObject()) {
			continue;
		}
		string r = item.get("rank", "").asString();
		vector<string> rr;
		CBasic::StringSplitTrim(r, "-", rr);
		if (rr.size() != 2) {
			continue;
		}
		ArenaCfgNpc cfg;
		cfg.from = CTrans::STOI(rr[0]);
		cfg.to = CTrans::STOI(rr[1]);
		cfg.id = item.get("id", 0).asUInt();
		cfg.power = item.get("power", 0).asUInt();
		cfg.exp = item.get("exp", 0).asUInt();
		cfg.name = item.get("name", 0).asString();
		m_npc.push_back(cfg);
	}
	const Json::Value *energy = fileParser.getMember("energy");
	if (energy == NULL || !energy->isArray()) {
		error_log("energy error");
		return false;
	}
	for (size_t i = 0; i < energy->size(); ++i) {
		m_energy.push_back(energy->get(i, 0).asUInt());
	}
	return true;
}
bool ArenaConfig::initShop(const Json::Value *v, byte type) {
	if (v == NULL || !v->isArray()) {
		error_log("v error");
		return false;
	}
	vector<byte> &types = m_shop_type[type];
	for (size_t i = 0; i < v->size(); ++i) {
		const Json::Value &item = v->get(i, Json::Value(Json::nullValue));
		if (item.isNull() && !item.isObject()) {
			continue;
		}
		ArenaCfgShop cfg;
		cfg.id = item.get("id", 0).asUInt();
		cfg.type = type;
		cfg.require = item.get("require", 0).asUInt();
		cfg.count = item.get("count", 0).asUInt();
		cfg.reward.Json2Award(item["reward"]);
		m_shops.insert(make_pair(cfg.id, cfg));
		types.push_back(cfg.id);
	}
	return true;
}
const Award* ArenaConfig::getRankReward(uint32_t r) const {
	vector<ArenaCfgRank>::const_iterator itr = m_ranks.begin();
	for (; itr != m_ranks.end(); ++itr) {
		if (r >= itr->from && r <= itr->to) {
			return &(itr->reward);
		}
	}
	return NULL;
}
const ArenaCfgShop* ArenaConfig::getShop(uint32_t id) const {
	map<uint8_t, ArenaCfgShop>::const_iterator itr = m_shops.find(id);
	if (itr == m_shops.end()) {
		return NULL;
	}
	return &(itr->second);
}
const ArenaCfgNpc* ArenaConfig::getNpc(uint32_t rank) const {
	vector<ArenaCfgNpc>::const_iterator itr = m_npc.begin();
	for (; itr != m_npc.end(); ++itr) {
		if (rank >= itr->from && rank <= itr->to) {
			return &(*itr);
		}
	}
	return NULL;
}
uint32_t ArenaConfig::getShopCost() const {
	return m_shop_refresh_cost;
}
uint32_t ArenaConfig::getBuyEnergyCost(byte cnt) {
	if (m_energy.empty()) {
		return 10;
	}
	if (cnt >= m_energy.size()) {
		return m_energy.back();
	}
	return m_energy[cnt];
}
bool ArenaConfig::refreshShop(vector<byte> &ids) {
	vector<byte> &pa = m_shop_type[ArenaCfgShopType_A];
	uint32_t need_size = m_shop_size / 2;
	if (!pa.empty()) {
		for (uint32_t i = 0; i < need_size; ++i) {
			ids.push_back(pa[Math::GetRandomInt(pa.size())]);
		}
	}
	vector<byte> &pb = m_shop_type[ArenaCfgShopType_B];
	if (!pb.empty()) {
		for (uint32_t i = 0; i < need_size; ++i) {
			ids.push_back(pb[Math::GetRandomInt(pb.size())]);
		}
	}
	return true;
}
