
/*
 * LogicHequActivity.h
 *
 *  Created on: 2014-07-17
 *      Author: Administrator
 */

#include "LogicHequActivity.h"


CLogicHequActivity::CLogicHequActivity() {
	// TODO Auto-generated constructor stub

}

CLogicHequActivity::~CLogicHequActivity() {
	// TODO Auto-generated destructor stub
}

CDataWorldAttack* CLogicHequActivity::GetHequWorldAttack()
{
	GET_MEM_DATA_SEM(CDataWorldAttack, HEQU_WORLD_ATTACK, sem_world_attack,false)
}

CDataAlliancePoint* CLogicHequActivity::GetHequAlliancePoing()
{
	GET_MEM_DATA_SEM(CDataAlliancePoint, HEQU_ALLIANCE_POINT, sem_alliance_point,false)
}

int CLogicHequActivity::GetHequAlliancePointRank(unsigned uid, vector <AlliancePoint> &vecPoints)
{
	CDataAlliancePoint *pdata= GetHequAlliancePoing();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_alliancepointrank_fail");
	}
	int ret = pdata->GetAlliancePointRankList(vecPoints);
	if(ret)
	{
		error_log("[get_alliancepointranktop10_fail] [uid=%u]",uid);
		return ret;
	}
	return 0;
}
int CLogicHequActivity::GetHequAlliancePointRankJson(unsigned uid, Json::Value &result)
{
	CDataAlliancePoint *pdata= GetHequAlliancePoing();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_alliancepointrank_fail");
	}

	vector <AlliancePoint> vecPoints;
	vecPoints.clear();
	int ret = GetHequAlliancePointRank(uid,vecPoints);
	if(ret != 0)
	{
		return ret;
	}

	//前十名积分
	for(int i = 0; i < vecPoints.size(); i++)
	{
		result[i]["alliance_id"] = vecPoints[i].alliance_id;
		result[i]["point"] = vecPoints[i].point;
		result[i]["name"] = string(vecPoints[i].name);
	}

	//发奖
	if((Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS))
	&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS) + 24*60*60))
	{
		vector <AlliancePoint> RewardPoints;
		RewardPoints.clear();
		pdata->RewardAlliancePointRankList(RewardPoints);
		if(RewardPoints.size() > 0)
		{
			for(int i = 0; i < 10; i++)
			{
				if(IsAllianceId(RewardPoints[i].alliance_id))
				{
					int leader_coins = 0;
					int member_coins = 0;
					int rs = 0;
					if(0 == i)
					{
						leader_coins = 1000;
						member_coins = 500;
						rs = 70000;
					}
					else if (i >=1 && i <=2)
					{
						leader_coins = 500;
						member_coins = 300;
						rs = 50000;

					}
					else if (i >=3 && i <=9)
					{
						leader_coins = 300;
						member_coins = 100;
						rs = 30000;
					}
					CLogicPay logicPay;
					CLogicAlliance alliance;
					//盟主奖励
					DataAlliance alliance_leader;
					alliance.GetAllianceLimit(RewardPoints[i].alliance_id,alliance_leader);
					ret = logicPay.ChangePay(alliance_leader.leader_uid, 0, leader_coins, "activity_hequ_alliancepoint_alliance_leader");
					if(ret)
					{
						error_log("[add_alliance_point_leader_reward_fail] [a_id=%u | uid=%u]",RewardPoints[i].alliance_id,alliance_leader.leader_uid);
						return R_ERROR;
					}

					//盟主奖励邮件
					string texT = "合区联盟贡献奖励已发放完毕（无需提取附件，系统已自动发放）,请查收！如有疑问，请联系GM";
					DataEmail email;
					CLogicEmail logicEmail;
					vector<uint64_t> toUidList;
					toUidList.push_back(alliance_leader.leader_uid);
					email.attach_flag = 0;
					email.attachments = "";
					email.uid = ADMIN_UID;
					email.post_ts = Time::GetGlobalTime();
					email.title = "合区联盟贡献活动奖励";
					email.text = texT;
					logicEmail.AddEmail(email,toUidList);
					info_log("[alliancepoint_reward] [a_id=%u | uid=%u | rank=%d]",RewardPoints[i].alliance_id,alliance_leader.leader_uid,i+1);

					//盟仓库资源奖励
					ret = alliance.ChangeResource(RewardPoints[i].alliance_id, rs, rs, rs, rs, 0, 0, "activity_hequ_alliancepoint");
					if(ret)
					{
						error_log("[add_alliance_point_resource_reward_fail] [a_id=%u]",RewardPoints[i].alliance_id);
						return R_ERROR;
					}

					info_log("[alliancepoint_rs_reward] [a_id=%u | rs=%u | rank=%d]",RewardPoints[i].alliance_id,rs,i+1);
					//盟成员奖励
					vector<DataAllianceMember> members;
					members.clear();
					alliance.GetMembers(RewardPoints[i].alliance_id, members);
					for(vector<DataAllianceMember>::iterator itr=members.begin(); itr!=members.end(); itr++)
					{
						if((*itr).uid == alliance_leader.leader_uid)
						{
							continue;
						}
						ret = logicPay.ChangePay((*itr).uid, 0, member_coins, "activity_hequ_alliancepoint");
						if(ret)
						{
							error_log("[add_alliance_point_member_reward_fail] [a_id=%u | uid=%u]",RewardPoints[i].alliance_id,(*itr).uid);
							return R_ERROR;
						}

						string texT = "合区联盟贡献奖励已发放完毕（无需提取附件，系统已自动发放）,请查收！如有疑问，请联系GM";
						DataEmail email;
						CLogicEmail logicEmail;
						vector<uint64_t> toUidList;
						toUidList.push_back((*itr).uid);
						email.attach_flag = 0;
						email.attachments = "";
						email.uid = ADMIN_UID;
						email.post_ts = Time::GetGlobalTime();
						email.title = "合区联盟贡献活动奖励";
						email.text = texT;
						logicEmail.AddEmail(email,toUidList);
						info_log("[alliancepoint_reward] [a_id=%u | uid=%u | rank=%d]",RewardPoints[i].alliance_id,(*itr).uid,i+1);
					}
				}
			}
		}

	}
	return 0;
}

int CLogicHequActivity::UpdateHequAlliancePointRank(unsigned uid, const AlliancePoint &points)
{
	CDataAlliancePoint *pdata= GetHequAlliancePoing();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_alliancepointrank_fail");
	}

	unsigned now = Time::GetGlobalTime();

	if(    	now >=Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS)
		&&	now <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS))
	{
		int ret = pdata->UpdateAlliancePointRankList(points);
		if(ret != 0)
		{
			return ret;
		}
	}
	return 0;

}


int CLogicHequActivity::GetHequWorldAttackRank(unsigned uid, vector <HequWorldAttack> &vecAttacks)
{
	CDataWorldAttack *pdata= GetHequWorldAttack();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattackrank_fail");
	}
	int ret = pdata->GetWorldAttackRankList(vecAttacks);
	if(ret)
	{
		error_log("[get_worldattackranktop10_fail] [uid=%u]",uid);
		return ret;
	}
	return 0;
}

int CLogicHequActivity::GetHequWorldAttackRankJson(unsigned uid, Json::Value &result)
{
	CDataWorldAttack *pdata= GetHequWorldAttack();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattackrank_fail");
	}

	vector <HequWorldAttack> vecAttacks;
	vecAttacks.clear();
	int ret = GetHequWorldAttackRank(uid,vecAttacks);
	if(ret != 0)
	{
		return ret;
	}

	//前十名积分
	for(int i = 0; i < 10; i++)
	{
		result[i]["uid"] = vecAttacks[i].uid;
		result[i]["attack_num"] = vecAttacks[i].attack_num;
		result[i]["name"] = string(vecAttacks[i].name);
	}

	HequWorldAttack selfData;
	ret = pdata->GetWorldAttackSelfData(uid,selfData);
	if(ret != 0)
	{
		return ret;
	}

	result[10]["self"] = selfData.attack_num;
	//发奖
	if((Time::GetGlobalTime() > Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS))
	&& (Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS) + 24*60*60))
	{
		vector <HequWorldAttack> reward_num;
		reward_num.clear();
		pdata->RewardWorldAttackRankList(reward_num);
		if(reward_num.size() > 0)
		{
			for(int i = 0; i < reward_num.size(); i++)
			{
				if(IsValidUid(reward_num[i].uid) && reward_num[i].attack_num >= 40000)
				{
					int xingyunshi_count = 0;
					int xilianshi_count = 0;
					int tz_cailiao_count = 0;
					if(0 == i)
					{
						xingyunshi_count = 10;
						xilianshi_count = 50;
						tz_cailiao_count = 10;
					}
					else if (i >=1 && i <=2)
					{
						xingyunshi_count = 8;
						xilianshi_count = 40;
						tz_cailiao_count = 8;
					}
					else if (i >=3 && i <=9)
					{
						xingyunshi_count = 5;
						xilianshi_count = 20;
						tz_cailiao_count = 5;
					}
					else if(i >= 10)
					{
						xingyunshi_count = 2;
						xilianshi_count = 2;
						tz_cailiao_count = 1;
					}

					CLogicEquipment Equipment;
					Json::Value result;
					result.clear();

					AUTO_LOCK_USER(reward_num[i].uid)
					Equipment.AddOneItem(reward_num[i].uid,11112,xingyunshi_count , "activity_world_attack_reward",result);
					Equipment.AddOneItem(reward_num[i].uid,4011,xilianshi_count , "activity_world_attack_reward",result);
					Equipment.AddOneItem(reward_num[i].uid,50045,tz_cailiao_count , "activity_world_attack_reward",result);


					string texT = "合区攻城拔寨活动奖励已发放完毕（无需提取附件，系统已自动发放）,请查收！如有疑问，请联系GM";
					DataEmail email;
					CLogicEmail logicEmail;
					vector<uint64_t> toUidList;
					toUidList.push_back(reward_num[i].uid);
					email.attach_flag = 0;
					email.attachments = "";
					email.uid = ADMIN_UID;
					email.post_ts = Time::GetGlobalTime();
					email.title = "合区攻城拔寨活动";
					email.text = texT;
					logicEmail.AddEmail(email,toUidList);

					info_log("[world_attack_reward],[uid=%u | attack_num=%u | rank=%u]",reward_num[i].uid,reward_num[i].attack_num,i+1);
				}
			}
		}

	}

	return 0;
}


int CLogicHequActivity::UpdateHequWorldAttackRank(unsigned uid, const HequWorldAttack &Attack)
{
	CDataWorldAttack *pdata= GetHequWorldAttack();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattackrank_fail");
	}

	unsigned now = Time::GetGlobalTime();

	if(    	now >=Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS)
		&&	now <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS))
	{
		int ret = pdata->UpdateWorldAttackRankList(Attack);
		if(ret != 0)
		{
			return ret;
		}
	}

	return 0;
}


int CLogicHequActivity::UpdateNewWorldAttackRank(multimap<unsigned, unsigned> herokill, map<unsigned, string> heroname)
{
	CDataWorldAttack *pdata= GetHequWorldAttack();
	if(pdata == NULL)
	{
		DB_ERROR_RETURN_MSG("init_worldattackrank_fail");
	}


	if( Time::GetGlobalTime() >=Config::GetIntValue(CONFIG_HEQU_ACTIVITY_BEGIN_TS)
	&&	Time::GetGlobalTime() <= Config::GetIntValue(CONFIG_HEQU_ACTIVITY_END_TS))
	{
		int ret = pdata->UpdateNewWorldAttackRankList(herokill, heroname);
		if(ret != 0)
		{
			return ret;
		}
	}

	return 0;
}




