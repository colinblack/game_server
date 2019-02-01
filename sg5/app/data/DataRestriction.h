/*
 * DataRestriction.h
 *
 *  Created on: 2015-03-18
 *      Author: jimmy
 */

#ifndef CDATARESTRICTION_H___
#define CDATARESTRICTION_H___
#include "Kernel.h"
#define RESTRIC_ITEMS_NUM 8

struct DataRestric
{
	unsigned version;						//活动版本控制
	unsigned ts;
	unsigned ItemsNumbers[RESTRIC_ITEMS_NUM];
	DataRestric()
	{
		version = ts = 0;
		memset(&ItemsNumbers, 0, sizeof(ItemsNumbers));
	}
};

class CDataRestric {
public:
	CDataRestric();
	~CDataRestric();
	int Init(const std::string &path, semdat sem=sem_restriction);
	int GetRestricItemsNum(vector <unsigned> &num);     //版本控制
	int UpdateRare(unsigned id, vector <unsigned> &num, bool &flag);

private:
	bool m_init;
	CShareMemory m_sh;
	static const unsigned max_num[RESTRIC_ITEMS_NUM];
};

#endif /* CDATARESTRICTION_H___ */
