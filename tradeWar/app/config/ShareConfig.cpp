/*
 * ShareConfig.cpp
 *
 *  Created on: 2017年10月14日
 *      Author: Administrator
 */

#include "ShareConfig.h"

CShareConfig::CShareConfig() {
}

CShareConfig::~CShareConfig() {
}

bool CShareConfig::init(const string &path) {
	int ret = 0;
	string buffer;
	ret = File::Read(path, buffer);
	if (ret) {
		error_log("read error");
		return false;
	}
	Json::Value obj;
	if (!Json::FromString(obj, buffer)) {
		error_log("parse error");
		return false;
	}

	Json::Value &content = obj["share"];
	if (content.isNull() || !content.isObject()) {
		error_log("share error");
		return false;
	}

	Json::Value &daily = content["daily"];
	if (daily.isNull() || !daily.isObject()) {
		error_log("daily error");
		return false;
	}

	if (!Json::GetUInt(daily, "max", m_daily.max)) {
		m_daily.max = 0;
	}
	if (!Json::GetUInt(daily, "interval", m_daily.interval)) {
		m_daily.interval = 0;
	}
	m_daily.reward.Json2Award(daily["reward"]);

	Json::Value &invite = content["invite"];
	if (invite.isNull() || !invite.isObject()) {
		error_log("invite error");
		return false;
	}
	m_invite.Json2Award(invite["reward"]);

	return true;
}
