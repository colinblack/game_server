/*
 * AdAnalizeChengfang.cpp
 *
 *  Created on: 2013年12月5日
 *      Author: Administrator
 */

#include "AdAnalizeChengfang.h"

#include "serverInc.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std;

bool AdAnalizeChengfang::init(const string &path) {
	string line;
	std::fstream infile(path.c_str());
	while (getline(infile, line)) {
		line = kfc::trim_right(line, "\r\n");
		m_vecAdTags.push_back(line);
	}
	infile.close();
	return true;
}


bool AdAnalizeChengfang::parse(ChatMsg &chatMsg){
	// 每天零时清空数据
	static unsigned secOfDay = 3600 * 24;
	if (time(NULL) % secOfDay == 0) {
		m_mapChat.clear();
	}
	return this->parseTag(chatMsg);
}

/**
 * 连续3条含有广告关键字的封号
 */
bool AdAnalizeChengfang::parseTag(ChatMsg &chatMsg){
	if(chatMsg.vip > 0) {
		return true;
	}

	string msg = string(chatMsg.msg);
	string key = chatMsg.uid;
	// 含有广告关键字，可能是广告
	bool maybeAd = false;
	for (size_t i = 0; i < m_vecAdTags.size(); ++i) {
		if (msg.find(m_vecAdTags[i]) != string::npos) {
			maybeAd = true;
			break;
		}
	}

	map<string, vector<string> >::iterator it = m_mapChat.find(key);
	if(!maybeAd) {
		if(it != m_mapChat.end()){
			m_mapChat.erase(it);
		}
	} else {
		if(it != m_mapChat.end()) {
			it->second.push_back(msg);
			if(it->second.size() >= CHAT_RESERVE_COUNT) {
				// log ad
				for(unsigned i = 0; i < it->second.size(); ++i) {
					*CUdpServer::getInstance()->m_ptDayLog  << s_time(time(NULL)) << " ADLOG " << key << " : " << it->second[i] << endl;
				}
				*CUdpServer::getInstance()->m_ptDayLog << endl;
				m_mapChat.erase(it);
				return false;
			}
		} else {
			vector<string> vecMsg;
			vecMsg.push_back(msg);
			m_mapChat[key] = vecMsg;
		}
	}
	return true;
}
