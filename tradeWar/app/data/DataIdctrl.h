/*
 * DataIdctrl.h
 *
 *  Created on: 2015-9-9
 *      Author: Administrator
 */

#ifndef DATA_IDCTRL_H_
#define DATA_IDCTRL_H_

#include "Kernel.h"

class CDataIdCtrl: public CDataBaseDBC {
public:
	CDataIdCtrl(int table = DB_ID_CTRL): CDataBaseDBC(table) {
	}
public:
	int SetId(int key, uint32_t curr_id, uint32_t serverid);
	int GetId(int key, uint32_t &curr_id, uint32_t serverid);
};

#endif /* DATA_IDCTRL_H_ */
