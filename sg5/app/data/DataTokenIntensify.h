/*
 * DataTokenIntensify.h
 *
 *  Created on: 2017-2-13
 *      Author: dawx62fac
 */

#ifndef DATATOKENINTENSIFY_H_
#define DATATOKENINTENSIFY_H_

#include <stdexcept>
#include "Kernel.h"


struct ShTokenIntensify
{
	enum {
		ITEMS_CNT = 12,
	};

public:
	void 		Accumulaive(int index, unsigned cnt = 1);
	unsigned 	GetExchangeCnt(int index);
	void 		Reset();

	unsigned index_cnt_[ITEMS_CNT];
	unsigned ts_;
};

class ShDataTokenIntensify
{
public:
	ShDataTokenIntensify();
	virtual ~ShDataTokenIntensify() {}

	int Init(const std::string &path, semdat sem=sem_token_intensify);

	void 		Accumulaive(int index, unsigned cnt = 1);
	unsigned 	GetExchangeCnt(int index);
	void 		Reset();
private:
	bool m_init;
	CShareMemory m_sh;
};



#endif /* DATATOKENINTENSIFY_H_ */
