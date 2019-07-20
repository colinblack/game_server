/*
 * DataBagExtend.h
 *
 *  Created on: 2019年7月1日
 *      Author: Administrator
 */

#ifndef DATA_BAG_EXTEND_H_
#define DATA_BAG_EXTEND_H_

#include "Kernel.h"

struct DataBagExtend {
	uint32_t uid;
	uint16_t bag;
	uint16_t num;

	DataBagExtend() {
		uid = 0;
		bag = 0;
		num = 0;
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt16, bag);
		PACKET_ENCODE(UInt16, num);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt16, bag);
		PACKET_DECODE(UInt16, num);
		return true;
	}
};

class CDataBagExtend: public CDataBaseDBC {
public:
	CDataBagExtend(int table = DB_BAG_EXTEND) : CDataBaseDBC(table) {
	}
	int AddData(const DataBagExtend &data);
	int SetData(const DataBagExtend &data);
	int RepData(const DataBagExtend &data);
	int DelData(const DataBagExtend &data);
	int GetData(uint32_t uid, DataBagExtend &data);
	int GetData(uint32_t uid, vector<DataBagExtend> &datas);
};

#endif /* DATA_BAG_EXTEND_H_ */
