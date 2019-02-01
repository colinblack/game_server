#ifndef DATA_KINGTREASURE_H_
#define DATA_KINGTREASURE_H_

#include "Kernel.h"

#define MAX_BOX_NUMS	(300)

struct TreasureBox
{
	unsigned id, used;

	TreasureBox()
	{
		id = used = 0;
	}
};

struct DataTreasureDepot
{
	unsigned version;
	unsigned num;
	TreasureBox boxes[MAX_BOX_NUMS];

	DataTreasureDepot():
		version(0),
		num(0)
	{
	}
};

class CDataTreasureDepot
{
private:
	CDataTreasureDepot();
public:
	virtual ~CDataTreasureDepot();
	static CDataTreasureDepot* GetCDataTreasureDepot();
	int Init(const std::string &path, semdat sem=sem_king_treasure);

	int CheckVersion(unsigned version);

	//获取已抽取次数
	int GetUsedTimes(unsigned id);

	//增加指定箱子的抽取次数
	int AddUsedTimes(unsigned id, int times);

protected:
	static CDataTreasureDepot* m_pData;
	bool m_init;
	CShareMemory m_sh;

	map<unsigned, unsigned> m_idPos;
};

#endif /* DATA_KINGTREASURE_H_ */
