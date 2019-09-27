#ifndef _U_SERVER_H_
#define _U_SERVER_H_

/*******************************************************************************
	function:	udp server 的基类
	author:	luckyxiang
	date:	2006.05.20
*******************************************************************************/

#include "bserver.h"

class CUServer:public CBaseServer
{
public:
	CUServer();
	virtual ~CUServer();

	virtual int Init(const kfc::CConfig& conf);
	virtual void Run();
	
protected:
	//子类实现，一般读取配置
	virtual int OnInit(const CConfig& conf)=0;				
	//子类实现，业务自身处理逻辑
	virtual int OnDoProcess(const char* sRecvBuff,int iRecvSize)=0;	

	int Bind2UdpPort();
	int ReadFromSvrPort();
	int SetSocketRecBuf(int Sock);


protected:
	//连接相关变量
	CONN_CONTEXT m_tConnText[MAX_CONN_NUM];

	//响应包的buff
	char m_csRespPacket[MAX_PROTO_PACKET_SIZE];
	//响应包的长度
    int m_iRespPacket;
};

#endif

