#include "LogicQQPay.h"

#define BLUE1_VIP_MAX 12
#define BLUE2_VIP_MAX 60

CLogicQQPay::T_ItemMap CLogicQQPay::g_ItemInfo;

int CLogicQQPay::GetItemInfo(
		const string &itemid,
		QQItemInfo &item)
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
	CLogicUserBasic logicUserBasic;
	unsigned uid = 0;
	ret = logicUserBasic.GetUid(uid, OpenPlatform::GetType(), openid, true);
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
	vector<string> uidanitem;
	CBasic::StringSplit(items[0], "_", uidanitem);
	if (uidanitem.size() == 2)
	{
		Convert::StringToUInt(uid, uidanitem[0]);
		items[0] = uidanitem[1];
	}

	DataPayHistory payHis;
	CDataPayHistory dbPayHis;
	ret = dbPayHis.GetPayHistory(uid, OpenPlatform::GetType(), billno, payHis);
	if (0 == ret)
	{
		CgiUtil::PrintText("{\"ret\":0,\"msg\":\"OK\"}");
		return R_SUCCESS;
	}

	/*CLogicUserBasic logicUserBasic;
	ret = logicUserBasic.GetUid(uid, OpenPlatform::GetType(), openid, true);
	if (ret == R_ERR_NO_DATA)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
	}
	else if (ret != 0)
	{
		ERROR_RETURN_MSG(1, "系统繁忙 ");
	}*/
	QQItemInfo itemInfo;
	ret = GetItemInfo(items[0], itemInfo);
	if (ret != 0)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（payitem） ");
	}
	int count = CTrans::STOI(items[2]);

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
	if (itemInfo.cash != 0 /*&& Config::GetIntValue("new_flag") != 1*/)
	{
		Json::Value updates;
		updates.resize(1);
		updates[(unsigned) 0]["s"] = "QQTOPUP";
		updates[(unsigned) 0]["itemid"] = itemInfo.itemid;
		updates[(unsigned) 0]["count"] = count;
		updates[(unsigned) 0]["ts"] = (unsigned) time(0);
		CLogicUpdates logicUpdates;
		ret = logicUpdates.AddUpdates(uid, updates);
		ret = logicPay.ChangePay(uid, itemInfo.cash * count, 0, pay, "QQTOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (0 != ret) {
			error_log("qqdeliever failed");
			ERROR_RETURN_MSG(1, "系统繁忙 ");
		}
	}

	logicPay.DoPay(uid,user,itemInfo.cash * count);
	if(bsave)
		logicUser.SetUserFlag(uid,user_flag);

	DataPayHistory payhis;
	payhis.channel = user.last_login_platform;
	payhis.channel_pay_id = billno;
	payhis.count = itemInfo.cash * count;
	payhis.credit = amt;
	payhis.status = PST_OK;
	payhis.type = itemInfo.type;
	payhis.uid = uid;
	payhis.open_id = openid;
	ret = logicPay.AddPayHistory(payhis);
	if (ret != 0)
	{
		error_log("[AddPayHistory fail][ret=%d,openid=%s,billno=%s,payitem=%s,amt=%d]",
				ret,openid.c_str(),billno.c_str(),payitem.c_str(),amt);
	}

/*
	if(Config::GetIntValue("new_flag") == 1)
	{
		CLogicBuyGoods buyGoods;
		DataGoods data;
		Json::Value sdata;
		Json::FastWriter writer;
		//buyGoods.GetGoods(uid,sdata);
		data.uid = uid;
		data.count = count;
		data.buy_time = Time::GetGlobalTime();
		sdata["id"] = itemInfo.itemid;
		data.data = writer.write(sdata);
		ret = buyGoods.BuyGoods(data);
		if(ret != 0)
		{
			error_log("buy goods failed,uid = %d,count = %d,buytime=%u,id =%s,",uid, count,data.buy_time,itemInfo.itemid.c_str());
			ERROR_RETURN_MSG(1, "系统繁忙 ");
		}
		info_log("buy equipments success uid=%u,id=%s,count=%d,",uid,itemInfo.itemid.c_str(),count);
	}
	// add by aaron
*/
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
	CLogicUserBasic logicUserBasic;
	unsigned uid = 0;
	ret = logicUserBasic.GetUid(uid, OpenPlatform::GetType(), openid, true);
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
	string payitem;
	String::Format(payitem, "%u", uid);
	payitem += "_" + itemid + "*" + CTrans::ITOS(itemInfo.price) + "*1";

	qsig += "&payitem=" + payitem + "&pf=" + pf + "&pfkey=" + pfkey;
	qstr += "&payitem=" + Crypt::UrlEncodeForTX(payitem) + "&pf=" + Crypt::UrlEncodeForTX(pf) + "&pfkey=" + Crypt::UrlEncodeForTX(pfkey);
	if(pf == "3366"){
		qsig += "&platform=30006";
		qstr += "&platform=30006";
	}
	qsig += "&ts=";
	qstr += "&ts=";
	string ts = CTrans::UTOS((unsigned)time(NULL));
	qsig += ts + "&userip=" + userip;
	qstr += ts + "&userip=" + Crypt::UrlEncodeForTX(userip);

	string zoneid;
	if(!Config::GetValue(zoneid, CONFIG_ZONE_ID))
		zoneid = "0";
	qsig += "&zoneid=" + zoneid;
	qstr += "&zoneid=" + Crypt::UrlEncodeForTX(zoneid);

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

int CLogicQQPay::PayRewarld(unsigned uid, int cash, int &coins)
{
	coins = 0;
	string newServerTs;
	if(!Config::GetValue(newServerTs, CONFIG_NEW_SERVER_TS))
	{
		error_log("[get config faile][file=%s]", CONFIG_NEW_SERVER_TS);
		return R_ERROR;
	}
	vector<string> tsItem;
	CBasic::StringSplitTrim(newServerTs, ",", tsItem);
	int item = (uid - 10000000) / 500000;
	if (item >= tsItem.size())
	{
		error_log("[server id is over tsItem][item=%d,tsItemsize=%d]",item,tsItem.size());
		return R_ERROR;
	}
	int iNewServerTs = Convert::StringToInt(tsItem[item]);
	if (iNewServerTs+3*24*60*60 > Time::GetGlobalTime())
	{
		coins = cash - cash % 10;
	}
	return 0;
}

int CLogicQQPay::InformTaskCompleted(
		const string &pf,
		const string &pfkey,
		const string &openid,
		const string &openkey,
		string &zoneid,
		string &appid,
		string &contractid)
{
	int ret = 0;
	appid = OpenPlatform::GetPlatform()->GetAppId();
	string appkey = OpenPlatform::GetPlatform()->GetAppKey();

	string url = "https://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + "/v3/pay/inform_task_completed?";
	//test config
	//string url = "https://119.147.19.43 openapi.tencentyun.com/v3/pay/inform_task_completed?";
	string qsig = "appid=" + appid;
	string qstr = "appid=" + Crypt::UrlEncodeForTX(appid);

	qsig += "&contractid=" + contractid;
	qstr += "&contractid=" + Crypt::UrlEncodeForTX(contractid);

	qsig += "&openid=" + openid + "&openkey=" + openkey;
	qstr += "&openid=" + Crypt::UrlEncodeForTX(openid) + "&openkey=" + Crypt::UrlEncodeForTX(openkey);

	qsig += "&pf=" + pf;
	qstr += "&pf=" + Crypt::UrlEncodeForTX(pf);

	qsig += "&pfkey=" + pfkey;
	qstr += "&pfkey=" + Crypt::UrlEncodeForTX(pfkey);

	string ts;
	String::Format(ts, "%u", Time::GetGlobalTime());
	qsig += "&ts=" + ts;
	qstr += "&ts=" + Crypt::UrlEncodeForTX(ts);

	qsig += "&zoneid=" + zoneid;
	qstr += "&zoneid=" + Crypt::UrlEncodeForTX(zoneid);

	string osig = "GET&" + Crypt::UrlEncodeForTX("/v3/pay/inform_task_completed") + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s]",openid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}
	Json::Value result;
	Json::Reader reader;
	int responsetRet = 0;
	if (   response.empty()
		|| !reader.parse(response, result)
		|| !Json::GetInt(result,"ret", responsetRet)
		|| responsetRet != 0)
	{
		error_log("[response error][openid=%s,response=%s]",openid.c_str(),response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
	}
	return 0;
}

int CLogicQQPay::ReqQQPanel(const string &pf,
			const string &pfkey,
			const string &openid,
			const string &openkey,
			string &userip,
			string &appid)
{
	int ret = 0;
	appid = OpenPlatform::GetPlatform()->GetAppId();
	string appkey = OpenPlatform::GetPlatform()->GetAppKey();

	string url = "https://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + "/v3/spread/is_app_onpanel?";
	string qsig = "appid=" + appid;
	string qstr = "appid=" + Crypt::UrlEncodeForTX(appid);

	qsig += "&openid=" + openid + "&openkey=" + openkey;
	qstr += "&openid=" + Crypt::UrlEncodeForTX(openid) + "&openkey=" + Crypt::UrlEncodeForTX(openkey);

	qsig += "&pf=" + pf;
	qstr += "&pf=" + Crypt::UrlEncodeForTX(pf);

	qsig += "&pfkey=" + pfkey;
	qstr += "&pfkey=" + Crypt::UrlEncodeForTX(pfkey);

	qsig += "&userip=" + userip;
	qstr += "&userip=" + Crypt::UrlEncodeForTX(userip);

	string osig = "GET&" + Crypt::UrlEncodeForTX("/v3/spread/is_app_onpanel") + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	string sig;
	Crypt::Base64Encode(sig, bsig);
	url += qstr + "&sig=" + Crypt::UrlEncodeForTX(sig);

	string response;
	if (!Network::HttpGetRequest(response, url) || response.empty())
	{
		error_log("[http request fail][openid=%s]",openid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}
	Json::Value result;
	Json::Reader reader;
	int responsetRet = 0;
	int in_applist = 0;
	if (   response.empty()
		|| !reader.parse(response, result)
		|| !Json::GetInt(result,"ret", responsetRet)
		|| responsetRet != 0
		|| !Json::GetInt(result,"in_applist", in_applist))
	{
		error_log("[response error][openid=%s,response=%s]",openid.c_str(),response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
	}
	if(in_applist == 1)
		return 0;
	else
		return R_ERR_LOGIC;
}

int CLogicQQPay::CheckTask(const string &appid, const string &openid, const string &contractid, const string &cmd, int step, unsigned eqid, const string &billno, unsigned &zoneid)
{
	int ret = 0;
	if (contractid.empty())
	{
		ERROR_RETURN_MSG(103, "请求参数错误：（contractid）");
	}
	string o_appid = OpenPlatform::GetPlatform()->GetAppId();
	if (appid != o_appid)
	{
		ERROR_RETURN_MSG(103, "请求参数错误：（appid）");
	}

	CDataMarketTask dbMarketTask;
	DataMarketTask task;
	task.openid = openid;
	task.contractid = contractid;

	ret = dbMarketTask.GetTask(task);
	if(0 != ret || !IsValidUid(task.uid))
	{
		ERROR_RETURN_MSG(1, "用户尚未在应用内创建角色");
	}

	zoneid = Config::GetZoneByUID(task.uid);

	int level = 0, ms2 = 0, ms3 = 0;
	level = CTrans::STOI(task.taskid);
	ms2 = level / 100;
	ms3 = level % 100;

	switch(step)
	{
	case 1:
	{
		if(cmd == "award")
		{
			if(task.flag & MARKET_QUEST_STEP_1)
			{
				ERROR_RETURN_MSG(3, "该步骤奖励已发放过");
			}

			task.flag &= MARKET_QUEST_STEP_1;
			ret = dbMarketTask.SetTask(task);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(102, "奖励发放失败");
			}

			if(eqid)
			{
				CLogicEquipment logicEquipment;
				Json::Value temp;
				ret = logicEquipment.AddOneItem(task.uid, eqid, 1,  billno, temp);
				if(0 != ret)
				{
					ERROR_RETURN_MSG(102, "奖励发放失败");
				}
			}
		}
		else
		{
			ERROR_RETURN_MSG(103, "请求参数错误：（cmd）");
		}
	}
		break;
	case 2:
	{
		if(cmd == "check")
		{
			if(task.flag & MARKET_QUEST_STEP_2)
			{
				ERROR_RETURN_MSG(3, "该步骤奖励已发放过");
			}

			CLogicUser logicUser;
			DataUser user;
			ret = logicUser.GetUserLimit(task.uid, user);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}

			if(user.level < ms2)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}
		}
		else if(cmd == "check_award")
		{
			if(task.flag & MARKET_QUEST_STEP_2)
			{
				ERROR_RETURN_MSG(3, "该步骤奖励已发放过");
			}

			CLogicUser logicUser;
			DataUser user;
			ret = logicUser.GetUserLimit(task.uid, user);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}

			if(user.level < ms2)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}

			task.flag &= MARKET_QUEST_STEP_2;
			ret = dbMarketTask.SetTask(task);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(102, "奖励发放失败");
			}

			if(eqid)
			{
				CLogicEquipment logicEquipment;
				Json::Value temp;
				ret = logicEquipment.AddOneItem(task.uid, eqid, 1,  billno, temp);
				if(0 != ret)
				{
					ERROR_RETURN_MSG(102, "奖励发放失败");
				}
			}
		}
		else
		{
			ERROR_RETURN_MSG(103, "请求参数错误：（cmd）");
		}
	}
		break;
	case 3:
	{
		if(cmd == "check")
		{
			if(task.flag & MARKET_QUEST_STEP_3)
			{
				ERROR_RETURN_MSG(3, "该步骤奖励已发放过");
			}

			CLogicUser logicUser;
			DataUser user;
			ret = logicUser.GetUserLimit(task.uid, user);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}

			if(user.level < ms3)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}
		}
		else if(cmd == "check_award")
		{
			if(task.flag & MARKET_QUEST_STEP_3)
			{
				ERROR_RETURN_MSG(3, "该步骤奖励已发放过");
			}

			CLogicUser logicUser;
			DataUser user;
			ret = logicUser.GetUserLimit(task.uid, user);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}

			if(user.level < ms3)
			{
				ERROR_RETURN_MSG(2, "用户尚未完成本步骤");
			}

			task.flag &= MARKET_QUEST_STEP_3;
			ret = dbMarketTask.SetTask(task);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(102, "奖励发放失败");
			}

			if(eqid)
			{
				CLogicEquipment logicEquipment;
				Json::Value temp;
				ret = logicEquipment.AddOneItem(task.uid, eqid, 1,  billno, temp);
				if(0 != ret)
				{
					ERROR_RETURN_MSG(102, "奖励发放失败");
				}
			}
		}
		else
		{
			ERROR_RETURN_MSG(103, "请求参数错误：（cmd）");
		}
	}
		break;
	case 4:
	{
		if(cmd == "award")
		{
			if(task.flag & MARKET_QUEST_STEP_4)
			{
				ERROR_RETURN_MSG(3, "该步骤奖励已发放过");
			}

			task.flag &= MARKET_QUEST_STEP_4;
			ret = dbMarketTask.SetTask(task);
			if(0 != ret)
			{
				ERROR_RETURN_MSG(102, "奖励发放失败");
			}

			if(eqid)
			{
				CLogicEquipment logicEquipment;
				Json::Value temp;
				ret = logicEquipment.AddOneItem(task.uid, eqid, 1,  billno, temp);
				if(0 != ret)
				{
					ERROR_RETURN_MSG(102, "奖励发放失败");
				}
			}
		}
		else
		{
			ERROR_RETURN_MSG(103, "请求参数错误：（cmd）");
		}
	}
		break;
	default:
	{
		ERROR_RETURN_MSG(103, "请求参数错误：（step）");
	}
		break;
	}

	return 0;
}

int CLogicQQPay::v3_pay_get_token(const string &pfkey,
		const string &pf,
		const string &openkey,
		const string &openid,
		const string &tokentype,
		const string &discountid,
		string &appid,
		string &token,
		string &zoneid)
{
	int ret = 0;
	string ts = CTrans::UTOS((unsigned)time(NULL));
	if(!Config::GetValue(zoneid, CONFIG_ZONE_ID))
		zoneid = "0";

	appid = OpenPlatform::GetPlatform()->GetAppId();
	string appkey = OpenPlatform::GetPlatform()->GetAppKey();

	string url = "https://" + OpenPlatform::GetPlatform()->GetConfig("v3domain") + "/v3/pay/get_token?";
	//string url = "https://119.147.19.43/v3/pay/get_token?";
	string qsig = "appid=" + appid + "&discountid=" + discountid + "&openid=" + openid + "&openkey=" + openkey +"&pf="+ pf+ "&pfkey=" + pfkey + "&tokentype=" + tokentype +"&ts=" + ts + "&version=v3&zoneid=" + zoneid;
	string qstr = "appid=" + appid + "&discountid=" + discountid + "&openid=" + openid + "&openkey=" + openkey +"&pf="+ pf+ "&pfkey=" + pfkey + "&tokentype=" + tokentype +"&ts=" + ts + "&version=v3&zoneid=" + zoneid;

	string osig = "GET&" + Crypt::UrlEncodeForTX("/v3/pay/get_token") + "&" + Crypt::UrlEncodeForTX(qsig);
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
		error_log("[http request fail][pfkey=%s]",openid.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http_request_fail");
	}
	Json::Value result;
	Json::Reader reader;
	int responsetRet = 0;
	if (response.empty()
		|| !reader.parse(response, result)
		|| !Json::GetInt(result,"ret", responsetRet)
		|| responsetRet != 0)
	{
		error_log("[response error][openid=%s,response=%s]",openid.c_str(),response.c_str());
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "response_error");
	}

	token = result["token"].asString();

	return 0;
}

int CLogicQQPay::vip_charge_deliver(
		const string &appid,
		const string &openid,
		const string &payitem)
{
	if(Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_VIP_CHARGE_BEGIN_TS)
		&&Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_VIP_CHARGE_END_TS))
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

		int month = CTrans::STOI(items[0]);
		int num = CTrans::STOI(items[2]);

		int total = 0;
		int used = 0;
		unsigned updatetime = 0;
		CDataVipCharge charge;
		int getret = charge.GetVipCharge(openid,total,used,updatetime);

		string type;
		Config::GetValue(type, CONFIG_VIP_CHARGE_TYPE);
		int flag = 1;
		if(type.find("1") != string::npos)
			flag = 1;
		else if(type.find("2") != string::npos)
			flag = 2;
		//本次活动时间内
		if(updatetime >= Config::GetIntValue(CONFIG_VIP_CHARGE_BEGIN_TS)
			&&updatetime <= Config::GetIntValue(CONFIG_VIP_CHARGE_END_TS))
		{
			if(flag == 1)
			{
				total += month*num;
				if(total > BLUE1_VIP_MAX)
					total = BLUE1_VIP_MAX;
			}
			else if(flag == 2)
			{
				++total;
				if(total > BLUE2_VIP_MAX)
					total = BLUE2_VIP_MAX;
			}
		}
		else
		{
			if(flag == 1)
			{
				if(total > BLUE1_VIP_MAX)
					total = BLUE1_VIP_MAX;
				total = month*num;
			}
			else if(flag == 2)
			{
				total = 1;
				if(total > BLUE2_VIP_MAX)
					total = BLUE2_VIP_MAX;
			}
			used = 0;
		}

		if(R_ERR_NO_DATA == getret)
		{
			ret = charge.AddVipCharge(openid,total,used);
			if(ret != 0)
				return ret;
		}
		else
		{
			ret = charge.UpdateVipChargeUsed(openid,total,used);
			if(ret != 0)
				return ret;
		}
	}
	return 0;
}

int CLogicQQPay::blue_year_charge_deliver(
		const string &appid,
		const string &openid,
		const string &payitem)
{

	int ret = 0;
	string o_appid = OpenPlatform::GetPlatform()->GetAppId();
	if (appid != o_appid)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（appid）");
	}

	int hero_total = 0;
	int hero_used = 0;

	CDataVipCharge charge;
	int getret = charge.GetBlueYearVipCharge(openid,hero_total,hero_used);

	if(R_ERR_NO_DATA == getret)
	{
		ret = charge.AddBlueYearVipCharge(openid,1,0);
		if(ret != 0)
			return ret;
	}
	else
	{
		hero_total += 1;
		ret = charge.UpdateBlueYearVipChargeUsed(openid,hero_total,hero_used);
		if(ret != 0)
			return ret;
	}
	return 0;
}

