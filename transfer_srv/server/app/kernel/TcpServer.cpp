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

#define htonll(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
#define ntohll(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))

CTcpServer::CTcpServer() :
	m_bRunning(false), m_listenCount(0), m_maxConn(0),
			m_lastFreeChannelId(0), m_fdEpoll(-1),m_lastNew(0) {
}

CTcpServer::~CTcpServer() {
	Close();
}

bool CTcpServer::Initialize(const vector<CInternetAddress> &listenList,
		int maxConn) {
	m_listenList = listenList;
	m_listenCount = m_listenList.size();
	m_maxConn = maxConn;
	return true;
}

bool CTcpServer::EnableOutput(CTcpChannel * pChannel, bool flag) {
	epoll_event ev;
	ev.data.fd = pChannel->GetChannelId();
	if (flag) {
		ev.events = EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLOUT;
	} else {
		ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
	}

	if (epoll_ctl(m_fdEpoll, EPOLL_CTL_MOD, pChannel->GetSocket(), &ev) == -1) {
		fatal_log("EPOLL_CTL_MOD failed:[%d,%d] %m",flag,pChannel->GetSocket());
		error_log("[epoll_ctl mod fail][error=%d,fd=%d]", errno, pChannel->GetSocket());
		return false;
	}
	return true;
}

bool CTcpServer::Run() {
	if (m_listenCount <= 0) {
		return false;
	}

	//init epoll
	int maxChannel = m_listenCount + m_maxConn;
	m_fdEpoll = epoll_create(maxChannel);
	if (m_fdEpoll == -1) {
		fatal_log("[epoll_create fail][error=%d]", errno);
		return false;
	}

	//创建监听Socket
	CTcpChannel::SetServer(this);
	m_lastFreeChannelId = m_listenCount - 1;
	for (int i = 0; i < m_listenCount; i++) {
		m_pChannels[i] = new CTcpChannel;
		if (!m_pChannels[i]->CreateServer(i, m_listenList[i])) {
			fatal_log("[CreateServer fail][error=%d,ip=%s,port=%d]",
					m_pChannels[i]->GetLastError(), m_listenList[i].IP.c_str(), (int)m_listenList[i].Port);
			close(m_fdEpoll);
			return false;
		}
		epoll_event evListen;
		evListen.data.fd = i;
		evListen.events = EPOLLIN | EPOLLERR | EPOLLHUP;
		if (epoll_ctl(m_fdEpoll, EPOLL_CTL_ADD, m_pChannels[i]->GetSocket(),
				&evListen) == -1) {
			fatal_log("[epoll_ctl add fail][type=listen,error=%d]", errno);
			close(m_fdEpoll);
			return false;
		}
	}

	//Run
	epoll_event *events = new epoll_event[maxChannel];
	if (events == NULL) {
		fatal_log("[new epoll_event fail][error=%d]", errno);
		close(m_fdEpoll);
		return false;
	}
	unsigned s_lastStatTime = 0,s_lastActiveTime = 0;
	m_bRunning = true;
	while (m_bRunning) {
		int nReady = epoll_wait(m_fdEpoll, events, maxChannel,
				EPOLL_WAIT_TIMEOUT);
		Time::UpdateGlobalTime();
		if (nReady != -1) {
			for (int i = 0; i < nReady; i++) {
				int cid = events[i].data.fd;
				if(!m_pChannels.count(cid)){
					error_log("[epoll data null][events=0x%08X]", events[i].events);
				} else if (m_pChannels[cid]->IsClosed()) {
					error_log("[epoll socket closed][id=%d,events=0x%08X]", m_pChannels[cid]->GetSocket(), events[i].events);
				} else if (cid < m_listenCount) {
					//accept
					if ((events[i].events & (EPOLLERR | EPOLLHUP)) != 0) {
						error_log("[listen socket error][id=%d,events=%d]", cid, events[i].events);
					} else {
						int acceptChannelId = GetFreeChannelId();
						if (acceptChannelId < 0) {
							fatal_log("[tcp connection overrun][maxconn=%d]", m_maxConn);
						} else {
							if(m_pChannels[acceptChannelId]->Accept(acceptChannelId, *m_pChannels[cid])){
								epoll_event evConnect;
								evConnect.data.fd = acceptChannelId;
								evConnect.events = EPOLLIN | EPOLLERR | EPOLLHUP; // | EPOLLET;
								if (epoll_ctl(m_fdEpoll,EPOLL_CTL_ADD,m_pChannels[acceptChannelId]->GetSocket(),&evConnect) == -1) {
									error_log("[epoll_ctl add fail][type=accept,error=%d,fd=%d]", errno, m_pChannels[acceptChannelId]->GetSocket());
									CloseTransferChannel(acceptChannelId);
								}
								OnConnect(m_pChannels[acceptChannelId]);
								//DATA_LOG("tcp", m_pChannels[acceptChannelId].GetRemoteAddress()->ToString().c_str(),"accept", "ChannelId=%d", acceptChannelId);
							} else {
								error_log("[socket accept error][error=%d,id=%d,fd=%d]",
										m_pChannels[acceptChannelId]->GetLastError(), acceptChannelId, m_pChannels[acceptChannelId]->GetSocket());
							}
						}
					}
				} else {
					bool colse = true;
					if (events[i].events & EPOLLIN) {
						if (m_pChannels[cid]->ReceiveData()) {
								colse = false;
								if(m_pChannels[cid]->isFrontChannel()&&m_pChannels[cid]->IsFirst())
								{
									if(!CreateTransferChannel(m_pChannels[cid]))
										continue;
								}
								OnTransferReceive(cid);
						}
					}
					if (events[i].events & EPOLLOUT) {
						colse = !m_pChannels[cid]->RealSend() ;
					}
					if(colse)
					{
						CloseTransferChannel(cid);
					}

				}
			}
		} else if (errno == EINTR) {
			error_log("[epoll_wait fail][error=EINTR]");
		} else {
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
			DATA_LOG("online_user","ip", "type", "%u|%d", s_lastStatTime, m_pChannels.size()/2);

			int s_lastActiveNum = 0;
			for(map<int,CTcpChannel*>::iterator it=m_pChannels.begin();it!=m_pChannels.end();++it)
			{
				++s_lastActiveNum;
				if(s_lastActiveNum <= m_listenCount)
					continue;
				if(!it->second->IsClosed() && !it->second->IsActive())
				{
					//debug_log("dead %u",it->first);
					CloseTransferChannel(it->first);
				}
			}
		}
		OnIdle();
	}

	info_log("[TcpServer Run End]");
	for(map<int,CTcpChannel*>::iterator it=m_pChannels.begin();it!=m_pChannels.end();++it)
	{
		CloseTransferChannel(it->first);
		delete it->second;
	}
	close(m_fdEpoll);
	m_fdEpoll = -1;

	delete[] events;

	return true;
}

bool CTcpServer::Close() {
	m_bRunning = false;
	return true;
}

bool CTcpServer::CloseChannel(int channelId) {
	if (channelId < 0 || channelId >= m_listenCount + m_maxConn) {
		return false;
	}
	if(!m_pChannels.count(channelId))
		return false;

	CTcpChannel *pChannel = m_pChannels[channelId];
	if (!pChannel->IsClosed()) {
		//error_log("CloseChannel | channelId=%d,IsFront=%d",channelId,pChannel->IsFront());
		if (!pChannel->GetReceiveData()->IsEmpty()) {
			error_log("[channel_close_unexpect][id=%d,data=%s]", channelId, pChannel->GetReceiveData()->ToString().c_str());
		}
		OnChannelClose(pChannel);
		epoll_event evDel;
		if (epoll_ctl(m_fdEpoll, EPOLL_CTL_DEL, pChannel->GetSocket(), &evDel)
				== -1) {
			error_log("[epoll_ctl del fail][error=%d,id=%d,fd=%d]", errno, channelId, pChannel->GetSocket());
		}
		pChannel->Close();
	}

	m_pFreeChannels.insert(channelId);
	//debug_log("close %u",channelId);
	return true;
}

int CTcpServer::CloseTransferChannel(int channelId){
	int rlt = -1;
	if (channelId < 0 || channelId >= m_listenCount + m_maxConn) {
		return rlt;
	}
	if(!m_pChannels.count(channelId))
		return rlt;

	bool isFront = m_pChannels[channelId]->IsFront();
	CloseChannel(channelId);

	map<int ,int >::iterator l_it1;
	map<int ,int >::iterator l_it2;
	if(isFront)
	{
		map<int ,int >::iterator l_it1 =m_transfer1.find(channelId);
		if(l_it1 != m_transfer1.end())
		{
			map<int ,int >::iterator l_it2 =m_transfer2.find(l_it1->second);
			if(l_it2 != m_transfer2.end())
				m_transfer2.erase(l_it2);
			CloseChannel(l_it1->second);
			rlt = l_it1->second;
			m_transfer1.erase(l_it1);
		}
		else
		{
			error_log("CloseTransferChannel | channelId=%d,IsFront=1",channelId);
		}
	}
	else
	{
		map<int ,int >::iterator l_it2 =m_transfer2.find(channelId);
		if(l_it2!=m_transfer2.end())
		{
			map<int ,int >::iterator l_it1 =m_transfer1.find(l_it2->second);
			if(l_it1 != m_transfer1.end())
				m_transfer1.erase(l_it1);
			CloseChannel(l_it2->second);
			rlt = l_it2->second;
			m_transfer2.erase(l_it2);
		}
		else
		{
			error_log("CloseTransferChannel | channelId=%d,IsFront=0",channelId);
		}
	}

	return rlt;
}

bool CTcpServer::SendData(CPacket *pHead, IPacketSend *pBody) {
	if (pHead == NULL) {
		return false;
	}
	if (pHead->ChannelId < m_listenCount || pHead->ChannelId >= m_listenCount
			+ m_maxConn) {
		return false;
	}
	if(!m_pChannels.count(pHead->ChannelId))
		return false;

	if (m_pChannels[pHead->ChannelId]->IsClosed()) {
		error_log("[channel_closed][channelid=%d,uid=%u,type=%d,mpn=%d,spn=%d,body=%u]",
				pHead->ChannelId, pHead->UserId, (int)pHead->PacketType, (int)pHead->MainProtocolType,
				(int)pHead->SubProtocolType, pHead->ProtocolBody.GetSize());
		return false;
	}
	if (pBody != NULL) {
		if (!pBody->Encode(&pHead->ProtocolBody)) {
			error_log("[body_encode_error][uid=%u,type=%d,mpn=%d,spn=%d]",
					pHead->UserId, (int)pHead->PacketType, (int)pHead->MainProtocolType, (int)pHead->SubProtocolType);
			return false;
		}
		//DATA_LOG("tcp", m_pChannels[pHead->ChannelId].GetRemoteAddress()->ToString().c_str(), "send",
		//		"%s&Protocol&%s", pHead->ToString().c_str(), pBody->ToString().c_str());
	} else {
		//DATA_LOG("tcp", m_pChannels[pHead->ChannelId].GetRemoteAddress()->ToString().c_str(), "send",
		//		"%s&Protocol&", pHead->ToString().c_str());
	}
	//CBuffer sendBuffer(MAX_PACKET_SIZE);
	CDanymicBuffer<MAX_PACKET_SIZE> sendBuffer;
	if (!pHead->Encode(&sendBuffer)) {
		error_log("[packet_encode_error][uid=%u,type=%d,mpn=%d,spn=%d,body=%u]",
				pHead->UserId, (int)pHead->PacketType, (int)pHead->MainProtocolType,
				(int)pHead->SubProtocolType, pHead->ProtocolBody.GetSize());
		return false;
	}
	if (!m_pChannels[pHead->ChannelId]->SendData(&sendBuffer)) {
		CloseTransferChannel(pHead->ChannelId);
		return false;
	}
	return true;
}

void CTcpServer::OnChannelReceive(CTcpChannel *pChannel) {
	if (pChannel == NULL) {
		return;
	}
	uint32_t decodeSize = 0;
	do {
		CPacket packet;
		bool decodeSuccess = packet.Decode(pChannel->GetReceiveData());
		///TODO: decode size error auto close
		decodeSize = packet.GetDecodeSize();
		if (decodeSize > 0) {
			if (!decodeSuccess) {
				error_log("[Decode fail][channelId=%d,size=%u,packet=%s]",
						pChannel->GetChannelId(), pChannel->GetReceiveData()->GetSize(),
						pChannel->GetReceiveData()->ToString().c_str());
			}
			pChannel->SetDataRead(decodeSize);
		}
		if (decodeSuccess) {
			packet.ChannelId = pChannel->GetChannelId();
			//DATA_LOG("tcp", pChannel->GetRemoteAddress()->ToString().c_str(), "recv", "Packet&%s", packet.ToString().c_str());
			OnReceive(&packet);
		}
	} while (decodeSize > 0);
	return;
}

bool CTcpServer::CreateTransferChannel(CTcpChannel *pChannel){
	int id  = pChannel-> GetChannelId();
	int byteRecv = pChannel ->GetReceiveData()->GetSize();
	byte buf[1024] = { 0 };
	int len = byteRecv > sizeof(buf) ? sizeof(buf) : byteRecv;
	pChannel ->GetReceiveData()->GetData(buf, len, 0);

	if(!pChannel->IsWebSocket() && strstr((char*)buf, "GET ") == (char*)buf)//websocket shake hand
	{
		pChannel->SetIsWebSocket(true);

        string k((char*)buf), b("Sec-WebSocket-Key:"), e("\r");
        if(k.find(b) == string::npos){
			error_log("[websocket key error]");
			CloseChannel(id);
			return false;
        }
        k = k.substr(k.find(b) + b.length());
        if(k.find(e) == string::npos){
			error_log("[websocket value error]");
			CloseChannel(id);
			return false;
        }
        k = k.substr(0, k.find(e));
        while(k.find(" ") != string::npos)
            k.erase(k.find(" "), 1);

		string magic = k + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
		string sha = Crypt::Sha1Raw(magic);
		string rkey;
		Crypt::Base64Encode(rkey, sha);

		string res = "HTTP/1.1 101 Switching Protocols\r\n";
		res.append("Upgrade: websocket\r\n");
		res.append("Connection: upgrade\r\n");
		res.append("Sec-WebSocket-Accept: ");
		res.append(rkey);
		res.append("\r\n\r\n");

		CDanymicBuffer<1000> buffer;
		CBufferWriter writer(&buffer);
		writer.AppendBytes((byte*)res.c_str(), res.size());
		pChannel->SendData(&buffer);

		pChannel->GetReceiveData()->Clear();
		//debug_log("websocket shake hand skey=%s,rkey=%s",skey.c_str(),rkey.c_str());
		return false;
	}

	pChannel->SetIsFirst(false);
	if(pChannel->IsWebSocket())
	{
		if((buf[0] & 0x80) != 0x80)
		{
			error_log("[websocket fin error]");
			CloseChannel(id);
			return false;
		}
		if((buf[0] & 0x0F) != 0x02)
		{
			error_log("[websocket opcode error]");
			CloseChannel(id);
			return false;
		}
		if((buf[1] & 0x80) != 0x80)
		{
			error_log("[websocket mask error]");
			CloseChannel(id);
			return false;
		}

		int skip, l;
		char mask[4];
		char c = buf[1] & 0x7F;
		if(c == 126){
			skip = 8;
			l = ntohs(*(uint16_t*)(buf + 2));
			memcpy(mask, buf + 4, 4);
		}
		else if(c == 127){
			skip = 14;
			l = ntohll(*(uint64_t*)(buf + 2));
			memcpy(mask, buf + 10, 4);
		}
		else{
			skip = 6;
			l = c;
			memcpy(mask, buf + 2, 4);
		}

		if(l + skip <= len){
			for(int i=0;i<l;++i)
				buf[i + skip] = buf[i + skip] ^ mask[i % 4];
		}

		//debug_log("websocket first %s", (char*)(buf+skip));
	}

	char* pos1 = strstr((char*) buf, "\r\n\r\n");
	char* pos2 = strstr((char*) buf, "serverid:");
	if(pos2 == NULL || !pos2 ||!pos1)
	{
		CloseChannel(id);
		return false;
	}
	char temp[100] = { 0 };
	memcpy(temp, (byte*) pos2 + 9, (byte*) pos1 - (byte*) pos2-9); //从serverid：位置开始取，仅取数值部分
	string serverid = string(temp);
	string tcpserver = Config::GetValue(serverid.c_str());
	int cport = 0;
	if(tcpserver.empty())
	{
		tcpserver = Config::GetValue("default");
		cport = atoi(serverid.c_str());
	}
	size_t pos = tcpserver.find(':');
	string host = tcpserver.substr(0, pos);
	string port = tcpserver.substr(pos + 1, tcpserver.length() - pos - 1);
	int sport = atoi(port.c_str()) + cport;
	CInternetAddress address = CInternetAddress(host.c_str(), sport);
	int	transferChannelId = GetFreeChannelId();
	if(transferChannelId < 0)
	{
		fatal_log("[tcp connection overrun][maxconn=%d]", m_maxConn);
		CloseChannel(id);
		return false;
	}
	else
	{
		if(!m_pChannels[transferChannelId]->CreateClient(transferChannelId, address, NULL))
		{
			CloseChannel(transferChannelId);
			CloseChannel(id);
			error_log("create client error %m serverid=%s,transferid=%d,host=%s,port=%d",serverid.c_str(),transferChannelId,host.c_str(),sport);
			return false;
		}
		m_pChannels[transferChannelId]->setFront(false);
		epoll_event evConnect;
		evConnect.data.fd = transferChannelId;
		evConnect.events = EPOLLIN | EPOLLERR | EPOLLOUT | EPOLLHUP; // | EPOLLET;
		if (epoll_ctl(m_fdEpoll, EPOLL_CTL_ADD,m_pChannels[transferChannelId]->GetSocket(), &evConnect) == -1) {
			error_log("[epoll_ctl add fail][type=create,error=%d,fd=%d]", errno, m_pChannels[transferChannelId]->GetSocket());
			CloseTransferChannel(transferChannelId);
			CloseChannel(id);
			return false;
		}
		m_transfer1.insert(pair<int, int> (id, transferChannelId));
		m_transfer2.insert(pair<int, int> (transferChannelId, id));
	}

	if(pChannel->IsWebSocket())//send first to chat to inform websocket
	{
		pChannel->GetReceiveData()->Clear();
		string t("websocket\r\n\r\n");
		pChannel->GetReceiveData()->Append((const byte *)t.c_str(), t.size());
	}

	return true;
}



void CTcpServer::OnTransferReceive(int id) {
	int	transferChannelId = m_transfer1.find(id) == m_transfer1.end() ?(m_transfer2.find(id) == m_transfer2.end()?-1: m_transfer2.find(id)->second ): m_transfer1.find(id)->second;
	if(transferChannelId<0)
	{
		CloseTransferChannel(id);
		return;
	}
	if (m_pChannels[transferChannelId]->SendData(m_pChannels[id]->GetReceiveData())) {
		m_pChannels[id]->GetReceiveData()->Remove(0,m_pChannels[id]->GetReceiveData()->GetSize());
	}
	else
	{
		error_log("[SendData][error=%d,id=%d,fd=%d,fromid=%d,fromfd=%d]", errno,id, m_pChannels[transferChannelId]->GetSocket(),id,m_pChannels[id]->GetSocket());
		CloseTransferChannel(transferChannelId);
		return;
	}
}

const CTcpChannel *CTcpServer::GetChannel(int channelId)  {
	if (channelId < 0 || channelId >= m_listenCount + m_maxConn) {
		return NULL;
	}
	if(!m_pChannels.count(channelId))
		return NULL;
	return m_pChannels[channelId];
}

int CTcpServer::GetFreeChannelId() {
	++m_lastNew;

	if(m_pFreeChannels.size() > 0)
	{
		int id = *m_pFreeChannels.begin();
		m_pFreeChannels.erase(m_pFreeChannels.begin());
		//debug_log("rcl %u",id);
		return id;
	}

	int maxChannel = m_listenCount + m_maxConn;
	for (int i = 0; i < m_maxConn; i++) {
		m_lastFreeChannelId++;
		if (m_lastFreeChannelId >= maxChannel) {
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
