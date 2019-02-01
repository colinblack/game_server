#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "unix_socket.h"
#include <listener.h>
//#include <client_unit.h>
#include <poll_thread.h>
#include <uvlog.h>
#include <memcheck.h>
#include "client_async.h"
#include "utils.h"
#include "config.h"


CListener::CListener (const char* path)
{
	strncpy (bindAddr, path, sizeof (bindAddr) - 1);
	unixSock = 1;
	name = STRDUP(bindAddr);
	window = 0;
	//outPeer = NULL;
}

CListener::CListener (const char* bindIp, uint16_t port)
	: CPollerObject (NULL, -1)
{
	strncpy (bindAddr, bindIp, sizeof (bindAddr) - 1);
	bindPort = port;
	unixSock = 0;
	char buf[128];
	snprintf(buf, sizeof(buf), "%s:%u", bindIp, port);
	name = STRDUP(buf);
	window = 0;
	//outPeer = NULL;
	
	//bind and listen
	//SockBind(bindIp,port,1024);
}

CListener::~CListener()
{
	if(name)
	{
		if(unixSock && netfd >= 0 && name[0]=='/')
		{
			unlink(name);
		}
		FREE(name);
	}
}

int CListener::Attach (CPollThread *unit, int blog)
{
	if ((unixSock == 0 && (netfd = SockBind (bindAddr, bindPort, blog)) == -1) ||
		(unixSock == 1  && (netfd = UnixSockBind (bindAddr, blog)) == -1))
			return -1;
	
	owerThread = unit;
	//outPeer = unit;
	EnableInput();
	return AttachPoller(unit);
}

void CListener::InputNotify (void)
{
	int newfd = -1;
	socklen_t peerSize;
	struct sockaddr peer;

	while (true)
	{
		peerSize = sizeof (peer);
		newfd = accept (netfd, &peer, &peerSize);

		if (newfd == -1)
		{
			if (errno != EINTR && errno != EAGAIN  )
				LOG_NOTICE("[%s]accept failed, fd=%d, %m", name, netfd);

			if(errno == EMFILE || errno == ENFILE){
				LOG_NOTICE("max fds reached,rest all,%m");
			}
			
			break;
		}
				
		CClientAsync* async = new CClientAsync(owerThread, newfd);
		if(async->Attach() == -1)
		{
			delete async;
		}
		
		//if(outPeer->ProcessIncoming(newfd, window) < 0)
		//	close(newfd);
		
		LOG_DEBUG("[%s]accept connection, fd=%d", name, newfd);
	}
}


