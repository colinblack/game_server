#define NO_FCGI_DEFINES

#include "OPPOPlatform.h"
#include <iostream>
#include "rsa.h"
#include "err.h"
#include "pem.h"



OPPOPlatform::OPPOPlatform()
{

}

int OPPOPlatform::Initialize(const string &appid, const string &appkey, map<string, string> &params)
{
	IOpenPlatform::Initialize(appid, appkey, params);
	return 0;
}

void OPPOPlatform::SetParameter(const map<string, string> &params)
{

}

int OPPOPlatform::GetUserInfo(OPUserInfo &userInfo, const string &openid, const string &openkey)
{
	userInfo.OpenId = openid;
	return 0;
}

int OPPOPlatform::formatUrl(const map<string, string> &param,
		const string &appkey,
		const string &api,
		string &url)
{
	string qstr;
	map<string, string>::const_iterator itr = param.begin();
	for (; itr != param.end(); ++itr)
	{
		if (!qstr.empty())
		{
			qstr.append("&").append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
		else
		{
			qstr.append(itr->first).append("=").append(Crypt::UrlEncodeForTX(itr->second));
		}
	}
	url = qstr + "&sign=" + Crypt::UrlEncodeForTX(appkey);
	return 0;
}

string OPPOPlatform::GetErrorMessage()
{
	return "no error message";
}

string OPPOPlatform::GetSig(const map<string, string> &params, const string &appkey, bool get, const string &uri, string &qstr)
{
	string sig;
	string qsig;
	qstr.clear();
	map<string, string>::const_iterator it = params.begin();
	for (; it != params.end(); it++)
	{
		if (!qsig.empty())
		{
			qsig += "&";
		}
		if (!qstr.empty())
		{
			qstr += "&";
		}
		qsig += it->first + "=" + it->second;
		qstr += it->first + "=" + Crypt::UrlEncodeForTX(it->second);
	}
	string osig = (get ? "GET&" : "POST&") + Crypt::UrlEncodeForTX(uri) + "&" + Crypt::UrlEncodeForTX(qsig);
	string key = appkey + "&";
	string bsig = Crypt::HmacSha1(osig, key);
	Crypt::Base64Encode(sig, bsig);
	qstr += "&sig=" + Crypt::UrlEncodeForTX(sig);

	return sig;
}

int OPPOPlatform::GetAppFriendList(OPFriendList &friendList, const string &openid, const string &openkey)
{
	return 0;
}

bool OPPOPlatform::CheckSign(const string &text,const string publicKey,const string sign)
{
	string decodeSign;
	Crypt::Base64Decode(decodeSign,sign);
	bool isvalid = Crypt::RsaWithSha1Verify(text,publicKey,decodeSign);
	return isvalid;
}

string OPPOPlatform::GetSigStr(map<string,string> param,const string key)
{
	info_log("key=%s",key.c_str());
	string sig = "";
	//1.签名按照请求参数名ASCII码从小到大排序（字典序）
	map<string,string>::iterator it = param.begin();
	for(; it != param.end(); it++)
	{
		if(sig.empty())
			sig += it->first + "=" + it->second;
		else
			sig += "&" + it->first + "=" + it->second;
	}

	sig = "appId=123456&callBackUrl=http://xxx.aa.bb&cpOrderId=abcde&price=200&productName";
	info_log("sig=%s",sig.c_str());


	string Sign;
	string base64Sign;
	//string filename = DEFAULT_APP_PATH;
	//filename.append("pi/conf/platform/rsa_private_key.pem");

	Crypt::RsaSignature(sig,key,Sign,"sha1");
	Crypt::Base64Encode(base64Sign,Sign);
	info_log("base64Sign=%s",base64Sign.c_str());

	return Sign;

	/*
	//2.使用sha256加密数据
	sig = "appId=123456&callBackUrl=http://xxx.aa.bb&cpOrderId=abcde&price=200&productName";
	string sha256;
	sha256 = Crypt::HmacSha256(sig.c_str(), "");
	string sha256Base64;
	Crypt::Base64Encode(sha256Base64,sha256);
	info_log("sha256Base64:%s",sha256Base64.c_str());

	//3.将参数使用RSA算法进行签名
	string strPemFileName = DEFAULT_APP_PATH;
	strPemFileName.append("pi/conf/platform/rsa_private_key.pem");
	if (strPemFileName.empty() || sha256.empty())
	{
		return "";
	}
	FILE* hPrivateFile = fopen(strPemFileName.c_str(), "rb");
	if( hPrivateFile == NULL )
	{
		error_log("open_private_key_failed:filepath=%s",strPemFileName.c_str());
		return "";
	}
	std::string strRet;
	std::string sign;
	RSA* pRSAPrivateKey = RSA_new();
	if((pRSAPrivateKey = PEM_read_RSAPrivateKey(hPrivateFile, &pRSAPrivateKey, 0, 0)) == NULL)
	{
		error_log("read_private_key_failed:filepath=%s",strPemFileName.c_str());
		return "";
	}


	int nLen = RSA_size(pRSAPrivateKey);
	char* pEncode = new char[nLen + 1];
	int ret = RSA_private_encrypt(sha256.length(), (const unsigned char*)sha256.c_str(), (unsigned char*)pEncode, pRSAPrivateKey, RSA_PKCS1_PADDING);

	if (ret >= 0)
	{
		strRet = std::string(pEncode, ret);
	}

	Crypt::Base64Encode(sign,strRet);
	info_log("sign:%s",sign.c_str());

	delete[] pEncode;
	RSA_free(pRSAPrivateKey);
	fclose(hPrivateFile);
	CRYPTO_cleanup_all_ex_data();


	return sign;
	*/
}

string  OPPOPlatform::GenerateXMLStr(map<string,string> param)
{
	string data = "";

	//使用param拼接xml格式的字符串
	CMarkupSTL xml;
	xml.AddElem("xml");
	xml.IntoElem();
	map<string,string>::iterator it = param.begin();
	for(; it != param.end(); it++)
	{
		xml.AddElem( it->first.c_str(), it->second.c_str() );
	}
	data = xml.GetDoc();

	return data;
}
