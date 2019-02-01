/*
 * DataPay.h
 *
 *  Created on: 2011-7-9
 *      Author: dada
 */

#ifndef DATAPAY_H_
#define DATAPAY_H_

#include "Kernel.h"

class CDataPay : public CDataBaseDBC
{
public:
	CDataPay(int table = DB_PAY) : CDataBaseDBC(table) {}

public:
	int AddPay(unsigned uid, unsigned cash);
	int SetPay(unsigned uid, unsigned cash);
	int GetPay(unsigned uid, unsigned &cash);
	int RemovePay(unsigned uid);

};

#endif /* DATAPAY_H_ */
