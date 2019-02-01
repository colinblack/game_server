/*
 * Packet.cpp
 *
 *  Created on: 2012-2-10
 *      Author: dada
 */

#include "Packet.h"

#define PACKET_HEAD_MAGIC_NUMBER	0x81
#define PACKET_TAIL_MAGIC_NUMBER	0x7e

#define htonll(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFUL)) << 32) | htonl((uint32_t)((x) >> 32)))
#define ntohll(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFUL)) << 32) | ntohl((uint32_t)((x) >> 32)))

static byte PacketCheckSum(const byte *buffer, uint32_t size)
{
	static byte s_salt[7] = {0x74, 0xe8, 0xa6, 0x97, 0x2e, 0x3c,  0x59};
	byte sum = 0;
	for(uint32_t i = 0; i < size; i++)
	{
		sum ^= buffer[i];
	}
	sum ^= s_salt[size % sizeof(s_salt)];
	return sum;
}

CPacket::CPacket() :
	ChannelId(-1),
	PacketType(PT_Unknow),
	PacketFlag(0),
	From(0),
	To(0),
	SequenceNo(0),
	RetryTime(0),
	UserId(0),
	Key(0),
	ProtocolType(0),
	ProtocolFlag(0),
	ProtocolResult(0),
	m_decodeSize(0),
	m_bWebSocket(false)
{
}

static byte s_baReserveData[8] = {0};

bool CPacket::Encode(IBuffer *pBuffer)
{
	if(pBuffer == NULL)
	{
		return false;
	}
	pBuffer->Clear();
	CBufferWriter writer(pBuffer);
	writer.SetSwapByte(true);
	uint32_t packetLength = PACKET_HEADER_SIZE + ProtocolBody.GetSize() + sizeof(byte);
	if(packetLength > UINT16_MAX)
	{
		return false;
	}

	int len = 0;
	if(m_bWebSocket)
	{
		PACKET_ENCODE(Byte, 0x82);
		if(packetLength < 126){
			PACKET_ENCODE(Byte, char(packetLength));
			len = 2;
		}
		else if(packetLength <= 65535){
			PACKET_ENCODE(Byte, char(126));
			PACKET_ENCODE(UInt16, (uint16_t)packetLength);
			len = 4;
		}else{
			PACKET_ENCODE(Byte, char(127));
			PACKET_ENCODE(UInt64, (uint64_t)packetLength);
			len = 10;
		}
	}

	PACKET_ENCODE(UInt16, (uint16_t)packetLength);
	PACKET_ENCODE(Byte, PACKET_HEAD_MAGIC_NUMBER);
	PACKET_ENCODE(Byte, 0);
	PACKET_ENCODE(Byte, PacketType);
	PACKET_ENCODE(Byte, PacketFlag);
	PACKET_ENCODE(Byte, From);
	PACKET_ENCODE(Byte, To);
	PACKET_ENCODE(UInt32, SequenceNo);
	PACKET_ENCODE(Byte, RetryTime);
	PACKET_ENCODE(Bytes, s_baReserveData, 3);
	PACKET_ENCODE(UInt32, UserId);
	PACKET_ENCODE(UInt32, Key);
	PACKET_ENCODE(UInt16, ProtocolBody.GetSize());
	PACKET_ENCODE(Byte, PACKET_HEADER_SIZE);
	PACKET_ENCODE(Byte, 0);
	PACKET_ENCODE(Byte, MainProtocolType);
	PACKET_ENCODE(Byte, SubProtocolType);
	PACKET_ENCODE(Byte, ProtocolFlag);
	PACKET_ENCODE(Byte, ProtocolResult);
	PACKET_ENCODE(Bytes, ProtocolBody.GetConstBuffer(), ProtocolBody.GetSize());
	PACKET_ENCODE(Byte, PACKET_TAIL_MAGIC_NUMBER);
	pBuffer->SetAt(27 + len, PacketCheckSum(pBuffer->GetConstBuffer() + 28 + len, pBuffer->GetSize() - 29 - len));
	pBuffer->SetAt(3 + len, PacketCheckSum(pBuffer->GetConstBuffer() + 4 + len, pBuffer->GetSize() - 5 - len));
	return true;
}

bool CPacket::Decode(IBuffer *pBuffer)
{
	m_decodeSize = 0;
	if(pBuffer == NULL)
	{
		return false;
	}

	if(m_bWebSocket)
	{
		if(pBuffer->GetSize() < 14)
			return false;
		byte* b = pBuffer->GetNativeBuffer();

		if((b[0] & 0x80) != 0x80)
		{
			error_log("[websocket fin error]");
			return false;
		}
		if((b[0] & 0x0F) != 0x02)
		{
			error_log("[websocket opcode error]");
			return false;
		}
		if((b[1] & 0x80) != 0x80)
		{
			error_log("[websocket mask error]");
			return false;
		}

		int m_skip, m_l;
		char m_mask[4];
		char c = b[1] & 0x7F;
		if(c == 126){
			m_skip = 8;
			m_l = ntohs(*(uint16_t*)(b + 2));
			memcpy(m_mask, b + 4, 4);
		}
		else if(c == 127){
			m_skip = 14;
			m_l = ntohll(*(uint64_t*)(b + 2));
			memcpy(m_mask, b + 10, 4);
		}
		else{
			m_skip = 6;
			m_l = c;
			memcpy(m_mask, b + 2, 4);
		}

		if(m_skip + m_l > pBuffer->GetSize())
			return false;
		for(int i=0;i<m_l;++i)
			b[i + m_skip] = b[i + m_skip] ^ m_mask[i % 4];
		pBuffer->Remove(0, m_skip);
	}

	CBufferReader reader(pBuffer);
	reader.SetSwapByte(true);
	uint16_t packetLength = 0;
	PACKET_DECODE(UInt16, packetLength);
	if(packetLength > pBuffer->GetSize())
	{
		return false;
	}
	if(packetLength < PACKET_HEADER_SIZE + sizeof(byte))
	{
		return false;
	}
	byte head = 0;
	PACKET_DECODE(Byte, head);
	if(head != PACKET_HEAD_MAGIC_NUMBER)
	{
		return false;
	}
	byte tail = pBuffer->GetAt(packetLength - sizeof(byte));
	if(tail != PACKET_TAIL_MAGIC_NUMBER)
	{
		return false;
	}
	m_decodeSize = packetLength;
	byte checkSum = 0;
	PACKET_DECODE(Byte, checkSum);
	if(PacketCheckSum(pBuffer->GetConstBuffer() + 4, packetLength - 5) != checkSum)
	{
		return false;
	}
	byte packetType = 0;
	PACKET_DECODE(Byte, packetType);
	PacketType = (EPacketType)packetType;
	PACKET_DECODE(Byte, PacketFlag);
	PACKET_DECODE(Byte, From);
	PACKET_DECODE(Byte, To);
	PACKET_DECODE(UInt32, SequenceNo);
	PACKET_DECODE(Byte, RetryTime);
	PACKET_DECODE_SKIP(3);
	PACKET_DECODE(UInt32, UserId);
	PACKET_DECODE(UInt32, Key);
	uint16_t bodySize = 0;
	PACKET_DECODE(UInt16, bodySize);
	byte bodyOffset = 0;
	PACKET_DECODE(Byte, bodyOffset);
	if(bodyOffset == 0)
	{
		bodyOffset = PACKET_HEADER_SIZE;
	}
	else if(bodyOffset < PACKET_HEADER_SIZE)
	{
		return false;
	}
	if(bodyOffset + bodySize >= packetLength)
	{
		return false;
	}
	byte bodyCheckSum = 0;
	PACKET_DECODE(Byte, bodyCheckSum);
	if(PacketCheckSum(pBuffer->GetConstBuffer() + 28, bodyOffset + bodySize - 28) != bodyCheckSum)
	{
		return false;
	}
	PACKET_DECODE(Byte, MainProtocolType);
	PACKET_DECODE(Byte, SubProtocolType);
	PACKET_DECODE(Byte, ProtocolFlag);
	PACKET_DECODE(Byte, ProtocolResult);
	ProtocolBody.Clear();
	if(bodyOffset != 0)
	{
		PACKET_DECODE_SKIP(bodyOffset - PACKET_HEADER_SIZE);
		if(!ProtocolBody.SetSize(bodySize))
		{
			return false;
		}
		PACKET_DECODE(Bytes, ProtocolBody.GetNativeBuffer(), bodySize);
	}
	PACKET_DECODE_SKIP(1);
	return true;
}

uint32_t CPacket::GetDecodeSize()
{
	return m_decodeSize;
}
