/*
 * DataSkill.cpp
 *
 *  Created on: 2016年1月22日
 *      Author: aaron
 *        desc: skill data table
 */

#include "DataSkill.h"
#include "AsyncDBManager.h"

#define OP_ADD_SKILL 1
#define OP_SET_SKILL 2
#define OP_REMOVE_SKILL 3

int CDataSkill::AddSkill(const DataSkill& skill)
{
	DB_ENCODE_BEGIN(DB_SKILL, OP_ADD_SKILL);
	DB_ENCODE(UInt32, skill.uid);
	DB_ENCODE(UInt16, skill.skillId);
	DB_ENCODE(UInt16, skill.level);
	DB_ENCODE(UInt32, skill.lastUpTime);
	DB_ENCODE(Byte, skill.status);
	DB_ENCODE(UInt32, skill.count);
	DB_ENCODE_END;
	return 0;
}

int CDataSkill::GetSkills(uint32_t uid, vector<DataSkill>& vecsSkills)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(skillId);
	DBCREQ_NEED(level);
	DBCREQ_NEED(lastUpTime);
	DBCREQ_NEED(status);
	DBCREQ_NEED(count);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;

	DBCREQ_ARRAY_GET_BEGIN(vecsSkills);
	DBCREQ_ARRAY_GET_INT(vecsSkills, uid);
	DBCREQ_ARRAY_GET_INT(vecsSkills, skillId);
	DBCREQ_ARRAY_GET_INT(vecsSkills, level);
	DBCREQ_ARRAY_GET_INT(vecsSkills, lastUpTime);
	DBCREQ_ARRAY_GET_INT(vecsSkills, status);
	DBCREQ_ARRAY_GET_INT(vecsSkills, count);
	DBCREQ_ARRAY_GET_END();
	return 0;
}

int CDataSkill::SetSkill(const DataSkill& skill)
{
	DB_ENCODE_BEGIN(DB_SKILL, OP_SET_SKILL);
	DB_ENCODE(UInt32,skill.uid);
	DB_ENCODE(UInt16,skill.skillId);
	DB_ENCODE(UInt16,skill.level);
	DB_ENCODE(UInt32,skill.lastUpTime);
	DB_ENCODE(Byte,skill.status);
	DB_ENCODE(UInt32,skill.count);
	DB_ENCODE_END;
	return 0;
}

int CDataSkill::RemoveSkill(uint32_t uid)
{
	DB_ENCODE_BEGIN(DB_SKILL, OP_REMOVE_SKILL);
	DB_ENCODE(UInt32, uid);
	DB_ENCODE_END;
	return 0;
}

int CDataSkill::RealAddSkill(CNetPacket *pPacket)
{
	DataSkill skill;
	DB_DECODE_BEGIN(&pPacket->body);
	DB_DECODE(UInt32, skill.uid);
	DB_DECODE(UInt16, skill.skillId);
	DB_DECODE(UInt16, skill.level);
	DB_DECODE(UInt32, skill.lastUpTime);
	DB_DECODE(Byte, skill.status);
	DB_DECODE(UInt32, skill.count);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::InsertRequest, skill.uid);
	DBCREQ_SET_KEY(skill.uid);
	DBCREQ_SET_INT(skill, skillId);
	DBCREQ_SET_INT(skill, level);
	DBCREQ_SET_INT(skill, lastUpTime);
	DBCREQ_SET_INT(skill, status);
	DBCREQ_SET_INT(skill, count);
	DBCREQ_EXEC;

	return 0;
}

int CDataSkill::RealSetSkill(CNetPacket* packet)
{
	DataSkill skill;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, skill.uid);
	DB_DECODE(UInt16, skill.skillId);
	DB_DECODE(UInt16, skill.level);
	DB_DECODE(UInt32, skill.lastUpTime);
	DB_DECODE(Byte, skill.status);
	DB_DECODE(UInt32, skill.count);
	DB_DECODE_END;

	DBCREQ_DECLARE(DBC::ReplaceRequest, skill.uid);
	DBCREQ_SET_KEY(skill.uid);
	DBCREQ_SET_INT(skill, skillId);
	DBCREQ_SET_INT(skill, level);
	DBCREQ_SET_INT(skill, lastUpTime);
	DBCREQ_SET_INT(skill, status);
	DBCREQ_SET_INT(skill, count);
	DBCREQ_EXEC;

	return 0;
}

int CDataSkill::RealRemoveSkill(CNetPacket* packet)
{
	uint32_t uid = 0;
	DB_DECODE_BEGIN(&packet->body);
	DB_DECODE(UInt32, uid);
	DB_DECODE_END;
	DBCREQ_DECLARE(DBC::DeleteRequest, uid);
	DBCREQ_SET_KEY(uid);
	DBCREQ_EXEC;
	return 0;
}

OP_PROCESS_BEGIN(CDataSkill)
OP_PROCESS(OP_ADD_SKILL,RealAddSkill)
OP_PROCESS(OP_SET_SKILL,RealSetSkill)
OP_PROCESS(OP_REMOVE_SKILL,RealRemoveSkill)
OP_PROCESS_END
