#ifndef _BASE_SERVER_H_
#define _BASE_SERVER_H_

/*******************************************************************************
	function:	 tcp/udp server 的基类接口
	author:	luckyxiang
	date:	2006.05.20
*******************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "kfc_comm.h"
#include "kfc_config_file.h"
#include "kfc_parsepara.h"
#include "kfc_epoll.h"
#include "kfc_log.h"

#include "server_comm.h"

#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace kfc;

class CBaseServer
{
public:
	CBaseServer();
	virtual ~CBaseServer();

	//子类实现
	virtual int Init(const CConfig& conf)=0;
	virtual void Run()=0;

	//公共函数
	virtual int InitProc(int iIndex);

	//进程相关函数
	void ForkChildProces();				//产生子进程
	int   ForkNewChild(int iChildIndex);	//产生某索引的子进程
	void CheckChildProcesStatus();	//检查子进程状态
	

	//底层函数
	void IgnorePipe();
	void InitDemo();
	int   AtoPort(const string sService, const string sProto);
	int   CreateSock(int iSocketType, unsigned uPort, int& iListenSocket,const string sBindAddr,int iReuseAddr,int iMaxConnection);
	int   SetNBlock(int iSock);
	int   GetPeerName(int fd,string & peer_address, uint16_t & peer_port);

public:
	kfc::CRollLog* m_ptRollLog;
	kfc::CDayLog* m_ptDayLog;

	map<string, CDayLog*> m_mapDayLog;

protected:
	//socket 变量
	int  m_iListenSock;

	//配置变量
	TCONFIG m_tConf;

	//业务进程相关变量(父进程使用)
	PROC_CONTEXT m_tProcText;

	//进程号
	int m_iProcID;

	string m_sAllowIP;

	kfc::CEPoller m_epoller;
};

#endif

