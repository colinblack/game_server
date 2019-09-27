/*
 * InviteManager.h
 *
 *  Created on: 2016-6-8
 *      Author: Administrator
 */

#ifndef INVITEMANAGER_H_
#define INVITEMANAGER_H_

#include "ProtocolInc.h"
#include "DataInc.h"
#include "Award.h"
#include "ShareConfig.h"
#include "IManager.h"

struct ShareInfo
{
	uint32_t first;
	uint32_t dailyShareGift;
	uint32_t dailyShareTs;
	uint32_t inviteNum;
	vector<uint8_t> rewardNum;

	ShareInfo()
	{
		first = 0;
		dailyShareGift = 0;
		dailyShareTs = 0;
		inviteNum = 0;
	}

	void FromJson(const Json::Value &value)
	{
		Json::GetUInt(value, "f", first);
		Json::GetUInt(value, "dg", dailyShareGift);
		Json::GetUInt(value, "dt", dailyShareTs);
		Json::GetUInt(value, "in", inviteNum);
		if (value.isMember("irn") && value["irn"].isArray()) {
			for (size_t i = 0; i < value["irn"].size(); ++i) {
				rewardNum.push_back(value["irn"].get(i, 0).asUInt());
			}
		}
	}

	Json::Value ToJson()
	{
		Json::Value value;
		value["f"] = first;
		value["dg"] = dailyShareGift;
		value["dt"] = dailyShareTs;
		value["in"] = inviteNum;
		value["irn"] = Json::Value(Json::arrayValue);
		for (vector<uint8_t>::iterator itr = rewardNum.begin(); itr != rewardNum.end(); ++itr) {
			value["irn"].append(static_cast<uint32_t>(*itr));
		}
		return value;
	}
};

enum ShareType
{
	ShareTypeDaily = 1,			// 每日分享
	ShareTypeGateWin = 2,		// 闯关胜利分享
	ShareTypeGateLost = 3,		// 闯关失败分享
	ShareTypeAttackWin = 4,		// 掠夺胜利分享
	ShareTypeAttackLost = 5,	// 掠夺失败分享
	ShareTypeDailyR1 = 6,		// 分享补充金币
	ShareTypeDailyR2 = 7,		// 分享补充魔能
	ShareTypeDailyBullet = 8,	// 分享补充弹仓
	ShareTypeSoldierReborn = 9,	// 分享士兵觉醒
	ShareTypeMax
};

enum ShareRewardType
{
	ShareRewardFirst = 1,			// 首次分享奖励
	ShareRewardDaily = 2,			// 每日分享奖励
	ShareRewardGateWin = 3,			// 闯关胜利分享奖励
	ShareRewardGateLost = 4,		// 闯关失败分享奖励
	ShareRewardAttackWin = 5,		// 掠夺胜利分享奖励
	ShareRewardAttackLost = 6,		// 掠夺失败分享奖励
	ShareRewardInvite = 7,			// 邀请奖励分享奖励
	ShareRewardDailyR1 = 8,			// 补充金币分享奖励
	ShareRewardDailyR2 = 9,			// 补充魔能分享奖励
	ShareRewardDailyBullet = 10,	// 补充弹仓分享奖励
	ShareRewardSoldierReborn = 11,	// 士兵觉醒分享奖励
	ShareRewardMax
};

enum ShareDailyFlag
{
	ShareDailyFlagDoing = 0,
	ShareDailyFlagDone = 1
};

class Player;
class InviteManager : public IManager
{
public:
	InviteManager();
	virtual ~InviteManager();
	virtual bool doPacket(CNetPacket * packet);
	bool load(uint32_t uid);
	bool save(uint32_t uid);
	bool sendShareInfo();
	bool sendShareReward(uint32_t type, uint32_t r1, uint32_t r2);
	bool onGateOver(uint64_t battleId, int32_t level, int32_t r1, int32_t r2);
	bool doInviteSuccess(uint32_t uid);
	bool onLogin();
private:
	bool loadShareData(uint32_t uid);
	bool saveShareData();
	bool doShare(CNetPacket * packet);
	bool doAccept(CNetPacket * packet);
	bool doInviteAward(CNetPacket * packet);
	bool doShareDaily();
	bool rewardDaily();
	bool resetShare();
private:
	ShareInfo m_share;
};

#endif /* INVITEMANAGER_H_ */

