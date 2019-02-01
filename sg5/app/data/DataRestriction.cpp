/*
 * DataRestriction.cpp
 *
 *  Created on: 2015-03-18
 *      Author: jimmy
 */

#include "DataRestriction.h"

const unsigned CDataRestric::max_num[RESTRIC_ITEMS_NUM] = {88, 88, 88, 88, 88, 88, 66, 66};

CDataRestric::CDataRestric(){
	m_init = false;
}
CDataRestric::~CDataRestric() {
	// TODO Auto-generated destructor stub
}

int CDataRestric::Init(const std::string &path, semdat sem)
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
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataRestric), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_DataRestric_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		DataRestric *pdata = (DataRestric *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_DataRestric_data_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}


int CDataRestric::GetRestricItemsNum(vector <unsigned> &num)
{
	DataRestric *pdata = (DataRestric *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_DataRestric_data_fail");
	}
	CAutoLock lock(&m_sh, true);

	time_t now;
	time(&now);
	struct tm *pTm = localtime(&now);
	int tempSec = pTm->tm_sec;
	int tempMin = pTm->tm_min;
	int tempHour = pTm->tm_hour;
	unsigned tempNow = tempSec + tempMin * 60 + tempHour *3600;

	if(Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_VER) != pdata->version)
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_ACTIVITY_RESTRICTION_VER);
		pdata->ts = now;
		for(int i=0; i<RESTRIC_ITEMS_NUM; ++i)
			pdata->ItemsNumbers[i] = max_num[i];
	}
	if(CTime::IsDiffDay(pdata->ts, now) && tempNow>37800)
	{
		pdata->ts = now;
		for(int i=0; i<RESTRIC_ITEMS_NUM; ++i)
			pdata->ItemsNumbers[i] = max_num[i];

	}

	for(int i=0; i<RESTRIC_ITEMS_NUM; ++i)
	{
		num.push_back(pdata->ItemsNumbers[i]);
	}

	return 0;
}

int CDataRestric::UpdateRare(unsigned id, vector <unsigned> &num, bool &flag)
{
	DataRestric *pdata = (DataRestric *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_DataRestric_data_fail");
	}
	CAutoLock lock(&m_sh, true);

	if(id >= RESTRIC_ITEMS_NUM)
	{
		error_log("id_error,id=%u",id);
		return R_ERR_DATA;
	}

	if(pdata->ItemsNumbers[id] == 0)
	{
		flag = false;
		for(int i=0; i<RESTRIC_ITEMS_NUM; ++i)
		{
			num.push_back(pdata->ItemsNumbers[i]);
		}
		return 0;
	}

	pdata->ItemsNumbers[id] -= 1;
	flag = true;
	for(int i=0; i<RESTRIC_ITEMS_NUM; ++i)
	{
		num.push_back(pdata->ItemsNumbers[i]);
	}
	return 0;
}
