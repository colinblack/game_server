/*
 * DataRward.h
 *
 *  Created on: 2019年7月19日
 *      Author: colin
 */

#ifndef APP_DATA_DATAREWARD_H_
#define APP_DATA_DATAREWARD_H_

#include "Kernel.h"

#define  TARGET_GOTS_SIZE 5
#define  LEVEL_REWARDS_SIZE 15


struct DataReward{
	uint32_t uid;
	uint32_t free_count;
	uint32_t today_is_sign;
	uint32_t sign_num;
	char  target_gots[TARGET_GOTS_SIZE];
	uint32_t sign_ts;
	char  level_rewards_flags[LEVEL_REWARDS_SIZE];

	DataReward(){
		uid = 0;
		free_count = 0;
		today_is_sign = 0;
		sign_num = 0;
		memset(target_gots, 0, TARGET_GOTS_SIZE);
		sign_ts = 0;
		memset(level_rewards_flags, 0, LEVEL_REWARDS_SIZE);
	}


	bool Encode(IBuffer *buff) const {
		PACKET_ENCODE_BEGIN(buff);
		PACKET_ENCODE(UInt32, uid);
		PACKET_ENCODE(UInt32, free_count);
		PACKET_ENCODE(UInt32, today_is_sign);
		PACKET_ENCODE(UInt32, sign_num);
		for(int i= 0; i < TARGET_GOTS_SIZE; ++i)
		{
			PACKET_ENCODE(Byte, target_gots[i]);
		}
		PACKET_ENCODE(UInt32, sign_ts);
		for(int i= 0; i < LEVEL_REWARDS_SIZE; ++i)
		{
			PACKET_ENCODE(Byte, level_rewards_flags[i]);
		}
		return true;
	}

	bool Decode(IBuffer *buff) {
		PACKET_DECODE_BEGIN(buff);
		PACKET_DECODE(UInt32, uid);
		PACKET_DECODE(UInt32, free_count);
		PACKET_DECODE(UInt32, today_is_sign);
		PACKET_DECODE(UInt32, sign_num);
		for(int i = 0; i < TARGET_GOTS_SIZE; ++i)
		{
			PACKET_DECODE(Byte, *(unsigned char*)(&target_gots[i]));
		}

		PACKET_DECODE(UInt32, sign_ts);
		for(int i= 0; i < LEVEL_REWARDS_SIZE; ++i)
		{
			PACKET_DECODE(Byte, *(unsigned char*)(&level_rewards_flags[i]));
		}

		return true;
	}

};


class CDataReward: public CDataBaseDBC {
public:
	CDataReward(int table = DB_REWARD):CDataBaseDBC(table) {
	}
	int AddData(const DataReward &data);
	int SetData(const DataReward &data);
	int RepData(const DataReward &data);
	int DelData(const DataReward &data);
	int GetData(uint32_t uid, DataReward &data);
	int GetData(uint32_t uid, vector<DataReward> &datas);
};


#endif /* APP_DATA_DATAREWARD_H_ */
