#ifndef _T_SERVER_H__
#define _T_SERVER_H__

/*******************************************************************************
	function:	tcp server 的基类
	author:	luckyxiang
	date:	2006.05.20
*******************************************************************************/
#include "bserver.h"

class CTServer:public CBaseServer
{
public:
	CTServer();
	virtual ~CTServer();
	
	virtual int Init(const CConfig& conf);	
	virtual void Run();								
protected:
	//子类只需实现以下三个纯虚函数即可

	//配置初始化
	virtual int  OnInit(const CConfig& conf) = 0;	
	//处理接收包的具体业务逻辑并生成响应包
	virtual int  OnDoProcess(char *sRecvBuffer, int iLength) = 0;

	//该函数可以根据需要重载
	virtual int  DoResponsePacket(int iRetCode			
								  , char *sSendBuffer
								  , int& iSendBufferSize
								  , int iMaxLength);	

	//网络相关函数
	int  CheckConnTimeout();			//检查链接是否超时
	int  AcceptNewConn();			//处理新链接
	int  ListenOnConnPort();				//监听端口
	int  SendConnBuffer(int iSocket);		//发送buffer
	int  ReadFromConn(int iSocket);			//读取buffer
	
protected:
	//连接相关变量
	CONN_CONTEXT m_tConnText[MAX_CONN_NUM];

	//响应包的buff
	char m_csRespPacket[MAX_PROTO_PACKET_SIZE];
	//响应包的长度
    	int m_iRespPacket;
	
};

#endif

