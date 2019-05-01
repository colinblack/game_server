/*
 * LogicResourceManager.cpp
 *
 *  Created on: 2016-9-10
 *      Author: dawx62fac
 */


#include "LogicResourceManager.h"



////////////////////////////////////////////////////////////////////////////
OfflineResourceItem& LogicResourceManager::Get(unsigned uid)
{
	int index = ResourceManager::Instance()->GetIndex(uid);
	if (index < 0)
	{
		DataBase& userBase = BaseManager::Instance()->Get(uid);
		index = this->Sync(userBase);
	}

	return ResourceManager::Instance()->m_data->item[index];
}

int LogicResourceManager::Sync(const DataBase& userBase)
{
	unsigned uid = userBase.uid;
	int index = ResourceManager::Instance()->GetIndex(uid);
	if (index  < 0)
	{
		int ret = ResourceManager::Instance()->Add(uid);
		if (ret != R_SUCCESS)
		{
			throw std::runtime_error("data_error");
		}

		index = ResourceManager::Instance()->GetIndex(uid);
		if (index < 0)
		{
			throw std::runtime_error("data_error");
		}
	}

	OfflineResourceItem& item = ResourceManager::Instance()->m_data->item[index];
	//同步需要的数据
	item.property[DemoOfflineProperty_chp]
				  = LogicBuildManager::Instance()->RecruitRate(uid);
	item.property[DemoOfflineProperty_u_level]
				 = userBase.level;
	LogicScienceMgr::Instance()->Sync(uid, item);

	//用户数据
	item.kingdom = userBase.kingdom;
	memcpy(item.fig, userBase.fig, BASE_FIG_LEN);
	memcpy(item.name, userBase.name, BASE_NAME_LEN);
	item.viplevel = userBase.viplevel;

	//官职数据
	OfficialDepartment* depart_ptr =
			OfficialManager::Instance()->GetDepartmentByUid(userBase.kingdom, uid);
	if (depart_ptr != NULL)
	{
		item.aid = depart_ptr->Type();
		Official* official_ptr = depart_ptr->GetOfficialByUid(uid);
		item.job = official_ptr != NULL ? official_ptr->Job() : 0;
	}
	else
	{
		item.aid = 0;
		item.job = 0;
	}

	item.ts = Time::GetGlobalTime();

	return index;
}

unsigned LogicResourceManager::GetRechargePays(unsigned uid, unsigned time)
{
	OfflineResourceItem& attr = Get(uid);
	for (int i = 0; i < RMI_PAY_HIS; i++)
	{
		if (attr.payHis[i].IsSameDay(time))
		{
			return attr.payHis[i].pay;
		}
	}

	return 0;
}

const OfflineResourceItem& LogicResourceManager::AddExploit(unsigned uid, int exploit)
{
	OfflineResourceItem& attr = Get(uid);

	if (exploit < 0)
	{
		error_log("params_error. uid=%u, exploit=%d", uid, exploit);
		exploit = 0;
	}


	int level = LogicScienceMgr::Instance()->GetExploitBoxLevel(uid);
	int add_box = attr.CalcAddExplotBox(attr.reward, level, exploit);
	attr.reward += exploit;

	//
	try
	{
		DBCUserBaseWrap user(uid);
		user.AddExploitBox(add_box);
	}
	catch(const std::exception& e)
	{
		if (std::string(e.what()) == "get_user_data_error")
		{
			attr.rewardb += add_box;
		}
	}

	attr.ts = Time::GetGlobalTime();

	return attr;
}

void LogicResourceManager::SyncUserLevel(unsigned uid, unsigned level)
{
	OfflineResourceItem& item = this->Get(uid);
	item.property[DemoOfflineProperty_u_level] = level;

	item.ts = Time::GetGlobalTime();
}

void LogicResourceManager::SyncRecruitRate(unsigned uid, unsigned rate)
{
	OfflineResourceItem& item = this->Get(uid);
	item.property[DemoOfflineProperty_chp] = rate;

	item.ts = Time::GetGlobalTime();
}

void LogicResourceManager::SyncPropertyValue(unsigned uid, DemoOfflineProperty prop, unsigned value)
{
	if ((int)prop < 0 || prop >= DemoOfflineProperty_max)
	{
		error_log("uid:%u, prot:%d", uid, prop);
		throw std::runtime_error("params_error");
	}

	OfflineResourceItem& item = this->Get(uid);
	item.property[prop] = value;

	item.ts = Time::GetGlobalTime();
}


void LogicResourceManager::Sync(unsigned uid, BattleReward& r, unsigned rewardb)
{
	try
	{
		DBCUserBaseWrap user(uid);
		user.FinalBattleReward(r);
		user.AddExp(r.exp);
		user.AddExploitBox(rewardb);

		LogicHeroManager::Instance()->FinalData(uid, r);

		for(map<unsigned, unsigned>::iterator it=r.item.begin();it!=r.item.end();++it)
			user.AddAsynItem(it->first, it->second, "BattleReward");
	}
	catch(const std::exception& e)
	{
		(void)e;
	}
}
void LogicResourceManager::Online(unsigned uid)
{
	try
	{
		OfflineResourceItem& src = this->Get(uid);
		DBCUserBaseWrap user(uid);
		if (user.FinalOfflineResource(src))
		{
			src.ResetProductResource();
		}

		if (user.AddExp(src.exp))
		{
			src.exp = 0;
		}

		user.AddExploitBox(src.rewardb);
		src.rewardb = 0;

		//结算英雄数据
		if (LogicHeroManager::Instance()->FinalData(uid, src.hexp))
		{
			src.ResetHexp();
		}


		src.ts = Time::GetGlobalTime();
	}
	catch(const std::exception& e)
	{
		(void)e;
	}
}

void LogicResourceManager::Offline(unsigned uid)
{
	try
	{
		OfflineResourceItem& src = this->Get(uid);
		src.cfood = BaseManager::Instance()->Get(uid).food;
		src.ts = Time::GetGlobalTime();
	}
	catch(const std::exception& e)
	{
		(void)e;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
int LogicResourceManager::Process(unsigned uid, ProtoResource::FlamenReq* req, ProtoResource::FlamemResp* resp)
{
	DBCUserBaseWrap userWrap(uid);

	int type =  req->type();
	///////////////////////////////////////////////////////////////////
	//计算次数
	int nTotal = req->isonce() ? 1 : 10;
	int nFreeCnt = 0;
	int nBuyCnt = 0;
	//镔铁没有免费
	if (type == IRON_TYPE)
	{
		nBuyCnt =  nTotal;
	}
	else
	{
		if (userWrap.Obj().sacrifice >= nTotal)
		{
			nFreeCnt = nTotal;
		}
		else
		{
			nFreeCnt = userWrap.Obj().sacrifice;
			nBuyCnt =  req->isfree() ? 0 : nTotal - userWrap.Obj().sacrifice;
		}
	}

	//////////////////////////////////////////////////////////////////////
	//价格=（n+1）*2
	int nCostCash = 0;
	if (nBuyCnt > 0)
	{
		// ((n + 1) + (n + 1) + m - 1)*2*m/2
		int n = userWrap.Obj().GetFlamenBuyCnt(type) + 1;
		int m = nBuyCnt;
		nCostCash = ((n + 1) + (n + m)) * m;
		if ((int)(userWrap.Obj().cash) < nCostCash)
		{
			throw std::runtime_error("cash_not_enough");
		}
	}

	std::vector<unsigned> vMuls;
	std::vector<unsigned> vRewards;
	do
	{
		if (nFreeCnt == 0 && nBuyCnt == 0) break;

		////////////////////////////////////////////////////////////////////////////
		//产出
		int nTotalVal = 0;
		int nYields = LogicBuildManager::Instance()->YieldsBase(uid, type);
		ResourceCfgWrap resourceCfgWrap;

		//镔铁是产量的四倍其他为2倍
		int nYieldsMul = (type == IRON_TYPE) ? 4 : 2;
		for (int i = 0; i < nFreeCnt; ++i)
		{
			int nMul = resourceCfgWrap.GetMultiple(true);
			int nVal = nMul * nYields * nYieldsMul;
			nTotalVal += nVal;
			vRewards.push_back(nVal);
			vMuls.push_back(nMul);
		}

		for (int i = 0; i < nBuyCnt; ++i)
		{
			int nMul = resourceCfgWrap.GetMultiple(false);
			int nVal = nMul * nYields * nYieldsMul;
			nTotalVal += nVal;

			vRewards.push_back(nVal);
			vMuls.push_back(nMul);
		}

		std::string reason = "Flamen_op_" + Convert::IntToString(type);


		/////////////////////////////////////////////////////////////////////////////
		userWrap.UseFreeFlamen(nFreeCnt);
		userWrap.FlamenCostCnt(type, nBuyCnt);
		//消耗元宝
		if (nCostCash > 0)
		{
			userWrap.CostCash(nCostCash, reason);
		}

		std::map<unsigned, unsigned> mapRes;
		mapRes[type] = nTotalVal;
		userWrap.AddResource(mapRes, reason);

		//todo 接入祭祀任务接口
		LogicMissionManager::MissionParam missionparam;
		missionparam.type = mission_type_pray;
		missionparam.subparam.push_back(type);  //祭祀的资源类型
		missionparam.subparam.push_back(nFreeCnt);  //免费次数
		missionparam.subparam.push_back(nBuyCnt);   //元宝购买的次数

		LogicMissionManager::Instance()->VerifyMissionComplete(uid, missionparam);

	} while(0);

	//resp
	if (resp)
	{
		resp->set_type(type);

		for(size_t i = 0; i < vMuls.size(); i++)
		{
			resp->add_multiple(vMuls[i]);
			resp->add_rewards(vRewards[i]);
		}
		resp->set_value(userWrap.Obj().GetResource(type));
		resp->set_free_cnt(userWrap.Obj().sacrifice);
		resp->set_buy_cnt(userWrap.Obj().GetFlamenBuyCnt(type));
		resp->set_cash(userWrap.Obj().cash);
	}

	return R_SUCCESS;
}

int LogicResourceManager::Process(unsigned uid, ProtoResource::CutBlackMarketCDReq * req, ProtoResource::CutBlackMarketCDResp * respmsg)
{
	int ret = R_SUCCESS;
	DBCUserBaseWrap userwrap(uid);

	//先获得剩余的cd时间，然后计算钻石数
	unsigned now = Time::GetGlobalTime();

	if (now > userwrap.Obj().bmarketcd)
	{
		userwrap.Obj().bmarketcd = now;
	}

	int diff_time = userwrap.Obj().bmarketcd - now;
	int cash = 0;
	unsigned newcash = 0;

	int per = 60;  //1分钟1钻石
	double divtimes = diff_time/static_cast<double>(per);

	int clearprice = MarketConfigWrap().GetBlackMarket().clearcdprice();

	cash = (int) ceil(divtimes) * clearprice;

	if (cash > 0)
	{
		//扣钻石
		userwrap.CostCash(cash, "BlackMarket_CUTCD");

		//获取黑市的CD时间
		userwrap.Obj().bmarketcd  = now;
		userwrap.Save();
	}

	respmsg->set_bmarketcd(userwrap.Obj().bmarketcd );
	respmsg->set_cash(userwrap.Obj().cash);

	return 0;
}

int LogicResourceManager::Process(unsigned uid, ProtoResource::BMarketExchangeReq *req, ProtoResource::BMarketExchangeResp * respmsg)
{
	unsigned usedtype = req->usedtype();
	unsigned gaintype = req->gaintype();

	if (usedtype == gaintype || usedtype < resource_type_coin || usedtype > resource_type_food
			|| gaintype < resource_type_coin || gaintype > resource_type_food)
	{
		error_log("[BMarketPurchaseReq] type invalid. usedtype=%u,gaintype=%u", usedtype, gaintype);
		throw std::runtime_error("param_invalid");
	}

	//判断当前cd时间
	unsigned now = Time::GetGlobalTime();
	DataBase &base = BaseManager::Instance()->Get(uid);

	int ret = VerifyCDTime(base, now);

	if (ret)
	{
		throw std::runtime_error("exchange_in_cd");
	}

	//todo 调用科技接口，获取黑市单次集市的倍数加成
	//int multiple = 1;  //倍数
	DBCUserBaseWrap user(uid);
	float multiple = 1.0f;
	int usedbase = MarketConfigWrap().GetBlackMarket().ratio(0u);  //消耗的基数
	int gainbase = MarketConfigWrap().GetBlackMarket().ratio(1u);  //获得产量的基础

	//扣资源
	int coin = 0;
	int wood = 0;
	int food = 0;

	switch(usedtype)
	{
		case resource_type_coin: coin = usedbase * multiple; break;
		case resource_type_wood: wood = usedbase * multiple; break;
		case resource_type_food: food = usedbase * multiple; break;
		default : throw std::runtime_error("param_invalid"); break;
	}

	Json::Value result;
	LogicUserManager::Instance()->CostUserResource(uid, coin, wood, food, 0, "BMarket_Exchange", result);

	multiple = 1 + user.VIPPower().GetMarketAdd();
	//加资源
	int addcoin = 0;
	int addwood = 0;
	int addfood = 0;

	switch(gaintype)
	{
		case resource_type_coin: addcoin = gainbase * multiple; break;
		case resource_type_wood: addwood = gainbase * multiple; break;
		case resource_type_food: addfood = gainbase * multiple; break;
		default : throw std::runtime_error("param_invalid"); break;
	}

	LogicUserManager::Instance()->AddUserResource(uid, addcoin, addwood, addfood, 0, "BMarket_Exchange", result);

	//生成随机cd时间.在1min-3min之间
	unsigned randval =  Math::GetRandomInt(120) + 60;
	base.bmarketcd += randval;

	BaseManager::Instance()->UpdateDatabase(base);

	//返回
	respmsg->set_coin(result["coin"].asUInt());
	respmsg->set_wood(result["wood"].asUInt());
	respmsg->set_food(result["food"].asUInt());
	respmsg->set_bmarketcd(base.bmarketcd);

	//todo 黑市兑换外部接口
	BMarketExternalInterface(uid);

	return 0;
}

int LogicResourceManager::BMarketExternalInterface(unsigned uid)
{
	//todo 接入每日黑市兑换任务
	LogicDailyMissionManager::DailyMissionParam dailymissionparam;
	dailymissionparam.type = daily_mission_type_blackmarket;

	LogicDailyMissionManager::Instance()->VerifyDailyMissionComplete(uid, dailymissionparam);

	return 0;
}

int LogicResourceManager::VerifyCDTime(DataBase & base, unsigned now)
{
	if (now > base.bmarketcd)
	{
		base.bmarketcd = now;
	}

	int diff_time = base.bmarketcd - now;
	int maxcdtime = 15*60;

	if (diff_time > maxcdtime)
	{
		error_log("[VerifyCDTime] black-market exchange is in cd. uid=%u,cd=%u", base.uid, diff_time);
		return R_ERR_LOGIC;
	}

	return 0;
}

void LogicResourceManager::Print()
{
	for (int  i = 0; i < MEMORY_HERO_PROPERTY_NUM; i++)
	{
		const  OfflineResourceItem& item =
				ResourceManager::Instance()->m_data->item[i];
		if (item.uid == 0) break;

		//char buffer[8192] = {0};
		debug_log("=======================================================");
		debug_log("uid: %u, aid:%u, job: %u,kingdom: %u, viplevel:%u"
				, item.uid, item.aid, item.job, item.kingdom, item.viplevel);
		debug_log("name: %s", item.name);
		debug_log("head: %s", item.fig);

		//英雄
		debug_log("Property: [%d, %d, %d, %d, %d, %d, %d]"
				, item.property[0], item.property[1]
				, item.property[2], item.property[3]
				, item.property[4], item.property[5], item.property[6]);

	}
}
