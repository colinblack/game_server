/*
 * LogicAttackInfo.h
 *
 *  Created on: 2017年6月1日
 *      Author: Administrator
 */

#ifndef LOGICATTACKINFO_H_
#define LOGICATTACKINFO_H_

#include "LogicInc.h"
#include "ProtoAttackInfo.pb.h"

struct AttackBuilding{
	uint32_t ud;
	int32_t hp;
	int32_t res;
	AttackBuilding(){
		ud = hp = res = 0;
	}
	AttackBuilding(uint32_t _ud, int32_t _hp, int32_t _res){
		ud = _ud;
		hp = _hp;
		res = _res;
	}
	AttackBuilding& operator=(const AttackBuilding &data){
		ud = data.ud;
		hp = data.hp;
		res = data.res;
		return *this;
	}
};


class CLogicAttackInfo
{
public:
	CLogicAttackInfo(unsigned uid);
	virtual ~CLogicAttackInfo();
	int GetInfo(Json::Value &result);
	int SetInfo(const Json::Value &data);
	int ClearBuildingInfo();
private:
	int Read(Json::Value &result);
	int Save(bool isclearbuilding = false);
	int GetDataPath(string &dataPath);
private:
	unsigned m_uid;
	map<unsigned, int> m_hero;
	map<unsigned, AttackBuilding> m_building;
	map<unsigned, int> m_res;
	unsigned m_attackts;
};

#endif /* LOGICATTACKINFO_H_ */
