/*
 * DataBattleReward.h
 *
 *  Created on: 2016-12-6
 *      Author: Ralf
 */

#ifndef DATABATTLEREWARD_H_
#define DATABATTLEREWARD_H_

#include "Kernel.h"

struct DataBattleReward
{
	uint32_t uid;
	uint32_t rts;
	uint32_t r;
	uint32_t ccd;
	uint32_t cts;
	uint8_t ctimes;

	DataBattleReward()
	{
		uid = rts = r = ccd = cts = ctimes = 0;
	}
	void SetMessage(ProtoBattleField::BattleReward *msg)
	{
		msg->set_rp(r);
		msg->set_ccd(ccd);
		msg->set_ctimes(ctimes);
	}
};

class CDataBattleReward :public DBCBase<DataBattleReward, DB_BATTLE_REWARD>
{
public:
	virtual int Get(DataBattleReward &data);
	virtual int Add(DataBattleReward &data);
	virtual int Set(DataBattleReward &data);
};



#endif /* DATABATTLEREWARD_H_ */
