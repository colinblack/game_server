#include "LogicUser.h"

map<unsigned, ILock*> CLogicUser::m_lockmap;

int CLogicUser::AddUser(unsigned uid, PlatformType platform, unsigned inviteUid)
{
	const Json::Value *pInitJson = 0;
	int ret = CLogicArchive::GetInitArchive(pInitJson);
	if (ret != 0)
		return ret;

	DataUser user;
	user.uid = uid;
	if(inviteUid == 1)
		user.kingdom = Math::GetRandomInt(3) + 1;
	else
		user.kingdom = 0;
	user.register_platform = platform;
	user.register_time = Time::GetGlobalTime();
	user.invite_uid = inviteUid;
	user.last_login_platform = platform;
	user.last_login_time = Time::GetGlobalTime();

	CLogicZhouNianQing logicZhouNianQing;
	ret = logicZhouNianQing.QianDao(uid, user.last_login_time);
	if (ret)
		return ret;

	user.last_active_time = Time::GetGlobalTime();
	user.login_times = 1;
	user.login_days = 1;
	user.invite_count = 0;
	user.today_invite_count = 0;
	user.status = Job_None;
	user.type = 0;
	user.level = 0;
	user.point = 0;
	user.tutorial_stage = 0;
	user.r1 = NEW_USER_R1;
	user.r1_max = NEW_USER_R1_MAX;
	user.r2 = NEW_USER_R2;
	user.r2_max = NEW_USER_R2_MAX;
	user.r3 = NEW_USER_R3;
	user.r3_max = NEW_USER_R3_MAX;
	user.r4 = NEW_USER_R4;
	user.r4_max = NEW_USER_R4_MAX;
	user.r5 = NEW_USER_R5;
	user.r5_max = NEW_USER_R5_MAX;
	user.last_save_time = Time::GetGlobalTime();
	user.tribute_time = 0;	//封号到到期时间
	user.protected_time = Time::GetGlobalTime() + NEW_USER_PROTECT;
	user.gcbase = NEW_DAILY_GCBASE;
	user.newgcbase = DAILY_NEW_GCBASE;
	user.gcbuy = 0;
	user.last_save_uid = user.uid;
	user.last_breath_time = 0;
	user.bit_info = 0;
	user.alliance_id = ALLIANCE_ID_NULL;
	user.damage = 0;
	user.prosper = 0;
	user.accCharge = 0;
	user.ext = 0;
	user.lastseq = 0;
	user.battle_spirits = 0;
	user.viplevel = 0;
	user.mainpos = 0;
	user.cdn = 0;
	user.refresh = 0;
	user.memory = 0;

	Json::FastWriter writer;
	if (pInitJson->isMember("trainQ"))
	{
		user.trainQ = writer.write((*pInitJson)["trainQ"]);
	}
	if (pInitJson->isMember("skillQ"))
	{
		user.skillQ = writer.write((*pInitJson)["skillQ"]);
	}
	if (pInitJson->isMember("barrackQ"))
	{
		user.barrackQ = writer.write((*pInitJson)["barrackQ"]);
	}
	if (pInitJson->isMember("buildQ"))
	{
		user.buildQ = writer.write((*pInitJson)["buildQ"]);
	}
	if (pInitJson->isMember("soldier"))
	{
		user.soldier = writer.write((*pInitJson)["soldier"]);
	}
	if (pInitJson->isMember("soldierlevel"))
	{
		user.soldierlevel = writer.write((*pInitJson)["soldierlevel"]);
	}
	CDataUser dbUser;
	ret = dbUser.AddUser(user);
	if (ret != 0)
	{
		fatal_log("[AddUser fail][ret=%d,platform=%d]", ret, platform);
		DB_ERROR_RETURN_MSG("db_add_user_fail");
	}

	CLogicPay logicPay;
	ret = logicPay.InitailizePay(uid);
	if (ret != 0)
		return ret;

	CLogicBuilding logicBuilding;
	ret = logicBuilding.InitializeBuilding(uid);
	if (ret != 0)
		return ret;

	CLogicHero logicHero;
	ret = logicHero.InitializeHero(uid);
	if (ret != 0)
		return ret;

	CLogicEquipment logicEquip;
	ret = logicEquip.InitializeEquipment(uid);
	if (ret != 0)
		return ret;

	CLogicUserData logicUserData;
	ret = logicUserData.InitializeUserData(uid);
	if (ret != 0)
		return ret;

	CLogicTribute logicTribute;
	ret = logicTribute.InitializeTribute(uid);
	if (ret != 0)
		return ret;

	DataRank rank;
	rank.uid = uid;
	rank.heroid = "{}";
	CDataRank dataRank;
	dataRank.AddRank(rank);

	return 0;
}

int CLogicUser::ProcessInvite(unsigned uid, unsigned inviteUid)
{
	if (!IsValidUid(inviteUid))
		return 0;
	CDataUser dbUser;
	DataUser user;
	int ret = dbUser.GetUserLimit(inviteUid, user);
	if(ret != 0)
	{
		if(ret != R_ERR_NO_DATA)
			error_log("[GetUserLimit fail][ret=%,uid=%u,inviteUid=%u]", ret,uid,inviteUid);
		//DB_ERROR_RETURN_MSG("db_get_user_fail");
		return 0;
	}
	++user.invite_count;
	++user.today_invite_count;
	ret = dbUser.SetUserLimit(inviteUid, user);
	if(ret != 0)
	{
		error_log("[SetUserLimit fail][ret=%,uid=%u,inviteUid=%u]", ret,uid,inviteUid);
		//DB_ERROR_RETURN_MSG("db_set_user_fail");
		return 0;
	}
	CDataInviteMapping dbInviteMapping;
	ret = dbInviteMapping.AddMapping(inviteUid, uid);
	if(ret)
		error_log("[add invite mapping fail][uid=%u,inviteUid=%u,ret=%d]", uid, inviteUid, ret);
	return 0;
}

int CLogicUser::SetUser(unsigned uid, DataUser &user, unsigned flag)
{
	CDataUser dbUser;
	int ret = dbUser.SetUser(uid, user, flag);
	if(ret != 0)
	{
		error_log("[SetUser fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}
	return 0;
}

int CLogicUser::SetUserLimit(DataUser &user, unsigned flag)
{
	return SetUserLimit(user.uid, user, flag);
}

int CLogicUser::SetUserLimit(unsigned uid, DataUser &user, unsigned flag)
{
	CDataUser dbUser;
	int ret = dbUser.SetUserLimit(uid, user, flag);
	if (ret != 0)
	{
		error_log("[SetUserLimit fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}
	return 0;
}

int CLogicUser::GetUser(unsigned uid, DataUser &user,unsigned uidBy)
{
	CDataUser dbUser;
	int ret = dbUser.GetUser(uid, user);
	if(ret != 0)
	{
		if(ret != R_ERR_NO_DATA)
			error_log("[GetUser fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_get_user_fail");
	}
	if(uid == uidBy)
	{
		int vipleve = 0;
		TransformVipLevel(user.accCharge, vipleve);
		if (vipleve != user.viplevel)
		{
			int from = user.viplevel + 1;
			int to = vipleve;
			// 合区活动
			/**合区vip晋级返利, add by vincent 2014-07-14*/
			bool isActivityTime = false;
			uint32_t now = Time::GetGlobalTime();
			uint32_t beginTime = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS);  // 合区时间
			uint32_t endTime   = Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS);
			isActivityTime = beginTime <= now && now <= endTime;

			if(!isActivityTime) {	// 开区时间
				beginTime = Config::GetIntValue(CONFIG_OPEN_TS);
				static int lastTime = 7 * 24 * 60 * 60;
				endTime  = beginTime + lastTime;
				isActivityTime = beginTime <= now && now <= endTime;
			}

			if(isActivityTime) {
				if(to >= from) {
					CLogicVipRebates logicVipRebates;
					uint32_t oldtime = logicVipRebates.getTime();
					if(!(beginTime <= oldtime && oldtime <= endTime)) {
						logicVipRebates.clear();
					}
					CLogicUserBasic logicUserBasic;
					DataUserBasic dataUserBasic;
					logicUserBasic.GetUserBasicLimit(uid,OpenPlatform::GetType(),dataUserBasic);
					logicVipRebates.setVip(uid, dataUserBasic.name, from,to);
				}
			}

			user.viplevel = vipleve;
			ret = dbUser.SetUser(uid,user);
			if (0 != ret)
			{
				error_log("Set user faile! ret=%d,uid=%u", ret, uid);
			}
			CLogicUpdates logicUpdates;
			Json::Value updates;
			updates.resize(1);
			updates[(unsigned)0]["s"] = "VIPPROMOTION";
			updates[(unsigned)0]["vip_level"] = vipleve;
			updates[(unsigned)0]["ts"] = (unsigned)time(0);
			ret = logicUpdates.AddUpdates(uid, updates);
			if (0 != ret)
			{
				error_log("AddUpdates failed! uid=%u,ret=%d", uid,ret);
			}
		}
	}

	return 0;
}

int CLogicUser::GetUserLimit(unsigned uid, DataUser &user)
{
	if(!IsValidUid(uid))
		return R_ERR_PARAM;

	CDataUser dbUser;
	int ret = dbUser.GetUserLimit(uid, user);
	if(ret != 0)
	{
		if(ret != R_ERR_NO_DATA)
			error_log("[GetUserLimit fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_get_user_fail");
	}
//	int vipleve = 0;
//	TransformVipLevel(user.accCharge, vipleve);
//	if (vipleve != user.viplevel)
//	{
//		user.viplevel = vipleve;
//		ret = dbUser.SetUserLimit(uid,user);
//		if (0 != ret)
//		{
//			error_log("Set user faile! ret=%d,uid=%u", ret, uid);
//		}
//		CLogicUpdates logicUpdates;
//		Json::Value updates;
//		updates.resize(1);
//		updates[(unsigned)0]["s"] = "VIPPROMOTION";
//		updates[(unsigned)0]["vip_level"] = vipleve;
//		updates[(unsigned)0]["ts"] = (unsigned)time(0);
//		ret = logicUpdates.AddUpdates(uid, updates);
//		if (0 != ret)
//		{
//			error_log("AddUpdates failed! uid=%u,ret=%d", uid,ret);
//		}
//	}
	return 0;
}

int CLogicUser::RemoveUser(unsigned uid)
{
	/* Ralf 20141203 change to job
	DataUser user;
	int ret = GetUserLimit(uid, user);
	if (ret != 0)
		return ret;
	user.status = US_REMOVE;
	ret = SetUserLimit(uid, user);
	if (ret != 0)
		return ret;
	*/
	return 0;
}

int CLogicUser::UpdateLogin(unsigned uid, PlatformType platform, unsigned loginTime)
{
	if (loginTime == 0)
		loginTime = Time::GetGlobalTime();
	DataUser user;
	int ret = GetUserLimit(uid, user);
	if (ret != 0)
	{
		return ret;
	}


	CLogicZhouNianQing logicZhouNianQing;
	ret = logicZhouNianQing.QianDao(uid, user.last_login_time);
	if (ret)
		return ret;


	int inter = CTime::GetDayInterval(user.last_login_time, loginTime);
	if (inter == 1)
		user.login_days++;
	else if (inter > 1)
		user.login_days = 1;
	if (inter > 0)
	{
		if (user.tutorial_stage < TOTORIAL_FINISH)
			user.gcbase = NEW_DAILY_GCBASE;
//		else
//		{
//			if (user.gcbase > GCBASE_LIMIT)
//				user.gcbase = GCBASE_LIMIT;
//		}
		user.newgcbase = DAILY_NEW_GCBASE;
		user.today_invite_count = 0;
		CLogicTribute logicTri;
		logicTri.DaliyTribute(uid, user.invite_count);

	}

	user.last_login_platform = platform;
	user.last_login_time = loginTime;
	user.login_times++;

	return SetUserLimit(uid, user);
}

int CLogicUser::UpdateActiveTime(unsigned uid, unsigned last_active_time, int ext)
{
	unsigned now = Time::GetGlobalTime();
	if (CTime::GetDayInterval(last_active_time, now) != 0)
	{
		ext = 0;
	}
	else if (IsOnlineUser(last_active_time))
	{
		ext += now - last_active_time;
	}
	CDataUser dbUser;
	int ret = dbUser.SetActiveTimeAndExt(uid, now, ext);
	if(ret != 0)
	{
		error_log("[SetActiveTimeAndExt fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}

int CLogicUser::UpdateLastSaveUid(unsigned uid, unsigned last_save_uid)
{
	CDataUser dbUser;
	int ret = dbUser.SetLastSaveUid(uid, last_save_uid);
	if(ret != 0)
	{
		error_log("[SetLastSaveUid fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}

int CLogicUser::UpdateProtectedTime(unsigned uid, unsigned protected_time)
{
	if(protected_time == 0)
	{
		protected_time = Time::GetGlobalTime();
	}
	CDataUser dbUser;
	int ret = dbUser.SetProtectedTime(uid, protected_time);
	if(ret != 0)
	{
		error_log("[SetProtectedTime fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}
/*
int CLogicUser::UpdateBitInfo(unsigned uid, unsigned bit_info)
{
	CDataUser dbUser;
	int ret = dbUser.SetBitInfo(uid, bit_info);
	if(ret != 0)
	{
		error_log("[SetBitInfo fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}
*/
int CLogicUser::SetBitInfo(unsigned uid, unsigned bit_info)
{
	CDataUser dbUser;
	int ret = dbUser.SetBitInfo(uid, bit_info);
	if(ret != 0)
	{
		error_log("[SetBitInfo fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}
int CLogicUser::SetBitInfoLastSaveUid(unsigned uid, unsigned bit_info, unsigned last_save_uid)
{
	CDataUser dbUser;
	int ret = dbUser.SetBitInfoLastSaveUid(uid, bit_info, last_save_uid);
	if(ret != 0)
	{
		error_log("[SetBitInfoLastSaveUid fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}

int CLogicUser::ChangeResource(unsigned uid, int r1, int r2, int r3, int r4)
{
	int ret;
	DataUser user;
	AUTO_LOCK_USER(uid)
	ret = GetUserLimit(uid, user);
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
		ret = SetUserLimit(user);
		if(ret == 0)
		{
			RESOURCE_LOG(
				"[alnc change][uid=%u,r1chg=%d,r1=%u,r2chg=%d,r2=%u,r3chg=%d,r3=%u,r4chg=%d,r4=%u,code=donate]",
				uid,  r1,user.r1, r2, user.r2, r3, user.r3, r4, user.r4);
		}
	}
	return ret;
}
int CLogicUser::ChangeResource(int r1,int r2,int r3,int r4,const string &reason,DataUser &dataUser,Json::Value &result)
{
	unsigned uid = dataUser.uid;
	if ((r1 < 0 && (unsigned)(-r1) > dataUser.r1))
	{
		error_log("[ChangeResource][uid=%u,r1=%d,r1_all=%u,]", uid, r1, dataUser.r1);
		throw std::runtime_error("resource_not_enough");
	}

	if ((r2 < 0 && (unsigned)(-r2) > dataUser.r2))
	{
		error_log("[ChangeResource][uid=%u,r2=%d,r2_all=%u,]", uid, r2, dataUser.r2);
		throw std::runtime_error("resource_not_enough");
	}

	if ((r3 < 0 && (unsigned)(-r3) > dataUser.r3))
	{
		error_log("[ChangeResource][uid=%u,r3=%d,r3_all=%u,]", uid, r3, dataUser.r3);
		throw std::runtime_error("resource_not_enough");
	}

	if ((r4 < 0 && (unsigned)(-r4) > dataUser.r4))
	{
		error_log("[ChangeResource][uid=%u,r4=%d,r4_all=%u,]", uid, r4, dataUser.r4);
		throw std::runtime_error("resource_not_enough");
	}

	if (r1 > 0 || r2 > 0 || r3 > 0 || r4 > 0)
	{
		dataUser.r1 +=  r1;
		if(dataUser.r1 > dataUser.r1_max)
			dataUser.r1 = dataUser.r1_max;
		dataUser.r2 +=  r2;
		if(dataUser.r2 > dataUser.r2_max)
			dataUser.r2 = dataUser.r2_max;
		dataUser.r3 +=  r3;
		if(dataUser.r3 > dataUser.r3_max)
			dataUser.r3 = dataUser.r3_max;
		dataUser.r4 +=  r4;
		if(dataUser.r4 > dataUser.r4_max)
			dataUser.r4 = dataUser.r4_max;
	}else{
		dataUser.r1 += r1;
		dataUser.r2 += r2;
		dataUser.r3 += r3;
		dataUser.r4 += r4;
	}
	RESOURCE_LOG("[%s][uid=%u,chgr1=%d,r1=%u,chgr2=%d,r2=%u,chgr3=%d,r3=%u,chgr4=%d,r4=%u]",
					reason.c_str(), uid, r1, dataUser.r1, r2, dataUser.r2, r3, dataUser.r3, r4, dataUser.r4);

	result["r1"] = dataUser.r1;
	result["r2"] = dataUser.r2;
	result["r3"] = dataUser.r3;
	result["r4"] = dataUser.r4;
	return 0;
}
/*
bool CLogicUser::GetFlag(unsigned bit_info, UserFlag flag)
{
	USER_BIT_INFO info;
	info.v = bit_info;
	unsigned res = 0;
	switch(flag)
	{
	case UF_BE_ATTACKED:
		res = info.s.beAttacked;break;
	case UF_BE_CAN_ONLINE_ATTACKED:
		res = info.s.canOnlineAttacked;break;
	default:break;
	}
	return (res == 1?true:false);
}

void CLogicUser::SetFlag(unsigned &bit_info, UserFlag flag, bool value)
{
	USER_BIT_INFO info;
	info.v = bit_info;
	switch(flag)
	{
	case UF_BE_ATTACKED:
		info.s.beAttacked = (value?1:0);break;
	case UF_BE_CAN_ONLINE_ATTACKED:
		info.s.canOnlineAttacked = (value?1:0);break;
	default:break;
	}
	bit_info = info.v;
}
*/

int CLogicUser::UpdateBreathTime(unsigned uid, unsigned breathTime)
{
	if(breathTime == 0)
	{
		breathTime = Time::GetGlobalTime();
	}
	CDataUser dbUser;
	int ret = dbUser.SetBreathTime(uid, breathTime);
	if(ret != 0)
	{
		error_log("[SetBreathTime fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}

int CLogicUser::UpdateActiveExtBreathTime(unsigned uid, unsigned last_active_time, int ext)
{
	unsigned now = Time::GetGlobalTime();
	if (CTime::GetDayInterval(last_active_time, now) != 0)
	{
		ext = 0;
	}
	else if (IsOnlineUser(last_active_time))
	{
		ext += now - last_active_time;
	}
	CDataUser dbUser;
	int ret = dbUser.SetActiveExtBreathTime(uid, now, ext, now);
	if(ret != 0)
	{
		error_log("[UpdateActiveExtBreathTime fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}

	return 0;
}

int CLogicUser::GetUserFlag(unsigned uid, Json::Value &userFlag)
{
	CDataUser userDB;
	string user_flag;
	int ret = userDB.GetUserFlag(uid, user_flag);
	if (ret != 0)
	{
		error_log("[GetUserFlag fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	if (user_flag.empty())
		user_flag = "{}";
	Json::Reader reader;
	if (!reader.parse(user_flag, userFlag))
	{
		error_log("[paser user_flag fail][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("user_flag_error");
	}
	return 0;
}

int CLogicUser::SetUserFlag(unsigned uid, const Json::Value &userFlag)
{
	Json::FastWriter writer;
	string user_flag = writer.write(userFlag);
	CDataUser userDB;
	int ret = userDB.SetUserFlag(uid, user_flag);
	if (ret != 0)
	{
		error_log("[SetUserFlag fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	return 0;
}

int CLogicUser::GetUserTech(unsigned uid, Json::Value &userTech)
{
	CDataUser userDB;
	string user_tech;
	int ret = userDB.GetUserTech(uid, user_tech);
	if (ret != 0)
	{
		error_log("[GetUserTech fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	if (user_tech.empty())
		user_tech = "{}";
	Json::Reader reader;
	if (!reader.parse(user_tech, userTech))
	{
		error_log("[paser user_flag fail][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("user_flag_error");
	}
	return 0;
}

int CLogicUser::SetUserTech(unsigned uid, const Json::Value &userTech)
{
	Json::FastWriter writer;
	string user_flag = writer.write(userTech);
	CDataUser userDB;
	int ret = userDB.SetUserTech(uid, user_flag);
	if (ret != 0)
	{
		error_log("[SetUserTech fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	return 0;
}

int CLogicUser::GetUserStat(unsigned uid, Json::Value &userStat)
{
	CDataUser userDB;
	string user_stat;
	int ret = userDB.GetUserStat(uid, user_stat);
	if (ret != 0)
	{
		error_log("[GetUserStat fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("get_user_fail");
	}
	if (user_stat.empty())
		user_stat = "{}";
	Json::Reader reader;
	if (!reader.parse(user_stat, userStat))
	{
		error_log("[paser user_stat fail][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("user_stat_error");
	}
	return 0;
}

int CLogicUser::SetUserStat(unsigned uid, const Json::Value &userStat)
{
	Json::FastWriter writer;
	string user_stat = writer.write(userStat);
	CDataUser userDB;
	int ret = userDB.SetUserStat(uid, user_stat);
	if (ret != 0)
	{
		error_log("[SetUserStat fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	return 0;
}

int  CLogicUser::GetMainpos(unsigned uid, unsigned &mainpos)
{
	CDataUser userDB;
	int ret = userDB.GetMainPos(uid,mainpos);
	if (ret != 0)
	{
		error_log("[SetMainpos fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	return 0;
}
int  CLogicUser::SetMainpos(unsigned uid, const  unsigned mainpos)
{
	CDataUser userDB;
	int ret = userDB.SetMainPos(uid,mainpos);
	if (ret != 0)
	{
		error_log("[GetMainpos fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("set_user_fail");
	}
	return 0;
}

int CLogicUser::UpdateMaterial(unsigned uid, const Json::Value &data, string &result)
{
	if(!data.isArray())
	{
		return R_ERR_PARAM;
	}
	Json::Value material = Json::Value(Json::arrayValue);
	Json::FastWriter writer;
	if (!result.empty())
	{
		if(!Json::FromString(material, result))
		{
			error_log("[resource_error][parse material fail]");
			LOGIC_ERROR_RETURN_MSG("resource_error");
		}
	}

	bool needlog = false;
	string log;
	for(unsigned i=0; i<data.size(); i++)
	{
		int iChgValue = 0;
		int currMaterial = 0;
		int itemp = 0;
		if (Json::GetInt(data[i], "d", iChgValue))
		{
			if (material.size() > i)
			{
				if (material[i].isMember("c"))
				{
					currMaterial = material[i]["c"].asInt();
				}
			}

			itemp = currMaterial + iChgValue;
			if(itemp >= 0)
			{
				material[i]["c"] = itemp;
				material[i]["m"] = itemp;
			}
			else
			{
				LOGIC_ERROR_RETURN_MSG("resource_limit");
			}
			char temlog[512];
			snprintf(temlog, 512, "m%d=%d,m%dchg=%d", i, itemp, i, iChgValue);
			log += ","+string(temlog);
			if (iChgValue != 0 )
				needlog = true;
		}
	}
	result = writer.write(material);
	if (needlog)
		MATERIAL_LOG("[change material][uid=%u%s]", uid, log.c_str());
	return 0;
}


int CLogicUser::TransformVipLevel(int accChargeTotal, int &vipLevel)
{
	if(OpenPlatform::IsDS())
	{
		if (accChargeTotal < 50)
		{
			vipLevel = 0;
		}
		else if (accChargeTotal>=50 && accChargeTotal<250)
		{
			vipLevel = 1;
		}
		else if (accChargeTotal>=250 && accChargeTotal<750)
		{
			vipLevel = 2;
		}
		else if (accChargeTotal>=750 && accChargeTotal<2250)
		{
			vipLevel = 3;
		}
		else if (accChargeTotal>=2250 && accChargeTotal<3750)
		{
			vipLevel = 4;
		}
		else if (accChargeTotal>=3750 && accChargeTotal<7500)
		{
			vipLevel = 5;
		}
		else if (accChargeTotal>=7500 && accChargeTotal<22500)
		{
			vipLevel = 6;
		}
		else if (accChargeTotal>=22500 && accChargeTotal<37500)
		{
			vipLevel = 7;
		}
		else if (accChargeTotal>=37500 && accChargeTotal<75000)
		{
			vipLevel = 8;
		}
		else if (accChargeTotal>=75000 && accChargeTotal<225000)
		{
			vipLevel = 9;
		}
		else if (accChargeTotal>=225000)
		{
			vipLevel = 10;
		}
	}
	else
	{
		if (accChargeTotal < 100)
		{
			vipLevel = 0;
		}
		else if (accChargeTotal>=100 && accChargeTotal<500)
		{
			vipLevel = 1;
		}
		else if (accChargeTotal>=500 && accChargeTotal<1000)
		{
			vipLevel = 2;
		}
		else if (accChargeTotal>=1000 && accChargeTotal<3000)
		{
			vipLevel = 3;
		}
		else if (accChargeTotal>=3000 && accChargeTotal<5000)
		{
			vipLevel = 4;
		}
		else if (accChargeTotal>=5000 && accChargeTotal<10000)
		{
			vipLevel = 5;
		}
		else if (accChargeTotal>=10000 && accChargeTotal<30000)
		{
			vipLevel = 6;
		}
		else if (accChargeTotal>=30000 && accChargeTotal<50000)
		{
			vipLevel = 7;
		}
		else if (accChargeTotal>=50000 && accChargeTotal<100000)
		{
			vipLevel = 8;
		}
		else if (accChargeTotal>=100000 && accChargeTotal<300000)
		{
			vipLevel = 9;
		}
		else if (accChargeTotal>=300000)
		{
			vipLevel = 10;
		}
	}
	return 0;
}

int CLogicUser::GetUserClass(unsigned uid, int &type)
{
	int ret = 0;
	DataUser user;
	ret = GetUserLimit(uid,user);
	if (0 != ret)
		return ret;
	/* Ralf 20141203 change to empty for keeping
	if (user.type == UT_NOT_REAL)
	{
		type = US_CLASS_NOT_REAL;
		return R_SUCCESS;
	}
	*/

	if (user.level<20)
	{
		type = US_CLASS_LOW_LEVEL;
	}
	else if (user.level>=20 && user.level<=30)
	{
		if (user.accCharge>=5000)
		{
			type = US_CLASS_PAY_ONE;
		}
		else if (user.accCharge>=1000 && user.accCharge <5000)
		{
			type = US_CLASS_PAY_TOW;
		}
		else if (user.accCharge>0 && user.accCharge<1000)
		{
			type = US_CLASS_PAY_THREE;
		}
		else
		{
			CLogicAttack logicAttack;
			vector<DataAttack> attacks;
			int attactNumber = 0;
			ret = logicAttack.GetAttackHistory(uid, attacks);
			if (0 == ret)
			{
				for (vector<DataAttack>::iterator itr=attacks.begin(); itr!=attacks.end();++itr)
				{
					if (itr->attack_uid == uid)
					{
						++attactNumber;
					}
				}
			}
			if (attactNumber>=5)
			{
				type = US_CLASS_LIKE_WAR;
			}
			else if (user.login_days > 3)
			{
				type = US_CLASS_ACTIVE;
			}
			else if (user.alliance_id != 0)
			{
				type = US_CLASS_IN_ALLIANCE;
			}
			else
			{
				type = US_CLASS_OTHER;
			}
		}
	}
	else if (user.level>30)
	{
		if (user.accCharge>=1000)
		{
			type = US_CLASS_PAY_ONE;
		}
		else if (user.accCharge>=1000 && user.accCharge <10000)
		{
			type = US_CLASS_PAY_TOW;
		}
		else if (user.accCharge>0 && user.accCharge<1000)
		{
			type = US_CLASS_PAY_THREE;
		}
		else
		{
			CLogicAttack logicAttack;
			vector<DataAttack> attacks;
			int attactNumber = 0;
			ret = logicAttack.GetAttackHistory(uid, attacks);
			if (0 == ret)
			{
				for (vector<DataAttack>::iterator itr=attacks.begin(); itr!=attacks.end();++itr)
				{
					if (itr->attack_uid == uid)
					{
						++attactNumber;
					}
				}
			}
			if (attactNumber>=20)
			{
				type = US_CLASS_LIKE_WAR;
			}
			else if (user.login_days > 7)
			{
				type = US_CLASS_ACTIVE;
			}
			else if (user.alliance_id != 0)
			{
				type = US_CLASS_IN_ALLIANCE;
			}
			else
			{
				type = US_CLASS_OTHER;
			}
		}
	}

	return R_SUCCESS;
}

int CLogicUser::ChangeBet(unsigned uid, int bet, bool allserver)
{
	if(allserver)
	{
		if(!bet)
			return 0;

		int ret,oldbet = 0;
		DataUser user;
		ret = GetUser(uid, user);
		if(ret != 0)
			return ret;

		Json::Value data;
		Json::Reader reader;
		Json::FastWriter writer;
		reader.parse(user.user_stat, data);
		if(data.isMember("bet"))
			oldbet = data["bet"].asInt();
		oldbet = oldbet + bet;
		if(oldbet < 0){
			error_log("[resource_error][uid,betchg=%d]", uid, bet);
			LOGIC_ERROR_RETURN_MSG("resource_error");
		}

		data["bet"] = oldbet;
		user.user_stat = writer.write(data);
		ret = SetUser(uid,user);
		if(ret == 0)
		{
			RESOURCE_LOG("[bet change][uid=%u,betchg=%d,bet=%d,code=bet]",uid,bet,oldbet);
		}

		return ret;
	}
	else
	{
		if(!bet)
			return 0;

		int ret,oldbet = 0;
		DataUser user;
		AUTO_LOCK_USER(uid)
		ret = GetUser(uid, user);
		if(ret != 0)
			return ret;

		Json::Value data;
		Json::Reader reader;
		Json::FastWriter writer;
		reader.parse(user.user_stat, data);
		if(data.isMember("bet"))
			oldbet = data["bet"].asInt();
		oldbet = oldbet + bet;
		if(oldbet < 0){
			error_log("[resource_error][uid,betchg=%d]", uid, bet);
			LOGIC_ERROR_RETURN_MSG("resource_error");
		}

		data["bet"] = oldbet;
		user.user_stat = writer.write(data);
		ret = SetUser(uid,user);
		if(ret == 0)
		{
			RESOURCE_LOG("[bet change][uid=%u,betchg=%d,bet=%d,code=bet]",uid,bet,oldbet);
		}

		return ret;
	}

	return 0;
}

int CLogicUser::ChangeBetForBack(unsigned uid, int bet, string &userStat, unsigned &balance)
{
	if(!bet)
		return 0;

	int oldbet = 0;

	Json::Value data;
	Json::Reader reader;
	Json::FastWriter writer;
	reader.parse(userStat, data);
	if(data.isMember("bet"))
		oldbet = data["bet"].asInt();
	oldbet = oldbet + bet;
	if(oldbet < 0){
		error_log("[resource_error][uid,betchg=%d]", uid, bet);
		LOGIC_ERROR_RETURN_MSG("resource_error");
	}

	data["bet"] = oldbet;
	balance = oldbet;
	userStat = writer.write(data);
	RESOURCE_LOG("[bet change][uid=%u,betchg=%d,bet=%d,code=bet]",uid,bet,oldbet);

	return R_SUCCESS;
}

ILock* CLogicUser::GetLock(unsigned uid)
{
	if(!IsValidUid(uid))
		return NULL;

	if(m_lockmap.count(uid))
		return m_lockmap[uid];

	CVsem* lock = new CVsem;
	if(!lock->CreateOrOpen(CTrans::ITOS(uid).c_str(),uid))
	{
		delete lock;
		return NULL;
	}

	m_lockmap[uid] = lock;
	return lock;
}
ILock* CLogicUser::GetSaveLock(unsigned uid, LoadType type)
{
	if(CLogicArchive::IsVision(type))
		return NULL;

	return GetLock(uid);
}
void CLogicUser::Lock(unsigned uid)
{
	ILock* lock = GetLock(uid);
	if(lock)
		lock->Lock();
}
void CLogicUser::Unlock(unsigned uid)
{
	ILock* lock = GetLock(uid);
	if(lock)
		lock->Unlock();
}

int CLogicUser::CheckR5(DataUser &user)//20150908 Ralf fix
{
	if(!IsAllianceId(user.alliance_id) || CTime::IsDiffDay(Time::GetGlobalTime(), user.cdn))
	{
		user.r5 = 0;
		user.r5_max = 0;
	}
	return 0;
}

int CLogicUser::SetR5(unsigned uid, int r5_max)
{
	AUTO_LOCK_USER(uid)
	CDataUser dbUser;
	int ret = dbUser.SetR5(uid, 2, r5_max, Time::GetGlobalTime());
	if(ret != 0)
	{
		error_log("[SetR5 fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("db_set_user_fail");
	}
	return 0;
}
