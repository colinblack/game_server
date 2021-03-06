/*
 * LogicDoulbe11.cpp
 *
 *  Created on: 2015-10-29
 *      Author: dawx5fsd
 */


#include "LogicDouble11.h"


int CLogicDouble11::GetRemainCount(Json::Value &rcnt, bool allserver)
{
	int ret = 0;
	CDataDouble11 *pdata = CDataDouble11::getCDataDouble11(allserver);

	if (NULL == pdata)
	{
		error_log("getCDataDouble11 failed");
		return R_ERR_DB;
	}

	ret = pdata->GetRemainCount(rcnt);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CLogicDouble11::BuyOneProp(unsigned type, unsigned id, XMLDouble11Prop &prop, bool &nocnt, Json::Value &rcnt, bool allserver)
{
	if (type >= XMLDOUBLE_TYPE_NUM_2018 || id >= XMLDOUBLE_PROP_NUM)
	{
		return R_ERR_PARAM;
	}

	int ret = 0;
	CDataDouble11 *pdata = CDataDouble11::getCDataDouble11(allserver);

	if (NULL == pdata)
	{
		error_log("getCDataDouble11 failed");
		return R_ERR_DB;
	}

	ret = pdata->BuyOneProp(type, id, prop, nocnt, rcnt);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}
