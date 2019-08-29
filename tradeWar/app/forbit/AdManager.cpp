/*
 * AdManager.cpp
 *
 *  Created on: 2013年12月5日
 *      Author: Administrator
 */

#include "serverInc.h"

bool AdManager::init(const CConfig& conf) {
	if(!AdAnalizeChengfang::getInstance()->init(conf["Main\\AdTags"])){
		*CUdpServer::getInstance()->m_ptRollLog << "init AdAnalizeChengfang failed" << endl;
		return false;
	}

	this->forbidTime = atoi(conf["Main\\ForbidTime"].c_str());
	this->cmdHead    = conf["Main\\CmdHead"];
	return true;
}


/**
 *	@return true - 正常聊天  ； false - 广告
 */
bool AdManager::analyzeChatMsg(ChatMsg &chatMsg){
	bool isNormalChat =  AdAnalizeChengfang::getInstance()->parse(chatMsg);
	if(!isNormalChat) {
		uint32_t ftime = time(NULL) + forbidTime;
		string cmd = cmdHead;
		cmd.append(" ").append(chatMsg.uid).append(" ").append(i2s(ftime)).append(" ").append(chatMsg.srvListen);
		system(cmd.c_str());
	}
	return isNormalChat;
}

bool AdManager::getIpAndPort(const string &listenStr, string &ip, short &port){
	unsigned pos = listenStr.find(':');
	ip = listenStr.substr(0,pos);
	port = (short)atoi(listenStr.substr(pos+1).c_str());
	return true;
}
