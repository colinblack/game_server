/*
 * DataAllServerMapBufferBuffer.cpp
 *
 *  Created on: 2015-9-17
 *      Author: Ralf
 */


#include "DataAllServerMapBuffer.h"

CDataAllServerMapBuffer* CDataAllServerMapBuffer::m_pData = NULL;

CDataAllServerMapBuffer::CDataAllServerMapBuffer()
{
	m_init = false;
}

int CDataAllServerMapBuffer::init(const std::string &path, semdat sem)
{
	if(m_init)
		return 0;

	int semgroup = 0;
	int semserver = 0;
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataAllServerMapBuffer), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_allservermapbuffer_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	DataAllServerMapBuffer *pdata = (DataAllServerMapBuffer *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);

	if(!m_sh.HasInit())
	{
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}

	m_init = true;

	return 0;
}

CDataAllServerMapBuffer* CDataAllServerMapBuffer::GetCDataAllServerMapBuffer()
{
	if(!m_pData)
	{
		m_pData = new CDataAllServerMapBuffer;
		string dataPath = MainConfig::GetAllServerPath(CONFIG_ALL_SERVER_MAP_BUFFER_PATH);
		if (dataPath.empty())
		{
			return NULL;
		}
		int ret = m_pData->init(dataPath,sem_allserver_map_buffer);
		if(ret)
		{
			delete m_pData;
			return NULL;
		}
	}
	return m_pData;
}

int CDataAllServerMapBuffer::Get(map<unsigned, unsigned> &res)
{
	DataAllServerMapBuffer *pdata = (DataAllServerMapBuffer *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);

	if(pdata->count == 0)
		return R_ERR_DATA_LIMIT;

	for(int i=0;i<pdata->count;++i)
		res[pdata->user[i].uid] = pdata->user[i].level;

	memset(pdata, 0, sizeof(*pdata));

	return 0;
}

int CDataAllServerMapBuffer::Set(unsigned uid, unsigned level)
{

	DataAllServerMapBuffer *pdata = (DataAllServerMapBuffer *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		return R_ERR_DB;
	}
	CAutoLock lock(&m_sh, true);

	if(pdata->count < ALL_SERVER_MAP_BUFFER_USER_NUM)
	{
		pdata->user[pdata->count].uid = uid;
		pdata->user[pdata->count].level = level;
		++pdata->count;
	}

	return 0;
}
