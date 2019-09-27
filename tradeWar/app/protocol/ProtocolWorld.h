/*
 * ProtocolWorld.h
 *
 *  Created on: 2018年12月25日
 *      Author: Administrator
 */

#ifndef _PROTOCOL_WORLD_H_
#define _PROTOCOL_WORLD_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(WorldCityInfoProto);
	byte cmd;
	byte subCmd;
	uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN;
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END;
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(WorldSoldierProto);
	byte cmd;
	byte subCmd;
	uint32_t cid;
	uint32_t pid;
	vector< pair<uint32_t, uint32_t> > sold;

	IMPLEMENT_PACKET_DECODE_BEGIN;
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, cid);
		PACKET_DECODE(UInt32, pid);
		uint32_t len = 0;
		PACKET_DECODE(UInt32, len);
		for (uint32_t i = 0; i < len; ++i) {
			pair<uint32_t, uint32_t> item;
			PACKET_DECODE(UInt32, item.first);
			PACKET_DECODE(UInt32, item.second);
			sold.push_back(item);
		}
	IMPLEMENT_PACKET_DECODE_END;
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(WorldAttackProto);
	byte cmd;
	byte subCmd;
	uint32_t cid;
	uint32_t pid;

	IMPLEMENT_PACKET_DECODE_BEGIN;
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, cid);
		PACKET_DECODE(UInt32, pid);
	IMPLEMENT_PACKET_DECODE_END;
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(WorldFinishProto);
	byte cmd;
	byte subCmd;
	uint32_t cid;
	uint32_t pid;
	uint32_t userid;
	uint32_t win;

	IMPLEMENT_PACKET_DECODE_BEGIN;
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, cid);
		PACKET_DECODE(UInt32, pid);
		PACKET_DECODE(UInt32, userid);
		PACKET_DECODE(UInt32, win);
	IMPLEMENT_PACKET_DECODE_END;
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(WorldBuyShopProto);
	byte cmd;
	byte subCmd;
	uint32_t id;

	IMPLEMENT_PACKET_DECODE_BEGIN;
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END;
DEFINE_RECEIVE_PACKET_END


#endif /* _PROTOCOL_WORLD_H_ */
