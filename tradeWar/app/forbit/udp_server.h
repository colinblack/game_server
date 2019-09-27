#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include "userver.h"

class CUdpServer:public CUServer
{


public:
	static CUdpServer* getInstance(){
		static CUdpServer srv;
		return &srv;
	}
	~CUdpServer(){};

private:
	CUdpServer(){};

protected:
	virtual int OnInit(const CConfig& conf);                //子类实现
	virtual int OnDoProcess(const char* sRecvBuff,int iRecvSize);      //子类实现

};

#endif

