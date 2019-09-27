/*
 * LogicIdCtrl.h
 *
 *  Created on: 2015-9-9
 *      Author: Administrator
 */

#ifndef LOGICIDCTRL_H_
#define LOGICIDCTRL_H_

#include "Kernel.h"
#include "DataInc.h"

class CLogicIdCtrl {
public:
	int GetNextId(int key, uint32_t &nextId, uint32_t serverId);
	int GetNextId(int key, uint32_t &nextId, uint32_t getCount, uint32_t serverId);
	int GetCurrentId(int key, uint32_t &currId, uint32_t serverId);
};

#endif /* LOGICIDCTRL_H_ */
