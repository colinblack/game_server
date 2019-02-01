#include "LogicFBPay.h"

CLogicFBPay::T_ItemMap CLogicFBPay::g_ItemInfo;

int CLogicFBPay::GetItemInfo(
		unsigned item_id,
		FBItemInfo &item)
{
	static bool bInit = false;
	if (!bInit)
	{
		string itemFile;
		itemFile = Config::GetValue("pay_item_info");
		if (itemFile.empty())
			itemFile = "/data/release/toywar/conf/pay_item_info.xml";
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
			FBItemInfo itemTmp;
			itemTmp.item_id = CTrans::STOI(xmlConf.GetAttrib("id"));
			itemTmp.title = xmlConf.GetAttrib("title");
			itemTmp.description = xmlConf.GetAttrib("description");
			itemTmp.image_url = xmlConf.GetAttrib("image_url");
			itemTmp.product_url = xmlConf.GetAttrib("product_url");
			itemTmp.price = CTrans::STOI(xmlConf.GetAttrib("price"));
			itemTmp.cash = CTrans::STOI(xmlConf.GetAttrib("cash"));
			g_ItemInfo[itemTmp.item_id] = itemTmp;
		}
		bInit = true;
	}

	if (g_ItemInfo.empty())
	{
		error_log("[no item info][item_id=%u]",item_id);
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_item_info");
	}

	T_ItemMap::const_iterator it;
	it = g_ItemInfo.find(item_id);
	if (it == g_ItemInfo.end())
	{
		error_log("[no item info][item_id=%u]",item_id);
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no_item_info");
	}

	item.item_id = (it->second).item_id;
	item.title = (it->second).title;
	item.description = (it->second).description;
	item.image_url = (it->second).image_url;
	item.product_url = (it->second).product_url;
	item.price = (it->second).price;
	item.cash = (it->second).cash;

	return 0;
}

int CLogicFBPay::payments_get_items(
		const string &openid,
		const string &orderId,
		unsigned itemId,
		FBItemInfo &itemInfo)
{
	int ret = 0;
	unsigned uid = 0;
	ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid, false);
	if (ret != 0)
		return ret;

	ret = GetItemInfo(itemId, itemInfo);
	if (ret != 0)
		return ret;

	CLogicPay logicPay;
	DataPayHistory payHis;
	payHis.uid = uid;
	payHis.type = itemId;
	payHis.channel = PCT_FACEBOOK_CREDITS;
	payHis.channel_pay_id = orderId;
	payHis.credit = itemInfo.price;
	payHis.count = itemInfo.cash;
	payHis.status = PST_PENDING;
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
		PARAM_ERROR_RETURN();
	}

	int ret = 0;
	unsigned uid = 0;
	ret = LogicUserBasic::GetUid(uid, OpenPlatform::GetType(), openid, false);
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
			ret = logicPay.BuyCash(uid, payHis.count, payHis.credit);
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
