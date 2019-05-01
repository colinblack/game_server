#include "LogicEquipShopManager.h"

int LogicEquipShopManager::EquipshopInit(unsigned uid)
{
	int ret = R_SUCCESS;
	//先进行刷新，再将刷新后的结果写入数据库
	int ipool = 0;
	GetLevelPoolIndex(uid, ipool);

	for(int i = 1; i <= MAX_POSITION; ++i)
	{
		DataEquipShop equipshop;
		equipshop.uid = uid;
		equipshop.pid = i;
		equipshop.status = 1;
		int eindex = 0;
		ret = RefreshPart(equipshop, ipool, eindex);

		if (ret)
		{
			return ret;
		}

		ret = EquipShopManager::Instance()->AddEquipShop(equipshop);

		if (ret)
		{
			error_log("[EquipshopInit] add equipshop error. uid=%u", uid);
			return ret;
		}
	}

	return R_SUCCESS;
}

int LogicEquipShopManager::LoginCheck(unsigned uid)
{
	//检查装备商店数据是否加载进内存
	int ret = EquipShopManager::Instance()->CheckBuff(uid);

	if (ret)   //内存中没有数据，可能是没有从dbc中取出来
	{
		ret = EquipShopManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)
		{
			return EquipshopInit(uid);
		}
	}

	return ret;
}

int LogicEquipShopManager::Process(unsigned uid, EquipShopLogic::RefreshReq *reqmsg, EquipShopLogic::RefreshResp * respmsg)
{
	int ret = R_SUCCESS;
	//获取装备商店的CD时间
	unsigned uindex = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[uindex];
	unsigned now = Time::GetGlobalTime();

	ret = VerifyRefreshConditon(base, now);

	if (ret)
	{
		throw std::runtime_error("cd_time_not_ready");
	}

	int ipool = 0;
	GetLevelPoolIndex(uid, ipool);

	for(int i = 1; i <= MAX_POSITION; ++i)
	{
		unsigned index = 0;

		DataEquipShop & equipshop = EquipShopManager::Instance()->GetEquipShop(uid, i, index);
		equipshop.Clear();
		int eindex = 0;

		ret = RefreshPart(equipshop, ipool, eindex);

		if (ret)
		{
			throw std::runtime_error("refresh_error");
		}

		ret = EquipShopManager::Instance()->UpdateEquipShop(index);

		if (!ret)
		{
			error_log("[ProcessRefresh] update equipshop error. uid=%u", uid);
			throw std::runtime_error("update_eqshop_error");
		}
	}

	EquipShopManager::Instance()->FullMessage(uid, respmsg);

	//生成随机cd时间.在1min-3min之间
	unsigned randval =  Math::GetRandomInt(120) + 60;
	base.eshopcd += randval;

	ret = BaseManager::Instance()->m_data->MarkChange(uindex);

	if (!ret)
	{
		error_log("[ProcessRefresh] markchange error. uid=%u", uid);
		throw std::runtime_error("mark_change_error");
	}

	respmsg->set_cdtime(base.eshopcd);

	//todo 接入装备商店刷新任务,不计算极品刷新，所以没有挪到外部接口中
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_equipshop_refresh;

	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	//todo 装备商店刷新外部接口
	RefreshExternalInterface(uid);

	return 0;
}

int LogicEquipShopManager::Process(unsigned uid, EquipShopLogic::SuperRefreshReq *reqmsg, EquipShopLogic::SuperRefreshResp * respmsg)
{
	int ret = R_SUCCESS;

	unsigned now = Time::GetGlobalTime();

	int ipool = 0;
	GetLevelPoolIndex(uid, ipool);

	//扣钻
	int price = ConfigManager::Instance()->equipshop.m_config.levelpool(ipool).jpprice();
	unsigned newcash = 0;
	//扣钻石
	LogicUserManager::Instance()->CostCash(uid, price, "SUPER_REFRESH", newcash);

	respmsg->set_cash(newcash);

	int jppid = 0;

	DoSuperRefresh(uid, ipool, jppid);

	bool isAlljp = true;

	for(int i = 1; i <= MAX_POSITION; ++i)
	{
		if (jppid == i)  //该部位已经刷新过，不再刷新
		{
			continue;
		}

		int pid = i;
		//判断是否是全极品
		for(int i = 0; i < ConfigManager::Instance()->equipshop.m_config.levelpool(ipool).positions(pid-1).equips_size(); ++i)
		{
			if (!ConfigManager::Instance()->equipshop.m_config.levelpool(ipool).positions(pid-1).equips(i).isjp())   //非极品时成立
			{
				isAlljp = false;
				break;
			}
		}

		unsigned index = 0;
		DataEquipShop & equipshop = EquipShopManager::Instance()->GetEquipShop(uid, pid, index);

		while(true)
		{
			equipshop.Clear();
			int eindex = 0;

			RefreshPart(equipshop, ipool, eindex);
			//判断刚刷出来的是否是极品
			if (ConfigManager::Instance()->equipshop.m_config.levelpool(ipool).positions(pid -1).equips(eindex).isjp())
			{
				//判断是否全是极品，如果是，只能取该装备
				if (isAlljp)
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		ret = EquipShopManager::Instance()->UpdateEquipShop(index);

		if (!ret)
		{
			error_log("[ProcessSuperRefresh] update equipshop error. uid=%u", uid);
			throw std::runtime_error("update_eqshop_error");
		}
	}

	EquipShopManager::Instance()->FullMessage(uid, respmsg);

	//todo 装备商店刷新外部接口
	RefreshExternalInterface(uid);

	return 0;
}

int LogicEquipShopManager::RefreshExternalInterface(unsigned uid)
{
	//todo 接入装备商店刷新每日任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_refresheqshop;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	return 0;
}

int LogicEquipShopManager::DoSuperRefresh(unsigned uid, int ipool, int &jppid)
{
	//先随机部位
	int randval = Math::GetRandomInt(MAX_POSITION) + 1;
	jppid = randval;

	//找出该部位的极品eqid
	int eindex = -1;

	vector<unsigned> vctjprate;
	vector<int> vctIndexs;

	const EquipmentShopConfig::EquipPositionPool& equipool = ConfigManager::Instance()->equipshop.m_config.levelpool(ipool).positions(jppid-1);
	for(int i = 0; i < equipool.equips_size(); ++i)
	{
		if (equipool.equips(i).isjp())
		{
			vctIndexs.push_back(i);
			int rate = equipool.equips(i).rate();
			vctjprate.push_back(rate);
		}
	}

	if (0 == vctjprate.size())   //库中没有极品装备，拿第一件
	{
		eindex = 0;
	}
	else
	{
		//在极品内，再随机
		int target = 0;
		LogicCommonUtil::TurnLuckTable(vctjprate, vctjprate.size(), target);
		eindex = vctIndexs[target];
	}

	unsigned index = 0;  //uid->pid
	DataEquipShop & equipshop = EquipShopManager::Instance()->GetEquipShop(uid, jppid, index);
	equipshop.Clear();

	equipshop.eqid = ConfigManager::Instance()->equipshop.m_config.levelpool(ipool).positions(jppid -1).equips(eindex).eqid();

	//生成装备的随机属性，如果该物品是装备的话
	GenerateSub(equipshop);
	//get出来index
	int ret = EquipShopManager::Instance()->UpdateEquipShop(index);

	if (!ret)
	{
		error_log("[DoSuperRefresh] update equipshop error. uid=%u", uid);
		throw std::runtime_error("update_eqshop_error");
	}

	return 0;
}

int LogicEquipShopManager::Process(unsigned uid, EquipShopLogic::CutRefreshReq *reqmsg, EquipShopLogic::CutRefreshResp *respmsg)
{
	int ret = R_SUCCESS;

	unsigned uindex = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[uindex];
	//先获得剩余的cd时间，然后计算钻石数
	unsigned now = Time::GetGlobalTime();

	if (now > base.eshopcd)
	{
		base.eshopcd = now;
	}

	int diff_time = base.eshopcd - now;
	int cash = 0;
	unsigned newcash = 0;

	int per = 5*60;  //5*1分钟 = 1单位
	double divtimes = diff_time/static_cast<double>(per);

	int clearprice = ConfigManager::Instance()->equipshop.m_config.clearcdprice();

	cash = (int) ceil(divtimes) * clearprice;
	//扣钻石
	LogicUserManager::Instance()->CostCash(uid, cash, "ESHOP_CUTCD", newcash);
	//获取装备商店的CD时间
	base.eshopcd = now;

	int cdtime = 0;
	respmsg->set_cdtime(base.eshopcd);
	respmsg->set_cash(newcash);

	return 0;
}

int LogicEquipShopManager::Process(unsigned uid, EquipShopLogic::PurchaseEquipReq *reqmsg, EquipShopLogic::PurchaseEquipResp *respmsg)
{
	uint8_t pid = reqmsg->pid();
	unsigned eqid = reqmsg->eqid();
	unsigned index = 0;

	DataEquipShop & equipshop = EquipShopManager::Instance()->GetEquipShop(uid, pid, index);

	//判断pid中的eqid是否与参数的eqid相同
	if (equipshop.eqid != eqid)
	{
		error_log("[ProcessBuy] eqid is not same. param_eqid=%u, memory_eqid=%u", eqid, equipshop.eqid);
		throw std::runtime_error("param_error");
	}

	int price = EquipCfgWrap().GetEquipPrice(eqid);

	Json::Value result;
	result["coin"] = 0;
	LogicUserManager::Instance()->CostUserResource(uid, price, 0, 0, 0, "ESHOP_BUY_EQUIPMENT", result);

	respmsg->set_coin(result["coin"].asUInt());
	EquipShopConfigWrap equipshopcfg;
	DBCUserBaseWrap userwrap(uid);

	if (equipshopcfg.IsOrder(equipshop.eqid))  //募兵令
	{
		int num = equipshopcfg.GetNumByEqid(equipshop.eqid);
		userwrap.AddRecruitProp(num, "ESHOP_BUY");
	}
	else if (equipshopcfg.IsIron(equipshop.eqid))  //黄金
	{
		int num = equipshopcfg.GetNumByEqid(equipshop.eqid);
		userwrap.AddResource(0, 0, 0, num, "ESHOP_BUY");
	}
	else   //正常的装备
	{
		PurChaseEquip(uid, equipshop, respmsg);
	}

	userwrap.Save();
	respmsg->set_order(userwrap.Obj().order);
	respmsg->set_iron(userwrap.Obj().iron);

	equipshop.status = 0;

	int ret = EquipShopManager::Instance()->UpdateEquipShop(index);

	if (!ret)
	{
		error_log("[PurchaseEquipReq] update equipshop error. uid=%u, eqid=%u", uid, eqid);
		throw std::runtime_error("save_equipshop_error");
	}

	for(int i = 1; i <= MAX_POSITION; ++i)
	{
		DataEquipShop & equipshop = EquipShopManager::Instance()->GetEquipShop(uid, i, index);

		DataCommon::EquipShopCPP * pmsg = respmsg->add_equippool();
		equipshop.SetMessage(pmsg);
	}

	return 0;
}

int LogicEquipShopManager::PurChaseEquip(unsigned uid, DataEquipShop & equipshop, EquipShopLogic::PurchaseEquipResp *respmsg)
{
	//添加装备
	DataEquipment equip;
	equip.uid = equipshop.uid;
	equip.eqid = equipshop.eqid;
	equip.num = 1;

	//获取星级
	EquipCfgWrap equipconfig;
	equip.star = equipconfig.GetEquip(equipshop.eqid).star();

	for(int i = 0; i < MAX_STAR_NUM; ++i)
	{
		switch(i)
		{
			case 0: equip.subt1 = equipshop.subt1; if (equip.subt1 != 0) equip.sublv1 = 1; break;
			case 1: equip.subt2 = equipshop.subt2; if (equip.subt2 != 0)  equip.sublv2 = 1; break;
			case 2: equip.subt3 = equipshop.subt3; if (equip.subt3 != 0) equip.sublv3 = 1; break;
			case 3: equip.subt4 = equipshop.subt4; if (equip.subt4 != 0) equip.sublv4 = 1; break;
			default: break;
		}
	}

	LogicEquipmentManager::Instance()->AddEqupmentUnderlying(equip, "EquipShop", respmsg->mutable_equip());
	//todo 接入任务接口
	LogicMissionManager::MissionParam missionparam;
	missionparam.type = mission_type_purchase;

	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	//指定品质的装备购买
	missionparam.type = mission_type_character_buy;
	LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	return 0;
}

int LogicEquipShopManager::Process(unsigned uid, EquipShopLogic::ExchangeWingmanReq *reqmsg, EquipShopLogic::ExchangeWingmanResp *respmsg)
{
	unsigned eqid = reqmsg->eqid();

	WingManExchange(uid, eqid, respmsg);

	return 0;
}

int LogicEquipShopManager::WingManExchange(unsigned uid, unsigned eqid, EquipShopLogic::ExchangeWingmanResp * respmsg)
{
	//首先判断是否是僚机的eqid，如果不是，则不处理
	int price = 0;

	switch(eqid)
	{
		case e_WingManID_1: price = price_wingman_1; break;
		case e_WingManID_2: price = price_wingman_2; break;
		case e_WingManID_3: price = price_wingman_3; break;
		case e_WingManID_4: price = price_wingman_4; break;
		case e_WingManID_5:
		case e_WingManID_6:
		case e_WingManID_7:
		case e_WingManID_8:
		case e_WingManID_9:
			price = price_wingman_5;
			break;

		default: error_log("not wingman. uid=%u,eqid=%u", uid, eqid); throw runtime_error("should_be_wingman"); break;
	}

	//判断当前是否已拥有该僚机，包括已装备和未装备
	bool ishave = LogicEquipmentManager::Instance()->IsHaveTheWingman(uid, eqid);

	if (ishave)
	{
		error_log("The wingman already have. uid=%u,eqid=%u", uid, eqid);
		throw runtime_error("already_have_thiswingman");
	}

	//扣除积分
	DBCUserBaseWrap userwrap(uid);
	userwrap.CostTicket(price, "WingMan_Exchange");

	respmsg->set_ticket(userwrap.Obj().ticket);

	//添加僚机
	LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, 1, "WingMan_Exchange", respmsg->mutable_equips());

	return 0;
}

int LogicEquipShopManager::VerifyRefreshConditon(DataBase & base, unsigned now)
{
	//获取装备商店的CD时间
	int maxcdtime = 30*60;

	if (now > base.eshopcd)
	{
		base.eshopcd = now;
	}

	int diff_time = base.eshopcd - now;

	if (diff_time > maxcdtime)
	{
		error_log("[VerifyRefreshConditon] eshop is in cd. uid=%u,cd=%u", base.uid, diff_time);
		return R_ERR_LOGIC;
	}

	return R_SUCCESS;
}

int LogicEquipShopManager::RefreshPart(DataEquipShop & equipshop, int lindex, int & eindex)
{
	//从配置文件中获取ipool的pid部位的所有装备
	//status,eqid,subs,所以只需知道eqid
	const EquipmentShopConfig::EquipPositionPool & equippools = ConfigManager::Instance()->equipshop.m_config.levelpool(lindex).positions(equipshop.pid - 1);

	vector<unsigned> vctrate;
	map<unsigned, unsigned> map_eqindex;

	for(int i = 0; i < equippools.equips_size(); ++i)
	{
		const EquipmentShopConfig::Equip & equip = equippools.equips(i);

		unsigned rate = equip.rate();
		unsigned eqid = equip.eqid();

		vctrate.push_back(rate);

		map_eqindex.insert(make_pair(i, eqid));
	}

	int target = 0;
	LogicCommonUtil::TurnLuckTable(vctrate, equippools.equips_size(), target);

	if (!map_eqindex.count(target))
	{
		error_log("[RefreshPart] refresh error. uid=%u", equipshop.uid);
		return R_ERROR;
	}

	eindex = target;
	unsigned eqid = map_eqindex[target];
	equipshop.eqid = eqid;

	//生成装备的随机属性，如果该物品是装备的话
	GenerateSub(equipshop);

	return 0;
}

int LogicEquipShopManager::GenerateSub(DataEquipShop & equipshop)
{
	//todo 对募兵令和黄金，不产生sub属性
	EquipShopConfigWrap equipshopcfg;
	if (equipshopcfg.IsOrder(equipshop.eqid) || equipshopcfg.IsIron(equipshop.eqid))
	{
		return 0;
	}

	EquipCfgWrap equipconfig;
	int star = equipconfig.GetEquip(equipshop.eqid).star();

	for(int i = 0 ; i < star; ++i)
	{
		unsigned randomval = Math::GetRandomInt(property_type_strong_defend) + 1;

		switch(i)
		{
			case 0: equipshop.subt1 = randomval; break;
			case 1: equipshop.subt2 = randomval; break;
			case 2: equipshop.subt3 = randomval; break;
			case 3: equipshop.subt4 = randomval; break;
			default: break;
		}
	}

	return 0;
}

int LogicEquipShopManager::GetLevelPoolIndex(unsigned uid, int & ipool)
{
	//先获得用户等级
	unsigned index = BaseManager::Instance()->GetIndex(uid);
	DataBase &base = BaseManager::Instance()->m_data->data[index];

	//获取等级库的索引
	int ipooltemp = -1;

	for(int i = 0; i < POOL_ITEMS_MAX; ++i)
	{
		uint8_t minlevel = ConfigManager::Instance()->equipshop.m_config.levelpool(i).level();

		if (minlevel > base.level)
		{
			ipooltemp = i - 1;
			break;
		}
	}

	if (-1 == ipooltemp)  //循环正常终止
	{
		ipooltemp = POOL_ITEMS_MAX - 1;
	}

	ipool = ipooltemp;

	return 0;
}
