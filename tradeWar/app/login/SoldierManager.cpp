/*
 * SoldierManager.cpp
 *
 *  Created on: 2016年5月11日
 *      Author: asdf
 */

#include "SoldierManager.h"
#include "Player.h"
#include "DataInc.h"
#include "ProtocolSoldier.h"
#include "SoldierConfig.h"
#include "VipConfig.h"
#include "SystemMessage.h"
#include "StrongConfig.h"
#include "RecyclingConfig.h"

SoldierManager::SoldierManager() :
		m_player(NULL), m_maxUd(0) {
}

SoldierManager::~SoldierManager() {
	for (map<uint32_t, Soldier*>::iterator it = m_soldiers.begin(); it != m_soldiers.end(); ++it) {
		delete it->second;
	}
	m_soldiers.clear();
}

void SoldierManager::release() {
	for (map<uint32_t, Soldier*>::iterator it = m_soldiers.begin(); it != m_soldiers.end(); ++it) {
		delete it->second;
	}
	m_soldiers.clear();
	m_player->clearAllTimer();
}

bool SoldierManager::doPacket(CNetPacket * packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_SOLDIER_LIST:
		doQuerySoldierList(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_UPGRADE:
		doSoldierUpgrade(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_UPGRADE_FINISH_NOW:
		doSoldierUpgradeFinishNow(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_TRAIN:
		doSoldierTrainFast(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_TRAIN_FINISH_NOW:
		doSoldierTrainFinishNow(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_TRAIN_LIST:
		doSoldierTrainList(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_TRAIN_SLOT_OPEN:
		doSoldierTrainSlotOpen(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_STATION_QUERY:
		doSoldierStationQuery(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_STATION_ADD:
		doSoldierStation(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_STATION_DEL:
		doSoldierStationDel(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_ALLIANCE_STATION_QUERY:
		doSoldierAllianceStationQuery(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_ALLIANCE_STATION_ADD:
		doSoldierAllianceStationAdd(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_STRONG:
		doSoldierStrong(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_STAR:
		doSoldierStar(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_BOX_SCORE:
		doBoxScore(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_ADD_BOX_SCORE:
		doSoldierSell(packet);
		break;
	case PROTOCOL_SUBCMD_SOLDIER_BOX_REWARD:
		doBoxReward(packet);
		break;
	default:
		break;
	}
	return true;
}
bool SoldierManager::doQuerySoldierList(CNetPacket * packet) {
	sendSoldierList();
	return true;
}

bool SoldierManager::doSoldierUpgrade(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	byte ret = 0;
	CSoldierUpgradeProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CSoldierUpgradeProtocol_fail&uid=%u", uid);
		ret = PROTOCOL_RET_SOLDIER_PACKET_ERROR;
	}

	uint32_t type = protocol.type;
	uint32_t level = protocol.level;

	Soldier *pSoldier = NULL;
	if (ret == 0 && (pSoldier = getSoldierByType(type)) == NULL) {
		error_log("soldier is lock uid=%u type=%u level=%u", uid, type, level);
		ret = PROTOCOL_RET_SOLDIER_FAIL;
	}

	if (ret == 0 && !upgradeSoldier(uid, type)) {
		error_log("upgradeSoldier fail uid=%u type=%u level=%u", uid, type, level);
		ret = PROTOCOL_RET_SOLDIER_FAIL;
	}

	CNetPacket sRspPacket;
	sRspPacket.uid = uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_SOLDIER);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_SOLDIER_UPGRADE);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(type);
	selfWriter.AppendUInt32(ret == 0 ? pSoldier->getCu() : 0);

	PlayerManager::getInstance()->sendToAccess(&sRspPacket);

	m_player->getActivenessManager()->onUpSoldier();

	debug_log("uid=%u,id=%u,lv=%u", uid, type, level);

	return true;
}
bool SoldierManager::doSoldierUpgradeFinishNow(CNetPacket* packet) {
	uint32_t uid = packet->uid;
	if (m_player == NULL) {
		error_log("m_player is NULL uid=%u", uid);
		return false;
	}
	byte ret = 0;
	CSoldierUpgradeFinishNowProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CSoldierUpgradeFinishNowProtocol_fail&uid=%u", uid);
		ret = PROTOCOL_RET_SOLDIER_PACKET_ERROR;
	}
	byte payType = protocol.payType;
	uint32_t type = protocol.type;
	Soldier* pSoldier = NULL;
	if (ret == 0 && (pSoldier = getSoldierByType(type)) == NULL) {
		error_log("soldier not exist uid=%u type=%u", uid, type);
		ret = PROTOCOL_RET_SOLDIER_NOT_EXIST;
	}
	if (ret == 0 && m_player == NULL) {
		error_log("m_player is NULL uid=%u", uid);
		ret = PROTOCOL_RET_SOLDIER_FAIL;
	}
	if (ret == 0 && pSoldier->getCu() > 0) {
		uint32_t leftTime = pSoldier->getCu();
		uint32_t pay = ceil(pow(leftTime / 60.0, 0.98) - pow(leftTime / 3600.0, 0.98));
		string code;
		String::Format(code, "soldier_upgrade_finish_now_ud=%u_cu=%u", pSoldier->getUD(), pSoldier->getCu());
		MoneyCost cost;
		if (ret == 0 && !m_player->getPay(payType, pay, cost)) {
			error_log("getPay fail uid=%u pay=%u", uid, pay);
			ret = PROTOCOL_RET_SOLDIER_FAIL;
		}
		if (ret == 0 && !m_player->getRm()->useMoney(cost, code)) {
			error_log("useMoney fail uid=%u pay=%u", uid, pay);
			ret = PROTOCOL_RET_SOLDIER_FAIL;
		}
		if (ret == 0) {
			pSoldier->setCu(0);
			if (ret == 0 && !m_player->doUpgradeSoldierOver(pSoldier)) {
				error_log("doUpgradeSoldierOver fail uid=%u type=%u", uid, type);
				ret = PROTOCOL_RET_SOLDIER_FAIL;
			}
			if (ret == 0 && !m_player->removeSoldierTimer(pSoldier)) {
				error_log("removeSoldierTimer fail uid=%u type=%u", uid, type);
				ret = PROTOCOL_RET_SOLDIER_FAIL;
			}
		}
	}

	CNetPacket sRspPacket;
	sRspPacket.uid = uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_SOLDIER);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_SOLDIER_UPGRADE_FINISH_NOW);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(type);
	PlayerManager::getInstance()->sendToAccess(&sRspPacket);
	return true;
}
bool SoldierManager::doSoldierTrain(CNetPacket* packet) {
	return true;
}

bool SoldierManager::doSoldierTrainFast(CNetPacket* packet) {
	return true;
}

bool SoldierManager::doSoldierTrainFinishNow(CNetPacket* packet) {
	return true;
}
bool SoldierManager::doSoldierTrainList(CNetPacket* packet) {
	return true;
}
bool SoldierManager::doSoldierTrainSlotOpen(CNetPacket* packet) {
	return false;
}
bool SoldierManager::doSoldierStationQuery(CNetPacket* packet) {
	return true;
}
bool SoldierManager::doSoldierAllianceStationQuery(CNetPacket *packet) {
	return true;
}
bool SoldierManager::doSoldierStation(CNetPacket *packet) {
	return true;
}

bool SoldierManager::doSoldierStationDel(CNetPacket *packet) {
	return true;
}

bool SoldierManager::load(uint32_t uid) {
	release();

	CDataSoldier dbSoldier;
	vector<DataSoldier> dataSoldier;

	if (dbSoldier.GetSoldier(uid, dataSoldier) != 0) {
		error_log("get %u's soldier failed", uid);
		return false;
	}
	setSoldierData(dataSoldier);

	return true;
}

bool SoldierManager::setSoldierData(vector<DataSoldier>& dh) {
	vector<DataSoldier>::iterator iter = dh.begin();
	for (; iter != dh.end(); ++iter) {
		setOneSoldier(iter->uid, iter->id, iter->data);
	}
	return true;
}

bool SoldierManager::setOneSoldier(uint32_t uid, uint32_t id, const string& data) {
	if (id > m_maxUd) {
		m_maxUd = id;
	}

	Soldier* pSoldier = new Soldier();
	if (pSoldier == NULL) {
		error_log("pSoldier is NULL uid=%u id=%u", uid, id);
		return false;
	}
	if (!pSoldier->setData(data)) {
		error_log("equipment_setData_fail&uid=%u&id=%u", uid, id);
		delete pSoldier;
		return true;
	}
	pSoldier->setUid(uid);
	pSoldier->setPropertyManager(m_player->getPm());
	pSoldier->calcProps();
	m_soldiers.insert(make_pair(id, pSoldier));
	return true;
}
bool SoldierManager::addOneSoldier(uint32_t uid, uint32_t id, uint32_t count, const string& reason) {
	if (m_player == NULL) {
		error_log("m_player is NULL uid=%u id=%u", uid, id);
		return false;
	}

	Soldier *pSoldier = getSoldierByType(id);
	if (pSoldier != NULL) {
		pSoldier->setCount(pSoldier->getCount() + count);
		pSoldier->saveData(false);
		BUSI_SOLDIER("add|code=%s|%u|%u|%u|%u|%u|%u|%u",
				reason.c_str(), uid, id, pSoldier->getLevel(), pSoldier->getCount(), count, pSoldier->getStar(), LogicManager::GlobalTime);
		m_player->sendSoldierInfo(pSoldier->getUD());
		m_player->getTaskManager()->onUnlockSoldier(count);
		return true;
	}

	if (!SoldierConfig::getInstance()->isExist(id)) {
		error_log("soldier not exist uid=%u id=%u", uid, id);
		return false;
	}

	pSoldier = new Soldier();
	if (pSoldier == NULL) {
		error_log("new soldier fail uid=%u id=%u", uid, id);
		return false;
	}

	pSoldier->setCu(0);
	pSoldier->setType(id);
	pSoldier->setUD(++m_maxUd);
	pSoldier->setPropertyManager(m_player->getPm());
	pSoldier->setUid(uid);
	pSoldier->setLevel(1);
	pSoldier->setCount(count);
	pSoldier->calcProps();
	pSoldier->setHp(pSoldier->getMaxHp());
	m_soldiers.insert(make_pair(m_maxUd, pSoldier));

	if (!pSoldier->saveData(true)) {
		error_log("saveData fail uid=%u id=%u", uid, id);
		return false;
	}
	m_player->getTaskManager()->onUnlockSoldier(count);
	BUSI_SOLDIER("add|code=%s|%u|%u|%u|%u|%u|%u|%u",
			reason.c_str(), uid, id, pSoldier->getLevel(), pSoldier->getCount(), count, pSoldier->getStar(), LogicManager::GlobalTime);

	if (!m_player->sendSoldierInfo(pSoldier->getUD())) {
		error_log("sendSoldierInfo fail uid=%u ud=%u", pSoldier->getUid(), pSoldier->getUD());
		return false;
	}
	return true;
}
bool SoldierManager::unlockSoldier(uint32_t uid, uint32_t type) {
	return true;
}
bool SoldierManager::upgradeSoldier(uint32_t uid, uint32_t type) {
	Soldier* pSoldier = getSoldierByType(type);
	if (pSoldier == NULL) {
		error_log("not exist soldier uid=%u type=%u", uid, type);
		return false;
	}
	if (pSoldier->getCu() > 0) {
		error_log("soldier being upgrade uid=%u ud=%u type=%u", uid, pSoldier->getCu(), type);
		return false;
	}
	const SoldierItemConfig *cfg = SoldierConfig::getInstance()->getItemConfig(pSoldier->getType());
	if (cfg == NULL) {
		error_log("soldier cfg error uid=%u ud=%u type=%u", uid, pSoldier->getCu(), type);
		return false;
	}
	uint32_t buildingType = 0;
	switch (cfg->type) {
	case SOLDIER_TYPE_VEHICLE:
		buildingType = BUILDING_ID_GARAGE;
		break;
	case SOLDIER_TYPE_ATTACK:
		buildingType = BUILDING_ID_ATTACK_BARRACKS;
		break;
	case SOLDIER_TYPE_DEFEND:
		buildingType = BUILDING_ID_DEFEND_BARRACKS;
		break;
	case SOLDIER_TYPE_WEAPON:
		buildingType = BUILDING_ID_WEAPONS;
		break;
	}
	Building* pBuilding = m_player->getBm()->getBuildingByType(buildingType);
	if (pBuilding == NULL) {
		error_log("not exist barrack uid=%u type=%u", uid, type);
		return false;
	}
	if (pBuilding->getLevel() <= pSoldier->getLevel()) {
		error_log("barrack level not enough needlv=%u soldierLevel=%u", pBuilding->getLevel(), pSoldier->getLevel());
		return false;
	}
	const SoldierItemConfig* pConfig = SoldierConfig::getInstance()->getItemConfig(type);
	if (pConfig == NULL) {
		error_log("getItemConfig fail uid=%u type=%u", uid, type);
		return false;
	}
	ResourceCost cost;
	if (!SoldierConfig::getInstance()->getSoldierUpgradeCost(type, pSoldier->getLevel(), cost)) {
		error_log("getSoldierUpgradeCost fail uid=%u type=%u", uid, type);
		return false;
	}
	string code = "upgrade_soldier_" + CTrans::ITOS(type);
	MoneyCost ncost;
	m_player->getRm()->ResToCash(cost, ncost.cash);
	if (ncost.cash && !m_player->getRm()->useMoney(ncost, code)) {
		error_log("useMoney fail uid=%u type=%u", uid, type);
		return false;
	}
	if (cost.ResSum() && !m_player->getRm()->useResources(cost, code)) {
		error_log("useResources fail uid=%u type=%u", uid, type);
		return false;
	}
	//pSoldier->setCu(1);
	//m_player->addSoldierTimer(pSoldier);
	pSoldier->onUpgradeOver();
	pSoldier->saveData();
	m_player->getTaskManager()->onUpgradeSoldier();
	m_player->addCombat(calcLevelCombat(pSoldier->getQuality(), pSoldier->getLevel()));
	BUSI_SOLDIER("upgrade|code=up|%u|%u|%u|%u|%u|%u|%u",
				pSoldier->getUid(), pSoldier->getType(), pSoldier->getLevel(), pSoldier->getCount(), 0, pSoldier->getStar(), LogicManager::GlobalTime);
	BUSI_MISC("play|soldierupgrade|%u|%u|%u|%u", uid, type, pSoldier->getLevel(), Time::GetGlobalTime());
	return true;
}
bool SoldierManager::autoUnlockSoldier(uint32_t uid, uint32_t lv) {
	return false;
}
bool SoldierManager::existSoldier(uint32_t type) {
	map<uint32_t, Soldier*>::iterator iter = m_soldiers.begin();
	for (; iter != m_soldiers.end(); ++iter) {
		Soldier* pSoldier = iter->second;
		if (pSoldier != NULL && pSoldier->getType() == type) {
			return true;
		}
	}
	return false;
}

bool SoldierManager::getSpawnSoldier(vector<pair<uint32_t, uint32_t> >& vSoldier) {
	for (map<uint32_t, Soldier*>::iterator iter = m_soldiers.begin(); iter != m_soldiers.end(); ++iter) {
		Soldier* pSoldier = iter->second;
		if (pSoldier != NULL /*&& pSoldier->getCount() > 0*/) {
			vSoldier.push_back(make_pair(pSoldier->getType(), pSoldier->getCount()));
		}
	}

	/*
	 if(vSoldier.size() > 0)
	 {
	 vector<pair<uint32_t, uint32_t> >::iterator middle = vSoldier.begin();
	 uint32_t middlePos = BATTLE_MAX_SPAWN_SOLDIER_NUM < vSoldier.size() ? BATTLE_MAX_SPAWN_SOLDIER_NUM : vSoldier.size();
	 advance(middle, middlePos);
	 partial_sort(vSoldier.begin(), middle, vSoldier.end(), spawnSoldierCompare);
	 vSoldier.resize(middlePos);
	 }
	 */
	return true;
}
bool SoldierManager::packInfo(IBuffer *buff) {
	if (buff == NULL) {
		return false;
	}
	PACKET_ENCODE_BEGIN(buff);
	PACKET_ENCODE(UInt32, m_soldiers.size());
	map<uint32_t, Soldier*>::iterator it;
	for (it = m_soldiers.begin(); it != m_soldiers.end(); it++) {
		Soldier *pSoldier = it->second;
		if (pSoldier != NULL) {
			pSoldier->encode(buff);
		}
	}
	return true;
}
Soldier* SoldierManager::getSoldierByType(uint32_t type) {
	for (map<uint32_t, Soldier*>::iterator iter = m_soldiers.begin(); iter != m_soldiers.end(); ++iter) {
		Soldier* pSoldier = iter->second;
		if (pSoldier != NULL && pSoldier->getType() == type) {
			return pSoldier;
		}
	}
	return NULL;
}

Soldier* SoldierManager::getSoldierByUd(uint32_t ud) {
	map<uint32_t, Soldier*>::iterator it = m_soldiers.find(ud);
	return it == m_soldiers.end() ? NULL : it->second;
}

uint32_t SoldierManager::getSoldierCapacity() {
	uint32_t capacity = 0;
	for (map<uint32_t, Soldier*>::iterator iter = m_soldiers.begin(); iter != m_soldiers.end(); ++iter) {
		Soldier* pSoldier = iter->second;
		if (pSoldier != NULL) {
			capacity += pSoldier->getMaxCapacity() * pSoldier->getCount();
		}
	}
	return capacity;
}

uint32_t SoldierManager::getSoldierCount() {
	uint32_t count = 0;
	for (map<uint32_t, Soldier*>::iterator iter = m_soldiers.begin(); iter != m_soldiers.end(); ++iter) {
		Soldier* pSoldier = iter->second;
		if (pSoldier != NULL) {
			count += pSoldier->getCount();
		}
	}
	return count;
}

bool SoldierManager::onSoldierStarReward(uint32_t count, Award &award) {
	if (count == 0) {
		return false;
	}
	const uint32_t pool[4] = { 701, 702, 703, 704 };
	for (uint32_t i = 0; i < count; ++i) {
		int index = Math::GetRandomInt(4);
		AwardInfo item;
		item.id = pool[index];
		item.count = 1;
		item.type = AWARD_TYPE_ITEM;
		award.add(item);
	}
	return true;
}

uint32_t SoldierManager::getInvalidCount(uint32_t type) {
//	uint32_t tcount = m_player->getTroopsManager()->getAttackCount(type);
//	uint32_t rcount = m_player->getSoldierRecoverTrain()->getDelCount(type);
//	return tcount + rcount;
	return 0;
}

bool SoldierManager::sendSoldierList() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_SOLDIER);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_SOLDIER_LIST);
	selfWriter.AppendUInt32(m_soldiers.size());
	map<uint32_t, Soldier*>::iterator it;
	for (it = m_soldiers.begin(); it != m_soldiers.end(); it++) {
		Soldier * pSoldier = it->second;
		if (pSoldier != NULL) {
			pSoldier->encode(&sRspPacket.body);
		} else {
			error_log("pSoldier is NULL uid=%u", sRspPacket.uid);
		}
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool SoldierManager::sendSoldierInfo(uint32_t ud) {
	Soldier* pSoldier = getSoldierByUd(ud);
	if (pSoldier == NULL) {
		error_log("pSoldier is NULL ud=%u", ud);
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = pSoldier->getUid();
	CBufferWriter writer(&sPacket.body);
	writer.AppendByte(PROTOCOL_CMD_SOLDIER);
	writer.AppendByte(PROTOCOL_RSP_SUBCMD_SOLDIER_INFO);
	writer.AppendByte(0);
	pSoldier->encode(&sPacket.body);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
	return true;
}

bool SoldierManager::checkSoldierNum(uint32_t type, uint32_t level, uint32_t count) {
	Soldier* pSoldier = getSoldierByType(type);
	if (pSoldier == NULL) {
		return false;
	}
	uint32_t curLevel = pSoldier->getLevel();
	if (pSoldier->getCu() > 0) {
		curLevel += 1;
	}
	return curLevel >= level && pSoldier->getCount() >= count;
}

bool SoldierManager::doSoldierAllianceStationAdd(CNetPacket *packet) {
	return true;
}

bool SoldierManager::doSoldierStrong(CNetPacket *packet) {
	return false;
}

bool SoldierManager::doSoldierStar(CNetPacket *packet) {
	byte ret = 0;
	CSoldierStrongProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		ret = PROTOCOL_RET_SOLDIER_PACKET_ERROR;
	}

	Soldier *pSoldier = NULL;
	if (ret == 0 && (pSoldier = getSoldierByType(protocol.type)) == NULL) {
		error_log("get soldier error uid=%u type=%u", packet->uid, protocol.type);
		ret = PROTOCOL_RET_SOLDIER_NOT_EXIST;
	}

	uint32_t cost = 0;
	if (ret == 0 && (cost = StrongConfig::getInstance()->getSoldierCost(protocol.type, pSoldier->getStar())) == 0) {
		error_log("get soldier error uid=%u type=%u", packet->uid, protocol.type);
		ret = PROTOCOL_RET_SOLDIER_NOT_EXIST;
	}

	if (ret == 0 && pSoldier->getCount() < cost + getInvalidCount(protocol.type) + 1) {
		error_log("cost error uid=%u equip=%u count=%u", packet->uid, protocol.type, cost);
		ret = PROTOCOL_RET_SOLDIER_FAIL;
	}

	Award result;
	if (ret == 0) {
		uint32_t reward_count = StrongConfig::getInstance()->getSoldierReward(protocol.type, pSoldier->getStar());
		pSoldier->setCount(pSoldier->getCount() - cost);
		uint32_t old_star = pSoldier->getStar();
		pSoldier->setStar(pSoldier->getStar() + 1);
		pSoldier->calcProps();
		if (!pSoldier->saveData()) {
			ret = PROTOCOL_RET_SOLDIER_FAIL;
		}
		m_player->addCombat(calcStarCombat(pSoldier->getType(), old_star, pSoldier->getStar()));

		BUSI_SOLDIER("star|code=up|%u|%u|%u|%u|%d|%u|%u",
				packet->uid, pSoldier->getType(), pSoldier->getLevel(), pSoldier->getCount(), 0-cost, pSoldier->getStar(), LogicManager::GlobalTime);
		Award award;
		onSoldierStarReward(reward_count, award);
		if (!award.get().empty()) {
			m_player->doReward(&award, "soldier_star", false, &result);
		}
	}

	sendSoldierList();

	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_SOLDIER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SOLDIER_STAR);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(pSoldier == NULL ? 0 : pSoldier->getType());
	const vector<AwardInfo> &awardInfo = result.get();
	selfWriter.AppendUInt32(awardInfo.size());
	vector<AwardInfo>::const_iterator itr = awardInfo.begin();
	for (; itr != awardInfo.end(); ++itr) {
		selfWriter.AppendByte(itr->type);
		selfWriter.AppendUInt32(itr->id);
		selfWriter.AppendUInt32(itr->count);
	}
	PlayerManager::getInstance()->sendToAccess(&sRspPacket);

	debug_log("uid=%u type=%u", packet->uid, protocol.type);

	m_player->getTaskManager()->onSoldierUpgrade();

	if (0 == ret) {
		BUSI_MISC("play|soldierstar|%u|%u|%u|%u", m_player->getUid(), protocol.type, pSoldier->getStar(), Time::GetGlobalTime());
	}
	return true;
}

bool SoldierManager::doSoldierSell(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CSoldierSellProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onSoldierSell(PROTOCOL_RET_SOLDIER_FAIL);
	}
	uint32_t score = 0;
	vector< pair<uint32_t, uint32_t> >::iterator itr = proto.data.begin();
	for (; itr != proto.data.end(); ++itr) {
		const SoldierItemConfig *cfg = SoldierConfig::getInstance()->getItemConfig(itr->first);
		if (cfg == NULL) {
			error_log("cfg error uid=%u id=%u", uid, itr->first);
			continue;
		}
		if (cfg->q >= 3) {
			error_log("color error uid=%u id=%u", uid, itr->first);
			continue;
		}
		Soldier *soldier = getSoldierByType(itr->first);
		if (soldier == NULL || soldier->getCount() < itr->second) {
			error_log("count error uid=%u id=%u", uid, itr->first);
			continue;
		}
		soldier->setCount(soldier->getCount() - itr->second);
		soldier->saveData();
		BUSI_SOLDIER("sub|code=sell|%u|%u|%u|%u|%d|%u|%u",
				packet->uid, soldier->getType(), soldier->getLevel(), soldier->getCount(), 0-itr->second, soldier->getStar(), LogicManager::GlobalTime);
		if (cfg->q == 1) {
			score += 2 * itr->second;
		} else if (cfg->q == 2) {
			score += 6 * itr->second;
		}
	}
	if (score != 0) {
		ResourceCost cost;
		cost.p2 = score;
		m_player->getRm()->addResources(cost, "sell_soldier");
	}

	m_player->sendBoxScore();

	onSoldierSell(PROTOCOL_RET_SOLDIER_SUCCESS);

	sendSoldierList();

	debug_log("uid=%u");

	return true;
}

bool SoldierManager::doBoxScore(CNetPacket *packet) {
	m_player->sendBoxScore();
	return true;
}

bool SoldierManager::doBoxReward(CNetPacket *packet) {
	const RecyclingItem *cfg = RecyclingConfig::getInstance()->getItem(m_player->getLevel());
	if (cfg == NULL) {
		error_log("cfg error uid=%u lv=%u", m_player->getUid(), m_player->getLevel());
		return onBoxReward(PROTOCOL_RET_SOLDIER_FAIL);
	}
	if (m_player->getRm()->getResources()->p2 < cfg->cost) {
		error_log("cost error uid=%u lv=%u", m_player->getUid(), m_player->getLevel());
		return onBoxReward(PROTOCOL_RET_SOLDIER_FAIL);
	}
	if (cfg->skill.empty()) {
		error_log("skill error uid=%u lv=%u", m_player->getUid(), m_player->getLevel());
		return onBoxReward(PROTOCOL_RET_SOLDIER_FAIL);
	}

	map<uint32_t, uint32_t> skill;
	for (int i = 0; i < cfg->count; ++i) {
		uint16_t s = cfg->skill[Math::GetRandomInt(cfg->skill.size())];
		if (skill.count(s)) {
			skill[s] += 1;
		} else {
			skill[s] = 1;
		}
	}
	Award reward;
	for (map<uint32_t, uint32_t>::iterator itr = skill.begin(); itr != skill.end(); ++itr) {
		AwardInfo rewardInfo;
		rewardInfo.type = AWARD_TYPE_SKILL;
		rewardInfo.count = itr->second;
		rewardInfo.id = itr->first;
		reward.add(rewardInfo);
	}
	AwardInfo r1;
	r1.type = AWARD_TYPE_R1;
	r1.count = RecyclingConfig::getInstance()->getR1(cfg->res);
	AwardInfo r2;
	r2.type = AWARD_TYPE_R2;
	r2.count = cfg->res - r1.count;
	reward.add(r1);
	reward.add(r2);

	string code = "recycling_box_" + CTrans::ITOS(m_player->getLevel());
	ResourceCost cost;
	cost.p2 = cfg->cost;
	if (!m_player->getRm()->useResources(cost, code)) {
		error_log("cost error uid=%u lv=%u", m_player->getUid(), m_player->getLevel());
		return onBoxReward(PROTOCOL_RET_SOLDIER_FAIL);
	}

	m_player->doReward(&reward, "recycling_box_" + CTrans::ITOS(m_player->getLevel()));

	onBoxReward(PROTOCOL_RET_SOLDIER_SUCCESS);

	m_player->sendBoxScore();

	debug_log("uid=%u,lv=%u", m_player->getUid(), m_player->getLevel());

	return true;
}

bool SoldierManager::onSoldierSell(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter selfWriter(sp.GetBody());
	selfWriter.AppendByte(PROTOCOL_CMD_SOLDIER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SOLDIER_ADD_BOX_SCORE);
	selfWriter.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool SoldierManager::onBoxReward(byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter selfWriter(sp.GetBody());
	selfWriter.AppendByte(PROTOCOL_CMD_SOLDIER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_SOLDIER_BOX_REWARD);
	selfWriter.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

uint32_t SoldierManager::calcStarCombat(uint32_t type, uint32_t f, uint32_t t) {
	const SoldierItemConfig *cfg = SoldierConfig::getInstance()->getItemConfig(type);
	if (cfg == NULL) {
		return 0;
	}
	return StrongConfig::getInstance()->getStrongPower(cfg->q, f, t);
}

uint32_t SoldierManager::calcLevelCombat(uint32_t color, uint32_t lv) {
	return SoldierConfig::getInstance()->getLevelPower(color, lv);
}
