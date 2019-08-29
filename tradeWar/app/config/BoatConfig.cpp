#include "BoatConfig.h"
#include "ConfigJson.h"
#include "CommonConfig.h"
#include "ExpConfig.h"

CBoatConfig::CBoatConfig() {
	m_config.clear();
}

CBoatConfig::~CBoatConfig() {
	m_config.clear();
}

bool CBoatConfig::init(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *reward = fileParser.getMember("boats.reward");
	if (reward == NULL || !reward->isArray()) {
		return false;
	}
	for (size_t i = 0; i < reward->size(); ++i) {
		const Json::Value &item = reward->get(i, Json::Value(Json::nullValue));
		BoatConfig config;
		string strVal;
		if (Json::GetString(item, "type", strVal)) {
			config.type = String::s2i(strVal, 0);
		}
		if (Json::GetString(item, "transportTime", strVal)) {
			config.ts = std::min(0xFFFF, String::s2i(strVal, 0) * 60);
		}
		config.count = std::min(0xFFFFu, item.get("maxTime", 0).asUInt());
		config.box = item.get("box", 0).asUInt();

		parseArray(item["reward"], config.cost);
		parseArray(item["reward2"], config.reward);

		m_config.insert(make_pair(config.type, config));
	}

	const Json::Value *npc = fileParser.getMember("boats.npc");
	if (npc == NULL || !npc->isArray()) {
		error_log("npc error");
		return false;
	}
	for (size_t i = 0; i < npc->size(); ++i) {
		const Json::Value &item = npc->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		BoatNpcConfig cfg;
		cfg.exp = item.get("exp", 0).asUInt();
		cfg.lv = ExpConfig::getInstance()->getNextUserLevel(cfg.exp);
		const Json::Value &npcItem = item["npc"];
		if (npcItem.isNull() && !npcItem.isArray()) {
			continue;
		}
		for (size_t j = 0; j < npcItem.size(); ++j) {
			BoatNpcItem n;
			Json::GetUInt(npcItem[j], "id", n.id);
			Json::GetUInt(npcItem[j], "res", n.res);
			Json::GetUInt(npcItem[j], "power", n.power);
			cfg.npc.push_back(n);
		}
		m_npc.insert(make_pair(cfg.lv, cfg));
	}

	const Json::Value *npc_name = fileParser.getMember("boats.npc_name");
	if (npc == NULL || !npc->isArray()) {
		error_log("npc_name error");
		return false;
	}
	for (size_t i = 0; i < npc_name->size(); ++i) {
		const Json::Value &item = npc_name->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		m_npc_name.push_back(item.asString());
	}

	return true;
}
uint32_t CBoatConfig::getReward(uint32_t type, uint32_t lv) {
	lv = lv > 0 ? lv - 1 : lv;
	return m_config.count(type) ? (m_config[type].reward.size() > lv ? m_config[type].reward[lv] : 0) : 0;
}
uint32_t CBoatConfig::getCost(uint32_t type, uint32_t lv) {
	lv = lv > 0 ? lv - 1 : lv;
	return m_config.count(type) ? (m_config[type].cost.size() > lv ? m_config[type].cost[lv] : 0) : 0;
}
uint32_t CBoatConfig::getTransportTs(uint32_t type) {
	return m_config.count(type) ? m_config[type].ts : 0;
}
uint32_t CBoatConfig::getCount(uint32_t type) {
	return m_config.count(type) ? m_config[type].count : 0;
}
uint32_t CBoatConfig::getBox(uint32_t type) {
	return m_config.count(type) ? m_config[type].box : 0;
}
const BoatNpcConfig* CBoatConfig::getBoatNpc(uint32_t lv) {
	map<uint32_t, BoatNpcConfig>::iterator itr = m_npc.begin();
	for (; itr != m_npc.end(); ++itr) {
		if (lv == itr->first) {
			return &(itr->second);
		}
	}
	return NULL;
}
string CBoatConfig::getNpcName() {
	if (m_npc_name.empty()) {
		return "";
	}
	return m_npc_name[Math::GetRandomInt(m_npc_name.size())];
}
bool CBoatConfig::getAllNpc(map<uint32_t, vector<uint64_t> > &data) {
	map<uint32_t, BoatNpcConfig>::iterator itr = m_npc.begin();
	for (; itr != m_npc.end(); ++itr) {
		vector<uint64_t> &npcs = data[itr->first];
		vector<BoatNpcItem>::iterator it = itr->second.npc.begin();
		for (; it != itr->second.npc.end(); ++it) {
			npcs.push_back(it->id);
		}
	}
	return true;
}
