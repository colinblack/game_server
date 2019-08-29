/*
 * ProtocolArena.h
 *
 *  Created on: 2015-12-30
 *      Author: Administrator
 */

#ifndef PROTOCOL_ARENA_H_
#define PROTOCOL_ARENA_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CArenaBeginAttackProto)
	byte cmd;
	byte subCmd;
	uint32_t rank;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, rank);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CArenaEndAttackProto)
	byte cmd;
	byte subCmd;
	byte win;
	uint32_t uid;
	uint32_t rank;
	map<pair<unsigned, unsigned>, unsigned> soldiers; //[id,lv]=>count
	map<pair<unsigned, unsigned>, unsigned> towers;   //[id,lv]=>count
	map<pair<unsigned, unsigned>, unsigned> soldier_dead;   //[id,lv]=>count
	map<pair<unsigned, unsigned>, unsigned> skill;   //[id,lv]=>count

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, win);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, rank);
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

DEFINE_RECEIVE_PACKET_BEGIN(CArenaShopBuyProto)
	byte cmd;
	byte subCmd;
	byte id;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOL_ARENA_H_ */
