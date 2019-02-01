#ifndef DATA_USER_ATTACK_H_
#define DATA_USER_ATTACK_H_

#include "Kernel.h"

struct DataUserAttack
{
	unsigned uid;
	uint64_t attack_id;
	unsigned opposite_uid;
	int opposite_platform;
	unsigned defence_baseid;
	int type;
	int status;
	unsigned start_time;
};

class CDataUserAttack : public CDataBaseDBC
{
public:

	CDataUserAttack(int table = DB_USER_ATTACK) : CDataBaseDBC(table) {}

public:
	int AddUserAttack(DataUserAttack &data);

	//baseid == 0 忽略
	int SetUserAttacksStatus(unsigned uid, int statusOld, int type, int baseid, int status);

	int GetUserAttacksAfter(unsigned uid, unsigned time, vector<DataUserAttack> &datas);

	//time == 0 忽略
	//baseid == 0 忽略
	int GetUserAttacksCondition(unsigned uid, int status, int type,
			unsigned baseid, unsigned time, vector<DataUserAttack> &datas);

	//baseid == 0 忽略
	int GetUserAttacksCondition(unsigned uid, unsigned time, int type, unsigned baseid, vector<DataUserAttack> &datas);

	//baseid == 0 忽略
	//opposite_uid == 0 忽略
	int GetUserAttacksCount(unsigned uid, unsigned time, int type, unsigned baseid, unsigned opposite_uid, int &count);
};

#endif
