/*
 * DataVipCharge.h
 *
 *  Created on: 2014-3-6
 *      Author: dada
 */

#ifndef DATAVIPCHARGE_H_
#define DATAVIPCHARGE_H_

#include "Kernel.h"

class CDataVipCharge : public CDataBaseDBC
{
public:
	CDataVipCharge(int table = DB_VIP_CHARGE) : CDataBaseDBC(table) {}

public:
	int AddVipCharge(const string &openid, int total,int used);
	int UpdateVipChargeUsed(const string &openid,int total,int used);
	int GetVipCharge(const string &openid, int &total,int &used,unsigned &updatetime);
	int AddBlueYearVipCharge(const string &openid, int hero_total,int hero_used);
	int UpdateBlueYearVipChargeUsed(const string &openid,int hero_total,int hero_used);
	int GetBlueYearVipCharge(const string &openid, int &hero_total,int &hero_used);
};

#endif /* DATAVIPCHARGE_H_ */
