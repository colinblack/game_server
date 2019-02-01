/*
 * LogicAllServerMap.cpp
 *
 *  Created on: 2015-9-15
 *      Author: Ralf
 */

#include "LogicAllServerMap.h"


int CLogicAllServerMap::Get(unsigned level, unsigned count, vector<unsigned> &res)
{
	Json::Value result;
	string url = "action=get";
	url += "&level=";
	url += CTrans::UTOS(level);
	url += "&count=";
	url += CTrans::UTOS(count);
	CLogicAllServerBaseMatch logicBaseMatch;
	logicBaseMatch.RequestBaseMatch(url,result, CONFIG_ALLS_MAP_PATH);

	if(result.isMember("map") && result["map"].isArray())
	{
		for(unsigned i=0;i<result["map"].size();++i)
			res.push_back(result["map"][i].asInt());
		random_shuffle(res.begin(), res.end());
	}

	return 0;
}

int CLogicAllServerMap::ReplyGet(unsigned level, unsigned count, Json::Value &result)
{
	CDataAllServerMap *data = GetData();
	if (NULL == data)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	set<unsigned> res;
	data->Get(level, count, res);

	result.resize(res.size());
	unsigned i = 0;
	for(set<unsigned>::iterator it=res.begin();it!=res.end();++it)
	{
		result[i] = *it;
		++i;
	}

	return 0;
}

int CLogicAllServerMap::Set(unsigned uid, unsigned level)
{
	CDataAllServerMapBuffer *data = CDataAllServerMapBuffer::GetCDataAllServerMapBuffer();
	if(!data)
	{
		error_log("GetCDataAllServerMap fail");
		return 1;
	}

	return data->Set(uid, level);
}

int CLogicAllServerMap::Syn()
{
	map<unsigned, unsigned> res;
	int ret = 0;
	CDataAllServerMapBuffer *data = CDataAllServerMapBuffer::GetCDataAllServerMapBuffer();
	if(!data)
	{
		error_log("GetCDataAllServerMap fail");
		return 1;
	}

	ret = data->Get(res);
	if (ret != 0)
		return ret;

	Json::Value val;
	val.resize(0);
	unsigned i=0;
	for(map<unsigned, unsigned>::iterator it=res.begin();it!=res.end();++it)
	{
		val[i][0u] = it->first;
		val[i][1u] = it->second;
		++i;

		if(i == 10)
		{
			string url = "action=set";
			string datastr = Json::ToString(val);
			url.append("&data=").append(Crypt::UrlEncode(datastr));

			CLogicAllServerBaseMatch logicBaseMatch;
			Json::Value result;
			logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MAP_PATH);

			val.resize(0);
			i=0;
		}

	}
	if(val.size())
	{
		string url = "action=set";
		string datastr = Json::ToString(val);
		url.append("&data=").append(Crypt::UrlEncode(datastr));

		CLogicAllServerBaseMatch logicBaseMatch;
		Json::Value result;
		logicBaseMatch.RequestBaseMatch(url,result,CONFIG_ALLS_MAP_PATH);
	}

	return 0;
}

int CLogicAllServerMap::ReplySyn(Json::Value &para)
{
	map<unsigned, unsigned> res;
	for(unsigned i=0;i<para.size();++i)
		res[para[i][0u].asUInt()] = para[i][1u].asInt();

	CDataAllServerMap *data = GetData();
	if (NULL == data)
	{
		error_log("GetData fail");
		return R_ERR_DATA;
	}

	return data->Set(res);
}
