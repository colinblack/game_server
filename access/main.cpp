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
#include "proctitle.h"
#include "BattleManager.h"

using namespace std;

#define MAX_EPOLL_WATH_COUNT 10240
#define LISTEN_BACKLOG 1024


int main(int argc,char** argv){

	Utils::daemonInit(argc, argv);
	
	CConfig *cfg = CConfig::getInstance();
//	const char *procname=cfg->GetStrVal("SERVER","tag");
//	string strprocname("push: ");
//	strprocname+=procname;
//	init_proc_title(argc,argv);
//	set_proc_title(strprocname.c_str());
//	set_proc_name(strprocname.c_str());

	
	uint32_t maxClient = cfg->GetIntVal("SERVER","maxclient",MAX_EPOLL_WATH_COUNT);
	CPollThread pThead("access",maxClient);
	pThead.InitializeThread(0);

	int port = cfg->GetIntVal("SERVER", "port",8080);
	const char *addr = cfg->GetStrVal("SERVER", "ip");

	if(addr == NULL)
	{
		addr = "0.0.0.0";
	}

	CListener listener(addr,port);
	if(listener.Attach(&pThead, LISTEN_BACKLOG))
	{
		LOG_ERROR("bind [%s:%d] failed\n",addr,port);
		exit(-1);
	}

	BattleManager::getInstance()->setPollThread(&pThead);
	if(!BattleManager::getInstance()->init()){
		LOG_ERROR("BattleManager init fail");
		exit(-1);
	}

	pThead.RunningThread();

	return 0;
}


