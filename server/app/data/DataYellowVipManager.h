/*
 * DataYellowVipManager.h
 *
 *  Created on: 2016-9-21
 *      Author: city
 */

#ifndef DATA_YELLOWVIP_MANAGER_H_
#define DATA_YELLOWVIP_MANAGER_H_

#include "Kernel.h"
#include "DataYellowVip.h"

class DataYellowVipManager : public DataSingleton<DataYellowVip, DB_YELLOW_VIP, DB_BASE_BUFF*DB_YELLOWVIP_FULL, CDataYellowVip, DB_YELLOWVIP_FULL>, public CSingleton<DataYellowVipManager>
{
private:
	friend class CSingleton<DataYellowVipManager>;
	DataYellowVipManager(){};
	virtual ~DataYellowVipManager(){}

	map<unsigned, unsigned> m_map;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int AddBuff(DataYellowVip & datayellowvip);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataYellowVip& Get(unsigned uid);
	bool IsDataYellowVipExists(unsigned uid);

	bool UpdateDataYellowVip(unsigned index);

	bool UpdateDataYellowVip(DataYellowVip& datayellowvip);
};

#endif /* DATA_YELLOWVIP_MANAGER_H_ */
