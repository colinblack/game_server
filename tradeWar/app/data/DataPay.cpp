/*
 * DataPay.cpp
 *
 *  Created on: 2015年9月9日
 *      Author: asdf
 */

#include "DataPay.h"
#include "AsyncDBManager.h"
#include "DataTableUidIdData.h"
#define OP_ADD_PAY 1
#define OP_UPDATE_PAY 2
#define OP_REMOVE_PAY 3
#define OP_REPLACE_PAY 4

#define DB_ENCODE_PAY_SERIES(dataPay, opId) \
	DB_ENCODE_BEGIN(DB_PAY, opId); \
	DB_ENCODE(UInt32,dataPay.uid); \
	DB_ENCODE(UInt32,dataPay.cash); \
	DB_ENCODE(UInt32,dataPay.coins); \
	DB_ENCODE_END;

#define DB_DECODE_PAY_SERIES(packet) \
	DataPay dataPay; \
	DB_DECODE_BEGIN(&packet->body); \
	DB_DECODE(UInt32,dataPay.uid); \
	DB_DECODE(UInt32,dataPay.cash); \
	DB_DECODE(UInt32,dataPay.coins); \
	DB_DECODE_END;
// get
int CDataPay::GetPay(uint32_t uid, DataPay &pay)
{
	DBCREQ_DECLARE(DBC::GetRequest, uid);
	DBCREQ_SET_KEY(uid);

	DBCREQ_NEED_BEGIN();
	DBCREQ_NEED(uid);
	DBCREQ_NEED(cash);
	DBCREQ_NEED(coins);

	DBCREQ_EXEC;
	DBCREQ_IFNULLROW;
	DBCREQ_IFFETCHROW;

	DBCREQ_GET_BEGIN();
	DBCREQ_GET_INT(pay, uid);
	DBCREQ_GET_INT(pay, cash);
	DBCREQ_GET_INT(pay, coins);
	return 0;
}
// add
int CDataPay::AddPay(const DataPay &dataPay)
{
	DB_ENCODE_PAY_SERIES(dataPay, OP_ADD_PAY)
	return 0;
}
int CDataPay::RealAddPay(CNetPacket* packet)
{
	DB_DECODE_PAY_SERIES(packet)

	DBCREQ_DECLARE(DBC::InsertRequest, dataPay.uid);
	DBCREQ_SET_KEY(dataPay.uid);
	DBCREQ_SET_INT(dataPay, cash);
	DBCREQ_SET_INT(dataPay, coins);
	DBCREQ_EXEC;
	return 0;
}
// set
int CDataPay::SetPay(const DataPay &dataPay)
{
	DB_ENCODE_PAY_SERIES(dataPay, OP_UPDATE_PAY)
	return 0;
}
int CDataPay::RealSetPay(CNetPacket* packet)
{
	DB_DECODE_PAY_SERIES(packet)

	DBCREQ_DECLARE(DBC::UpdateRequest, dataPay.uid);
	DBCREQ_SET_KEY(dataPay.uid);
	DBCREQ_SET_INT(dataPay, cash);
	DBCREQ_SET_INT(dataPay, coins);
	DBCREQ_EXEC;
	return 0;
}
// replace
int CDataPay::ReplacePay(const DataPay& dataPay)
{
	DB_ENCODE_PAY_SERIES(dataPay, OP_REPLACE_PAY)
	return 0;
}
int CDataPay::RealReplacePay(CNetPacket* packet)
{
	DB_DECODE_PAY_SERIES(packet)

	DBCREQ_DECLARE(DBC::ReplaceRequest, dataPay.uid);
	DBCREQ_SET_KEY(dataPay.uid);
	DBCREQ_SET_INT(dataPay, cash);
	DBCREQ_SET_INT(dataPay, coins);
	DBCREQ_EXEC;
	return 0;
}

// remove
REMOVE_ITEM_KEY1(Pay, PAY, UInt32, uid)
REAL_REMOVE_ITEM_KEY1(Pay, UInt32, uid)

///////////////////////
OP_PROCESS_BEGIN(CDataPay)
OP_PROCESS(OP_ADD_PAY, RealAddPay)
OP_PROCESS(OP_UPDATE_PAY, RealSetPay)
OP_PROCESS(OP_REMOVE_PAY, RealRemovePay)
OP_PROCESS(OP_REPLACE_PAY, RealReplacePay)
OP_PROCESS_END

