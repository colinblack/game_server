/*
 * packet.h
 *
 *  Created on: 2015-8-31
 *      Author: Administrator
 */

#ifndef NET_PACKET_H_
#define NET_PACKET_H_

#include "Common.h"
#include "IPacket.h"
#include "../protocol/ProtocolDefine.h"

class CNetPacket: public IPacket, public IEncodable, public IDecodable
{
public:
	uint16_t head;
	uint16_t bodyLen;
	uint16_t ptype;
	uint32_t fd;		//客户端句柄。
	uint32_t stime;		//秒
	uint32_t mtime;		//毫秒
	uint32_t clientIp;	//原始客户端的ip
	byte cmd;
	byte subCmd;
	uint32_t uid;
	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> body;	//包体
public:
	CNetPacket();
	CNetPacket(const CNetPacket& other);
	virtual bool Encode(IBuffer *pBuffer);
	virtual bool Decode(IBuffer *pBuffer);
	bool SetBody(IBuffer* pBuf);
	IBuffer* GetBody();
};

#endif /* PACKET_H_ */
