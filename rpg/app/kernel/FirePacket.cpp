/*
 * Packet.cpp
 *
 *  Created on: 2012-2-10
 *      Author: dada
 */

#include "FirePacket.h"

CFirePacket::CFirePacket() {
	ChannelId = -1;
	head = FP_SHEAD;
	bodyLen = 0;
	cmd = 0;
	fd = 0;
	time = 0;
	microTime = 0;
	clientIp = 0;
	m_decodeSize = 0;
	subCmd = 0;
	callback = 0;
	msgId = 0;
	errorCode = 0;
}

CFirePacket::CFirePacket(CFirePacket *oth) {
	if (oth != NULL) {
		ChannelId = oth->ChannelId;
		head = oth->head;
		bodyLen = oth->bodyLen;
		cmd = oth->cmd;
		fd = oth->fd;
		time = oth->time;
		microTime = oth->microTime;
		clientIp = oth->clientIp;
		m_decodeSize = oth->m_decodeSize;
		subCmd = oth->subCmd;
		callback = oth->callback;
		msgId = oth->msgId;
		errorCode = oth->errorCode;
		body.Clear();
		body.Append(oth->body.GetNativeBuffer(), oth->body.GetSize());
	}
}

CFirePacket::~CFirePacket() {
}

bool CFirePacket::Encode(IBuffer *pBuffer) {
	if (pBuffer == NULL) {
		return false;
	}
	pBuffer->Clear();
	CBufferWriter writer(pBuffer);
	if (body.GetSize() > UINT16_MAX) {
		return false;
	}
	PACKET_ENCODE(UInt16, FP_SHEAD);
	PACKET_ENCODE(UInt16, body.GetSize());
	PACKET_ENCODE(UInt16, cmd);
	PACKET_ENCODE(UInt32, fd);
	PACKET_ENCODE(UInt32, time);
	PACKET_ENCODE(UInt32, microTime);
	PACKET_ENCODE(UInt32, clientIp);
	PACKET_ENCODE(UInt32, subCmd);
	PACKET_ENCODE(UInt32, callback);
	PACKET_ENCODE(Int32,  msgId);
	PACKET_ENCODE(UInt32, errorCode);
	PACKET_ENCODE(Bytes, body.GetConstBuffer(), body.GetSize());
	return true;
}

bool CFirePacket::Decode(IBuffer *pBuffer) {
	m_decodeSize = 0;
	if (pBuffer == NULL) {
		return false;
	}
	CBufferReader reader(pBuffer);
	PACKET_DECODE(UInt16, head);
	if (head != FP_SHEAD) {
		debug_log("get head failed:%x", head);
		m_decodeSize = 2;
		return false;
	}
	if (sizeof(BattleHead) > pBuffer->GetSize()) {
		return false;
	}
	PACKET_DECODE(UInt16, bodyLen);
	PACKET_DECODE(UInt16, cmd);
	PACKET_DECODE(UInt32, fd);
	PACKET_DECODE(UInt32, time);
	PACKET_DECODE(UInt32, microTime);
	PACKET_DECODE(UInt32, clientIp);
	PACKET_DECODE(UInt32, subCmd);
	PACKET_DECODE(UInt32, callback);
	PACKET_DECODE(Int32,  msgId);
	PACKET_DECODE(UInt32, errorCode);
	if (static_cast<uint32_t>(sizeof(BattleHead) + bodyLen) > pBuffer->GetSize()) {
		return false;
	}
	m_decodeSize = bodyLen + sizeof(BattleHead) ;
	if (!body.SetSize(bodyLen)) {
		error_log("buf capacity insufficent expect %u but only %u", bodyLen, body.GetCapacity());
		return true;
	}
	PACKET_DECODE(Bytes, body.GetNativeBuffer(), bodyLen);
	return true;
}

bool CFirePacket::SetBody(IBuffer* pBuf) {
	if (pBuf == NULL) {
		return false;
	}
	if (pBuf->GetSize() > FP_BODY_SIZE) {
		return false;
	}
	body.Clear();
	CBufferWriter writer(&body);
	writer.AppendBytes(pBuf->GetConstBuffer(), pBuf->GetSize());
	return true;
}

IBuffer* CFirePacket::GetBody() {
	return &body;
}

void CFirePacket::Clean() {
	ChannelId = 0;
	head = 0;
	bodyLen = 0;
	cmd = 0;
	fd = 0;
	time = 0;
	microTime = 0;
	clientIp = 0;
	subCmd = 0;
	callback = 0;
	msgId = 0;
	errorCode = 0;
	body.Clear();
}

