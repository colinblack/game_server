#ifndef DATA_DAILYMISSION_MANAGER_H_
#define DATA_DAILYMISSION_MANAGER_H_

#include "Kernel.h"
#include "DataDailyMission.h"

class DataDailyMissionManager : public DataSingleton<DataDailyMission, DB_DAILY_MISSION, DB_BASE_BUFF*DB_DAILY_MISSION_FULL, CDataDailyMission, DB_DAILY_MISSION_FULL>,
	public CSingleton<DataDailyMissionManager>
{
private:
	friend class CSingleton<DataDailyMissionManager>;
	DataDailyMissionManager(){};
	virtual ~DataDailyMissionManager(){}

	typedef map<uint32_t, map<uint32_t, uint32_t> > MapMap;  //uid->id =>index
	typedef map<uint32_t, map<uint32_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;
	MapMap m_mapMissidIndex;  //映射任务id. //uid->missid =>index;
public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	//判断是否加载进内存
	int CheckBuff(unsigned uid);

	//添加数据到内存和dbc中
	int AddBuff(DataDailyMission & dailymission);

	//加载dbc到内存中
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	DataDailyMission& GetDailyMission(unsigned uid, unsigned id);

	DataDailyMission& GetDailyMissionByMissid(unsigned uid, unsigned missid);

	DataDailyMission& GetDailyMission(unsigned index);

	//获取所有部件
	int GetDailyMissions(unsigned uid, vector<unsigned> & indexs);

	//更新每日任务
	bool UpdateDailyMission(DataDailyMission& dailymission);

	//删除每日任务id索引
	int ClearMissidIndex(unsigned uid);

private:
	int CreateSelfIndex(unsigned uid, unsigned missid, unsigned id, unsigned index);

private:
	static const int MAX_INDEX = DB_BASE_BUFF*DB_DAILY_MISSION_FULL;
};

#endif /* DATA_DAILYMISSION_MANAGER_H_ */
