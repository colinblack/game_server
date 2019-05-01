#ifndef DATA_SHAKE_DICE_MANAGER_H_
#define DATA_SHAKE_DICE_MANAGER_H_

#include "Kernel.h"
#include "DataShakeDice.h"

class DataShakeDiceManager : public DataSingleton<DataShakeDice, DB_SHAKE_DICE, DB_BASE_BUFF*DB_BASE_FULL, CDataShakeDice, DB_BASE_FULL>,
	public CSingleton<DataShakeDiceManager>
{
private:
	friend class CSingleton<DataShakeDiceManager>;
	DataShakeDiceManager(){};
	virtual ~DataShakeDiceManager(){}

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
	int AddBuff(DataShakeDice & shakedice);
	int LoadBuff(unsigned uid);

	unsigned GetIndex(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataShakeDice& GetShakeDice(unsigned uid);

	bool UpdateDataShakeDice(DataShakeDice& shakedice);
};

#endif /* DATA_SHAKE_DICE_MANAGER_H_ */
