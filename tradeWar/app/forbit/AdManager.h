/*
 * AdManager.h
 *
 *  Created on: 2013年12月5日
 *      Author: Administrator
 */

#ifndef ADMANAGER_H_
#define ADMANAGER_H_

#define QUAN_HAO 5
#define BAYU     6

#include "serverInc.h"

struct ChatMsg
{
	string uid;
	int vip;  // vip等级
	int lvl;  // 等级

	string srvListen;
	string msg;
	uint32_t time;
};

class AdManager {

public:
	static AdManager *getInstance(){
		static AdManager mrg;
		return &mrg;
	}

private:
	AdManager(){forbidTime = 0;};
	~AdManager(){};

public:
	bool init(const CConfig& conf);
	bool analyzeChatMsg(ChatMsg &chatMsg);
private:
	bool parseBayu(const ChatMsg &chatMsg);
	bool parseText(const ChatMsg &chatMsg);
	bool getIpAndPort(const string &listenStr, string &ip, short &port);

private:
	map<uint32_t, pair<string, short> > m_mapIp;
	int forbidTime;
	string cmdHead;

protected:
	map<uint32_t, vector<string> > m_mapAdWords;
};

#endif /* ADMANAGER_H_ */
