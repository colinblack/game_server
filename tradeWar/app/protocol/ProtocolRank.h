/*
 * ProtocolRank.h
 *
 *  Created on: 2015-12-30
 *      Author: Administrator
 */

#ifndef PROTOCOLRANK_H_
#define PROTOCOLRANK_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CRankQueryProtocol)
	byte cmd;
	byte subCmd;
	byte all;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte,cmd);
		PACKET_DECODE(Byte,subCmd);
		if (!reader.GetByte(all)) {
			all = 0;
		}
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLRANK_H_ */
