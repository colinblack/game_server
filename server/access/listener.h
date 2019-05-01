#ifndef __LISTENER_H__
#define __LISTENER_H__
#include "poller.h"
#include "poll_thread.h"

int UnixSockBind (const char *path, int backlog=0);
int SockBind (const char *addr, uint16_t port, int backlog=0);
int UdpSockBind (const char *addr, uint16_t port, int rbufsz, int wbufsz);

class CDecoderUnit;
class CListener : public CPollerObject {
public:
	CListener (const char* addr, uint16_t port);
	CListener (const char* path);
	~CListener();
	virtual void InputNotify(void);
	virtual int Attach (CPollThread *, int blog=0);
	void SetRequestWindow(int w) { window = w; };
	int FD(void) const { return netfd; }

private:
	//CDecoderUnit *outPeer;
	CPollThread* owerThread;
	int unixSock;

	uint16_t bindPort;
	char bindAddr[128];
	char *name;
	int window;
}; 
#endif
