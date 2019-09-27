#ifndef DATA_CHARGE_HISTORY_H_
#define DATA_CHARGE_HISTORY_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataChargeHistory {
	uint32_t uid;
	uint32_t ts;
	uint32_t cash;
	uint32_t cost;

	DataChargeHistory() : uid(0), ts(0), cash(0), cost(0) {
	}

	bool Encode(CBufferWriter &writer) const {
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, ts);
		PACKET_ENCODE(UInt32, cash);
		PACKET_ENCODE(UInt32, cost);
		return true;
	}

	bool Decode(CBufferReader &reader) {
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, ts);
		PACKET_DECODE(UInt32, cash);
		PACKET_DECODE(UInt32, cost);
		return true;
	}
};

class CDataChargeHistory: public CDataBaseDBC, public AsyncDBInterface {
public:
	CDataChargeHistory(int table = DB_CHARGE_HISTORY): CDataBaseDBC(table) {
	}
	void doRequest(CNetPacket* p);
	int Get(uint32_t uid, uint32_t ts, DataChargeHistory &data);
	int Get(uint32_t uid, vector<DataChargeHistory> &data);
	int Add(const DataChargeHistory &data);
	int Set(const DataChargeHistory &data);
	int Del(uint32_t uid, uint32_t ts);

	int Add(CNetPacket* p);
	int Set(CNetPacket* p);
	int Del(CNetPacket* p);
};

#endif //DATA_CHARGE_HISTORY_H_
