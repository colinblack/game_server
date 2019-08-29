#include "DataInc.h"
#include "AsyncDBManager.h"
#include "AsyncDBInterface.h"

#define ADD_PROCESSOR(tableId,className) { \
static className obj; \
m_tables[tableId] = &obj; \
}

void* AsyncDBThread(void* data) {
	AsyncDBManager::getInstance()->getPacket();
	return NULL;
}

AsyncDBManager::AsyncDBManager() {
}

bool AsyncDBManager::initThread() {
	ADD_PROCESSOR(DB_USER, CDataUser);
	ADD_PROCESSOR(DB_USER_RESOURCE, CDataUserResource);
	ADD_PROCESSOR(DB_HERO, CDataHero);
	ADD_PROCESSOR(DB_BUILDING, CDataBuilding);
	ADD_PROCESSOR(DB_EQUIPMENT, CDataEquipment);
	ADD_PROCESSOR(DB_TASK, CDataTask);
	ADD_PROCESSOR(DB_PAY, CDataPay);
	ADD_PROCESSOR(DB_VIDEO, CDataVideo);
	ADD_PROCESSOR(DB_EMAIL, CDataEmail);
	ADD_PROCESSOR(DB_STATE, CDataState);
	ADD_PROCESSOR(DB_ACTIVENESS, CDataActiveness);
	ADD_PROCESSOR(DB_SKILL, CDataSkill);
	ADD_PROCESSOR(DB_SOLDIER, CDataSoldier);
	ADD_PROCESSOR(DB_SOCIAL, CDataSocial);
	ADD_PROCESSOR(DB_PRETASK, CDataPreTask);
	ADD_PROCESSOR(DB_WORKER, CDataWorker);
	ADD_PROCESSOR(DB_DEFEND, CDataDefend);
	ADD_PROCESSOR(DB_TROOPS, CDataTroops);
	ADD_PROCESSOR(DB_TOWER, CDataTower);
	ADD_PROCESSOR(DB_ACHIEVEMENT, CDataAchievement);
	ADD_PROCESSOR(DB_BOAT_ROB_LOG, CDataBoatRobLog);
	ADD_PROCESSOR(DB_BATTLE_GATE, CDataBattleGate);
	ADD_PROCESSOR(DB_BOAT, CDataBoat);
	ADD_PROCESSOR(DB_BOAT_TRAIN, CDataBoatTrain);
	ADD_PROCESSOR(DB_RANDOM_QUEST, CDataRandomQuest);
	ADD_PROCESSOR(DB_ACTIVITY, CDataActivity);
	ADD_PROCESSOR(DB_CHARGE_HISTORY, CDataChargeHistory);
	ADD_PROCESSOR(DB_GEM_POINT, CDataGemPoint);
	ADD_PROCESSOR(DB_BOSS, CDataBoss);
	ADD_PROCESSOR(DB_ARENA, CDataArena);
	ADD_PROCESSOR(DB_ARENA_LOG, CDataArenaLog);
	ADD_PROCESSOR(DB_USER_INTERACT, CDataUserInteract);
	ADD_PROCESSOR(DB_GUARD, CDataGuard);

	if (0 != CLog::create_inst("misc", Config::GetValue("log_busi").c_str())) {
		error_log("create_inst_fail");
		return false;
	}

	if (!startAsynThread()) {
		return false;
	}
	return true;
}

bool AsyncDBManager::startAsynThread() {
	pthread_t pid;
	if (pthread_create(&pid, NULL, AsyncDBThread, (void*) NULL) != 0) {
		error_log("create async db thread failed,%m");
		return false;
	}
	info_log("start AsyncDBThread thread  %u success", pid);
	return true;
}

bool AsyncDBManager::push(const CNetPacket& packet) {
	if (m_mutex.acquire() == 0) {
		m_packets.push_back(packet);
		m_cond.Signal();
		m_mutex.release();
		return true;
	}
	return false;
}

bool AsyncDBManager::getPacket() {
	CNetPacket packet;
	bool ret = false;
	uint32_t count = 0;
	while (true) {
		if (m_mutex.acquire() == 0) {
			if (!m_packets.empty()) {
				packet = m_packets.front();
				m_packets.pop_front();
				ret = true;
				if (++count % 1000 == 0) {
					info_log("list size is %u count is %u", m_packets.size(), count);
				}
			} else {
				m_cond.Wait(m_mutex.getMutex());
				ret = false;
			}
			m_mutex.release();
		}
		if (ret) {
			doPacket(&packet);
		}
	}

	return ret;
}

bool AsyncDBManager::printStat() {
	if (m_stat.size() == 300 || Time::GetGlobalTime() % 300 == 0) {
		info_log("async_data_stat_head statSize=%u", m_stat.size());
		for (map<uint32_t, uint32_t>::iterator iter = m_stat.begin(); iter != m_stat.end(); ++iter) {
			info_log("async_data_stat fd=%u op=%u count=%u", iter->first >> 16, iter->first & 0xFFFF, iter->second);
		}
		m_stat.clear();
	}
	return true;
}

bool AsyncDBManager::send(CNetPacket* packet) {
	packet->ptype = PROTOCOL_TYPE_ASYNC_DB;
	if (!addEncodedPacket(packet)) {
		error_log("addEncodedPacket fail ptype=%u", packet->ptype);
		return false;
	}
	return true;
}

bool AsyncDBManager::doPacket(CNetPacket* packet) {
	switch (packet->ptype) {
	case PROTOCOL_TYPE_ASYNC_DB:
		doWrite(packet);
		break;
	case PROTOCOL_TYPE_ASYNC_DB_TRANSFER:
		doProbe(packet);
		break;
	default:
		error_log("unknow_packet_ptype=%u", packet->ptype);
		return false;
	}
	return true;
}

bool AsyncDBManager::doWrite(CNetPacket* packet) {
	AsyncDBManager* dbMng = AsyncDBManager::getInstance();
	AsyncDBInterface* processor = dbMng->getProcessor(packet->fd);
	if (!processor) {
		error_log("table %u has no processor", packet->fd);
		return false;
	}
	processor->doRequest(packet);

	return true;
}

bool AsyncDBManager::doProbe(CNetPacket* packet) {
	return true;
}

bool AsyncDBManager::sendData(CNetPacket& packet) {
	return true;
}

bool AsyncDBManager::getSendPacket(CNetPacket& packet) {
	bool ret = true;
	if (m_sendMutex.acquire() == 0) {
		if (m_sendQueue.size() > 0) {
			packet = m_sendQueue.front();
			m_sendQueue.pop_front();
		} else {
			ret = false;
		}
		m_sendMutex.release();
	} else {
		ret = false;
	}
	return ret;
}

bool AsyncDBManager::addEncodedPacket(CNetPacket* packet) {
	CNetPacket* pTmp = new CNetPacket(*packet);
	if (pTmp != NULL && m_eplMutex.acquire() == 0) {
		m_encodedPacketList.push_back(pTmp);
		m_eplMutex.release();

		////////////////////////////////////////////// 统计日志
		uint32_t statKey = packet->fd << 16;
		statKey |= packet->stime & 0xFFFF;
		if (m_stat.find(statKey) == m_stat.end()) {
			m_stat[statKey] = 0;
		}
		m_stat[statKey]++;
		///////////////////////////////////////////////////////

		return true;
	}
	return false;
}
bool AsyncDBManager::getEncodedPacket(list<CNetPacket*>& epList) {
	if (m_eplMutex.acquire() == 0) {
		if (!m_encodedPacketList.empty()) {
			epList.insert(epList.end(), m_encodedPacketList.begin(), m_encodedPacketList.end());
		}
		m_encodedPacketList.clear();
		m_eplMutex.release();
		return true;
	}

	return false;
}
