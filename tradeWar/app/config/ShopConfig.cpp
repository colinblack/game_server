/*
 * ShopConfig.cpp
 *
 *  Created on: 2017年8月12日
 *      Author: Administrator
 */

#include "ShopConfig.h"

CShopConfig::CShopConfig() {
}

CShopConfig::~CShopConfig() {
}

bool CShopConfig::init() {
	string path = Config::GetValue(CONFIG_SHOP);
	if (Config::GetValue(CONFIG_WEIXIN) == "1") {
		path = Config::GetValue("shop_wx");
	}
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret != 0) {
		error_log("read error");
		return false;
	}
	Json::Value content;
	Json::Reader reader;
	if (!reader.parse(buffer, content)) {
		error_log("parse error");
		return false;
	}

	Json::Value &diamond = content["shop"]["diamond"];
	if (diamond.isNull() || !diamond.isArray()) {
		error_log("diamond error");
		return false;
	}
	for (size_t i = 0; i < diamond.size(); ++i) {
		Json::Value &item = diamond[i];
		if (item.isNull()) {
			continue;
		}
		ShopConfigDiamondItem info;
		info.id = String::s2i(item["id"].asString(), 0);
		info.count = String::s2i(item["count"].asString(), 0);
		info.extra = String::s2i(item["extra"].asString(), 0);
		info.cost = String::s2i(item["cost"].asString(), 0);
		m_diamond.push_back(info);
	}

	Json::Value &res = content["shop"]["res"];
	if (res.isNull() || !res.isArray()) {
		error_log("res error");
		return false;
	}
	for (size_t i = 0; i < res.size(); ++i) {
		Json::Value &item = res[i];
		if (item.isNull()) {
			continue;
		}
		ShopGood info;
		info.id = String::s2i(item["id"].asString(), 0);
		info.cost = String::s2i(item["cost"].asString(), 0);
		info.subType = ShopGoodSubTypeRes;
		m_good[info.id] = info;
	}

	Json::Value &gold = content["shop"]["gold"];
	if (gold.isNull() || !gold.isArray()) {
		error_log("gold error");
		return false;
	}
	for (size_t i = 0; i < gold.size(); ++i) {
		Json::Value &item = gold[i];
		if (item.isNull()) {
			continue;
		}
		ShopGood info;
		info.id = String::s2i(item["id"].asString(), 0);
		info.cost = String::s2i(item["cost"].asString(), 0);
		info.subType = ShopGoodSubTypeBag;
		m_good[info.id] = info;
	}

	Json::Value &goods = content["shop"]["goods"];
	if (goods.isNull() || !goods.isArray()) {
		error_log("goods error");
		return false;
	}
	for (size_t i = 0; i < goods.size(); ++i) {
		Json::Value &item = goods[i];
		if (item.isNull()) {
			continue;
		}
		ShopGood info;
		info.id = String::s2i(item["id"].asString(), 0);
		info.cost = String::s2i(item["cost"].asString(), 0);
		info.subType = ShopGoodSubTypeBag;
		m_good[info.id] = info;
	}

	const Json::Value &chip = content["shop"]["chip"];
	if (chip.isNull() || !chip.isArray()) {
		error_log("chip error");
		return false;
	}
	for (size_t i = 0; i < chip.size(); ++i) {
		ShopChipItem cfg;
		cfg.id = chip[i].get("id", 0).asUInt();
		cfg.require = chip[i].get("compound", 0).asUInt();
		cfg.equip = chip[i].get("chipId", 0).asUInt();
		m_chip.insert(make_pair(cfg.id, cfg));
	}
	return true;
}

bool CShopConfig::getDiamondIndex(uint32_t cash, uint32_t &id) {
	for (size_t i = 0; i < m_diamond.size(); ++i) {
		if (cash == m_diamond[i].count) {
			id = i;
			return true;
		}
	}
	return false;
}

uint32_t CShopConfig::getDiamondSize() {
	return m_diamond.size();
}

const ShopGood* CShopConfig::getGoodItem(uint32_t id) {
	map<uint32_t, ShopGood>::iterator itr = m_good.find(id);
	if (itr == m_good.end()) {
		return NULL;
	}
	return &(itr->second);
}

const ShopChipItem* CShopConfig::getChip(uint16_t id) const {
	map<uint16_t, ShopChipItem>::const_iterator itr = m_chip.find(id);
	if (itr == m_chip.end()) {
		return NULL;
	}
	return &(itr->second);
}
