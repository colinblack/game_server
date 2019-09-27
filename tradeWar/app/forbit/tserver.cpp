#include "tserver.h"

CTServer::CTServer()
{
	m_iRespPacket = 0;
	memset(m_csRespPacket,0,sizeof(m_csRespPacket));
}

CTServer::~CTServer()
{
}

//监听socket初始化并监听端口
int CTServer::ListenOnConnPort()
{
	int iPort;

	if ((iPort = AtoPort(m_tConf.sPort, "tcp")) < 0)
	{
		cerr << "Invalid Port: " << m_tConf.sPort << endl;
		return -1;
	}

	cout << "Initiating Listening Port= " << m_tConf.sPort << endl;
	CreateSock(SOCK_STREAM
			, iPort
			, m_iListenSock
			, m_tConf.sBindIP
			, m_tConf.iReuseAddr
			, m_tConf.iMaxConn);
	if (m_iListenSock < 0)
	{
		cerr << "Initiating Listening Fail!" << endl;
		return -1;
	}

	SetNBlock(m_iListenSock);

	cout << "Initiating Listening OK!" << endl;
	return 0;
}

int CTServer::SendConnBuffer(int iSocket)
{
	int iBytesSent;
	int i;

	if (m_tConnText[iSocket].iStatus == CONN_DISCONNECTED)
	{
		return 1;
	}

	*m_ptRollLog << debug << "[SendConnBuffer] iSocket=" << iSocket << endl;
	iBytesSent = send(iSocket,
					m_tConnText[iSocket].caSendBuffer,
					m_tConnText[iSocket].iBytesToSend
					, 0);
	if (iBytesSent < 0)
	{
		close(iSocket);
		m_tConnText[iSocket].iStatus = CONN_DISCONNECTED;
		return iBytesSent;
	}
	time(&(m_tConnText[iSocket].iLastAccessTime));

	for (i = iBytesSent; i < m_tConnText[iSocket].iBytesToSend;i++)
	{
		m_tConnText[iSocket].caSendBuffer[i - iBytesSent] = m_tConnText[iSocket].caSendBuffer[i];
	}
	m_tConnText[iSocket].iBytesToSend -= iBytesSent;
	if ((m_tConnText[iSocket].iBytesToSend == 0) && (m_tConnText[iSocket].iDisconnectPost != 0))
	{
		*m_ptRollLog << debug << "[SendConnBuffer] Send finished,and close socket " << iSocket << endl;
		close(iSocket);
		m_tConnText[iSocket].iStatus = CONN_DISCONNECTED;
	}
	return 0;
}

int CTServer::ReadFromConn(int iSocket)
{
	if (m_tConnText[iSocket].iStatus == CONN_DISCONNECTED)
	{
		return 0;
	}

	int iBytesReceived;
	int iRet;
	int iResponseRet;
	
	iBytesReceived = read(iSocket,
	                      &(m_tConnText[iSocket].caRecvBuffer[m_tConnText[iSocket].iBytesReceived]),
	                      sizeof(m_tConnText[iSocket].caRecvBuffer) - m_tConnText[iSocket].iBytesReceived - 1);
	if (iBytesReceived <= 0)
	{
		if ((iBytesReceived < 0) && (errno == EINTR))
		{
			*m_ptRollLog << error << "[ReadFromConn] socket "<< iSocket << ", read error..." << endl;
			return 0;
		}
		else
		{
			*m_ptRollLog << debug << "[ReadFromConn] socket " << iSocket << ", read finished..." << endl;
			close(iSocket);
			m_tConnText[iSocket].iStatus = CONN_DISCONNECTED;
			return iBytesReceived;
		}
	}

	time(&(m_tConnText[iSocket].iLastAccessTime));
	m_tConnText[iSocket].iBytesReceived += iBytesReceived;

	*m_ptRollLog << debug << "[ReadFromConn] socket " << iSocket << ", read " << iBytesReceived << " bytes" << endl;
	iRet = OnDoProcess(m_tConnText[iSocket].caRecvBuffer, iBytesReceived);
	if(iRet < 0)
	{
		close(iSocket);
		m_tConnText[iSocket].iStatus = CONN_DISCONNECTED;
		return iRet;
	}

	do
	{
		memset(m_tConnText[iSocket].caSendBuffer, 0x00, sizeof(m_tConnText[iSocket].caSendBuffer));
		iResponseRet = DoResponsePacket(iRet
									, m_tConnText[iSocket].caSendBuffer
									, m_tConnText[iSocket].iBytesToSend
									, MAX_BUFF_SIZE);
		if(iResponseRet == RESP_MORE_DATA)
		{
			while(m_tConnText[iSocket].iBytesToSend)
			{
				if(SendConnBuffer(iSocket))			//出错则不发送了
				{
					iResponseRet = -1;
					break;
				}
			}	
		}
	}while(iResponseRet == RESP_MORE_DATA);

	//清空socket接收buffer
	m_tConnText[iSocket].iBytesReceived = 0;
	memset(m_tConnText[iSocket].caRecvBuffer, 0, sizeof(m_tConnText[iSocket].caRecvBuffer));

	return iRet;
}

int CTServer::DoResponsePacket(int iRetCode
								, char * sSendBuffer
								, int& iSendBufferSize
								, int iMaxLength)
{
	//此处可以根据iRetCode作处理，可以子类扩展

	if(m_iRespPacket == 0)
	{
		return 0;
	}

	if(m_iRespPacket > iMaxLength)
	{
		memcpy(sSendBuffer, m_csRespPacket, iMaxLength);
		iSendBufferSize = iMaxLength;
		for(int i=0;i<m_iRespPacket-iMaxLength;i++)
		{
			m_csRespPacket[i] = m_csRespPacket[i+iMaxLength];
		}
		m_iRespPacket = m_iRespPacket - iMaxLength;
		return RESP_MORE_DATA;
	}
	else
	{
		memcpy(sSendBuffer, m_csRespPacket, m_iRespPacket);
		iSendBufferSize = m_iRespPacket;
		sSendBuffer[(iSendBufferSize)] = 0;
		
		//log 响应数据包
		//*m_ptDayLog << "Send:|" << string(sSendBuffer) << endl;

		memset(m_csRespPacket,0,sizeof(m_csRespPacket));			 //clear
		m_iRespPacket = 0;              
		return 0;
	}
}

int CTServer::AcceptNewConn()
{
	//trpc_debug_log("enter [AcceptNewConn]\n");
	struct sockaddr_in stSockAddr;
	int iSockAddrSize, iNewSock;

	iSockAddrSize = sizeof(stSockAddr);
	iNewSock = accept(m_iListenSock, (struct sockaddr *) &stSockAddr,( socklen_t*)&iSockAddrSize);

	//trpc_debug_log("iNewSock is %d\n", iNewSock);
	if (iNewSock > 0)
	{
		if (iNewSock >= MAX_CONN_NUM)
		{
			*m_ptRollLog << debug << "--- Too Many Connection," << iNewSock << endl;
			close(iNewSock);
			return 1;
		}

		string tmp_ip;
		uint16_t  tmp_port;
		GetPeerName(iNewSock, tmp_ip, tmp_port);

		if(m_sAllowIP.find(tmp_ip) == string::npos)
		{
			*m_ptRollLog << "--- not allow ip, fd=" << iNewSock << ",ip=" << tmp_ip << ",port=" << tmp_port << endl;
			close(iNewSock);
			return 1;
	 	}

		*m_ptRollLog << debug << "[AcceptNewConn] iNewSock=" << iNewSock << ", MaxConnNum=" << MAX_CONN_NUM 
			<< ",IP=" << tmp_ip <<",Port=" << tmp_port << endl;
	 
		SetNBlock(iNewSock);
		m_tConnText[iNewSock].iStatus = CONN_CONNECTED;
		time(&(m_tConnText[iNewSock].iLastAccessTime));
		m_tConnText[iNewSock].iDisconnectPost = 0;
		m_tConnText[iNewSock].iBytesToSend = 0;
		m_tConnText[iNewSock].iBytesReceived = 0;
		m_tConnText[iNewSock].sConnIp = tmp_ip;
		m_tConnText[iNewSock].iConnPort = tmp_port;

		m_epoller.add(iNewSock, EPOLLIN | EPOLLERR | EPOLLHUP );
	}
 
    return 0;
}

int CTServer::CheckConnTimeout()
{
	if(m_tConf.iTimeout <= 0)		//不需要检测超时
	{
		return 0;
	}

	time_t iCurTime;
	int i;

	time(&iCurTime);
	for (i = 0; i < MAX_CONN_NUM; i++)
	{
		if ((m_tConnText[i].iStatus != CONN_DISCONNECTED)&& (m_tConnText[i].iDisconnectPost == 0))
		{
			if ((iCurTime - m_tConnText[i].iLastAccessTime) > m_tConf.iTimeout)
			{
				*m_ptRollLog << "--- (" << i << ") Conn Timeout" << endl;
				close(i);
				m_tConnText[i].iStatus = CONN_DISCONNECTED;
			}
		}
	}
    return 0;
}

int CTServer::Init(const CConfig& conf)
{
	int iRet;

	//初始化,读入配置信息
	iRet = OnInit(conf);	
	if(iRet < 0)
	{
		 return -1;
	}	

	if (m_tConf.iProcNum > MAX_PROC_NUM)
	{
		cerr << "Error: ProcessNum by Conf > MAX_PROC_NUM :" << MAX_PROC_NUM << endl;
		return -1;
	}

	//监听端口
	iRet = ListenOnConnPort();
	if (iRet < 0)
	{
		return -1;
	}

	m_epoller.create(m_tConf.iMaxConn + 1024);
	m_epoller.add(m_iListenSock, EPOLLIN | EPOLLERR | EPOLLHUP);

	InitDemo();

	cout << "Initializing as a daemon..." << endl;

	ForkChildProces();
	
	//下面是子进程流程,父进程不到这里,循环监控子进程
	for (int i = 0; i < MAX_CONN_NUM; i++)
	{
		m_tConnText[i].iStatus = CONN_DISCONNECTED;
	}
	return 0;
}

//主执行函数
void CTServer::Run()
{
	while (1)
	{
		//处理请求的连接

		CheckConnTimeout();

		kfc::CEPollResult result = m_epoller.wait(1000);

		//int iCount = 0;
		for(kfc::CEPollResult::iterator it = result.begin(); it != result.end(); it++) 
		{
			int fd = it->data.fd;
			int event = it->events;

			if(fd == m_iListenSock) 
			{
				if(!(event & EPOLLIN)) 
				{
					*m_ptRollLog << error << "listen socket is fail,EXIT" << endl;
					exit(-1);
				}
				AcceptNewConn();
			}
			else 
			{

				if(event & EPOLLIN) 
				{
					ReadFromConn(fd);
					SendConnBuffer(fd);
				} 

				if(event & (EPOLLERR | EPOLLHUP)) 
				{
					close(fd);
					m_tConnText[fd].iStatus = CONN_DISCONNECTED;
				}
			}

			//iCount++;
		}

		//trpc_debug_log("I get %d events this time\n",iCount);
	}
	
}
