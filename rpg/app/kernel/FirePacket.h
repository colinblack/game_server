/*
 * Packet.h
 *
 *  Created on: 2012-2-10
 *      Author: dada
 */

#ifndef _FIRE_PACKET_H_
#define _FIRE_PACKET_H_

#include "Common.h"
#include "IPacket.h"

#pragma pack(1)
struct ClientHead {
	byte head;
	byte seq;
	uint32_t command;
	uint32_t callback;
	uint32_t msgId;
};
struct BattleHead {
	uint16_t head;
	uint16_t bodyLen;
	uint16_t cmd;
	uint32_t fd;
	uint32_t time;
	uint32_t microTime;
	uint32_t clientIp;
	uint32_t subCmd;
	uint32_t callback;
	int32_t msgId;
	uint32_t errorCode;

	void Clear() {
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
	}
};
#pragma pack()

#define FP_BODY_SIZE 0xFFD7
#define FP_CHEAD 0x10
#define FP_SHEAD 0xFA
#define FP_SERVER_HEAD_SIZE 38
#define MAX_PACKET_SIZE (FP_SERVER_HEAD_SIZE + FP_BODY_SIZE)

#define PROTOCOL_ACCESS_TRANSFER 1          // 客户端到login,login可直接转发
#define PROTOCOL_ACCESS_ANSWER 2            // 回包到客户端,login可直接转发
#define PROTOCOL_ACCESS_HEARBEAT 3          // 心跳
#define PROTOCOL_ACCESS_COFFLINE 4          // 客户端下线
#define PROTOCOL_ACCESS_LOFFLINE 5          // 服务端下线

#define PROTOCOL_EVENT_BEGIN 100
#define PROTOCOL_EVENT_OFFLINE 200
#define PROTOCOL_EVENT_SECOND_TIMER 201
#define PROTOCOL_EVENT_MANAGER 202
#define PROTOCOL_EVENT_BUY_GOODS 203
#define PROTOCOL_EVENT_LOGIN 204
#define PROTOCOL_ENENT_ACTIVITY 205

class CFirePacket: public IPacket, public IEncodable, public IDecodable {
public:
	int ChannelId;
	uint16_t head;
	uint16_t bodyLen;
	uint16_t cmd;
	uint32_t fd;
	uint32_t time;
	uint32_t microTime;
	uint32_t clientIp;
	uint32_t subCmd;
	uint32_t callback;
	int32_t msgId;
	uint32_t errorCode;
	CStaticBuffer<FP_BODY_SIZE> body;
public:
	CFirePacket();
	CFirePacket(CFirePacket *oth);
	virtual ~CFirePacket();
	virtual bool Encode(IBuffer *pBuffer);
	virtual bool Decode(IBuffer *pBuffer);
	bool SetBody(IBuffer* pBuf);
	IBuffer* GetBody();
	void Clean();
	uint32_t GetDecodeSize() {
		return m_decodeSize;
	}
private:
	uint32_t m_decodeSize;
};
#endif /* _FIRE_PACKET_H_ */
