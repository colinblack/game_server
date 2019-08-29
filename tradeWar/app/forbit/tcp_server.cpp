#include "tcp_server.h"
#include "kfc_parsepara.h"

int CTcpServer::OnInit(const CConfig & conf)
{
	try
	{
		m_tConf.iMaxConn =  s2i(conf["Main\\MaxConnection"]);
		m_tConf.iProcNum = s2i(conf["Main\\ProcessNum"]);
		m_tConf.iTimeout = s2i(conf["Main\\ConnTimeOut"]);
		m_tConf.sBindIP = conf["Main\\ServerIP"];
		m_tConf.sPort = conf["Main\\ServerPort"];
		m_sAllowIP = conf["Main\\AllowIP"];

		string sRollLogPrefix = conf["Main\\RollLogPrefix"];
		int iMaxRollLogSize = s2i(conf["Main\\MaxRollLogSize"]);
		string sDayLogPrefix = conf["Main\\DayLogPrefix"];
		const string module = "";
		m_ptRollLog = new kfc::CRollLog();
		m_ptRollLog->Init(sRollLogPrefix, module, iMaxRollLogSize, 10);
		m_ptDayLog = new kfc::CDayLog();
		m_ptDayLog->Init(sDayLogPrefix, module);
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


bool CTcpServer::checkSvcId(int svcId)
{
	if(svcId >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CTcpServer::checkSex(int sex)
{
	if(0==sex || 1==sex)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CTcpServer::checkName(const string & name)
{
	size_t length = name.length();
	if(length<=32)
	{
		return true;
	}
	else
	{
		return false;
	}
}

