#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "UnixSocket.h"
#include "PollThread.h"
#include "MemCheck.h"
#include "Utils.h"
#include "Poller.h"
#include "commlog.h"

template<class T>
class CListener: public CPollerObject {
public:
	CListener(const char* addr, uint16_t port) : CPollerObject(NULL, -1) {
		owerThread = NULL;
		strncpy(bindAddr, addr, sizeof(bindAddr) - 1);
		bindPort = port;
		unixSock = 0;
		char buf[128];
		snprintf(buf, sizeof(buf), "%s:%u", addr, port);
		name = STRDUP(buf);
		window = 0;
	}
	CListener(const char* path) {
		owerThread = NULL;
		strncpy(bindAddr, path, sizeof(bindAddr) - 1);
		unixSock = 1;
		name = STRDUP(bindAddr);
		window = 0;
		bindPort = 0;
	}
	~CListener() {
		if (name) {
			if (unixSock && netfd >= 0 && name[0] == '/') {
				unlink(name);
			}
			FREE(name);
		}
	}
	void InputNotify(void) {
		int newfd = -1;
		socklen_t peerSize;
		struct sockaddr peer;
		while (true) {
			peerSize = sizeof(peer);
			newfd = accept(netfd, &peer, &peerSize);
			if (newfd == -1) {
				if (errno != EINTR && errno != EAGAIN) {
					error_log("[%s]accept failed, fd=%d, %m", name, netfd);
				}
				if (errno == EMFILE || errno == ENFILE) {
					error_log("max fds reached,rest all,%m");
				}
				break;
			}
			T* async = new T(owerThread, newfd);
			if (async->Attach() == -1) {
				delete async;
			}
			char peerAddr[20] = {0};
			uint32_t peerIp = 0;
			uint16_t peerPort = 0;
			Utils::fdinfo(newfd, peerAddr, peerIp, peerPort);
			info_log("accept fd=%d addr=%s port=%d", newfd, peerAddr, peerPort);
		}
	}
	int Attach(CPollThread *unit, int blog = 0) {
		if ((unixSock == 0 && (netfd = SockBind(bindAddr, bindPort, blog)) == -1)
		|| (unixSock == 1 && (netfd = UnixSockBind(bindAddr, blog)) == -1)) {
			return -1;
		}
		owerThread = unit;
		EnableInput();
		return AttachPoller(unit);
	}
	void SetRequestWindow(int w) {
		window = w;
	}
	int FD(void) const {
		return netfd;
	}
private:
	CPollThread* owerThread;
	int unixSock;
	uint16_t bindPort;
	char bindAddr[128];
	char *name;
	int window;
};
#endif
