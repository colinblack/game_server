#include "LogicVNPay.h"

CLogicVNPay::T_ItemMap CLogicVNPay::g_ItemInfo;

int CLogicVNPay::GetItemInfo(
		const string &itemid,
		VNItemInfo &item)
{
	static bool bInit = false;
	if (!bInit)
	{
		string itemFile;
		itemFile = MainConfig::GetAllServerPath(CONFIG_QQ_ITEM_INFO);
		if (itemFile.empty())
		{
			fatal_log("[empty item info][path=%s]", itemFile.c_str());
			ERROR_RETURN_MSG(R_ERROR, "load_item_fail");
		}
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
			VNItemInfo itemTmp;
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

int CLogicVNPay::deliver(
		const string &openid,
		unsigned serverid,
		unsigned count,
		const string &billno)
{
	int ret = 0;

	CLogicPay logicPay;

	unsigned uid = 0;
	CDataUserMapping dbUserMapping;
	ret = dbUserMapping.GetUID(openid, serverid, uid);
	if( ret!=0 || uid == 0)
		return R_ERR_DB;

	/****change to ourself's platform************/
	//防重发, 如果该payment_id已经处理, 那么不再增加钻石
	DataPayHistory payHistory;
	CDataPayHistory dbPayHistory;
	ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), billno, payHistory);
	if(ret != R_ERR_NO_DATA)
	{
		error_log("vndeliever failed: payment_id %s had been paid", billno.c_str());
		ERROR_RETURN_MSG(1, "账单已支付，宝石已发 ");
	}

	unsigned quantity_sales = count; //加上送的宝石数
	if (count == 5000)      quantity_sales += 500;
	else if (count == 10000) quantity_sales += 1500;
	else if (count == 20000) quantity_sales += 4000;
	/*********************************************/

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

	if (count != 0)
	{
		ret = logicPay.ChangePay(uid, quantity_sales, 0, pay, "VNTOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (ret != 0) {
			error_log("qqdeliever failed");
			ERROR_RETURN_MSG(1, "系统繁忙 ");
		}
	}
	logicPay.DoPay(uid,user,count);
	if(bsave)
		logicUser.SetUserFlag(uid,user_flag);

	DataPayHistory payhis;
	payhis.channel = OpenPlatform::GetType();
	payhis.channel_pay_id = billno;
	payhis.count = count;
	payhis.credit = count*2;//count*10000;
	payhis.status = PST_OK;
	payhis.type = 0;
	payhis.uid = uid;
	payhis.open_id = openid;
	ret = logicPay.AddPayHistory(payhis);
	if (ret != 0)
	{
		error_log("[AddPayHistory fail][ret=%d,openid=%s,billno=%s]",
				ret,openid.c_str(),billno.c_str());
	}

	return 0;
}

int CLogicVNPay::v3_buy_goods(
		unsigned int uid,
		const string &openid,
		const string &openkey,
		const string &userip,
		const string &itemid,
		string &url_params)
{
	int ret = 0;
	CLogicUserBasic logicUserBasic;
	//unsigned uid = 0;
	//ret = logicUserBasic.GetUid(uid, OpenPlatform::GetType(), openid, true);
	if (ret != 0)
		return ret;
	VNItemInfo itemInfo;
	ret = GetItemInfo(itemid, itemInfo);
	if (ret != 0)
		return ret;

	string appkey = OpenPlatform::GetPlatform()->GetAppKey();

	string url = "https://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + "/pay/buy_goods?";

	string qsig = "itemid=" + itemid;
	string qstr = "itemid=" + Crypt::UrlEncodeForTX(itemid);
	qsig += "&openid=" + openid + "&openkey=" + openkey;
	qstr += "&openid=" + Crypt::UrlEncodeForTX(openid) + "&openkey=" + Crypt::UrlEncodeForTX(openkey);
	string price = CTrans::UTOS((unsigned)(itemInfo.price));
	qsig += "&price=" + price;
	qstr += "&price=" + Crypt::UrlEncodeForTX(price);
	qsig += "&ts=";
	qstr += "&ts=";
	string ts = CTrans::UTOS((unsigned)time(NULL));
	string uids = CTrans::UTOS(uid);
	qsig += ts + "&uid=" + uids + "&userip=" + userip;
	qstr += ts + "&uid=" + Crypt::UrlEncodeForTX(uids) + "&userip=" + Crypt::UrlEncodeForTX(userip);

	string osig = "GET&" + Crypt::UrlEncodeForTX("/pay/buy_goods") + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);

	//info_log("[qqtopup][url=%s]",url.c_str());
	//info_log("[qqtopup][osig=%s,key=%s]",osig.c_str(),key.c_str());
	string response;

	error_log("[buy_goods]%s",url.c_str());
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s]",openid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}
	error_log("[buy_goods_response]%s",response.c_str());

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


