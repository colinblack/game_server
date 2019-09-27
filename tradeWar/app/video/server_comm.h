#ifndef _SERVER_COMM_H_
#define _SERVER_COMM_H_

/***********************************************************
	function:	server的基本宏定义和结构定义
	author:	luckyxiang
	date:	2006.05.20
***********************************************************/
#include <string>
#include <stdint.h>
#include <iostream>

//最大进程数
#define MAX_PROC_NUM 	20

//单次发送/接收buff大小
#define MAX_BUFF_SIZE 1024

//具体协议包最大长度
#define MAX_PROTO_PACKET_SIZE (0xF000 + 20)

//最大链接数,(socket从4开始,所以最大链接数应该是该数-4)
#define MAX_CONN_NUM	3096

//
#define RESP_MORE_DATA  0x14001

//每个socket对应一个结构
typedef struct _CONN_CONTEXT
{
	int 		iStatus;
	string 	sConnIp;
	uint16_t 	iConnPort;
	time_t 	iLastAccessTime;
	int 		iDisconnectPost;
	int 		iBytesToSend;
	char 		caSendBuffer[MAX_BUFF_SIZE];
	int 		iBytesReceived;
	char 		caRecvBuffer[MAX_BUFF_SIZE];
}CONN_CONTEXT;

//每个进程对应一个结构
typedef struct _PROC_CONTEXT
{
	int	iProcNum;						//进程数
	int	iaChildPid[MAX_PROC_NUM];		//子进程pid
}PROC_CONTEXT;

//配置信息结构
typedef struct _TCONFIG
{
//	string	sProcID;		//供TMON监控使用
	int 		iProcNum;	//进程数
	string	sBindIP;
	string	sPort;
	int		iTimeout;
	int		iReuseAddr;
	int		iMaxConn;
}TCONFIG;

enum
{
	CONN_DISCONNECTED = 0,
	CONN_CONNECTED = 1,
	CONN_DISCONNECT_POST = 2
};

//具体协议长度
//#define	MIN_PROTO_LEN 30
//#define	MAX_PROTO_LEN 300

#endif
