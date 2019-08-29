#ifndef DATA_ACTIVENESS_H_
#define DATA_ACTIVENESS_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataActiveness
{
	uint32_t uid;
	uint32_t ts;
	uint32_t score;
	uint32_t reward;
	string data;

	DataActiveness() : uid(0), ts(0), score(0), reward(0)
	{
		data.clear();
	}

	void Clear()
	{
		uid = 0;
		ts = 0;
		score = 0;
		reward = 0;
		data.clear();
	}
};

class CDataActiveness: public CDataBaseDBC, public AsyncDBInterface
{
public:
	CDataActiveness(int table = DB_ACTIVENESS) : CDataBaseDBC(table)
	{
	}
	~CDataActiveness()
	{
	}
public:
	int GetActiveness(uint32_t uid, DataActiveness &data);
	int RemoveActiveness(uint32_t uid);
	int UpdateActiveness(const DataActiveness &data);
	int AddActiveness(const DataActiveness &data);
	virtual void doRequest(CNetPacket* packet);
	int RealAddActiveness(CNetPacket* packet);
	int RealUpdateActiveness(CNetPacket* packet);
	int RealRemoveActiveness(CNetPacket* packet);
};

#endif
