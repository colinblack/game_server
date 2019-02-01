/*
 * LogicBarbarianKing.cpp
 *
 *  Created on: 2014-4-3
 *      Author: dawx123
 */

#include "LogicBarbarianKing.h"

CDataBarbarianKing* CLogicBarbarianKing::GetCDataBarbarianKing()
{
	GET_MEM_DATA_SEM(CDataBarbarianKing, CONFIG_BARBARIANKING_PATH, sem_barbarian_king,true)
}

int CLogicBarbarianKing::GetBKList(unsigned group, Json::Value &result)
{
	if(group >= BK_GROUP_MAX)
		return R_ERR_PARAM;

	string url = "action=getbarbariankingrank&group=";
	url.append(CTrans::ITOS(group));

	CLogicAllServerBaseMatch logicBaseMatch;
	return logicBaseMatch.RequestBaseMatch(url,result);
}
int CLogicBarbarianKing::SetBKChallenger(unsigned level, unsigned uid, unsigned point, string &name)
{
	int group =  GetGroupByLevel(level);
	if(group < 0 || group >= BK_GROUP_MAX)
		return R_ERR_PARAM;

	int serverid = 0;
	Config::GetDB(serverid);
	Json::Value data;
	data["group"] = group;
	data["uid"] = uid;
	data["serverid"] = serverid;
	data["point"] = point;
	data["name"] = name;
	string url = "action=barbarianingpoint";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	Json::Value result;
	return logicBaseMatch.RequestBaseMatch(url,result);
}

int CLogicBarbarianKing::GetGroupByLevel(unsigned level)
{
	if(level < 90)
		return 0;
	else if(level < 110)
		return 1;
	else
		return 2;
}

int sortBarbarianKing(const BKChallenger& left,const BKChallenger& right)
{
	return left.point > right.point;
}
int CLogicBarbarianKing::Reward()
{
	CDataBarbarianKing* dataBarbarianKing = GetCDataBarbarianKing();
	if (!dataBarbarianKing)
	{
		error_log("init_BarbarianKing_fail");
		DB_ERROR_RETURN_MSG("init_BarbarianKing_fail");
	}

	int res = 0;
	CLogicUpdates logicUpdates;
	for(int i=0;i<BK_GROUP_MAX;++i)
	{
		vector<BKChallenger> challenger;
		int ret = dataBarbarianKing->GetBKList(i, challenger);
		dataBarbarianKing->SetReward(i);
		if(ret)
		{
			res += ret;
			continue;
		}
		sort(challenger.begin(),challenger.end(),sortBarbarianKing);
		for(int j=0;j<challenger.size();++j)
		{
			Json::Value updates;
			updates["s"] = "BARBARIANKINGREWARD";
			updates["rank"] = j + 1;
			updates["ts"] = Time::GetGlobalTime();
			logicUpdates.AddUpdates(challenger[j].uid, updates,true);

			info_log("reward %u=%u,point=%u",j+1,challenger[j].uid,challenger[j].point);
		}
	}
	return res;
}

int CLogicBarbarianKing::ReplyBKList(unsigned group, Json::Value &result)
{
	CDataBarbarianKing* dataBarbarianKing = GetCDataBarbarianKing();
	if (!dataBarbarianKing)
	{
		error_log("init_BarbarianKing_fail");
		DB_ERROR_RETURN_MSG("init_BarbarianKing_fail");
	}

	vector<BKChallenger> challenger;
	int ret = dataBarbarianKing->GetBKList(group, challenger);
	if(ret)
		return ret;

	//debug_log("size=%u",challenger.size());
	if(challenger.size())
	{
		result.resize(challenger.size());
		for(unsigned i=0;i<challenger.size();++i)
		{
			result[i]["uid"] = challenger[i].uid;
			result[i]["serverid"] = challenger[i].serverid;
			result[i]["point"] = challenger[i].point;
			result[i]["name"] = challenger[i].name;
		}
	}
	return 0;
}
int CLogicBarbarianKing::ReplyBKChallenger(Json::Value &data)
{
	CDataBarbarianKing* dataBarbarianKing = GetCDataBarbarianKing();
	if (!dataBarbarianKing)
	{
		error_log("init_BarbarianKing_fail");
		DB_ERROR_RETURN_MSG("init_BarbarianKing_fail");
	}

	unsigned group;
	string name;
	BKChallenger challenger;
	Json::GetUInt(data,"group",group);
	Json::GetUInt(data,"uid",challenger.uid);
	Json::GetUInt(data,"serverid",challenger.serverid);
	Json::GetUInt(data,"point",challenger.point);
	Json::GetString(data,"name",name);
	strcpy(challenger.name,name.c_str());

	return dataBarbarianKing->SetBKChallenger(group, challenger);
}
