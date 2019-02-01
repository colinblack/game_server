/*
 * DataAllianceMember.h
 *
 *  Created on: 2011-9-19
 *      Author: dada
 */

#ifndef DATAALLIANCEMEMBER_H_
#define DATAALLIANCEMEMBER_H_

#include "Kernel.h"

struct DataAllianceMember
{
	unsigned alliance_id;
	unsigned uid;
	int type;
	uint64_t point;
	unsigned join_time;
	string extra_data;
};

class CDataAllianceMember : public CDataBaseDBC
{
public:
	CDataAllianceMember(int table = DB_ALLIANCE_MEMBER) : CDataBaseDBC(table) {}

public:
	int AddMember(const DataAllianceMember &member);
	int SetMember(const DataAllianceMember &member);
	int GetMember(unsigned alliance_id, unsigned uid, DataAllianceMember &member);
	int GetMembers(unsigned alliance_id, vector<DataAllianceMember> &members);
	int RemoveMember(unsigned alliance_id, unsigned uid);
	int RemoveMembers(unsigned alliance_id);

	int AddPoint(unsigned alliance_id, unsigned uid, int point);
	int SetMemberType(unsigned alliance_id, unsigned uid, int type);
	int GetMemberType(unsigned alliance_id, unsigned uid, int &type);
};

#endif /* DATAALLIANCEMEMBER_H_ */
