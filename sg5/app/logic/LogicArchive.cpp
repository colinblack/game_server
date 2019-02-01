#include "LogicArchive.h"
#include "LogicCMD.h"

static struct S_LOAD_TYPE
{
	LoadType type;
	const char *desc;
}
loadTypes[] =
{
	{LT_LOGIN, "login"},
	{LT_BUILD, "build"},

	{LT_SUBBASE, "branchbuild"},

	{LT_DEFEND, "defense"},
	{LT_DEFEND, "barbarian"},

	{LT_VIEW, "view"},

	{LT_ATTACK, "attack"},
	{LT_ATTACK, "allianceboss"},
	{LT_ATTACK, "worldboss"},
	{LT_ATTACK, "godfb"},

	{LT_RANK, "rankmode"},
	{LT_CHALLENGE, "challenge"},
	{LT_DRAGON, "dragon"},
	{LT_BNW, "bnw"},
	{LT_MVP, "mvp"},

	{LT_SPORTS, "sports"},
	{LT_SPORTS, "boatdata"},
	{LT_SPORTS, "escortmode"},
	{LT_SPORTS, "fairyland"},

	{LT_REPLAY, "review"},

	{LT_UNKNOW, NULL}
};

static int SetProtectedTime(int userLevel, int damage, int damage2, unsigned pt)
{
	unsigned protectedTime;
	unsigned p = 3;
	if(userLevel <= 30)
		p = 1;
	else if(userLevel <= 80)
		p = 2;

	damage2 = damage;//fix again 20150310
	if(damage2 <= 50)
		protectedTime = 0;
	else if(damage2 <= 80)
		protectedTime = p * (damage2 - 20);
	else
		protectedTime = p * 60;
	/* fix again 20150310
	if(damage > 80 && protectedTime < 30)
		protectedTime = 30;
	*/

	if(protectedTime)
	{
		float p1 = 0.0f;
		if(pt < 60 * 60)
			p1 = 1.0f;
		else if(pt < 120 * 60)
			p1 = 0.9f;
		else if(pt < 180 * 60)
			p1 = 0.7f;//fix again 20150310
		else if(pt < 300 * 60)
			p1 = 0.4f;//fix again 20150310
		else if(pt < 500 * 60)
			p1 = 0.2f;

		protectedTime = std::max(10.0f, (float)protectedTime * p1);
	}

	return protectedTime * 60;
}

int CLogicArchive::GetInitArchive(const Json::Value *&pArchive)
{
	static unsigned s_lastUpdateTime = 0;
	static Json::Value s_initArchive(Json::objectValue);  // 对象类型
	if (Time::GetGlobalTime() - s_lastUpdateTime > 1800) {
		int result;
		string archivePath = MainConfig::GetAllServerPath(CONFIG_INIT_ARCHIVE);
		if (!archivePath.empty()) {
			string data;
			result = File::Read(archivePath, data);
			if (result != 0) {
				fatal_log("[init archive not exist][ret=%d,path=%s]", result,
						archivePath.c_str());
				DB_ERROR_RETURN_MSG("db_init_archive_fail");
			}
			Json::Reader reader;
			if (!reader.parse(data, s_initArchive)) {
				fatal_log("[parse json fail][path=%s]", archivePath.c_str());
				DB_ERROR_RETURN_MSG("db_init_archive_fail");
			}
			s_lastUpdateTime = Time::GetGlobalTime();
		}
	}

	pArchive = &s_initArchive;

	return 0;
}

int CLogicArchive::Load(unsigned uid, unsigned uidBy, const string &type,const Json::Value &data, Json::Value &result, unsigned lasttime, unsigned gmFlag)
{
	//TIME_COUNT_RESTART("[load start]");
	LoadType loadType = GetLoadType(type);
	if((uid == uidBy && !IsSelfType(loadType))
	|| (uid != uidBy && !IsOtherType(loadType)))
	{
		REFUSE_RETURN_MSG("load_type_error");
	}

	Json::FastWriter writer;
	Json::Reader reader;
	bool reload = true;
	int ret = 0;
	CLogicUser logicUser;
#if DATA_NEW_WORLD_ENABLE == 0
	WorldPoint worldPoint;
	CLogicWorld logicWorld;
#endif
	CLogicBaseExtra logicBaseExtra;
	DataBaseExtra dataBaseExtra;

	DataUser userBy;
	if (uid != uidBy) {
		ret = logicUser.GetUser(uidBy, userBy);
		if (ret != 0)
			return ret;
		//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
		if (IsBeingAttacked(userBy.last_breath_time))
		{
			//error_log("[being_attacked][userBy=%u,last_breath_time=%u]",uidBy,userBy.last_breath_time);
			LOGIC_ERROR_RETURN_MSG("u_being_attacked");
		}
	}

	// 判断要加载的是不是NPC角色
	if (IsNPCUid(uid)) {
		CLogicNpc logicNpc;
		ret = logicNpc.Load(uid, uidBy, result);
		if (ret != 0)
			return ret;
		//result["lasttime"] = Time::GetGlobalTime();

		result["attackpermitted"] = APT_ALLOW;
		result["online"] = 0;
		// 判断是不是世界bos
		if (IsWorldNPCUid(uid)) {
#if DATA_NEW_WORLD_ENABLE == 0
			unsigned world_pos;
			if (Json::GetUInt(data, "world_pos", world_pos)) {
				//result["world_pos"] = world_pos;
				result["world_pos"]["world_pos"] = world_pos;
				if (IsValidWorldPos(world_pos)) {
					logicWorld.GetUserInfo(world_pos, worldPoint);
					result["world_pos"]["type"] = worldPoint.map_flag;
				}
			}
#endif
			result["worldnpc"] = 1;
			if (loadType == LT_ATTACK) {
#if DATA_NEW_WORLD_ENABLE == 0
				WORLD_ATTACK_LOG("attack|%u|%u|%u|%d|%d|", uidBy, uid, world_pos, worldPoint.map_flag, 0);
#else
				WORLD_ATTACK_LOG("attack|%u|%u|%u|%d|%d|", uidBy, uid, 0, 0, 0);
#endif
			}
			if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
			{
				if (LT_CHALLENGE == loadType)
				{
//					debug_log("start NPC Challenge -- Cream");
					unsigned cid = 0;
					Json::GetUInt(data, "cid", cid);
					CLogicNewWorld logicNewWorld;
					ret = logicNewWorld.SetChallengeTS(cid, 1, userBy.kingdom);
					if (ret)
					{
						return ret;
					}

					CLogicSecinc logicSecinc;
					Json::Value zhulu;
					ret = logicSecinc.GetSecinc(uidBy, NAT_NEWWORLD_MISSION_2, zhulu);
					zhulu["a"] = 0;
					ret = logicSecinc.SetOneSecinc(uidBy, zhulu);
					if (ret)
					{
						return ret;
					}
				}
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
			}
			//TIME_COUNT_LOG("[load world boss over]");
			return 0;
		}
		//五虎将统计日志
		if(IsWuhujiangNPCUid(uid)){
			int zhang = data["zhang"].asInt();
			int jie = data["jie"].asInt();
			WORLD_ATTACK_LOG("wuhujiang|%u|%u|%d|%d|%d|", uidBy, uid,
					zhang, jie, 0);
		}
		result["npc"] = 1;
		if (result["userid"].asInt() == 401)  // 竞技场初始化npc
				{
			result["name"] = "挑战我吧";
		}
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
		{
			if(IsCityNPCUid(uid))
			{
				userBy.bit_info = Time::GetGlobalTime();
				Json::Value worldres;
				if(!userBy.worldres.empty())
					reader.parse(userBy.worldres, worldres);
				worldres["r1"] = userBy.r1;
				worldres["r2"] = userBy.r2;
				worldres["r3"] = userBy.r3;
				worldres["r4"] = userBy.r4;
				worldres["r5"] = userBy.r5;
				worldres["bug"] = 0;
				userBy.worldres = writer.write(worldres);
				logicUser.SetUser(uidBy, userBy, DATA_USER_BI);
			}
			else
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		}
		//TIME_COUNT_LOG("[load npc over]");
		return 0;
	}
	// 判断是不是擂主
	if (IsValidArenaId(uid)) {
		//int regfee = 0;
		//Json::GetInt(data, "coin", regfee);
		CLogicArena logicArena;
		ret = logicArena.Load(uid, uidBy, userBy.level, loadType, ARENA_COST, result);
		if (ret != 0)
			return ret;
		result["arena"] = 1;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load arena over]");
		return 0;
	}
	if (IsValidInstanceId(uid)) {
		int iscontinue = 0;
		Json::GetInt(data, "iscontinue", iscontinue);
		CLogicInstance logicInstance;
		ret = logicInstance.Load(uid, uidBy, (iscontinue == 1 ? false : true),
				result);
		if (ret != 0)
			return ret;
		result["instance"] = 1;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load instance over]");
		return 0;
	}
	if (IsValidFightingId(uid)) {
		CLogicFighting logicFighting;
		ret = logicFighting.Load(uid, uidBy, result);
		if (ret != 0)
			return ret;
		result["fighting"] = 1;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load fight over]");
		return 0;
	}
	if (IsValidFightArenaId(uid)) {
		//int regfee = 0;
		//Json::GetInt(data, "coin", regfee);
		CLogicFightArena logicArena;
		ret = logicArena.Load(uid, uidBy, userBy.level, loadType, ARENA_COST, result);
		if (ret != 0)
			return ret;
		result["arena"] = 2;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load fight arena over]");
		return 0;
	}
	if (IsValidWorldBossId(uid)) {
		CLogicWorldBoss logicWorldBoss;
		ret = logicWorldBoss.Load(uid, uidBy, result);
		if (ret != 0)
			return ret;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load world boss over]");
		return 0;
	}
	if (IsValidNianShouId(uid)) {
		CLogicNianShou logicNianShou;
		ret = logicNianShou.Load(uid, uidBy, result);
		if (ret != 0)
			return ret;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load world boss over]");
		return 0;
	}
	//AllianceBoss
	if (IsValidAllianceBossId(uid)) {
			CLogicAllianceBoss logicAllianceBoss;
			ret = logicAllianceBoss.Load(uid, userBy, result);
			if (ret != 0)
				return ret;
			result["online"] = 0;
			if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
					logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
			//TIME_COUNT_LOG("[load alliance world boss over]");
			return 0;
		}
	if (IsValidBMatchInstId(uid)) {
		CLogicBaseMatch logicBaseMatch;
		ret = logicBaseMatch.Load(uid, uidBy, result);
		if (ret != 0)
			return ret;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load base match over]");
		return 0;
	}
	if (IsValidAllServerBMatchInstId(uid)) {
		string url = "action=loadallserverbmatch";
		string strUid;
		String::Format(strUid, "%u", uid);
		url.append("&uid=");
		url += strUid;

		string strUidBy;
		String::Format(strUidBy, "%u", uidBy);
		url.append("&userid=");
		url += strUidBy;

		CLogicAllServerBaseMatch logicBaseMatch;
		ret = logicBaseMatch.RequestBaseMatch(url, result);
		if (ret != 0)
			return ret;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load all server base match over]");
		return 0;
	}
	if (IsValidPersonMatchId(uid)) {
		CLogicPersonMatch logicPersonMatch;
		ret = logicPersonMatch.Load(uid, uidBy, result);
		if (ret != 0)
			return ret;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load person match over]");
		return 0;
	}
	if (IsValidAllServerPersonMatchId(uid)) {
		string url = "action=loadallserverpmatch";
		string strUid;
		String::Format(strUid, "%u", uid);
		url.append("&uid=");
		url += strUid;

		string strUidBy;
		String::Format(strUidBy, "%u", uidBy);
		url.append("&userid=");
		url += strUidBy;

		CLogicAllServerBaseMatch logicBaseMatch;
		ret = logicBaseMatch.RequestBaseMatch(url, result);
		if (ret != 0)
			return ret;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		//TIME_COUNT_LOG("[load all server person match over]");
		return 0;
	}
	if (IsValidAllianceBattleId(uid)) {
		CLogicAllianceBattle logicAllianceBattle;
		ret = logicAllianceBattle.Load(uid, userBy, loadType, result);
		if (ret != 0)
			return ret;
		result["online"] = 0;
		if (IsBattleType(loadType))//Ralf20140225  后台增加pve或pvp保护
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		return 0;
	}
	if (!IsValidUid(uid)) {
		REFUSE_RETURN_MSG("invalid_uid");
	}

	DataPay payData;
	CLogicPay logicPay;
	ret = logicPay.GetPay(uidBy, payData);
	if (ret != 0)
		return ret;

	DataUserBasic userBasic;
	DataUser user;
	DataUserData userData;
	CLogicUserBasic logicUserBasic;
	ret = logicUserBasic.GetUserBasicLimitSmart(uid, OpenPlatform::GetType(),
			userBasic);
	if (ret != 0)
		return ret;
	ret = logicUser.GetUser(uid, user, uidBy);
	if (ret != 0)
		return ret;

	bool isMainPos = true;
	unsigned world_pos;
	if (!Json::GetUInt(data, "world_pos", world_pos) || world_pos == 0) {
		if (IsValidWorldPos(user.mainpos)) {
			world_pos = user.mainpos;
		} else {
			world_pos = 0;
		}
	}
	// 默认主城坐标
	isMainPos = ((world_pos == 0 || world_pos == user.mainpos) ? true : false);
	if (!isMainPos) {
		if (IsValidUid(uid)) {
			ret = logicBaseExtra.GetBaseExtra(uid, world_pos, dataBaseExtra);
			if (0 != ret) {
				error_log("uid_worldpos_mismatch,operated=%u,world_pos=%u,operator=%u",
						uid, world_pos, uidBy);
				LOGIC_ERROR_RETURN_MSG("uid_worldpos_mismatch");
			}
		}
	}
	// add by aaron 20121030
	CLogicUserData logicUserData;
	ret = logicUserData.GetUserData(uid, userData);
	if (ret != 0)
		return ret;

	CLogicAlliance logicAlliance;
	DataAlliance alliance;
	DataAllianceMember allianceMember;
	vector<DataEmail> vDataEmail;
	CLogicEmail clogicEmail;
	if (IsAllianceId(user.alliance_id)) {
		ret = logicAlliance.GetAlliance(user.alliance_id, alliance);
		if (ret != 0)
			return ret;
		CDataAllianceMember dbAllianceMember;
		ret = dbAllianceMember.GetMember(user.alliance_id, uid, allianceMember);
		if (ret != 0) {
			if (R_ERR_NO_DATA == ret) {
				user.alliance_id = ALLIANCE_ID_NULL;
				user.r5 = 0;
				user.r5_max = 0;
				user.cdn = Time::GetGlobalTime();
				CDataUser dbUser;
				dbUser.SetAllianceId(uid, ALLIANCE_ID_NULL, 0, 0, Time::GetGlobalTime());
				alliance.alliance_id = ALLIANCE_ID_NULL;
				alliance.flag = 0;
			} else {
				error_log("[GetMember fail][ret=%d,allianceId=%u,uid=%u]", ret,
						user.alliance_id, uid);
				DB_ERROR_RETURN_MSG("get_alliance_member_fail");
			}
		}
	}
	else
	{
		alliance.alliance_id = ALLIANCE_ID_NULL;
		alliance.flag = 0;
	}

	result["online"] = 0;
	if (CTime::GetDayInterval(user.last_active_time, Time::GetGlobalTime())
			!= 0) {
		result["onlinets"] = 0;
	} else {
		result["onlinets"] = user.ext;
	}

	logicUser.CheckR5(user);

	if (uid == uidBy)
		userBy.copyLimit(user);

	unsigned ballid = 0;
	unsigned ballts = 0;
	CLogicDragonball logicBall;
	logicBall.WhichDragonballHold(uid, ballid, ballts);
	result["ballid"] = ballid;
	result["ballts"] = ballts;
	bool isFriend = false;
	//不同类型载入的差异部分

	//TIME_COUNT_LOG("[load 2 user over]");

	if (uid == uidBy) {
		if (isMainPos) {
			/* Ralf 20141203 change to job
			if (user.status == US_BAN) {
				REFUSE_RETURN_MSG("being_blocked");
			}
			*/
			if (user.tribute_time > Time::GetGlobalTime())
			{  // 封一段时间，being_blocked_后面是还剩的秒数
				string retStr = "being_blocked_" + CTrans::ITOS(user.tribute_time-Time::GetGlobalTime());
				REFUSE_RETURN_MSG(retStr);
			}
			//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
			if (IsBeingAttacked(user.last_breath_time))
			{
				//debug_log("[load self be attacked,uid=%u,last_breath_time=%u]",uid,user.last_breath_time);
				LOGIC_ERROR_RETURN_MSG("u_being_attacked");
			}
			//20131107 Ralf last_save_uid -> last_load_save_uid : fix for bugs, can save only last load archieve
			Json::Value worldres;
			if(!user.worldres.empty())
				reader.parse(user.worldres, worldres);
			int bug = 0;
			unsigned tokencount = 1;
			Json::GetInt(worldres, "bug", bug);
			Json::GetUInt(worldres, "tokencount", tokencount);

			result["tokencount"] = tokencount;

			if(user.bit_info || user.last_save_uid != uid || bug)
			{
				/*
				if(user.bit_info)
					BATTLE_LOG("uid=%u,battle=%u,time=%u",uid,user.last_save_uid,Time::GetGlobalTime()-user.bit_info);
				*/
				user.bit_info = 0;
				user.last_save_uid = uid;
				worldres["r1"] = 0;
				worldres["r2"] = 0;
				worldres["r3"] = 0;
				worldres["r4"] = 0;
				worldres["r5"] = 0;
				worldres["bug"] = 0;
				user.worldres = writer.write(worldres);
				logicUser.SetUser(uid, user, DATA_USER_BI|DATA_USER_LSUID);
			}
			//debug_log("[load self uid=%u]",uid);

			//处理朝贡
			CLogicTribute logicTribute;
			ret = logicTribute.GetTribute(uid, result["tributes"]);
			if (ret != 0)
			return ret;
			if (!userData.npcattack.empty() && !reader.parse(userData.npcattack, result["npcattack"]))
			{
				error_log("[npcattack parse fail][uid=%u]",uid);
				DATA_ERROR_RETURN_MSG("parse_npcattack_fail");
			}
			if (!userData.gift.empty() && !reader.parse(userData.gift, result["gift"]))
			{
				error_log("[gift parse fail][uid=%u]",uid);
				DATA_ERROR_RETURN_MSG("parse_gift_fail");
			}
			if (!userData.dailyquest.empty() && !reader.parse(userData.dailyquest, result["dailyquest"]))
			{
				error_log("[dailyquest parse fail][uid=%u]",uid);
				DATA_ERROR_RETURN_MSG("parse_dailyquest_fail");
			}
			CLogicQuest logicQuest;
			ret = logicQuest.GetQuest(uid, result["quest"]);
			if (ret != 0)
				return ret;

			Json::Value userFlag;
			if (!user.user_flag.empty())
			{
				if(reader.parse(user.user_flag, userFlag))
				{
					if (!userFlag.isMember("dchg")
							|| CTime::GetDayInterval(userFlag["dchg"][0u].asUInt(), Time::GetGlobalTime()) != 0)
					{
						userFlag["dchg"][0u] = Time::GetGlobalTime();
						userFlag["dchg"][1u] = 0;
					}
					result["dailyacccharge"] = userFlag["dchg"][1u];
					result["dailyaccchargeTS"] = userFlag["dchg"][0u];
				}
				else
				{
					error_log("[user_flag parse fail][uid=%u]",uid);
					DATA_ERROR_RETURN_MSG("parse_user_flag_fail");
				}
			}

			result["pointpay"].resize(0);
			if(userFlag.isMember("user_pay"))
			{
				result["pointpay"] = userFlag["user_pay"];
			}

			result["chgs"].resize(0);
			if(userFlag.isMember("chgs"))
			{
				result["chgs"] = userFlag["chgs"];
			}

			if(!userFlag.isMember("heroCoins"))   //用于购买武将碎片
			{
				result["coins3"] = 0;
				result["todaycharge"] = 0;
			}
			else
			{
				unsigned coins3 = 0;
				Json::GetUInt(userFlag["heroCoins"],1,coins3);
				result["coins3"] = coins3;
				unsigned last_ts = 0;
				Json::GetUInt(userFlag["heroCoins"],0u,last_ts);
				unsigned now = time(0);
				if(CTime::GetDayInterval(last_ts,now) == 0)
				{
					unsigned todaycharge = 0;
					Json::GetUInt(userFlag["heroCoins"],2,todaycharge);
					result["todaycharge"] = todaycharge;
				}
				else
				{
					result["todaycharge"] = 0;
				}
			}

			// add by aaron 20130130
			CLogicBroadcast logicBd;
			vector<BroadcastMessage> bdMsgs;
			ret = logicBd.GetBdMessage(bdMsgs);
			if (ret == 0 && bdMsgs.size() > 0)
			{
				result["broadcast"].resize(bdMsgs.size());
				for (unsigned i = 0; i < bdMsgs.size(); i++)
				{
					result["broadcast"][i]["id"] = bdMsgs[i].id;
					result["broadcast"][i]["content"] = bdMsgs[i].content;
				}
			}
			result["acccharge"] = user.accCharge;

			//未成年标志
			unsigned nonage = 0;
			if (!userBasic.extra.empty())
			{
				Json::Value extraJson;
				if (reader.parse(userBasic.extra, extraJson))
					Json::GetUInt(extraJson, "nng", nonage);
				else
					error_log("[userBasic.extra parse fail][uid=%u]",uid);
			}
			result["nonage"] = nonage;

			// daily accharge add by aaron 20121106
			/********************for new email remind, add by aaron 20120803******************/
			ret = clogicEmail.GetInboxEmailList(uid,vDataEmail);
			if(ret == 0)
			{
				unsigned int iCount = vDataEmail.size();
				for(unsigned int i = 0; i < iCount;i++)
				{

					if(vDataEmail[i].read_ts == 0)
					{
						result["not_read"] = 1;
						break;
					}
					result["not_read"] = 0;
				}
			}
			/********************for new email remind, add by aaron 20120803******************/
			// 返回开服天数
			result["open_days"] = CTime::GetDayInterval(Config::GetIntValue(CONFIG_OPEN_TS), Time::GetGlobalTime()) + 1;
			GetActivityTime(result["activitytime"]);

			//TIME_COUNT_LOG("[load main self over]");
		}//isMainPos
		else
		{
			if (BEING_ATTACK == dataBaseExtra.being_attack_flag && IsBeingAttacked(dataBaseExtra.last_breath_time) && uidBy != dataBaseExtra.last_breath_uid)
			{
				LOGIC_ERROR_RETURN_MSG("u_being_attacked");
			}
			dataBaseExtra.last_breath_time = Time::GetGlobalTime();
			dataBaseExtra.last_breath_uid = uidBy;
			dataBaseExtra.being_attack_flag = NO_ATTACK;
			ret = logicBaseExtra.SetBaseExtra(uid,world_pos,dataBaseExtra);
			if(0 != ret)
			{
				LOGIC_ERROR_RETURN_MSG("update_baseExtra_failed");
			}

			//TIME_COUNT_LOG("[load extra self over]");
		}
		vector<DataUserAttack> attacks;
		CLogicAttack logicAttack;
		ret = logicAttack.GetUnreadAttacks(uid,world_pos, AT_DEFENCE, attacks,isMainPos);
		if(ret == 0)
		{
			result["attacks"].resize(attacks.size());
			for(unsigned i = 0; i < attacks.size(); i++)
			{
				Json::Value attackData;
				attackData["userid"] = attacks[i].opposite_uid;
				attackData["starttime"] = attacks[i].start_time;
				attackData["world_pos"] = attacks[i].worldpos;
				attackData["log"] = "";
				DataUserBasic userAttack;
				ret = logicUserBasic.GetUserBasicLimit(attacks[i].opposite_uid, (PlatformType)attacks[i].opposite_platform, userAttack);
				if(ret == 0)
				{
					attackData["fbid"] = userAttack.open_id;
					attackData["name"] = userAttack.name;
					attackData["pic_square"] = userAttack.figure_url;
				}
				result["attacks"][i] = attackData;
			}
		}
#if DATA_NEW_WORLD_ENABLE == 0
		// 读取分基地坐标信息
		logicBaseExtra.GetWorldPosList(uid,result["world_pos"]["sub_base_pos"]);
#endif
		//加载自己才加载stat
		if (!user.user_stat.empty()
				&& !reader.parse(user.user_stat, result["stats"])) {
			error_log("[user stat parse error][uid=%u]", uid);
			DATA_ERROR_RETURN_MSG("parse_user_stat_fail");
		}

		// 2014901 Ralf change to save activity
		CLogicSecinc logicSecinc;
		ret = logicSecinc.GetSecinc(uid, result["newAct"]);
		if (ret != 0)
			return ret;

		if(loadType == LT_LOGIN)
		{
			/*************20140815 优化邀请这一部分，只有登录时才发************************/
			DataUserBasic dataUserBasic;
			CDataInviteMapping mappingdata;
			DataUser userInvited;
			CLogicUser logicuser;
			vector<unsigned> vUid;
			int iCount = 0;
			int level45Count = 0;
			int level25Count = 0;
			int level15Count = 0;
			ret = mappingdata.GetUid(uid, vUid);
			if(ret == 0)
			{
				int i = 0;
				iCount = vUid.size();
				for(i = iCount - 1;i >=0;i--)
				{
					logicuser.GetUserLimit(vUid[i],userInvited);
					if( userInvited.level >= 45)
						level45Count++;
					if(userInvited.level >= 25)
						level25Count++;
					if(userInvited.level >= 15)
						level15Count++;
				}
			}
			result["invite_reward_info"]["level45"] = level45Count;
			result["invite_reward_info"]["level25"] = level25Count;
			result["invite_reward_info"]["level15"] = level15Count;
			result["invite_reward_info"]["invite_count"] = iCount;
			/*************20140815 优化邀请这一部分，只有登录时才发************************/

			if(gmFlag == gm_gift || gmFlag == gm_s_gift)
			{
				if((gmFlag == gm_gift && (!result["stats"].isMember("bso") || result["stats"]["bso"].asUInt() == 0))
				|| (gmFlag == gm_s_gift && (!result["stats"].isMember("bso2") || result["stats"]["bso2"].asUInt() == 0)))
				{
					if(gmFlag == gm_gift)
						result["stats"]["bso"] = 1;
					else
						result["stats"]["bso2"] = 1;
				}
			}
		}
		//TIME_COUNT_LOG("[load self over]");
	}//uid == uidBy
	else
	{	//加载别人的数据
		isFriend = logicUserBasic.IsFriend(uidBy, OpenPlatform::GetType(), uid);
		if(isMainPos)
		{
			if (IsOnlineUser(user.last_active_time))
			{
				result["online"] = 1;
			}
		}
		if (loadType == LT_ATTACK)
		{
			DataUserBasic userBasicBy;
			ret = logicUserBasic.GetUserBasicLimit(uidBy, OpenPlatform::GetType(), userBasicBy);
			if (ret != 0)
				return ret;
			//判断是否可以攻击
			CLogicMap logicMap;
			AttackPermitType permit = APT_ALLOW;
			if(isMainPos)
			{
				if(user.last_save_time == lasttime)
					reload = false;

				ret = logicMap.GetAttackPermit(user, userBy, permit);
				if (ret != 0)
					return ret;
				if (!IsAllowAttack(permit))
				{
					string banMsg = "ban_attack_" + CTrans::ITOS(permit);
					LOGIC_ERROR_RETURN_MSG(banMsg.c_str());
				}

				//TIME_COUNT_LOG("[load main attack over]");
			}
			else
			{
				if(dataBaseExtra.last_breath_time == lasttime)
					reload = false;

				if(Time::GetGlobalTime() < dataBaseExtra.protected_time)
				{
					LOGIC_ERROR_RETURN_MSG("ban_attack_world_24_protected");
				}
				if (IsOnlineUser(dataBaseExtra.last_breath_time) && uid == dataBaseExtra.last_breath_uid)
				{
					result["online"] = 1;
					// LOGIC_ERROR_RETURN_MSG("user_online");
				}
				if (BEING_ATTACK == dataBaseExtra.being_attack_flag && IsBeingAttacked(dataBaseExtra.last_breath_time) && uidBy != dataBaseExtra.last_breath_uid)
				{
					LOGIC_ERROR_RETURN_MSG("being_attacked");
				}
				WORLD_ATTACK_LOG("attack|%u|%u|%u|%d|%d|",uidBy,uid,world_pos,dataBaseExtra.type,Time::GetGlobalTime() - dataBaseExtra.occupy_time);

				//TIME_COUNT_LOG("[load extra attack over]");
			}

			DataAlliance allianceBy;
			if (IsAllianceId(userBy.alliance_id))
			{
				ret = logicAlliance.GetAlliance(userBy.alliance_id, allianceBy);
				if(ret != 0)
				return ret;
			}
			else
			{
				allianceBy.alliance_id = ALLIANCE_ID_NULL;
				allianceBy.flag = 0;
			}
			CLogicAttack logicAttack;
			DataAttack attackData;
			attackData.attack_id = 0;
			attackData.attack_uid = uidBy;
			attackData.defence_uid = uid;
			attackData.worldpos = world_pos;
			attackData.attack_platform = OpenPlatform::GetType();
			attackData.attack_user_name = userBasicBy.name;
			attackData.attack_photo = userBasicBy.figure_url;
			attackData.attack_alliance_id = allianceBy.alliance_id;
			attackData.attack_alliance_name = allianceBy.name;
			attackData.attack_alliance_flag = allianceBy.flag;
			attackData.defence_platform = userBasic.platform;
			attackData.defence_user_name = userBasic.name;
			attackData.defence_photo = userBasic.figure_url;
			attackData.defence_alliance_id = alliance.alliance_id;
			attackData.defence_alliance_name = alliance.name;
			attackData.defence_alliance_flag = alliance.flag;
			attackData.start_time = 0;
			attackData.end_time = 0;
			attackData.r1_loot = 0;
			attackData.r2_loot = 0;
			attackData.r3_loot = 0;
			attackData.r4_loot = 0;
			attackData.r5_loot = 0;
			ret = logicAttack.AddAttack(attackData,0,isMainPos);
			if (ret != 0)
			return ret;
			result["attackid"] = Convert::UInt64ToString(attackData.attack_id);
			//更新联盟动态
			if(isMainPos)
			{
				if(attackData.attack_alliance_id != attackData.defence_alliance_id)
				{
					if(IsAllianceId(attackData.attack_alliance_id))
					{
						Json::Value attackActive;
						attackActive["type"] = "attack";
						attackActive["attackid"] = Convert::UInt64ToString(attackData.attack_id);
						attackActive["a_uid"] = attackData.attack_uid;
						attackActive["a_name"] = attackData.attack_user_name;
						attackActive["d_uid"] = attackData.defence_uid;
						attackActive["d_name"] = attackData.defence_user_name;
						if(IsAllianceId(attackData.defence_alliance_id))
						{
							attackActive["d_aid"] = attackData.defence_alliance_id;
							attackActive["d_aname"] = attackData.defence_alliance_name;
							attackActive["d_aflag"] = attackData.defence_alliance_flag;
						}
						attackActive["time"] = Time::GetGlobalTime();
						ret = logicAlliance.AddActivity(allianceBy, attackActive);
					}
					if(IsAllianceId(attackData.defence_alliance_id))
					{
						Json::Value defenceActive;
						defenceActive["time"] = Time::GetGlobalTime();
						defenceActive["a_uid"] = attackData.attack_uid;
						defenceActive["a_name"] = attackData.attack_user_name;
						if(IsAllianceId(attackData.attack_alliance_id))
						{
							defenceActive["a_aid"] = attackData.attack_alliance_id;
							defenceActive["a_aname"] = attackData.attack_alliance_name;
							defenceActive["a_aflag"] = attackData.attack_alliance_flag;
						}
						ret = logicAlliance.AddLastAttack(attackData.defence_alliance_id, attackData.defence_uid, defenceActive);

						defenceActive["d_uid"] = attackData.defence_uid;
						defenceActive["d_name"] = attackData.defence_user_name;
						defenceActive["type"] = "defence";
						defenceActive["attackid"] = Convert::UInt64ToString(attackData.attack_id);
						ret = logicAlliance.AddActivity(alliance, defenceActive);
					}
				}
				//设置连续进攻保护
				/*
				int beAttackedCount = 0;
				ret = logicAttack.GetConBeAttackedCount(uid, beAttackedCount);

				if (ret == 0 && beAttackedCount >= 4)
				{
					user.protected_time = Time::GetGlobalTime() + CON_PROTECT_TIME;
				}
				*/
				result["beAttackedCount"] = 0;//beAttackedCount;

				//设置攻击状态
				//20131107 Ralf last_save_uid -> last_load_save_uid : fix for bugs, can save only last load archieve
				user.last_save_uid = uidBy;
				//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
				user.last_breath_time = Time::GetGlobalTime();
				if(IsOnlineUser(user.last_active_time))
					user.protected_time = Time::GetGlobalTime() + ATTACK_PRO_TIME;
				ret = logicUser.SetUserLimit(uid, user, DATA_USER_LSUID|DATA_USER_LBT);
				if (ret != 0)
					return ret;
				//debug_log("[load attack operated=%u,operator=%u,last_breath_time=%u,]",uid, uidBy,user.last_breath_time);

				//取消攻击者保护
				if (IsInProtect(userBy.protected_time))
				{
					//ret = logicUser.UpdateProtectedTime(uidBy);
					userBy.protected_time = Time::GetGlobalTime();
				}
				//userBy.last_breath_time = 0; 20141225 ralf
				//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
				//userBy.last_save_uid = uid;
				userBy.bit_info = Time::GetGlobalTime();//Ralf20140225  后台增加pve或pvp保护 20140416 change to the time start pvp or pve by ralf
				//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长 20140416 change to the time start pvp or pve by ralf
				Json::Value worldres;
				if(!userBy.worldres.empty())
					reader.parse(userBy.worldres, worldres);
				worldres["r1"] = userBy.r1;
				worldres["r2"] = userBy.r2;
				worldres["r3"] = userBy.r3;
				worldres["r4"] = userBy.r4;
				worldres["r5"] = userBy.r5;
				worldres["bug"] = 0;
				userBy.worldres = writer.write(worldres);
				ret = logicUser.SetUser(uidBy, userBy, /*DATA_USER_LSUID|DATA_USER_LBT|*/DATA_USER_BI);
					if (ret != 0)
						return ret;
			}
			else
			{
				dataBaseExtra.last_breath_time = Time::GetGlobalTime();
				dataBaseExtra.last_breath_uid = uidBy;
				dataBaseExtra.being_attack_flag = BEING_ATTACK;
				ret = logicBaseExtra.SetBaseExtra(uid,world_pos,dataBaseExtra);
				if(0 != ret)
				{
					LOGIC_ERROR_RETURN_MSG("update_baseExtra_failed");
				}
				logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
			}

			//TIME_COUNT_LOG("[load attack over]");
		}//LT_ATTACK
		else if (loadType == LT_VIEW)
		{
			AttackPermitType permit = APT_ALLOW;
			if(isMainPos) // add by aaron
			{
				//20131107 Ralf last_save_uid -> last_load_save_uid : fix for bugs, can save only last load archieve
				//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
				if (IsBeingAttacked(user.last_breath_time))
				{
					//debug_log("[load view be attacked,operated=%u,operator=%u,last_breath_time=%u]",uid,uidBy,user.last_breath_time);
					LOGIC_ERROR_RETURN_MSG("being_attacked");
				}
				else
				{ //设置进攻许可
					CLogicMap logicMap;
					ret = logicMap.GetAttackPermit(user, userBy, permit);
					if (ret != 0)
						return ret;
				}
				CLogicTribute logicTribute;
				bool enable = false;
				logicTribute.IsEnableTribute(user, uidBy, enable);
				result["enable_tribute"] = enable?1:0;

				//TIME_COUNT_LOG("[load main view over]");
			}
			else
			{
				if (IsOnlineUser(dataBaseExtra.last_breath_time) && dataBaseExtra.uid == dataBaseExtra.last_breath_uid)
				{
					permit = APT_BAN_ONLINE;
					result["online"] = 1;
				}
				if (BEING_ATTACK == dataBaseExtra.being_attack_flag && IsBeingAttacked(dataBaseExtra.last_breath_time) && uidBy != dataBaseExtra.last_breath_uid)
				{
					permit = APT_BAN_BEING_ATTACK;
				}
				if(Time::GetGlobalTime() < dataBaseExtra.protected_time)
				{
					permit = APT_BAN_WORLD_PROTECT;
				}
				result["enable_tribute"] = 0;

				//TIME_COUNT_LOG("[load extra view over]");
			}
			result["attackpermitted"] = permit;
		}//LT_VIEW
		else if (loadType == LT_RANK)
		{
			string attacker,defender,attackername,defendername,win,lvl;
			String::Format(attacker, "%u", uidBy);
			String::Format(defender, "%u", uid);
			string url = "action=start";
			url.append("&attacker=").append(attacker);
			url.append("&defender=").append(defender);

			Json::Value temp;
			CLogicAllServerBaseMatch logicBaseMatch;
			ret = logicBaseMatch.RequestBaseMatch(url,temp,CONFIG_ALLS_RANK_PATH, true);
			if(ret)
				return ret;

			logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		}
		else if (loadType == LT_CHALLENGE)
		{
			// 在这里设置标志
			// NOT NPC
			// debug_log("start NOT NPC Challenge -- Cream");
			unsigned cid = 0;
			Json::GetUInt(data, "cid", cid);
			CLogicNewWorld logicNewWorld;
			ret = logicNewWorld.SetChallengeTS(cid, 1, userBy.kingdom);
			if (ret)
			{
				return ret;
			}

			CLogicSecinc logicSecinc;
			Json::Value zhulu;
			ret = logicSecinc.GetSecinc(uidBy, NAT_NEWWORLD_MISSION_2, zhulu);
			zhulu["a"] = 0;
			ret = logicSecinc.SetOneSecinc(uidBy, zhulu);
			if (ret)
			{
				return ret;
			}

			logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		}
		else if (loadType == LT_DRAGON)
		{
			if(!IsValidDragonballId(ballid))
			{
				LOGIC_ERROR_RETURN_MSG("dragonball_invalid");
			}
			if(!logicBall.EnableAttackForDragonball(ballid, userBy.level))
			{
				LOGIC_ERROR_RETURN_MSG("dragonball_level_protect");
			}
			if (IsDragonBallProtectFinished(ballts))
			{	//持有龙珠不足5分钟不能被攻击
				LOGIC_ERROR_RETURN_MSG("dragonball_protect");
			}
			logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		}
		else if (loadType == LT_BNW)
		{
			logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		}
		else if (loadType == LT_MVP)
		{
			logicUser.SetBitInfo(uidBy,Time::GetGlobalTime());
		}
		else if (loadType != LT_SPORTS)
		{
			if(isMainPos)
			{
				//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
				//20131107 Ralf last_save_uid -> last_load_save_uid : fix for bugs, can save only last load archieve
				if (IsBeingAttacked(user.last_breath_time))
				{
					//debug_log("[load other be attacked,operated=%u,operator=%u,last_breath_time=%u]",uid,uidBy,user.last_breath_time);
					LOGIC_ERROR_RETURN_MSG("being_attacked");
				}
			}
		}
	}//uid != uidBy

	if(reload)
	{
		result["reload"] = 1;

		if (isMainPos) {
			if(!user.glory.empty() && !reader.parse(user.glory, result["md"]))
			{
				error_log("[user.glory parse fail][uid=%u]",uid);
				DATA_ERROR_RETURN_MSG("parse_user.glory_fail");
			}

			//alliance
			if (IsAllianceId(user.alliance_id)) {
				Json::Value &allianceData = result["alliance"];
				allianceData["id"] = alliance.alliance_id;
				allianceData["name"] = alliance.name;
				allianceData["flag"] = alliance.flag;
				allianceData["level"] = alliance.level;
				Json::FromString(allianceData["data"], alliance.extra_data);
				Json::Value &memberData = allianceData["member"];
				memberData["type"] = allianceMember.type;
				memberData["point"] = Convert::UInt64ToString(allianceMember.point>0x7fffffff?0x7fffffff:allianceMember.point);
				Json::FromString(memberData["data"], allianceMember.extra_data);
			}
		}

#if DATA_NEW_WORLD_ENABLE == 0
		// 分基地load
		if (IsValidWorldPos(world_pos)) {
			logicWorld.GetUserInfo(world_pos, worldPoint);
			result["world_pos"]["type"] = worldPoint.map_flag;
			result["world_pos"]["world_pos"] = world_pos;
		} else {
			result["world_pos"]["type"] = USER_MAIN_CITY;
			result["world_pos"]["world_pos"] = 0;
		}
#else
		result["world_pos"]["type"] = USER_MAIN_CITY;
		result["world_pos"]["world_pos"] = world_pos;
#endif
		//下面为共同load部分
		result["userid"] = uid;

		//user basic
		result["name"] = userBasic.name;
		result["pic"] = userBasic.figure_url;
		result["viptype"] = userBasic.vip_type;
		result["viplevel"] = userBasic.vip_level;
		int level_3366 = 1;
		string level_name_3366;
		int grow_level_3366 = 1;
		int grow_value_3366 = 1;
		if (!userBasic.extra.empty())
		{
			Json::Value extraJson;
			if (reader.parse(userBasic.extra, extraJson))
				{
					Json::GetInt(extraJson, "3366_level", level_3366);
					Json::GetString(extraJson, "3366_level_name", level_name_3366);
					Json::GetInt(extraJson, "3366_grow_level", grow_level_3366);
					Json::GetInt(extraJson, "3366_grow_value", grow_value_3366);
				}
			else
				error_log("[userBasic.extra parse fail][uid=%u]",uid);
		}
		result["level_3366"] = level_3366;
		result["level_name_3366"] = level_name_3366;
		result["grow_level_3366"] = grow_level_3366;
		result["grow_value_3366"] = grow_value_3366;
		result["pt"] = (int)OpenPlatform::GetType();//userBasic.platform;
		//user
		result["kingdom"] = user.kingdom;
		result["job"] = user.status;
		result["sstate"] = user.sstate;
		result["bnwm"] = user.type;
		result["register_time"] = user.register_time;
		result["register_platform"] = user.register_platform;
		result["invite_count"] = user.invite_count;
		result["today_invite_count"] = user.today_invite_count;
		result["level"] = user.level;
		result["exp"] = Convert::UInt64ToString(user.point);
		result["tutorialstage"] = user.tutorial_stage;
		result["resources"].resize(5);
		result["resources"][(unsigned) 0]["c"] = user.r1>user.r1_max?user.r1_max:user.r1;
		result["resources"][(unsigned) 0]["m"] = user.r1_max;
		result["resources"][(unsigned) 1]["c"] = user.r2>user.r2_max?user.r2_max:user.r2;
		result["resources"][(unsigned) 1]["m"] = user.r2_max;
		result["resources"][(unsigned) 2]["c"] = user.r3>user.r3_max?user.r3_max:user.r3;
		result["resources"][(unsigned) 2]["m"] = user.r3_max;
		result["resources"][(unsigned) 3]["c"] = user.r4>user.r4_max?user.r4_max:user.r4;
		result["resources"][(unsigned) 3]["m"] = user.r4_max;
		result["resources"][(unsigned) 4]["c"] = 0;
		result["resources"][(unsigned) 4]["m"] = 0;
		result["r5"] = user.r5;
		result["r5_max"] = user.r5_max;
		result["currencys"][(unsigned) 0] = user.gcbase;
		result["currencys"][(unsigned) 1] = user.gcbuy;
		result["currencys"][(unsigned) 2] = user.prosper;
		result["currencys"][(unsigned) 3] = user.battle_spirits;
		result["lasttime"] = isMainPos?user.last_save_time:dataBaseExtra.last_breath_time;
		result["newgcbase"] = user.newgcbase;
		result["protected_time"] = user.protected_time;
		result["lastseq"] = user.lastseq;
		result["game_vip_level"] = user.viplevel;
		result["refresh"] = user.refresh;
		result["memory"] = user.memory;
		if (isMainPos) {
			if (!user.barrackQ.empty()
					&& !reader.parse(user.barrackQ, result["barrackQ"])) {
				error_log("[barrackQ parse error][uid=%u]", uid);
				DATA_ERROR_RETURN_MSG("parse_barrackQ_fail");
			}
			if (!user.buildQ.empty()
					&& !reader.parse(user.buildQ, result["buildQ"])) {
				error_log("[buildQ parse error][uid=%u]", uid);
				//DATA_ERROR_RETURN_MSG("parse_buildQ_fail");
			}
			if (!user.skillQ.empty()
					&& !reader.parse(user.skillQ, result["skillQ"])) {
				error_log("[skillQ parse error][uid=%u]", uid);
				DATA_ERROR_RETURN_MSG("parse_skillQ_fail");
			}
			if (!user.trainQ.empty()
					&& !reader.parse(user.trainQ, result["trainQ"])) {
				error_log("[trainQ parse error][uid=%u]", uid);
				DATA_ERROR_RETURN_MSG("parse_trainQ_fail");
			}
		}
		if (!user.vipstat.empty()
				&& !reader.parse(user.vipstat, result["game_vip_state"])) {
			error_log("[user game_vip_state parse error][uid=%u]", uid);
			DATA_ERROR_RETURN_MSG("parse_game_vip_state_fail");
		}

		if (!user.user_tech.empty()
				&& !reader.parse(user.user_tech, result["tech"])) {
			error_log("[user user_tech parse error][uid=%u]", uid);
			DATA_ERROR_RETURN_MSG("parse_user_tech_fail");
		}

		if (!user.soldier.empty()
				&& !reader.parse(user.soldier, result["soldier"])) {
			error_log("[soldier parse error][uid=%u]", uid);
			DATA_ERROR_RETURN_MSG("parse_soldier_fail");
		}
		if (!user.soldierlevel.empty()
				&& !reader.parse(user.soldierlevel, result["soldierlevel"])) {
			error_log("[soldierlevel parse error][uid=%u]", uid);
			DATA_ERROR_RETURN_MSG("parse_soldierlevel_fail");
		}
		if (!user.wf_status.empty()
				&& !reader.parse(user.wf_status, result["wf_status"])) {
			error_log("[wf_status parse error][uid=%u]", uid);
			DATA_ERROR_RETURN_MSG("parse_wf_status_fail");
		}

		if (user.alliance_tech.empty()) {
			string allianceTech("{\"techLv\":[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]}");
			if (!reader.parse(allianceTech, result["alliance_tech"])) {
				error_log("[user alliance_tech parse error][uid=%u]", uid);
				DATA_ERROR_RETURN_MSG("parse_alliance_tech_fail");
			}
		} else {
			if (!reader.parse(user.alliance_tech, result["alliance_tech"])) {
				error_log("[user alliance_tech parse error][uid=%u]", uid);
				DATA_ERROR_RETURN_MSG("parse_alliance_tech_fail");
			}
		}

		//TIME_COUNT_LOG("[user over]");

		CLogicUpdates logicUpdates;
		ret = logicUpdates.GetUpdates(uid, result["updates"]["data"], uid != uidBy);
		if (ret != 0)
			return ret;

		//TIME_COUNT_LOG("[updates over]");

		//building
		CLogicBuilding logicBuiding;

		ret = logicBuiding.GetBuilding(uid, world_pos, result["baseop"], isMainPos);
		if (ret != 0)
			return ret;

		//TIME_COUNT_LOG("[building over]");

		//hero
		CLogicHero logicHero;
		ret = logicHero.GetHero(uid, result["hero"]);
		if (ret != 0)
			return ret;

		//TIME_COUNT_LOG("[hero over]");

		//equipment
		CLogicEquipment logicEquip;
		ret = logicEquip.GetEquipment(uid, uidBy, result["equipment"]);
		if (ret != 0)
			return ret;

		//TIME_COUNT_LOG("[equipment over]");

		result["npc"] = 0;
		result["friend"] = isFriend ? 1 : 0;
		result["coins"] = payData.coins;	//金币
		result["coins2"] = payData.cash;	//钻石
	}//reload
	else
		result["reload"] = 0;

	//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
	logicUser.UpdateActiveExtBreathTime(uidBy, userBy.last_active_time,	userBy.ext);

	//TIME_COUNT_LOG("[load over]");

	return 0;
}

int CLogicArchive::Save(unsigned uid, unsigned uidBy, const string &type,Json::Value &data, Json::Value &result)
{
	//TIME_COUNT_RESTART("[save start]");

	LoadType loadType = GetLoadType(type);
	if((uid == uidBy && !IsSelfType(loadType))
	|| (uid != uidBy && !IsOtherType(loadType))
	|| (IsValidUid(uid) && loadType == LT_SPORTS))
	{
		REFUSE_RETURN_MSG("load_type_error");
	}

	CLogicTopTenUser logicTopTenUser;
	int ret = 0;
	Json::Reader reader;
	Json::FastWriter writer;
	CLogicBaseExtra logicBaseExtra;
	DataPay payData;
	CLogicPay logicPay;
	DataUser userBy;
	CLogicUser logicUser;
	unsigned flagUser = 0;
	Json::Value userFlag;
	bool bsave = false;
	bool res = true;

	if (data.isMember("nonage"))//20140411 ralf 增加沉迷自己的接口
	{
		unsigned nonage = 0;
		Json::GetUInt(data, "nonage", nonage);
		if(nonage)
		{
			DataUserBasic userBasic;
			CDataUserBasic dbUser;
			ret = dbUser.GetUserBasicExt(uidBy, OpenPlatform::GetType(),userBasic);
			if (ret == 0)
			{
				Json::Value extra;
				Json::FastWriter writer;
				Json::Reader reader;
				if (!userBasic.extra.empty())
					reader.parse(userBasic.extra, extra);
				extra["nng"] = nonage;
				userBasic.extra = writer.write(extra);
				dbUser.SetUserBasicExt(uidBy, OpenPlatform::GetType(), userBasic);
			}
		}
	}

	AUTO_LOCK_SAVE_USER(uid,loadType)
	ret = logicUser.GetUser(uidBy, userBy, uidBy);
	if (ret != 0)
		return ret;
	if(!userBy.user_flag.empty() && !reader.parse(userBy.user_flag, userFlag))
	{
		error_log("parse user flag error uid=%u",uid);
		return R_ERR_DATA;
	}

	if (IsBeingAttacked(userBy.last_breath_time))
	{
		//error_log("[being_attacked][userBy=%u,last_breath_time=%u]",uidBy,userBy.last_breath_time);
		LOGIC_ERROR_RETURN_MSG("u_being_attacked");
	}
	/*
	//20131107 Ralf last_save_uid -> last_load_save_uid : fix for bugs, can save only last load archieve
	if(userBy.last_save_uid != uid)
	{
		error_log("[last_save_uid_mismatch][operated=%u,operator=%u,userBy_last_save_uid=%u]",uid, uidBy, userBy.last_save_uid);
		LOGIC_ERROR_RETURN_MSG("last_save_uid_mismatch");
	}
	*/

	logicUser.UpdateActiveExtBreathTime(uidBy, userBy.last_active_time,	userBy.ext);
	//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
	/*20140416 change to the time start pvp or pve by ralf*/
	int attackend = 0;
	int damage = 0, damage2 = 0;
	//int battletime = 0;
	Json::GetInt(data, "attackend", attackend);
	Json::GetInt(data, "damage", damage);
	Json::GetInt(data, "damage2", damage2);
	if(attackend && userBy.bit_info)
	{
		/*
		battletime = Time::GetGlobalTime()-userBy.bit_info;
		BATTLE_LOG("uid=%u,battle=%u,time=%d",uidBy,uid,battletime);
		*/
		logicUser.SetBitInfo(uidBy,0);
		userBy.bit_info = 0;
	}

	ret = logicPay.GetPay(uidBy, payData);
	if (ret != 0)
		return ret;

	//TIME_COUNT_LOG("[get_loader_breath_pay over]");

	if (!IsValidUid(uid))
	{
		ret = ProcessOrders(uidBy, data, payData,false,userFlag,bsave);
		if (ret != 0)
			return ret;
		if(bsave)
		{
			ret = logicUser.SetUserFlag(uidBy,userFlag);
			if(ret)
				return ret;
		}

		/*********20140417 ralf check damage pve**************/
		if (IsValidFightingId(uid)) {
			CLogicFighting logicFighting;
			ret = logicFighting.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save fight over]");
			return 0;
		}
		if (IsValidArenaId(uid)) {
			CLogicArena logicArena;
			ret = logicArena.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save arena over]");
			return 0;
		}
		if (IsValidFightArenaId(uid)) {
			CLogicFightArena logicFight;
			ret = logicFight.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save fight arena over]");
			return 0;
		}
		if (IsValidWorldBossId(uid)) {
			CLogicWorldBoss logicWorldBoss;
			ret = logicWorldBoss.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save world boss over]");
			return 0;
		}
		if (IsValidNianShouId(uid)) {
			CLogicNianShou logicNianShou;
			ret = logicNianShou.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save world boss over]");
			return 0;
		}
		//allianceBoss
		if (IsValidAllianceBossId(uid)) {
			CLogicAllianceBoss logicAllianceBoss;
			ret = logicAllianceBoss.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save alliance world boss over]");
			return 0;
		}
		if (IsValidAllianceBattleId(uid)) {
			CLogicAllianceBattle logicAllianceBattle;
			ret = logicAllianceBattle.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			return 0;
		}

		/*********20140417 ralf check time pve**************
		if(damage>99 && attackend && battletime<=4 && !(uid<25 || (uid>200 && uid<=350)))
		{
			error_log("[battle too short][uid=%u,battle=%u,time=%u]",uidBy,uid,battletime);
			LOGIC_ERROR_RETURN_MSG("????");
		}
		*/

		if (IsNPCUid(uid)) {
//			debug_log("NPC end Challenge -- Cream");
			CLogicNpc logicNpc;
			ret = logicNpc.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//result["lasttime"] = Time::GetGlobalTime();
			//TIME_COUNT_LOG("[save npc over]");
			return 0;
		}
		if (IsValidInstanceId(uid)) {
			CLogicInstance logicInstance;
			ret = logicInstance.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save instance over]");
			return 0;
		}
		if (IsValidBMatchInstId(uid)) {
			CLogicBaseMatch logicBaseMatch;
			ret = logicBaseMatch.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save base match over]");
			return 0;
		}
		if (IsValidAllServerBMatchInstId(uid)) {
			CLogicAllServerBaseMatch logicBaseMatch;
			ret = logicBaseMatch.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save all server base match over]");
			return 0;
		}
		if (IsValidPersonMatchId(uid)) {
			CLogicBaseMatch logicBaseMatch;
			ret = logicBaseMatch.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save person match over]");
			return 0;
		}
		if (IsValidAllServerPersonMatchId(uid)) {
			CLogicAllServerBaseMatch logicBaseMatch;
			ret = logicBaseMatch.Save(uid, userBy, data, result, loadType);
			if (ret != 0)
				return ret;
			//TIME_COUNT_LOG("[save all server person match over]");
			return 0;
		}

		REFUSE_RETURN_MSG("invalid_uid");
	}//!IsValidUid(uid)

	//for quest_reward
	XMLQuestReward reward_res;
	Json::Value newEqDatas = Json::Value(Json::arrayValue);
	vector<string> reward_hero;
	reward_hero.clear();
	result["resources"].resize(5);
	//*************************

	DataUser user;
	if (uid == uidBy)
		user = userBy;
	else
	{
		ret = logicUser.GetUser(uid, user, uidBy);
		if (ret != 0)
			return ret;
	}

	//TIME_COUNT_LOG("[get_be_loader over]");

	// add by aaron 20121030
	int _r1chg = 0, _r2chg = 0, _r3chg = 0, _r4chg = 0;
	int r1chg = 0, r2chg = 0, r3chg = 0, r4chg = 0, r5chg = 0;
	int gcbaschg = 0, gcbuychg = 0, addprosper = 0, addbs = 0, itemp = 0;
	int qleold = -1, qlechg = 0, qleres = -1;
	int ylold = -1, ylchg = 0, ylres = -1;
	int betold = -1, betchg = 0, betres = -1;
	int exp = 0;
	int gate_reward = 0, gate_cost = 0;
	string rcode;
	if(data.isMember("rcode"))
		rcode = data["rcode"].asString();
	DataRank rank;
	rank.uid = uid;

	unsigned fcm = 0;
	Json::GetUInt(data,"fcm",fcm);
	if(fcm >= e_fcm_max)
		return R_ERR_PARAM;

	bool isMainPos = true;
	unsigned world_pos;
	if (!Json::GetUInt(data, "world_pos", world_pos) || world_pos == 0) {
		world_pos = user.mainpos;
	}
	// 默认主城坐标
	isMainPos = ((world_pos == 0 || world_pos == user.mainpos) ? true : false);
	if (isMainPos)
	{
		if(!IsVision(loadType))
		{
			//20131107 Ralf last_save_uid -> last_load_save_uid : fix for bugs, can save only last load archieve
			if(user.last_save_uid != uidBy)
			{
				error_log("[last_save_uid_mismatch][operated=%u,operator=%u,user_last_save_uid=%u]", uid, uidBy, user.last_save_uid);
				LOGIC_ERROR_RETURN_MSG("last_save_uid_mismatch");
			}

			unsigned lasttime = 0;
			unsigned seqid = 0;
			Json::GetUInt(data, "seqid", seqid);
			Json::GetUInt(data, "lastime", lasttime);
			if (lasttime != user.last_save_time || seqid != user.lastseq + 1)
			{
				result["lasttime"] = user.last_save_time;
				result["lastseq"] = user.lastseq;
				result["saveuserid"] = uid;

				unsigned retry = 0;
				if(Json::GetUInt(data, "retry", retry) && retry)
				{
					error_log("[retry_mismatch][operated=%u,operator=%u,lasttime=%u,last_save_time=%u,seqid=%u,lastseq=%u]",
							uid, uidBy, lasttime, user.last_save_time, seqid, user.lastseq);
					return 0;
				}

				error_log(
						"[lasttime_mismatch][operated=%u,operator=%u,lasttime=%u,last_save_time=%u,seqid=%u,lastseq=%u]",
						uid, uidBy, lasttime, user.last_save_time, seqid, user.lastseq);
				//LOGIC_ERROR_RETURN_MSG("lasttime_mismatch");
				return 0;
			}
		}//loadType != LT_RANK && loadType != LT_CHALLENGE

		//差异部分
		if (uid != uidBy)
		{
			if(loadType == LT_RANK)
			{
				if(attackend)
				{
					//nothing
				}
				else if(userBy.bit_info && (Time::GetGlobalTime()>RANK_ATTACK_MAX_TIME+userBy.bit_info))//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
				{
					//lose
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
				else
				{
					if(userBy.bit_info == 0)
					{
						userBy.bit_info = Time::GetGlobalTime();
						logicUser.SetBitInfo(uidBy, userBy.bit_info);
					}
					//nothing
				}

				ret = ProcessOrders(uidBy, data, payData,false,userFlag,bsave);
				if (ret != 0)
					return ret;
				if(bsave)
				{
					ret = logicUser.SetUserFlag(uidBy,userFlag);
					if(ret)
						return ret;
				}

				if (attackend) {
					//over
					string attacker,defender,attackername,defendername,win,lvl;
					String::Format(attacker, "%u", uidBy);
					String::Format(defender, "%u", uid);
					String::Format(win, "%u", damage>99?1:0);
					String::Format(lvl, "%u", userBy.level);
					CLogicUserBasic logicUserBasic;
					DataUserBasic userBasic,userByBasic;
					logicUserBasic.GetUserBasicLimit(uid, OpenPlatform::GetType(),userBasic);
					logicUserBasic.GetUserBasicLimit(uidBy, OpenPlatform::GetType(),userByBasic);
					attackername = userByBasic.name;
					defendername = userBasic.name;
					string url = "action=over";
					url.append("&attacker=").append(attacker);
					url.append("&defender=").append(defender);
					url.append("&win=").append(win);
					url.append("&lvl=").append(lvl);
					url.append("&attackername=").append(attackername);
					url.append("&defendername=").append(defendername);

					Json::Value temp;
					CLogicAllServerBaseMatch logicBaseMatch;
					ret = logicBaseMatch.RequestBaseMatch(url,temp,CONFIG_ALLS_RANK_PATH, true);
					if(ret == 0)
					{
						Json::Value userByTech;
						int score = 0;
						Json::GetInt(temp,"score",score);
						if(!userBy.user_tech.empty() && reader.parse(userBy.user_tech, userByTech))
						{
							userByTech["rank"]["score"] = score;
							logicUser.SetUserTech(uidBy, userByTech);
						}
					}
				}
			}//loadType == LT_RANK
			else if(loadType == LT_CHALLENGE)
			{
				if(attackend)
				{
				}
				else if(IsAttackFinished(userBy.bit_info) && userBy.bit_info)//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
				{
					//lose
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
				else
				{
					if(userBy.bit_info == 0)
					{
						userBy.bit_info = Time::GetGlobalTime();
						logicUser.SetBitInfo(uidBy, userBy.bit_info);
					}
					//nothing
				}

				ret = ProcessOrders(uidBy, data, payData,false,userFlag,bsave);
				if (ret != 0)
					return ret;
				if(bsave)
				{
					ret = logicUser.SetUserFlag(uidBy,userFlag);
					if(ret)
						return ret;
				}

				if (attackend && damage > 99) {
					//challenge win
					unsigned cid = 0;
					Json::GetUInt(data,"cid",cid);
					CLogicUserBasic logicUserBasic;
					DataUserBasic userByBasic;
					logicUserBasic.GetUserBasicLimit(uidBy, OpenPlatform::GetType(),userByBasic);
					CLogicNewWorld logicNewWorld;
					unsigned olduid = uid;
					string oldname = userByBasic.name;
					DataAlliance alliance;
					CLogicAlliance logicAlliance;
					ret = logicAlliance.GetAlliance(userBy.alliance_id, alliance);
					if (ret == 0)
					{
						oldname = alliance.name + "-" + oldname;
					}
					logicNewWorld.Challenge(uidBy,olduid,cid,oldname,userBy.kingdom);
					result["cityuid"] = olduid;
					result["cityname"] = oldname;
				}
				else if (attackend)
				{
					unsigned cid = 0;
					Json::GetUInt(data,"cid",cid);
					CLogicNewWorld logicNewWorld;
					logicNewWorld.SetChallengeTS(cid, 0, userBy.kingdom);

				}
			}//loadType == LT_CHALLENGE
			else if(loadType == LT_DRAGON)
			{
				if(attackend)
				{
					//nothing
				}
				else if(IsAttackFinished(userBy.bit_info) && userBy.bit_info)//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
				{
					//lose
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
				else
				{
					if(userBy.bit_info == 0)
					{
						userBy.bit_info = Time::GetGlobalTime();
						logicUser.SetBitInfo(uidBy, userBy.bit_info);
					}
					//nothing
				}

				ret = ProcessOrders(uidBy, data, payData,false,userFlag,bsave);
				if (ret != 0)
					return ret;
				if(bsave)
				{
					ret = logicUser.SetUserFlag(uidBy,userFlag);
					if(ret)
						return ret;
				}

				//龙珠活动
				CLogicDragonball logicBall;
				if (attackend && damage > 99 && logicBall.IsDragonballActivityTs() == DragonballActivityStatus_attack)
				{
					unsigned ballId = 0;
					unsigned ballts = 0;
					result["ballId"] = 0;
					if (logicBall.WhichDragonballHold(uid, ballId, ballts, DragonballActivityStatus_attack) == 0
					&& IsValidDragonballId(ballId)
					&& logicBall.EnableAttackForDragonball(ballId,userBy.level))
					{
						DataUserBasic userBasicBy;
						CLogicUserBasic logicUserBasic;
						logicUserBasic.GetUserBasicLimit(uidBy,	OpenPlatform::GetType(), userBasicBy);
						unsigned balluid = uid;
						string ballname = userBasicBy.name;
						logicBall.SnatchDragonball(ballId, uidBy, ballname, balluid);
						result["balluid"] = balluid;
						result["ballname"] = ballname;
					}
				}
			}//loadType == LT_DRAGON
			else if(loadType == LT_BNW)
			{
				if(attackend)
				{
					//nothing
				}
				else if(userBy.bit_info && (Time::GetGlobalTime()>BNW_ATTACK_MAX_TIME+userBy.bit_info))//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
				{
					//lose
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
				else
				{
					if(userBy.bit_info == 0)
					{
						userBy.bit_info = Time::GetGlobalTime();
						logicUser.SetBitInfo(uidBy, userBy.bit_info);
					}
					//nothing
				}

				ret = ProcessOrders(uidBy, data, payData,false,userFlag,bsave);
				if (ret != 0)
					return ret;
				if(bsave)
				{
					ret = logicUser.SetUserFlag(uidBy,userFlag);
					if(ret)
						return ret;
				}
			}//loadType == LT_BNW
			else if(loadType == LT_MVP)
			{
				if(attackend)
				{
					//nothing
				}
				else if(userBy.bit_info && (Time::GetGlobalTime()>MVP_ATTACK_MAX_TIME+userBy.bit_info))//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
				{
					//lose
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
				else
				{
					if(userBy.bit_info == 0)
					{
						userBy.bit_info = Time::GetGlobalTime();
						logicUser.SetBitInfo(uidBy, userBy.bit_info);
					}
					//nothing
				}

				ret = ProcessOrders(uidBy, data, payData,false,userFlag,bsave);
				if (ret != 0)
					return ret;
				if(bsave)
				{
					ret = logicUser.SetUserFlag(uidBy,userFlag);
					if(ret)
						return ret;
				}
			}//loadType == LT_MVP
			else
			{
				//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
				if(attackend)
				{
					user.last_breath_time = Time::GetGlobalTime() - ATTACK_TIMEOUT - 5;
					flagUser |= DATA_USER_LBT;
				}
				else if(IsAttackFinished(userBy.bit_info) && userBy.bit_info)//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
				{
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
				else
				{
					if(userBy.bit_info == 0)
					{
						userBy.bit_info = Time::GetGlobalTime();
						logicUser.SetBitInfo(uidBy, userBy.bit_info);
					}

					user.last_breath_time = Time::GetGlobalTime();
					flagUser |= DATA_USER_LBT;
				}

				ret = ProcessOrders(uidBy, data, payData,false,userFlag,bsave);
				if (ret != 0)
					return ret;
				if(bsave)
				{
					ret = logicUser.SetUserFlag(uidBy,userFlag);
					if(ret)
						return ret;
				}

				if (damage || damage2)	//	受损保护
				{
					if (damage > 100)
						damage = 100;
					if (damage2 > 100)
						damage2 = 100;

					Json::Value worldres;
					if(!user.worldres.empty())
						reader.parse(user.worldres, worldres);
					unsigned lpt = 0, pt = 0;
					unsigned tokencount = 1;
					Json::GetUInt(worldres,"lpt",lpt);
					Json::GetUInt(worldres,"pt",pt);
					Json::GetUInt(worldres, "tokencount", tokencount);
					if(CTime::GetDayInterval(lpt, Time::GetGlobalTime()) != 0)
					{
						pt = 0;
						tokencount = 1;
					}

					unsigned protectedTime = SetProtectedTime(user.level, damage, damage2, pt);
					//debug_log("protectedTime=%u", protectedTime);
					if(protectedTime && Time::GetGlobalTime() + protectedTime > user.protected_time)
					{
						if (user.protected_time > Time::GetGlobalTime())
							pt += protectedTime - (user.protected_time - Time::GetGlobalTime());
						else
							pt +=  protectedTime;
						user.protected_time = Time::GetGlobalTime() + protectedTime;
						lpt = Time::GetGlobalTime();
						worldres["lpt"] = lpt;
						worldres["pt"] = pt;
						worldres["tokencount"] = tokencount;
						user.worldres = writer.write(worldres);
						//debug_log("user.protected_time=%u, pt=%u", user.protected_time, pt);
					}

					if (attackend) {
						if (IsAllianceId(userBy.alliance_id)
								&& userBy.alliance_id != user.alliance_id) {
							CLogicAlliance logicAlliance;
							ret = logicAlliance.AddAttackPoint(userBy.alliance_id,
									uidBy, data, userBy.level);
						}
						logicTopTenUser.SetUserPlunder(uidBy, uid);
					}
				}
				//debug_log("[save attack,operated=%u,operator=%u,last_breath_time=%u,attackend=%d]",uid,uidBy,user.last_breath_time,attackend);

				//TIME_COUNT_LOG("[main_other over]");
			}//loadType == else
		}//uid != uidBy
		else
		{
			int isbattle = 0;//Ralf20140225  后台增加pve或pvp保护 20140416 change to the time start pvp or pve by ralf
			Json::GetInt(data, "isbattle", isbattle);
			if((isbattle == 1 || loadType == LT_DEFEND) && user.bit_info == 0)//Ralf20140821 fix just for start once
			{
				user.bit_info = Time::GetGlobalTime();
				flagUser |= DATA_USER_BI;
			}
			else if(loadType == LT_DEFEND && IsDefendFinished(user.bit_info))
			{
				LOGIC_ERROR_RETURN_MSG("defend_too_long");
			}
			else if(loadType != LT_DEFEND && user.bit_info)
			{
				//BATTLE_LOG("uid=%u,battle=%u,time=%u",uid,uid,Time::GetGlobalTime()-user.bit_info);
				user.bit_info = 0;
				flagUser |= DATA_USER_BI;
			}

			ret = ProcessOrders(uidBy, data, payData,true,userFlag,bsave);
			if (ret != 0)
				return ret;
			if(bsave)
				user.user_flag = writer.write(userFlag);

			//处理任务和关卡奖励
			if (data.isMember("questreward")) {

				//添加主线任务闯关翻牌的校验
				if ((ret = CheckQuestRewardValid(uid, user, data, gate_reward)) != R_SUCCESS && user.level > 30)
				{
					LOGIC_ERROR_RETURN_MSG("quest_reward_invalid");
					error_log("quest_reward_invalid. uid=%d,ret=%d", uid, ret);
					return ret;
				}

				CLogicCMD logiccmd;
				logiccmd.QuestReward(uid, data["questreward"],reward_res,newEqDatas,reward_hero);
				if (reward_res.gol != 0 || reward_res.cas != 0) {
					ret = logicPay.ChangePay(uid, reward_res.cas, reward_res.gol, "QUEST_REWARD", payData);
					if (0 != ret) {
						return ret;
					}
				}
			}
			reward_res.hex = (int)(reward_res.hex * FCM_VALUE[fcm]);
			reward_res.gol = (int)(reward_res.gol * FCM_VALUE[fcm]);
			reward_res.cas = (int)(reward_res.cas * FCM_VALUE[fcm]);
			reward_res.exp = (int)(reward_res.exp * FCM_VALUE[fcm]);
			reward_res.ene = (int)(reward_res.ene * FCM_VALUE[fcm]);
			reward_res.sou = (int)(reward_res.sou * FCM_VALUE[fcm]);
			reward_res.pro = (int)(reward_res.pro * FCM_VALUE[fcm]);
			for(int i=0;i<MAX_RES;i++)
				reward_res.rs[i] = (int)(reward_res.rs[i] * FCM_VALUE[fcm]);
			if(fcm != e_fcm_normal)
			{
				newEqDatas.clear();
				reward_hero.clear();
			}


			if (data.isMember("barbarreward"))
			{
				CLogicCMD logicCMD;
				ret = logicCMD.GetBarbarReward(uid, data["barbarreward"], result["barbarreward"]);
				if (ret)
				{
					return ret;
				}
			}

			if (data.isMember("fivereward"))
			{
				CLogicCMD logicCMD;
				ret = logicCMD.GetFiveTigerReward(uid, user.user_tech, data["fivereward"], result["fivereward"]);
				if (ret)
				{
					return ret;
				}
			}

			if (data.isMember("amicablenpcid")) {
				CLogicInstance dbInstance;
				unsigned npcid = data["amicablenpcid"].asUInt();
				ret = dbInstance.RemoveInstance(uid, npcid);
				if (0 != ret) {
					error_log("amicable npc failed ,uid = %u,npcid = %u", uid,
							npcid);
					return ret;
				}
			}
			//自己保存自己

			/* 2014901 Ralf change to save activity
			   if (Json::IsArray(data, "secinc"))
			   {
					CLogicSecinc logicSecinc;
					ret = logicSecinc.ProcessSecinc(uid, data["secinc"]);
					if (ret != 0)
						return ret;
				}
			*/
			if (Json::IsArray(data, "newAct"))
		    {
				CLogicSecinc logicSecinc;
				ret = logicSecinc.SetSecinc(uid, data["newAct"]);
				if (ret != 0)
					return ret;
			}

			/*挪后端了
			//朝贡
			if (Json::IsArray(data, "tributes")) {
				CLogicTribute logicTribute;
				ret = logicTribute.ProcessTribute(uid, data["tributes"]);
				if (ret != 0)
					return ret;
			}
			*/

			CLogicUserData logicUserData;
			if (data.isMember("npcattack")) {
				ret = logicUserData.SetNpcattack(uid, data["npcattack"]);
				if (ret != 0)
					return ret;
			}
			if (data.isMember("gift")) {
				Json::Value gift;
				ret = logicUserData.GetGift(uid, gift);
				if(ret == 0)
				{
					const unsigned kk = 8;
					const char* k[] = {"charge", "qiri","boughtfund","fund","fundlog","level","pay","lInvite"};
					for(unsigned j=0;j<kk;++j)
					{
						if(gift.isMember(k[j]))
							data["gift"][k[j]] = gift[k[j]];
					}
				}
				ret = logicUserData.SetGift(uid, data["gift"]);
				if (ret != 0)
					return ret;
			}
			if (data.isMember("dailyquest")) {
				ret = logicUserData.SetDailyQuest(uid, data["dailyquest"]);
				if (ret != 0)
					return ret;
			}
			//quest
			if (Json::IsArray(data, "quest")) {
				CLogicQuest logicQuest;
				ret = logicQuest.UpdateQuest(uid, data["quest"]);
				if (ret != 0)
					return ret;
			}
			//gate
			if (Json::IsArray(data, "gate")) {
				CLogicGate logicGate;
				ret = logicGate.UpdateGate(uid, data["gate"]);
				if (ret != 0)
					return ret;
			}
			if (Json::IsArray(data, "wf_status")) {
				user.wf_status = writer.write(data["wf_status"]);
			}
			//add by aaron for barbarian 20130110
			int barbarianPoint = 0;
			if (Json::GetInt(data, "barbarianpoint",barbarianPoint)
			&& barbarianPoint != 0 && IsAllianceId(user.alliance_id)) {
				int barbarianlevel = 0;
				Json::GetInt(data, "barbarianlevel",barbarianlevel);

				static CLogicBarbarianInvasion logicBarbarianInvasion;
				DataPlayerItem playerItem;
				memset(&playerItem, 0x00, sizeof(DataPlayerItem));
				CLogicUserBasic logicUserBasic;
				DataUserBasic userBasic;
				logicUserBasic.GetUserBasicLimit(uid, OpenPlatform::GetType(),
						userBasic);
				playerItem.uid = uid;
				playerItem.points = barbarianPoint;
				playerItem.rewardCash = barbarianlevel;
				memcpy(playerItem.name, userBasic.name.c_str(),
						sizeof(playerItem.name) - 1);
				logicBarbarianInvasion.UpdateRank(playerItem, user.alliance_id);
				DataPlayersPoints playersRank;
				memset(&playersRank, 0x00, sizeof(DataPlayersPoints));
				DataTeamItem teamRank[512];
				memset(teamRank, 0x00, sizeof(teamRank));
				int teamNum = 0;
				int i = 0;
				logicBarbarianInvasion.GetTeamPlayersRank(playersRank,
						user.alliance_id);
				logicBarbarianInvasion.GetTeamRank(teamRank, teamNum);
				for (i = 0; i < playersRank.playerNum; i++) {
					result["barbairanplayersrank"][i]["uid"] = playersRank.players[i].uid;
					result["barbairanplayersrank"][i]["points"] = playersRank.players[i].points;
					result["barbairanplayersrank"][i]["name"] =	playersRank.players[i].name;
					result["barbairanplayersrank"][i]["level"] =	playersRank.players[i].rewardCash;
				}
				for (i = 0; i < teamNum; i++) {
					result["barbairanteamrank"][i]["aid"] = teamRank[i].aid;
					result["barbairanteamrank"][i]["kingdom"] = teamRank[i].kingdom;
					result["barbairanteamrank"][i]["teampoints"] =
							teamRank[i].teamPoints;
					result["barbairanteamrank"][i]["name"] = teamRank[i].aname;
				}
			}
			//add by ralf 20140403 for barbarian king
			int barbarianingpoint = 0;
			if (Json::GetInt(data, "barbarianingpoint",
					barbarianingpoint) && barbarianingpoint != 0) {
				static CLogicBarbarianKing logicBarbarianKing;
				CLogicUserBasic logicUserBasic;
				DataUserBasic userBasic;
				logicUserBasic.GetUserBasicLimit(uid, OpenPlatform::GetType(), userBasic);
				logicBarbarianKing.SetBKChallenger(user.level, uid, barbarianingpoint, userBasic.name);
			}
			// add by aaron 20130130

			if (!userFlag.isMember("dchg")
					|| CTime::GetDayInterval(userFlag["dchg"][0u].asUInt(), Time::GetGlobalTime()) != 0)
			{
				userFlag["dchg"][0u] = Time::GetGlobalTime();
				userFlag["dchg"][1u] = 0;
			}
			result["dailyacccharge"] = userFlag["dchg"][1u];
			result["dailyaccchargeTS"] = userFlag["dchg"][0u];

			result["pointpay"].resize(0);
			if(userFlag.isMember("user_pay"))
			{
				result["pointpay"] = userFlag["user_pay"];
			}

			result["chgs"].resize(0);
			if(userFlag.isMember("chgs"))
			{
				result["chgs"] = userFlag["chgs"];
			}

			if(!userFlag.isMember("heroCoins"))   //用于购买武将碎片
			{
				result["coins3"] = 0;
				result["todaycharge"] = 0;
			}
			else
			{
				result["coins3"] = userFlag["heroCoins"][1u].asInt();
				unsigned last_ts = userFlag["heroCoins"][0u].asUInt();
				unsigned now = time(0);
				if(CTime::GetDayInterval(last_ts,now) == 0)
				{
					result["todaycharge"] = userFlag["heroCoins"][2u].asInt();
				}
				else
				{
					result["todaycharge"] = 0;
				}
			}

			//add by aaron
			/*
			if (Config::GetIntValue("new_flag") == 1) // 判断是否为混战三国  1：混战三国 其他:非混战三国
					{
				int count = 0;
				uint64_t seq = 0;
				CLogicBuyGoods logicBuyGoods;
				CDataGoods datagoods;
				int dbCount = 0;
				if (data["buy_goods"].isArray()
						&& data["buy_goods"].size() > 0) {
					int iCount = data["buy_goods"].size();
					for (int i = 0; i < iCount; i++) {
						seq = atol(
								data["buy_goods"][i]["seq"].asString().c_str());
						Json::GetInt(data["buy_goods"][i], "count", count);
						datagoods.GetCountById(uid, seq, dbCount);
						ret = logicBuyGoods.UpdateGoods(uid, seq,
								dbCount - count);
						if (0 != ret) {
							error_log(
									"update buy equipments failed ,uid=%u,seq=%ld,count=%d",
									uid, seq, count);
						} else {
							info_log(
									"update buy equipments success ,uid=%u,seq=%ld,count=%d",
									uid, seq, count);
						}
					}
				}
			}
			*/
			// add by aaron

			//自己保存自己才存stat
			if (data.isMember("stats"))
			{
				Json::Value old;
				reader.parse(user.user_stat, old);
				ret = checkUserStats(old,data["stats"]);
				if(ret != 0)
				{
					error_log("[user_stat error][operated=%u,operator=%u,ret=%u]",uid, uidBy,ret);
					LOGIC_ERROR_RETURN_MSG("user_stat error");
				}

				unsigned oldpower = 0;
				Json::GetUInt(old, "dehp", oldpower);
				Json::GetUInt(data["stats"], "dehp", rank.dehp);
				if(rank.dehp > 100000000 && OpenPlatform::GetType() != PT_TEST)
					return R_ERR_LOGIC;
				bool error = false;
				if(rank.dehp != oldpower)
					logicTopTenUser.SetHeroPower(user.uid, rank.dehp, error);
				if(error)
					return R_ERR_LOGIC;
				Json::GetUInt(data["stats"], "mcity", rank.mcity);
				unsigned nsp = 0;
				Json::GetUInt(data["stats"], "nsp", nsp);
				user.memory = max(user.memory, nsp);

				if(data["stats"].isMember("bet"))
				{
					betchg = data["stats"]["bet"].asInt();
					if(old.isMember("bet"))
						betold = old["bet"].asInt();
					else
						betold = 0;
					betres = betchg + betold;
					if(betres < 0){
						error_log("[resource_error][operated=%u,operator=%u,betchg=%d]", uid, uidBy,betchg);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
					data["stats"]["bet"] = betres;
				}

				user.user_stat = writer.write(data["stats"]);
			}

			if (data.isMember("tech")) {
				Json::Value OldUserTech;
				reader.parse(user.user_tech, OldUserTech);

				ret = checkUserTech(OldUserTech,data["tech"]);
				if(ret != 0)
				{
					error_log("[user_tech error][operated=%u,operator=%u,ret=%u]", uid,uidBy,ret);
					LOGIC_ERROR_RETURN_MSG("user_tech error");
				}

				if (data["tech"]["godE"].isObject()) {
					if (data["tech"]["godE"]["qlE"].isArray()) {
						if (OldUserTech["godE"]["qlE"].isArray()) {
							qleold = OldUserTech["godE"]["qlE"][0u].asInt();
							qlechg = data["tech"]["godE"]["qlE"][0u].asInt();
							qleres = qlechg + qleold;
							if(qleres < 0 || qlechg > 300){
								error_log("[resource_error][operated=%u,operator=%u,qlechg=%d]", uid, uidBy,qlechg);
								LOGIC_ERROR_RETURN_MSG("resource_error");
							}
							data["tech"]["godE"]["qlE"][0u] = qleres;
						}
					}
				}

				user.user_tech = writer.write(data["tech"]);

				if(data["tech"].isMember("part") && data["tech"]["part"].isArray())
				{
					for(unsigned i=0;i<data["tech"]["part"].size();++i)
						rank.part += data["tech"]["part"][i].asUInt();
				}
				Json::GetUInt(data["tech"], "soul", rank.soul);
				Json::GetUInt(data["tech"]["heaven"], "lv", rank.book);
				Json::GetUInt(data["tech"]["daoist"], "lv", rank.mac);
			}

			//个人部分挪到存自己 ralf 20140527
			if (data.isMember("barrackQ")) {
				user.barrackQ = writer.write(data["barrackQ"]);
			}
			if (data.isMember("soldier")) {
				//checksoldier(user.soldier, data["soldier"]);
				user.soldier = writer.write(data["soldier"]);
			}
			if (data.isMember("soldierlevel")) {
				checksoldierlevel(user.soldierlevel, data["soldierlevel"]);
				user.soldierlevel = writer.write(data["soldierlevel"]);
			}
			if (data.isMember("buildQ")) {
				user.buildQ = writer.write(data["buildQ"]);
			}
			if (data.isMember("skillQ")) {
				checkskillQ(user.skillQ,data["skillQ"]);
				user.skillQ = writer.write(data["skillQ"]);
			}
			if (data.isMember("trainQ")) {
				user.trainQ = writer.write(data["trainQ"]);
			}
			if (data.isMember("game_vip_state") && user.vipstat.empty()) {
				user.vipstat = writer.write(data["game_vip_state"]);
			}
			if (data.isMember("godfb")) {
				CLogicWeapon logicWeapon;
				logicWeapon.SetWeapon(user.uid, data["godfb"]);
			}

			if (!user.kingdom && data.isMember("kingdom"))
				Json::GetUInt(data, "kingdom", user.kingdom);
			if (data.isMember("tutorialstage"))
				Json::GetInt(data, "tutorialstage", user.tutorial_stage);
			if (data.isMember("alliance_tech"))
				user.alliance_tech = writer.write(data["alliance_tech"]);

			// 保存用户状态信息  sns相关
			int unsigned sstate;
			if (Json::GetUInt(data, "sstate", sstate)) {
				user.sstate = sstate;
			}
			if (data.isMember("md")) {
				user.glory = writer.write(data["md"]);
			}

			//移除帮助好友的记录
			unsigned lastts = 0;
			if (Json::IsObject(data, "updates")
					&& Json::GetUInt(data["updates"], "lastts", lastts)
					&& lastts > 0) {
				CLogicUpdates logicUpdates;
				ret = logicUpdates.RemoveUpdatesBeforeTs(uid, lastts);
				if (ret != 0)
					return ret;
			}

			if (data.isMember("wnpcdrwd")) {
				Json::Value baseExtraData;
				DataBaseExtra baseExtra;
				int iCount = data["wnpcdrwd"].size();
				for (int i = 0; i < iCount; i++) {
					ret = logicBaseExtra.GetBaseExtra(uid, data["wnpcdrwd"][i].asUInt(),
							baseExtra);
					if (0 != ret) {
						error_log("Get baseExtra data failed worldpos = %u, uid = %u",
								baseExtra.worldpos, uid);
						return ret;
					}
					baseExtra.last_collect_ts = Time::GetGlobalTime();
					ret = logicBaseExtra.SetBaseExtra(uid, baseExtra.worldpos,
							baseExtra);
					if (0 != ret) {
						error_log("Set baseExtra data failed worldpos = %u, uid = %u",
								baseExtra.worldpos, uid);
						return ret;
					}
				}
			}
			/*20150908 Ralf fix
			unsigned daily = 0;
			Json::GetUInt(data, "daily", daily);
			if(daily)
				logicUser.CheckR5(user, false);
			*/

			//TIME_COUNT_LOG("[main_self over]");
		}//uid == uidBy

		if(!IsVision(loadType))
		{
			//共同部分
			// user
			Json::GetInt(data, "damage", user.damage);
			user.last_save_time = Time::GetGlobalTime();
			Json::GetUInt(data, "seqid", user.lastseq);
			//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
			//user.last_breath_time = Time::GetGlobalTime();
			//20131107 Ralf last_save_uid -> last_load_save_uid : fix for bugs, can save only last load archieve
			//user.last_save_uid = uidBy;
			Json::GetUInt(data, "newgcbase", user.newgcbase);
			if (Json::IsArray(data, "currencys") || reward_res.ene || reward_res.sou || reward_res.pro) {
				if (data["currencys"].size() > 0 || reward_res.ene) {
					if (Json::GetInt(data["currencys"], (unsigned) 0, gcbaschg) || reward_res.ene)  {
						if(gcbaschg > 0)//移后端，禁止加
						{
							error_log("[gcbaschg error]uid=%u,gcbaschg=%u", uid, gcbaschg);
							gcbaschg = 0;
						}
						else
							gate_cost -= gcbaschg;
						gcbaschg += reward_res.ene;
						if (gcbaschg != 0) {
							itemp = gcbaschg + user.gcbase;
							if (itemp >= 0)
								user.gcbase += gcbaschg;
							else {
								error_log("[resource_error][operated=%u,operator=%u,gcbaschg=%d]", uid, uidBy, gcbaschg);
								LOGIC_ERROR_RETURN_MSG("resource_error");
							}
						}
					}
				}
				if (data["currencys"].size() > 1) {
					if (Json::GetInt(data["currencys"], (unsigned) 1, gcbuychg)	&& gcbuychg != 0) {
						if(gcbuychg > 0)//移后端，禁止加
						{
							error_log("[gcbuychg error]uid=%u,gcbuychg=%u", uid, gcbuychg);
							gcbuychg = 0;
						}
						else
							gate_cost -= gcbuychg;
						itemp = gcbuychg + user.gcbuy;
						if (itemp >= 0)
							user.gcbuy += gcbuychg;
						else {
							error_log("[resource_error][operated=%u,operator=%u,gcbuychg=%d]", uid,uidBy,  gcbuychg);
							LOGIC_ERROR_RETURN_MSG("resource_error");
						}
					}
				}
				if(gate_reward > 1 && gate_cost/10 < gate_reward){
					error_log("[resource_error][operated=%u,operator=%u,gate_cost=%d,gate_reward=%d]", uid, uidBy, gate_cost, gate_reward);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
				if(uid == uidBy && user.level > 30)
				{
					if(gate_reward == 1 && gate_cost < 10)
					{
						unsigned ec1 = 0;
						Json::Value stat;
						reader.parse(user.user_stat, stat);
						Json::GetUInt(stat, "ec1", ec1);
						if(ec1 == 0){
							error_log("[resource_error][operated=%u,operator=%u,gate_cost=%d,gate_reward=%d]", uid, uidBy, gate_cost, gate_reward);
							//LOGIC_ERROR_RETURN_MSG("resource_error");
							memset(&reward_res, 0, sizeof(reward_res));
						}
						stat["ec1"] = 0;
						user.user_stat = writer.write(stat);
					}
					else if(gate_reward == 0 && gate_cost >= 10)
					{
						Json::Value stat;
						reader.parse(user.user_stat, stat);
						stat["ec1"] = 1;
						user.user_stat = writer.write(stat);
					}
				}
				if (data["currencys"].size() > 2 || reward_res.pro) {
					if (Json::GetInt(data["currencys"], (unsigned) 2, addprosper) || reward_res.pro) {
						addprosper += reward_res.pro;
						if (addprosper != 0) {
							itemp = addprosper + user.prosper;
							if (itemp >= 0)
								user.prosper += addprosper;
							else {
								error_log("[resource_error][operated=%u,operator=%u,addprosper=%d]",  uid, uidBy,addprosper);
								LOGIC_ERROR_RETURN_MSG("resource_error");
							}
						}
					}
				}
				if (data["currencys"].size() > 3 || reward_res.sou) {
					if (Json::GetInt(data["currencys"], (unsigned) 3, addbs) || reward_res.sou) {
						if(addbs > 0)//移后端，禁止加
						{
							error_log("[addbs error]uid=%u,addbs=%u", uid, addbs);
							addbs = 0;
						}
						addbs += reward_res.sou;
						if (addbs != 0) {
							itemp = addbs + user.battle_spirits;
							if (itemp >= 0)
								user.battle_spirits += addbs;
							else {
								error_log("[resource_error][operated=%u,operator=%u,addbs=%d]", uid, uidBy, addbs);
								LOGIC_ERROR_RETURN_MSG("resource_error");
							}
						}
					}
				}
			}
			if (Json::IsArray(data, "resources") || reward_res.rs[0] || reward_res.rs[1] || reward_res.rs[2] || reward_res.rs[3]) {
				if (data["resources"].size() > 0 || reward_res.rs[0]) {
					if (Json::GetInt(data["resources"][(unsigned) 0], "d", _r1chg) || reward_res.rs[0]) {
						if(_r1chg > 0)
							_r1chg = (int)(_r1chg * FCM_VALUE[fcm]);
						r1chg = _r1chg + reward_res.rs[0];
						itemp = r1chg + user.r1;
						if (itemp >= 0)
							user.r1 = (unsigned)itemp>user.r1_max?user.r1_max:itemp;
						else {
							if(r1chg > 0)
								user.r1 = user.r1_max;
							else{
								if(uid != uidBy)
								{
									error_log("[resource_error][operated=%u,operator=%u,r1chg=%d]", uid, uidBy, r1chg);
									res = false;
									r1chg = 0;
								}
								else
								{
									error_log("[resource_error][operated=%u,operator=%u,r1chg=%d]", uid, uidBy, r1chg);
									LOGIC_ERROR_RETURN_MSG("resource_error");
								}
							}
						}
					}
					Json::GetUInt(data["resources"][(unsigned) 0], "m",	user.r1_max);
				}
				if (data["resources"].size() > 1 || reward_res.rs[1]) {
					if (Json::GetInt(data["resources"][(unsigned) 1], "d", _r2chg) || reward_res.rs[1]) {
						if(_r2chg > 0)
							_r2chg = (int)(_r2chg * FCM_VALUE[fcm]);
						r2chg = _r2chg + reward_res.rs[1];
						itemp = r2chg + user.r2;
						if (itemp >= 0)
							user.r2 = (unsigned)itemp>user.r2_max?user.r2_max:itemp;
						else {
							if(r2chg > 0)
								user.r2 = user.r2_max;
							else{
								if(uid != uidBy)
								{
									error_log("[resource_error][operated=%u,operator=%u,r2chg=%d]", uid,uidBy,  r2chg);
									res = false;
									r2chg = 0;
								}
								else
								{
									error_log("[resource_error][operated=%u,operator=%u,r2chg=%d]", uid,uidBy,  r2chg);
									LOGIC_ERROR_RETURN_MSG("resource_error");
								}
							}
						}
					}
					Json::GetUInt(data["resources"][(unsigned) 1], "m",	user.r2_max);
				}
				if (data["resources"].size() > 2 || reward_res.rs[2]) {
					if (Json::GetInt(data["resources"][(unsigned) 2], "d", _r3chg) || reward_res.rs[2]) {
						if(_r3chg > 0)
							_r3chg = (int)(_r3chg * FCM_VALUE[fcm]);
						r3chg = _r3chg + reward_res.rs[2];
						itemp = r3chg + user.r3;
						if (itemp >= 0)
							user.r3 = (unsigned)itemp>user.r3_max?user.r3_max:itemp;
						else {
							if(r3chg > 0)
								user.r3 = user.r3_max;
							else{
								if(uid != uidBy)
								{
									error_log("[resource_error][operated=%u,operator=%u,r3chg=%d]", uid,uidBy,  r3chg);
									res = false;
									r3chg = 0;
								}
								else
								{
									error_log("[resource_error][operated=%u,operator=%u,r3chg=%d]", uid,uidBy,  r3chg);
									LOGIC_ERROR_RETURN_MSG("resource_error");
								}
							}
						}
					}
					Json::GetUInt(data["resources"][(unsigned) 2], "m",	user.r3_max);
				}
				if (data["resources"].size() > 3 || reward_res.rs[3]) {
					if (Json::GetInt(data["resources"][(unsigned) 3], "d", _r4chg) || reward_res.rs[3]) {
						if(_r4chg > 0)
							_r4chg = (int)(_r4chg * FCM_VALUE[fcm]);
						r4chg = _r4chg + reward_res.rs[3];
						itemp = r4chg + user.r4;
						if (itemp >= 0)
							user.r4 = (unsigned)itemp>user.r4_max?user.r4_max:itemp;
						else {
							if(r4chg > 0)
								user.r4 = user.r4_max;
							else{
								if(uid != uidBy)
								{
									error_log("[resource_error][operated=%u,operator=%u,r4chg=%d]",uid,  uidBy, r4chg);
									res = false;
									r4chg = 0;
								}
								else
								{
									error_log("[resource_error][operated=%u,operator=%u,r4chg=%d]",uid,  uidBy, r4chg);
									LOGIC_ERROR_RETURN_MSG("resource_error");
								}
							}
						}
					}
					Json::GetUInt(data["resources"][(unsigned) 3], "m",	user.r4_max);
				}
			}

			if (Json::GetInt(data, "r5", r5chg) && r5chg != 0) {
				if(uid != uidBy)
				{
					if(r5chg != -1)
					{
						error_log("[resource_error][operated=%u,operator=%u,r5chg=%d]",uid,  uidBy, r5chg);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}

					if(user.r5 == 0)
					{
						error_log("[resource_error][operated=%u,operator=%u,r5chg=%d]",uid,  uidBy, r5chg);
						res = false;
						r5chg = 0;
					}
					else
						--user.r5;
				}
				else
				{
					error_log("[resource_error][operated=%u,operator=%u,r5chg=%d]",uid,  uidBy, r5chg);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}

			result["lasttime"] = user.last_save_time;
			result["lastseq"] = user.lastseq;
			result["saveuserid"] = uid;
			result["resources"][(unsigned) 0]["c"] = user.r1;
			result["resources"][(unsigned) 1]["c"] = user.r2;
			result["resources"][(unsigned) 2]["c"] = user.r3;
			result["resources"][(unsigned) 3]["c"] = user.r4;
			result["resources"][(unsigned) 4]["c"] = 0;
			result["r5"] = user.r5;
			result["r5_max"] = user.r5_max;
			result["currencys"][(unsigned) 0] = user.gcbase;
			result["currencys"][(unsigned) 1] = user.gcbuy;
			result["currencys"][(unsigned) 2] = user.prosper;
			result["currencys"][(unsigned) 3] = user.battle_spirits;

			//TIME_COUNT_LOG("[main over]");
		}//loadType != LT_RANK && loadType != LT_CHALLENGE

		if(uid == uidBy)//经验增加放后面了
		{
			/*Json::GetInt(data, "exp", exp);
			if(exp > 0)//移后端，禁止加
			{
				error_log("[exp error]uid=%u,exp=%u", uid, exp);
				exp = 0;
			}*/
			if (reward_res.exp > 0)
				exp += reward_res.exp;
			if(rcode.find("bd_harvest") != string::npos)
				exp += getResGetAddExp(user.level, _r1chg, _r2chg, _r3chg, _r4chg);
			if(exp > getMaxAddExp(user.level))
			{
				error_log("[exp_error][operator=%u,expchg=%d]", uid, exp);
				LOGIC_ERROR_RETURN_MSG("exp_error");
			}
			int tempexp = exp + user.point;
			if (tempexp < 0)
			{
				error_log("[resource_error][operated=%u,operator=%u,expchg=%d]", uid, uidBy, exp);
				LOGIC_ERROR_RETURN_MSG("resource_error");
			}
			user.point += exp;
			result["exp"] = Convert::UInt64ToString(user.point);

			int leveltemp = getLevel(user.point);
			/*Json::GetInt(data, "level", leveltemp);
			if(leveltemp > 30 && ((user.level > 50 && leveltemp > user.level + 1) || leveltemp > user.level + 3))
			{
				error_log("[level_error][operated=%u,operator=%u]", uid, uidBy);
				LOGIC_ERROR_RETURN_MSG("level_error");
			}
			else*/
			{
				//logicTopTenUser.SetUserLevel(user.uid, user.level,leveltemp); 功能取消
				/***add by ralf 20140411 for check level***/
				if(user.level != leveltemp)
					USER_LEVEL_LOG("uid=%u,l=%u",uid,leveltemp);
				/*****************************************/
				user.level =  leveltemp;
				rank.level = user.level;
			}
			result["level"] = leveltemp;
		}
	}//isMainPos
	else
	{
		ret = ProcessOrders(uidBy, data, payData, false,userFlag,bsave);
		if (ret != 0)
			return ret;
		if(bsave)
		{
			ret = logicUser.SetUserFlag(uidBy,userFlag);
			if(ret)
				return ret;
		}

		// 更新攻击者保存分基地的时间。
		DataBreathInfo breathInfo;
		breathInfo.last_breath_time = Time::GetGlobalTime();
		breathInfo.last_breath_uid = uidBy;
		if (uid != uidBy)
		{
			if (attackend)
			{
				breathInfo.being_attack_flag = NO_ATTACK;
			}
			else if(IsAttackFinished(userBy.bit_info) && userBy.bit_info)//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
			{
				LOGIC_ERROR_RETURN_MSG("attack_too_long");
			}
			else
			{
				if(userBy.bit_info == 0)
				{
					userBy.bit_info = Time::GetGlobalTime();
					logicUser.SetBitInfo(uidBy, userBy.bit_info);
				}

				breathInfo.being_attack_flag = BEING_ATTACK;
			}
		}
		else
		{
			breathInfo.being_attack_flag = NO_ATTACK;
		}
		logicBaseExtra.UpdateBreathInfo(uid, world_pos, breathInfo);

		//TIME_COUNT_LOG("[extra over]");
	}//!isMainPos

	if(uid == uidBy)
	{
		if (newEqDatas.size())
		{
			for(unsigned newEqDatas_count=0; newEqDatas_count<newEqDatas.size();newEqDatas_count++)
			{
				data["equipment"].append(newEqDatas[newEqDatas_count]);
			}
			//debug_log("newEqDatas=%s",Json::ToString(data["equipment"]).c_str());
		}
		if (Json::IsArray(data, "equipment")) {
			CLogicEquipment logicEquip;
#if SERVER_EQUIP_ADDABLE == 1
			ret = logicEquip.UpdateEquipment(uid, uidBy, data["equipment"],result["equipment"],true);
#else
			Json::Value res;
			ret = logicEquip.UpdateEquipment(uid, uidBy, data["equipment"],res,true);
#endif
			if (ret != 0)
				return ret;
		}
		//TIME_COUNT_LOG("[equip over]");
	}

	if(!IsVision(loadType))
	{
		//building
		if (Json::IsArray(data, "baseop")) {
			CLogicBuilding logicBuilding;
#if SERVER_BUILD_ADDABLE == 1
			ret = logicBuilding.UpdateBuilding(uid, world_pos, data["baseop"],result["baseop"],isMainPos);
#else
			Json::Value res;
			ret = logicBuilding.UpdateBuilding(uid, world_pos, data["baseop"],res,isMainPos);
#endif
			if (ret != 0)
				return ret;

			if(loadType == LT_BUILD)
			{
				for(unsigned bseq=0;bseq<data["baseop"].size();++bseq)
				{
					int type = 0;
					Json::GetInt(data["baseop"][bseq], "t", type);
					if(type == 1)
					{
						rank.citylevel = data["baseop"][bseq]["l"].asUInt();
						break;
					}
				}
			}

#if DATA_NEW_WORLD_ENABLE == 0
			// 二级地图初始化主城
			if (isMainPos && user.mainpos == 0) {
				int iCount = data["baseop"].size();
				for (int i = 0; i < iCount; i++) {
					if (data["baseop"][i]["t"].asInt() == 1
							&& data["baseop"][i]["l"].asInt() >= 40) {
						CLogicWorld logicWorld;
						WorldPoint worldPoint;
						worldPoint.uid = uid;
						worldPoint.map_flag = USER_MAIN_CITY;
						ret = logicWorld.AddUser(worldPoint, user.mainpos);
						if (0 != ret) {
							error_log("add world user failed %u", uid);
							return ret;
						}
						ret = logicUser.SetMainpos(uid, user.mainpos);
						if (0 != ret) {
							error_log("set user limit failed %u", uid);
							return ret;
						}
						result["world_pos"]["world_pos"] = user.mainpos;
						break;
					}
				}
			}
#endif
		}
		//TIME_COUNT_LOG("[building over]");

		//hero
		CLogicHero logicHero;
		int hexnow = 0;
		if (reward_res.hex)
		{
			for(int hero_size=0; hero_size<data["hero"].size(); ++hero_size)
			{
				if(data["hero"][hero_size]["ud"].asUInt() == reward_res.hud)
				{
					hexnow = data["hero"][hero_size]["exp"].asInt() + reward_res.hex;
					data["hero"][hero_size]["exp"] = hexnow;
					reward_res.hex = 0;
					break;
				}
			}
		}
		for(int add_hero_size=0; add_hero_size<reward_hero.size(); add_hero_size++)
		{
			string addheroid = reward_hero[add_hero_size];
			string addherocod = "quest_reward";
			data["hero"].append(logicHero.genHero(addheroid, addherocod));
		}
		if (Json::IsArray(data, "hero"))
		{
#if SERVER_HERO_ADDABLE == 1
			ret = logicHero.UpdateHero(uid, data["hero"],result["hero"], uid!=uidBy);
#else
			Json::Value res;
			ret = logicHero.UpdateHero(uid, data["hero"],res);
#endif
			if (ret != 0)
				return ret;

			if(loadType == LT_BUILD)
			{
				for(unsigned hseq=0;hseq<data["hero"].size();++hseq)
				{
					int hero_def = 0;
					Json::GetInt(data["hero"][hseq], "def", hero_def);
					if(hero_def == 1)
					{
						Json::Value heroid;
						heroid["heroid"] = data["hero"][hseq]["id"];
						if(data["hero"][hseq].isMember("name"))
							heroid["name"] = data["hero"][hseq]["name"];
						rank.heroid = writer.write(heroid);
						break;
					}
				}
			}
		}
		if (reward_res.hex)
		{
			if(logicHero.AddHeroExp(uid,reward_res.hud,reward_res.hex, hexnow))
				reward_res.hud = 0;
		}
		result["hud"] = reward_res.hud;
		result["hex"] = hexnow;
		//TIME_COUNT_LOG("[hero over]");
	}//loadType != LT_RANK && loadType != LT_CHALLENGE

	if(uid != uidBy)
	{
		int rchg[4];
		memset(rchg, 0, sizeof(rchg));
		if (Json::IsObject(data, "attackinfo")) {
			ret = ProcessAttackInfo(uidBy, data["attackinfo"], result["attackinfo"], uid, loadType, res, rchg);
			if (ret != 0)
				return ret;
		}
		else
		{
			Json::Value worldres;
			if(!userBy.worldres.empty() && reader.parse(userBy.worldres, worldres))
			{
				int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
				Json::GetInt(worldres, "r1", r1);
				Json::GetInt(worldres, "r2", r2);
				Json::GetInt(worldres, "r3", r3);
				Json::GetInt(worldres, "r4", r4);
				rchg[0] = std::max(0 ,(int)userBy.r1 - r1);
				rchg[1] = std::max(0, (int)userBy.r2 - r2);
				rchg[2] = std::max(0, (int)userBy.r3 - r3);
				rchg[3] = std::max(0, (int)userBy.r4 - r4);
			}
		}

		if(!IsVision(loadType))
		{
			UpdateAttack(userBy, user, data, rchg);
		}
	}

	if(!IsVision(loadType))
	{
		if(isMainPos)
		{
			/**20140417 ralf 最后再保存用户信息**/
			// 保存用户状态信息
			ret = logicUser.SetUser(uid, user, flagUser);
			if (ret != 0)
				return ret;
			/******************************/

			CDataRank dataRank;
			dataRank.SetRank(uid, rank);

			RESOURCE_LOG(
					"[save change][uid=%u,gcbaschg=%d,gcbase=%u,gcbuychg=%d,gcbuy=%u,r1chg=%d,r1=%u,r2chg=%d,r2=%u,r3chg=%d,r3=%u,r4chg=%d,r4=%u,r5chg=%d,r5=%u,addprosper=%d,prosper=%u,addbs=%d,bs=%u,qlechg=%d,qle=%d,ylchg=%d,yl=%d,betchg=%d,bet=%d,expchg=%u,exp=%u,lvl=%u,code=%s]",
					uid, gcbaschg, user.gcbase, gcbuychg, user.gcbuy, r1chg,
					user.r1, r2chg, user.r2, r3chg, user.r3, r4chg, user.r4, r5chg,
					user.r5, addprosper, user.prosper, addbs, user.battle_spirits,
					qlechg,qleres,ylchg,ylres,betchg,betres,exp,user.point,user.level,rcode.c_str());
		}
	}

	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	//TIME_COUNT_LOG("[save over]");

	return 0;
}

int CLogicArchive::GetMainQuestFinishMap(unsigned uid, std::map<unsigned, int>& result)
{
	result.clear();

	int ret = 0;
	Json::Value jsonQuest;
	CLogicQuest logicQuest;
	if ((ret = logicQuest.GetQuest(uid, jsonQuest)) != R_SUCCESS)
	{
		error_log("[quest get data error][uid=%u,ret=%d]",uid, ret);
		return ret;
	}

	if (! jsonQuest.isArray())
	{
		error_log("[quest data error][uid=%u]",uid);
		return R_ERR_DATA;
	}

	//----------------------------------------------------------------------
	//将领取过的主线任务id放入map表
	unsigned id = 0;
	int c = 0;
	for (int i = 0; i < (int)jsonQuest.size();  ++i)
	{
		if (!Json::GetUInt(jsonQuest[i], "id", id))
		{
			error_log("[quest data node id error][uid=%u,index=%u]",uid,i);
			return R_ERR_DATA;
		}

		if (!Json::GetInt(jsonQuest[i],  "c", c))
		{
			error_log("[quest data node c error][uid=%u,index=%u]",uid,i);
			return R_ERR_DATA;
		}

		if (c >= 2) //任务完成，已领取奖励
		{
			result[id] = c;
		}
	}
	//@end

	return R_SUCCESS;
}

int CLogicArchive::GetOlgateCnt(unsigned uid, const DataUser& user, int& result)
{
	Json::Value jsonState;
	int ret = 0;

	if (! Json::FromString(jsonState, user.user_stat))
	{
		error_log("[GetOlgateCnt][parse user state error. uid=%u]", uid);
		return ret;
	}

	unsigned time = 0;

	Json::GetUInt(jsonState, "lts", time);
	unsigned nowTime = Time::GetGlobalTime();
	if (CTime::IsDiffDay(time, nowTime))
	{
		result = 0;
	}
	else
	{
		int cnt = 0;
		Json::GetInt(jsonState, "brt", cnt);
		result = cnt;
	}

	return R_SUCCESS;
}

int CLogicArchive::ParseMainQuestSubmitMap(unsigned uid, const Json::Value jsonQuest, std::map<unsigned, int>& result)
{
	if (! jsonQuest.isArray())
	{
		error_log("[ParseMainQuestSubmitMap][params_quest_error.uid=%d]", uid);
		return R_ERR_PARAM;
	}

	result.clear();

	int ret = 0;
	for (int i = 0; i < (int)jsonQuest.size(); ++i)
	{

		unsigned c = 0;
		unsigned id = 0;

		const Json::Value &item = jsonQuest[i];

		if (! Json::GetUInt(item, "id", id))
		{
			continue;
		}

		Json::GetUInt(item, "c" , c);
		if (c == 2)
		{
			result[id] = c;
		}
	}

	return R_SUCCESS;
}

int CLogicArchive::CheckQuestRewardValid(unsigned uid, const DataUser& user, const Json::Value& data, int &gate_reward)
{
	gate_reward = 0;
	Json::Value questReward;
	if (! Json::GetArray(data, "questreward", questReward))
	{
		error_log("[CheckQuestRewardValid][parse_questReward_failed uid=%u]", uid);
		return R_ERROR;
	}

	int ret = 0;

	bool isGetMainQuestMap = false;
	std::map<unsigned, int> mapQuest;
	std::map<unsigned, int> mapSubmitQuest;
	//检查主线任务的奖励是否合法
	for(int i=0; i < (int)questReward.size(); i++)
	{
		const Json::Value &item = questReward[i];

		std::string configname;

		Json::GetString(item, "cn", configname);
		if (configname.empty())
		{
			continue;
		}

		if ("questconfig" == configname)
		{
			if (! isGetMainQuestMap)
			{
				Json::Value jsonQuest;
				if (! Json::GetArray(data, "quest", jsonQuest))
				{
					error_log("[CheckQuestRewardValid][parse_quest_failed uid=%u]", uid);
					return R_ERROR;
				}

				if ((ret = GetMainQuestFinishMap(uid, mapQuest)) != R_SUCCESS
					|| ((ret = ParseMainQuestSubmitMap(uid, jsonQuest, mapSubmitQuest)) != R_SUCCESS))
				{
					error_log("[CheckQuestRewardValid][make_map_error. uid=%u]", uid);
					return ret;
				}

				isGetMainQuestMap = true;
			}

			int id = -1;
			if (! Json::GetInt(item, "id", id))
			{
				error_log("[CheckQuestRewardValid][quest reward data node id invalid][uid=%u]",uid);
				return R_ERR_PARAM;
			}

			//判断提交的quest的对应任务的c字段是否为 2
			if (mapSubmitQuest.count(id) == 0)
			{
				error_log("[CheckQuestRewardValid][quest reward data node c invalid][uid=%u]",uid);
				return R_ERR_PARAM;
			}

			//判断该任务是否已经是领取状态
			if (mapQuest.count(id) > 0)
			{
				error_log("[CheckQuestRewardValid][already get quest reward][uid=%u,id=%u]",uid,id);
				return R_ERR_PARAM;
			}
		}
		else if ("olgateconfig" == configname)
		{
			unsigned id = 0;
			Json::GetUInt(item, "id", id);
			//传记Id
			if (id >= 1001 && id <= 1038)
			{
				int cnt = 0;
				if ((ret = GetOlgateCnt(uid, user, cnt)) != R_SUCCESS)
				{
					error_log("[CheckQuestRewardValid][GetOlgateCnt_failed.uid=%u,ret=%d]", uid, ret);
					return R_ERR_DATA;
				}

				if (cnt > 15)
				{
					error_log("[CheckQuestRewardValid][olgate_cnt_over_limit.uid=%u,id=%d,cnt=%d]", uid,id,cnt);
					return R_ERR_REFUSE;
				}
			}
			else
				++gate_reward;
		}
	}

	return R_SUCCESS;
}

int CLogicArchive::UpdateSave(unsigned uid, unsigned uidBy, const string &type, unsigned world_pos,	Json::Value &result)
{
	LoadType loadType = GetLoadType(type);
	if((uid == uidBy && !IsSelfType(loadType))
	|| (uid != uidBy && !IsOtherType(loadType))
	|| (IsValidUid(uid) && loadType == LT_SPORTS))
	{
		REFUSE_RETURN_MSG("load_type_error");
	}

	int ret = 0;
	DataUser userBy;
	CLogicUser logicUser;
	AUTO_LOCK_SAVE_USER(uid,loadType)
	ret = logicUser.GetUserLimit(uidBy, userBy);
	if (ret != 0)
		return ret;

	logicUser.UpdateActiveExtBreathTime(uidBy, userBy.last_active_time,	userBy.ext);

	if (IsValidArenaId(uid)) {
		CLogicArena logicArena;
		logicArena.BreathArena(uid, uidBy);
		return 0;

	}
	if (IsValidFightArenaId(uid)) {
		CLogicFightArena logicArena;
		logicArena.BreathFightArena(uid, uidBy);
		return 0;

	}
	if (IsValidWorldBossId(uid)) {
		CLogicWorldBoss logicWorldBoss;
		ret = logicWorldBoss.ViewWorldBoss(uidBy, uid, result["worldboss"]);
		if (ret != 0)
			return ret;
		return 0;
	}
	if (IsValidNianShouId(uid)) {
		CLogicNianShou logicNianShou;
		ret = logicNianShou.ViewNianShou(uidBy, uid, result["nianshou"]);
		if (ret != 0)
			return ret;
		return 0;
	}
	//AllianceBoss
	if (IsValidAllianceBossId(uid)) {
			CLogicAllianceBoss logicAllianceBoss;
			ret = logicAllianceBoss.ViewAllianceBoss(uidBy, uid, result["allianceboss"]);
			if (ret != 0)
				return ret;
			return 0;
		}
	if (!IsValidUid(uid)) {
		return 0;
	}

	DataPay payData;
	CLogicPay logicPay;
	ret = logicPay.GetPay(uidBy, payData);
	if (ret != 0)
		return ret;

	DataUser user;
	if (uid == uidBy)
	{
		if (userBy.tribute_time > Time::GetGlobalTime())
		{
			string retStr = "being_blocked_"
					+ CTrans::ITOS(userBy.tribute_time - Time::GetGlobalTime());
			REFUSE_RETURN_MSG(retStr);
		}
		// 太频繁，改慢点
		if((userBy.last_active_time - userBy.last_login_time) % 1800 > 1770)
		{
			CLogicUserBasic logicUserBaisc;
			DataUserBasic userBasic;
			ret = logicUserBaisc.GetUserBasic(uid, OpenPlatform::GetType(), userBasic);
			if (0 == ret)
			{
				bool isBlackUser = false;
				logicUserBaisc.CheckBlackUser(userBasic.open_id,isBlackUser);
				if (isBlackUser)
				{
					REFUSE_RETURN_MSG("being_blocked");
				}
			}
		}

		user.copyLimit(userBy);

		if(loadType == LT_DEFEND && user.bit_info == 0)
		{
			logicUser.SetBitInfo(uid, Time::GetGlobalTime());
		}
		else if(loadType == LT_DEFEND && IsDefendFinished(user.bit_info))
		{
			LOGIC_ERROR_RETURN_MSG("defend_too_long");
		}

		result["acccharge"] = user.accCharge;

		/* 2014901 Ralf change to save activity
		CLogicSecinc logicSecinc;
		ret = logicSecinc.GetSecinc(uid, result["secinc"]);
		if (ret != 0)
			return ret;
		*/

		Json::Value userFlag;
		ret = logicUser.GetUserFlag(uidBy, userFlag);
		if (ret != 0)
			return ret;

		if (!userFlag.isMember("dchg")
				|| CTime::GetDayInterval(userFlag["dchg"][0u].asUInt(), Time::GetGlobalTime()) != 0)
		{
			userFlag["dchg"][0u] = Time::GetGlobalTime();
			userFlag["dchg"][1u] = 0;
		}
		result["dailyacccharge"] = userFlag["dchg"][1u];
		result["dailyaccchargeTS"] = userFlag["dchg"][0u];

		result["pointpay"].resize(0);
		if(userFlag.isMember("user_pay"))
		{
			result["pointpay"] = userFlag["user_pay"];
		}

		result["chgs"].resize(0);
		if(userFlag.isMember("chgs"))
		{
			result["chgs"] = userFlag["chgs"];
		}

		if(!userFlag.isMember("heroCoins"))   //用于购买武将碎片
		{
			result["coins3"] = 0;
			result["todaycharge"] = 0;
		}
		else
		{
			result["coins3"] = userFlag["heroCoins"][1u].asInt();
			unsigned last_ts = userFlag["heroCoins"][0u].asUInt();
			unsigned now = time(0);
			if(CTime::GetDayInterval(last_ts,now) == 0)
			{
				result["todaycharge"] = userFlag["heroCoins"][2u].asInt();
			}
			else
			{
				result["todaycharge"] = 0;
			}
		}

		/*
		if(Config::GetIntValue("new_flag") == 1)
		{

			CLogicBuyGoods logicBuyGoods;
			ret = logicBuyGoods.GetGoods(uid,result["buy_goods"]);
		}
		*/
	}//uid == uidBy
	else
	{
		if(userBy.bit_info == 0)
		{
			userBy.bit_info = Time::GetGlobalTime();
			logicUser.SetBitInfo(uidBy, userBy.bit_info);
		}
		else if(IsAttackFinished(userBy.bit_info))//Ralf20140307 这里用作开始进攻时间，检测进攻时间过长
		{
			if(loadType == LT_RANK)
			{
				if(Time::GetGlobalTime()>RANK_ATTACK_MAX_TIME+userBy.bit_info)
				{
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
			}
			else if(loadType == LT_BNW)
			{
				if(Time::GetGlobalTime()>BNW_ATTACK_MAX_TIME+userBy.bit_info)
				{
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
			}
			else if(loadType == LT_MVP)
			{
				if(Time::GetGlobalTime()>MVP_ATTACK_MAX_TIME+userBy.bit_info)
				{
					LOGIC_ERROR_RETURN_MSG("attack_too_long");
				}
			}
			else
			{
				LOGIC_ERROR_RETURN_MSG("attack_too_long");
			}
		}

		ret = logicUser.GetUserLimit(uid, user);
		if (ret != 0)
			return ret;
		bool isMainPos = ((world_pos == 0 || world_pos == user.mainpos) ? true : false);
		if (isMainPos)
		{
			if(!IsVision(loadType))
			{
				//20131107 Ralf last_breath_time -> last_attacked_time : fix for online attacking bugs
				logicUser.UpdateBreathTime(uid);
				//debug_log("[update attack,operated=%u,operator=%u,last_breath_time=%u]",uid,uidBy,Time::GetGlobalTime());
			}
		}
	}

	CLogicUpdates logicUpdates;
	ret = logicUpdates.GetUpdates(uid, result["updates"]["data"], uid != uidBy);
	if (ret != 0)
		return ret;

	CLogicBroadcast logicBd;
	vector<BroadcastMessage> bdMsgs;
	ret = logicBd.GetBdMessage(bdMsgs);
	if (ret == 0 && bdMsgs.size() > 0) {
		result["broadcast"].resize(bdMsgs.size());
		for (unsigned i = 0; i < bdMsgs.size(); i++) {
			result["broadcast"][i]["id"] = bdMsgs[i].id;
			result["broadcast"][i]["content"] = bdMsgs[i].content;
		}
	}
	// add by aaron 20121106
	result["mainpos"] = user.mainpos;

	// add by aaron 20121030
	CLogicBaseExtra logicBaseExtra;
	// 默认主城坐标
	bool isMainPos = (
			(world_pos == 0 || world_pos == user.mainpos) ? true : false);
	if (!isMainPos) {
		DataBaseExtra baseExtra;
		logicBaseExtra.GetBaseExtra(uid, world_pos, baseExtra);
		if (BEING_ATTACK == baseExtra.being_attack_flag
				&& IsBeingAttacked(baseExtra.last_breath_time)
				&& uidBy != baseExtra.last_breath_uid) {
			LOGIC_ERROR_RETURN_MSG("u_being_attacked");

		}
		baseExtra.last_breath_time = Time::GetGlobalTime();
		baseExtra.last_breath_uid = uidBy;
		logicBaseExtra.SetBaseExtra(uid, world_pos, baseExtra);
	}
	result["coins"] = payData.coins;
	result["coins2"] = payData.cash;

	result["invite_count"] = user.invite_count;
	result["today_invite_count"] = user.today_invite_count;
	result["resources"].resize(5);
	result["resources"][(unsigned) 0]["c"] = user.r1>user.r1_max?user.r1_max:user.r1;
	result["resources"][(unsigned) 1]["c"] = user.r2>user.r2_max?user.r2_max:user.r2;
	result["resources"][(unsigned) 2]["c"] = user.r3>user.r3_max?user.r3_max:user.r3;
	result["resources"][(unsigned) 3]["c"] = user.r4>user.r4_max?user.r4_max:user.r4;
	result["resources"][(unsigned) 4]["c"] = 0;
	result["r5"] = user.r5;
	result["r5_max"] = user.r5_max;
	result["currencys"][(unsigned) 0] = user.gcbase;
	result["currencys"][(unsigned) 1] = user.gcbuy;
	result["currencys"][(unsigned) 2] = user.prosper;
	result["currencys"][(unsigned) 3] = user.battle_spirits;
	result["sstate"] = user.sstate;
	return 0;
}
int CLogicArchive::Updates(unsigned uid, unsigned uidBy,Json::Value &data, Json::Value &result)
{
	int ret = 0;
	if (uid != uidBy && IsValidUid(uid))
	{
		CLogicHelpHist logicHelphist;
		CLogicUpdates logicUpdates;
		if (Json::IsObject(data, "updates")	&& Json::IsArray(data["updates"], "data"))
		{
			for(unsigned i=0;i<data["updates"]["data"].size();++i)
			{
				string helpType;
				Json::GetString(data["updates"]["data"][i], "s", helpType);
				if(helpType == "BHWATER")
				{
					CLogicBuilding logicBuilding;
					AUTO_LOCK_USER(uid)
					ret = logicBuilding.Water(uid,uidBy);
					if(ret)
						return ret;
					logicUpdates.AddUpdates(uid, data["updates"]["data"][i]);
				}
				else
				{
					ret = logicUpdates.AddUpdates(uid, data["updates"]["data"][i],false, true);
					if (ret != 0)
						return ret;
				}
			}
			//增加帮助信息
			CLogicUserInteract logicInteract;
			logicInteract.AddHelp(uidBy, uid);
			logicInteract.AddFriendInteract(uidBy, uid, "HELP");
			logicHelphist.AddHelpHist(uid, data["updates"]["data"]);
		}
		if (Json::IsObject(data, "tribute2"))
		{
			bool bfull = false;
			CLogicTribute logicTribute;
			ret = logicTribute.Tribute(uid, uidBy, data["tribute2"],bfull);
			if (ret != 0)
				return ret;
			if(!bfull)
			{
				unsigned ts = data["ts"].asUInt();
				ret = logicHelphist.AddTributeHist(uid, uidBy, ts);
				if (0 != ret)
					return ret;
			}
		}
		if (Json::IsObject(data, "updateinfo"))
		{
			unsigned sstate = 0;
			if (Json::GetUInt(data["updateinfo"], "sstate", sstate))
			{
				CLogicUser logicUser;
				DataUser user;
				AUTO_LOCK_USER(uid)
				ret = logicUser.GetUserLimit(uid, user);
				if (ret != 0)
				{
					//info_log("[get user faile!][uid=%u,ret=%d]", uid, ret);
					return ret;
				}
				user.sstate = sstate;
				ret = logicUser.SetUserLimit(uid, user);
				if (0 != ret)
				{
					//info_log("[set user faile!][uid=%u,ret=%d]", uid, ret);
					return ret;
				}
			}
		}
	}
	if (Json::IsObject(data, "updateinfo"))
	{
		ret = ProcessUpdateInfo(uidBy, data["updateinfo"], result["updateinfo"]);
		if (ret != 0)
			return ret;
	}

	string broadcast;
	if (Json::GetString(data, "broadcast", broadcast))
	{
		CLogicBroadcast logicBd;
		logicBd.AddBdMessage(broadcast);
	}

	return 0;
}

int CLogicArchive::ProcessOrders(unsigned uid, const Json::Value data,DataPay &payData, bool addable, Json::Value &user_flag, bool &bsave)
{
	bsave = false;

	if (data.isMember("orders")) {
		if (!data["orders"].isArray()) {
			error_log("[orders error][uid=%u,type=%d]", uid,
					data["orders"].type());
			DATA_ERROR_RETURN_MSG("data_orders_error");
		}
		Json::FastWriter writer;
		int totalCoins = 0;
		int totalCash = 0;
		int totalCoins2 = 0;
		string payType;
		for (unsigned i = 0; i < data["orders"].size(); i++)
		{
			if (!data["orders"][i].isArray()
					|| data["orders"][i].size() != 4
					|| !data["orders"][i][(unsigned)0].isString()
					|| !data["orders"][i][(unsigned)1].isIntegral()
					|| !data["orders"][i][(unsigned)2].isIntegral()
					|| !data["orders"][i][(unsigned)3].isIntegral())
			{
				error_log("[orders error][uid=%u,index=%d,data=%s]",uid,i,(writer.write(data["orders"][i])).c_str());
				DATA_ERROR_RETURN_MSG("data_orders_error");
			}
			int orderType = data["orders"][i][(unsigned)3].asInt();
			if (orderType != 0 && orderType != 1 && orderType != 2)
			{
				error_log("[orders error][uid=%u,index=%d,data=%s]",uid,i,(writer.write(data["orders"][i])).c_str());
				DATA_ERROR_RETURN_MSG("orders_type_error");
			}

			int price = data["orders"][i][(unsigned)1].asInt();
			if(!addable && price > 0)
			{
				error_log("[not addable][uid=%u,index=%d,data=%s]",uid,i,(writer.write(data["orders"][i])).c_str());
				continue;
			}
			if(price == 0)
			{
				error_log("[price error][uid=%u,index=%d,data=%s]",uid,i,(writer.write(data["orders"][i])).c_str());
				DATA_ERROR_RETURN_MSG("o_p_error");
			}

			const char *pCode = data["orders"][i][(unsigned)0].asCString();
			int amount = data["orders"][i][(unsigned)2].asInt();

			string code(pCode);
			if (orderType == 1)
			{
				if(price > 0)
				{
					if(OpenPlatform::GetType() != PT_TEST)
					{
						ORDERS_LOG("cash_too_large:uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,pCode,price,amount,orderType);
						LOGIC_ERROR_RETURN_MSG("order_too_large");
					}
				}
				totalCash += price * amount;
			}
			else if(0 == orderType)
			{
				int maxp = OpenPlatform::IsEN()?5000:0;
				if(price > maxp
				&& OpenPlatform::GetType() != PT_TEST)
				{
					ORDERS_LOG("coin_too_large:uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,pCode,price,amount,orderType);
					LOGIC_ERROR_RETURN_MSG("order_too_large");
				}
				if(price > 0 && amount > 1)
				{
					ORDERS_LOG("amount_too_large:uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,pCode,price,amount,orderType);
					LOGIC_ERROR_RETURN_MSG("order_too_large");
				}
				totalCoins += price * amount;
			}
			else if(2 == orderType)
			{
				if(price > 0 && OpenPlatform::GetType() != PT_TEST)
				{
					ORDERS_LOG("hero_too_large:uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,pCode,price,amount,orderType);
					LOGIC_ERROR_RETURN_MSG("order_too_large");
				}
				totalCoins2 += price * amount;
			}

			if (amount <= 0)
			{
				ORDERS_LOG("amount_error!uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,pCode,price,amount,orderType);
				LOGIC_ERROR_RETURN_MSG("order_too_large");
			}

			ORDERS_LOG("uid=%u&code=%s&price=%d&amount=%d&type=%d",uid,pCode,price,amount,orderType);

			if (!payType.empty()) payType.append(";");
			payType.append(pCode).append(":").append(CTrans::ITOS(amount));
		}

		bool saveHero = false, saveCash = false;
		if (totalCash != 0 || totalCoins != 0)
		{
			CLogicPay logicPay;
			int ret = logicPay.ChangePay(uid, totalCash, totalCoins, payData, payType, user_flag,saveCash);
			if (ret != 0)
			return ret;
		}

		if(totalCoins2 != 0)
		{
			saveHero = true;

			CLogicPay logicPay;
			int ret = logicPay.ChangePayHeroCoins(uid, totalCoins2, payType, user_flag);
			if (ret != 0)
				return ret;
		}
		bsave = saveHero || saveCash;
	}
	return 0;
}

int CLogicArchive::UpdateAttack(const DataUser &user,const DataUser &userDefence, Json::Value &data, int* rchg)
{
	int ret = 0;

	if (data.isMember("lootreport") || data.isMember("attackreport")) {
		Json::FastWriter writer;
		//更新进攻历史
		DataAttack attackData;
		attackData.attack_uid = user.uid;
		attackData.defence_uid = userDefence.uid;
		attackData.attack_platform = OpenPlatform::GetType();
		attackData.r1_loot = 0;
		attackData.r2_loot = 0;
		attackData.r3_loot = 0;
		attackData.r4_loot = 0;
		attackData.r5_loot = 0;

		/*
		if (data.isMember("lootreport") && data["lootreport"].isObject()) {
			Json::GetInt(data["lootreport"], "r1", attackData.r1_loot);
			Json::GetInt(data["lootreport"], "r2", attackData.r2_loot);
			Json::GetInt(data["lootreport"], "r3", attackData.r3_loot);
			Json::GetInt(data["lootreport"], "r4", attackData.r4_loot);
			Json::GetInt(data["lootreport"], "r5", attackData.r5_loot);
		}
		*/
		attackData.r1_loot = rchg[0];
		attackData.r2_loot = rchg[1];
		attackData.r3_loot = rchg[2];
		attackData.r4_loot = rchg[3];

		if (data.isMember("attackreport")) {
			attackData.log = writer.write(data["attackreport"]);
		}

		CLogicAttack logicAttack;
		//ret = logicAttack.UpdateAttack(attackData);
		uint64_t attackId = 0;
		ret = logicAttack.UpdateAttack(attackData, attackId);
		if (ret != 0)
			return ret;
		//attackid|进攻者id|进攻者等级|被进攻者id|被进攻者等级|damage
		int damage = 0;
		Json::GetInt(data, "damage", damage);
		int attackend = 0;
		if (Json::GetInt(data, "attackend", attackend) && attackend == 1) {
			ATTACK_LOG("%lu|%u|%d|%u|%d|%d|%d|%d|%d|%d|%d|", attackId, user.uid,
					user.level, userDefence.uid, userDefence.level, damage,
					attackData.r1_loot, attackData.r2_loot, attackData.r3_loot,
					attackData.r4_loot, attackData.r5_loot);
		}
	}

	return 0;
}
int CLogicArchive::ProcessAttackInfo(unsigned uid,Json::Value &attackinfo, Json::Value &result, unsigned attackuid, LoadType type, bool res, int* rchg)
{
	if (!attackinfo.isObject()) {
		error_log("[attackinfo type error][uid=%u]", uid);
		PARAM_ERROR_RETURN_MSG("param_error");
	}
	if (attackinfo.isNull())
		return 0;

	unsigned fcm = 0;
	Json::GetUInt(attackinfo,"fcm",fcm);
	if(fcm >= e_fcm_max)
		return R_ERR_PARAM;

	CLogicUser logicUser;
	DataUser user;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid, user,uid);
	if (ret != 0)
		return ret;

	unsigned lasttime = 0;
	unsigned seqid = 0;
	Json::GetUInt(attackinfo, "seqid", seqid);
	Json::GetUInt(attackinfo, "lastime", lasttime);
	if (lasttime != user.last_save_time || seqid != user.lastseq + 1)
	{
		result["lasttime"] = user.last_save_time;
		result["lastseq"] = user.lastseq;

		error_log(
				"[lasttime_mismatch][operater=%u,lasttime=%u,last_save_time=%u,seqid=%u,lastseq=%u]",
				uid, lasttime, user.last_save_time, seqid, user.lastseq);
		//LOGIC_ERROR_RETURN_MSG("lasttime_mismatch");
		return 0;
	}
	user.last_save_time = Time::GetGlobalTime();
	user.lastseq = seqid;
	result["lasttime"] = user.last_save_time;
	result["lastseq"] = user.lastseq;
	//debug_log("operater=%u,lasttime=%u,seqid=%u",uid,lasttime,seqid);

	int gcbaschg = 0, gcbuychg = 0, addprosper = 0, addbs = 0, itemp = 0;
	int qleold = -1, qlechg = 0, qleres = -1;
	int ylold = -1, ylchg = 0, ylres = -1;
	int betold = -1, betchg = 0, betres = -1;
	int exp = 0;
	bool needJuexueLog = false;
	int gate_cost = 0;
	string rcode;
	if(attackinfo.isMember("rcode"))
		rcode = attackinfo["rcode"].asString();

	if (Json::IsArray(attackinfo, "currencys"))
	{
		if (attackinfo["currencys"].size() > 0)
		{
			if (Json::GetInt(attackinfo["currencys"], (unsigned)0, gcbaschg) && gcbaschg != 0)
			{
				if(gcbaschg > 0)//移后端，禁止加
				{
					error_log("[gcbaschg error]uid=%u,gcbaschg=%u", uid, gcbaschg);
					gcbaschg = 0;
				}
				else
					gate_cost -= gcbaschg;
				itemp = gcbaschg + user.gcbase;
				if (itemp >= 0)
					user.gcbase += gcbaschg;
				else {
					user.gcbase = 0;
					error_log("[resource_error][uid=%u,gcbaschg=%d]", uid, gcbaschg);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
		if (attackinfo["currencys"].size() > 1)
		{
			if (Json::GetInt(attackinfo["currencys"], (unsigned)1, gcbuychg) && gcbuychg != 0)
			{
				if(gcbuychg > 0)//移后端，禁止加
				{
					error_log("[gcbuychg error]uid=%u,gcbuychg=%u", uid, gcbuychg);
					gcbuychg = 0;
				}
				else
					gate_cost -= gcbuychg;
				itemp = gcbuychg + user.gcbuy;
				if (itemp >= 0)
					user.gcbuy += gcbuychg;
				else {
					user.gcbuy = 0;
					error_log("[resource_error][uid=%u,gcbuychg=%d]", uid, gcbuychg);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
		if (attackinfo["currencys"].size() > 2)
		{
			if (Json::GetInt(attackinfo["currencys"], (unsigned)2, addprosper) && addprosper != 0)
			{
				itemp = addprosper + user.prosper;
				if (itemp >= 0)
					user.prosper += addprosper;
				else {
					error_log("[resource_error][uid=%u]", uid);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
		if (attackinfo["currencys"].size() > 3)
		{
			if (Json::GetInt(attackinfo["currencys"], (unsigned)3, addbs) && addbs != 0)
			{
				if(addbs > 0)//移后端，禁止加
				{
					error_log("[addbs error]uid=%u,addbs=%u", uid, addbs);
					addbs = 0;
				}
				itemp = addbs + user.battle_spirits;
				if (itemp >= 0)
					user.battle_spirits += addbs;
				else {
					error_log("[resource_error][uid=%u]", uid);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
	}
	bool npc = IsCityNPCUid(attackuid) || IsValidAllianceBossId(attackuid) || IsValidWorldBossId(attackuid);
	bool min = IsCityNPCUid(attackuid);
	int r1chg = 0, r2chg = 0, r3chg = 0, r4chg = 0, r5chg = 0;
	if(Json::IsArray(attackinfo, "resources"))
	{
		if (attackinfo["resources"].size() > 0)
		{
			if (Json::GetInt(attackinfo["resources"][(unsigned)0], "d", r1chg))
			{
				if(r1chg > 0)
					r1chg = (int)(r1chg * FCM_VALUE[fcm]);
				if((min && r1chg > NPC_RES_MAX) || (r1chg > 0 && ((!IsValidUid(attackuid) && !npc) || !res || type != LT_ATTACK))){
					error_log("[resource_error][uid=%u]", uid);
					res = false;
					r1chg = 0;
				}else{
					itemp = r1chg + user.r1;
					if (itemp >= 0)
						user.r1 = (unsigned)itemp>user.r1_max?user.r1_max:itemp;
					else {
						if(r1chg > 0)
							user.r1 = user.r1_max;
						else{
							error_log("[resource_error][uid=%u]", uid);
							LOGIC_ERROR_RETURN_MSG("resource_error");
						}
					}
				}
			}
		}
		if (attackinfo["resources"].size() > 1)
		{
			if (Json::GetInt(attackinfo["resources"][(unsigned)1], "d", r2chg))
			{
				if(r2chg > 0)
					r2chg = (int)(r2chg * FCM_VALUE[fcm]);
				if((min && r2chg > NPC_RES_MAX) || (r2chg > 0 && ((!IsValidUid(attackuid) && !npc) || !res || type != LT_ATTACK))){
					error_log("[resource_error][uid=%u]", uid);
					res = false;
					r2chg = 0;
				}else{
					itemp = r2chg + user.r2;
					if (itemp >= 0)
						user.r2 = (unsigned)itemp>user.r2_max?user.r2_max:itemp;
					else {
						if(r2chg > 0)
							user.r2 = user.r2_max;
						else{
							error_log("[resource_error][uid=%u]", uid);
							LOGIC_ERROR_RETURN_MSG("resource_error");
						}
					}
				}
			}
		}
		if (attackinfo["resources"].size() > 2)
		{
			if (Json::GetInt(attackinfo["resources"][(unsigned)2], "d", r3chg))
			{
				if(r3chg > 0)
					r3chg = (int)(r3chg * FCM_VALUE[fcm]);
				if((min && r3chg > NPC_RES_MAX) || (r3chg > 0 && ((!IsValidUid(attackuid) && !npc) || !res || type != LT_ATTACK))){
					error_log("[resource_error][uid=%u]", uid);
					res = false;
					r3chg = 0;
				}else{
					itemp = r3chg + user.r3;
					if (itemp >= 0)
						user.r3 = (unsigned)itemp>user.r3_max?user.r3_max:itemp;
					else {
						if(r3chg > 0)
							user.r3 = user.r3_max;
						else{
							error_log("[resource_error][uid=%u]", uid);
							LOGIC_ERROR_RETURN_MSG("resource_error");
						}
					}
				}
			}
		}
		if (attackinfo["resources"].size() > 3)
		{
			if (Json::GetInt(attackinfo["resources"][(unsigned)3], "d", r4chg))
			{
				if(r4chg > 0)
					r4chg = (int)(r4chg * FCM_VALUE[fcm]);
				if((min && r4chg > NPC_RES_MAX) || (r4chg > 0 && ((!IsValidUid(attackuid) && !npc) || !res || type != LT_ATTACK))){
					error_log("[resource_error][uid=%u]", uid);
					res = false;
					r4chg = 0;
				}else{
					itemp = r4chg + user.r4;
					if (itemp >= 0)
						user.r4 = (unsigned)itemp>user.r4_max?user.r4_max:itemp;
					else {
						if(r4chg > 0)
							user.r4 = user.r4_max;
						else{
							error_log("[resource_error][uid=%u]", uid);
							LOGIC_ERROR_RETURN_MSG("resource_error");
						}
					}
				}
			}
		}
	}

	if (Json::GetInt(attackinfo, "r5", r5chg) && r5chg != 0)
	{
		if(!IsValidUid(attackuid) || type != LT_ATTACK)
		{
			error_log("[resource_error][uid=%u]", uid);
			LOGIC_ERROR_RETURN_MSG("resource_error");
		}
		else
		{
			if(r5chg != 1)
			{
				error_log("[resource_error][uid=%u]", uid);
				LOGIC_ERROR_RETURN_MSG("resource_error");
			}
			else
				++user.r5;
		}
	}

	Json::Reader reader;
	Json::FastWriter writer;

	Json::Value worldres;
	if((IsValidUid(attackuid) || min) && !user.worldres.empty() && reader.parse(user.worldres, worldres))
	{
		int bug = 0;
		Json::GetInt(worldres, "bug", bug);
		if(IsValidUid(attackuid) && type == LT_ATTACK)
		{
			unsigned oldr5 = 0;
			Json::GetUInt(worldres, "r5", oldr5);
			if(user.r5 > oldr5 + 1)
				res = false;
		}
		if(bug == 1 || !res)
		{
			r1chg = r2chg = r3chg = r4chg = r5chg = 0;
			unsigned r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;
			Json::GetUInt(worldres, "r1", r1);
			Json::GetUInt(worldres, "r2", r2);
			Json::GetUInt(worldres, "r3", r3);
			Json::GetUInt(worldres, "r4", r4);
			Json::GetUInt(worldres, "r5", r5);
			user.r1 = r1;
			user.r2 = r2;
			user.r3 = r3;
			user.r4 = r4;
			user.r5 = std::min(user.r5, r5);
			worldres["bug"] = 1;
			user.worldres = writer.write(worldres);
			if(rchg)
				rchg[0] = rchg[1] = rchg[2] = rchg[3] = 0;
		}
		else if(rchg)
		{
			int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
			Json::GetInt(worldres, "r1", r1);
			Json::GetInt(worldres, "r2", r2);
			Json::GetInt(worldres, "r3", r3);
			Json::GetInt(worldres, "r4", r4);
			rchg[0] = std::max(0 ,(int)user.r1 - r1);
			rchg[1] = std::max(0, (int)user.r2 - r2);
			rchg[2] = std::max(0, (int)user.r3 - r3);
			rchg[3] = std::max(0, (int)user.r4 - r4);
		}
	}

	/*Json::GetInt(attackinfo, "exp", exp);
	if(exp > 0)//移后端，禁止加
	{
		error_log("[exp error]uid=%u,exp=%u", uid, exp);
		exp = 0;
	}*/
	if(rcode.find("bd_rob") != string::npos)
		exp += std::min(getResGetAddExp(user.level, r1chg, r2chg, r3chg, r4chg)	, getAttMaxAddExp(user.level));
	if(exp > getMaxAddExp(user.level))
	{
		error_log("[exp_error][operator=%u,expchg=%d]", uid, exp);
		LOGIC_ERROR_RETURN_MSG("exp_error");
	}
	user.point += exp;

	int leveltemp = getLevel(user.point);
	/*Json::GetInt(attackinfo, "level", leveltemp);
	if(leveltemp > 30 && leveltemp > user.level + 1)
	{
		error_log("[level_error][uid=%u]", uid);
		LOGIC_ERROR_RETURN_MSG("level_error");
	}
	else */if(leveltemp != user.level)
	{
		USER_LEVEL_LOG("uid=%u,l=%u",uid,leveltemp);
		user.level =  leveltemp;
		//logicTopTenUser.SetUserLevel(user.uid, user.level);
	}

	if (attackinfo.isMember("soldier"))
	{
		//checksoldier(user.soldier, attackinfo["soldier"]);
		user.soldier = writer.write(attackinfo["soldier"]);
	}
	if (attackinfo.isMember("stats"))
	{
		Json::Value old;
		reader.parse(user.user_stat, old);
		ret = checkUserStats(old,attackinfo["stats"]);
		if(ret != 0)
		{
			error_log("[user_stat error][uid=%u,ret=%u]", uid,ret);
			LOGIC_ERROR_RETURN_MSG("user_stat error");
		}

		if(attackinfo["stats"].isMember("bet"))
		{
			betchg = attackinfo["stats"]["bet"].asInt();
			if(old.isMember("bet"))
				betold = old["bet"].asInt();
			else
				betold = 0;
			betres = betchg + betold;
			if(betres < 0){
				error_log("[resource_error][uid=%u,betchg=%d]", uid, betchg);
				LOGIC_ERROR_RETURN_MSG("resource_error");
			}
			attackinfo["stats"]["bet"] = betres;
		}

		if(gate_cost >= 10 && user.level > 30)
			attackinfo["stats"]["ec1"] = 1;

		user.user_stat = writer.write(attackinfo["stats"]);
	}
	else if(gate_cost >= 10 && user.level > 30)
	{
		Json::Value old;
		reader.parse(user.user_stat, old);
		old["ec1"] = 1;
		user.user_stat = writer.write(old);
	}

	if (attackinfo.isMember("tech"))
	{
		Json::Value OldUserTech;
		reader.parse(user.user_tech, OldUserTech);

		ret = checkUserTech(OldUserTech,attackinfo["tech"]);
		if(ret != 0)
		{
			error_log("[user_tech error][uid=%u,ret=%u]", uid,ret);
			LOGIC_ERROR_RETURN_MSG("user_tech error");
		}

		if (attackinfo["tech"]["godE"].isObject()) {
			if (attackinfo["tech"]["godE"]["qlE"].isArray()) {
				if (OldUserTech["godE"]["qlE"].isArray()) {
					qleold = OldUserTech["godE"]["qlE"][0u].asInt();
					qlechg = attackinfo["tech"]["godE"]["qlE"][0u].asInt();
					qleres = qlechg + qleold;
					if(qleres < 0){
						error_log("[resource_error][uid=%u]", uid);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
					attackinfo["tech"]["godE"]["qlE"][0u] = qleres;
				}
			}
		}

		user.user_tech = writer.write(attackinfo["tech"]);
	}
	//前台不需要处理wood字段
	/*Json::Value statJson;
	 if (user.user_stat.empty())
	 user.user_stat = "{}";
	 if (reader.parse(user.user_stat, statJson))
	 {
	 unsigned wood = 0;
	 if (!statJson.isMember("wood") || Json::GetUInt(statJson, "wood", wood))
	 {
	 wood += r2chg + r3chg + r4chg + r5chg;
	 statJson["wood"] = wood;
	 user.user_stat = writer.write(statJson);
	 }
	 }*/

	if (Json::IsArray(attackinfo, "newAct"))
    {
		CLogicSecinc logicSecinc;
		ret = logicSecinc.SetSecinc(uid, attackinfo["newAct"]);
		if (ret != 0)
			return ret;
	}

	if (Json::IsArray(attackinfo, "hero"))
	{
		CLogicHero logicHero;
		Json::Value res;
		ret = logicHero.UpdateHero(uid, attackinfo["hero"],res,true);
		if (ret != 0)
			return ret;
	}
	if (Json::IsArray(attackinfo, "equipment"))
	{
		CLogicEquipment logicEquip;
		Json::Value res;
		ret = logicEquip.UpdateEquipment(uid, uid, attackinfo["equipment"],res,true);
		if (ret != 0)
			return ret;
	}

	ret = logicUser.SetUser(uid, user);
	if (ret != 0)
		return ret;
	RESOURCE_LOG("[atck change][uid=%u,gcbaschg=%d,gcbase=%u,gcbuychg=%d,gcbuy=%u,r1chg=%d,r1=%u,r2chg=%d,r2=%u,r3chg=%d,r3=%u,r4chg=%d,r4=%u,r5chg=%d,r5=%u,addprosper=%d,prosper=%u,addbs=%d,bs=%u,qlechg=%d,qle=%d,ylchg=%d,yl=%d,betchg=%d,bet=%d,expchg=%u,exp=%u,lvl=%u,code=%s]",
			uid,gcbaschg,user.gcbase,gcbuychg,user.gcbuy,r1chg,user.r1,r2chg,user.r2,r3chg,user.r3,r4chg,user.r4,r5chg,user.r5,addprosper,user.prosper,addbs,user.battle_spirits,qlechg,qleres,ylchg,ylres,betchg,betres,exp,user.point,user.level,rcode.c_str());

	return 0;
}

int CLogicArchive::ProcessUpdateInfo(unsigned uid,Json::Value &updateinfo, Json::Value &result)
{
	if (!updateinfo.isObject()) {
		error_log("[updateinfo type error][uid=%u]", uid);
		PARAM_ERROR_RETURN_MSG("param_error");
	}
	if (updateinfo.isNull())
		return 0;
	CLogicUser logicUser;
	DataUser user;
	AUTO_LOCK_USER(uid)
	int ret = logicUser.GetUser(uid, user, uid);
	if (ret != 0)
		return ret;

	unsigned lasttime = 0;
	unsigned seqid = 0;
	Json::GetUInt(updateinfo, "seqid", seqid);
	Json::GetUInt(updateinfo, "lastime", lasttime);
	if (lasttime != user.last_save_time || seqid != user.lastseq + 1)
	{
		result["lasttime"] = user.last_save_time;
		result["lastseq"] = user.lastseq;

		error_log(
				"[lasttime_mismatch][operater=%u,lasttime=%u,last_save_time=%u,seqid=%u,lastseq=%u]",
				uid, lasttime, user.last_save_time, seqid, user.lastseq);
		//LOGIC_ERROR_RETURN_MSG("lasttime_mismatch");
		return 0;
	}
	user.last_save_time = Time::GetGlobalTime();
	user.lastseq = seqid;
	result["lasttime"] = user.last_save_time;
	result["lastseq"] = user.lastseq;
	//debug_log("operater=%u,lasttime=%u,seqid=%u",uid,lasttime,seqid);

	int gcbaschg = 0, gcbuychg = 0, addprosper = 0, addbs = 0, itemp = 0;
	int qleold = -1, qlechg = 0, qleres = -1;
	int ylold = -1, ylchg = 0, ylres = -1;
	int betold = -1, betchg = 0, betres = -1;
	bool needJuexueLog = false;
	string rcode;
	if(updateinfo.isMember("rcode"))
		rcode = updateinfo["rcode"].asString();

	if (Json::IsArray(updateinfo, "currencys"))
	{
		if (updateinfo["currencys"].size() > 0)
		{
			if (Json::GetInt(updateinfo["currencys"], (unsigned)0, gcbaschg) && gcbaschg != 0)
			{
				if(gcbaschg > 5)//移后端，禁止加
				{
					error_log("[gcbaschg error]uid=%u,gcbaschg=%u", uid, gcbaschg);
					gcbaschg = 0;
				}
				itemp = gcbaschg + user.gcbase;
				if (itemp >= 0)
				user.gcbase += gcbaschg;
				else {
					error_log("[resource_error][uid=%u]", uid);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
		if (updateinfo["currencys"].size() > 1)
		{
			if (Json::GetInt(updateinfo["currencys"], (unsigned)1, gcbuychg) && gcbuychg != 0)
			{
				if(gcbuychg > 0)//移后端，禁止加
				{
					error_log("[gcbuychg error]uid=%u,gcbuychg=%u", uid, gcbuychg);
					gcbuychg = 0;
				}
				itemp = gcbuychg + user.gcbuy;
				if (itemp >= 0)
				user.gcbuy += gcbuychg;
				else {
					error_log("[resource_error][uid=%u]", uid);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
		if (updateinfo["currencys"].size() > 2)
		{
			if (Json::GetInt(updateinfo["currencys"], (unsigned)2, addprosper) && addprosper != 0)
			{
				itemp = addprosper + user.prosper;
				if (itemp >= 0)
				user.prosper += addprosper;
				else {
					error_log("[resource_error][uid=%u]", uid);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
		if (updateinfo["currencys"].size() > 3)
		{
			if (Json::GetInt(updateinfo["currencys"], (unsigned)3, addbs) && addbs != 0)
			{
				if(addbs > 0)//移后端，禁止加
				{
					error_log("[addbs error]uid=%u,addbs=%u", uid, addbs);
					addbs = 0;
				}
				itemp = addbs + user.battle_spirits;
				if (itemp >= 0)
				user.battle_spirits += addbs;
				else {
					error_log("[resource_error][uid=%u]", uid);
					LOGIC_ERROR_RETURN_MSG("resource_error");
				}
			}
		}
	}
	int r1chg = 0, r2chg = 0, r3chg = 0, r4chg = 0, r5chg = 0;
	if (Json::IsArray(updateinfo, "resources"))
	{
		if (updateinfo["resources"].size() > 0)
		{
			if (Json::GetInt(updateinfo["resources"][(unsigned)0], "d", r1chg))
			{
				itemp = r1chg + user.r1;
				if (itemp >= 0)
				user.r1 = (unsigned)itemp>user.r1_max?user.r1_max:itemp;
				else {
					if(r1chg > 0)
						user.r1 = user.r1_max;
					else{
						error_log("[resource_error][uid=%u]", uid);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
				}
			}
		}
		if (updateinfo["resources"].size() > 1)
		{
			if (Json::GetInt(updateinfo["resources"][(unsigned)1], "d", r2chg))
			{
				itemp = r2chg + user.r2;
				if (itemp >= 0)
				user.r2 = (unsigned)itemp>user.r2_max?user.r2_max:itemp;
				else {
					if(r2chg > 0)
						user.r2 = user.r2_max;
					else{
						error_log("[resource_error][uid=%u]", uid);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
				}
			}
		}
		if (updateinfo["resources"].size() > 2)
		{
			if (Json::GetInt(updateinfo["resources"][(unsigned)2], "d", r3chg))
			{
				itemp = r3chg + user.r3;
				if (itemp >= 0)
				user.r3 = (unsigned)itemp>user.r3_max?user.r3_max:itemp;
				else {
					if(r3chg > 0)
						user.r3 = user.r3_max;
					else{
						error_log("[resource_error][uid=%u]", uid);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
				}
			}
		}
		if (updateinfo["resources"].size() > 3)
		{
			if (Json::GetInt(updateinfo["resources"][(unsigned)3], "d", r4chg))
			{
				itemp = r4chg + user.r4;
				if (itemp >= 0)
				user.r4 = (unsigned)itemp>user.r4_max?user.r4_max:itemp;
				else {
					if(r4chg > 0)
						user.r4 = user.r4_max;
					else{
						error_log("[resource_error][uid=%u]", uid);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
				}
			}
		}
	}
	Json::Reader reader;
	Json::FastWriter writer;
	if (updateinfo.isMember("soldier"))
	{
		//checksoldier(user.soldier, updateinfo["soldier"]);
		user.soldier = writer.write(updateinfo["soldier"]);
	}
	if (updateinfo.isMember("stats"))
	{
		Json::Value old;
		reader.parse(user.user_stat, old);
		ret = checkUserStats(old,updateinfo["stats"]);
		if(ret != 0)
		{
			error_log("[user_stat error][uid=%u,ret=%u]", uid,ret);
			LOGIC_ERROR_RETURN_MSG("user_stat error");
		}

		if(updateinfo["stats"].isMember("bet"))
		{
			betchg = updateinfo["stats"]["bet"].asInt();
			if(old.isMember("bet"))
				betold = old["bet"].asInt();
			else
				betold = 0;
			betres = betchg + betold;
			if(betres < 0){
				error_log("[resource_error][uid=%u,betchg=%d]", uid, betchg);
				LOGIC_ERROR_RETURN_MSG("resource_error");
			}
			updateinfo["stats"]["bet"] = betres;
		}

		user.user_stat = writer.write(updateinfo["stats"]);
	}
	if (updateinfo.isMember("tech"))
	{
		Json::Value OldUserTech;
		reader.parse(user.user_tech, OldUserTech);

		ret = checkUserTech(OldUserTech,updateinfo["tech"]);
		if(ret != 0)
		{
			error_log("[user_tech error][uid=%u,ret=%u]", uid,ret);
			LOGIC_ERROR_RETURN_MSG("user_tech error");
		}

		if (updateinfo["tech"]["godE"].isObject()) {
			if (updateinfo["tech"]["godE"]["qlE"].isArray()) {
				if (OldUserTech["godE"]["qlE"].isArray()) {
					qleold = OldUserTech["godE"]["qlE"][0u].asInt();
					qlechg = updateinfo["tech"]["godE"]["qlE"][0u].asInt();
					qleres = qlechg + qleold;
					if(qleres < 0){
						error_log("[resource_error][uid=%u]", uid);
						LOGIC_ERROR_RETURN_MSG("resource_error");
					}
					updateinfo["tech"]["godE"]["qlE"][0u] = qleres;
				}
			}
		}

		user.user_tech = writer.write(updateinfo["tech"]);
	}

	if (Json::IsArray(updateinfo, "newAct"))
    {
		CLogicSecinc logicSecinc;
		ret = logicSecinc.SetSecinc(uid, updateinfo["newAct"]);
		if (ret != 0)
			return ret;
	}

	ret = logicUser.SetUser(uid, user);
	if (ret != 0)
		return ret;
	RESOURCE_LOG("[updt change][uid=%u,gcbaschg=%d,gcbase=%u,gcbuychg=%d,gcbuy=%u,r1chg=%d,r1=%u,r2chg=%d,r2=%u,r3chg=%d,r3=%u,r4chg=%d,r4=%u,r5chg=%d,r5=%u,addprosper=%d,prosper=%u,addbs=%d,bs=%u,qlechg=%d,qle=%d,ylchg=%d,yl=%d,betchg=%d,bet=%d,expchg=%u,exp=%u,lvl=%u,code=%s]",
			uid,gcbaschg,user.gcbase,gcbuychg,user.gcbuy,r1chg,user.r1,r2chg,user.r2,r3chg,user.r3,r4chg,user.r4,r5chg,user.r5,addprosper,user.prosper,addbs,user.battle_spirits,qlechg,qleres,ylchg,ylres,betchg,betres,0,user.point,user.level,rcode.c_str());

	return 0;
}

int CLogicArchive::GetActivityTime(Json::Value &data)
{
	string rangeTime = Config::GetValue(CONFIG_MYSTICALSHOP_RANGE_TS);
	Json::Value value;
	Json::Reader().parse(rangeTime, value);
	data["mysticalTime"] = value;

	unsigned beginTime = 0;
	unsigned endTime = 0;
	unsigned version = 0;
	string platform;
	string type;
	unsigned midTime = 0;
	//后台活动返回给前台统一格式顺序为：开始时间，结束时间，版本号（没版本号就返回0），平台号（没有加配置的就返回all）
	Json::Value activityTime = Json::Value(Json::arrayValue);
	if (Config::GetUIntValue(beginTime, "twice_reward_b")
			&& Config::GetUIntValue(endTime, "twice_reward_e")) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = 0;
		activityTime[3u] = "all";
		data["wolong"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_SUNCE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_SUNCE_END_TS)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = 0;
		activityTime[3u] = "all";
		data["sunce"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_PAY_OF_HUNDRED_DAYS_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_PAY_OF_HUNDRED_DAYS_END_TS)
			&& Config::GetValue(platform, CONFIG_PAY_OF_HUNDRED_DAYS_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime + 22*60*60;
		activityTime[2u] = 0;
		activityTime[3u] = platform;
		data["lebusishu"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_POINTS_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_POINTS_END_TS)
			&& Config::GetValue(platform, CONFIG_POINTS_PF)
			&& Config::GetUIntValue(version, CONFIG_POINTS_VERSION)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["jug"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_MERRYSOULS_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_MERRYSOULS_END_TS)
			&& Config::GetValue(platform, CONFIG_MERRYSOULS_PF)
			&& Config::GetUIntValue(version, CONFIG_MERRYSOULS_VERSION)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["zhongqiu"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_DOUBLE_EXPERIENCE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_DOUBLE_EXPERIENCE_END_TS)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = 0;
		activityTime[3u] = "all";
		data["doubleExp"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_MONEYTREE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_MONEYTREE_END_TS)
			&& Config::GetValue(platform, CONFIG_MONEYTREE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = 0;
		activityTime[3u] = platform;
		data["moneytree"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_DOUBLE_BARBARIAN_BEGIN)
			&& Config::GetUIntValue(endTime, CONFIG_DOUBLE_BARBARIAN_END)
			&& Config::GetValue(platform, CONFIG_NANMAN_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = 0;
		activityTime[3u] = platform;
		data["nanman"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_GATE_ZONGZI_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_GATE_ZONGZI_END_TS)
			&& Config::GetValue(platform, CONFIG_GATE_ZONGZI_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = 0;
		activityTime[3u] = platform;
		data["zongzi"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_DIANJIANG_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_DIANJIANG_END_TS)
			&& Config::GetUIntValue(version, CONFIG_DIANJIANG_VER)
			&& Config::GetValue(platform, CONFIG_DIANJIANG_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["dianjiang"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_MONTH_LIBAO_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_MONTH_LIBAO_END_TS)
			&& Config::GetUIntValue(version, CONFIG_MONTH_LIBAO_VER)
			&& Config::GetValue(platform, CONFIG_MONTH_LIBAO_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["libao"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_VIPBAG_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_VIPBAG_END_TS)
			&& Config::GetUIntValue(version, CONFIG_VIPBAG_VER)
			&& Config::GetValue(platform, CONFIG_VIPBAG_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["vipbag"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_TREASURE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_TREASURE_END_TS)
			&& Config::GetUIntValue(version, CONFIG_TREASURE_VER)
			&& Config::GetValue(platform, CONFIG_TREASURE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["treasurehunt"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_PAY_OF_QIXIJIE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_PAY_OF_QIXIJIE_END_TS)
			&& Config::GetUIntValue(version, CONFIG_PAY_OF_QIXIJIE_VERSION)
			&& Config::GetValue(platform, CONFIG_PAY_OF_QIXIJIE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime + 86400;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["qixijie"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_TUANGOU_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_TUANGOU_END_TS)
			&& Config::GetUIntValue(version, CONFIG_TUANGOU_VER)
			&& Config::GetValue(platform, CONFIG_TUANGOU_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["tuangou"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_YUANDAN_B_TS)
			&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_YUANDAN_E_TS)
			&& Config::GetUIntValue(version, CONFIG_ACTIVITY_YUANDAN_VER)
			&& Config::GetValue(platform, CONFIG_ACTIVITY_YUANDAN_PF)
			&& Config::GetValue(type, CONFIG_ACTIVITY_YUANDAN_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["yuandan"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_HAPPYCARD_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_HAPPYCARD_END_TS)
			&& Config::GetUIntValue(version, CONFIG_HAPPYCARD_VER)
			&& Config::GetValue(platform, CONFIG_HAPPYCARD_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["happycard"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_TOMB_TREASURE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_TOMB_TREASURE_END_TS)
			&& Config::GetUIntValue(version, CONFIG_TOMB_TREASURE_VER)
			&& Config::GetValue(platform, CONFIG_TOMB_TREASURE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["tomb"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_HEQU_ACTIVITY_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_HEQU_ACTIVITY_END_TS)
			&& Config::GetUIntValue(version, CONFIG_HEQU_ACTIVITY_VER)
			&& Config::GetValue(platform, CONFIG_HEQU_ACTIVITY_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["hequ_activity"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_DIG_STONE_B_TS)
			&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_DIG_STONE_E_TS)
			&& Config::GetUIntValue(version, CONFIG_ACTIVITY_DIG_STONE_VER)
			&& Config::GetValue(platform, CONFIG_ACTIVITY_DIG_STONE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["dig_stone"] = activityTime;
	}
/*  武魂打折活动屏蔽
	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_WUHUN_B_TS)
			&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_WUHUN_E_TS)
			&& Config::GetUIntValue(version, CONFIG_ACTIVITY_WUHUN_VER)
			&& Config::GetValue(platform, CONFIG_ACTIVITY_WUHUN_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["wuhun"] = activityTime;
	}
*/
	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_MOONCAKE_B_TS)
			&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_MOONCAKE_E_TS)
			&& Config::GetUIntValue(version, CONFIG_ACTIVITY_MOONCAKE_VER)
			&& Config::GetValue(platform, CONFIG_ACTIVITY_MOONCAKE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["mooncake"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_ZHENBAOGE_B_TS)
			&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_ZHENBAOGE_E_TS)
			&& Config::GetUIntValue(version, CONFIG_ACTIVITY_ZHENBAOGE_VER)
			&& Config::GetValue(platform, CONFIG_ACTIVITY_ZHENBAOGE_PF)
			&& Config::GetValue(type, CONFIG_ACTIVITY_ZHENBAOGE_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["zhenbaoge"] = activityTime;
	}


	if (Config::GetUIntValue(beginTime, CONFIG_SR_CHARGE_REBATES_BEGIN_TS)
				&& Config::GetUIntValue(endTime, CONFIG_SR_CHARGE_REBATES_END_TS)
				&& Config::GetUIntValue(version, CONFIG_SR_CHARGE_REBATES_VER)
				&& Config::GetValue(platform, CONFIG_SR_CHARGE_REBATES_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["srchg_rebates"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_LR_CHARGE_REBATES_BEGIN_TS)
					&& Config::GetUIntValue(endTime, CONFIG_LR_CHARGE_REBATES_END_TS)
					&& Config::GetUIntValue(version, CONFIG_LR_CHARGE_REBATES_VER)
					&& Config::GetValue(platform, CONFIG_LR_CHARGE_REBATES_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["lrchg_rebates"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_PART_STONE_BEGIN_TS)
					&& Config::GetUIntValue(endTime, CONFIG_PART_STONE_END_TS)
					&& Config::GetUIntValue(version, CONFIG_PART_STONE_VER)
					&& Config::GetValue(platform, CONFIG_PART_STONE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["part_stone"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_OLD_USER_BEGIN_TS)
					&& Config::GetUIntValue(endTime, CONFIG_OLD_USER_END_TS)
					&& Config::GetUIntValue(version, CONFIG_OLD_USER_VER)
					&& Config::GetValue(platform, CONFIG_OLD_USER_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["old_user"] = activityTime;
	}


	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_FAIRYLAND_BEGIN_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_FAIRYLAND_END_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_FAIRYLAND_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_FAIRYLAND_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["fairyland"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_RESTRICTION_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_RESTRICTION_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_RESTRICTION_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_RESTRICTION_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["restriction"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_TRE_BOWL_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_TRE_BOWL_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_TRE_BOWL_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_TRE_BOWL_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["tre_bowl"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_SNAP_STONE_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_SNAP_STONE_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_SNAP_STONE_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_SNAP_STONE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["snap_stone"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_SNAP_BINGSHU_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_SNAP_BINGSHU_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_SNAP_BINGSHU_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_SNAP_BINGSHU_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["snap_bingshu"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_NEW_LOTTERY_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_NEW_LOTTERY_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_NEW_LOTTERY_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_NEW_LOTTERY_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["new_lottery"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_TUMO_DOUBLE_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_TUMO_DOUBLE_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_TUMO_DOUBLE_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_TUMO_DOUBLE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["tumo"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_CONSUME_RANK_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_CONSUME_RANK_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_CONSUME_RANK_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_CONSUME_RANK_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["consume_rank"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_RECHARGE_RANK_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_RECHARGE_RANK_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_RECHARGE_RANK_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_RECHARGE_RANK_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["recharge_rank"] = activityTime;
	}


	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_SNAP_DUNJIA_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_SNAP_DUNJIA_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_SNAP_DUNJIA_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_SNAP_DUNJIA_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["snap_dunjia"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_GALLERY_BEGIN_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_GALLERY_END_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_GALLERY_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_GALLERY_PF)
					&& Config::GetValue(type, CONFIG_ACTIVITY_GALLERY_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["gallert"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_MIRROR_BEGIN_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_MIRROR_END_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_MIRROR_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_MIRROR_PF)
					&& Config::GetValue(type, CONFIG_ACTIVITY_MIRROR_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["mirror"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_GEM_STONE_B_TS)
					&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_GEM_STONE_E_TS)
					&& Config::GetUIntValue(version, CONFIG_ACTIVITY_GEM_STONE_VER)
					&& Config::GetValue(platform, CONFIG_ACTIVITY_GEM_STONE_PF)
					&& Config::GetValue(type, CONFIG_ACTIVITY_GEM_STONE_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["synthesis"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_PAYRANK_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_PAYRANK_END_TS)
			&& Config::GetUIntValue(version, CONFIG_PAYRANK_VERSION)
			&& Config::GetValue(platform, CONFIG_PAYRANK_PF)
			&& Config::GetValue(type, CONFIG_PAYRANK_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["points"] = activityTime;

	}

	if (Config::GetUIntValue(beginTime, CONFIG_VIP_CHARGE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_VIP_CHARGE_END_TS)
			&& Config::GetUIntValue(version, CONFIG_VIP_CHARGE_VER)
			&& Config::GetValue(platform, CONFIG_VIP_CHARGE_PF)
			&& Config::GetValue(type, CONFIG_VIP_CHARGE_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["bluecreditdata"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ALLIANCE_RECHARGE_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_ALLIANCE_RECHARGE_END_TS)
			&& Config::GetUIntValue(version, CONFIG_ALLIANCE_RECHARGE_VER)
			&& Config::GetValue(platform, CONFIG_ALLIANCE_RECHARGE_PF)
			&& Config::GetValue(type, CONFIG_ALLIANCE_RECHARGE_TYPE)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		data["alli_recharge"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_PAY_TOTAL_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_PAY_TOTAL_END_TS)
			&& Config::GetValue(platform, CONFIG_PAY_TOTAL_PF)
			&& Config::GetValue(type, CONFIG_PAYTOTAL_RETURN_TYPE)
			&& Config::GetUIntValue(midTime, CONFIG_PAYTOTAL_MIDDLE_TS)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = 0;
		activityTime[3u] = platform;
		activityTime[4u] = type;
		activityTime[5u] = midTime;
		data["paytotal"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ZAOHUA_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_ZAOHUA_END_TS)
		&& Config::GetUIntValue(version, CONFIG_ZAOHUA_VER)
		&& Config::GetValue(platform, CONFIG_ZAOHUA_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["zaohua"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_TEMAI_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_TEMAI_END_TS)
		&& Config::GetUIntValue(version, CONFIG_TEMAI_VER)
		&& Config::GetValue(platform, CONFIG_TEMAI_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["temai"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ZIYUAN_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_ZIYUAN_END_TS)
		&& Config::GetUIntValue(version, CONFIG_ZIYUAN_VER)
		&& Config::GetValue(platform, CONFIG_ZIYUAN_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["ziyuan"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_DIANJIANGTAI_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_DIANJIANGTAI_END_TS)
		&& Config::GetUIntValue(version, CONFIG_DIANJIANGTAI_VER)
		&& Config::GetValue(platform, CONFIG_DIANJIANGTAI_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["dianjiangtai"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ZHIZUN_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_ZHIZUN_END_TS)
		&& Config::GetUIntValue(version, CONFIG_ZHIZUN_VER)
		&& Config::GetValue(platform, CONFIG_ZHIZUN_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["zhizun"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ACTIVITY_DRAGON_SCALE_B_TS)
		&& Config::GetUIntValue(endTime, CONFIG_ACTIVITY_DRAGON_SCALE_E_TS)
		&& Config::GetUIntValue(version, CONFIG_ACTIVITY_DRAGON_SCALE_VER)
		&& Config::GetValue(platform, CONFIG_ACTIVITY_DRAGON_SCALE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["dragonScale"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_DUANWUJIE_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_DUANWUJIE_END_TS)
		&& Config::GetUIntValue(version, CONFIG_DUANWUJIE_VER)
		&& Config::GetValue(platform, CONFIG_DUANWUJIE_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["duanwujie"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_TAOZHUANG_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_TAOZHUANG_END_TS)
		&& Config::GetUIntValue(version, CONFIG_TAOZHUANG_VER)
		&& Config::GetValue(platform, CONFIG_TAOZHUANG_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["taozhuang"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_PEIYANG_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_PEIYANG_END_TS)
		&& Config::GetUIntValue(version, CONFIG_PEIYANG_VER)
		&& Config::GetValue(platform, CONFIG_PEIYANG_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["peiyang"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_SUMMER_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_SUMMER_END_TS)
		&& Config::GetUIntValue(version, CONFIG_SUMMER_VER)
		&& Config::GetValue(platform, CONFIG_SUMMER_PF)) {
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["summer"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_LIMIT_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_LIMIT_END_TS)
		&& Config::GetUIntValue(version, CONFIG_LIMIT_VER)
		&& Config::GetValue(platform, CONFIG_LIMIT_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["limit"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_QIXI_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_QIXI_END_TS)
		&& Config::GetUIntValue(version, CONFIG_QIXI_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["qixi"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_MULTIPLE_WHEEL_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_MULTIPLE_WHEEL_END_TS)
		&& Config::GetUIntValue(version, CONFIG_MULTIPLE_WHEEL_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["multipleWheel"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_HAMMERHIT_ALLSERVER_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_HAMMERHIT_ALLSERVER_END_TS)
		&& Config::GetUIntValue(version, CONFIG_HAMMERHIT_ALLSERVER_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["hammerHitAllServer"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_DOUBLE11_ALLSERVER_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_DOUBLE11_ALLSERVER_END_TS)
		&& Config::GetUIntValue(version, CONFIG_DOUBLE11_ALLSERVER_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["double11"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_JUEXINGTEHUI_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_JUEXINGTEHUI_END_TS)
		&& Config::GetUIntValue(version, CONFIG_JUEXINGTEHUI_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["juexingtehui"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_SHIWAITAOYUAN_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_SHIWAITAOYUAN_END_TS)
		&& Config::GetUIntValue(version, CONFIG_SHIWAITAOYUAN_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["shiwaitaoyuan"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_WUJIANGSHEGNXING_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_WUJIANGSHEGNXING_END_TS)
		&& Config::GetUIntValue(version, CONFIG_WUJIANGSHEGNXING_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["wujiangshengxing"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_FUDAIHUODONG_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_FUDAIHUODONG_END_TS)
		&& Config::GetUIntValue(version, CONFIG_FUDAIHUODONG_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["fudaihuodong"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_HITEGG_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_HITEGG_END_TS)
		&& Config::GetUIntValue(version, CONFIG_HITEGG_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["hitegg"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_LOTTERY_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_LOTTERY_END_TS)
		&& Config::GetUIntValue(version, CONFIG_LOTTERY_VER))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["lottery"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_CHARGE_BINGSHU_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_CHARGE_BINGSHU_END_TS)
		&& Config::GetUIntValue(version, CONFIG_CHARGE_BINGSHU_VERSION))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["charge_bingshu"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_JINQIUSHIYUE_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_JINQIUSHIYUE_END_TS))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		data["jinqiushiyue"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_COMBINE_SHOP_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_COMBINE_SHOP_END_TS)
		&& Config::GetUIntValue(version, CONFIG_COMBINE_SHOP_VERSION))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["combine_shop"] = activityTime;
	}
	if (Config::GetUIntValue(beginTime, CONFIG_DEDAOZHENREN_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_DEDAOZHENREN_END_TS)
		&& Config::GetUIntValue(version, CONFIG_DEDAOZHENREN_VER)
		&& Config::GetValue(platform, CONFIG_DEDAOZHENREN_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["dedaozhenren"] = activityTime;
	}

	//暑假前奏
	if (Config::GetUIntValue(beginTime, CONFIG_PRE_SUMMER_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_PRE_SUMMER_END_TS)
		&& Config::GetUIntValue(version, CONFIG_PRE_SUMMER_VERSION))
	{
		activityTime.clear();

		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["pre_summer"] = activityTime;
	}
	//暑假前奏2
	if (Config::GetUIntValue(beginTime, CONFIG_PRE_SUMMER2_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_PRE_SUMMER2_END_TS)
		&& Config::GetUIntValue(version, CONFIG_PRE_SUMMER2_VERSION))
	{
		activityTime.clear();

		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["pre_summer2"] = activityTime;
	}
	//暑假前奏3
	if (Config::GetUIntValue(beginTime, CONFIG_PRE_SUMMER3_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_PRE_SUMMER3_END_TS)
		&& Config::GetUIntValue(version, CONFIG_PRE_SUMMER3_VERSION))
	{
		activityTime.clear();

		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["pre_summer3"] = activityTime;
	}

	//新绝世无双
	if (Config::GetUIntValue(beginTime, CONFIG_NEWJUESHIWS_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_NEWJUESHIWS_END_TS)
		&& Config::GetUIntValue(version, CONFIG_NEWJUESHIWS_VER)
		&& Config::GetValue(platform, CONFIG_NEWJUESHIWS_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["new_jueshiws"] = activityTime;
	}

	//厚惠有期
	if (Config::GetUIntValue(beginTime, CONFIG_LARGE_FAVORABLE_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_LARGE_RAVORABLE_END_TS)
		&& Config::GetUIntValue(version, CONFIG_LARGE_RAVORABLE_VER)
		&& Config::GetValue(platform, CONFIG_LARGE_RAVORABLE_PF))
	{
		activityTime.clear();

		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["large_favorable"] = activityTime;
	}

	//鸿运当头
	if (Config::GetUIntValue(beginTime, CONFIG_OPPOR_KNOCK_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_OPPOR_KNOCK_END_TS)
		&& Config::GetUIntValue(version, CONFIG_OPPOR_KNOCK_VER)
		&& Config::GetValue(platform, CONFIG_OPPOR_KNOCK_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["oppor_knock"] = activityTime;
	}

	//幸运连连
	if (Config::GetUIntValue(beginTime, CONFIG_FORTUNATELY_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_FORTUNATELY_END_TS)
		&& Config::GetUIntValue(version, CONFIG_FORTUNATELY_VER)
		&& Config::GetValue(platform, CONFIG_FORTUNATELY_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["fortunately_again"] = activityTime;
	}

	//充值自选
	if (Config::GetUIntValue(beginTime, CONFIG_RECHARGE_OPTIONAL_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_RECHARGE_OPTIONAL_END_TS)
		&& Config::GetUIntValue(version, CONFIG_RECHARGE_OPTIONAL_VER)
		&& Config::GetValue(platform, CONFIG_RECHARGE_OPTIONAL_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["recharge_optional"] = activityTime;
	}

	//充值送星级
	if (Config::GetUIntValue(beginTime, CONFIG_RECHARGE_SEND_UPGRADE_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_RECHARGE_SEND_UPGRADE_END_TS)
		&& Config::GetUIntValue(version, CONFIG_RECHARGE_SEND_UPGRADE_VER)
		&& Config::GetValue(platform, CONFIG_RECHARGE_SEND_UPGRADE_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["recharge_send_upgrade"] = activityTime;
	}

	//国庆盛典
	if (Config::GetUIntValue(beginTime, CONFIG_GUOQING_HAPPY_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_GUOQING_HAPPY_END_TS)
		&& Config::GetUIntValue(version, CONFIG_GUOQING_HAPPY_VER)
		&& Config::GetValue(platform, CONFIG_GUOQING_HAPPY_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["guoqing_happy"] = activityTime;
	}

	//五行灵珠
	if (Config::GetUIntValue(beginTime, CONFIG_WUXING_PEARL_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_WUXING_PEARL_END_TS)
		&& Config::GetUIntValue(version, CONFIG_WUXING_PEARL_VER)
		&& Config::GetValue(platform, CONFIG_WUXING_PEARL_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["wuxing_pearl"] = activityTime;
	}

	//五行商铺
	if (Config::GetUIntValue(beginTime, CONFIG_WUXING_SHOP_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_WUXING_SHOP_END_TS)
		&& Config::GetUIntValue(version, CONFIG_WUXING_SHOP_VER)
		&& Config::GetValue(platform, CONFIG_WUXING_SHOP_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["wuxing_shop"] = activityTime;
	}

	//至尊宝箱
	if (Config::GetUIntValue(beginTime, CONFIG_ZHIZUNBAOXIANG_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_ZHIZUNBAOXIANG_END_TS)
		&& Config::GetUIntValue(version, CONFIG_ZHIZUNBAOXIANG_VERSION))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		data["zhizunbaoxiang"] = activityTime;
	}

	//双11
	if (Config::GetUIntValue(beginTime, CONFIG_DOUBLEELEVEN_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_DOUBLEELEVEN_END_TS)
		&& Config::GetUIntValue(version, CONFIG_DOUBLEELEVEN_VER)
		&& Config::GetValue(platform, CONFIG_DOUBLEELEVEN_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["doubleeleven"] = activityTime;
	}

	//11月回馈
	if (Config::GetUIntValue(beginTime, CONFIG_JINQIUNOVEMBER_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_JINQIUNOVEMBER_END_TS)
		&& Config::GetUIntValue(version, CONFIG_JINQIUNOVEMBER_VER)
		&& Config::GetValue(platform, CONFIG_JINQIUNOVEMBER_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["jinqiunovember"] = activityTime;
	}

	//充值送神纹符
	if (Config::GetUIntValue(beginTime, CONFIG_ACCHARGEBACKSHENWEN_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_ACCHARGEBACKSHENWEN_END_TS)
		&& Config::GetUIntValue(version, CONFIG_ACCHARGEBACKSHENWEN_VER)
		&& Config::GetValue(platform, CONFIG_ACCHARGEBACKSHENWEN_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["acchargebackshenwen"] = activityTime;
	}

	//国庆福袋
	if (Config::GetUIntValue(beginTime, CONFIG_COUNTRY_BAG_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_COUNTRY_BAG_END_TS)
		&& Config::GetUIntValue(version, CONFIG_COUNTRY_BAG_VER)
		&& Config::GetValue(platform, CONFIG_COUNTRY_BAG_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["countrydaybag"] = activityTime;
	}

	//vikcy的无节操累计充值活动
	if (Config::GetUIntValue(beginTime, CONFIG_VICKY_ACC_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_VICKY_ACC_END_TS)
		&& Config::GetUIntValue(version, CONFIG_VICKY_ACC_VER)
		&& Config::GetValue(platform, CONFIG_VICKY_ACC_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["vicky_acc"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_HOLIDAY_REVELRY_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_HOLIDAY_REVELRY_END_TS)
			&& Config::GetUIntValue(version, CONFIG_HOLIDAY_REVELRY_VER)
			&& Config::GetValue(platform, CONFIG_HOLIDAY_REVELRY_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["holiday_revelay"] = activityTime;
	}

	//鸡年纳福
	if (Config::GetUIntValue(beginTime, CONFIG_VICKY_CHICK_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_VICKY_CHICK_END_TS)
		&& Config::GetValue(platform, CONFIG_VICKY_CHICK_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = platform;
		data["vicky_chick"] = activityTime;
	}

	//vikcy的消费自选活动
	if (Config::GetUIntValue(beginTime, CONFIG_VICKY_PAY_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_VICKY_PAY_END_TS)
		&& Config::GetUIntValue(version, CONFIG_VICKY_PAY_VER)
		&& Config::GetValue(platform, CONFIG_VICKY_PAY_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["vicky_pay"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_TOWER_ACTIVITY_BEGIN_TS)
				&& Config::GetUIntValue(endTime, CONFIG_TOWER_ACTIVITY_END_TS)
				&& Config::GetUIntValue(version, CONFIG_TOWER_ACTIVITY_VER)
				&& Config::GetValue(platform, CONFIG_TOWER_ACTIVITY_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["tower"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_WORLD_TREASURE_BEGIN_TS)
				&& Config::GetUIntValue(endTime, CONFIG_WORLD_TREASURE_END_TS)
				&& Config::GetUIntValue(version, CONFIG_WORLD_TREASURE_VER)
				&& Config::GetValue(platform, CONFIG_WORLD_TREASURE_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["world_treasure"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_TOKEN_INTENSIFY_BEGIN_TS)
				&& Config::GetUIntValue(endTime, CONFIG_TOKEN_INTENSIFY_END_TS)
				&& Config::GetUIntValue(version, CONFIG_TOKEN_INTENSIFY_VER)
				&& Config::GetValue(platform, CONFIG_TOKEN_INTENSIFY_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["token_intensify"] = activityTime;
	}

	//装备强化活动
	if (Config::GetUIntValue(beginTime, CONFIG_EQUIP_STRENGTHEN_BEGIN_TS)
				&& Config::GetUIntValue(endTime, CONFIG_EQUIP_STRENGTHEN_END_TS)
				&& Config::GetUIntValue(version, CONFIG_EQUIP_STRENGTHEN_VER)
				&& Config::GetValue(platform, CONFIG_EQUIP_STRENGTHEN_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["equip_strengthen"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_SOUL_FEEDBACK_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_SOUL_FEEDBACK_END_TS)
			&& Config::GetUIntValue(version, CONFIG_SOUL_FEEDBACK_VER)
			&& Config::GetValue(platform, CONFIG_SOUL_FEEDBACK_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["soul_feedback"] = activityTime;
	}

	/*
	 * 觉醒回馈
	 */
	if (Config::GetUIntValue(beginTime, CONFIG_AWAKEN_FEEDBACK_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_AWAKEN_FEEDBACK_END_TS)
			&& Config::GetUIntValue(version, CONFIG_AWAKEN_FEEDBACK_VER)
			&& Config::GetValue(platform, CONFIG_AWAKEN_FEEDBACK_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["awaken_feedback"] = activityTime;
	}

	/*
	 * 铸魂打折
	 */
	if (Config::GetUIntValue(beginTime, CONFIG_CAST_SOUL_BEGIN_TS)
			&& Config::GetUIntValue(endTime, CONFIG_CAST_SOUL_END_TS)
			&& Config::GetUIntValue(version, CONFIG_CAST_SOUL_VER)
			&& Config::GetValue(platform, CONFIG_CAST_SOUL_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["cast_soul"] = activityTime;
	}

	/*
	 * 宝石折扣
	 */
	if (Config::GetUIntValue(beginTime, CONFIG_GEM_DISCOUNT_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_GEM_DISCOUNT_END_TS)
		&& Config::GetUIntValue(version, CONFIG_GEM_DISCOUNT_VER)
		&& Config::GetValue(platform, CONFIG_GEM_DISCOUNT_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["gem_discount"] = activityTime;
	}

	if (Config::GetUIntValue(beginTime, CONFIG_ALLIANCE_CONSUME_BEGIN_TS)
		&& Config::GetUIntValue(endTime, CONFIG_ALLIANCE_CONSUME_END_TS)
		&& Config::GetUIntValue(version, CONFIG_ALLIANCE_CONSUME_VER)
		&& Config::GetValue(platform, CONFIG_ALLIANCE_CONSUME_PF))
	{
		activityTime[0u] = beginTime;
		activityTime[1u] = endTime;
		activityTime[2u] = version;
		activityTime[3u] = platform;
		data["alliance_consume"] = activityTime;
	}

	full_all_act_info(data);

	return 0;
}

int CLogicArchive::checkUserStats(Json::Value &old, Json::Value &now)
{
	if(old.isMember("stars"))
	{
		if(!now.isMember("stars"))
			return 1;
		if(old["stars"].asUInt() > now["stars"].asUInt())
			return 2;
	}
	if(!now.isMember("bet"))
		now["bet"] = 0;
	if(old.isMember("ec1"))
		now["ec1"] = old["ec1"];
	return 0;
}
int CLogicArchive::checkUserTech(Json::Value &old, Json::Value &now)
{
	bool needJuexueLog = false;

	if(old.isMember("godE") && old["godE"].isObject() && old["godE"]["godE"].isArray())
	{
		if(now.isMember("godE") && now["godE"].isObject() && now["godE"]["godE"].isArray())
		{
			for(unsigned i=0;i<old["godE"]["godE"].size();++i)
			{
				if(old["godE"]["godE"][i].isArray())
				{
					if(now["godE"]["godE"].size() > i && now["godE"]["godE"][i].isArray())
					{
						for(unsigned j=0;j<old["godE"]["godE"][i].size();++j)
						{
							if(now["godE"]["godE"][i].size()>j)
							{
								if(old["godE"]["godE"][i][j] > now["godE"]["godE"][i][j])
									return 4;
							}
							else
								return 3;
						}
					}
					else
						return 2;
				}
			}
		}
		else
			return 1;
	}

	if(old.isMember("part") && old["part"].isArray())
	{
		if(now.isMember("part") && now["part"].isArray())
		{
			for(unsigned i=0;i<old["part"].size();++i)
			{
				if(now["part"].size() > i)
				{
					if(old["part"][i] != now["part"][i])
						return 7;
				}
				else
					return 6;
			}
		}
		else
			return 5;
	}

	if(old.isMember("soul"))
	{
		if(!now.isMember("soul"))
			return 8;
		if(old["soul"].asUInt() != now["soul"].asUInt())
			return 9;
	}

	if(old.isMember("sgrowth"))
	{
		if(!now.isMember("sgrowth"))
			return 10;
		if(old["sgrowth"].asUInt() != now["sgrowth"].asUInt())
			return 11;
	}

	if(old.isMember("tw") && old["tw"].isArray())
	{
		if(now.isMember("tw") && now["tw"].isArray())
		{
			for(unsigned i=0;i<old["tw"].size();++i)
			{
				if(old["tw"][i].isArray())
				{
					if(now["tw"].size() > i && now["tw"][i].isArray())
					{
						if(now["tw"][i].size() > 0)
						{
							if(old["tw"][i][0u] != now["tw"][i][0u])
								return 12;
						}
						else
							return 13;
					}
					else
						return 14;
				}
			}
		}
		else
			return 15;
	}

	if(!old.isMember("yinliang"))
		old["yinliang"] = 0;
	now["yinliang"] = old["yinliang"];

	if(old.isMember("rank"))
		now["rank"] = old["rank"];

	if(old.isMember("bnw"))
		now["bnw"] = old["bnw"];
	if(old.isMember("bnwt"))
		now["bnwt"] = old["bnwt"];

	if(old.isMember("jyt"))
		now["jyt"] = old["jyt"];

	if(old.isMember("soldier_spirit"))
		now["soldier_spirit"] = old["soldier_spirit"];

	if(old.isMember("jm"))
		now["jm"] = old["jm"];

	if(old.isMember("ancientScroll"))
		now["ancientScroll"] = old["ancientScroll"];

	if(old.isMember("nsa"))
		now["nsa"] = old["nsa"];

	if(old.isMember("ylna"))
		now["ylna"] =  old["ylna"];

	if(old.isMember("catapult"))
		now["catapult"] = old["catapult"];
	if(old.isMember("cskill"))
			now["cskill"] = old["cskill"];

	if(old.isMember("godh"))
		now["godh"] =  old["godh"];

	if(!needJuexueLog && now.isMember("hecheng") && old.isMember("hecheng"))
	{
		if(now["hecheng"][0u] != old["hecheng"][0u]
		|| now["hecheng"][1u] > old["hecheng"][1u])
			needJuexueLog = true;
	}
	if(!needJuexueLog && now.isMember("xiulianlist") && old.isMember("xiulianlist"))
	{
		if(now["xiulianlist"].size() == old["xiulianlist"].size())
		{
			for(unsigned j=0;j<old["xiulianlist"].size();++j)
			{
				if(now["xiulianlist"][j][0u] != old["xiulianlist"][j][0u]
				|| now["xiulianlist"][j][1u] > old["xiulianlist"][j][1u])
				{
					needJuexueLog = true;
					break;
				}
			}
		}
	}
	if(!needJuexueLog && now.isMember("baglist") && old.isMember("baglist"))
	{
		if(now["baglist"].size() == old["baglist"].size())
		{
			for(unsigned j=0;j<old["baglist"].size();++j)
			{
				if(now["baglist"][j][0u] != old["baglist"][j][0u]
				|| now["baglist"][j][1u] > old["baglist"][j][1u])
				{
					needJuexueLog = true;
					break;
				}
			}
		}
	}
	if(needJuexueLog)
	{
		error_log("[juexue_error]");
		LOGIC_ERROR_RETURN_MSG("resource_error");
	}

	return 0;
}
void CLogicArchive::checksoldier(string &olds, Json::Value &now)
{
	Json::Value old;
	Json::Reader().parse(olds, old);
	map<string, int> o, n;
	for(int i=0;i<old.size();++i)
		o[old[i]["id"].asString()] = old[i]["amount"].asInt();
	for(int i=0;i<now.size();++i)
		n[now[i]["id"].asString()] = now[i]["amount"].asInt();
	now.resize(0);
	for(map<string, int>::iterator it=n.begin();it!=n.end();++it)
	{
		if(o.count(it->first))
		{
			Json::Value t;
			t["id"] = it->first;
			t["amount"] = min(it->second, o[it->first]);
			now.append(t);
		}
	}
}

int CLogicArchive::checkskillQ(string &olds, Json::Value &now)
{
	Json::Value old;
	Json::Reader().parse(olds, old);
	Json::Value::Members n = now.getMemberNames();
	for(Json::Value::Members::iterator it=n.begin();it!=n.end();++it)
	{
		if(now[*it].isObject())
		{
			if(old.isMember(*it))
			{
				if(now[*it].isMember("i"))
				{
					if(old[*it].isMember("i"))
					{
						now[*it]["i"]["hid"] = old[*it]["i"]["hid"];
						now[*it]["i"]["hud"] = old[*it]["i"]["hud"];
						now[*it]["i"]["sid"] = old[*it]["i"]["sid"];
						now[*it]["i"]["l"] = old[*it]["i"]["l"];
					}
					else
						now[*it].removeMember("i");
				}
			}
			else
				now.removeMember(*it);
		}
	}
	return 0;
}

void CLogicArchive::checksoldierlevel(string &olds, Json::Value &now)
{
	Json::Value old;
	Json::Reader().parse(olds, old);
	Json::Value::Members n = now.getMemberNames();
	for(Json::Value::Members::iterator it=n.begin();it!=n.end();++it)
	{
		if(now[*it].isObject())
		{
			if(old.isMember(*it))
			{
				now[*it]["l"] = old[*it]["l"];
				now[*it]["lt"] = min(now[*it]["lt"].asUInt(), old[*it]["lt"].asUInt());
			}
			else
				now.removeMember(*it);
		}
	}
}

LoadType CLogicArchive::GetLoadType(const string &type)
{
	for (int i = 0; loadTypes[i].desc != NULL; i++)
	{
			if (type == loadTypes[i].desc)
				return loadTypes[i].type;
	}
	return LT_UNKNOW;
}

int CLogicArchive::getMaxAddExp(unsigned level)
{
	--level;
	if(level >= 119)
		level = 118;
	float exp = (float)(user_lvl_exp[level + 1] - user_lvl_exp[level]) * (level <= 50 ? 4.0f : 0.5f);
	return (int)exp;
}
int CLogicArchive::getAttMaxAddExp(unsigned level)
{
	--level;
	if(level >= 119)
		level = 118;
	float exp = (float)(user_lvl_exp[level + 1] - user_lvl_exp[level]) * 0.2f;
	return (int)exp;
}
int CLogicArchive::getResCostAddExp(int level, int r1, int r2, int r3, int r4)
{
	return (int)ceil((double(r1) + double(r2) + double(r3) + double(r4))
		/ (double(1) + pow(double(level), double(3.3376)) * double(0.0042)));
}
int CLogicArchive::getResGetAddExp(int level, int r1, int r2, int r3, int r4)
{
	return getResCostAddExp(level, r1, r2, r3, r4) / 10;
}
int CLogicArchive::getLevel(unsigned exp)
{
	int level = 1;
	int levelSize = (int)(sizeof(user_lvl_exp) / sizeof(user_lvl_exp[0]));
	if (exp >= user_lvl_exp[levelSize - 1])
		level = levelSize;
	else
	{
		for (int i = 1; i < levelSize; i++)
		{
			if (exp < user_lvl_exp[i])
			{
				level = i;
				break;
			}
		}
	}
	return level;
}
unsigned CLogicArchive::getExp(unsigned level)
{
	--level;
	if(level >= 119)
		level = 118;
	return user_lvl_exp[level + 1];
}
