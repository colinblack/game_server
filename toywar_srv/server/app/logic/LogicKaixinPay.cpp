/*
 * LogicKaixinPay.cpp
 *
 *  Created on: 2012-2-6
 *      Author: dada
 */

#include "LogicKaixinPay.h"

int CLogicKaixinPay::Order(unsigned uid, int type, int cash, int price, uint64_t &payId)
{
	int realCash;
	int realPrice;
	if(!GetItem(type, realCash, realPrice))
	{
		error_log("[get_items_fail][uid=%u,type=%d,cash=%d,price=%d]", uid, type, cash, price);
		PARAM_ERROR_RETURN();
	}
	if(cash != realCash || price != realPrice)
	{
		error_log("[item_data_error][uid=%u,type=%d,cash=%d,price=%d,realCash=%d,realPrice=%d]",
				uid, type, cash, price, realCash, realPrice);
		PARAM_ERROR_RETURN();
	}
	DataPayHistory payHistory;
	payHistory.uid = uid;
	payHistory.channel = PCT_KAIXIN;
	payHistory.type = type;
	payHistory.count = cash;
	payHistory.credit = price;
	payHistory.status = PST_PENDING;
	CLogicPay logicPay;
	int ret = logicPay.AddPayHistory(payHistory);
	if(ret != 0)
	{
		return ret;
	}
	payId = payHistory.pay_id;
	return 0;
}

int CLogicKaixinPay::Pay(unsigned uid, uint64_t payId, const string &channelPayId)
{
	int ret;
	CLogicPay logicPay;
	DataPayHistory payHistory;
	ret = logicPay.GetPayHistory(uid, payId, payHistory);
	if(ret != 0)
	{
		error_log("[get_pay_fail][ret=%d,uid=%u,payid=%llu]", ret, uid, payId);
		return ret;
	}
	payHistory.channel_pay_id = channelPayId;
	payHistory.status = PST_OK;
	ret = logicPay.SetPayHistory(uid, payId, payHistory);
	if(ret != 0)
	{
		error_log("[set_pay_fail][ret=%d,uid=%u,payid=%llu,channelPayId=%s]", ret, uid, payId, channelPayId.c_str());
		return ret;
	}
	ret = logicPay.BuyCash(uid, payHistory.count, payHistory.credit);
	if(ret != 0)
	{
		error_log("[add_cash_fail][ret=%d,uid=%u,cash=%d,payid=%llu]", ret, uid, payHistory.count, payId);
		return ret;
	}
	return 0;
}

static bool ParamCompare(const pair<string, string> &left, const pair<string, string> &right)
{
	int cmp = left.first.compare(right.first);
	if(cmp == 0)
	{
		cmp = left.second.compare(right.second);
	}
	return cmp < 0;
}

bool CLogicKaixinPay::CheckSignature(const map<string, string> &params, const string &key, const string &signature)
{
	vector< pair<string, string> > vecParams;
	for(map<string, string>::const_iterator itr = params.begin(); itr != params.end(); itr++)
	{
		if(itr->first != "sig")
		{
			vecParams.push_back(pair<string, string>(itr->first, itr->second));
		}
	}
	sort(vecParams.begin(), vecParams.end(), ParamCompare);
	string baseString;
	bool isFirst = true;
	for(vector< pair<string, string> >::iterator itr = vecParams.begin(); itr != vecParams.end(); itr++)
	{
		if(isFirst)
		{
			isFirst = false;
		}
		else
		{
			baseString.append("&");
		}
		baseString.append(itr->first);
		baseString.append("=");
		baseString.append(itr->second);
	}
	baseString.append(key);
	string realSign = Crypt::Md5Encode(baseString);
	if(realSign != signature)
	{
		error_log("[kx_sign_error][basestring=%s,realsign=%s,sig=%s]",
				baseString.c_str(), realSign.c_str(), signature.c_str());
		return false;
	}
	return true;
}

bool CLogicKaixinPay::GetItem(int type, int &cash, int &price)
{
	static map<int, pair<int, int> > s_payItems;
	static bool s_initItems = false;
	if(!s_initItems)
	{
		string sItems = OpenPlatform::GetPlatform()->GetConfig("pay_items");
		vector<string> vItems;
		CBasic::StringSplitTrim(sItems, ";", vItems);
		for(vector<string>::iterator itrItem = vItems.begin(); itrItem != vItems.end(); itrItem++)
		{
			vector<string> vItem;
			CBasic::StringSplitTrim(*itrItem, ",", vItem);
			if(vItem.size() == 3)
			{
				int itemType;
				int itemCash;
				int itemPrice;
				if(Convert::StringToInt(itemType, vItem[0]) &&
					Convert::StringToInt(itemCash, vItem[1]) &&
					Convert::StringToInt(itemPrice, vItem[2]))
				{
					if(itemType >= 0 && itemCash >= 0 && itemPrice >= 0)
					{
						s_payItems[itemType] = make_pair(itemCash, itemPrice);
					}
				}
			}
		}
		s_initItems =  true;
	}
	map<int, pair<int, int> >::iterator itrFind = s_payItems.find(type);
	if(itrFind == s_payItems.end())
	{
		return false;
	}
	cash = itrFind->second.first;
	price = itrFind->second.second;
	return true;
}
