/*
 * Logic4399Pay.cpp
 *
 *  Created on: 2015-4-30
 *      Author: Ralf
 */


#include "Logic4399Pay.h"

int CLogic4399Pay::deliver(
		const string &openid,
		unsigned serverid,
		unsigned count,
		const string &billno,
		unsigned money)
{
	int ret = 0;
	CLogicPay logicPay;
	unsigned uid = 0;
	CDataUserMapping dbUserMapping;
	ret = dbUserMapping.GetUID(openid, serverid, uid);
	if(ret == R_ERR_NO_DATA)
	{
		CgiUtil::PrintText("-3");
		return 0;
	}
	if(ret || uid == 0)
		return R_ERR_DB;

	/****change to ourself's platform************/
	//防重发, 如果该payment_id已经处理, 那么不再增加钻石
	DataPayHistory payHistory;
	CDataPayHistory dbPayHistory;
	ret = dbPayHistory.GetPayHistory(uid, OpenPlatform::GetType(), billno, payHistory);
	if(ret == 0)
	{
		CgiUtil::PrintText("2");
		return 0;
	}

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

	ret = logicPay.ChangePay(uid, count, 0, pay, "4399TOPUP", user_flag, bsave, PAY_FLAG_CHARGE);
	if (ret != 0) {
		error_log("qqdeliever failed");
		ERROR_RETURN_MSG(1, "系统繁忙 ");
	}
	logicPay.DoPay(uid,user,count);
	if(bsave)
		logicUser.SetUserFlag(uid,user_flag);

	DataPayHistory payhis;
	payhis.channel = OpenPlatform::GetType();
	payhis.channel_pay_id = billno;
	payhis.count = count;
	payhis.credit = money;
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





