#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "uvlog.h"
#include "utils.h"
#include "config.h"
#include "poll_thread.h"
#include "listener.h"
#include "db_logic.h"
#include "db_client_async.h"

using namespace std;

#define MAX_EPOLL_WATH_COUNT 1000
#define LISTEN_BACKLOG 1024

#include "Kernel.h"
#include "Common.h"

static void OnExit() {

}

int main(int argc, char** argv) {
	if (!Kernel::Init()) {
		fatal_log("[Kernel::Init fail][server=Toywar]");
		return -1;
	}

	if (!System::InitDaemon(NULL, OnExit)) {
		fatal_log("[System::InitDaemon fail][error=%d]", errno);
		return -1;
	}

	if (!DBLogic::init()) {
		return -1;
	}

	uint32_t maxClient = Config::GetIntValue("maxclient");
	if (maxClient == 0) {
		maxClient = MAX_EPOLL_WATH_COUNT;
	}

	CPollThread pThead("dbwriter", maxClient);
	pThead.InitializeThread(0);

	int port = Config::GetIntValue("port");
	const char *addr = Config::GetValue("ip").c_str();

	CListener<CDBClientAsync> listener(addr, port);
	if (listener.Attach(&pThead, LISTEN_BACKLOG)) {
		error_log("bind [%s:%d] failed\n", addr, port);
		exit(-1);
	}

	pThead.RunningThread();

	return 0;
}

