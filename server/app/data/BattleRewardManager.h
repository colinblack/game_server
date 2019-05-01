/*
 * BattleRewardManager.h
 *
 *  Created on: 2016-12-6
 *      Author: Ralf
 */

#ifndef BATTLEREWARDMANAGER_H_
#define BATTLEREWARDMANAGER_H_

#include "Kernel.h"
#include "DataBattleReward.h"
#include "DataInc.h"

class BattleRewardManager : public DataSingleton<DataBattleReward, DB_BATTLE_REWARD, DB_BASE_BUFF*DB_BASE_FULL, CDataBattleReward, DB_BASE_FULL>, public CSingleton<BattleRewardManager>
{
private:
	friend class CSingleton<BattleRewardManager>;
	BattleRewardManager(){};
	virtual ~BattleRewardManager(){}

	map<unsigned, unsigned> m_map;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();

	int CheckBuff(unsigned uid);
	int AddBuff(unsigned uid);
	int LoadBuff(unsigned uid);
	unsigned GetIndex(unsigned uid);
	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	void OnLogin(unsigned uid);
};

#endif /* BATTLEREWARDMANAGER_H_ */
