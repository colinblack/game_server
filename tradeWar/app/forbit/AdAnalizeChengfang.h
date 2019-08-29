/*
 * AdAnalizeBayu.h
 *
 *  Created on: 2013年12月5日
 *      Author: Administrator
 */

#ifndef ADANALIZECHENGFANG_H_
#define ADANALIZECHENGFANG_H_

#include "serverInc.h"
#include "AdManager.h"
#include <time.h>

#define CHAT_RESERVE_COUNT 3
#define LIMIT_SRV          8
#define	FILTER_TIME_INTERVAL 180
#define FILTER_SPEEK_LIMIT 40
#define FILTER_LEVEL_LIMIT 35
#define FILTER_SIM 0.8

struct ChatFrq{
	uint32_t time;
	map<uint32_t, string> mapFrq;  // map<toRid, msg>
};

class AdAnalizeChengfang {
public:
	static AdAnalizeChengfang* getInstance() {
		static AdAnalizeChengfang instance;
		return &instance;
	}

public:
	bool init(const string &path);

private:
	AdAnalizeChengfang(){};
	virtual ~AdAnalizeChengfang(){};
public:
	bool parse(ChatMsg &chatMsg);
	bool parseTag(ChatMsg &chatMsg);
private:
	bool maybeAd(const ChatMsg &chatMsg);
	double getSimilarity(const string &rawStrA, const string &rawStrB);
	inline string s_time(time_t t)
	{
		struct tm curr;
		curr = *localtime(&t);
		char sTmp[1024];
		string formatStr = "[%H:%M:%S]";
		strftime(sTmp, sizeof(sTmp), formatStr.c_str(), &curr);
		return string(sTmp);
	}

	bool getValue(ChatMsg &chatMsg);

private:
	map<string,vector<string> > m_mapChat;   // map<"gameId|srvId|rid", charList>  只保留3条
	vector<string> m_vecAdTags;
};

#endif /*ADANALIZECHENGFANG_H_ */
