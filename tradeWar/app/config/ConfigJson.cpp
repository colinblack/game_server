/*
 * ConfigJson.cpp
 *
 *  Created on: 2018年3月31日
 *      Author: Administrator
 */

#include "ConfigJson.h"

ConfigJson::ConfigJson(const string & path): path_(path)
{
}

ConfigJson::~ConfigJson()
{
}

bool ConfigJson::Init()
{
	int ret = 0;
	string buffer;
	ret = File::Read(path_, buffer);
	if (0 != ret)
	{
		error_log("read file error ret=%d path=%s", ret, path_.c_str());
		return false;
	}

	//del utf-8 bom head
	if (buffer.size() > 3) {
		const unsigned char a = *(buffer.c_str() + 0);
		const unsigned char b = *(buffer.c_str() + 1);
		const unsigned char c = *(buffer.c_str() + 2);
		if (a == 0xEF && b == 0xBB && c == 0xBF) {
			buffer.erase(0, 3);
		}
	}

	Json::Reader reader;
	if (!reader.parse(buffer, content_))
	{
		error_log("parse file error err=%s path=%s", reader.getFormatedErrorMessages().c_str(), path_.c_str());
		return false;
	}
	return true;
}

const Json::Value* ConfigJson::getMember(const string &key)
{
	Json::Value *root = &content_;
	vector<string> keys;
	CBasic::StringSplitTrim(key, ".", keys);
	vector<string>::iterator itr = keys.begin();
	for (; itr != keys.end(); ++itr) {
		if (!root->isMember(*itr))
		{
			return NULL;
		}
		root = &((*root)[*itr]);
	}
	return root;
}
