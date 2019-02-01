/*
 * LogicCrowdFunding.h
 *
 *  Created on: 2016-1-25
 *      Author: Ralf
 */

#ifndef LOGICCROWDFUNDING_H_
#define LOGICCROWDFUNDING_H_

#include "LogicInc.h"
#include "LogicBase.h"

class CLogicCrowdFunding : public LogicBase<CDataCrowdFunding>
{
public:
	CLogicCrowdFunding(){}
	~CLogicCrowdFunding(){}
	int Get(unsigned uid, Json::Value &result);
	int Buy(unsigned uid, unsigned id, unsigned need, Json::Value &result);
	int _Get(unsigned uid, Json::Value &result);
	int _Buy(unsigned uid, unsigned id, unsigned need, Json::Value &result);
};


#endif /* LOGICCROWDFUNDING_H_ */
