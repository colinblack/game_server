/*
 * DataBarbarianKing.h
 *
 *  Created on: 2014-4-3
 *      Author: dawx123
 */

#ifndef DATABARBARIANKING_H_
#define DATABARBARIANKING_H_
#include "Kernel.h"

#define BK_MAX 300
#define BK_GROUP_MAX 3

struct BKChallenger
{
	unsigned uid;
	unsigned serverid;
	unsigned point;
	char name[32];
};
struct DataBarbarianKing
{
	unsigned minIndex;
	unsigned num;
	unsigned startTS;
	BKChallenger challenger[BK_MAX];
};

class CDataBarbarianKing
{
public:
	CDataBarbarianKing();
	virtual ~CDataBarbarianKing();
	int Init(const std::string &path, semdat sem=sem_barbarian_king);
	int GetBKList(unsigned group, vector<BKChallenger> &challenger);
	int SetBKChallenger(unsigned group, BKChallenger &challenger);
	int SetReward(unsigned group);

protected:
	bool m_init;
	CShareMemory m_sh[BK_GROUP_MAX];
};


#endif /* DATABARBARIANKING_H_ */
