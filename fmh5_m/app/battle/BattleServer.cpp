#include "BattleServer.h"

CBaseMutex BattleServer::m_mutex;
pthread_t BattleServer::m_thread;
pthread_cond_t BattleServer::m_cond;
list<CFirePacket *> BattleServer::m_recv;
list<CFirePacket *> BattleServer::m_send;
set<int> BattleServer::m_closed;

static void OnReloadConfig()
{
	LogicManager::NeedReloadConfig = true;
}
static void OnExit()
{
	LogicManager::IsPreClosed = true;
}
static void OnSigNum(int signum, siginfo_t *info, void *myact)
{
	LogicManager::m_signum = signum;
}

static bool ParseAddress(vector<CInternetAddress> &vecAddress, const string &sAddress)
{
	if (sAddress.empty())
	{
		return false;
	}

	vector<string> vecStrAddress;
	CBasic::StringSplitTrim(sAddress, ",", vecStrAddress);
	for (vector<string>::iterator itr = vecStrAddress.begin(); itr != vecStrAddress.end(); itr++)
	{
		CInternetAddress address;
		if (address.FromString(*itr))
		{
			vecAddress.push_back(address);
		}
	}
	return vecAddress.size() != 0;
}

bool BattleServer::Initialize()
{
	if (!Kernel::Init())
	{
		fatal_log("[Kernel::Init fail][server=Toywar]");
		return false;
	}
	vector<CInternetAddress> listenAddress;
	//	string ip = "0.0.0.0";
	//	ip.append(":").append(String::i2s(BASE_SERVER_PORT + atoi(Config::GetValue(CONFIG_SRVID).c_str()) * 10 + atoi(Config::GetValue("process_id").c_str()))))
	if (!ParseAddress(listenAddress, Config::GetValue("server_listen")))
	{
		fatal_log("[ParseAddress fail]");
		return false;
	}
	int maxConn = TCP_SERVER_MAX_CONNECTIONS;
	Config::GetIntValue(maxConn, "server_max_conn");
	if (!CTcpServer::Initialize(listenAddress, maxConn))
	{
		fatal_log("[TcpServer::Initialize fail]");
		return false;
	}

	if (!System::InitDaemon())
	{
		fatal_log("[System::InitDaemon fail][error=%d]", errno);
		return false;
	}

	//CLog::startLogThread();

	return true;
}

void BattleServer::OnReceive(CFirePacket *pPacket)
{
	CScopedLock guard(m_mutex);
	m_recv.push_back(pPacket);
	pthread_cond_signal(&m_cond);
}

void *BattleServer::_run(void *args)
{
	System::InitSig(OnExit, OnReloadConfig, OnSigNum);
	CFirePacket *packet = NULL;
	while (1)
	{
		{
			CScopedLock guard(m_mutex);
			if (!packet)
				pthread_cond_wait(&m_cond, m_mutex.GetMutex());
			if (!m_recv.empty())
			{
				packet = *m_recv.begin();
				m_recv.pop_front();
			}
			else
				packet = NULL;
		}
		if (packet)
		{
			try
			{
				LogicManager::Instance()->process(packet);
			}
			catch (const std::exception &e)
			{
			}
			if (packet->m_msg)
				debug_log("process:%s", packet->m_msg->GetTypeName().c_str());
			DestoryObj<CFirePacket>(packet);
		}
	}
	pthread_exit(NULL);
}

bool BattleServer::AddSend(CFirePacket *packet)
{
	if (!packet->delmsg)
	{
		packet->delmsg = true;
		Message *m = packet->m_msg->New();
		m->MergeFrom(*packet->m_msg);
		packet->m_msg = m;
	}
	CScopedLock guard(m_mutex);
	m_send.push_back(packet);
	return true;
}

void BattleServer::OnIdle()
{
	CFirePacket *packet = NULL;
	do
	{
		{
			CScopedLock guard(m_mutex);
			if (!m_send.empty())
			{
				packet = *m_send.begin();
				m_send.pop_front();
			}
			else
				packet = NULL;
		}
		if (packet)
		{
			try
			{
				SendData(packet);
			}
			catch (const std::exception &e)
			{
			}
			//if(packet->m_msg) debug_log("send:%s", packet->m_msg->GetTypeName().c_str());
			DestoryObj<CFirePacket>(packet);
		}
	} while (packet);
}

void BattleServer::OnChannelClose(int channelId)
{
	CScopedLock guard(m_mutex);
	m_closed.insert(channelId);
}

bool BattleServer::IsChannelClosed(int channel)
{
	CScopedLock guard(m_mutex);
	bool c = false;
	if (m_closed.count(channel))
		c = true;
	m_closed.clear();
	return c;
}
