#include "LogicQQPay.h"

CLogicQQPay::CLogicQQPay() {
}

CLogicQQPay::~CLogicQQPay() {
}

int CLogicQQPay::GetItemInfo(uint32_t id, uint32_t osPlatform, QQItemInfo &item) {
	int ret = 0;
	static bool bInit = false;
	static map<uint32_t, QQItemInfo> andItemInfo;
	static map<uint32_t, QQItemInfo> iosItemInfo;
	static map<uint32_t, QQItemInfo> miniItemInfo;
	if (!bInit) {
		string itemFile = Config::GetValue(CONFIG_QQ_ITEM_INFO);
		if (itemFile.empty()) {
			fatal_log("[empty item info][path=%s]", itemFile.c_str());
			ERROR_RETURN_MSG(R_ERROR, "load_item_fail");
		}
		string buffer;
		ret = File::Read(itemFile, buffer);
		if (ret) {
			fatal_log("[Read error][path=%s]", itemFile.c_str());
			return ret;
		}
		Json::Value content;
		Json::Reader reader;
		if (!reader.parse(buffer, content)) {
			fatal_log("[Read error][path=%s mst=%s]", itemFile.c_str(), reader.getFormatedErrorMessages().c_str());
			return R_ERR_DATA;
		}

		Json::Value &android = content["and"];
		if (android.isNull() || !android.isArray()) {
			fatal_log("[android error][path=%s]", itemFile.c_str());
			return R_ERR_DATA;
		}
		for (size_t i = 0; i < android.size(); ++i) {
			QQItemInfo itemRead;
			itemRead.pt = OSPT_AND;
			itemRead.id = android[i].get("id", 0).asUInt();
			itemRead.cash = android[i].get("cash", 0).asUInt();
			itemRead.price = android[i].get("price", 0).asUInt();
			itemRead.itemid = android[i].get("itemid", 0).asString();
			andItemInfo.insert(make_pair(itemRead.id, itemRead));
		}

		Json::Value &ios = content["ios"];
		if (ios.isNull() || !ios.isArray()) {
			fatal_log("[ios error][path=%s]", itemFile.c_str());
			return R_ERR_DATA;
		}
		for (size_t i = 0; i < ios.size(); ++i) {
			QQItemInfo itemRead;
			itemRead.pt = OSPT_IOS;
			itemRead.id = ios[i].get("id", 0).asUInt();
			itemRead.cash = ios[i].get("cash", 0).asUInt();
			itemRead.price = ios[i].get("price", 0).asUInt();
			itemRead.itemid = ios[i].get("itemid", 0).asString();
			iosItemInfo.insert(make_pair(itemRead.id, itemRead));
		}

		Json::Value &mini = content["mini"];
		if (mini.isNull() || !mini.isArray()) {
			fatal_log("[mini error][path=%s]", itemFile.c_str());
			return R_ERR_DATA;
		}
		for (size_t i = 0; i < mini.size(); ++i) {
			QQItemInfo itemRead;
			itemRead.pt = OSPT_MINI;
			itemRead.id = mini[i].get("id", 0).asUInt();
			itemRead.cash = mini[i].get("cash", 0).asUInt();
			itemRead.price = mini[i].get("price", 0).asUInt();
			itemRead.itemid = mini[i].get("itemid", 0).asString();
			miniItemInfo.insert(make_pair(itemRead.id, itemRead));
		}

		bInit = true;
	}
	const map<uint32_t, QQItemInfo> *pItemInfo = NULL;
	if (osPlatform == OSPT_AND) {
		pItemInfo = &andItemInfo;
	} else if (osPlatform == OSPT_IOS) {
		pItemInfo = &iosItemInfo;
	} else if (osPlatform == OSPT_MINI) {
		pItemInfo = &miniItemInfo;
	}
	if (pItemInfo == NULL || pItemInfo->empty()) {
		error_log("[no item info][itemid=%u,pt=%u]", id, osPlatform);
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_item_info");
	}

	map<uint32_t, QQItemInfo>::const_iterator it = pItemInfo->find(id);
	if (it == pItemInfo->end()) {
		error_log("[no item info][itemid=%u,pt=%u]", id, osPlatform);
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_item_info");
	}

	item.id = (it->second).id;
	item.cash = (it->second).cash;
	item.price = (it->second).price;
	item.pt = (it->second).pt;
	item.itemid = (it->second).itemid;
	debug_log("id=%u,cash=%u,pt=%u,itemid=%s", item.id, item.cash, item.pt, item.itemid.c_str());
	return 0;
}

int CLogicQQPay::v3_get_playzone_userinfo(const string opid, const string &opkey, const string &pf, const string &zone, const string &ip, int32_t &score) {
	const string api_name = "/v3/user/get_playzone_userinfo";
	const string &appid = OpenPlatform::GetPlatform()->GetAppId();
	const string &appkey = OpenPlatform::GetPlatform()->GetAppKey();
	map<string, string> param_map;
	param_map["appid"] = appid;
	param_map["openid"] = opid;
	param_map["openkey"] = opkey;
	param_map["pf"] = pf;
	param_map["format"] = "json";
	param_map["userip"] = ip;
	param_map["zoneid"] = zone;
	string url;
	formatUrl(param_map, appkey, api_name, url);
	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty()) {
		error_log("[http request fail][url=%s,openid=%s,response=%s]", url.c_str(), opid.c_str(), response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}
	debug_log("openid=%s,url=%s", opid.c_str(), url.c_str());
	Json::Value result;
	Json::Reader reader;
	int responsetRet = 0;
	if (response.empty() || !reader.parse(response, result) || !Json::GetInt(result, "code", responsetRet)
	|| responsetRet != 0 || !result.isMember("data") || !result["data"].isArray() || result["data"].size() == 0) {
		error_log("[response error][openid=%s,response=%s,url=%s]", opid.c_str(), response.c_str(), url.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
	}
	Json::GetInt(result["data"][0u], "score", score);
	debug_log("openid=%s, response=%s", opid.c_str(), Json::ToString(result).c_str());
	return 0;
}

int CLogicQQPay::v3_buy_playzone_item(const string &opid, const string &opkey, const string &pf, const string &zone, const string &ip, uint32_t id, uint32_t count, string &strBillno, uint32_t &cash, uint32_t &cost) {
	int ret = 0;
	uint32_t ts = static_cast<uint32_t>(time(NULL));
	const string api_name = "/v3/user/buy_playzone_item";
	const string &appid = OpenPlatform::GetPlatform()->GetAppId();
	const string &appkey = OpenPlatform::GetPlatform()->GetAppKey();
	QQItemInfo itemInfo;
	ret = GetItemInfo(id, String::s2i(zone, 0), itemInfo);
	if (ret != 0) {
		return ret;
	}
	string billno = Crypt::Md5Encode(opid + CTrans::ITOS(ts) + itemInfo.itemid);
	map<string, string> param_map;
	param_map["appid"] = appid;
	param_map["openkey"] = opkey;
	param_map["openid"] = opid;
	param_map["pf"] = pf;
	param_map["format"] = "json";
	param_map["userip"] = ip;
	param_map["zoneid"] = zone;
	param_map["billno"] = billno;
	param_map["itemid"] = itemInfo.itemid;
	param_map["count"] = CTrans::ITOS(count);

	string url;
	formatUrl(param_map, appkey, api_name, url);
	debug_log("openid=%s,url=%s", opid.c_str(), url.c_str());
	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty()) {
		error_log("[http request fail][url=%s,openid=%s,response=%s]", url.c_str(), opid.c_str(), response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}
	Json::Value result;
	Json::Reader reader;
	int responsetRet = 0;
	if (response.empty() || !reader.parse(response, result) || !Json::GetInt(result, "code", responsetRet)
	|| responsetRet != 0 || !result.isMember("data") || !result["data"].isArray() || result["data"].size() == 0) {
		error_log("[response error][openid=%s,response=%s]", opid.c_str(), response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
	}

	Json::GetString(result["data"][0u], "billno", strBillno);
	Json::GetUInt(result["data"][0u], "cost", cost);

	cash = itemInfo.cash * count;
	debug_log("openid=%s, cash=%u, response=%s", opid.c_str(), itemInfo.cash, Json::ToString(result).c_str());
	return 0;
}

int CLogicQQPay::formatUrl(const map<string, string> &param, const string &appkey, const string &api, string &url) {
	string qsig;
	string qstr;
	map<string, string>::const_iterator itr = param.begin();
	for (; itr != param.end(); ++itr) {
		if (!qsig.empty()) {
			qsig.append("&").append(itr->first).append("=").append(itr->second);
			qstr.append("&").append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		} else {
			qsig.append(itr->first).append("=").append(itr->second);
			qstr.append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
	}
	url = "https://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + api + "?";
	string osig = "GET&" + Crypt::UrlEncodeForTX(api) + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);
	return 0;
}
