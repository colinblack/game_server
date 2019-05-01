#include "LogicAchievementManager.h"
#include "ProtoManager.h"

int LogicAchievementManager::NewUserInit(unsigned uid)
{
	return 0;
}

int LogicAchievementManager::LoginCheck(unsigned uid)
{
	//检查累积登录数据是否加载进内存
	int ret = DataAchievementManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		DataAchievementManager::Instance()->LoadBuff(uid);
	}

	return 0;
}

int LogicAchievementManager::Process(unsigned uid, ProtoAchievement::VerifyAchievementReq *reqmsg)
{
	//暂时只用来支持迷雾战成就
	unsigned type = reqmsg->type();

	if (type == achievement_type_foggate)
	{
		//todo 接入迷雾战成就
		AchievementParam achievementparam;
		achievementparam.type = achievement_type_foggate;

		VerifyAchievementComplete(uid, achievementparam);
	}

	return 0;
}

int LogicAchievementManager::Process(unsigned uid, ProtoAchievement::GetAchievementRewardReq* reqmsg, ProtoAchievement::GetAchievementRewardResp * respmsg)
{
	unsigned achieveid = reqmsg->id();

	GetAchievementReward(uid, achieveid, respmsg);

	return 0;
}

int LogicAchievementManager::GetAchievementReward(unsigned uid, unsigned id, ProtoAchievement::GetAchievementRewardResp * respmsg)
{
	//获取成就的数据
	DataAchievement & achievement = DataAchievementManager::Instance()->GetAchievement(uid, id);
	DBCUserBaseWrap userwrap(uid);

	//判断是否满足领取的条件
	if (status_uncomplete == achievement.status)
	{
		error_log("[GetAchievementReward] achievement not complete. uid=%u,id=%u", uid, id);
		throw runtime_error("achievement_not_complete");
	}
	else if (status_get_reward == achievement.status)
	{
		error_log("[GetAchievementReward] achievement reward already got. uid=%u,id=%u", uid, id);
		throw runtime_error("reward_already_get");
	}

	//根据任务id，获取任务配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	char szreason[100] = {0};
	sprintf(szreason, "Achievement_%u", id);

	//领取奖励
	for(int i = 0; i < achievecfg.reward_size(); ++i)
	{
		const RewardConfig::Reward & rewardconfig = achievecfg.reward(i);

		//装备
		if (rewardconfig.has_equips())
		{
			unsigned eqid = rewardconfig.equips().eqid();
			unsigned count = rewardconfig.equips().count();

			LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, count, szreason, respmsg->mutable_equips());
		}

		//英雄
		if (rewardconfig.has_hero())
		{
			unsigned heroid = rewardconfig.hero();
			int ret = LogicHeroManager::Instance()->UnlockHero(uid, heroid, szreason, respmsg->mutable_hero());

			if (ret)
			{
				error_log("[GetAchievementReward] unlock hero error. uid=%u", uid);
				throw std::runtime_error("Achievement_unlock_hero_error");
			}
		}

		//资源+钻石+次数
		if (rewardconfig.has_base())
		{
			const CommonGiftConfig::BaseReward& base = rewardconfig.base();
			userwrap.Reward(base, respmsg->mutable_base(),  szreason);
		}
	}

	//更新成就状态
	achievement.status = status_get_reward;
	DataAchievementManager::Instance()->UpdateAchievement(achievement);

	//返回给前端
	achievement.SetMessage(respmsg->mutable_achievement());

	return 0;
}

int LogicAchievementManager::VerifyAchievementComplete(unsigned uid, AchievementParam & param)
{
	if(ProtoManager::m_CurCMD == e_CMD_new)//新用户不处理
		return 0;

	unsigned type = param.type;

	//获取该类型的未完成的成就
	ProtoAchievement::PushAchievementReq *msg = new ProtoAchievement::PushAchievementReq;
	AchievementConfigWrap achieveconfigwrap;

	try
	{
		vector<unsigned> achieveids = achieveconfigwrap.GetAchievesByType(param.type);

		//将同类型的成就id写入到表中
		for(int i = 0; i < achieveids.size(); ++i)
		{
			//判断id是否在档里
			unsigned achieveid = achieveids[i];

			bool isExist = DataAchievementManager::Instance()->IsAchieveExist(uid, achieveid);

			if (!isExist)  //成就不存在，则新增
			{
				//插入数据库
				DataAchievement achievement;
				achievement.uid = uid;
				achievement.id = achieveid;

				int ret = DataAchievementManager::Instance()->AddBuff(achievement);

				if (ret)  //新增失败，如何处理？直接返回错误码
				{
					delete msg;
					return ret;
				}
			}

			DataAchievement & achievement = DataAchievementManager::Instance()->GetAchievement(uid, achieveid);

			//排除已完成的成就
			if (achievement.status != status_uncomplete)
			{
				continue;
			}

			//加载配置
			const AchievementConfig::Achievement achievecfg = achieveconfigwrap.GetAchievementcfg(achievement.id);

			if (param.subparam.size() > 0 && achievement_type_productivity == type)  //这个只用于验证资源相关的成就
			{
				//子类型不一致，比如产量，配置的资源类型和发来的类型不一致,则过滤掉
				if (achievecfg.subtype() != param.subparam[0])
				{
					continue;
				}
			}

			//发出验证
			VerifyAchievement(achievement, param);
			if(ProtoManager::m_CurCMD != e_CMD_login)//登录不推送
				achievement.SetMessage(msg->mutable_achievements()->add_achievement());
		}
	}
	catch(runtime_error & e)
	{
		error_log("[VerifyAchievementComplete] exception:%s. uid=%u", e.what(), uid);
		delete msg;  //释放内存空间

		return R_ERROR;
	}

	//发送推送的信息
	if (0 == msg->achievements().achievement_size())  //没有任务推送时，释放内存
	{
		delete msg;
	}
	else
	{
		LogicManager::Instance()->sendMsg(uid, msg);
	}

	return 0;
}

int LogicAchievementManager::VerifyAchievement(DataAchievement & achievement, AchievementParam & param)
{
	int subvalue = 0;

	if (param.subparam.size() > 0)
	{
		subvalue = param.subparam[0];
	}

	switch(param.type)
	{
		case achievement_type_productivity: VerifyProductivity(achievement); break;
		case achievement_type_openmine: VerifyOpenMine(achievement); break;
		case achievement_type_minesupport: VerifyMineSupport(achievement); break;
		case achievement_type_unlockhero: VerifyUnlockHero(achievement); break;
		case achievement_type_hprecover: VerifyUseOrder(achievement, subvalue); break;
		case achievement_type_joindepartment: VerifyJoinDepartment(achievement); break;
		case achievement_type_official: VerifyOfficial(achievement); break;
		case achievement_type_affair: VerifyAffair(achievement); break;
		case achievement_type_loyalexchange: VerifyLoyalExchange(achievement); break;
		case achievement_type_parade: VerifyParade(achievement); break;
		case achievement_type_dailymission: VerifyDailyMission(achievement); break;
		case achievement_type_weaponlevel: VerifyWeaponLevel(achievement); break;
		case achievement_type_character_equip: VerifyCharacterEquip(achievement); break;
		case achievement_type_star_equip: VerifyStarEquip(achievement); break;
		case achievement_type_extraproperty: VerifyExtraProperty(achievement); break;
		case achievement_type_character_component: VerifyCharacterComponent(achievement); break;
		case achievement_type_tech_research: VerifyTechResearch(achievement); break;
		case achievement_type_composesuit: VerifyComposeSuit(achievement); break;
		case achievement_type_rush: VerifyRush(achievement); break;
		case achievement_type_kill: VerifyKill(achievement); break;
		case achievement_type_march: VerifyMarch(achievement); break;
		case achievement_type_retreat: VerifyRetreat(achievement); break;
		case achievement_type_occupycity: VerifyOccupy(achievement); break;
		case achievement_type_foggate: VerifyFoggate(achievement); break;

		default: break;
	}

	DataAchievementManager::Instance()->UpdateAchievement(achievement);

	return 0;
}

int LogicAchievementManager::VerifyProductivity(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	//获取资源类型
	unsigned uid = achievement.uid;
	int subtype = achievecfg.subtype();

	//根据资源类型，获取当前产量，排除加倍道具
	int productivity = LogicBuildManager::Instance()->YieldAchievement(uid, subtype);
	achievement.current = productivity;

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyOpenMine(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	achievement.current += 1;

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyMineSupport(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	achievement.current += 1;

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyUnlockHero(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned heroid = achievecfg.condition(0u);

	//判断指定英雄是否解锁
	bool isexist = DataHeroManager::Instance()->isHeroExists(achievement.uid, heroid);

	if (isexist)
	{
		achievement.current = 1;
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyUseOrder(DataAchievement & achievement, unsigned count)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	achievement.current += count;

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyJoinDepartment(DataAchievement & achievement)
{
	//如何判断是否加入非军校部门
	unsigned index = ResourceManager::Instance()->GetIndex(achievement.uid);

	if (0 != ResourceManager::m_data->item[index].aid)  //非军校
	{
		achievement.current = 1;
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyOfficial(DataAchievement & achievement)
{
	unsigned index = ResourceManager::Instance()->GetIndex(achievement.uid);

	if (0 != ResourceManager::m_data->item[index].job)  //非普通成员
	{
		achievement.current = 1;
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyAffair(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	achievement.current += 1;

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyLoyalExchange(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	achievement.current += 1;

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyParade(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	achievement.current += 1;

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyDailyMission(DataAchievement & achievement)
{
	//外层加判断，非三星不会进来
	achievement.current += 1;

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyWeaponLevel(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	//x项军工达到y级
	//获取所有已解锁的军工
	unsigned uid = achievement.uid;

	vector<unsigned> indexs;
	DataWeaponMgr::Instance()->GetIndexs(uid, indexs);

	unsigned count_condition = achievecfg.condition(0u);
	unsigned level_condition = achievecfg.condition(1u);

	unsigned count = 0;

	for(int i = 0; i < indexs.size(); ++i)
	{
		DBCWeapon & weapon = DataWeaponMgr::Instance()->GetWeapon(indexs[i]);

		if (weapon.level >= level_condition)
		{
			++count;
		}
	}

	achievement.current = count;

	if (achievement.current >= count_condition)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyCharacterEquip(DataAchievement & achievement)
{
	//x件y品质装备

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned count_condition = achievecfg.condition(0u);
	unsigned character_condition = achievecfg.condition(1u);

	EquipCfgWrap equipcfgwrap;
	int count = 0;
	unsigned uid = achievement.uid;

	//获取用户已拥有的物品
	vector<unsigned> vctEquipsIndex;
	EquipmentManager::Instance()->GetEquipments(uid, vctEquipsIndex);

	//查找满足条件的品质装备
	for(int j = 0; j < vctEquipsIndex.size(); ++j)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctEquipsIndex[j]);

		//排除普通道具
		if (!equipcfgwrap.IsEquipment(equip.eqid))
		{
			continue;
		}

		const EquipmentConfig::Equip & equipcfg = equipcfgwrap.GetEquip(equip.eqid);

		if (equipcfg.character() >= character_condition)
		{
			++count;

			if (count >= count_condition)   //满足条件，就停止遍历
			{
				break;
			}
		}
	}

	achievement.current = count;

	if (achievement.current >= count_condition)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyStarEquip(DataAchievement & achievement)
{
	//x件y星装备

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned count_condition = achievecfg.condition(0u);
	unsigned star_condition = achievecfg.condition(1u);

	EquipCfgWrap equipcfgwrap;
	int count = 0;
	unsigned uid = achievement.uid;

	//获取用户已拥有的物品
	vector<unsigned> vctEquipsIndex;
	EquipmentManager::Instance()->GetEquipments(uid, vctEquipsIndex);

	//查找满足条件的品质装备
	for(int j = 0; j < vctEquipsIndex.size(); ++j)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctEquipsIndex[j]);

		//排除普通道具
		if (!equipcfgwrap.IsEquipment(equip.eqid))
		{
			continue;
		}

		if (equip.star >= star_condition)
		{
			++count;

			if (count >= count_condition)   //满足条件，就停止遍历
			{
				break;
			}
		}
	}

	achievement.current = count;

	if (achievement.current >= count_condition)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyExtraProperty(DataAchievement & achievement)
{
	//x条A秘籍属性+y条b秘籍属性
	//只计算装备的第四条属性

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned countA_condition = achievecfg.condition(0u);
	unsigned typeA_condition = achievecfg.condition(1u);
	unsigned countB_condition = achievecfg.condition(2u);
	unsigned typeB_condition = achievecfg.condition(3u);

	EquipCfgWrap equipcfgwrap;
	int count = 0;
	unsigned uid = achievement.uid;

	//获取用户已拥有的物品
	vector<unsigned> vctEquipsIndex;
	EquipmentManager::Instance()->GetEquipments(uid, vctEquipsIndex);

	int countA = 0;
	int countB = 0;

	//查找满足条件的品质装备
	for(int j = 0; j < vctEquipsIndex.size(); ++j)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctEquipsIndex[j]);

		//排除普通道具
		if (!equipcfgwrap.IsEquipment(equip.eqid))
		{
			continue;
		}

		//过滤低于4星的
		if (equip.star < 4)
		{
			continue;
		}

		//排除非指定属性类型
		if (equip.subt4 == typeA_condition)
		{
			++countA;
		}
		else if (equip.subt4 == typeB_condition)
		{
			++countB;
		}
	}

	if (countA >= countA_condition && countB >= countB_condition)
	{
		achievement.status = 1;
		achievement.current = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyCharacterComponent(DataAchievement & achievement)
{
	//x件y品质部件

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned count_condition = achievecfg.condition(0u);
	unsigned character_condition = achievecfg.condition(1u);

	ComponentConfigWrap compofgwrap;
	unsigned uid = achievement.uid;

	//获取用户已拥有的物品
	vector<unsigned> indexs;
	DataComponentManager::Instance()->GetComponents(uid, indexs);

	int count = 0;

	//查找满足条件的品质装备
	for(int j = 0; j < indexs.size(); ++j)
	{
		DataComponent & component = DataComponentManager::Instance()->GetComponent(indexs[j]);

		const ComponentConfig::ComponentBase & compocfg = compofgwrap.GetComponentBaseConfig(component.compid);

		if (compocfg.character() >= character_condition)
		{
			++count;

			if (count >= count_condition)   //满足条件，就停止遍历
			{
				break;
			}
		}
	}

	achievement.current = count;

	if (achievement.current >= count_condition)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyTechResearch(DataAchievement & achievement)
{
	//研究成功指定的科技

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);
	unsigned techid = achievecfg.condition(0u);

	bool isdone = LogicScienceMgr::Instance()->IsScienceDoneResearch(achievement.uid, techid);

	if (isdone)
	{
		achievement.status = 1;
		achievement.current = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyComposeSuit(DataAchievement & achievement)
{
	//x件y级套装

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned count_condition = achievecfg.condition(0u);
	unsigned level_condition = achievecfg.condition(1u);

	//获取用户已拥有的物品
	EquipCfgWrap equipcfgwrap;
	unsigned uid = achievement.uid;

	vector<unsigned> vctEquipsIndex;
	EquipmentManager::Instance()->GetEquipments(uid, vctEquipsIndex);

	int count = 0;

	//查找满足条件的品质装备
	for(int j = 0; j < vctEquipsIndex.size(); ++j)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctEquipsIndex[j]);

		const EquipmentConfig::Equip & equipcfg = equipcfgwrap.GetEquip(equip.eqid);

		if (equipcfg.type() == (level_condition + 3))
		{
			++count;

			if (count >= count_condition)   //满足条件，就停止遍历
			{
				break;
			}
		}
	}

	achievement.current = count;

	if (achievement.current >= count_condition)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyRush(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned rush_condtion = achievecfg.condition(0u);

	//直接从英雄的档里获取单挑
	achievement.current = LogicHeroManager::Instance()->GetUserRush(achievement.uid);

	if (achievement.current >= rush_condtion)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyKill(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned kill_condtion = achievecfg.condition(0u);

	achievement.current = LogicHeroManager::Instance()->GetUserKill(achievement.uid);

	if (achievement.current >= kill_condtion)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyMarch(DataAchievement & achievement)
{
	achievement.current += 1;

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyRetreat(DataAchievement & achievement)
{
	achievement.current += 1;

	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyOccupy(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	unsigned occupy_condtion = achievecfg.condition(0u);

	achievement.current = LogicHeroManager::Instance()->GetUserOccupy(achievement.uid);

	if (achievement.current >= occupy_condtion)
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::VerifyFoggate(DataAchievement & achievement)
{
	//加载配置
	const AchievementConfig::Achievement achievecfg = AchievementConfigWrap().GetAchievementcfg(achievement.id);

	//获取当前已闯过的迷雾数
	achievement.current = LogicFogGateManager::Instance()->GetFogGateSuccessNum(achievement.uid);

	if (achievement.current >= achievecfg.condition(0u))
	{
		achievement.status = 1;
	}

	return 0;
}

int LogicAchievementManager::FullMessage(unsigned uid, ProtoAchievement::AchievementAllCPP * msg)
{
	vector<unsigned> indexs;

	DataAchievementManager::Instance()->GetUserAchievements(uid, indexs);

	for(int i = 0; i < indexs.size(); ++i)
	{
		DataAchievement & achievement = DataAchievementManager::Instance()->GetAchievement(indexs[i]);

		achievement.SetMessage(msg->add_achievement());
	}

	return 0;
}
