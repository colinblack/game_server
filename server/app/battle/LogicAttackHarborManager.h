#ifndef LOGIC_ATTACK_HARBOR_MANAGER_H
#define LOGIC_ATTACK_HARBOR_MANAGER_H

#include "ServerInc.h"

class LogicAttackHarborManager : public BattleSingleton, public CSingleton<LogicAttackHarborManager>
{
private:
	friend class CSingleton<LogicAttackHarborManager>;
	LogicAttackHarborManager():m_timer(0),m_isActive(false){};
	virtual ~LogicAttackHarborManager(){}

	enum
	{
		active_begin_open_day = 4, //开服第4天开启
		time_of_refresh_rank = 5, //刷新排行榜间隔
		active_time_of_hour = 19, //活动开启小时
		active_time_of_beginmin = 0,  //活动启动分钟
		active_time_of_endmin = 30,  //活动结束分钟
		ret_by_already_max, //到达最高等级
	};
public:
	struct CountryRank
	{
			uint8_t kingdom;   //国家
			unsigned kingdom_wreckage;   //国家残骸
			unsigned trump_uid;   //王牌uid
			unsigned trump_wreckage;  //王牌残骸

			CountryRank():
					kingdom(0),
					kingdom_wreckage(0),
					trump_uid(0),
					trump_wreckage(0)
			{
			}

			CountryRank(uint8_t k, unsigned kwreck, unsigned tuid, unsigned twreck):
				kingdom(k),
				kingdom_wreckage(kwreck),
				trump_uid(tuid),
				trump_wreckage(twreck)
			{
			}

			bool operator < (CountryRank & oth)
			{
				if (kingdom_wreckage < oth.kingdom_wreckage)
				{
					return true;
				}
				else if (kingdom_wreckage > oth.kingdom_wreckage)
				{
					return false;
				}
				else
				{
					//国家残骸相同，则比较王牌残骸
					if (trump_wreckage < oth.trump_wreckage)
					{
						return true;
					}
					else if (trump_wreckage > oth.trump_wreckage)
					{
						return false;
					}
					else
					{
						return false;
					}
				}
			}

			bool operator == (CountryRank & oth)
			{
				if (kingdom_wreckage == oth.kingdom_wreckage && trump_wreckage == oth.trump_wreckage)
				{
					return true;
				}

				return false;
			}
	};

	struct Record
	{
		unsigned rank;
		unsigned wreckage;
		unsigned reward;

		Record():
			rank(0),
			wreckage(0),
			reward(0)
		{

		}
	};

	virtual void CallDestroy() {Destroy();}
	int AttackHarborInit();

	void OnMinute();

	//增加残骸次数
	void AddTTT(unsigned uid, unsigned count);

	int Process(unsigned uid, ProtoAttackHarbor::OpenAttackWindowReq* msg, ProtoAttackHarbor::OpenAttackWindowResp* resp);

	int Process(unsigned uid, ProtoAttackHarbor::RecieveCountryRewardReq* msg, ProtoAttackHarbor::RecieveCountryRewardResp* resp);

private:
	int OpenWindow(unsigned uid, ProtoAttackHarbor::OpenAttackWindowResp *msg);

	//领取国家奖励
	int ReceiveCountryReward(unsigned uid, ProtoAttackHarbor::RecieveCountryRewardResp* msg);

	//活动开始
	void BeginAttackHarbor();

	bool IsReceiveReward(unsigned lastts);

	//计算国家排名
	int CalcuteCountryRank();

	//比较两个国家的残骸数量大小
	int CompareTwoCountry(uint8_t kingdomA, uint8_t kindomB);

	//活动结束
	int EndOfAttackHarbor();

	//发放个人奖励
	int ProvideRankReward();

	//发送全部杀敌人员的通知
	int SendRankNotify();

	//重置偷袭珍珠港记录
	int ResetAttachRecord();

	//刷新NPC
	int RefreshNPC();

	//销毁NPC
	int DestroyNPC();

	//刷新残骸排行榜
	int RefreshWreckageRank();

	//是否在副本时间内
	bool IsAttackActive(time_t ts);
private:
	unsigned m_timer;
	map<uint8_t, uint8_t> m_kingdom_rank;
	map<unsigned, Record> m_wreck_rank;  //残骸排行榜，uid->记录内容
	bool m_isActive;
	const static string m_wrecagerank;
	const static string killrankpath;
};

#endif //LOGIC_ATTACK_HARBOR_MANAGER_H
