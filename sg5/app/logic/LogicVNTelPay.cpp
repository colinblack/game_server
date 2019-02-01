#include "LogicVNTelPay.h"

int CLogicVNTelPay::deliver(
        const unsigned uid,
        const string &openid,
        const string &payment_id,
        const int vnd)
{
    //防重发, 如果该payment_id已经处理, 那么不再增加钻石
    DataPayHistory payHistory; 
	CDataPayHistory dbPayHistory;
	int ret = dbPayHistory.GetPayHistory(uid, PT_VN, payment_id, payHistory);
	if(ret != R_ERR_NO_DATA)
	{
        error_log("vnteldeliever failed: payment_id %s had been paid", payment_id.c_str());
        ERROR_RETURN_MSG(1, "used");
	}

	int cash = vnd / 10000 * 24;
	int addcash;
	if(vnd >= 500000)
		addcash = cash + 120;
	else
		addcash = cash;
    
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
	if (addcash > 0)
	{
		ret = logicPay.ChangePay(uid, addcash, 0, "VNTOPUP", PAY_FLAG_CHARGE);
		if (ret != 0) {
			error_log("vnteldeliever failed");
			ERROR_RETURN_MSG(1, "busy ");
		}
	}
	logicPay.DoPay(uid,user,cash);
	if(bsave)
		logicUser.SetUserFlag(uid,user_flag);

    DataPayHistory payhis;
    payhis.channel = PT_VN;
    payhis.channel_pay_id = payment_id;
    payhis.count = cash;
    payhis.credit = cash*2;
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

