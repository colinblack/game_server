/*
 * DataYellowVipManager.h
 *
 *  Created on: 2016-9-21
 *      Author: city
 */

#ifndef DATA_MARKET_MANAGER_H_
#define DATA_MARKET_MANAGER_H_

#include "Kernel.h"
#include "DataMarket.h"

class DataMarketManager : public DataSingleton<DataMarket, DB_MARKET, DB_BASE_BUFF*DB_MARKET_FULL, CDataMarket, DB_MARKET_FULL>,
	public CSingleton<DataMarketManager>
{
private:
	friend class CSingleton<DataMarketManager>;
	DataMarketManager(){};
	virtual ~DataMarketManager(){}

	map<unsigned, unsigned> m_map;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int AddBuff(DataMarket & datamarket);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataMarket& Get(unsigned uid);
	bool IsDataMarketExists(unsigned uid);

	bool UpdateDataMarket(unsigned index);

	bool UpdateDataMarket(DataMarket& datamarket);
};

#endif /* DATA_MARKET_MANAGER_H_ */
