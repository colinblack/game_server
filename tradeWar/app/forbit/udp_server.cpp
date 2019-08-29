#include "udp_server.h"
#include "kfc_parsepara.h"
#include "serverInc.h"

int CUdpServer::OnInit(const CConfig& conf)
{
	try
	{
		m_tConf.iProcNum = s2i(conf["Main\\ProcessNum"]);
		m_tConf.sBindIP = conf["Main\\ServerIP"];
		m_tConf.sPort =  conf["Main\\ServerPort"];
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


int CUdpServer::OnDoProcess(const char* sRecvBuff,int iRecvSize)
{
	try
		{
			string strRecvBuffer = string(sRecvBuff) ;
//			strRecvBuffer = kfc::trim_right(strRecvBuffer, "\r\n");
			*m_ptRollLog<< "recv_msg:" << strRecvBuffer << endl;

			kfc::CCgiPara para;
			para.Decode(sRecvBuff);
			map<string, string> mapPara = para.GetPairs();

			ChatMsg chatMsg;
			// uid=10003620&vip=10&lvl=&srvListen=192.168.100.254:10001&msg=32323
			chatMsg.uid       = mapPara["uid"];
			chatMsg.vip       = s2i(mapPara["vip"]);
			chatMsg.lvl       = s2i(mapPara["lvl"]);
			chatMsg.msg       = mapPara["msg"];
			chatMsg.srvListen = mapPara["srvListen"];
			chatMsg.time      = time(NULL);

			// 广告分析
			AdManager::getInstance()->analyzeChatMsg(chatMsg);

		}
		catch (std::exception& e)
		{
			*m_ptRollLog << error << "catch exception|" << e.what() << endl;
			return -1;
		}
		return 0;
}

