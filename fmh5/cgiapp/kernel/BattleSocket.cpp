/*
 * BattleSocket.cpp
 *
 *  Created on: 2016-9-17
 *      Author: Ralf
 */


#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "BattleSocket.h"
#include "ErrorUtil.h"
#include "ConfigManager.h"

map<unsigned, BattleSocket*> BattleSocket::m_map;

int BattleSocket::Send(unsigned server, CSG17Packet* packet)
{
	server = ConfigManager::Instance()->GetMainServer(server);
	if(!m_map.count(server))
		m_map[server] = new BattleSocket(server);
	if(m_map[server]->IsClosed() && m_map[server]->Connect() != 0)
		return R_ERROR;
	return m_map[server]->Send(packet);
}
int BattleSocket::Receive(unsigned server, CSG17Packet* packet)
{
	server = ConfigManager::Instance()->GetMainServer(server);
	if(!m_map.count(server) || m_map[server]->IsClosed())
		return R_ERROR;
	return m_map[server]->Receive(packet);
}

int BattleSocket::Connect()
{
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
int BattleSocket::Send(CSG17Packet* packet)
{
	CBuffer buffer(SG17_MAX_PACKET_SIZE);
	if(!packet->Encode(&buffer))
	{
		error_log(" packet encode failed");
		return R_ERR_DATA;
	}
	int ret = socket.Send(buffer.GetConstBuffer(), buffer.GetSize(), 0);
	if(ret <= 0)
	{
		error_log("send socket error ret=%d", ret);
		socket.Close();
		return R_ERR_REFUSE;
	}
	return 0;
}
int BattleSocket::Receive(CSG17Packet* packet)
{
	CBuffer buffer(SG17_MAX_PACKET_SIZE);
	int recvsize =  0;
	while(true)
	{
		recvsize += socket.Receive(buffer.GetNativeBuffer() + buffer.GetSize(), buffer.GetFreeCapacity());
		if(recvsize > 0)
		{
			buffer.SetSize(recvsize);
		}
		if (recvsize <= 0)
		{
			error_log("receive socket error");
			socket.Close();
			return R_ERR_REFUSE;
		}


		CBufferReader reader(&buffer);
		unsigned bodyLen = 0;
		unsigned short head = 0;
		if(!reader.GetUInt16(head))
		{
			error_log("receive socket error");
			socket.Close();
			return R_ERR_REFUSE;
		}

		if(!reader.GetUInt32(bodyLen))
		{
			error_log("receive socket error");
			socket.Close();
			return R_ERR_REFUSE;
		}

		if(recvsize >= (unsigned)(SG17_PACKET_HEADER_SIZE + bodyLen))
			break;
	}
	if(!packet->Decode(&buffer))
	{
		error_log("cpacket decode error");
		socket.Close();
		return R_ERR_DATA;
	}

	socket.Close();
	return 0;
}
