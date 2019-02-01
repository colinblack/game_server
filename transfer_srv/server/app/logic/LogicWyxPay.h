#ifndef __LOGIC_WYX_PAY_H__
#define __LOGIC_WYX_PAY_H__

#include "LogicInc.h"

class CLogicWyxPay
{
public:
	int WyxGenerateOrder(
			const string &openid,
			const string &openkey,
			int itemId,
			string &order_id,
			string &desc,
			int &amount,
			string &token
			);

	int WyxDeliverGood(
			const string &openid,
			const string &order_id,
			const string &appid,
			int amount
			);
};

#endif
