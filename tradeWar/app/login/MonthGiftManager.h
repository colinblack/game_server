/*
 * MonthGiftManager.h
 *
 *  Created on: 2019年1月2日
 *      Author: Administrator
 */

#ifndef MONTH_GIFT_MANAGER_H_
#define MONTH_GIFT_MANAGER_H_

#include "IManager.h"
class Award;

struct DataMonthGift {
	byte id;
	uint32_t end_ts;
	uint32_t reward_ts;

	DataMonthGift() {
		id = 0;
		end_ts = 0;
		reward_ts = 0;
	}
};

class MonthGiftManager: public IManager {
public:
	enum {
		MONTH_GIFT_FLAG_NONE = 0,
		MONTH_GIFT_FLAG_BUY = 1,
		MONTH_GIFT_FLAG_REWARD = 2
	};
	MonthGiftManager();
	virtual ~MonthGiftManager();
	virtual bool doPacket(CNetPacket* packet);
	bool load(uint32_t uid);
	bool save();
	bool push();
	bool buy(uint32_t id);
	bool doReward(CNetPacket* packet);
	bool onReward(byte ret, uint32_t lv, Award &reward, Award &box);
private:
	map<byte, DataMonthGift> m_data;
};

#endif /* MONTH_GIFT_MANAGER_H_ */
