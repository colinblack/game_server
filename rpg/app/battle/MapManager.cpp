/*
 * MapManager.cpp
 *
 *  Created on: 2013-3-11
 *      Author: Administrator
 */

#include "MapManager.h"
#include "BattleInc.h"

map<unsigned, string> MapManager::m_mapFiles;
map<unsigned, string> MapManager::m_mapNames;
map<unsigned, string> MapManager::m_mapwwmFiles;

uint32_t MapManager::createCarbon(uint32_t fbId) {
	static uint32_t g_fbInstanceId = 1;
	if (++g_fbInstanceId == 0) {
		++g_fbInstanceId;
	}
	DungeonCfgWrap dungeonCfgWrap;
	MapCfgWrap mapCfgWrap;
	uint32_t fbInstanceId = g_fbInstanceId;

	const CfgDungeon::DungeonItem &cfg = dungeonCfgWrap.Get(fbId);
	const CfgMap::Map &mapCfg = mapCfgWrap.Get(cfg.mapid());

	string wwmConfPath = Config::GetValue(CONFIG_WWM_PATH);
	uint16_t mapId = cfg.mapid();
	string mapFile;
	String::Format(mapFile, "%u", mapCfg.mapscene());
	string mapName = mapCfg.name();
	string wwmFile = wwmConfPath + mapFile + ".txt";

	Map *pMap = new Map();
	if (pMap == NULL) {
		error_log("map Memory allocation failed mapId=%d mapName = %s", mapId, mapName.c_str());
		return 0;
	}

	m_mapCarbon[fbInstanceId][mapId] = pMap;
	pMap->setFbId(fbInstanceId);
	if (!pMap->init(wwmFile, mapName, mapId, 3)) {
		error_log("map init mapId=%d mapName = %s", mapId, mapName.c_str());
		goto CREATE_CARBON_FAIL;
	}
	if (!pMap->initMoveAbleArena(cfg.aroundborninterposlist())) {
		error_log("map init mapId=%d mapName = %s", mapId, mapName.c_str());
		goto CREATE_CARBON_FAIL;
	}
	m_mapwwmFiles[mapId] = wwmFile;
	return fbInstanceId;

	CREATE_CARBON_FAIL:
	delete pMap;
	pMap = NULL;
	m_mapCarbon[fbInstanceId].erase(mapId);
	return 0;
}

MapManager::~MapManager() {

}

bool MapManager::init() {
	string wwmConfPath = Config::GetValue(CONFIG_WWM_PATH);
	uint32_t mapId = 0;
	uint32_t mapType = 0;
	string mapFile;
	string mapName;
	string wwmFile;
	Map *pMap = NULL;
	SceneCfgWrap sceneCfgwrap;
	const CfgMap::Maps &map_cfg = ConfigManager::Instance()->map_cfg_.m_config;
	for (int i = 0; i < map_cfg.maps_size(); ++i) {
		const CfgMap::Map &cfg = map_cfg.maps(i);
		const CfgMap::Scene &item = sceneCfgwrap.Get(cfg.mapscene());
		mapType = item.instancetype();
		if (mapType != SceneCfgWrap::SCENE_TYPE_HANG&&mapType != SceneCfgWrap::SCENE_TYPE_COPY && item.id() != DEFAULT_MAP_ID&&item.mapid()!=200403) {
			continue;
		}

		mapId = cfg.id();
		String::Format(mapFile, "%u", cfg.mapscene());
		mapName = cfg.name();
		wwmFile = wwmConfPath + mapFile + ".txt";
		m_mapFiles[mapId] = mapFile;
		m_mapNames[mapId] = mapName;
		m_mapwwmFiles[mapId] = wwmFile;
		if(cfg.copytype()!=0){
			if(cfg.copytype()==1){
				pMap = new MapHang();
			}
			else{
				pMap = new MapCopy();
			}
//			try {
//				//伙伴岛
//				if(mapId==200501||mapId==200502||mapId==200503||mapId==200504||mapId==200505){
//					pMap = new MapHang();
//				}
//				//符文塔
//				else if(mapId==200401||mapId==200401||mapId==200401||mapId==200401||mapId==200401){
//					pMap = new MapHang();
//				}
//				else{
//					const CfgCopy::Copy& copyCfg =  CopyWrap().GetCopyByMapId(mapId);
//					if(copyCfg.type()==TYPE_COPY_WORLDBOSS||copyCfg.type()==TYPE_COPY_GODPLANET||copyCfg.copyid()==901||copyCfg.type()==TYPE_IMMORTALROAD_COPY){
//						pMap = new MapCopy();
//					}else{
//						pMap = new MapHang();
//					}
//				}
//			} catch (...) {
//				continue;
//			}

		}
		else{
			if (mapType == SceneCfgWrap::SCENE_TYPE_HANG) {
				pMap = new MapHang();
			} else {
				pMap = new Map();
			}
		}

		if (pMap == NULL) {
			error_log("map Memory allocation failed mapId=%d mapName=%s", mapId, mapName.c_str());
			return false;
		}

		if (!pMap->init(wwmFile, mapName, mapId, mapType)) {
			delete pMap;
			pMap = NULL;
			m_mapCarbon[0].erase(mapId);
			error_log("map init mapId=%d mapName=%s", mapId, mapName.c_str());
			return false;
		}

		m_mapCarbon[0][mapId] = pMap;
	}

	return true;
}

int MapManager::Process(uint32_t uid, logins::SRoleMove *req) {
	Human *pHuman = getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	if (req->path_.empty()) {
		return R_SUCCESS;
	}

	Point cur_pos;
	pHuman->getPos(cur_pos.x, cur_pos.y);
	if (req->path_.front() == cur_pos) {
		req->path_.erase(req->path_.begin());
	}

	if (req->path_.empty()) {
		return R_SUCCESS;
	}

	msgs::SMapEntityMoves move_msg;
	move_msg.clear();
	move_msg.entityId_ = pHuman->getEntityMsg();
	move_msg.path_ = req->path_;
	mapMoveObjectMsg(pHuman, &move_msg, false);
	pHuman->setPath(req->path_);

	return R_SUCCESS;
}

int MapManager::Process(uint32_t uid, logins::SEnterHang *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERR_NO_DATA;
	}
	DataBase &base = cache.base_;

	uint32_t des_map = 0;
	Point des_pos;
	if (!HangManager::Instance()->GetHangMap(base.hang, des_map, des_pos)) {
		return R_ERROR;
	}

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = des_map;
	info.desPoint.x = des_pos.x;
	info.desPoint.y = des_pos.y;

	if (!actorChangeMap(uid, base.role_num, info)) {
		return false;
	}
	enterMapSync();
	debug_log("enter hang %u %u", uid, des_map);
	return 0;
}

int MapManager::Process(uint32_t uid, logins::SBackToCity *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERR_NO_DATA;
	}
	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = DEFAULT_MAP_ID;
	info.desPoint.x = DEFAULT_X;
	info.desPoint.y = DEFAULT_Y;
	if (!actorChangeMap(uid, cache.base_.role_num, info)) {
		return false;
	}

	enterMapSync();

	return 0;
}

int MapManager::Process(uint32_t uid, logins::SMapJump *req) {
	return 0;
}

int MapManager::Process(uint32_t uid, logins::SMapTransfer *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	const CfgMap::Scene &cfg = SceneCfgWrap().Get(pHuman->getMapId());
	for (int i = 0; i < cfg.passpoints_size(); ++i) {
		if (req->passId_ != cfg.passpoints(i).passpointid()) {
			continue;
		}
		for (int j = 0; j < cfg.passpoints(i).passto_size(); ++j) {
			if (req->passToId_ != cfg.passpoints(i).passto(j).passtoid()) {
				continue;
			}
			info.desPoint.x = cfg.passpoints(i).passto(j).topoint().x();
			info.desPoint.y = cfg.passpoints(i).passto(j).topoint().y();
			info.desMapId = cfg.passpoints(i).passto(j).mapid();
		}
	}

	if (info.desMapId == 0) {
		return R_ERR_LOGIC;
	}

	if (!actorChangeMap(uid, cache.base_.role_num, info)) {
		return R_ERROR;
	}

	enterMapSync();

	debug_log("%u,%lld,%d,%d,%d", uid, req->operTime_, req->passType_, req->passId_, req->passToId_);

	return 0;
}

int MapManager::Process(uint32_t uid, logins::SAdvanceRide *req) {
	Human *pHuman = getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	pHuman->setRide(req->ride_);

	msgs::SPlayerCurrentMapPos msg;
	msg.clear();
	msg.entityId_ = pHuman->getEntityMsg();
	msg.moveId_ = pHuman->getMoveId();
	pHuman->getPos(msg.curPos_.x, msg.curPos_.y);
	mapFieldMsg(pHuman, CMD_PLAYER_CURRENT_MAP_POS, &msg);
	return 0;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerEnterMap *resp) {
	Human *pHuman = getHuman(cache.uid_);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	uint32_t map_id = pHuman->getMapId();
	MapCfgWrap mapCfgWrap;
	SceneCfgWrap sceneCfgwrap;
	const CfgMap::Map &mapCfg = mapCfgWrap.Get(map_id);
	const CfgMap::Scene &sceneCfg = sceneCfgwrap.Get(mapCfg.mapscene());
	resp->incId_ = 1;
	resp->cellLine_ = 0;
	if(mapCfg.copytype()!=0){
		const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(pHuman->getRealFbId());
		resp->copyCode_ = copyCfg.copyid();
		resp->fightMode_ = 1;
		resp->enterCellId_.type_ = copyCfg.type();
	}else{
		resp->copyCode_=0;
		resp->fightMode_ = map_id == 10000 ? 1 : 2;
		resp->enterCellId_.type_ = 1;
	}
	resp->useUninterested_ = false;
	resp->enterCellId_.id_ = 1;
	resp->enterCellId_.server_ = 0;
	resp->enterCellId_.proxy_ = 0;
	resp->spaceId_ = sceneCfg.id();
	pHuman->getPos(resp->spacePos_.x, resp->spacePos_.y);
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SRoleEnterMap *resp) {
	Human *pHuman = getHuman(cache.uid_);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	uint32_t map_id = pHuman->getMapId();
	const PropertySets &props = pHuman->getProps();

	resp->isMain_ = true;
	resp->moveId_ = pHuman->getMoveId();
	msgs::SFightData fight_data;
	fight_data.clear();
	fight_data.entityId_ = pHuman->getEntityMsg();
	fight_data.name_ = pHuman->getName();
	fight_data.sex_ = pHuman->getSex();
	fight_data.career_ = pHuman->getCareer();
	fight_data.careerLevel_ = cache.m_reinCarnInfo.reinCarnLevel;
	fight_data.combat_ = pHuman->getCombat();
	fight_data.level_ = cache.base_.level == 0 ? 1 : cache.base_.level;
	fight_data.curLife_ = pHuman->getHp();
	fight_data.speed_ = pHuman->getSpeed();
	fight_data.bodySize_ = 45;
	fight_data.fightMode_ = map_id == 10000 ? 1 : 2;

	pHuman->getShow(fight_data.entityShows_);
	pHuman->getPos(fight_data.spacePos_.x, fight_data.spacePos_.y);

	PropertyCfg::getPropsMsg(props, fight_data.fightAttr_);

	fight_data.totalAttr_ = fight_data.fightAttr_;

	resp->fightData_ = &fight_data;

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}

	return R_SUCCESS;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SRoleEnterMapEnd *resp) {
	resp->roleNum_ = 1;
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SFightFlyingUp *resp) {
	resp->clear();
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SHangPower *resp) {
	resp->power_ = cache.base_.hang_power;
	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SMapEntityEnters *resp) {
	Human *pHuman = getHuman(cache.uid_);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	Map *pMap = getMapInstance(pHuman->getFbId(), pHuman->getMapId());
	if (pMap == NULL) {
		return R_ERR_NO_DATA;
	}
	msgs::SMapEntityEnters msg;
	pMap->getFieldAppear(pHuman, &msg);
	if (msg.entities_.empty()) {
		return R_ERR_NO_DATA;
	}
	if(!LogicManager::Instance()->SendMsg(cache.uid_, CMD_MAP_ENTERS, &msg)) {
		return R_ERROR;
	}
	return R_SUCCESS;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SRoleCombatData *resp) {
	Human *pHuman = getHuman(cache.uid_);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	resp->roleId_ = cache.base_.main_role;
	resp->combat_ = pHuman->getCombat();
	PropertyCfg::getPropsMsg(pHuman->getProps(), resp->fightAttr_);
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return R_SUCCESS;
}

int MapManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerCombatData *resp) {
	Human *pHuman = getHuman(cache.uid_);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	resp->combat_ = pHuman->getCombat();
	resp->avatarCombat_ = 0;
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return R_SUCCESS;
}

bool MapManager::canMoveTo(Human *pHuman, Map *pCurMap, const Point &endPoint, const Point &curPoint, Point &desPoint) {
	if (pHuman->isDie()) {
		error_log("human is die uid=%u", pHuman->getUid());
		return false;
	}
	desPoint = endPoint;

	// 禁止穿怪 穿人
//	if (pCurMap->getForbidFlag()) {
//		for (int step = 1; step <= entityMove.step; ++step) {
//			desPoint = calcForwardPosition(curPoint.x, curPoint.y, entityMove.dir, step);
//			if ((pCurMap->isInCrossMonsterFbArea(desPoint) && pCurMap->hasObjectOnPoint(desPoint, RACE_MONSTER)) || (pCurMap->isInCrossHumanFbArea(desPoint) && pCurMap->hasObjectOnPoint(desPoint, RACE_HUMAN))) {
//				return false;
//			}
//		}
//	}

//	desPoint = calcForwardPosition(entityMove.x, entityMove.y, entityMove.dir, entityMove.step);
	if (!pCurMap->isInMap(desPoint)){
		error_log("point is not in map uid=%u x=%d y=%d w=%u h=%u",
				pHuman->getUid(), desPoint.x, desPoint.y, pCurMap->getMapWidth(), pCurMap->getMapHeight());
		return false;
	}
	if(!pCurMap->isMoveAble(desPoint)) {
		error_log("point can not move uid=%u x=%d y=%d", pHuman->getUid(), desPoint.x, desPoint.y);
		return false;
	}

	return true;
}

bool MapManager::ActorLogin(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}

	if (m_humans.find(uid) != m_humans.end()) {
		return false;
	}

	DataPos &pos = cache.pos_;

	if (pos.uid == 0) {
		Point def;
		getDefaultPos(def);
		pos.uid = cache.uid_;
		pos.map_id = def.sceneId;
		pos.x = def.x;
		pos.y = def.y;
		pos.dir = 1;
		pos.update_time = Time::GetGlobalTime();
		DataPosManager::Instance()->Add(pos);
	}

	Human *pHuman = new Human();
	if (!pHuman->init(cache, cache.base_.main_role)) {
		error_log("init human error uid=%u rid=%u", uid, cache.base_.main_role);
		delete pHuman;
		return R_ERROR;
	}
	DataRole &role = cache.role_[cache.base_.main_role];
	uint32_t combat = pHuman->calcCombat();
	if (role.combat != combat) {
		role.combat = combat;
		DataRoleManager::Instance()->Set(role);
	}

	Point point;
	pHuman->getPos(point.x, point.y);
	Map *pCurMap = getMapInstance(pHuman->getFbId(), pHuman->getMapId());
	if (!pCurMap || !pCurMap->isMoveAble(point)) {
		getDefaultPos(point);
		pHuman->setPos(point.x, point.y);
		pHuman->setFbId(0);
		pHuman->setMapId(point.sceneId);
		pCurMap = getMapInstance(pHuman->getFbId(), pHuman->getMapId());
		debug_log("%u,%u,%u", uid, point.x, point.y);
	}
	if (pCurMap == NULL) {
		error_log("curr map null uid=%u fid=%u mid=%u", uid, pHuman->getFbId(), pHuman->getMapId());
		return R_ERROR;
	}
	pCurMap->addMainActor(pHuman);
	m_humans[uid] = pHuman;
	m_allObjects[uid] = pHuman;
	ZhanLingManager::Instance()->onChangeMap(uid);
	return true;
}

bool MapManager::actorTransfer(CFirePacket* pPacket) {
	return false;
}
bool MapManager::actorChangeMap(uint32_t uid, byte role_num, const MapChangeInfo &info) {

	map<uint32_t, Human*>::iterator itr = m_humans.find(uid);
	if (itr == m_humans.end()) {
		return false;
	}
	Human *pMo = itr->second;
	if (pMo == NULL) {
		return false;
	}

	uint32_t curFbId = pMo->getFbId();
	uint32_t curMapId = pMo->getMapId();
	int32_t race = pMo->getRace();

	if (m_allObjects.find(pMo->getId()) == m_allObjects.end()) {
		m_allObjects[pMo->getId()] = pMo;
	}

	Map *pCurMap = getMapInstance(curFbId, pMo->getMapId());
	if (!pCurMap) {
		error_log("find current map failed mapId = %d", pMo->getMapId());
		return false;
	}

	Map *pDesMap = getMapInstance(info.desFbInstanceId, info.desMapId);
	if (pDesMap == NULL) {
		error_log("destination map not exists fbid=%u mapid=%u", info.desFbInstanceId, info.desMapId);
		return false;
	}

	if (!pDesMap->isInMap(info.desPoint) || !pDesMap->isMoveAble(info.desPoint)) {
		error_log("des pos error fbid=%u mapid=%u [%d,%d]", info.desFbInstanceId, info.desMapId, info.desPoint.x, info.desPoint.y);
		return false;
	}

	Point desPoint(info.desPoint.x, info.desPoint.y);

	if (info.desMapId != curMapId) {
		pCurMap->delObject(pMo);
		pMo->setFbId(info.desFbInstanceId);
		pMo->setMapId(info.desMapId);
		pMo->setPos(desPoint.x, desPoint.y);

		if (race == RACE_HUMAN) {
			Human *pHuman = static_cast<Human*>(pMo);
			pDesMap->addMainActor(pHuman);
			ZhanLingManager::Instance()->onChangeMap(uid);
			//savePos(dynamic_cast<Human*>(pMo));
		} else {
			pDesMap->addObject(pMo);
		}
		debug_log("id=%u,dmid=%u", pMo->getId(), info.desMapId);
	}

	return true;
}

void MapManager::actorOffline(uint32_t uid) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return;
	}
	map<uint32_t, Human*>::iterator itr = m_humans.find(uid);
	if (itr == m_humans.end() || !itr->second) {
		error_log("human not exist rid=%u", uid);
		return;
	}
	Human *pHuman = itr->second;
	Point point;
	pHuman->getPos(point.x, point.y);
	Map *pCurMap = getMapInstance(pHuman->getFbId(), pHuman->getMapId());
	if (pCurMap) {
		pCurMap->delObject(pHuman);
		if (pCurMap->isInCrossHumanFbArea(point)) {
			pHuman->setPos(point.x + 1, point.y);
		}
	} else {
		error_log("map not exist mapId=%u,rid=%u", pHuman->getUid(), pHuman->getMapId());
	}
	savePos(pHuman);
	m_allObjects.erase(uid);
	m_humans.erase(uid);
	MapMoveManager::Instance()->DelObj(pHuman);
	delete pHuman;
}

void MapManager::enterMapSync() {
	LogicManager::Instance()->AddSync(CMD_PLAYER_ENTER_MAP);
	LogicManager::Instance()->AddSync(CMD_FIGHT_FLYING_UP);
	LogicManager::Instance()->AddSync(CMD_ROLE_ENTER_MAP);
	LogicManager::Instance()->AddSync(CMD_ROLE_ENTER_MAP_END);
	LogicManager::Instance()->AddSync(CMD_HANG_POWER);
	LogicManager::Instance()->AddSync(CMD_MAP_ENTERS);
}

void MapManager::getBirthPos(Point &point) {
	point.sceneId = BIRTH_MAP_ID;
	point.x = ACTOR_BIRTH_BEGIN_X + rand() % (ACTOR_BIRTH_END_X - ACTOR_BIRTH_BEGIN_X + 1);
	point.y = ACTOR_BIRTH_BEGIN_Y + rand() % (ACTOR_BIRTH_END_Y - ACTOR_BIRTH_BEGIN_Y + 1);
}

void MapManager::getDefaultPos(Point &point) {
	point.sceneId = DEFAULT_MAP_ID;
	point.x = DEFAULT_X;
	point.y = DEFAULT_Y;
}

Point MapManager::calcForwardPosition(int32_t x, int32_t y, int16_t dir, int16_t step) {
	if (step < 0 || step > 4) {
		return Point(x, y);
	}

	switch (dir) {
	case 0:
		return (Point(x, (y - step)));
	case 1:
		return (Point((x + step), (y - step)));
	case 2:
		return (Point((x + step), y));
	case 3:
		return (Point((x + step), (y + step)));
	case 4:
		return (Point(x, (y + step)));
	case 5:
		return (Point((x - step), (y + step)));
	case 6:
		return (Point((x - step), y));
	case 7:
		return (Point((x - step), (y - step)));
	default:
		return (Point(x, y));
	}
}

int MapManager::calcOppositeDirection(int16_t dir) {
	switch (dir) {
	case 0:
		return 4;
	case 1:
		return 5;
	case 2:
		return 6;
	case 3:
		return 7;
	case 4:
		return 0;
	case 5:
		return 1;
	case 6:
		return 2;
	case 7:
		return 3;
	default:
		return 0;
	}
}

int MapManager::calcForwardDirection(const Point &srcPoint, const Point &desPoint) {

	if (srcPoint.x == desPoint.x) {
		return ((((srcPoint.y) <= desPoint.y) ? 4 : 0));
	}

	if (srcPoint.y == desPoint.y) {
		return ((((srcPoint.x) > desPoint.x) ? 6 : 2));
	}

	if (srcPoint.x < desPoint.x) {
		return ((((srcPoint.y) > desPoint.y) ? 1 : 3));
	}

	return ((((srcPoint.y) > desPoint.y) ? 7 : 5));

}

string MapManager::getMapFile(uint32_t mapId) {
	return m_mapFiles[mapId];
}

string MapManager::getMapName(uint32_t mapId) {
	return m_mapNames[mapId];
}

string MapManager::getwwmFile(uint32_t mapId) {
	return m_mapwwmFiles[mapId];
}

bool MapManager::IsInField(const Point &point, const Point &beginPoint, const Point &endPoint) {
	return (point.x >= beginPoint.x && point.x < endPoint.x && point.y >= beginPoint.y && point.y < endPoint.y);
}

int MapManager::savePos(Human *pHuman) {
	UserCache &cache = CacheManager::Instance()->GetUser(pHuman->getUid());
	DataPos &dataPos = cache.pos_;
	int x = 0, y = 0;
	Point fromPoint;
	dataPos.fb_id = pHuman->getFbId();
	dataPos.map_id = pHuman->getMapId();
	dataPos.uid = pHuman->getUid();
	dataPos.update_time = LogicManager::GlobalTime;
	pHuman->getPos(x, y);
	dataPos.x = x;
	dataPos.y = y;
	dataPos.dir = pHuman->getDir();

	if (dataPos.fb_id != 0) {
		CarbonBase *pCarbon = CarbonManager::Instance()->getCarbon(dataPos.fb_id);
		if (!pCarbon || (!(pCarbon->getFromPos(dataPos.uid, fromPoint)))) {
			getDefaultPos(fromPoint);
		}
	} else {
		getDefaultPos(fromPoint);
	}

	dataPos.from_map_id = fromPoint.sceneId;
	dataPos.from_x = fromPoint.x;
	dataPos.from_y = fromPoint.y;
	int ret = DataPosManager::Instance()->Set(dataPos);
	if (0 != ret) {
		error_log("add pos error,rid = %u", dataPos.uid);
		return ret;
	}
	return 0;
}

bool MapManager::addObject(MapDisplayObject *target) {
	Map *pMap = getMapInstance(target->getFbId(), target->getMapId());
	if (!pMap) {
		error_log("get map instance failed fbId = %u,mapId = %u", target->getFbId(), target->getMapId());
		return false;
	}

	int ret = pMap->addObject(target);
	if (0 != ret) {
		error_log("add objects failed id=%u ret=%d", target->getId(), ret);
		return false;
	}

	m_allObjects[target->getId()] = target;
	return true;
}

MapDisplayObject* MapManager::getObject(uint32_t id) {
	map<uint32_t, MapDisplayObject*>::iterator itr = m_allObjects.find(id);
	if (itr != m_allObjects.end()) {
		return itr->second;
	}
	return NULL;
}

MapMoveObject* MapManager::getObject(uint32_t id, int16_t race) {
	if (race == RACE_HUMAN) {
		map<uint32_t, Human*>::iterator humanItr = m_humans.find(id);
		return (humanItr != m_humans.end() ? humanItr->second : NULL);
	}
	map<uint32_t, MapDisplayObject*>::iterator itr = m_allObjects.find(id);
	return itr != m_allObjects.end() ? dynamic_cast<MapMoveObject *>(itr->second) : NULL;
}


MapMoveObject* MapManager::getMonster(uint32_t monsterId) {
	map<uint32_t, MapDisplayObject*>::iterator itr;
	for(itr=m_allObjects.begin();itr!=m_allObjects.end();itr++){
		if(dynamic_cast<MapMoveObject *>(itr->second)->checkEntityId(monsterId)){
			return dynamic_cast<MapMoveObject *>(itr->second);
		}
	}
	return NULL;
}

MapMoveObject* MapManager::getMoveObject(uint32_t id) {
	map<uint32_t, MapDisplayObject*>::iterator itr = m_allObjects.find(id);
	if (itr == m_allObjects.end()) {
		return NULL;
	}
	MapDisplayObject *pDo = itr->second;
	if (pDo == NULL) {
		return NULL;
	}
	if (pDo->getRace() != RACE_HUMAN && pDo->getRace() != RACE_MONSTER) {
		return NULL;
	}
	return dynamic_cast<MapMoveObject*>(pDo);
}

Human* MapManager::getHuman(uint32_t uid) {
	map<uint32_t, Human*>::iterator itr = m_humans.find(uid);
	return (itr != m_humans.end() ? itr->second : NULL);
}

Human* MapManager::getHumanByName(string name) {
	for (map<uint32_t, Human*>::iterator it = m_humans.begin(); it != m_humans.end(); ++it) {
		if (it->second->getName() == name)
			return it->second;
	}

	return NULL;
}

void MapManager::getAroundHuman(MapMoveObject *obj, vector<Human *> &vHuman) {
	Map *pMap = getMapInstance(obj->getFbId(), obj->getMapId());
	if (pMap) {
		pMap->getAroundHuman(obj, vHuman);
	}
}

void MapManager::getMapHumans(uint32_t fbinstanceId, uint32_t mapId, vector<Human *> &vecHumans) {
	Map *pMap = getMapInstance(fbinstanceId, mapId);
	if (pMap) {
		pMap->getHumans(vecHumans);
	}
}

void MapManager::getAroundHuman(uint32_t fbInstanceId, uint32_t mapId, const Point &point, map<uint32_t, Human*> &mapHumans) {
	Map *pMap = getMapInstance(fbInstanceId, mapId);
	if (pMap) {
		pMap->getAroundHuman(point, mapHumans);
	}
}

void MapManager::getAroundMonsters(MapMoveObject *pMo, vector<MapMoveObject *> &vecMonsters) {
	Map *pMap = getMapInstance(pMo->getFbId(), pMo->getMapId());
	if (pMap) {
		pMap->getAroundMonsters(pMo, vecMonsters);
	}
}

void MapManager::getAroundObjects(MapMoveObject *pMo, vector<MapMoveObject *> &objs) {
	Map *pMap = getMapInstance(pMo->getFbId(), pMo->getMapId());
	if (pMap) {
		pMap->getAroundObjects(pMo, objs);
	}
}

void MapManager::getAroundPoints(MapMoveObject* pMo, vector<Point> &vecPoints, int16_t distance) {
	Point point;
	pMo->getPos(point.x, point.y);

	Map *pMap = getMapInstance(pMo->getFbId(), pMo->getMapId());
	if (pMap) {
		pMap->getAroundPoints(point, vecPoints, distance);
	}
}

bool MapManager::getNearestEmptyPoint(MapMoveObject *pMo, Point &point) {
	if (!pMo) {
		return false;
	}

	Map *pMap = getMapInstance(pMo->getFbId(), pMo->getMapId());
	if (!pMap) {
		error_log("find map failed,mapId = %d", pMo->getMapId());
		return false;
	}

	vector<Point> vecPoints;
	getAroundPoints(pMo, vecPoints, 3);
	for (vector<Point>::iterator itr = vecPoints.begin(); itr != vecPoints.end(); ++itr) {
		if (pMap->isPointEmpty(*itr)) {
			point = *itr;
			return true;
		}
	}

	return false;
}

Map *MapManager::getMapInstance(uint32_t fbInstanceId, uint32_t mapId) {
	map<uint32_t, map<uint32_t, Map*> >::iterator curCarbonItr = m_mapCarbon.find(fbInstanceId);
	if (curCarbonItr == m_mapCarbon.end()) {
		return NULL;
	}

	map<uint32_t, Map*>::iterator mapItr = curCarbonItr->second.find(mapId);
	if (mapItr == curCarbonItr->second.end()) {
		error_log("mapid not exist,fbid = %d", mapId);
		return NULL;
	}
	return mapItr->second;
}

void MapManager::mapRemoveObject(uint32_t id) {
	map<uint32_t, MapDisplayObject *>::iterator itr = m_allObjects.find(id);
	if (itr == m_allObjects.end()) {
		error_log("object not exist id=%u", id);
		return;
	}

	MapDisplayObject *pDo = itr->second;
	if (pDo == NULL) {
		return;
	}

	if (pDo->getRace() == RACE_HUMAN) {
		m_humans.erase(pDo->getId());
	}

	Map *pMap = getMapInstance(pDo->getFbId(), pDo->getMapId());
	if (!pMap) {
		error_log("map not exit mapId=%u id=%u", pDo->getMapId(), id);
		return;
	}

	if (pDo->getRace() == RACE_MONSTER) {
		pMap->objectDie(dynamic_cast<MapMoveObject*>(pDo));
	} else {
		pMap->delObject(pDo);
	}

	m_allObjects.erase(id);
}

void MapManager::mapMoveObjectDie(MapMoveObject *caster, MapMoveObject *target) {
	if (NULL == target) {
		return;
	}

	int targetRace = target->getRace();
	if (targetRace != RACE_HUMAN) {
		m_allObjects.erase(target->getId());
	}

	Map *pMap = MapManager::Instance()->getMapInstance(target->getFbId(), target->getMapId());
	if (NULL != pMap) {
		pMap->objectDie(target);
	}
}

void MapManager::mapMoveObjectMsg(MapMoveObject *pMo, Msg *msg, bool self) {
	if (pMo == NULL || msg == NULL) {
		return;
	}
	Map *pMap = getMapInstance(pMo->getFbId(), pMo->getMapId());
	if (pMap == NULL) {
		return;
	}
	pMap->syncFieldMsg(pMo, CMD_MAP_MOVES, msg, self);
}

void MapManager::mapFieldMsg(MapMoveObject *pMo, uint32_t cmd, Msg *msg) {
	if (pMo == NULL || msg == NULL) {
		return;
	}
	Map *pMap = getMapInstance(pMo->getFbId(), pMo->getMapId());
	if (pMap == NULL) {
		return;
	}
	pMap->syncFieldMsg(pMo, cmd, msg, true);
}

void MapManager::updateSafeArea(const DataLastSafeArea &data) {
	m_mapLastSafeArea[data.rid] = data;
}

void MapManager::getLastSafeArea(unsigned rid, DataLastSafeArea &data) {
	map<uint32_t, DataLastSafeArea>::iterator itr;
	if ((itr = m_mapLastSafeArea.find(rid)) != m_mapLastSafeArea.end()) {
		data = itr->second;
	} else {

		data.mapId = DEFAULT_MAP_ID;
		data.rid = rid;
		data.x = DEFAULT_X;
		data.y = DEFAULT_Y;
		m_mapLastSafeArea[rid] = data;
	}

	data.fbInstanceId = 0;
	return;
}

void MapManager::getSafeArea(uint32_t rid, int32_t mapId, DataLastSafeArea &data) {
	MapAreaState *pMapAreaState = MapAreaManager::getInstance()->getMapAreaInfo(mapId);
	Rect safeArea;
	if (!pMapAreaState || !pMapAreaState->getSafeArea(safeArea)) {
		getLastSafeArea(rid, data);
		return;
	}

	data.mapId = mapId;
	data.rid = rid;
	data.x = safeArea.beginPoint.x + rand() % (safeArea.endPoint.x - safeArea.beginPoint.x + 1);
	data.y = safeArea.beginPoint.y + rand() % (safeArea.endPoint.y - safeArea.beginPoint.y + 1);
	data.fbInstanceId = 0;

	return;
}

bool MapManager::getMonsterBirthPoint(uint32_t fbInstanceId, uint32_t mapId, int32_t zoneId, Point &point) {
	Map *pMap = getMapInstance(fbInstanceId, mapId);
	if (pMap) {
		pMap->getMonterBirthPoint(zoneId, point);
		return true;
	}
	return false;
}

void MapManager::destoryCarbon(uint32_t fbInstanceId) {
	map<uint32_t, map<uint32_t, Map*> >::iterator carbonItr = m_mapCarbon.find(fbInstanceId);
	if (carbonItr == m_mapCarbon.end()) {
		error_log("carbon not exist ,carbonId=%d", fbInstanceId);
		return;
	}

	for (map<uint32_t, Map*>::iterator mapItr = carbonItr->second.begin(); mapItr != carbonItr->second.end();) {
		mapItr->second->onDestory();
		delete mapItr->second;
		carbonItr->second.erase(mapItr++);

	}

	m_mapCarbon.erase(fbInstanceId);
}

void MapManager::eraseObject(MapDisplayObject *pObj) {
	m_allObjects.erase(pObj->getId());
}

bool MapManager::onSecondTimer() {
	return true;
}

bool MapManager::onTimer() {
	static map<uint32_t, Human*>::iterator itr;
	static Human *pHuman = NULL;
	for (itr = m_humans.begin(); itr != m_humans.end(); ++itr) {
		pHuman = itr->second;
		if (pHuman != NULL) {
			pHuman->doAi();
		}
	}
	return true;
}

bool MapManager::canUseTransferEquip(Human *pHuman) {
	return false;
}

bool MapManager::canTransfer(Human *pHuman) {
	return false;
}

void MapManager::reclaimBirthPoint(uint32_t fbInstanceId, uint32_t mapId, int zoneId, const Point &point) {
	Map *pMap = getMapInstance(fbInstanceId, mapId);
	if (pMap) {
		pMap->reclaimBirthPoint(zoneId, point);
	}
}

