#ifndef DATA_RESOURCE_COPY_MANAGER_H_
#define DATA_RESOURCE_COPY_MANAGER_H_

#include "Kernel.h"
#include "DataResourceCopy.h"

class DataResourceCopyManager : public DataSingleton<DataResourceCopy, DB_RESOURCE_COPY, DB_BASE_BUFF*DB_RESOURCE_COPY_FULL, CDataResourceCopy, DB_RESOURCE_COPY_FULL>,
	public CSingleton<DataResourceCopyManager>
{
private:
	friend class CSingleton<DataResourceCopyManager>;
	DataResourceCopyManager(){};
	virtual ~DataResourceCopyManager(){}

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
	int AddBuff(DataResourceCopy & resourcecopy);
	int LoadBuff(unsigned uid);

	void DoClear(unsigned uid);
	void DoSave(unsigned uid);

	//如果没有，则新增
	DataResourceCopy& GetResourceCopy(unsigned uid, unsigned id);

	DataResourceCopy& GetResourceCopy(unsigned index);

	int NewResrouceCopy(unsigned uid, unsigned id);

	//获取所有资源副本信息
	int GetResourceCopies(unsigned uid, vector<unsigned> & indexs);

	bool UpdateResourceCopy(DataResourceCopy& resourcecopy);

private:
	static const int MAX_INDEX = DB_BASE_BUFF*DB_RESOURCE_COPY_FULL;
};

#endif /* DATA_RESOURCE_COPY_MANAGER_H_ */
