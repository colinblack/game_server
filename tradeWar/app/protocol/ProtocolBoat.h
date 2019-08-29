/*
 * ProtocolBoat.h
 *
 *  Created on: 2016-11-15
 *      Author:
 */

#ifndef PROTOCOL_BOAT_H_
#define PROTOCOL_BOAT_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CBoatRefreshProtocol)
	byte cmd;
	byte subCmd;
	byte type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, type);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatRewardProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatRobResultProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	byte damage;
	byte star;
	uint32_t userid;
	uint32_t res;
	map< pair<unsigned, unsigned>, unsigned> soldiers; //[id,lv]=>count
	map< pair<unsigned, unsigned>, unsigned> towers;   //[id,lv]=>count
	map< pair<unsigned, unsigned>, unsigned> soldier_dead;   //[id,lv]=>count
	map< pair<unsigned, unsigned>, unsigned> skill;   //[id,lv]=>count

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(Byte, damage);
		PACKET_DECODE(Byte, star);
		PACKET_DECODE(UInt32, userid);
		PACKET_DECODE(UInt32, res);

		//soldiers
		uint32_t len = 0;
		if (!reader.GetUInt32(len)) {
			len = 0;
		}
		for (uint32_t i = 0; i < len; ++i) {
			uint32_t id = 0;
			PACKET_DECODE(UInt32, id);
			uint32_t lv = 0;
			PACKET_DECODE(UInt32, lv);
			uint32_t count = 0;
			PACKET_DECODE(UInt32, count);
			pair<unsigned, unsigned> k(id,lv);
			if (soldiers.count(k)) {
				soldiers[k] += count;
			} else {
				soldiers.insert(make_pair(k, count));
			}
		}

		//tower
		if (!reader.GetUInt32(len)) {
			len = 0;
		}
		for (uint32_t i = 0; i < len; ++i) {
			uint32_t id = 0;
			PACKET_DECODE(UInt32, id);
			uint32_t lv = 0;
			PACKET_DECODE(UInt32, lv);
			uint32_t count = 0;
			PACKET_DECODE(UInt32, count);
			pair<unsigned, unsigned> k(id,lv);
			if (towers.count(k)) {
				towers[k] += count;
			} else {
				towers.insert(make_pair(k, count));
			}
		}

		//soldier_dead
		if (!reader.GetUInt32(len)) {
			len = 0;
		}
		for (uint32_t i = 0; i < len; ++i) {
			uint32_t id = 0;
			PACKET_DECODE(UInt32, id);
			uint32_t lv = 0;
			PACKET_DECODE(UInt32, lv);
			uint32_t count = 0;
			PACKET_DECODE(UInt32, count);
			pair<unsigned, unsigned> k(id,lv);
			if (soldier_dead.count(k)) {
				soldier_dead[k] += count;
			} else {
				soldier_dead.insert(make_pair(k, count));
			}
		}
		//skill
		if (!reader.GetUInt32(len)) {
			len = 0;
		}
		for (uint32_t i = 0; i < len; ++i) {
			uint32_t id = 0;
			PACKET_DECODE(UInt32, id);
			uint32_t lv = 0;
			PACKET_DECODE(UInt32, lv);
			uint32_t count = 0;
			PACKET_DECODE(UInt32, count);
			pair<unsigned, unsigned> k(id,lv);
			if (skill.count(k)) {
				skill[k] += count;
			} else {
				skill.insert(make_pair(k, count));
			}
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatStartProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatSpeedUpProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatGetTargetProtocol)
	byte cmd;
	byte subCmd;
	byte first;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, first);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatRevengeProtocol)
	byte cmd;
	byte subCmd;
	uint32_t target_uid;
	uint32_t ts;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, target_uid);
		if (!reader.GetUInt32(ts)) {
			ts = 0;
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatRobResProtocol)
	byte cmd;
	byte subCmd;
	uint32_t uid;
	uint32_t id;
	uint32_t res;
	int32_t exp;
	string name;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, res);
		PACKET_DECODE(Int32, exp);
		PACKET_DECODE(String, name);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


//跨服
DEFINE_RECEIVE_PACKET_BEGIN(CBoatAsrvStartProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	byte lv;
	uint32_t uid;
	uint32_t res;
	uint32_t ts;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(Byte, lv);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, res);
		PACKET_DECODE(UInt32, ts);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatAsrvSpeedUpProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	uint32_t uid;
	uint32_t ts;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ts);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatAsrvSearchProtocol)
	byte cmd;
	byte subCmd;
	byte lv;
	uint32_t uid;
	uint32_t ts;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, lv);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ts);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatAsrvRobProtocol)
	byte cmd;
	byte subCmd;
	byte id;
	uint32_t uid;
	uint32_t res;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, res);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CBoatAsrvTargetProtocol)
	byte cmd;
	byte subCmd;
	uint32_t target_uid;
	uint32_t boat_id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, target_uid);
		PACKET_DECODE(UInt32, boat_id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOL_BOAT_H_ */
