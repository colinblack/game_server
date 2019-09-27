#include "TencentPlatform.h"
#include <iostream>

CTencentPlatform::CTencentPlatform() {
	m_type = PT_UNKNOW;
}

int CTencentPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params) {
	IOpenPlatform::Initialize(appid, appkey, params);
	m_type = PT_QZONE;
	return 0;
}

void CTencentPlatform::SetParameter(const map<string, string> &params) {
}

int CTencentPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey, const string& pf, const string& userip) {
	const string api = "/v3/user/get_info";
	map<string, string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;
	params["userip"] = userip;
	string url = "https://" + m_config["v3domain"] + api + "?" + FormatGetUrl(params, m_appKey, api);
	string resp;
	if (!Network::HttpGetRequest(resp, url) || resp.empty()) {
		error_log("[http request fail][openid=%s,openkey=%s,resp=%s,url=%s]", openid.c_str(), openkey.c_str(), resp.c_str(), url.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(resp, value)) {
		error_log("[json parse fail][openid=%s,openkey=%s,resp=%s,url=%s]", openid.c_str(), openkey.c_str(), resp.c_str(), url.c_str());
		return -1;
	}
	int ret = 0;
	if (!Json::GetInt(value, "ret", ret) || ret != 0) {
		error_log("[get_info fail][openid=%s,openkey=%s,resp=%s,url=%s]", openid.c_str(), openkey.c_str(), resp.c_str(), url.c_str());
		return -1;
	}
	userInfo.Clear();
	userInfo.OpenId = openid;
	Json::GetString(value, "nickname", userInfo.Name);
	Json::GetString(value, "figureurl", userInfo.FigureUrl);
	size_t httppos = userInfo.FigureUrl.find("http://");
	if (httppos != 0) {
		userInfo.FigureUrl = "https://" + userInfo.FigureUrl;
	} else {
		userInfo.FigureUrl = "https://" + userInfo.FigureUrl.substr(httppos + strlen("http://"));
	}
	string temp;
	Json::GetString(value, "gender", temp);
	if (temp == "男") {
		userInfo.Gender = GD_MALE;
	} else if (temp == "女") {
		userInfo.Gender = GD_FEMALE;
	} else {
		userInfo.Gender = GD_UNKNOW;
	}
	Json::GetString(value, "country", userInfo.Nation);
	Json::GetString(value, "province", userInfo.Province);
	Json::GetString(value, "city", userInfo.City);
	int is_yellow_vip = 0;
	int is_yellow_year_vip = 0;
	int yellow_vip_level = 0;
	Json::GetInt(value, "is_yellow_vip", is_yellow_vip);
	Json::GetInt(value, "is_yellow_year_vip", is_yellow_year_vip);
	Json::GetInt(value, "yellow_vip_level", yellow_vip_level);
	userInfo.ExtraIntInfo["bIsVip"] = is_yellow_vip == 1 ? 1 : 0;
	userInfo.ExtraIntInfo["bIsYearVip"] = is_yellow_year_vip == 1 ? 1 : 0;
	userInfo.ExtraIntInfo["nVipLevel"] = yellow_vip_level;
	return 0;
}

int CTencentPlatform::GetVipInfo(const string &openid, const string &openkey, const string &pf, const string &userip, uint32_t &vip) {
	const string api = "/v3/user/get_vip_level";
	map<string, string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;
	params["userip"] = userip;
	string url = "https://" + m_config["v3domain"] + api + "?" + FormatGetUrl(params, m_appKey, api);
	string resp;
	if (!Network::HttpGetRequest(resp, url) || resp.empty()) {
		error_log("[http request fail][openid=%s,openkey=%s,resp=%s,url=%s]", openid.c_str(), openkey.c_str(), resp.c_str(), url.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(resp, value)) {
		error_log("[json parse fail][openid=%s,openkey=%s,resp=%s,url=%s]", openid.c_str(), openkey.c_str(), resp.c_str(), url.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0) {
		error_log("[get ret fail][openid=%s,openkey=%s,resp=%s,url=%s]", openid.c_str(), openkey.c_str(), resp.c_str(), url.c_str());
		return -1;
	}
	if (!Json::GetUInt(value, "level", vip)) {
		vip = 0;
	}
	info_log("openid=%s,resp=%s", openid.c_str(), Json::ToString(value).c_str());
	return 0;
}

int CTencentPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey, const string& pf, const string& userip) {
	const string api = "/v3/relation/get_app_friends";
	map<string, string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;
	params["userip"] = userip;
	string url = "https://" + m_config["v3domain"] + api + "?" + FormatGetUrl(params, m_appKey, api);
	string resp;
	if (!Network::HttpGetRequest(resp, url) || resp.empty()) {
		error_log("[http request fail][openid=%s,openkey=%s,resp=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(resp, value)) {
		error_log("[json parse fail][openid=%s,openkey=%s,resp=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0) {
		error_log("[get ret fail][openid=%s,openkey=%s,resp=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	if (Json::IsArray(value, "items")) {
		for (unsigned i = 0; i < value["items"].size(); i++) {
			string temp;
			if (Json::GetString(value["items"][i], "openid", temp)) {
				friendList.push_back(temp);
			}
		}
	}
	info_log("openid=%s,resp=%s", openid.c_str(), Json::ToString(value).c_str());
	return 0;
}

int CTencentPlatform::GiftExchange(const string &openid, const string &openkey, const string &pf, const string &userip, const string &giftid, int &code) {
	const string api = "/v3/user/gift_exchange";
	map<string, string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;
	params["userip"] = userip;
	params["gift_id"] = giftid;
	string url = "https://" + m_config["v3domain"] + api + "?" + FormatGetUrl(params, m_appKey, api);
	string resp;
	if (!Network::HttpGetRequest(resp, url) || resp.empty()) {
		error_log("[http request fail][openid=%s,openkey=%s,giftid=%s,url=%s,resp=%s]", openid.c_str(), openkey.c_str(), giftid.c_str(), url.c_str(), resp.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(resp, value)) {
		error_log("[json parse fail][openid=%s,openkey=%s,resp=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	if (!Json::GetInt(value, "ret", code)) {
		error_log("[get_info fail][openid=%s,openkey=%s,resp=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	info_log("openid=%s,resp=%s", openid.c_str(), resp.c_str());
	return 0;
}

string CTencentPlatform::GetErrorMessage() {
	return "no error message";
}

string CTencentPlatform::FormatGetUrl(const map<string, string> &params, const string &appkey, const string &uri) {
	string sig;
	string qsig;
	string qstr;
	map<string, string>::const_iterator it = params.begin();
	for (; it != params.end(); it++) {
		if (!qsig.empty()) {
			qsig += "&";
		}
		if (!qstr.empty()) {
			qstr += "&";
		}
		qsig += it->first + "=" + it->second;
		qstr += it->first + "=" + Crypt::UrlEncodeForTX(it->second);
	}
	string osig = "GET&" + Crypt::UrlEncodeForTX(uri) + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	Crypt::Base64Encode(sig, bsig);
	qstr += "&sig=" + Crypt::UrlEncodeForTX(sig);
	return qstr;
}

int CTencentPlatform::IsLogin(const string &openid, const string &openkey, const string &pf, const string &user_ip) {
	const string api = "/v3/user/is_login";
	map<string, string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;
	params["userip"] = user_ip;
	string url = "https://" + m_config["v3domain"] + api + "?" + FormatGetUrl(params, m_appKey, api);
	string resp;
	if (!Network::HttpGetRequest(resp, url) || resp.empty()) {
		error_log("[http request fail][openid=%s,openkey=%s,errmsg=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(resp, value)) {
		error_log("[json parse fail][openid=%s,openkey=%s,response=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0) {
		error_log("[get_info fail][openid=%s,openkey=%s,response=%s]", openid.c_str(), openkey.c_str(), resp.c_str());
		return -1;
	}
	return 0;
}

int CTencentPlatform::SendGameBarMsg(const string &openid, const string &openkey, const string &pf, const string &userip, const string &frd, int type, const string &msg, const string &qua) {
	const string api = "/v3/user/send_gamebar_msg";
	map<string, string> params;
	params["appid"] = m_appId;
	params["format"] = "json";
	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;
	params["userip"] = userip;
	params["frd"] = frd;
	params["msgtype"] = CTrans::ITOS(type);
	params["content"] = msg;
	params["qua"] = qua;
	string url = "https://" + m_config["v3domain"] + api + "?" + FormatGetUrl(params, m_appKey, api);
	string resp;
	if (!Network::HttpGetRequest(resp, url) || resp.empty()) {
		error_log("[http request fail][openid=%s,openkey=%s,url=%s,resp=%s]", openid.c_str(), openkey.c_str(), url.c_str(), resp.c_str());
		return -1;
	}
	Json::Value value;
	if (!Json::Reader().parse(resp, value)) {
		error_log("[json parse fail][openid=%s,openkey=%s,url=%s,resp=%s]", openid.c_str(), openkey.c_str(), url.c_str(), resp.c_str());
		return -1;
	}
	int ret;
	if (!Json::GetInt(value, "ret", ret) || ret != 0) {
		error_log("[get_info fail][openid=%s,openkey=%s,url=%s,resp=%s]", openid.c_str(), openkey.c_str(), url.c_str(), resp.c_str());
		return -1;
	}
	info_log("openid=%s,resp=%s", openid.c_str(), resp.c_str());
	return 0;
}
