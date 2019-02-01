#ifndef __DATA_ALLIANCE_BATTLE_H__
#define __DATA_ALLIANCE_BATTLE_H__

#include "Kernel.h"

#define CITY_RAG 10
#define M_CITY_NUM 6
#define C_CITY_NUM 3
#define K_CITY_NUM 1
#define AB_CITY_NUM (M_CITY_NUM + C_CITY_NUM * 3 + K_CITY_NUM)
#define KINGDOM_1_CITY_NUM (M_CITY_NUM)
#define KINGDOM_2_CITY_NUM (M_CITY_NUM + C_CITY_NUM)
#define KINGDOM_3_CITY_NUM (M_CITY_NUM + C_CITY_NUM * 2)
#define KINGDOM_K_CITY_NUM (M_CITY_NUM + C_CITY_NUM * 3)
#define BATTLE_NUM 8
#define BATTLE_NUM_K 16
#define PRICE_NUM 10

#define DATA_BATTLE_POINT_HEAD \
	unsigned aid;				\
	unsigned uid;			/*uid*/ \
	char     name[32];			/*姓名*/\
	unsigned challenger;	/*挑战者*/ \
	char     challengername[32];	\
	unsigned breathTs;      /*最近挑战者活跃时间*/

struct BattlePointLimit
{
	DATA_BATTLE_POINT_HEAD

	BattlePointLimit& operator=(const BattlePointLimit &point)
	{
		aid = point.aid;
		uid = point.uid;
		strcpy(name,point.name);
		challenger = point.challenger;
		strcpy(challengername,point.challengername);
		breathTs = point.breathTs;
		return *this;
	}
};

struct BattlePoint
{
	DATA_BATTLE_POINT_HEAD
	char     archive[1048128];		//存档

	BattlePoint& operator=(const BattlePoint &point)
	{
		aid = point.aid;
		uid = point.uid;
		strcpy(name,point.name);
		challenger = point.challenger;
		strcpy(challengername,point.challengername);
		breathTs = point.breathTs;
		strcpy(archive,point.archive);
		return *this;
	}
};

struct CityPrice
{
	unsigned aid;
	char     name[32];
	unsigned price;

	CityPrice& operator=(const CityPrice &point)
	{
		aid = point.aid;
		strcpy(name,point.name);
		price = point.price;
		return *this;
	}
};

#define DATA_ALLIANCE_BATTLE_HEAD \
	unsigned aid;				\
	char     name[32];			\
	unsigned flag;				\
	unsigned kingdom;				\
	unsigned challenger;	/*挑战者*/ \
	char     challengername[32];	\
	unsigned stage;

struct DataAllianceBattleLimit
{
	DATA_ALLIANCE_BATTLE_HEAD

	DataAllianceBattleLimit& operator=(const DataAllianceBattleLimit &city)
	{
		aid = city.aid;
		strcpy(name,city.name);
		flag = city.flag;
		kingdom = city.kingdom;
		challenger = city.challenger;
		strcpy(challengername,city.challengername);
		stage = city.stage;
		return *this;
	}
};
struct DataAllianceBattle
{
	DATA_ALLIANCE_BATTLE_HEAD
	CityPrice price[PRICE_NUM];
	BattlePoint point[BATTLE_NUM*2];

	DataAllianceBattle& operator=(const DataAllianceBattle &city)
	{
		aid = city.aid;
		strcpy(name,city.name);
		flag = city.flag;
		challenger = city.challenger;
		strcpy(challengername,city.challengername);
		stage = city.stage;
		unsigned i = 0;
		for(;i<PRICE_NUM;++i)
			price[i] = city.price[i];
		for(;i<BATTLE_NUM;++i)
			point[i] = city.point[i];
		return *this;
	}
};
struct DataAllianceBattle_K
{
	DATA_ALLIANCE_BATTLE_HEAD
	CityPrice price[PRICE_NUM];
	BattlePoint point[BATTLE_NUM_K*2];

	DataAllianceBattle_K& operator=(const DataAllianceBattle_K &city)
	{
		aid = city.aid;
		strcpy(name,city.name);
		flag = city.flag;
		challenger = city.challenger;
		strcpy(challengername,city.challengername);
		stage = city.stage;
		unsigned i = 0;
		for(;i<PRICE_NUM;++i)
			price[i] = city.price[i];
		for(;i<BATTLE_NUM_K;++i)
			point[i] = city.point[i];
		return *this;
	}
};
enum AllianceBattleStage
{
	AllianceBattle_Price = 0,
	AllianceBattle_Defence = 1,
	AllianceBattle_Attack = 2,
	AllianceBattle_Occupy = 3,

	AllianceBattle_max,
};

class CDataAllianceBattle
{
public:
	CDataAllianceBattle();
	int Init(const string &path, semdat sem=sem_alliance_battle);

	int GetCityLimit(unsigned cid, DataAllianceBattleLimit &data);
	int SetCityLimit(unsigned cid, DataAllianceBattleLimit &data);
	int GetAllCityLimit(DataAllianceBattleLimit *data);
	int SetAllCityLimit(DataAllianceBattleLimit *data);
	int GetCityPrice(unsigned cid, CityPrice *price);
	int SetCityPrice(unsigned cid, CityPrice *price);
	int GetAllCityPrice(vector<vector<CityPrice> > &price);
	int ClearAllCityPrice();
	int GetCityBattlePointLimit(unsigned cid, BattlePointLimit *defence, BattlePointLimit *attack);
	int GetBattlePointLimit(unsigned bid, BattlePointLimit &data);
	int SetBattlePointLimit(unsigned bid, BattlePointLimit &data);
	int GetAllBattlePointLimit(vector<vector<BattlePointLimit> > &defence, vector<vector<BattlePointLimit> > &attack);
	int SetAllBattlePointLimit(vector<vector<BattlePointLimit> > &defence, vector<vector<BattlePointLimit> > &attack);
	int SetAllBattlePoint(vector<vector<BattlePoint> > &defence, vector<vector<BattlePoint> > &attack);
	int ClearAllBattlePoint();
	int GetBattlePoint(unsigned bid, BattlePoint &data);
	int SetBattlePoint(unsigned bid, BattlePoint &data);
	int Cid2CityNum(unsigned cid);
	int Bid2BattleNum(unsigned bid);
	int Bid2CityNum(unsigned bid);

	static void copylimit(BattlePoint &to,const BattlePointLimit &from);
	static void copylimit(BattlePointLimit &to,const BattlePoint &from);
	static void copylimit(DataAllianceBattle &to,const DataAllianceBattleLimit &from);
	static void copylimit(DataAllianceBattleLimit &to,const DataAllianceBattle &from);
	static void copylimit(DataAllianceBattle_K &to,const DataAllianceBattleLimit &from);
	static void copylimit(DataAllianceBattleLimit &to,const DataAllianceBattle_K &from);

	int RepairAllianceID();
protected:
	CShareMemory m_sh[AB_CITY_NUM];
	bool m_init;
};

#endif
