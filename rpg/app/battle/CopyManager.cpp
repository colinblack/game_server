/*
 * CopyManager.cpp
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#include "BattleInc.h"
#include "CopyManager.h"

CopyManager::CopyManager() {
	m_data = new CDataCopy();
}

CopyManager::~CopyManager() {
}

bool CopyManager::Init(){
	if(!m_data){
		return false;
	}
	if(!m_data->Init(Config::GetPath(CONFIG_BOSS_DATA))){
		return false;
	}
	DataCopy * pData =m_data->getDataCopy();
	if(!pData){
		return false;
	}

	vector<uint32_t> taskcopy;
	if(!CopyWrap().GetCopyListByType(TYPE_COPY_TASKBOSS,taskcopy)){
		return false;
	}
	vector<uint32_t> worldcopy;
	if(!CopyWrap().GetCopyListByType(TYPE_COPY_WORLDBOSS,worldcopy)){
		return false;
	}
	vector<uint32_t> godplane;
	if(!CopyWrap().GetCopyListByType(TYPE_COPY_GODPLANET,godplane)){
		return false;
	}
	sort(worldcopy.begin(), worldcopy.end());
	for(uint32_t i=0;i<taskcopy.size();i++){
		if(!pData->bossInfo[0][i].init){
			const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(taskcopy[i]);
			const CfgBoss::Boss &bossCfg = BossWrap().GetBoss(taskcopy[i]);
			const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(copyCfg.mapid());
			const CfgMonster::Monster &moncfg = MonsterCfgWrap().Get(bossCfg.bossid());
			CopyBoss tmp;
			pData->bossInfo[0][i].bossId = bossCfg.bossid();
			pData->bossInfo[0][i].copyId = copyCfg.copyid();
			pData->bossInfo[0][i].mapId = scenecfg.mapid();
			pData->bossInfo[0][i].wLevel=0;
			pData->bossInfo[0][i].init = 1;
			pData->bossInfo[0][i].refreshTime=0;
			pData->bossInfo[0][i].status =BOSS_STATUS_WAIT;
			pData->bossInfo[0][i].hp=moncfg.hp();
			pData->bossInfo[0][i].maxHp =moncfg.hp();
		}
		pData->bossInfo[0][i].status =BOSS_STATUS_WAIT;
	}
	for(uint32_t i=0;i<worldcopy.size();i++){
		if(!pData->bossInfo[1][i].init){
			const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(worldcopy[i]);
			const CfgBoss::Boss &bossCfg = BossWrap().GetBoss(worldcopy[i]);
			const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(copyCfg.mapid());
			const CfgMonster::Monster &moncfg = MonsterCfgWrap().Get(bossCfg.bossid());
			CopyBoss tmp;
			pData->bossInfo[1][i].bossId = bossCfg.bossid();
			pData->bossInfo[1][i].copyId = copyCfg.copyid();
			pData->bossInfo[1][i].mapId = scenecfg.mapid();
			pData->bossInfo[1][i].wLevel=0;
			pData->bossInfo[1][i].init = 1;
			pData->bossInfo[1][i].refreshTime=0;
			pData->bossInfo[1][i].status =BOSS_STATUS_WAIT;
			pData->bossInfo[1][i].hp=moncfg.hp();
			pData->bossInfo[1][i].maxHp =moncfg.hp();
		}
		pData->bossInfo[1][i].status =BOSS_STATUS_WAIT;
	}
	for(uint32_t i=0;i<godplane.size();i++){
		if(!pData->bossInfo[2][i].init){
			const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(godplane[i]);
			const CfgBoss::Boss &bossCfg = BossWrap().GetBoss(godplane[i]);
			const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(copyCfg.mapid());
			const CfgMonster::Monster &moncfg = MonsterCfgWrap().Get(bossCfg.bossid());
			CopyBoss tmp;
			pData->bossInfo[2][i].bossId = bossCfg.bossid();
			pData->bossInfo[2][i].copyId = copyCfg.copyid();
			pData->bossInfo[2][i].mapId = scenecfg.mapid();
			pData->bossInfo[2][i].wLevel=0;
			pData->bossInfo[2][i].init = 1;
			pData->bossInfo[2][i].refreshTime=0;
			pData->bossInfo[2][i].status =BOSS_STATUS_WAIT;
			pData->bossInfo[2][i].hp=moncfg.hp();
			pData->bossInfo[2][i].maxHp =moncfg.hp();
		}
		pData->bossInfo[2][i].status =BOSS_STATUS_WAIT;
	}
	return true;
}

int CopyManager::Process(uint32_t uid, copy::CSEnterReincarnCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	CopyWrap copyCfgWrap;
	SceneCfgWrap sceneCfgWrap;
	BossWrap bossCfgWrap;
	MonsterCfgWrap monsterCfgWarp;
	const CfgCopy::Copy &copyCfg = copyCfgWrap.GetCopy(req->copyCode);
	const CfgBoss::Boss &bossCfg = bossCfgWrap.GetBoss(req->copyCode);
	const CfgMap::Scene &scenecfg = sceneCfgWrap.Get(copyCfg.mapid());
	CopySaveInfo tmp ;
	tmp.copyCode = (uint32_t)req->copyCode;
	tmp.copyType = copyCfg.type();
	tmp.fromMapId = pHuman->getMapId();
	tmp.bossId = bossCfg.bossid();
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;

	Point bpos;
	bpos.x =scenecfg.bosscenterpoints(0).point().x()*24+12;
	bpos.y =scenecfg.bosscenterpoints(0).point().y()*24+12;

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = copyCfg.mapid();;
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();
	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = bpos.x;
		info.desPoint.y = bpos.y;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return false;
	}
	pHuman->setRealFbId((uint32_t)req->copyCode);
	StdMonster *boss = new StdMonster();
	boss->init(bossCfg.bossid(), 0, copyCfg.mapid(), bpos);

	boss->setBelong(uid);
	boss->setNeedRecove(false);
	boss->setForce(FORCE_HOSTILE);
	if (!boss->recove()) {
		delete boss;
		return R_ERROR;
	}
	MapManager::Instance()->enterMapSync();
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = req->copyCode;
	msg.startDt_ = Time::GetGlobalTime()*1000LL;
	msg.endDt_ =(copyCfg.duringtime()+ Time::GetGlobalTime())*1000LL;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
	msgs::SEnterReincarnCopy msg2;
	msg2.copyCode_ = req->copyCode;
	LogicManager::Instance()->SendMsg(uid, CMD_ENTER_REINCARN_COPY, &msg2);

	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = req->copyCode;
		copyInfo.enterTime =Time::GetGlobalTime();
		copyInfo.firstEnterTime=Time::GetGlobalTime();
		copyInfo.enterNum =1;
		copyInfo.totalEnterNum =1;
		copyInfo.totalEnterDay =1;
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
		if (CTime::GetDayInterval(it->second.enterTime, Time::GetGlobalTime()) != 0){
			it->second.totalEnterDay++;
		}
		it->second.enterTime =Time::GetGlobalTime();
		it->second.enterNum ++;
		it->second.totalEnterNum ++;
		ATTR_DB_SET(it->second);
	}
	return 0;
}

int CopyManager::Process(uint32_t uid, copy::CSEnterMagicTowerCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	uint32_t index;
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(MAGIC_TOWER_COPY);
	if(it==cache.m_copyInfo.end()){
		index=MAGIC_TOWER_BASE+1;
	}else{
		index = MAGIC_TOWER_BASE+it->second.data+1;
	}
	const CfgMonster::Plan &plancfg = MonsterCfgWrap().GetPlan(index);
	uint32_t mapId = plancfg.mapid();
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(mapId);
	//const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(MAGIC_TOWER_COPY);

	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	CopySaveInfo tmp;
	tmp.copyType=122;
	tmp.copyCode = MAGIC_TOWER_COPY;
	tmp.fromMapId = pHuman->getMapId();
	tmp.mapId = plancfg.mapid();
	tmp.bossId = index-MAGIC_TOWER_BASE;
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;

	Point bpos;
	bpos.x =plancfg.pos(0).x();
	bpos.y =plancfg.pos(0).y();

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = plancfg.mapid();;
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();

	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = bpos.x;
		info.desPoint.y = bpos.y;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return false;
	}
	pHuman->setRealFbId(MAGIC_TOWER_COPY);
	StdMonster *boss = new StdMonster();
	boss->init(plancfg.boss(), 0, plancfg.mapid(), bpos);

	boss->setBelong(uid);
	boss->setNeedRecove(false);
	boss->setForce(FORCE_HOSTILE);
	if (!boss->recove()) {
		delete boss;
		return R_ERROR;
	}
	MapManager::Instance()->enterMapSync();
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = MAGIC_TOWER_COPY;
	msg.startDt_ = (Time::GetGlobalTime()+3)*1000LL;
	//msg.endDt_ =(copyCfg.duringtime()+ Time::GetGlobalTime())*1000LL;
	msg.endDt_ =(123+ Time::GetGlobalTime())*1000LL;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
	msgs::SMagicTowerCopyInfo msg2;
	msg2.layer_ = index-MAGIC_TOWER_BASE;
	LogicManager::Instance()->SendMsg(uid, CMD_MAGIC_TOWER_COPY_INFO, &msg2);

	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = MAGIC_TOWER_COPY;
		copyInfo.enterTime =Time::GetGlobalTime();
		copyInfo.firstEnterTime=Time::GetGlobalTime();
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
		it->second.enterTime =Time::GetGlobalTime();
		ATTR_DB_SET(it->second);
	}
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSEnterMaterialCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}

	CopyWrap copyCfgWrap;
	SceneCfgWrap sceneCfgWrap;
	BossWrap bossCfgWrap;
	MonsterCfgWrap monsterCfgWarp;
	const CfgCopy::Copy &copyCfg = copyCfgWrap.GetCopy(req->copyCode);
	vector<CfgMonster::Plan> plans;
	MonsterCfgWrap().GetPlansByMap(copyCfg.mapid(),plans);
	if(plans.empty()){
		return R_ERROR;
	}
	uint32_t mapId = copyCfg.mapid();
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(mapId);

	CopySaveInfo tmp ;
	tmp.fromMapId = pHuman->getMapId();
	tmp.mapId = copyCfg.mapid();
	tmp.copyCode = req->copyCode;
	tmp.copyType =127;
	tmp.bossId =1;
	tmp.count =plans[0].count();

	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;

	Point bpos;
	bpos.x =plans[0].pos(0).x();
	bpos.y =plans[0].pos(0).y();

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = copyCfg.mapid();
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();

	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = bpos.x;
		info.desPoint.y = bpos.y;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return R_ERROR;
	}
	pHuman->setRealFbId((uint32_t)req->copyCode);
	for(uint32_t j=0;j<plans[0].count();j++){
		Point mpos;
		mpos.x =plans[0].pos(j).x();
		mpos.y =plans[0].pos(j).y();
		StdMonster *boss = new StdMonster();
		boss->init(plans[0].boss(), 0, copyCfg.mapid(), mpos);
		boss->setBelong(uid);
		boss->setNeedRecove(false);
		boss->setForce(FORCE_HOSTILE);
		if (!boss->recove()) {
			delete boss;
			return R_ERROR;
		}
	}

	MapManager::Instance()->enterMapSync();
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = req->copyCode;
	msg.startDt_ = (Time::GetGlobalTime()+3)*1000LL;
	msg.endDt_ =(1800+ Time::GetGlobalTime())*1000LL;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);

	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = req->copyCode;
		copyInfo.enterTime =Time::GetGlobalTime();
		copyInfo.firstEnterTime=Time::GetGlobalTime();
		copyInfo.enterNum =1;
		copyInfo.totalEnterNum =1;
		copyInfo.totalEnterDay =1;
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
		if (CTime::GetDayInterval(it->second.enterTime, Time::GetGlobalTime()) != 0){
			it->second.totalEnterDay++;
		}
		it->second.enterTime =Time::GetGlobalTime();
		it->second.enterNum ++;
		it->second.totalEnterNum ++;
		ATTR_DB_SET(it->second);
	}
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSEnterWorldBoss *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return R_ERR_NO_DATA;
	const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(req->copyCode);
	const CfgBoss::Boss &bossCfg = BossWrap().GetBoss(req->copyCode);
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(copyCfg.mapid());
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_WORLDBOSS,bossCfg.bossid(),index1,index2)){
		return R_ERR_NO_DATA;
	}
	CopySaveInfo tmp ;
	tmp.copyCode = (uint32_t)req->copyCode;
	tmp.copyType = copyCfg.type();
	tmp.fromMapId = pHuman->getMapId();
	tmp.bossId = bossCfg.bossid();
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;

	Point bpos;
	bpos.x =scenecfg.bosscenterpoints(0).point().x()*24+12;
	bpos.y =scenecfg.bosscenterpoints(0).point().y()*24+12;

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = copyCfg.mapid();;
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();
	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = bpos.x;
		info.desPoint.y = bpos.y;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return R_ERROR;
	}
	pHuman->setRealFbId((uint32_t)req->copyCode);
	if(pData->bossInfo[index1][index2].status==BOSS_STATUS_WAIT){
		pData->bossInfo[index1][index2].status =BOSS_STATUS_ALIVE;
		StdMonster *boss = new StdMonster();
		boss->init(bossCfg.bossid(), 0, copyCfg.mapid(), bpos,pData->bossInfo[index1][index2].hp);
		boss->setBelong(0);
		boss->setNeedRecove(false);
		boss->setForce(FORCE_HOSTILE);
		boss->setRealFbId(copyCfg.copyid());
		if (!boss->recove()) {
			delete boss;
			return R_ERROR;
		}
	}
	MapManager::Instance()->enterMapSync();
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = req->copyCode;
	msg.startDt_ = Time::GetGlobalTime()*1000LL;
	msg.endDt_ =0;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
	msgs::SEnterCopy msg2;
	msg2.copyCode_ = req->copyCode;
	LogicManager::Instance()->SendMsg(uid, CMD_ENTER_WORLD_BOSS, &msg2);
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = req->copyCode;
		copyInfo.enterTime =Time::GetGlobalTime();
		copyInfo.firstEnterTime=Time::GetGlobalTime();
		copyInfo.enterNum =1;
		copyInfo.totalEnterNum =1;
		copyInfo.totalEnterDay =1;
		copyInfo.dataExt=1;
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
		if (CTime::GetDayInterval(it->second.enterTime, Time::GetGlobalTime()) != 0){
			it->second.totalEnterDay++;
		}
		it->second.enterTime =Time::GetGlobalTime();
		it->second.enterNum ++;
		it->second.totalEnterNum ++;
		it->second.dataExt++;
		ATTR_DB_SET(it->second);
	}
	return 0;
}




int CopyManager::Process(uint32_t uid, copy::CSEnterTaskCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return R_ERR_NO_DATA;
	const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(req->copyCode);
	const CfgBoss::Boss &bossCfg = BossWrap().GetBoss(req->copyCode);
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(copyCfg.mapid());
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_TASKBOSS,bossCfg.bossid(),index1,index2)){
		return R_ERR_NO_DATA;
	}

	CopySaveInfo tmp ;
	tmp.copyCode = (uint32_t)req->copyCode;
	tmp.copyType = copyCfg.type();
	tmp.fromMapId = pHuman->getMapId();
	tmp.bossId = bossCfg.bossid();
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;

	Point bpos;
	bpos.x =scenecfg.bosscenterpoints(0).point().x()*24+12;
	bpos.y =scenecfg.bosscenterpoints(0).point().y()*24+12;

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = copyCfg.mapid();;
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();
	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = bpos.x;
		info.desPoint.y = bpos.y;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return R_ERROR;
	}
	pHuman->setRealFbId((uint32_t)req->copyCode);
	if(pData->bossInfo[index1][index2].status==BOSS_STATUS_WAIT){
		pData->bossInfo[index1][index2].status =BOSS_STATUS_ALIVE;
		StdMonster *boss = new StdMonster();
		boss->init(bossCfg.bossid(), 0, copyCfg.mapid(), bpos,pData->bossInfo[index1][index2].hp);
		boss->setBelong(0);
		boss->setNeedRecove(false);
		boss->setForce(FORCE_HOSTILE);
		boss->setRealFbId(copyCfg.copyid());
		if (!boss->recove()) {
			delete boss;
			return R_ERROR;
		}
	}
	MapManager::Instance()->enterMapSync();
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = req->copyCode;
	msg.startDt_ = Time::GetGlobalTime()*1000LL;
	msg.endDt_ =0;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
	msgs::SEnterCopy msg2;
	msg2.copyCode_ = req->copyCode;
	LogicManager::Instance()->SendMsg(uid, CMD_ENTER_TASK_COPY, &msg2);
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = req->copyCode;
		copyInfo.enterTime =Time::GetGlobalTime();
		copyInfo.firstEnterTime=Time::GetGlobalTime();
		copyInfo.enterNum =1;
		copyInfo.totalEnterNum =1;
		copyInfo.totalEnterDay =1;
		copyInfo.dataExt=1;
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
		if (CTime::GetDayInterval(it->second.enterTime, Time::GetGlobalTime()) != 0){
			it->second.totalEnterDay++;
		}
		it->second.enterTime =Time::GetGlobalTime();
		it->second.enterNum ++;
		it->second.totalEnterNum ++;
		it->second.dataExt++;
		ATTR_DB_SET(it->second);
	}
	return 0;
	return 0;
}




int CopyManager::Process(uint32_t uid, copy::CSLeaveCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if(!pHuman){
		return R_ERROR;
	}
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);

	if(it->second.copyType ==TYPE_COPY_GODPLANET){
		//处理如果是归属的情况
		vector<Human *> vHuman;
		MapManager::Instance()->getMapHumans(0,it->second.mapId,vHuman);
		if(vHuman.size()==1){
			resetGodPlaneBoss(it->second.bossId);
		}
	}else if(it->second.copyType ==TYPE_IMMORTALROAD_COPY){
		//处理组队副本
		TeamManager::Instance()->doLeaveTeam(uid);
	}
	if(it==m_saveInfo.end()){
		logins::SBackToCity *req=NULL;
		MapManager::Instance()->Process(uid,req);
		return 0;
	}
	if(it->second.fromMapId==DEFAULT_MAP_ID){
		logins::SBackToCity *req=NULL;
		MapManager::Instance()->Process(uid,req);
	}else{
		logins::SEnterHang *req=NULL;
		MapManager::Instance()->Process(uid,req);
	}
	pHuman->doRecover();
	m_saveInfo.erase(it);
	return 0;
}

int CopyManager::Process(uint32_t uid, copy::CSQuickFinish *req){
	//转生BOSSquick
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		return R_ERR_NO_DATA;
	}else{
		it->second.completeNum ++;
		it->second.totalCompleteNum ++;
		it->second.enterNum ++;
		it->second.totalEnterNum ++;
		ATTR_DB_SET(it->second);
	}

	const CfgBoss::Boss &bossCfg = BossWrap().GetBoss(req->copyCode);
	const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(bossCfg.bossid());

	Award reward;
	reward.Random(drop_cfg.randomreward(), drop_cfg.randomcount());
	if (!reward.Format(drop_cfg.fixedreward(), 1)) {
		error_log("parse reward error");
		return false;
	}
	UserManager::Instance()->Reward(uid, reward, "reincarn boss quick");
	sendUpdate(cache,req->copyCode);
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSGotReward *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		return R_ERR_NO_DATA;
	}else{
		it->second.dataExt ++;
		ATTR_DB_SET(it->second);
	}
	CopyWrap copyCfgWrap;
	const CfgCopy::Copy &copyCfg = copyCfgWrap.GetCopy(req->copyCode);
	Award reward;
	reward.Format(copyCfg.firstreward(),1);
	UserManager::Instance()->Reward(uid, reward, "reincarnCopy_first_rward");
	sendUpdate(cache,req->copyCode);
	return 0;
}



int CopyManager::Process(uint32_t uid, copy::CSLotteryMagicTower *req,copy::SCLotteryMagicTowerResp* resp){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(MAGIC_TOWER_COPY);
	if(it==cache.m_copyInfo.end()){
		return 0;
	}
	uint32_t count =it->second.data/10;
	for(uint32_t i=0;i<10;i++){
		if(GET_BIT(it->second.rewardMark,i)){
			count--;
		}
	}
	if(count<1) return R_ERROR;
	uint32_t rewardIndex = (it->second.data/100)*100+1;
	const CfgMagic::MagicTower &tower_cfg = MagicTowerWrap().GetMagicTower(rewardIndex);
	const CfgItem::Gift& giftCfg = ItemCfgWrap().GetGift(tower_cfg.dailyreward());

	uint32_t size = giftCfg.reward_size();
	if(size!=10){
		return R_ERROR;
	}
	uint32_t randomVal=0;
	while(1){
		randomVal = Math::GetRandomInt(10);
		if(GET_BIT(it->second.rewardMark,randomVal)){
			continue;
		}else{
			break;
		}
	}
	SET_BIT(it->second.rewardMark,randomVal);
	ATTR_DB_SET(it->second);
	resp->pos = randomVal;
	UpdateManager::Instance()->SetCode(UC_MagicTowerLotteryReward);
	Award reward;
	if (!reward.Format(giftCfg.reward(randomVal),1)) {
		error_log("parse reward error");
		return false;
	}
	UserManager::Instance()->Reward(uid, reward, "magic_tower reward");
	LogicManager::Instance()->AddSync(CMD_LOTTERY_MAGIC_TOWER);
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSGetWorldBossList *req){
	sendWorldBossList(uid);
	return 0;
}

int CopyManager::Process(uint32_t uid, copy::CSGetGodPlaneList *req){
	sendGodPlaneList(uid);
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSFightRevive *req){
	debug_log("receive fight revive %d",req->type);

	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return R_ERR_NO_DATA;
	}
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}

	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if(!pHuman){
		return R_ERROR;
	}
	if(req->type==1){
		pHuman->doRecover();
	}else{
		pHuman->doRecover();
		const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(it->second.mapId);
		Point bpos;
		bpos.x =scenecfg.bosscenterpoints(0).point().x()*24+12;
		bpos.y =scenecfg.bosscenterpoints(0).point().y()*24+12;
		MapChangeInfo info;
		info.desPoint.x = scenecfg.addenterpoint_x();
		info.desPoint.y =  scenecfg.addenterpoint_y();
		if(info.desPoint.x==0||info.desPoint.y==0){
			info.desPoint.x = bpos.x;
			info.desPoint.y = bpos.y;
		}
		pHuman->setPos(info.desPoint.x,info.desPoint.y);
		Map* pMap = MapManager::Instance()->getMapInstance(0,it->second.mapId);
		pMap->updateField(pHuman,true);
	}

	Msg msg;
	LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_REVIVE_END, &msg);
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSEnterImmortalroadCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}

	CopyWrap copyCfgWrap;
	SceneCfgWrap sceneCfgWrap;
	BossWrap bossCfgWrap;
	MonsterCfgWrap monsterCfgWarp;
	const CfgCopy::Copy &copyCfg = copyCfgWrap.GetCopy(req->copyCode);
	map<uint32_t,vector<CfgMonster::Plan> >plans;
	MonsterCfgWrap().GetPlansByMap(copyCfg.mapid(),plans);
	if(plans.empty()){
		return R_ERROR;
	}
	uint32_t mapId = copyCfg.mapid();
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(mapId);

	CopySaveInfo tmp ;
	tmp.fromMapId = pHuman->getMapId();
	tmp.mapId = copyCfg.mapid();
	tmp.copyCode = req->copyCode;
	tmp.copyType =TYPE_IMMORTALROAD_COPY;
	tmp.wave =0;
	tmp.count =0;
	Point bpos;
	bpos.x =plans[0][0].pos(0).x();
	bpos.y =plans[0][0].pos(0).y();
	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = copyCfg.mapid();
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();

	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = 756;
		info.desPoint.y = 1572;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return R_ERROR;
	}
	pHuman->setRealFbId((uint32_t)req->copyCode);
	MapManager::Instance()->enterMapSync();
	map<uint32_t,uint32_t> monsterPlan;
	sendImmortalRoadCopyInfo(uid,0,monsterPlan);
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = req->copyCode;
	msg.startDt_ = (Time::GetGlobalTime())*1000LL;
	msg.endDt_ =(2420+ Time::GetGlobalTime())*1000LL;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
	for(uint32_t j=0;j<plans[0].size();j++){
		for(uint32_t k=0;k<plans[0][j].count();k++){
			Point mpos;
			mpos.x =plans[0][j].pos(k).x();
			mpos.y =plans[0][j].pos(k).y();
			StdMonster *boss = new StdMonster();
			boss->init(plans[0][j].boss(), 0, copyCfg.mapid(), mpos);
			//boss->setBelong(uid);
			boss->setNeedRecove(false);
			boss->setForce(FORCE_HOSTILE);
			if (!boss->recove()) {
				error_log("recove monster failed id=%d,mapid=%d,x=%d,y=%d",plans[0][j].boss(),copyCfg.mapid(),mpos.x,mpos.y);
				delete boss;
				return R_ERROR;
			}
			tmp.count ++;
		}
		monsterPlan.insert(make_pair(plans[0][j].boss(),plans[0][j].count()));
	}
	sendImmortalRoadCopyInfo(uid,1,monsterPlan);
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;
//	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
//	if(it==cache.m_copyInfo.end()){
//		CopyInfo copyInfo;
//		copyInfo.uid = uid;
//		copyInfo.type = TYPE_ATTR_COPY;
//		copyInfo.id = req->copyCode;
//		copyInfo.enterTime =Time::GetGlobalTime();
//		copyInfo.firstEnterTime=Time::GetGlobalTime();
//		copyInfo.enterNum =1;
//		copyInfo.totalEnterNum =1;
//		copyInfo.totalEnterDay =1;
//		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
//		ATTR_DB_ADD(copyInfo);
//	}else{
//		if (CTime::GetDayInterval(it->second.enterTime, Time::GetGlobalTime()) != 0){
//			it->second.totalEnterDay++;
//		}
//		it->second.enterTime =Time::GetGlobalTime();
//		it->second.enterNum ++;
//		it->second.totalEnterNum ++;
//		ATTR_DB_SET(it->second);
//	}
	return 0;
}




int CopyManager::Process(uint32_t uid, copy::CSEnterPartnerIslandCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	uint32_t index=0;
	uint32_t copyCode=0;
	if(req->type==0){
		index =200002000;
		copyCode =221;
	}else if(req->type==1){
		index = 200003000;
		copyCode =222;
	}else{
		return R_ERROR;
	}

	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(copyCode);
	if(it==cache.m_copyInfo.end()){
		index=index+1;
	}else{
		index = index+it->second.data+1;
	}
	const CfgMonster::Plan &plancfg = MonsterCfgWrap().GetPlan(index);
	uint32_t mapId = plancfg.mapid();
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(mapId);

	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	CopySaveInfo tmp;
	tmp.copyType=TYPE_PARTNERISLAND_COPY;
	tmp.copyCode = copyCode;
	tmp.fromMapId = pHuman->getMapId();
	tmp.mapId = plancfg.mapid();
	tmp.index = req->type;
	tmp.startTime =Time::GetGlobalTime();
	if(req->type==0){
		tmp.bossId = index-200002000;
	}else if(req->type==1){
		tmp.bossId = index-200003000;
	}
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;

	Point bpos;
	bpos.x =plancfg.pos(0).x();
	bpos.y =plancfg.pos(0).y();

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = plancfg.mapid();;
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();

	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = bpos.x;
		info.desPoint.y = bpos.y;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return false;
	}
	MapManager::Instance()->enterMapSync();
	pHuman->setRealFbId(copyCode);
	StdMonster *boss = new StdMonster();
	boss->init(plancfg.boss(), 0, plancfg.mapid(), bpos);

	boss->setBelong(uid);
	boss->setNeedRecove(false);
	boss->setForce(FORCE_HOSTILE);
	if (!boss->recove()) {
		delete boss;
		return R_ERROR;
	}
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = copyCode;
	msg.startDt_ = (Time::GetGlobalTime()+3)*1000LL;
	msg.endDt_ =(123+ Time::GetGlobalTime())*1000LL;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
	sendPartnerIslandInfo(uid);
	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = copyCode;
		copyInfo.enterTime =Time::GetGlobalTime();
		copyInfo.firstEnterTime=Time::GetGlobalTime();
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
		it->second.enterTime =Time::GetGlobalTime();
		ATTR_DB_SET(it->second);
	}
	return 0;
}









bool CopyManager::sendExpCopyInfo(uint32_t uid){
	map<uint32_t,CopySaveInfo>::iterator it = m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return false;
	}
	msgs::SExpCopyInfo msg;
	msg.coinNum_=0;
	msg.goldNum_=0;
	msg.count_=it->second.rateCount;
	msg.copyCode_ =it->second.copyCode;
	msg.totalExp_ =it->second.singExp*it->second.rateCount;
	LogicManager::Instance()->SendMsg(uid, CMD_EXP_COPY_INFO, &msg);
	return true;
}

bool CopyManager::sendPartnerIslandInfo(uint32_t uid){
	map<uint32_t,CopySaveInfo>::iterator it = m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return false;
	}
	msgs::SPartnerIslandInfo msg;
	msg.copyCode_ =it->second.copyCode;
	if(it->second.copyCode==221){
		msg.type_=0;
	}else{
		msg.type_=1;
	}
	LogicManager::Instance()->SendMsg(uid, CMD_PARTNER_ISLAND_INFO, &msg);
	return true;
}



int CopyManager::Process(uint32_t uid, copy::CSEnterExpCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}

	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = req->copyCode;
		copyInfo.enterTime =Time::GetGlobalTime();
		copyInfo.firstEnterTime=Time::GetGlobalTime();
		copyInfo.enterNum =1;
		copyInfo.totalEnterNum =1;
		copyInfo.totalEnterDay =1;
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
		if(it->second.enterNum>=2){
			error_log("enter num wrong");
			return R_ERROR;
		}
		if (CTime::GetDayInterval(it->second.enterTime, Time::GetGlobalTime()) != 0){
			it->second.totalEnterDay++;
		}
		it->second.enterTime =Time::GetGlobalTime();
		it->second.enterNum ++;
		it->second.totalEnterNum ++;
		ATTR_DB_SET(it->second);
	}


	CopyWrap copyCfgWrap;
	SceneCfgWrap sceneCfgWrap;
	MonsterCfgWrap monsterCfgWarp;
	const CfgCopy::Copy &copyCfg = copyCfgWrap.GetCopy(req->copyCode);
	//5波怪
	vector<CfgMonster::Plan> plans;
	MonsterCfgWrap().GetPlansByMap(copyCfg.mapid(),plans);
	if(plans.empty()){
		return R_ERROR;
	}

	uint32_t mapId = copyCfg.mapid();
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(mapId);
	CopySaveInfo tmp ;
	tmp.fromMapId = pHuman->getMapId();
	tmp.mapId = copyCfg.mapid();
	tmp.copyCode = req->copyCode;
	tmp.copyType =TYPE_COPY_EXP;
	tmp.rateCount = req->count;
	tmp.wave =0;
	tmp.index=0;
	tmp.count =plans[tmp.wave].count();
	tmp.refreshTime =Time::GetGlobalTime()+33;
	Point bpos;
	bpos.x =plans[tmp.wave].pos(0).x();
	bpos.y =plans[tmp.wave].pos(0).y();
	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = copyCfg.mapid();
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();
	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = 756;
		info.desPoint.y = 1572;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return R_ERROR;
	}
	pHuman->setRealFbId((uint32_t)req->copyCode);
	MapManager::Instance()->enterMapSync();

	//copyTime
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = req->copyCode;
	msg.startDt_ = (Time::GetGlobalTime()+3)*1000LL;
	msg.endDt_ =(153+ Time::GetGlobalTime())*1000LL;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);


	uint32_t boss_base = plans[tmp.wave].boss()-150;
	uint32_t bossId = boss_base+(cache.base_.level-70)/2+cache.m_reinCarnInfo.reinCarnLevel*10;

	for(uint32_t k=0;k<plans[tmp.wave].count();k++){
		Point mpos;
		mpos.x =plans[tmp.wave].pos(k).x();
		mpos.y =plans[tmp.wave].pos(k).y();
		StdMonster *boss = new StdMonster();
		boss->init(bossId, 0, copyCfg.mapid(), mpos);
		boss->setBelong(uid);
		boss->setNeedRecove(false);
		boss->setCanMove(true);
		boss->setActively(true);
		boss->setForce(FORCE_HOSTILE);
		if (!boss->recove()) {
			error_log("recove monster failed id=%d,mapid=%d,x=%d,y=%d",bossId,copyCfg.mapid(),mpos.x,mpos.y);
			delete boss;
			return R_ERROR;
		}
	}
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSEnterGodPlane *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return R_ERR_NO_DATA;
	const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(req->copyCode);
	const CfgBoss::Boss &bossCfg = BossWrap().GetBoss(req->copyCode);
	const CfgMap::Map &mapCfg = MapCfgWrap().Get(copyCfg.mapid());
	const CfgMap::Scene &scenecfg = SceneCfgWrap().Get(mapCfg.mapscene());
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_GODPLANET,bossCfg.bossid(),index1,index2)){
		return R_ERR_NO_DATA;
	}
	CopySaveInfo tmp ;
	tmp.copyCode = (uint32_t)req->copyCode;
	tmp.copyType = copyCfg.type();
	tmp.fromMapId = pHuman->getMapId();
	tmp.bossId = bossCfg.bossid();
	tmp.mapId = copyCfg.mapid();
	map<uint32_t,CopySaveInfo>::iterator itp = m_saveInfo.find(uid);
	if(itp==m_saveInfo.end()){
		m_saveInfo.insert(make_pair(uid,tmp));
	}
	else
		itp->second=tmp;

	Point bpos;
	bpos.x =scenecfg.bosscenterpoints(0).point().x()*24+12;
	bpos.y =scenecfg.bosscenterpoints(0).point().y()*24+12;

	MapChangeInfo info;
	info.desFbInstanceId = 0;
	info.desMapId = copyCfg.mapid();;
	info.desPoint.x = scenecfg.addenterpoint_x();
	info.desPoint.y =  scenecfg.addenterpoint_y();
	if(info.desPoint.x==0||info.desPoint.y==0){
		info.desPoint.x = bpos.x;
		info.desPoint.y = bpos.y;
	}
	DataBase &base = cache.base_;
	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
		return R_ERROR;
	}
	pHuman->setRealFbId((uint32_t)req->copyCode);
	if(pData->bossInfo[index1][index2].status==BOSS_STATUS_WAIT){
		pData->bossInfo[index1][index2].owner =0;
		pData->bossInfo[index1][index2].status =BOSS_STATUS_ALIVE;
		StdMonster *boss = new StdMonster();
		boss->init(bossCfg.bossid(), 0, copyCfg.mapid(), bpos,pData->bossInfo[index1][index2].hp);
		boss->setBelong(0);
		boss->setNeedRecove(false);
		boss->setRealFbId(req->copyCode);
		boss->setForce(FORCE_HOSTILE);
		if (!boss->recove()) {
			delete boss;
			return R_ERROR;
		}
	}
	MapManager::Instance()->enterMapSync();
	msgs::SCopyTimeInfo msg;
	msg.copyCode_ = req->copyCode;
	msg.startDt_ = Time::GetGlobalTime()*1000LL;
	msg.endDt_ =0;
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
	msgs::SEnterCopy msg2;
	msg2.copyCode_ = req->copyCode;
	LogicManager::Instance()->SendMsg(uid, CMD_ENTER_GOD_PLANE, &msg2);
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end()){
		CopyInfo copyInfo;
		copyInfo.uid = uid;
		copyInfo.type = TYPE_ATTR_COPY;
		copyInfo.id = req->copyCode;
//		copyInfo.enterTime =Time::GetGlobalTime();
//		copyInfo.firstEnterTime=Time::GetGlobalTime();
//		copyInfo.enterNum =1;
//		copyInfo.totalEnterNum =1;
//		copyInfo.totalEnterDay =1;
//		copyInfo.dataExt=1;
		cache.m_copyInfo.insert(make_pair(copyInfo.id,copyInfo));
		ATTR_DB_ADD(copyInfo);
	}else{
//		if (CTime::GetDayInterval(it->second.enterTime, Time::GetGlobalTime()) != 0){
//			it->second.totalEnterDay++;
//		}
//		it->second.enterTime =Time::GetGlobalTime();
//		it->second.enterNum ++;
//		it->second.totalEnterNum ++;
//		it->second.dataExt++;
		ATTR_DB_SET(it->second);
	}
	LogicManager::Instance()->AddSync(CMD_ENTITY_UPDATE);
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSQuickFinishMaterial *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}

	for(uint32_t i =0;i<req->copyCodes.size();i++){
		map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCodes[i]);
		if(it==cache.m_copyInfo.end()){
			return R_ERROR;
		}else{
			it->second.completeNum ++;
			it->second.totalCompleteNum ++;
			it->second.enterNum ++;
			it->second.totalEnterNum ++;
			ATTR_DB_SET(it->second);
		}
		const CfgCopy::Copy &copy_cfg = CopyWrap().GetCopy(req->copyCodes[i]);
		Award reward;
		if (!reward.Format(copy_cfg.reward(), 1)) {
			error_log("parse reward error");
			return false;
		}
		UserManager::Instance()->Reward(uid, reward, "material_copy reward");
		sendUpdate(cache,req->copyCodes[i]);
	}
	return 0;
}


int CopyManager::Process(uint32_t uid, copy::CSMopMaterial *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERROR;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(req->copyCode);
	if(it==cache.m_copyInfo.end())
		return R_ERROR;
	UpdateManager::Instance()->SetCode(UC_BuyCopyNum);
	if (!UserManager::Instance()->UseMoney(uid, MONEY_GOLD, 300, "copy_mop")){
		return R_ERROR;
	}

	it->second.completeNum ++;
	it->second.totalCompleteNum ++;
	it->second.enterNum ++;
	it->second.totalEnterNum ++;
	it->second.payNum++;
	ATTR_DB_SET(it->second);

	const CfgCopy::Copy &copy_cfg = CopyWrap().GetCopy(req->copyCode);
	Award reward;
	if (!reward.Format(copy_cfg.reward(), 1)){
		error_log("parse reward error");
		return R_ERROR;
	}
	UserManager::Instance()->Reward(uid, reward, "material_copy reward");
	sendUpdate(cache,req->copyCode);
	return 0;
}



void CopyManager::onSecondTimer(){
	//检查经验副本wave
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.begin();
	for(it=m_saveInfo.begin();it!=m_saveInfo.end();it++){
		if(it->second.copyType==TYPE_COPY_EXP&&Time::GetGlobalTime()>it->second.refreshTime&&it->second.refreshTime!=0){
			if(it->second.wave==4){
				onExpFinish(it->first,it->second);
				it->second.refreshTime=0;
			}else{
				it->second.refreshTime=Time::GetGlobalTime()+30;
				it->second.wave++;
			}
		}
	}


	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return;

	for(uint32_t i=0;i<BOSS_COUNT;i++){
		if(pData->bossInfo[0][i].init&&pData->bossInfo[0][i].status==BOSS_STATUS_DEAD&&pData->bossInfo[0][i].refreshTime<Time::GetGlobalTime()){
			pData->bossInfo[0][i].refreshTime=0;
			pData->bossInfo[0][i].status = BOSS_STATUS_WAIT;
			pData->bossInfo[0][i].hp = pData->bossInfo[0][i].maxHp;
		}
		else{
			continue;
		}
		vector<uint32_t> uids;
		CacheManager::Instance()->GetAllUser(uids);
		for(uint32_t i=0;i<uids.size();i++){
			sendBossUpdate(uids[i],TYPE_COPY_TASKBOSS,pData->bossInfo[0][i].bossId);
		}
	}
	for(uint32_t i=0;i<BOSS_COUNT;i++){
		if(pData->bossInfo[1][i].init&&pData->bossInfo[1][i].status==BOSS_STATUS_DEAD&&pData->bossInfo[1][i].refreshTime<Time::GetGlobalTime()){
			pData->bossInfo[1][i].refreshTime=0;
			pData->bossInfo[1][i].status = BOSS_STATUS_WAIT;
			pData->bossInfo[1][i].hp = pData->bossInfo[1][i].maxHp;
		}
		else{
			continue;
		}
		vector<uint32_t> uids;
		CacheManager::Instance()->GetAllUser(uids);
		for(uint32_t i=0;i<uids.size();i++){
			sendBossUpdate(uids[i],TYPE_COPY_WORLDBOSS,pData->bossInfo[1][i].bossId);
		}
	}
}

void CopyManager::onHour(uint32_t hour){
	vector<uint32_t> uids;
	CacheManager::Instance()->GetAllUser(uids);
	for(uint32_t i=0;i<uids.size();i++){
		UserCache &cache = CacheManager::Instance()->GetUser(uids[i]);
		if(!cache.init_) {
			return;
		}
		for(map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.begin();it!= cache.m_copyInfo.end();it++){
			if(Time::IsToday(it->second.resetTime)) continue;
			it->second.resetTime = Time::GetGlobalTime();
			it->second.enterNum=0;
			it->second.completeNum=0;
			ATTR_DB_SET(it->second);
		}
	}
	return;
}




bool CopyManager::onMatrialMonsterDie(uint32_t uid,CopySaveInfo& saveInfo,uint32_t monsterid,const Point &diePos){
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return false;
	}
	const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(saveInfo.copyCode);
	vector<CfgMonster::Plan> plans;
	MonsterCfgWrap().GetPlansByMap(copyCfg.mapid(),plans);
	if(plans.empty()){
		return false;
	}
	if(saveInfo.bossId>plans.size()){
		return false;
	}
	if(saveInfo.bossId==plans.size()){
		onMaterialFinish(uid,saveInfo,diePos);
	}else{
		if(saveInfo.count>1){
			saveInfo.count--;
		}else{
			for(uint32_t j=0;j<plans[saveInfo.bossId].count();j++){
				Point mpos;
				mpos.x =plans[saveInfo.bossId].pos(j).x();
				mpos.y =plans[saveInfo.bossId].pos(j).y();
				StdMonster *boss = new StdMonster();
				boss->init(plans[saveInfo.bossId].boss(), 0, copyCfg.mapid(), mpos);
				boss->setBelong(uid);
				boss->setNeedRecove(false);
				boss->setForce(FORCE_HOSTILE);
				if (!boss->recove()) {
					delete boss;
					return R_ERROR;
				}
			}
			saveInfo.count =plans[saveInfo.bossId].count();
			saveInfo.bossId++;
		}
	}
	return true;
}



bool CopyManager::onImmortalRoadMonsterDie(uint32_t uid,CopySaveInfo& saveInfo,uint32_t monsterid,const Point &diePos){
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return false;
	}
	const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(saveInfo.copyCode);
	map<uint32_t,vector<CfgMonster::Plan> >plans;
	MonsterCfgWrap().GetPlansByMap(copyCfg.mapid(),plans);
	if(plans.empty()){
		return false;
	}
	if(saveInfo.count>1){
		saveInfo.count--;
	}else{
		saveInfo.wave++;
		saveInfo.count=0;
		if(saveInfo.wave>=plans.size()){
			onImmortalRoadFinish(uid,saveInfo,diePos);
			return true;
		}
		for(uint32_t j=0;j<plans[saveInfo.wave].size();j++){
			for(uint32_t k=0;k<plans[saveInfo.wave][j].count();k++){
				Point mpos;
				mpos.x =plans[saveInfo.wave][j].pos(k).x();
				mpos.y =plans[saveInfo.wave][j].pos(k).y();
				StdMonster *boss = new StdMonster();
				boss->init(plans[saveInfo.wave][j].boss(), 0, copyCfg.mapid(), mpos);
				//boss->setBelong(uid);
				boss->setNeedRecove(false);
				boss->setForce(FORCE_HOSTILE);
				if (!boss->recove()) {
					delete boss;
					return R_ERROR;
				}
				saveInfo.count++;
			}
		}

	}
	vector<uint32_t> tmp;
	uint32_t allCount=0;
	for(uint32_t j=0;j<plans[saveInfo.wave].size();j++){
		tmp.push_back(plans[saveInfo.wave][j].count());
		allCount+=plans[saveInfo.wave][j].count();
	}
	uint32_t subCount =allCount-saveInfo.count;
	for(uint32_t i=0;i<subCount;i++){
		for(uint32_t j=0;j<tmp.size();j++){
			if(tmp[j]>0){
				tmp[j]--;
				break;
			}else{
				continue;
			}
		}
	}
	map<uint32_t,uint32_t> monsterPlan;
	for(uint32_t j=0;j<tmp.size();j++){
		monsterPlan.insert(make_pair(plans[saveInfo.wave][j].boss(),tmp[j]));
	}
	sendImmortalRoadCopyInfo(uid,saveInfo.wave+1,monsterPlan);
	return true;
}


bool CopyManager::onExpMonsterDie(uint32_t uid,CopySaveInfo& saveInfo,uint32_t monsterId,const Point &diePos){
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return false;
	}
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	const CfgMonster::Monster &monCfg = MonsterCfgWrap().Get(monsterId);
	UserManager::Instance()->AddExp(uid, monCfg.exp()*it->second.rateCount);
	it->second.singExp +=monCfg.exp();
	const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(saveInfo.copyCode);
	vector<CfgMonster::Plan>plans;
	MonsterCfgWrap().GetPlansByMap(copyCfg.mapid(),plans);
	if(plans.empty()){
		return false;
	}
	saveInfo.index++;
	saveInfo.count--;
	sendExpCopyInfo(uid);
	uint32_t boss_base = plans[saveInfo.wave].boss()-150;
	uint32_t bossId = boss_base+(cache.base_.level-70)/2+cache.m_reinCarnInfo.reinCarnLevel*10;
	if(saveInfo.count<15){
		for(uint32_t j=0;j<4;j++){
			Point mpos;
			mpos.x =plans[saveInfo.wave].pos(j).x();
			mpos.y =plans[saveInfo.wave].pos(j).y();
			StdMonster *boss = new StdMonster();
			boss->init(bossId, 0, copyCfg.mapid(), mpos);
			boss->setBelong(uid);
			boss->setNeedRecove(false);
			boss->setForce(FORCE_HOSTILE);
			if (!boss->recove()) {
				delete boss;
				return R_ERROR;
			}
			saveInfo.count++;
		}
	}
	return true;
}



bool CopyManager::OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos) {
	//检查是否副本怪物
	debug_log("copyManager monster died id = %d",monster_id);
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return R_ERROR;
	}

	switch(it->second.copyType){
	//
	case 127:
		onMatrialMonsterDie(uid,it->second,monster_id,diePos);
		break;
	case 128:
		onReinCarnFinish(uid,it->second,diePos);
		break;
	case 122:
		onMagicTowerFinish(uid,it->second,diePos);
		break;
	case 130:
		onTaskCopyFinish(uid,it->second,diePos);
		break;
	case 110:
		onWorldBossFinish(uid,it->second,diePos);
		break;
	case TYPE_COPY_GODPLANET:
		onGodPlaneFinish(uid,it->second,diePos);
		break;
	case TYPE_IMMORTALROAD_COPY:
		onImmortalRoadMonsterDie(uid,it->second,monster_id,diePos);
		break;
	case TYPE_COPY_EXP:
		onExpMonsterDie(uid,it->second,monster_id,diePos);
		break;
	case TYPE_PARTNERISLAND_COPY:
		onPartnerIslandFinish(uid,it->second,diePos);
		break;
	}
	return true;
}



bool CopyManager::checkReset(CopyInfo& copyInfo){
	if (CTime::GetDayInterval(copyInfo.resetTime, Time::GetGlobalTime()) == 0) {
		return false ;
	}
	copyInfo.completeNum = 0;
	copyInfo.enterNum = 0;
	copyInfo.resetTime = Time::GetGlobalTime();
	ATTR_DB_SET(copyInfo);
	return true;
}



bool CopyManager::onReinCarnFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end())
		return false;
	if(it->second.data==0){
		it->second.data=1;
		it->second.completeNum ++;
		it->second.totalCompleteNum ++;
	}
	ATTR_DB_SET(it->second);
	sendUpdate(cache,saveInfo.copyCode);
	//发奖
	try{
		const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(saveInfo.bossId);
		Award reward;
		reward.Random(drop_cfg.randomreward(), drop_cfg.randomcount());
		if (!reward.Format(drop_cfg.fixedreward(), 1)) {
			error_log("parse reward error");
			return false;
		}
		MonsterDrop(uid, saveInfo.bossId,reward,diePos);
		vector<msgs::SItemAmount> v;
		reward.Get(v);
		msgs::SCompleteReincarnCopy msg;
		msg.failed_ = false;
		msg.costCount_ =0;
		msg.copyCode_ = saveInfo.copyCode;
		for(uint32_t i=0;i<v.size();i++){
			msg.rewards_.insert(make_pair(v[i].itemCode_,v[i].itemNum_));
		}
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_REINCARN_COPY, &msg);
		MissionManager::Instance()->onSubMission(uid, MT_KILL_BOSS, saveInfo.copyCode, 1);
	}catch(...){
		return false;
	}
	return true;
}


bool CopyManager::onMagicTowerFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end()){
		return false;
	}
	it->second.data++;
	it->second.totalCompleteNum++;
	it->second.totalEnterDay++;
	it->second.totalEnterNum++;
	ATTR_DB_SET(it->second);
	LogicManager::Instance()->AddSync(CMD_LOTTERY_MAGIC_TOWER);
	sendUpdate(cache,saveInfo.copyCode);
	//发奖
	const CfgMagic::MagicTower &tower_cfg = MagicTowerWrap().GetMagicTower(saveInfo.bossId);
	Award reward;
	if (!reward.Format(tower_cfg.reward(), 1)) {
		error_log("parse reward error");
		return false;
	}
	UserManager::Instance()->Reward(uid, reward, "magic_tower reward");
	vector<msgs::SItemAmount> v;
	reward.Get(v);
	msgs::SCompleteMagicTowerCopy msg;
	msg.completeTime_ = Time::GetGlobalTime();
	msg.layer_ = saveInfo.bossId;
	msg.isQuick_ =false;
	msg.isDoubleExp_ =false;
	msg.failed_ = false;
	msg.costCount_ =0;
	msg.copyCode_ = saveInfo.copyCode;
	for(uint32_t i=0;i<v.size();i++){
		msg.rewards_.insert(make_pair(v[i].itemCode_,v[i].itemNum_));
	}

	MissionManager::Instance()->onMission(uid, MT_RUNE_TOWER,it->second.data);
	LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_MAGIC_TOWER_COPY, &msg);
	LogicManager::Instance()->AddSync(CMD_MAGIC_INFO);
	return true;
}


bool CopyManager::onPartnerIslandFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end()){
		return false;
	}
	it->second.data++;
	it->second.totalCompleteNum++;
	it->second.totalEnterDay++;
	it->second.totalEnterNum++;
	ATTR_DB_SET(it->second);
	sendUpdate(cache,saveInfo.copyCode);

	//发奖
	const CfgPartnerIsland::PartnerIsland &cfg = PartnerIslandWrap().GetPartnerIsland(saveInfo.index,saveInfo.bossId);
	Award reward;
	if (!reward.Format(cfg.reward(), 1)) {
		error_log("parse reward error");
		return false;
	}
	if (!reward.Format(cfg.exreward(), 1)) {
		error_log("parse reward error");
		return false;
	}
	UserManager::Instance()->Reward(uid, reward, "PartnerIsland reward");
	msgs::SCompletePartnerIsland msg;
	msg.type_ =saveInfo.index;
	msg.completeTime_=Time::GetGlobalTime()-saveInfo.startTime;
	msg.copyCode_ = saveInfo.copyCode;
	msg.costCount_ =0;
	msg.failed_ = false;
	msg.isDoubleExp_ =false;
	msg.isQuick_ =false;
	msg.layer_ = saveInfo.bossId;
	LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_PARTNER_ISLAND, &msg);
	return true;
}

bool CopyManager::onTaskCopyFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point& diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end()){
		return false;
	}
	map<uint32_t,CopySaveInfo>::iterator itc = m_saveInfo.find(uid);
	if(itc==m_saveInfo.end()){
		return false;
	}

	it->second.completeNum++;
	it->second.totalCompleteNum++;
	ATTR_DB_SET(it->second);
	sendUpdate(cache,saveInfo.copyCode);
	//发奖
	const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(saveInfo.bossId);
	msgs::SCompleteTaskCopy msg;
	onTaskBossDie(itc->second.bossId);
	sendBossUpdate(uid, TYPE_COPY_TASKBOSS,itc->second.bossId);
	Award reward;
	reward.Random(drop_cfg.killreward(), drop_cfg.killrewardcount());
	vector<BossPlayerRank> tmp;
	m_data->getBossRank(TYPE_COPY_TASKBOSS,itc->second.bossId,tmp);

	if(uid ==tmp[0].uid){
		reward.Random(drop_cfg.ownreward(), drop_cfg.ownrewardcount());
	}

	MonsterDrop(uid,saveInfo.bossId,reward,diePos);
	msg.failed_ = false;
	msg.costCount_ =0;
	msg.copyCode_ = saveInfo.copyCode;
	msg.ownerMonsterId_ = saveInfo.bossId;
	reward.Get(msg.rewards_);
	LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_TASK_COPY, &msg);
	MissionManager::Instance()->onEnterCopy(uid,MT_TASK_COPY,saveInfo.copyCode);
	LogicManager::Instance()->AddSync(CMD_PLAYER_CONFIG);
	return true;
}



void CopyManager::onTaskBossDie(uint32_t bossId){
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return;
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_TASKBOSS,bossId,index1,index2)){
		return ;
	}
	if(pData->bossInfo[index1][index2].status!=BOSS_STATUS_ALIVE){
		return;
	}
	pData->bossInfo[index1][index2].status =BOSS_STATUS_DEAD;
	pData->bossInfo[index1][index2].refreshTime = Time::GetGlobalTime()+15*60;
	pData->bossInfo[index1][index2].hp =0;
	map<uint32_t,CopyBoss>::iterator it =  m_worldboss.find(bossId);
}

void CopyManager::onWorldBossDie(uint32_t bossId){
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return;
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_WORLDBOSS,bossId,index1,index2)){
		return ;
	}
	if(pData->bossInfo[index1][index2].status!=BOSS_STATUS_ALIVE)
		return ;
	pData->bossInfo[index1][index2].status = BOSS_STATUS_DEAD;
	pData->bossInfo[index1][index2].refreshTime = Time::GetGlobalTime()+15*60;
	pData->bossInfo[index1][index2].hp = 0;
}


bool CopyManager::onWorldBossFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end()){
		return false;
	}
	map<uint32_t,CopySaveInfo>::iterator itc = m_saveInfo.find(uid);
	if(itc==m_saveInfo.end()){
		return false;
	}

	it->second.completeNum++;
	it->second.totalCompleteNum++;
	ATTR_DB_SET(it->second);
	sendUpdate(cache,saveInfo.copyCode);
	//发奖
	const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(saveInfo.bossId);
	msgs::SCompleteBoss msg;
	onWorldBossDie(itc->second.bossId);
	sendBossUpdate(uid,TYPE_COPY_WORLDBOSS,itc->second.bossId);

	Award reward;
	reward.Random(drop_cfg.killreward(), drop_cfg.killrewardcount());
	vector<BossPlayerRank> tmp;
	m_data->getBossRank(TYPE_COPY_WORLDBOSS,itc->second.bossId,tmp);
	if(uid ==tmp[0].uid){
		reward.Random(drop_cfg.ownreward(), drop_cfg.ownrewardcount());
	}
	MonsterDrop(uid,saveInfo.bossId,reward,diePos);

	Human *pHuman = MapManager::Instance()->getHuman(tmp[0].uid);
	if (pHuman != NULL) {
		msg.publicPlayer_.name_ = pHuman->getName();
		msg.publicPlayer_.entityId_ = pHuman->getEntityMsg();
		msg.publicPlayer_.sex_ = pHuman->getSex();
		msg.publicPlayer_.career_ =pHuman->getCareer();
		msg.publicPlayer_.careerLevel_ = 2;
		msg.publicPlayer_.level_ = pHuman->getLevel();
		msg.publicPlayer_.vipLevel_ = 3;
		msg.publicPlayer_.hangLevel_=0;
		msg.publicPlayer_.combat_ =0;
		msg.publicPlayer_.online_ =0;
		msg.publicPlayer_.camp_ =0;

	}
	msg.guildName_="";
	msg.failed_ = true;
	msg.costCount_ =0;
	msg.copyCode_ = saveInfo.copyCode;
	reward.Get(msg.rewards_);
	LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_WORLD_BOSS, &msg);;
	return true;
}

bool CopyManager::onGodPlaneFinish(uint32_t uid,CopySaveInfo& saveInfo,const Point &diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end()){
		return false;
	}
	map<uint32_t,CopySaveInfo>::iterator itc = m_saveInfo.find(uid);
	if(itc==m_saveInfo.end()){
		return false;
	}
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return false;
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_GODPLANET,itc->second.bossId,index1,index2)){
		return false;
	}
	if(pData->bossInfo[index1][index2].status!=BOSS_STATUS_ALIVE)
		return false;
	pData->bossInfo[index1][index2].status = BOSS_STATUS_DEAD;
	pData->bossInfo[index1][index2].refreshTime = Time::GetGlobalTime()+15*60;
	pData->bossInfo[index1][index2].hp = 0;
	sendUpdate(cache,saveInfo.copyCode);
	const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(saveInfo.bossId);
	sendBossUpdate(uid,TYPE_COPY_GODPLANET,itc->second.bossId);
	Award reward;
	reward.Random(drop_cfg.ownreward(), drop_cfg.ownrewardcount());
	MonsterDrop(pData->bossInfo[index1][index2].owner,saveInfo.bossId,reward,diePos);
	Human *pHuman = MapManager::Instance()->getHuman(pData->bossInfo[index1][index2].owner);
	msgs::SCompleteBoss msg;
	if (pHuman != NULL) {
		msg.publicPlayer_.name_ = pHuman->getName();
		msg.publicPlayer_.entityId_ = pHuman->getEntityMsg();
		msg.publicPlayer_.sex_ = pHuman->getSex();
		msg.publicPlayer_.career_ =pHuman->getCareer();
		msg.publicPlayer_.careerLevel_ = 2;
		msg.publicPlayer_.level_ = pHuman->getLevel();
		msg.publicPlayer_.vipLevel_ = 3;
		msg.publicPlayer_.hangLevel_=0;
		msg.publicPlayer_.combat_ =0;
		msg.publicPlayer_.online_ =0;
		msg.publicPlayer_.camp_ =0;
	}
	msg.guildName_="";
	msg.failed_ = false;
	msg.costCount_ =0;
	msg.copyCode_ = saveInfo.copyCode;
	reward.Get(msg.rewards_);
	LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_GOD_PLANE, &msg);
	return true;
}

bool CopyManager::onMaterialFinish(uint32_t uid,CopySaveInfo& saveInfo, const Point &diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end())
		return false;
	if(it->second.data==0){
		it->second.data=1;
		it->second.completeNum ++;
		it->second.totalCompleteNum ++;
	}
	ATTR_DB_SET(it->second);
	sendUpdate(cache,saveInfo.copyCode);
	//发奖
	try{
		const CfgCopy::Copy &copy_cfg = CopyWrap().GetCopy(saveInfo.copyCode);
		Award reward;
		if (!reward.Format(copy_cfg.reward(), 1)) {
			error_log("parse reward error");
			return false;
		}
		UserManager::Instance()->Reward(uid, reward, "material_copy reward");
		msgs::SCompleteMaterialCopy msg;
		msg.failed_ = false;
		msg.costCount_ =0;
		msg.copyCode_ = saveInfo.copyCode;
		for(uint32_t i=0;i<(uint32_t)copy_cfg.reward().size();i++){
			msg.rewards_.insert(make_pair(copy_cfg.reward(i).item(),copy_cfg.reward(i).num()));
		}
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_MATERIAL_COPY, &msg);
	}catch(...){
		return false;
	}
	return true;
}

bool CopyManager::onExpFinish(uint32_t uid,CopySaveInfo& saveInfo){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
	if(it==cache.m_copyInfo.end())
		return false;
	it->second.completeNum ++;
	it->second.totalCompleteNum ++;
	//发奖
	try{
		msgs::SCompleteExpCopy msg;
		msg.failed_ = false;
		msg.costCount_ =0;
		msg.copyCode_ = saveInfo.copyCode;
		msg.lastTotalExp_ = it->second.data;
		msg.singleTotalExp_ = saveInfo.singExp;
		msg.monsterKilledNum_ = saveInfo.index;
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_EXP_COPY, &msg);
	}catch(...){
		return false;
	}
	if(saveInfo.singExp>it->second.data){
		it->second.data =saveInfo.singExp;
		UserManager::Instance()->AddExp(uid, saveInfo.singExp);
	}
	ATTR_DB_SET(it->second);
	sendUpdate(cache,saveInfo.copyCode);
	return true;
}

bool CopyManager::onImmortalRoadFinish(uint32_t uid,CopySaveInfo& saveInfo, const Point &diePos){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
//	map<uint32_t, CopyInfo>::iterator it = cache.m_copyInfo.find(saveInfo.copyCode);
//	if(it==cache.m_copyInfo.end())
//		return false;
//	if(it->second.data==0){
//		it->second.data=1;
//		it->second.completeNum ++;
//		it->second.totalCompleteNum ++;
//	}
//	ATTR_DB_SET(it->second);
//	sendUpdate(cache,saveInfo.copyCode);
	//发奖
	try{
		const CfgCopy::Copy &copy_cfg = CopyWrap().GetCopy(saveInfo.copyCode);
		Award reward;
		if (!reward.Format(copy_cfg.reward(), 1)) {
			error_log("parse reward error");
			return false;
		}
		UserManager::Instance()->Reward(uid, reward, "material_copy reward");
		msgs::SCompleteImmortalRoadCopy msg;
		msg.isAssist_ =false;
		msg.costTime_ = 100;
		msg.failed_ = false;
		msg.costCount_ =0;
		msg.copyCode_ = saveInfo.copyCode;
		//msg.records_ =
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_IMMORTAL_ROAD_COPY, &msg);
	}catch(...){
		return false;
	}
	return true;
}

bool CopyManager::MonsterDrop(uint32_t uid, uint32_t monster_id, Award& reward,const Point &diePos) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return false;
	}
	try {
		msgs::SPlayerAutoDrop msg;
		msg.belongEntityId_ = pHuman->getEntityMsg();
		msg.dropPoint_.x = diePos.x;
		msg.dropPoint_.y = diePos.y;
		msg.type_ = 0;
		reward.Get(msg.items_);
		UpdateManager::Instance()->SetCode(UC_AddDrop);
		string code;
		String::Format(code, "copy_boss_%u", monster_id);
		if (!UserManager::Instance()->Reward(uid, reward, code)) {
			return false;
		}
		LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_AUTO_DROP_BAG, &msg);
		return true;
	}catch(...){
		return false;
	}
}



bool CopyManager::OnHumanDie(uint32_t uid) {
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return R_ERR_NO_DATA;
	}
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	if(it->second.copyType==127){
		msgs::SCompleteMaterialCopy msg;
		msg.failed_ = true;
		msg.costCount_ =0;
		msg.copyCode_ = it->second.copyCode;
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_MATERIAL_COPY, &msg);
	}else if(it->second.copyType==128){
		msgs::SCompleteReincarnCopy msg;
		msg.failed_ = true;
		msg.costCount_ =0;
		msg.copyCode_ = it->second.copyCode;
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_REINCARN_COPY, &msg);

	}else if(it->second.copyType==122){
		msgs::SCompleteMagicTowerCopy msg;
		msg.completeTime_ = Time::GetGlobalTime();
		msg.layer_ = it->second.bossId;
		msg.isQuick_ =false;
		msg.isDoubleExp_ =false;
		msg.failed_ = true;
		msg.costCount_ =0;
		msg.copyCode_ = it->second.copyCode;
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_MAGIC_TOWER_COPY, &msg);
	}else if(it->second.copyType==TYPE_COPY_WORLDBOSS){



	}else if(it->second.copyType==TYPE_COPY_GODPLANET){



	}else if(it->second.copyType==TYPE_COPY_TASKBOSS){



	}else if(it->second.copyType==TYPE_IMMORTALROAD_COPY){


	}else if(it->second.copyType==TYPE_PARTNERISLAND_COPY){
		msgs::SCompletePartnerIsland msg;
		msg.type_ =it->second.index;
		msg.completeTime_=Time::GetGlobalTime();
		msg.copyCode_ = it->second.copyCode;
		msg.costCount_ =0;
		msg.failed_ = true;
		msg.isDoubleExp_ =false;
		msg.isQuick_ =false;
		msg.layer_ = it->second.bossId;
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_PARTNER_ISLAND, &msg);
	}
	return true;
}


bool CopyManager::OnCopyHumanDie(uint32_t uid) {
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return R_ERR_NO_DATA;
	}
	if(it->second.copyType==TYPE_COPY_GODPLANET){
		onGoldPlaneHumanDie(uid);
		return true;
	}else if(it->second.copyType==TYPE_COPY_WORLDBOSS){
		return true;
	}else{
		return false;
	}

}


void CopyManager::resetGodPlaneBoss(uint32_t bossId){
	DataCopy * pData =m_data->getDataCopy();
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_GODPLANET,bossId,index1,index2)){
		return ;
	}
	pData->bossInfo[index1][index2].owner=0;
	pData->bossInfo[index1][index2].refreshTime =0;
	pData->bossInfo[index1][index2].hp = pData->bossInfo[index1][index2].maxHp;
	MapMoveObject * monObj = MapManager::Instance()->getMonster(bossId);
	monObj->doRecover();
}

bool CopyManager::onGoldPlaneHumanDie(uint32_t uid){
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return R_ERR_NO_DATA;
	}
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}
	DataCopy * pData =m_data->getDataCopy();
	//human 重生
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_GODPLANET,it->second.bossId,index1,index2)){
		return false;
	}
	if(pData->bossInfo[index1][index2].owner==uid){
		pData->bossInfo[index1][index2].owner=0;
	}

	sendPlayerDeath(uid,it->second.bossId,Time::GetGlobalTime()+10);
	return true;
}



void CopyManager::OnTaskBossHurt(uint32_t mapIndex,uint32_t monsterId,map<uint64_t, HurtInfo>& hurtList,uint64_t hp){
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return;
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_TASKBOSS,monsterId,index1,index2)){
		return ;
	}
	if(pData->bossInfo[index1][index2].status!=BOSS_STATUS_ALIVE)
		return;

	pData->bossInfo[index1][index2].hp =hp;
	for(map<uint64_t, HurtInfo>::iterator itp = hurtList.begin();itp!=hurtList.end();itp++){
		m_data->setBossRank(TYPE_COPY_TASKBOSS,monsterId,itp->second.id,itp->second.hurt);
	}
	vector<BossPlayerRank> ranks;
	m_data->getBossRank(TYPE_COPY_TASKBOSS,monsterId,ranks);

	msgs::SBossHurtRank msg;
	msg.myRank_=0;
	MapDisplayObject * monObj = MapManager::Instance()->getObject(mapIndex);
	msg.bossEntityId_ =monObj->getEntityMsg();
	for(uint32_t i=0;i<ranks.size();i++){
		Human *pHuman = MapManager::Instance()->getHuman(ranks[i].uid);
		if (pHuman == NULL) {
			continue;
		}
		msgs::SPlayerBossHurt tmp;
		tmp.hurt_ =ranks[i].value;
		tmp.name_ = pHuman->getName();
		tmp.rank_ =i+1;
		tmp.entityId_ = pHuman->getEntityMsg();
		msg.ranks_.push_back(tmp);
	}
	for(map<uint32_t,CopySaveInfo>::iterator itc = m_saveInfo.begin();itc!=m_saveInfo.end();itc++){
		if(itc->second.bossId ==monsterId){
			for(uint32_t i=0;i<3;i++){
				if(itc->first==ranks[i].uid){
					Human *pHuman2 = MapManager::Instance()->getHuman(itc->first);
					if (pHuman2 == NULL) {
						continue;
					}
					msgs::SPlayerBossHurt tmp;
					tmp.hurt_ =ranks[i].value;
					tmp.name_ = pHuman2->getName();
					tmp.rank_ =i+1;
					tmp.entityId_ = pHuman2->getEntityMsg();
					msg.ranks_.push_back(tmp);
				}
			}
			LogicManager::Instance()->SendMsg(itc->first, CMD_BOSS_HURT_RANK, &msg);
		}
	}
}



void CopyManager::OnGodPlaneHurt(uint32_t monsterId,uint32_t lastAttacker){
	MapDisplayObject * monObj = MapManager::Instance()->getMonster(monsterId);
	uint32_t mapId = monObj->getMapId();
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return;
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_GODPLANET,monsterId,index1,index2)){
		return ;
	}
	if(pData->bossInfo[index1][index2].owner==0){
		pData->bossInfo[index1][index2].owner =lastAttacker;
		vector<Human *> vecHumans;
		MapManager::Instance()->getMapHumans(0,mapId, vecHumans);
		for(uint32_t i=0;i<vecHumans.size();i++){
			sendEntityUpdate(vecHumans[i]->getUid(),monsterId,pData->bossInfo[index1][index2].owner);
		}
	}
}

void CopyManager::OnWorldBossHurt(uint32_t mapIndex,uint32_t monsterId,map<uint64_t, HurtInfo>& hurtList,uint64_t hp){
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return;
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_WORLDBOSS,monsterId,index1,index2)){
		return ;
	}
	if(pData->bossInfo[index1][index2].status!=BOSS_STATUS_ALIVE)
		return;

	pData->bossInfo[index1][index2].hp =hp;
	for(map<uint64_t, HurtInfo>::iterator itp = hurtList.begin();itp!=hurtList.end();itp++){
		m_data->setBossRank(TYPE_COPY_WORLDBOSS,monsterId,itp->second.id,itp->second.hurt);
	}
	vector<BossPlayerRank> ranks;
	m_data->getBossRank(TYPE_COPY_WORLDBOSS,monsterId,ranks);

	msgs::SBossHurtRank msg;
	msg.myRank_=0;
	MapDisplayObject * monObj = MapManager::Instance()->getObject(mapIndex);
	msg.bossEntityId_ =monObj->getEntityMsg();
	for(uint32_t i=0;i<ranks.size();i++){
		Human *pHuman = MapManager::Instance()->getHuman(ranks[i].uid);
		if (pHuman == NULL) {
			continue;
		}
		msgs::SPlayerBossHurt tmp;
		tmp.hurt_ =ranks[i].value;
		tmp.name_ = pHuman->getName();
		tmp.rank_ =i+1;
		tmp.entityId_ = pHuman->getEntityMsg();
		msg.ranks_.push_back(tmp);
	}
	for(map<uint32_t,CopySaveInfo>::iterator itc = m_saveInfo.begin();itc!=m_saveInfo.end();itc++){
		if(itc->second.bossId ==monsterId){
			for(uint32_t i=0;i<3;i++){
				if(itc->first==ranks[i].uid){
					Human *pHuman2 = MapManager::Instance()->getHuman(itc->first);
					if (pHuman2 == NULL) {
						continue;
					}
					msgs::SPlayerBossHurt tmp;
					tmp.hurt_ =ranks[i].value;
					tmp.name_ = pHuman2->getName();
					tmp.rank_ =i+1;
					tmp.entityId_ = pHuman2->getEntityMsg();
					msg.ranks_.push_back(tmp);
				}
			}
			LogicManager::Instance()->SendMsg(itc->first, CMD_BOSS_HURT_RANK, &msg);
		}
	}
}

void CopyManager::OnHurt(uint32_t copyId,uint32_t mapIndex,uint32_t monsterId,uint32_t lastAttacker,map<uint64_t, HurtInfo>& hurtList,uint64_t hp){
	if(copyId==0){
		return;
	}
	const CfgCopy::Copy &copyCfg = CopyWrap().GetCopy(copyId);
	switch(copyCfg.type()){
	case TYPE_COPY_TASKBOSS:
		OnTaskBossHurt(mapIndex,monsterId,hurtList,hp);
		break;
	case TYPE_COPY_WORLDBOSS:
		OnWorldBossHurt(mapIndex,monsterId,hurtList,hp);
		break;
	case TYPE_COPY_GODPLANET:
		OnGodPlaneHurt(monsterId,lastAttacker);
		break;
	}
}


int CopyManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerCopyDataList *resp) {
	for(map<uint32_t, CopyInfo>::const_iterator it = cache.m_copyInfo.begin();it!=cache.m_copyInfo.end();it++){
		dbs::TPlayerCopyData tmp;
		tmp.playerId_ = cache.base_.uid;
		tmp.copyGroup_ = it->second.id;
		tmp.data_ = it->second.data;
		tmp.dataEx_ = it->second.dataExt;
		tmp.enterNum_ = it->second.enterNum;
		tmp.completeNum_ = it->second.completeNum;
		tmp.todayEnterNum_ = it->second.enterNum;
		tmp.totalEnterDay_ = it->second.totalEnterDay;
		tmp.todayEnterNum_ = it->second.totalEnterNum;
		tmp.totalCompleteNum_ = it->second.totalCompleteNum;
		tmp.enterTime_ = it->second.enterTime;
		tmp.getBackNum_ =0;
		tmp.assistNum_ =0;
		tmp.grabNum_=0;
		resp->copyDatas_.push_back(tmp);
	}
	LogicManager::Instance()->SendMsg(cache.uid_,CMD_PLAYER_COPY_DATA_LIST,resp);
	return 0;
}

int CopyManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SLotteryMagicTower *resp) {
	resp->round_=0;
	map<uint32_t, CopyInfo>::const_iterator it = cache.m_copyInfo.find(MAGIC_TOWER_COPY);
	if(it==cache.m_copyInfo.end()){
		return 0;
	}
	uint32_t count =it->second.data/10;
	for(uint32_t i=0;i<10;i++){
		if(GET_BIT(it->second.rewardMark,i)){
			resp->rewardMap_.insert(make_pair(i,true));
			count--;
		}
	}
	resp->remainCount_=count;
	LogicManager::Instance()->SendMsg(cache.uid_,CMD_LOTTERY_MAGIC_TOWER,resp);
	return 0;
}


int CopyManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SBossList *resp){
	DataCopy * pData = m_data->getDataCopy();
	if(!pData)return false;
	map<uint32_t,CopyBoss>::iterator it;
	resp->type_ = 0;
//	for(uint32_t i=0;i<BOSS_COUNT;i++){
//		if(pData->bossInfo[1][i].bossId==0)
//			continue;
//		msgs::SBoss tmp;
//		tmp.bossId_ = pData->bossInfo[1][i].bossId;
//		tmp.copyCode_ =pData->bossInfo[1][i].copyId;
//		tmp.lastKillName_ ="";
//		tmp.lastKillTime_ =0;
//		if(pData->bossInfo[1][i].status==BOSS_STATUS_DEAD){
//			tmp.life_ =0;
//			tmp.refreshTime_ =pData->bossInfo[1][i].refreshTime*1000LL;
//		}else{
//			tmp.life_ = pData->bossInfo[1][i].hp;
//			tmp.refreshTime_ =0;
//		}
//		tmp.maxLife_ = pData->bossInfo[1][i].maxHp;
//		tmp.line_ = 0;
//		tmp.playerNum_ = 0;
//		resp->seq_.push_back(tmp);
//	}
	LogicManager::Instance()->SendMsg(cache.uid_,CMD_BOSS_INFO,resp);
	return 0;
}

int CopyManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SEntityUpdate *resp){
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return R_ERROR;
	map<uint32_t,CopySaveInfo>::iterator it =  m_saveInfo.find(cache.uid_);
	if(it==m_saveInfo.end()){
		return R_ERROR;
	}
	uint32_t index1 =0;
	uint32_t index2=0;
	if(!m_data->getBossIndex(TYPE_COPY_GODPLANET,it->second.bossId,index1,index2)){
		return R_ERROR;
	}
	MapDisplayObject * monObj = MapManager::Instance()->getMonster(it->second.bossId);
	resp->entityId_ = monObj->getEntityMsg();
	resp->updateType_ =71;
	resp->updateStr_="";
	Human *pHuman = MapManager::Instance()->getHuman(pData->bossInfo[index1][index2].owner);
	if (pHuman == NULL) {
		return false;
	}
	Identity tmp = pHuman->getEntityMsg();
	resp->updateData_.push_back(tmp.proxy_);
	resp->updateData_.push_back(tmp.server_);
	resp->updateData_.push_back(tmp.type_);
	resp->updateData_.push_back(tmp.id_);
	LogicManager::Instance()->SendMsg(cache.uid_, CMD_ENTITY_UPDATE, resp);
	return 0;
}

bool CopyManager::sendGodPlaneList(uint32_t uid){
	msgs::SBossList resp;
	DataCopy * pData = m_data->getDataCopy();
	if(!pData)return false;
	resp.type_ = 2;
	for(uint32_t i=0;i<BOSS_COUNT;i++){
		if(pData->bossInfo[2][i].bossId==0)
			continue;
		msgs::SBoss tmp;
		tmp.bossId_ = pData->bossInfo[2][i].bossId;
		tmp.copyCode_ =pData->bossInfo[2][i].copyId;
		tmp.lastKillName_ ="";
		tmp.lastKillTime_ =0;
		if(pData->bossInfo[2][i].status==BOSS_STATUS_DEAD){
			tmp.life_ =0;
			tmp.refreshTime_ =pData->bossInfo[2][i].refreshTime*1000LL;
		}else{
			tmp.life_ = pData->bossInfo[2][i].hp;
			tmp.refreshTime_ =0;
		}
		tmp.maxLife_ = pData->bossInfo[2][i].maxHp;
		tmp.line_ = 0;
		tmp.playerNum_ = 0;
		resp.seq_.push_back(tmp);
	}
	LogicManager::Instance()->SendMsg(uid,CMD_BOSS_INFO,&resp);
	return true;
}



bool CopyManager::sendWorldBossList(uint32_t uid){
	msgs::SBossList resp;
	DataCopy * pData = m_data->getDataCopy();
	if(!pData)return false;
	resp.type_ = 0;
	for(uint32_t i=0;i<BOSS_COUNT;i++){
		if(pData->bossInfo[1][i].bossId==0)
			continue;
		msgs::SBoss tmp;
		tmp.bossId_ = pData->bossInfo[1][i].bossId;
		tmp.copyCode_ =pData->bossInfo[1][i].copyId;
		tmp.lastKillName_ ="";
		tmp.lastKillTime_ =0;
		if(pData->bossInfo[1][i].status==BOSS_STATUS_DEAD){
			tmp.life_ =0;
			tmp.refreshTime_ =pData->bossInfo[1][i].refreshTime*1000LL;
		}else{
			tmp.life_ = pData->bossInfo[1][i].hp;
			tmp.refreshTime_ =0;
		}
		tmp.maxLife_ = pData->bossInfo[1][i].maxHp;
		tmp.line_ = 0;
		tmp.playerNum_ = 0;
		resp.seq_.push_back(tmp);
	}
	LogicManager::Instance()->SendMsg(uid,CMD_BOSS_INFO,&resp);
	return true;
}

bool CopyManager::sendUpdate(const UserCache &cache, uint32_t copyId){
	map<uint32_t, CopyInfo>::const_iterator it = cache.m_copyInfo.find(copyId);
	if(it==cache.m_copyInfo.end()){
		return false;
	}
	dbs::TPlayerCopyData resp;
	resp.playerId_ = cache.base_.uid;
	resp.copyGroup_ = it->second.id;
	resp.data_ = it->second.data;
	resp.dataEx_ = it->second.dataExt;
	resp.enterTime_ = it->second.enterTime;
	resp.enterNum_ = it->second.enterNum;
	resp.completeNum_ = it->second.completeNum;
	resp.todayEnterNum_ = it->second.enterNum;
	resp.totalEnterDay_ = (Time::GetGlobalTime()-it->second.enterTime)/86400+1;
	resp.totalEnterNum_ = it->second.totalEnterNum;
	resp.totalCompleteNum_ = it->second.totalCompleteNum;
	resp.enterTime_ = it->second.enterTime;
	resp.copyGroup_ = it->second.id;
	resp.enterTime_ = it->second.enterTime;
	resp.getBackNum_ =0;
	resp.assistNum_ =0;
	resp.grabNum_=0;
	resp.extend_="";
	resp.json_="";
	LogicManager::Instance()->SendMsg(cache.base_.uid, CMD_PLAYER_COPY_DATA_UPDATE, &resp);
	return true;
}

bool CopyManager::sendBossUpdate(uint32_t uid, uint32_t type,uint32_t bossId){
	DataCopy * pData =m_data->getDataCopy();
	if(!pData)return false;
	if(type==TYPE_COPY_TASKBOSS){
		for(uint32_t i=0;i<BOSS_COUNT;i++){
			if(pData->bossInfo[0][i].bossId==bossId){
				msgs::SBoss msg;
				msg.bossId_ = pData->bossInfo[0][i].bossId;
				msg.copyCode_ =pData->bossInfo[0][i].copyId;
				if(pData->bossInfo[0][i].status ==BOSS_STATUS_DEAD){
					msg.life_ =0;
					msg.refreshTime_ =pData->bossInfo[0][i].refreshTime*1000LL;
				}else{
					msg.life_ = pData->bossInfo[0][i].hp;
					msg.refreshTime_=0;

				}
				msg.maxLife_ = pData->bossInfo[0][i].maxHp;
				msg.lastKillName_="";
				msg.lastKillTime_=0;
				msg.line_=0;
				msg.playerNum_=0;
				LogicManager::Instance()->SendMsg(uid, CMD_UPDATE_BOSS, &msg);
				return true;
			}
		}
	}else if(type==TYPE_COPY_WORLDBOSS){
		for(uint32_t i=0;i<BOSS_COUNT;i++){
			if(pData->bossInfo[1][i].bossId==bossId){
				msgs::SBoss msg;
				msg.bossId_ = pData->bossInfo[1][i].bossId;
				msg.copyCode_ =pData->bossInfo[1][i].copyId;
				if(pData->bossInfo[1][i].status ==BOSS_STATUS_DEAD){
					msg.life_ =0;
					msg.refreshTime_ =pData->bossInfo[1][i].refreshTime*1000LL;
				}else{
					msg.life_ = pData->bossInfo[1][i].hp;
					msg.refreshTime_=0;

				}
				msg.maxLife_ = pData->bossInfo[1][i].maxHp;
				msg.lastKillName_="";
				msg.lastKillTime_=0;
				msg.line_=0;
				msg.playerNum_=0;
				LogicManager::Instance()->SendMsg(uid, CMD_UPDATE_BOSS, &msg);
				return true;
			}
		}
	}else if(type ==TYPE_COPY_GODPLANET){
		for(uint32_t i=0;i<BOSS_COUNT;i++){
			if(pData->bossInfo[2][i].bossId==bossId){
				msgs::SBoss msg;
				msg.bossId_ = pData->bossInfo[1][i].bossId;
				msg.copyCode_ =pData->bossInfo[1][i].copyId;
				if(pData->bossInfo[2][i].status ==BOSS_STATUS_DEAD){
					msg.life_ =0;
					msg.refreshTime_ =pData->bossInfo[2][i].refreshTime*1000LL;
				}else{
					msg.life_ = pData->bossInfo[2][i].hp;
					msg.refreshTime_=0;

				}
				msg.maxLife_ = pData->bossInfo[2][i].maxHp;
				msg.lastKillName_="";
				msg.lastKillTime_=0;
				msg.line_=0;
				msg.playerNum_=0;
				LogicManager::Instance()->SendMsg(uid, CMD_UPDATE_BOSS, &msg);
				return true;
			}
		}
	}
	return false;
}


bool CopyManager::sendEntityUpdate(uint32_t uid,uint32_t monsterId,uint64_t ownerId){
	msgs::SEntityUpdate msg;
	MapDisplayObject * monObj = MapManager::Instance()->getMonster(monsterId);
	msg.entityId_ = monObj->getEntityMsg();
	msg.updateType_ =71;
	msg.updateStr_="";
	Human *pHuman = MapManager::Instance()->getHuman(ownerId);
	if (pHuman == NULL) {
		return false;
	}
	Identity tmp = pHuman->getEntityMsg();
	msg.updateData_.push_back(tmp.proxy_);
	msg.updateData_.push_back(tmp.server_);
	msg.updateData_.push_back(tmp.type_);
	msg.updateData_.push_back(tmp.id_);
	LogicManager::Instance()->SendMsg(uid, CMD_ENTITY_UPDATE, &msg);
	return true;
}


bool CopyManager::sendPlayerDeath(uint32_t uid,uint32_t bossId,uint32_t reviveTime){
	msgs::SPlayerDeath msg;
	MapDisplayObject * monObj = MapManager::Instance()->getMonster(bossId);
	msg.fromId_ = monObj->getEntityMsg();
	msg.bossCode_ = bossId;
	msg.deathType_=0;
	msg.freeRevive_=0;
	msg.fromName_ ="";
	msg.reviveCd_.push_back(reviveTime*1000LL);
	msg.reviveCd_.push_back(0);
	msg.reviveType_ = 0;
	LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_DEATH, &msg);
	return true;

}


bool CopyManager::sendImmortalRoadCopyInfo(uint32_t uid,uint32_t wave,map<uint32_t,uint32_t>& monsters){
	msgs::SImmortalRoadCopyInfo msg;
	msg.waveNum_ = wave;
	for(map<uint32_t,uint32_t>::iterator it =monsters.begin();it!=monsters.end();it++){
		msg.monsters_.insert(make_pair(it->first,it->second));
	}
	LogicManager::Instance()->SendMsg(uid, CMD_IMMORTAL_ROAD_COPY_INFO, &msg);
	return true;
}
