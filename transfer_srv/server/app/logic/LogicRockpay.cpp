#include "LogicRockpay.h"
#include "soapRoFunSoapProxy.h"
#include "RoFunSoap.nsmap"
#include "DataPayHistory.h"
#include "DataUserMapping.h"
#include "LogicPay.h"
#include "IOpenPlatform.h"
using namespace std;

int CLogicRockpay::GenerateOrderId(
		const string &openid,
		string &app,
		string &aoid,
		string &r_url,
		string &m1,
		string &m2,
		string &v_code)
{
	CDataUserMapping mapping;
	unsigned int uid = 0;
	int ret = mapping.GetMapping(openid, PT_FACEBOOK, uid);
	if (ret != 0)
	{
		m_errMsg = "query user failed";
		error_log("[GetMapping fail][openid=%s,ret=%d]",openid.c_str(),ret);
		return -1;
	}
	string appid = OpenPlatform::GetPlatform()->GetConfig("rockpay_app_id");
	string appkey = OpenPlatform::GetPlatform()->GetConfig("rockpay_app_key");
	string app_r_url = OpenPlatform::GetPlatform()->GetConfig("rockpay_r_url");

	int now = time(0);
	string orderid;
	orderid.append(CTrans::UTOS(uid)).append(CTrans::ITOS(now));

	string ssig = appid + orderid + appkey;
	string sig = Crypt::Md5Encode(ssig);

	app = appid;
	aoid = orderid;
	r_url = app_r_url;
	m1 = openid;
	m2 = CTrans::UTOS(uid);
	v_code = sig;

	return 0;
}

int CLogicRockpay::PayCallback(
		const string &aoid,
		const string &m1,
		const string &m2,
		const string &tid,
		const string &v_code,
		int &cash)
{
	cash = 0;
	unsigned int uid = CTrans::STOI(m2);
	if (!IsValidUid(uid))
	{
		m_errMsg = "invalid uid";
		error_log("[invalid uid][uid=%d,m2=%s]",uid,m2.c_str());
		return -1;
	}
	unsigned long long orderid = CTrans::STOI64(aoid);

	string appid = OpenPlatform::GetPlatform()->GetConfig("rockpay_app_id");
	string appkey = OpenPlatform::GetPlatform()->GetConfig("rockpay_app_key");

	string ssig = appid + tid + appkey;
	string sig = Crypt::Md5Encode(ssig);
	if (v_code != sig)
	{
		m_errMsg = "sig error";
		error_log("[sig error][uid=%d,aoid=%s]", uid,aoid.c_str());
		return 1;
	}

	CDataPayHistory payHisDB;
	DataPayHistory payHis;
	int ret = payHisDB.GetPayHistory(uid, orderid, payHis);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		m_errMsg = "query pay failed";
		error_log("[GetPayHistory fail][uid=%d,ret=%d]",uid,ret);
		return -1;
	}
	if (ret == R_ERR_NO_DATA)
	{
		payHis.uid = uid;
		payHis.pay_id = orderid;
		payHis.type = 0;
		payHis.channel = PCT_ROCKPAY;
		payHis.channel_pay_id = tid;
		payHis.credit = 0;
		payHis.count = 0;
		payHis.status = PST_PENDING;
		payHis.time = time(0);
		int ret2 = payHisDB.AddPayHistory(payHis);
		if (ret2 != 0)
		{
			m_errMsg = "add pay failed";
			error_log("[AddPayHistory fail][uid=%d,ret2=%d]",uid,ret2);
			return -1;
		}
	}

	string no_const_tid = tid;

	RoFunSoapProxy RoFun;

	_ns1__CheckTransaction req;
	_ns1__CheckTransactionResponse res;

	req.app_USCOREid = &appid;
	req.transaction_USCOREid = &no_const_tid;
	req.verify_USCOREcode = &sig;
	if (RoFun.CheckTransaction(&req, &res) != SOAP_OK)
	{
		m_errMsg = "CheckTransaction error";
		error_log("[CheckTransaction error][uid=%d,aoid=%s,err=%s]",
				uid,aoid.c_str(),RoFun.soap_fault_string());
		return 2;
	}
	int result = CTrans::STOI(res.CheckTransactionResult->string[0]);
	if (result != 1)
	{
		m_errMsg = "status error";
		error_log("[status error][uid=%d,aoid=%s,result=%d]",uid,aoid.c_str(),result);
		return 2;
	}
	if (payHis.status == PST_PENDING)
	{
		payHis.status = PST_OK;
		payHis.credit = CTrans::STOI(res.CheckTransactionResult->string[3]);
		payHis.count = CTrans::STOI(res.CheckTransactionResult->string[4]);
		ret = payHisDB.SetPayHistory(uid, orderid, payHis);
		if (ret != 0)
		{
			m_errMsg = "update status failed";
			error_log("[SetPayHistory fail][uid=%d,ret=%d]",uid,ret);
			return -1;
		}
		CLogicPay logicPay;
		ret = logicPay.BuyCash(uid, payHis.count, payHis.credit);
		if (ret != 0)
		{
			m_errMsg = "add cash failed";
			return -1;
		}
		info_log("[add cash][uid=%d,aoid=%s,credit=%d,count=%d,tid=%s,name=%s]",
				uid,aoid.c_str(),payHis.credit,payHis.count,tid.c_str(),res.CheckTransactionResult->string[2].c_str());
	}

	_ns1__CommitTransaction req2;
	_ns1__CommitTransactionResponse res2;

	req2.app_USCOREid = &appid;
	req2.transaction_USCOREid = &no_const_tid;
	req2.verify_USCOREcode = &sig;

	if (RoFun.CommitTransaction(&req2, &res2) != SOAP_OK)
	{
		m_errMsg = "CommitTransaction error";
		error_log("[CommitTransaction error][uid=%d,err=%s]",uid,RoFun.soap_fault_string());
		return 2;
	}
	int result2 = CTrans::STOI(res2.CommitTransactionResult->string[0]);
	if (result2 != 1)
	{
		m_errMsg = "CommitTransaction failed";
		error_log("[CommitTransaction fail][uid=%d,result2=%d]",uid,result2);
		return 2;
	}

	cash = payHis.count;
	return 0;
}
