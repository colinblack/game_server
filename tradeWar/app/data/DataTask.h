#ifndef _DATA_TASK_H_
#define _DATA_TASK_H_

#include "Kernel.h"
#include "AsyncDBInterface.h"

struct DataTask {
	uint32_t uid;
	uint32_t id;
	uint32_t curr;
	byte type;
	byte status;

	DataTask() : uid(0), id(0), curr(0), type(0), status(0) {
	}
};

DECLARE_DBC_DATA_CLASS(CDataTask, DB_TASK)
public:
	int AddTask(const DataTask& task);
	int GetTasks(uint32_t uid, vector<DataTask>& vecDataQuests);
	int SetTask(const DataTask& task);
	int DelTask(uint32_t uid, uint32_t id = -1);
	int DelTasks(uint32_t uid);

	virtual void doRequest(CNetPacket* packet);
	int RealAddTask(CNetPacket* packet);
	int RealSetTask(CNetPacket* packet);
	int RealDelTask(CNetPacket* packet);
	int RealDelTasks(CNetPacket* packet);
DECLARE_DBC_DATA_CLASS_END

#endif /* _DATA_TASK_H_ */
