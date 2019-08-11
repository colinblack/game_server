/*
 * DataTrump.h
 *
 *  Created on: 2019年7月24日
 *      Author: colin
 */

#ifndef APP_DATA_DATATRUMP_H_
#define APP_DATA_DATATRUMP_H_

#include "Kernel.h"


#define ACTIVE_TRUMP_SKILL_COUNT 15

struct DataTrump {
	uint32_t uid;
	uint32_t unlock;
	uint32_t active_count;
	uint32_t current_fight;
	char active_map[ACTIVE_TRUMP_SKILL_COUNT];

	DataTrump() {
		uid = 0;
		unlock = 0;
		active_count = 0;
		current_fight = 0;
		memset(active_map, 0,sizeof(active_map));
	}

	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, unlock);
		PACKET_ENCODE(UInt32, active_count);
		PACKET_ENCODE(UInt32, current_fight);
		for(int i = 0; i < ACTIVE_TRUMP_SKILL_COUNT; ++i){
			PACKET_ENCODE(Byte, active_map[i]);
		}

		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, unlock);
		PACKET_DECODE(UInt32, active_count);
		PACKET_DECODE(UInt32, current_fight);
		for(int i= 0; i < ACTIVE_TRUMP_SKILL_COUNT; ++i){
			PACKET_DECODE(Byte, *(unsigned char*)(&active_map[i]));
		}

		return true;
	}
};

class CDataTrump: public CDataBaseDBC {
public:
	CDataTrump(int table = DB_TRUMP): CDataBaseDBC(table) {
	}
	int AddData(const DataTrump &data);
	int SetData(const DataTrump &data);
	int RepData(const DataTrump &data);
	int DelData(const DataTrump &data);
	int GetData(uint32_t uid, DataTrump &data);
	int GetData(uint32_t uid, vector<DataTrump> &datas);
};


#endif /* APP_DATA_DATATRUMP_H_ */
