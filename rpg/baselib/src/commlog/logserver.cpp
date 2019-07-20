/*
 * logserver.cpp
 *
 *  Created on: 2014年1月24日
 *      Author: Administrator
 */

#include "logserver.h"

using namespace std;

bool Logger::init(){
	return this->createSocket();
}

bool Logger::createSocket(){
	this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		return false;
	} else {
		printf("socket : %d\n", sockfd);
	}
	return true;
}


bool Logger::sendData(const LogMsg &logMsg, string ip, short port){
	sockaddr_in clnt_addr;

	clnt_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	clnt_addr.sin_port = htons(port);
	clnt_addr.sin_family = AF_INET;

	char sendmsg[MAXSIZE];
	memset(sendmsg, 0, MAXSIZE);
	string content = this->enCode(logMsg);
	strcpy(sendmsg, content.c_str());
	sendto(sockfd, sendmsg, strlen(sendmsg) + 1, 0,	(struct sockaddr *) &clnt_addr, sizeof(clnt_addr));

//	string ip;
//		short port;
//		this->getIpAndPort(ad_listen, ip, port);
//
//		sockaddr_in clnt_addr;
//
//		clnt_addr.sin_addr.s_addr = inet_addr(ip.c_str());
//		clnt_addr.sin_port = htons(port);
//		clnt_addr.sin_family = AF_INET;
//
//		char sendmsg[MAXSIZE];
//		memset(sendmsg, 0, MAXSIZE);
//		string content = this->enCode(chatMsg);
//		strcpy(sendmsg, content.c_str());
//		sendto(sockfd, sendmsg, strlen(sendmsg) + 1, 0, (struct sockaddr *)&clnt_addr, sizeof(clnt_addr));



	return true;
}


string Logger::enCode(const LogMsg &logMsg){
	string msg;
	msg.append("srvId=").append(logMsg.srvId).append("&").
		append("proId=").append(logMsg.proId).append("&").
		append("logFileName=").append(logMsg.logFileName).append("&").
		append("logStr=").append(logMsg.logStr);
	return msg;
}
