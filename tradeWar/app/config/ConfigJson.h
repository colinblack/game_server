/*
 * ConfigJson.h
 *
 *  Created on: 2018年3月31日
 *      Author: Administrator
 */

#ifndef CONFIG_JSON_H_
#define CONFIG_JSON_H_

#include "Kernel.h"

class ConfigJson
{
public:
	ConfigJson(const string & path);
	virtual ~ConfigJson();
	bool Init();
	const Json::Value* getMember(const string &key);
private:
	string path_;
	Json::Value content_;
};

#endif /* CONFIG_JSON_H_ */
