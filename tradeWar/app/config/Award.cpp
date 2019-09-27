/*
 * Award.cpp
 *
 *  Created on: 2015-12-30
 *      Author: Administrator
 */

#include "Award.h"

Award::Award() {
	m_vecAward.clear();
}

Award::~Award() {
	m_vecAward.clear();
}

void Award::clear() {
	m_vecAward.clear();
}

int Award::add(const AwardInfo& awardInfo) {
	for (vector<AwardInfo>::iterator it = m_vecAward.begin(); it != m_vecAward.end(); ++it) {
		if (it->id == awardInfo.id && it->type == awardInfo.type) {
			it->count += awardInfo.count;
			return 0;
		}
	}
	m_vecAward.push_back(awardInfo);
	return 0;
}

int Award::sub(const AwardInfo& awardInfo) {
	for (vector<AwardInfo>::iterator it = m_vecAward.begin(); it != m_vecAward.end(); ++it) {
		if (it->id == awardInfo.id && it->type == awardInfo.type && it->count >= awardInfo.count) {
			it->count -= awardInfo.count;
			return 0;
		}
	}
	return 1;
}

void Award::multiply(uint32_t times) {
	for (vector<AwardInfo>::iterator iter = m_vecAward.begin(); iter != m_vecAward.end(); ++iter) {
		iter->count *= times;
	}
}

bool Award::Json2Award(const Json::Value &value, vector<AwardInfo> &vecAward) {
	vecAward.clear();
	if (!value.isObject()) {
		return false;
	}
	Json::Value::Members member = value.getMemberNames();
	Json::Value::Members::iterator it = member.begin();
	for (; it != member.end(); ++it) {
		AwardInfo awardInfo;
		if (JsonItem2Award(value[*it], *it, awardInfo)) {
			vecAward.push_back(awardInfo);
		}
	}
	return true;
}

bool Award::JsonItem2Award(const Json::Value &itemValue, const string &name, AwardInfo &awardInfo) {
	if (name.find("equip") != string::npos) {
		awardInfo.type = AWARD_TYPE_ITEM;
		awardInfo.count = itemValue["c"].asUInt();
		awardInfo.id = itemValue["id"].asUInt();
	} else if (name == "rs1") {
		awardInfo.type = AWARD_TYPE_R1;
		awardInfo.count = itemValue.asUInt();
	} else if (name == "rr1") {
		awardInfo.type = AWARD_TYPE_R1_RATE;
		awardInfo.count = itemValue.asUInt();
	} else if (name == "rs2") {
		awardInfo.type = AWARD_TYPE_R2;
		awardInfo.count = itemValue.asUInt();
	} else if (name == "rr2") {
		awardInfo.type = AWARD_TYPE_R2_RATE;
		awardInfo.count = itemValue.asUInt();
	} else if (name == "energy") {
		awardInfo.type = AWARD_TYPE_ENERGY;
		awardInfo.count = itemValue.asUInt();
	} else if (name.find("cash") != string::npos) {
		awardInfo.type = AWARD_TYPE_DIAMOND;
		awardInfo.count = itemValue.asUInt();
	} else if (name == "exp") {
		awardInfo.type = AWARD_TYPE_PEXP;
		awardInfo.count = itemValue.asUInt();
	} else if (name.find("soldier") != string::npos) {
		awardInfo.type = AWARD_TYPE_SOLDIER;
		if (itemValue.isString()) {
			awardInfo.id = CTrans::STOI(itemValue.asString().substr(1));
			awardInfo.count = 1;
		} else if (itemValue.isObject()) {
			awardInfo.id = CTrans::STOI(itemValue["id"].asString().substr(1));
			awardInfo.count = itemValue["c"].asUInt();
		}
	} else if (name.find("skill") != string::npos) {
		awardInfo.type = AWARD_TYPE_SKILL;
		if (itemValue.isIntegral()) {
			awardInfo.id = itemValue.asUInt();
			awardInfo.count = 1;
		} else if (itemValue.isObject()) {
			awardInfo.id = itemValue["id"].asUInt();
			awardInfo.count = itemValue["c"].asUInt();
		}
	} else if (name == "loyal") {
		awardInfo.type = AWARD_TYPE_LOYAL;
		awardInfo.count = itemValue.asUInt();
	} else {
		return false;
	}
	return true;
}

bool Award::Json2Award(const Json::Value &value) {
	return Json2Award(value, m_vecAward);
}

bool Award::changeResRate(uint32_t r1, uint32_t r2) {
	uint32_t addR1 = 0, addR2 = 0;
	vector<AwardInfo>::iterator itr = m_vecAward.begin();
	for (; itr != m_vecAward.end();) {
		if (itr->type == AWARD_TYPE_R1_RATE) {
			addR1 += r1 * itr->count / 100;
			itr = m_vecAward.erase(itr);
		} else if (itr->type == AWARD_TYPE_R2_RATE) {
			addR2 += r2 * itr->count / 100;
			itr = m_vecAward.erase(itr);
		} else {
			++itr;
		}
	}

	if (addR1 > 0) {
		itr = find(m_vecAward.begin(), m_vecAward.end(), AWARD_TYPE_R1);
		if (itr != m_vecAward.end()) {
			itr->count += addR1;
		} else {
			AwardInfo item;
			item.type = AWARD_TYPE_R1;
			item.count = addR1;
			m_vecAward.push_back(item);
		}
	}
	if (addR2 > 0) {
		itr = find(m_vecAward.begin(), m_vecAward.end(), AWARD_TYPE_R2);
		if (itr != m_vecAward.end()) {
			itr->count += addR2;
		} else {
			AwardInfo item;
			item.type = AWARD_TYPE_R2;
			item.count = addR2;
			m_vecAward.push_back(item);
		}
	}
	return true;
}

const string& Award::Award2String(const vector<AwardInfo> &vecAward) {
	static string str;
	str.clear();
	Json::FastWriter writer;
	str = writer.write(Award2Json(vecAward));
	return str;
}

Json::Value Award::Award2Json(const vector<AwardInfo> &vecAward) {
	Json::Value value;

	size_t equipSize = 0;
	size_t soldierSize = 0;
	size_t skillSize = 0;
	for (vector<AwardInfo>::const_iterator conIt = vecAward.begin(); conIt != vecAward.end(); ++conIt) {
		AwardInfo awardItem = *conIt;
		switch (awardItem.type) {
		case AWARD_TYPE_ITEM: {
			string name("equip");
			name.append(String::i2s(++equipSize));
			value[name]["c"] = (uint32_t) awardItem.count;
			value[name]["id"] = awardItem.id;
			break;
		}
		case AWARD_TYPE_PEXP:
			addAward(value, "exp", awardItem.count);
			break;
		case AWARD_TYPE_DIAMOND:
			addAward(value, "diamond", awardItem.count);
			break;
		case AWARD_TYPE_R1:
			addAward(value, "rs1", awardItem.count);
			break;
		case AWARD_TYPE_R2:
			addAward(value, "rs2", awardItem.count);
			break;
		case AWARD_TYPE_R2_RATE:
			addAward(value, "rr2", awardItem.count);
			break;
		case AWARD_TYPE_R1_RATE:
			addAward(value, "rr1", awardItem.count);
			break;
		case AWARD_TYPE_ENERGY:
			addAward(value, "energy", awardItem.count);
			break;
		case AWARD_TYPE_SOLDIER: {
			string name = "soldier" + CTrans::ITOS(++soldierSize);
			value[name]["id"] = "S" + CTrans::ITOS(awardItem.id);
			value[name]["c"] = static_cast<uint32_t>(awardItem.count);
			break;
		}
		case AWARD_TYPE_SKILL: {
			string name = "skill" + CTrans::ITOS(++skillSize);
			value[name]["id"] = awardItem.id;
			value[name]["c"] = static_cast<uint32_t>(awardItem.count);
			break;
		}
		default:
			break;
		}
	}

	return value;
}

bool Award::addAward(Json::Value &value, const string &key, uint32_t count) {
	if (!value.isMember(key)) {
		value[key] = (uint32_t) 0;
	}
	value[key] = value[key].asUInt() + count;
	return true;
}
bool Award::mergeAward(const vector<AwardInfo> &in, vector<AwardInfo> &out) {
	map<uint32_t, AwardInfo> merge_equip;
	map<uint32_t, AwardInfo> merge_soldier;
	map<uint32_t, AwardInfo> merge_skill;
	map<uint32_t, uint32_t> merge_res;

	vector<AwardInfo>::const_iterator itr = in.begin();
	for (; itr != in.end(); ++itr) {
		switch (itr->type) {
		case AWARD_TYPE_ITEM:
			if (!merge_equip.count(itr->id)) {
				merge_equip[itr->id] = *itr;
			} else {
				merge_equip[itr->id].count += itr->count;
			}
			break;
		case AWARD_TYPE_PEXP:
		case AWARD_TYPE_DIAMOND:
		case AWARD_TYPE_R1:
		case AWARD_TYPE_R2:
		case AWARD_TYPE_R1_RATE:
		case AWARD_TYPE_R2_RATE:
		case AWARD_TYPE_ENERGY:
			if (merge_res.count(AWARD_TYPE_PEXP)) {
				merge_res[itr->type] += itr->count;
			} else {
				merge_res[itr->type] = itr->count;
			}
			break;
		case AWARD_TYPE_SOLDIER:
			if (!merge_soldier.count(itr->id)) {
				merge_soldier[itr->id] = *itr;
			} else {
				merge_soldier[itr->id].count += itr->count;
			}
			break;
		case AWARD_TYPE_SKILL:
			if (!merge_skill.count(itr->id)) {
				merge_skill[itr->id] = *itr;
			} else {
				merge_skill[itr->id].count += itr->count;
			}
			break;
		}
	}
	map<uint32_t, AwardInfo>::iterator mitr;
	for (mitr = merge_equip.begin(); mitr != merge_equip.end(); ++mitr) {
		out.push_back(mitr->second);
	}
	for (mitr = merge_soldier.begin(); mitr != merge_soldier.end(); ++mitr) {
		out.push_back(mitr->second);
	}
	for (mitr = merge_skill.begin(); mitr != merge_skill.end(); ++mitr) {
		out.push_back(mitr->second);
	}
	map<uint32_t, uint32_t>::iterator resitr = merge_res.begin();
	for (; resitr != merge_res.end(); ++resitr) {
		AwardInfo item;
		item.type = resitr->first;
		item.count = resitr->second;
		out.push_back(item);
	}
	return true;
}

bool Award::packetData(CBufferWriter &writer) const {
	writer.AppendUInt32(m_vecAward.size());
	vector<AwardInfo>::const_iterator itr = m_vecAward.begin();
	for (; itr != m_vecAward.end(); ++itr) {
		writer.AppendByte(itr->type);
		writer.AppendUInt32(itr->id);
		writer.AppendUInt32(itr->count);
	}
	return true;
}
