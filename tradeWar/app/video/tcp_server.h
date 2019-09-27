#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "tserver.h"

class CTcpServer:public CTServer
{
public:
	CTcpServer(){}
	~CTcpServer(){}
	
	virtual int  OnInit(const CConfig& conf) ;
	virtual int  OnDoProcess(char *sRecvBuffer, int iLength);

	static bool checkSvcId(int svcId);
	static bool checkSex(int sex);
	static bool checkName(const string& name);
};

#endif

