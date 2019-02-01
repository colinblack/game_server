
#include "LogicInc.h"

class CCgiLogin : public CCgiBase
{
public:
	CCgiLogin() : CCgiBase("login")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		//SetFeature(CF_COMPRESS_OUT);
	}

	CGI_DIRECT_PROCESS(Login)

	int Login()
	{
		//解析参数
		string openid;
		if (!Json::GetString(m_data, "openid", openid))
		{
			PARAM_ERROR_RETURN_MSG("check_openid_fail");
		}
		string openkey;
		Json::GetString(m_data, "openkey", openkey);
		string iopenid;
		Json::GetString(m_data, "iopenid", iopenid);
		int isWhite = openkey == "white" ? 1 : 0;//0;
		//Json::GetInt(m_data, "white", isWhite);
		string promotionId;
		Json::GetString(m_data, "spreadid", promotionId);
		unsigned spreadid = atoi(promotionId.c_str());
		string via("NULL");
		Json::GetString(m_data, "via", via);
		if (openid.empty())
		{
			error_log("[openid is empty][platform=%d,openid=%s,openkey=%s]",
					OpenPlatform::GetType(), openid.c_str(),openkey.c_str());
			PARAM_ERROR_RETURN_MSG("check_openid_fail");
		}
		string myip,ip,ipstr;
		Json::GetString(m_data, "ip", myip);
		vector<string> rlt;
		String::Split(myip, ',', rlt);
		if (rlt.size() >= 3)
		{
			ip = rlt[0];
			ipstr = rlt[2];
		}

		//GM flag
		CLogicAdmin logicAdmin;
		unsigned gmFlag = gm_none;
		logicAdmin.CheckGM(openid, gmFlag);
		if(gmFlag == gm_forbid)
		{
			REFUSE_RETURN_MSG("being_blocked");
		}

		if((gmFlag == gm_ip/* || gmFlag == gm_th*/) && ip != "218.17.157.202")
		{
			error_log("check_ip_fail,openid=%s,ip=%s",openid.c_str(),ip.c_str());
			PARAM_ERROR_RETURN_MSG("check_locale_fail");
		}

		m_jsonResult["gm"] = (gmFlag == gm_admin)?1:0;
		m_jsonResult["th"] = (gmFlag == gm_th)?1:0;
		m_jsonResult["old_gift"] = 0;

		if(gmFlag == gm_gift || gmFlag == gm_s_gift)
		{
			int ret = logicAdmin.SetFlag(openid, gm_none);
			if(ret)
				gmFlag = gm_none;
		}

		unsigned app_appbitmap = 0;
		Json::GetUInt(m_data, "app_appbitmap", app_appbitmap);

		//  获取UID
		OPUserInfo userinfo;
		unsigned uid = 0;
		/*
		if (WhiteList::Check(openid, openid))
		{
			error_log("[invalid white user][openid=%s,openkey=%s]", openid.c_str(), openkey.c_str());
			REFUSE_RETURN_MSG("check_white_user_fail");
			isWhite = 1;
		}
		*/
		if (isWhite == 1)
		{
			/*
			//  白名单
			//openkey = openid;
			if (!WhiteList::Check(openid, openkey))
			{
				error_log("[invalid white user][openid=%s,openkey=%s]", openid.c_str(), openkey.c_str());
				REFUSE_RETURN_MSG("check_white_user_fail");
			}
			//uid = Convert::StringToUInt(openid, 0);
			if (!IsValidUid(uid))
			{
				error_log("[invalid white user][openid=%s,openkey=%s]", openid.c_str(), openkey.c_str());
				REFUSE_RETURN_MSG("check_white_user_fail");
			}
			int ret = 0;

			map<string, string> params;
			string pf;
			if (Json::GetString(m_data, "pf", pf) && !pf.empty())
				params["pf"] = pf;
			params["userip"] = m_ipstr;
			OpenPlatform::GetPlatform()->SetParameter(params);
			CLogicUserBasic logicUserBasic;
			bool isNewUser = false;
			OPFriendList friendList;
			ret = logicUserBasic.LoginPlatformUser(OpenPlatform::GetPlatform()->GetPlatformByPF(), userinfo, friendList, iopenid, uid,isNewUser,via);
			if(ret != 0)
				return ret;
			*/

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

			info_log("[white user login][uId=%d,openid=%s,openkey=%s]", uid, openid.c_str(), openkey.c_str());
		}
		else
		{
			// 非白名单
			int ret = 0;

			map<string, string> params;
			string pf;
			if (Json::GetString(m_data, "pf", pf) && !pf.empty())
				params["pf"] = pf;
			params["userip"] = m_ipstr;
			params["app_appbitmap"] = CTrans::ITOS(app_appbitmap);
			if(m_data.isMember("time"))
			{
				if(m_data["time"].isString())
					params["time"] = m_data["time"].asString();
				else if(m_data["time"].isIntegral())
					params["time"] = CTrans::UTOS(m_data["time"].asInt());
			}
			if(m_data.isMember("cm"))
			{
				if(m_data["cm"].isString())
					params["cm"] = m_data["cm"].asString();
				else if(m_data["cm"].isIntegral())
					params["cm"] = CTrans::UTOS(m_data["cm"].asInt());
			}
			if(OpenPlatform::GetType() == PT_4399 || OpenPlatform::GetType() == PT_NEW_4399)
			{
				unsigned time = 0, cm = 0;
				Json::GetUInt(m_data, "time4399", time);
				Json::GetUInt(m_data, "cm4399", cm);
				params["time4399"] = CTrans::UTOS(time);
				params["cm4399"] = CTrans::UTOS(cm);
			}
			else if (OpenPlatform::GetType() == PT_XUNLEI)
			{
				if(m_data.isMember("clienttype"))
				{
					if(m_data["clienttype"].isString())
						params["clienttype"] = m_data["clienttype"].asString();
					else if(m_data["clienttype"].isIntegral())
						params["clienttype"] = CTrans::UTOS(m_data["clienttype"].asInt());
				}
			}
			else if (OpenPlatform::GetType() == PT_7k7k)
			{
				if(m_data.isMember("vip_type"))
				{
					if(m_data["vip_type"].isString())
						params["vip_type"] = m_data["vip_type"].asString();
					else if(m_data["vip_type"].isIntegral())
						params["vip_type"] = CTrans::UTOS(m_data["vip_type"].asInt());
				}
				if(m_data.isMember("vip_expired"))
				{
					if(m_data["vip_expired"].isString())
						params["vip_expired"] = m_data["vip_expired"].asString();
					else if(m_data["vip_expired"].isIntegral())
						params["vip_expired"] = CTrans::UTOS(m_data["vip_expired"].asInt());
				}
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

			if(userinfo.ExtraIntInfo.count("customflag"))
			{
				int customflag = userinfo.ExtraIntInfo["customflag"];
				if(customflag == 2)
					gmFlag = gm_gift;
				else if(customflag == 1 && gmFlag != gm_gift)
					gmFlag = gm_s_gift;
			}

			/*
			if(OpenPlatform::IsQQPlatform()	&& (gmFlag == gm_th))
			{
				userinfo.ExtraIntInfo["bIsVip"] = 1;
				userinfo.ExtraIntInfo["bIsYearVip"] = 0;
				userinfo.ExtraIntInfo["nVipLevel"] = 1;

				userinfo.ExtraIntInfo["is_blue_vip"] = 1;
				userinfo.ExtraIntInfo["is_blue_year_vip"] = 0;
				userinfo.ExtraIntInfo["blue_vip_level"] = 1;
				userinfo.ExtraIntInfo["is_super_blue_vip"] = 0;
			}
			*/

			userinfo.Province = ip;
			userinfo.City = ipstr;

			OPFriendList friendList;
			ret = OpenPlatform::GetPlatform()->GetAppFriendList(friendList, openid, openkey);
			if(ret != 0)
			{
				error_log("[GetAppFriendList fail][ret=%d,openid=%s,openkey=%s]",
						ret,openid.c_str(),openkey.c_str());
			}
			CLogicUserBasic logicUserBasic;
			bool isNewUser = false;
			ret = logicUserBasic.LoginPlatformUser(OpenPlatform::GetPlatform()->GetPlatformByPF(), userinfo, friendList, iopenid, uid,isNewUser,via,gmFlag);
			if(ret != 0)
				return ret;
			// 推广登记
//			if(OpenPlatform::GetType() == PT_TEST) //测试用，现网暂时屏蔽
//			{
				if(spreadid == 0 && OpenPlatform::GetType() == PT_TEST && isNewUser)
				{
					spreadid=10000001;

				}
				if(spreadid != 0 && isNewUser)
				{
					CLogicPromotionMapping logicPromotionMapping;
					DataPromotionMapping dataPromotionMapping;
					dataPromotionMapping.uid = uid;
					dataPromotionMapping.pid = spreadid;
					dataPromotionMapping.usetime = 0;
					dataPromotionMapping.useflag = 0;
					logicPromotionMapping.AddPromotionMapping(dataPromotionMapping);
				}
				if(isNewUser)
				{
					SPREAD_LOG("%s|%u|%u|%s|",openid.c_str(),uid,spreadid,iopenid.c_str());
				}
//			}
		}

		if (OpenPlatform::GetType() == 7)
		{
			size_t found = openkey.find('|');
			if (found != string::npos)
			{
				openkey = openkey.substr(0, found);
			}
		}
		//  分配KEY
		string skey = Session::CreateSessionKey(uid);
		string sessionData;
		String::Format(sessionData, "{\"rip\":%u,\"lvt\":%u,\"skey\":\"%s\",\"oid\":\"%s\",\"okey\":\"%s\",\"pt\":%d}",
				m_remoteip, Time::GetGlobalTime(), skey.c_str(), openid.c_str(), openkey.c_str(), OpenPlatform::GetType());
		Session::SetValue(uid, SESSION_DATA, sessionData);
		//m_skey = skey;

		int encode = CCGIIn::GetCGIInt("encode");

		CLogicUserBasic logicUserBasic;
		Json::Value friends, blacklist;

		int ret = logicUserBasic.GetFriendsJson(uid, OpenPlatform::GetType(), friends, (encode==1?true:false));
		if(ret != 0)
			return ret;

		ret = logicUserBasic.GetBlacksJson(uid, OpenPlatform::GetType(), blacklist);
		if(ret != 0)
			return ret;

		m_jsonResult["uid"] = uid;
		m_jsonResult["name"] = userinfo.Name;
		m_jsonResult["cur_pt"] = (int)OpenPlatform::GetType();
		m_jsonResult["currenttime"] = Time::GetGlobalTime();
		m_jsonResult["skey"] = skey;
		m_jsonResult["tcp_server"] = Config::GetValue(CONFIG_TCP_SERVER);
		m_jsonResult["all_server"] = Config::GetValue(CONFIG_ALL_SERVER);
		m_jsonResult["all_server_rank"] = Config::GetValue(CONFIG_ALL_SERVER_RANK);
		int serveridb;
		Config::GetDomain(serveridb);
		m_jsonResult["serverid"] = serveridb;
		set<int> db;
		MainConfig::GetIncludeDomains(serveridb, db);
		m_jsonResult["domains"].resize(0);
		for(set<int>::iterator it=db.begin();it!=db.end();++it)
			m_jsonResult["domains"].append(*it);
		m_jsonResult["defaultkingdom"] = Config::GetValue(CONFIG_DEFAULT_KINGDOM);
		m_jsonResult["friends"] = friends;
		m_jsonResult["black"] = blacklist;
		//读档
		Json::Value archive;
		CLogicArchive logicArchive;
		int result = logicArchive.Load(uid, uid, "login", m_data, m_jsonResult, 0, gmFlag);
		if (result != 0)
			return result;

		CLogicNominateAlliance nAlliance;
		ret = nAlliance.CheckAlliance(uid);

		/*************版署和谐用***********************
		if(openid == "2C8974AC5BD94624A2C9ED2FD81C9E65"
		|| openid == "BE5FD86BF5ACA88EC3B6921DD90CB3AD"
		|| openid == "0398EAEAE7012BE64EC0A1B8941F755A")//版署和我
		{
			m_jsonResult["nonage"] = 1;
		}
		else if(m_jsonResult["register_time"].asInt() > 1393487339
				&& (OpenPlatform::GetPlatform()->GetPlatformByPF() == 4
				|| OpenPlatform::GetPlatform()->GetPlatformByPF() == 2))
				//&& (m_jsonResult["register_platform"].asInt() == 4
				//|| m_jsonResult["register_platform"].asInt() == 2))//新号，略过滚服，加上版署
		{
			bool flag = true;
			vector<unsigned> registertime;
			CDataUserMapping dataUserMapping;
			dataUserMapping.GetAllRegisterTime(openid,registertime);
			for(vector<unsigned>::iterator it=registertime.begin();it!=registertime.end();++it)
			{
				if(*it < 1393487339)
				{
					flag = false;
					break;
				}
			}
			for(vector<unsigned>::iterator it=registertime.begin();it!=registertime.end();++it)
			{
				if(*it < 1387555200 && *it > 1386518400)
				{
					flag = true;
					break;
				}
			}
			if(flag)
			{
				m_jsonResult["nonage"] = 1;
				debug_log("%u,%u",m_jsonResult["register_time"].asInt() ,OpenPlatform::GetPlatform()->GetPlatformByPF());
			}
		}
		else if(m_jsonResult["register_time"].asInt() < 1393487339
				&& (OpenPlatform::GetPlatform()->GetPlatformByPF() == 4
				|| OpenPlatform::GetPlatform()->GetPlatformByPF() == 2))
				//&& (m_jsonResult["register_platform"].asInt() == 4
				//|| m_jsonResult["register_platform"].asInt() == 2))//老号，过滤版署
		{
			bool flag = false;
			vector<unsigned> registertime;
			CDataUserMapping dataUserMapping;
			dataUserMapping.GetAllRegisterTime(openid,registertime);
			for(vector<unsigned>::iterator it=registertime.begin();it!=registertime.end();++it)
			{
				if(*it < 1387555200 && *it > 1386518400)
				{
					flag = true;
					break;
				}
			}
			if(flag && m_jsonResult["level"].asInt() < 50)
			{
				m_jsonResult["nonage"] = 1;
				debug_log("%u,%u",m_jsonResult["register_time"].asInt() ,OpenPlatform::GetPlatform()->GetPlatformByPF());
			}
		}
		************************************/

		CGI_SEND_LOG("uid=%u&platform=%d&openid=%s&openkey=%s&iopenid=%s&isWhite=%d",
				uid, OpenPlatform::GetPlatform()->GetPlatformByPF(), openid.c_str(), openkey.c_str(), iopenid.c_str(), isWhite);
		return R_SUCCESS;
	}

};

CGI_MAIN(CCgiLogin)
