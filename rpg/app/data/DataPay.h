/*
 * DataPay.h
 *
 *  Created on: 2019年6月20日
 *      Author: Administrator
 */

#ifndef DATA_PAY_H_
#define DATA_PAY_H_

#include "Kernel.h"

struct DataPay {
	uint32_t uid;
	uint32_t id;
	uint32_t num;

	DataPay(){
		uid = 0;
		id = 0;
		num = 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(UInt32, num);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, num);
		return true;
	}
};

class CDataPay: public CDataBaseDBC {
public:
	CDataPay(int table = DB_PAY): CDataBaseDBC(table) {
	}
	int AddData(const DataPay &data);
	int SetData(const DataPay &data);
	int RepData(const DataPay &data);
	int DelData(const DataPay &data);
	int GetData(uint32_t uid, DataPay &data);
	int GetData(uint32_t uid, vector<DataPay> &datas);
};

#endif /* APP_DATA_DATAPAY_H_ */
