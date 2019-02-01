/*
 * LogicKaixinPay.h
 *
 *  Created on: 2012-2-6
 *      Author: dada
 */

#ifndef LOGICKAIXINPAY_H_
#define LOGICKAIXINPAY_H_

#include "LogicInc.h"

class CLogicKaixinPay
{
public:
	int Order(unsigned uid, int type, int cash, int price, uint64_t &payId);
	int Pay(unsigned uid, uint64_t payId, const string &channelPayId);
	bool CheckSignature(const map<string, string> &params, const string &key, const string &signature);
protected:
	bool GetItem(int type, int &cash, int &price);
};

#endif /* LOGICKAIXINPAY_H_ */
