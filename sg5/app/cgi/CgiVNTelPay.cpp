#include "LogicInc.h"
#include "LogicVNTelPay.h"

class CCgiVNTelPay : public CCgiBase
{
public:
	CCgiVNTelPay() : CCgiBase("VNTelPay")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
		SetFeature(CF_COMPRESS_OUT);
	}

	CGI_DIRECT_PROCESS(VNTelPay)

	int VNTelPay()
	{
		string knp = "https://api.knp.vn/";
		string success = "RESULT:10@";
		string TxtPartnerId  = OpenPlatform::GetPlatform()->GetConfig(CONFIG_VN_TEL_PNID);
		string signal = OpenPlatform::GetPlatform()->GetConfig(CONFIG_VN_TEL_SGN);
		string TxtMaThe,TxtSeri,TxtTransId,TxtTelco,TxtType,TxtKey,openid;
		unsigned type;
		Json::GetString(m_data,"openid",openid);
		Json::GetUInt(m_data,"type",type);
		Json::GetString(m_data,"card",TxtMaThe);
		Json::GetString(m_data,"sn",TxtSeri);
		TxtTransId = CTrans::UTOS(m_uid) + "_" + TxtMaThe;
		switch(type)
		{
		case 1:
		{
			if(TxtMaThe.length() != 12
			|| TxtMaThe.length() != 14
			|| TxtSeri.length() < 9
			|| TxtSeri.length() > 15)
				return R_ERR_PARAM;
			TxtTelco = "VINA";
			TxtType = "VNP";
		}
			break;
		case 2:
		{
			if(TxtMaThe.length() != 12
			|| TxtMaThe.length() != 14
			|| TxtSeri.length() < 9
			|| TxtSeri.length() > 15)
				return R_ERR_PARAM;
			TxtTelco = "MOBI";
			TxtType = "VMS";
		}
			break;
		case 3:
		{
			if(TxtMaThe.length() < 13
			|| TxtMaThe.length() > 15
			|| TxtSeri.length() < 11
			|| TxtSeri.length() > 15)
				return R_ERR_PARAM;
			TxtTelco = "VIETTEL";
			TxtType = "VTT";
		}
			break;
		case 4:
		{
			if(TxtMaThe.length() != 10
			|| TxtSeri.length() != 10)
				return R_ERR_PARAM;
			TxtTelco = "GATE";
			TxtType = "GATE ";
		}
			break;
		default:
			return R_ERR_PARAM;
			break;
		}
		TxtKey = Crypt::Md5Encode(TxtPartnerId + TxtType + TxtTransId + TxtMaThe + signal);
		string url = knp + TxtTelco
				+ "/?TxtPartnerId=" + TxtPartnerId + "&TxtType=" + TxtType
				+ "&TxtMaThe=" + TxtMaThe + "&TxtSeri=" + TxtSeri
				+ "&TxtTransId" + TxtTransId + "&TxtKey=" + TxtKey;

		string response;
		if (!Network::HttpGetRequest(response, url) || response.empty())
		{
			error_log("[https request fail][url=%s]",url.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, "https_request_fail");
		}

		if(response.find(success) == string::npos)
		{
			error_log("[response error][response=%s]",response.c_str());
			ERROR_RETURN_MSG(R_ERR_NO_DATA, response.c_str());
		}
		int vnd = CTrans::STOI(response.substr(success.length()));

		CLogicVNTelPay logicPay;
		int ret = logicPay.deliver(m_uid, openid, TxtTransId, vnd);
		if (ret != 0) {
			error_log("[vntel pay failed][payment_id=%s&openid=%s&uid=%u&vnd=%u]",
					TxtTransId.c_str(), openid.c_str(), m_uid, vnd);
			return ret;
		}

		error_log("[vntel deliver after][payment_id=%s&openid=%s&uid=%u&vnd=%u]",
				TxtTransId.c_str(), openid.c_str(), m_uid, vnd);

		CGI_SEND_LOG("openid=%s&uid=%s&vnd=%u", openid.c_str(),TxtTransId.c_str(),vnd);
		return R_SUCCESS;
	}
};

CGI_MAIN(CCgiVNTelPay)
