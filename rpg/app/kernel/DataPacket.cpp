/*
 * DataPacket.cpp
 *
 *  Created on: 2019年4月18日
 *      Author: Administrator
 */

#include "DataPacket.h"

DataPacket::DataPacket() {
	m_size = 0;
	m_tableId = 0;
	m_opId = 0;
}

DataPacket::~DataPacket() {

}

bool DataPacket::Encode(IBuffer *pBuffer) {
	if (pBuffer == NULL) {
		return false;
	}
	pBuffer->Clear();
	CBufferWriter writer(pBuffer);
	if (body.GetSize() > UINT16_MAX) {
		return false;
	}
	PACKET_ENCODE(UInt16, DP_CHEAD);
	PACKET_ENCODE(UInt16, body.GetSize());
	PACKET_ENCODE(UInt32, m_tableId);
	PACKET_ENCODE(UInt32, m_opId);
	PACKET_ENCODE(Bytes, body.GetConstBuffer(), body.GetSize());
	return true;
}

bool DataPacket::Decode(IBuffer *pBuffer) {
	if (pBuffer == NULL) {
		return false;
	}
	CBufferReader reader(pBuffer);
	uint16_t head = 0;
	PACKET_DECODE(UInt16, head);
	if (head != DP_CHEAD) {
		m_size = 2;
		return false;
	}
	if (DP_HEAD_SIZE > pBuffer->GetSize()) {
		return false;
	}
	uint16_t bodyLen = 0;
	PACKET_DECODE(UInt16, bodyLen);
	PACKET_DECODE(UInt32, m_tableId);
	PACKET_DECODE(UInt32, m_opId);
	if (static_cast<unsigned>(DP_HEAD_SIZE + bodyLen) > pBuffer->GetSize()) {
		return false;
	}
	m_size = bodyLen + DP_HEAD_SIZE;
	if (!body.SetSize(bodyLen)) {
		return false;
	}
	PACKET_DECODE(Bytes, body.GetNativeBuffer(), bodyLen);
	return true;
}

uint32_t DataPacket::GetDecodeSize() {
	return m_size;
}

void DataPacket::Clean() {
	m_tableId = 0;
	m_opId = 0;
	body.Clear();
	m_size = 0;
}
