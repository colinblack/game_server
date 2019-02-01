/*
 *LogicRestriction.cpp
 *
 *  Created on: 2015-03-18
 *      Author: jimmy
 */

#include "LogicRestriction.h"


CLogicRestric::CLogicRestric() {
	// TODO Auto-generated constructor stub

}

CLogicRestric::~CLogicRestric() {
	// TODO Auto-generated destructor stub
}

CDataRestric* CLogicRestric::GetRestricData()
{
	GET_MEM_DATA_SEM(CDataRestric, ACTIVITY_RESTRIC_DATA, sem_restriction,false)

}

int CLogicRestric::GetRestricData(unsigned uid, Json::Value &result)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_E_TS))
	{
		error_log("activity_Restriction_time_error");
		return R_ERR_REFUSE;
	}
	CDataRestric *pdata= GetRestricData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_RestricData_fail");
	}

	vector <unsigned> num;
	int ret = pdata->GetRestricItemsNum(num);
	if(ret != 0)
	{
		return ret;
	}
	for(int i=0; i<num.size(); ++i)
	{
		result["id"][i] = num[i];
	}
	return 0;
}

int CLogicRestric::UpdateRestricData(unsigned uid, unsigned id, Json::Value &result)
{
	if(Time::GetGlobalTime() < Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_B_TS)
	|| Time::GetGlobalTime() > Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_E_TS))
	{
		error_log("activity_Restriction_time_error");
		return R_ERR_REFUSE;
	}
	CDataRestric *pdata= GetRestricData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_RestricData_fail");
	}

	vector <unsigned> num;
	bool flag = false;
	int ret = pdata->UpdateRare(id, num, flag);
	if(ret != 0)
	{
		return ret;
	}

	result["flag"] = flag;
	for(int i=0; i<num.size(); ++i)
	{
		result["id"][i] = num[i];
	}
	return 0;
}






