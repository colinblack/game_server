/*
 * NPCActivity.cpp
 *
 *  Created on: 2016-10-20
 *      Author: Ralf
 */

#include "NPCActivity.h"

#define NPC_ACT_TIME (Time::GetGlobalTime() + 900)
#define NPC_ACT_ID (140401 + Math::GetRandomInt(3))

void NPCActivity::OnStart()
{
	for(unsigned j=1;j<=SG17_KINGDOM;++j)
	{
		unsigned id = NPC_ACT_ID;
		uint16_t c = WMI->OnNPCAct(j, id);
		m_cts[j] = make_pair(make_pair(c, c?id:0), c?0:NPC_ACT_TIME);
	}
}

void NPCActivity::OnMin()
{
	for(unsigned j=1;j<=SG17_KINGDOM;++j)
	{
		if(m_cts[j].first.first == 0 && m_cts[j].second <= Time::GetGlobalTime())
		{
			unsigned id = NPC_ACT_ID;
			uint16_t c = WMI->OnNPCAct(j, id);
			m_cts[j] = make_pair(make_pair(c, c?id:0), c?0:NPC_ACT_TIME);
		}
		else if(m_cts[j].first.first && !WMI->IsCityFighting(m_cts[j].first.first))
			m_cts[j] = make_pair(make_pair(0, 0), NPC_ACT_TIME);
	}
}

void NPCActivity::OnDay()
{
	//跨天，处理所有在线用户的活动事件的刷新
	//加载在线用户
    const map<unsigned, Common::Login>& uidmap = UserManager::Instance()->GetUser();
    vector<unsigned> uids;

    for(map<unsigned, Common::Login>::const_iterator it = uidmap.begin(); it != uidmap.end(); ++it)
    {
    	uids.push_back(it->first);
    }

    //刷新活动事件
    for(vector<unsigned>::iterator it = uids.begin(); it != uids.end(); ++it)
	{
    	RefreshNewDayAffair(*it);
	}
}

int NPCActivity::NewUserInit(unsigned uid)
{
	//不管活动是否开启，都要初始化空白的活动数据
	int ret = NPCActivityInit(uid);

	if (ret)
	{
		return ret;
	}

	CheckNPCActivity(uid);

	return 0;
}

int NPCActivity::LoginCheck(unsigned uid)
{
	int ret = 0;
	//判断活动数据是否已经加载进内存
	bool isExist = DataNPCActivityManager::Instance()->IsNPCActivityExists(uid);

	if (!isExist)
	{
		ret = DataNPCActivityManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)  //表中没有活动数据，初始化它
		{
			ret = NPCActivityInit(uid);
		}

		if (ret)
		{
			return ret;
		}
	}

	//检查活动
	ret = CheckNPCActivity(uid);

	if (ret)
	{
		return ret;
	}

	//加载活动数据
	DataNPCActivity & datanpcactivity = DataNPCActivityManager::Instance()->Get(uid);

	//获取用户的上次离线时间
	DBCUserBaseWrap userwrap(uid);
	unsigned now = Time::GetGlobalTime();

	if (CTime::IsDiffDay(now, userwrap.Obj().last_off_time))  //跨天
	{
		//刷新活动事件
		datanpcactivity.affair_id = GetNewDayAffair();
	}

	DataNPCActivityManager::Instance()->UpdateDataNPCActivity(datanpcactivity);

	return 0;
}

int NPCActivity::NPCActivityInit(unsigned uid)
{
	//初始化空白活动数据
	DataNPCActivity npcactivity;
	npcactivity.uid = uid;

	int ret = DataNPCActivityManager::Instance()->AddBuff(npcactivity);

	if (ret)
	{
		error_log("[NPCActivityInit] add activity error. uid=%u", uid);
		return ret;
	}

	return 0;
}

int NPCActivity::AddNPCActivityMaterial(unsigned uid, unsigned id, unsigned count)
{
	//如果活动未开启，则不处理
	int ret = CheckNPCActivity(uid);

	if (ret)
	{
		return ret;
	}

	//加载活动数据
	DataNPCActivity & datanpcactivity = DataNPCActivityManager::Instance()->Get(uid);

	//结算npc掉落的材料数量
	switch(id)
	{
		case e_asyn_npc_1: datanpcactivity.materialnum1 += count; break;
		case e_asyn_npc_2: datanpcactivity.materialnum2 += count; break;
		case e_asyn_npc_3: datanpcactivity.materialnum3 += count; break;
	}

	DataNPCActivityManager::Instance()->UpdateDataNPCActivity(datanpcactivity);

	return 0;
}

int NPCActivity::Process(unsigned uid, ProtoNPCActivity::OpenNPCActivityWindowReq *reqmsg, ProtoNPCActivity::OpenNPCActivityWindowResp * respmsg)
{
	return OpenNPCActivity(uid, respmsg);
}

int NPCActivity::Process(unsigned uid, ProtoNPCActivity::GetActiveAffairRewardReq *reqmsg, ProtoNPCActivity::GetActiveAffairRewardResp * respmsg)
{
	unsigned type = reqmsg->type();

	return GetAffairReward(uid, type, respmsg);
}

int NPCActivity::Process(unsigned uid, ProtoNPCActivity::GetActiveValueRewardReq *reqmsg, ProtoNPCActivity::GetActiveValueRewardResp * respmsg)
{
	unsigned index = reqmsg->index();
	return GetActiveValueReward(uid, index, respmsg);
}

int NPCActivity::OpenNPCActivity(unsigned uid, ProtoNPCActivity::OpenNPCActivityWindowResp * respmsg)
{
	User::ActivityItem act;
	ConfigManager::Instance()->GetActivity(e_Activity_NPC, act);

	if (!IsOn()) //活动未开启
	{
		respmsg->mutable_activityitem()->MergeFrom(act);
		return 0;
	}

	//判断是否重置
	DataNPCActivity & npcactivity = DataNPCActivityManager::Instance()->Get(uid);

	if (act.ver() != npcactivity.version)
	{
		ResetNPCActivity(npcactivity, act.ver());
		DataNPCActivityManager::Instance()->UpdateDataNPCActivity(npcactivity);

		//如果有重置，则将新的活动版本信息返回给前端
		respmsg->mutable_activityitem()->MergeFrom(act);
	}

	//发送活动配置
	NPCAcitivityConfigWrap npcactivityconfig;

	//距离开服的天数
	unsigned diff = LogicManager::Instance()->GetOpenDays();

	//活力值奖励的配置
	respmsg->mutable_activityconfig()->mutable_activevalueconfig()->MergeFrom(npcactivityconfig.GetOpenPlatReward(diff).active_value_reward());

	//活动内容
	npcactivity.SetMessage(respmsg->mutable_activity());

	//掉落的NPC信息
	for(map<uint8_t, pair<pair<uint16_t, unsigned>, unsigned> >::iterator piter = m_cts.begin(); piter != m_cts.end(); ++piter)
	{
		ProtoNPCActivity::SpecialNPCCPP specialnpc;

		specialnpc.set_kindom(piter->first);
		specialnpc.set_city(piter->second.first.first);
		specialnpc.set_npcid(piter->second.first.second);
		specialnpc.set_nextts(piter->second.second);

		respmsg->add_npcinfo()->MergeFrom(specialnpc);
	}

	//倍数
	int multiple = GetMultiple();
	respmsg->set_multiple(multiple);

	//天数
	int day = GetBeginDays();
	respmsg->set_day(day);

	return 0;
}

int NPCActivity::GetAffairReward(unsigned uid, unsigned type, ProtoNPCActivity::GetActiveAffairRewardResp * respmsg)
{
	int ret = CheckNPCActivity(uid);

	if (ret)
	{
		error_log("[GetAffairReward] activity is not on. uid=%u", uid);
		throw std::runtime_error("activity_not_on");
	}

	//判断参数是否合法
	if (complete_affair_by_props != type && complete_affair_by_cash != type)
	{
		error_log("[GetAffairReward] type param error. uid=%u,type=%u", uid, type);
		throw std::runtime_error("param_error");
	}

	//加载活动数据
	DataNPCActivity & npcactivity = DataNPCActivityManager::Instance()->Get(uid);

	//判断事件是否存在
	if (0 == npcactivity.affair_id)
	{
		error_log("[GetAffairReward] no activity affair. uid=%u,id=%u", uid, npcactivity.affair_id);
		throw std::runtime_error("no_activity_affair");
	}

	//根据事件id获取事件的配置
	NPCAcitivityConfigWrap npcactivitycfgwrap;

	const ProtoNPCActivity::AffairConfigCPP & affairconfig = npcactivitycfgwrap.GetAffairConfig(npcactivity.affair_id);

	DBCUserBaseWrap userwrap(uid);

	//获取开服时间对应的下标
	unsigned diff = LogicManager::Instance()->GetOpenDays();
	int openindex = npcactivitycfgwrap.GetOpenPlatfromIndex(diff);

	//扣除道具或者钻石
	if (complete_affair_by_props == type)  //通过消耗道具完成，进行验证和扣除道具
	{
		CheckAndCostMaterial(npcactivity, affairconfig);
	}
	else
	{
		int count = affairconfig.items(1u).open_platform_affair(openindex).paycash();
		userwrap.CostCash(count, "NPCActivityAffair");
	}

	respmsg->set_cash(userwrap.Obj().cash);

	//发放奖励
	int index = type - 1;

	for(int i = 0; i < affairconfig.items(index).open_platform_affair(openindex).reward_size(); ++i)
	{
		const DataConfig::RewardConfigCPP & rewardconfig = affairconfig.items(index).open_platform_affair(openindex).reward(i);
		ProvideReward(uid, rewardconfig, 1, "NPCActivityAffair", respmsg->mutable_reward());
	}

	//活力值
	int active_value = affairconfig.items(index).open_platform_affair(openindex).active_value();
	npcactivity.active_value += active_value;

	//领取完事件，更新事件id
	RefreshNextAffair(uid);

	DataNPCActivityManager::Instance()->UpdateDataNPCActivity(npcactivity);
	npcactivity.SetMessage(respmsg->mutable_activity());

	return 0;
}

int NPCActivity::CheckAndCostMaterial(DataNPCActivity & npcactivity, const ProtoNPCActivity::AffairConfigCPP & affairconfig)
{
	//验证条件是否符合
	int props = affairconfig.items(0u).props();
	int materialtype = Props2Type(props);

	int count = affairconfig.items(0u).count();
	bool isEnough = false;

	//扣除道具
	switch(materialtype)
	{
		case e_asyn_npc_1: if (npcactivity.materialnum1 >= count) { isEnough = true; npcactivity.materialnum1 -= count;} break;
		case e_asyn_npc_2: if (npcactivity.materialnum2 >= count) { isEnough = true; npcactivity.materialnum2 -= count;} break;
		case e_asyn_npc_3: if (npcactivity.materialnum3 >= count) { isEnough = true; npcactivity.materialnum3 -= count;} break;
		default: break;
	}

	if (!isEnough)
	{
		error_log("[VerifyAffairCondition] material is not enough. uid=%u,type=%d", npcactivity.uid, materialtype);
		throw std::runtime_error("props_not_enough");
	}

	return 0;
}

int NPCActivity::GetActiveValueReward(unsigned uid, unsigned index, ProtoNPCActivity::GetActiveValueRewardResp * respmsg)
{
	int ret = CheckNPCActivity(uid);

	if (ret)
	{
		error_log("[GetAffairReward] activity is not on. uid=%u", uid);
		throw std::runtime_error("activity_not_on");
	}

	//获取开服天数
	unsigned diff = LogicManager::Instance()->GetOpenDays();

	NPCAcitivityConfigWrap npcactivitycfgwrap;
	const ProtoNPCActivity::OpenPlatformRewardConfigCPP & npcactivityconfig = npcactivitycfgwrap.GetOpenPlatReward(diff);

	int max_active_size = npcactivityconfig.active_value_reward_size();

	if (1 > index || index > max_active_size)
	{
		error_log("[GetActiveValueReward] index param error. uid=%u,index=%u", uid, index);
		throw std::runtime_error("param_error");
	}

	int pos = index - 1;
	int condition_value = npcactivityconfig.active_value_reward(pos).value();

	//加载活动数据
	DataNPCActivity & npcactivity = DataNPCActivityManager::Instance()->Get(uid);
	//校验活力值是否足够
	if (npcactivity.active_value < condition_value)
	{
		error_log("[GetActiveValueReward] active value is not enough. uid=%u,index=%u,value=%u", uid, index, npcactivity.active_value);
		throw std::runtime_error("active_value_not_enough");
	}

	//判断是否已经领取该位置的奖励
	bool iszero = LogicCommonUtil::CheckPosIsZero(npcactivity.status, pos);

	if (!iszero)   //非0，表示已领取
	{
		error_log("[GetActiveValueReward] active value reward already get. uid=%u, index=%u", uid, index);
		throw std::runtime_error("already_get_reward");
	}

	int multiple = 1;

	if (index == max_active_size)  //最后一个活力值兑换，才有加倍
	{
		multiple = GetMultiple();
	}

	for(int i = 0; i < npcactivityconfig.active_value_reward(pos).reward_size(); ++i)
	{
		ProvideReward(uid, npcactivityconfig.active_value_reward(pos).reward(i), multiple, "NPCActiveValue" ,respmsg->mutable_reward());
	}

	//设置已领取状态
	LogicCommonUtil::SetBitCurrent(npcactivity.status, pos);
	DataNPCActivityManager::Instance()->UpdateDataNPCActivity(npcactivity);
	npcactivity.SetMessage(respmsg->mutable_activity());

	return 0;
}

int NPCActivity::Props2Type(unsigned props)
{
	int type = 0;
	type = 4 + props;
	return type;
}

int NPCActivity::GetMultiple()
{
	if (!IsOn())
	{
		return 0;
	}

	//倍数
	User::ActivityItem act;
	ConfigManager::Instance()->GetActivity(e_Activity_NPC, act);
	unsigned now = Time::GetGlobalTime();
	int diff_day = CTime::GetDayInterval(act.bts(), now);

	if (diff_day > 2)
	{
		diff_day = 2;
	}

	int multiple = 3 - diff_day;

	return multiple;
}

int NPCActivity::GetBeginDays()
{
	if (!IsOn())
	{
		return 0;
	}

	//天数
	User::ActivityItem act;
	ConfigManager::Instance()->GetActivity(e_Activity_NPC, act);
	unsigned now = Time::GetGlobalTime();
	int diff_day = CTime::GetDayInterval(act.bts(), now);

	int day = diff_day + 1;  //包含活动开始当天

	return day;
}

int NPCActivity::ProvideReward(unsigned uid, const DataConfig::RewardConfigCPP & rewardconfig, unsigned multiple, string reason, ProtoNPCActivity::FinalRewardCPP * reward)
{
	//装备
	if (rewardconfig.has_equips())
	{
		unsigned eqid = rewardconfig.equips().eqid();
		unsigned count = rewardconfig.equips().count() * multiple;

		LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, count, reason, reward->mutable_equips());
	}

	//资源+钻石+次数
	if (rewardconfig.has_base())
	{
		CommonGiftConfig::BaseReward base;

		AdaptCommonGiftBase(rewardconfig.base(), base);

		DBCUserBaseWrap userwrap(uid);
		userwrap.Reward(base, reward->mutable_base(), reason, multiple);
	}

	return 0;
}

int NPCActivity::AdaptCommonGiftBase(const DataConfig::BaseRewardConfigCPP & from_base, CommonGiftConfig::BaseReward & dest_base)
{
	if (from_base.has_coin())
	{
		dest_base.set_coin(from_base.coin());
	}

	if (from_base.has_wood())
	{
		dest_base.set_wood(from_base.wood());
	}

	if (from_base.has_food())
	{
		dest_base.set_food(from_base.food());
	}

	if (from_base.has_iron())
	{
		dest_base.set_iron(from_base.iron());
	}

	if (from_base.has_hammer())
	{
		dest_base.set_hammer(from_base.hammer());
	}

	if (from_base.has_order())
	{
		dest_base.set_order(from_base.order());
	}

	if (from_base.has_exp())
	{
		dest_base.set_exp(from_base.exp());
	}

	if (from_base.has_cash())
	{
		dest_base.set_cash(from_base.cash());
	}

	if (from_base.has_refresh())
	{
		dest_base.set_refresh(from_base.refresh());
	}

	if (from_base.has_arefresh())
	{
		dest_base.set_arefresh(from_base.arefresh());
	}

	if (from_base.has_sacrifice())
	{
		dest_base.set_sacrifice(from_base.sacrifice());
	}

	if (from_base.has_market())
	{
		dest_base.set_market(from_base.market());
	}

	//影子
	if (from_base.has_shadow())
	{
		dest_base.set_shadow(from_base.shadow());
	}

	return 0;
}

int NPCActivity::RefreshNewDayAffair(unsigned uid)
{
	//检查活动，包括活动是否开启，活动的版本号等
	int ret = CheckNPCActivity(uid);

	if (ret)
	{
		return ret;
	}

	try
	{
		//加载活动数据
		DataNPCActivity & datanpcactivity = DataNPCActivityManager::Instance()->Get(uid);
		datanpcactivity.affair_id = GetNewDayAffair();
		DataNPCActivityManager::Instance()->UpdateDataNPCActivity(datanpcactivity);
	}
	catch (std::runtime_error &e)
	{
		error_log("[RefreshNewDayAffair] exception error. reason=%s", e.what());
		return R_ERROR;
	}

	return 0;
}

int NPCActivity::RefreshNextAffair(unsigned uid)
{
	//检查活动，包括活动是否开启，活动的版本号等
	int ret = CheckNPCActivity(uid);

	if (ret)
	{
		return ret;
	}

	try
	{
		//加载活动数据
		DataNPCActivity & datanpcactivity = DataNPCActivityManager::Instance()->Get(uid);

		//根据当前id，获取下一个id，如果没有就为0，排除已到底末尾的情况
		if (datanpcactivity.affair_id != 0)
		{
			datanpcactivity.affair_id = NPCAcitivityConfigWrap().GetNextAffair(datanpcactivity.affair_id);
			DataNPCActivityManager::Instance()->UpdateDataNPCActivity(datanpcactivity);
		}
	}
	catch (std::runtime_error &e)
	{
		error_log("[RefreshNextAffair] exception error. reason=%s", e.what());
		return R_ERROR;
	}

	return 0;
}


int NPCActivity::CheckNPCActivity(unsigned uid)
{
	if (!IsOn())
	{
		return R_ERROR;
	}

	DataNPCActivity & npcactivity = DataNPCActivityManager::Instance()->Get(uid);

	User::ActivityItem act;

	ConfigManager::Instance()->GetActivity(e_Activity_NPC, act);

	if (act.ver() != npcactivity.version)
	{
		ResetNPCActivity(npcactivity, act.ver());
		DataNPCActivityManager::Instance()->UpdateDataNPCActivity(npcactivity);
	}

	return 0;
}

int NPCActivity::ResetNPCActivity(DataNPCActivity & npcactivity, unsigned version)
{
	npcactivity.version = version;
	npcactivity.active_value = 0;  //活力值重置
	npcactivity.status = 0;  //领取状态重置
	npcactivity.materialnum1 = 0;   //材料1重置
	npcactivity.materialnum2 = 0;   //材料2重置
	npcactivity.materialnum3 = 0;   //材料3重置

	npcactivity.affair_id =  GetNewDayAffair();  //活动事件id重置

	return 0;
}

int NPCActivity::GetNewDayAffair()
{
	//新一天的事件刷新
	unsigned now = Time::GetGlobalTime();
	User::ActivityItem act;
	ConfigManager::Instance()->GetActivity(e_Activity_NPC, act);
	int diffday = CTime::GetDayInterval(act.bts(), now);

	int day = diffday + 1;   //实际活动时间

	return NPCAcitivityConfigWrap().GetFirstAffair(day);
}

