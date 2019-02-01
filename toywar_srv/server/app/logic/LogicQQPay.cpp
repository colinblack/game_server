#include "LogicQQPay.h"

CLogicQQPay::T_ItemMap CLogicQQPay::g_ItemInfo;

int CLogicQQPay::GetItemInfo(
		const string &itemid,
		QQItemInfo &item)
{
	static bool bInit = false;
	if (!bInit)
	{
		string itemFile;
		itemFile = Config::GetValue("qq_item_info");
		if (itemFile.empty())
			itemFile = "/data/release/toywar/conf/qq_item_info.xml";
		CMarkupSTL xmlConf;
		if(!xmlConf.Load(itemFile.c_str()))
		{
			fatal_log("[load item info fail][path=%s]", itemFile.c_str());
			ERROR_RETURN_MSG(R_ERROR, "load_item_fail");
		}
		if(!xmlConf.FindElem("items"))
		{
			fatal_log("[parse item info fail][path=%s]", itemFile.c_str());
			ERROR_RETURN_MSG(R_ERROR, "load_item_fail");
		}
		xmlConf.IntoElem();
		while(xmlConf.FindElem("item"))
		{
			QQItemInfo itemTmp;
			itemTmp.itemid = xmlConf.GetAttrib("id");
			itemTmp.name = xmlConf.GetAttrib("name");
			itemTmp.description = xmlConf.GetAttrib("description");
			itemTmp.url = xmlConf.GetAttrib("url");
			itemTmp.price = CTrans::STOI(xmlConf.GetAttrib("price"));
			itemTmp.type = CTrans::STOI(xmlConf.GetAttrib("type"));
			itemTmp.cash = CTrans::STOI(xmlConf.GetAttrib("cash"));
			g_ItemInfo[itemTmp.itemid] = itemTmp;
		}
		bInit = true;
	}

	if (g_ItemInfo.empty())
	{
		error_log("[no item info][itemid=%s]",itemid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_item_info");
	}

	T_ItemMap::const_iterator it;
	it = g_ItemInfo.find(itemid);
	if (it == g_ItemInfo.end())
	{
		error_log("[no item info][itemid=%s]",itemid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_item_info");
	}

	item.itemid = (it->second).itemid;
	item.name = (it->second).name;
	item.description = (it->second).description;
	item.url = (it->second).url;
	item.price = (it->second).price;
	item.type = (it->second).type;
	item.cash = (it->second).cash;

	return 0;
}

int CLogicQQPay::qz_buy_goods(
		const string &openid,
		const string &openkey,
		const string &userip,
		const string &itemid,
		string &appid,
		string &url_params)
{
	int ret = 0;
	unsigned uid = 0;
	ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid, true);
	if (ret != 0)
		return ret;
	QQItemInfo itemInfo;
	ret = GetItemInfo(itemid, itemInfo);
	if (ret != 0)
		return ret;

	string payUrl = OpenPlatform::GetPlatform()->GetConfig("buy_goods_url");
	if (payUrl.empty())
	{
		error_log("[url is empty][openid=%s]",openid.c_str());
		ERROR_RETURN_MSG(R_ERROR, "url_config_error");
	}
	appid =  OpenPlatform::GetPlatform()->GetAppId();
	string appkey = OpenPlatform::GetPlatform()->GetAppKey();
	string appname = OpenPlatform::GetPlatform()->GetConfig("appname");

	string ts = CTrans::UTOS(Time::GetGlobalTime());
	string payitem = itemid + "*" + CTrans::ITOS(itemInfo.price) + "*1";
	string metatmp = itemInfo.name + "*" + itemInfo.description;
	string goodsmeta;
	Crypt::Base64Encode(goodsmeta, metatmp);
	string goodsurl = Crypt::UrlEncode(itemInfo.url);

	string osig;
	osig.append("appid").append(appid);
	osig.append("appkey").append(appkey);
	osig.append("appmode2");
	osig.append("appname").append(appname);
	osig.append("openid").append(openid);
	osig.append("openkey").append(openkey);
	osig.append("payitem").append(payitem);
	osig.append("ts").append(ts);
	osig.append(appkey);
	string sig = Crypt::Md5Encode(osig);

	string qstr;
	qstr.append("openid=").append(openid);
	qstr.append("&openkey=").append(openkey);
	qstr.append("&appid=").append(appid);
	qstr.append("&appkey=").append(appkey);
	qstr.append("&appname=").append(appname);
	qstr.append("&ts=").append(ts);
	qstr.append("&device=0");
	qstr.append("&payitem=").append(payitem);
	qstr.append("&appmode=2");
	qstr.append("&goodsmeta=").append(goodsmeta);
	qstr.append("&goodsurl=").append(goodsurl);
	qstr.append("&userip=").append(userip);
	qstr.append("&sig=").append(sig);

	//info_log("[qqpay test][qstr=%s]",qstr.c_str());

	string response;
	if (!Network::HttpPostRequest(response, payUrl, qstr))
	{
		error_log("[http request fail][openid=%s]",openid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}

	Json::Value result;
	Json::Reader reader;
	if (response.empty() || !reader.parse(response, result)
			|| !result.isMember("url_params") || !result["url_params"].isString())
	{
		error_log("[response error][openid=%s,response=%s]",openid.c_str(),response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
	}

	url_params = result["url_params"].asString();

	return 0;
}

int CLogicQQPay::deliver(
		const string &appid,
		const string &openid,
		const string &payitem,
		int amt,
		const string &billno)
{
	int ret = 0;
	string o_appid = OpenPlatform::GetPlatform()->GetAppId();
	if (appid != o_appid)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（appid）");
	}
	vector<string> items;
	CBasic::StringSplit(payitem, "*", items);
	if (items.size() != 3)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（payitem）");
	}
	unsigned uid = 0;
	ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid, true);
	if (ret == R_ERR_NO_DATA)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
	}
	else if (ret != 0)
	{
		ERROR_RETURN_MSG(1, "系统繁忙 ");
	}
	QQItemInfo itemInfo;
	ret = GetItemInfo(items[0], itemInfo);
	if (ret != 0)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（payitem） ");
	}
	int count = CTrans::STOI(items[2]);

	CLogicPay logicPay;
	if (itemInfo.cash != 0)
	{
		ret = logicPay.BuyCash(uid, itemInfo.cash * count, amt);
		if (ret != 0)
		{
			ERROR_RETURN_MSG(1, "系统繁忙 ");
		}
	}
	else
	{
		CLogicInventory logicInv;
		ret = logicInv.ChangeItem(uid, itemInfo.itemid, count);
		if (ret != 0)
		{
			ERROR_RETURN_MSG(1, "系统繁忙 ");
		}
	}

	DataPayHistory payhis;
	payhis.channel = PCT_QQ;
	payhis.channel_pay_id = billno;
	payhis.count = count;
	payhis.credit = amt;
	payhis.status = PST_OK;
	payhis.type = itemInfo.type;
	payhis.uid = uid;
	ret = logicPay.AddPayHistory(payhis);
	if (ret != 0)
	{
		error_log("[AddPayHistory fail][ret=%d,openid=%s,billno=%s,payitem=%s,amt=%d]",
				ret,openid.c_str(),billno.c_str(),payitem.c_str(),amt);
	}

	return 0;
}

int CLogicQQPay::v3_buy_goods(
		const string &pf,
		const string &pfkey,
		const string &openid,
		const string &openkey,
		const string &userip,
		const string &itemid,
		string &appid,
		string &url_params)
{
	int ret = 0;
	unsigned uid = 0;
	ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid, true);
	if (ret != 0)
		return ret;
	QQItemInfo itemInfo;
	ret = GetItemInfo(itemid, itemInfo);
	if (ret != 0)
		return ret;
	appid = OpenPlatform::GetPlatform()->GetAppId();
	string appkey = OpenPlatform::GetPlatform()->GetAppKey();

	string url = "https://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + "/v3/pay/buy_goods?";
	string qsig = "appid=" + appid + "&appmode=2&format=json&goodsmeta=";
	string qstr = "appid=" + Crypt::UrlEncodeForTX(appid) + "&appmode=2&format=json&goodsmeta=";
	string tmp = itemInfo.name + "*" + itemInfo.description;
	string goodsmeta;
	Crypt::Base64Encode(goodsmeta, tmp);
	qsig += goodsmeta;
	qstr += Crypt::UrlEncodeForTX(goodsmeta);
	qsig += "&goodsurl=" + itemInfo.url;
	qstr += "&goodsurl=" + Crypt::UrlEncodeForTX(itemInfo.url);
	qsig += "&openid=" + openid + "&openkey=" + openkey;
	qstr += "&openid=" + Crypt::UrlEncodeForTX(openid) + "&openkey=" + Crypt::UrlEncodeForTX(openkey);
	string payitem = itemid + "*" + CTrans::ITOS(itemInfo.price) + "*1";
	qsig += "&payitem=" + payitem + "&pf=" + pf + "&pfkey=" + pfkey + "&ts=";
	qstr += "&payitem=" + Crypt::UrlEncodeForTX(payitem) + "&pf=" + Crypt::UrlEncodeForTX(pf) + "&pfkey=" + Crypt::UrlEncodeForTX(pfkey) + "&ts=";
	string ts = CTrans::UTOS((unsigned)time(NULL));
	qsig += ts + "&userip=" + userip;
	qstr += ts + "&userip=" + Crypt::UrlEncodeForTX(userip);

	string osig = "GET&" + Crypt::UrlEncodeForTX("/v3/pay/buy_goods") + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);

	//info_log("[qqtopup][url=%s]",url.c_str());
	//info_log("[qqtopup][osig=%s,key=%s]",osig.c_str(),key.c_str());
	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s]",openid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}
	Json::Value result;
	Json::Reader reader;
	if (response.empty() || !reader.parse(response, result)
			|| !result.isMember("url_params") || !result["url_params"].isString())
	{
		error_log("[response error][openid=%s,response=%s]",openid.c_str(),response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
	}

	url_params = result["url_params"].asString();

	return 0;
}
