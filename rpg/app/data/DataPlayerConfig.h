/*
 * DataPlayerConfig.h
 *
 *  Created on: 2019年8月10日
 *      Author: Administrator
 */

#ifndef DATA_PLAYER_CONFIG_H_
#define DATA_PLAYER_CONFIG_H_

#include "Kernel.h"

struct DataPlayerConfig {
	uint32_t uid;
	uint32_t id;
	string data;

	DataPlayerConfig() {
		uid = 0;
		id = 0;
		data.clear();
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, id);
		PACKET_ENCODE(String, data);
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(String, data);
		return true;
	}
};

class CDataPlayerConfig: public CDataBaseDBC {
public:
	CDataPlayerConfig(int table = DB_PLAYER_CONFIG) : CDataBaseDBC(table) {
	}
	int AddData(const DataPlayerConfig &data);
	int SetData(const DataPlayerConfig &data);
	int RepData(const DataPlayerConfig &data);
	int DelData(const DataPlayerConfig &data);
	int GetData(uint32_t uid, DataPlayerConfig &data);
	int GetData(uint32_t uid, vector<DataPlayerConfig> &datas);
};

#endif /* DATA_PLAYER_CONFIG_H_ */
