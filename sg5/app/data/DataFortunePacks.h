#ifndef DATA_FORTUNE_PACKS_H_
#define DATA_SEQUENCE_CHARGE_H_

#include "Kernel.h"

//礼包奖励信息
struct DataFortunePacks
{
	unsigned version;
	unsigned num;  //参与活动的玩家人数
	unsigned extranum;  //获得礼包的人数
	unsigned userlist[MAX_EXTRA_ITEMS];   //已获得礼包的用户名单

	DataFortunePacks():
		version(0),
		num(0),
		extranum(0)
	{
		memset(userlist, 0, sizeof(userlist));
	}
};

class CDataFortunePacks
{
private:
	CDataFortunePacks();
public:
	virtual ~CDataFortunePacks();
	static CDataFortunePacks* GetCDataFortunePacks();
	int Init(const std::string &path, semdat sem=sem_fortune_pack);

	int CheckVersion(unsigned version);

	//获取获得礼包的玩家列表
	int GetGiftedUsers(vector<unsigned> & uids);

	//获取当前已参与活动的玩家个数
	unsigned GetParticipateNum();

	unsigned GetExtraNum();

	//玩家参与活动
	int Participate(unsigned uid, bool isgift);
private:
	DataFortunePacks * GetDataPointer();
protected:
	static CDataFortunePacks* m_pData;
	bool m_init;
	CShareMemory m_sh;

	map<unsigned, unsigned> m_idPos;
};

#endif /* DATA_SEQUENCE_CHARGE_H_ */
