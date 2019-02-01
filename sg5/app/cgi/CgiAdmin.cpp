#include "LogicInc.h"
#include "LogicCustomServiceAdmin.h"

string CreateCode()
{
	string skey = "";
	int range = 62;
	for (int i = 0; i < CODE_SIZE ; i++ )
	{
		int c = Math::GetRandomInt(range);
		if(c >= 36)
		{
			c -= 36;
			//skey += CTrans::ITOS(c) ;
			skey += (char)('a' + c);
		}else if(c >= 26)
		{	c -= 26;
			skey += (char)('0' + c);
		}else
		{
			skey += (char)('A' + c);
		}
	}
	return skey;
}
class CCgiAdmin : public CCgiBase
{
public:
	CCgiAdmin() : CCgiBase("admin")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
	}

	CGI_SIMPLE_ACTION_MAP_BEGIN
	CGI_SET_ACTION_MAP("login", Login)
	CGI_SET_ACTION_MAP("logincheck", LoginCheck)
	CGI_SET_ACTION_MAP("autologin", AutoLogin)
	CGI_SET_ACTION_MAP("modifypwd", ModifyPwd)
	CGI_SET_ACTION_MAP("querypay",QueryPay)
	CGI_SET_ACTION_MAP("changecash", ChangeCash)
	CGI_SET_ACTION_MAP("changecoins", ChangeCoins)
	CGI_SET_ACTION_MAP("querybasic", QueryBasic)
	CGI_SET_ACTION_MAP("queryuser", QueryUser)
	CGI_SET_ACTION_MAP("changegc", ChangeGcbase)
	CGI_SET_ACTION_MAP("changer1", ChangeR1)
	CGI_SET_ACTION_MAP("changer2", ChangeR2)
	CGI_SET_ACTION_MAP("changer3", ChangeR3)
	CGI_SET_ACTION_MAP("changer4", ChangeR4)
	CGI_SET_ACTION_MAP("changer5", ChangeR5)
	CGI_SET_ACTION_MAP("changebs", ChangeBattleSpirits)
	CGI_SET_ACTION_MAP("changelonglin", ChangeLonglin)    //龙鳞
	CGI_SET_ACTION_MAP("changets", ChangeTutorialStage)
	CGI_SET_ACTION_MAP("changewf", ChangeWfStatus)
	CGI_SET_ACTION_MAP("chgprosper", ChangeProsper)
	CGI_SET_ACTION_MAP("chgblockts", ChangeBlockTs)
	CGI_SET_ACTION_MAP("export", ExportArchive)
	CGI_SET_ACTION_MAP("import", ImportArchive)
	CGI_SET_ACTION_MAP("broadcast", BroadCast)
	CGI_SET_ACTION_MAP("forbidchat", ForbidChat)
	CGI_SET_ACTION_MAP("getexchargenumber", GetExchangeCode)
	CGI_SET_ACTION_MAP("addmysticalequip", AddMysticalEquip)
	CGI_SET_ACTION_MAP("delmysticalequip", DelMysticalEquip)
	CGI_SET_ACTION_MAP("querymysticalequips", QueryMysticalEquips)
	CGI_SET_ACTION_MAP("queryactivitytime", QueryActivityTime)
	//CGI_SET_ACTION_MAP("changeactivitytime", ChangeActivityTime)
	CGI_SET_ACTION_MAP("changeblocktsbyopenid", changeBlockTsByOpenId)
	CGI_SET_ACTION_MAP("queryblocktsbyopenid", QueryBlockTsByOpenId)
	CGI_SET_ACTION_MAP("changePoint", ChangePoint)
	CGI_SET_ACTION_MAP("queryinvitelist", QueryInviteList)
	CGI_SET_ACTION_MAP("addacccharge", AddAccCharge)
	CGI_SET_ACTION_MAP("changepo",ChangeExperence)
	CGI_SET_ACTION_MAP("addgamemanager",AddGM)
	CGI_SET_ACTION_MAP("delgamemanager",DelGM)
	CGI_SET_ACTION_MAP("add_th",Add_th)
	CGI_SET_ACTION_MAP("del_th",Del_th)
	CGI_SET_ACTION_MAP("add_ip",Add_ip)
	CGI_SET_ACTION_MAP("del_ip",Del_ip)
	CGI_SET_ACTION_MAP("addattack",AddAttack)
	CGI_SET_ACTION_MAP("querybuilding", QueryBuilding)
	CGI_SET_ACTION_MAP("updatebuilding",UpdateBuilding)
	CGI_SET_ACTION_MAP("changeprotecttime",ChangeProtectTime)
	CGI_SET_ACTION_MAP("copyarchive", CopyArchive)
	CGI_SET_ACTION_MAP("changestars", ChangeStars)    //官职
	CGI_SET_ACTION_MAP("changesoul", ChangeSoul)     //将灵
	CGI_SET_ACTION_MAP("changeqle", ChangeqlE)     //将灵
	CGI_SET_ACTION_MAP("updategate", UpdateGate)
	CGI_SET_ACTION_MAP("updatewuhujiang", UpdateWuhujiang)
	CGI_SET_ACTION_MAP("thvip", THVIP)
	CGI_SET_ACTION_MAP("addhero", AddHero)
	CGI_SET_ACTION_MAP("addequipment", AddEquipment)
	CGI_SET_ACTION_MAP("ChangeHeroCoin", ChangeHeroCoin)
	CGI_SET_ACTION_MAP("ChangeRechargeAlliance", ChangeRechargeAlliance)
	//CGI_SET_ACTION_MAP("gmcoin", GMCoin)
	CGI_SET_ACTION_MAP("charge", Charge)
	CGI_SET_ACTION_MAP("th_export", Th_Export)		//TH 倒档 一个英雄，一件装备 user_tech
	CGI_SET_ACTION_MAP("th_import", Th_Import)		//TH 存档 一个英雄，一件装备 user_tech
	CGI_SET_ACTION_MAP("kickOffline", KickOffline)  //踢下线
	CGI_SET_ACTION_MAP("chgrefreshts", ChangeRefreshTs)  //禁言

	CGI_ACTION_MAP_END


	int AddTsCheck(const string &name, const int &ts)
	{
		m_tscheck[name] = ts;
		return 0;
	}

	int CheckTs(const string &name,const int &ts)
	{
		if(m_tscheck.count(name) && m_tscheck[name] == ts)
			return 0;
		error_log("name=%s,ts=%d,real_ts=%d,wrong!",name.c_str(), ts,m_tscheck.count(name)?m_tscheck[name]:0);
		SESS_ERROR_RETURN_MSG("TS error");
	}

	int loginIP(const string &name, const string &ip)
	{
		m_ipcheck[name] = m_ipstr;
		return 0;
	}
	int checkIP(const string &name)
	{
		if(m_ipcheck.count(name) && m_ipcheck[name] == m_ipstr)
			return 0;
		error_log("name=%s,ip=%s,real_ip=%s,wrong!",name.c_str(), m_ipstr.c_str(),m_ipcheck.count(name)?m_ipcheck[name].c_str():"NULL");
		SESS_ERROR_RETURN_MSG("IP error");
	}

	int checkTry(const string &name)
	{
		if(m_trycheck.count(name))
		{
			if(m_trycheck[name].second + 86400 > Time::GetGlobalTime())
			{
				if(m_trycheck[name].first > 5)
					return R_ERR_LOGIC;
			}
			else
				m_trycheck.erase(name);
		}

		return 0;
	}
	int addTry(const string &name)
	{
		if(m_trycheck.count(name))
			m_trycheck[name] = pair<unsigned, unsigned>(m_trycheck[name].first+1, Time::GetGlobalTime());
		else
			m_trycheck[name] = pair<unsigned, unsigned>(1, Time::GetGlobalTime());

		return 0;
	}

	int Login()
	{
		int ret = 0;
		int ts = Time::GetGlobalTime();
		string name = CCGIIn::GetCGIStr("username");
		string password = CCGIIn::GetCGIStr("password");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if(checkTry(name))
		{
			REFUSE_RETURN_MSG("Passwd error");
		}

		string skey;
		int level = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.Login(name, password, skey);
			if (ret != 0)
			{
				addTry(name);
				return ret;
			}
			m_jsonResult["username"] = name;
			m_jsonResult["skey"] = skey;
			m_jsonResult["ts"] = ts;
		}
		else
		{
			CLogicAdmin logicAdmin;
			ret = logicAdmin.Login(name, password, skey);
			if (ret != 0)
			{
				addTry(name);
				return ret;
			}

			level = logicAdmin.GetLevel(name);
			m_jsonResult["username"] = name;
			m_jsonResult["skey"] = skey;
			m_jsonResult["level"] = level;
			m_jsonResult["ts"] = ts;
		}

		loginIP(name, m_ipstr);
		AddTsCheck(name,ts);

		CGI_SEND_LOG("action=login&name=%s&skey=%s&level=%u", name.c_str(), skey.c_str(),level);
		return 0;
	}

	int LoginCheck(){
			string name = CCGIIn::GetCGIStr("username");
			string skey = CCGIIn::GetCGIStr("skey");

			CLogicAdmin logicAdmin;
			int ret = logicAdmin.LoginCheck(name,skey);
			if(ret!=0)
			{
				return ret;
			}

			ret = checkIP(name);if(ret)	return ret;

			return 0 ;
		}

	int AutoLogin()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int level = logicAdmin.AutoLogin(name, skey);
		m_jsonResult["level"] = level;

		CGI_SEND_LOG("action=autologin&level=%u", level);
		return 0;
	}

	int ModifyPwd()
	{
		string name = CCGIIn::GetCGIStr("username");
		string password = CCGIIn::GetCGIStr("password");
		string newpwd = CCGIIn::GetCGIStr("newpwd");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || newpwd.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if(checkTry(name))
		{
			REFUSE_RETURN_MSG("Passwd error");
		}

		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.ChangePwd(name, password, newpwd);
			if (0 != ret)
			{
				addTry(name);
				return ret;
			}
		}
		else
		{
			CLogicAdmin logicAdmin;
			ret = logicAdmin.ModifyPassword(name, password, newpwd);
			if (ret != 0)
			{
				addTry(name);
				return ret;
			}
		}
		CGI_SEND_LOG("action=modifypwd&name=%s", name.c_str());
		return 0;
	}

	int QueryPay()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int custom = CCGIIn::GetCGIInt("custom");
		int ts =  CCGIIn::GetCGIInt("ts");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		int ret = 0;

		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", 0);
			if (0 != ret) return ret;
		}
		else
		{
			CLogicAdmin logicAdmin;
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		CLogicPay logicPay;
		DataPay pay;
		ret = logicPay.GetPay(uid, pay);
		if (ret != 0)
			return ret;

		CLogicUser logicUser;
		Json::Value userFlag;
		ret = logicUser.GetUserFlag(uid, userFlag);
		if (ret != 0)
			return ret;

		m_jsonResult["uid"] = uid;
		m_jsonResult["cash"] = pay.cash;
		m_jsonResult["coins"] = pay.coins;
		m_jsonResult["ts"] = ts;
		m_jsonResult["herocoins"] = userFlag.isMember("heroCoins")?userFlag["heroCoins"][1u].asInt():0;

		CGI_SEND_LOG("action=querypay&name=%s&skey=%s&cash=%u&coins=%u",
				name.c_str(), skey.c_str(), pay.cash, pay.coins);
		return 0;
	}

	int ChangeCash()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int cash = CCGIIn::GetCGIInt("cash");
		string reason = CCGIIn::GetCGIStr("reason");
		int custom = CCGIIn::GetCGIInt("custom");
		int ts =  CCGIIn::GetCGIInt("ts");
		int channel = CCGIIn::GetCGIInt("channel");
		if (name.empty() || skey.empty() || cash == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}
		DataPay pay;
		ret = logicAdmin.ChangePay(uid, cash, 0, pay,channel);
		if (ret != 0)
			return ret;

		m_jsonResult["balance"] = pay.cash;
		m_jsonResult["ts"] = ts;
		CGI_SEND_LOG("action=changecash&name=%s&uid=%u&cash=%d&balance=%u", name.c_str(), uid, cash, pay.cash);

		//channel用于区分大r，内部体验及托 ；    0为gm渠道，99为大R，100为托。
		if (1 != custom)
		{
			if(channel == 99)
			{
				CLogicAdmin::R_Log(name, "changecash", reason, uid, CTrans::ITOS(cash));
			}
			else
			{
				CLogicAdmin::Log(name, "changecash", reason, uid, CTrans::ITOS(cash));
			}
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changecash", reason, uid, CTrans::ITOS(cash));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"钻石",reason,uid,0,cash);

		return 0;
	}

	int ChangeCoins()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int coins = CCGIIn::GetCGIInt("coins");
		string reason = CCGIIn::GetCGIStr("reason");
		int custom = CCGIIn::GetCGIInt("custom");
		int ts =  CCGIIn::GetCGIInt("ts");
		int channel = CCGIIn::GetCGIInt("channel");
		if (name.empty() || skey.empty() || coins == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}
		DataPay pay;
		ret = logicAdmin.ChangePay(uid, 0, coins, pay,channel);
		if (ret != 0)
			return ret;

		m_jsonResult["balance"] = pay.coins;
		m_jsonResult["ts"] = ts;
		CGI_SEND_LOG("action=changecash&name=%s&uid=%u&coins=%d&balance=%u", name.c_str(), uid, coins, pay.coins);
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changecoins", reason, uid, CTrans::ITOS(coins));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changecoins", reason, uid, CTrans::ITOS(coins));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"金币",reason,uid,0,coins);

		return 0;
	}

	int QueryBasic()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		if (name.empty() || skey.empty() || openid.empty()
				|| tpt <= PT_UNKNOW || tpt >= PT_MAX)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		PlatformType pt = static_cast<PlatformType>(tpt);
		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;

		DataUserBasic userBasic;
		ret = logicAdmin.QueryUserBasicInfo(openid, pt, userBasic);
		if (ret != 0)
			return ret;
		m_jsonResult["uid"] = userBasic.uid;
		m_jsonResult["platform"] = userBasic.platform;
		m_jsonResult["is_register_platform"] = userBasic.is_register_platform;
		m_jsonResult["open_id"] = userBasic.open_id;
		m_jsonResult["name"] = userBasic.name;
		m_jsonResult["gender"] = userBasic.gender;
		m_jsonResult["nation"] = userBasic.nation;
		m_jsonResult["province"] = userBasic.province;
		m_jsonResult["city"] = userBasic.city;
		m_jsonResult["figure_url"] = userBasic.figure_url;
		m_jsonResult["vip_type"] = userBasic.vip_type;
		m_jsonResult["vip_level"] = userBasic.vip_level;
		m_jsonResult["fnum"] = userBasic.fnum;

		CGI_SEND_LOG("action=querybasic&name=%s&openid=%s&pt=%d", name.c_str(), openid.c_str(), pt);
		return 0;
	}

	int QueryUser()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", 0);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		DataUser user;
		ret = logicAdmin.QueryUser(uid, user);
		if (ret != 0)
			return ret;

		int donate = 0;
		string allianceData("");
		uint64_t alliancePoint = 0;
		Json::Value ext_data;
		DataAlliance allianceDB;
		CLogicAlliance logicAlliance;
		DataAllianceMember allianceMemberDB;

		if(user.alliance_id == 0)
		{
			allianceData = "无联盟";
			alliancePoint = 0;
			donate = 0;
		}else{
			ret = logicAlliance.GetAlliance(user.alliance_id, allianceDB);
			if(ret != 0)
				return ret;
			ret = logicAlliance.GetMember(user.alliance_id, uid, allianceMemberDB);
			if(ret != 0)
				return ret;
			Json::FromString(ext_data, allianceMemberDB.extra_data);
			Json::GetInt(ext_data, "donate", donate);
			allianceData = allianceDB.name;
			alliancePoint = allianceMemberDB.point;

		}

		m_jsonResult["uid"]					= user.uid;
		m_jsonResult["kingdom"]				= user.kingdom;
		m_jsonResult["register_platform"]	= user.register_platform;
		m_jsonResult["register_time"]		= user.register_time;
		m_jsonResult["invite_uid"]			= user.invite_uid;
		m_jsonResult["last_login_platform"]	= user.last_login_platform;
		m_jsonResult["last_login_time"]		= user.last_login_time;
		m_jsonResult["last_active_time"]	= user.last_active_time;
		m_jsonResult["login_times"]			= user.login_times;
		m_jsonResult["login_days"]			= user.login_days;
		m_jsonResult["invite_count"]		= user.invite_count;
		m_jsonResult["alliance"]			= allianceData;
		m_jsonResult["alliance_point"]		= Convert::UInt64ToString(alliancePoint);
		m_jsonResult["donate"]				= donate;
		m_jsonResult["today_invite_count"]	= user.today_invite_count;
		m_jsonResult["status"]				= user.status;
		m_jsonResult["type"]				= user.type;
		m_jsonResult["level"]				= user.level;
		m_jsonResult["point"]				= Convert::UInt64ToString(user.point);
		m_jsonResult["tutorial_stage"]		= user.tutorial_stage;
		m_jsonResult["r1"]					= user.r1;
		m_jsonResult["r1_max"]				= user.r1_max;
		m_jsonResult["r2"]					= user.r2;
		m_jsonResult["r2_max"]				= user.r2_max;
		m_jsonResult["r3"]					= user.r3;
		m_jsonResult["r3_max"]				= user.r3_max;
		m_jsonResult["r4"]					= user.r4;
		m_jsonResult["r4_max"]				= user.r4_max;
		m_jsonResult["r5"]					= user.r5;
		m_jsonResult["r5_max"]				= user.r5_max;
		m_jsonResult["last_save_time"]		= user.last_save_time;
		m_jsonResult["alliance_id"]			= user.alliance_id;
		m_jsonResult["protected_time"]		= user.protected_time;
		m_jsonResult["last_save_uid"]		= user.last_save_uid;
		m_jsonResult["last_breath_time"]	= user.last_breath_time;
		m_jsonResult["gcbase"]				= user.gcbase;
		m_jsonResult["newgcbase"]			= user.newgcbase;
		m_jsonResult["gcbuy"]				= user.gcbuy;
		m_jsonResult["bit_info"]			= user.bit_info;
		m_jsonResult["user_stat"]			= user.user_stat;
		m_jsonResult["user_flag"]			= user.user_flag;
		m_jsonResult["tech"]			= user.user_tech;
		m_jsonResult["barrackQ"]			= user.barrackQ;
		m_jsonResult["soldier"]				= user.soldier;
		m_jsonResult["soldierlevel"]		= user.soldierlevel;
		m_jsonResult["wf_status"]			= user.wf_status;
		m_jsonResult["buildQ"]				= user.buildQ;
		m_jsonResult["skillQ"]				= user.skillQ;
		m_jsonResult["trainQ"]				= user.trainQ;
		m_jsonResult["prosper"]				= user.prosper;
		m_jsonResult["acccharge"]			= user.accCharge;
		m_jsonResult["block_time"]			= user.tribute_time;
		m_jsonResult["close_reason"]		= user.close_reason;
		m_jsonResult["battle_spirits"]		= user.battle_spirits;
		m_jsonResult["cdn"]                 = user.cdn;
		m_jsonResult["kingdom"]             = user.kingdom;
		m_jsonResult["refresh"]             = user.refresh;
		m_jsonResult["memory"]              = user.memory;

		CGI_SEND_LOG("action=queryuser&name=%s&uid=%u", name.c_str(), uid);
		return 0;
	}

	int ChangeGcbase()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int gcbase = CCGIIn::GetCGIInt("gcbase");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || gcbase == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeGcbase(uid, gcbase, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["gcbase"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changegcbase", reason, uid, CTrans::ITOS(gcbase));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changegcbase", reason, uid, CTrans::ITOS(gcbase));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"能量",reason,uid,0,gcbase);

		CGI_SEND_LOG("action=changegc&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

    //经验值
	int ChangeExperence()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int point = CCGIIn::GetCGIInt("point");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || point == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error0");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error1");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error2");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangePoint1(uid, point, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["point"] = balance;
		m_jsonResult["ts"] = ts;

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changeexperience", reason, uid, CTrans::ITOS(point));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changeexperience", reason, uid, CTrans::ITOS(point));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"经验",reason,uid,0,point);

		CGI_SEND_LOG("action=changepo&name=%s&balance=%u", name.c_str(), balance);
		return 0;

	}

	int ChangePoint()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		int point = CCGIIn::GetCGIInt("point");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("uid");
		}
		CLogicUser logicUser;
		DataUser user;
		CLogicAlliance logicAlliance;
		ret = logicUser.GetUserLimit(uid,user);
		if(0 == ret && IsAllianceId(user.alliance_id))
		{
			ret = logicAlliance.AddPoint(user.alliance_id,uid,point);
			if (0 != ret)
			{
				LOGIC_ERROR_RETURN_MSG("add_point_fail");
			}
		}
		else
		{
			LOGIC_ERROR_RETURN_MSG("add_point_fail");
		}
		DataAllianceMember allianceMemberDB;
		ret = logicAlliance.GetMember(user.alliance_id, uid, allianceMemberDB);
		if(ret == 0)
		{
			m_jsonResult["alliance_point"] = (unsigned)allianceMemberDB.curr_point;
			m_jsonResult["ts"] = ts;
		}

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changepoint", reason, uid, CTrans::ITOS(point));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changepoint", reason, uid, CTrans::ITOS(point));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"贡献",reason,uid,0,point);

		return 0;
	}

	int ChangeR1()  //改变粮食的
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int r1 = CCGIIn::GetCGIInt("r1");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || r1 == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeR1(uid, r1, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["r1"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changer1", reason, uid, CTrans::ITOS(r1));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changer1", reason, uid, CTrans::ITOS(r1));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"粮食",reason,uid,0,r1);

		CGI_SEND_LOG("action=changer1&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeR2()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int r2 = CCGIIn::GetCGIInt("r2");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || r2 == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeR2(uid, r2, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["r2"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changer2", reason, uid, CTrans::ITOS(r2));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changer2", reason, uid, CTrans::ITOS(r2));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"木材",reason,uid,0,r2);

		CGI_SEND_LOG("action=changer2&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeR3()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int r3 = CCGIIn::GetCGIInt("r3");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || r3 == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			int ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeR3(uid, r3, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["r3"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changer3", reason, uid, CTrans::ITOS(r3));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changer3", reason, uid, CTrans::ITOS(r3));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"石料",reason,uid,0,r3);

		CGI_SEND_LOG("action=changer3&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeR4()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int r4 = CCGIIn::GetCGIInt("r4");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || r4 == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeR4(uid, r4, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["r4"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changer4", reason, uid, CTrans::ITOS(r4));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changer4", reason, uid, CTrans::ITOS(r4));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"铁矿",reason,uid,0,r4);

		CGI_SEND_LOG("action=changer4&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeR5()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int r5 = CCGIIn::GetCGIInt("r5");
		int custom = CCGIIn::GetCGIInt("custom");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		if (name.empty() || skey.empty() || reason.empty() || r5 == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeR5(uid, r5, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["r5"] = balance;
		m_jsonResult["ts"] = ts;

		CLogicAdmin::AddCheckLog(name,m_ipstr,"R5",reason,uid,0,r5);

		CGI_SEND_LOG("action=changer5&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeBattleSpirits()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int battleSpirits = CCGIIn::GetCGIInt("battle_spirits");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || battleSpirits == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeBattleSpirits(uid, battleSpirits, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["battle_spirits"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changebs", reason, uid, CTrans::ITOS(battleSpirits));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changebs", reason, uid, CTrans::ITOS(battleSpirits));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"战魂",reason,uid,0,battleSpirits);

		CGI_SEND_LOG("action=ChangeBattleSpirits&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeLonglin()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int long_lin = CCGIIn::GetCGIInt("long_lin");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || long_lin == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.AddLonglin(uid, long_lin, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["long_lin"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changelonglin", reason, uid, CTrans::ITOS(long_lin));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changelonglin", reason, uid, CTrans::ITOS(long_lin));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"龙鳞",reason,uid,0,long_lin);

		CGI_SEND_LOG("action=ChangeLonglin&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeTutorialStage()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int tutorial_stage = CCGIIn::GetCGIInt("tutorial_stage");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || tutorial_stage == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		ret = logicAdmin.ChangeTutorialStage(uid, tutorial_stage);
		if (ret != 0)
			return ret;

		m_jsonResult["tutorial_stage"] = tutorial_stage;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changets", reason, uid, CTrans::ITOS(tutorial_stage));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changets", reason, uid, CTrans::ITOS(tutorial_stage));
		}
		CGI_SEND_LOG("action=changets&name=%s&tutorial_stage=%d", name.c_str(), tutorial_stage);
		return 0;
	}

	int ChangeWfStatus()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string wf_status = CCGIIn::GetCGIStr("wf_status");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || wf_status.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		ret = logicAdmin.ChangeWfStatus(uid, wf_status);
		if (ret != 0)
			return ret;

		m_jsonResult["wf_status"] = wf_status;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changewf", reason, uid, wf_status);
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changewf", reason, uid, wf_status);
		}
		CGI_SEND_LOG("action=changewf&name=%s&wf_status=%s", name.c_str(), wf_status.c_str());
		return 0;
	}

	int ChangeProsper()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int prosper = CCGIIn::GetCGIInt("prosper");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		int channel = CCGIIn::GetCGIInt("channel");
		if (name.empty() || skey.empty() || reason.empty() || prosper == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeProsper(uid, prosper, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["prosper"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			if(channel == 99)
			{
				CLogicAdmin::R_Log(name, "chgprosper", reason, uid, CTrans::ITOS(prosper));
			}
			else
			{
				CLogicAdmin::Log(name, "chgprosper", reason, uid, CTrans::ITOS(prosper));
			}
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "chgprosper", reason, uid, CTrans::ITOS(prosper));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"威望",reason,uid,0,prosper);

		CGI_SEND_LOG("action=chgprosper&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeBlockTs()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string blockts = CCGIIn::GetCGIStr("blockts");
		string close_reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || blockts.empty() || close_reason.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;

			if(OpenPlatform::IsQQPlatform())
			{
				ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
				if (ret != 0)
					return ret;
			}
		}

		unsigned block_time = (unsigned)CTime::ParseDate(blockts);
		if (block_time == 0)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		ret = logicAdmin.ChangeBlockTs(uid, block_time, close_reason);
		if (ret != 0)
			return ret;

		m_jsonResult["block_time"] = block_time;
		m_jsonResult["close_reason"] = close_reason;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "lockuser", close_reason, uid, CTrans::ITOS(block_time));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "lockuser", close_reason, uid, CTrans::ITOS(block_time));
		}
		CGI_SEND_LOG("action=chgblockts&name=%s&blockts=%s&block_time=%uclose_reason=%s", name.c_str(), blockts.c_str(), block_time, close_reason.c_str());
		return 0;
	}


	int ChangeRefreshTs()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string refreshts = CCGIIn::GetCGIStr("refreshts");
		string close_reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || refreshts.empty() || close_reason.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;

			if(OpenPlatform::IsQQPlatform())
			{
				ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
				if (ret != 0)
					return ret;
			}
		}

		unsigned refresh_time = (unsigned)CTime::ParseDate(refreshts);
		if (refresh_time == 0)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		//改变禁言时间
		ret = logicAdmin.ChangeRefreshTs(uid, refresh_time);
		if (ret != 0)
			return ret;

		//然后把玩家踢下线2分钟, 目的是为了把玩家踢下线，重新读档
		unsigned now_ts = (unsigned)(Time::GetGlobalTime());
		unsigned block_time = now_ts + 120;
		ret = logicAdmin.ChangeBlockTs(uid, block_time, close_reason);
		if (ret != 0)
			return ret;

		m_jsonResult["refresh"] = refresh_time;
		m_jsonResult["close_reason"] = close_reason;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "forbidtalk", close_reason, uid, CTrans::ITOS(refresh_time));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "forbidtalk", close_reason, uid, CTrans::ITOS(refresh_time));
		}
		CGI_SEND_LOG("action=chgrefreshts&name=%s&refreshts=%s&refresh_time=%u&forbidtalk_reason=%s", name.c_str(), refreshts.c_str(), refresh_time, close_reason.c_str());
		return 0;
	}


	int ExportArchive()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (name.empty() || skey.empty() || (int)uid == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = checkIP(name);if(ret)	return ret;

		Json::FastWriter writer;
		Json::Value data;
		ret = logicAdmin.ExportArchive(uid, data);
		if (ret != 0)
			return ret;

		m_jsonResult["uid"] = uid;
		m_jsonResult["data"] = writer.write(data);
		CGI_SEND_LOG("action=export&name=%s&uid=%u", name.c_str(), uid);
		return 0;
	}

	int ImportArchive()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string sdata = CCGIIn::GetCGIStr("data");
		string reason = CCGIIn::GetCGIStr("reason");
		if (reason.empty() || name.empty() || skey.empty() || (int) uid == CCGIIn::CGI_INT_ERR
				|| sdata.empty()) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
		if (ret != 0)
			return ret;
		ret = checkIP(name);if(ret)	return ret;

		Json::Reader reader;
		Json::FastWriter writer;
		Json::Value data, old;
		if (!reader.parse(sdata, data)) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		unsigned userid = 0;
		Json::GetUInt(data, "userid", userid);
		if (userid != uid)
			data["userid"] = uid;

		ret = logicAdmin.ExportArchive(uid, old);
		if (ret != 0)
			return ret;

		ret = logicAdmin.ImportArchive(uid, data);
		Json::Value all;
		all["old"] = old;
		all["new"] = data;
		all["ret"] = ret;
		string as = writer.write(all);
		CLogicAdmin::Log(name, "import", reason, uid, "", as);
		if (ret != 0)
			return ret;

		m_jsonResult["uid"] = uid;
		CGI_SEND_LOG("action=import&name=%s&uid=%u", name.c_str(), uid);

		CLogicAdmin::AddCheckLog(name,m_ipstr,"倒档",reason,uid,0,0);

		return 0;
	}

	int BroadCast()
	{
		int ret = 0;
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");

		int ts =  CCGIIn::GetCGIInt("ts");
		CLogicAdmin logicAdmin;
		ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;

		if(OpenPlatform::IsQQPlatform())
		{
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		string message = CCGIIn::GetCGIStr("content");
		int repeats = CCGIIn::GetCGIInt("repeats");
		unsigned interval = CCGIIn::GetCGIInt("interval");
		string serverid = CCGIIn::GetCGIStr("serverid");

		if (serverid.empty())
			Config::GetValue(serverid, CONFIG_SERVER_ID);

		vector<string> rlt;
		String::Split(serverid, '-', rlt);
		if (rlt.size() >= 2) {
			unsigned begin = Convert::StringToUInt(rlt[0]);
			unsigned end = Convert::StringToUInt(rlt[1]);
			if (end < begin) {
				error_log("BroadCast error!");
				return ret;
			}

			for (unsigned i = begin; i <= end; ++i) {
				string serverstr = Convert::UIntToString(i);
				logicAdmin.BroadCastByTool(message, repeats, interval,serverstr);
			}
		} else
			logicAdmin.BroadCastByTool(message, repeats, interval, serverid);
		m_jsonResult["ts"] = ts;
		CGI_SEND_LOG("action=broadcast&repeats = %d&interval = %d&message=%s",repeats,interval,message.c_str());
		return 0;
	}
	int ForbidChat()
	{
		CLogicAdmin logicAdmin;
		int ret = 0;
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;

		if(OpenPlatform::IsQQPlatform())
		{
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_1);
			if (ret != 0)
				return ret;
		}

		unsigned uid = CCGIIn::GetCGIInt("uid");
		string deadline = CCGIIn::GetCGIStr("deadline");
		string serverid = CCGIIn::GetCGIStr("serverid");

		unsigned forbidts= (unsigned) CTime::ParseDate(deadline);
		//unsigned block_time = (unsigned) CTime::ParseDate(blockts);
		if (forbidts == 0) {
			PARAM_ERROR_RETURN_MSG("time_format_error");
		}
		//info_log("uid = %u,forbidts = %u,deadline =%s",uid,forbidts,deadline.c_str());

		ret  = logicAdmin.AddForbidUser(uid,forbidts,serverid);
		if(ret != 0)
		{
			return ret;
		}
		return 0;
	}
	int GetExchangeCode()
	{
		Json::Value data;
		Json::FastWriter writer;
		//ofstream ofile;
		//unsigned pid = CCGIIn::GetCGIInt("spreadid");
		string type = CCGIIn::GetCGIStr("type");
		if(type.empty())
		{
			type="01";
		}
		int count = CCGIIn::GetCGIInt("count",0,100000,10,10);
		if(!count)
			count = 10;
		int ret = 0;
		DataExchangeCode dataExchangeCode;
		CLogicExchangeCode logicExchangeCode;
		//uint64_t exchangeCode;
		string code;
		int i = 0;
		dataExchangeCode.uid = ADMIN_UID;
		dataExchangeCode.type = atoi(type.c_str());
		dataExchangeCode.gentime = Time::GetGlobalTime();
		dataExchangeCode.deadline = dataExchangeCode.gentime + (86400 * 99);
		dataExchangeCode.usetime = 0;
		for(i = 0; i < count; i++)
		{
			code = CreateCode();
			dataExchangeCode.code = code;
			ret = logicExchangeCode.AddExchangeCode(dataExchangeCode);
			if(ret != 0)
			{
				continue;
			}
			data[i]=type + code;
		}
		m_jsonResult["data"] = data;
		return 0;
	}
	int AddMysticalEquip()
	{
		unsigned eid = CCGIIn::GetCGIInt("eid");
		unsigned nums = CCGIIn::GetCGIInt("nums");
		unsigned min = CCGIIn::GetCGIInt("minPrice");
		unsigned max = CCGIIn::GetCGIInt("maxPrice");
		unsigned ratio = CCGIIn::GetCGIInt("ratio");
		if (   (int)eid == CCGIIn::CGI_INT_ERR
			|| (int)nums == CCGIIn::CGI_INT_ERR
			|| (int)min == CCGIIn::CGI_INT_ERR
			|| (int)max == CCGIIn::CGI_INT_ERR
			|| (int)ratio == CCGIIn::CGI_INT_ERR
			)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CDataMysticalShop dataMysticalShop;
		int ret = dataMysticalShop.Init(Config::GetPath(CONFIG_MYSTICALSHOP_PATH));
		if (ret != 0)
		{
			return ret;
		}
		ret = dataMysticalShop.AddEquip(eid, nums, min, max, ratio);
		if (ret != 0)
		{
			return ret;
		}

		return 0;
	}

	int DelMysticalEquip()
	{
		unsigned eid = CCGIIn::GetCGIInt("eid");
		if ((int)eid == CCGIIn::CGI_INT_ERR )
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CDataMysticalShop dataMysticalShop;
		int ret = dataMysticalShop.Init(Config::GetPath(CONFIG_MYSTICALSHOP_PATH));
		if (ret != 0)
		{
			return ret;
		}
		ret = dataMysticalShop.DeleteEquip(eid);
		if (ret != 0)
		{
			return ret;
		}

		return 0;
	}

	int QueryMysticalEquips()
	{
		vector<DataEquipItem> vecDataEquips;
		CDataMysticalShop dataMysticalShop;
		int ret = dataMysticalShop.Init(Config::GetPath(CONFIG_MYSTICALSHOP_PATH));
		if (ret != 0)
		{
			return ret;
		}
		vecDataEquips.clear();
		ret = dataMysticalShop.QueryEquips(vecDataEquips);
		if (ret != 0)
		{
			return ret;
		}
		int count = vecDataEquips.size();
		for (int i = 0; i < count; ++i)
		{
			m_jsonResult["mysticalEquips"][i]["eid"] = vecDataEquips[i].eid;
			m_jsonResult["mysticalEquips"][i]["nums"] = vecDataEquips[i].nums;
			m_jsonResult["mysticalEquips"][i]["min"] = vecDataEquips[i].min;
			m_jsonResult["mysticalEquips"][i]["max"] = vecDataEquips[i].max;
			m_jsonResult["mysticalEquips"][i]["ratio"] = vecDataEquips[i].ratio;
		}
		return 0;
	}

	int QueryActivityTime()
	{
#define GET_UINT_VALUE(name,Jname) \
		ret = logicAdmin.GetActivityTime(name,value); \
		if (0 == ret) \
		{ \
			m_jsonResult[Jname] = value; \
		}

		string valuestring;

#define GET_STRING_VALUE(name,Jname) \
		ret = logicAdmin.GetPlatform(name,valuestring); \
		if (0 == ret) \
		{ \
			m_jsonResult[Jname] = valuestring; \
		}

		int ret = 0;
		CLogicAdmin logicAdmin;
		unsigned value = 0;
		GET_UINT_VALUE(CONFIG_PAY_TOTAL_BEGIN_TS, "PayTotalBeginTs");
		GET_UINT_VALUE(CONFIG_PAY_TOTAL_END_TS, "PayTotalEndTs");
		GET_UINT_VALUE(CONFIG_POINTS_BEGIN_TS, "PointRankBeginTs");
		GET_UINT_VALUE(CONFIG_POINTS_END_TS, "PointRankEndTs");
//		GET_UINT_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_BEGIN_TS, "HundredDaysActivityRankBeginTs");   //百日庆典
//		GET_UINT_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_END_TS, "HundredDaysActivityRankEndTs");
		GET_UINT_VALUE(CONFIG_POINTS_VERSION, "PointRankVersion");
		GET_UINT_VALUE(CONFIG_PAYRANK_BEGIN_TS, "PayRankBeginTs");
		GET_UINT_VALUE(CONFIG_PAYRANK_END_TS, "PayRankEndTs");
		GET_UINT_VALUE(CONFIG_PAYRANK_VERSION, "PayRankVersion");
		GET_UINT_VALUE("twice_reward_b","ZhuGeLiangB");
		GET_UINT_VALUE("twice_reward_e","ZhuGeLiangE");
		GET_UINT_VALUE(CONFIG_SUNCE_BEGIN_TS,"SunCeB");
		GET_UINT_VALUE(CONFIG_SUNCE_END_TS,"SunCeE");
		GET_UINT_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_BEGIN_TS,"HundBegin");
		GET_UINT_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_END_TS,"HundEnd");
		GET_UINT_VALUE(CONFIG_MERRYSOULS_BEGIN_TS,"MerrySoulsbeginB");
		GET_UINT_VALUE(CONFIG_MERRYSOULS_END_TS,"MerrySoulsendE");
		GET_UINT_VALUE(CONFIG_MERRYSOULS_VERSION,"MerrySoulsVersion");

		GET_STRING_VALUE(CONFIG_MERRYSOULS_PF,"MerrySoulsPF");
		GET_STRING_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_PF,"HundDayPF");
		GET_STRING_VALUE(CONFIG_PAY_TOTAL_PF,"PayTotalPF");
		GET_STRING_VALUE(CONFIG_POINTS_PF,"PointsPF");
		GET_STRING_VALUE(CONFIG_PAYRANK_PF,"PayRankPF");
		return 0;
	}
	/*
	int ChangeActivityTime()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
		if (ret != 0)
			return ret;
		ret = checkIP(name);if(ret)	return ret;

		string PayTotalBeginTs = CCGIIn::GetCGIStr("paytotalbegints");
		string PayTotalEndTs = CCGIIn::GetCGIStr("paytotalendts");
		string PointRankBeginTs = CCGIIn::GetCGIStr("pointrankbegints");
		string PointRankEndTs = CCGIIn::GetCGIStr("pointrankendts");
		string PointRankVersion = CCGIIn::GetCGIStr("pointrankv");
		string PayRankBeginTs = CCGIIn::GetCGIStr("payrankbegints");
		string PayRankEndTs = CCGIIn::GetCGIStr("payrankendts");
		string PayRankVersion = CCGIIn::GetCGIStr("payrankv");
		string ZhuGeLiangB = CCGIIn::GetCGIStr("zhugeliangb");
		string ZhuGeLiangE = CCGIIn::GetCGIStr("zhugeliange");
		string SunCeB = CCGIIn::GetCGIStr("sunceb");
		string SunCeE = CCGIIn::GetCGIStr("suncee");
		string HundPaybegin = CCGIIn::GetCGIStr("hundbegin");
		string HundPayend = CCGIIn::GetCGIStr("hundend");
		string MerrySoulsbegin = CCGIIn::GetCGIStr("merrysoulsbegin");
		string MerrySoulsend = CCGIIn::GetCGIStr("merrysoulsend");
		string MerrySoulsVersion = CCGIIn::GetCGIStr("merrysoulsv");

		string PayTotal_pf = CCGIIn::GetCGIStr("paytotalpf");
		string PointRank_pf = CCGIIn::GetCGIStr("pointspf");
		string PayRank_pf = CCGIIn::GetCGIStr("payrankpf");
		string Hund_pf = CCGIIn::GetCGIStr("hundpf");
		string MerrySouls_pf = CCGIIn::GetCGIStr("merrysoulspf");

#define CHANGE_CONFIG_VALUE(name,value) \
		if(!value.empty()) \
		{ \
			unsigned timeValue = (unsigned)CTime::ParseDate(value); \
			ret = logicAdmin.ChangeActivityTime(name, timeValue); \
			if (0 != ret) \
				return ret; \
			else \
				m_jsonResult[#value] = timeValue; \
		}\

#define CHANGE_CONFIG_PF_VALUE(name,value) \
		if(!value.empty()) \
		{ \
			ret = logicAdmin.ChangePlatform(name, value); \
			if (0 != ret) \
				return ret; \
			else \
				m_jsonResult[#value] = value; \
		}\

		CHANGE_CONFIG_VALUE(CONFIG_PAY_TOTAL_BEGIN_TS, PayTotalBeginTs);
		CHANGE_CONFIG_VALUE(CONFIG_PAY_TOTAL_END_TS, PayTotalEndTs);
		CHANGE_CONFIG_VALUE(CONFIG_POINTS_BEGIN_TS, PointRankBeginTs);
		CHANGE_CONFIG_VALUE(CONFIG_POINTS_END_TS, PointRankEndTs);
		CHANGE_CONFIG_VALUE(CONFIG_PAYRANK_BEGIN_TS, PayRankBeginTs);
		CHANGE_CONFIG_VALUE(CONFIG_PAYRANK_END_TS, PayRankEndTs);
		CHANGE_CONFIG_VALUE("twice_reward_b",ZhuGeLiangB);
		CHANGE_CONFIG_VALUE("twice_reward_e",ZhuGeLiangE);
		CHANGE_CONFIG_VALUE(CONFIG_SUNCE_BEGIN_TS, SunCeB);
		CHANGE_CONFIG_VALUE(CONFIG_SUNCE_END_TS, SunCeE);
		CHANGE_CONFIG_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_BEGIN_TS, HundPaybegin);
		CHANGE_CONFIG_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_END_TS, HundPayend);
		CHANGE_CONFIG_VALUE(CONFIG_MERRYSOULS_BEGIN_TS,MerrySoulsbegin);
		CHANGE_CONFIG_VALUE(CONFIG_MERRYSOULS_END_TS,MerrySoulsend);

		CHANGE_CONFIG_PF_VALUE(CONFIG_MERRYSOULS_PF,MerrySouls_pf);
		CHANGE_CONFIG_PF_VALUE(CONFIG_PAY_OF_HUNDRED_DAYS_PF,Hund_pf);
		CHANGE_CONFIG_PF_VALUE(CONFIG_PAY_TOTAL_PF,PayTotal_pf);
		CHANGE_CONFIG_PF_VALUE(CONFIG_POINTS_PF,PointRank_pf);
		CHANGE_CONFIG_PF_VALUE(CONFIG_PAYRANK_PF,PayRank_pf);



		if (!PointRankVersion.empty())
		{
			unsigned timeValue = Convert::StringToUInt(PointRankVersion);
			ret = logicAdmin.ChangeActivityTime(CONFIG_POINTS_VERSION, timeValue);
			if (0 != ret)
				return ret;
			m_jsonResult["PointRankVersion"] = timeValue;
		}

		if (!PayRankVersion.empty())
		{
			unsigned timeValue = Convert::StringToUInt(PayRankVersion);
			ret = logicAdmin.ChangeActivityTime(CONFIG_PAYRANK_VERSION, timeValue);
			if (0 != ret)
				return ret;
			m_jsonResult["PayRankVersion"] = timeValue;
		}

		if (!MerrySoulsVersion.empty())
		{
			unsigned timeValue = Convert::StringToUInt(MerrySoulsVersion);
			ret = logicAdmin.ChangeActivityTime(CONFIG_MERRYSOULS_VERSION, timeValue);
			if (0 != ret)
				return ret;
			m_jsonResult["MerrySoulsVersion"] = timeValue;
		}

		return 0;
	}
	*/

	int AddGM()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		if (name.empty() || skey.empty() || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
		if (ret != 0)
			return ret;

		ret = logicAdmin.SetFlag(openid,gm_admin);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("ChageGMList_fail");
		}
		CLogicAdmin::Log(name, "add_GM", openid,time(0),skey,"");
		return 0;
	}

	int DelGM()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		if (name.empty() || skey.empty() || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
		if (ret != 0)
			return ret;

		ret = logicAdmin.SetFlag(openid,gm_none);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("ChageGMList_fail");
		}
		CLogicAdmin::Log(name, "del_GM", openid,88,skey,"");
		return 0;
	}

	int Add_th()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			return 1;
			/*
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
			*/
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
			if (ret != 0)
				return ret;
		}

		ret = logicAdmin.SetFlag(openid,gm_th);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("ChageTHList_fail");
		}

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "add_th", openid, time(0), skey, "");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "add_th", openid, time(0), skey, "");
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"运营号",openid,0,0,0);

		return 0;

	}

	int Del_th()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			return 1;
			/*
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
			*/
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
			if (ret != 0)
				return ret;
		}

		ret = logicAdmin.SetFlag(openid,gm_none);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("ChageTHList_fail");
		}
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "del_th", openid,99,skey,"");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "del_th", openid, 99, skey, "");
		}
		return 0;
	}

	int Add_ip()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			return 1;
			/*
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
			*/
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
			if (ret != 0)
				return ret;
		}

		ret = logicAdmin.SetFlag(openid,gm_ip);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("ChageIPList_fail");
		}

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "add_ip", openid, time(0), skey, "");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "add_ip", openid, time(0), skey, "");
		}

		return 0;
	}

	int Del_ip()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			return 1;
			/*
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
			*/
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
			if (ret != 0)
				return ret;
		}

		ret = logicAdmin.SetFlag(openid,gm_none);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("ChageIPList_fail");
		}
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "del_ip", openid,99,skey,"");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "del_ip", openid, 99, skey, "");
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"解除ip限制",openid,0,0,0);

		return 0;
	}

	int changeBlockTsByOpenId()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		string blockts = CCGIIn::GetCGIStr("blockts");
		string close_reason = CCGIIn::GetCGIStr("resonforclose");
		if (name.empty() || skey.empty() || openid.empty() || close_reason.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
		if (ret != 0)
			return ret;

		unsigned block_time = (unsigned)CTime::ParseDate(blockts);
		ret = logicAdmin.ChangeBlockTs(openid,block_time,close_reason);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("ChangeBlockTs");
		}
		return 0;
	}
	int QueryBlockTsByOpenId()
	{
		string openid = CCGIIn::GetCGIStr("openid");
		if (openid.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;

		int ret = logicAdmin.GetBlockTs(openid,m_jsonResult);
		if (0 != ret)
		{
			REFUSE_RETURN_MSG("QueryBlockTsByOpenId");
		}
		return 0;
	}


	int QueryInviteList()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}
		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = logicAdmin.GetInviteList(uid,m_jsonResult["invitelist"]);
		if (ret != 0)
			return ret;
		return 0;
	}

	int AddAccCharge()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int acc = CCGIIn::GetCGIInt("acc");
		string accs = CCGIIn::GetCGIStr("acc");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		int channel = CCGIIn::GetCGIInt("channel");
		if (name.empty() || skey.empty() || reason.empty() || (int) uid == CCGIIn::CGI_INT_ERR
				|| acc == CCGIIn::CGI_INT_ERR) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);


		ret = logicAdmin.AddAccCharge(uid, acc);
		if(ret)
			return ret;

		m_jsonResult["ts"] = ts;
		CGI_SEND_LOG("action=AddAccCharge&name=%s&uid=%u", name.c_str(), uid);
		if (1 != custom)
		{
			if(channel == 99)
			{
				CLogicAdmin::R_Log(name, "AddAccCharge", reason, uid,accs, CTrans::ITOS(acc));
			}
			else
			{
				CLogicAdmin::Log(name, "AddAccCharge", reason, uid,accs, CTrans::ITOS(acc));
			}
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "AddAccCharge", reason, uid, accs, CTrans::ITOS(acc));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"累积充值",reason,uid,0,acc);

		return 0;
	}

	int AddAttack()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned attackuid = CCGIIn::GetCGIInt("attackuid");
		unsigned defenceuid = CCGIIn::GetCGIInt("defenceuid");
		int res = CCGIIn::GetCGIInt("resources");
		string ress = CCGIIn::GetCGIStr("resources");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || (int) attackuid == CCGIIn::CGI_INT_ERR
				|| res == CCGIIn::CGI_INT_ERR) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", 0);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;

		ret = logicAdmin.AddAttack(attackuid, defenceuid,res);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=AddAttack&name=%s&uid=%u&res=%d", name.c_str(), attackuid,res);

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "AddAttack", "", attackuid, ress, CTrans::ITOS(defenceuid));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "AddAttack", "", attackuid, ress, CTrans::ITOS(defenceuid));
		}
		return 0;
	}

	int QueryBuilding()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIUin("uid");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty()) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", 0);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}
		CLogicBuilding logiBuilding;
		ret = logiBuilding.GetBuilding(uid, 0, m_jsonResult["data"], true);
		if (0 != ret)
			return ret;
		return 0;
	}

	int UpdateBuilding()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		int id = CCGIIn::GetCGIInt("bid");
		int level = CCGIIn::GetCGIInt("blv");
		string reason = CCGIIn::GetCGIStr("reason");
		unsigned uid = CCGIIn::GetCGIUin("uid");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty()) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;

		ret = logicAdmin.UpdateBuildingLevel(uid, id, level);
		if (0 != ret)
			return ret;
		CGI_SEND_LOG("action=UpdateBuildingLevel&name=%s&uid=%u,id=%d,level=%d",
				name.c_str(), uid, id, level);
		string value = CTrans::ITOS(id) + ":" + CTrans::ITOS(level);
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "UpdateBuildingLevel", reason, uid, value);
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "UpdateBuildingLevel", reason, uid, value);
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"建筑等级",reason,uid,id,level);

		return 0;
	}
	int ChangeProtectTime()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string protime = CCGIIn::GetCGIStr("protecttime");
		string change_reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || protime.empty() || change_reason.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		unsigned pro_time = (unsigned)CTime::ParseDate(protime);
		if (pro_time == 0)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		ret = logicAdmin.ChangeProtectTs(uid, pro_time);
		if (ret != 0)
			return ret;

		m_jsonResult["protect_time"] = pro_time;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "chgpro_time", change_reason, uid, CTrans::ITOS(pro_time));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "chgpro_time", change_reason, uid, CTrans::ITOS(pro_time));
		}
		CGI_SEND_LOG("action=changeprotecttime&name=%s&protime=%s&pro_time=%change_reason=%s", name.c_str(), protime.c_str(), pro_time, change_reason.c_str());

		return 0;

	}

	int CopyArchive()
	{
		int ret = 0;
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned fromuid = CCGIIn::GetCGIInt("fromuid");
		unsigned touid = CCGIIn::GetCGIInt("touid");
		string reason = CCGIIn::GetCGIStr("reason");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param");
		}

		CLogicCustomServiceAdmin logicCustomServiceAdmin;
		ret = logicCustomServiceAdmin.CheckSession(name, skey, "", touid);
		if (ret != 0)
			return ret;
		ret = logicCustomServiceAdmin.CopyArchive(fromuid,touid);
		if (0 != ret)
		{
			return ret;
		}
		ret = checkIP(name);if(ret)	return ret;

		CLogicCustomServiceAdmin::Log(name, "CopyArchive", reason, touid, CTrans::ITOS(fromuid));
		CGI_SEND_LOG("action=CopyArchive&name=%s&fromuid=%u&touid=%u&reason=%s",
				name.c_str(), fromuid, touid, reason.c_str());
		return 0;
	}

	int ChangeStars()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int stars = CCGIIn::GetCGIInt("stars");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || stars == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeStars(uid, stars, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["stars"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changestars", reason, uid, CTrans::ITOS(stars));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changestars", reason, uid, CTrans::ITOS(stars));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"闯关星数",reason,uid,0,stars);

		CGI_SEND_LOG("action=changestars&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeSoul()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int soul = CCGIIn::GetCGIInt("soul");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || soul == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);


		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeSoul(uid, soul, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["soul"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changesoul", reason, uid, CTrans::ITOS(soul));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changesoul", reason, uid, CTrans::ITOS(soul));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"将灵",reason,uid,0,soul);

		CGI_SEND_LOG("action=changesoul&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int ChangeqlE()
	{
		int ts =  CCGIIn::GetCGIInt("ts");
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int qle = CCGIIn::GetCGIInt("qle");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || qle == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		unsigned balance = 0;
		ret = logicAdmin.ChangeqlE(uid, qle, balance);
		if (ret != 0)
			return ret;

		m_jsonResult["qle"] = balance;
		m_jsonResult["ts"] = ts;
		if (1 != custom)
		{
			CLogicAdmin::Log(name, "changeqle", reason, uid, CTrans::ITOS(qle));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "changeqle", reason, uid, CTrans::ITOS(qle));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"器魂",reason,uid,0,qle);

		CGI_SEND_LOG("action=changeqle&name=%s&balance=%u", name.c_str(), balance);
		return 0;
	}

	int UpdateGate()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int endGate = CCGIIn::GetCGIInt("gate");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty() || endGate == CCGIIn::CGI_INT_ERR )
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		CLogicGate gate;
		ret = gate.TH_UpdateGate(uid,endGate);
		if(ret != 0)
		{
			error_log("TH_UpdateGate_fail! uid=%d, endGate=%d",uid,endGate);
			return ret;
		}

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "UpdateGate", reason, uid,"");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "UpdateGate", reason, uid,"");
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"闯关数",reason,uid,0,endGate);

		return 0;
	}

	int UpdateWuhujiang()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned zhang = CCGIIn::GetCGIInt("zhang");
		unsigned jie = CCGIIn::GetCGIInt("jie");
		string reason = CCGIIn::GetCGIStr("resonforclose");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		CLogicAdmin admin;
		ret = admin.Changewuhujiang(uid, zhang, jie);
		if(ret != 0)
		{
			error_log("Changewuhujiang! uid=%d, zhang=%d, jie=%d",uid,zhang,jie);
			return ret;
		}

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "UpdateWuhujiang", reason, uid,"");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "UpdateWuhujiang", reason, uid,"");
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"五虎将进度",reason,uid,zhang,jie);

		return 0;
	}

	int THVIP()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");

		unsigned bIsYearVip = CCGIIn::GetCGIInt("bIsYearVip");
		unsigned bIsVip = CCGIIn::GetCGIInt("bIsVip");
		unsigned is_blue_vip = CCGIIn::GetCGIInt("is_blue_vip");
		unsigned is_blue_year_vip = CCGIIn::GetCGIInt("is_blue_year_vip");
		unsigned is_super_blue_vip = CCGIIn::GetCGIInt("is_super_blue_vip");

		unsigned viptype = VT_NORMAL;
		if(bIsYearVip)
			viptype |= VT_QQ_YELLOW_YEAR;
		if(bIsVip)
			viptype |= VT_QQ_YELLOW;
		if(is_blue_vip)
			viptype |= VT_QQ_BLUE;
		if(is_blue_year_vip)
			viptype |= VT_QQ_BLUE_YEAR;
		if(is_super_blue_vip)
			viptype |= VT_QQ_SUPER_BULE;

		unsigned nVipLevel = CCGIIn::GetCGIInt("nVipLevel");
		unsigned blue_vip_level = CCGIIn::GetCGIInt("blue_vip_level");

		unsigned viplevel = blue_vip_level*16 + nVipLevel;

		string reason = "NULL";
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || reason.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;


		DataUserBasic userBasic;
		CLogicUserBasic logicUserBasic;
		CDataUserBasic dbUserBasic;
		ret = logicUserBasic.GetUserBasicLimitWithoutPlatform(uid, userBasic);
		if(ret)
			return ret;
		userBasic.vip_type = viptype;
		userBasic.vip_level = viplevel;
		ret = dbUserBasic.SetUserBasicLimit(uid,PT_TEST,userBasic);
		if(ret)
			return ret;

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "Updatevip", reason, uid,"");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "Updatevip", reason, uid,"");
		}

		return 0;
	}

	int AddHero()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int hero_id = CCGIIn::GetCGIInt("hero_id");
		string reason = CCGIIn::GetCGIStr("reason");
		int ts =  CCGIIn::GetCGIInt("ts");
		int custom = CCGIIn::GetCGIInt("custom");
		string icon = CCGIIn::GetCGIStr("icon");
		string heroname = CCGIIn::GetCGIStr("heroname");
		int count = CCGIIn::GetCGIInt("count");
		if (name.empty() || skey.empty() || hero_id == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if(0 == hero_id)
		{
			PARAM_ERROR_RETURN_MSG("param_error_id_is_0");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);
		m_jsonResult["ts"] = ts;

		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("uid_error");
		}

		CDataXML *dataXML = CDataXML::GetCDataXML();
		if(!dataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}
		if(dataXML->CheckHero(hero_id))
		{
			LOGIC_ERROR_RETURN_MSG("id_error");
		}

		string code = "background_add";

		CLogicHero Hero;
		string hid = CDataXML::Hero2Str(hero_id);
		if(Hero.IsGodHero(hid) && (icon.empty() || heroname.empty()))
		{
			LOGIC_ERROR_RETURN_MSG("name_icon_error");
		}

		for(int i=0;i<count;++i)
		{
			ret = Hero.AddOneHero(uid,hid,code,m_jsonResult["hero"], icon, heroname);
			if(ret)
			{
				error_log("[background_add_hero_error] [uid=%u|hero_id=%u]", uid, hero_id);
				//return R_ERR_DATA;
			}
		}

		CGI_SEND_LOG("action=addhero&name=%s&uid=%u&hero_id=%d&count=%u", name.c_str(), uid, hero_id, count);
		CLogicAdmin::AddHeroOrEquip_Log(name, "addhero", reason, uid, hero_id, count);

		CLogicAdmin::AddCheckLog(name,m_ipstr,"发武将",reason,uid,hero_id,count);

		return 0;
	}

	int AddEquipment()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int count = CCGIIn::GetCGIInt("count");
		int equip_id = CCGIIn::GetCGIInt("equip_id");
		string reason = CCGIIn::GetCGIStr("reason");
		int ts =  CCGIIn::GetCGIInt("ts");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty() || equip_id == CCGIIn::CGI_INT_ERR)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if(0 == equip_id || 4040 == equip_id || 50063 == equip_id || 5110 == equip_id || 5111 == equip_id || 5114 == equip_id)
		{
			PARAM_ERROR_RETURN_MSG("param_error_id_is_0");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);
		m_jsonResult["ts"] = ts;

		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("uid_error");
		}

		CDataXML *dataXML = CDataXML::GetCDataXML();
		if(!dataXML)
		{
			error_log("GetInitXML fail");
			return R_ERR_DB;
		}
		if(dataXML->CheckEquipment(equip_id))
		{
			LOGIC_ERROR_RETURN_MSG("id_error");
		}

		vector<ItemAdd> equip_items;
		CLogicEquipment Equip;
		ItemAdd eqip;
		eqip.eqid = equip_id;
		eqip.count = count;
		eqip.q = 0;
		if(IS_ADVANCED_SET_EQID(equip_id))
			eqip.ch = 6; //套装品质
		else if(IS_SET_EQID(equip_id))
			eqip.ch = 5; //套装品质
		else if(IS_GENERAL_EQ_EQID(equip_id))
			eqip.ch = 4; //紫装品质
		else
			eqip.ch = 0;
		eqip.reason = "background_add";
		equip_items.push_back(eqip);

		ret = Equip.AddItems(uid,equip_items,m_jsonResult["add_equip"]);
		if(ret)
		{
			error_log("[background_add_equip_error] [uid=%u]", uid);
			return R_ERR_DATA;
		}

		CGI_SEND_LOG("action=addequipment&name=%s&uid=%u&addequip=%d&count=%u", name.c_str(), uid, equip_id, count);
		CLogicAdmin::AddHeroOrEquip_Log(name, "addequipment", reason, uid, equip_id, count);

		CLogicAdmin::AddCheckLog(name,m_ipstr,"发装备",reason,uid,equip_id,count);

		return 0;
	}

	int ChangeHeroCoin()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int coin = CCGIIn::GetCGIInt("coin");
		string reason = CCGIIn::GetCGIStr("reason");
		int ts =  CCGIIn::GetCGIInt("ts");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("uid_error");
		}
		unsigned blance = 0;
		ret = logicAdmin.ChangeHeroCoin(uid, coin, reason, blance);
		if(ret)
			return ret;

		m_jsonResult["ts"] = ts;
		m_jsonResult["balance"] = blance;
		CGI_SEND_LOG("action=ChangeHeroCoin&name=%s&uid=%u&coin=%d", name.c_str(), uid, coin);

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "ChangeHeroCoin", reason, uid, CTrans::ITOS(coin));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "ChangeHeroCoin", reason, uid, CTrans::ITOS(coin));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"兑换武将碎片积分",reason,uid,0,coin);

		return 0;
	}

	int ChangeRechargeAlliance()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int cash = CCGIIn::GetCGIInt("cash");
		string reason = CCGIIn::GetCGIStr("reason");
		int ts =  CCGIIn::GetCGIInt("ts");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("uid_error");
		}

		ret = logicAdmin.ChangeRechargeAlliance(uid, cash);
		if(ret)
			return ret;

		m_jsonResult["ts"] = ts;
		CGI_SEND_LOG("action=ChangeRechargeAlliance&name=%s&uid=%u&cash=%d", name.c_str(), uid, cash);

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "ChangeRechargeAlliance", reason, uid, CTrans::ITOS(cash));
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "ChangeRechargeAlliance", reason, uid, CTrans::ITOS(cash));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"联盟充值额度",reason,uid,0,cash);

		return 0;
	}

	int Charge()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string openid = CCGIIn::GetCGIStr("openid");
		int tpt = CCGIIn::GetCGIInt("platform");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		int cash = CCGIIn::GetCGIInt("cash");
		string reason = CCGIIn::GetCGIStr("reason");
		int custom = CCGIIn::GetCGIInt("custom");
		int ts =  CCGIIn::GetCGIInt("ts");
		int channel = CCGIIn::GetCGIInt("channel");
		if (name.empty() || skey.empty() || cash == CCGIIn::CGI_INT_ERR || cash <= 0)
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, openid, uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!openid.empty())
		{
			if (tpt <= PT_UNKNOW || tpt >= PT_MAX)
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
			PlatformType pt = static_cast<PlatformType>(tpt);
			CLogicUserBasic userBasic;
			ret = userBasic.GetUid(uid, pt, openid);
			if (ret != 0)
				return ret;
		}
		else
		{
			if (!IsValidUid(uid))
			{
				PARAM_ERROR_RETURN_MSG("param_error");
			}
		}

		bool bsave = false;
		DataPay pay;
		CLogicUser logicUser;
		DataUser user;
		Json::Value user_flag;
		Json::Reader reader;
		ret = logicUser.GetUser(uid,user);
		if(ret)
			return ret;
		reader.parse(user.user_flag, user_flag);

		CLogicPay logicPay;
		ret = logicPay.ChangePay(uid, cash, 0, pay, "THTOPUP", user_flag, bsave, PAY_FLAG_CHARGE|PAY_FLAG_NO_REPLY);
		if (0 != ret)
			return ret;

		logicPay.DoPay(uid,user,cash);
		if(bsave)
			logicUser.SetUserFlag(uid,user_flag);

		DataPayHistory payhis;
		payhis.channel = channel;
		payhis.channel_pay_id = "0";
		payhis.count = cash;
		payhis.credit = 0;
		payhis.status = PST_OK;
		payhis.type = 0;
		payhis.uid = uid;
		payhis.open_id = openid;
		ret = logicPay.AddPayHistory(payhis);
		if (ret != 0)
			return ret;

		m_jsonResult["balance"] = pay.cash;
		m_jsonResult["ts"] = ts;
		CGI_SEND_LOG("action=charge&name=%s&uid=%u&cash=%d&balance=%u", name.c_str(), uid, cash, pay.cash);

		//channel用于区分大r，内部体验及托 ；    0为gm渠道，99为大R，100为托。
		if (1 != custom)
		{
			if(channel == 99)
			{
				CLogicAdmin::R_Log(name, "charge", reason, uid, CTrans::ITOS(cash));
			}
			else
			{
				CLogicAdmin::Log(name, "charge", reason, uid, CTrans::ITOS(cash));
			}
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "charge", reason, uid, CTrans::ITOS(cash));
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"充值",reason,uid,0,cash);

		return 0;
	}

	/*
	int GMCoin()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string sdata = CCGIIn::GetCGIStr("data");
		string reason = CCGIIn::GetCGIStr("reason");
		if (reason.empty() || name.empty() || skey.empty() || sdata.empty()) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = logicAdmin.CheckSession(name, skey);
		if (ret != 0)
			return ret;
		ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
		if (ret != 0)
			return ret;
		ret = checkIP(name);if(ret)	return ret;

		CLogicPay logicPay;
		typedef pair<unsigned,int> cash;
		vector<cash> vec;
		vector<string> rlt;
		String::Split(sdata, ',', rlt);
		for(int i=0;i<rlt.size();++i)
		{
			cash temp(CTrans::STOI(rlt[i]), 200);
			vec.push_back(temp);
		}
		for(vector<cash>::iterator it=vec.begin();it!=vec.end();++it)
			logicPay.ChangePay(it->first, 0, it->second, "ADMINOP");

		CGI_SEND_LOG("action=gmcoin&name=%s", name.c_str());
		CLogicAdmin::Log(name, "gmcoin", reason, 0, sdata, "");

		string str = reason + "--" + sdata;
		CLogicAdmin::AddCheckLog(name,m_ipstr,"线上活动奖励",str,0,0,200);

		return 0;
	}
	*/

	int Th_Export()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string type = CCGIIn::GetCGIStr("type");
		int custom = CCGIIn::GetCGIInt("custom");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned ud = CCGIIn::GetCGIInt("ud");
		unsigned ts =  CCGIIn::GetCGIInt("ts");
		if ( name.empty() || skey.empty() || type.empty()) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		Json::FastWriter writer;
		Json::Value data;
		if(type == "user_tech")
		{
			ret = logicAdmin.Th_ExportUserTech(uid, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "user_stat")
		{
			ret = logicAdmin.Th_ExportUserStat(uid, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "hero")
		{
			ret = logicAdmin.Th_ExportHero(uid, ud, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "equip")
		{
			ret = logicAdmin.Th_ExportEquip(uid, ud, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "newAct")
		{
			ret = logicAdmin.Th_ExportNewAct(uid, ud, data);
			if (ret != 0)
				return ret;
		}

		m_jsonResult["ts"] = ts;
		m_jsonResult["data"] = writer.write(data);
		CGI_SEND_LOG("action=th_export&name=%s", name.c_str());
		if (1 != custom)
			CLogicAdmin::Log(name, "th_export", type, 0, "", "");
		else
			CLogicCustomServiceAdmin::Log(name, "th_export", type, 0, "", "");

		CLogicAdmin::AddCheckLog(name,m_ipstr,"gm_th导出单个英雄或单件装备或活动或user_tech或user_stat",type,uid,ud,0);

		return 0;
	}

	int Th_Import()
	{
		if(!OpenPlatform::IsOurPlatform())
			return -1;

		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		string type = CCGIIn::GetCGIStr("type");
		string reason = CCGIIn::GetCGIStr("reason");
		string sdata = CCGIIn::GetCGIStr("data");
		int custom = CCGIIn::GetCGIInt("custom");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		unsigned ud = CCGIIn::GetCGIInt("ud");
		unsigned ts =  CCGIIn::GetCGIInt("ts");
		if ( name.empty() || skey.empty() || type.empty()) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", uid);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_ALL);
			if (ret != 0)
				return ret;
		}
		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		Json::Reader reader;
		Json::Value data;
		if (!reader.parse(sdata, data)) {
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		if(type == "user_tech")
		{
			ret = logicAdmin.Th_ImportUserTech(uid, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "user_stat")
		{
			ret = logicAdmin.Th_ImportUserStat(uid, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "hero")
		{
			ret = logicAdmin.Th_ImportHero(uid, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "equip")
		{
			ret = logicAdmin.Th_ImportEquip(uid, data);
			if (ret != 0)
				return ret;
		}
		else if(type == "newAct")
		{
			ret = logicAdmin.Th_ImportNewAct(uid, data);
			if (ret != 0)
				return ret;
		}

		m_jsonResult["ts"] = ts;
		sdata = Json::ToString(data);
		CGI_SEND_LOG("action=th_import&name=%s&uid=%u", name.c_str(), uid);
		if (1 != custom)
			CLogicAdmin::Log(name, "th_import", reason, uid, "", sdata);
		else
			CLogicCustomServiceAdmin::Log(name, "th_import", reason, uid, "", sdata);
		CLogicAdmin::AddCheckLog(name,m_ipstr,"gm_th导入单个英雄或单件装备或活动或user_tech或user_stat",reason,uid,ud,0);

		return 0;
	}

	int KickOffline()
	{
		string name = CCGIIn::GetCGIStr("username");
		string skey = CCGIIn::GetCGIStr("skey");
		unsigned uid = CCGIIn::GetCGIInt("uid");
		string reason = CCGIIn::GetCGIStr("reason");
		int ts =  CCGIIn::GetCGIInt("ts");
		int custom = CCGIIn::GetCGIInt("custom");
		if (name.empty() || skey.empty())
		{
			PARAM_ERROR_RETURN_MSG("param_error");
		}

		CLogicAdmin logicAdmin;
		int ret = 0;
		if (1 == custom)
		{
			CLogicCustomServiceAdmin logicCustomServiceAdmin;
			ret = logicCustomServiceAdmin.CheckSession(name, skey, "", 0);
			if (ret != 0) return ret;
		}
		else
		{
			ret = logicAdmin.CheckSession(name, skey);
			if (ret != 0)
				return ret;
			ret = logicAdmin.CheckLevel(name, ADMIN_LEVEL_9);
			if (ret != 0)
				return ret;
		}

		ret = checkIP(name);if(ret)	return ret;
		ret = CheckTs(name,ts);if(ret)return ret;
		ts = Time::GetGlobalTime();
		AddTsCheck(name,ts);

		if (!IsValidUid(uid))
		{
			PARAM_ERROR_RETURN_MSG("uid_error");
		}

		ret = logicAdmin.KickOffline(uid);
		if(ret)
			return ret;

		m_jsonResult["ts"] = ts;
		CGI_SEND_LOG("action=KickOffline&name=%s&uid=%u", name.c_str(), uid);

		if (1 != custom)
		{
			CLogicAdmin::Log(name, "KickOffline", reason, uid, "");
		}
		else
		{
			CLogicCustomServiceAdmin::Log(name, "KickOffline", reason, uid, "");
		}

		CLogicAdmin::AddCheckLog(name,m_ipstr,"踢下线",reason,uid,0,0);

		return R_SUCCESS;
	}

public:
	static map<string,string> m_ipcheck;
	static map<string,int> m_tscheck;
	static map<string,pair<unsigned, unsigned> > m_trycheck;

};
map<string,string> CCgiAdmin::m_ipcheck;
map<string,int> CCgiAdmin::m_tscheck;
map<string,pair<unsigned, unsigned> > CCgiAdmin::m_trycheck;
CGI_MAIN(CCgiAdmin)
