
#include "LogicInc.h"
#include "comm.h"

class CCgiLogin : public CCgiBase
{
public:
	CCgiLogin() : CCgiBase("login")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_VERSION);
	}

	CGI_DIRECT_PROCESS(Login)

	int Login()
	{
		//解析参数
		string openid = CCGIIn::GetCGIStr("openid");
		string openkey = CCGIIn::GetCGIStr("openkey");
		string iopenid = CCGIIn::GetCGIStr("iopenid");
		string pf = CCGIIn::GetCGIStr("pf");
		unsigned app_appbitmap = CCGIIn::GetCGIInt("app_appbitmap");
		string via = CCGIIn::GetCGIStr("via");
		string time = CCGIIn::GetCGIStr("time");
		string cm = CCGIIn::GetCGIStr("cm");
		int isWhite = openkey == "white" ? 1 : 0;
		if (openid.empty())
		{
			error_log("[openid is empty][platform=%d,openid=%s,openkey=%s]",
					OpenPlatform::GetType(), openid.c_str(),openkey.c_str());
			PARAM_ERROR_RETURN_MSG("check_openid_fail");
		}

		//GM flag
		CLogicAdmin logicAdmin;
		unsigned gmFlag = gm_none;
		logicAdmin.CheckGM(openid, gmFlag);
		if(gmFlag == gm_forbid)
		{
			REFUSE_RETURN_MSG("being_blocked");
		}
		m_jsonResult["flag"] = gmFlag;

		//  获取UID
		OPUserInfo userinfo;
		unsigned uid = 0;
		bool isNewUser = false;
		if (isWhite == 1)
		{
			if(gmFlag == gm_white)
			{
				CDataUserMapping dbUserMapping;
				int ret = dbUserMapping.GetMapping(openid, PT_TEST, uid);
				if(ret)
				{
					error_log("[GetMapping fail][ret=%d,openid=%s]", ret, openid.c_str());
					DB_ERROR_RETURN_MSG("db_get_user_mapping_fail");
				}
			}
			else
			{
				error_log("[invalid white user][openid=%s,openkey=%s]", openid.c_str(), openkey.c_str());
				REFUSE_RETURN_MSG("check_white_user_fail");
			}

			int is_yellow_vip = 1;
			int is_yellow_year_vip = 1;
			int yellow_vip_level = 4;
			userinfo.msg.set_is_yellow_vip(is_yellow_vip);
			userinfo.msg.set_is_yellow_year_vip(is_yellow_year_vip);
			userinfo.msg.set_yellow_vip_level(yellow_vip_level);

			int level_3366 = 4;
			string level_name_3366("Ralf");
			int grow_level_3366 = 4;
			int grow_value_3366 = 4;
			userinfo.msg.set_ttss_level(level_3366);
			userinfo.msg.set_ttss_level_name(level_name_3366);
			userinfo.msg.set_ttss_grow_level(grow_level_3366);
			userinfo.msg.set_ttss_grow_value(grow_value_3366);

			int is_blue_vip = 1;
			int is_blue_year_vip = 1;
			int is_super_blue_vip = 1;
			int blue_vip_level = 4;
			userinfo.msg.set_is_blue_vip(is_blue_vip);
			userinfo.msg.set_is_blue_year_vip(is_blue_year_vip);
			userinfo.msg.set_is_super_blue_vip(is_super_blue_vip);
			userinfo.msg.set_blue_vip_level(blue_vip_level);

			info_log("[white user login][uId=%d,openid=%s,openkey=%s]", uid, openid.c_str(), openkey.c_str());
		}
		else
		{
			// 非白名单
			int ret = 0;

			map<string, string> params;
			params["pf"] = pf;
			params["userip"] = m_ipstr;
			params["app_appbitmap"] = CTrans::ITOS(app_appbitmap);
			params["time"] = time;
			params["cm"] = cm;
			OpenPlatform::GetPlatform()->SetParameter(params);

			ret = OpenPlatform::GetPlatform()->GetUserInfo(userinfo, openid, openkey);
			if (ret != 0)
			{
				if(OpenPlatform::GetType() == PT_TEST && ret == R_ERR_DATA_LIMIT)
				{
					ERROR_RETURN_MSG(R_ERR_DATA_LIMIT, "名字中包含非法字符");
				}

				error_log("[GetUserInfo fail][ret=%d,openid=%s,openkey=%s]",
						ret,openid.c_str(),openkey.c_str());
				PT_ERROR_RETURN_MSG("get_user_info_fail");
			}

			CLogicUserMapping LogicUserMapping;
			ret = LogicUserMapping.LoginPlatformUser(OpenPlatform::GetPlatform()->GetPlatformByPF(), userinfo, iopenid, uid,isNewUser,via);
			if(ret != 0)
				return ret;
		}

		userinfo.msg.set_uid(uid);
		userinfo.msg.set_openkey(openkey);
		userinfo.msg.set_ts(Time::GetGlobalTime());
		userinfo.msg.set_fig(userinfo.FigureUrl);
		userinfo.msg.set_isnew(isNewUser);
		userinfo.msg.set_platform((unsigned)OpenPlatform::GetPlatform()->GetPlatformByPF());
		userinfo.msg.set_kingdom(0);

		string suid = CTrans::UTOS(uid);
		string sts = CTrans::UTOS(Time::GetGlobalTime());
		string sak(DAWX_RALF_KEY);
		string sig = Crypt::Md5Encode(suid + openkey + sts + sak);
		userinfo.msg.set_sig(sig);

		string out;
		userinfo.msg.SerializeToString(&out);
		Proto2Json p2j;
		p2j._p2j(&userinfo.msg, m_jsonResult["msg"]);

		m_jsonResult["open_ts"] = Config::GetIntValue(CONFIG_OPEN_TS);
		m_jsonResult["cur_pt"] = (int)OpenPlatform::GetType();
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		m_jsonResult["tcp_server"] = Config::GetValue(CONFIG_TCP_SERVER);
		m_jsonResult["access_server"] = Config::GetValue(CONFIG_ACCESS_SERVER);
		int serveridb;
		Config::GetDomain(serveridb);
		m_jsonResult["serverid"] = serveridb;
		set<int> db;
		MainConfig::GetIncludeDomains(serveridb, db);
		m_jsonResult["domains"].resize(0);
		for(set<int>::iterator it=db.begin();it!=db.end();++it)
			m_jsonResult["domains"].append(*it);

		CGI_SEND_LOG("uid=%u&platform=%d&openid=%s&openkey=%s&iopenid=%s&isWhite=%d",
				uid, OpenPlatform::GetPlatform()->GetPlatformByPF(), openid.c_str(), openkey.c_str(), iopenid.c_str(), isWhite);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLogin)
