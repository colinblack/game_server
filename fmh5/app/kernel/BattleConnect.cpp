/*
 * BattleConnect.cpp
 *
 *  Created on: 2018年4月10日
 *      Author: Ralf
 */



#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "BattleConnect.h"
#include "ErrorUtil.h"

map<unsigned, BattleConnect*> BattleConnect::m_map;
CBaseMutex   BattleConnect::m_mutex;
pthread_t BattleConnect::m_thread;
pthread_cond_t BattleConnect::m_cond;
list<CFirePacket*> BattleConnect::m_send;

bool BattleConnect::InitThread()
{
	pthread_cond_init(&m_cond, NULL);
	return pthread_create(&m_thread, NULL, BattleConnect::_run, NULL) == 0;
}
void BattleConnect::DestoryThread()
{
	pthread_cancel(m_thread);
	pthread_cond_destroy(&m_cond);
}

void BattleConnect::AddSend(unsigned server, CFirePacket* packet)
{
	if(!packet->delmsg)
	{
		packet->delmsg = true;
		Message* m = packet->m_msg->New();
		m->MergeFrom(*packet->m_msg);
		packet->m_msg = m;
	}
	packet->uid = server;
	CScopedLock guard(m_mutex);
	m_send.push_back(packet);
	pthread_cond_signal(&m_cond);
}
void* BattleConnect::_run(void* args)
{
	CFirePacket *packet = NULL;
	while(1)
	{
		{
			CScopedLock guard(m_mutex);
			if(!packet)
				pthread_cond_wait(&m_cond, m_mutex.GetMutex());
			if(!m_send.empty())
			{
				packet = *m_send.begin();
				m_send.pop_front();
			}
			else
				packet = NULL;
		}
		if(packet)
		{
			try
			{
				Send(packet->uid, packet);
			}
			catch(const std::exception& e)
			{}
			//if(packet->m_msg) debug_log("connect:%s", packet->m_msg->GetTypeName().c_str());
			delete packet;
		}
	}
	pthread_exit(NULL);
}
int BattleConnect::Send(unsigned server, CFirePacket* packet)
{
	server = ConfigManager::Instance()->GetMainServer(server);
	if(!m_map.count(server))
		m_map[server] = new BattleConnect(server);
	if(m_map[server]->IsClosed() && m_map[server]->Connect() != 0)
		return R_ERROR;
	return m_map[server]->Send(packet);
}
/*
int BattleConnect::Receive(unsigned server, CFirePacket* packet)
{
	server = ConfigManager::Instance()->GetMainServer(server);
	if(!m_map.count(server) || m_map[server]->IsClosed())
		return R_ERROR;
	return m_map[server]->Receive(packet);
}
*/
int BattleConnect::Connect()
{
	if(Config::GetIntValue(CONFIG_SRVID) == ConfigManager::Instance()->GetMainServer(serverid))
		return R_ERROR;
	const Demo::Server& c = ConfigManager::Instance()->GetServer(serverid);

	if (!socket.Socket(SOCK_STREAM, 0, AF_INET))
	{
		error_log("create socket error");
		return R_ERROR;
	}

	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(c.host().c_str());
	server.sin_port = htons(c.port());
	server.sin_family = AF_INET;
	memset(server.sin_zero, 0x00, sizeof(server.sin_zero));

	if (!socket.Connect((struct sockaddr *) &server,sizeof(struct sockaddr)))
	{
		error_log("connect socket error,addr = %s, port=%u,errno = %d, errmsg = %s", c.host().c_str(),c.port(),errno, strerror(errno));
		socket.Close();
		return R_ERR_REFUSE;
	}

	struct timeval timeout;
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;
	if(!socket.SetSockOpt(SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(struct timeval))
	|| !socket.SetSockOpt(SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(struct timeval))
	|| !socket.SetBlock(true))
	{
		error_log("set socket wrong");
		socket.Close();
		return R_ERR_REFUSE;
	}

	return 0;
}
int BattleConnect::Send(CFirePacket* packet)
{
	CBuffer buffer(MAX_PACKET_SIZE);
	if(!packet->Encode(&buffer))
	{
		error_log(" packet encode failed");
		return R_ERR_DATA;
	}
	if(socket.Send(buffer.GetConstBuffer(), buffer.GetSize(), 0) < 0)
	{
		error_log("send socket error");
		socket.Close();
		return R_ERR_REFUSE;
	}
	return 0;
}
/*
int BattleConnect::Receive(CFirePacket* packet)
{
	CBuffer buffer(MAX_PACKET_SIZE);
	int recvsize = 0;
	recvsize = socket.Receive(buffer.GetNativeBuffer(), buffer.GetFreeCapacity());
	if (recvsize < 0)
	{
		error_log("receive socket error");
		socket.Close();
		return R_ERR_REFUSE;
	}
	buffer.SetSize(recvsize);

	if(!packet->Decode(&buffer))
	{
		error_log("cpacket decode error");
		socket.Close();
		return R_ERR_DATA;
	}

	return 0;
}
*/
