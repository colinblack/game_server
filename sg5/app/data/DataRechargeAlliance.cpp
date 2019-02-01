
#include "DataRechargeAlliance.h"

CDataRechargeAlliance::CDataRechargeAlliance()
{
	m_init = false;
}

CDataRechargeAlliance::~CDataRechargeAlliance()
{
	// TODO Auto-generated destructor stub
}

int CDataRechargeAlliance::Init(const std::string &path,unsigned allianceid, semdat sem)
{
	if(m_init)
	{
		return 0;
	}

	if(!IsAllianceId(allianceid))
	{
		error_log("invalid AllianceId");
		return R_ERROR;
	}

	int semgroup = Config::GetZoneByAID(allianceid);
	int semserver = 0;
	Config::GetDomain(semserver);
	if(!semserver)
		Config::GetDB(semserver);
	string address = path;
	address.append("."+Convert::UIntToString(semgroup));
	if(!m_sh.CreateOrOpen(address.c_str(),sizeof(AllianceRechargeData),SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_recharge_alliance_data_fail!][path=%s]",path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		AllianceRechargeData *pdata = (AllianceRechargeData *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			error_log("get_AllianceRechargeData_fail");
			DB_ERROR_RETURN_MSG("init_recharge_alliance_fail");
		}
		memset(pdata,0,sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}

int CDataRechargeAlliance::GetRechargeAlliacneData(unsigned alliance_id,unsigned version,vector <AllianceMember> &All_data)
{
	AllianceRechargeData *pdata = (AllianceRechargeData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		error_log("get_AllianceRechargeData_fail");
		DB_ERROR_RETURN_MSG("get_AllianceRechargeData_fail");
	}
	CAutoLock lock(&m_sh, true);

	if(version == pdata->version_num)
	{
		for(int i = 0; i < NUMBER_OF_UNION; i++)
		{
			if(pdata->num_of_union[i].alliance_id == alliance_id)
			{
				for(int j = 0; j < ALLIANCE_MEMBER_MAX; j++)
				{
					if(pdata->num_of_union[i].num_of_people[j].uid != 0)
					{
						All_data.push_back(pdata->num_of_union[i].num_of_people[j]);
					}
				}
			}
		}
	}
	else								//first get
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version_num = version;
	}
	return 0;
}

int CDataRechargeAlliance::UpdateRechargeAlliance(const AllianceMember &recharge,unsigned alliance_id,unsigned version)
{
	AllianceRechargeData *pdata = (AllianceRechargeData *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		error_log("get_AllianceRechargeData_fail");
		DB_ERROR_RETURN_MSG("get_AllianceRechargeData_fail");
	}
	CAutoLock lock(&m_sh, true);

	if(version == pdata->version_num)
	{
		for(int i = 0; i < NUMBER_OF_UNION; i++)
		{
			if(pdata->num_of_union[i].alliance_id == alliance_id)
			{
				for(int j = 0; j < ALLIANCE_MEMBER_MAX; j++)
				{
					if(pdata->num_of_union[i].num_of_people[j].uid == recharge.uid)
					{
						pdata->num_of_union[i].num_of_people[j].cash += recharge.cash;
						break;
					}
					else if(pdata->num_of_union[i].num_of_people[j].uid == 0)    //personal first recharge
					{
						pdata->num_of_union[i].num_of_people[j].uid = recharge.uid;
						pdata->num_of_union[i].num_of_people[j].cash = recharge.cash;
						memcpy(pdata->num_of_union[i].num_of_people[j].name,recharge.name,sizeof(recharge.name) - 1);
						break;
					}
				}
				break;

			}
			else if(pdata->num_of_union[i].alliance_id == 0)  //alliance first people recharge
			{
				pdata->num_of_union[i].alliance_id = alliance_id;
				pdata->num_of_union[i].num_of_people[0].uid = recharge.uid;
				pdata->num_of_union[i].num_of_people[0].cash = recharge.cash;
				memcpy(pdata->num_of_union[i].num_of_people[0].name,recharge.name,sizeof(recharge.name) - 1);
				break;
			}
		}

	}
	else                       //activity first people recharge
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version_num = version;
		pdata->num_of_union[0].alliance_id = alliance_id;

		pdata->num_of_union[0].num_of_people[0].uid = recharge.uid;
		pdata->num_of_union[0].num_of_people[0].cash = recharge.cash;
		memcpy(pdata->num_of_union[0].num_of_people[0].name,recharge.name,sizeof(recharge.name) - 1);
	}
	return 0;
}

