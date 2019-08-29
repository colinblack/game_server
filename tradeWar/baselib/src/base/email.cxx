
#include "socket.h"
#include "trans.h"
#include "ctime.h"
#include "basic.h"

#include "email.h"

int QQMail::send(const std::string& sNameSend, const std::string& sMailSend, const std::string& sMailRecv, const std::string& sTitle, const std::string& sContent, int iMailTime, const std::string& sHost, int iPort, int nTimeOut, const std::string& sHelo)
{
	struct CMD
	{
		CMD(CQQShowTcpSocketIO& stSocket, int nTimeOut) : m_stSocket(stSocket), m_nTimeOut(nTimeOut)
		{
		}
		int DO(const std::string& sSend)
		{
			std::string sRecv;
			if ((int)sSend.size() != m_stSocket.send_n(sSend, sSend.size(), m_nTimeOut))
			{
				return -1;
			}
			if (m_stSocket.recv_line(sRecv, m_nTimeOut) <= 0)
			{
				return -2;
			}
			int iCode = CTrans::STOI(sRecv);
			if (iCode > 400)
			{
				return -3;
			}
			return 0;
		}
		CQQShowTcpSocketIO& m_stSocket;
		int m_nTimeOut;
	};
	CQQShowTcpConnetor stConnector;		// 打开一个TCP连接
	
	if (0 != stConnector.connect(sHost, iPort, nTimeOut))
	{
		return -1;
	}
	
	// 发送请求信息
	CQQShowTcpSocketIO stSocket(stConnector.get_handle());	// 打开一个读写IO

	CMD xCmd(stSocket, nTimeOut);
	
	if (0 != xCmd.DO("helo "+sHelo+"\r\n"))
	{
		return -11;
	}

	if (0 != xCmd.DO("mail from:"+sMailSend+"\r\n"))
	{
		return -21;
	}

	if (0 != xCmd.DO("rcpt to:"+sMailRecv+"\r\n"))
	{
		return -31;
	}

	if (0 != xCmd.DO("data\r\n"))
	{
		return -41;
	}

	if (0 != xCmd.DO("From: "+sNameSend+" "+sMailSend+"\r\n"\
                     "To: "+sMailRecv+"\r\n"\
                     "Date: "+CTime::FormatTime("%a, %d %b %Y %H:%M:%S %z (CST)", iMailTime)+"\r\n"\
                     "Subject: "+sTitle+"\r\n"\
                     "Content-Type: text/html; charset=gb2312\r\n\r\n"))
	{
		return -42;
	}

	std::string sContentEscape(sContent);
	CBasic::StringReplace(sContentEscape, "\n.", "\n..");

	if (0 != xCmd.DO(sContentEscape+"\r\n.\r\n"))
	{
		return -43;
	}

	if (0 != xCmd.DO("quit\r\n"))
	{
		return -51;
	}

	return 0;
}

