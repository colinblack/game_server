#include <sys/un.h>
#include <sys/socket.h>

static inline int IsUnixSocketPath(const char *path) {
	return path[0] == '/' || path[0] == '@';
}

static inline int InitUnixSocketAddress(struct sockaddr_un *addr, const char *path) {

	bzero(addr, sizeof(struct sockaddr_un));
	addr->sun_family = AF_LOCAL;
	strncpy(addr->sun_path, path, sizeof(addr->sun_path) - 1);
	socklen_t addrlen = SUN_LEN(addr);
	if (path[0] == '@')
		addr->sun_path[0] = '\0';
	return addrlen;
}

int SockBind(const char *addr, uint16_t port, int backlog);
int UdpSockBind(const char *addr, uint16_t port, int rbufsz, int wbufsz);
int UnixSockBind(const char *path, int backlog);

