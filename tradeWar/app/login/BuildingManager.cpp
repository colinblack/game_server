/*
 * BuildingManager.cpp
 *
 *  Created on: 2015-9-1
 *      Author: Administrator
 */

#include "BuildingManager.h"
#include "ProtocolInc.h"
#include "Player.h"
#include "DataInc.h"
#include "PlayerManager.h"
#include "BuildingConfig.h"
#include "ProtocolBuilding.h"
#include "SocialManager.h"
#include "VipConfig.h"
#include "StrongConfig.h"
#include "AutoTransportManager.h"

BuildingManager::BuildingManager() {
	m_maxUd = 0;
	m_player = NULL;
}
BuildingManager::~BuildingManager() {
	map<uint32_t, Building*>::iterator it = m_buildings.begin();
	for (; it != m_buildings.end(); ++it) {
		delete it->second;
	}
	m_buildings.clear();
}
void BuildingManager::release() {
	map<uint32_t, Building*>::iterator it = m_buildings.begin();
	for (; it != m_buildings.end(); ++it) {
		delete it->second;
	}
	m_buildings.clear();
	m_player->clearAllTimer();
}
bool BuildingManager::doBuildingHarvest(uint32_t uid, Building* pBuilding, int ret, uint32_t addResource) {
	if (pBuilding == NULL) {
		error_log("pBuilding is NULL");
		ret = PROTOCOL_RET_BUILDING_NOT_EXIST;
	}
	uint32_t ud = 0;
	if (ret == 0) {
		ud = pBuilding->getUD();
		uint32_t curStorage = 0;
		ResourceCost cost;
		uint32_t* pResource = NULL;
		uint32_t storageMaxCapacity = 0;
		if (pBuilding->getType() == BUILDING_ID_RESOURCE_R1) {
			pResource = &cost.r1;
			curStorage = m_player->getRm()->getResources()->r1;
			storageMaxCapacity = getResourceGoldCapacity();
		} else if (pBuilding->getType() == BUILDING_ID_RESOURCE_R2) {
			pResource = &cost.r2;
			curStorage = m_player->getRm()->getResources()->r2;
			storageMaxCapacity = getResourceMagicCapacity();
		} else {
			error_log("building is not valid resource building type=%u uid=%u", pBuilding->getType(), uid);
			ret = PROTOCOL_RET_BUILDING_FAIL;
		}
		if (ret == 0 && pResource != NULL) {
			uint32_t currCapacity = 0;
			if (pBuilding->getType() == BUILDING_ID_RESOURCE_R2) {
				currCapacity = pBuilding->getProduce();
			} else {
				currCapacity = pBuilding->getCapacity();
			}
			if (addResource > currCapacity || addResource == 0) {
				addResource = currCapacity;
			}
			debug_log("addResource=%u,type=%u,level=%u,curStorage=%u,storageMaxCapacity=%u,rate=%f,currCapacity=%u", addResource, pBuilding->getType(), pBuilding->getLevel(), curStorage, storageMaxCapacity, m_player->getExpRate(), currCapacity);

			if (addResource + curStorage > storageMaxCapacity) {
				addResource = storageMaxCapacity - curStorage;
			}
			if (addResource > 0) {
				if (pBuilding->getType() == BUILDING_ID_RESOURCE_R2) {
					pBuilding->setProduce(currCapacity > addResource ? currCapacity - addResource : 0);
				} else {
					if (pBuilding->getCapacity() > addResource) {
						pBuilding->setCapacity(pBuilding->getCapacity() - addResource);
					} else {
						pBuilding->setCapacity(0);
					}
					pBuilding->saveData();
				}
				*pResource = addResource * m_player->getExpRate();
				float rate = m_player->getVipManager()->getRight(VipManager::VIP_RIGHT_HARVEST);
				*pResource += static_cast<float>(*pResource) * rate;
				m_player->getRm()->addResources(cost, "collect_building_resource");
				if (pBuilding->getType() == BUILDING_ID_RESOURCE_R2) {
					m_player->getTaskManager()->onProduceRes(cost.ResSum());
				}
			}
		}
	}

	// 回包
	CNetPacket sRspPacket;
	sRspPacket.uid = uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BUILDING);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDING_COLLECT_RESOURCE);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(ud);
	selfWriter.AppendUInt32(pBuilding == NULL ? 0 : pBuilding->getCp());
	selfWriter.AppendUInt32(pBuilding == NULL ? 0 : pBuilding->getCapacity());

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", uid);
		return false;
	}
	if (0 == ret) {
		debug_log("uid=%u,id=%u,cp=%u", uid, pBuilding->getType(), pBuilding->getCp());
	}
	return true;
}
byte BuildingManager::upgradeOneBuilding(uint32_t ud, bool acc) {
	uint32_t uid = m_player->getUid();
	Building* pBuilding = getBuilding(ud);
	if (pBuilding == NULL) {
		error_log("find_building_fail uid=%u bud=%u", uid, ud);
		return PROTOCOL_RET_BUILDING_FAIL;
	}
	uint32_t bId = pBuilding->getType();
	uint32_t level = pBuilding->getLevel() + 1;
	if (!checkRelyBuilding(bId, level)) {
		error_log("rely build error uid=%u bud=%u bid=%u blv=%u", uid, ud, bId, level);
		return PROTOCOL_RET_BUILDING_FAIL;
	}
	// 检查是否在建造
	if (pBuilding->getCb() > 0) {
		error_log("already in build uid=%u bud=%u", uid, ud);
		return PROTOCOL_RET_BUILDING_FAIL;
	}
	// 检查是否已经在升级中
	if (pBuilding->getCu() > 0) {
		error_log("already in upgrade uid=%u bud=%u", uid, ud);
		return PROTOCOL_RET_BUILDING_FAIL;
	}
	// 检查资源数量
	const BuildingBuildCost *bc = BuildingConfig::getInstance()->getBuildCost(bId, level);
	if (bc == NULL) {
		error_log("getBuildCost_fail uid=%u bud=%u", uid, ud);
		return PROTOCOL_RET_BUILDING_FAIL;
	}
	// 剩余资源是否足够升级
	if (bc->r1 > 0 || bc->r2 > 0) {
		ResourceCost cost;
		cost.r1 = bc->r1;
		cost.r2 = bc->r2;
		string code;
		String::Format(code, "upgrade_building_%u_%u_%u", pBuilding->getUD(), pBuilding->getType(), level);
		MoneyCost ncost;
		m_player->getRm()->ResToCash(cost, ncost.cash);
		if (ncost.cash && !m_player->getRm()->useMoney(ncost, code)) {
			error_log("useMoney error uid=%u bud=%u", uid, ud);
			return PROTOCOL_RET_BUILDING_FAIL;
		}

		if (cost.ResSum() && !m_player->getRm()->useResources(cost, code)) {
			error_log("useResources uid=%u bud=%u", uid, ud);
			return PROTOCOL_RET_BUILDING_FAIL;
		}
	}

	pBuilding->setLevel(level);
	m_player->doUpgradeBuildingOver(pBuilding);
	m_player->sendBuildingActionOver(PROTOCOL_CMD_BUILDING, PROTOCOL_RSP_SUBCMD_BUILDING_UPGRADE_OVER, pBuilding, pBuilding->getLevel());
	m_player->getActivenessManager()->onBuild();
	if (pBuilding->getType() == BUILDING_ID_RESOURCE_R1) {
		AutoTransportManager::getInstance()->updateLevel(m_player->getUid());
	}
	BUSI_MISC("play|buildingupgrade|%u|%u|%u|%u", uid, bId, level, Time::GetGlobalTime());
	return PROTOCOL_RET_BUILDING_SUCCESS;
}
bool BuildingManager::loadTower(uint32_t uid) {
	CDataTower dbTower;
	vector<DataTower> towers;
	int ret = 0;
	ret = dbTower.GetTowers(uid, towers);
	for (vector<DataTower>::iterator itr = towers.begin(); itr != towers.end(); ++itr) {
		if (itr->id < TOWER_STAR_MIN_ID) {
			m_tower.insert(make_pair(itr->id, *itr));
		} else {
			m_towerStar.insert(make_pair(itr->id, itr->level));
		}
	}
	initTowerStar();
	return true;
}
bool BuildingManager::initTowerStar() {
	map<uint32_t, DataTower>::iterator itr = m_tower.begin();
	for (; itr != m_tower.end(); ++itr) {
		const BuildingItemConfig *cfg = BuildingConfig::getInstance()->getItemConfig(itr->first);
		if (cfg == NULL) {
			continue;
		}
		DataTower &tower = itr->second;
		if (m_towerStar.count(cfg->group)) {
			tower.star = m_towerStar[cfg->group];
		}
	}
	return true;
}
bool BuildingManager::saveTower(uint32_t id, bool isNew) {
	if (!m_tower.count(id)) {
		return false;
	}
	CDataTower dbTower;
	DataTower tower;
	tower.uid = m_player->getUid();
	tower.id = id;
	tower.level = m_tower[id].level;
	if (isNew) {
		dbTower.AddTower(tower);
	} else {
		dbTower.SetTower(tower);
	}
	return true;
}
bool BuildingManager::saveTowerStar(uint32_t id, bool isNew) {
	if (!m_towerStar.count(id)) {
		return false;
	}
	CDataTower dbTower;
	DataTower tower;
	tower.uid = m_player->getUid();
	tower.id = id;
	tower.level = m_towerStar[id];
	if (isNew) {
		dbTower.AddTower(tower);
	} else {
		dbTower.SetTower(tower);
	}
	debug_log("uid=%u,id=%u,lv=%u,isnew=%u", tower.uid, tower.id, tower.level, isNew);
	return true;
}
bool BuildingManager::calcTowerCombat(uint32_t id, uint32_t lv) {
	const BuildingItemConfig *cfg = BuildingConfig::getInstance()->getItemConfig(id);
	if (cfg == NULL) {
		return false;
	}
	m_player->addCombat(BuildingConfig::getInstance()->getBuildingPower(cfg->color, lv));
	return true;
}
bool BuildingManager::checkRelyBuilding(uint32_t id, uint32_t lv) {
	const RelyBuildingAll *rely_cfg = BuildingConfig::getInstance()->getRelyBuilding(id, lv);
	if (rely_cfg == NULL) {
		error_log("rely error bid=%u blv=%u", id, lv);
		return false;
	}
	bool flag = true;
	vector<RelyBuilding>::const_iterator itr = rely_cfg->data.begin();
	for (; itr != rely_cfg->data.end(); ++itr) {
		if (itr->type == RELY_BUILDING_BUILDING) {
			Building *building = getBuildingByType(itr->id);
			if (building == NULL || building->getLevel() < itr->level) {
				flag = false;
			}
		} else if (itr->type == RELY_BUILDING_GATE) {
			if (m_player->getBattleGateMgr()->getCurr() < itr->level) {
				flag = false;
			}
		}
	}
	return flag;
}
uint32_t BuildingManager::getTowerLevel(uint32_t id) {
	return m_tower.count(id) ? m_tower[id].level : 0;
}
bool BuildingManager::unlockTower(uint32_t id) {
	map<uint32_t, uint32_t> ids;
	BuildingConfig::getInstance()->getRelyBuildingGate(id, ids);
	for (map<uint32_t, uint32_t>::iterator itr = ids.begin(); itr != ids.end(); ++itr) {
		if (m_tower.count(itr->first)) {
			continue;
		}
		m_tower[itr->first].level = 1;
		saveTower(itr->first, true);
		calcTowerCombat(itr->first, m_tower[itr->first].level);
	}
	debug_log("uid=%u,gateid=%u,ids=%u", m_player->getUid(), id, ids.size());
	return true;
}
bool BuildingManager::sendTower() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&sp.body);
	writer.AppendByte(PROTOCOL_CMD_BUILDING);
	writer.AppendByte(PROTOCOL_SUBCMD_BUILDING_TOWER);
	writer.AppendUInt32(m_tower.size());
	for (map<uint32_t, DataTower>::iterator itr = m_tower.begin(); itr != m_tower.end(); ++itr) {
		writer.AppendUInt32(itr->first);
		writer.AppendUInt32(itr->second.level);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool BuildingManager::sendTowerStar() {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&sp.body);
	writer.AppendByte(PROTOCOL_CMD_BUILDING);
	writer.AppendByte(PROTOCOL_SUBCMD_BUILDING_TOWER_STAR_INFO);
	writer.AppendUInt32(m_towerStar.size());
	for (map<uint32_t, uint32_t>::iterator itr = m_towerStar.begin(); itr != m_towerStar.end(); ++itr) {
		writer.AppendUInt32(itr->first - TOWER_STAR_MIN_ID);
		writer.AppendUInt32(itr->second);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool BuildingManager::load(uint32_t uid) {
	release();
	CDataBuilding dbBuilding;
	vector<DataBuilding> dataBuilding;
	if (dbBuilding.GetBuilding(uid, dataBuilding) != 0) {
		error_log("get %u's building failed", uid);
		return false;
	}
	setBuildingData(dataBuilding);
	loadTower(uid);
	return true;
}
bool BuildingManager::setOneBuilding(uint32_t uid, uint32_t id, const string &data) {
	if (id > m_maxUd) {
		m_maxUd = id;
	}
	Json::Value jsonBuild;
	Json::Reader reader;
	if (!reader.parse(data, jsonBuild)) {
		error_log("hero data json parse failed:%s", data.c_str());
		return false;
	}
	if (!jsonBuild.isMember("t")) {
		error_log("must has field t,%s", data.c_str());
		return false;
	}
	uint32_t bt = 0;
	if (!Json::GetUInt(jsonBuild, "t", bt)) {
		error_log("get building type fail uid=%u ud=%u", uid, id);
		return false;
	}
	const BuildingItemConfig *bc = BuildingConfig::getInstance()->getItemConfig(bt);
	if (bc == NULL) {
		error_log("get building config fail uid=%u ud=%u", uid, id);
		return false;
	}
	Building* pBuilding = Building::newBuildingByType(bt);
	if (!pBuilding) {
		error_log("unknow building type %u uid %u", bt, uid);
		return false;
	}
	if (!pBuilding->setData(jsonBuild)) {
		error_log("building_setData_fail&uid=%u&id=%u", uid, id);
		delete pBuilding;
		return false;
	}
	pBuilding->setUid(uid);
	pBuilding->setPropertyManager(m_player->getPm());
	pBuilding->propsCalc();
	if (!pBuilding->initHp()) {
		error_log("initHp_fail&type=%u", pBuilding->getType());
	}
	if (pBuilding->getHp() > pBuilding->getMaxHp()) {
		pBuilding->setHp(pBuilding->getMaxHp());
	}
	if (IS_VALID_NPC_UID(uid)) {
		pBuilding->setHp(pBuilding->getMaxHp());
	}
	pBuilding->calcCombat();
	if (!pBuilding->initProduceTime()) {
		error_log("initProduceTime fail uid=%u ud=%u", pBuilding->getUid(), pBuilding->getUD());
	}
	m_buildings.insert(make_pair(id, pBuilding));
	return true;
}
bool BuildingManager::setBuildingData(vector<DataBuilding> &db) {
	vector<DataBuilding>::iterator iter = db.begin();
	for (; iter != db.end(); ++iter) {
		setOneBuilding(iter->uid, iter->id, iter->data);
	}
	return true;
}
Building* BuildingManager::getBuildingByType(uint32_t type) {
	for (map<uint32_t, Building*>::iterator it = m_buildings.begin(); it != m_buildings.end(); it++) {
		Building * pBuilding = it->second;
		if (pBuilding != NULL && pBuilding->getType() == type) {
			return pBuilding;
		}
	}
	return NULL;
}
Building* BuildingManager::getBaseBuilding() {
	return getBuildingByType(BUILDING_ID_BASE);
}
bool BuildingManager::save(uint32_t uid) {
	map<uint32_t, Building*>::iterator iter = m_buildings.begin();
	for (; iter != m_buildings.end(); ++iter) {
		iter->second->saveData();
	}
	return true;
}
bool BuildingManager::doPacket(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_BUILDINGLIST:
		doBuildingQueryAll(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_QUERY_ONE:
		doBuildingQueryOne(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_BUILD:
		doBuildingCreate(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_MOVE:
		doBuildingMove(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_UPGRADE:
		doBuildingUpgrade(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_COLLECT_RESOURCE:
		doBuildingHarvest(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_REMOVE:
		doBuildingRemove(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_UPGRADE_TOWER:
		doTowerUpgrade(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_TOWER_STAR_UPGRADE:
		doTowerUpgradeStar(packet);
		break;
	default:
		return false;
	}
	return true;
}
bool BuildingManager::doBuildingQueryAll(CNetPacket *packet) {
	sendBuildingList();
	return true;
}
bool BuildingManager::doBuildingQueryOne(CNetPacket *packet) {
	byte ret = 0;
	CQueryOneBuildingProtocol qob;
	if (!qob.Decode(&(packet->body))) {
		error_log("decodeQueryOneBuilding_fail&uid=%u", packet->uid);
		ret = PROTOCOL_RET_BUILDING_PACKET_ERROR;
	}
	uint32_t ud = qob.ud;

	CNetPacket sRspPacket;
	sRspPacket.uid = packet->uid;
	sRspPacket.cmd = PROTOCOL_CMD_BUILDING;
	sRspPacket.subCmd = PROTOCOL_RSP_SUBCMD_BUILDING_QUERY_ONE;
	CBufferWriter selfWriter(&sRspPacket.body);

	selfWriter.AppendByte(PROTOCOL_CMD_BUILDING);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDING_QUERY_ONE);

	map<uint32_t, Building*>::iterator it = m_buildings.find(ud);
	if (ret == 0 && it == m_buildings.end()) {
		error_log("not_find_building&ud=%u", ud);
		ret = PROTOCOL_RET_BUILDING_PACKET_ERROR;
	}
	selfWriter.AppendByte(ret);
	if (ret == 0) {
		it->second->encode(&sRspPacket.body);
	} else {
		selfWriter.AppendUInt32(ud); // 查询失败返回建筑ud
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", packet->uid);
		return false;
	}
	return true;
}

bool BuildingManager::doBuildingCreate(CNetPacket *packet) {
	if (m_player == NULL) {
		error_log("m_player is NULL");
		return false;
	}
	byte ret = PROTOCOL_RET_BUILDING_SUCCESS;
	CBuildBuildingProtocol bb;
	if (!bb.Decode(&(packet->body))) {
		error_log("decodeBuildBuilding_fail&uid=%u", packet->uid);
		ret = PROTOCOL_RET_BUILDING_PACKET_ERROR;
	}
	const uint32_t level = 1;
	uint32_t uid = packet->uid;
	uint16_t bId = bb.bId;
	int x = bb.x.pi;
	int y = bb.y.pi;
	if (ret == 0) {
		map<uint32_t, Building*>::iterator itr = m_buildings.begin();
		for (; itr != m_buildings.end(); ++itr) {
			Building *pb = itr->second;
			if (pb == NULL) {
				continue;
			}
			if (pb->getType() == bId) {
				error_log("checkBuildingCountLimit_fail uid=%u bId=%u", uid, bId);
				ret = PROTOCOL_RET_BUILDING_COUNT_LIMIT;
				break;
			}
			if (pb->getX() == x) {
				error_log("checkBuildingPoint_fail uid=%u bId=%u", uid, bId);
				ret = PROTOCOL_RET_BUILDING_POSITION_ERROR;
				break;
			}
		}
	}
	const BuildingBuildCost *bc = BuildingConfig::getInstance()->getBuildCost(bId, level);
	if (ret == 0 && bc == NULL) {
		error_log("getBuildCost_fail uid=%u bId=%u", uid, bId);
		ret = PROTOCOL_RET_BUILDING_FAIL;
	}

	string code;
	String::Format(code, "upgrade_building_%u_%u_%u", m_maxUd + 1, bId, level);
	if (ret == 0) {
		ResourceCost rc;
		rc.r1 = bc->r1;
		rc.r2 = bc->r2;
		if (!m_player->getRm()->useResources(rc, code)) {
			error_log("use_res_fail uid=%u bId=%u", uid, bId);
			ret = PROTOCOL_RET_BUILDING_FAIL;
		}
	}
	Building* pBuilding = NULL;
	if (ret == 0 && (pBuilding = Building::newBuildingByType(bId)) == NULL) {
		error_log("newBuildingByType uid=%u bid=%u", uid, bId);
		ret = PROTOCOL_RET_BUILDING_FAIL;
	}

	if (ret == 0) {
		pBuilding->setUid(uid);
		pBuilding->setType(bId);
		pBuilding->setPosition(x, y);
		pBuilding->setCb(0);
		pBuilding->setUpts(Time::GetGlobalTime());
		pBuilding->setCp(Time::GetGlobalTime());
		pBuilding->setUD(++m_maxUd);
		pBuilding->setLevel(level);
		pBuilding->setStatus(0);
		pBuilding->setPropertyManager(m_player->getPm());
		pBuilding->propsCalc();
		pBuilding->setHp(pBuilding->getMaxHp());
		if (!pBuilding->initProduceTime()) {
			error_log("initProduceTime fail uid=%u ud=%u", pBuilding->getUid(), pBuilding->getUD());
		}
		if (ret == 0 && !pBuilding->saveData(true)) {
			error_log("saveData_fail uid=%u bId=%u ud=%u", uid, bId, m_maxUd);
			ret = PROTOCOL_RET_BUILDING_FAIL;
			delete pBuilding;
			pBuilding = NULL;
		}
		if (ret == 0) {
			m_buildings.insert(make_pair(pBuilding->getUD(), pBuilding));
			m_player->doUpgradeBuildingOver(pBuilding);
			if (pBuilding->getType() == BUILDING_ID_RESOURCE_R1) {
				AutoTransportManager::getInstance()->updateLevel(m_player->getUid());
			}
		}
	}

	// 回包
	CNetPacket sRspPacket;
	sRspPacket.uid = packet->uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	sRspPacket.cmd = PROTOCOL_CMD_BUILDING;
	sRspPacket.subCmd = PROTOCOL_RSP_SUBCMD_BUILDING_BUILD;
	selfWriter.AppendByte(PROTOCOL_CMD_BUILDING);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDING_BUILD);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(m_maxUd);
	selfWriter.AppendUInt32(x);
	selfWriter.AppendUInt32(y);
	selfWriter.AppendUInt32(bId);

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail uid=%u bId=%u", packet->uid, bId);
		return false;
	}

	return true;
}

bool BuildingManager::doBuildingMove(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	byte ret = 0;
	CMoveBuildingProtocol mb;
	if (!mb.Decode(&(packet->body))) {
		error_log("decodeMoveBuilding_fail&uid=%u", uid);
		ret = PROTOCOL_RET_BUILDING_PACKET_ERROR;
	}
	uint32_t ud = mb.ud;
	Property x = mb.x;
	Property y = mb.y;
	map<uint32_t, Building*>::iterator iter = m_buildings.find(ud);
	if (ret == 0 && iter == m_buildings.end()) {
		error_log("find_building_fail&ud=%u", ud);
		ret = PROTOCOL_RET_BUILDING_FAIL;
	}
	if (ret == 0) {
		Building* pBuilding = iter->second;
		// 存档
		if (ret == 0) {
			pBuilding->setPosition(x.pi, y.pi);
			pBuilding->propsCalc();
			if (!pBuilding->saveData()) {
				error_log("saveData_fail&uid=%u&ud=%u", uid, ud);
				ret = PROTOCOL_RET_BUILDING_FAIL;
			}
		}
	}
	// 回包
	CNetPacket sRspPacket;
	sRspPacket.uid = packet->uid;
	sRspPacket.cmd = PROTOCOL_CMD_BUILDING;
	sRspPacket.subCmd = PROTOCOL_RSP_SUBCMD_BUILDING_MOVE;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BUILDING);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDING_MOVE);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(ud);
	selfWriter.AppendUInt32(x.pui);
	selfWriter.AppendUInt32(y.pui);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", packet->uid);
		return false;
	}

	return true;
}
bool BuildingManager::doBuildingUpgrade(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	byte ret = 0;
	if (m_player == NULL) {
		error_log("m_player is NULL uid=%u", uid);
		return false;
	}
	CUpgradeBuildingProtocol ub;
	if (!ub.Decode(&(packet->body))) {
		error_log("decodeUpgradeBuilding_fail&uid=%u", uid);
		ret = PROTOCOL_RET_BUILDING_PACKET_ERROR;
	}
	const vector<uint32_t>& udVec = ub.udVec;
	vector<Building *> vDones;
	for (uint32_t i = 0; ret == 0 && i < udVec.size(); ++i) {
		ret = upgradeOneBuilding(udVec[i], true);
		if (ret != 0) {
			break;
		}
		Building* pBuilding = getBuilding(udVec[i]);
		vDones.push_back(pBuilding);
	}

	// 回包
	CNetPacket sRspPacket;
	sRspPacket.uid = packet->uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BUILDING);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDING_UPGRADE);
	selfWriter.AppendByte(ret);
	if (ret == 0) {
		selfWriter.AppendUInt32(vDones.size());
		for (uint32_t i = 0; i < vDones.size(); ++i) {
			selfWriter.AppendUInt32(vDones[i]->getUD());
			selfWriter.AppendUInt32(vDones[i]->getType());
		}
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail uid=%u", uid);
		return false;
	}
	return true;
}
bool BuildingManager::doBuildingHarvest(CNetPacket *packet) {
	byte ret = 0;
	CCollectBuildingResourceProtocol cb;
	if (!cb.Decode(&(packet->body))) {
		error_log("CCollectBuildingResourceProtocol_fail&uid=%u", packet->uid);
		ret = PROTOCOL_RET_BUILDING_PACKET_ERROR;
	}
	uint32_t uid = packet->uid;
	uint32_t ud = cb.ud;
	Building * pBuilding = NULL;
	if (ret == 0 && (pBuilding = getBuilding(ud)) == NULL) {
		error_log("find_building_fail&ud=%u", ud);
		ret = PROTOCOL_RET_BUILDING_NOT_EXIST;
	}
	if (!doBuildingHarvest(uid, pBuilding, ret, cb.res)) {
		error_log("singleBuildingCollectResource fail uid=%u ud=%u", uid, ud);
		return false;
	}
	m_player->getActivenessManager()->onHarvest();
	return true;
}
bool BuildingManager::doBuildingRemove(CNetPacket *packet) {
	byte ret = 0;
	CBuildingRemoveProtocol cb;
	if (!cb.Decode(&(packet->body))) {
		error_log("CBuildingRemoveProtocol fail&uid=%u", packet->uid);
		ret = PROTOCOL_RET_BUILDING_PACKET_ERROR;
	}
	uint32_t ud = cb.ud;
	map<uint32_t, Building*>::iterator iter = m_buildings.find(ud);
	if (ret == 0 && iter == m_buildings.end()) {
		error_log("find_building_fail&ud=%u", ud);
		ret = PROTOCOL_RET_BUILDING_FAIL;
	}
	if (ret == 0 && iter->second == NULL) {
		error_log("find_building_fail&ud=%u", ud);
		ret = PROTOCOL_RET_BUILDING_FAIL;
	}
	if (ret == 0 && !Building::delBuilding(iter->second->getUid(), iter->second->getUD())) {
		error_log("del_building_fail&ud=%u&uid=%u", ud, packet->uid);
		ret = PROTOCOL_RET_BUILDING_FAIL;
	}
	if (ret == 0) {
		delete (iter->second);
		iter->second = NULL;
		m_buildings.erase(iter);
	}

	CNetPacket sRspPacket;
	sRspPacket.uid = packet->uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BUILDING);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BUILDING_REMOVE);
	selfWriter.AppendByte(ret);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", packet->uid);
		return false;
	}
	return true;
}
bool BuildingManager::doTowerUpgrade(CNetPacket * packet) {
	uint32_t uid = packet->uid;
	CBuildingTowerUpgradeProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CBuildingTowerUpgradeProtocol fail uid=%u", uid);
		onTowerUpgradeResp(1, 0, 0);
		return false;
	}
	if (!m_tower.count(protocol.id)) {
		error_log("id is not exists uid=%u id=%u", uid, protocol.id);
		onTowerUpgradeResp(1, 0, 0);
		return false;
	}
	uint32_t level = m_tower[protocol.id].level + 1;
	const BuildingBuildCost *bc = BuildingConfig::getInstance()->getBuildCost(protocol.id, level);
	if (bc == NULL) {
		error_log("getBuildCost_fail uid=%u bid=%u", uid, protocol.id);
		onTowerUpgradeResp(1, 0, 0);
		return false;
	}
	ResourceCost cost;
	MoneyCost ncost;
	cost.r1 = bc->r1;
	cost.r2 = bc->r2;
	string code = "tower_upgrade_" + CTrans::ITOS(protocol.id);
	m_player->getRm()->ResToCash(cost, ncost.cash);
	if (ncost.cash && !m_player->getRm()->useMoney(ncost, code)) {
		error_log("useMoney error uid=%u bid=%u", uid, protocol.id);
		onTowerUpgradeResp(1, 0, 0);
		return false;
	}
	if (cost.ResSum() && !m_player->getRm()->useResources(cost, code)) {
		error_log("useResources error uid=%u bid=%u", uid, protocol.id);
		onTowerUpgradeResp(1, 0, 0);
		return false;
	}

	m_tower[protocol.id].level += 1;

	saveTower(protocol.id, false);

	onTowerUpgradeResp(0, protocol.id, m_tower[protocol.id].level);

	m_player->getTaskManager()->onUpgradeTower();
	calcTowerCombat(protocol.id, m_tower[protocol.id].level);
	debug_log("uid=%u,id=%u,lv=%u", uid, protocol.id, level);
	BUSI_MISC("play|towerupgrade|%u|%u|%u|%u", uid, protocol.id, level, Time::GetGlobalTime());
	return true;
}
bool BuildingManager::doTowerUpgradeStar(CNetPacket * packet) {
	uint32_t uid = packet->uid;
	CBuildingTowerUpgradeProtocol protocol;
	if (!protocol.Decode(&(packet->body))) {
		error_log("CBuildingTowerUpgradeProtocol fail uid=%u", uid);
		onTowerUpgradeStarResp(1, 0, 0);
		return false;
	}

	uint32_t id = protocol.id + TOWER_STAR_MIN_ID;
	bool isNew = m_towerStar.find(id) == m_towerStar.end();
	uint32_t star = isNew ? 1 : m_towerStar[id] + 1;
	uint32_t cost = StrongConfig::getInstance()->getTower(protocol.id, star - 1);
	if (cost == 0) {
		error_log("CBuildingTowerUpgradeProtocol fail uid=%u", uid);
		onTowerUpgradeStarResp(1, 0, 0);
		return false;
	}

	uint32_t lv = StrongConfig::getInstance()->getTowerLevelLimit(star - 1);
	Building *altar = getBuildingByType(BUILDING_ID_ALTAR);
	if (altar == NULL || altar->getLevel() < lv) {
		error_log("altar lv error uid=%u lv=%u", uid, lv);
		onTowerUpgradeStarResp(1, 0, 0);
		return false;
	}

	string code = "tower_star_" + CTrans::ITOS(protocol.id) + "_" + CTrans::ITOS(star);
	uint32_t equip_id = 701 + protocol.id;
	if (!m_player->getEm()->useBagItemByType(equip_id, cost, code)) {
		error_log("use item error uid=%u id=%u itemid=%u itemnum=%u", uid, protocol.id, equip_id, cost);
		onTowerUpgradeStarResp(1, 0, 0);
		return false;
	}

	m_towerStar[id] = star;

	saveTowerStar(id, isNew);

	sendTowerStar();

	onTowerUpgradeStarResp(0, protocol.id, star);

	debug_log("uid=%u,id=%u,star=%u", uid, protocol.id, star);
	BUSI_MISC("play|towerstar|%u|%u|%u|%u", uid, id, star, Time::GetGlobalTime());
	return true;
}
void BuildingManager::onTowerUpgradeResp(byte ret, uint32_t id, uint32_t lv) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&sp.body);
	writer.AppendByte(PROTOCOL_CMD_BUILDING);
	writer.AppendByte(PROTOCOL_SUBCMD_BUILDING_UPGRADE_TOWER);
	writer.AppendByte(ret);
	writer.AppendUInt32(id);
	writer.AppendUInt32(lv);

	PlayerManager::getInstance()->sendToAccess(&sp);
}
void BuildingManager::onTowerUpgradeStarResp(byte ret, uint32_t id, uint32_t lv) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(&sp.body);
	writer.AppendByte(PROTOCOL_CMD_BUILDING);
	writer.AppendByte(PROTOCOL_SUBCMD_BUILDING_TOWER_STAR_UPGRADE);
	writer.AppendByte(ret);
	writer.AppendUInt32(id);
	writer.AppendUInt32(lv);

	PlayerManager::getInstance()->sendToAccess(&sp);
}
uint32_t BuildingManager::getBuildingTypeCount(uint32_t buildingId) {
	uint32_t num = 0;
	map<uint32_t, Building*>::iterator itr = m_buildings.begin();
	for (; itr != m_buildings.end(); ++itr) {
		Building *p = itr->second;
		if (p != NULL && p->getType() == buildingId) {
			num++;
		}
	}
	return num;
}
Building* BuildingManager::getBuilding(uint32_t ud) {
	map<uint32_t, Building*>::iterator it = m_buildings.find(ud);
	if (it != m_buildings.end()) {
		return it->second;
	}
	return NULL;
}
uint32_t BuildingManager::getResourceCapacity() {
	uint32_t cap = 0;
	for (map<uint32_t, Building*>::iterator it = m_buildings.begin(); it != m_buildings.end(); ++it) {
		Building * pBuilding = it->second;
		if (pBuilding != NULL && BUILDING_ID_BASE == pBuilding->getType()) {
			cap += pBuilding->getMaxCapacity();
		}
	}
	return cap;
}
uint32_t BuildingManager::getResourceGoldCapacity() {
	uint32_t cap = 0;
	for (map<uint32_t, Building*>::iterator it = m_buildings.begin(); it != m_buildings.end(); ++it) {
		Building * pBuilding = it->second;
		if (pBuilding == NULL) {
			continue;
		}
		uint32_t type = pBuilding->getType();
		if (BUILDING_ID_STORAGE_R1 == type) {
			cap += pBuilding->getMaxCapacity();
		} else if (BUILDING_ID_BASE == type) {
			cap += BASE_MAX_CAPACITY;
		}
	}
	return cap;
}
uint32_t BuildingManager::getResourceMagicCapacity() {
	uint32_t cap = 0;
	for (map<uint32_t, Building*>::iterator it = m_buildings.begin(); it != m_buildings.end(); ++it) {
		Building * pBuilding = it->second;
		if (pBuilding == NULL) {
			continue;
		}
		uint32_t type = pBuilding->getType();
		if (BUILDING_ID_STORAGE_R2 == type) {
			cap += pBuilding->getMaxCapacity();
		} else if (BUILDING_ID_BASE == type) {
			cap += BASE_MAX_CAPACITY;
		}
	}
	return cap;
}
uint32_t BuildingManager::getBuildingLevel(uint32_t type) {
	for (map<uint32_t, Building*>::iterator it = m_buildings.begin(); it != m_buildings.end(); it++) {
		Building * pBuilding = it->second;
		if (pBuilding && pBuilding->getType() == type) {
			return pBuilding->getLevel();
		}
	}
	return 0;
}
bool BuildingManager::sendBuildingList() {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BUILDING);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDINGLIST);
	selfWriter.AppendUInt32(m_buildings.size());
	map<uint32_t, Building*>::iterator it;
	for (it = m_buildings.begin(); it != m_buildings.end(); it++) {
		it->second->encode(&sRspPacket.body);
	}
	selfWriter.AppendUInt32(0);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}
