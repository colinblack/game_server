
/*
 * LogicQixi.h
 *
 *  Created on: 2013-08-06
 *      Author: Administrator
 */

#include "LogicQixi.h"
#include "LogicCMD.h"


CLogicQixijie::CLogicQixijie() {
	// TODO Auto-generated constructor stub

}

CLogicQixijie::~CLogicQixijie() {
	// TODO Auto-generated destructor stub
}

CDataQixijie* CLogicQixijie::GetQixijieData()
{
	GET_MEM_DATA_SEM(CDataQixijie, QIXIJIE_PAY_RANK, sem_qixijie,false)

}

int CLogicQixijie::GetQixiActivityRank(unsigned uid, vector <DataQixiRank> &vecPoints)
{
	CDataQixijie *pdata= GetQixijieData();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_hundreddaysactivityrank_fail");
	}
	int version = Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_VERSION);

	int ret = pdata->GetRankList(vecPoints,version);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}
int CLogicQixijie::GetQixiActivityRankJson(unsigned uid, Json::Value &result)
{
	CDataQixijie *pdata= GetQixijieData();

	if( Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_BEGIN_TS)
	&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_END_TS) + 48*60*60)
	{
		vector <DataQixiRank> vecPoints;
		int ret = GetQixiActivityRank(uid,vecPoints);
		if(ret != 0)
		{
				return ret;
		}
		DataGetWinners vecPrize[4];
		int Lotterynumber;
		int markreward;
		vector <int> prizenum;
		ret = pdata->GetReturnData(vecPrize,Lotterynumber,markreward,prizenum);
		if(ret != 0)
		{
			error_log("qixi_GetReturnData_fail!!!");
			return ret;
		}

		int iCount = RANK_SIZE;

		//前十名积分
		for(int i = 0; i < iCount; i++)
		{
			result[i]["uid"] = vecPoints[i].uid;
			result[i]["pay"] = vecPoints[i].pay;
			result[i]["name"] = string(vecPoints[i].name);
		}

		int open_second = Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_OPEN_SECOND);
		result[iCount]["open_second"] = open_second;           //开启第二层条件
		result[iCount +1]["number"] = Lotterynumber;            //全区总共抽了多少次

		for(int i = iCount+2; i < iCount +6 ; i++)              //大奖
		{
			result[i]["uid"] = vecPrize[i- iCount-2].uid;
			result[i]["rewards"] = vecPrize[i-iCount-2].reward;
			result[i]["name"] = string(vecPrize[i-iCount-2].name);
		}

		result[iCount +6]["Prizesnum_1"] = prizenum[0];
		result[iCount +7]["Prizesnum_2"] = prizenum[1];
		result[iCount +8]["Prizesnum_3"] = prizenum[2];
		result[iCount +9]["Prizesnum_4"] = prizenum[3];

		//个人积分
		CLogicSecinc Secinc;
		Json::Value SecincData;
		ret = Secinc.GetSecinc(uid, NAT_CHOUJIANG, SecincData);
		if(ret!=0 && ret!=R_ERR_NO_DATA)
		{
			return ret;
		}

		if(!SecincData.isMember("ver") || SecincData["ver"].asInt() != Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_VERSION))
		{
			SecincData["id"] = NAT_CHOUJIANG;
			SecincData["ver"] = Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_VERSION);
			SecincData["count"] = 0;
			SecincData["fc"] = NAT_CHOUJIANG_FREE_NUM;
			SecincData["fts"] = Time::GetGlobalTime();

			ret = Secinc.SetOneSecinc(uid, SecincData);
			if(ret)
				return ret;
		}
		if(!SecincData.isMember("fts") || !SecincData.isMember("fc") || !Time::IsToday(SecincData["fts"].asUInt()))
		{
			SecincData["fc"] = NAT_CHOUJIANG_FREE_NUM;
			SecincData["fts"] = Time::GetGlobalTime();

			ret = Secinc.SetOneSecinc(uid, SecincData);
			if(ret)
				return ret;
		}

		result[iCount +10]["Self"] = SecincData["count"].asUInt() * 10;
		result[iCount +10]["fc"] = SecincData["fc"].asUInt();
		result[iCount +10]["fts"] = SecincData["fts"].asUInt();

		//发奖
		if( Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_END_TS)
			&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_END_TS) + 48*60*60)
		{
			vector <DataQixiRank> reward_vec;
			Json::Value updateJson;
			updateJson.resize(1);
			CLogicUpdates logiceUpdates;

			ret = pdata->GetRewardData(reward_vec);
			if(ret != 0)
			{
				return ret;
			}

			if(reward_vec.size() > 0)
			{
				for (int i=0; i<5; i++)
				{
					if(reward_vec[i].pay >= 2000)
					{
						if (!IsValidUid(reward_vec[i].uid))
						{
							continue;
						}

						updateJson[(unsigned)0]["uid"] = reward_vec[i].uid;
						updateJson[(unsigned)0]["s"] = "QixiJieRank";
						updateJson[(unsigned)0]["rank"] = i+1;
						updateJson[(unsigned)0]["ts"] = Time::GetGlobalTime();
						updateJson[(unsigned)0]["pay"] = reward_vec[i].pay;

						ret = logiceUpdates.AddUpdates(reward_vec[i].uid, updateJson,true);
						if (0 != ret)
						{
							error_log("[qixijie_Add_updates_fail][ret=%d,uid=%u]", ret, reward_vec[i].uid);
						}
						Json::FastWriter writer;
						info_log("qixijie_reward,updates=%s", writer.write(updateJson).c_str());
					}
				}
			}
		}
	}
	return 0;
}

/*
int CLogicQixijie::UpdateQixiActivityRank(int unsigned uid, Json::Value &input,Json::Value &result)
{
	if( Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_BEGIN_TS)
	&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_END_TS))
	{
		int lotteryNum = 1;
		Json::GetInt(input,"lotteryNum",lotteryNum);

		unsigned now = Time::GetGlobalTime();
		CDataQixijie *pdata= GetQixijieData();
		if(pdata == NULL)
		{
			DB_ERROR_RETURN_MSG("init_qixiactivityrank_fail");
		}
		int ret = 0;
		DataUser user;
		CLogicUser logicUser;
		ret = logicUser.GetUser(uid,user);
		if(ret != 0)
			return ret;

		int payTotal = 0;
		Json::Reader reader;
		Json::Value userStat;
		if (!reader.parse(user.user_stat, userStat))
		{
			error_log("[paser user_flag fail][uid=%u]", uid);
			DB_ERROR_RETURN_MSG("user_flag_error");
		}
		if(!userStat.isMember("cjn"))
		{
			payTotal = 0;
		}
		else
		{
			payTotal = (userStat["cjn"].asUInt()+lotteryNum) * 10;  //抽奖积分
		}

		CLogicSecinc Secinc;
		Json::Value SecincData;
		ret = Secinc.GetSecinc(uid, NAT_CHOUJIANG, SecincData);
		if(ret == 0 || ret == R_ERR_NO_DATA)
		{
			if(!SecincData.isMember("id"))
			{
				SecincData["id"] = NAT_CHOUJIANG;
				SecincData["count"] = payTotal/10;
				SecincData["ver"] = Config::GetIntValue(CONFIG_PAY_OF_QIXIJIE_VERSION);
			}
			else
			{
				SecincData["count"] = payTotal/10;
			}

			Secinc.SetOneSecinc(uid, SecincData);
		}

		DataQixiRank points;
		CLogicUserBasic logicUserBasic;
		DataUserBasic dataUserBasic;
		logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);
		points.uid = uid;
		points.pay = payTotal;
		memcpy(points.name,dataUserBasic.name.c_str(),sizeof(points.name) - 1);

		ret = pdata->SetRecordLotterynumber(lotteryNum);      //设置全区抽奖次数
		if(ret != 0)
		{
			return ret;
		}

///////////////////////////////////随机数产生
		int s1 = 0;
		int s2 = 0;

		for(int i = 0; i < 10; i++)
		{
			s1 = s1 +  input["qixifirstlayer"]["rate"][i].asInt();
		}
		for(int i = 0; i < 24; i++)
		{
			s2 = s2 +  input["qixisecondlayer"]["rate"][i].asInt();
		}
		int Platform = OpenPlatform::GetType();
		vector<int> reward;
		for (int i = 0; i < lotteryNum; ++i) {
			int mark_reward = 0;
			ret = pdata->LotteryResults(uid,input,s1,s2,Platform,mark_reward);
			if(ret != 0)
			{
				return ret;
			}
			reward.push_back(mark_reward);
		}
///////////////////////////////////
		ret = pdata->UpdateRankList(points);        //更新玩家抽奖积分排行榜
		if(ret != 0)
		{
			return ret;
		}
		result["reward_uid"] = uid;
//		result["mark_reward"] = mark_reward;
		if (lotteryNum == 1) {
			result["mark_reward"] = reward[0];;
		}
		else {
			for (int i = 0; i < lotteryNum; ++i) {
				result["mark_reward"][(unsigned)i] = reward[i];
			}
		}
	}
	return 0;
}
*/


