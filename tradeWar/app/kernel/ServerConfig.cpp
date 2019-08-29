/*
 * ServerConfig.cpp
 *
 *  Created on: 2018年10月16日
 *      Author: Administrator
 */

#include "ServerConfig.h"

ServerConfig::ServerConfig() {
}

ServerConfig::~ServerConfig() {
}

bool ServerConfig::Init(const string &path) {
	string buff;
	int ret = File::Read(path, buff);
	if (ret != 0) {
		error_log("read server config error path is %s", path.c_str());
		return false;
	}
	Json::Value data;
	Json::Reader reader;
	if (!reader.parse(buff, data)) {
		error_log("parse server config error path is %s err is %s", path.c_str(), reader.getFormatedErrorMessages().c_str());
		return false;
	}
	Json::Value &login = data["login"];
	if (login.isNull() || !login.isArray()) {
		error_log("server config style error path is %s", path.c_str());
		return false;
	}
	for (size_t i = 0; i < login.size(); ++i) {
		ServerItem item;
		if (!item.fromJson(login[i])) {
			continue;
		}
		if (item.sid == 0 || item.port == 0) {
			continue;
		}
		m_data.insert(make_pair(item.sid, item));
		set<uint32_t> &merged = m_merged[item.port];
		merged.insert(item.sid);
	}

	if (!m_dbwrite.fromJson(data["dbwrite"])) {
		error_log("server config style error path is %s", path.c_str());
		return false;
	}

	if (!m_allserver.fromJson(data["allserver"])) {
		error_log("server config style error path is %s", path.c_str());
		return false;
	}

	if (!m_transit.fromJson(data["transit"])) {
		error_log("server config style error path is %s", path.c_str());
		return false;
	}
	return true;
}

bool ServerConfig::GetLogin(uint32_t sid, ServerItem &addr) {
	map<uint32_t, ServerItem>::iterator itr = m_data.find(sid);
	if (itr == m_data.end()) {
		return false;
	}
	addr = itr->second;
	return true;
}

bool ServerConfig::IsMerged(uint32_t sid) {
	uint32_t curr_server = Config::GetIntValue("server_id");
	map<uint32_t, ServerItem>::iterator itr1 = m_data.find(curr_server);
	map<uint32_t, ServerItem>::iterator itr2 = m_data.find(sid);
	if (itr1 == m_data.end() || itr2 == m_data.end()) {
		return false;
	}
	return itr1->second.port == itr2->second.port;
}

bool ServerConfig::GetAllServer(ServerItem &addr) {
	addr = m_allserver;
	return m_allserver.port != 0 && !m_allserver.host.empty();
}

bool ServerConfig::GetDbWrite(ServerItem &addr) {
	addr = m_dbwrite;
	return m_dbwrite.port != 0 && !m_dbwrite.host.empty();
}

bool ServerConfig::GetTransit(ServerItem &addr) {
	addr = m_transit;
	return m_transit.port != 0 && !m_transit.host.empty();
}

bool ServerConfig::GetChat(ServerItem &addr) {
	addr = m_chat;
	return m_chat.port != 0 && !m_chat.host.empty();
}
