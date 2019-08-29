/***********************************************************
	function:	霸域删广告服务
	author:	luckyxiang
	date:	2013.04.26
 ***********************************************************/

#include "tcp_server.h"
#include "VideoUdpServer.h"
#include <iostream>
#include "Logger.h"

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		cerr << "where is my conf file name?" << endl;
		cerr << "USAGE:" << argv[0] << " <conf file>" << endl;
		return -1;
	}

	kfc::CFileConfig _conf;
	bool bUseUdp = false;

	try
	{
		_conf.Init(argv[1]);

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
		pMyServer = CVideoUdpServer::getInstance();
		Logger::getInstance()->init(_conf);
	}
	else
	{
		pMyServer = new CTcpServer();
	}

	try
	{
		pMyServer->Init(_conf);
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
