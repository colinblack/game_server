/*
 *LogicGroupsFighting.h
 *
 *  Created on: 2013-08-20
 *      Author: Administrator
 */

#ifndef LOGICGROUPSFIGHTINF_H__
#define LOGICGROUPSFIGHTINF_H__
#include "LogicInc.h"
class CLogicGroupsFighting {
public:
	CLogicGroupsFighting();
	virtual ~CLogicGroupsFighting();
	static CDataGroupsFigthing* GetGroupsFightingData(int cityid);
	int GetGroupsFightingJsonData(int cityid,Json::Value &result,Json::Value &input,unsigned uid);       //获取所有的数据
	int LogicUpdatesFightingData(int cityid,Json::Value &input,unsigned uid,Json::Value &result);
	int LogicAddFullmorale(unsigned uid, int cityid);
	int CleanGroupsFightingDate(int cityid);

};
#endif /* LOGICGROUPSFIGHTING_H_ */
