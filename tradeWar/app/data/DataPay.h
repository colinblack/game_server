/*
 * DataPay.h
 *
 *  Created on: 2015年9月9日
 *      Author: asdf
 */

#ifndef SERVERS_APP_DATA_DATAPAY_H_
#define SERVERS_APP_DATA_DATAPAY_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataPay
{
	uint32_t uid;
	uint32_t cash;
	uint32_t coins;
//	uint32_t price;			// 充值Q点
//	uint32_t charge_cash;	// 充值钻石数
	DataPay()
	{
		uid = 0;
		cash = 0;
		coins = 0;
//		price = 0;
//		charge_cash = 0;
	}
};

class CDataPay : public CDataBaseDBC, public AsyncDBInterface
{
public:
	CDataPay(int table = DB_PAY) : CDataBaseDBC(table) {}
	virtual void doRequest(CNetPacket* packet);

	int GetPay(uint32_t uid, DataPay &pay);

	int AddPay(const DataPay &pay);
	int RealAddPay(CNetPacket* packet);

	int SetPay(const DataPay &pay);
	int RealSetPay(CNetPacket* packet);

	int ReplacePay(const DataPay& dataPay);
	int RealReplacePay(CNetPacket* packet);

	int RemovePay(uint32_t uid);
	int RealRemovePay(CNetPacket* packet);
};

#endif /* SERVERS_APP_DATA_DATAPAY_H_ */
