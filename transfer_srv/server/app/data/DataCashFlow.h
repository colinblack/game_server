/*
 * DataCashFlow.h
 *
 *  Created on: 2011-12-31
 *      Author: dada
 */

#ifndef DATACASHFLOW_H_
#define DATACASHFLOW_H_

#include "Kernel.h"

struct DataCashFlow
{
	unsigned uid;
	uint64_t flow_id;
	string type;
	int count;
	int cash;
	unsigned balance;
	unsigned time;
	unsigned data;
};

class CDataCashFlow : public CDataBaseDBC
{
public:
	CDataCashFlow(int table = DB_CASH_FLOW) : CDataBaseDBC(table) {}

	int AddCashFlow(const DataCashFlow &flow);
	int GetCashFlows(unsigned uid, unsigned startTime, unsigned endTime, vector<DataCashFlow> &flows);
};

#endif /* DATACASHFLOW_H_ */
