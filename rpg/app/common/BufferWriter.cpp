/*
 * BufferWriter.cpp
 *
 *  Created on: 2012-2-8
 *      Author: dada
 */

#include "BufferWriter.h"

CBufferWriter::CBufferWriter() :
	m_pBuffer(NULL),
	m_bSwapByte(false)
{
}

CBufferWriter::CBufferWriter(IBuffer *pBuffer) :
	m_pBuffer(pBuffer),
	m_bSwapByte(false)
{
}

bool CBufferWriter::Attach(IBuffer *pBuffer)
{
	m_pBuffer = pBuffer;
	return true;
}

bool CBufferWriter::Detach()
{
	m_pBuffer = NULL;
	return true;
}

bool CBufferWriter::SetSwapByte(bool bSwapByte)
{
	m_bSwapByte = bSwapByte;
	return true;
}

#define NOTHING(value) value

#define IMPLEMENT_BUFFER_WRITE(TypeName, Type, SwapByte)	\
	bool CBufferWriter::Append##TypeName(Type value)	\
	{	\
		if(m_pBuffer == NULL)	\
		{	\
			return false;	\
		}	\
		if(m_bSwapByte)	\
		{	\
			value = SwapByte(value);	\
		}	\
		return m_pBuffer->Append((byte *)&value, sizeof(Type));	\
	}	\

IMPLEMENT_BUFFER_WRITE(Byte, byte, htonb)
IMPLEMENT_BUFFER_WRITE(Int16, int16_t, htons)
IMPLEMENT_BUFFER_WRITE(UInt16, uint16_t, htons)
IMPLEMENT_BUFFER_WRITE(Int32, int32_t, htonl)
IMPLEMENT_BUFFER_WRITE(UInt32, uint32_t, htonl)
//IMPLEMENT_BUFFER_WRITE(Int64, int64_t, hton64)
//IMPLEMENT_BUFFER_WRITE(UInt64, uint64_t, hton64)
//IMPLEMENT_BUFFER_WRITE(Double, double, hton64)

bool CBufferWriter::AppendInt64(int64_t value) {
	int64_t e = value >= 0 ? 2 * value : 2 * -value - 1;
	uint32_t i = e % 0x100000000;
	uint32_t s = (e - i) / 0x100000000;
	if (m_bSwapByte) {
		if (!AppendUInt32(s)) {
			return false;
		}
		if (!AppendUInt32(i)) {
			return false;
		}
	} else {
		if (!AppendUInt32(i)) {
			return false;
		}
		if (!AppendUInt32(s)) {
			return false;
		}
	}
	return true;
}

bool CBufferWriter::AppendUInt64(uint64_t value) {
	uint32_t e = value % 0x100000000;
	uint32_t i = (value - e) / 0x100000000;
	if (m_bSwapByte) {
		if (!AppendUInt32(i)) {
			return false;
		}
		if (!AppendUInt32(e)) {
			return false;
		}
	} else {
		if (!AppendUInt32(e)) {
			return false;
		}
		if (!AppendUInt32(i)) {
			return false;
		}
	}

	return true;
}

bool CBufferWriter::AppendFloat(float value){
	if(m_pBuffer == NULL)
	{
		return false;
	}

	return m_pBuffer->Append((byte *)&value, sizeof(float));
}

bool CBufferWriter::AppendDouble(double value){
	if(m_pBuffer == NULL)
	{
		return false;
	}

	return m_pBuffer->Append((byte *)&value, sizeof(double));
}

bool CBufferWriter::AppendShortString(const string &value)
{
	if(m_pBuffer == NULL)
	{
		return false;
	}
	byte size = (byte)value.size();
	if(!m_pBuffer->Append(&size, sizeof(size)))
	{
		return false;
	}
	if(!m_pBuffer->Append((byte *)value.c_str(), size))
	{
		m_pBuffer->SetSize(m_pBuffer->GetSize() - sizeof(size));
		return false;
	}
	return true;
}

bool CBufferWriter::AppendString(const string &value)
{
	if(m_pBuffer == NULL)
	{
		return false;
	}
	if(!AppendUVar32(value.size()))
	{
		return false;
	}
//	if(m_bSwapByte)
//	{
//		uint16_t tempSize = htons(size);
//		if(!m_pBuffer->Append((byte *)&tempSize, sizeof(tempSize)))
//		{
//			return false;
//		}
//	}
//	else
//	{
//		if(!m_pBuffer->Append((byte *)&size, sizeof(size)))
//		{
//			return false;
//		}
//	}
	if(!m_pBuffer->Append((byte *)value.c_str(), value.size()))
	{
		//m_pBuffer->SetSize(m_pBuffer->GetSize() - sizeof(size));
		return false;
	}
	return true;
}

bool CBufferWriter::AppendBuffer(const IBuffer *value)
{
	if(m_pBuffer == NULL || value == NULL)
	{
		return false;
	}
	uint16_t size = (uint16_t)value->GetSize();
	if(m_bSwapByte)
	{
		uint16_t tempSize = htons(size);
		if(!m_pBuffer->Append((byte *)&tempSize, sizeof(tempSize)))
		{
			return false;
		}
	}
	else
	{
		if(!m_pBuffer->Append((byte *)&size, sizeof(size)))
		{
			return false;
		}
	}
	if(!m_pBuffer->AppendBuffer(value))
	{
		m_pBuffer->SetSize(m_pBuffer->GetSize() - sizeof(size));
		return false;
	}
	return true;
}

bool CBufferWriter::AppendBytes(const byte *value, uint32_t size)
{
	if(m_pBuffer == NULL || value == NULL)
	{
		return false;
	}
	if(!m_pBuffer->Append(value, size))
	{
		return false;
	}
	return true;
}

bool CBufferWriter::AppendUVar32(uint32_t value) {
	if (value < 255) {
		return AppendByte(value);
	}
	if (!AppendByte(255)) {
		return false;
	}
	return AppendUInt32(value);
}

bool CBufferWriter::AppendBool(bool value) {
	return AppendByte(value ? 1 : 0);
}
