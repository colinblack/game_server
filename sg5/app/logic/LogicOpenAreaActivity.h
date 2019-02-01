/*
 *LogicOpenAreaActivity.h
 *
 *  Created on: 2014-09-02
 *      Author: Administrator
 */

#ifndef LOGICOPENAREAACTIVITY_H_
#define LOGICOPENAREAACTIVITY_H_
#include "LogicInc.h"

class CLogicOpenAreaActivity {
public:
	CLogicOpenAreaActivity();
	virtual ~CLogicOpenAreaActivity();
	static CDataOpenAreaActivity* GetOpenAreaActivityPoint();

	int GetOpenAreaActivitySelfData(unsigned uid, Json::Value &result);
	int UpdateOpenAreaActivitySelfData(unsigned uid,int grade_range,Json::Value &result);

};
#endif /* LOGICOPENAREAACTIVITY_H_ */
