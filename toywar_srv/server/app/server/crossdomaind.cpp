/*
 * crossdomaind.cpp
 *
 *  Created on: 2012-3-21
 *      Author: dada
 */

#include "Kernel.h"

#define CONNECTION_TIMEOUT 30

class CCrossDomainServer : public CTcpServer
{

protected:

	CCrossDomainServer() : m_index(0) {}

public:

	static CCrossDomainServer *GetInstance()
	{
		static CCrossDomainServer server;
		return &server;
	}

	bool Initialize();
	virtual void OnChannelReceive(CTcpChannel *pChannel);
	virtual void OnConnect(CTcpChannel *pChannel);
	virtual void OnChannelClose(CTcpChannel *pChannel);
	virtual void OnIdle();
	void Reset();

private:

	int m_index;
	//CStaticBuffer<1000> m_abCrossDomain[2];
	CDanymicBuffer<1000> m_abCrossDomain[2];
	map<int, unsigned> m_connections;

};

static void OnExit()
{
	CCrossDomainServer::GetInstance()->Close();
}

static void OnReset()
{
	CCrossDomainServer::GetInstance()->Reset();
}

static bool ParseAddress(vector<CInternetAddress> &vecAddress, const string &sAddress)
{
	if(sAddress.empty())
	{
		return false;
	}
	vector<string> vecStrAddress;
	CBasic::StringSplitTrim(sAddress, ",", vecStrAddress);
	for(vector<string>::iterator itr = vecStrAddress.begin(); itr != vecStrAddress.end(); itr++)
	{
		CInternetAddress address;
		if(address.FromString(*itr))
		{
			vecAddress.push_back(address);
		}
	}
	return vecAddress.size() != 0;
}

bool CCrossDomainServer::Initialize()
{
	if(!Kernel::Init())
	{
		fatal_log("[Kernel::Init fail][server=CrossDomain]");
		return false;
	}
	vector<CInternetAddress> listenAddress;
	if(!ParseAddress(listenAddress, Config::GetValue("crossdomain_listen")))
	{
		fatal_log("[ParseAddress fail][server=CrossDomain]");
		return false;
	}
	int maxConn = TCP_SERVER_MAX_CONNECTIONS;
	Config::GetIntValue(maxConn, "crossdomain_max_conn");
	if(!CTcpServer::Initialize(listenAddress, maxConn))
	{
		fatal_log("[TcpServer::Initialize fail][server=CrossDomain]");
		return false;
	}
	Reset();
	if(!System::InitDaemon(OnReset, OnExit))
	{
		fatal_log("[System::InitDaemon fail][server=CrossDomain,error=%d]", errno);
		return false;
	}
	return true;
}

void CCrossDomainServer::OnChannelReceive(CTcpChannel *pChannel)
{
	if(pChannel == NULL)
	{
		return;
	}
	IBuffer *pBuffer = pChannel->GetReceiveData();
	static char s_requestCommand[] = "<policy-file-request/>";
	if(pBuffer->GetSize() < sizeof(s_requestCommand) - 1)
	{
		return ;
	}
	if(memcmp(pBuffer->GetConstBuffer(), s_requestCommand, sizeof(s_requestCommand) - 1) == 0)
	{
		if(!pChannel->SendData(m_abCrossDomain + m_index))
		{
			error_log("[SendData fail][action=CrossDomain,channelId=%d,remote=%s]",
					pChannel->GetChannelId(), pChannel->GetRemoteAddress()->ToString().c_str());
		}
	}
	pChannel->SetDataRead(pBuffer->GetSize());
	return ;
}

void CCrossDomainServer::OnConnect(CTcpChannel *pChannel)
{
	m_connections[pChannel->GetChannelId()] = Time::GetGlobalTime();
}

void CCrossDomainServer::OnChannelClose(CTcpChannel *pChannel)
{
	m_connections.erase(pChannel->GetChannelId());
}

void CCrossDomainServer::OnIdle()
{
	vector<int> expiredSessions;
	unsigned expiredTime = Time::GetGlobalTime() - CONNECTION_TIMEOUT;
	for(map<int, unsigned>::const_iterator itr = m_connections.begin(); itr != m_connections.end(); itr++)
	{
		if(itr->second < expiredTime)
		{
			expiredSessions.push_back(itr->first);
		}
	}
	for(vector<int>::iterator itr = expiredSessions.begin(); itr != expiredSessions.end(); itr++)
	{
		CloseChannel(*itr);
	}
}

void CCrossDomainServer::Reset()
{
	Config::Init(APP_CONFIG_PATH);
	string sCrossDomainFile = Config::GetValue("crossdomain_file");
	if(sCrossDomainFile.empty())
	{
		fatal_log("[crossdomain_config_error][path=%s]", sCrossDomainFile.c_str());
	}
	string sCrossDomain;
	int ret = File::Read(sCrossDomainFile, sCrossDomain);
	if(ret != 0)
	{
		fatal_log("[load_crossdomain_fail][ret=%d,path=%s]", ret, sCrossDomainFile.c_str());
	}
	m_abCrossDomain[1 - m_index].CopyFrom((const byte *)sCrossDomain.c_str(), sCrossDomain.size() + 1);
	m_index = 1 - m_index;
}

int main()
{
	if(!CCrossDomainServer::GetInstance()->Initialize())
	{
		printf("CrossDomain Server Initialize Error\n");
	}
	if(!CCrossDomainServer::GetInstance()->Run())
	{
		fatal_log("[CrossDomainServer::Run fail]");
	}
	return 0;
}

