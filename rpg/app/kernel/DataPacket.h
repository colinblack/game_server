/*
 * DataPacket.h
 *
 *  Created on: 2019年4月18日
 *      Author: Administrator
 */

#ifndef _DATA_PACKET_H_
#define _DATA_PACKET_H_

#include "Common.h"
#include "IPacket.h"

#define DP_BODY_SIZE 0x8000
#define DP_CHEAD 0xFC00
#define DP_HEAD_SIZE 0xC

class DataPacket: public IPacket, public IEncodable, public IDecodable {
public:
	uint32_t m_tableId;
	uint32_t m_opId;
	CStaticBuffer<DP_BODY_SIZE> body;
public:
	DataPacket();
	virtual ~DataPacket();
	virtual bool Encode(IBuffer *pBuffer);
	virtual bool Decode(IBuffer *pBuffer);
	uint32_t GetDecodeSize();
	void Clean();
private:
	uint32_t m_size;
};

#endif /* _DATA_PACKET_H_ */
