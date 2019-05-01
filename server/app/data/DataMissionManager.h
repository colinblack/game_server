/*
 * DataMissionManager.h
 *
 *  Created on: 2016-09-13
 *      Author: city
 */

#ifndef DATA_MISSION_MANAGER_H_
#define DATA_MISSION_MANAGER_H_

#include "Kernel.h"
#include "DataMission.h"

class DataMissionManager : public DataSingleton<DataMission, DB_MISSION, DB_BASE_BUFF*DB_MISSION_FULL, CDataMission, DB_MISSION_FULL>, public CSingleton<DataMissionManager>
{
private:
	friend class CSingleton<DataMissionManager>;
	DataMissionManager(){};
	virtual ~DataMissionManager(){}

	typedef map<uint32_t, map<uint32_t, uint32_t> > MapMap;
	typedef map<uint32_t, map<uint32_t, uint32_t> >::iterator MapMap_ITER;
	MapMap m_map;

public:
	virtual void CallDestroy() {Destroy();}
	virtual int OnInit();
	virtual void OnExit();
	virtual void OnTimer1();
	virtual void OnTimer2();

	int CheckBuff(unsigned uid);

	int AddBuff(DataMission & mission);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	/*
	 * 根据参数获取任务实例的引用
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return DataMission引用
	 */
	DataMission & GetMission(unsigned uid, unsigned id);

	/*
	 * 根据参数获取数组下标
	 * param  uid(in),id(in)
	 * return 数组的下标. -1表示失败
	 */
	int GetMissionIndex(unsigned uid, unsigned id);

	/*
	 * 更新任务
	 * param  index(in)
	 * return true-成功
	 */
	bool UpdateMission(unsigned index);

	/*
	 * 更新任务
	 * param  mission(in)
	 *  exception runtime_error
	 * return true-成功
	 */
	bool UpdateMission(DataMission & mission);

	/*
	 * 根据参数获取任务对象
	 * param  index(in)
	 * return true-成功
	 */
	bool DeleteMission(DataMission & mission);

	/*
	 * 根据uid获取未完成的任务
	 * param  uid(in),vctindexs(out)
	 * return 0-成功
	 */
	int GetUnDoneMission(unsigned uid, vector<unsigned> & vctindexs);

	/*
	 * 根据uid获取所有任务
	 * param  uid(in),vctindexs(out)
	 * return 0-成功
	 */
	int GetUserMissions(unsigned uid, vector<unsigned> & vctindexs);

	/*
	 * 根据index获取任务
	 * param  uid(in),vctindexs(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	DataMission &  GetMissionByIndex(unsigned index);

	/*
	 * 将用户的任务数据写入消息协议中
	 * param  uid(in),msg(out)
	 * return 0-成功
	 */
	int FullMessage(unsigned uid, ProtoMission::MissionAllCPP * msg);

private:
	/*
	 * 根据下标索引删除任务表
	 * param  index(in)
	 * return true-成功
	 */
	bool DeleteDBCMission(unsigned index);
};
#endif /* DATA_MISSION_MANAGER_H_ */
