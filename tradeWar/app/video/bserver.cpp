#include "bserver.h"

CBaseServer::CBaseServer()
{
	//设置一些默认值,根据需要可以在初始化时修改
	m_tConf.iMaxConn = 1024;
	m_tConf.iProcNum = 3;
	m_tConf.iReuseAddr = 1;
	m_tConf.iTimeout = 60;
	m_ptRollLog = NULL;
	m_ptDayLog = NULL;
}

CBaseServer::~CBaseServer()
{
	delete m_ptRollLog;
	delete m_ptDayLog;
}

int CBaseServer::InitProc(int iIndex)
{
	//子类中实现
	//TODO
	return 0;
}

int CBaseServer::ForkNewChild(int iChildIndex)
{
	pid_t iPID;

	if ((iPID = fork()) < 0)
	{
		*m_ptRollLog << error << "Fail to fork process " << iChildIndex << "!" << endl;
	}
	else if (iPID == 0)
	{
		m_iProcID = iChildIndex;	//子进程

		InitProc(iChildIndex);
	}
	else
	{
		m_tProcText.iaChildPid[iChildIndex] = iPID;	//父进程
	}

	return iPID;
}

void CBaseServer::CheckChildProcesStatus()
{
    
	while (1)
	{
		sleep(30);		

//		*m_ptRollLog << debug << "check child process status!\n" << endl;

		for (int i = 1; i <= m_tProcText.iProcNum; i++)
		{
			if ((m_tProcText.iaChildPid[i] <= 0) || (kill(m_tProcText.iaChildPid[i], 0)))
			{
				//child process not exist, so fork
				*m_ptRollLog << debug << i << " Child(pid " << m_tProcText.iaChildPid[i] << ") not exist,fork new" << endl;
				if (ForkNewChild(i) == 0)
				{
					//child process
					return;
				}
			}
		}
	}
}

void CBaseServer::ForkChildProces()
{
	m_tProcText.iProcNum = 0;

	//进程编号从1开始,父进程为0
	for (int i = 1; i <= m_tConf.iProcNum; i++)
	{
		m_tProcText.iaChildPid[i] = 0;

		if (ForkNewChild(i) == 0)
		{
			return;             //child process
		}
		else
		{
			m_tProcText.iProcNum++;
		}
	}

	//父进程负责监控子进程的状态
	CheckChildProcesStatus();
}

void CBaseServer::IgnorePipe()
{
	struct sigaction sig;

	sig.sa_handler = SIG_IGN;
	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGPIPE,&sig,NULL);
}

void CBaseServer::InitDemo()
{
	pid_t pid;

	if ((pid = fork()) != 0)
	{
		exit(0);
	}

	setsid();

	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	IgnorePipe();

	if ((pid = fork()) != 0)
	{
		exit(0);
	}

	chdir("/");
	umask(0);
}

int CBaseServer::AtoPort(const string sService, const string sProto)
{
	int port;
	long int lport;
	struct servent *serv;
	char *errpos;

	/* First try to read it from /etc/services */
	serv = getservbyname(sService.c_str(), sProto.c_str());
	if (serv != NULL)
	{
		port = serv->s_port;
	}
	else 
	{ /* Not in services, maybe a number? */
		lport = strtol(sService.c_str(),&errpos,0);
		if ( (errpos[0] != 0) || (lport < 1) || (lport > 65535) )
		{
	  		return -1; /* Invalid port address */
		}
		port = htons(lport);
	}
	return port;
}

int CBaseServer::CreateSock(int iSocketType, unsigned uPort, int & iListenSocket, const string sBindAddr, int iReuseAddr, int iMaxConnection)
{
	struct sockaddr_in address;
	int listening_socket;
	/* Setup internet address information.
	This is used with the bind() call */
	memset((char *) &address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = uPort;

    	if(sBindAddr!="")
    	{
        	inet_pton(AF_INET,sBindAddr.c_str(),&address.sin_addr);
    	}
    	else
    	{
    		address.sin_addr.s_addr = htonl(INADDR_ANY);
    	}

	listening_socket = socket(AF_INET, iSocketType, 0);
	if (listening_socket < 0) 
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	iListenSocket= listening_socket;

	setsockopt(listening_socket, SOL_SOCKET, SO_REUSEADDR, (void*)(&(iReuseAddr)),sizeof(iReuseAddr));

	if (bind(listening_socket, (struct sockaddr *) &address,sizeof(address)) < 0) 
	{
		perror("bind");
		close(listening_socket);
		exit(EXIT_FAILURE);
	}

	if (iSocketType== SOCK_STREAM) 
	{
		listen(listening_socket, iMaxConnection); /* Queue up to max_connection connections before
		having them automatically rejected. */
	}
	return listening_socket;
}

int CBaseServer::SetNBlock(int iSock)
{
	int iFlags;

	iFlags = fcntl(iSock, F_GETFL, 0);
	iFlags |= O_NONBLOCK;
	iFlags |= O_NDELAY;
	fcntl(iSock, F_SETFL, iFlags);
	return 0;
}

int CBaseServer::GetPeerName(int fd,string & peer_address, uint16_t & peer_port)
{
    struct sockaddr name;
    struct sockaddr_in *p = (struct sockaddr_in *) &name;
    socklen_t namelen = sizeof(name);

    bzero(&name, sizeof(struct sockaddr));

    if(getpeername(fd, &name, &namelen))
    {
	return -1;
    }

    char addr[INET_ADDRSTRLEN];
    peer_address = inet_ntop(AF_INET, &p->sin_addr, addr, sizeof(addr));
    peer_port = ntohs(p->sin_port);

    return 0;
} 
