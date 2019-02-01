#ifndef __LOGIC_BUILDING_H__
#define __LOGIC_BUILDING_H__

#include "LogicInc.h"
#define WATER_BUILDING_T 50

class CLogicBuilding
{
public:
	int InitializeBuilding(unsigned uid);
	int InitializeBuilding(unsigned uid,unsigned worldpos);

	int GetAllBuilding(unsigned uid, Json::Value &data);
	int GetBuilding(unsigned uid, unsigned worldpos,Json::Value &data,bool isMainBase);

	int UpdateBuilding(unsigned uid, unsigned worldpos, Json::Value &data, Json::Value &result,bool isMainBase, bool isAdmin=false);
	//int GetBuilding(unsigned uid, unsigned id, Json::Value &data);
	//int GetBuilding(unsigned uid, unsigned id, unsigned worldpos,Json::Value &data,bool isMainBase);
	int RemoveBuilding(unsigned uid, unsigned worldpos);
	int ImportBuilding(unsigned uid, unsigned worldpos,const Json::Value &data, bool isMainBase);

	int Get(unsigned uid, unsigned id, unsigned worldpos, bool isMainBase, Json::Value &data);
	int Del(unsigned uid, unsigned id, unsigned worldpos, bool isMainBase);
	int Chg(unsigned uid, unsigned id, unsigned worldpos, bool isMainBase, Json::Value &data);

	int Water(unsigned uid, unsigned uidBy);

private:
	void check_water(unsigned uid, Json::Value &old, Json::Value &data);
};

#endif
