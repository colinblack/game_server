/*
 * AdAnalize.h
 *
 *  Created on: 2013年12月13日
 *      Author: Administrator
 */

#ifndef ADANALIZE_H_
#define ADANALIZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include<string>
using namespace std;
#define BAYU             6
#define MAXSIZE          4096



struct ChatMsg {
	unsigned uid;
	string vip;
	string lvl;
	string type;
	string srvListen;//ip:port
	string msg;

	ChatMsg(){
		uid = 0;
	}
};

class AdAnalize {
public:
	static AdAnalize* getInstance(){
		static AdAnalize sender;
		if(!sender.initFlag) {
			if(sender.init())
				sender.initFlag = true;
		}
		return &sender;
	}
	static bool getFlag(){return config_flag;}
	~AdAnalize(){};
private:
	AdAnalize(){initFlag = false; sockfd = -1;};

public:
	bool sendData(const ChatMsg &chatMsg);
private:
	bool init();
	bool createSocket();
	string enCode(const ChatMsg &chatMsg);
	string iToString(int i);
	bool getIpAndPort(const string &listenStr, string &ip, short &port);

private:
	bool initFlag;
	int sockfd;
	static bool config_flag;
	struct sockaddr_in clnt_addr;
};

#endif /* ADANALIZE_H_ */
