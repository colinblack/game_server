/*
 * PayConfig.h
 *
 *  Created on: 2018年11月9日
 *      Author: Administrator
 */

#ifndef PAY_CONFIG_H_
#define PAY_CONFIG_H_

#include "Kernel.h"

struct PayItem {
	uint32_t id;
	uint32_t money;
	uint16_t type;
	uint32_t gift;

	PayItem() {
		id = 0;
		money = 0;
		type = 0;
		gift = 0;
	}
};

enum PayType {
	PayTypeDiamond = 1,     //钻石
	PayTypeVip = 2,         //vip月卡
	PayTypeSpecial = 3,     //特别优惠
	PayTypeSevenTask = 4,   //全民庆典活动
	PayTypeDailyCharge = 5, //每日首充
	PayTypeMonthGift = 6,   //宝箱
	PayTypeMax
};

class PayConfig {
	SINGLETON_CLASS(PayConfig);
	bool init();
	const PayItem* getItem(uint32_t id) const;
private:
	map<uint32_t, PayItem> m_data;
};

#endif /* PAY_CONFIG_H_ */
