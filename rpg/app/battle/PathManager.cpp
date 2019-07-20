#include "BattleInc.h"

//最大延迟(s)，超过该延迟则放弃该寻路动作
#define MAX_TASK_INTERVAL 3

void* PathThreadFunc(void* arg) {
	PathManager* pathManager = PathManager::Instance();
	pathManager->doTask();
	return NULL;
}

bool PathManager::init() {
	int threadCount = 1;
	Config::GetIntValue(threadCount, "path_thread");
	pthread_t pid;
	for (int i = 0; i < threadCount; ++i) {
		if (pthread_create(&pid, NULL, PathThreadFunc, (void*) NULL) != 0) {
			error_log("start path thread failed");
			return false;
		}
		info_log("start  path thread %u success", pid);
	}
	return true;
}

bool PathManager::addTask(const PathTask& task) {
	if (m_taskMutex.acquire() == 0) {
		m_tasks.push_back(task);
		m_recvCond.Signal();
		m_taskMutex.release();
		return true;
	}
	return false;
}

bool PathManager::addRlt(const PathRlt& rlt) {
	if (m_rltMutex.acquire() == 0) {
		m_rlts.push_back(rlt);
		m_rltMutex.release();
		return true;
	}
	return false;
}

bool PathManager::getTask(PathTask& task) {
	bool ret = true;
	if (m_taskMutex.acquire() == 0) {
		if (m_tasks.empty()) {
			ret = false;
		} else {
			task = *(m_tasks.begin());
			m_tasks.pop_front();
		}
		m_taskMutex.release();
	} else {
		ret = false;
	}
	return ret;
}

void PathManager::doTask() {
	PathTask pathTask;
	bool ret = true;
	while(!LogicManager::IsClosed) {
		ret = true;
		if (m_taskMutex.acquire() == 0) {
			if (m_tasks.empty()) {
				ret = false;
				m_recvCond.Wait(m_taskMutex.getMutex());
			} else {
				pathTask = m_tasks.front();
				m_tasks.pop_front();
			}
			m_taskMutex.release();
		} else {
			ret = false;
		}
		if (!ret) {
			continue;
		}
		PathRlt pathRlt;
		pathRlt.id = pathTask.id;
		pathRlt.mapId = pathTask.mapId;
		pathRlt.time = LogicManager::GlobalTime;
		pathRlt.flag = true;
		pathRlt.address = pathTask.address;
		if (pathRlt.time - pathTask.time > MAX_TASK_INTERVAL) {
			pathRlt.flag = false;
			error_log("mapid=%u,id=%u find path timeout", pathTask.mapId, pathTask.id);
		} else {
			APath::AStar* pAstar = APath::AStar::getInstance(pathTask.mapId);
			if (pAstar == NULL) {
				error_log("cannot get astar by mapid:%d", pathTask.mapId);
				pathRlt.flag = false;
			} else {
				if (!pAstar->FindPath(pathTask.start, pathTask.end, pathRlt.path)) {
					pathRlt.flag = false;
					error_log("find path failed:start [%d,%d],end [%d,%d],mapId %d", pathTask.start.x, pathTask.start.y, pathTask.end.x, pathTask.end.y, pathTask.mapId);
				}
			}
		}
		addRlt(pathRlt);
	}
}

void PathManager::onTimer() {
	static MapManager* pMM = MapManager::Instance();
	if (m_rltMutex.acquire() == 0) {
		PathRlt rlt;
		while (!m_rlts.empty()) {
			rlt = *(m_rlts.begin());
			m_rlts.pop_front();
			MapMoveObject *pMo = dynamic_cast<MapMoveObject*>(pMM->getObject(rlt.id));
			if (pMo) {
				pMo->setPath(rlt);
			}
		}
		m_rltMutex.release();
	}
}

void PathManager::onExit() {
	m_recvCond.Broadcast();
}
