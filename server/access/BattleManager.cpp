#include "BattleManager.h"
#include "config.h"
#include "utils.h"


bool BattleManager::init(){
	CConfig *cfg = CConfig::getInstance();
	vector<string> vecServers;

	cfg->getSecAllKey("BATTLES",vecServers);

	if(vecServers.size() == 0){
		LOG_ERROR("BATTLES config error");
		return false;
	}

	for(vector<string>::iterator it = vecServers.begin(); it != vecServers.end(); ++it){
		int spanId,srvId;
		if(sscanf(it->c_str(),"%d",&srvId) != 1){
			LOG_ERROR("invalid config format");
			return false;
		}

		CBattleAsync* pBattle = connectBattle(spanId,srvId);
		if(pBattle == NULL){
			return false;
		}

		uint32_t key =  srvId;
		m_battles[key] = pBattle;
	}

	return true;
}

bool BattleManager::sendData(uint32_t spanId,uint32_t srvId,const string& data){
	//LOG_DEBUG(Utils::b2s(data.c_str(),data.length()).c_str());

	uint32_t key = srvId;
	map<uint32_t,CBattleAsync*>::iterator it = m_battles.find(key);
	CBattleAsync* pBattle;
	if(it == m_battles.end()){
		pBattle = connectBattle(spanId,srvId);
		if(pBattle == NULL){
			return false;
		}

		m_battles[key] = pBattle;
	}
	else{
		pBattle = it->second;
	}

	return pBattle->sendData(data);
}

CBattleAsync* BattleManager::connectBattle(uint32_t spanId,uint32_t srvId){
	char key[64] = {0};
	sprintf(key,"%u",srvId);
	CConfig *cfg = CConfig::getInstance();
	const char *addr = cfg->GetStrVal("BATTLES", key);

	if(addr == NULL){
		LOG_ERROR("unknow battle server %u_%u",spanId,srvId);
		return NULL;
	}

	CBattleAsync* pBattle = new CBattleAsync(m_pollThread,spanId,srvId);

	return pBattle;
}

bool BattleManager::clientClose(uint32_t spanId,uint32_t srvId,uint32_t fd,uint32_t time,uint32_t microTime,uint32_t ip)
{
	uint32_t key = srvId;
	map<uint32_t,CBattleAsync*>::iterator it = m_battles.find(key);
	if(it == m_battles.end()){
		LOG_ERROR("invalid span,srv [%u %u]",spanId,srvId);
		return false;
	}

	it->second->clientClose(fd,time,microTime,ip);

	return true;
}
