/*
 * GateEnemyConfig.h
 *
 *  Created on: 2019年4月23日
 *      Author: Administrator
 */

#ifndef GATE_ENEMY_CONFIG_H_
#define GATE_ENEMY_CONFIG_H_

#include "Kernel.h"

class GateEnemyConfig {
	SINGLETON_CLASS(GateEnemyConfig);
	bool init(const string &path);
	uint32_t getData(uint32_t id);
private:
	map<uint32_t, uint32_t> m_data;
};

#endif /* GATE_ENEMY_CONFIG_H_ */
