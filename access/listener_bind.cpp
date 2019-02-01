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
#include <poll_thread.h>
#include <uvlog.h>

int SockBind (const char *addr, uint16_t port, int backlog)
{
	struct sockaddr_in inaddr;
	int reuse_addr = 1;
	int netfd;

	bzero (&inaddr, sizeof (struct sockaddr_in));
	inaddr.sin_family = AF_INET;
	inaddr.sin_port = htons (port);

	const char *end = strchr(addr, ':');
	if(end)
	{
		char *p = (char *)alloca(end-addr+1);
		memcpy(p, addr, end-addr);
		p[end-addr] = '\0';
		addr = p;
	}
	if(strcmp(addr, "*")!=0 &&
			inet_pton(AF_INET, addr, &inaddr.sin_addr) <= 0)
	{
		LOG_ERROR("invalid address %s:%d", addr, port);
		return -1;
	}

	if((netfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
	{
		LOG_ERROR("make tcp socket error, %m");
		return -1;
	}

	setsockopt (netfd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof (reuse_addr));
	if(bind(netfd, (struct sockaddr *)&inaddr, sizeof(struct sockaddr)) == -1)
	{
		LOG_ERROR("bind tcp %s:%u failed, %m", addr, port);
		close (netfd);
		return -1;
	}

	if(listen(netfd, backlog) == -1)
	{
		LOG_ERROR("listen tcp %s:%u failed, %m", addr, port);
		close (netfd);
		return -1;
	}

	LOG_INFO("listen on tcp %s:%u", addr, port);
	return netfd;
}

int UdpSockBind (const char *addr, uint16_t port, int rbufsz, int wbufsz)
{
	struct sockaddr_in inaddr;
	int netfd;

	bzero (&inaddr, sizeof (struct sockaddr_in));
	inaddr.sin_family = AF_INET;
	inaddr.sin_port = htons (port);

	const char *end = strchr(addr, ':');
	if(end)
	{
		char *p = (char *)alloca(end-addr+1);
		memcpy(p, addr, end-addr);
		p[end-addr] = '\0';
		addr = p;
	}
	if(strcmp(addr, "*")!=0 &&
			inet_pton(AF_INET, addr, &inaddr.sin_addr) <= 0)
	{
		LOG_ERROR ("invalid address %s:%d", addr, port);
		return -1;
	}

	if ((netfd = socket (AF_INET, SOCK_DGRAM, 0)) == -1) {
		LOG_ERROR ("make udp socket error, %m");
		return -1;
	}

	if (bind (netfd, (struct sockaddr *)&inaddr, sizeof(struct sockaddr)) == -1) {
		LOG_ERROR ("bind udp %s:%u failed, %m", addr, port);
		close (netfd);
		return -1;
	}

	if(rbufsz)
	setsockopt(netfd, SOL_SOCKET, SO_RCVBUF, &rbufsz, sizeof(rbufsz));
	if(wbufsz)
	setsockopt(netfd, SOL_SOCKET, SO_SNDBUF, &wbufsz, sizeof(wbufsz));

	LOG_INFO("listen on udp %s:%u", addr, port);
	return netfd;
}

int UnixSockBind (const char *path, int backlog)
{
	struct sockaddr_un unaddr;
	int netfd;
	
	socklen_t addrlen = InitUnixSocketAddress(&unaddr, path);
	if ((netfd = socket(PF_UNIX, SOCK_STREAM, 0)) == -1)  {
		LOG_ERROR ("%s", "make unix socket error, %m");
		return -1;
	}

	if (bind (netfd, (struct sockaddr *)&unaddr, addrlen) == -1) {
		LOG_ERROR ("bind unix %s failed, %m", path);
		close (netfd);
		return -1;
	}

	if (listen (netfd, backlog) == -1) {
		LOG_ERROR ("listen unix %s failed, %m", path);
		close (netfd);
		return -1;
	}

	LOG_INFO ("listen on unix %s, fd=%d", path, netfd);
	return netfd;
}

