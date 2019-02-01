/*
 * LogicBaiduReport.cpp
 *
 *  Created on: 2015-12-14
 *      Author: dawx5fsd
 */



#include "LogicBaiduReport.h"


int CLogicBaiduReport::Report(unsigned uid, string &action)
{
	int serverid;
	Config::GetDomain(serverid);

	CLogicUserBasic logicUserBasic;
	DataUserBasic userBasic;

	int ret = logicUserBasic.GetUserBasicLimit(uid, OpenPlatform::GetType(), userBasic);
	if (ret)
	{
		return ret;
	}

	CLogicUser logicUser;
	DataUser dataUser;

	ret = logicUser.GetUserLimit(uid, dataUser);
	if (ret)
	{
		return ret;
	}

	string timestamp = CTime::FormatTime("%Y-%m-%d %H:%M:%S", Time::GetGlobalTime());
	string openid = userBasic.open_id;

	// xxx: 注意
	string role_name = Crypt::UrlDecode(userBasic.name.empty() ? "null" : userBasic.name);
	unsigned role_level = dataUser.level;
	string role_time;

	if ("CREATE" == action)
	{
		role_time = CTime::FormatTime("%Y%m%d%H%M%S", dataUser.register_time);
	}
	else
	{
		role_time = CTime::FormatTime("%Y%m%d%H%M%S", Time::GetGlobalTime());
	}

	unsigned role_online_time = dataUser.ext / 60;
	unsigned role_count_online_time = (dataUser.last_active_time - dataUser.register_time) / 60;

	string ssid = CTrans::UTOS(serverid);
	string srl = CTrans::UTOS(role_level);
	string srot = CTrans::UTOS(role_online_time);
	string srcot = CTrans::UTOS(role_count_online_time);


	static const string url = "http://youxi.baidu.com/roleAction/gameRolePost.jsp";
	static const string multi_flag = "N";
	string api_key = OpenPlatform::GetPlatform()->GetAppId();
	string app_secret = OpenPlatform::GetPlatform()->GetAppKey();

	// 按字典顺序
	string osig = app_secret + "action" + action + "api_key" + api_key
			+ "multi_flag" + multi_flag
			+ "role_count_online_time" + role_count_online_time
			+ "role_level" + srl
			+ "role_name" + role_name
			+ "role_online_time" + srot
			+ "role_time" + role_time
			+ "server_id" + ssid
			+ "timestamp" + timestamp
			+ "user_id" + openid;

	string sig = Crypt::Md5Encode(osig);

	// 转化成大写
	String::ToUpper(sig);

	string data;
	data.append("api_key=").append(api_key);
	data.append("&user_id=").append(openid);
	data.append("&server_id=").append(ssid);
	data.append("&timestamp=").append(timestamp);
	data.append("&role_name=").append(role_name);
	data.append("&role_time=").append(role_time);
	data.append("&action=").append(action);
	data.append("&multi_flag=").append(multi_flag);
	data.append("&role_level=").append(srl);
	data.append("&role_online_time=").append(srot);
	data.append("&role_count_online_time=").append(srcot);
	data.append("&sign=").append(sig);

	string response;
	if (!Network::HttpPostRequest(response, url, data) || response.empty())
	{
		error_log("[http request fail][openid=%s,url=%s,response=%s]",
				openid.c_str(), url.c_str(), response.c_str());
		return -1;
	}

	if ("recive ok" != response)
	{
		error_log("[recive error][response = %s, osig = %s, sig = %s]", response.c_str(), osig.c_str(), sig.c_str());
		return R_ERR_DATA;
	}
	return R_SUCCESS;
}
