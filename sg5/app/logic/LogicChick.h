/*
 * LogicChick.h
 *
 *  Created on: 2018年7月26日
 *      Author: Ralf
 */

#ifndef APP_LOGIC_LOGICCHICK_H_
#define APP_LOGIC_LOGICCHICK_H_


#include "LogicInc.h"
#include "LogicBase.h"

class CLogicChick : public LogicBase<CDataChick>
{
public:
	CLogicChick(){}
	~CLogicChick(){}

	int GetChickReg(unsigned uid, Json::Value &res);
	int ChickReg(unsigned uid, Json::Value &data, Json::Value &res);
};




#endif /* APP_LOGIC_LOGICCHICK_H_ */
