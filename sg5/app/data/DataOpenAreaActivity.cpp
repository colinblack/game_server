/*
 * DataOpenAreaActivity.cpp
 *
 *  Created on: 2013-09-02
 *      Author: Administrator
 */

#include "DataOpenAreaActivity.h"



CDataOpenAreaActivity::CDataOpenAreaActivity(){
	m_init = false;
}
CDataOpenAreaActivity::~CDataOpenAreaActivity() {
	// TODO Auto-generated destructor stub
}

int  CDataOpenAreaActivity::Init(const std::string &path, semdat sem)
{
	if(m_init)
	{
		return 0;
	}
	int semgroup = 0;
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataOpenAreaData), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_open_area_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		DataOpenAreaData *pdata = (DataOpenAreaData *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_open_area_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}



int CDataOpenAreaActivity::UpdateOpenAreaActivityList( unsigned uid,int grade_range,Json::Value &result)
{
	DataOpenAreaData *pdata = (DataOpenAreaData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_open_area_fail");
	}
	CAutoLock lock(&m_sh, true);

	if((Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_OPEN_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_OPEN_TS) + 7*24*60*60))
	{
		int flag = 0;
		int size_max = 0;
		if(0 == grade_range)
			size_max = LEVEL_1_SIZE;
		else if(1 == grade_range)
			size_max = LEVEL_2_SIZE;
		else if(2 == grade_range)
			size_max = LEVEL_3_SIZE;
		else if(3 == grade_range)
			size_max = LEVEL_4_SIZE;
		else if(4 == grade_range)
			size_max = LEVEL_5_SIZE;
		else if(5 == grade_range)
			size_max = LEVEL_6_SIZE;
		else if(6 == grade_range)
			size_max = LEVEL_7_SIZE;
		else if(7 == grade_range)
			size_max = LEVEL_8_SIZE;

		for(int i = 0;i < size_max; ++i)
		{
			if(pdata->uid[grade_range][i] == uid)
			{
				flag = 1;
				break;
			}
			else if(pdata->uid[grade_range][i] == 0 )
			{
				pdata->uid[grade_range][i] = uid;
				flag = 2;
				break;
			}

		}
		result["flag"] = flag;		//0为奖励已领完 , 1为已领过奖励  , 2为成功领到奖励

	}
	return 0;
}

int CDataOpenAreaActivity::GetOpenAreaActivityList( unsigned uid,Json::Value &result)
{
	DataOpenAreaData *pdata = (DataOpenAreaData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_open_area_fail");
	}
	CAutoLock lock(&m_sh, true);

	if((Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_OPEN_TS))
		&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_OPEN_TS) + 7*24*60*60))
	{
		for(int i = 0; i < GRADE_RANGE;++i)
		{
			int flag = 0;
			int get_num = 0;
			int size_max = 0;
			if(0 == i)
				size_max = LEVEL_1_SIZE;
			else if(1 == i)
				size_max = LEVEL_2_SIZE;
			else if(2 == i)
				size_max = LEVEL_3_SIZE;
			else if(3 == i)
				size_max = LEVEL_4_SIZE;
			else if(4 == i)
				size_max = LEVEL_5_SIZE;
			else if(5 == i)
				size_max = LEVEL_6_SIZE;
			else if(6 == i)
				size_max = LEVEL_7_SIZE;
			else if(7 == i)
				size_max = LEVEL_8_SIZE;

			for(int j =0; j < size_max;j++)
			{
				if(pdata->uid[i][j] != 0)
					get_num++;

				if(pdata->uid[i][j] == uid)
				{
					flag = 1;
				}
			}

			result["flag"][i] = flag;
			result["num"][i] = size_max - get_num;
		}
	}

	return 0;
}

