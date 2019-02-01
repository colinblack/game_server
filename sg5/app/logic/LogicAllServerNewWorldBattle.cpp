/*
 * LogicAllServerNewWorldBattle.cpp
 *
 *  Created on: 2015-2-12
 *      Author: Ralf
 */


#include "LogicAllServerNewWorldBattle.h"

CLogicAllServerNewWorldBattle::CLogicAllServerNewWorldBattle(){
}

CDataAllServerNewWorldBattle* CLogicAllServerNewWorldBattle::GetDataAllServerNewWorldBattle(void)
{
	GET_MEM_DATA_SEM(CDataAllServerNewWorldBattle, CONFIG_ALL_SERVER_NEW_WORLD_BATTLE_DATA, sem_all_server_new_world_battle, true)
}

int CLogicAllServerNewWorldBattle::GetList(Json::Value &result)
{
	string url = "action=getAllServerNewWorldBattlelist";
	CLogicAllServerBaseMatch logicBaseMatch;
	int ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
	if(ret)
		return ret;

	return 0;
}

int CLogicAllServerNewWorldBattle::SetAttack(unsigned uid, unsigned attack, unsigned kingdom, unsigned defend, Json::Value &result)
{
	CLogicKingdom logicKingdom;
	vector<KingdomJob> kingdomjob;
	kingdomjob.push_back(Job_King);
	kingdomjob.push_back(Job_General);
	kingdomjob.push_back(Job_Minister);
	int ret = logicKingdom.CheckJobs(kingdom, kingdomjob, uid);
	if(ret)
		return ret;

	Json::Value data;
	data["attack"] = attack;
	data["kingdom"] = kingdom;
	data["defend"] = defend;
	string url = "action=setAllServerNewWorldBattleAttack";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
	if(ret)
		return ret;

	CLogicPay logicPay;
	DataPay payData;
	Json::Value user_flag;
	bool bsave = false;
	ret = logicPay.ProcessOrderForBackend(uid, -100, 0, payData, "setAllServerNewWorldBattleAttack", user_flag, bsave);
	if (ret)
		return ret;

	return 0;
}

int CLogicAllServerNewWorldBattle::ReplyList(Json::Value &result)
{
	int ret = 0;

	CDataAllServerNewWorldBattle *pData = GetDataAllServerNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataAllServerNewWorldBattle fail");
		return R_ERR_DATA;
	}

	vector<NewWorldBattleServer> domain;
	ret = pData->GetList(domain);
	if(ret)
		return ret;

	result.resize(domain.size());
	for(unsigned i=0;i<domain.size();++i)
	{
		Json::Value temp;
		temp["serverid"] 		= domain[i].serverid;
		temp["domain"] 			= domain[i].domain;
		temp["defendTS"] 		= domain[i].defendTS;
		temp["defendServer"] 	= domain[i].defendServer;
		temp["host"] 			= domain[i].host;
		temp["result"] 			= domain[i].result;
		temp["defendKingdom"] 	= domain[i].defendKingdom;
		for(unsigned j=0;j<3;++j)
		{
			temp["kingdom"][j]["attackTS"] 		= domain[i].kingdom[j].attackTS;
			temp["kingdom"][j]["army"] 			= domain[i].kingdom[j].army;
			temp["kingdom"][j]["attackServer"] 	= domain[i].kingdom[j].attackServer;
			temp["kingdom"][j]["result"] 	= domain[i].kingdom[j].result;
		}
		result[i] = temp;
	}

	return 0;
}

int CLogicAllServerNewWorldBattle::ReplyAttack(unsigned attack, unsigned kingdom, unsigned defend, Json::Value &result)
{
	int ret = 0;

	CDataAllServerNewWorldBattle *pData = GetDataAllServerNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataAllServerNewWorldBattle fail");
		return R_ERR_DATA;
	}

	vector<NewWorldBattleServer> domain;
	ret = pData->SetAttack(attack, kingdom, defend, domain);
	if(ret)
		return ret;

	result.resize(domain.size());
	for(unsigned i=0;i<domain.size();++i)
	{
		Json::Value temp;
		temp["serverid"] 		= domain[i].serverid;
		temp["domain"] 			= domain[i].domain;
		temp["defendTS"] 		= domain[i].defendTS;
		temp["defendServer"] 	= domain[i].defendServer;
		temp["host"] 			= domain[i].host;
		temp["result"] 			= domain[i].result;
		temp["defendKingdom"] 	= domain[i].defendKingdom;
		for(unsigned j=0;j<3;++j)
		{
			temp["kingdom"][j]["attackTS"] 		= domain[i].kingdom[j].attackTS;
			temp["kingdom"][j]["army"] 			= domain[i].kingdom[j].army;
			temp["kingdom"][j]["attackServer"] 	= domain[i].kingdom[j].attackServer;
			temp["kingdom"][j]["result"] 	= domain[i].kingdom[j].result;
		}
		result[i] = temp;
	}

	return 0;
}

int CLogicAllServerNewWorldBattle::SetArmy(unsigned serverid, unsigned domain, unsigned army[3], string& host)
{
	Json::Value data;
	data["serverid"] = serverid;
	data["domain"] = domain;
	data["army"][0u] = army[0];
	data["army"][1u] = army[1];
	data["army"][2u] = army[2];
	data["host"] = host;
	string url = "action=setAllServerNewWorldBattleArmy";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	CLogicAllServerBaseMatch logicBaseMatch;
	Json::Value result;
	int ret = logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MATCH_SERVER_PATH,true);
	if(ret)
		return ret;

	return 0;
}
int CLogicAllServerNewWorldBattle::ReplyArmy(unsigned serverid, unsigned domain, unsigned army[3], string& host)
{
	int ret = 0;

	CDataAllServerNewWorldBattle *pData = GetDataAllServerNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataAllServerNewWorldBattle fail");
		return R_ERR_DATA;
	}

	ret = pData->SetArmy(serverid, domain, army, host);
	if(ret)
		return ret;

	return 0;
}

int CLogicAllServerNewWorldBattle::SetResult(unsigned defend, unsigned result)
{
	Json::Value data;
	data["defend"] = defend;
	data["result"] = result;
	string url = "action=setAllServerNewWorldBattleResult";
	string datastr = Json::ToString(data);
	url.append("&data=").append(Crypt::UrlEncode(datastr));

	Json::Value temp;
	CLogicAllServerBaseMatch logicBaseMatch;
	return logicBaseMatch.RequestBaseMatch(url,temp,CONFIG_ALLS_MATCH_SERVER_PATH,true);
}
int CLogicAllServerNewWorldBattle::ReplyResult(unsigned defend, unsigned result)
{
	CDataAllServerNewWorldBattle *pData = GetDataAllServerNewWorldBattle();
	if (NULL == pData)
	{
		error_log("GetDataAllServerNewWorldBattle fail");
		return R_ERR_DATA;
	}

	return pData->SetResult(defend, result);
}
