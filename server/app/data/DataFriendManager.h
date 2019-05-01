#ifndef DATA_FRIEND_MANAGER_H_
#define DATA_FRIEND_MANAGER_H_

#include "Kernel.h"
#include "DataFriend.h"

class DataFriendManager : public DataSingleton<DataFriend, DB_FRIEND, DB_BASE_BUFF*DB_FRIEND_FULL, CDataFriend, DB_FRIEND_FULL>,
	public CSingleton<DataFriendManager>
{
private:
	friend class CSingleton<DataFriendManager>;
	DataFriendManager(){};
	virtual ~DataFriendManager(){}

	typedef map<uint32_t, map<uint32_t, uint32_t> > MapMap;  //uid->frienduid =>index
	typedef map<uint32_t, map<uint32_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int CheckBuff(unsigned uid);
	int AddBuff(DataFriend & datafriend);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataFriend& GetFriend(unsigned uid, unsigned frienduid);

	DataFriend& GetFriend(unsigned index);

	bool IsFriendExist(unsigned uid, unsigned othuid);

	//获取所有好友
	int GetFriends(unsigned uid, vector<unsigned> & indexs);

	bool UpdateFriend(DataFriend& datafriend);

	//删除好友
	bool DeleteFriend(DataFriend & datafriend);

	bool DeleteDBC(unsigned index);

private:
	static const int MAX_INDEX = DB_BASE_BUFF*DB_FRIEND_FULL;
};

#endif /* DATA_FRIEND_MANAGER_H_ */
