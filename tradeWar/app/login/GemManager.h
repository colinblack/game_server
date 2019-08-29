/*
 * GemManager.h
 *
 *  Created on: 2019年1月4日
 *      Author: Administrator
 */

#ifndef GEM_MANAGER_H_
#define GEM_MANAGER_H_

#include "IManager.h"
#include "DataInc.h"

#define GEM_POINT_NUM 4

class GemManager: public IManager {
public:
	GemManager();
	virtual ~GemManager();
	virtual bool doPacket(CNetPacket *packet);
	bool load(uint32_t uid);
	bool save(const DataGemPoint &data, bool isNew);
	bool push();
	bool encode(IBuffer *buff);
	bool encode(uint32_t type, IBuffer *buff);
	bool setPoint(uint32_t type, uint32_t point, uint32_t id);
	bool getGem(map<byte, uint32_t> &gem);
	uint32_t getPower();
	uint32_t getGemPower(uint32_t id);
	uint32_t getCount(uint32_t type);
protected:
	bool addCount(uint32_t type, uint32_t count);
private:
	map<uint32_t, DataGemPoint> m_data;
	uint32_t m_power;
	map<uint32_t, uint32_t> m_count;
};

#endif /* GEM_MANAGER_H_ */
