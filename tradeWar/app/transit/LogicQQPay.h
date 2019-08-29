#ifndef _LOGIC_QQ_PAY_H_
#define _LOGIC_QQ_PAY_H_

#include "TransitInc.h"
#include "OpenPlatform.h"

struct QQItemInfo {
	uint32_t id;
	uint32_t pt;
	uint32_t cash;
	uint32_t price;
	string itemid;

	QQItemInfo() :
			id(0), pt(0), cash(0), price(0) {
	}
};

class CLogicQQPay {
public:
	CLogicQQPay();
	virtual ~CLogicQQPay();
	static int v3_get_playzone_userinfo(const string opid, const string &opkey, const string &pf, const string &zone, const string &ip, int32_t &score);
	static int v3_buy_playzone_item(const string &opid, const string &opkey, const string &pf, const string &zone, const string &ip, uint32_t id, uint32_t count, string &strBillno, uint32_t &cash, uint32_t &cost);
	static int GetItemInfo(uint32_t id, uint32_t osPlatform, QQItemInfo &item);
	static int formatUrl(const map<string, string> &param, const string &appkey, const string &api, string &url);
};

#endif /*_LOGIC_QQ_PAY_H_*/
