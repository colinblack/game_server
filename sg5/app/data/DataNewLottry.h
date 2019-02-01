/*
 * DataNewLottry.h
 *
 *  Created on: 2015-02-03
 *      Author: jimmy
 */

#ifndef CDATANEWLOTTERY_H___
#define CDATANEWLOTTERY_H___
#include "Kernel.h"
#define RARE_ITEMS_SIZE 10
#define RARE_ITEMS_NUM 3

struct RareItemsNumbers{                        //珍惜奖品已经得到数量
	unsigned id;
	unsigned over_num;

	RareItemsNumbers()
	{
		id = over_num = 0;
	}
};

struct RareItemsWinner{                    //抽到大奖的最新10个人
	unsigned uid;
	unsigned eqid;
	unsigned type_id;
	unsigned num;
	char name[32];

	RareItemsWinner()
	{
		uid = eqid = type_id = num = 0;
		memset(name,0,sizeof(name));
	}

};


struct DataNewlottery
{
	int version;						//活动版本控制
	unsigned winner_flag;
	RareItemsNumbers ItemsNumbers[RARE_ITEMS_NUM];
	RareItemsWinner ItemsWinner[RARE_ITEMS_SIZE];
	DataNewlottery()
	{
		version = winner_flag = 0;
	}
};

class CDataNewlottery {
public:
	CDataNewlottery();
	virtual ~CDataNewlottery();
	int Init(const std::string &path, semdat sem=sem_new_lottery);
	int GetRareItemsNumbers(vector <unsigned> id, vector <unsigned> total, vector <unsigned> &get_id, vector <unsigned> &get_total, vector <RareItemsWinner> &peoples);     //版本控制
	int GetNewLotteryActivity(unsigned uid, unsigned level, unsigned count, vector <unsigned> total, vector <unsigned> rate, vector <unsigned> id, vector <unsigned> type_id, vector <unsigned> eqid, vector <unsigned> num
			, vector <unsigned> &awards_id, vector <unsigned> &awards_eqid, vector <unsigned> &awards_typeid, vector <unsigned> &awards_num
			, vector <unsigned> &get_id, vector <unsigned> &over_num, vector <RareItemsWinner> &peoples);

private:
	bool m_init;
	CShareMemory m_sh;
};

#endif /* CDATANEWLOTTERY_H___ */
