/*
 * DanymicBuffer.h
 *
 *  Created on: 2014-3-18
 *      Author: Ralf
 */

#ifndef DanymicBuffer_H_
#define DanymicBuffer_H_

#include "Common.h"
template<size_t m_capacity>
class CDanymicBuffer : public IBuffer
{
public:

	CDanymicBuffer()  {}

	virtual byte *GetNativeBuffer()
	{
		return (byte *)const_cast<char *>(m_pBuffer.c_str());
	}

	virtual const byte *GetConstBuffer() const
	{
		return (byte *)m_pBuffer.c_str();
	}

	virtual uint32_t GetSize() const
	{
		return m_pBuffer.size();
	}

	virtual bool SetSize(uint32_t size)
	{
		if(size > m_capacity)
			return false;
		m_pBuffer.resize(size);
		return true;
	}

	virtual uint32_t GetCapacity() const
	{
		return m_capacity;
	}

	virtual bool IsEmpty() const
	{
		return m_pBuffer.empty();
	}

	virtual bool Clear()
	{
		m_pBuffer.clear();
		return true;
	}

	virtual byte GetAt(uint32_t uIndex) const
	{
		if(uIndex >= m_pBuffer.size())
		{
			return 0;
		}
		return m_pBuffer[uIndex];
	}

	virtual bool SetAt(uint32_t uIndex, byte cValue)
	{
		if(uIndex >= m_pBuffer.size())
		{
			return false;
		}
		m_pBuffer[uIndex] = cValue;
		return true;
	}

	virtual bool CopyFrom(const byte *pcBuffer, uint32_t uSize)
	{
		if(pcBuffer == NULL || uSize > m_capacity)
		{
			return false;
		}
		m_pBuffer.assign((const char *)pcBuffer,uSize);
		return true;
	}

	virtual bool Append(const byte *pcBuffer, uint32_t uSize)
	{
		if(pcBuffer == NULL || m_pBuffer.size() + uSize > m_capacity)
		{
			return false;
		}
		m_pBuffer.append((const char *)pcBuffer,uSize);
		return true;
	}

	virtual bool Remove(uint32_t uStart, uint32_t uSize)
	{
		if(uStart + uSize > m_pBuffer.size())
		{
			return false;
		}
		m_pBuffer.erase(uStart,uSize);
		return true;
	}

	virtual bool GetData(byte *pBuffer, uint32_t uSize, uint32_t uIndex) const
	{
		if(pBuffer == NULL || uIndex + uSize > m_pBuffer.size())
		{
			return false;
		}
		memcpy(pBuffer, m_pBuffer.c_str() + uIndex, uSize);
		return true;
	}

private:
	string m_pBuffer;
};

#endif /* DanymicBuffer_H_ */
