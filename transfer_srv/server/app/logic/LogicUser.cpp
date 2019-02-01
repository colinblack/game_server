/*
 * LogicUser.cpp
 *
 *  Created on: 2011-5-27
  *      Author: dada
 */

#include "LogicUser.h"
#include "FacebookPlatform.h"
#include "WeiyouxiPlatform.h"

int LogicUser::AddUser(unsigned &uid, PlatformType platform, unsigned inviteUid)
{
	int ret;

	uint64_t nextUid;
	CLogicIdCtrl logicIdCtrl;
	ret = logicIdCtrl.GetNextId(KEY_UID_CTRL, nextUid);
	if(ret != 0)
	{
		return ret;
	}

	DataUser user;
	user.uid = (unsigned)nextUid;
	user.register_platform = platform;
	user.register_time = Time::GetGlobalTime();
	user.invite_uid = inviteUid;
	user.last_login_platform = platform;
	user.last_login_time = Time::GetGlobalTime();
	user.last_active_time = Time::GetGlobalTime();
	user.login_times = 0;
	user.invite_count = 0;
	user.status = US_ACTIVE;
	user.main_base_id = 0;
	user.level = 0;
	user.point = 0;
	user.value = 0;
	user.tutorial_stage = 0;
	user.r1 = 0;
	user.r1_max = 0;
	user.r2 = 0;
	user.r2_max = 0;
	user.r3 = 0;
	user.r3_max = 0;
	user.r4 = 0;
	user.r4_max = 0;
	user.alliance_id = ALLIANCE_ID_NULL;
	user.unread_message = 0;
	user.world = 0;
	CDataUser dbUser;
	ret = dbUser.AddUser(user);
	if(ret != 0)
	{
		fatal_log("[AddUser fail][ret=%d,platform=%d]", ret, platform);
		DB_ERROR_RETURN_MSG("add_user_fail");
	}
	uid = user.uid;

	DataUserExtra userExtra;
	userExtra.uid = uid;
	userExtra.gate_left_times = 0;
	userExtra.gate_extra_times = 0;
	userExtra.stat = "{}";
	userExtra.wf_status = "";
	userExtra.lock = "{}";
	userExtra.technology = "{}";
	userExtra.quest = "{}";
	userExtra.bookmark = "{}";
	userExtra.extra_data = "{}";
	CDataUserExtra dbUserExtra;
	ret = dbUserExtra.AddUser(userExtra);
	if(ret != 0)
	{
		fatal_log("[AddUserExtra fail][ret=%d,platform=%d]", ret, platform);
		DB_ERROR_RETURN_MSG("add_user_extra_fail");
	}

	CLogicPay logicPay;
	ret = logicPay.AddUser(uid, NEW_USER_CASH);
	if(ret != 0)
	{
		return ret;
	}

	unsigned baseid;
	ret = LogicBase::AddMainBase(uid, baseid);
	if(ret != 0)
	{
		fatal_log("[AddMainBase fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("add_base_fail");
	}

	ret = dbUser.SetMainBaseId(uid, baseid);
	if( ret != 0 )
	{
		fatal_log("[SetMainBaseId fail][ret=%d,uid=%u,baseid=%u]", ret, uid, baseid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}

	//add invite count
	if(IsValidUid(inviteUid))
	{
		ret = dbUser.AddInviteCount(inviteUid, 1);
		if(ret != 0)
		{
			error_log("[AddInviteCount fail][ret=%,uid=%u]", ret, inviteUid);
		}
	}

	return 0;
}

int LogicUser::RemoveUser(unsigned uid)
{
	//移除平台信息
	int ret;
	ret = LogicUserBasic::RemoveUser(uid);

	//设置状态为Remove
	CDataUser dbUser;
	ret = dbUser.SetStatus(uid, US_REMOVE);
	if(ret != 0)
	{
		error_log("[SetStatus fail][ret=%,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}

	//TODO: remove neighbour

	return 0;
}

int LogicUser::SetUser(DataUser &user)
{
	int ret;
	UpdateLevel(user);
	CDataUser dbUser;
	ret = dbUser.SetUser(user);
	if(ret != 0)
	{
		error_log("[SetUser fail][ret=%d,uid=%u]", ret, user.uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	return 0;
}

int LogicUser::GetUser(unsigned uid, DataUser &user)
{
	int ret;
	CDataUser dbUser;
	ret = dbUser.GetUser(uid, user);
	if(ret != 0)
	{
		error_log("[GetUser fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	return 0;
}

int LogicUser::SetUserExtra(const DataUserExtra &userExtra)
{
	int ret;
	CDataUserExtra dbUserExtra;
	ret = dbUserExtra.SetUser(userExtra);
	if(ret != 0)
	{
		error_log("[SetUserExtra fail][ret=%d,uid=%u]", ret, userExtra.uid);
		DB_ERROR_RETURN_MSG("set_user_extra_fail");
	}
	return 0;
}

int LogicUser::GetUserExtra(unsigned uid, DataUserExtra &userExtra)
{
	int ret;
	CDataUserExtra dbUserExtra;
	ret = dbUserExtra.GetUser(uid, userExtra);
	if(ret != 0)
	{
		error_log("[GetUserExtra fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_extra_fail");
	}
	return 0;
}

int LogicUser::UpdateActiveTime(unsigned uid, unsigned activeTime)
{
	int ret;
	if(activeTime == 0)
	{
		activeTime = Time::GetGlobalTime();
	}
	CDataUser dbUser;
	ret = dbUser.SetActiveTime(uid, activeTime);
	if(ret != 0)
	{
		error_log("[SetActiveTime fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	return 0;
}

int LogicUser::GetMainBaseId(unsigned uid, unsigned &baseid)
{
	int ret;
	CDataUser dbUser;
	ret = dbUser.GetMainBaseId(uid, baseid);
	if(ret != 0)
	{
		error_log("[GetMainBaseId fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	return 0;
}

int LogicUser::GetActiveTime(unsigned uid, unsigned activeTime)
{
	CDataUser userDB;
	int ret = userDB.GetActiveTime(uid, activeTime);
	if (ret != 0)
	{
		error_log("[GetActiveTime fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	return 0;
}

int LogicUser::GetExtraData(unsigned uid, Json::Value &extraData)
{
	CDataUserExtra dbUserExtra;
	string sExtraData;
	int ret = dbUserExtra.GetExtraData(uid, sExtraData);
	if (ret != 0)
	{
		error_log("[GetExtraData fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_extra_fail");
	}
	if(!Json::FromString(extraData, sExtraData))
	{
		if(!sExtraData.empty())
		{
			error_log("[user_extra_data_parse_fail][uid=%u,data=%s]", uid, sExtraData.c_str());
		}
		extraData = Json::Value(Json::objectValue);
	}
	return 0;
}

int LogicUser::SetExtraData(unsigned uid, const Json::Value &extraData)
{
	string sExtraData = Json::ToString(extraData);
	if(sExtraData.size() > 500)
	{
		fatal_log("[ASSERT(user_extra_data_overflow)][uid=%u,data=%s,size=%d]",
				uid, sExtraData.c_str(), (int)sExtraData.size());
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "set_user_extra_fail");
	}
	CDataUserExtra dbUserExtra;
	int ret = dbUserExtra.SetExtraData(uid, sExtraData);
	if (ret != 0)
	{
		error_log("[SetExtraData fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_extra_fail");
	}
	return 0;
}

int LogicUser::GetStat(unsigned uid, Json::Value &stat)
{
	CDataUserExtra dbUserExtra;
	string sStat;
	int ret = dbUserExtra.GetStat(uid, sStat);
	if (ret != 0)
	{
		error_log("[GetStat fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_extra_fail");
	}
	if(!Json::FromString(stat, sStat))
	{
		if(!sStat.empty())
		{
			error_log("[user_stat_parse_fail][uid=%u,data=%s]", uid, sStat.c_str());
		}
		stat = Json::Value(Json::objectValue);
	}
	return 0;
}

int LogicUser::SetStat(unsigned uid, const Json::Value &stat)
{
	string sStat = Json::ToString(stat);
	if(sStat.size() > 500)
	{
		fatal_log("[ASSERT(user_extra_data_overflow)][uid=%u,data=%s,size=%d]",
				uid, sStat.c_str(), (int)sStat.size());
		ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "set_user_extra_fail");
	}
	CDataUserExtra dbUserExtra;
	int ret = dbUserExtra.SetStat(uid, sStat);
	if (ret != 0)
	{
		error_log("[SetExtraData fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_extra_fail");
	}
	return 0;
}

int LogicUser::SetGateTimes(const DataUserExtra &userExtra)
{
	CDataUserExtra dbUserExtra;
	int ret = dbUserExtra.SetGateTimes(userExtra);
	if(ret != 0)
	{
		error_log("[GetGateTimes fail][ret=%d,uid=%u]", ret, userExtra.uid);
		DB_ERROR_RETURN_MSG("set_user_extra_fail");
	}
	return 0;
}

int LogicUser::GetGateTimes(unsigned uid, DataUserExtra &userExtra)
{
	CDataUserExtra dbUserExtra;
	int ret = dbUserExtra.GetGateTimes(uid, userExtra);
	if(ret != 0)
	{
		error_log("[GetGateTimes fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_extra_fail");
	}
	return 0;
}

int LogicUser::SetWorld(unsigned uid, int world)
{
	CDataUser dbUser;
	int ret = dbUser.SetWorld(uid, world);
	if(ret != 0)
	{
		error_log("[SetWorld fail][ret=%d,uid=%u,world=%d]", ret, uid, world);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	LogicWorld::RefreshUserWorld(uid, world);
	return 0;
}

int LogicUser::GetWorld(unsigned uid, int &world)
{
	CDataUser dbUser;
	int ret = dbUser.GetWorld(uid, world);
	if(ret != 0)
	{
		error_log("[GetWorld fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	return 0;
}

int LogicUser::SetAllianceId(unsigned uid, unsigned allianceId)
{
	CDataUser dbUser;
	int ret = dbUser.SetAllianceId(uid, allianceId);
	if(ret != 0)
	{
		error_log("[SetAllianceId fail][ret=%d,uid=%u,allianceid=%u]", ret, uid, allianceId);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	if(IsAllianceId(allianceId))
	{
		LogicWorld::RefreshUserWorld(uid, 0);
	}
	return 0;
}

int LogicUser::GetAllianceId(unsigned uid, unsigned &allianceId)
{
	CDataUser dbUser;
	int ret = dbUser.GetAllianceId(uid, allianceId);
	if(ret != 0)
	{
		error_log("[GetAllianceId fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	return 0;
}

int LogicUser::SetBookmark(unsigned uid, const Json::Value &bookmark)
{
	string sBookmark = Json::ToString(bookmark);
	if(sBookmark.size() >= 500)
	{
		error_log("[bookmark_overflow][uid=%u,bookmark=%u]", uid, (unsigned)bookmark.size());
		DB_ERROR_RETURN_MSG("too_many_bookmark");
	}
	CDataUserExtra dbUserExtra;
	int ret = dbUserExtra.SetBookmark(uid, sBookmark);
	if(ret != 0)
	{
		error_log("[SetBookmark fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_extra_fail");
	}
	return 0;
}

int LogicUser::ChangeResource(unsigned uid, int r1, int r2, int r3, int r4)
{
	int ret;
	DataUser user;
	ret = GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}
	bool change = false;

#define CHANGE_RESOURCE(res)	\
	if(res != 0)	\
	{	\
		if(res < 0 && user.res < (unsigned)(-res))	\
		{	\
			error_log("[not_enough_resource][uid=%u,resource=%u,change=%d]", uid, user.res, res);	\
			ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "not_enough_resource");	\
		}	\
		else	\
		{	\
			user.res += res;	\
		}	\
		change = true;	\
	}	\

	CHANGE_RESOURCE(r1);
	CHANGE_RESOURCE(r2);
	CHANGE_RESOURCE(r3);
	CHANGE_RESOURCE(r4);
	if(change)
	{
		ret = SetUser(user);
	}
	return ret;
}

int LogicUser::GetResourcesJson(const DataUser &user, Json::Value &data)
{
	data["r1"] = user.r1;
	data["r1max"] = user.r1_max;
	data["r2"] = user.r2;
	data["r2max"] = user.r2_max;
	data["r3"] = user.r3;
	data["r3max"] = user.r3_max;
	data["r4"] = user.r4;
	data["r4max"] = user.r4_max;
	return 0;
}

int LogicUser::UpdateLevel(DataUser &user)
{
	static uint64_t s_levels[] = {
			0, 900, 3500, 5000, 7500, 10500,
			14700, 20580, 28812, 40337, 56472,
			79060, 110684, 154958, 216941, 303717,
			425204, 595286, 833401, 1166761, 1633465,
			2286851, 3201591, 4482228, 6275119, 8785167,
			12299234, 17218927, 24106498, 33749097, 47248736,
			66148230, 92607522, 129650530, 181510743, 254115040,
			355761056, 498065478, 697291669, 976208337, 1366691671,
			1913368339ULL, 2678715675ULL, 3750201945ULL, 5250282723ULL, 7350395812ULL,
			10290554137ULL, 14406775792ULL, 20169486109ULL, 28237280553ULL, 39532192774ULL,
			55345069884ULL, 77483097838ULL, 108476336973ULL, 151866871762ULL, 212613620467ULL,
			297659068653ULL
	};
	int oldLevel = user.level;
	uint64_t point = user.point + user.value;
	for(unsigned i = 0; i < COUNT_OF(s_levels); i++)
	{
		if(point < s_levels[i])
		{
			user.level = i;

			//新浪微游戏成就
			if(OpenPlatform::GetType() == PT_WEIYOUXI)
			{
				if(user.level > oldLevel && user.level > 6)
				{
					string openid;
					string openkey;
					int ret = LogicSso::GetOpenKey(user.uid, openid, openkey);
					if(ret == 0)
					{
//						if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetLeaderboard(openid, openkey, WYX_LEADERBOARD_LEVEL_ID, user.level) != 0)
//						{
//							error_log("[set_leaderboard_fail][uid=%u,lid=%u,value=%u,error=%s]",
//									user.uid, WYX_LEADERBOARD_LEVEL_ID, user.level, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
//						}
						if(user.level / 10 > oldLevel / 10 && user.level >= 10)
						{
							unsigned aid = WYX_ACHIEVEMENT_LEVEL_BASE + user.level / 10;
							if(((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->SetAchievement(openid, openkey, aid) != 0)
							{
								error_log("[set_achievement_fail][uid=%u,aid=%u,error=%s]",
										user.uid, aid, OpenPlatform::GetPlatform()->GetErrorMessage().c_str());
							}
						}
					}
				}
			}

			//被邀请都升到15级25级奖励
			if (Config::GetValue("active") == "true")
			{
				if (user.level > oldLevel && OpenPlatform::GetType() != PT_FACEBOOK && OpenPlatform::GetType() != PT_MOBAGE)
				{
					if ((oldLevel < 20 && user.level >= 20) || (oldLevel < 30 && user.level >= 30))
					{
						DataUser inviteUser;
						Json::Value stat;
						if (IsValidUid(user.invite_uid)
								&& (GetExtraData(user.invite_uid, stat) == 0))
						{
							if (!stat.isMember("rws"))
							{
								stat["rws"].resize(3);
								for (unsigned i = 0; i < 3; i++)
								{
									stat["rws"][i] = 0;
								}
							}
							unsigned index = 1;
							if (user.level >= 30)
								index = 2;
							int limit = stat["rws"][index].asInt();
							if (limit < 300)
							{
								CLogicPay logicPay;
								int addCash = (index == 2 ? 20 : 10);
								if (logicPay.ChangeCash(user.invite_uid, "ACTINVLV", addCash) == 0)
								{
									info_log("[invite upgrade][uid=%u,inviteUid=%u,addcash=%d,lvl=%d,limit=%d]",
											user.uid,user.invite_uid,addCash,user.level,limit);
									DataUserBasic beInvited;
									LogicUserBasic::GetUserSmart(user.uid, OpenPlatform::GetType(), beInvited);
									CLogicMessage logicMsg;
									logicMsg.AddInviteUpgradeRewardMsg(user.uid, beInvited.name, user.invite_uid, (index == 2 ? 30 : 20), addCash);

									limit += addCash;
									stat["rws"][index] = limit;
									SetExtraData(inviteUser.invite_uid, stat);
								}
							}
						}
					}
				}
			}

			if (OpenPlatform::GetType() == PT_MOBAGE)
			{
				if (IsValidUid(user.invite_uid) && oldLevel < 15 && user.level >= 15)
				{
					CLogicPay logicPay;
					int addCash = 50;
					if (logicPay.ChangeCash(user.invite_uid, "ACTINVLV", addCash) == 0)
					{
						info_log("[invite upgrade][uid=%u,inviteUid=%u,addcash=%d,lvl=%d]",
								user.uid,user.invite_uid,addCash,user.level);
						DataUserBasic beInvited;
						LogicUserBasic::GetUserSmart(user.uid, OpenPlatform::GetType(), beInvited);
						CLogicMessage logicMsg;
						logicMsg.AddInviteUpgradeRewardMsg(user.uid, beInvited.name, user.invite_uid, 15, addCash);
					}
				}
			}

			return 0;
		}
	}
	user.level = COUNT_OF(s_levels);
	return 0;
}

static int WeiyouxiActive(unsigned uid, const string &openid, const string &openkey)
{
	int ret = 0;
	Json::Value stat;
	ret = LogicUser::GetStat(uid, stat);
	if(ret != 0)
	{
		return ret;
	}
	Json::Value &sdata = stat["sdata"];
	if(!sdata.isObject())
	{
		sdata = Json::Value(Json::objectValue);
	}
	unsigned lastUpdateTime = 0;
	Json::GetUInt(sdata, "alut", lastUpdateTime);
	if(lastUpdateTime + 3600 > Time::GetGlobalTime())
	{
		return 0;
	}
	int fan = 0;
//	int scored = 0;
	Json::GetInt(sdata, "fan", fan);
//	Json::GetInt(sdata, "scored", scored);
	if(fan != 0)// && scored > 0)
	{
		return 0;
	}

	CLogicPay logicPay;
	CLogicMessage logicMessage;
	if(fan == 0)
	{
		ret = ((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->IsFan(openid, openkey, fan);
		if(ret == 0 && fan != 0)
		{
			ret = logicPay.ChangeCash(uid, "ACTWYXFAN", 50);
			if(ret == 0)
			{
				DATA_INFO_LOG("purchase", "uid=%u&item=WYXFANRW&count=1&cash=-50", uid);
				ret = logicMessage.AddSysMessage(uid, "{\"id\":\"wyx_fan_reward\",\"cash\":50}");
			}
		}
	}
//	if(scored <= 0)
//	{
//		ret = ((CWeiyouxiPlatform *)OpenPlatform::GetPlatform())->Scored(openid, openkey, scored);
//		if(ret == 0 && scored >= 0)
//		{
//			if(scored == 5)
//			{
//				ret = logicPay.ChangeCash(uid, "ACTWYXSCR", 50);
//				if(ret == 0)
//				{
//					DATA_INFO_LOG("purchase", "uid=%u&item=WYXSCOREDRW&count=1&cash=-50", uid);
//					ret = logicMessage.AddSysMessage(uid, "{\"id\":\"wyx_scored_reward\",\"cash\":50}");
//				}
//			}
//		}
//	}

	sdata["lut"] = Time::GetGlobalTime();
	sdata["fan"] = fan;
//	sdata["scored"] = scored;
	ret = LogicUser::SetStat(uid, stat);
	return ret;
}

static int FacebookActive(unsigned uid, const string &openid, const string &openkey)
{
	int ret;
	Json::Value stat;
	ret = LogicUser::GetStat(uid, stat);
	if(ret != 0)
	{
		return ret;
	}
	if (stat.isMember("lk") && stat["lk"].asInt() != 0)
		return 0;

	CFacebookPlatform *platform = dynamic_cast<CFacebookPlatform *>(OpenPlatform::GetPlatform());
	vector<string> appIds;
	ret = platform->GetLikes(appIds, openid, openkey);
	if (ret != 0)
		return ret;

	string appid = OpenPlatform::GetPlatform()->GetAppId();

	bool bExit = false;
	for(size_t i = 0; i < appIds.size(); i++)
	{
		if (appIds[i] == appid)
		{
			bExit = true;
			break;
		}
	}

	if (!bExit)
		return 0;

	CLogicPay logicPay;
	ret = logicPay.ChangeCash(uid, "ACTFBLIKE", 30);
	if (ret != 0)
		return ret;

	info_log("[like reward][uid=%u,openid=%s]",uid,openid.c_str());

	Json::FastWriter writer;

	Json::Value msgJson;
	msgJson["id"] = "like";
	msgJson["cash"] = 30;
	string content = writer.write(msgJson);
	CLogicMessage logicMsg;
	logicMsg.AddSysMessage(uid, content);

	stat["lk"] = 1;
	ret = LogicUser::SetStat(uid, stat);
	if(ret != 0)
	{
		error_log("[SetStat fail][ret=%,uid=%u]", ret, uid);
		return -1;
	}

	return 0;
}

static int AfterLogin(unsigned uid, const string &openid, const string &openkey)
{
	if(String::EqualNoCase(Config::GetValue("active"), "true"))
	{
		switch(OpenPlatform::GetType())
		{
		case PT_FACEBOOK:
			return FacebookActive(uid, openid, openkey);
		case PT_WEIYOUXI:
			return WeiyouxiActive(uid, openid, openkey);
		default:
			return 0;
		}
	}
	return 0;
}

int LogicUser::OnLogin(unsigned uid, PlatformType platform, const string &openid, const string &openkey)
{
	int ret;
	DataUser user;
	ret = GetUser(uid, user);
	if(ret != 0)
	{
		return ret;
	}
	LogicWorld::RefreshUserWorld(uid, IsAllianceId(user.alliance_id) ? 0 : user.world);
	if(!Time::IsToday(user.last_login_time))
	{
		DataUserExtra userExtra;
		ret = GetGateTimes(uid, userExtra);
		if(ret != 0)
		{
			return ret;
		}
		if(userExtra.gate_left_times != GATE_TIMES_DAILY)
		{
			userExtra.gate_left_times = GATE_TIMES_DAILY;
			ret = SetGateTimes(userExtra);
			if(ret != 0)
			{
				return ret;
			}
		}
	}
	user.last_login_platform = platform;
	user.last_login_time = Time::GetGlobalTime();
	user.login_times++;
	ret = SetUser(user);
	if(ret != 0)
	{
		return ret;
	}
	ret = AfterLogin(uid, openid, openkey);
	if(ret != 0)
	{
		return ret;
	}
	return 0;
}

int LogicUser::OnInvite(unsigned uid, const string &name, PlatformType platform, unsigned inviteUid)
{
	int ret;
	Json::Value stat;
	CLogicPay logicPay;
	CLogicMessage logicMsg;

	if (!IsValidUid(inviteUid))
	{
		return 0;
	}
	if(platform == PT_MOBAGE)
	{
		ret = logicPay.ChangeCash(inviteUid, "ACTINVU", 10);
		if(ret != 0)
		{
			return ret;
		}
		info_log("[invite reward][uid=%u,pt=%d,inviteUid=%u,cash=10]", uid, (int)platform, inviteUid);
		logicMsg.AddInviteRewardMsg(uid, name, inviteUid, 10);
		return 0;
	}
	if (Config::GetValue("active") != "true")
	{
		return 0;
	}

	if (platform == PT_FACEBOOK)
	{
		int ret = logicPay.ChangeCash(inviteUid, "ACTFBINV", 20);
		if(ret != 0)
		{
			return ret;
		}
		info_log("[invite reward][uid=%u,inviteUid=%u,addcash=20]", uid, inviteUid);
		ret = logicMsg.AddInviteRewardMsg(uid, name, inviteUid, 20);
		if(ret != 0)
		{
			return ret;
		}
	}
	else
	{
		if(!GetExtraData(inviteUid, stat))
		{
			return ret;
		}
		if (!stat.isMember("rws"))
		{
			stat["rws"].resize(3);
			for (unsigned i = 0; i < 3; i++)
			{
				stat["rws"][i] = 0;
			}
		}
		int limit = stat["rws"][0u].asInt();
		if (limit >= 300)
		{
			return 0;
		}
		unsigned reward = 5;
		ret = logicPay.ChangeCash(inviteUid, "ACTINVU", reward);
		if(ret != 0)
		{
			return ret;
		}
		info_log("[invite reward][uid=%u,pt=%d,inviteUid=%u,cash=%u,limit=%d]", uid, (int)platform, inviteUid, reward, limit);
		logicMsg.AddInviteRewardMsg(uid, name, inviteUid, 5);
		limit += 5;
		stat["rws"][0u] = limit;
		ret = SetExtraData(inviteUid, stat);
		if(ret != 0)
		{
			return ret;
		}
	}
	return 0;
}

int LogicUser::GetUserInfo(unsigned uid, Json::Value &data)
{
	DataUser user;
	int ret = GetUser(uid, user);
	if (ret != 0)
		return ret;
	unsigned position = 0;
	ret = LogicBase::GetPosition(user.main_base_id, position);
	if (ret != 0)
		return ret;

	data["level"] = user.level;
	data["world"] = user.world;
	int X = (position >> 12) & 0xfff;
	int Y = position & 0xfff;
	data["x"] = X;
	data["y"] = Y;

	return 0;
}
