
#ifndef PROTOCOL_SHARE_H_
#define PROTOCOL_SHARE_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CShareProtocol)
	byte cmd;
	byte subCmd;
	uint32_t type;	//分享类型
	uint64_t battleId;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, type);
		PACKET_DECODE(UInt64, battleId);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


#endif /* PROTOCOL_SHARE_H_ */
