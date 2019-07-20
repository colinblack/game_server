/*
 * CopyManager.cpp
 *
 *  Created on: 2019年6月27日
 *      Author: Administrator
 */

#include "BattleInc.h"
#include "CopyManager.h"

CopyManager::CopyManager() {
}

CopyManager::~CopyManager() {
}


int CopyManager::Process(uint32_t uid, boss::CSEnterReincarnCopy *req){
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
	vector<uint32_t> tmp ;
	tmp.push_back(pHuman->getMapId());
	tmp.push_back((uint32_t)req->copyCode);
	tmp.push_back(bossCfg.bossid());
	m_saveInfo.insert(make_pair(uid,tmp));

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
	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg2);

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

int CopyManager::Process(uint32_t uid, boss::CSEnterMagicTowerCopy *req){
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
	vector<uint32_t> tmp ;
	tmp.push_back(plancfg.mapid());
	tmp.push_back(MAGIC_TOWER_COPY);
	tmp.push_back(index-MAGIC_TOWER_BASE);
	m_saveInfo.insert(make_pair(uid,tmp));

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


int CopyManager::Process(uint32_t uid, boss::CSEnterMaterialCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
//	Human *pHuman = MapManager::Instance()->getHuman(uid);
//	if (pHuman == NULL) {
//		return R_ERR_NO_DATA;
//	}
//	CopyWrap copyCfgWrap;
//	SceneCfgWrap sceneCfgWrap;
//	BossWrap bossCfgWrap;
//	MonsterCfgWrap monsterCfgWarp;
//	const CfgCopy::Copy &copyCfg = copyCfgWrap.GetCopy(req->copyCode);
//	const CfgBoss::Boss &bossCfg = bossCfgWrap.GetBoss(req->copyCode);
//	const CfgMap::Scene &scenecfg = sceneCfgWrap.Get(copyCfg.mapid());
//	vector<uint32_t> tmp ;
//	tmp.push_back(pHuman->getMapId());
//	tmp.push_back((uint32_t)req->copyCode);
//	tmp.push_back(bossCfg.bossid());
//	m_saveInfo.insert(make_pair(uid,tmp));
//
//	Point bpos;
//	bpos.x =scenecfg.bosscenterpoints(0).point().x()*24+12;
//	bpos.y =scenecfg.bosscenterpoints(0).point().y()*24+12;
//
//	MapChangeInfo info;
//	info.desFbInstanceId = 0;
//	info.desMapId = copyCfg.mapid();;
//	info.desPoint.x = scenecfg.addenterpoint_x();
//	info.desPoint.y =  scenecfg.addenterpoint_y();
//	if(info.desPoint.x==0||info.desPoint.y==0){
//		info.desPoint.x = bpos.x;
//		info.desPoint.y = bpos.y;
//	}
//	DataBase &base = cache.base_;
//	if (!MapManager::Instance()->actorChangeMap(uid, base.role_num, info)) {
//		return false;
//	}
//
//	StdMonster *boss = new StdMonster();
//	boss->init(bossCfg.bossid(), 0, copyCfg.mapid(), bpos);
//
//	boss->setBelong(uid);
//	boss->setNeedRecove(false);
//	boss->setForce(FORCE_HOSTILE);
//	if (!boss->recove()) {
//		delete boss;
//		return R_ERROR;
//	}
//	MapManager::Instance()->enterMapSync();
//	msgs::SCopyTimeInfo msg;
//	msg.copyCode_ = req->copyCode;
//	msg.startDt_ = Time::GetGlobalTime()*1000LL;
//	msg.endDt_ =(copyCfg.duringtime()+ Time::GetGlobalTime())*1000LL;
//	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg);
//	msgs::SEnterReincarnCopy msg2;
//	msg2.copyCode_ = req->copyCode;
//	LogicManager::Instance()->SendMsg(uid, CMD_COPY_TIME_INFO, &msg2);
//
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

int CopyManager::Process(uint32_t uid, boss::CSLeaveCopy *req){
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	map<uint32_t,vector<uint32_t> >::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		logins::SBackToCity *req=NULL;
		MapManager::Instance()->Process(uid,req);
		return 0;
	}
	if(it->second.size()<3){
		return R_ERR_NO_DATA;
	}

	if(it->second[0]==DEFAULT_MAP_ID){
		logins::SBackToCity *req=NULL;
		MapManager::Instance()->Process(uid,req);
	}else{
		logins::SEnterHang *req=NULL;
		MapManager::Instance()->Process(uid,req);
	}
	m_saveInfo.erase(it);

	return 0;
}

int CopyManager::Process(uint32_t uid, boss::CSQuickFinish *req){
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


int CopyManager::Process(uint32_t uid, boss::CSGotReward *req){
	//CMD_RPC_COPY_GOTREINCARNREWARDS
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


void CopyManager::onHour(uint32_t hour){




	return;
}


bool CopyManager::OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}

	map<uint32_t,vector<uint32_t> >::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return R_ERR_NO_DATA;
	}
	if(it->second.size()<3){
		return R_ERR_NO_DATA;
	}

	map<uint32_t, CopyInfo>::iterator itc = cache.m_copyInfo.find(it->second[1]);
	if(itc==cache.m_copyInfo.end()){
		return R_ERR_NO_DATA;
	}else{
		if(it->second[1]==MAGIC_TOWER_COPY){
			itc->second.data++;
			itc->second.totalCompleteNum++;
			itc->second.totalEnterDay++;
			itc->second.totalEnterNum++;
		}else if(itc->second.data==0){
			itc->second.data=1;
			itc->second.completeNum ++;
			itc->second.totalCompleteNum ++;
		}
		ATTR_DB_SET(itc->second);
	}
	sendUpdate(cache,it->second[1]);

	//发奖
	if(it->second[1]==MAGIC_TOWER_COPY){
		const CfgMagic::MagicTower &tower_cfg = MagicTowerWrap().GetMagicTower(it->second[2]);

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
		msg.layer_ = it->second[2];
		msg.isQuick_ =false;
		msg.isDoubleExp_ =false;
		msg.failed_ = false;
		msg.costCount_ =0;
		msg.copyCode_ = it->second[1];
		for(uint32_t i=0;i<v.size();i++){
			msg.rewards_.insert(make_pair(v[i].itemCode_,v[i].itemNum_));
		}
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_MAGIC_TOWER_COPY, &msg);
		LogicManager::Instance()->AddSync(CMD_MAGIC_INFO);

	}else{
		try{
			const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(monster_id);
			Award reward;
			reward.Random(drop_cfg.randomreward(), drop_cfg.randomcount());
			if (!reward.Format(drop_cfg.fixedreward(), 1)) {
				error_log("parse reward error");
				return false;
			}
			MonsterDrop(uid,it->second[2],diePos);
			vector<msgs::SItemAmount> v;
			reward.Get(v);
			msgs::SCompleteReincarnCopy msg;
			msg.failed_ = false;
			msg.costCount_ =0;
			msg.copyCode_ = it->second[1];
			for(uint32_t i=0;i<v.size();i++){
				msg.rewards_.insert(make_pair(v[i].itemCode_,v[i].itemNum_));
			}
			LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_REINCARN_COPY, &msg);
		}catch(...){
			return false;
		}

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


bool CopyManager::MonsterDrop(uint32_t uid, uint32_t monster_id, const Point &diePos) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return false;
	}
	try {
		const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(monster_id);

		Award reward;
		reward.Random(drop_cfg.randomreward(), drop_cfg.randomcount());
		msgs::SPlayerAutoDrop msg;
		msg.belongEntityId_ = pHuman->getEntityMsg();
		msg.dropPoint_.x = diePos.x;
		msg.dropPoint_.y = diePos.y;
		msg.type_ = 0;
		reward.Get(msg.items_);
		if (!reward.Format(drop_cfg.fixedreward(), 1)) {
			error_log("parse reward error");
			return false;
		}
		msgs::SItemAmount msg_item;
		for (int i = 0; i < drop_cfg.fixedreward_size(); ++i) {
			msg_item.itemCode_ = drop_cfg.fixedreward(i).item();
			msg_item.itemNum_ = drop_cfg.fixedreward(i).num();
			msg.items_.push_back(msg_item);
		}
		UpdateManager::Instance()->SetCode(UC_AddDrop);
		string code;
		String::Format(code, "reincarn_boss_%u", monster_id);
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
	map<uint32_t,vector<uint32_t> >::iterator it =  m_saveInfo.find(uid);
	if(it==m_saveInfo.end()){
		return R_ERR_NO_DATA;
	}
	if(it->second.size()<3){
		return R_ERR_NO_DATA;
	}
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}

	if(it->second[1]==MAGIC_TOWER_COPY){
		msgs::SCompleteMagicTowerCopy msg;
		msg.completeTime_ = Time::GetGlobalTime();
		msg.layer_ = it->second[2];
		msg.isQuick_ =false;
		msg.isDoubleExp_ =false;
		msg.failed_ = true;
		msg.costCount_ =0;
		msg.copyCode_ = it->second[1];
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_MAGIC_TOWER_COPY, &msg);

	}else {
		msgs::SCompleteReincarnCopy msg;
		msg.failed_ = true;
		msg.costCount_ =0;
		msg.copyCode_ = it->second[1];
		LogicManager::Instance()->SendMsg(uid, CMD_COMPLETE_REINCARN_COPY, &msg);
	}
	return true;
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
		tmp.totalCompleteNum_ = it->second.totalCompleteNum;
		tmp.enterTime_ = it->second.enterTime;
		tmp.getBackNum_ =0;
		tmp.assistNum_ =0;
		tmp.grabNum_=0;
		resp->copyDatas_.push_back(tmp);
	}
	LogicManager::Instance()->SendMsg(cache.uid_,CMD_PLAYER_COPY_DATA_LIST,resp);
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
	LogicManager::Instance()->SendMsg(cache.base_.uid, CMD_PLAYER_COPY_DATA_UPDATE, &resp);
	return true;
}


