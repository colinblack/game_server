/*
 * DataIdCtrl.h
 *
 *  Created on: 2013-2-6
 *      Author: Administrator
 */

#ifndef DATA_ID_CTRL_H_
#define DATA_ID_CTRL_H_

#include "Kernel.h"

class CDataIdCtrl : public CDataBaseDBC
{
public:
	CDataIdCtrl(int table = DB_ID_CTRL) : CDataBaseDBC(table) {}

public:
	int SetId(int key, uint32_t sid, uint64_t curr_id);
	int GetId(int key, uint32_t sid, uint64_t &curr_id);
};

#endif /* DATA_ID_CTRL_H_ */
