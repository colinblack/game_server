/*
 * ProtocolOtherServer.h
 *
 *  Created on: 2019年3月6日
 *      Author: Administrator
 */

#ifndef PROTOCOL_OTHER_SERVER_H_
#define PROTOCOL_OTHER_SERVER_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(COthSrvUserInteractReqProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	byte lv;
	byte type;
	string name;
	string pic;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(Byte, lv);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(String, name);
		PACKET_DECODE(String, pic);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(COthSrvUserInteractRespProtocol)
	byte cmd;
	byte subCmd;
	byte ret;
	int16_t cnt;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, ret);
		PACKET_DECODE(Int16, cnt);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(COthSrvUserInfoReqProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END



#endif /* PROTOCOL_OTHER_SERVER_H_ */
