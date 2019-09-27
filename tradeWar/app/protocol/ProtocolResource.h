/*
 * ProtocolResource.h
 *
 *  Created on: 2016年4月13日
 *      Author: Administrator
 */

#ifndef PROTOCOLRESOURCE_H_
#define PROTOCOLRESOURCE_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CBuyResProtocol)
	byte protocolType;
	byte command;
	byte type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, protocolType);
		PACKET_DECODE(Byte, command);
		PACKET_DECODE(Byte, type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CUseResProtocol)
	byte cmd;
	byte subCmd;
	int32_t r1;
	int32_t r2;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Int32, r1);
		PACKET_DECODE(Int32, r2);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLRESOURCE_H_ */
