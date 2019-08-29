/*
 * DataSkill.h
 *
 *  Created on: 2016年1月22日
 *      Author: Administrator
 */

#ifndef _DATA_SKILL_H_
#define _DATA_SKILL_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataSkill
{
	uint32_t uid;
	uint16_t skillId;
	uint16_t level;
	uint32_t lastUpTime;
	uint32_t count;
	byte status;

	DataSkill():uid(0), skillId(0), level(0), lastUpTime(0), count(0), status(0)
	{
	}
	uint32_t getLeftUpTime()
	{
		return time(NULL) < lastUpTime ? lastUpTime - time(NULL) : 0;
	}
	void encode(IBuffer *pBuffer) const
	{
		CBufferWriter writer(pBuffer);
		uint32_t ts = static_cast<uint32_t>(time(NULL));
		writer.AppendUInt16(skillId);
		writer.AppendUInt32(level);
		writer.AppendUInt32(ts < lastUpTime ? lastUpTime - ts : 0);
		writer.AppendByte(status);
		writer.AppendUInt32(count);
	}
};

DECLARE_DBC_DATA_CLASS(CDataSkill, DB_SKILL)
	int AddSkill(const DataSkill& dataRide);
	int GetSkills(uint32_t uid, vector<DataSkill>& vecDataRides);
	int SetSkill(const DataSkill& dataRide);
	int RemoveSkill(uint32_t uid);

	virtual void doRequest(CNetPacket* packet);
	int RealAddSkill(CNetPacket *pPacket);
	int RealSetSkill(CNetPacket* packet);
	int RealRemoveSkill(CNetPacket* packet);
DECLARE_DBC_DATA_CLASS_END

#endif /* _DATA_SKILL_H_ */
