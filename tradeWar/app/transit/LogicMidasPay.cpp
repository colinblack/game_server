/*
 * LogicMidasPay.cpp
 *
 *  Created on: 2018年11月19日
 *      Author: Administrator
 */

#include "LogicMidasPay.h"

ThreadMutex CLogicMidasPay::m_tokenMutex;
string CLogicMidasPay::m_token;
uint32_t CLogicMidasPay::m_ts = 0;

CLogicMidasPay::CLogicMidasPay() {
}

CLogicMidasPay::~CLogicMidasPay() {
}

bool CLogicMidasPay::GetToken(const string &url, const string &appid, const string &appkey, const string &pf, string &token) {
	if (0 != m_tokenMutex.acquire()) {
		return false;
	}
	if (m_ts > Time::GetGlobalTime()) {
		token = m_token;
		m_tokenMutex.release();
		return true;
	}
	string get_url;
	if (pf.find("QQmini") != string::npos) {
		get_url = "https://" + url + "/api/getToken?grant_type=client_credential&appid=" + appid + "&secret=" + appkey;
	}
	else {
		get_url = "https://" + url + "/cgi-bin/token?grant_type=client_credential&appid=" + appid + "&secret=" + appkey;
	}

	string resp;
	if (!Network::HttpGetRequest(resp, get_url)) {
		error_log("get request error, url=%s", get_url.c_str());
		m_tokenMutex.release();
		return false;
	}
	Json::Value obj;
	Json::Reader reader;
	if (!reader.parse(resp, obj)) {
		error_log("parse resp error, url=%s, resp=%s", get_url.c_str(), resp.c_str());
		m_tokenMutex.release();
		return false;
	}
	if (!Json::GetString(obj, "access_token", token)) {
		error_log("parse token error, url=%s, resp=%s", get_url.c_str(), resp.c_str());
		m_tokenMutex.release();
		return false;
	}

	int expires_in = 0;
	Json::GetInt(obj, "expires_in", expires_in);

	m_token = token;
	m_ts = expires_in + Time::GetGlobalTime();
	m_tokenMutex.release();
	return true;
}

bool CLogicMidasPay::ResetToken() {
	if (0 == m_tokenMutex.acquire()) {
		m_ts = 0;
		m_tokenMutex.release();
		return true;
	}
	return false;
}

void CLogicMidasPay::Sign(map<string, string> &params, const string &appkey, const string &openkey, const string &pf, const string &token, const string &api, const string &method) {
	if(pf.find("QQmini") != string::npos) {
		string sign_str = "";
		sign_str += method + "&";
		sign_str += Crypt::UrlEncode(api) + "&";
		for (map<string, string>::const_iterator itr = params.begin(); itr != params.end(); ++itr) {
			sign_str += itr->first + "=" + itr->second + "&";
		}
		sign_str += "session_key=" + openkey;

		string sig;
		StrToHex(Crypt::HmacSha256(sign_str, openkey), sig);
		params["sig"] = sig;
		params["access_token"] = token;
		debug_log("sign_str=%s,sig=%s", sign_str.c_str(), sig.c_str());

	} else {
		string sign_str = "";
		for (map<string, string>::const_iterator itr = params.begin(); itr != params.end(); ++itr) {
			sign_str += itr->first + "=" + itr->second + "&";
		}
		sign_str += "org_loc=" + api + "&";
		sign_str += "method=" + method + "&";
		sign_str += "secret=" + appkey;
		string sig;
		StrToHex(Crypt::HmacSha256(sign_str, appkey), sig);
		params["sig"] = sig;
		params["access_token"] = token;

		debug_log("sign_str=%s,sig=%s", sign_str.c_str(), sig.c_str());

		sign_str.clear();
		for (map<string, string>::const_iterator itr = params.begin(); itr != params.end(); ++itr) {
			sign_str += itr->first + "=" + itr->second + "&";
		}
		sign_str += "org_loc=" + api + "&";
		sign_str += "method=" + method + "&";
		sign_str += "session_key=" + openkey;

		sig.clear();
		StrToHex(Crypt::HmacSha256(sign_str, openkey), sig);
		debug_log("sign_str=%s,sig=%s", sign_str.c_str(), sig.c_str());
		params["mp_sig"] = sig;
	}
}

void CLogicMidasPay::QQCallBackSign(map<string, string> &params, const string &appkey, const string &api, const string &method) {
	string sign_str = "";
	sign_str += method + "&";
	sign_str += Crypt::UrlEncode(api) + "&";
	for (map<string, string>::const_iterator itr = params.begin(); itr != params.end(); ++itr) {
		sign_str += itr->first + "=" + itr->second + "&";
	}
	sign_str += "AppSecret=" + appkey;

	string sig;
	StrToHex(Crypt::HmacSha256(sign_str, appkey), sig);
	params["checkSig"] = sig;
	debug_log("sign_str=%s,sig=%s", sign_str.c_str(), sig.c_str());
}

void CLogicMidasPay::StrToHex(const string &in, string &out) {
	static const char* table = "0123456789abcdef";
	size_t len = in.length();
	out.clear();
	out.reserve(2 * len);
	for (size_t i = 0; i < len; ++i) {
		char c = in[i];
		out.push_back(table[(c & 0xF0) >> 4]);
		out.push_back(table[c & 0x0F]);
	}
}
