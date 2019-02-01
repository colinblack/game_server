#ifndef  LOGICTWPAY_INC
#define  LOGICTWPAY_INC

#include "LogicInc.h"

class CLogicTWPay
{
public:
	int deliver(
	        const string &openid,
	        const unsigned serverid,
	        const string &payment_id,
	        const string &product,
	        const unsigned quantity);

private:
	int PayRewarld(unsigned uid, int cash, int &coins);
};


#endif

