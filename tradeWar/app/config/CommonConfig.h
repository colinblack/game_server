/*
 * CommonConfig.h
 *
 *  Created on: 2016年6月16日
 *      Author: asdf
 */

#ifndef CONFIG_COMMON_CONFIG_H_
#define CONFIG_COMMON_CONFIG_H_

using std::vector;
using std::set;
using std::pair;

template<typename T>
bool parseArray(const Json::Value &v, vector<T> &d) {
	if (v.isNull() || !v.isArray()) {
		return false;
	}
	for (size_t i = 0; i < v.size(); ++i) {
		unsigned item = 0;
		Json::GetUInt(v, i, item);
		d.push_back(item);
	}
	return true;
}

#endif /* CONFIG_COMMON_CONFIG_H_ */
