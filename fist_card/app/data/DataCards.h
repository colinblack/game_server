/*
 * DataCards.h
 *
 *  Created on: 2018年11月21日
 *      Author: colin
 */

#ifndef APP_DATA_DATACARDS_H_
#define APP_DATA_DATACARDS_H_

#include "Kernel.h"

struct DataCards{
	uint32_t uid;
	uint32_t id;
	uint32_t card_id;
	uint32_t star;

	DataCards(){
		uid = 0;
		id  = 0;
		card_id = 0;
		star = 0;
	}

	void SetMessage(ProtoCards::UserCardsCPP* msg) const
	{
		msg->set_ud(id);
		msg->set_cardid(card_id);
		msg->set_star(star);
	}
};

class CDataCards : public DBCBase<DataCards, DB_CARDS>
{
public:
	virtual int Get(DataCards &data);
	virtual int Get(vector<DataCards>&data);
	virtual int Add(DataCards &data);
	virtual int Set(DataCards &data);
	virtual int Del(DataCards &data);
};


#endif /* APP_DATA_DATACARDS_H_ */
