
#include "LogicInc.h"

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
		int serverid = CCGIIn::GetCGIInt("serverid", 0, 100000, 0, 0);
		string js_code = CCGIIn::GetCGIStr("code");//接入微信平台前端传入的code
		string itest  = CCGIIn::GetCGIStr("itest");
		string token  = CCGIIn::GetCGIStr("token");//小米4部接入传入的token
		ConfigManager::Instance()->SetServer(serverid);
		int isWhite = (openkey.empty() && OpenPlatform::GetType() != PT_TEST && OpenPlatform::GetType() != PT_WX && OpenPlatform::GetType() != PT_XMFOUR && OpenPlatform::GetType() != PT_XMZZ && OpenPlatform::GetType() != PT_VIVO && OpenPlatform::GetType() != PT_OPPO) ? 1 : 0;
		String::Trim(openid);
		if (openid.empty())
		{
			if(OpenPlatform::GetType() != PT_WX && OpenPlatform::GetType() != PT_XMFOUR){
				error_log("[openid is empty][platform=%d,openid=%s,openkey=%s]",
					OpenPlatform::GetType(), openid.c_str(),openkey.c_str());
				PARAM_ERROR_RETURN_MSG("check_openid_fail");
			}
		}
		if(OpenPlatform::GetType() == PT_360)
		{
			openid = Crypt::UrlDecode(openid);
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
				int ret = CDataUserMapping().GetMapping(openid, PT_TEST, uid);
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
			if(OpenPlatform::GetType() == PT_XUNLEI)
			{
				params["clienttype"] = CCGIIn::GetCGIStr("clienttype");
			}
			else if(OpenPlatform::GetType() == PT_7k7k)
			{
				params["vip_type"] = CCGIIn::GetCGIStr("vip_type");
				params["vip_expired"] = CCGIIn::GetCGIStr("vip_expired");
			}
			else if(OpenPlatform::GetType() == PT_WX)
			{
				params["code"] = js_code;
			}
			else if(OpenPlatform::GetType() == PT_XMFOUR)
			{
				params["token"] = token;
			}
			else if(OpenPlatform::GetType() == PT_4399)
			{
				string site = CCGIIn::GetCGIStr("site");
				params["site"] = site;
			}
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
			ret = LogicUserMapping.LoginPlatformUser(OpenPlatform::GetPlatform()->GetPlatformByPF(), userinfo, iopenid, uid, isNewUser, via);
			if(ret != 0)
				return ret;
		}

		if(OpenPlatform::GetType() == PT_TEST && ((uid & 0x1) == 0))	// 偶数ID
		{
			userinfo.msg.set_isbluevip(1);
			userinfo.msg.set_isblueyearvip(1);
			userinfo.msg.set_issuperbluevip(1);
			userinfo.msg.set_blueviplevel(4);
		}

		userinfo.msg.set_uid(uid);
		userinfo.msg.set_openkey(openkey);
		userinfo.msg.set_ts(Time::GetGlobalTime());
		userinfo.msg.set_fig(userinfo.FigureUrl);
		userinfo.msg.set_name(userinfo.Name);
		userinfo.msg.set_isnew(isNewUser);
		userinfo.msg.set_platform(isWhite?0:((unsigned)OpenPlatform::GetPlatform()->GetPlatformByPF()));
		if(OpenPlatform::GetType() != PT_WX && OpenPlatform::GetType() != PT_XMFOUR)
			userinfo.msg.set_openid(openid);
		else
			userinfo.msg.set_openid(userinfo.OpenId);

		string suid = CTrans::UTOS(uid);
		string sts = CTrans::UTOS(Time::GetGlobalTime());
		string sak(DAWX_RALF_KEY);
		string sig = Crypt::Md5Encode(suid + openkey + sts + sak);
		userinfo.msg.set_sig(sig);

		//string out;
		//userinfo.msg.SerializeToString(&out);
		Proto2Json p2j;
		p2j._p2j(&userinfo.msg, m_jsonResult["msg"]);

		const Demo::Server& c = ConfigManager::Instance()->GetServer(ConfigManager::Instance()->GetServer());
		//m_jsonResult["open_ts"] = Config::GetIntValue(CONFIG_OPEN_TS);
		m_jsonResult["cur_pt"] = (int)OpenPlatform::GetType();
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		if(pf == "wechat")
		{
			if(itest == "1")
			{
				//表明需连测试服
				m_jsonResult["tcp_server"] = "test.wx.tianyuan.dawx.net:7001";
				m_jsonResult["access_host"] = "test.wx.tianyuan.dawx.net";
			}
			else
			{
				m_jsonResult["tcp_server"] = "wx.tianyuan.dawx.net:7001";
				if(c.accesshost() == "118.89.27.97")
					m_jsonResult["access_host"] = "g1.tianyuan.dawx.net";
				else if(c.accesshost() == "111.230.140.229")
					m_jsonResult["access_host"] = "g3.tianyuan.dawx.net";
				else
				{
					REFUSE_RETURN_MSG("access_server_error");
				}

			}

		}
		else if(pf == "oppo")
		{
			if(itest == "1")
			{
				//表明需连测试服
				m_jsonResult["tcp_server"] = "test.wx.tianyuan.dawx.net:7001";
				m_jsonResult["access_host"] = "test.wx.tianyuan.dawx.net";
			}
			else
			{
				m_jsonResult["tcp_server"] = "wx.tianyuan.dawx.net:7001";
				if(c.accesshost() == "118.89.27.97")
					m_jsonResult["access_host"] = "g1.tianyuan.dawx.net";
				else if(c.accesshost() == "111.230.140.229")
					m_jsonResult["access_host"] = "g3.tianyuan.dawx.net";
				else
				{
					REFUSE_RETURN_MSG("access_server_error");
				}

			}

		}
		else if(pf == "facebook-instant")
		{
			if(itest == "1")
			{
				//表明需连测试服
				m_jsonResult["tcp_server"] = "test.tianyuan.dawx.com:7001";
				m_jsonResult["access_host"] = "test.tianyuan.dawx.com";
			}
			else
			{
				m_jsonResult["tcp_server"] = "tianyuan.dawx.com:7001";
				m_jsonResult["access_host"] = "tianyuan.dawx.com";
			}
		}
		else if(pf == "xiaomi2")
		{
			m_jsonResult["tcp_server"] = "wx.tianyuan.dawx.net:7001";
			if(c.accesshost() == "118.89.27.97")
				m_jsonResult["access_host"] = "g1.tianyuan.dawx.net";
			else if(c.accesshost() == "111.230.140.229")
				m_jsonResult["access_host"] = "g3.tianyuan.dawx.net";
			else
			{
				REFUSE_RETURN_MSG("access_server_error");
			}
		}
		else
		{
			m_jsonResult["tcp_server"] = Config::GetValue(CONFIG_TCP_SERVER);
			m_jsonResult["access_host"] = c.accesshost();
		}
		m_jsonResult["access_port"] = c.accessport();
		m_jsonResult["serverid"] = c.begin();
		m_jsonResult["switch"] = Config::GetIntValue("switch");

		CGI_SEND_LOG("uid=%u&platform=%d&openid=%s&openkey=%s&iopenid=%s&isWhite=%d",
				uid, OpenPlatform::GetPlatform()->GetPlatformByPF(), openid.c_str(), openkey.c_str(), iopenid.c_str(), isWhite);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLogin)
