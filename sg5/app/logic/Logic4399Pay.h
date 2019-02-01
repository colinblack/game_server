/*
 * Logic4399Pay.h
 *
 *  Created on: 2015-4-30
 *      Author: Ralf
 */

#ifndef LOGIC4399PAY_H_
#define LOGIC4399PAY_H_

#include "LogicInc.h"

class CLogic4399Pay
{
public:
	int deliver(
			const string &openid,
			unsigned serverid,
			unsigned count,
			const string &billno,
			unsigned money);
};


#endif /* LOGIC4399PAY_H_ */
