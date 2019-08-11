/*
 * OnlineReward.cpp
 *
 *  Created on: 2019年7月25日
 *      Author: memory
 */

#include "OnlineRewardManager.h"

#include "BattleInc.h"

OnlineRewardManager::OnlineRewardManager() {
}

OnlineRewardManager::~OnlineRewardManager() {
}

// 是否需要重置跨天时间戳
bool OnlineRewardManager::DailyReset(UserCache &cache) {
	if (cache.base_.uid == 0) {
		error_log("uid is not exist uid=%u ", cache.uid_);
		return false;
	}
	DataBase &data = cache.base_;
	// 获取时间间隔，判断是不是同一天
	if (CTime::GetDayInterval(data.ts, Time::GetGlobalTime()) == 0) {
		return false;
	}
	// 不是同一天，就把当前时间戳记录下来
	data.ts = Time::GetGlobalTime();
	data.online_time = 0;
	return true;
}

// 消息处理 4071
int OnlineRewardManager::Process(uint32_t uid, logins::COnlineRewardReq *req) {
	UserCache &cache = CacheManager::Instance()->GetUser(uid);
	if (!cache.init_) {
		return R_ERROR;
	}
	uint32_t onlineTime = req->onlineTime_; // 秒
	uint32_t itemId = 1;// 通过时间获取id
	uint32_t itemCnt = 1;

	uint32_t onlineRewardId = 0;

	// 发奖 通过时间从配置中获取itemId
	map<uint32_t, uint32_t>::iterator itr = ConfigManager::Instance()->online_reward_cfg_Index.begin();
	for (; itr != ConfigManager::Instance()->online_reward_cfg_Index.end(); ++itr) {
		const CfgOnlineReward::OnlineReward&cfg = OnlineRewardCfgWrap().Get(itr->first);
		uint32_t currentDay = CTime::GetDayInterval(cache.base_.register_time, Time::GetGlobalTime()) +1;
		if(cfg.onlinetime() == onlineTime && currentDay == cfg.registeredday()){
			onlineRewardId = cfg.id();
			itemId = cfg.reward(0).item();
			itemCnt = cfg.reward(0).num();
			break;
		}
	}
	if(itr==ConfigManager::Instance()->online_reward_cfg_Index.end()){
		error_log("not find cfg onlineTime =%d, currentDay=%d",req->onlineTime_, CTime::GetDayInterval(cache.base_.register_time, Time::GetGlobalTime()) +1);
		return R_ERROR;
	}
	// 没发奖就发
	if(cache.user_onlineReward_.count(onlineRewardId) == 0) {
		UserManager::Instance()->AddItem(uid, itemId, itemCnt, "OnlineReward"); // 发道具
		DataOnlineReward onlineReward;
		onlineReward.init(uid,TYPE_ATTR_ONLINT_REWARD,onlineRewardId,1);
		cache.user_onlineReward_.insert(make_pair(onlineRewardId, onlineReward));
		// 向数据库存储数据 已发奖的时间
		ATTR_DB_ADD(onlineReward);
	}
	else{
		DataOnlineReward &onlineReward  = cache.user_onlineReward_[onlineRewardId];
		onlineReward.hasGotReward = true;
		ATTR_DB_SET(onlineReward);
	}

	// 更新消息  4072 - 1568 推送 onlineTime  和 hasGotReward的map
	LogicManager::Instance()->AddSync(CMD_PLAYER_ONLINE_REWARD);
	return 0;
}

// 服务器主动推送的消息  s2c:更新消息 4072 - 1568 上线的时候推送当前在线时长
int OnlineRewardManager::Sync(const UserCache &cache, uint32_t cmd, msgs::SPlayerOnlineReward *resp) {
	// 遍历下数据库 从中获取玩家所有在在线奖励集合
	map<uint32_t, DataOnlineReward>::const_iterator itr = cache.user_onlineReward_.begin();
	uint32_t userOnlineTime = CacheManager::Instance()->GetUserOnlineTime(cache.uid_);
	resp->onlineTime_ =userOnlineTime;
	for (; itr != cache.user_onlineReward_.end(); ++itr) {
		if(itr->second.hasGotReward ){
			// 通过id从配置中获取时间
			const CfgOnlineReward::OnlineReward&cfg = OnlineRewardCfgWrap().Get(itr->first);
			uint32_t currentDay = CTime::GetDayInterval(cache.base_.register_time, Time::GetGlobalTime()) +1;
			if(currentDay  == cfg.registeredday()){
				uint32_t hasGotOnlineTime = cfg.onlinetime();
				resp->hasGotReward_.insert(make_pair(hasGotOnlineTime, itr->second.hasGotReward));
			}
		}
	}
	LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp);
	return 0;
}
