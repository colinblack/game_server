/*
 * ProtocolBoss.h
 *
 *  Created on: 2019年2月25日
 *      Author: Administrator
 */

#ifndef PROTOCOL_BOSS_H_
#define PROTOCOL_BOSS_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(BossResultProto);
	byte cmd;
	byte subCmd;
	byte id;
	uint32_t hurt;
	vector<pair<uint32_t, uint32_t> > soldier;

	IMPLEMENT_PACKET_DECODE_BEGIN;
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(UInt32, hurt);
		byte len = 0;
		PACKET_DECODE(Byte, len);
		for (byte i = 0; i < len; ++i) {
			uint32_t sid = 0;
			PACKET_DECODE(UInt32, sid);
			uint32_t scnt = 0;
			PACKET_DECODE(UInt32, scnt);
			soldier.push_back(make_pair(sid, scnt));
		}
	IMPLEMENT_PACKET_DECODE_END;
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(BossShopProto);
	byte cmd;
	byte subCmd;
	byte id;

	IMPLEMENT_PACKET_DECODE_BEGIN;
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
	IMPLEMENT_PACKET_DECODE_END;
DEFINE_RECEIVE_PACKET_END


#endif /* PROTOCOL_BOSS_H_ */
