#include "AsyncDBManager.h"
#include "DataManager.h"
#include "Utils.h"

#define DB_WRITER "dbwriter"

#define ADD_PROCESSOR(tableId,className) { \
m_tables[tableId] = className::Instance(); \
}

void* AsyncDBThread(void* data) {
	AsyncDBManager::Instance()->pop();
	return NULL;
}

AsyncDBManager::AsyncDBManager() {
	m_channel = NULL;
	m_server = NULL;
}

bool AsyncDBManager::init(CTcpServer* pServer) {
	m_server = pServer;
	CInternetAddress address;
	if (!address.FromString(Config::GetValue("dbwriter"))) {
		error_log("invalid dbwriter address,%s", Config::GetValue("dbwriter").c_str());
		return false;
	}
	if ((m_channel = m_server->GetRemoteClientChannel(address, DP_CHEAD)) == NULL) {
		error_log("connect dbwriter failed,address=%s", Config::GetValue("dbwriter").c_str());
		return false;
	}
	return true;
}

bool AsyncDBManager::initThread() {
	ADD_PROCESSOR(DB_BASE, DataBaseManager);
	ADD_PROCESSOR(DB_POS, DataPosManager);
	ADD_PROCESSOR(DB_SKILL, DataSkillManager);
	ADD_PROCESSOR(DB_PAY, DataPayManager);
	ADD_PROCESSOR(DB_ROLE, DataRoleManager);
	ADD_PROCESSOR(DB_MISSION, DataMissionManager);
	ADD_PROCESSOR(DB_ADVANCE, DataAdvanceManager);
	ADD_PROCESSOR(DB_EQUIP, DataEquipManager);
	ADD_PROCESSOR(DB_SHENQI, DataShenQiManager);
	ADD_PROCESSOR(DB_BAG_EXTEND, DataBagExtendManager);
	ADD_PROCESSOR(DB_TREASURE, DataTreasureManager);
	ADD_PROCESSOR(DB_FORGE, DataForgeManager);
	ADD_PROCESSOR(DB_ATTR, DataAttrManager);
	ADD_PROCESSOR(DB_ROLE_ATTR, DataRoleAttrManager);
	ADD_PROCESSOR(DB_ACTIVE, DataActiveManager);
	ADD_PROCESSOR(DB_REWARD, DataSignManager);
	ADD_PROCESSOR(DB_TRUMP, DataTrumpManager);
	ADD_PROCESSOR(DB_PLAYER_CONFIG, DataPlayerConfigManager);

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

bool AsyncDBManager::push(const DataPacket& packet) {
	if (m_mutex.acquire() == 0) {
		m_packets.push_back(packet);
		m_recvCond.Signal();
		m_mutex.release();
		return true;
	}
	return false;
}

bool AsyncDBManager::pop() {
	bool ret = true;
	DataPacket packet;
	AsyncDBInterfaceBase *processor = NULL;
	while (stop == 0) {
		if (m_mutex.acquire() == 0) {
			if (!m_packets.empty()) {
				ret = true;
				packet = m_packets.front();
				m_packets.pop_front();
			} else {
				ret = false;
				m_recvCond.Wait(m_mutex.getMutex());
			}
			m_mutex.release();
		} else {
			ret = false;
		}
		if (!ret) {
			continue;
		}
		processor = getProcessor(packet.m_tableId);
		if (!processor) {
			error_log("table %u has no processor", packet.m_tableId);
			continue;
		}
		processor->doRequest(&packet);
	}
	return true;
}

bool AsyncDBManager::onExit() {
	m_recvCond.Broadcast();
	return true;
}

AsyncDBInterfaceBase* AsyncDBManager::getProcessor(uint32_t tableId) {
	map<uint32_t, AsyncDBInterfaceBase*>::iterator it = m_tables.find(tableId);
	return it == m_tables.end() ? NULL : it->second;
}

bool AsyncDBManager::send(DataPacket& packet) {
	if (m_channel == NULL) {
		return false;
	}
	static CStaticBuffer<DP_BODY_SIZE> buff;
	buff.Clear();
	if (!packet.Encode(&buff)) {
		return false;
	}
	if (!m_channel->SendData(&buff)) {
		return false;
	}
	return true;
}

bool AsyncDBManager::onSecondTimer() {
	if (m_channel == NULL) {
		info_log("try reconnect dbwriter,%s", Config::GetValue(DB_WRITER).c_str());
		return init(m_server);
	}
	if (m_channel->IsClosed() || m_channel->getFlag() != DP_CHEAD) {
		info_log("try reconnect dbwriter,%s", Config::GetValue(DB_WRITER).c_str());
		return init(m_server);
	}
	return true;
}
