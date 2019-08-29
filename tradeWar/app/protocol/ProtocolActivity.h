/*
 * ProtocolActivity.h
 *
 *  Created on: 2016年10月26日
 *      Author: asdf
 */

#ifndef PROTOCOL_ACTIVITY_H_
#define PROTOCOL_ACTIVITY_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CActivityGetDataProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CActivityRewardProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;
	uint32_t index;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, index);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CActivityAddCountProtocol)
	byte cmd;
	byte subCmd;
	byte type;
	uint32_t id;
	uint32_t quest;
	uint32_t count;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, quest);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CActivityQuestRewardProtocol)
	byte cmd;
	byte subCmd;
	uint32_t type;
	uint32_t id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, type);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CActivityLotteryProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;
	uint32_t cnt;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, cnt);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


#endif /* PROTOCOL_ACTIVITY_H_ */
