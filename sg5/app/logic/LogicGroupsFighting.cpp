
/*
 * LogicGroupsFighting.h
 *
 *  Created on: 2013-08-20
 *      Author: Administrator
 */

#include "LogicGroupsFighting.h"


CLogicGroupsFighting::CLogicGroupsFighting() {
	// TODO Auto-generated constructor stub

}

CLogicGroupsFighting::~CLogicGroupsFighting() {
	// TODO Auto-generated destructor stub
}

CDataGroupsFigthing* CLogicGroupsFighting::GetGroupsFightingData(int cityid)
{
//	GET_MEM_DATA_SEM(CDataGroupsFigthing, GROUPS_FIGHTING, sem_groupsfighting)


	static map<int, CDataGroupsFigthing*> dataMap;
	int serverId = 0;
	Config::GetDomain(serverId);
	if (0 == serverId)
		return NULL;
	map<int, CDataGroupsFigthing*>::iterator itr = dataMap.find(serverId);
	if (itr != dataMap.end() && NULL != itr->second)
		return itr->second;

	static CDataGroupsFigthing* pdata = NULL;
	if (!pdata)
	{

		pdata = new CDataGroupsFigthing();
		if (pdata->Init(Config::GetPath(GROUPS_FIGHTING),cityid ,sem_groupsfighting) != 0)
		{
			delete pdata;
			pdata = NULL;
			return NULL;
		}
	}
	dataMap[serverId] = pdata;
	return pdata;

}


//获取所有数据
int CLogicGroupsFighting::GetGroupsFightingJsonData(int cityid,Json::Value &result,Json::Value &input,unsigned uid)
{
	CDataGroupsFigthing *pdata= GetGroupsFightingData(cityid);
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_getgroupsjsondata_fail");
	}
	vector <EveryoneFormation> All_data;
	struct EveryoneFormation Selfdata;
	memset(&Selfdata,0,sizeof(EveryoneFormation));
	unsigned alliance_id = 0;  //通过uid获取其帮会id
	CDataUser datauser;
	DataUser user;
	int ret = datauser.GetUserLimit(uid,user);
	if(ret != 0)
		return ret;
	alliance_id = user.alliance_id;

	Selfdata.alliance_id = alliance_id;
	Selfdata.camp = input["soldier"][0u]["camp"].asInt();
	Selfdata.fullmorale = input["soldier"][0u]["fullmorale"].asUInt();
	Selfdata.morale = input["soldier"][0u]["morale"].asUInt();
	Selfdata.position = input["soldier"][0u]["position"].asInt();
	Selfdata.state = input["soldier"][0u]["state"].asInt();
	Selfdata.target = input["soldier"][0u]["target"].asInt();
	Selfdata.ts = input["soldier"][0u]["ts"].asUInt();
	Selfdata.uid = input["soldier"][0u]["uid"].asUInt();
	Selfdata.personalWarData.attack = input["soldier"][0u]["attack"].asInt();
	Selfdata.personalWarData.attackRate = input["soldier"][0u]["attackRate"].asInt();
	Selfdata.personalWarData.critRate = input["soldier"][0u]["critRate"].asInt();
	Selfdata.personalWarData.defence = input["soldier"][0u]["defence"].asUInt();
	Selfdata.personalWarData.dodgeRate = input["soldier"][0u]["dodgeRate"].asInt();
	Selfdata.personalWarData.level = input["soldier"][0u]["level"].asInt();
	Selfdata.personalWarData.maxHp = input["soldier"][0u]["maxHp"].asUInt();
	Selfdata.personalWarData.type = input["soldier"][0u]["type"].asInt();
	Selfdata.personalWarData.typeLevels[0] = input["soldier"][0u]["typeLevel_0"].asInt();
	Selfdata.personalWarData.typeLevels[1] = input["soldier"][0u]["typeLevel_1"].asInt();
	Selfdata.personalWarData.typeLevels[2] = input["soldier"][0u]["typeLevel_2"].asInt();

	unsigned seq_id = 0;
	unsigned Senduid = 0;
	int holdsNum = 0;
	int map_id = 0;
	int num_flag = 0;

	if(!Json::GetInt(input, "holdsNum", holdsNum) || !Json::GetInt(input, "mapId", map_id))
	{
		return R_ERR_PARAM;
	}

	ret = pdata->GetAllCombatData(All_data,cityid,map_id,seq_id,Senduid,Selfdata,num_flag,holdsNum);
	if(ret != 0)
	{
		return ret;
	}

	if(999 == num_flag)	      //人数已满
	{
		result["num_of_full"] = 999;
	}
	else
	{
		int numbers = All_data.size();
		result["cityid"] = cityid;
		result["map_id"] = map_id;
		result["seq_id"] = seq_id;
		result["senduid"] = Senduid;
		result["personal_num"] = numbers;

		for(int i = 0; i < holdsNum;i++)
		{
			int num = 0;
			int camp = 0;
			for(int j = 0; j < numbers;j++)
			{
				if(i == All_data[j].position &&All_data[j].target == -1)
				{
					num++;
					camp = All_data[j].camp;
				}
			}
			result["fortified"][i]["num"] = num;
			result["fortified"][i]["camp"] = camp;
			result["fortified"][i]["position"] = i;
		}
		for(int i = 0; i < All_data.size(); i++)
		{
			result["personal_data"][i]["uid"] = All_data[i].uid;
			result["personal_data"][i]["camp"] = All_data[i].camp;
			result["personal_data"][i]["state"] = All_data[i].state;
	//		result["personal_data"][i]["role"] = All_data[i].role;
			result["personal_data"][i]["morale"] = All_data[i].morale;
			result["personal_data"][i]["position"] = All_data[i].position;
			result["personal_data"][i]["fullmorale"] = All_data[i].fullmorale;
			result["personal_data"][i]["allianceId"] = All_data[i].alliance_id;
			result["personal_data"][i]["target"] = All_data[i].target;
			result["personal_data"][i]["ts"] = All_data[i].ts;
			result["personal_data"][i]["attack"] = All_data[i].personalWarData.attack;
			result["personal_data"][i]["attackRate"] = All_data[i].personalWarData.attackRate;
			result["personal_data"][i]["critRate"] = All_data[i].personalWarData.critRate;
			result["personal_data"][i]["defence"] = All_data[i].personalWarData.defence;
			result["personal_data"][i]["dodgeRate"] = All_data[i].personalWarData.dodgeRate;
			result["personal_data"][i]["level"] = All_data[i].personalWarData.level;
			result["personal_data"][i]["maxHp"] = All_data[i].personalWarData.maxHp;
			result["personal_data"][i]["type"] = All_data[i].personalWarData.type;
			result["personal_data"][i]["typeLevels_0"] = All_data[i].personalWarData.typeLevels[0];
			result["personal_data"][i]["typeLevels_1"] = All_data[i].personalWarData.typeLevels[1];
			result["personal_data"][i]["typeLevels_2"] = All_data[i].personalWarData.typeLevels[2];
		}
	}
	return 0;
}

int CLogicGroupsFighting::LogicUpdatesFightingData(int cityid,Json::Value &input,unsigned uid,Json::Value &result)
{
	CDataGroupsFigthing *pdata= GetGroupsFightingData(cityid);
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_getgroupsjsondata_fail");
	}

	vector <EveryoneFormation> All_data;
	struct EveryoneFormation Selfdata;
	memset(&Selfdata,0,sizeof(EveryoneFormation));


	unsigned seq_id = 0;
	int map_id = 0;
	int personal_num = 0;
	int holdsNum = 0;
	unsigned Senduid = uid;

	if(!Json::GetUInt(input, "seq_id", seq_id) || !Json::GetInt(input, "personal_num", personal_num)
	|| !Json::GetInt(input, "mapId", map_id)  || !Json::GetInt(input, "holdsNum", holdsNum))
	{
		return R_ERR_PARAM;
	}

	for(int i =0; i < personal_num; i++)
	{
		All_data.push_back(Selfdata);
		All_data[i].alliance_id = input["soldiers"][i]["allianceId"].asUInt();
		All_data[i].camp = input["soldiers"][i]["camp"].asInt();
		All_data[i].fullmorale = input["soldiers"][i]["fullmorale"].asUInt();
		All_data[i].morale = input["soldiers"][i]["morale"].asUInt();
		All_data[i].position = input["soldiers"][i]["position"].asInt();
		All_data[i].state = input["soldiers"][i]["state"].asInt();
		All_data[i].target = input["soldiers"][i]["target"].asInt();
		All_data[i].ts = input["soldiers"][i]["ts"].asUInt();
		All_data[i].uid = input["soldiers"][i]["uid"].asUInt();
		All_data[i].personalWarData.attack = input["soldiers"][i]["attack"].asInt();
		All_data[i].personalWarData.attackRate = input["soldiers"][i]["attackRate"].asInt();
		All_data[i].personalWarData.critRate = input["soldiers"][i]["critRate"].asInt();
		All_data[i].personalWarData.defence = input["soldiers"][i]["defence"].asUInt();
		All_data[i].personalWarData.dodgeRate = input["soldiers"][i]["dodgeRate"].asInt();
		All_data[i].personalWarData.level = input["soldiers"][i]["level"].asInt();
		All_data[i].personalWarData.maxHp = input["soldiers"][i]["maxHp"].asUInt();
		All_data[i].personalWarData.type = input["soldiers"][i]["type"].asInt();
		All_data[i].personalWarData.typeLevels[0] = input["soldiers"][i]["typeLevel_0"].asInt();
		All_data[i].personalWarData.typeLevels[1] = input["soldiers"][i]["typeLevel_1"].asInt();
		All_data[i].personalWarData.typeLevels[2] = input["soldiers"][i]["typeLevel_2"].asInt();
	}

	int flag = 0;     //判断这个消息包是否采用
	int ret = pdata->UpdatesFightingData(All_data,cityid,seq_id,Senduid,map_id,holdsNum,flag);
	if(ret != 0)
		return ret;

	if(1 == flag)     //弃用消息包
	{
		result["message_packet"] = 0;
	}
	else
	{
		result["message_packet"] = 1;
	}
	return 0;

}

int CLogicGroupsFighting::LogicAddFullmorale(unsigned uid, int cityid)
{
	CDataGroupsFigthing *pdata= GetGroupsFightingData(cityid);
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_nationalwar_rgt_fail");
	}

	int ret = pdata->AddFullmorale(cityid,uid);
	if(ret != 0)
	{
		return ret;
	}

	return 0;

}


int CLogicGroupsFighting::CleanGroupsFightingDate(int cityid)
{
	CDataGroupsFigthing *pdata= GetGroupsFightingData(cityid);
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_nationalwar_rgt_fail");
	}
	return pdata->CleanGroupsfigthingData(cityid);
}
