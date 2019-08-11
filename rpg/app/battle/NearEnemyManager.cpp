/*
 * NearEnemyManager.cpp
 *
 *  Created on: 2019年7月31日
 *      Author: colin
 */

#include "BattleInc.h"

map<uint32_t, NearEnemyData> NearEnemyManager::m_data;

NearEnemyManager::NearEnemyManager(){
}


NearEnemyManager::~NearEnemyManager(){
}

bool NearEnemyManager::Init(){

	return true;
}


int NearEnemyManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SNearEnemyInfo *resp)
{
	uint32_t uid = cache.uid_;

	for(set<uint32_t>::iterator it = m_enemys[uid].begin(); it != m_enemys[uid].end(); ++it){
		uint32_t enemyUid = *it;
		UserCache &enemyCache = CacheManager::Instance()->GetUser(enemyUid);

		msgs::SNearEnemy msg;
		msg.career_ = enemyCache.base_.main_role;
		msg.level_  = enemyCache.base_.level;
		msg.career_level_ = enemyCache.m_reinCarnInfo.reinCarnLevel;
		msg.playerId_ = enemyCache.base_.uid;
		msg.name_   = enemyCache.base_.open_id;
		resp->enemys_.push_back(msg);
	}


	NearEnemyData& data = m_data[uid];
	resp->zhangong_ = (int32_t)data.zhangong;
	resp->shalu_ 	= (int32_t)data.shalu;
	resp->totalKill_ = (int32_t)data.total_kill;

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
			return R_ERROR;
	}


	return R_SUCCESS;
}

bool NearEnemyManager::Recover(Human *pHuman){
	if(!MapManager::Instance()->addObject(pHuman)){
		return false;
	}

	return true;
}


int NearEnemyManager::Process(uint32_t uid, logins::SNearenmeyFightenemyReq *req){
	if(m_data[uid].shalu > SHALU_LIMIT){
		error_log("shalu_over_limit, uid=%u", uid);
		return R_ERROR;
	}

	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return R_ERR_NO_DATA;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}

	m_old_points[uid] = req->oldPoints;

	HangCfgWrap hangCfgWrap;
	MonsterCfgWrap monsterCfgWarp;

	const CfgHang::Plan &plan = hangCfgWrap.GetPlan(cache.base_.hang);

	Map *pMap = MapManager::Instance()->getMapInstance(0, plan.mapid());
	if (pMap == NULL) {
		error_log("get map error mid=%u", plan.mapid());
		return R_ERROR;
	}

	const CfgHang::Hang &hang = hangCfgWrap.Get(cache.base_.hang);
	const CfgMonster::Plan &monster_plan = monsterCfgWarp.GetPlan(hang.plan());
	const CfgMap::Point &point = SceneCfgWrap().GetBossPoint(monster_plan.mapid(), monster_plan.plan());

	Point bpos;
	bpos.x = point.x() * pMap->getGridWidth() + pMap->getGridWidth() / 2;
	bpos.y = point.y() * pMap->getGridHeight() + pMap->getGridHeight() / 2;

	NearEnemy* boss = new NearEnemy();

	UserCache enemyCache = CacheManager::Instance()->GetUser(req->playerId);


	WWMParser* pWwm = WWMParser::getInstance(MapManager::Instance()->getwwmFile(plan.mapid()));
	if (pWwm == NULL) {
		error_log("may be invalid mapid:%d", plan.mapid());
		return R_ERROR;
	}

	boss->init(enemyCache, enemyCache.base_.main_role, 0, plan.mapid(), bpos);
	boss->setBelong(uid);
	boss->setNeedRecove(false);
	boss->setForce(FORCE_HOSTILE);
	boss->setCanMove(true);
//	boss->setmaxRadius(100);
//	boss->setRadius(100);


	Point p;
	p.x = abs(point.x() * pMap->getGridWidth() - 5 * pMap->getGridWidth()); //玩家坐标暂时设置成这样
	p.y = abs(point.y() * pMap->getGridHeight() - 10 * pMap->getGridHeight());

	pHuman->setPos(p.x, p.y);
	if (!boss->recove()) {
		delete boss;
		return R_ERROR;
	}
	ZhanLingManager::Instance()->resetNuQi(uid);


	msgs::SHangResetPoint msg;
	msg.hang_ = 0; //cache.base_.hang;
	msg.toPoints_.push_back(p);

	LogicManager::Instance()->SendMsg(uid, CMD_HANG_RESETPOINT, &msg);


	msgs::SPlayerFighting msg1;
	msg1.isFighting_ = true;
	msg1.isPvpFighting_ = false;
	LogicManager::Instance()->SendMsg(uid, CMD_PLAYER_UPDATE_FIGHTING , &msg1);

	m_boss[uid] = enemyCache.uid_;
	return R_SUCCESS;

}


int NearEnemyManager::Process(uint32_t uid, logins::SNearenemyBacktoHangReq *req){
	msgs::SHangResetPoint msgReset;
	msgReset.hang_ = 1; //cache.base_.hang;
	msgReset.toPoints_ = m_old_points[uid];
	LogicManager::Instance()->SendMsg(uid, CMD_HANG_RESETPOINT, &msgReset);

	return R_SUCCESS;
}



bool NearEnemyManager::OnMonsterDie(uint32_t uid, uint32_t monster_id, const Point &diePos){
	map<uint32_t, uint32_t>::iterator itr = m_boss.find(uid);
	if (itr == m_boss.end()) {
		return false;
	}

	if (itr->second != monster_id) {
		return false;
	}


	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}

	msgs::SNearEnemyResult msg;
	msg.succ_ = 1;
	msg.hangLevel_ = cache.base_.hang;
	msg.enemyId_ = m_boss[uid];
	uint32_t id = 10000 + cache.m_reinCarnInfo.reinCarnLevel;
	MonsterDrop(uid, id, msg.rewards_);

	LogicManager::Instance()->SendMsg(uid, CMD_NEARENEMY_RESULT, &msg);

	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman != NULL) {
		pHuman->doRecover();
	}

	NearEnemyData& data = m_data[uid];
	data.total_kill += 1;
	data.zhangong = ZhanGong(data.total_kill);
	data.shalu += SHALU_CONST;
	//玩家返回原挂机点
	pHuman->setPos(m_old_points[uid].begin()->x, m_old_points[uid].begin()->y);

	//更新击杀排名
	if (m_kill_rank.count(uid) > 0) {
		m_kill_rank.erase(uid);
		m_kill_rank.insert(uid);
	} else {
		if (m_kill_rank.size() >= RANK_LIMIT) {
			uint32_t key = *(m_kill_rank.rbegin());
			if (data.total_kill > m_data.at(key).total_kill) {
				m_kill_rank.erase(key);
				m_kill_rank.insert(uid);
			}

		} else {
			m_kill_rank.insert(uid);
		}

	}

	m_enemys[uid].erase(m_boss[uid]);

	LogicManager::Instance()->AddSync(CMD_NEARENEMY_INFO);
	m_boss.erase(uid);

	return true;
}


bool NearEnemyManager::OnHumanDie(uint32_t uid){
	map<uint32_t, uint32_t>::iterator itr = m_boss.find(uid);
	if (itr == m_boss.end()) {
		return false;
	}
	m_boss.erase(uid);

	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if(!cache.init_) {
		return false;
	}

	msgs::SNearEnemyResult msg;
	msg.succ_ = 0;
	msg.hangLevel_ = cache.base_.hang;
	msg.enemyId_ = m_boss[uid];

	LogicManager::Instance()->SendMsg(uid, CMD_NEARENEMY_RESULT, &msg);


	Human *pHuman = MapManager::Instance()->getHuman(uid);
	pHuman->setPos(m_old_points[uid].begin()->x, m_old_points[uid].begin()->y);


	return true;
}

void NearEnemyManager::GenEnemyList(uint32_t uid, uint32_t cnt, vector<uint32_t>& enemys) {
	//过滤掉0和自己的uid
	if(enemys.size() <= 2)
		return;

	if(m_enemys[uid].size() == ENEMY_SIZE)
		return;

	random_shuffle(enemys.begin(), enemys.end());
	vector<uint32_t>::iterator pre = enemys.begin();
	vector<uint32_t>::iterator tail = enemys.end();

	for(; pre != tail;){
		if(*pre == uid || *pre == 0){
			std::swap(*pre, *(--tail));
		} else{
			if(m_enemys[uid].count(*pre) == 0)
				m_enemys[uid].insert(*pre);
			++pre;
		}
	}

	LogicManager::Instance()->AddSync(CMD_NEARENEMY_INFO);
}

bool NearEnemyManager::MonsterDrop(uint32_t uid, uint32_t id, vector<msgs::SItemAmount>& rewards){
	try{
		UserCache &cache = CacheManager::Instance()->GetUser(uid);
		if (!cache.init_) {
			return false;
		}
		const CfgItem::Drop &drop_cfg = ItemCfgWrap().GetDrop(id);
		Award reward;
		reward.Random(drop_cfg.randomreward(), drop_cfg.randomcount());
		reward.Get(rewards);

		if (!reward.Format(drop_cfg.fixedreward(), 1)) {
			error_log("parse reward error");
			return false;
		}

		msgs::SItemAmount msg_item;
		for (int i = 0; i < drop_cfg.fixedreward_size(); ++i) {
			msg_item.itemCode_ = drop_cfg.fixedreward(i).item();
			msg_item.itemNum_ = drop_cfg.fixedreward(i).num();
			rewards.push_back(msg_item);
		}

		string code;
		String::Format(code, "near_enemy_%u", id);
		if (!UserManager::Instance()->Reward(uid, reward, code)) {
			return false;
		}
	}
	catch(const exception& e){
		error_log("drop error: %s", e.what());
		return false;
	}

	return true;
}

int  NearEnemyManager::killEnemyRank(uint32_t uid, msgs::SToplist* resp){
	resp->toplistType_ = TypeNearEnemy;
	resp->version_     = Time::GetGlobalTime();
	dbs::TToplist list;

	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if(pHuman == NULL){
		error_log("phuman_is_null, uid=%u", uid);
		return R_ERROR;
	}

	list.entityId_ = pHuman->getEntityId();
	list.entityType_ = 1;
	list.property1_ = pHuman->getName();
	list.property2_ = "0";
	list.proxyId_  = LogicManager::ProxyId;
	set<uint32_t, Compare>::iterator it = m_kill_rank.find(uid);
	list.rank_ = it == m_kill_rank.end() ? 0 : std::distance(m_kill_rank.begin(), it) + 1;
	list.serverId_ = LogicManager::ServerId;
	list.toplistType_ = TypeNearEnemy;
	list.updateDt_  = Time::GetGlobalTime()*1000LL;
	list.value2_    = pHuman->getCombat();
	list.value_		= (int)m_data[uid].zhangong;
	list.version_   = Time::GetGlobalTime();
	resp->records_.push_back(list);

	return R_SUCCESS;
}


void NearEnemyManager::onSecondTimer() {
	try{
		static uint32_t cnt = 0;
		if (cnt++ % 60 == 0) {
			vector<uint32_t> enemys;
			CacheManager::Instance()->GetAllUser(enemys);

			vector<uint32_t> onlineUser;
			FdManager::Instance()->getAllUid(onlineUser);

			for (int i = 0; i < (int)onlineUser.size(); ++i) {
				uint32_t &shalu = m_data[onlineUser[i]].shalu;
				if(shalu > 0)
					shalu--;
				debug_log("onlineuser: %u", onlineUser[i]);
				GenEnemyList(onlineUser[i], ENEMY_SIZE, enemys);
			}
		}
	}
	catch(const exception& e)
	{
		error_log("ontime=%s", e.what());

	}
}
