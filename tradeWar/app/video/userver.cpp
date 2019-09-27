#include "userver.h"

CUServer::CUServer()
{
}

CUServer::~CUServer()
{
}

int CUServer::Init(const kfc::CConfig& conf)
{
	int iRet;

	iRet = OnInit(conf);
	if(iRet)
	{
		return -1;
	}

	if(m_tConf.iProcNum > MAX_PROC_NUM)
	{
		cerr << "proc num by conf > MAX_PROC_NUM :" << MAX_PROC_NUM << endl;
		return -1;
	}
	
	iRet = Bind2UdpPort();
	if(iRet < 0)
	{
		return -1;
	}

	m_epoller.create(m_tConf.iMaxConn + 1024);
	m_epoller.add(m_iListenSock, EPOLLIN | EPOLLERR | EPOLLHUP);
	
	InitDemo();

	cout << "Init as a demo ...." << endl;
	
	ForkChildProces();
	return 0;
	
}


int CUServer::Bind2UdpPort()
{
	int iPort;

	if((iPort = AtoPort(m_tConf.sPort, "udp")) < 0)
	{
	 cerr << "Invalid Port: " << m_tConf.sPort << endl;
	    return -1;
	}

	cout << "Initiating UdpSocket Port= " << m_tConf.sPort << endl;
	CreateSock(SOCK_DGRAM, iPort, m_iListenSock, m_tConf.sBindIP, 1, 1);
	if (m_iListenSock< 0)
	{
	 cerr << "Initiating UdpSocket Fail!" << endl;
	    return -1;
	}

	SetNBlock(m_iListenSock);
	SetSocketRecBuf(m_iListenSock);

	cout << "Initiating UdpSocket OK!" << endl;
	return 0;
	
}

int CUServer::SetSocketRecBuf(int Sock){
	int nRecvBuf= 4 * 1024 * 1024;  //设置为4M
	int ret = setsockopt(Sock,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
	return ret;
}

int CUServer::ReadFromSvrPort()
{

	char sRecvBuff[MAX_PROTO_PACKET_SIZE],sErrMsg[1024];
	int iRecvLen,iRet,iAddrLen;
	struct sockaddr_in stAddr;

	memset(sRecvBuff,0,sizeof(sRecvBuff));
	memset(sErrMsg,0,sizeof(sErrMsg));
	iAddrLen = sizeof(stAddr);

	iRecvLen = recvfrom(m_iListenSock,sRecvBuff,sizeof(sRecvBuff),0,(struct sockaddr *)&stAddr,(socklen_t*)&iAddrLen);

	if(iRecvLen <= 0)
	{
		*m_ptRollLog << "the recv length is " << iRecvLen << endl;
		return -1;
	}
	
	char addr[INET_ADDRSTRLEN];
	string sSrcIp = inet_ntop(AF_INET,&(stAddr.sin_addr),addr,sizeof(addr));

	// -1 为不设ip限制
	if(m_sAllowIP.find("-1") == string::npos && m_sAllowIP.find(sSrcIp) == string::npos)
	{
		*m_ptRollLog << debug << "NOTICE:udp packet from not allowed ip:" << sSrcIp << endl;
		return 0;
	}

	iRet = OnDoProcess(sRecvBuff,iRecvLen);
	if(iRet != 0)
	{
		*m_ptRollLog << debug << "OnDoProcess fail!" << endl;
		return -1;
	}
	return 0;
}

void CUServer::Run()
{
	while(1)
	{
		// 处理请求的连接
		kfc::CEPollResult result = m_epoller.wait(1000);
		kfc::CEPollResult::iterator it = result.begin();

		for(; it != result.end(); it++)
		{
			//int fd = it->data.fd;
			int event = it->events;

			if(event & EPOLLIN) 
			{
				ReadFromSvrPort();
			} 

			if(event & (EPOLLERR | EPOLLHUP)) 
			{
				*m_ptRollLog << debug << "udp socket ERPOLLERR|HUP,exit" << endl;
				exit(0);
			}	
		}
	}
}

