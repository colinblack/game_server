#include "DataKingTreasure.h"

CDataTreasureDepot* CDataTreasureDepot::m_pData = NULL;

CDataTreasureDepot::CDataTreasureDepot()
{
	m_init = false;
}

CDataTreasureDepot::~CDataTreasureDepot()
{
	// TODO Auto-generated destructor stub
}

CDataTreasureDepot* CDataTreasureDepot::GetCDataTreasureDepot()
{
	if(!m_pData)
	{
		m_pData = new CDataTreasureDepot;
		string dataPath = Config::GetPath(DATA_KING_TREASURE);

		if (dataPath.empty())
		{
			return NULL;
		}

		int ret = m_pData->Init(dataPath, sem_king_treasure);

		if(ret)
		{
			delete m_pData;
			return NULL;
		}
	}

	return m_pData;
}

int CDataTreasureDepot::Init(const std::string &path, semdat sem)
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

	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataTreasureDepot), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_kingtreasure_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	CAutoLock lock(&m_sh, true);

	if(!m_sh.HasInit())
	{
		DataTreasureDepot *pdata = (DataTreasureDepot *)m_sh.GetAddress();

		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_kingtreasure_data_fail");
		}

		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}

	m_init = true;

	//设置映射关系
	DataTreasureDepot *pdata = (DataTreasureDepot *)m_sh.GetAddress();

	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_kingtreasure_data_fail");
	}

	for(int i = 0; i < pdata->num; ++i)
	{
		unsigned id = pdata->boxes[i].id;

		if (id)  //非0的id
		{
			m_idPos[id] = i;
		}
	}

	return 0;
}

int CDataTreasureDepot::GetUsedTimes(unsigned id)
{
	if (!m_idPos.count(id))
	{
		return 0;
	}

	DataTreasureDepot *pdata = (DataTreasureDepot *)m_sh.GetAddress();

	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_kingtreasure_data_fail");
	}

	CAutoLock lock(&m_sh, true);

	unsigned pos = m_idPos[id];

	return pdata->boxes[pos].used;
}

int CDataTreasureDepot::AddUsedTimes(unsigned id, int times)
{
	DataTreasureDepot *pdata = (DataTreasureDepot *)m_sh.GetAddress();

	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_kingtreasure_data_fail");
	}

	CAutoLock lock(&m_sh, true);

	if (!m_idPos.count(id))
	{
		//之前未出现过，要求新增，则判断数组长度是否越界
		if (pdata->num >= MAX_BOX_NUMS)
		{
			error_log("box nums is max.");
			return 0;
		}

		//未越界，则新增长度，设置映射关系
		m_idPos[id] = pdata->num;

		pdata->boxes[pdata->num].id = id;
		pdata->num += 1;
	}

	unsigned pos = m_idPos[id];

	pdata->boxes[pos].used += times;

	return 0;
}

int CDataTreasureDepot::CheckVersion(unsigned version)
{
	DataTreasureDepot *pdata = (DataTreasureDepot *)m_sh.GetAddress();

	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_kingtreasure_data_fail");
	}

	CAutoLock lock(&m_sh, true);

	if (version != pdata->version)
	{
		//版本重置，旧版本数据清空
		pdata->version = version;
		pdata->num = 0;
		memset(pdata->boxes, 0, sizeof(pdata->boxes));

		m_idPos.clear();
	}

	return 0;
}


