/*
 * TcpServer.cpp
 *
 *  Created on: 2012-2-9
 *      Author: dada
 */

#include "TcpServer.h"
#include <sys/epoll.h>

#define EPOLL_WAIT_TIMEOUT 10
#define TCP_SERVER_STAT_INTERVAL 60
#define TCP_SERVER_ACTIVE_INTERVAL 10

CTcpServer::CTcpServer() :
	m_bRunning(false),
	m_listenCount(0),
	m_maxConn(0),
	m_lastFreeChannelId(0),
	m_fdEpoll(-1),
	m_lastNew(0)
{
}

CTcpServer::~CTcpServer()
{
	Close();
}

void* TimerThread(void* arg) {
	CTcpChannel* pChannel = (CTcpChannel*) arg;
	struct timeval timeOut;
	timeOut.tv_sec = 1;
	timeOut.tv_usec = 0;

	CPacket packet;
	packet.MainProtocolType = 7;
	packet.SubProtocolType = 1;
	packet.UserId = UID_MIN ;
	//CStaticBuffer<PACKET_HEADER_SIZE+1> buf;
	CDanymicBuffer<PACKET_HEADER_SIZE+1> buf;
	int ret = packet.Encode(&buf);
	fatal_log("ret=%d\n",ret);

	while (true) {
		timeOut.tv_sec = 1;
		timeOut.tv_usec = 0;

		if (select(0, NULL, NULL, NULL, &timeOut) == 0) {
			pChannel->SendData(&buf);
		}
	}

	return NULL;
}

bool CTcpServer::Initialize(const vector<CInternetAddress> &listenList, int maxConn)
{
	m_listenList = listenList;
	m_listenCount = m_listenList.size();
	m_maxConn = maxConn;
	return true;
}

bool CTcpServer::EnableOutput(CTcpChannel * pChannel, bool flag ){
	epoll_event ev;
	ev.data.fd = pChannel->GetChannelId();
	if(flag){
		ev.events = EPOLLIN | EPOLLERR | EPOLLHUP |  EPOLLOUT;
	}
	else{
		ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
	}

	if(epoll_ctl(m_fdEpoll, EPOLL_CTL_MOD, pChannel->GetSocket(), &ev) == -1)
	{
		fatal_log("EPOLL_CTL_MOD failed:[%d,%d] %m",flag,pChannel->GetSocket());
		return false;
	}	

	return true;
}

bool CTcpServer::Run()
{
	if(m_listenCount <= 0)
	{
		return false;
	}

	//init epoll
	int maxChannel = m_listenCount + m_maxConn;
	m_fdEpoll = epoll_create(maxChannel);
	if(m_fdEpoll == -1)
	{
		fatal_log("[epoll_create fail][error=%d]", errno);
		return false;
	}

	//创建监听Socket
	CTcpChannel::SetServer(this);
	m_lastFreeChannelId = m_listenCount - 1;
	for(int i = 0; i < m_listenCount; i++)
	{
		m_pChannels[i] = new CTcpChannel;
		if(!m_pChannels[i]->CreateServer(i, m_listenList[i]))
		{
			fatal_log("[CreateServer fail][error=%d,ip=%s,port=%d]",
					m_pChannels[i]->GetLastError(), m_listenList[i].IP.c_str(), (int)m_listenList[i].Port);
			close(m_fdEpoll);
			return false;
		}
		epoll_event evListen;
		evListen.data.fd = i;
		evListen.events = EPOLLIN | EPOLLERR | EPOLLHUP;
		if(epoll_ctl(m_fdEpoll, EPOLL_CTL_ADD, m_pChannels[i]->GetSocket(), &evListen) == -1)
		{
			fatal_log("[epoll_ctl add fail][type=listen,error=%d]", errno);
			close(m_fdEpoll);
			return false;
		}
	}

	/* ralf 20140319, fix me ,i don't know what is it used for
	CTcpChannel* pTimeChannel = GetSelfClientChannel();
	pthread_t pid;
	if (pthread_create(&pid, NULL, TimerThread, (void*) pTimeChannel) != 0) {
		error_log("start time thread failed,%m");
		return false;
	}
	*/

	//Run
	epoll_event *events = new epoll_event[maxChannel];
	if(events == NULL)
	{
		fatal_log("[new epoll_event fail][error=%d]", errno);
		close(m_fdEpoll);
		return false;
	}
	unsigned s_lastStatTime = 0, s_lastActiveTime = 0;
	m_bRunning = true;
	while(m_bRunning)
	{
		int nReady = epoll_wait(m_fdEpoll, events, maxChannel, EPOLL_WAIT_TIMEOUT);
		Time::UpdateGlobalTime();
		if(nReady != -1)
		{
			for(int i = 0; i < nReady; i++)
			{
				int cid = events[i].data.fd;
				if(!m_pChannels.count(cid))
				{
					error_log("[epoll data null][events=0x%08X]", events[i].events);
				}
				else if(m_pChannels[cid]->IsClosed())
				{
					error_log("[epoll socket closed][id=%d,events=0x%08X]", m_pChannels[cid]->GetSocket(), events[i].events);
				}
				else if(cid < m_listenCount)
				{
					//accept
					if((events[i].events & (EPOLLERR | EPOLLHUP)) != 0)
					{
						error_log("[listen socket error][id=%d,events=%d]", cid, events[i].events);
					}
					else
					{
						int acceptChannelId = GetFreeChannelId();
						if(acceptChannelId < 0)
						{
							fatal_log("[tcp connection overrun][maxconn=%d]", m_maxConn);
						}
						else
						{
							if(m_pChannels[acceptChannelId]->Accept(acceptChannelId, *m_pChannels[cid]))
							{
								epoll_event evConnect;
								evConnect.data.fd = acceptChannelId;
								evConnect.events = EPOLLIN | EPOLLERR | EPOLLHUP;	// | EPOLLET;
								if(epoll_ctl(m_fdEpoll, EPOLL_CTL_ADD, m_pChannels[acceptChannelId]->GetSocket(), &evConnect) == -1)
								{
									error_log("[epoll_ctl add fail][type=accept,error=%d,fd=%d]", errno, m_pChannels[acceptChannelId]->GetSocket());
									CloseChannel(acceptChannelId);
								}
								OnConnect(m_pChannels[acceptChannelId]);
								//DATA_LOG("tcp", m_pChannels[acceptChannelId].GetRemoteAddress()->ToString().c_str(),"accept", "ChannelId=%d", acceptChannelId);
							}
							else
							{
								error_log("[socket accept error][error=%d,id=%d,fd=%d]",
										m_pChannels[acceptChannelId]->GetLastError(), acceptChannelId, m_pChannels[acceptChannelId]->GetSocket());
							}
						}
					}
				}
				else
				{
					if(events[i].events & EPOLLIN){
						//recv
						if(m_pChannels[cid]->ReceiveData())
						{
							OnChannelReceive(m_pChannels[cid]);
						}
						else
						{
							CloseChannel(cid);
						}
					}

					if(events[i].events & EPOLLOUT){
						if(!m_pChannels[cid]->RealSend()){
							CloseChannel(cid);
						}
					}
				}
			}
		}
		else if(errno == EINTR)
		{
			error_log("[epoll_wait fail][error=EINTR]");
		}
		else
		{
			error_log("[epoll_wait fail][error=%d,fd=%d]", errno, m_fdEpoll);
			m_bRunning = false;
		}
		if(s_lastActiveTime + TCP_SERVER_ACTIVE_INTERVAL <= Time::GetGlobalTime())
		{
			s_lastActiveTime = Time::GetGlobalTime();
			if(m_lastNew < m_pFreeChannels.size())
			{
				vector<int> unkeep;
				set<int>::iterator iter=m_pFreeChannels.begin();
				for(int k=0;k<m_pFreeChannels.size()-m_lastNew;++k)
				{
					delete m_pChannels[*iter];
					unkeep.push_back(*iter);
					m_pChannels.erase(*iter);
					//debug_log("delete %u",*iter);
					++iter;
				}
				for(vector<int>::iterator ite=unkeep.begin();ite!=unkeep.end();++ite)
					m_pFreeChannels.erase(*ite);
			}
			m_lastNew = 0;
		}
		if(s_lastStatTime + TCP_SERVER_STAT_INTERVAL <= Time::GetGlobalTime())
		{
			s_lastStatTime = Time::GetGlobalTime();
			DATA_LOG("online_user","ip", "type", "%u|%d", s_lastStatTime, m_pChannels.size());

			int s_lastActiveNum = 0;
			for(map<int,CTcpChannel*>::iterator it=m_pChannels.begin();it!=m_pChannels.end();++it)
			{
				++s_lastActiveNum;
				if(s_lastActiveNum <= m_listenCount)
					continue;
				if(!it->second->IsClosed() && !it->second->IsActive())
				{
					//debug_log("dead %u",it->first);
					CloseChannel(it->first);
				}
			}
		}
		OnIdle();
	}

	info_log("[TcpServer Run End]");
	for(map<int,CTcpChannel*>::iterator it=m_pChannels.begin();it!=m_pChannels.end();++it)
	{
		CloseChannel(it->first);
		delete it->second;
	}
	close(m_fdEpoll);
	m_fdEpoll = -1;

	delete [] events;

	return true;
}

bool CTcpServer::Close()
{
	m_bRunning = false;
	return true;
}

bool CTcpServer::CloseChannel(int channelId)
{
	if(channelId < 0 || channelId >= m_listenCount + m_maxConn)
	{
		return false;
	}
	if(!m_pChannels.count(channelId))
		return false;

	CTcpChannel *pChannel = m_pChannels[channelId];
	if(!pChannel->IsClosed())
	{
		if(!pChannel->GetReceiveData()->IsEmpty())
		{
			error_log("[channel_close_unexpect][id=%d,data=%s]", channelId, pChannel->GetReceiveData()->ToString().c_str());
		}
		OnChannelClose(pChannel);
		epoll_event evDel;
		if(epoll_ctl(m_fdEpoll, EPOLL_CTL_DEL, pChannel->GetSocket(), &evDel) == -1)
		{
			error_log("[epoll_ctl del fail][error=%d,id=%d,fd=%d]", errno, channelId, pChannel->GetSocket());
		}
		pChannel->Close();
	}

	m_pFreeChannels.insert(channelId);
	//debug_log("close %u",channelId);
	return true;
}

bool CTcpServer::SendData(CPacket *pHead, IPacketSend *pBody)
{
	if(pHead == NULL)
	{
		return false;
	}
	if(pHead->ChannelId < m_listenCount || pHead->ChannelId >= m_listenCount + m_maxConn)
	{
		return false;
	}
	if(!m_pChannels.count(pHead->ChannelId))
		return false;

	if(m_pChannels[pHead->ChannelId]->IsClosed())
	{
		error_log("[channel_closed][channelid=%d,uid=%u,type=%d,mpn=%d,spn=%d,body=%u]",
				pHead->ChannelId, pHead->UserId, (int)pHead->PacketType, (int)pHead->MainProtocolType,
				(int)pHead->SubProtocolType, pHead->ProtocolBody.GetSize());
		return false;
	}
	if(pBody != NULL)
	{
		if(!pBody->Encode(&pHead->ProtocolBody))
		{
			error_log("[body_encode_error][uid=%u,type=%d,mpn=%d,spn=%d]",
					pHead->UserId, (int)pHead->PacketType, (int)pHead->MainProtocolType, (int)pHead->SubProtocolType);
			return false;
		}
		//DATA_LOG("tcp", m_pChannels[pHead->ChannelId].GetRemoteAddress()->ToString().c_str(), "send",
		//		"%s&Protocol&%s", pHead->ToString().c_str(), pBody->ToString().c_str());
	}
	else
	{
		//DATA_LOG("tcp", m_pChannels[pHead->ChannelId].GetRemoteAddress()->ToString().c_str(), "send",
		//		"%s&Protocol&", pHead->ToString().c_str());
	}
	//CBuffer sendBuffer(MAX_PACKET_SIZE);
	CDanymicBuffer<MAX_PACKET_SIZE> sendBuffer;
	pHead->SetWebSocket(m_pChannels[pHead->ChannelId]->IsWebSocket());
	if(!pHead->Encode(&sendBuffer))
	{
		error_log("[packet_encode_error][uid=%u,type=%d,mpn=%d,spn=%d,body=%u]",
				pHead->UserId, (int)pHead->PacketType, (int)pHead->MainProtocolType,
				(int)pHead->SubProtocolType, pHead->ProtocolBody.GetSize());
		return false;
	}
	if(!m_pChannels[pHead->ChannelId]->SendData(&sendBuffer))
	{
		CloseChannel(pHead->ChannelId);
		return false;
	}
	return true;
}

void CTcpServer::OnChannelReceive(CTcpChannel *pChannel)
{
	if(pChannel == NULL)
	{
		return;
	}
	uint32_t decodeSize = 0;
	do
	{
		CPacket packet;
		packet.SetWebSocket(pChannel->IsWebSocket());
		bool decodeSuccess = packet.Decode(pChannel->GetReceiveData());
		///TODO: decode size error auto close
		decodeSize = packet.GetDecodeSize();
		if(decodeSize > 0)
		{
			if(!decodeSuccess)
			{
				error_log("[Decode fail][channelId=%d,size=%u,packet=%s]",
						pChannel->GetChannelId(), pChannel->GetReceiveData()->GetSize(),
						pChannel->GetReceiveData()->ToString().c_str());
			}
			pChannel->SetDataRead(decodeSize);
		}
		if(decodeSuccess)
		{
			packet.ChannelId  = pChannel->GetChannelId();
			//DATA_LOG("tcp", pChannel->GetRemoteAddress()->ToString().c_str(), "recv", "Packet&%s", packet.ToString().c_str());
			OnReceive(&packet);
		}
	}while(decodeSize > 0);
	return ;
}


const CTcpChannel *CTcpServer::GetChannel(int channelId)
{
	if(channelId < 0 || channelId >= m_listenCount + m_maxConn)
	{
		return NULL;
	}
	if(!m_pChannels.count(channelId))
		return NULL;
	return m_pChannels[channelId];
}

int CTcpServer::GetFreeChannelId()
{
	++m_lastNew;

	if(m_pFreeChannels.size() > 0)
	{
		int id = *m_pFreeChannels.begin();
		m_pFreeChannels.erase(m_pFreeChannels.begin());
		//debug_log("rcl %u",id);
		return id;
	}

	int maxChannel = m_listenCount + m_maxConn;
	for(int i = 0; i < m_maxConn; i++)
	{
		m_lastFreeChannelId++;
		if(m_lastFreeChannelId >= maxChannel)
		{
			m_lastFreeChannelId = m_listenCount;
		}
		if(!m_pChannels.count(m_lastFreeChannelId))
		{
			m_pChannels[m_lastFreeChannelId] = new CTcpChannel;
			if(!m_pChannels[m_lastFreeChannelId])
				return -1;
			//debug_log("new %u",m_lastFreeChannelId);
			return m_lastFreeChannelId;
		}
	}
	return -1;
}
CTcpChannel* CTcpServer::GetSelfClientChannel(){
	int id = GetFreeChannelId();
	if(-1 == id){
		return NULL;
	}

	if(!m_pChannels[id]->CreateClient(id,m_listenList[0])){
		error_log("connect %s failed",m_listenList[0].ToString().c_str());
		return NULL;
	}

	epoll_event evConnect;
	evConnect.data.fd = id;
	evConnect.events = EPOLLIN | EPOLLERR | EPOLLHUP;	// | EPOLLET;
	if(epoll_ctl(m_fdEpoll, EPOLL_CTL_ADD, m_pChannels[id]->GetSocket(), &evConnect) == -1)
	{
		error_log("[epoll_ctl add fail][type=accept,error=%d,fd=%d]", errno, m_pChannels[id]->GetSocket());
		CloseChannel(id);
	}

	return m_pChannels[id];
}
