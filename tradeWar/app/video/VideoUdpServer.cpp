/*
 * VideoUdpServer.cpp
 *
 *  Created on: 2015年11月16日
 *      Author: Administrator
 */

#include "VideoUdpServer.h"
#include "Logger.h"
#include "Common.h"
#include <pthread.h>
#define MAGIC_HEADER 26284
#define TIMER_HEADER 0

CVideoUdpServer::CVideoUdpServer() {
}

CVideoUdpServer::~CVideoUdpServer() {
}

void * VideoTimerThread(void * arg)
{
	struct sockaddr_in inaddr = *((sockaddr_in*)arg);
	struct timeval timeOut;

	static int netfd;
	if((netfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		return NULL;
	}

	char sendMsg[64] = {0};
	ClientHead head;
	head.head = 0;
	memcpy(sendMsg,&head,sizeof(ClientHead));

	while(1){
		timeOut.tv_sec = 0;
		timeOut.tv_usec = 500000;
		if(select(0,NULL,NULL,NULL,&timeOut) == 0){
			 sendto(netfd, sendMsg,sizeof(sendMsg) , 0,	(struct sockaddr *) &inaddr, sizeof(inaddr));
		}
	}

	return NULL;
}

bool CVideoUdpServer::timerInit()
{
	static struct sockaddr_in inaddr;

	bzero (&inaddr, sizeof (struct sockaddr_in));
	inaddr.sin_addr.s_addr = inet_addr(m_tConf.sBindIP.c_str());
	inaddr.sin_port = htons(atoi(m_tConf.sPort.c_str()));
	inaddr.sin_family = AF_INET;

	pthread_t pid;
	if(pthread_create(&pid,NULL,VideoTimerThread,(void*)&inaddr) != 0){
		return false;
	}

	return true;
}

int CVideoUdpServer::Init(const kfc::CConfig& conf)
{
	CUServer::Init(conf);
	timerInit();
	return 0;
}
int CVideoUdpServer::OnInit(const kfc::CConfig& conf)
{
	try
	{
		m_tConf.iProcNum = s2i(conf["Main\\ProcessNum"]);
		m_tConf.sBindIP = conf["Main\\ServerIP"];
		m_tConf.sPort =  conf["Main\\ServerPort"];
		m_sAllowIP = conf["Main\\AllowIP"];

		string sRollLogPrefix = conf["Main\\RollLogPrefix"];
		int iMaxRollLogSize = s2i(conf["Main\\MaxRollLogSize"]);
		m_ptRollLog = new kfc::CRollLog();
		m_ptRollLog->Init(sRollLogPrefix, "", iMaxRollLogSize, 10);
	}
	catch(conf_not_find &e)
	{
		cerr << "catch conf_not_find:" << e.what() << endl;
		return -1;
	}
	catch(comm_error &e)
	{
		cerr << "catch comm_error:" << e.what() << endl;
		return -1;
	}
	return 0;
}

int CVideoUdpServer::OnDoProcess(const char* sRecvBuff,int iRecvSize)
{
	try{
		if((size_t)iRecvSize < sizeof(ClientHead))
		{
			return 0;
		}

		ClientHead *pClientHead = (ClientHead *)sRecvBuff;
		if(pClientHead->head == MAGIC_HEADER)
		{
			Logger::getInstance()->onReceive(pClientHead->battleId,sRecvBuff,iRecvSize);
		}else{
			Logger::getInstance()->onTimer();
		}

	}
	catch (std::exception& e)
	{
		*m_ptRollLog << error << "catch exception|" << e.what() << endl;
		return -1;
	}
	return 0;
}

