#ifndef DATA_OPERA_BATTLE_MANAGER_H_
#define DATA_OPERA_BATTLE_MANAGER_H_

#include "Kernel.h"
#include "DataOperaBattle.h"

class DataOperaBattleManager : public DataSingleton<DataOperaBattle, DB_OPERA_BATTLE, DB_BASE_BUFF*DB_OPERA_BATTLE_FULL, CDataOperaBattle, DB_OPERA_BATTLE_FULL>,
	public CSingleton<DataOperaBattleManager>
{
private:
	friend class CSingleton<DataOperaBattleManager>;
	DataOperaBattleManager(){};
	virtual ~DataOperaBattleManager(){}

	typedef map<uint32_t, map<uint32_t, map<uint32_t, uint32_t> > > MapMap;  //uid->gateid->difficulty =>index
	typedef map<uint32_t, map<uint32_t, map<uint32_t, uint32_t> > >::iterator MapMap_ITER;
	MapMap m_map;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int CheckBuff(unsigned uid);
	int AddBuff(DataOperaBattle & operabattle);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//throw std::runtime_error
	DataOperaBattle& GetDiffBattle(unsigned uid, unsigned gateid, unsigned diff);

	DataOperaBattle& GetDiffBattle(unsigned index);

	bool IsDiffBattleExist(unsigned uid, unsigned gateid, unsigned diff);

	//获取所有剧本
	int GetBattles(unsigned uid, vector<unsigned> & indexs);

	bool UpdateDiffBattle(DataOperaBattle& operabattle);

private:
	static const int MAX_INDEX = DB_BASE_BUFF*DB_OPERA_BATTLE_FULL;
};

#endif /* DATA_OPERA_BATTLE_MANAGER_H_ */
