/*
 * DataQixijie.cpp
 *
 *  Created on: 2013-08-06
 *      Author: Administrator
 */

#include "DataQixi.h"
#include "DataUserBasic.h"
#include "DataXML.h"


CDataQixijie::CDataQixijie(){
	m_init = false;
}
CDataQixijie::~CDataQixijie() {
	// TODO Auto-generated destructor stub
}

int  CDataQixijie::Init(const std::string &path, semdat sem)
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
	if(!m_sh.CreateOrOpen(path.c_str(), sizeof(QixiAcvitityPayRank), SEM_ID(sem,semgroup,semserver)))
	{
		error_log("[init__qixi_data_fail][path=%s]", path.c_str());
		return R_ERROR;
	}
	CAutoLock lock(&m_sh, true);
	if(!m_sh.HasInit())
	{
		QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_qixi_fail");
		}
		memset(pdata, 0, sizeof(*pdata));
		m_sh.SetInitDone();
	}
	m_init = true;
	return 0;
}


int sortFunc(const DataQixiRank& left,const DataQixiRank& right){
	return left.pay > right.pay;
}
/*
int CDataQixijie::UpdateRankList(const DataQixiRank &points)
{
	int i= 0;
	bool inFlag = false;  // 用户是否在排行榜中
	QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_qixiactivity_fail");
	}
	CAutoLock lock(&m_sh, true);
	for(i = RANK_SIZE -1;i >= 0; i--)
	{
		if(pdata->QixiAcvitityRank[i].uid == points.uid  )
		{
			pdata->QixiAcvitityRank[i].pay = points.pay;
			// 如果用户已在排行榜，inFlag = true
			inFlag = true;
			break;
		}
	}
	if(!inFlag)
	{
		pdata->QixiAcvitityRank[RANK_SIZE] = points;
	}
	else
	{
		memset(&(pdata->QixiAcvitityRank[RANK_SIZE]),0,sizeof(DataQixiRank));
	}

	vector<DataQixiRank> vecQixi;
	for(i = 0; i<=RANK_SIZE;++i)
	{
		vecQixi.push_back(pdata->QixiAcvitityRank[i]);
	}

	sort(vecQixi.begin(),vecQixi.end(),sortFunc);

	for(i = 0; i<=RANK_SIZE;++i){
		pdata->QixiAcvitityRank[i] = vecQixi[i];
	}
	return 0;
}
*/

int CDataQixijie::GetRankList( vector <DataQixiRank> &vecPoints,const int version)
{
	QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_qixiactivity_fail");
	}
	CAutoLock lock(&m_sh, true);
	if(version != pdata->version)
	{
		memset(pdata, 0, sizeof(*pdata));
		pdata->version = version;
	}
	for(int i=0; i<RANK_SIZE;i++)
	{
		vecPoints.push_back(pdata->QixiAcvitityRank[i]);
	}
	return 0;
}

int CDataQixijie::GetReturnData(DataGetWinners vecPrize[],int &Lotterynumber,int &markreward,vector <int> &prizenum)
{
	QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_qixiactivity_fail");
	}
	CAutoLock lock(&m_sh, true);

	memcpy(vecPrize,pdata->GetRewards,sizeof(pdata->GetRewards));
	Lotterynumber = pdata->Lotterynumber;
	markreward = pdata->markreward;
	for(int i =0; i < 4; i++)
	{
		prizenum.push_back(pdata->prizenum[i]);
	}
	return 0;
}

int CDataQixijie::QixiChoujiang(unsigned uid,unsigned count, unsigned integral, vector <unsigned> &awards_index_id, vector <unsigned> &awards_type_id,
		vector <unsigned> &awards_eqid, vector <unsigned> &awards_num, Json::Value &result)
{
	QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_qixiactivity_fail");
	}
	CAutoLock lock(&m_sh, true);

	CDataXML *pDataXML = CDataXML::GetCDataXML();
	if(!pDataXML)
	{
		error_log("GetInitXML fail");
		return R_ERR_DB;
	}

	unsigned floors = 1;
	if(pdata->Lotterynumber >= Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_OPEN_SECOND))
	{
		floors = 2;
	}

	if(CTime::GetDayInterval(pdata->ts, Time::GetGlobalTime()) != 0)
		pdata->Lotterynumber = count;
	else
		pdata->Lotterynumber = pdata->Lotterynumber + count;
	pdata->ts = Time::GetGlobalTime();

	vector <unsigned> limit_items;
	for(int i=0; i<4; ++i)
	{
		limit_items.push_back(pdata->prizenum[i]);
	}
	int ret =  pDataXML->GetChoujiangWupin(uid, floors, count, awards_index_id, awards_type_id,
			awards_eqid, awards_num, limit_items);
	if(ret)
	{
		error_log("[XMLchoujiang_error][uid=%u,]", uid);
		return R_ERR_DATA;
	}

	DataUserBasic dataUserBasic;
	CDataUserBasic dbUserBasic;
	ret = dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, dataUserBasic);
	if (ret != 0)
	{
		error_log("[GetUserBasicLimit fail][ret=%d,uid=%u,platform=%d]", ret, uid);
		DB_ERROR_RETURN_MSG("db_get_uesr_basic_fail");
	}
	///////////////////////大奖上电视
	for(int i=0; i<awards_index_id.size(); ++i)
	{
		if(awards_index_id[i] == 10 || awards_index_id[i] == 13 || awards_index_id[i] == 17 || awards_index_id[i] == 20
		|| awards_index_id[i] == 8 || awards_index_id[i] == 9 || awards_index_id[i] == 18 || awards_index_id[i] == 23)
		{
			DataGetWinners points;
			points.uid = uid;
			points.reward = awards_index_id[i];
			points.ts = Time::GetGlobalTime();
			memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);
			if(pdata->markreward == 0)
			{
				for(int i=0; i<4; ++i)
				{
					if(pdata->GetRewards[i].uid == 0)
					{
						memcpy(&pdata->GetRewards[i],&points,sizeof(DataGetWinners));
						if(i == 3)
							pdata->markreward = 1;
						break;
					}
				}
			}
			else
			{
				for(int i=0; i<3; ++i)
				{
					memcpy(&pdata->GetRewards[i],&pdata->GetRewards[i+1],sizeof(DataGetWinners));
				}
				memcpy(&pdata->GetRewards[3], &points, sizeof(DataGetWinners));
			}
		}
	}

	//////////更新排行榜
	DataQixiRank people_rank;
	people_rank.uid = uid;
	people_rank.pay = integral;
	memcpy(people_rank.name,dataUserBasic.name.c_str(),sizeof(people_rank.name) - 1);
	int i;
	bool inFlag = false;  // 用户是否在排行榜中
	for(i = RANK_SIZE -1;i >= 0; i--)
	{
		if(pdata->QixiAcvitityRank[i].uid == people_rank.uid  )
		{
			pdata->QixiAcvitityRank[i].pay = people_rank.pay;
			// 如果用户已在排行榜，inFlag = true
			inFlag = true;
			break;
		}
	}
	if(!inFlag)
	{
		pdata->QixiAcvitityRank[RANK_SIZE] = people_rank;
	}
	else
	{
		memset(&(pdata->QixiAcvitityRank[RANK_SIZE]),0,sizeof(DataQixiRank));
	}

	vector<DataQixiRank> vecQixi;
	for(i = 0; i<=RANK_SIZE;++i)
	{
		vecQixi.push_back(pdata->QixiAcvitityRank[i]);
	}

	sort(vecQixi.begin(),vecQixi.end(),sortFunc);

	for(i = 0; i<=RANK_SIZE;++i){
		pdata->QixiAcvitityRank[i] = vecQixi[i];
	}

	for(int i=0; i <limit_items.size(); ++i)
	{
		pdata->prizenum[i] = limit_items[i];
		result["value"][i] = limit_items[i];
		result["awards"][i]["name"] = pdata->GetRewards[i].name;
		result["awards"][i]["reward"] = pdata->GetRewards[i].reward;
		result["awards"][i]["uid"] = pdata->GetRewards[i].uid;
	}
	result["Lotterynumber"] = pdata->Lotterynumber;
	result["self_pay"] = integral;
	return 0;
}

int CDataQixijie::GetRewardData(vector <DataQixiRank> &reward_vec)
{
	QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("GetRewardData_qixiactivity_fail");
	}
	CAutoLock lock(&m_sh, true);

	if( Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_END_TS)
	&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_END_TS) + 48*60*60
	&& pdata->rewardflag ==0)
	{
		pdata->rewardflag = 1;
		for(int i=0; i<RANK_SIZE;i++)
		{
			reward_vec.push_back(pdata->QixiAcvitityRank[i]);
		}
	}
	return 0;
}

/*
// modify by vincent
int CDataQixijie::SetRecordLotterynumber(int addNum)
{
	unsigned now = Time::GetGlobalTime();

	QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_qixiactivity_fail");
	}
	CAutoLock lock(&m_sh, true);
	if(CTime::GetDayInterval(pdata->ts, now) != 0)
	{
		pdata->ts = now;
		//EQUIPMENT_LOG("uid=%u,moneyTotal=%u,ts=%d,act=%s,code=%s,data=%s",0,pdata->Lotterynumber*20,now,"qixijie","ConsumptionData","money");
		pdata->Lotterynumber = 1;
	}
	else
	{
		pdata->ts = now;
		pdata->Lotterynumber = pdata->Lotterynumber + addNum;
	}
	return 0;
}

int CDataQixijie::LotteryResults(unsigned uid,Json::Value input,int s1, int s2,int platform,int &mark_reward)
{
	QixiAcvitityPayRank *pdata = (QixiAcvitityPayRank *)m_sh.GetAddress();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("clean_qixiactivity_fail");
	}
	CAutoLock lock(&m_sh, true);
	int Lotterynumber = pdata->Lotterynumber;

	int open_second = Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_OPEN_SECOND);
	if(Lotterynumber <= open_second )
	{
		int mark = Math::GetRandomInt(s1);                   //产生0至(s1-1)的随机数
		int s0 = 0;

		for(int i=0;i<10;i++)
		{
			if(mark >= s0 && mark < s0 + input["qixifirstlayer"]["rate"][i].asInt())
			{
				pdata->markreward = i + 1;
				break;
			}
			s0 += input["qixifirstlayer"]["rate"][i].asInt();
		}

	}
	else if(Lotterynumber > open_second )
	{
		int mark = Math::GetRandomInt(s2);
		int s0 = 0;

		for(int i=0;i<24;i++)
		{
			if(mark >= s0 && mark < s0 + input["qixisecondlayer"]["rate"][i].asInt())
			{
				pdata->markreward = i + 1;
				break;
			}
			s0 += input["qixisecondlayer"]["rate"][i].asInt();
		}
	}



	//4个全区限量奖励物品
	if(pdata->markreward == 11 )
	{
		pdata->prizenum[0] = pdata->prizenum[0] +1;
		if(pdata->prizenum[0] >= 5)
		{
			pdata->prizenum[0] = 5;
			pdata->markreward = pdata->markreward + 1;
		}
	}
	else if(pdata->markreward == 14 )
	{
		pdata->prizenum[1] = pdata->prizenum[1] +1;
		if(pdata->prizenum[1] >= 5)
		{
			pdata->prizenum[1] = 5;
			pdata->markreward = pdata->markreward + 1;
		}
	}
	else if(pdata->markreward == 18 )
	{
		pdata->prizenum[2] = pdata->prizenum[2] +1;
		if(pdata->prizenum[2] >= 5)
		{
			pdata->prizenum[2] = 5;
			pdata->markreward = pdata->markreward + 1;
		}
	}
	else if(pdata->markreward == 21 )
	{
		pdata->prizenum[3] = pdata->prizenum[3] +1;
		if(pdata->prizenum[3] >= 5)
		{
			pdata->prizenum[3] = 5;
			pdata->markreward = pdata->markreward + 1;
		}
	}

	mark_reward = pdata->markreward;

	//大奖展示更新
	if(pdata->markreward == 11 || pdata->markreward == 14 || pdata->markreward == 18 || pdata->markreward == 21
		|| pdata->markreward == 9 || pdata->markreward == 10 || pdata->markreward == 19 || pdata->markreward == 24)
	{
		DataGetWinners points;
		DataUserBasic dataUserBasic;
		CDataUserBasic dbUserBasic;
		int ret = dbUserBasic.GetUserBasicLimit(uid, platform, dataUserBasic);
		if (ret != 0)
		{
			error_log("[GetUserBasicLimit fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
			DB_ERROR_RETURN_MSG("db_get_uesr_basic_fail");
		}
		points.uid = uid;
		points.reward = pdata->markreward;
		points.ts = Time::GetGlobalTime();
		memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);


		if( 0 == pdata->GetRewards[0].ts || 0 == pdata->GetRewards[1].ts
		|| 0 == pdata->GetRewards[2].ts || 0 == pdata->GetRewards[3].ts)
		{
			for(int i = 0; i < 4; i++ )
			{
				if(pdata->GetRewards[i].uid == 0 && 0 == pdata->GetRewards[i].ts)
				{
					pdata->GetRewards[i].reward = points.reward;
					pdata->GetRewards[i].uid = points.uid;
					pdata->GetRewards[i].ts = Time::GetGlobalTime();
					memcpy(pdata->GetRewards[i].name,points.name,sizeof(points.name) - 1);
					//debug_log("aaaaaaaaaa:%u | %d",pdata->GetRewards[i].uid,pdata->GetRewards[i].reward);
					break;
				}
			}
		}
		else if( 0 != pdata->GetRewards[0].ts && 0 != pdata->GetRewards[1].ts
				&& 0 != pdata->GetRewards[2].ts && 0 != pdata->GetRewards[3].ts)
		{
			for(int i = 0; i < 3; i++)
			{
				pdata->GetRewards[i].reward = pdata->GetRewards[i+1].reward;
				pdata->GetRewards[i].uid = pdata->GetRewards[i+1].uid;
				pdata->GetRewards[i].ts = pdata->GetRewards[i+1].ts;
				memcpy(pdata->GetRewards[i].name,pdata->GetRewards[i+1].name,sizeof(pdata->GetRewards[i+1].name) - 1);

			}
			pdata->GetRewards[3].reward = points.reward;
			pdata->GetRewards[3].uid = points.uid;
			pdata->GetRewards[3].ts = Time::GetGlobalTime();
			memcpy(pdata->GetRewards[3].name,points.name,sizeof(points.name) - 1);
		}
	}
	return 0;
}
*/
