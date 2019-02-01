
/*
 * LogicRechargeAlliance.cpp
 *
 *  Created on: 2013-12-18
 *      Author: Administrator
 */

#include "LogicRechargeAlliance.h"


CLogicRechargeAlliance::CLogicRechargeAlliance() {
	// TODO Auto-generated constructor stub

}

CLogicRechargeAlliance::~CLogicRechargeAlliance() {
	// TODO Auto-generated destructor stub
}

CDataRechargeAlliance* CLogicRechargeAlliance::GetRechargeAlliancePdata(unsigned allianceid)
{
	if(!IsAllianceId(allianceid))
	{
		error_log("invalid AllianceId");
		return NULL;
	}

	static map<int, CDataRechargeAlliance*> dataMap;
	int serverId = Config::GetZoneByAID(allianceid);
	map<int, CDataRechargeAlliance*>::iterator itr = dataMap.find(serverId);
	if (itr != dataMap.end() && NULL != itr->second)
		return itr->second;

	CDataRechargeAlliance *pdata = new CDataRechargeAlliance();
	if (pdata->Init(MainConfig::GetAllServerPath(CONFIG_ALLIANCE_RECHARGE_DATA),allianceid,sem_recharge_alliance) != 0)
	{
		delete pdata;
		pdata = NULL;
		return NULL;
	}
	dataMap[serverId] = pdata;
	return pdata;
}

int CLogicRechargeAlliance::GetRechargeAllianceData(unsigned uid,Json::Value &result)
{
	unsigned alliance_id = 0;  //通过uid获取其帮会id
	CDataUser datauser;
	DataUser user;
	int ret = datauser.GetUserLimit(uid,user);
	if(ret != 0)
		return ret;
	alliance_id = user.alliance_id;

	return _getRechargeAllianceData(alliance_id,result);
}

int CLogicRechargeAlliance::_getRechargeAllianceData(unsigned allianceid,Json::Value &result)
{
	if(!IsAllianceId(allianceid))
		return 0;

	int version = 0;
	Config::GetIntValue(version, CONFIG_ALLIANCE_RECHARGE_VER);

	Json::Value data;
	data["allianceid"] = allianceid;
	data["version"] = version;
	string url = "action=getalliancerecharge";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	return logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
}

int CLogicRechargeAlliance::ReplyRechargeAllianceData(const Json::Value para,Json::Value &result)
{
	unsigned version = 0, allianceid = 0;
	Json::GetUInt(para, "allianceid", allianceid);
	Json::GetUInt(para, "version", version);

	CDataRechargeAlliance *pdata= GetRechargeAlliancePdata(allianceid);
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_recharge_alliance_fail");
	}

	vector <AllianceMember> ReAlliData;
	int ret = pdata->GetRechargeAlliacneData(allianceid,version,ReAlliData);
	if(ret != 0)
	{
		return ret;
	}

	result["alliance_id"] = allianceid;
	for(int i = 0; i < ReAlliData.size(); i++)
	{
		result["alliancedata"][i]["uid"] = ReAlliData[i].uid;
		result["alliancedata"][i]["cash"] = ReAlliData[i].cash;
		result["alliancedata"][i]["name"] = ReAlliData[i].name;
	}

	return 0;
}

int CLogicRechargeAlliance::UpdateRechargeAllianceData(AllianceMember &recharge)
{
	if( Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_ALLIANCE_RECHARGE_BEGIN_TS)
		&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_ALLIANCE_RECHARGE_END_TS))
	{
		CLogicUserBasic logicUserBasic;
		DataUserBasic dataUserBasic;
		logicUserBasic.GetUserBasicLimitWithoutPlatform(recharge.uid,dataUserBasic);
		memcpy(recharge.name,dataUserBasic.name.c_str(),sizeof(recharge.name) - 1);

		unsigned alliance_id = 0;  //通过uid获取其帮会id
		CDataUser datauser;
		DataUser user;
		int ret = datauser.GetUserLimit(recharge.uid,user);
		if(ret != 0)
			return ret;
		alliance_id = user.alliance_id;

		return _reportRechargeAllianceData(alliance_id,recharge);
	}
	return 0;
}

int CLogicRechargeAlliance::UpdateRechargeAllianceData(unsigned allianceid, AllianceMember &recharge)
{
	if( Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_ALLIANCE_RECHARGE_BEGIN_TS)
		&& Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_ALLIANCE_RECHARGE_END_TS))
	{
		return _reportRechargeAllianceData(allianceid,recharge);
	}
	return 0;
}

int CLogicRechargeAlliance::_reportRechargeAllianceData(unsigned allianceid, AllianceMember &recharge)
{
	if(!IsAllianceId(allianceid))
		return 0;

	int version = 0;
	Config::GetIntValue(version, CONFIG_ALLIANCE_RECHARGE_VER);

	Json::Value data;
	data["allianceid"] = allianceid;
	data["uid"] = recharge.uid;
	data["cash"] = recharge.cash;
	data["name"] = recharge.name;
	data["version"] = version;
	string url = "action=reportalliancerecharge";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	Json::Value result;
	return logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
}

int CLogicRechargeAlliance::ReceiveRechargeAllianceData(Json::Value data)
{
	unsigned allianceid = 0;
	unsigned version = 0;
	string temp;
	AllianceMember recharge;
	Json::GetUInt(data, "allianceid", allianceid);
	Json::GetUInt(data, "uid", recharge.uid);
	Json::GetUInt(data, "cash", recharge.cash);
	Json::GetUInt(data, "version", version);
	Json::GetString(data, "name", temp);
	memcpy(recharge.name,temp.c_str(),sizeof(recharge.name) - 1);

	CDataRechargeAlliance *pdata= GetRechargeAlliancePdata(allianceid);

	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_recharge_alliance_fail");
	}

	return pdata->UpdateRechargeAlliance(recharge,allianceid,version);
}
