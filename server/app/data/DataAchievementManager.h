#ifndef DATA_ACHIEVEMENT_MANAGER_H_
#define DATA_ACHIEVEMENT_MANAGER_H_

#include "Kernel.h"
#include "DataAchievement.h"

class DataAchievementManager : public DataSingleton<DataAchievement, DB_ACHIEVEMENT, DB_BASE_BUFF*DB_ACHIEVEMENT_FULL, CDataAchievement, DB_ACHIEVEMENT_FULL>,
	public CSingleton<DataAchievementManager>
{
private:
	friend class CSingleton<DataAchievementManager>;
	DataAchievementManager(){};
	virtual ~DataAchievementManager(){}

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

	int AddBuff(DataAchievement & achievement);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	/*
	 * 根据参数获取任务实例的引用
	 * param  uid(in),id(in)
	 * exception runtime_error
	 * return DataMission引用
	 */
	DataAchievement & GetAchievement(unsigned uid, unsigned id);

	/*
	 * 根据index获取任务
	 * param  uid(in),vctindexs(out)
	 * exception runtime_error
	 * return 0-成功
	 */
	DataAchievement & GetAchievement(unsigned index);

	/*
	 * 更新任务
	 * param  index(in)
	 * return true-成功
	 */
	bool UpdateAchievement(unsigned index);

	/*
	 * 更新成就
	 * param  achievement(in)
	 * exception runtime_error
	 * return true-成功
	 */
	bool UpdateAchievement(DataAchievement & achievement);

	//判断成就是否存在
	bool IsAchieveExist(unsigned uid, unsigned id);

	/*
	 * 获取用户的指定类型的未完成成就
	 * param  uid(in),type(in), vctindexs(out)
	 * return 0-成功
	 */
	int GetUnDoneAchieveByType(unsigned uid, unsigned type, vector<unsigned> & vctindexs);

	/*
	 * 根据uid获取所有成就
	 * param  uid(in),vctindexs(out)
	 * return 0-成功
	 */
	int GetUserAchievements(unsigned uid, vector<unsigned> & vctindexs);

	/*
	 * 将用户的成就数据写入消息协议中
	 * param  uid(in),msg(out)
	 * return 0-成功
	 */
	int FullMessage(unsigned uid, ProtoAchievement::AchievementAllCPP * msg);

private:
	static const int MAX_INDEX = DB_BASE_BUFF*DB_ACHIEVEMENT_FULL;
};
#endif /* DATA_ACHIEVEMENT_MANAGER_H_ */
