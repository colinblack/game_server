#include "LogicTWPay.h"

int CLogicTWPay::PayRewarld(unsigned uid, int cash, int &coins)
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

int CLogicTWPay::deliver(
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

    //防重发, 如果该payment_id已经处理, 那么不再增加钻石
    DataPayHistory payHistory; 
	CDataPayHistory dbPayHistory;
	ret = dbPayHistory.GetPayHistory(uid, PT_TW, payment_id, payHistory);
	if(ret != R_ERR_NO_DATA)
	{
        error_log("twdeliever failed: payment_id %s had been paid", payment_id.c_str());
        ERROR_RETURN_MSG(1, "账单已支付，宝石已发 ");
	}
    
	unsigned quantity_sales = quantity; //加上送的宝石数

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
		ret = logicPay.ChangePay(uid, quantity_sales, 0, pay, "TWTOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
		if (ret != 0) {
			error_log("twdeliever failed");
			ERROR_RETURN_MSG(1, "系统繁忙 ");
		}
	}

	logicPay.DoPay(uid,user,quantity);
	if(bsave)
		logicUser.SetUserFlag(uid,user_flag);

    DataPayHistory payhis;
    payhis.channel = PT_TW;
    payhis.channel_pay_id = payment_id;
    payhis.count = quantity;
    payhis.credit = quantity*50;
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

