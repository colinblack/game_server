#include "LogicMissionManager.h"

int LogicMissionManager::NewUserInit(unsigned uid)
{
	ProtoMission::MissionAllCPP * nextmission = new ProtoMission::MissionAllCPP;
	UnlockMission(uid, 0, nextmission);   //解锁第一个任务

	MissionParam firstloginparam;
	firstloginparam.type = mission_type_first_login;

	//判断第一个任务是否完成
	VerifyMissionComplete(uid, firstloginparam, nextmission);   //自动校验第一个是否完成
	delete nextmission;

	return 0;
}

int LogicMissionManager::LoginCheck(unsigned uid)
{
	//判断任务是否加载进内存
	int ret = DataMissionManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = DataMissionManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)   //没有数据，可能是因为任务已经全部完成了，所以不做处理
		{
			return 0;
		}
	}

	return ret;
}

int LogicMissionManager::UnlockMission(unsigned uid, unsigned mid, ProtoMission::MissionAllCPP * nextmission)
{
	//取出前置id是指定id的
	int ret = R_SUCCESS;

	if (!ConfigManager::Instance()->m_mapPreMission.count(mid))
	{
		return 0;
	}

	set<unsigned>::iterator miter;
	vector<MissionConfigWrap::MissionBase> vctNextMission;
	MissionConfigWrap missionConfig;

	MissionConfigWrap::MissionBase misconfigbase;

	for(miter = ConfigManager::Instance()->m_mapPreMission[mid].begin(); miter != ConfigManager::Instance()->m_mapPreMission[mid].end(); ++miter)
	{
		ret = missionConfig.GetMissionBase(*miter, misconfigbase);

		if (ret)
		{
			error_log("[UnlockMission] get config error. uid=%u,mid=%u", uid, *miter);
			throw std::runtime_error("get_mission_config_error");
		}

		if (misconfigbase.pre == mid)   //解锁没有前置任务或者前置任务是当前已完成的任务
		{
			vctNextMission.push_back(misconfigbase);
		}
	}

	for(int i = 0; i < vctNextMission.size(); ++i)
	{
		DataMission addmission;
		addmission.uid = uid;
		addmission.id = vctNextMission[i].id;

		DataMissionManager::Instance()->AddBuff(addmission);
	}

	//todo 领取奖励通过界面点击
	for(int i = 0; i < vctNextMission.size(); ++i)
	{
		MissionParam param;
		param.type = vctNextMission[i].type;

		switch(param.type)
		{
			case mission_type_productivity:
			case mission_type_tech_research:
			case mission_type_upgrade_building:
			case mission_type_gate:
			case mission_type_purchase:
			case mission_type_herodress:
			case mission_type_herohp_recover:
			case mission_type_hegemony_kill:
			case mission_type_hegemony_feats:
			case mission_type_recruit:
			case mission_type_autoupgrade:
			case mission_type_character_buy:
			case mission_type_character_dress:
			case mission_type_hero_upgrade:
			case mission_type_num_dress:
			case mission_type_foggate_success:
			case mission_type_tech_done:
				VerifyMissionComplete(uid, param, nextmission); break;  //这些任务，任务接取之前有效
			default:
			{
				DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, vctNextMission[i].id);
				SetMissionMessage(datamission, nextmission->add_missions());
				break;
			}
		}
	}

	return 0;
}

int LogicMissionManager::Process(unsigned uid, ProtoMission::GetMissionRewardReq *reqmsg, ProtoMission::GetMissionRewardResp * respmsg)
{
	unsigned mid = reqmsg->id();

	GetMissionReward(uid, mid, respmsg);

	return 0;
}

int LogicMissionManager::Process(unsigned uid, ProtoMission::VerfifyMissonReq *reqmsg)
{
	//接入争霸杀敌任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_hegemony_kill;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	//接入争霸功勋任务
	missionparam.type = mission_type_hegemony_feats;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}

int LogicMissionManager::Process(unsigned uid, ProtoMission::VerifyWorldMoveMissionReq *reqmsg)
{
	//接入世界移动任务
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_world_move;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}

int LogicMissionManager::GetMissionReward(unsigned uid, unsigned mid, ProtoMission::GetMissionRewardResp * respmsg)
{
	//领取任务奖励
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, mid);

	//判断任务是否已完成
	if (0 == datamission.status)
	{
		error_log("[GetMissionReward] mission is not complete. uid=%u,mid=%u", uid, mid);
		throw std::runtime_error("mission_not_complete");
	}

	MissionConfigWrap missionConfig;
	const MissionConfig::MissionReward & reward = missionConfig.GetRewardConfig(mid);

	int food = reward.food();
	int coin = reward.coin();
	int wood = reward.wood();
	int exp = reward.exp();

	Json::Value result;

	DataBase & database = BaseManager::Instance()->Get(uid);

	char reason[100] = {0};
	sprintf(reason, "Get_Mission_Reward_%u", mid);
	//资源添加
	LogicUserManager::Instance()->AddUserResource(uid, coin, wood, food, 0, reason, result);

	respmsg->set_coin(result["coin"].asUInt());
	respmsg->set_food(result["food"].asUInt());
	respmsg->set_wood(result["wood"].asUInt());

	//判断是否有黄金锤子的添加
	if (reward.has_hammer())
	{
		DBCUserBaseWrap userwrap(uid);
		unsigned count = reward.hammer();
		userwrap.AddGoldHammer(count, "Get_Mission_Reward");
		respmsg->set_hammer(userwrap.Obj().harmmer);
	}

	//经验添加
	LogicUserManager::Instance()->AddExp(uid, exp);

	respmsg->set_exp(database.exp);
	respmsg->set_level(database.level);

	//领取奖励之后，将任务从表中删除
	DataMissionManager::Instance()->DeleteMission(datamission);

	//解锁下一批任务
	UnlockMission(uid, mid, respmsg->mutable_nextmission());
	return 0;
}

int LogicMissionManager::FullMessage(unsigned uid, ProtoMission::MissionAllCPP * msg)
{
	//先取出任务列表中的所有任务
	vector<unsigned> vctIndexs;
	DataMissionManager::Instance()->GetUserMissions(uid, vctIndexs);

	for(int i = 0; i < vctIndexs.size(); ++i)
	{
		DataMission & datamission = DataMissionManager::Instance()->GetMissionByIndex(vctIndexs[i]);
		SetMissionMessage(datamission, msg->add_missions());
	}

	return 0;
}

int LogicMissionManager::VerifyMissionComplete(unsigned uid, MissionParam & param)
{
	//将内容写入推送协议中
	ProtoMission::PushMissionReq * pushmission = new ProtoMission::PushMissionReq;
	int ret = VerifyMissionComplete(uid, param, pushmission->mutable_missions());

	if (ret || 0 == pushmission->missions().missions_size())  //没有任务推送时，释放内存
	{
		delete pushmission;
		return 0;
	}

	LogicManager::Instance()->sendMsg(uid, pushmission);

	return 0;
}

int LogicMissionManager::VerifyMissionComplete(unsigned uid, MissionParam & param, ProtoMission::MissionAllCPP * missions)
{
	MissionConfigWrap missionConfig;
	MissionConfigWrap::MissionBase misconfigbase;

	//从数据库中取出未完成的任务
	vector<unsigned> vctIndexs;
	DataMissionManager::Instance()->GetUnDoneMission(uid, vctIndexs);

	int ret = 0;

	try
	{
		for(int i = 0; i < vctIndexs.size(); ++i)
		{
			DataMission & datamission = DataMissionManager::Instance()->GetMissionByIndex(vctIndexs[i]);

			if (datamission.status)   //任务已完成的，将不再做推送
			{
				continue;
			}

			ret = missionConfig.GetMissionBase(datamission.id, misconfigbase);

			if (ret)
			{
				error_log("[VerifyMissionComplete] get config error. uid=%u,mid=%u", uid, datamission.id);
				return R_ERROR;
			}

			if (misconfigbase.type != param.type)
			{
				continue;
			}

			VerifyMission(uid, param, datamission.id);
			//都要将校验结果返回给前端
			SetMissionMessage(datamission, missions->add_missions());
		}
	}
	catch (std::runtime_error & e)
	{
		error_log("[VerifyMissionComplete] exception:%s", e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicMissionManager::VerifyMission(unsigned uid, MissionParam & param, unsigned id)
{
	int ret = 0;

	switch(param.type)
	{
		case mission_type_first_login: ret = VerifyFirstLogin(uid, id); break;
		case mission_type_upgrade_building: ret = VerifyUpgradeBuild(uid, id); break;
		case mission_type_register: ret = VerifyRegister(uid, id); break;
		case mission_type_gate: ret = VerifyGate(uid, id); break;
		case mission_type_productivity: ret = VerifyProductivity(uid, id); break;
		case mission_type_pray: ret = VerifyPray(uid, id, param.subparam); break;    //需要调用者传来参数
		case mission_type_purchase: ret = VerifyPurchaseEquip(uid, id); break;  //需要调用者传来参数
		case mission_type_herodress: ret = VerifyDressEquip(uid, id); break;
		case mission_type_herohp_recover: ret = VerifyHeroHP(uid, id); break;
		case mission_type_tech_research: ret = VerifyTechResearch(uid, id); break;
		case mission_type_hegemony_kill: ret = VerifyHegemonyKillNum(uid, id); break;
		case mission_type_hegemony_feats: ret = VerifyHegemonyFeats(uid, id); break;
		case mission_type_recruit: ret = VerifyHeroRecruit(uid, id); break;
		case mission_type_autoupgrade : ret = VerifyAutoUpgrade(uid, id); break;
		case mission_type_hammer : ret = VerifyUseHammer(uid, id); break;
		case mission_type_character_buy: ret = VerifyCharacterBuy(uid, id); break;
		case mission_type_character_dress: ret = VerifyCharacterDress(uid, id); break;
		case mission_type_hero_upgrade : ret = VerifyHeroUpgrade(uid, id); break;
		case mission_type_num_dress : ret = VerifyNumDress(uid, id); break;
		case mission_type_governaffair: ret = VerifyGovernAffair(uid, id); break;
		case mission_type_open_exploitbox : ret = VerifyOpenExploitbox(uid, id); break;
		case mission_type_equipshop_refresh: ret = VerifyRefreshEquipshop(uid, id); break;
		case mission_type_foggate_success: ret = VerifyFogGateSuccess(uid, id); break;
		case mission_type_world_move: ret = VerifyWorldMove(uid, id); break;
		case mission_type_tech_done:  ret = VerifyTechDone(uid, id); break;
		default: break;
	}

	if (ret)
	{
		return ret;
	}

	return 0;
}

int LogicMissionManager::VerifyFirstLogin(unsigned uid, unsigned id)
{
	//不需要条件，进入这个过程就当完成
	//根据id取mission
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = 1;
	datamission.status = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyUpgradeBuild(unsigned uid, unsigned id)
{
	//升级指定建筑类型，到指定等级. 需额外参数指定建筑类型
	//查询表
	MissionConfigWrap missionConfig;
	const MissionConfig::TripleCondition & triplecondion = missionConfig.GetTripleCondition(id);
	vector<DBCBuildingData> vctBuilds;

	int buildtype = triplecondion.subtype();
	LogicBuildManager::Instance()->GetBuildingByType(uid, buildtype, vctBuilds);
	BuildCfgWrap buildCfg;

	int matchCount = 0;

	for(int i = 0; i < vctBuilds.size(); ++i)
	{
		//先排除各自的仓库
		const Building::Item& item = buildCfg.Item(vctBuilds[i].id);

		if (1 == item.type())  //排除type为1的仓库
		{
			continue;
		}

		//先查找等级
		if (vctBuilds[i].level >= triplecondion.level())   //大于等于条件的等级
		{
			++matchCount;
		}
	}

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);

	datamission.current = matchCount;

	if (datamission.current >= triplecondion.count())
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyRegister(unsigned uid, unsigned id)
{
	//不需要条件，进入这个过程就当完成
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = 1;
	datamission.status = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyGate(unsigned uid, unsigned id)
{
	//todo 查询闯关表，判断是否通过此关
	//获取条件，根据闯关id判断是否已通过此关
	//再获取指定id的配置条件
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	unsigned gateid = mission.single(mindex).condition();

	//接下来判断闯关数目
	int gatetimes = LogicNPCPassMgr::Instance()->GetNPCPassCnt(uid, gateid);

	if (gatetimes > 0)  //已通关
	{
		DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
		datamission.current = 1;
		datamission.status = 1;
		DataMissionManager::Instance()->UpdateMission(datamission);
	}

	return 0;
}

int LogicMissionManager::VerifyProductivity(unsigned uid, unsigned id)
{
	//todo 查询当前资源产量
	//获取指定id的配置条件
	MissionConfigWrap missionConfig;
	const MissionConfig::DoubleCondition & doublecondion = missionConfig.GetDoubleConditon(id);

	//获得该类型的总产量
	int resourcetype = doublecondion.subtype();
	int productivity = LogicBuildManager::Instance()->Yields(uid, resourcetype);

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = productivity;

	if (datamission.current >= doublecondion.count())  //当前产量大于等于条件要求的产量
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyPray(unsigned uid, unsigned id, vector<int> &vctPray)
{
	//todo 祭祀，任务开启之后，接入祭祀接口.需额外参数，指定资源类型,以及免费和购买的次数
	//先判断参数是否合格
	if (vctPray.empty())
	{
		return R_ERR_PARAM;
	}

	//再获取指定id的配置条件
	MissionConfigWrap missionConfig;
	const MissionConfig::DoubleCondition & doublecondion = missionConfig.GetDoubleConditon(id);

	//判断子类型，即祭祀的资源类型是否一致
	if (doublecondion.subtype() != vctPray[0u])
	{
		return R_ERROR;
	}

	unsigned freetime = vctPray[1u];
	unsigned buytime =  vctPray[2u];

	//判断次数是否满足条件
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current += freetime;  //当前这一次祭祀也算在内
	datamission.current += buytime;

	if (datamission.current >= doublecondion.count())
	{
		datamission.status = 1;  //满足条件
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}
int LogicMissionManager::VerifyPurchaseEquip(unsigned uid, unsigned id)
{
	//todo 装备购买，任务开启之后，接入装备购买接口
	//modify:改为判断是否拥有该装备

	//获取指定id的配置条件
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();

	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;
	const  MissionConfig::AssembleMission&  assemecondition = mission.assemble(mindex);

	int maxsize = assemecondition.condition_size();

	vector<unsigned> vctEquipsIndex;
	EquipmentManager::Instance()->GetEquipments(uid, vctEquipsIndex);

	vector<unsigned> vctMatch;  //符合条件的下标

	//判断eqid是否在需求的列表中
	for(int i = 0; i < maxsize; ++i)
	{
		for(int j = 0; j < vctEquipsIndex.size(); ++j)
		{
			DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctEquipsIndex[j]);

			if (equip.eqid == assemecondition.condition(i))
			{
				vctMatch.push_back(i);
				break;
			}
		}
	}

	unsigned target = 0;

	LogicCommonUtil::GetTargetBitValue(maxsize, target);

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = 0;

	for(int i = 0; i < vctMatch.size(); ++i)
	{
		//将当前满足的条件写入current中
		LogicCommonUtil::SetBitCurrent(datamission.current, vctMatch[i]);
	}

	if (target == datamission.current)   //任务条件全都满足
	{
		datamission.status = 1;  //满足条件
	}

	DataMissionManager::Instance()->UpdateMission(datamission);
	return 0;
}

int LogicMissionManager::VerifyDressEquip(unsigned uid, unsigned id)
{
	//todo 指定英雄个数，指定每个英雄都穿戴装备
	//查询英雄身上的装备
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();

	//判断eqid是否在需求的列表中
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;
	int heros = mission.assemble(mindex).condition(0);  //要求满足的英雄个数

	vector<unsigned> conditionVec;
	int maxsize = mission.assemble(mindex).condition_size() - 1;

	for(int i = 1; i < mission.assemble(mindex).condition_size(); ++i)   //跳过第一个表示英雄个数的字段
	{
		unsigned eqid = mission.assemble(mindex).condition(i);
		conditionVec.push_back(eqid);
	}

	//查询上阵英雄
	vector<DataHero> vctHeros;
	DataHeroManager::Instance()->GetRecruitHero(uid, vctHeros);
	vector<unsigned> vctMatch;  //符合条件的下标

	for(int i = 0; i < vctHeros.size(); ++i)
	{
		vector<DataEquipment> vctEquips;

		EquipmentManager::Instance()->GetHeroEquips(uid, vctHeros[i].heroid, vctEquips);

		vector<unsigned> matchtemp;

		for(int j = 0; j < conditionVec.size(); ++j)
		{
			//判断eqid是否在条件中

			for(int k = 0; k < vctEquips.size(); ++k)
			{
				if (conditionVec[j] == vctEquips[k].eqid)
				{
					matchtemp.push_back(j);
					break;
				}
			}
		}

		if (vctMatch.size() < matchtemp.size()) //符合条件个数，以匹配度高的优先
		{
			vctMatch = matchtemp;
		}
	}

	unsigned target = 0;
	LogicCommonUtil::GetTargetBitValue(maxsize, target);

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = 0;

	for(int i = 0; i < vctMatch.size(); ++i)
	{
		LogicCommonUtil::SetBitCurrent(datamission.current, vctMatch[i]);
	}

	if (datamission.current == target)
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyHeroHP(unsigned uid, unsigned id)
{
	//todo 查询当前英雄是否满血
	vector<DataHero> vctHeros;
	DataHeroManager::Instance()->GetRecruitHero(uid, vctHeros);

	if (0 == vctHeros.size())
	{
		return R_ERROR;
	}

	bool isFull = false;

	//找出第一顺位的英雄，等级最高，然后heroid最大
	unsigned firstIndex = 0;

	for(int i = 1; i < vctHeros.size(); ++i)
	{
		//等级优先
		if (vctHeros[i].level > vctHeros[firstIndex].level)
		{
			firstIndex = i;
		}
		else if (vctHeros[i].level == vctHeros[firstIndex].level)  //等级相同，则比较heroid
		{
			if (vctHeros[i].heroid > vctHeros[firstIndex].heroid)   //取大的heroid
			{
				firstIndex = i;
			}
		}
	}

	//只判断第一顺位的英雄血量
	if(LogicHeroManager::Instance()->IsHeroFullHP(uid, vctHeros[firstIndex].heroid))
	{
		isFull = true;
	}

	if (!isFull)  //条件不满足
	{
		return R_ERROR;
	}

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);

	datamission.status = 1;
	datamission.current = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyTechResearch(unsigned uid, unsigned id)
{
	//todo 查询是否研究指定科技
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	unsigned scienceid = mission.single(mindex).condition();

	bool isResearch = LogicScienceMgr::Instance()->IsScienceBeginResearch(uid, scienceid);

	if (isResearch)  //已开始研究
	{
		DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
		datamission.status = 1;

		DataMissionManager::Instance()->UpdateMission(datamission);
	}

	return 0;
}

int LogicMissionManager::VerifyHegemonyKillNum(unsigned uid, unsigned id)
{
	//todo 任务开启之后，即可进行校验
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	if ( ConfigManager::Instance()->m_mapMissonIndex[id].first != mission_condition_single)
	{
		error_log("[VerifyHegemonyKillNum] wrong mission conditon type.uid=%u,id=%u,should=%u", uid, id, mission_condition_single);
		return 0;
	}

	unsigned kill_condtion = mission.single(mindex).condition();

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = GET_RMI(uid).kill;

	if (datamission.current >= kill_condtion)
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyHegemonyFeats(unsigned uid, unsigned id)
{
	//todo 任务开启之后，即可进行校验
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	if ( ConfigManager::Instance()->m_mapMissonIndex[id].first != mission_condition_single)
	{
		error_log("[VerifyHegemonyFeats] wrong mission conditon type.uid=%u,id=%u,should=%u", uid, id, mission_condition_single);
		return 0;
	}

	unsigned reward_condtion = mission.single(mindex).condition();

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = GET_RMI(uid).reward;

	if (datamission.current >= reward_condtion)
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyHeroRecruit(unsigned uid, unsigned id)
{
	//todo 英雄招募验证
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	unsigned heroid = mission.single(mindex).condition();
	//先查询上阵英雄
	vector<DataHero> vctHeros;
	DataHeroManager::Instance()->GetRecruitHero(uid, vctHeros);

	//暂时当前进度只记录满足的英雄个数
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	bool isHave = false;

	for(int i = 0; i < vctHeros.size(); ++i)
	{
		if (heroid == vctHeros[i].heroid)
		{
			isHave = true;
			break;
		}
	}

	if (isHave)
	{
		datamission.current = 1;
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyAutoUpgrade(unsigned uid, unsigned id)
{
	DBCBuildingQueueDataWrap dbcbuildqueue(uid);

	if (dbcbuildqueue.Obj().auto_cnt > 0)
	{
		//任务完成
		DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
		datamission.status = 1;
		datamission.current = 1;

		DataMissionManager::Instance()->UpdateMission(datamission);
	}

	return 0;
}

int LogicMissionManager::VerifyUseHammer(unsigned uid, unsigned id)
{
	//触发了，就算完成任务
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.status = 1;
	datamission.current = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyCharacterBuy(unsigned uid, unsigned id)
{
	//根据id获取任务的条件
	MissionConfigWrap missionConfig;
	const MissionConfig::DoubleCondition & doublecondion = missionConfig.GetDoubleConditon(id);

	unsigned character_condition = doublecondion.subtype();
	unsigned count_condition = doublecondion.count();

	//用户已购买的装备
	vector<unsigned> vctEquipsIndex;
	EquipmentManager::Instance()->GetEquipments(uid, vctEquipsIndex);

	int count = 0;
	//计算已购买的装备中，指定品质的装备是否达到条件数目
	EquipCfgWrap equipcfg;

	for(int j = 0; j < vctEquipsIndex.size(); ++j)
	{
		DataEquipment & equip = EquipmentManager::Instance()->GetEquipmentByIndex(vctEquipsIndex[j]);

		//根据eqid，获取当前装备的品质
		const EquipmentConfig::Equip & equipconfig = equipcfg.GetEquip(equip.eqid);

		//排除不是装备的普通道具
		if (!equipcfg.IsEquipment(equip.eqid))
		{
			continue;
		}

		if (equipconfig.character() == character_condition)
		{
			++count;

			if (count >= count_condition)
			{
				break;
			}
		}
	}

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = count;

	if (datamission.current >= count_condition)
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyCharacterDress(unsigned uid, unsigned id)
{
	//根据id获取任务的条件
	MissionConfigWrap missionConfig;
	const MissionConfig::DoubleCondition & doublecondion = missionConfig.GetDoubleConditon(id);

	unsigned character_condition = doublecondion.subtype();
	unsigned count_condition = doublecondion.count();

	//查询上阵英雄
	vector<DataHero> vctHeros;
	DataHeroManager::Instance()->GetRecruitHero(uid, vctHeros);

	int max_count = 0;

	for(int i = 0; i < vctHeros.size(); ++i)
	{
		vector<DataEquipment> vctEquips;

		EquipmentManager::Instance()->GetHeroEquips(uid, vctHeros[i].heroid, vctEquips);

		//判断eqid的品质是否在条件中
		int count_temp = 0;

		for(int j = 0; j < vctEquips.size(); ++j)
		{
			//根据eqid，获取当前装备的品质
			const EquipmentConfig::Equip & equipconfig = EquipCfgWrap().GetEquip(vctEquips[j].eqid);

			if (equipconfig.character() == character_condition)
			{
				++count_temp;
			}
		}

		if (max_count < count_temp) //符合条件个数，以匹配度高的优先
		{
			max_count = count_temp;
		}

		if (max_count >= count_condition)
		{
			break;
		}
	}

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = max_count;

	if (datamission.current >= count_condition)
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyHeroUpgrade(unsigned uid, unsigned id)
{
	//获取指定id的配置条件
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();

	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	unsigned contion_level = mission.single(mindex).condition();

	//获取正在招募的英雄
	vector<unsigned>  vHeroIndexs;
	DataHeroManager::Instance()->GetRecruitHero(uid, vHeroIndexs);
	bool isHave = false;

	for(unsigned i = 0; i < vHeroIndexs.size(); ++i)
	{
		DataHero& hero = DataHeroManager::Instance()->GetHeroByIndex(vHeroIndexs[i]);

		if (hero.level >= contion_level)
		{
			isHave = true;
			break;
		}
	}

	if (isHave)
	{
		DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
		datamission.status = 1;
		datamission.current = 1;
		DataMissionManager::Instance()->UpdateMission(datamission);
	}

	return 0;
}

int LogicMissionManager::VerifyNumDress(unsigned uid, unsigned id)
{
	//根据id获取任务的条件
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	unsigned condition_num = mission.single(mindex).condition();

	//查询上阵英雄
	vector<DataHero> vctHeros;
	DataHeroManager::Instance()->GetRecruitHero(uid, vctHeros);

	int max_count = 0;

	for(int i = 0; i < vctHeros.size(); ++i)
	{
		vector<unsigned> vctEquips;
		EquipmentManager::Instance()->GetHeroEquipment(uid, vctHeros[i].heroid, vctEquips);

		max_count += vctEquips.size();

		if (max_count >= condition_num)  //满足条件后，就不再进行遍历
		{
			break;
		}
	}

	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.current = max_count;

	if (datamission.current >= condition_num)
	{
		datamission.status = 1;
	}

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyGovernAffair(unsigned uid, unsigned id)
{
	//触发了，就算完成任务
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.status = 1;
	datamission.current = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyOpenExploitbox(unsigned uid, unsigned id)
{
	//触发了，就算完成任务
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.status = 1;
	datamission.current = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyRefreshEquipshop(unsigned uid, unsigned id)
{
	//触发了，就算完成任务
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.status = 1;
	datamission.current = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyFogGateSuccess(unsigned uid, unsigned id)
{
	bool isHaveSuccess = LogicFogGateManager::Instance()->IsHaveFogGateSuccess(uid);

	if (isHaveSuccess)  //成功通过迷雾战的任意关卡,任务完成
	{
		DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
		datamission.status = 1;
		datamission.current = 1;

		DataMissionManager::Instance()->UpdateMission(datamission);
	}

	return 0;
}

int LogicMissionManager::VerifyWorldMove(unsigned uid, unsigned id)
{
	//触发了，就算完成任务
	DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
	datamission.status = 1;
	datamission.current = 1;

	DataMissionManager::Instance()->UpdateMission(datamission);

	return 0;
}

int LogicMissionManager::VerifyTechDone(unsigned uid, unsigned id)
{
	//todo 是否指定科技研究完成
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;

	unsigned scienceid = mission.single(mindex).condition();

	bool isdone = LogicScienceMgr::Instance()->IsScienceDoneResearch(uid, scienceid);

	if (isdone)
	{
		DataMission & datamission = DataMissionManager::Instance()->GetMission(uid, id);
		datamission.status = 1;
		datamission.current = 1;

		DataMissionManager::Instance()->UpdateMission(datamission);
	}

	return 0;
}

int LogicMissionManager::SetMissionMessage(DataMission & datamission, ProtoMission::MissionCPP * msg)
{
	//根据任务id，获取任务类型
	MissionConfigWrap missionConfig;
	MissionConfigWrap::MissionBase misconfigbase;

	int ret = missionConfig.GetMissionBase(datamission.id, misconfigbase);

	if (ret)
	{
		error_log("[SetMissionMessage] get config error.uid=%u,mid=%u", datamission.uid, datamission.id);
		throw std::runtime_error("get_mission_config_error");
	}

	switch(misconfigbase.type)   //区分按位表示是否任务完成进度的和其他类型
	{
		case mission_type_herodress:
		case mission_type_purchase: SetSpecialMessage(datamission, msg);  break;

		default : datamission.SetMessage(msg); break;
	}

	return 0;
}

int LogicMissionManager::SetSpecialMessage(DataMission & datamission, ProtoMission::MissionCPP * msg)
{
	unsigned id = datamission.id;
	msg->set_id(id);
	msg->set_status(datamission.status);

	//根据id，找出总共的条件个数
	MissionConfigWrap missionConfig;
	const MissionConfig::Mission & mission = missionConfig.Mission().missions();

	//判断eqid是否在需求的列表中
	int mindex = ConfigManager::Instance()->m_mapMissonIndex[id].second;
	int maxsize = mission.assemble(mindex).condition_size();  //要求满足的英雄个

	//对穿装备区别对待，因为穿装备是英雄个数+要求装备，长度需减1
	if (mission.assemble(mindex).type() == mission_type_herodress)
	{
		maxsize -= 1;
	}

	for(int i = 0; i < maxsize; ++i)
	{
		//判断指定位数是否为0
		bool iszero = LogicCommonUtil::CheckPosIsZero(datamission.current, i);
		unsigned value = 0;

		if (iszero)
		{
			value = 0;
		}
		else
		{
			value = 1;
		}

		msg->add_current(value);
	}

	return 0;
}
