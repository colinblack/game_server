/*
 * DataNewLottry.cpp
 *
 *  Created on: 2015-02-03
 *      Author: jimmy
 */

#include "DataNewLottry.h"
#include "DataUserBasic.h"


CDataNewlottery::CDataNewlottery(){
	m_init = false;
}
CDataNewlottery::~CDataNewlottery() {
	// TODO Auto-generated destructor stub
}

int CDataNewlottery::Init(const std::string &path, semdat sem)
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
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(DataNewlottery), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init_datanewlottery_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		DataNewlottery *pdata = (DataNewlottery *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_datanewlottery_data_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}


int CDataNewlottery::GetNewLotteryActivity(unsigned uid, unsigned level, unsigned count, vector <unsigned> total, vector <unsigned> rate, vector <unsigned> id, vector <unsigned> type_id, vector <unsigned> eqid, vector <unsigned> num
		, vector <unsigned> &awards_id, vector <unsigned> &awards_eqid, vector <unsigned> &awards_typeid, vector <unsigned> &awards_num
		, vector <unsigned> &get_id, vector <unsigned> &over_num, vector <RareItemsWinner> &peoples)
{
	DataNewlottery *pdata = (DataNewlottery *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_datanewlottery_data_fail");
	}
	CAutoLock lock(&m_sh, true);
	map<unsigned, unsigned> lottery_rate;
	unsigned self_rate = 0;
	for(int i=0; i<id.size(); ++i)
	{
		for(int j=0; j<rate[i]; ++j)
		{
			lottery_rate[self_rate] = id[i];
			++self_rate;
		}
	}

	for(int i=0; i<count; ++i)
	{
		int rate_num = 0;
		rate_num = Math::GetRandomInt(10000);
//		cout<<"level:"<<level<<endl;
//		cout<<"id:"<<lottery_rate[rate_num]<<"  rate:"<<rate_num<<endl;
		for(int j=0; j<id.size(); ++j)
		{
			if(id[j] == lottery_rate[rate_num])
			{
				if(level ==2 && total[j]!=0)				//限量物品
				{
					for(int k=0;k<RARE_ITEMS_NUM; ++k)
					{
						if(id[j] == pdata->ItemsNumbers[k].id)
						{
							if(pdata->ItemsNumbers[k].over_num == 0)
							{
								awards_id.push_back(id[j+1]);
								awards_typeid.push_back(type_id[j+1]);
								awards_eqid.push_back(eqid[j+1]);
								awards_num.push_back(num[j+1]);
							}
							else										//上电视
							{
								pdata->ItemsNumbers[k].over_num--;
								awards_id.push_back(id[j]);
								awards_typeid.push_back(type_id[j]);
								awards_eqid.push_back(eqid[j]);
								awards_num.push_back(num[j]);

								RareItemsWinner points;
								DataUserBasic dataUserBasic;
								CDataUserBasic dbUserBasic;
								int ret = dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, dataUserBasic);
								if (ret != 0)
								{
									error_log("[GetUserBasicLimit fail][ret=%d,uid=%u]", ret, uid);
									DB_ERROR_RETURN_MSG("db_get_uesr_basic_fail");
								}
								points.uid = uid;
								points.eqid = eqid[j];
								points.type_id = type_id[j];
								points.num = num[j];
								memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);

								if(pdata->winner_flag == 0)
								{
									for(int i=0; i<RARE_ITEMS_SIZE; ++i)
									{
										if(pdata->ItemsWinner[i].uid == 0)
										{
											memcpy(&pdata->ItemsWinner[i],&points,sizeof(RareItemsWinner));
											if(i == RARE_ITEMS_SIZE-1)
												pdata->winner_flag = 1;
											break;
										}
									}
								}
								else
								{
									for(int i=0; i<RARE_ITEMS_SIZE-1; ++i)
									{
										memcpy(&pdata->ItemsWinner[i],&pdata->ItemsWinner[i+1],sizeof(RareItemsWinner));
									}
									memcpy(&pdata->ItemsWinner[RARE_ITEMS_SIZE-1], &points, sizeof(RareItemsWinner));
								}
							}
							break;
						}
					}
				}
				else
				{
					awards_id.push_back(id[j]);
					awards_typeid.push_back(type_id[j]);
					awards_eqid.push_back(eqid[j]);
					awards_num.push_back(num[j]);
					if((level==1 && id[j]==6) || (level==2 && id[j]==8))		//上电视
					{
						RareItemsWinner points;
						DataUserBasic dataUserBasic;
						CDataUserBasic dbUserBasic;
						int ret = dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, dataUserBasic);
						if (ret != 0)
						{
							error_log("[GetUserBasicLimit fail][ret=%d,uid=%u]", ret, uid);
							DB_ERROR_RETURN_MSG("db_get_uesr_basic_fail");
						}
						points.uid = uid;
						points.eqid = eqid[j];
						points.type_id = type_id[j];
						points.num = num[j];
						memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);

						if(pdata->winner_flag == 0)
						{
							for(int i=0; i<RARE_ITEMS_SIZE; ++i)
							{
								if(pdata->ItemsWinner[i].uid == 0)
								{
									memcpy(&pdata->ItemsWinner[i],&points,sizeof(RareItemsWinner));
									if(i == RARE_ITEMS_SIZE-1)
										pdata->winner_flag = 1;
									break;
								}
							}
						}
						else
						{
							for(int i=0; i<RARE_ITEMS_SIZE-1; ++i)
							{
								memcpy(&pdata->ItemsWinner[i],&pdata->ItemsWinner[i+1],sizeof(RareItemsWinner));
							}
							memcpy(&pdata->ItemsWinner[RARE_ITEMS_SIZE-1], &points, sizeof(RareItemsWinner));
						}
					}
				}
				break;
			}
		}
	}

	for(int i=0; i<RARE_ITEMS_NUM; ++i)
	{
		get_id.push_back(pdata->ItemsNumbers[i].id);
		over_num.push_back(pdata->ItemsNumbers[i].over_num);
	}

	for(int i=0; i<RARE_ITEMS_SIZE; ++i)
	{
		if(pdata->ItemsWinner[i].uid != 0)
		{
			peoples.push_back(pdata->ItemsWinner[i]);
		}
	}

	return 0;
}

int CDataNewlottery::GetRareItemsNumbers(vector <unsigned> id, vector <unsigned> total, vector <unsigned> &get_id, vector <unsigned> &over_num, vector <RareItemsWinner> &peoples)
{
	DataNewlottery *pdata = (DataNewlottery *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_datanewlottery_data_fail");
	}
	CAutoLock lock(&m_sh, true);
	if(Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_VER) != pdata->version)
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = Config::GetIntValue(CONFIG_ACTIVITY_NEW_LOTTERY_VER);
		unsigned pos = 0;
		for(int i=0; i<id.size(); ++i)
		{
			if(total[i] != 0)
			{
				pdata->ItemsNumbers[pos].id = id[i];
				pdata->ItemsNumbers[pos].over_num = total[i];
				++pos;
			}
		}
	}

	for(int i=0; i<RARE_ITEMS_NUM; ++i)
	{
		get_id.push_back(pdata->ItemsNumbers[i].id);
		over_num.push_back(pdata->ItemsNumbers[i].over_num);
	}

	for(int i=0; i<RARE_ITEMS_SIZE; ++i)
	{
		if(pdata->ItemsWinner[i].uid != 0)
		{
			peoples.push_back(pdata->ItemsWinner[i]);
		}
	}
	return 0;
}
