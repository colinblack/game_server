/*
 * packet.cpp
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#include "NetPacket.h"

CNetPacket::CNetPacket() {
	head = 0;
	bodyLen = 0;
	ptype = 0;
	fd = 0;
	stime = 0;
	mtime = 0;
	clientIp = 0;
	cmd = 0;
	subCmd = 0;
	uid = 0;
}

CNetPacket::CNetPacket(const CNetPacket& other) {
	head = other.head;
	bodyLen = other.bodyLen;
	ptype = other.ptype;
	fd = other.fd;
	stime = other.stime;
	mtime = other.mtime;
	clientIp = other.clientIp;
	cmd = other.cmd;
	subCmd = other.subCmd;
	uid = other.uid;
	body = other.body;
}

bool CNetPacket::Encode(IBuffer *pBuffer) {
	if (pBuffer == NULL) {
		return false;
	}
	pBuffer->Clear();
	CBufferWriter writer(pBuffer);
//	writer.SetSwapByte(true);
	uint32_t packetLength = PACKET_HEADER_SIZE + body.GetSize();
	if (packetLength > UINT16_MAX) {
		return false;
	}

	PACKET_ENCODE(UInt16, MAGIC_HEADER);
	PACKET_ENCODE(UInt16, body.GetSize());
	PACKET_ENCODE(UInt16, ptype);
	PACKET_ENCODE(UInt32, fd);
	PACKET_ENCODE(UInt32, stime);
	PACKET_ENCODE(UInt32, mtime);
	PACKET_ENCODE(UInt32, clientIp); //client ip
	PACKET_ENCODE(Bytes, body.GetConstBuffer(), body.GetSize());
	return true;
}

bool CNetPacket::Decode(IBuffer *pBuffer) {
	if (pBuffer == NULL) {
		return false;
	}
	CBufferReader reader(pBuffer);
//	reader.SetSwapByte(true);
	PACKET_DECODE(UInt16, head);
	if (head != MAGIC_HEADER) {
		debug_log("get head failed:%x", head);
		return false;
	}
	if (PACKET_HEADER_SIZE > pBuffer->GetSize()) {
		return false;
	}
	PACKET_DECODE(UInt16, bodyLen);
	PACKET_DECODE(UInt16, ptype);
	PACKET_DECODE(UInt32, fd);
	PACKET_DECODE(UInt32, stime);
	PACKET_DECODE(UInt32, mtime);
	PACKET_DECODE(UInt32, clientIp);
	if ((unsigned) (PACKET_HEADER_SIZE + bodyLen) > pBuffer->GetSize()) {
		return false;
	}
	if (bodyLen >= 2) {
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		reader.Skip(-2);
	}
	if (!body.SetSize(bodyLen)) {
		error_log("buf capacity insufficent expect %u but only %u", bodyLen, body.GetCapacity());
		return true;
	}
	PACKET_DECODE(Bytes, body.GetNativeBuffer(), bodyLen);
	return true;
}

bool CNetPacket::SetBody(IBuffer* pBuf) {
	if (pBuf == NULL || pBuf->GetSize() > MAX_PROTOCOL_BODY_SIZE) {
		return false;
	}
	body.Clear();
	body.AppendBuffer(pBuf);
	return true;
}

IBuffer* CNetPacket::GetBody() {
	return &body;
}

