#ifndef __LOGIC_VN_TEL_PAY_H__
#define __LOGIC_VN_TEL_PAY_H__

#include "LogicInc.h"

class CLogicVNTelPay
{
public:
	int deliver(
	        const unsigned uid,
	        const string &openid,
	        const string &payment_id,
	        const int vnd);
};

#endif
