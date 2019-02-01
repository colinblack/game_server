/*
 * LogicNewWorldAllianceMap.h
 *
 *  Created on: 2015-12-22
 *      Author: Ralf
 */

#ifndef LOGICGVGMAP_H_
#define LOGICGVGMAP_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicNewWorldAllianceMap : public LogicBase<CDataNewWorldAllianceMap>
{
public:
	CLogicNewWorldAllianceMap(){}
	~CLogicNewWorldAllianceMap(){}
	int GetRoom(unsigned aid, Json::Value &result);
};


#endif /* LOGICGVGMAP_H_ */
