/*
 * DataDouble11.cpp
 *
 *  Created on: 2015-10-29
 *      Author: dawx5fsd
 */



#include "DataDouble11.h"


CDataDouble11::CDataDouble11() : m_init(false)
{
	string path = Config::GetPath(CONFIG_DOUBLE11_PATH);
	Init(path);
}


int CDataDouble11::Init(const string &path, semdat sem)
{
	if (m_init)
	{
		return 0;
	}

	int semgroup = 0;
	int semserver = 0;

	Config::GetDomain(semserver);
	if (!semserver)
	{
		Config::GetDB(semserver);
	}

	if (!m_sh.CreateOrOpen(path.c_str(), sizeof(Double11Prop), SEM_ID(sem, semgroup, semserver)))
	{
		error_log("init double11 data failed. path=%s", path.c_str());
		return R_ERROR;
	}

	CAutoLock lock(&(m_sh), true);

	if (!m_sh.HasInit())
	{
		Double11Prop *pdata = (Double11Prop *)m_sh.GetAddress();
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}

	m_init = true;

	return 0;
}


// must lock
int CDataDouble11::ResetData()
{
	int ret = 0;

	Double11Prop *pdata = (Double11Prop *)m_sh.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	unsigned now = Time::GetGlobalTime();
	unsigned configver = Config::GetIntValue(CONFIG_DOUBLE11_ALLSERVER_VER);

	if (CTime::IsDiffDay(now, pdata->lastts) || (configver != pdata->version))
	{
		CDataXML *dataxml = CDataXML::GetCDataXML();
		if (NULL == dataxml)
		{
			error_log("GetCDataXML failed");
			return R_ERR_DB;
		}

		ret = dataxml->GetDouble11AllData(pdata->dataDouble);
		if (ret)
		{
			return ret;
		}

		pdata->lastts = now;
		pdata->version = configver;
	}

	return R_SUCCESS;
}


int CDataDouble11::cpRcnt(Json::Value &rcnt)
{
	Double11Prop *pdata = (Double11Prop *)m_sh.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	rcnt.resize(XMLDOUBLE_TYPE_NUM * XMLDOUBLE_PROP_NUM);
	for (unsigned i = 0; i < XMLDOUBLE_TYPE_NUM; ++i)
	{
		for (unsigned j = 0; j < XMLDOUBLE_PROP_NUM; ++j)
		{
			rcnt[i * XMLDOUBLE_TYPE_NUM + j] = pdata->dataDouble.prop[i][j].total;
		}
	}

	return R_SUCCESS;

}


int CDataDouble11::GetRemainCount(Json::Value &rcnt)
{
	Double11Prop *pdata = (Double11Prop *)m_sh.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh), true);

	int ret = 0;

	ret = ResetData();
	if (ret)
	{
		return ret;
	}

	ret = cpRcnt(rcnt);
	if (ret)
	{
		return ret;
	}

	return R_SUCCESS;
}


int CDataDouble11::BuyOneProp(unsigned type, unsigned id, XMLDouble11Prop &prop, bool &nocnt)
{
	Double11Prop *pdata = (Double11Prop *)m_sh.GetAddress();

	if (NULL == pdata)
	{
		return R_ERR_DB;
	}

	CAutoLock lock(&(m_sh), true);
	int ret = R_SUCCESS;


	ret = ResetData();
	if (ret)
	{
		return ret;
	}

	if (pdata->dataDouble.prop[type][id].total > 0)
	{
		nocnt = false;
		pdata->dataDouble.prop[type][id].total--;
		prop = pdata->dataDouble.prop[type][id];
	}
	else
	{
		nocnt = true;
	}

	return R_SUCCESS;
}
