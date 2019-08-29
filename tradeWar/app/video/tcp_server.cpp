#include "tcp_server.h"
#include "kfc_parsepara.h"

int CTcpServer::OnInit(const CConfig & conf)
{
	try
	{
		m_tConf.iProcNum = s2i(conf["Main\\ProcessNum"]);
		m_tConf.sBindIP = conf["Main\\ServerIP"];
		m_tConf.sPort = conf["Main\\ServerPort"];
		m_sAllowIP = conf["Main\\AllowIP"];

		string sRollLogPrefix = conf["Main\\RollLogPrefix"];
		int iMaxRollLogSize = s2i(conf["Main\\MaxRollLogSize"]);
		string sDayLogPrefix = conf["Main\\DayLogPrefix"];
		const string module = "";
		m_ptRollLog = new kfc::CRollLog();
		m_ptRollLog->Init(sRollLogPrefix, module, iMaxRollLogSize, 10);

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

	return 0;
}


int CTcpServer::OnDoProcess(char * sRecvBuffer, int iLength)
{
	return 0;
}


