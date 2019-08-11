/*
 * PlayerSignDaliyManager.cpp
 *
 *  Created on: 2019年7月18日
 *      Author: colin
 */

#include "BattleInc.h"
#include "RewardManager.h"

RewardManager::RewardManager() {
}

int RewardManager::Process(uint32_t uid,
		logins::SPlayerSignEveryDayReq* req) {
	uint32_t type = req->flag_;
	DataReward& cache = CacheManager::Instance()->GetUser(uid).reward_;
	uint32_t index = cache.sign_num;
	const CfgSignRewards::signDaliyReward& rewardCfg =
			SignRewardsCfgWrap().GetRewardsByIndex(index);

	if (!Time::IsToday(cache.sign_ts)) {
		cache.today_is_sign = 0;
	}

	uint32_t multiple = 1;
	if (ePlayerDaliyCommon == type) //免费签到
			{
		if (cache.today_is_sign == 1) {
			error_log("already signed: %u", uid);
			return R_ERROR;
		}

		cache.today_is_sign = 1;
	} else if (ePlayerDaliyRetroaction == type) //补签
			{
		if (cache.free_count == 0) {
			error_log("sign, free count is 0: %u", uid);
			return R_ERROR;
		}

		UpdateManager::Instance()->SetCode(UC_EveryDaySignReward);
		if (!UserManager::Instance()->UseMoney(uid, MONEY_GOLD,
				RETROACTION_GOLD_COUNT, "retroact sign cost")) {
			error_log("retroact sign cost error uid=%u", uid);
			return R_ERROR;
		}
		cache.free_count--;
	} else //vip
	{
		multiple = rewardCfg.times();
		multiple = multiple == 0 ? 1 : multiple;
	}

	UpdateManager::Instance()->SetCode(UC_EveryDaySignReward);

	Award signReward;
	signReward.Add(rewardCfg.item(), rewardCfg.count() * multiple);
	UserManager::Instance()->Reward(uid, signReward, "sign free reward");

	cache.sign_num++;
	DataSignManager::Instance()->Set(cache);
	LogicManager::Instance()->AddSync(CMD_PLAYER_SIGNEVERYDAY);

	return R_SUCCESS;
}

int RewardManager::Process(uint32_t uid,
		logins::SGetSignEverydayRwardReq* req) {
	uint32_t day = req->day_;
	DataReward& cache = CacheManager::Instance()->GetUser(uid).reward_;
	uint32_t dayIndex = day / GET_TARGET_REWARD_GAP;
	if (dayIndex >= TARGET_GOTS_SIZE) {
		error_log("get sign target reward, day is invalid: uid=%u, day=%u", uid,
				day);
		return R_ERROR;
	}

	if (cache.target_gots[dayIndex] != 0) {
		error_log("get sign target reward, already got: uid=%u, day=%u", uid,
				day);
		return R_ERROR;
	}

	uint32_t cfgIndex = (cache.sign_num / 30) * 30 + day - 1;
	const CfgSignRewards::signDaliyReward& rewardCfg =
			SignRewardsCfgWrap().GetRewardsByIndex(cfgIndex);
	if (rewardCfg.extra_item() == 0) {
		error_log("get sign target reward, reward not exist: uid=%u, day=%u",
				uid, day);
		return R_ERROR;
	}

	Award targetReward;
	targetReward.Add(rewardCfg.extra_item(), 1);
	UserManager::Instance()->Reward(uid, targetReward, "get signreward");

	UpdateManager::Instance()->SetCode(UC_EveryDaySignTargetReward);
	LogicManager::Instance()->AddSync(CMD_PLAYER_SIGNEVERYDAY);

	cache.target_gots[dayIndex] = (char) day;

	return R_SUCCESS;
}

int RewardManager::Process(uint32_t uid, logins::SGetLevelRwardReq* req) {
	uint32_t level = req->level;
	uint32_t careerLevel = req->careerLevel;

	try {
		const CfgSignRewards::levelTargetRewards& cfg =
				LevelRewardsCfgWrap().GetRewardByLevel(careerLevel, level);
		int32_t index =
				ConfigManager::Instance()->level_reward_index[careerLevel][level];
		DataReward& reward = CacheManager::Instance()->GetUser(uid).reward_;
		if (reward.level_rewards_flags[index] != eStatusOwn) {
			error_log("get level reward: uid=%u, code=level invalid", uid);
			return R_ERROR;
		}

		if (!LevelRewardRecordManager::Instance()->exist(careerLevel, level)) {
			LevelRewardRecordManager::Instance()->Add(careerLevel, level,
					(cfg.limit_count() == 0 ? -1 : cfg.limit_count()));
		}

		int32_t left_count = LevelRewardRecordManager::Instance()->GetCount(
				careerLevel, level);
		if (left_count > 0) {
			Award targetReward;
			targetReward.Add(cfg.gift_id(), 1);
			UserManager::Instance()->Reward(uid, targetReward,
					"get levelreward");

			UpdateManager::Instance()->SetCode(UC_LevelReward);
			left_count--;

			reward.level_rewards_flags[index] = eStatusGot;
			DataSignManager::Instance()->Set(reward);

		}

	} catch (exception& e) {
		error_log("get level reward: uid=%u, code=%s", uid, e.what());
		return R_ERROR;
	}

	return R_SUCCESS;
}

int RewardManager::Sync(const UserCache &cache, uint32_t cmd,
		msgs::SPlayerSignEveryDay *resp) {
	resp->freeCount_ = cache.reward_.free_count;
	resp->signNum_ = cache.reward_.sign_num;
	resp->todayIsSign_ = cache.reward_.today_is_sign;

	resp->targetGots_.reserve(TARGET_GOTS_SIZE);
	for (uint32_t i = 0; i < TARGET_GOTS_SIZE; ++i) {
		resp->targetGots_[i] = cache.reward_.target_gots[i];
	}

	if (!LogicManager::Instance()->SendMsg(cache.uid_, cmd, resp)) {
		return R_ERROR;
	}
	return true;
}

int RewardManager::Sync(const UserCache &cache, uint32_t cmd,
		msgs::SPlayerLevelReward *resp) {
	uint32_t index = 0;
	uint32_t career = 0;
	uint32_t level = 0;

	const ReinCarnInfo& carn = cache.m_reinCarnInfo;
	const DataBase& base = cache.base_;

	const CfgSignRewards::LevelRewards& cfg =
			ConfigManager::Instance()->level_rewards_cfg_.m_config;
	DataReward& reward = CacheManager::Instance()->GetUser(cache.uid_).reward_;
	for (int i = 0; i < cfg.levelreward_size(); ++i) {
		career = cfg.levelreward(i).career_level();
		level = cfg.levelreward(i).level();
		index = ConfigManager::Instance()->level_reward_index[career][level];
		char& status = reward.level_rewards_flags[index];
		if (status == eStatusOwn || status == eStatusGot)
			continue;
		if (status == eStatusEmpty) {
			if (carn.reinCarnLevel >= career && base.level >= level)
				status = eStatusOwn;
		}

		if (status == eStatusOwn || status == eStatusGot) {
			resp->rewardDict_.insert(make_pair(career * 10000 + level, status));
		}

	}

	LevelRewardRecordManager::Instance()->Get(resp->numDict_);

	return R_SUCCESS;
}
