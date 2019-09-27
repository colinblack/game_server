#ifndef __DATA_BUILDING_H__
#define __DATA_BUILDING_H__

#include "Kernel.h"
#include "AsyncDBInterface.h"
#include "DataTableUidIdData.h"

TABLE_UID_ID_DATA_HEAD(Building, BUILDING)
/*
struct DataBuilding
{
	uint32_t uid;
	uint32_t id;
	string   data;
};

class CDataBuilding : public CDataBaseDBC, public AsyncDBInterface
{
public:
	CDataBuilding(int table = DB_BUILDING) : CDataBaseDBC(table) {}
	virtual void doRequest(CNetPacket* packet);

	int GetBuilding(unsigned uid, unsigned id, string &data);
	int GetBuilding(unsigned uid, vector<DataBuilding> &datas);
	int GetBuilding(unsigned uid, map<unsigned, string> &datas);

	int AddBuilding(const DataBuilding& dataBuilding);
	int RealAddBuilding(CNetPacket* packet);

	int SetBuilding(uint32_t uid, uint32_t id, const string& data);
	int SetBuilding(const DataBuilding& dataBuilding);
	int RealSetBuilding(CNetPacket* packet);

	int ReplaceBuilding(const DataBuilding& dataBuilding);
	int RealReplaceBuilding(CNetPacket* packet);

	int RemoveOneBuilding(unsigned uid, unsigned id);
	int RealRemoveOneBuilding(CNetPacket* packet);

	int RemoveBuilding(unsigned uid);
	int RealRemoveBuilding(CNetPacket* packet);

};
*/
#endif
