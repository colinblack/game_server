/*
 * DataCumulationLoginManager.h
 *
 *  Created on: 2016-10-12
 *      Author: city
 */

#ifndef DATA_FRIEND_GIFT_MANAGER_H_
#define DATA_FRIEND_GIFT_MANAGER_H_

#include "Kernel.h"
#include "DataFriendGift.h"

class DataFriendGiftManager : public DataSingleton<DataFriendGift, DB_FRIEND_GIFT, DB_BASE_BUFF*DB_BASE_FULL, CDataFriendGift, DB_BASE_FULL>,
	public CSingleton<DataFriendGiftManager>
{
private:
	friend class CSingleton<DataFriendGiftManager>;
	DataFriendGiftManager(){};
	virtual ~DataFriendGiftManager(){}

	map<unsigned, unsigned> m_map;
	static const int MAX_INDEX = DB_BASE_BUFF*DB_BASE_FULL;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int New(unsigned uid);

	int CheckBuff(unsigned uid);
	int AddBuff(DataFriendGift & friendgift);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataFriendGift& GetFriendGift(unsigned uid);

	bool UpdateDataFriendGift(DataFriendGift& friendgift);
};

#endif /* DATA_FRIEND_GIFT_MANAGER_H_ */
