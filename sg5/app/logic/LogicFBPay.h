#ifndef __LOGIC_FB_PAY_H__
#define __LOGIC_FB_PAY_H__

#include "LogicInc.h"

struct FBItemInfo
{
	unsigned item_id;
	string title;						//默认的标题
	string description;					//默认的描述
	string image_url;
	string product_url;
	unsigned price;
	unsigned cash;
	map<string, string> titleMap;		//标题map,与locale有关
	map<string, string> descMap;
};

class CLogicFBPay
{
public:
    /*
	int payments_get_items(
			const string &openid,
			const string &orderId,
			unsigned itemId,
			const string &locale,
			FBItemInfo &itemInfo);

	int payments_status_update(
			const string &openid,
			const string &orderId,
			const string &status,
			string &next_state);
	*/

	int deliver_no_serverid(
	        const string &openid,
	        const string &payment_id,
	        const string &product,
	        const unsigned quantity);

	int deliver_serverid(
	        const string &openid,
	        const unsigned serverid,
	        const string &payment_id,
	        const string &product,
	        const unsigned quantity);

	int chargeback(
			const string &openid,
			const unsigned serverid,
			const string &payment_id,
			const unsigned quantity);

private:
	int deliver(
	        const unsigned uid,
	        const string &openid,
	        const string &payment_id,
	        const string &product,
	        const unsigned quantity);

    static int GetItemInfo(
            const string &product,
            const string &locale,
            FBItemInfo &item);

	static int Init();
	int PayRewarld(unsigned uid, int cash, int &coins);

	typedef map<string, FBItemInfo> T_ItemMap;
	static T_ItemMap g_ItemInfo;
};

#endif
