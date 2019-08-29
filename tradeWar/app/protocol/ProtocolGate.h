/*
 * ProtocolGate.h
 *
 *  Created on: 2015-12-11
 *      Author: Administrator
 */

#ifndef PROTOCOLGATE_H_
#define PROTOCOLGATE_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CGateListProtocol)
	byte cmd;
	byte subCmd;
	uint32_t from;
	uint32_t to;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, from);
		PACKET_DECODE(UInt32, to);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateOverProtocol)
	byte cmd;
	byte subCmd;
	double battleId;
	uint32_t level;
	uint32_t win;
	uint32_t star;
	byte diff;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32, level);
		PACKET_DECODE(UInt32, win);
		PACKET_DECODE(UInt32, star);
		PACKET_DECODE(Byte, diff);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGodGateOverProtocol)
	byte cmd;
	byte subCmd;
	double battleId;
	uint32_t level;
	uint32_t win;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32, level);
		PACKET_DECODE(UInt32, win);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateRobotProtocol)
	byte cmd;
	byte subCmd;
	uint32_t level;
	uint32_t option;
	uint32_t count;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, level);
		PACKET_DECODE(UInt32, option);
		PACKET_DECODE(UInt32, count);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateGetTreasureInfoProtocol)
	byte cmd;
	byte subCmd;
	uint32_t chapter;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, chapter);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateSetTreasureInfoProtocol)
	byte cmd;
	byte subCmd;
	uint32_t chapter;
	uint32_t treasureId;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, chapter);
		PACKET_DECODE(UInt32, treasureId);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END



DEFINE_RECEIVE_PACKET_BEGIN(CGateGetStarInfoProtocol)
	byte cmd;
	byte subCmd;
	uint32_t minChapter;
	uint32_t maxChapter;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, minChapter);
		PACKET_DECODE(UInt32, maxChapter);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CGateRobotAccProtocol)
	byte cmd;
	byte subCmd;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateRewardProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateRandAwardProtocol)
	byte cmd;
	byte subCmd;
	byte index1;
	byte index2;
	byte index3;
	byte isCash;//(cash:2 coin:1)
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, index1);
		PACKET_DECODE(Byte, index2);
		PACKET_DECODE(Byte, index3);
		PACKET_DECODE(Byte, isCash);

	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateRandAwardPushProtocol)
	byte cmd;
	byte subCmd;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateBattleOverProtocol)
	byte cmd;
	byte subCmd;
	uint32_t level;
	byte star;
	uint32_t score;
	uint32_t res;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, level);
		PACKET_DECODE(Byte, star);
		PACKET_DECODE(UInt32, score);
		PACKET_DECODE(UInt32, res);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateDefendOverProtocol)
	byte cmd;
	byte subCmd;
	uint32_t level;
	byte star;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, level);
		PACKET_DECODE(Byte, star);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateKillNumberProtocol)
	byte cmd;
	byte subCmd;
	uint32_t level;
	uint32_t num;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, level);
		PACKET_DECODE(UInt32, num);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CGateSpeedUpProtocol)
	byte cmd;
	byte subCmd;
	byte flag;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Byte, flag);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLGATE_H_ */
