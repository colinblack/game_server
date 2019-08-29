/*
 * FriendConfig.cpp
 *
 *  Created on: 2017年11月15日
 *      Author: Administrator
 */

#include "FriendConfig.h"

FriendConfig::FriendConfig() : max_send_help(0), max_recv_help(0), max_send_gift(0), max_recv_gift(0)
{
}

FriendConfig::~FriendConfig()
{
}

bool FriendConfig::init(const string &path)
{
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret)
	{
		error_log("read error");
		return false;
	}
	Json::Value content;
	Json::Reader reader;
	if (!reader.parse(buffer, content))
	{
		error_log("parse error msg=%s", reader.getFormatedErrorMessages().c_str());
		return false;
	}
	Json::Value &data = content["friend"];
	if (data.isNull() || !data.isObject())
	{
		error_log("friend error");
		return false;
	}
	max_send_help = data.get("kjmax", 0).asInt();
	max_recv_help = data.get("kjper", 0).asInt();
	max_send_gift = data.get("giftmax", 0).asInt();
	max_recv_gift = data.get("giftper", 0).asInt();

	Json::Value &gift = data["gift"];
	if (gift.isNull() || !gift.isArray())
	{
		error_log("gift error");
		return false;
	}

	for (size_t i = 0; i < gift.size(); ++i)
	{
		Json::Value &item = gift[i];
		if (item.isNull() || !item.isObject())
		{
			continue;
		}
		uint16_t id = item.get("id", 0).asInt();
		Award award;
		award.Json2Award(item["reward"]);
		m_reward.insert(make_pair(id, award));
	}
	return true;
}

