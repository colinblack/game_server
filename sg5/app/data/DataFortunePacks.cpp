#include "DataFortunePacks.h"

CDataFortunePacks* CDataFortunePacks::m_pData = NULL;

CDataFortunePacks::CDataFortunePacks()
{
	m_init = false;
}

CDataFortunePacks::~CDataFortunePacks()
{
	// TODO Auto-generated destructor stub
}

CDataFortunePacks* CDataFortunePacks::GetCDataFortunePacks()
{
	if(!m_pData)
	{
		m_pData = new CDataFortunePacks;
		string dataPath = Config::GetPath(DATA_SEQUENCE_CHARGE);

		if (dataPath.empty())
		{
			return NULL;
		}

		int ret = m_pData->Init(dataPath, sem_fortune_pack);

		if(ret)
		{
			delete m_pData;
			return NULL;
		}
	}

	return m_pData;
}

int CDataFortunePacks::Init(const std::string &path, semdat sem)
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

	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataFortunePacks), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_sequencecharge_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}

	CAutoLock lock(&m_sh, true);

	if(!m_sh.HasInit())
	{
		DataFortunePacks *pdata  = GetDataPointer();
		memset(pdata, 0, sizeof(*pdata));

		m_sh.SetInitDone();
	}

	m_init = true;

	return 0;
}

int CDataFortunePacks::GetGiftedUsers(vector<unsigned> & uids)
{
	DataFortunePacks *pdata  = GetDataPointer();

	CAutoLock lock(&m_sh, true);

	for(int i = 0; i < pdata->extranum; ++i)
	{
		if (pdata->userlist[i] == 0)
		{
			break;
		}

		uids.push_back(pdata->userlist[i]);
	}

	return 0;
}

unsigned CDataFortunePacks::GetParticipateNum()
{
	DataFortunePacks *pdata  = GetDataPointer();

	CAutoLock lock(&m_sh, true);

	return pdata->num;
}

unsigned CDataFortunePacks::GetExtraNum()
{
	DataFortunePacks *pdata  = GetDataPointer();

	CAutoLock lock(&m_sh, true);

	return pdata->extranum;
}

int CDataFortunePacks::Participate(unsigned uid, bool isgift)
{
	DataFortunePacks *pdata  = GetDataPointer();
	CAutoLock lock(&m_sh, true);

	//先增加参与活动的玩家个数
	pdata->num += 1;

	if (isgift && pdata->extranum < MAX_EXTRA_ITEMS)
	{
		pdata->userlist[pdata->extranum++] = uid;
	}

	return 0;
}

int CDataFortunePacks::CheckVersion(unsigned version)
{
	DataFortunePacks *pdata  = GetDataPointer();
	CAutoLock lock(&m_sh, true);

	if (version != pdata->version)
	{
		//版本重置，旧版本数据清空
		pdata->version = version;
		pdata->num = 0;
		pdata->extranum = 0;

		memset(pdata->userlist, 0, sizeof(pdata->userlist));
	}

	return 0;
}

DataFortunePacks * CDataFortunePacks::GetDataPointer()
{
	DataFortunePacks *pdata = (DataFortunePacks *)m_sh.GetAddress();

	if(pdata == NULL)
	{
		throw runtime_error("init_sequencecharge_data_fail");
	}

	return pdata;
}


