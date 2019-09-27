/*
 * VideoUdpServer.h
 *
 *  Created on: 2015年11月16日
 *      Author: Administrator
 */

#ifndef VIDEOUDPSERVER_H_
#define VIDEOUDPSERVER_H_

#include "userver.h"

class CVideoUdpServer: public CUServer {
public:
	virtual ~CVideoUdpServer();

	static CVideoUdpServer* getInstance(){
		static CVideoUdpServer srv;
		return &srv;
	}
public:
	bool timerInit();


private:
	CVideoUdpServer();

protected:
	virtual int Init(const kfc::CConfig& conf);
	virtual int OnInit(const kfc::CConfig& conf);                //子类实现
	virtual int OnDoProcess(const char* sRecvBuff,int iRecvSize);      //子类实现
};

#endif /* VIDEOUDPSERVER_H_ */
