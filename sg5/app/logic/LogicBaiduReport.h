/*
 * LogicBaiduReport.h
 *
 *  Created on: 2015-12-14
 *      Author: dawx5fsd
 */

#ifndef LOGICBAIDUREPORT_H_
#define LOGICBAIDUREPORT_H_


#include "LogicInc.h"

class CLogicBaiduReport
{
public:
	CLogicBaiduReport() {}
	~CLogicBaiduReport() {}

	int Report(unsigned uid, string &action);
};


#endif /* LOGICBAIDUREPORT_H_ */
