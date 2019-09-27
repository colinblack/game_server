/*
 * FeteConfig.h
 *
 *  Created on: 2016年4月13日
 *      Author: Administrator
 */

#ifndef FETECONFIG_H_
#define FETECONFIG_H_
#include "Kernel.h"
struct FetConfig{
	byte bj;
	uint32_t weight;
	FetConfig():bj(0),weight(0)
	{

	}
};
class CFeteConfig {
public:
	virtual ~CFeteConfig();
	static CFeteConfig *getInstance()
	{
		static CFeteConfig ins;
		return &ins;
	}
public:
	bool init(const string &paht);
	byte getBj();
private:
	CFeteConfig();
private:
	uint32_t m_totalWeight;
	vector<FetConfig> m_config;
};

#endif /* FETECONFIG_H_ */
