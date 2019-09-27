/*
 * ProtocolSkill.h
 *
 *  Created on: 2015年12月21日
 *      Author: aaron
 *        desc: 技能协议
 */

#ifndef PROTOCOLSKILL_H_
#define PROTOCOLSKILL_H_
// 技能使用
DEFINE_RECEIVE_PACKET_BEGIN(CSkillAttackProtocol)
	byte cmd;
	byte subCmd;
	double battleId;
	byte race;
	uint32_t ud;
	uint32_t attackedUid;
	byte attackedRace;
	uint32_t attackedUd;
	uint16_t skillId;
	uint16_t x;
	uint16_t y;
	byte prof;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(Byte, race);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, attackedUid);
		PACKET_DECODE(Byte, attackedRace);
		PACKET_DECODE(UInt32, attackedUd);
		PACKET_DECODE(UInt16, skillId);
		PACKET_DECODE(UInt16, x);
		PACKET_DECODE(UInt16, y);
		PACKET_DECODE(Byte, prof);

	IMPLEMENT_PACKET_DECODE_END

	IMPLEMENT_PACKET_ENCODE_BEGIN
	PACKET_ENCODE(Byte, PROTOCOL_CMD_BATTLE);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_BATTLE_SKILL_ATTACK);
	PACKET_ENCODE(Double, battleId);
	PACKET_ENCODE(Byte, race);
	PACKET_ENCODE(UInt32, ud);
	PACKET_ENCODE(UInt32, attackedUid);
	PACKET_ENCODE(Byte, attackedRace);
	PACKET_ENCODE(UInt32, attackedUd);
	PACKET_ENCODE(UInt16, skillId);
	PACKET_ENCODE(UInt16, x);
	PACKET_ENCODE(UInt16, y);
	PACKET_ENCODE(Byte, prof);
	IMPLEMENT_PACKET_ENCODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSkillUpProtocol)
	byte cmd;
	byte subCmd;
	uint16_t skillId;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt16, skillId);
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSyncSkillToBattle)
	byte cmd;
	byte subCmd;
	double battleId;
	uint32_t ud;
	byte size;
	vector<uint16_t> ids;
	vector<uint16_t> level;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(Double, battleId);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(Byte, size);
		ids.resize(size);
		level.resize(size);
		for(size_t index = 0; index < size; ++index)
		{
			PACKET_DECODE(UInt16, ids[index]);
			PACKET_DECODE(UInt16, level[index]);
		}
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END


DEFINE_RECEIVE_PACKET_BEGIN(CSkillUseProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_RECEIVE_PACKET_BEGIN(CSkillStatusProtocol)
	byte cmd;
	byte subCmd;
	uint32_t ud;
	uint32_t status;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, ud);
		PACKET_DECODE(UInt32, status);
	IMPLEMENT_PACKET_DECODE_END

DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOLSKILL_H_ */
