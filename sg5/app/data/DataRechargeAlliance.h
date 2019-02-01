
#ifndef _DATA_RECHARGE_ALLIANCE_H
#define _DATA_RECHARGE_ALLIANCE_H

#include "Kernel.h"

#define NUMBER_OF_UNION 1000
#define ALLIANCE_MEMBER_MAX 100

struct AllianceMember
{
	unsigned uid;
	unsigned cash;
	char name[32];

public:
	AllianceMember()
	{
		uid = 0;
		cash = 0;
		memset(name,0,sizeof(name));
	}
};

struct NumberOfUnion
{
	unsigned alliance_id;
	AllianceMember num_of_people[ALLIANCE_MEMBER_MAX];
};

struct AllianceRechargeData
{
	int version_num;
	NumberOfUnion num_of_union[NUMBER_OF_UNION];
};

class CDataRechargeAlliance
{
public:
	CDataRechargeAlliance();
	virtual ~CDataRechargeAlliance();
	int Init(const string &path,unsigned allianceid, semdat sem=sem_recharge_alliance);
	int GetRechargeAlliacneData(unsigned alliance_id,unsigned version, vector <AllianceMember> &All_data);
	int UpdateRechargeAlliance(const AllianceMember &recharge,unsigned alliance_id,unsigned version);

private:
	bool m_init;
	CShareMemory m_sh;
};

#endif


