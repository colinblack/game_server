#include "LogicQueueManager.h"
#include "ServerInc.h"

//加速。立即完成系列
void DataRoutineBase::CheckUd(unsigned ud)
{
	if(ud_ != ud)
	{
		error_log("vector can't find ud. uid=%u,ud=%u,type=%u", uid_, ud, type);
		throw runtime_error("cannot_find_routine_ud");
	}
}
int DataRoutineBase::DoEnd()
{
	//debug_log("routine DoEnd begin. uid=%u,rid=%llu", uid_, rid);
	//判断是否在线，如果离线，则不做处理
	if (!UserManager::Instance()->IsOnline(uid_))
	{
		return R_ERROR;
	}

	//ProtoPush::PushBuildingsCPP * msg = new ProtoPush::PushBuildingsCPP;

	SingleRoutineEnd(ud_/*, msg*/);

	//推送
	//bool issuccess = LogicManager::Instance()->sendMsg(uid_, msg);

	//debug_log("routine DoEnd end. uid=%u,rid=%llu,result=%u", uid_, rid, issuccess);

	return 0;
}
uint32_t DataRoutineBase::GetBuildType()
{
	return 0;
}
int DataRoutineBase::GetLeftTime()
{
	uint32_t now = Time::GetGlobalTime();
	return (endts_ > now) ? (endts_ - now) : 0;
}

void LogicQueueManager::OnTimer1()
{
	unsigned now = Time::GetGlobalTime();
	list<DataRoutineBase*> overList;
	for(map<unsigned, list<DataRoutineBase*> >::iterator uIter = userTask.begin(); uIter != userTask.end(); ++uIter)
	{
		uint32_t uid = uIter->first;
		list<DataRoutineBase*>& rList = uIter->second;
		for(list<DataRoutineBase*>::iterator rIter = rList.begin(); rIter != rList.end();)
		{
			DataRoutineBase* pRoutine = *rIter;
			if(pRoutine == NULL)
			{
				rIter = rList.erase(rIter);
				continue;
			}
			if(pRoutine->endts_ <= now)
			{
				overList.push_back(pRoutine);
				rIter = rList.erase(rIter);	// 删除映射
				continue;
			}
			break;
		}
	}
	for(list<DataRoutineBase*>::iterator oIter = overList.begin(); oIter != overList.end(); ++oIter)
	{
		DataRoutineBase* pRoutine = *oIter;
		if(pRoutine != NULL)
		{
	        try
	        {
	        	TaskDone(pRoutine);
	        }catch (exception & e)
	        {
	            error_log("task done fail msg=%s", e.what());
	        }
		}
	}
}
void LogicQueueManager::Offline(unsigned uid)
{
	map<unsigned, list<DataRoutineBase*> >::iterator uIter = userTask.find(uid);
	if(uIter == userTask.end())
	{
		return;
	}
	list<DataRoutineBase*>& routineList = uIter->second;
	for(list<DataRoutineBase*>::iterator iter = routineList.begin(); iter != routineList.end(); ++iter)
	{
		DataRoutineBase* pRoutine = *iter;
//		debug_log("queue_routine_timer_del_old uid=%u ud=%u type=%u", pRoutine->uid_, pRoutine->ud_, pRoutine->type);
		delete pRoutine;
	}
	userTask.erase(uIter);
}

int LogicQueueManager::Process(unsigned uid, User::SpeedUpReq* req, User::SpeedUpResp* resp)
{
	unsigned type = req->type();
	unsigned ud = req->ud();

	SpeedUp(uid, type, ud, resp);

	return 0;
}

DataRoutineBase * LogicQueueManager::GetRoutineObj(unsigned uid, unsigned ud, uint8_t type)
{
	map<unsigned, list<DataRoutineBase*> >::iterator uIter = userTask.find(uid);
	if(uIter == userTask.end())
	{
		return NULL;
	}
	list<DataRoutineBase*>& routineList = uIter->second;
	for(list<DataRoutineBase*>::iterator iter = routineList.begin(); iter != routineList.end(); ++iter)
	{
		if(uid == (*iter)->uid_ && ud == (*iter)->ud_ && type == (*iter)->type)
		{
			return *iter;
		}
	}
	return NULL;
}

void LogicQueueManager::TaskDone(DataRoutineBase * task)
{
//	调用TaskDone时,已经从映射中删除定时任务,但是还未释放空间
	task->DoEnd();
	delete task;
	task = NULL;
}
void LogicQueueManager::FinishInstant(uint32_t uid, uint32_t buildType)
{
	map<unsigned, list<DataRoutineBase*> >::iterator uIter = userTask.find(uid); // 玩家任务
	if(uIter == userTask.end())
	{
		return;
	}
	list<DataRoutineBase*> routineList;
	list<DataRoutineBase*>& task = uIter->second;
	for(list<DataRoutineBase*>::iterator tIter = task.begin(); tIter != task.end(); ++tIter)
	{
		DataRoutineBase *pRoutine = *tIter;
		if(pRoutine != NULL && pRoutine->GetBuildType() == buildType)
		{
			routineList.push_back(pRoutine);
		}
	}

	for(list<DataRoutineBase*>::iterator tIter = routineList.begin(); tIter != routineList.end(); ++tIter)
	{
		DataRoutineBase *pRoutine = *tIter;
		FinishRoutine(pRoutine, pRoutine->ud_, pRoutine->GetLeftTime());
	}
}
int LogicQueueManager::SpeedUp(unsigned uid, unsigned type, unsigned ud, User::SpeedUpResp * resp)
{
	DataRoutineBase * proutine = GetRoutineObj(uid, ud, type);
	if (NULL == proutine)
	{
		error_log("routine's maps can't find routine. uid=%u,type=%u,ud=%u", uid, type, ud);
		throw runtime_error("queue_no_routine");
	}

	//检查队列是否存在
	proutine->CheckUd(ud);

	int cash = 0;
	int diffts = 0;

	int speedType = routine_speed_cash;
	//获取消耗的钻石以及钻石减去的时间
	proutine->GetPriceAndATime(ud, cash, diffts, speedType);

	//钻石消耗
	CommonGiftConfig::CommonModifyItem cfg;
	if(speedType == routine_speed_cash)
		cfg.mutable_based()->set_cash(-cash);
	else
	{
		CommonGiftConfig::PropsItem* k = cfg.add_props();
		k->set_id(60089);
		k->set_count(-cash);
	}

	LogicUserManager::Instance()->CommonProcess(proutine->uid_, cfg, "SpeedUp", resp->mutable_commons());

	//结束当前ud的定时任务
	FinishRoutine(proutine, ud, diffts);

	return 0;
}

int LogicQueueManager::SpeedUpTask(DataRoutineBase *pTask, int sec, bool &taskDone)
{
	taskDone = false;
	if(pTask == NULL)
	{
		throw runtime_error("wrong_routine");
	}
	unsigned currts = Time::GetGlobalTime();
	unsigned oldEndts = pTask->endts_;
	if(pTask->endts_ >= sec)
	{
		pTask->endts_ -= sec;
	}
	else
	{
		pTask->endts_ = 0;
	}
	EraseTask(pTask->uid_, pTask->ud_, pTask->type);
	if(currts >= pTask->endts_)
	{
		//当前时间大于结束时间，表示任务完成，直接在这里处理完成的动作
		taskDone = true;
		return 0;
	}
	else
	{
		AddTask(pTask);
	}
	return 0;
}

void LogicQueueManager::AddTask(DataRoutineBase * task)
{
	list<DataRoutineBase*>& routineList = userTask[task->uid_];
	list<DataRoutineBase*>::iterator iter = routineList.begin();
	for(; iter != routineList.end(); ++iter)
	{
		if(task->endts_ <= (*iter)->endts_)
		{
			break;
		}
	}
	routineList.insert(iter, task);
}
DataRoutineBase* LogicQueueManager::EraseTask(uint32_t uid, uint32_t ud, uint8_t type)
{
	map<unsigned, list<DataRoutineBase*> >::iterator uIter = userTask.find(uid);
	if(uIter == userTask.end())
	{
		return NULL;
	}
	list<DataRoutineBase*>& routineList = uIter->second;
	for(list<DataRoutineBase*>::iterator iter = routineList.begin(); iter != routineList.end(); ++iter)
	{
		if(uid == (*iter)->uid_ && ud == (*iter)->ud_ && type == (*iter)->type)
		{
			DataRoutineBase* pRoutine = *iter;
			routineList.erase(iter);
			return pRoutine;
		}
	}
	return NULL;
}
bool LogicQueueManager::IsExistBuildRoutine(unsigned uid, unsigned ud) const
{
	return LogicQueueManager::Instance()->GetRoutineObj(uid, ud, routine_type_build) != NULL;
}
int LogicQueueManager::FinishRoutine(DataRoutineBase* proutine, unsigned ud, int diffts)
{
	bool taskDone = false;
	//最后一个加速，则调用routine，用于结束routine
	SpeedUpTask(proutine, diffts, taskDone);
	if(taskDone)
	{
//		debug_log("queue_routine_speed_up_del uid=%u ud=%u type=%u", proutine->uid_, proutine->ud_, proutine->type);
		TaskDone(proutine);
	}
	return 0;
}
