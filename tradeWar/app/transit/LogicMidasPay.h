/*
 * LogicMidasPay.h
 *
 *  Created on: 2018年11月19日
 *      Author: Administrator
 */

#ifndef LOGIC_MIDAS_PAY_H_
#define LOGIC_MIDAS_PAY_H_

#include "Kernel.h"

class CLogicMidasPay {
public:
	enum {
		TOKEN_ERR = 40001
	};
	CLogicMidasPay();
	virtual ~CLogicMidasPay();

	static bool GetToken(const string &url, const string &appid, const string &appkey, const string &pf, string &token);
	static bool ResetToken();
	static void Sign(map<string, string> &params, const string &appkey, const string &openkey, const string &pf, const string &token, const string &api, const string &method);
	static void QQCallBackSign(map<string, string> &params, const string &appkey, const string &api, const string &method);
	static void StrToHex(const string &in, string &out);
private:
	static ThreadMutex m_tokenMutex;
	static string m_token;
	static uint32_t m_ts;
};

#endif /* LOGIC_MIDAS_PAY_H_ */
