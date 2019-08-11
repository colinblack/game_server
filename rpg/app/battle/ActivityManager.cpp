/*	ActivityManager.cpp
 *
 * 	2019.07.15
 *
 *  auto: next
 */

#include "ActivityManager.h"
#include "BattleInc.h"

enum Active_level {
	ACTIVE_DAY_1 = 1,
	ACTIVE_DAY_2 = 2,
	ACTIVE_DAY_3 = 3,
	ACTIVE_DAY_4 = 4,
	ACTIVE_WEEK_5 = 5,
};

ActivityManager::ActivityManager() {
}

bool ActivityManager::addActInfo(uint32_t uid, uint32_t id) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);

	//新增 act_info 数据
	DataActivity data;
	data.init(uid, TYPE_ATTR_ACTIVITY_INFO, id);
	cache.act_info_.insert(make_pair(data.id, data));
	DataAttr attr;
	memcpy((void*)&attr, (const void*)&data, sizeof(data));
	DataAttrManager::Instance()->Add(attr);
	return true;
}

bool ActivityManager::addActCnt(uint32_t uid, uint32_t id) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);

	//新增 act_cnt 数据
	DataActivity data;
	data.init(uid, TYPE_ATTR_ACT_CNT, id);
	cache.act_cnt_.insert(make_pair(data.id, data));
	DataAttr attr;
	memcpy((void*)&attr, (const void*)&data, sizeof(data));
	DataAttrManager::Instance()->Add(attr);
	return true;
}

bool ActivityManager::ReflashActive(uint32_t uid) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if(0 == cache.m_active_.ts) {
		cache.m_active_.ts = Time::GetGlobalTime();
	}

	if(CTime::IsDiffDay(cache.m_active_.ts, Time::GetGlobalTime())) {
		cache.m_active_.ts = Time::GetGlobalTime();
		cache.m_active_.day_active = 0;
		//每日活跃领奖标志位重置
		cache.m_active_.reward[0] = false;
		cache.m_active_.reward[1] = false;
		cache.m_active_.reward[2] = false;
		cache.m_active_.reward[3] = false;

		map<uint32_t, DataActivity>::iterator it = cache.act_info_.begin();
		for(; it != cache.act_info_.end(); ++it) {
			it->second.cnt = 0;
			DataAttr attr;
			memcpy((void*)&attr, (const void*)&(it->second), sizeof(it->second));
			DataAttrManager::Instance()->Set(attr);
		}
		it = cache.act_cnt_.begin();
		for(; it != cache.act_cnt_.end(); ++it) {
			it->second.cnt = 0;
			DataAttr attr;
			memcpy((void*)&attr, (const void*)&(it->second), sizeof(it->second));
			DataAttrManager::Instance()->Set(attr);
		}

	}
	if(CTime::IsDiffWeek(cache.m_active_.ts, Time::GetGlobalTime())) {
		cache.m_active_.ts = Time::GetGlobalTime();
		cache.m_active_.week_active = 0;
		cache.m_active_.reward[4] = false;
	}
	DataActiveManager::Instance()->Set(*((DataActive*)&cache.m_active_));

	return true;
}

bool ActivityManager::SyncActivity(UserCache& cache, uint32_t actId, uint32_t num) {
	if(0 == cache.act_cnt_.count(actId)) {
		addActCnt(cache.uid_, actId);
	}

	DataActivity& act_cnt = cache.act_cnt_[actId];
	const CfgActivity::DaliyAct& act_cfg = ActivityCfgWrap().GetAct(actId);
	if((act_cnt.cnt + num) > act_cfg.count()) {
		error_log("act count:%d already complete", act_cfg.count());
		return false;
	}
	act_cnt.cnt += num;
	DataAttr attr;
	memcpy((void*)&attr, (const void*)&act_cnt, sizeof(act_cnt));
	DataAttrManager::Instance()->Set(attr);
	return true;
}

bool ActivityManager::ActorLogin(uint32_t uid) {
	return ReflashActive(uid);
}

bool ActivityManager::onHour(uint32_t lastHour) {
	if(lastHour != 0) {
		return false;
	}
	vector<uint32_t> uids;
	CacheManager::Instance()->GetAllUser(uids);
	for(uint32_t i=0;i<uids.size();i++){
		UserCache &cache = CacheManager::Instance()->GetUser(uids[i]);
		if(!cache.init_) {
			return false;
		}
		ReflashActive(cache.uid_);
	}
	return true;
}

int ActivityManager::Process(uint32_t uid, logins::SGetActivityReq *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	//刷新每日、周活动数据
	ReflashActive(uid);

	if(!ActivityCfgWrap().isActExist(req->id_)) {
		error_log("act_cfg id:%d is not exist", req->id_);
		return R_ERROR;
	}
	if(0 == cache.act_info_.count(req->id_)) {
		addActInfo(uid, req->id_);
	}

	DataActivity& act = cache.act_info_[req->id_];
	if(0 == cache.act_cnt_.count(req->id_) ||
			(req->count_ + act.cnt) != cache.act_cnt_[req->id_].cnt) {
		error_log("act_cnt data error");
		return R_ERROR;
	}

	const CfgActivity::DaliyAct& act_cfg = ActivityCfgWrap().GetAct(req->id_);

	if((req->count_ + act.cnt) > act_cfg.count()) {
		error_log("act count:%d already complete", act_cfg.count());
		return R_ERROR;
	}
	act.cnt += req->count_;
	DataAttr attr;
	memcpy((void*)&attr, (const void*)&act, sizeof(act));
	DataAttrManager::Instance()->Set(attr);

	DataActiveEtr& active = cache.m_active_;
	active.day_active += (act_cfg.activity() * req->count_);
	active.week_active += (act_cfg.activity() * req->count_);

	if (active.uid == 0) {
		active.uid = uid;
		DataActiveManager::Instance()->Add(*((DataActive*)&active));
	} else {
		DataActiveManager::Instance()->Set(*((DataActive*)&active));
	}

	LogicManager::Instance()->AddSync(CMD_DAILY_ACTIVITY_INFO);

	return R_SUCCESS;
}

int ActivityManager::Process(uint32_t uid, logins::SGetActivityRewardReq *req) {
	UserCache& cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return false;
	}
	uint32_t limit = ActivityCfgWrap().GetActiveLimit(req->id_, cache.m_reinCarnInfo.reinCarnLevel);

	if(!ActivityCfgWrap().isActiveExit(limit, cache.m_reinCarnInfo.reinCarnLevel)) {
		error_log("active id:%d is not exist", req->id_);
		return R_ERROR;
	}
	const CfgActivity::Active& active_cfg = ActivityCfgWrap().GetActive(limit, cache.m_reinCarnInfo.reinCarnLevel);
	if(cache.m_active_.day_active < limit && req->id_ != ACTIVE_WEEK_5) {
		error_log("day_active:%d is not enough", cache.m_active_.day_active);
		return R_ERROR;
	} else if (cache.m_active_.day_active < limit && req->id_ == ACTIVE_WEEK_5) {
		error_log("day_active:%d is not enough", cache.m_active_.day_active);
		return R_ERROR;
	}
	DataActiveEtr& data = cache.m_active_;
	data.reward[req->id_ - 1] = true;
	DataActiveManager::Instance()->Set(*((DataActive*)&data));

	UpdateManager::Instance()->SetCode(UC_DailyActivityReward);
	Award ActiveRward;
	ActiveRward.Format(active_cfg.reward(), 1);
	UserManager::Instance()->Reward(uid, ActiveRward, "active reward");

	LogicManager::Instance()->AddSync(CMD_DAILY_ACTIVITY_INFO);

	return R_SUCCESS;
}

int ActivityManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SDailyActivityInfo *resp) {
	resp->activity_ = cache.m_active_.day_active;
	resp->levelLimit_ = 1;
	resp->carrerLevelLimit_ = 0;
	const DataActiveEtr& data = cache.m_active_;
	for(uint32_t i = 0; i < ACTIVE_REWARD_SIZE; ++i) {
		if(true == data.reward[i]) {
			resp->hadGetRewards_.insert(make_pair(i+1, data.reward[i]));
		}
	}

	map<uint32_t, DataActivity>::const_iterator it = cache.act_info_.begin();
	for(;it != cache.act_info_.end(); ++it) {
		if(it->second.cnt != 0) {

			resp->getActivity_.insert(make_pair(it->second.id, it->second.cnt));
		}
	}

	map<uint32_t, DataActivity>::const_iterator item = cache.act_cnt_.begin();
	for(;item != cache.act_cnt_.end(); ++item) {
		if(item->second.cnt != 0) {
			resp->getActCnt_.insert(make_pair(item->second.id, item->second.cnt));
		}
	}

	resp->weekActivity_ = cache.m_active_.week_active;
	resp->weekLevelLimit_ = 1;
	resp->weekCarrerLevelLimit_ = 0;

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return true;
}
