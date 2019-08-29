/*
 * ServerConfig.h
 *
 *  Created on: 2018年10月16日
 *      Author: Administrator
 */

#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include "Common.h"

struct ServerItem {
	uint32_t sid;
	uint16_t port;
	string host;

	ServerItem() : sid(0), port(0) {
		host.clear();
	}

	bool fromJson(const Json::Value &v) {
		if (v.isNull() || !v.isObject()) {
			return false;
		}
		sid = v.get("sid", 0).asUInt();
		port = v.get("port", 0).asUInt();
		host = v.get("host", "127.0.0.1").asString();
		return true;
	}

	ServerItem& operator=(const ServerItem &d) {
		this->sid = d.sid;
		this->port = d.port;
		this->host = d.host;
		return *this;
	}
};

class ServerConfig {
public:
	static ServerConfig *getInstance() {
		static ServerConfig _instance;
		return &_instance;
	}
	virtual ~ServerConfig();
	bool Init(const string &path);
	bool GetLogin(uint32_t sid, ServerItem &addr);
	bool IsMerged(uint32_t sid);
	bool GetAllServer(ServerItem &addr);
	bool GetDbWrite(ServerItem &addr);
	bool GetTransit(ServerItem &addr);
	bool GetChat(ServerItem &addr);
protected:
	ServerConfig();
private:
	map<uint32_t, ServerItem> m_data;
	map<uint32_t, set<uint32_t> > m_merged;
	ServerItem m_dbwrite;
	ServerItem m_allserver;
	ServerItem m_transit;
	ServerItem m_chat;
};

#endif /* APP_KERNEL_SERVERCONFIG_H_ */
