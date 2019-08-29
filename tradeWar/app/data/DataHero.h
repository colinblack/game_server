#ifndef __DATA_HERO_H__
#define __DATA_HERO_H__

#include "Kernel.h"
#include "AsyncDBInterface.h"
#include "DataTableUidIdData.h"

TABLE_UID_ID_DATA_HEAD(Hero, HERO)

/*
struct DataHero
{
	uint32_t uid;
	uint32_t id;
	string   data;
};

class CDataHero : public CDataBaseDBC, public AsyncDBInterface
{
public:
	CDataHero(int table = DB_HERO) : CDataBaseDBC(table) {}
	virtual void doRequest(CNetPacket* packet);

	int GetHero(unsigned uid, map<unsigned, string> &datas);
	int GetHero(unsigned uid, unsigned id, string &data);
	int GetHero(unsigned uid, vector<DataHero> &datas);

	int AddHero(const DataHero& dataHero);
	int RealAddHero(CNetPacket* packet);

	int SetHero(unsigned uid, unsigned id, const string &data);
	int SetHero(const DataHero& dataHero);
	int RealSetHero(CNetPacket* packet);

	int ReplaceHero(const DataHero& dataHero);
	int RealReplaceHero(CNetPacket* packet);

	int RemoveOneHero(unsigned uid, unsigned id);
	int RealRemoveOneHero(CNetPacket* packet);

	int RemoveHero(unsigned uid);
	int RealRemoveHero(CNetPacket* packet);

};
*/
#endif
