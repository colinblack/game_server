#ifndef _PATH_MANAGER_H_
#define _PATH_MANAGER_H_

#include "Kernel.h"
#include "Path.h"

struct PathTask {
	uint32_t id;	//请求寻路目标id
	uint32_t mapId;
	uint32_t time;	//请求提交时间
	void* address;
	APath::pos start;
	APath::pos end;
};

struct PathRlt {
	uint32_t id;
	uint32_t mapId;
	uint32_t time;	//计算完成时间
	bool flag;	//是否成功
	void* address;
	list<APath::pos> path;
};

class PathManager: public CSingleton<PathManager> {
public:
	~PathManager() {
	}
private:
	friend class CSingleton<PathManager>;
	PathManager() {
	}
public:
	bool init();
	bool addTask(const PathTask& task);
	bool addRlt(const PathRlt& rlt);
	bool getTask(PathTask& task);
	void doTask();
	void onTimer();
	void onExit();
private:
	ThreadMutex m_taskMutex;
	ThreadMutex m_rltMutex;
	ThreadCond m_recvCond;
	list<PathTask> m_tasks;
	list<PathRlt> m_rlts;
};

#endif

