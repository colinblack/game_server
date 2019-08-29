/*
 * GiftBagConfig.cpp
 *
 *  Created on: 2016年5月30日
 *      Author: asdf
 */

#include "GiftBagConfig.h"
#include "ConfigJson.h"

GiftBagConfig::GiftBagConfig() {
}

GiftBagConfig::~GiftBagConfig() {
}

bool GiftBagConfig::init(const string & path) {
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret != 0) {
		error_log("read file error,ret=%d,path=%s", ret, path.c_str());
		return false;
	}
	Json::Value content;
	Json::Reader reader;
	if (!reader.parse(buffer, content)) {
		error_log("parse error, msg=%s", reader.getFormatedErrorMessages().c_str());
		return false;
	}
	Json::Value &package = content["giftbags"]["equippackage"];
	if (package.isNull() || !package.isArray()) {
		error_log("equippackage error");
		return false;
	}
	for (size_t i = 0; i < package.size(); ++i) {
		Json::Value &item = package[i];
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		string idStr;
		if (!Json::GetString(item, "id", idStr)) {
			idStr.clear();
		}
		GiftBagItemConfig gift;
		gift.id = String::s2i(idStr, 0);
		gift.award.Json2Award(item["data"]["reward"]);
		m_giftBag.insert(make_pair(gift.id, gift));
	}

	if (!initDailyCharge(content["giftbags"]["shouchong"])) {
		error_log("initDailyCharge error");
		return false;
	}
	if (!initTotalCharge(content["giftbags"]["total_charge"])) {
		error_log("initTotalCharge error");
		return false;
	}
	if (!initLuckyBox(content["giftbags"]["luckybox"])) {
		error_log("initLuckyBox error");
		return false;
	}

	if (!initNewServerRank(content["giftbags"]["consumeRankReward"], NEW_SERVER_RANK_TYPE_CONSUME, 0)) {
		error_log("init consumeRankReward error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["cupRankReward"], NEW_SERVER_RANK_TYPE_EXP, 0)) {
		error_log("init cupRankReward error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["militaryRankReward"], NEW_SERVER_RANK_TYPE_POWER, 0)) {
		error_log("init militaryRankReward error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["transportRankReward"], NEW_SERVER_RANK_TYPE_TRANSPORT, 0)) {
		error_log("init transportRankReward error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["cardRankReward"], NEW_SERVER_RANK_TYPE_SOLDIER, 0)) {
		error_log("init cardRankReward error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["goldRankReward"], NEW_SERVER_RANK_TYPE_COINS, 0)) {
		error_log("init goldRankReward error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["goldRankReward2"], NEW_SERVER_RANK_TYPE_COINS, 1)) {
		error_log("init goldRankReward2 error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["stoneRankReward"], NEW_SERVER_RANK_TYPE_GEM, 0)) {
		error_log("init stoneRankReward error");
		return false;
	}
	if (!initNewServerRank(content["giftbags"]["warRankReward"], NEW_SERVER_RANK_TYPE_WORLD_BATTLE, 0)) {
		error_log("init warRankReward error");
		return false;
	}
	if (!initActRank(content["giftbags"]["consumeRankReward_new"], ACT_RANK_TYPE_CONSUME)) {
		error_log("init consumeRankReward error");
		return false;
	}
	if (!initActRank(content["giftbags"]["cupRankReward_new"], ACT_RANK_TYPE_EXP)) {
		error_log("init cupRankReward error");
		return false;
	}
	if (!initActRank(content["giftbags"]["militaryRankReward_new"], ACT_RANK_TYPE_POWER)) {
		error_log("init militaryRankReward error");
		return false;
	}
	if (!initActRank(content["giftbags"]["transportRankReward_new"], ACT_RANK_TYPE_BOAT)) {
		error_log("init transportRankReward error");
		return false;
	}
	if (!initActRank(content["giftbags"]["cardRankReward_new"], ACT_RANK_TYPE_SOLDIER)) {
		error_log("init cardRankReward error");
		return false;
	}
	if (!initActRank(content["giftbags"]["warRankReward_new"], ACT_RANK_TYPE_ARENA)) {
		error_log("init warRankReward error");
		return false;
	}
	if (!initDailyBuyBag(content["giftbags"]["dailyBuyBag"], m_dailyBuyBag)) {
		error_log("init dailyBuyBag error");
		return false;
	}
	if (!initDailyBuyBag(content["giftbags"]["dailyBuyBag_new"], m_dailyBuyBagNew)) {
		error_log("init dailyBuyBag_new error");
		return false;
	}
	if (!initDailyChargeEquip(content["giftbags"]["dailyChargeEquip"], m_dailyChargeEquip)) {
		error_log("init dailyChargeEquip error");
		return false;
	}
	if (!initDailyChargeEquip(content["giftbags"]["dailyChargeEquip_new"], m_dailyChargeEquipNew)) {
		error_log("init dailyChargeEquip_new error");
		return false;
	}
	if (!initDailyChargeCash(content["giftbags"]["dailyChargeDiamond"], m_dailyChargeCash)) {
		error_log("init dailyChargeDiamond error");
		return false;
	}
	if (!initDailyChargeCash(content["giftbags"]["dailyChargeDiamond_new"], m_dailyChargeCashNew)) {
		error_log("init dailyChargeDiamond_new error");
		return false;
	}
	if (!initContinueCharge(content["giftbags"]["continueCharge"], m_continueCharge)) {
		error_log("init continueCharge error");
		return false;
	}
	if (!initContinueCharge(content["giftbags"]["continueCharge_new"], m_continueChargeNew)) {
		error_log("init continueCharge_new error");
		return false;
	}
	if (!initWanbaVipSpecialBag(content["giftbags"]["wanbaVipSpecialBag"])) {
		error_log("init wanbaVipSpecialBag error");
		return false;
	}
	if (!initWanbaVipDailyBag(content["giftbags"]["wanbaVipDailyBag"])) {
		error_log("init wanbaVipDailyBag error");
		return false;
	}
	if (!initWanbaVipDailyBag(content["giftbags"]["wanbaWeekBag"])) {
		error_log("init wanbaVipDailyBag error");
		return false;
	}
	m_share.Json2Award(content["giftbags"]["share"]["reward"]);
	m_addShortcut.Json2Award(content["giftbags"]["shoucang"]["reward"]);
	return true;
}

bool GiftBagConfig::initFirstCharge(const string & path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *detail = fileParser.getMember("firstCharge.detail");
	if (detail == NULL || !detail->isArray()) {
		error_log("detail error!");
		return false;
	}
	for (size_t i = 0; i < detail->size(); ++i) {
		const Json::Value &item = detail->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		uint32_t id = item.get("id", 0).asUInt();
		Award reward;
		reward.Json2Award(item["data"]["reward"]);
		m_firstCharge.insert(make_pair(id, reward));
	}
	return true;
}

bool GiftBagConfig::initDailyCharge(const Json::Value &value) {
	if (value.isNull() || !value.isObject()) {
		error_log("shouchong error");
		return false;
	}
	m_dailyCharge.require = 1;
	m_dailyCharge.award.Json2Award(value["reward"]);
	return true;
}

bool GiftBagConfig::initTotalCharge(const Json::Value &value) {
	if (value.isNull() || !value.isArray()) {
		error_log("total_charge error");
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		ChargeRewardConfig item;
		uint32_t id = value[i].get("id", 0).asUInt();
		item.require = value[i].get("require", 0).asUInt();
		item.award.Json2Award(value[i]["reward"]);
		m_totalCharge.insert(make_pair(id, item));
	}
	return true;
}

bool GiftBagConfig::initNewServerRank(const Json::Value &value, uint32_t type, uint32_t day) {
	if (value.isNull() || !value.isArray()) {
		error_log("total_charge error");
		return false;
	}
	map<uint32_t, vector<NewServerRankConfig> > &all_day = m_new_srv_rank[type];
	vector<NewServerRankConfig> &data = all_day[day];
	for (size_t i = 0; i < value.size(); ++i) {
		NewServerRankConfig item;
		string rank;
		Json::GetString(value[i], "rank", rank);
		if (rank.empty()) {
			Json::GetUInt(value[i], "require", item.require);
		} else {
			size_t pos = rank.find("-");
			if (pos == string::npos) {
				error_log("rank error");
				return false;
			}
			item.from = CTrans::STOI(rank.substr(0, pos));
			item.to = CTrans::STOI(rank.substr(pos + 1));
		}
		item.reward.Json2Award(value[i]["reward"]);
		data.push_back(item);
	}
	return true;
}

bool GiftBagConfig::initActRank(const Json::Value &value, uint32_t type) {
	if (value.isNull() || !value.isArray()) {
		error_log("total_charge error");
		return false;
	}
	vector<NewServerRankConfig> &data = m_act_rank[type];
	for (size_t i = 0; i < value.size(); ++i) {
		NewServerRankConfig item;
		string rank;
		Json::GetString(value[i], "rank", rank);
		if (rank.empty()) {
			error_log("rank error");
			return false;
		}
		size_t pos = rank.find("-");
		if (pos == string::npos) {
			error_log("rank error");
			return false;
		}
		item.from = CTrans::STOI(rank.substr(0, pos));
		item.to = CTrans::STOI(rank.substr(pos + 1));
		Json::GetUInt(value[i], "require", item.require);
		item.reward.Json2Award(value[i]["reward"]);
		data.push_back(item);
	}
	return true;
}

bool GiftBagConfig::initDailyBuyBag(const Json::Value &value, map<uint32_t, ChargeRewardConfig> &data) {
	if (value.isNull() || !value.isArray()) {
		error_log("daily buy bag error");
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		ChargeRewardConfig item;
		uint32_t day = value[i].get("day", 0).asUInt();
		item.require = value[i].get("require", 0).asUInt();
		item.award.Json2Award(value[i]["reward"]);
		data.insert(make_pair(day, item));
	}
	return true;
}

bool GiftBagConfig::initDailyChargeEquip(const Json::Value &value, map<uint32_t, map<uint32_t, ChargeRewardConfig> > &data) {
	if (value.isNull() || !value.isArray()) {
		error_log("daily charge equip error");
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		uint32_t day = value[i].get("day", 0).asUInt();
		map<uint32_t, ChargeRewardConfig> &cfg = data[day];
		for (size_t j = 0; j < value[i]["data"].size(); ++j) {
			ChargeRewardConfig item;
			uint32_t id = value[i]["data"][j].get("id", 0).asUInt();
			item.require = value[i]["data"][j].get("require", 0).asUInt();
			item.award.Json2Award(value[i]["data"][j]["reward"]);
			cfg.insert(make_pair(id, item));
		}
	}
	return true;
}

bool GiftBagConfig::initDailyChargeCash(const Json::Value &value, map<uint32_t, map<uint32_t, ChargeRewardConfig> > &data) {
	if (value.isNull() || !value.isArray()) {
		error_log("daily charge cash error");
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		uint32_t day = value[i].get("day", 0).asUInt();
		map<uint32_t, ChargeRewardConfig> &cfg = data[day];
		for (size_t j = 0; j < value[i]["data"].size(); ++j) {
			ChargeRewardConfig item;
			uint32_t id = value[i]["data"][j].get("id", 0).asUInt();
			item.require = value[i]["data"][j].get("require", 0).asUInt();
			item.award.Json2Award(value[i]["data"][j]["reward"]);
			cfg.insert(make_pair(id, item));
		}
	}
	return true;
}

bool GiftBagConfig::initContinueCharge(const Json::Value &value, map<uint32_t, ChargeRewardConfig> &data) {
	if (value.isNull() || !value.isArray()) {
		error_log("continue charge error");
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		ChargeRewardConfig item;
		uint32_t day = value[i].get("id", 0).asUInt();
		item.require = value[i].get("require", 0).asUInt();
		item.award.Json2Award(value[i]["reward"]);
		data.insert(make_pair(day, item));
	}
	return true;
}

bool GiftBagConfig::initWanbaVipSpecialBag(const Json::Value &value) {
	if (value.isNull() || !value.isArray()) {
		error_log("error");
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		ChargeRewardConfig item;
		uint32_t id = value[i].get("id", 0).asUInt();
		item.require = value[i].get("require", 0).asUInt();
		item.award.Json2Award(value[i]["reward"]);
		m_wanbaVipSpecialBag.insert(make_pair(id, item));
	}
	return true;
}

bool GiftBagConfig::initWanbaVipDailyBag(const Json::Value &value) {
	if (value.isNull() || !value.isArray()) {
		error_log("error");
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		ChargeRewardConfig item;
		uint32_t id = value[i].get("id", 0).asUInt();
		item.award.Json2Award(value[i]["reward"]);
		m_wanbaVipDailyBag.insert(make_pair(id, item));
	}
	return true;
}

bool GiftBagConfig::initLuckyLottery(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *value = fileParser.getMember("diamondDraw.detail");
	if (value == NULL || !value->isArray()) {
		error_log("lucky lottery error");
		return false;
	}
	uint32_t rate = 0;
	for (size_t i = 0; i < value->size(); ++i) {
		const Json::Value &item = value->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		ChargeRewardConfig cfg;
		rate += item.get("rate", 0).asUInt();
		cfg.require = rate;
		cfg.award.Json2Award(item["data"]["reward"]);
		m_luckyLottery.pools.push_back(cfg);
	}
	const Json::Value *draw1Price = fileParser.getMember("diamondDraw.draw1Price");
	if (draw1Price != NULL && draw1Price->isIntegral()) {
		m_luckyLottery.one = draw1Price->asUInt();
	}
	draw1Price = fileParser.getMember("diamondDraw.draw10Price");
	if (draw1Price != NULL && draw1Price->isIntegral()) {
		m_luckyLottery.ten = draw1Price->asUInt();
	}
	draw1Price = fileParser.getMember("diamondDraw.maxCount");
	if (draw1Price != NULL && draw1Price->isIntegral()) {
		m_luckyLottery.lucky_count = draw1Price->asUInt();
	}
	draw1Price = fileParser.getMember("diamondDraw.bestId");
	if (draw1Price != NULL && draw1Price->isIntegral()) {
		m_luckyLottery.lucky_id = draw1Price->asUInt();
	}
	return true;
}

bool GiftBagConfig::initfunctionUnlock(const string &path) {
	ConfigJson fileParser(path);
	if (!fileParser.Init()) {
		return false;
	}
	const Json::Value *value = fileParser.getMember("");
	if (value == NULL || !value->isArray()) {
		error_log("lucky lottery error");
		return false;
	}
	for (size_t i = 0; i < value->size(); ++i) {
		const Json::Value &item = value->get(i, Json::Value(Json::nullValue));
		if (item.isNull()) {
			continue;
		}
		ChargeRewardConfig cfg;
		uint32_t id = item.get("id", 0).asUInt();
		string type = item.get("type", "").asString();

		cfg.require = item.get("require", 0).asUInt();
		cfg.award.Json2Award(item["reward"]);
		if (type == "building") {
			m_functionUnlock_b.insert(make_pair(id, cfg));
		} else {
			m_functionUnlock_a.insert(make_pair(id, cfg));
		}
	}
	return true;
}

bool GiftBagConfig::initLuckyBox(const Json::Value &value) {
	if (value.isNull() || !value.isArray()) {
		return false;
	}
	for (size_t i = 0; i < value.size(); ++i) {
		const Json::Value &item = value[i];
		uint32_t id = 0;
		Json::GetUInt(item, "id", id);
		const Json::Value &rate = item["rate"];
		const Json::Value &ratekey = item["ratekey"];
		const Json::Value &reward = item["reward"];
		if (!rate.isArray() || !ratekey.isArray() || rate.size() != ratekey.size()) {
			error_log("lucky box error,id=%u", id);
			return false;
		}
		GiftBagItemConfig bag;
		bag.id = id;
		uint32_t totalRate = 0;
		for (size_t k = 0; k < rate.size(); ++k) {
			totalRate += rate[k].asUInt();
			bag.rate.push_back(totalRate);
		}
		for (size_t k = 0; k < ratekey.size(); ++k) {
			string key = ratekey[k].asString();
			if (!reward.isMember(key)) {
				error_log("lucky box ratekey error,id=%u,key=%s", id, key.c_str());
				return false;
			}
			AwardInfo awardInfo;
			if (!Award::JsonItem2Award(reward[key], key, awardInfo)) {
				error_log("JsonItem2Award error,id=%u,reward=%s", id, Json::ToString(reward[key]).c_str());
				return false;
			}
			bag.award.get().push_back(awardInfo);
		}
		m_giftBag.insert(make_pair(bag.id, bag));
	}
	return true;
}

const GiftBagItemConfig* GiftBagConfig::getConfig(uint32_t id) {
	map<uint32_t, GiftBagItemConfig>::iterator iter = m_giftBag.find(id);
	return (iter != m_giftBag.end()) ? &(iter->second) : NULL;
}

const Award* GiftBagConfig::getDailyChargeReward(uint32_t cash) {
	if (m_dailyCharge.require <= cash) {
		return &m_dailyCharge.award;
	}
	return NULL;
}

const Award* GiftBagConfig::getTotalChargeReward(uint32_t id, uint32_t cash) {
	map<uint32_t, ChargeRewardConfig>::iterator itr = m_totalCharge.find(id);
	if (itr == m_totalCharge.end()) {
		return NULL;
	}
	if (cash / 10 < itr->second.require) {
		return NULL;
	}
	return &(itr->second.award);
}

uint32_t GiftBagConfig::getTotalChargeRewardLen() const {
	return m_totalCharge.size();
}

bool GiftBagConfig::openLuckyBox(uint32_t id, uint32_t count, Award &award) {
	if (!m_giftBag.count(id)) {
		return false;
	}
	GiftBagItemConfig &giftBag = m_giftBag[id];
	if (giftBag.rate.empty()) {
		for (uint32_t c = 0; c < count; ++c) {
			vector<AwardInfo>::iterator it = giftBag.award.get().begin();
			for (; it != giftBag.award.get().end(); ++it) {
				award.add(*it);
			}
		}
		return true;
	}
	int maxRate = giftBag.rate.back();
	for (uint32_t c = 0; c < count; ++c) {
		uint32_t rate = Math::GetRandomInt(maxRate ? maxRate : 1);
		for (size_t i = 0; i < giftBag.rate.size(); ++i) {
			if (rate < giftBag.rate[i]) {
				const vector<AwardInfo> &reward = giftBag.award.get();
				if (reward.size() > i) {
					award.add(reward.at(i));
				}
				break;
			}
		}
	}

	return true;
}

bool GiftBagConfig::isBox(uint32_t id) {
	return m_giftBag.find(id) != m_giftBag.end();
}

bool GiftBagConfig::openAllLuckyBox(uint32_t boxId, uint32_t count, Award &award) {
	AwardInfo gift;
	gift.type = AWARD_TYPE_ITEM;
	gift.id = boxId;
	gift.count = count;
	Award box;
	box.add(gift);
	Award reward;
	while (0 != box.get().size()) {
		for (vector<AwardInfo>::const_iterator itr = box.get().begin(); itr != box.get().end(); ++itr) {
			openLuckyBox(itr->id, itr->count, reward);
		}
		Award newBox;
		for (vector<AwardInfo>::const_iterator itr = reward.get().begin(); itr != reward.get().end(); ++itr) {
			if (itr->type == AWARD_TYPE_ITEM && isBox(itr->id) && itr->count > 0) {
				debug_log("id=%u,count=%u", itr->id, itr->count);
				newBox.add(*itr);
				reward.sub(*itr);
			}
		}
		box = newBox;
	}

	if (reward.isEmpty()) {
		error_log("random gift bag reward error,equipId=%u", boxId);
		return false;
	}

	for (vector<AwardInfo>::const_iterator itr = reward.get().begin(); itr != reward.get().end(); ++itr) {
		if (itr->count != 0) {
			award.add(*itr);
		}
	}

	debug_log("boxId=%u,count=%u,boxSize=%u,awardSize=%u", boxId, count, box.get().size(), award.get().size());

	return true;
}

bool GiftBagConfig::openAll(const vector<AwardInfo> &in, Award &award) {
	vector<AwardInfo>::const_iterator itr = in.begin();
	for (; itr != in.end(); ++itr) {
		if (itr->type == AWARD_TYPE_ITEM && isBox(itr->id) && itr->count > 0) {
			openAllLuckyBox(itr->id, itr->count, award);
		} else {
			award.add(*itr);
		}
	}
	return true;
}

const NewServerRankConfig* GiftBagConfig::getNewSrvTar(uint32_t type, uint32_t id, uint32_t day) const {
	uint32_t real = 1;
	map<uint32_t, map<uint32_t, vector<NewServerRankConfig> > >::const_iterator it = m_new_srv_rank.find(type);
	if (it == m_new_srv_rank.end()) {
		return NULL;
	}
	map<uint32_t, vector<NewServerRankConfig> >::const_iterator it2 = it->second.find(day);
	if (it2 == it->second.end()) {
		return NULL;
	}
	const vector<NewServerRankConfig> &cfg = it2->second;
	vector<NewServerRankConfig>::const_iterator itr = cfg.begin();
	for (; itr != cfg.end(); ++itr) {
		if (itr->require != 0) {
			if (id == real) {
				return &(*itr);
			}
			++real;
		}
	}
	return NULL;
}

const NewServerRankConfig* GiftBagConfig::getNewSrvRank(uint32_t type, uint32_t id, uint32_t day) const {
	map<uint32_t, map<uint32_t, vector<NewServerRankConfig> > >::const_iterator it = m_new_srv_rank.find(type);
	if (it == m_new_srv_rank.end()) {
		return NULL;
	}
	map<uint32_t, vector<NewServerRankConfig> >::const_iterator it2 = it->second.find(day);
	if (it2 == it->second.end()) {
		return NULL;
	}
	const vector<NewServerRankConfig> &cfg = it2->second;
	vector<NewServerRankConfig>::const_iterator itr = cfg.begin();
	for (; itr != cfg.end(); ++itr) {
		if (id >= itr->from && itr->to >= id) {
			return &(*itr);
		}
	}
	return NULL;
}

const NewServerRankConfig* GiftBagConfig::getActRank(uint32_t type, uint32_t id) const {
	map<uint32_t, vector<NewServerRankConfig> >::const_iterator it = m_act_rank.find(type);
	if (it == m_act_rank.end()) {
		return NULL;
	}
	const vector<NewServerRankConfig> &cfg = it->second;
	vector<NewServerRankConfig>::const_iterator itr = cfg.begin();
	for (; itr != cfg.end(); ++itr) {
		if (id >= itr->from && itr->to >= id) {
			return &(*itr);
		}
	}
	return NULL;
}

uint32_t GiftBagConfig::getActRankRequire(uint32_t type) const {
	map<uint32_t, vector<NewServerRankConfig> >::const_iterator it = m_act_rank.find(type);
	if (it == m_act_rank.end() || it->second.empty()) {
		return 1;
	}
	return it->second.begin()->require;
}

uint32_t GiftBagConfig::getFirstChargeSize() const {
	return m_firstCharge.size();
}

const Award* GiftBagConfig::getFirstChargeReward(uint32_t id) const {
	map<uint32_t, Award>::const_iterator itr = m_firstCharge.find(id);
	if (itr == m_firstCharge.end()) {
		return NULL;
	}
	return &(itr->second);
}

const ChargeRewardConfig* GiftBagConfig::getDailyBuyBag(uint32_t day, bool is_new) const {
	if (is_new) {
		map<uint32_t, ChargeRewardConfig>::const_iterator itr = m_dailyBuyBagNew.find(day);
		return itr == m_dailyBuyBagNew.end() ? NULL : &(itr->second);
	}
	map<uint32_t, ChargeRewardConfig>::const_iterator itr = m_dailyBuyBag.find(day);
	return itr == m_dailyBuyBag.end() ? NULL : &(itr->second);
}

uint32_t GiftBagConfig::getDailyChargeEquipSize(uint32_t day, bool is_new) const {
	if (is_new) {
		map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeEquipNew.find(day);
		if (itr == m_dailyChargeEquipNew.end()) {
			return 0;
		}
		return itr->second.size();
	}
	map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeEquip.find(day);
	if (itr == m_dailyChargeEquip.end()) {
		return 0;
	}
	return itr->second.size();
}

const ChargeRewardConfig* GiftBagConfig::getDailyChargeEquip(uint32_t day, uint32_t id, bool is_new) const {
	if (is_new) {
		map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeEquipNew.find(day);
		if (itr == m_dailyChargeEquipNew.end()) {
			return NULL;
		}
		map<uint32_t, ChargeRewardConfig>::const_iterator it = itr->second.find(id);
		return it == itr->second.end() ? NULL : &(it->second);
	}
	map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeEquip.find(day);
	if (itr == m_dailyChargeEquip.end()) {
		return NULL;
	}
	map<uint32_t, ChargeRewardConfig>::const_iterator it = itr->second.find(id);
	return it == itr->second.end() ? NULL : &(it->second);
}

uint32_t GiftBagConfig::getDailyChargeCashSize(uint32_t day, bool is_new) const {
	if (is_new) {
		map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeCashNew.find(day);
		if (itr == m_dailyChargeEquipNew.end()) {
			return 0;
		}
		return itr->second.size();
	}
	map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeCash.find(day);
	if (itr == m_dailyChargeEquip.end()) {
		return 0;
	}
	return itr->second.size();
}

const ChargeRewardConfig* GiftBagConfig::getDailyChargeCash(uint32_t day, uint32_t id, bool is_new) const {
	if (is_new) {
		map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeCashNew.find(day);
		if (itr == m_dailyChargeCashNew.end()) {
			return NULL;
		}
		map<uint32_t, ChargeRewardConfig>::const_iterator it = itr->second.find(id);
		return it == itr->second.end() ? NULL : &(it->second);
	}
	map<uint32_t, map<uint32_t, ChargeRewardConfig> >::const_iterator itr = m_dailyChargeCash.find(day);
	if (itr == m_dailyChargeCash.end()) {
		return NULL;
	}
	map<uint32_t, ChargeRewardConfig>::const_iterator it = itr->second.find(id);
	return it == itr->second.end() ? NULL : &(it->second);
}

uint32_t GiftBagConfig::getContinueChargeSize(bool is_new) const {
	return is_new ? m_continueChargeNew.size() : m_continueCharge.size();
}

const ChargeRewardConfig* GiftBagConfig::getContinueCharge(uint32_t id, bool is_new) const {
	if (is_new) {
		map<uint32_t, ChargeRewardConfig>::const_iterator itr = m_continueChargeNew.find(id);
		return itr == m_continueChargeNew.end() ? NULL : &(itr->second);
	}
	map<uint32_t, ChargeRewardConfig>::const_iterator itr = m_continueCharge.find(id);
	return itr == m_continueCharge.end() ? NULL : &(itr->second);
}

uint32_t GiftBagConfig::getLuckyLotteryCost(bool ten) const {
	return ten ? m_luckyLottery.ten : m_luckyLottery.one;
}

uint32_t GiftBagConfig::getLuckyLotteryLuckyCount() const {
	return m_luckyLottery.lucky_count;
}

uint32_t GiftBagConfig::getLuckyLotteryLuckyId() const {
	return m_luckyLottery.lucky_id;
}

int32_t GiftBagConfig::randomLuckyLottery() const {
	if (m_luckyLottery.pools.empty()) {
		return -1;
	}
	int rate = m_luckyLottery.pools.back().require;
	uint32_t r = Math::GetRandomInt(rate == 0 ? 1 : rate);
	vector<ChargeRewardConfig>::const_iterator itr = m_luckyLottery.pools.begin();
	int id = 0;
	for (; itr != m_luckyLottery.pools.end(); ++itr, ++id) {
		if (r <= itr->require) {
			break;
		}
	}
	return id + 1;
}

const Award* GiftBagConfig::getLuckyLotteryReward(uint32_t id) const {
	if (m_luckyLottery.pools.size() <= id) {
		return NULL;
	}
	vector<ChargeRewardConfig>::const_iterator itr = m_luckyLottery.pools.begin() + id;
	return &(itr->award);
}

const ChargeRewardConfig* GiftBagConfig::getWanbaVipSpecialBag(uint32_t id) const {
	map<uint32_t, ChargeRewardConfig>::const_iterator itr = m_wanbaVipSpecialBag.find(id);
	if (itr == m_wanbaVipSpecialBag.end()) {
		return NULL;
	}
	return &(itr->second);
}

const ChargeRewardConfig* GiftBagConfig::getWanbaVipDailyBag(uint32_t id) const {
	map<uint32_t, ChargeRewardConfig>::const_iterator itr = m_wanbaVipDailyBag.find(id);
	if (itr == m_wanbaVipDailyBag.end()) {
		return NULL;
	}
	return &(itr->second);
}

const Award* GiftBagConfig::getShare() const {
	return &m_share;
}

const Award* GiftBagConfig::getAddShortcut() const {
	return &m_addShortcut;
}

const ChargeRewardConfig* GiftBagConfig::getFunctionUnlock(byte type, uint32_t id) const {
	map<uint32_t, ChargeRewardConfig>::const_iterator itr;
	if (type == 0) {
		itr = m_functionUnlock_a.find(id);
		return itr == m_functionUnlock_a.end() ? NULL : &(itr->second);
	} else if (type == 1) {
		itr = m_functionUnlock_b.find(id);
		return itr == m_functionUnlock_b.end() ? NULL : &(itr->second);
	}
	return NULL;
}
