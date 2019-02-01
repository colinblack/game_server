/*
 * AdAnalize.cpp
 *
 *  Created on: 2013年12月19日
 *      Author: vincent
 */
#include "AdAnalize.h"
#include <vector>
using namespace std;

#include "Common.h"

bool AdAnalize::config_flag = true;

bool AdAnalize::init(){
	return this->createSocket();
}

bool AdAnalize::createSocket(){
	string ad_listen;
	if(!Config::GetValue(ad_listen, "ad_listen"))
	{
		error_log("ad_config_error");
		config_flag = false;
		return false;
	}

	this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		return false;
	} else {
		printf("socket : %d\n", sockfd);
	}

	string ip;
	short port;
	this->getIpAndPort(ad_listen, ip, port);

	clnt_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	clnt_addr.sin_port = htons(port);
	clnt_addr.sin_family = AF_INET;

	return true;
}

bool AdAnalize::sendData(const ChatMsg &chatMsg) {
	if(!initFlag)
		return false;

	char sendmsg[MAXSIZE];
	memset(sendmsg, 0, MAXSIZE);
	string content = this->enCode(chatMsg);
	strcpy(sendmsg, content.c_str());
	sendto(sockfd, sendmsg, strlen(sendmsg) + 1, 0, (struct sockaddr *)&clnt_addr, sizeof(clnt_addr));
	return true;
}

string AdAnalize::enCode(const ChatMsg &chatMsg){
	string msg;
	msg.append("uid=").append(iToString(chatMsg.uid)).append("&")
	   .append("vip=").append(chatMsg.vip).append("&")
	   .append("lvl=").append(chatMsg.lvl).append("&")
	   .append("type=").append(chatMsg.type).append("&")
	   .append("srvListen=").append(chatMsg.srvListen).append("&")
	   .append("msg=").append(chatMsg.msg);
	return msg;
}

string AdAnalize::iToString(int i){
	char buff[12];
	sprintf(buff,"%d",i);
	return string(buff);
}

bool AdAnalize::getIpAndPort(const string &listenStr, string &ip, short &port){
	unsigned pos = listenStr.find(':');
	ip = listenStr.substr(0,pos);
	port = (short)atoi(listenStr.substr(pos+1).c_str());
	return true;
}
