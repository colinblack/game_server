/*
 *LogicRestriction.h
 *
 *  Created on: 2015-03-18
 *      Author: jimmy
 */

#ifndef LOGICRESTRICTION_H___
#define LOGICRESTRICTION_H___
#include "LogicInc.h"
class CLogicRestric {
public:
	CLogicRestric();
	~CLogicRestric();
	static CDataRestric* GetRestricData();
	int GetRestricData(unsigned uid, Json::Value &result);
	int UpdateRestricData(unsigned uid, unsigned id, Json::Value &result);

};
#endif /* LOGICRESTRICTION_H___ */
