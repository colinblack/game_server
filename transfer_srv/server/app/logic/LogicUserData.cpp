/*
 * LogicUserData.cpp
 *
 *  Created on: 2011-11-1
 *      Author: dada
 */

#include "LogicUserData.h"

#define RELATION_UPDATE_TIME (7*24*60*60)

int CLogicUserData::SetUserData(unsigned uid, const Json::Value &data)
{
	int ret;
	CDataUserData dbUserData;
	ret = dbUserData.SetData(uid, Json::ToString(data));
	if(ret != 0)
	{
		error_log("[SetData fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_data_fail");
	}
	return 0;
}

int CLogicUserData::GetUserData(unsigned uid, Json::Value &data)
{
	int ret;
	CDataUserData dbUserData;
	string sData;
	ret = dbUserData.GetData(uid, sData);
	if(ret == 0)
	{
		Json::FromString(data, sData);
	}
	else if(ret == R_ERR_NO_DATA)
	{
		ret = dbUserData.AddData(uid, "{}");
		if(ret != 0)
		{
			error_log("[AddData fail][ret=%d,uid=%u]", ret, uid);
			DB_ERROR_RETURN_MSG("add_user_data_fail");
		}
		data = Json::Value(Json::objectValue);
	}
	else
	{
		error_log("[GetData fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_data_fail");
	}
	return 0;
}

int CLogicUserData::RemoveUserData(unsigned uid)
{
	int ret;
	CDataUserData dbUserData;
	ret = dbUserData.RemoveData(uid);
	if(ret != 0)
	{
		error_log("[RemoveData fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("remove_user_data_fail");
	}
	return 0;
}

int CLogicUserData::GetPromoteFriends(unsigned uid, int count, vector<string> &friends)
{
	int ret;
	Json::Value data;
	ret = GetRelationData(uid, data, false);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value &naf = data["relation"]["naf"];
	Json::Value::Members members = naf.getMemberNames();
	int size = members.size();
	if(size > count)
	{
		vector<int> weightList;
		for(int i = 0; i < size; i++)
		{
			string openId = members[i];
			Json::Value &friendData = naf[openId];
			int promoteCount;
			if(Json::GetInt(friendData, 1u, promoteCount))
			{
				if((int)weightList.size() < count)
				{
					members[weightList.size()] = openId;
					weightList.push_back(promoteCount);
				}
				else
				{
					for(int j = 0; j < count; j++)
					{
						if(promoteCount < weightList[j])
						{
							int tempCount = weightList[j];
							weightList[j] = promoteCount;
							promoteCount = tempCount;
							string tempOpenId = members[j];
							members[j] = openId;
							openId = tempOpenId;
						}
					}
				}
			}
		}
		members.resize(weightList.size());
	}

	friends.clear();
	for(vector<string>::iterator itr = members.begin(); itr != members.end(); itr++)
	{
		Json::Value &friendData = naf[*itr];
		string name;
		if(Json::GetString(friendData, 0u, name))
		{
			friends.push_back(name);
			int promoteCount = 0;
			Json::GetInt(friendData, 1u, promoteCount);
			promoteCount++;
			friendData[1u] = promoteCount;
		}
	}

	ret = SetUserData(uid, data);
	return 0;
}

int CLogicUserData::GetNoAppFriends(unsigned uid, int count, vector<OPUserInfo> &friends)
{
	int ret;
	Json::Value data;
	ret = GetRelationData(uid, data);
	if(ret != 0)
	{
		return ret;
	}
	friends.clear();
	Json::Value &naf = data["relation"]["naf"];
	Json::Value::Members members = naf.getMemberNames();
	int size = members.size();
	for(int i = 0; i < count && size > 0; i++)
	{
		int n = Math::GetRandomInt(size);
		OPUserInfo userInfo;
		userInfo.OpenId = members[n];
		Json::Value &friendData = naf[userInfo.OpenId];
		Json::GetString(friendData, 0u, userInfo.Name);
		Json::GetString(friendData, 2u, userInfo.FigureUrl);
		friends.push_back(userInfo);
		members.erase(members.begin() + n);
		size--;
	}
	return 0;
}

int CLogicUserData::GetRelationData(unsigned uid, Json::Value &data, bool autoSave)
{
	int ret;
	ret = GetUserData(uid, data);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value &relation = data["relation"];
	unsigned lastUpdate = 0;
	Json::GetUInt(relation, "lut", lastUpdate);
	if(lastUpdate + RELATION_UPDATE_TIME > Time::GetGlobalTime())
	{
		return 0;
	}
	string openid;
	string openkey;
	ret = LogicSso::GetOpenKey(uid, openid, openkey);
	if(ret != 0)
	{
		return 0;
	}
	vector<OPUserInfo> friendList;
	ret = OpenPlatform::GetPlatform()->GetFriendList(friendList, openid, openkey);
	if(ret != 0)
	{
		return 0;
	}
	Json::Value &appFriends = relation["af"];
	set<string> appFriendSet;
	if(!appFriends.isArray())
	{
		appFriends = Json::Value(Json::arrayValue);
	}
	else
	{
		unsigned count = appFriends.size();
		for(unsigned i = 0; i < count; i++)
		{
			string friendId;
			if(Json::GetString(appFriends, i, friendId))
			{
				appFriendSet.insert(friendId);
			}
		}
	}
	Json::Value oldNoAppFriends = relation["naf"];
	Json::Value &noAppFriends = relation["naf"];
	noAppFriends = Json::Value(Json::objectValue);
	for(vector<OPUserInfo>::iterator itr = friendList.begin(); itr != friendList.end(); itr++)
	{
		string friendOpenId = itr->OpenId;
		if(appFriendSet.find(friendOpenId) == appFriendSet.end())
		{
			unsigned friendUid;
			ret = LogicUserBasic::GetUid(friendUid, OpenPlatform::GetType(), friendOpenId);
			if(ret == 0)
			{
				appFriends[appFriends.size()] = friendOpenId;
				appFriendSet.insert(friendOpenId);
			}
			else if(ret == R_ERR_NO_DATA)
			{
				int promoteCount = 0;
				if(oldNoAppFriends.isMember(friendOpenId))
				{
					Json::GetInt(oldNoAppFriends[friendOpenId], 1u, promoteCount);
				}
				Json::Value &friendData = noAppFriends[friendOpenId];
				friendData[0u] = itr->Name;
				friendData[1u] = promoteCount;
				friendData[2u] = itr->FigureUrl;
			}
		}
	}
	relation["lut"] = Time::GetGlobalTime();
	if(autoSave)
	{
		ret = SetUserData(uid, data);
	}
	return 0;
}
