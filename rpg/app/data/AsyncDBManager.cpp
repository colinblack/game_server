#include "AsyncDBManager.h"
#include "DataManager.h"

#define DB_WRITER "dbwriter"

#define ADD_PROCESSOR(tableId,className) { \
m_tables[tableId] = className::Instance(); \
}

void* AsyncDBThread(void* data) {
	AsyncDBManager* dbMng = AsyncDBManager::getInstance();
	DataPacket packet;
	while (true) {
		while (dbMng->get(packet)) {
			AsyncDBInterfaceBase* processor = dbMng->getProcessor(packet.m_tableId);
			if (!processor) {
				error_log("table %u has no processor", packet.m_tableId);
				continue;
			}
			processor->doRequest(&packet);
		}
		usleep(1000);
	}

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
		m_mutex.release();
		return true;
	}
	return false;
}

bool AsyncDBManager::get(DataPacket& packet) {
	bool ret = true;
	if (m_mutex.acquire() == 0) {
		if (!m_packets.empty()) {
			packet = m_packets.front();
			m_packets.pop_front();
		} else {
			ret = false;
		}
		m_mutex.release();
	} else {
		ret = false;
	}
	return ret;
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

int AsyncDBManager::onSecondTimer() {
	if (m_channel == NULL) {
		info_log("try reconnect dbwriter,%s", Config::GetValue(DB_WRITER).c_str());
		return init(m_server) ? 0 : -1;
	}

	if (m_channel->IsClosed() || m_channel->getFlag() != DP_CHEAD) {
		info_log("try reconnect dbwriter,%s", Config::GetValue(DB_WRITER).c_str());
		return init(m_server) ? 0 : -1;
	}

	return 0;
}
