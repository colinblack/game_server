/*
 * UserManager.cpp
 *
 *  Created on: 2016-8-16
 *      Author: Ralf
 */

#include "UserManager.h"
#include "ProtoManager.h"

void UserManager::OnTimer2() {
	unsigned ts = LMI->GetTimerTS();
	if(ts % 600 == 0)
		CheckActive();
	else if(ts % 60 == 0)
		CheckClear();
	else
		CheckSave();
}

int UserManager::Process(unsigned uid, Common::ChangeName* msg, Common::ReplyChangeName* resp)
{
	string name = msg->name();
	String::Trim(name);
	if(name.empty() || !StringFilter::Check(name))
	{
		LogicManager::Instance()->SetErrMsg("name_fobbid");
		return R_ERR_PARAM;
	}

	string openid;
	int ret = m_dbName.AddName(name, openid, uid);
	if(ret)
	{
		LogicManager::Instance()->SetErrMsg("name_exist");
		return R_ERR_LOGIC;
	}

	OfflineResourceItem& rmi = GET_RMI(uid);
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];
	memset(base.name, 0, sizeof(base.name));
	strncpy(base.name, name.c_str(), BASE_NAME_LEN-1);
	BaseManager::Instance()->m_data->MarkChange(index);
	memset(rmi.name, 0, sizeof(rmi.name));
	strncpy(rmi.name, name.c_str(), BASE_NAME_LEN-1);

	resp->set_name(string(name));

	//todo 接入取名任务接口
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_register;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}
int UserManager::Process(Admin::AddCash* msg, Admin::ReplyAddCash* resp)
{
	unsigned uid = msg->uid();
	if(!IsOnline(uid))
		return R_ERR_LOGIC;
	int cash = msg->cash();

	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];
	if(cash < 0 && base.cash < unsigned(-cash))
		return R_ERR_LOGIC;
	COINS_LOG("[%s][uid=%u,ocash=%u,ncash=%u,chgcash=%d]", "ADMIN", uid, base.cash, base.cash+cash, cash);
	base.cash += cash;
	BaseManager::Instance()->m_data->MarkChange(index);

	resp->set_uid(uid);
	resp->set_cash(base.cash);

	return 0;
}
int UserManager::Process(unsigned uid, User::Tutorial_stage* msg)
{
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];
	base.tutorial_stage = msg->tutorial_stage();
	BaseManager::Instance()->m_data->MarkChange(index);
	return 0;
}

int UserManager::Process(Admin::AsycAdd* req, Admin::AsycAddResp* resp)
{
	std::string op = "ADMIN";
	for (int i = 0; i < req->item_size(); i++)
	{
		try
		{
			AsynItem item(req->item(i));
			if (IsOnline(item.uid))
			{
				DBCUserBaseWrap(item.uid).AddAsynItem(item.id, item.count, op);
			}
			else
			{
				AsynManager::Instance()->Add(item.uid, item.id, item.count);
			}
		}
		catch(const std::exception& e)
		{
			error_log("uid: %d, %s", req->item(i).uid(), e.what());
		}
	}

	if (resp)
	{
		resp->set_ret(0);
	}

	return R_SUCCESS;
}

int UserManager::Process(Admin::RequestForbidTS* req, Admin::ReplyForbidTS* resp)
{
	unsigned uid = req->uid();
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	if(index == -1)
		return R_ERR_NO_DATA;
	DataBase &base = BaseManager::Instance()->m_data->data[index];
	resp->set_forbid_ts(base.forbid_ts);
	resp->set_reason(base.forbid_reason);
	return 0;
}
int UserManager::Process(Admin::SetForbidTS* req)
{
	unsigned uid = req->uid();
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	if(index == -1)
		return R_ERR_NO_DATA;
	DataBase &base = BaseManager::Instance()->m_data->data[index];
	base.forbid_ts = req->forbid_ts();
	strncpy(base.forbid_reason, req->reason().c_str(),BASE_FORBID_REASON_LEN-1);
	BaseManager::Instance()->m_data->MarkChange(index);
	LMI->forceKick(uid, "forbid");
	return 0;
}

int UserManager::ProcessLogin(Common::Login* msg)
{
	//验证
	unsigned uid = msg->uid();
	unsigned ts = msg->ts();
	if(ts - 300 > Time::GetGlobalTime() || ts + 300 < Time::GetGlobalTime())
	{
		LogicManager::Instance()->SetErrMsg("login_ts_error");
		return R_ERR_PARAM;
	}
	if(!IsValidUid(uid))
	{
		LogicManager::Instance()->SetErrMsg("login_uid_error");
		return R_ERR_PARAM;
	}
	string suid = CTrans::UTOS(uid);
	string sts = CTrans::UTOS(ts);
	string sak(DAWX_RALF_KEY);
	string openkey = msg->openkey();
	string tsig = Crypt::Md5Encode(suid + openkey + sts + sak);
	string sig = msg->sig();
	if(sig != tsig)
	{
		LogicManager::Instance()->SetErrMsg("login_sig_error");
		return R_ERR_PARAM;
	}

	//顶号
	bool other = false;
	unsigned ofd = LMI->Getfd(uid);
	unsigned nfd = LMI->Getfd();
	unsigned ouid = LMI->Getuid(nfd);
	if(ouid != -1)
	{
		other = true;
		if(ouid != uid)
		{
			info_log("kick other login ouid, uid=%u, ouid=%u, ofd=%u, fd=%u", uid, ouid, ofd, nfd);
			LMI->offline(ouid);
		}
		LMI->Erasefd(nfd);
		LMI->Eraseuid(ouid);
	}
	if(ofd != -1)
	{
		other = true;
		if(ofd != nfd)
		{
			info_log("kick other login ofd, uid=%u, ouid=%u, ofd=%u, fd=%u", uid, ouid, ofd, nfd);
			LMI->sendKickMsg(ofd, "other_login");
		}
		LMI->Erasefd(ofd);
		LMI->Eraseuid(uid);
	}
	LMI->Addfd(uid, nfd);

	//加载
	int ret = 0;
	bool isNew = true;
	if(CheckUser(uid) == 0)
		isNew = false;
	if(isNew)
	{
		if(LogicManager::Instance()->IsDataManagerFull())
		{
			error_log("DataManagerFull!");
			return R_ERR_DATA;
		}
		ret = BaseManager::Instance()->LoadBuff(uid);
		if(ret == R_ERR_NO_DATA)
			ret = AddUser(uid);
		else if(ret == 0)
		{
			isNew = false;
			ret = LoadUser(uid);
		}

		if(ret)
		{
			LogicManager::Instance()->SetErrMsg("load_login_data_error");
			error_log("DataManager Error!");
			return ret;
		}
	}

	//封号
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];
	if(base.forbid_ts > Time::GetGlobalTime())
		return R_ERR_LOGIC;

	//登录
	if(m_infomap.count(uid))//一分钟内重新登录没有算做掉线，不用进行登录数据处理
	{
		m_infomap[uid] = *msg;
		if(!other)
			LogicManager::Instance()->EraseLeaveList(uid);
	}
/**************下面是登录数据处理,不应该在大括号外面有内容************************/
	else
	{
		m_infomap[uid] = *msg;
		if(isNew)
			ret = OnNewUser(uid, msg);
		else
			ret = OnUserLogin(uid, msg);

		if(ret)
		{
			LogicManager::Instance()->SetErrMsg("new_or_login_error");
			return ret;
		}
	}
/**************下面是写登录返回包的数据，数据处理应该在此前完成************************/
	User::User* reply = new User::User;
	reply->set_ts(Time::GetGlobalTime());
	base.SetMessage(reply->mutable_base());

	//todo: other data
	try
	{
		LogicBuildManager::Instance()->FullMessageInLogin(uid, reply->mutable_building());
		WMI->SetMessage(uid, reply->mutable_field());
		EquipShopManager::Instance()->FullMessage(uid, reply);
		EquipmentManager::Instance()->FullMessage(uid, reply);
		LogicHeroManager::Instance()->FullMessage(uid, reply->mutable_heroes());
		LogicMissionManager::Instance()->FullMessage(uid, reply->mutable_mission());
		LogicScienceMgr::Instance()->FullMessage(uid, reply->mutable_science());
		LogicYellowVipManager::Instance()->FullMessage(uid, reply->mutable_yellowvip());
		LogicWeaponsMgr::Instance()->FullMessage(uid, reply->mutable_weapon());
		LogicNPCPassMgr::Instance()->FullMessage(uid, reply->mutable_npcpass());
		WMI->SetMessage(uid, reply->mutable_reward());
		LogicCumulationLogicManager::Instance()->FullMessage(uid, reply->mutable_cumulation());
		reply->mutable_activity()->MergeFrom(ConfigManager::Instance()->activity.m_config);
		LogicOfficialMgr::Instance()->FullMessage(base, reply);
		//迷雾战
		LogicFogGateManager::Instance()->FullMessage(uid, reply->mutable_foggates());
		LogicMineMgr::Instance()->FullMessage(DBCUserBaseWrap(index, base), reply->mutable_mine());
		LogicDailyMissionManager::Instance()->FullMessage(uid, reply->mutable_dailymissions());
		//限时道具
		LogicTimeLimitPropMgr::Instance()->FullMessage(uid, reply->mutable_time_limit_props());
		//部件系统
		LogicComponentManager::Instance()->FullMessage(uid, reply->mutable_components());
		//部件产出
		LogicCompProduceManager::Instance()->FullMessage(uid, reply->mutable_producecomponent());
		//成就
		LogicAchievementManager::Instance()->FullMessage(uid, reply->mutable_achievements());
		//精英部队
		LogicEliteMilitaryManager::Instance()->FullMessage(reply->mutable_elitenpcs());
	}
	catch(const std::exception& e)
	{
		if (reply)
		{
			delete reply;
			reply = NULL;
		}

		error_log("uid=%u,%s", uid, e.what());

		LogicManager::Instance()->SetErrMsg(e.what());
		return R_ERROR;
	}

	LogicManager::Instance()->SetReplyProtocol(reply);

	info_log("user login, uid=%u, fd=%u, new=%u", uid, nfd, isNew?1:0);
	return 0;
}

int UserManager::CheckUser(unsigned uid)
{
	return BaseManager::Instance()->CheckBuff(uid);
}
int UserManager::AddUser(unsigned uid)
{
	int ret = BaseManager::Instance()->AddBuff(uid); if(ret) return ret;

	//@add oulong 20160905
	try
	{
		ret = DataBuildingManager::Instance()->New(uid);if(ret) return ret;
		ret = DataBuildQueue::Instance()->New(uid);if(ret) return ret;
	}
	catch(const std::exception& e)
	{
		error_log("uid:%u, %s", uid, e.what());
		return R_ERROR;
	}

	return 0;
}
int UserManager::LoadUser(unsigned uid)
{
	int ret = 0;
	//@add oulong 20160905
	try
	{
		ret = DataBuildingManager::Instance()->Load(uid);if(ret) return ret;
		ret = DataBuildQueue::Instance()->Load(uid);if(ret) return ret;
		ret = EquipShopManager::Instance()->LoadBuff(uid); if (ret && ret != R_ERR_NO_DATA) return ret;
		ret = EquipmentManager::Instance()->LoadBuff(uid);  if (ret && ret != R_ERR_NO_DATA) return ret;
		ret = DataNPCPassMgr::Instance()->LoadBuffer(uid); if(ret) return ret;
		ret = DataHeroManager::Instance()->LoadBuff(uid); if (ret && ret != R_ERR_NO_DATA) return ret;
		ret = DataMissionManager::Instance()->LoadBuff(uid);  if (ret && ret != R_ERR_NO_DATA) return ret;
		ret = DataYellowVipManager::Instance()->LoadBuff(uid);  if (ret && ret != R_ERR_NO_DATA) return ret;
		ret = DataCumulationLoginManager::Instance()->LoadBuff(uid); if(ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataNPCActivityManager::Instance()->LoadBuff(uid); if(ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataFogGateManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataDailyMissionManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataComponentManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataProduceComponentManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataAchievementManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataFriendManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataFriendGiftManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataShakeDiceManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
		ret = DataOperaBattleManager::Instance()->LoadBuff(uid); if (ret && R_ERR_NO_DATA != ret) return ret;
	}
	catch(const std::exception& e)
	{
		error_log("uid:%u, %s", uid, e.what());
		return R_ERROR;
	}

	return 0;
}

int UserManager::OnNewUser(unsigned uid, Common::Login* msg)
{
	ProtoManager::m_CurCMD = e_CMD_new;

	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];

	base.register_platform = msg->platform();
	base.register_time = Time::GetGlobalTime();
	base.last_login_platform = msg->platform();
	base.last_login_time = Time::GetGlobalTime();
	base.login_times = 1;
	base.login_days = 1;
	base.last_active_time = Time::GetGlobalTime();
	if(!msg->fig().empty())
		strncpy(base.fig, msg->fig().c_str(), sizeof(base.fig));
	base.kingdom = msg->kingdom();
	unsigned rc = 0;
	if(base.kingdom == 0)
	{
		rc = RAND_KINGDOM_CASH;
		base.kingdom = Math::GetRandomInt(SG17_KINGDOM) + 1;
	}

	const UserCfg::UserBase& userBaseCfg = UserCfgWrap().UserBase();
	base.level = userBaseCfg.level();
	//todo: new user init
	base.bag = ConfigManager::Instance()->bag.m_config.init();  //初始化背包格数
	base.up_res_time = Time::GetGlobalTime();
	//等级	经验		银币		木材		粮食		镔铁		金币
	//1		0		1000	1000	1000	1000	2100
	base.coin = userBaseCfg.coin();
	base.wood = userBaseCfg.wood();
	base.food = userBaseCfg.food();
	base.iron = userBaseCfg.iron();
	base.cash = userBaseCfg.cash() + rc;
	base.order = userBaseCfg.order();

	std::string op = "user_init";
	for (int i = 0; i < userBaseCfg.equips_size(); i++)
	{
		LogicEquipmentManager::Instance()
			->AddEquipment(uid, userBaseCfg.equips(i), op);
	}

	//整点/后勤领取次数
	base.integral_time_cnt = INTEGRA_TIME_CNT_INIT;

	base.ladder = PK_FIELD_CNT_INIT;

	BaseManager::Instance()->m_data->MarkChange(index);	

	try
	{
		LogicResourceManager::Instance()->Get(uid);
		//初始化装备商店
		LogicEquipShopManager::Instance()->EquipshopInit(uid);
		//初始化英雄
		LogicHeroManager::Instance()->NewUserInit(uid);
		//初始化任务
		LogicMissionManager::Instance()->NewUserInit(uid);

		//初始化黄钻
		LogicYellowVipManager::Instance()->NewUserInit(uid);

		//初始化累积登录
		LogicCumulationLogicManager::Instance()->NewUserInit(uid);

		//初始化广结名士活动数据
		NPCActivity::Instance()->NewUserInit(uid);

		//初始化每日任务
		LogicDailyMissionManager::Instance()->NewUserInit(uid);

		BattleRewardManager::Instance()->OnLogin(uid);

		//初始化部件产出数据
		LogicCompProduceManager::Instance()->NewUserInit(uid);

		//成就初始化
		LogicAchievementManager::Instance()->NewUserInit(uid);

		//好友管理初始化
		LogicFriendManager::Instance()->NewUserInit(uid);

		//摇骰子初始化
		LogicShakeDiceActivity::Instance()->NewUserInit(uid);
	}
	catch (const std::exception& e)
	{
		error_log("uid:%u, %s", uid, e.what());
		return R_ERROR;
	}

	return 0;
}

int UserManager::OnUserLogin(unsigned uid, Common::Login* msg)
{
	ProtoManager::m_CurCMD = e_CMD_login;

	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];

	int di = CTime::GetDayInterval(base.last_off_time, Time::GetGlobalTime());

	DBCUserBaseWrap(index, base).RefreshVIPLevel(false);
	if(di == 0)
	{
		//todo: today
	}
	else if(di > 0)
	{
		DBCUserBaseWrap user(index, base);
		user.EveryDayAction(di);
	}
	base.last_login_platform = msg->platform();
	base.last_login_time = Time::GetGlobalTime();
	base.last_active_time = Time::GetGlobalTime();
	if(!msg->fig().empty())
		strncpy(base.fig, msg->fig().c_str(), sizeof(base.fig));

	BaseManager::Instance()->m_data->MarkChange(index);	

	try
	{
		LogicResourceManager::Instance()->Online(uid);
		LogicTimeLimitPropMgr::Instance()->Online(uid);

		DBCUserBaseWrap user(index, base);
		user.RestoreResource();

		//结算异步数据之前，先要保证检查广结名士活动的数据
		NPCActivity::Instance()->LoginCheck(uid);

		user.FinalAsynData();
		user.ResetCountryTaskStatus(base.last_off_time);
		//装备商店登录检查
		LogicEquipShopManager::Instance()->LoginCheck(uid);
		//英雄是否存在于共享内存
		LogicHeroManager::Instance()->LoginHeroCheck(uid);
		//装备数据初始化处理，包括删除回购装备，设置当前用户的最大ud
		LogicEquipmentManager::Instance()->EquipLoginInit(uid);
		//募兵
		LogicHeroManager::Instance()->RecruitSoldiersByStartTime(uid, base.last_off_time);
		//免费洗练次数
		LogicEquipmentManager::Instance()->CalculateRefreshTimes(uid, base.last_off_time);
		//
		LogicScienceMgr::Instance()->Online(uid);
		LogicWeaponsMgr::Instance()->Online(uid);

		//任务登录检查
		LogicMissionManager::Instance()->LoginCheck(uid);

		//累积登录初始化
		LogicCumulationLogicManager::Instance()->LoginCheck(uid);

		//政务事件次数登录结算
		LogicUserManager::Instance()->LoginCheck(uid);

		//黄钻-空间礼包登录检查
		LogicYellowVipManager::Instance()->LoginCheck(uid);

		//限时商店
		LimitShop::Instance()->Online(uid);
		LogicHugeDiscount::Instance()->Online(uid);

		//迷雾战
		LogicFogGateManager::Instance()->LoginCheck(uid);
		//充值返现
		LogicCashBack::Instance()->Online(uid);
		//摸金校尉
		LogicTouchGold::Instance()->Online(uid);
		//每日任务
		LogicDailyMissionManager::Instance()->LoginCheck(uid);

		BattleRewardManager::Instance()->OnLogin(uid);

		//部件
		LogicComponentManager::Instance()->LoginCheck(uid);

		//部件产出
		LogicCompProduceManager::Instance()->LoginCheck(uid);

		//成就系统
		LogicAchievementManager::Instance()->LoginCheck(uid);

		//好友管理
		LogicFriendManager::Instance()->LoginCheck(uid);

		//摇骰子
		LogicShakeDiceActivity::Instance()->LoginCheck(uid);

		//杀敌活跃活动
		LogicEnlivenKillActivity::Instance()->LoginCheck(uid);

		//剧本战管理
		LogicOperaBattleManager::Instance()->LoginCheck(uid);
	}
	catch(const std::exception& e)
	{
		error_log("uid:%u, %s", uid, e.what());
		return R_ERROR;
	}

	return 0;
}
int UserManager::UserOffLine(unsigned uid)
{
	if(!m_infomap.count(uid))
		return R_ERR_PARAM;

	m_infomap.erase(uid);
	m_save.insert(uid);
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	if(index == -1)
		return R_ERR_DATA;
	DataBase &base = BaseManager::Instance()->m_data->data[index];

	//todo: offline
	base.last_off_time = Time::GetGlobalTime();
	BaseManager::Instance()->m_data->MarkChange(index);	

	try
	{
		DBCUserBaseWrap(uid).RestoreResource();
		LogicResourceManager::Instance()->Offline(uid);
		LogicScienceMgr::Instance()->Offline(uid);
		LogicWeaponsMgr::Instance()->Offline(uid);
		LogicTimeLimitPropMgr::Instance()->Offline(uid);
	}
	catch(const std::exception& e)
	{
		error_log("uid:%u, %s", uid, e.what());
		return R_ERROR;
	}

	return 0;
}
void UserManager::CheckActive()
{
	vector<unsigned> uids;
	for(map<unsigned, Common::Login>::iterator it=m_infomap.begin();it!=m_infomap.end();++it)
	{
		unsigned index = BaseManager::Instance()->GetIndex(it->first);
		if(index == -1)
			continue;
		if(BaseManager::Instance()->m_data->data[index].CanOff())
			uids.push_back(it->first);
	}
	for(vector<unsigned>::iterator it=uids.begin();it!=uids.end();++it)
	{
		info_log("kick not active, uid=%u, fd=%u", *it, LMI->Getfd(*it));
		LMI->forceKick(*it, "not_active");
	}
}
void UserManager::CheckSave()
{
	if(LogicManager::Instance()->IsDataManagerWorking())
		return;
	for(set<unsigned>::iterator it=m_save.begin();it!=m_save.end();++it)
		LogicManager::Instance()->DoDataManagerSave(*it);
	m_save.clear();
}
void UserManager::CheckClear()
{
	if(!LogicManager::Instance()->IsDataManagerWorking() && LogicManager::Instance()->IsDataManagerNeedClear())
	{
		vector<unsigned> uids;
		BaseManager::Instance()->GetClear(uids);
		for(vector<unsigned>::iterator it=uids.begin();it!=uids.end();++it)
			LogicManager::Instance()->DoDataManagerClear(*it);
	}
	if(LogicManager::Instance()->IsMemoryManagerNeedClear())
	{
		vector<unsigned> uids;
		ResourceManager::Instance()->GetClear(uids);
		for(vector<unsigned>::iterator it=uids.begin();it!=uids.end();++it)
			LogicManager::Instance()->DoMemoryManagerClear(*it);
		WorldManager::Instance()->DoClear();
	}
	if(AsynManager::Instance()->IsFull())
		AsynManager::Instance()->Clear();
}

int UserManager::ProcessBagAdd(BagLogic::PurchaseBagResp *msg, string & errmsg)
{
	unsigned uid = LogicManager::Instance()->Getuid();
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];

	uint16_t nowbag = base.bag;
	uint16_t initbag = ConfigManager::Instance()->bag.m_config.init();  //初始背包格数
	uint16_t maxbag = ConfigManager::Instance()->bag.m_config.max();  //最大背包格数

	if (nowbag < initbag)   //当前背包格数小于初始格数，数据不正常
	{
		error_log("[ProcessBagAdd] user's bag value error. less than init. now=%hu, init=%hu", nowbag, initbag);
		errmsg = "bag_init_error";
		return R_ERR_LOGIC;
	}

	if (nowbag >= maxbag)
	{
		error_log("[ProcessBagAdd] user's bag is max. now=%hu, max=%hu", nowbag, maxbag);
		errmsg = "bag_already_max";
		return R_ERR_LOGIC;
	}

	uint16_t addbagnum = nowbag - initbag;

	const BagConfig::Costs& cost = ConfigManager::Instance()->bag.m_config.costs(addbagnum);   //增加的背包格数作为下标，获取需要花费的银币
	int coin = cost.price();

	try
	{
		Json::Value result;
		LogicUserManager::Instance()->CostUserResource(uid, coin, 0, 0, 0, "Buy_Bag", result);
		base.bag = nowbag + 1;
		BaseManager::Instance()->m_data->MarkChange(index);

		msg->set_bag(nowbag + 1);
		msg->set_coin(result["coin"].asUInt());
	}
	catch(const std::exception& e)
	{
		errmsg = e.what();
		return R_ERROR;
	}

	return 0;
}

void UserManager::GetOnlineUsers(std::vector<unsigned>& users)
{
	users.clear();
	std::map<unsigned, Common::Login>::const_iterator it = m_infomap.begin();
	for (; it != m_infomap.end(); ++it)
	{
		users.push_back(it->first);
	}
}

void UserManager::AddRefresh()
{
	vector<unsigned> uids;
	GetOnlineUsers(uids);
	for (vector<unsigned>::iterator it=uids.begin();it!=uids.end();++it)
	{
		DataBase& base = BaseManager::Instance()->Get(*it);

		if (base.refresh >= LogicEquipmentManager::MAX_REFRESH_TIME)
		{
			continue;
		}

		base.refresh += 1;
		BaseManager::Instance()->UpdateDatabase(base);
	}
}

int UserManager::Process(Bot::RequestLogin* req)
{
	int result = R_SUCCESS;
	try
	{
		unsigned uid = req->uid();
		unsigned kingdom = req->kingdom();
		unsigned id = req->id();
		bool reload = req->reload();

		Common::Login msg;
		msg.set_uid(uid);
		msg.set_openkey("bot");
		msg.set_ts(0);
		msg.set_sig("bot");
		msg.set_fig(ConfigManager::Instance()->bot.m_config.fig());
		msg.set_isnew(false);
		msg.set_kingdom(kingdom);
		msg.set_platform(PT_TEST);
		msg.set_ttss_level(1);
		msg.set_ttss_level_name("");
		msg.set_ttss_grow_value(0);
		msg.set_is_blue_vip(1);
		msg.set_is_blue_year_vip(0);
		msg.set_is_super_blue_vip(0);
		msg.set_blue_vip_level(1);
		msg.set_is_yellow_vip(1);
		msg.set_is_yellow_year_vip(0);
		msg.set_yellow_vip_level(1);

		int ret = 0;
		bool isNew = true;
		if(CheckUser(uid) == 0)
			isNew = false;
		if(isNew)
		{
			if(LogicManager::Instance()->IsDataManagerFull())
			{
				error_log("DataManagerFull!");
				throw runtime_error("DataManagerFull");
			}
			ret = BaseManager::Instance()->LoadBuff(uid);
			if(ret == R_ERR_NO_DATA)
				ret = AddUser(uid);
			else if(ret == 0)
			{
				isNew = false;
				ret = LoadUser(uid);
			}

			if(ret)
			{
				error_log("DataManager Error!");
				throw runtime_error("DataManager Error");
			}
		}
		if(m_infomap.count(uid))
		{
			m_infomap[uid] = msg;
			BaseManager::Instance()->m_data->data[BaseManager::Instance()->GetIndex(uid)].last_active_time = Time::GetGlobalTime();
		}
		else
		{
			m_infomap[uid] = msg;
			if(isNew)
				ret = OnNewUser(uid, &msg);
			else
				ret = OnUserLogin(uid, &msg);

			if(ret)
				throw runtime_error("new_or_login_error");
		}

		OfflineResourceItem& rmi = GET_RMI(uid);
		if(id)
		{
			unsigned ui = BaseManager::Instance()->GetIndex(uid);
			DataBase &base = BaseManager::Instance()->m_data->data[ui];
			string name = ConfigManager::Instance()->GetBotName(id, kingdom, LMI->ServerId);
			memset(base.name, 0, sizeof(base.name));
			strncpy(base.name, name.c_str(), BASE_NAME_LEN-1);
			BaseManager::Instance()->m_data->MarkChange(ui);
			memset(rmi.name, 0, sizeof(rmi.name));
			strncpy(rmi.name, name.c_str(), BASE_NAME_LEN-1);

			int index;
			if(reload || isNew || base.forbid_ts == 0)
				index = ConfigManager::Instance()->GetBotIndex(id, CTime::GetDayInterval(LMI->SecOpenTime, Time::GetGlobalTime()));
			else
			{
				unsigned day1 = CTime::GetDayInterval(LMI->SecOpenTime, base.forbid_ts);
				unsigned day2 = CTime::GetDayInterval(LMI->SecOpenTime, Time::GetGlobalTime());
				index = ConfigManager::Instance()->NeedChangeBotAccount(id, day1, day2);
			}
			if(index != -1)
			{
				bool flag = true;
				set<HeroPropertyItemIndex> hero;
				HMI->GetHeros(uid, hero);
				for(set<HeroPropertyItemIndex>::iterator it=hero.begin();it!=hero.end();++it)
				{
					if(WMI->IsHeroFighting(*it) || WMI->IsHeroMoving(*it))
					{
						flag = false;
						break;
					}
				}
				if(flag)
				{
					const BotConfig::BotPlayer& bot = ConfigManager::Instance()->GetBotAccount(id, index);
					LogicUserManager::Instance()->SetBotPlayerData(uid, &bot);
					base.forbid_ts = Time::GetGlobalTime();
				}
			}
		}

		if(!reload)
		{
			rmi.is_atuo = true;
			uint16_t uc = BattleFieldManager::getCapital(rmi.kingdom);
			set<HeroPropertyItemIndex> heros;
			HMI->GetHeros(uid, heros);
			for(set<HeroPropertyItemIndex>::iterator it=heros.begin();it!=heros.end();++it)
			{
				if(!BattleFieldManager::isCapital(GET_HMI(*it).city))
					WMI->Fly(*it, uc);
			}

			if(Math::GetRandomInt(100) < 10)
			{
				string chat = ConfigManager::Instance()->GetBotChat();
				Bot::BotChat *msg = new Bot::BotChat;
				rmi.SetMessage(msg->mutable_info());
				msg->set_msg(chat);
				LMI->broadcastMsg(msg);
			}
		}

		//debug_log("uid=%u,reload=%d", uid, reload?1:0);
	}
	catch(runtime_error & e)
	{
		result = R_ERROR;
	}
	ProtoManager::m_CurCMD = e_CMD_none;
	return result;
}
int UserManager::Process(Bot::RequestLogout* req)
{
	unsigned uid = req->uid();

	if(!IsOnline(uid))
		return R_ERROR;

	LMI->offline(uid);

	return 0;
}

int UserManager::Process(unsigned uid, Common::ShutDown* msg)
{
	unsigned ts = msg->ts();
	if(ts - 300 > Time::GetGlobalTime() || ts + 300 < Time::GetGlobalTime())
		return R_ERR_PARAM;
	string suid = CTrans::UTOS(uid);
	string sts = CTrans::UTOS(ts);
	string tsig = Crypt::Md5Encode(suid + sts);
	string sign = msg->sign();
	if(sign != tsig)
		return R_ERR_PARAM;

	LogicManager::IsPreClosed = true;
	return 0;
}
