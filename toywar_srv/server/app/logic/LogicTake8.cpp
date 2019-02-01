#include "LogicTake8.h"

int CLogicTake8::ProcessOrder(
		const string &gameId,
		const string &orderId,
		const string &fbuid,
		int amt,
		const string &vcode)
{
	string take8_game_id = OpenPlatform::GetPlatform()->GetConfig("take8_game_id");
	if (gameId != take8_game_id)
	{
		error_log("[GameID not match][fbuid=%s,gameId=%s,tgameId=%s]",
				fbuid.c_str(),gameId.c_str(),take8_game_id.c_str());
		m_outMsg = "0004";
		ERROR_RETURN_MSG(R_ERR_REFUSE, "GameID not match");
	}

	string key = OpenPlatform::GetPlatform()->GetConfig("take8_key");
	string osig;
	osig.append(gameId);
	osig.append(orderId);
	osig.append(fbuid);
	osig.append(key);
	string sig = Crypt::Md5Encode(osig);
	if (vcode != sig)
	{
		error_log("[GameID not match][fbuid=%s,orderId=%s,vcode=%s]",
				fbuid.c_str(),orderId.c_str(),vcode.c_str());
		m_outMsg = "0003";
		PARAM_ERROR_RETURN_MSG("sig error");
	}

	unsigned int uid = 0;
	int ret = LogicUserBasic::GetUid(uid, PT_FACEBOOK, fbuid, false);
	if (ret != 0)
	{
		m_outMsg = "0001";
		DB_ERROR_RETURN_MSG("find uid failed");
	}

	CDataPayHistory payHisDB;
	DataPayHistory payHis;
	ret = payHisDB.GetPayHistory(uid, PCT_TAKE8, orderId, payHis);
	if (ret == 0)
	{
		info_log("[duplicate orderId][uid=%d,orderId=%s,amt=%d,fbuid=%s]",
				uid,orderId.c_str(),amt,fbuid.c_str());
		return 0;
	}

	string query_url = OpenPlatform::GetPlatform()->GetConfig("take8_url");
	string osig2;
	osig2.append(gameId);
	osig2.append(orderId);
	osig2.append(key);
	string sig2 = Crypt::Md5Encode(osig2);
	string qstr = "GameID=" + gameId + "&OrderID=" + orderId + "&VCode=" + sig2;
	string response;
	if (!Network::HttpPostRequest(response, query_url, qstr))
	{
		error_log("[http request fail][uid=%d,orderId=%s]",uid,orderId.c_str());
		m_outMsg = "0004";
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "http request fail");
	}

	if (response.empty())
	{
		error_log("[no response][uid=%d,orderId=%s]",uid,orderId.c_str());
		m_outMsg = "0004";
		ERROR_RETURN_MSG(R_ERR_NO_DATA, "no response");
	}
	vector<string> vec;
	CBasic::StringSplit(response, ":", vec);
	if (vec.size() < 2)
	{
		error_log("[res data error][uid=%d,orderId=%s,res=%s]",uid,orderId.c_str(),response.c_str());
		m_outMsg = "0004";
		ERROR_RETURN_MSG(R_ERR_DATA, "res data error");
	}
	info_log("[][uid=%d,orderId=%s,res=%s]",uid,orderId.c_str(),response.c_str());
	int cash = 0;
	if (vec[0] == "cash01")
	{
		cash = 50 * atoi(vec[1].c_str());
	}
	else if (vec[0] == "cash02")
	{
		cash = 110 * atoi(vec[1].c_str());
	}
	else if (vec[0] == "cash03")
	{
		cash = 575 * atoi(vec[1].c_str());
	}
	else if (vec[0] == "cash04")
	{
		cash = 1200 * atoi(vec[1].c_str());
	}
	else if (vec[0] == "cash05")
	{
		cash = 2450 * atoi(vec[1].c_str());
	}
//	else if (vec[0] == "cash06")
//	{
//		cash = 5000 * atoi(vec[1].c_str());
//	}

	if (cash <= 0)
	{
		error_log("[cash error][uid=%d,orderId=%s,cash=%d]",uid,orderId.c_str(),cash);
		m_outMsg = "0004";
		ERROR_RETURN_MSG(R_ERR_DATA, "cash error");
	}

	CLogicPay logicPay;
	ret = logicPay.BuyCash(uid, cash, amt);
	if (ret != 0)
	{
		m_outMsg = "0004";
		DB_ERROR_RETURN_MSG("change cash fail");
	}

	int now = time(0);
	payHis.uid = uid;
	payHis.pay_id = 0;
	payHis.type = 1;
	payHis.channel = PCT_TAKE8;
	payHis.channel_pay_id = orderId;
	payHis.credit = amt;
	payHis.count = cash;
	payHis.status = PST_OK;
	payHis.time = now;
	ret = logicPay.AddPayHistory(payHis);
	if (ret != 0)
	{
		error_log("[AddPayHistory fail][uid=%d,ret=%d,pay_id=%ld,orderId=%s]",
				uid,ret,payHis.pay_id,orderId.c_str());
	}

	/*ret = payHisDB.AddPayHistory(payHis);
	if (ret != 0)
	{
		error_log("[AddPayHistory fail][uid=%d,ret=%d]",uid,ret);
	}*/

	return 0;
}
