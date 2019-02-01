/*
 * LogicUserBasicBasic.cpp
 *
 *  Created on: 2011-7-11
 *      Author: dada
 */

#include "LogicUserBasic.h"
#include "WeiyouxiPlatform.h"

static int SetUserBasic(unsigned uid, bool newUser, PlatformType platform, OPUserInfo &userInfo, const OPFriendList &friendList)
{
	int ret;
	DataUserBasic userOld;
	CDataUserBasic dbUser;
	bool add = true;
	if(!newUser)
	{
		ret = dbUser.GetUser(uid, platform, userOld);
		if(ret != 0)
		{
			if(ret != R_ERR_NO_DATA)
			{
				error_log("[GetUser fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
				DB_ERROR_RETURN_MSG("get_user_basic_fail");
			}
		}
		else
		{
			add = false;
		}
	}

	DataUserBasic user;
	user.uid = uid;
	user.platform = platform;
	if(add)
	{
		user.is_register_platform = newUser ? True : False;
	}
	else
	{
		user.is_register_platform = userOld.is_register_platform;
	}
	user.open_id = userInfo.OpenId;
	user.name = userInfo.Name;
	if(user.name.size() > 50)
	{
		user.name = user.name.substr(0, 50);
		String::Utf8Regularize(user.name);
	}
	user.gender = userInfo.Gender;
	user.figure_url = userInfo.FigureUrl;
	user.nation = userInfo.Nation;
	user.province = userInfo.Province;
	user.city = userInfo.City;
	if(IsTencentPlatform(platform))
	{
		if(userInfo.ExtraIntInfo["bIsYearVip"])
		{
			user.vip_type = VT_QQ_YELLOW_YEAR;
		}
		else if(userInfo.ExtraIntInfo["bIsVip"])
		{
			user.vip_type = VT_QQ_YELLOW;
		}
		else
		{
			user.vip_type = VT_NORMAL;
		}
		user.vip_level = userInfo.ExtraIntInfo["nVipLevel"];
	}
	else if(platform == PT_WEIYOUXI)
	{
		if(userInfo.ExtraIntInfo["type"] != 0)
		{
			user.vip_type = VT_SINAWB;
			user.vip_level = userInfo.ExtraIntInfo["type"];
		}
		else
		{
			user.vip_type = VT_NORMAL;
			user.vip_level = 0;
		}
	}
	else
	{
		user.vip_type = VT_NORMAL;
		user.vip_level = 0;
	}
	if(platform == PT_FACEBOOK)
	{
		Json::Value extraData;
		Json::FromString(extraData, user.extra_data);
		extraData["email"] = userInfo.ExtraStrInfo["email"];
		user.extra_data = Json::ToString(extraData);
	}

	//当存在旧数据，且新数据为空时，信任旧数据
	if(!add)
	{
		if(user.name.empty())
		{
			user.name = userOld.name;
		}
		if(user.gender == GD_UNKNOW)
		{
			user.gender = userOld.gender;
		}
		if(user.figure_url.empty())
		{
			user.figure_url = userOld.figure_url;
		}
		if(user.nation.empty())
		{
			user.nation = userOld.nation;
		}
		if(user.province.empty())
		{
			user.province = userOld.province;
		}
		if(user.city.empty())
		{
			user.city = userOld.city;
		}
	}

	if(add)
	{
		ret = dbUser.AddUser(user);
		if(ret != 0)
		{
			error_log("[AddUser fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
			DB_ERROR_RETURN_MSG("add_user_basic_fail");
		}
		ret = LogicFriend::AddFriends(uid, platform, user.open_id, friendList);
		if(ret != 0)
		{
			return ret;
		}
		CDataUserMapping dbUserMapping;
		ret = dbUserMapping.AddMapping(user.open_id, platform, uid);
		if(ret != 0)
		{
			error_log("[AddMapping fail][ret=%d,uid=%u,openid=%s,platform=%d]", ret, uid, user.open_id.c_str(), platform);
			DB_ERROR_RETURN_MSG("add_user_mapping_fail");
		}
	}
	else
	{
		if(user.open_id != userOld.open_id ||
			user.name != userOld.name ||
			user.gender != userOld.gender ||
			user.figure_url != userOld.figure_url ||
			user.nation != userOld.nation ||
			user.province != userOld.province ||
			user.city != userOld.city ||
			user.vip_type != userOld.vip_type ||
			user.vip_level != userOld.vip_level ||
			user.extra_data != userOld.extra_data)
		{
			ret = dbUser.SetUser(user);
			if(ret != 0)
			{
				error_log("[SetUser fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
				DB_ERROR_RETURN_MSG("set_user_basic_fail");
			}
		}
		if(!friendList.empty())
		{
			ret = LogicFriend::UpdateFriends(uid, platform, user.open_id, friendList);
		}
	}

	return 0;
}

int LogicUserBasic::LoginPlatformUser(PlatformType platform, OPUserInfo &userInfo, const OPFriendList &friendList,
		const string &openkey, const string &inviteId, unsigned &uid)
{
	int ret;
	bool isNewUser = false;
	ret = GetUid(uid, platform, userInfo.OpenId);
	if(ret == 0)
	{
		ret = SetUserBasic(uid, isNewUser, platform, userInfo, friendList);
		if(ret != 0)
		{
			return ret;
		}
		return 0;
	}
	if(ret != R_ERR_NO_DATA)
	{
		return ret;
	}
	isNewUser = true;
	unsigned inviteUid = 0;
	if(!inviteId.empty())
	{
		ret = GetUid(inviteUid, platform, inviteId);
		if(ret != 0)
		{
			error_log("[invite id invaild][platform=%d,inviteid=%s]", platform, inviteId.c_str());
		}
	}
	ret = LogicUser::AddUser(uid, platform, inviteUid);
	if(ret != 0)
	{
		fatal_log("[AddUser fail][ret=%d,platform=%d,openid=%s]", ret, platform, userInfo.OpenId.c_str());
		return ret;
	}
	ret = SetUserBasic(uid, isNewUser, platform, userInfo, friendList);
	if(ret != 0)
	{
		fatal_log("[add user fail][error=SetUserBasic,ret=%d,uid=%u,platform=%d,openid=%s]",
				ret, uid, platform, userInfo.OpenId.c_str());
		int result = LogicUser::RemoveUser(uid);
		if(result != 0)
		{
			fatal_log("[remove user fail][ret=%d,uid=%u,platform=%d,openid=%s]",
				ret, uid, platform, userInfo.OpenId.c_str());
		}
		return ret;
	}

	if(IsMercenary())
	{
		CLogicPlatformUser logicPlatformUser;
		logicPlatformUser.OnRegisterUser(userInfo.OpenId, platform, uid);
	}

	LogicUser::OnInvite(uid, userInfo.Name, platform, inviteUid);

	if(platform == PT_WEIYOUXI)
	{
		((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->IgnoreInvite(userInfo.OpenId, openkey);
	}
	DATA_INFO_LOG("new_user", "uid=%u&platform=%d&openid=%s&invite_uid=%u",
			uid, platform, userInfo.OpenId.c_str(), inviteUid);
	return 0;
}

int LogicUserBasic::GetUid(unsigned &uid, PlatformType platform, const string &openid, bool autoAlt)
{
	int ret;
	CDataUserMapping dbUserMapping;
	ret = dbUserMapping.GetMapping(openid, platform, uid);
	if(ret == 0)
	{
		return 0;
	}
	if(ret != R_ERR_NO_DATA)
	{
		error_log("[GetMapping fail][ret=%d,openid=%s,platform=%d]", ret, openid.c_str(), platform);
		DB_ERROR_RETURN_MSG("get_user_mapping_fail");
	}
	if(autoAlt && IsTencentPlatform(platform))
	{
		PlatformType altPlatform[] = {PT_PENGYOU, PT_QZONE, PT_TXWEIBO};
		for(unsigned i = 0; i < COUNT_OF(altPlatform); i++)
		{
			if(altPlatform[i] != platform)
			{
				ret = dbUserMapping.GetMapping(openid, altPlatform[i], uid);
				if(ret == 0)
				{
					return 0;
				}
				else if(ret != R_ERR_NO_DATA)
				{
					error_log("[GetMapping fail][ret=%d,openid=%s,platform=%d]", ret, openid.c_str(), altPlatform[i]);
					DB_ERROR_RETURN_MSG("get_user_mapping_fail");
				}
			}
		}
	}
	return ret;
}

int LogicUserBasic::GetUser(unsigned uid, PlatformType platform, DataUserBasic &user)
{
	int ret;
	CDataUserBasic dbUserBasic;
	ret = dbUserBasic.GetUser(uid, platform, user);
	if(ret != 0)
	{
		error_log("[GetUserLimit fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
		DB_ERROR_RETURN_MSG("get_uesr_basic_fail");
	}
	return 0;
}

int LogicUserBasic::GetUserSmart(unsigned uid, PlatformType platform, DataUserBasic &user)
{
	int ret;
	CDataUserBasic dbUserBasic;
	if(IsTencentPlatform(platform))
	{
		ret = dbUserBasic.GetUser(uid, platform, user);
		if(ret == 0)
		{
			return 0;
		}
		if(ret != R_ERR_NO_DATA)
		{
			error_log("[GetUserLimit fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
			DB_ERROR_RETURN_MSG("get_uesr_basic_fail");
		}
	}
	ret = dbUserBasic.GetUserRegister(uid, user);
	if(ret != 0)
	{
		error_log("[GetUserRegisterLimit fail][ret=%d,uid=%u,platform=%d]", ret, uid, platform);
		DB_ERROR_RETURN_MSG("get_uesr_basic_fail");
	}
	return 0;
}

int LogicUserBasic::RemoveUser(unsigned uid)
{
	//只删除Mapping，不删除UserBasic，移除朋友
	int ret;
	CDataUserMapping dbUserMapping;
	vector<DataUserBasic> userBasics;
	CDataUserBasic dbUserBasic;
	ret = dbUserBasic.GetUserAll(uid, userBasics);
	if(ret != 0)
	{
		error_log("[GetUserAll fail][ret=%,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_uesr_basic_fail");
	}
	for(vector<DataUserBasic>::iterator itr = userBasics.begin(); itr != userBasics.end(); itr++)
	{
		ret = dbUserMapping.RemoveMapping(itr->open_id, itr->platform);
		if(ret != 0)
		{
			error_log("[RemoveMapping fail][ret=%,uid=%u,openid=%s,platform=%d]",
					ret, uid, itr->open_id.c_str(), itr->platform);
		}
		//TODO: remove friends
	}
	return 0;
}


