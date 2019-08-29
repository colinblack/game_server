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
#include "battle_manager.h"
#include "Kernel.h"
#include "client_async.h"
using namespace std;

#define MAX_EPOLL_WATH_COUNT 10240
#define LISTEN_BACKLOG 1024

int main(int argc, char** argv) {
	if (!Kernel::Init()) {
		fatal_log("[Kernel::Init fail][server=Toywar]");
		return -1;
	}
	if (!ServerConfig::getInstance()->Init(Config::GetValue(CONFIG_SERVER_CONFIG))) {
		fatal_log("[System::InitServerConfig fail]");
		return -1;
	}
	Utils::daemonInit(argc, argv);
	uint32_t maxClient = Config::GetIntValue("server_max_conn");
	if (maxClient == 0) {
		maxClient = MAX_EPOLL_WATH_COUNT;
	}
	CPollThread pThead("access", maxClient);
	pThead.InitializeThread(0);
	CInternetAddress address;
	if (!address.FromString(Config::GetValue("server_listen"))) {
		error_log("config server_listen format error:%s", Config::GetValue("server_listen").c_str());
		return false;
	}
	CListener<CClientAsync> listener(address.IP.c_str(), address.Port);
	if (listener.Attach(&pThead, LISTEN_BACKLOG)) {
		LOG_ERROR("bind [%s:%d] failed\n", address.IP.c_str(), address.Port);
		exit(-1);
	}
	BattleManager::getInstance()->setPollThread(&pThead);
	if (!BattleManager::getInstance()->init()) {
		LOG_ERROR("BattleManager init fail");
		exit(-1);
	}
	pThead.RunningThread();
	return 0;
}

