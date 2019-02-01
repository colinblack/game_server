/*
 * LogicUserInteract.cpp
 *
 *  Created on: 2011-7-13
 *      Author: dada
 */

#include "LogicUserInteract.h"
#include "FacebookPlatform.h"

#define REQUEST_ITEM_TIMEOUT (6 * 60 * 60)
#define HELP_REWARD_TIMEOUT (24 * 60 * 60)
#define REQUEST_ITEM_LIMIT 3
#define APP_INTERACTS_LIMIT 4

int CLogicUserInteract::AddHelp(unsigned uidFrom, unsigned uidTo)
{
	int ret;
	if(uidFrom == uidTo)
	{
		PARAM_ERROR_RETURN_MSG("self_help");
	}
	DataUserInteract userInteract;
	CDataUserInteract dbUserInteract;
	ret = dbUserInteract.GetInteract(uidFrom, uidTo, userInteract);
	if(ret == 0)
	{
		userInteract.help_to++;
		ret = dbUserInteract.SetInteract(userInteract);
		if(ret != 0)
		{
			error_log("[SetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidFrom, uidTo);
			DB_ERROR_RETURN_MSG("set_user_interact_fail");
		}
	}
	else if(ret == R_ERR_NO_DATA)
	{
		userInteract.uid = uidFrom;
		userInteract.opposite_uid = uidTo;
		userInteract.help_from = 0;
		userInteract.help_to = 1;
		userInteract.attack_from = 0;
		userInteract.attack_to = 0;
		userInteract.retaliate_count = 0;
		userInteract.last_attack_time = 0;
		userInteract.truce_time = 0;
		userInteract.flag = 0;
		ret = dbUserInteract.AddInteract(userInteract);
		if(ret != 0)
		{
			error_log("[AddInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidFrom, uidTo);
			DB_ERROR_RETURN_MSG("add_user_interact_fail");
		}
	}
	else
	{
		error_log("[GetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidFrom, uidTo);
		DB_ERROR_RETURN_MSG("get_user_interact_fail");
	}

	ret = dbUserInteract.GetInteract(uidTo, uidFrom, userInteract);
	if(ret == 0)
	{
		userInteract.help_from++;
		ret = dbUserInteract.SetInteract(userInteract);
		if(ret != 0)
		{
			error_log("[SetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidTo, uidFrom);
			DB_ERROR_RETURN_MSG("set_user_interact_fail");
		}
	}
	else if(ret == R_ERR_NO_DATA)
	{
		userInteract.uid = uidTo;
		userInteract.opposite_uid = uidFrom;
		userInteract.help_from = 1;
		userInteract.help_to = 0;
		userInteract.attack_from = 0;
		userInteract.attack_to = 0;
		userInteract.retaliate_count = 0;
		userInteract.last_attack_time = 0;
		userInteract.truce_time = 0;
		userInteract.flag = 0;
		ret = dbUserInteract.AddInteract(userInteract);
		if(ret != 0)
		{
			error_log("[AddInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidTo, uidFrom);
			DB_ERROR_RETURN_MSG("add_user_interact_fail");
		}
	}
	else
	{
		error_log("[GetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidTo, uidFrom);
		DB_ERROR_RETURN_MSG("get_user_interact_fail");
	}

	return 0;
}


int CLogicUserInteract::AddAttack(unsigned uidFrom, unsigned uidTo)
{
	int ret;
	if(uidFrom == uidTo)
	{
		PARAM_ERROR_RETURN_MSG("self_attack");
	}
	DataUserInteract userInteract;
	CDataUserInteract dbUserInteract;
	ret = dbUserInteract.GetInteract(uidFrom, uidTo, userInteract);
	if(ret == 0)
	{
		userInteract.attack_to++;
		if(userInteract.retaliate_count > 0)
		{
			userInteract.retaliate_count--;
		}
		userInteract.last_attack_time = Time::GetGlobalTime();
		ret = dbUserInteract.SetInteract(userInteract);
		if(ret != 0)
		{
			error_log("[SetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidFrom, uidTo);
			DB_ERROR_RETURN_MSG("set_user_interact_fail");
		}
	}
	else if(ret == R_ERR_NO_DATA)
	{
		userInteract.uid = uidFrom;
		userInteract.opposite_uid = uidTo;
		userInteract.help_from = 0;
		userInteract.help_to = 0;
		userInteract.attack_from = 0;
		userInteract.attack_to = 1;
		userInteract.retaliate_count = 0;
		userInteract.last_attack_time = Time::GetGlobalTime();
		userInteract.truce_time = 0;
		userInteract.flag = 0;
		ret = dbUserInteract.AddInteract(userInteract);
		if(ret != 0)
		{
			error_log("[AddInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidFrom, uidTo);
			DB_ERROR_RETURN_MSG("add_user_interact_fail");
		}
	}
	else
	{
		error_log("[GetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidFrom, uidTo);
		DB_ERROR_RETURN_MSG("get_user_interact_fail");
	}

	ret = dbUserInteract.GetInteract(uidTo, uidFrom, userInteract);
	if(ret == 0)
	{
		userInteract.attack_from++;
		if(userInteract.retaliate_count < 10000)
		{
			userInteract.retaliate_count++;
		}
		userInteract.last_attack_time = Time::GetGlobalTime();
		ret = dbUserInteract.SetInteract(userInteract);
		if(ret != 0)
		{
			error_log("[SetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidTo, uidFrom);
			DB_ERROR_RETURN_MSG("set_user_interact_fail");
		}
	}
	else if(ret == R_ERR_NO_DATA)
	{
		userInteract.uid = uidTo;
		userInteract.opposite_uid = uidFrom;
		userInteract.help_from = 0;
		userInteract.help_to = 0;
		userInteract.attack_from = 1;
		userInteract.attack_to = 0;
		userInteract.retaliate_count = 1;
		userInteract.last_attack_time = Time::GetGlobalTime();
		userInteract.truce_time = 0;
		userInteract.flag = 0;
		ret = dbUserInteract.AddInteract(userInteract);
		if(ret != 0)
		{
			error_log("[AddInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidTo, uidFrom);
			DB_ERROR_RETURN_MSG("add_user_interact_fail");
		}
	}
	else
	{
		error_log("[GetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, uidTo, uidFrom);
		DB_ERROR_RETURN_MSG("get_user_interact_fail");
	}

	return 0;
}

int CLogicUserInteract::GetInteract(unsigned uid, unsigned oppositeUid, DataUserInteract &interact)
{
	int ret;
	CDataUserInteract dbUserInteract;
	ret = dbUserInteract.GetInteract(uid, oppositeUid, interact);
	if(ret == R_ERR_NO_DATA)
	{
		return R_ERR_NO_DATA;
	}
	if(ret != 0)
	{
		error_log("[GetInteracts fail][ret=%d,uid=%u,opuid=%u]", ret, uid, oppositeUid);
		DB_ERROR_RETURN_MSG("get_user_interact_fail");
	}
	return 0;
}

int CLogicUserInteract::GetInteracts(unsigned uid, map<unsigned, DataUserInteract> &interacts)
{
	int ret;
	CDataUserInteract dbUserInteract;
	ret = dbUserInteract.GetInteracts(uid, interacts);
	if(ret != 0)
	{
		error_log("[GetInteracts fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_interact_fail");
	}
	return 0;
}

int CLogicUserInteract::ProcessRequest(const DataMessage &request, unsigned from, unsigned to, const string &type, int action, const Json::Value &data)
{
	int ret;
	if(action != MS_ACCEPT)
	{
		return 0;
	}
	if(!IsValidUid(from) || (!IsValidUid(to) && to != MUT_ALL))
	{
		error_log("[error_request][from=%u,to=%u,type=%s,action=%d]", from, to, type.c_str(), action);
		PARAM_ERROR_RETURN();
	}
	if(type == "truce")
	{
		CDataUserInteract dbInteract;
		DataUserInteract userInteract;
		ret = GetInteract(from, to, userInteract);
		if(ret == 0)
		{
			userInteract.truce_time = Time::GetGlobalTime() + TRUCE_TIME;
			ret = dbInteract.SetInteract(userInteract);
			if(ret != 0)
			{
				error_log("[SetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, from, to);
				DB_ERROR_RETURN_MSG("set_user_interact_fail");
			}
		}
		else if(ret == R_ERR_NO_DATA)
		{
			userInteract.uid = from;
			userInteract.opposite_uid = to;
			userInteract.help_from = 0;
			userInteract.help_to = 0;
			userInteract.attack_from = 0;
			userInteract.attack_to = 0;
			userInteract.retaliate_count = 0;
			userInteract.last_attack_time = 0;
			userInteract.truce_time = Time::GetGlobalTime() + TRUCE_TIME;
			userInteract.flag = 0;
			ret = dbInteract.AddInteract(userInteract);
			if(ret != 0)
			{
				error_log("[AddInteract fail][ret=%u,uid=%u,opuid=%u]", ret, from, to);
				return ret;
			}
		}
		else
		{
			return ret;
		}

		ret = GetInteract(to, from, userInteract);
		if(ret == 0)
		{
			userInteract.truce_time = Time::GetGlobalTime() + TRUCE_TIME;
			ret = dbInteract.SetInteract(userInteract);
			if(ret != 0)
			{
				error_log("[SetInteract fail][ret=%u,uid=%u,opuid=%u]", ret, to, from);
				DB_ERROR_RETURN_MSG("set_user_interact_fail");
			}
		}
		else if(ret == R_ERR_NO_DATA)
		{
			userInteract.uid = to;
			userInteract.opposite_uid = from;
			userInteract.help_from = 0;
			userInteract.help_to = 0;
			userInteract.attack_from = 0;
			userInteract.attack_to = 0;
			userInteract.retaliate_count = 0;
			userInteract.last_attack_time = 0;
			userInteract.truce_time = Time::GetGlobalTime() + TRUCE_TIME;
			userInteract.flag = 0;
			ret = dbInteract.AddInteract(userInteract);
			if(ret != 0)
			{
				error_log("[AddInteract fail][ret=%u,uid=%u,opuid=%u]", ret, to, from);
				return ret;
			}
		}
		else
		{
			return ret;
		}
	}
	else if(type == "sendgift" || type == "responsegift" || type == "sendback")
	{
		string itemid;
		if(!Json::GetString(data, "data", itemid))
		{
			error_log("[send_gift_data_error][from=%u,to=%u,type=%s,data=%s]", from, to, type.c_str(), Json::ToString(data).c_str());
			return R_ERR_PARAM;
		}
		CLogicInventory logicInventory;
		ret = logicInventory.ChangeItem(to, itemid, 1);
		if(ret != 0)
		{
			return ret;
		}
		if(type == "sendgift")
		{
			CDataUser dbUser;
			ChangeInteractStat(from, "giftsend", 1);
			if(ret != 0)
			{
				error_log("[AddGiftSend fail][ret=%d,uid=%u]", ret, from);
			}
		}
		ret = ChangeInteractStat(to, "giftrecv", 1);
	}
	else if(type == "requesthelp" || type == "requestcrew")
	{
		string updateType;
		if(type == "requestcrew")
		{
			updateType = "CREW";
		}
		else
		{
			updateType = "BH";
		}
		string buildingId;
		if(!Json::GetString(data, "data", buildingId))
		{
			error_log("[help_data_error][from=%u,to=%u,type=%s,data=%s]", from, to, type.c_str(), Json::ToString(data).c_str());
			return R_ERR_PARAM;
		}
		unsigned baseid;
		ret = LogicUser::GetMainBaseId(from, baseid);
		if(ret != 0)
		{
			return ret;
		}
		Json::Value updates;
		Json::Value &update = updates[0u];
		update[0u] = Time::GetGlobalTime();
		update[1u] = updateType;
		update[2u] = buildingId;
		update[3u] = to;
		ret = LogicBase::AddUpdate(from, baseid, to, updates);
		if(ret != 0)
		{
			return ret;
		}
	}
	else if(type == "requestitem")
	{
		string itemid;
		Json::GetString(data, "itemid", itemid);
		if(Json::IsArray(data, "users"))
		{
			unsigned userCount = data["users"].size();
			for(unsigned i = 0; i < userCount; i++)
			{
				unsigned currUid;
				if(Json::GetUInt(data["users"], i, currUid))
				{
					if(currUid == to)
					{
						error_log("[have_sent_item][messageId=%llu,from=%u,to=%u]", request.message_id, from, to);
						ERROR_RETURN_MSG(R_ERR_LOGIC, "have_sent_item");
					}
				}
			}
		}
		if(request.time + REQUEST_ITEM_TIMEOUT < Time::GetGlobalTime())
		{
			error_log("[request_item_timeout][from=%u,to=%u,messageId=%llu,ts=%u]", from, to, request.message_id, request.time);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "request_item_timeout");
		}
		int requestCount = 0;
		int count = 0;
		Json::GetInt(data, "rcount", requestCount);
		Json::GetInt(data, "count", count);
		if(count >= requestCount || requestCount <= 0)
		{
			error_log("[request_enough_item][messageId=%llu,count=%d,rcount=%d]", request.message_id, count, requestCount);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "request_item_enough");
		}
		if(!LogicFriend::IsFriend(from, OpenPlatform::GetType(), to))
		{
			error_log("[is_not_friend][messageId=%llu,from=%u,to=%u]", request.message_id, from, to);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_friend");
		}
		CLogicInventory logicInventory;
		ret = logicInventory.ChangeItem(from, itemid, 1);
		if(ret != 0)
		{
			return ret;
		}
		ret = ChangeInteractStat(from, "giftrecv", 1);
		ret = logicInventory.ChangeItem(to, itemid, 1);
		if(ret != 0)
		{
			return ret;
		}
		ret = ChangeInteractStat(to, "giftrecv", 1);
		Json::Value newData = data;
		newData["count"] = count + 1;
		newData["users"].append(to);
		CLogicMessage logicMessage;
		ret = logicMessage.SetMessageContent(request.message_id, Json::ToString(newData));
		if(ret != 0)
		{
			return ret;
		}
	}
	else if(type == "helpreward")
	{
		string itemid;
		Json::GetString(data, "itemid", itemid);
		if(Json::IsArray(data, "users"))
		{
			unsigned userCount = data["users"].size();
			for(unsigned i = 0; i < userCount; i++)
			{
				unsigned currUid;
				if(Json::GetUInt(data["users"], i, currUid))
				{
					if(currUid == to)
					{
						error_log("[have_sent_reward][messageId=%llu,from=%u,to=%u]", request.message_id, from, to);
						ERROR_RETURN_MSG(R_ERR_LOGIC, "have_sent_reward");
					}
				}
			}
		}
		if(request.time + HELP_REWARD_TIMEOUT < Time::GetGlobalTime())
		{
			error_log("[help_reward_timeout][from=%u,to=%u,messageId=%llu,ts=%u]", from, to, request.message_id, request.time);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "help_reward_timeout");
		}
		int totalCount = 0;
		int count = 0;
		Json::GetInt(data, "tcount", totalCount);
		Json::GetInt(data, "count", count);
		if(count >= totalCount || totalCount <= 0)
		{
			error_log("[reward_send_ount][messageId=%llu,count=%d,tcount=%d]", request.message_id, count, totalCount);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "reward_send_out");
		}
		if(!LogicFriend::IsFriend(from, OpenPlatform::GetType(), to))
		{
			error_log("[is_not_friend][messageId=%llu,from=%u,to=%u]", request.message_id, from, to);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "is_not_friend");
		}
		CLogicInventory logicInventory;
		ret = logicInventory.ChangeItem(to, itemid, 1);
		if(ret != 0)
		{
			return ret;
		}
		ret = ChangeInteractStat(to, "giftrecv", 1);
		Json::Value newData = data;
		newData["count"] = count + 1;
		newData["users"].append(to);
		CLogicMessage logicMessage;
		ret = logicMessage.SetMessageContent(request.message_id, Json::ToString(newData));
		if(ret != 0)
		{
			return ret;
		}
	}
	return 0;
}

int CLogicUserInteract::SendRequest(unsigned uid, const string &type, const string &data, const map<string, string> &userRequests)
{
	int ret;
	bool toAll = false;
	if(type == "sendgift" || type == "requestgift")
	{
		if(!String::StartWith(data, "gift_"))
		{
			error_log("[invalid_gift_id][uid=%u,type=%s,data=%s]", uid, type.c_str(), data.c_str());
		}
		toAll = true;
	}
	else if(type == "sendback" || type == "responsegift")
	{
		if(!String::StartWith(data, "gift_"))
		{
			error_log("[invalid_gift_id][uid=%u,type=%s,data=%s]", uid, type.c_str(), data.c_str());
		}
		toAll = false;
	}
	else if(type == "requesthelp" || type == "requestcrew")
	{
		//toAll = false;
		toAll = true;
	}
	else
	{
		error_log("[unknow_type][uid=%u,type=%s,typeId=%s]", uid, type.c_str(), data.c_str());
		PARAM_ERROR_RETURN();
	}

	Json::Value userData;
	CLogicUserData logicUserData;
	ret = logicUserData.GetUserData(uid, userData);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value &requestData = userData[type];
	unsigned lastTime = 0;
	Json::GetUInt(requestData, "lt", lastTime);
	if(!Time::IsToday(lastTime) || !Json::IsArray(requestData, "users"))
	{
		requestData["users"] = Json::Value(Json::arrayValue);
	}
	requestData["lt"] = Time::GetGlobalTime();
	Json::Value &usersData = requestData["users"];
	set<string> requestUsers;
	unsigned count = usersData.size();
	for(unsigned i = 0; i < count; i++)
	{
		string friendId;
		if(Json::GetString(usersData, i, friendId))
		{
			requestUsers.insert(friendId);
		}
	}

	string openid;
	string openkey;
	CLogicMessage logicMessage;
	for(map<string, string>::const_iterator itr = userRequests.begin(); itr != userRequests.end(); itr++)
	{
		string toOpenId = itr->first;
		if(requestUsers.find(toOpenId) == requestUsers.end())
		{
			Json::Value requestData;
			requestData["type"] = type;
			requestData["data"] = data;
			requestData["requestid"] = itr->second;

			unsigned friendUid = 0;
			ret = LogicUserBasic::GetUid(friendUid, OpenPlatform::GetType(), toOpenId);
			if(ret == 0)
			{
				ret = logicMessage.AddRequest(uid, friendUid, requestData);
				if(ret == 0)
				{
					usersData[usersData.size()] = toOpenId;
					requestUsers.insert(toOpenId);
				}
			}
			else if(ret == R_ERR_NO_DATA && toAll && OpenPlatform::GetType() == PT_FACEBOOK)
			{
				if(openid.empty() && openkey.empty())
				{
					ret = LogicSso::GetOpenKey(uid, openid, openkey);
					if(ret != 0)
					{
						return ret;
					}
				}
				OPUserInfo userInfo;
				ret = ((CFacebookPlatform *)(OpenPlatform::GetPlatform()))->GetOtherUserInfo(userInfo, toOpenId, openid, openkey);
				if(ret == 0)
				{
					uint64_t messageId;
					ret = logicMessage.AddPlatformRequest(messageId, uid, userInfo, requestData);
					if(ret == 0)
					{
						CLogicPlatformUser logicPlatformUser;
						ret = logicPlatformUser.AddPendingMessage(toOpenId, OpenPlatform::GetType(), messageId);
						usersData[usersData.size()] = toOpenId;
						requestUsers.insert(toOpenId);
					}
				}
			}
			else
			{
				error_log("[unknow_user][ret=%d,uid=%u,toOpenId=%s,type=%s]", ret, uid, toOpenId.c_str(), type.c_str());
			}
		}
		else
		{
			error_log("[have_sent_gift][uid=%u,type=%s,itemid=%s,targetOpenId=%s,requestId=%s]",
					uid, type.c_str(), data.c_str(), toOpenId.c_str(), itr->second.c_str());
		}
	}
	ret = logicUserData.SetUserData(uid, userData);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

int CLogicUserInteract::GetRequestFilter(unsigned uid, const string &requestType, Json::Value &users)
{
	int ret;
	Json::Value data;
	CLogicUserData logicUserData;
	ret = logicUserData.GetUserData(uid, data);
	if(ret != 0)
	{
		return ret;
	}
	users = Json::Value(Json::arrayValue);
	if(!Json::IsObject(data, requestType.c_str()))
	{
		return 0;
	}
	Json::Value &request = data[requestType];
//	if(requestType == "requestcrew")
//	{
//		if(Json::IsArray(request, "crew"))
//		{
//			users = request["crew"];
//		}
//	}
	unsigned lastTime = 0;
	Json::GetUInt(request, "lt", lastTime);
	if(!Time::IsToday(lastTime))
	{
		return 0;
	}
	if(!Json::IsArray(request, "users"))
	{
		return 0;
	}
//	if(users.size() == 0)
//	{
		users = request["users"];
//	}
//	else
//	{
//		Json::Value &requestUsers = request["users"];
//		unsigned size = requestUsers.size();
//		for(unsigned i = 0; i < size; i++)
//		{
//			users[users.size()] = requestUsers[i];
//		}
//	}
	return 0;
}

int CLogicUserInteract::FilterRequestUsers(const UidList &users, const Json::Value &filter, Json::Value &filterUsers)
{
	int ret;
	set<string> filterSet;
	unsigned filterSize = filter.size();
	for(unsigned i = 0; i < filterSize; i++)
	{
		string openid;
		if(Json::GetString(filter, i, openid))
		{
			filterSet.insert(openid);
		}
	}
	for(UidList::const_iterator itr = users.begin(); itr != users.end(); itr++)
	{
		DataUserBasic userBasic;
		ret = LogicUserBasic::GetUserSmart(*itr, OpenPlatform::GetType(), userBasic);
		if(ret == 0)
		{
			if(filterSet.find(userBasic.open_id) == filterSet.end())
			{
				filterUsers[filterUsers.size()] = userBasic.open_id;
			}
		}
	}
	return 0;
}

int CLogicUserInteract::RequestItem(unsigned uid, const string &itemid, int requireCount, uint64_t &messageId, unsigned &waitTime)
{
	int ret;
	if(!String::StartWith(itemid, "gift_"))
	{
		error_log("[invalid_gift_id][uid=%u,itemid=%s]", uid, itemid.c_str());
	}
	CLogicInventory logicInventory;
	unsigned currCount = 0;
	ret = logicInventory.GetItem(uid, itemid, currCount);
	if(ret != 0)
	{
		return ret;
	}
	int requestCount = requireCount - currCount;
	if(requestCount <= 0)
	{
		error_log("[have_enough_item][uid=%u,itemid=%s,requireCount=%d,count=%u]",
				uid, itemid.c_str(), requireCount, currCount);
		ERROR_RETURN_MSG(R_ERR_LOGIC, "have_enough_item");
	}
	if(requestCount > REQUEST_ITEM_LIMIT)
	{
		requestCount = REQUEST_ITEM_LIMIT;
	}
	CLogicMessage logicMessage;
	vector<DataMessage> messages;
	ret = logicMessage.GetRequest(uid, "requestitem", TOWARD_SEND, MS_STATUS_ALL, messages);
	if(ret != 0)
	{
		return ret;
	}
	for(vector<DataMessage>::iterator itr = messages.begin(); itr != messages.end(); itr++)
	{
		if(Time::IsToday(itr->time) && itr->time + REQUEST_ITEM_TIMEOUT > Time::GetGlobalTime())
		{
			Json::Value currData;
			if(Json::FromString(currData, itr->content))
			{
				string currItemId;
				if(Json::GetString(currData, "itemid", currItemId))
				{
					if(currItemId == itemid)
					{
						unsigned expireTime = itr->time + REQUEST_ITEM_TIMEOUT;
						if(Time::IsToday(expireTime))
						{
							waitTime = expireTime - Time::GetGlobalTime();
						}
						else
						{
							waitTime = CTime::GetDayBeginTime(expireTime) - Time::GetGlobalTime();
						}
						ERROR_RETURN_MSG(R_ERR_LOGIC, "request_item_time_limit");
					}
				}
			}
		}
	}
	Json::Value requestData;
	requestData["type"] = "requestitem";
	requestData["itemid"] = itemid;
	requestData["rcount"] = requestCount;
	requestData["count"] = 0;
	ret = logicMessage.AddRequest(messageId, uid, MUT_ALL, requestData);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

int CLogicUserInteract::SendHelpReward(unsigned uid, const string &itemid, int count, uint64_t &messageId)
{
	int ret;
	if(!String::StartWith(itemid, "gift_"))
	{
		error_log("[invalid_gift_id][uid=%u,itemid=%s]", uid, itemid.c_str());
	}
	CLogicMessage logicMessage;
	Json::Value requestData;
	requestData["type"] = "helpreward";
	requestData["itemid"] = itemid;
	requestData["tcount"] = count;
	requestData["count"] = 0;
	ret = logicMessage.AddRequest(messageId, uid, MUT_ALL, requestData);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

int CLogicUserInteract::GetFriendInteracts(unsigned uid, map<unsigned, int> &interacts)
{
	int ret;
	Json::Value userData;
	CLogicUserData logicUserData;
	ret = logicUserData.GetUserData(uid, userData);
	if(ret != 0)
	{
		return ret;
	}
	interacts.clear();
	Json::Value &interactsData = userData["interacts"];
	unsigned lastTime = 0;
	Json::GetUInt(interactsData, "lt", lastTime);
	if(!Time::IsToday(lastTime) || !Json::IsObject(interactsData, "users"))
	{
		return 0;
	}
	Json::Value &usersData = interactsData["users"];
	Json::Value::Members members = usersData.getMemberNames();
	for(Json::Value::Members::iterator itr = members.begin(); itr != members.end(); itr++)
	{
		unsigned uid;
		int count;
		if(Convert::StringToUInt(uid, *itr) && Json::GetInt(usersData, itr->c_str(), count))
		{
			interacts[uid] = count;
		}
	}
	return 0;
}

int CLogicUserInteract::AddFriendInteract(unsigned uid, unsigned friendId, const string &type)
{
	int ret;
	Json::Value userData;
	CLogicUserData logicUserData;
	ret = logicUserData.GetUserData(uid, userData);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value &interactsData = userData["interacts"];
	unsigned lastTime = 0;
	Json::GetUInt(interactsData, "lt", lastTime);
	if(!Time::IsToday(lastTime) || !Json::IsObject(interactsData, "users"))
	{
		interactsData["users"] = Json::Value(Json::objectValue);
	}
	interactsData["lt"] = Time::GetGlobalTime();
	Json::Value &usersData = interactsData["users"];
	string sFriendId = Convert::UIntToString(friendId);
	int count = 0;
	if(Json::GetInt(usersData, sFriendId.c_str(), count))
	{
		if(count >= APP_INTERACTS_LIMIT)
		{
			error_log("[interact_limit][uid=%u,fid=%u,type=%s,count=%d]", uid, friendId, type.c_str(), count);
			ERROR_RETURN_MSG(R_ERR_LOGIC, "interact_limit");
		}
	}
	count++;
	usersData[sFriendId] = count;
	ret = logicUserData.SetUserData(uid, userData);
	if(ret != 0)
	{
		return ret;
	}
	ret = ChangeInteractPoint(uid, 1);
	if(ret != 0)
	{
		return ret;
	}
	ret = ChangeInteractStat(uid, "trp", 1);
	if(count == APP_INTERACTS_LIMIT)
	{
		CLogicInventory logicInventory;
		ret = logicInventory.ChangeItem(uid, "gift_3005", 1);
	}
	return 0;
}

int CLogicUserInteract::ChangeInteractPoint(unsigned uid, int count)
{
	CLogicInventory logicInventory;
	return logicInventory.ChangeItem(uid, "rp", count);
}

int CLogicUserInteract::ChangeInteractStat(unsigned uid, const char *name, int delta)
{
	if(!IsMercenary())
	{
		return 0;
	}
	int ret;
	Json::Value userExtraData;
	ret = LogicUser::GetExtraData(uid, userExtraData);
	if(ret != 0)
	{
		return ret;
	}
	if(!Json::IsObject(userExtraData, "istat"))
	{
		userExtraData["istat"] = Json::Value(Json::objectValue);
	}
	Json::Value &istat = userExtraData["istat"];
	int counter = 0;
	Json::GetInt(istat, name, counter);
	istat[name] = counter + delta;
	ret = LogicUser::SetExtraData(uid, userExtraData);
	if(ret != 0)
	{
		error_log("[SetExtraData fail][ret=%d,uid=%u,name=%s,delta=%d]", ret, uid, name, delta);
		return ret;
	}
	return 0;
}
