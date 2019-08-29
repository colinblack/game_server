/*
 * SevenDaysConfig.h
 *
 *  Created on: 2018年9月7日
 *      Author: rein
 */

#ifndef _SEVEN_DAYS_CONFIG_H_
#define _SEVEN_DAYS_CONFIG_H_

#include "Kernel.h"
#include "Award.h"

struct SignReward {
	byte type;
	Award award;
};

class SevenDaysConfig {
	SINGLETON_CLASS(SevenDaysConfig);
public:
	bool init(const string &path);
	bool initSign(const string &path);
	const Award* getAward(byte id);
	const SignReward* getSign(byte id);
	uint32_t getCount();
private:
	map<byte, Award> m_data;
	map<byte, SignReward> m_sign;
};

#endif /* _SEVEN_DAYS_CONFIG_H_ */
