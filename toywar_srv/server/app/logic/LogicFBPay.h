#ifndef __LOGIC_FB_PAY_H__
#define __LOGIC_FB_PAY_H__

#include "LogicInc.h"

struct FBItemInfo
{
	unsigned item_id;
	string title;
	string description;
	string image_url;
	string product_url;
	unsigned price;
	unsigned cash;
};

class CLogicFBPay
{
public:
	int payments_get_items(
			const string &openid,
			const string &orderId,
			unsigned itemId,
			FBItemInfo &itemInfo);

	int payments_status_update(
			const string &openid,
			const string &orderId,
			const string &status,
			string &next_state);

private:
	static int GetItemInfo(
			unsigned item_id,
			FBItemInfo &item);

	typedef map<unsigned, FBItemInfo> T_ItemMap;
	static T_ItemMap g_ItemInfo;
};

#endif
