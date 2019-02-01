
/*
 * LogicOpenAreaActivity.cpp
 *
 *  Created on: 2014-09-02
 *      Author: Administrator
 */

#include "LogicOpenAreaActivity.h"


CLogicOpenAreaActivity::CLogicOpenAreaActivity() {
	// TODO Auto-generated constructor stub

}

CLogicOpenAreaActivity::~CLogicOpenAreaActivity() {
	// TODO Auto-generated destructor stub
}

CDataOpenAreaActivity* CLogicOpenAreaActivity::GetOpenAreaActivityPoint()
{
	GET_MEM_DATA_SEM(CDataOpenAreaActivity, OPEN_AREA_PATH, sem_openarea_activity,false)
}

int CLogicOpenAreaActivity::GetOpenAreaActivitySelfData(unsigned uid, Json::Value &result)
{
	CDataOpenAreaActivity *pdata= GetOpenAreaActivityPoint();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_openarea_activity_fail");
	}
	int ret = pdata->GetOpenAreaActivityList(uid,result);
	if(ret)
	{
		error_log("[get_openarea_activity_fail] [uid=%u]",uid);
		return ret;
	}
	return 0;
}
int CLogicOpenAreaActivity::UpdateOpenAreaActivitySelfData(unsigned uid,int grade_range,Json::Value &result)
{
	CDataOpenAreaActivity *pdata= GetOpenAreaActivityPoint();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_openarea_activity_fail");
	}

	int ret = pdata->UpdateOpenAreaActivityList(uid,grade_range,result);
	if(ret != 0)
	{
		return ret;
	}


	return 0;
}







