/*
 * LogicFriend.cpp
 *
 *  Created on: 2012-3-5
 *      Author: dada
 */

#include "LogicFriend.h"

static bool AddNewFriend(unsigned uid, PlatformType platform, const string &openId, const OPFriendList &friendList, DataFriend &dataFriend)
{
	int ret;
	CDataFriend dbFriend;
	int add = false;
	string separator = ",";
	string selfAppend = openId + separator;
	string selfFind = separator + selfAppend;
	string selfUidAppend;
	String::Format(selfUidAppend, "%u,", uid);
	for(OPFriendList::const_iterator itr = friendList.begin(); itr != friendList.end(); itr++)
	{
		if(*itr!= openId && dataFriend.friends_mapping.find(separator + *itr + separator) == string::npos)
		{
			unsigned friendId;
			ret = LogicUserBasic::GetUid(friendId, platform, *itr, false);
			if(ret == 0)
			{
				//增加反向好友
				DataFriend friendsOp;
				ret = dbFriend.GetFriend(friendId, platform, friendsOp);
				if(ret != 0)
				{
					error_log("[GetFriends fail][ret=%d,uid=%u,platform=%d]", ret, friendId, platform);
				}
				else
				{
					if(friendsOp.friends_mapping.find(selfFind) == string::npos)
					{
						friendsOp.friends.append(selfUidAppend);
						friendsOp.friends_mapping.append(selfAppend);
						ret = dbFriend.SetFriend(friendsOp);
						if(ret != 0)
						{
							error_log("[SetFriends fail][ret=%d,uid=%u,platform=%d]", ret, friendId, platform);
						}
						else
						{
							string friendAppend;
							String::Format(friendAppend, "%u,", friendId);
							dataFriend.friends.append(friendAppend);
							dataFriend.friends_mapping.append(*itr + separator);
							add = true;
						}
					}
					else
					{
						error_log("[ASSERT(friend_not_pair)][uid=%u,fid=%u,platform=%d,action=add]", uid, friendId, platform);
						string friendAppend;
						String::Format(friendAppend, "%u,", friendId);
						dataFriend.friends.append(friendAppend);
						dataFriend.friends_mapping.append(*itr + separator);
						add = true;
					}
				}
			}
		}
	}
	return add;
}

int LogicFriend::AddFriends(unsigned uid, PlatformType platform, const string &openId, const OPFriendList &friendList)
{
	int ret;
	CDataFriend dbFriend;
	DataFriend dataFriend;
	dataFriend.uid = uid;
	dataFriend.platform = platform;
	dataFriend.last_update_time = Time::GetGlobalTime();
	dataFriend.friends = ",";
	dataFriend.friends_mapping = ",";
	AddNewFriend(uid, platform, openId, friendList, dataFriend);
	ret = dbFriend.AddFriend(dataFriend);
	if(ret != 0)
	{
		error_log("[AddFriend fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
		DB_ERROR_RETURN_MSG("add_friend_fail");
	}
	return 0;
}

int LogicFriend::UpdateFriends(unsigned uid, PlatformType platform, const string &openId, const OPFriendList &friendList)
{
	int ret;
	bool update = false;
	CDataFriend dbFriend;
	DataFriend dataFriend;
	ret = dbFriend.GetFriend(uid, platform, dataFriend);
	if(ret != 0)
	{
		error_log("[GetFriend fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
		DB_ERROR_RETURN_MSG("get_friend_fail");
	}

	//每天第一次更新同步删除好友
	if(!Time::IsToday(dataFriend.last_update_time))
	{
		update = true;
		string separator = ",";
		string selfRemoveUid;
		String::Format(selfRemoveUid, ",%u,", uid);
		string selfRemoveOpenId = separator + openId + separator;
		vector<string> currFriendUidList;
		CBasic::StringSplitTrim(dataFriend.friends, separator, currFriendUidList);
		vector<string> currFriendList;
		CBasic::StringSplitTrim(dataFriend.friends_mapping, separator, currFriendList);
		if(currFriendList.size() != currFriendUidList.size())
		{
			fatal_log("[friend_count_mismatch][uid=%u,platform=%d,friend=%d,friend_mapping=%d]",
					uid, platform, (int)currFriendList.size(), (int)currFriendUidList.size());
		}
		else
		{
			for(size_t i = 0; i < currFriendList.size(); i++)
			{
				string currFriend = currFriendList[i];
				if(currFriend == openId || find(friendList.begin(), friendList.end(), currFriend) == friendList.end())
				{
					string sOpenIdRemove = separator + currFriend + separator;
					string sUidFriend = currFriendUidList[i];
					string sUidRemove = separator + sUidFriend + separator;
					CBasic::StringReplace(dataFriend.friends, sUidRemove, separator);
					CBasic::StringReplace(dataFriend.friends_mapping, sOpenIdRemove, separator);

					//删除反向好友
					unsigned currFriendUid;
					if(!Convert::StringToUInt(currFriendUid, sUidFriend))
					{
						error_log("[unknow_friend_uid][uid=%u,friendid=%s]", uid, sUidFriend.c_str());
					}
					else
					{
						DataFriend friendsOp;
						ret = dbFriend.GetFriend(currFriendUid, platform, friendsOp);
						if(ret != 0)
						{
							error_log("[GetFriends fail][ret=%d,uid=%u,platform=%d]", ret, currFriendUid, platform);
						}
						else
						{
							if(friendsOp.friends.find(selfRemoveUid) != string::npos &&
								friendsOp.friends_mapping.find(selfRemoveOpenId) != string::npos)
							{
								CBasic::StringReplace(friendsOp.friends, selfRemoveUid, separator);
								CBasic::StringReplace(friendsOp.friends_mapping, selfRemoveOpenId, separator);
								ret = dbFriend.SetFriend(friendsOp);
								if(ret != 0)
								{
									error_log("[SetFriends fail][ret=%d,uid=%u,platform=%d]", ret, currFriendUid, platform);
								}
							}
							else
							{
								error_log("[ASSERT(friend_not_pair)][uid=%u,fid=%u,platform=%d,action=remove]", uid, currFriendUid, platform);
							}
						}
					}
				}
			}
		}
	}

	if(AddNewFriend(uid, platform, openId, friendList, dataFriend))
	{
		update = true;
	}

	if(update)
	{
		dataFriend.last_update_time = Time::GetGlobalTime();
		ret = dbFriend.SetFriend(dataFriend);
		if(ret != 0)
		{
			error_log("[SetFriend fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
			DB_ERROR_RETURN_MSG("set_friend_fail");
		}
	}
	return 0;
}

int LogicFriend::GetFriends(unsigned uid, PlatformType platform, UidList &friends)
{
	int ret;
	CDataFriend dbFriend;
	string sFriends;
	ret = dbFriend.GetFriends(uid, platform, sFriends);
	if(ret != 0)
	{
		error_log("[GetFriends fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
		DB_ERROR_RETURN_MSG("get_friend_fail");
	}
	friends.clear();
	vector<string> vecFriends;
	CBasic::StringSplitTrim(sFriends, ",", vecFriends);
	for(vector<string>::iterator itr = vecFriends.begin(); itr != vecFriends.end(); itr++)
	{
		unsigned friendId;
		if(Convert::StringToUInt(friendId, *itr))
		{
			friends.push_back(friendId);
		}
		else
		{
			error_log("[parse_friend_fail][uid=%u,platform=%d,friend=%s]", uid, platform, itr->c_str());
		}
	}
	return 0;
}

int LogicFriend::GetFriendsJson(unsigned uid, PlatformType platform, Json::Value &friends)
{
	int ret;
	UidList friendList;
	ret = GetFriends(uid, platform, friendList);
	if(ret != 0)
	{
		return ret;
	}

	map<unsigned, int> interacts;
	if(IsMercenary())
	{
		CLogicUserInteract logicInteract;
		ret = logicInteract.GetFriendInteracts(uid, interacts);
	}

	friends.resize(0);
	friendList.push_back(uid);
	for(UidList::iterator itr = friendList.begin(); itr != friendList.end(); itr++)
	{
		DataUserBasic userBasic;
		ret = LogicUserBasic::GetUser(*itr, platform, userBasic);
		if(ret != 0)
		{
			continue;
		}
		DataUser user;
		ret = LogicUser::GetUser(*itr, user);
		if(ret != 0)
		{
			continue;
		}
		if(user.status != US_ACTIVE)
		{
			continue;
		}

		Json::Value userData;
		userData["userid"] = *itr;
		if(uid == *itr)
		{
			userData["mine"] = 1;
		}
		userData["openid"] = userBasic.open_id;
		userData["name"] = userBasic.name;
		userData["pic"] = userBasic.figure_url;
		userData["baseid"] = user.main_base_id;
		userData["level"] = user.level;
		userData["world"] = user.world;
		userData["vt"] = userBasic.vip_type;
		userData["vl"] = userBasic.vip_level;
		if(IsMercenary())
		{
			map<unsigned, int>::iterator itrInteract = interacts.find(*itr);
			if(itrInteract != interacts.end())
			{
				userData["ic"] = itrInteract->second;
			}
		}
		friends.append(userData);
	}

	return 0;
}

bool LogicFriend::IsFriend(unsigned uid, PlatformType platform, unsigned friendId)
{
	int ret;
	CDataFriend dbFriend;
	string sFriends;
	ret = dbFriend.GetFriends(uid, platform, sFriends);
	if(ret != 0)
	{
		error_log("[GetFriends fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
		return false;
	}
	string sFind;
	String::Format(sFind, ",%u,", friendId);
	if(sFriends.find(sFind) == string::npos)
	{
		return false;
	}
	return true;
}

