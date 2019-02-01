#ifndef __LOGIC_QQ_PAY_H__
#define __LOGIC_QQ_PAY_H__

#include "LogicInc.h"

#define MARKET_QUEST_STEP_1 0x01
#define MARKET_QUEST_STEP_2 0x02
#define MARKET_QUEST_STEP_3 0x04
#define MARKET_QUEST_STEP_4 0x08

struct QQItemInfo
{
	string itemid;
	string name;
	string description;
	string url;
	int price;
	int type;
	int cash;
};

class CLogicQQPay
{
public:
	int qz_buy_goods(
			const string &openid,
			const string &openkey,
			const string &userip,
			const string &itemid,
			string &appid,
			string &url_params);

	int deliver(
			const string &appid,
			const string &openid,
			const string &payitem,
			int amt,
			const string &billno);

	int v3_buy_goods(
			const string &pf,
			const string &pfkey,
			const string &openid,
			const string &openkey,
			const string &userip,
			const string &itemid,
			string &appid,
			string &url_params);
	int PayRewarld(unsigned uid, int cash, int &coins);

	int InformTaskCompleted(
			const string &pf,
			const string &pfkey,
			const string &openid,
			const string &openkey,
			string &zoneid,
			string &appid,
			string &contractid);
	int CheckTask(const string &appid, const string &openid, const string &contractid, const string &cmd, int step, unsigned eqid, const string &billno, unsigned &zoneid);
	int ReqQQPanel(const string &pf,
			const string &pfkey,
			const string &openid,
			const string &openkey,
			string &userip,
			string &appid);
	int v3_pay_get_token(const string &pfkey,
			const string &pf,
			const string &openkey,
			const string &openid,
			const string &tokentype,
			const string &discountid,
			string &appid,
			string &token,
			string &zoneid);

	int vip_charge_deliver(const string &appid,
			const string &openid,
			const string &payitem);

	int blue_year_charge_deliver(const string &appid,
				const string &openid,
				const string &payitem);

private:
	static int GetItemInfo(
			const string &itemid,
			QQItemInfo &item);

	typedef map<string, QQItemInfo> T_ItemMap;
	static T_ItemMap g_ItemInfo;
};

#endif
