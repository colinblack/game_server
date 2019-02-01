#include "LogicWyxPay.h"

int CLogicWyxPay::WyxGenerateOrder(
		const string &openid,
		const string &openkey,
		int itemId,
		string &order_id,
		string &desc,
		int &amount,
		string &token
		)
{
	unsigned int timestamp = 0;
	mtime(timestamp);
	unsigned int ts = 0;
	unixtime(ts);

	string source = OpenPlatform::GetPlatform()->GetConfig("appid");
	string app_secret = OpenPlatform::GetPlatform()->GetConfig("appkey");

	unsigned int uid = 0;
	int ret = LogicUserBasic::GetUid(uid, PT_WEIYOUXI, openid, false);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("find uid failed");
	}

	// TODO ... generate order_id
	CLogicIdCtrl logicIdCtrl;
	uint64_t tempid = 0;
	ret = logicIdCtrl.GetNextId(KEY_WYX_ORDER_ID_CTRL, tempid);
	if(ret != 0)
	{
		error_log("[GetNextId fail][ret=%d,openid=%s]", ret, openid.c_str());
		DB_ERROR_RETURN_MSG("get order_id fail");
	}
	if (tempid > 999999999)
	{
		error_log("[order_id to big][tempid=%llu]",tempid);
		ERROR_RETURN(R_ERR_DATA_LIMIT);
	}
	int order = (int)tempid;
	char buf[20];
	sprintf(buf, "1109006%09d", order);
	order_id = buf;

	int count = 0;
	amount = 0;
	switch(itemId)
	{
	case 1:
		amount = 500;
		count = 50;
		desc = OpenPlatform::GetPlatform()->GetConfig("item1");
		break;
	case 2:
		amount = 1000;
		count = 110;
		desc = OpenPlatform::GetPlatform()->GetConfig("item2");
		break;
	case 3:
		amount = 5000;
		count = 575;
		desc = OpenPlatform::GetPlatform()->GetConfig("item3");
		break;
	case 4:
		amount = 10000;
		count = 1200;
		desc = OpenPlatform::GetPlatform()->GetConfig("item4");
		break;
	case 5:
		amount = 50000;
		count = 6250;
		desc = OpenPlatform::GetPlatform()->GetConfig("item5");
		break;
	case 6:
		amount = 20000;
		count = 2450;
		desc = OpenPlatform::GetPlatform()->GetConfig("item6");
		break;
	default:
		PARAM_ERROR_RETURN_MSG("item id error");
	}

	string osign;
	String::Format(osign, "%s|%d|%s|%s",
			order_id.c_str(),amount,desc.c_str(),app_secret.c_str());
	string sign = Crypt::Md5Encode(osign);

	string osignature;
	String::Format(osignature, "amount=%d&desc=%s&order_id=%s&session_key=%s&sign=%s&source=%s&timestamp=%u%s",
			amount,desc.c_str(),order_id.c_str(),openkey.c_str(),sign.c_str(),source.c_str(),timestamp,app_secret.c_str());
	string signature = Crypt::Sha1(osignature);

	string qstr;
	String::Format(qstr, "amount=%d&desc=%s&order_id=%s&session_key=%s&sign=%s&signature=%s&source=%s&timestamp=%u",
			amount,desc.c_str(),order_id.c_str(),openkey.c_str(),sign.c_str(),signature.c_str(),source.c_str(),timestamp);

	string apiUrl = "http://api.weibo.com/game/1/pay/get_token.json";
	string response;
	if(!Network::HttpPostRequest(response, apiUrl, qstr))
	{
		error_log("[http request fail][uid=%u,errmsg=%s]",
				uid, response.c_str());
		DATA_ERROR_RETURN_MSG("http request fail");
	}
	Json::Value value;
	Json::Reader reader;
	if(!reader.parse(response, value))
	{
		error_log("[json parse fail][uid=%d,response=%s]",
				uid, response.c_str());
		DATA_ERROR_RETURN_MSG("json parse fail");
	}
	if (!value.isMember("token"))
	{
		error_log("[token error][uid=%d,response=%s]",
				uid, response.c_str());
		DATA_ERROR_RETURN_MSG("token error");
	}
	token = value["token"].asString();

	DataPayHistory payHis;
	payHis.uid = uid;
	payHis.type = itemId;
	payHis.channel = PCT_WEIYOUXI;
	payHis.credit = amount/100;
	payHis.count = count;
	payHis.status = PST_PENDING;
	payHis.time = ts;
	payHis.channel_pay_id = order_id;
	CLogicPay logicPay;
	ret = logicPay.AddPayHistory(payHis);
	if (ret != 0)
		return ret;

	return 0;
}

int CLogicWyxPay::WyxDeliverGood(
		const string &openid,
		const string &order_id,
		const string &appid,
		int amount
		)
{
	unsigned int uid = 0;
	int ret = LogicUserBasic::GetUid(uid, PT_WEIYOUXI, openid, false);
	if (ret != 0)
	{
		DB_ERROR_RETURN_MSG("find uid failed");
	}

	string source = OpenPlatform::GetPlatform()->GetConfig("appid");

	if (source != appid)
	{
		error_log("[appid error][uid=%u,appid=%s]",uid,appid.c_str());
		ERROR_RETURN_MSG(R_ERR_REFUSE, "appid error");
	}

	CDataPayHistory payHisDB;
	DataPayHistory payHis;
	ret = payHisDB.GetPayHistory(uid, PCT_WEIYOUXI, order_id, payHis);
	if (ret != 0)
	{
		error_log("[GetPayHistory fail][uid=%d,ret=%d,order_id=%s]", uid,ret,order_id.c_str());
		DB_ERROR_RETURN_MSG("get record fail");
	}

	if (payHis.status != PST_PENDING)
	{
		return 0;
	}

	payHis.status = PST_OK;
	ret = payHisDB.SetPayHistoryStatus(uid, PCT_WEIYOUXI, order_id, PST_OK);
	if (ret != 0)
	{
		error_log("[SetPayHistoryStatus fail][uid=%d,ret=%d,order_id=%s]", uid,ret,order_id.c_str());
		DB_ERROR_RETURN_MSG("update status fail");
	}

	CLogicPay logicPay;
	ret = logicPay.BuyCash(uid, payHis.count, payHis.credit);
	if (ret != 0)
	{
		error_log("[BuyCash fail][uid=%d,ret=%d,order=%s]", uid,ret,order_id.c_str());
		DB_ERROR_RETURN_MSG("add cash fail");
	}

	return 0;
}
