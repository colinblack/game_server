/*
 * DataDragonScaleGiftBag.h
 *
 *  Created on: 2015-06-16
 *      Author: eddard
 */

#ifndef CDATADRAGONSCALEGIFTBAG_H___
#define CDATADRAGONSCALEGIFTBAG_H___
#include "Kernel.h"

#define GIFT_BAG_MAX	5

struct DataDragonScaleWinner
{
	unsigned uid;
	char name[32];
};

struct DataDragonScaleGiftBag
{
	int version;						//活动版本控制
	int count;
	DataDragonScaleWinner winners[GIFT_BAG_MAX];

	DataDragonScaleGiftBag()
	{
		version = count = 0;
		memset(winners, 0, sizeof(winners));
	}
};

class CDataDragonScaleGiftBag {
public:
	CDataDragonScaleGiftBag();
	virtual ~CDataDragonScaleGiftBag();
	int Init(const std::string &path, semdat sem=sem_dragon_scale_gift_bag);
	int GetGiftBag(unsigned uid, Json::Value &winners, int &count, bool &succ);
	int GetData(unsigned uid, Json::Value &winners, unsigned &count);
private:
	bool m_init;
	CShareMemory m_sh;
};


#endif //CDATADRAGONSCALEGIFTBAG_H___
