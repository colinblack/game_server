/*
 * BattleLogWriter.cpp
 *
 *  Created on: 2015年11月16日
 *      Author: aaron
 */

#include "BattleLogWriter.h"

CVideoDataWriter::CVideoDataWriter() :_fd(0),lastTime(0),m_isBattleOver(false){
}

CVideoDataWriter::~CVideoDataWriter() {
	if(_fd > 0)
	{
		close(_fd);
	}
}


bool CVideoDataWriter::init(const string &prefix, uint64_t battleId)
{
	char sBattleId[128]={0};
    snprintf(sBattleId,sizeof(sBattleId),"%llu", battleId);

	_filename = prefix + sBattleId;
	_fd = open(_filename.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(_fd < 0)
	{
		return false;
	}

	return true;
}

void CVideoDataWriter::onReceive(const char *sRecvBuff,size_t iRecvSize)
{
	ClientHead *pClientHead = (ClientHead*)sRecvBuff;
	if(pClientHead->bodyLen == 0) // 空包表示战场结束
	{
		m_isBattleOver = true;
		return ;
	}

	list<ReceiveBuffer>::iterator it = m_buffer.begin();
	list<ReceiveBuffer>::reverse_iterator lastIt = m_buffer.rbegin();
	for(;it !=  m_buffer.end();++it)
	{
		// 最大id,跳到最后
		if(pClientHead->id > lastIt->id)
		{
			it = m_buffer.end();
			break;
		}else if(pClientHead->id == it->id)
		{
			break;
		}else if(pClientHead->id < it->id )
		{
			ReceiveBuffer buffer;
			buffer.id = pClientHead->id;
			buffer.bodyLen = pClientHead->bodyLen;
			it = m_buffer.insert(it,buffer);
			break;
		}
	}

	if(it == m_buffer.end())
	{
		ReceiveBuffer buffer;
		buffer.id = pClientHead->id;
		buffer.bodyLen = pClientHead->bodyLen;
		m_buffer.push_back(buffer);
		it = m_buffer.end();
		--it;
	}

	ReceiveBuffer &recBuffer = *it;
	if(pClientHead->offSet == 0)
	{
		// 第一个包处理
		PacketHead head;
		head.head = pClientHead->head;
		head.bodyLen = pClientHead->bodyLen;
		head.offSet = 0;
		head.id = 0;
		head.battleId = 0;
		head.ts = pClientHead->ts;

		memcpy(recBuffer.buffer,&head,sizeof(PacketHead));
		memcpy(recBuffer.buffer + sizeof(PacketHead),sRecvBuff + sizeof(ClientHead),iRecvSize - sizeof(ClientHead));
		recBuffer.len += iRecvSize - sizeof(ClientHead);

	}else{
		memcpy(recBuffer.buffer + pClientHead->offSet,sRecvBuff + sizeof(ClientHead),iRecvSize - sizeof(ClientHead));
		recBuffer.len += iRecvSize - sizeof(ClientHead);
	}


	recBuffer.lt = time(NULL);
	lastTime = time(NULL);


}

void CVideoDataWriter::appendText()
{
	if(m_buffer.empty())
	{
		return ;
	}
	time_t nowTs = time(NULL);
	while(!m_buffer.empty())
	{
		list<ReceiveBuffer>::iterator it = m_buffer.begin();
		ReceiveBuffer &recBuffer = *it;
		if(recBuffer.len == recBuffer.bodyLen && recBuffer.lt + 2 < nowTs)
		{
			m_text.append(recBuffer.buffer,recBuffer.bodyLen + 16);
			// 延迟2s写数据，保证顺序
			m_buffer.pop_front();
		}else if(recBuffer.lt + 2 < nowTs){
			// 超过2s没有全部接收，丢弃
			m_buffer.pop_front();
		}else{
			break ;
		}
	}
}


void CVideoDataWriter::write()
{
	time_t nowTs = time(NULL);
	while(!m_buffer.empty())
	{
		list<ReceiveBuffer>::iterator it = m_buffer.begin();
		ReceiveBuffer &recBuffer = *it;
		if(recBuffer.len == recBuffer.bodyLen && recBuffer.lt + 2 < nowTs)
		{
			// 延迟2s写数据，保证顺序
			::write(_fd,recBuffer.buffer,recBuffer.len + sizeof(PacketHead));
			m_buffer.pop_front();
		}else if(recBuffer.lt + 2 < nowTs){
			// 超过2s没有全部接收，丢弃
			m_buffer.pop_front();
		}else{
			break ;
		}
	}
}

bool CVideoDataWriter::isTimeToWriteFile()
{
	return lastTime + REMOVE_INTERVAL < time(NULL);
}

bool CVideoDataWriter::isTimeDel()
{
	return m_buffer.empty() && (m_isBattleOver || lastTime + REMOVE_INTERVAL < time(NULL));
}

void CVideoDataWriter::zipWrite()
{
	if(m_text.empty())
	{
		return ;
	}

	static string result;
	result.clear();

	Compress::GzipCompress(result,m_text);
	//::write(_fd,result.c_str(),result.length());

	::write(_fd,m_text.c_str(),m_text.length());
}



