/*
 * InteractManager.h
 *
 *  Created on: 2019年3月5日
 *      Author: Administrator
 */

#ifndef INTERACT_MANAGER_H_
#define INTERACT_MANAGER_H_

#include "IManager.h"
#include "DataUserInteract.h"

class InteractManager: public IManager {
public:
	InteractManager();
	~InteractManager();
	bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool getData(IBuffer *buff);
	bool setData(uint32_t uid, uint32_t lv, uint32_t type, const string &name, const string &pic);
	bool checkDaily(uint32_t uid);
	bool reset();
private:
	vector<DataUserInteract> m_data;
	set<uint32_t> m_daily;
	uint32_t m_ts;
};

#endif /* INTERACT_MANAGER_H_ */
