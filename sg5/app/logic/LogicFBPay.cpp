#include "LogicFBPay.h"

CLogicFBPay::T_ItemMap CLogicFBPay::g_ItemInfo;

int CLogicFBPay::Init()
{
	static bool bInit = false;
	if (!bInit)
	{
		string itemFile;
		itemFile = Config::GetValue("pay_item_info");
		if (itemFile.empty())
			itemFile = "/data/release/sgonline/conf/pay_item_info.xml";
		CMarkupSTL xmlConf;
		if(!xmlConf.Load(itemFile.c_str()))
		{
			fatal_log("[load item info fail][path=%s]", itemFile.c_str());
			DB_ERROR_RETURN_MSG("load_item_fail");
		}
		if(!xmlConf.FindElem("items"))
		{
			fatal_log("[parse item info fail][path=%s]", itemFile.c_str());
			DB_ERROR_RETURN_MSG("load_item_fail");
		}
		xmlConf.IntoElem();
		while(xmlConf.FindElem("item"))
		{
			FBItemInfo itemTmp;
			itemTmp.item_id = CTrans::STOI(xmlConf.GetAttrib("id"));
			itemTmp.title = xmlConf.GetAttrib("title");
			itemTmp.description = xmlConf.GetAttrib("description");
			itemTmp.image_url = xmlConf.GetAttrib("image_url");
			itemTmp.product_url = xmlConf.GetAttrib("product_url");
			itemTmp.price = CTrans::STOI(xmlConf.GetAttrib("price"));
			itemTmp.cash = CTrans::STOI(xmlConf.GetAttrib("cash"));
			xmlConf.IntoElem();
			while(xmlConf.FindElem("locale"))
			{
				string name = xmlConf.GetAttrib("name");
				if (!name.empty())
				{
					itemTmp.titleMap[name] = xmlConf.GetAttrib("title");
					itemTmp.descMap[name] = xmlConf.GetAttrib("description");
				}
			}
			xmlConf.OutOfElem();
			g_ItemInfo[itemTmp.product_url] = itemTmp;
		}
		bInit = true;
	}

	return 0;
}

int CLogicFBPay::GetItemInfo(
		const string &product,
		const string &locale,
		FBItemInfo &item)
{
    int ret = Init();
    if (ret != 0)
    {
        return ret;
    }

	if (g_ItemInfo.empty())
	{
		error_log("[no item info][product=%s]",product.c_str());
		DB_ERROR_RETURN_MSG("no_item_info");
	}

	T_ItemMap::const_iterator it;
	it = g_ItemInfo.find(product);
	if (it == g_ItemInfo.end())
	{
		error_log("[no item info][product=%s]",product.c_str());
		DB_ERROR_RETURN_MSG("no_item_info");
	}

	item.item_id = (it->second).item_id;
	item.title = (it->second).title;
	item.description = (it->second).description;
	item.image_url = (it->second).image_url;
	item.product_url = (it->second).product_url;
	item.price = (it->second).price;
	item.cash = (it->second).cash;
	if (!locale.empty())
	{
		map<string, string>::const_iterator it2;
		it2 = (it->second).titleMap.find(locale);
		if (it2 != (it->second).titleMap.end())
		{
			item.title = it2->second;
		}
		it2 = (it->second).descMap.find(locale);
		if (it2 != (it->second).descMap.end())
		{
			item.description = it2->second;
		}
	}

	return 0;
}

/*
int CLogicFBPay::payments_get_items(
		const string &openid,
		const string &orderId,
		unsigned itemId,
		const string &locale,
		FBItemInfo &itemInfo)
{
	int ret = 0;
	CLogicUserBasic logicUserBasic;
	unsigned uid = 0;
	ret = logicUserBasic.GetUid(uid, PT_FACEBOOK, openid, false);
	if (ret != 0)
		return ret;

	ret = GetItemInfo(itemId, locale, itemInfo);
	if (ret != 0)
		return ret;

	CLogicPay logicPay;
	DataPayHistory payHis;
	payHis.uid = uid;
	payHis.type = itemId;
	payHis.channel = PCT_FACEBOOK_CREDITS;
	payHis.channel_pay_id = orderId;
	payHis.credit = itemInfo.price * 10;
	payHis.count = 1;
	payHis.status = PST_PENDING;
	payHis.open_id = openid;
	ret = logicPay.AddPayHistory(payHis);
	if (ret != 0)
		return ret;

	return 0;
}

int CLogicFBPay::payments_status_update(
		const string &openid,
		const string &orderId,
		const string &status,
		string &next_state)
{
	if (status != "placed" && status != "settled")
	{
		PARAM_ERROR_RETURN_MSG("status_error");
	}

	int ret = 0;
	CLogicUserBasic logicUserBasic;
	unsigned uid = 0;
	ret = logicUserBasic.GetUid(uid, PT_FACEBOOK, openid, false);
	if (ret != 0)
		return ret;

	CLogicPay logicPay;
	DataPayHistory payHis;

	if (status == "placed")
	{
		ret = logicPay.GetPayHistory(uid, PCT_FACEBOOK_CREDITS, orderId, payHis);
		if (ret != 0)
			return ret;
		next_state = "settled";
	}
	else
	{
		ret = logicPay.GetPayHistory(uid, PCT_FACEBOOK_CREDITS, orderId, payHis);
		if (ret != 0)
			return ret;

		if (payHis.status == PST_PENDING)
		{
			FBItemInfo itemInfo;
			ret = GetItemInfo(payHis.type, "", itemInfo);
			if (ret != 0)
				return ret;
			int addCash = itemInfo.cash;
			unsigned balance = 0;
			ret = logicPay.ChangePay(uid, addCash, 0, "FBTOPUP");
			if (ret != 0)
				return ret;
			ret = logicPay.SetPayHistoryStatus(uid, PCT_FACEBOOK_CREDITS, orderId, PST_OK);
			if (ret != 0)
			{
				error_log("[SetPayHistoryStatus fail][uid=%d,ret=%d,orderId=%s]",
						uid,ret,orderId.c_str());
			}
		}
		else
		{
			info_log("[duplicate settled][uid=%u,orderId=%s,status=%s]",uid,orderId.c_str(),status.c_str());
		}
		next_state = "";
	}

	return 0;
}
*/

/*
int CLogicFBPay::deliver(
        const string &openid,
        const string &payment_id,
        const string &product,
        const unsigned quantity)
{
	CLogicUserBasic logicUserBasic;
	unsigned uid = 0;
	int ret = logicUserBasic.GetUid(uid, OpenPlatform::GetType(), openid, true);
	if (ret == R_ERR_NO_DATA)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
	}
	else if (ret != 0)
	{
		ERROR_RETURN_MSG(1, "系统繁忙 ");
	}

    DataPayHistory payHistory; 
	CDataPayHistory dbPayHistory;
	ret = dbPayHistory.GetPayHistory(uid, PT_FACEBOOK, payment_id, payHistory);
	if(ret != R_ERR_NO_DATA)
	{
        error_log("fbdeliever failed: payment_id %s had been paid", payment_id.c_str());
        ERROR_RETURN_MSG(1, "账单已支付，宝石已发 ");
	}
    
	unsigned quantity_sales = quantity; //加上送的宝石数
	if (quantity == 2000)      quantity_sales += 200;
    else if (quantity == 4000) quantity_sales += 600;
    else if (quantity == 8000) quantity_sales += 1600;

    CLogicPay logicPay;
    ret = logicPay.ChangePay(uid, quantity_sales, 0, "FBTOPUP", 1);
    if (0 != ret) {
        error_log("fbdeliever failed");
        ERROR_RETURN_MSG(1, "系统繁忙 ");
    }
    else
        error_log("fbdeliever sucessed uid=%d count=%d",uid,quantity);

    DataPayHistory payhis;
    payhis.channel = PT_FACEBOOK;
    payhis.channel_pay_id = payment_id;
    payhis.count = 1;
    payhis.credit = quantity;
    payhis.status = PST_OK;
    payhis.type = 0;
    payhis.uid = uid;
    payhis.open_id = openid;
    ret = logicPay.AddPayHistory(payhis);
    if (ret != 0)
    {
        error_log("[AddPayHistory fail][ret=%d,openid=%s,payment_id=%s]",
                ret,openid.c_str(),payment_id.c_str());
    }

    return 0;
}
*/

int CLogicFBPay::PayRewarld(unsigned uid, int cash, int &coins)
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

int CLogicFBPay::chargeback(
			const string &openid,
			const unsigned serverid,
			const string &payment_id,
			const unsigned quantity)
{
	if(!serverid)
		return R_ERR_DB;

	unsigned uid = 0;
	CDataUserMapping dbUserMapping;
	int ret = dbUserMapping.GetUID(openid, serverid, uid);
	if( ret!=0 || uid == 0)
		return R_ERR_DB;

	DataPayHistory payHistory;
	CDataPayHistory dbPayHistory;
	ret = dbPayHistory.GetPayHistory(uid,OpenPlatform::GetType(), payment_id, payHistory);
	if(ret)
		return ret;
	if(payHistory.status != PST_OK)
		return R_ERR_DB;
	dbPayHistory.SetPayHistoryStatus(uid, payHistory.pay_id , PST_BACK);

	int quantity_sales = quantity; //加上送的宝石数
	if (quantity == 5000)      quantity_sales += 500;
	else if (quantity == 10000) quantity_sales += 1500;
	else if (quantity == 20000) quantity_sales += 4000;

	COINS_LOG("[chargeback][payment_id=%s&openid=%s&quantity=%u]",payment_id.c_str(),openid.c_str(), quantity);
	CLogicPay logicPay;
	if (quantity != 0)
		logicPay.ChangePay(uid, -quantity_sales, -quantity_sales, "FBTOPUP",PAY_FLAG_COST_ALL);

	int accCharge = quantity;
	CDataUser userDb;
	DataUser user;
	userDb.GetUserLimit(uid,user);
	userDb.AddAccCharge(uid, -accCharge);

	return 0;
}

int CLogicFBPay::deliver(
        const unsigned uid,
        const string &openid,
        const string &payment_id,
        const string &product,
        const unsigned quantity)
{
    //防重发, 如果该payment_id已经处理, 那么不再增加钻石
    DataPayHistory payHistory; 
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), payment_id, payHistory);
	if(ret != R_ERR_NO_DATA)
	{
        error_log("fbdeliever failed: payment_id %s had been paid", payment_id.c_str());
        ERROR_RETURN_MSG(1, "账单已支付，宝石已发 ");
	}
    
	unsigned quantity_sales = quantity; //加上送的宝石数
	if (quantity == 5000)      quantity_sales += 500;
    else if (quantity == 10000) quantity_sales += 1500;
    else if (quantity == 20000) quantity_sales += 4000;

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
	if (quantity != 0)
	{
		int coins = 0;
		ret = logicPay.ChangePay(uid, quantity_sales, coins, pay, "FBTOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (ret != 0) {
			error_log("fbdeliever failed");
			ERROR_RETURN_MSG(1, "系统繁忙 ");
		}
	}
	logicPay.DoPay(uid,user,quantity);
	if(bsave)
		logicUser.SetUserFlag(uid,user_flag);

    DataPayHistory payhis;
    payhis.channel = OpenPlatform::GetType();
    payhis.channel_pay_id = payment_id;
    payhis.count = quantity;
    payhis.credit = quantity*2;
    payhis.status = PST_OK;
    payhis.type = 0;
    payhis.uid = uid;
    payhis.open_id = openid;
    ret = logicPay.AddPayHistory(payhis);
    if (ret != 0)
    {
        error_log("[AddPayHistory fail][ret=%d,openid=%s,payment_id=%s]",
                ret,openid.c_str(),payment_id.c_str());
    }
	
    return 0;
}

int CLogicFBPay::deliver_no_serverid(
        const string &openid,
        const string &payment_id,
        const string &product,
        const unsigned quantity)
{
	CLogicUserBasic logicUserBasic;
	unsigned uid = 0;
	int ret = logicUserBasic.GetUid(uid, OpenPlatform::GetType(), openid, true);
	if (ret == R_ERR_NO_DATA)
	{
		ERROR_RETURN_MSG(4, "请求参数错误：（openid）");
	}
	else if (ret != 0)
	{
		ERROR_RETURN_MSG(1, "系统繁忙 ");
	}

    return deliver(uid, openid, payment_id, product, quantity);
}

int CLogicFBPay::deliver_serverid(
        const string &openid,
        const uint32_t serverid,
        const string &payment_id,
        const string &product,
        const unsigned quantity)
{
	unsigned uid = 0;
	CDataUserMapping dbUserMapping;
	int ret = dbUserMapping.GetUID(openid, serverid, uid);
	if( ret!=0 || uid == 0)
		return R_ERR_DB;

    return deliver(uid, openid, payment_id, product, quantity);
}

