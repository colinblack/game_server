/*
 * DataUnlockCards.h
 *
 *  Created on: 2018年11月23日
 *      Author: colin
 */

#ifndef APP_DATA_DATAUNLOCKCARDS_H_
#define APP_DATA_DATAUNLOCKCARDS_H_

#include "Kernel.h"

struct DataUnlockCards{
	uint32_t	uid;
	uint32_t	id;

	DataUnlockCards(){
		uid = 0;
		id  = 0;
	}

	void SetMessage(ProtoCards::UnlockCardsCPP* msg) const
	{
		msg->set_id(id);
	}
};

class CDataUnlockCards : public DBCBase<DataUnlockCards, DB_UNLOCK_CARDS>
{
public:
	virtual int Get(DataUnlockCards &data);
	virtual int Get(vector<DataUnlockCards>&data);
	virtual int Add(DataUnlockCards &data);
	virtual int Set(DataUnlockCards &data);
	virtual int Del(DataUnlockCards &data);
};




#endif /* APP_DATA_DATAUNLOCKCARDS_H_ */
