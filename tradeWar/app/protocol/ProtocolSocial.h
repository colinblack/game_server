/*
 * ProtocolSocial.h
 *
 *  Created on: 2016-5-26
 *      Author: Administrator
 */

#ifndef PROTOCOLSOCIAL_H_
#define PROTOCOLSOCIAL_H_
#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CSocialQueryProtocol)
		byte cmd;
		byte subCmd;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CFriendAddRequestProtocol)
		byte cmd;
		byte subCmd;
		uint32_t other_uid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, other_uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CFriendAddResponseProtocol)
		byte cmd;
		byte subCmd;
		byte type;
		uint32_t other_uid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(UInt32, other_uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CFriendDelRequestProtocol)
		byte cmd;
		byte subCmd;
		uint32_t other_uid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, other_uid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CFriendSetBuildingTsProtocol)
		byte cmd;
		byte subCmd;
		byte reset;	// 重置时间戳(1:重置,0:不重置)
		uint32_t bts; // 建筑升级完成时间
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, reset);
		PACKET_DECODE(UInt32, bts);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CFriendAccBuildingProtocol)
		byte cmd;
		byte subCmd;
		uint32_t otherUid; // 好友UID
		uint32_t bud; // 建筑UD
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, otherUid);
		PACKET_DECODE(UInt32, bud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CFriendQueryAccBuildingProtocol)
		byte cmd;
		byte subCmd;
		uint32_t otherUid; // 好友UID
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, otherUid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CFriendQueryAccBuildingHistoryProtocol)
		byte cmd;
		byte subCmd;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CFriendHelpProtocol)
		byte cmd;
		byte subCmd;
		uint32_t friendUid;
		uint32_t bud;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, friendUid);
		PACKET_DECODE(UInt32, bud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CNuclearQueryProtocol)
		byte cmd;
		byte subCmd;
		uint32_t friendUid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, friendUid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CNuclearChargeProtocol)
		byte cmd;
		byte subCmd;
		uint32_t friendUid;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, friendUid);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CStealResourceProtocol)
		byte cmd;
		byte subCmd;
		uint32_t friendUid;
		uint32_t bud;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, friendUid);
		PACKET_DECODE(UInt32, bud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CFriendSendGiftProtocol)
		byte cmd;
		byte subCmd;
		uint32_t friendUid;
		uint32_t gift;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, friendUid);
		PACKET_DECODE(UInt32, gift);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


#endif /* PROTOCOLSOCIAL_H_ */
