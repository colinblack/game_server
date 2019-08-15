#include "LogicQQReport.h"
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

unsigned  CLogicQQReport::m_ip = 0;

CLogicQQReport::CLogicQQReport()
{
	if(!m_ip)
	{
		struct ifaddrs * ifAddrStruct = NULL;

		getifaddrs(&ifAddrStruct);

		while (ifAddrStruct != NULL) {
			if (ifAddrStruct->ifa_addr->sa_family == AF_INET) { // check it is IP4
				// is a valid IP4 Address
				string eth = ifAddrStruct->ifa_name;
				if(eth == "eth1")
					m_ip = ntohl(((struct sockaddr_in *) ifAddrStruct->ifa_addr)->sin_addr.s_addr);
			}
			ifAddrStruct = ifAddrStruct->ifa_next;
		}

		//info_log("[qq report][m_ip=%u]", m_ip);
	}
}

QQPT CLogicQQReport::GetQQPT(string pt)
{
	if (pt.find("union") != string::npos)
	{
		return QQPT_union;
	}

	if(pt == "qzone")
		return QQPT_qzone;
	if(pt == "pengyou")
		return QQPT_pengyou;
	if(pt == "weibo")
		return QQPT_weibo;
	if(pt == "qqgame")
		return QQPT_qqgame;
	if(pt == "3366")
		return QQPT_3366;

	return QQPT_none;
}

int CLogicQQReport::Report(unsigned report, string openid, unsigned uid, unsigned fee, string userip, string pf, string zoneid, string pid)
{
	int ret = 0;

	if(report > QQREPORT_max)
		return 1;

	if(openid.empty())
		return 2;

	unsigned uidtemp;
	CDataUserMapping dbUserMapping;
	ret = dbUserMapping.GetMapping(openid, PT_PENGYOU, uidtemp);
	if (ret)
	{
		if(!uid)
			return 3;
	}
	else
		uid = uidtemp;

	unsigned ip;
	if(userip.empty())
		ip = CCGIIn::GetRemoteIP();
	else
	{
		struct in_addr addr;
		inet_aton(userip.c_str(), &addr);
		ip = ntohl(addr.s_addr);
	}

	unsigned pt;
	if(pf.empty())
		pf = CCGIIn::GetCGIStr("pf");
	pt = GetQQPT(pf);
	if(!pt)
		return 4;

	if(zoneid.empty())
	{
		string host = getenv("SERVER_NAME");
		vector<string> rlt;
		String::Split(host, '.', rlt);
		zoneid = rlt[0].substr(1,rlt[0].length()-1);
	}

	const string reportURL="http://tencentlog.com/stat/";
	const string reportAPI[QQREPORT_max]={
			"report_login.php",
			"report_register.php",
			"report_accept.php",
			"report_invite.php",
			"report_consume.php"
	};

	bool is_union = false;
	if(pf.find("union") != string::npos)
		is_union = true;

	string url = reportURL + reportAPI[report] + "?version=1";
	url += "&appid=" + OpenPlatform::GetPlatform()->GetAppId();
	url += "&userip=" + CTrans::UTOS(ip);
	url += "&svrip=" + CTrans::UTOS(m_ip);
	url += "&time=" + CTrans::UTOS(Time::GetGlobalTime());
	url += "&domain=" + CTrans::UTOS(pt);
	url += "&worldid=" + zoneid;
	url += "&opuid=" + CTrans::UTOS(uid);
	url += "&opopenid=" + openid;
	if (is_union)
	{
		url += "&reserve_5=" + pf;
	}
	if(report == QQREPORT_consume)
		url += "&modifyfee=" + CTrans::UTOS(fee);
	if ((report == QQREPORT_login || report == QQREPORT_consume) && !pid.empty())
	{
		url += "&wdpid=" + pid;
	}
//	if (report == QQREPORT_quit)
//	{
//		CLogicUser logicuser;
//		DataUser user;
//		logicuser.GetUserLimit(uid, user);
//		int onlinetime = user.last_login_time - Time::GetGlobalTime();
//		if (onlinetime < 0)
//			onlinetime = 0;
//		url += "&onlinetime=" + CTrans::UTOS(onlinetime);
//	}

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[report request fail][url=%s,response=%s]", url.c_str(), response.c_str());
		return 5;
	}
	Json::Value value;
	if(!Json::Reader().parse(response, value))
	{
		error_log("[report parse fail][url=%s]", url.c_str());
		return 6;
	}
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		//error_log("[report fail][url=%s,response=%s]", url.c_str(),response.c_str());
		return 7;
	}
	info_log("[qq report][url=%s, respons=%s]", url.c_str(), response.c_str());

	if (report == QQREPORT_register && is_union)
	{
		UnionReport(openid, uid, CTrans::UTOS(ip), pf, zoneid);
	}
	return 0;
}

int CLogicQQReport::ReportEx(unsigned report, string openid, unsigned uid, string userip, string pf, string zoneid) {
	int ret = 0;
	if (report > QQREPORT_max) {
		return 1;
	}
	if (openid.empty()) {
		return 2;
	}
	unsigned uidtemp;
	CDataUserMapping dbUserMapping;
	ret = dbUserMapping.GetMapping(openid, PT_PENGYOU, uidtemp);
	if (ret) {
		if (!uid) {
			return 3;
		}
	} else {
		uid = uidtemp;
	}
	unsigned ip;
	if (userip.empty()) {
		ip = CCGIIn::GetRemoteIP();
	} else {
		struct in_addr addr;
		inet_aton(userip.c_str(), &addr);
		ip = ntohl(addr.s_addr);
	}
	unsigned pt;
	if (pf.empty()) {
		pf = CCGIIn::GetCGIStr("pf");
	}
	pt = GetQQPT(pf);
	if (!pt) {
		return 4;
	}
//	CLogicUser logicUser;
//	DataUser user;
//	ret = logicUser.GetUserLimit(uid, user);
//	if (0 != ret) {
//		return 5;
//	}

	DataBase base;
	base.uid = uid;
	int ret_base = CDataBase().Get(base);
	if(0 != ret_base)
	{
		return 5;
	}

	if (zoneid.empty()) {
		string host = getenv("SERVER_NAME");
		vector<string> rlt;
		String::Split(host, '.', rlt);
		zoneid = rlt[0].substr(1, rlt[0].length() - 1);
	}
	const string url = OpenPlatform::GetPlatform()->GetConfig("report_domain");
	const string report_key = OpenPlatform::GetPlatform()->GetConfig("report_key");
	map<string, string> params;
	params["dtEventTime="] = CTime::FormatTime("%Y-%m-%d %H:%M:%S", Time::GetGlobalTime());
	params["iversion"] = "1.0.0";
	params["appid"] = OpenPlatform::GetPlatform()->GetAppId();
	params["userip"] = CTrans::UTOS(ip);
	params["svrip"] = CTrans::UTOS(m_ip);
	params["time"] = CTrans::UTOS(Time::GetGlobalTime());;
	params["domain"] = CTrans::UTOS(pt);
	params["iworldid"] = zoneid;
	params["optype"] = "3";
	params["actionid"] = CTrans::UTOS(report + 1);
	params["opuid"] = CTrans::UTOS(uid);
	params["opopenid"] = openid;
	params["level"] = CTrans::ITOS(base.level);
	if (report == QQREPORT_logout || report == QQREPORT_role_logout) {
//		if (!IsOnlineUser(base.last_active_time)) {
//			return 10;
//		}
		params["onlinetime"] = CTrans::ITOS(Time::GetGlobalTime() - base.last_login_time);
	}
	string data = "";
	for (map<string, string>::iterator itr = params.begin(); itr != params.end(); ++itr) {
		data.append(itr->first);
		data.append("=");
		data.append(itr->second);
		data.append("&");
	}
	Json::Value post_data;
	post_data = Json::Value(Json::objectValue);
	post_data["log_name"] = "log_common";
	post_data["log_fields"] = data.substr(0, data.size() - 1);
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long mts = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	Json::Value post;
	post["title"] = Json::Value(Json::objectValue);
	post["title"]["app_id"] = OpenPlatform::GetPlatform()->GetAppId();
	post["title"]["timestamp"] = Time::GetGlobalTime();
	post["title"]["seq_id"] = CTrans::UTOS(uid + mts);
	post["data"] = Json::Value(Json::arrayValue);
	post["data"].append(post_data);
	string post_str = Json::ToString(post);
	map<string, string> headers;
	headers["version"] = "1.0";
	headers["signature"] = Crypt::Md5Encode(post_str + report_key);
	string response;
	if (!Network::HttpPostRequest(response, url, post_str, headers) || response.empty()) {
		error_log("[report request fail][url=%s,response=%s,post=%s]", url.c_str(), response.c_str(), post_str.c_str());
		return 6;
	}
	Json::Value value;
	if (!Json::Reader().parse(response, value) || !value.isObject()) {
		error_log("[report parse fail][url=%s,response=%s,post=%s]", url.c_str(), response.c_str(), post_str.c_str());
		return 7;
	}
	if (!value.isMember("data") || !Json::GetInt(value["data"], "code", ret) || ret != 200) {
		error_log("[report fail][url=%s,response=%s,post=%s]", url.c_str(), response.c_str(), post_str.c_str());
		return 8;
	}
	info_log("[qq report][report=%u, openid=%s, uid=%u]", report, openid.c_str(), uid);
	return 0;
}

int CLogicQQReport::UnionReport(string openid, unsigned uid, string userip, string pf, string zoneid)
{
	string openkey = CCGIIn::GetCGIStr("openkey");
	string pfkey = CCGIIn::GetCGIStr("pfkey");
	string url = "http://union.tencentlog.com/cgi-bin/Register.cgi?version=1";
	url += "&appid=" + OpenPlatform::GetPlatform()->GetAppId();
	url += "&userip=" + userip;
	url += "&svrip=" + CTrans::UTOS(m_ip);
	url += "&time=" + CTrans::UTOS(Time::GetGlobalTime());
	url += "&worldid=" + zoneid;
	url += "&opuid=" + CTrans::UTOS(uid);
	url += "&opopenid=" + openid;
	url += "&pf=" + pf;
	url += "&openkey=" + openkey;
	url += "&pfkey=" + pfkey;
	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[UnionReport request fail][url=%s]", url.c_str());
		return 5;
	}
	Json::Value value;
	if(!Json::Reader().parse(response, value))
	{
		error_log("[UnionReport parse fail][url=%s]", url.c_str());
		return 6;
	}
	int ret = 0;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		error_log("[UnionReport fail][url=%s,response=%s]", url.c_str(),response.c_str());
		error_log("[UnionReport fail][openid=%s,pf=%s,pfkey=%s,iRet=%d]",
				openid.c_str(),pf.c_str(),pfkey.c_str(), ret);
		return 7;
	}
	return 0;
}

int CLogicQQReport::SetFeed(const string &openid, const string &openkey, const string &pf, const string &imgurl, const string &text)
{
	string url = "http://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + "/v3/spread/set_feed";

	string osig = "POST&" + Crypt::UrlEncodeForTX("/v3/spread/set_feed") + "&";

	string qsig = "appid=" + OpenPlatform::GetPlatform()->GetAppId()
			+ "&charset=utf-8" + "&flag=28"
			+ "&imgurl=" + imgurl
			+ "&openid=" + openid
			+ "&openkey=" + openkey
			+ "&pf=" + pf
			+ "&txt=" + text
			+ "&urlcmd_0=1&urlnum=1"
			+ "&urlparam_0=" + "&urltxt_0=PLAY";

	osig += Crypt::UrlEncodeForTX(qsig);
	//error_log("[qq set feed sig][sig=%s]", osig.c_str());
	string key = OpenPlatform::GetPlatform()->GetAppKey() + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);

	string data;
	data.append("appid=").append(Crypt::UrlEncodeForTX(OpenPlatform::GetPlatform()->GetAppId()));
	data.append("&charset=").append(Crypt::UrlEncodeForTX("utf-8"));
	data.append("&flag=28");
	data.append("&imgurl=").append(Crypt::UrlEncodeForTX(imgurl));
	data.append("&openid=").append(Crypt::UrlEncodeForTX(openid));
	data.append("&openkey=").append(Crypt::UrlEncodeForTX(openkey));
	data.append("&pf=").append(Crypt::UrlEncodeForTX(pf));
	data.append("&txt=").append(Crypt::UrlEncodeForTX(text));
	data.append("&urlcmd_0=1");
	data.append("&urlnum=1");
	data.append("&urlparam_0=");
	data.append("&urltxt_0=PLAY");
	data.append("&sig=").append(Crypt::UrlEncodeForTX(sig));

	string response;
	if (!Network::HttpPostRequest(response, url, data) || response.empty())
	{
		error_log("[http request fail][openid=%s,url=%s,response=%s]",
				openid.c_str(), url.c_str(), response.c_str());
		return -1;
	}

	Json::Value value;
	if(!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,data=%s,response=%s]",
				openid.c_str(), data.c_str(), response.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		//error_log("[json ret fail][openid=%s,data=%s,response=%s]",	openid.c_str(), data.c_str(), response.c_str());
		return -1;
	}
	//info_log("[qq set feed][data=%s, respons=%s]", data.c_str(), response.c_str());

	return 0;
}

int CLogicQQReport::SetAchievement(const string &openid, const string &openkey, const string &pf,string level, string zoneid)
{
	string attr = "{\"level\":" + level + ",\"area_name\":\"" + zoneid + "\"}";

	string url = "http://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + "/v3/user/set_achievement";

	string osig = "POST&" + Crypt::UrlEncodeForTX("/v3/user/set_achievement") + "&";

	string qsig = "appid=" + OpenPlatform::GetPlatform()->GetAppId()
			+ "&openid=" + openid
			+ "&openkey=" + openkey
			+ "&pf=" + pf
			+ "&user_attr=" + attr;

	osig += Crypt::UrlEncodeForTX(qsig);
	//error_log("[qq setachievement sig][sig=%s]", osig.c_str());
	string key = OpenPlatform::GetPlatform()->GetAppKey() + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);

	string data;
	data.append("appid=").append(Crypt::UrlEncodeForTX(OpenPlatform::GetPlatform()->GetAppId()));
	data.append("&openid=").append(Crypt::UrlEncodeForTX(openid));
	data.append("&openkey=").append(Crypt::UrlEncodeForTX(openkey));
	data.append("&pf=").append(Crypt::UrlEncodeForTX(pf));
	data.append("&user_attr=").append(Crypt::UrlEncodeForTX(attr));
	data.append("&sig=").append(Crypt::UrlEncodeForTX(sig));

	string response;
	if (!Network::HttpPostRequest(response, url, data) || response.empty())
	{
		error_log("[http request fail][openid=%s,url=%s,response=%s]",
				openid.c_str(), url.c_str(), response.c_str());
		return -1;
	}

	Json::Value value;
	if(!Json::Reader().parse(response, value))
	{
		error_log("[json parse fail][openid=%s,data=%s,response=%s]",
				openid.c_str(), data.c_str(), response.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0)
	{
		//error_log("[json ret fail][openid=%s,data=%s,response=%s]",	openid.c_str(), data.c_str(), response.c_str());
		return -1;
	}
	//info_log("[qq setachievement][data=%s, respons=%s]", data.c_str(), response.c_str());

	return 0;
}
