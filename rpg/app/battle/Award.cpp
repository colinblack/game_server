/*
 * Award.cpp
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#include "Award.h"

Award::Award() {
	m_data.clear();
}

Award::~Award() {
	m_data.clear();
}

bool Award::Add(uint32_t item, uint32_t num) {
	map<uint32_t, uint32_t>::iterator itr = m_data.find(item);
	if (itr == m_data.end()) {
		m_data[item] = num;
	}
	itr->second += num;
	return true;
}

bool Award::Format(const string &v) {
	vector<string> items;
	CBasic::StringSplitTrim(v, "&", items);
	vector<string>::iterator itr = items.begin();
	for (; itr != items.end(); ++itr) {
		vector<string> node;
		CBasic::StringSplitTrim(*itr, "#", node);
		if (node.size() != 2) {
			continue;
		}
		Add(Convert::StringToUInt(node[0]), Convert::StringToUInt(node[1]));
	}
	return true;
}

bool Award::Format(const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > &v, uint32_t multiple) {
	for (int i = 0; i < v.size(); ++i) {
		Add(v.Get(i).item(), v.Get(i).num() * multiple);
	}
	return true;
}

bool Award::Get(vector<msgs::SItemAmount> &v) {
	map<uint32_t, uint32_t>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr) {
		msgs::SItemAmount item;
		item.itemCode_ = itr->first;
		item.itemNum_ = itr->second;
		v.push_back(item);
	}
	return true;
}

const map<uint32_t, uint32_t>& Award::Data() const {
	return m_data;
}

bool Award::Random(const ::google::protobuf::RepeatedPtrField< ::CfgCommon::Reward > &v, uint32_t num) {
	if (num == 0) {
		return true;
	}
	uint32_t rate_sum = 0;
	vector<uint32_t> rates;
	for (int i = 0; i < v.size(); ++i) {
		rate_sum += v.Get(i).rate();
		rates.push_back(rate_sum);
	}
	for (uint32_t i = 0; i < num; ++i) {
		uint32_t r = Math::GetRandomInt(rate_sum == 0 ? 1 : rate_sum);
		for (size_t j = 0; j < rates.size(); ++j) {
			if (r < rates[j]) {
				Add(v.Get(j).item(), v.Get(j).num());
				break;
			}
		}
	}
	return true;
}

bool Award::IsExist(uint32_t item) const {
	map<uint32_t, uint32_t>::const_iterator itr = m_data.find(item);
	return itr != m_data.end();
}
