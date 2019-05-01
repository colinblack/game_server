/*
 * DataBuildingManager.h
 *
 *  Created on: 2016-8-31
 *      Author: dawx62fac
 */

#ifndef DATABUILDINGMANAGER_H_
#define DATABUILDINGMANAGER_H_

#include "DataBase.h"
#include "DataBuilding.h"


class DataBuildQueue
	: public DataSingleton<DBCBuidingQueueData, DB_BUILD_QUEUE, DB_BASE_BUFF*DB_BASE_FULL, DBCBuildingQueueHandler, DB_BASE_FULL>
	, public CSingleton<DataBuildQueue>
{
//
	typedef DataSingleton<DBCBuidingQueueData, DB_BUILD_QUEUE, DB_BASE_BUFF*DB_BASE_FULL, DBCBuildingQueueHandler, DB_BASE_FULL> base;
private:
	int FreeIndex();

	int GetIndex(unsigned uid);
public:
	int OnInit();

	virtual void CallDestroy() { Destroy();}

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	unsigned UserId2Index(unsigned uid);

	//新建
	int New(unsigned uid);
	int Load(unsigned uid);
private:
	std::map<unsigned, unsigned> m_map;
};


class DataBuildingManager
	: public DataSingleton<DBCBuildingData, DB_BUILDING, DB_BASE_BUFF*DB_BUILDING_FACTOR, DBCBuildingHandler, DB_BUILDING_FACTOR>
	, public CSingleton<DataBuildingManager>
{
#if 0
	enum {
			FOLK_HOUSE = 0, //民居
			TIMBER_YARD, 	//木场
			FARMLAND,		//农田
			MINE_FIELD,		//矿场
			BARRACKS,		//兵营
			BUID_TYPES
	};
#endif

public:
	enum {
		FOLK_HOUSE_TYPE 	= 1, //民居
		TIMBER_YARD_TYPE 	= 2, //木场
		FARMLAND_TYPE 		= 3, //农田
		MINE_FIELD_TYPE 	= 4, //矿场
		BARRACKS_TYPE		= 5, //兵营
		BUID_TYPES
	};


	typedef DataSingleton<DBCBuildingData, DB_BUILDING, DB_BASE_BUFF*DB_BUILDING_FACTOR, DBCBuildingHandler, DB_BUILDING_FACTOR> base;
private:
	int FreeIndex();

	int NewItem(unsigned uid, unsigned build_id);

	bool IsInMap(unsigned uid);
public:
	int OnInit();

	virtual void CallDestroy() { Destroy();}

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	int IndexFromBuildId(unsigned uid, unsigned id);

	unsigned GetIndex(unsigned uid, unsigned build_id);

	//建筑ID转换成类型
	int BuildId2Type(unsigned id) const;

	//新建
	int New(unsigned uid);
	//加载
	int Load(unsigned uid);


	//获取所以的同类建筑
	void GetBuildIds(unsigned uid, unsigned type, std::vector<unsigned>& result);
	void IndexsBuildsByType(unsigned uid, unsigned type, std::vector<unsigned>& result);


	//资源产量 type--建筑类型 1-5; throw exception
	//unsigned Yields(unsigned uid, int type);
	//资源的容量  throw exception
	//unsigned Capacity(unsigned uid, int type);

private:
	std::multimap<unsigned, unsigned> m_mapTb[BUID_TYPES - 1];

	std::map<unsigned, bool> m_new_user;
};


#endif /* DATABUILDINGMANAGER_H_ */
