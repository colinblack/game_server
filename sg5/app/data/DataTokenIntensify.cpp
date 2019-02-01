/*
 * DataTokenIntensify.cpp
 *
 *  Created on: 2017-2-13
 *      Author: dawx62fac
 */

#include "DataTokenIntensify.h"


void ShTokenIntensify::Reset()
{
	for (int i = 0; i < ITEMS_CNT; i++)
	{
		index_cnt_[i] = 0;
	}

	ts_ = Time::GetGlobalTime();
}

void ShTokenIntensify::Accumulaive(int index, unsigned cnt)
{
	if (index < 0 || index >= ShTokenIntensify::ITEMS_CNT)
	{
		throw std::runtime_error("zone_data_index_out_range");
	}

	if (! Time::IsToday(ts_))
	{
		Reset();
	}

	index_cnt_[index] += cnt;
}

unsigned ShTokenIntensify::GetExchangeCnt(int index)
{
	if (index <0 || index >= ShTokenIntensify::ITEMS_CNT)
	{
		throw std::runtime_error("zone_data_index_out_range");
	}

	if (! Time::IsToday(ts_))
	{
		Reset();
	}

	return index_cnt_[index];
}

/////////////////////////////////////////////////////////////
ShDataTokenIntensify::ShDataTokenIntensify()
	: m_init(false)
{

}

int ShDataTokenIntensify::Init(const std::string &path, semdat sem)
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
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(ShTokenIntensify), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_open_area_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		ShTokenIntensify *pdata = (ShTokenIntensify *)m_sh.GetAddress();
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

unsigned ShDataTokenIntensify::GetExchangeCnt(int index)
{
	ShTokenIntensify *pdata = (ShTokenIntensify *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		throw std::runtime_error("get_sh_addr_error");
	}
	CAutoLock lock(&m_sh, true);

	return pdata->GetExchangeCnt(index);
}

void ShDataTokenIntensify::Accumulaive(int index, unsigned cnt)
{
	ShTokenIntensify *pdata = (ShTokenIntensify *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		throw std::runtime_error("get_sh_addr_error");
	}
	CAutoLock lock(&m_sh, true);

	pdata->Accumulaive(index, cnt);
}

void ShDataTokenIntensify::Reset()
{
	ShTokenIntensify *pdata = (ShTokenIntensify *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		throw std::runtime_error("get_sh_addr_error");
	}
	CAutoLock lock(&m_sh, true);

	pdata->Reset();
}


