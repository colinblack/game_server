#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"
#include "config.h"
#include "poll_thread.h"
#include "listener.h"
#include "client_async.h"
#include "all_server.h"
#include "Kernel.h"
#include "Common.h"

using namespace std;

static void OnExit() {
	stop = 1;
	AsrvServer::IsClosed = true;
	AsrvServer::getInstance()->onExit();
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

	if (!ServerConfig::getInstance()->Init(Config::GetValue(CONFIG_SERVER_CONFIG))) {
		fatal_log("[System::InitServerConfig fail]");
		return -1;
	}

	if (!AsrvServer::getInstance()->doInit()) {
		fatal_log("[RankServer::doInit fail][error=%d]", errno);
		return -1;
	}

	AsrvServer::getInstance()->RunningThread();

	return 0;
}

