/***********************************************************
	function:	霸域删广告服务
	author:	luckyxiang
	date:	2013.04.26
 ***********************************************************/

#include "tcp_server.h"
#include "udp_server.h"
#include <iostream>
#include "serverInc.h"
#define CONF "../conf/app_config.conf"

int main(int argc, char * argv[])
{
//	if(argc < 2)
//	{
//		cerr << "where is my conf file name?" << endl;
//		cerr << "USAGE:" << argv[0] << " <conf file>" << endl;
//		return -1;
//	}

	kfc::CFileConfig _conf;
	bool bUseUdp = false;

	try
	{
//		_conf.Init(argv[1]);
		_conf.Init(CONF);

		bUseUdp = _conf["Main\\Protocol"].find("udp") != string::npos || _conf["Main\\Protocol"].find("UDP") != string::npos;
		cout << "USE PROTOCOL:" << (bUseUdp ? "UDP" : "TCP") << endl;
	}
	catch(conf_load_error &e)
	{
		cerr << "catch conf_load_error:" << e.what() << endl;
		return -1;
	}
	catch(conf_not_find &e)
	{
		cerr << "catch conf_not_find:" << e.what() << endl;
		return -1;
	}
	catch(comm_error &e)
	{
		cerr << "catch comm_error:" << e.what() << endl;
		return -1;
	}

	CBaseServer* pMyServer;
	if(bUseUdp)
	{
//		pMyServer = new CUdpServer();
		pMyServer = CUdpServer::getInstance();
	}
	else
	{
		pMyServer = new CTcpServer();
	}

	try
	{
		pMyServer->Init(_conf);
		AdManager::getInstance()->init(_conf);
		pMyServer->Run();
	}
	catch(runtime_error &e)
	{
		cerr << "catch runtime_error:" << e.what() << endl;
		delete pMyServer;
		return -1;
	}
	catch(exception &e)
	{
		cerr << "catch exception:" << e.what() << endl;
		delete pMyServer;
		return -1;
	}

	return 0;

}
