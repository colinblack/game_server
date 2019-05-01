#include "LogicCrossBusinessManager.h"

int LogicCrossBusinessManager::Process(unsigned uid, ProtoCrossBusiness::BusinessOpenWindowReq *reqmsg, ProtoCrossBusiness::BusinessOpenWindowResp * respmsg)
{
	OpenWindow(uid, respmsg);

	return 0;
}

int LogicCrossBusinessManager::OpenWindow(unsigned uid, ProtoCrossBusiness::BusinessOpenWindowResp * respmsg)
{
	//判断是否有跨国商人数据
	bool isexist = DataCrossBusinessManager::Instance()->IsCrossBusinessExists(uid);

	if (!isexist)
	{
		//不存在，则先新增
		DataCrossBusiness business;
		business.uid = uid;
		business.refreshts = Time::GetGlobalTime();

		DataCrossBusinessManager::Instance()->AddBuff(business);

		//再进行刷新
		Refresh(uid, false);

		//这里要做下特别的处理，将下次可刷新的时间进行调整，是为了让用户打开就可以再次刷新
		DataCrossBusiness&  datacross = DataCrossBusinessManager::Instance()->GetCrossBusiness(uid);
		datacross.refreshts = Time::GetGlobalTime();

		DataCrossBusinessManager::Instance()->UpdateCrossBusiness(datacross);
	}

	//传递跨国信息给前端
	DataCrossBusiness&  datacross = DataCrossBusinessManager::Instance()->GetCrossBusiness(uid);
	datacross.SetMessage(respmsg->mutable_crossbusiness());

	return 0;
}

int LogicCrossBusinessManager::Process(unsigned uid, ProtoCrossBusiness::BusinessRefreshReq *reqmsg, ProtoCrossBusiness::BusinessRefreshResp * respmsg)
{
	bool bcash = reqmsg->iscash();

	RefreshShop(uid, bcash, respmsg);

	return 0;
}

int LogicCrossBusinessManager::RefreshShop(unsigned uid, bool iscash, ProtoCrossBusiness::BusinessRefreshResp * respmsg)
{
	Refresh(uid, iscash);

	DataCrossBusiness&  datacross = DataCrossBusinessManager::Instance()->GetCrossBusiness(uid);
	datacross.SetMessage(respmsg->mutable_crossbusiness());

	int cash = BaseManager::Instance()->Get(uid).cash;
	respmsg->set_cash(cash);

	return 0;
}

int LogicCrossBusinessManager::Refresh(unsigned uid, bool iscash)
{
	CrossBusinessConfigWrap cross_business_cfg;
	DataCrossBusiness&  datacross = DataCrossBusinessManager::Instance()->GetCrossBusiness(uid);

	if (iscash)
	{
		int cash = cross_business_cfg.GetRefreshCash();

		//扣钻
		DBCUserBaseWrap userwrap(uid);
		userwrap.CostCash(cash, "CrossBusiness_Refresh");
	}
	else
	{
		//判断刷新时间是否达到
		if (datacross.refreshts > Time::GetGlobalTime())
		{
			error_log("refresh is in cd. uid=%u", uid);
			throw runtime_error("refresh_in_cd");
		}
	}

	//开始刷新
	unsigned diff = LogicManager::Instance()->GetOpenDays();
	const CrossBusinessConfig::OpenPlatformSlots & slots_cfg = cross_business_cfg.GetSlotsByDiff(diff);
	vector<unsigned> vctrates;

	for(int i = 0; i < slots_cfg.slots_size(); ++i)
	{
		vctrates.push_back(slots_cfg.slots(i).rate());
	}

	for(int i = 0; i < max_slot_items; ++i)
	{
		int target = 0;
		LogicCommonUtil::TurnLuckTable(vctrates, vctrates.size(), target);  //从库中根据权重随机抽取出结果

		//修改已抽取出来的商品处的概率
		vctrates[target] = 0;

		//设置跨国商人刷新的数据
		SetSlotValue(datacross, i, slots_cfg.slots(target).id());
	}

	if (!iscash)
	{
		//非花钻刷新才更新下次可刷新时间
		datacross.refreshts = Time::GetGlobalTime() + 60 * 60; //60min的cd时间
	}

	datacross.status = 0;  //刷新购买状态

	DataCrossBusinessManager::Instance()->UpdateCrossBusiness(datacross);

	return 0;
}

int LogicCrossBusinessManager::Process(unsigned uid, ProtoCrossBusiness::BusinessPurchaseReq *reqmsg, ProtoCrossBusiness::BusinessPurchaseResp * respmsg)
{
	unsigned pos = reqmsg->pos();

	Purchase(uid, pos, respmsg);

	return 0;
}

int LogicCrossBusinessManager::Purchase(unsigned uid, unsigned pos, ProtoCrossBusiness::BusinessPurchaseResp * respmsg)
{
	if (pos < 1 || pos > max_slot_items)
	{
		throw runtime_error("wrong_param");
	}

	DataCrossBusiness&  datacross = DataCrossBusinessManager::Instance()->GetCrossBusiness(uid);

	int index = pos - 1;
	//判断指定位置是否已经购买
	if (! LogicCommonUtil::CheckPosIsZero(datacross.status, index) )  //非0，则表示已领取
	{
		error_log("goods already been bought. uid=%u,pos=%u", uid, pos);
		throw runtime_error("goods_already_bought");
	}

	DBCUserBaseWrap userwrap(uid);
	CrossBusinessConfigWrap cross_business_cfg;

	unsigned id = GetSlotValue(datacross, pos - 1);
	const CrossBusinessConfig::SlotGoods & slotgoods = cross_business_cfg.GetGoodsById(id);

	//扣钻购买
	int price = slotgoods.price();
	userwrap.CostCash(price, "CrossBusiness_Buy");

	for(int i = 0; i < slotgoods.goods_size(); ++i)
	{
		LogicUserManager::Instance()->OpReward(userwrap, slotgoods.goods(i), "CrossBusiness", respmsg->mutable_goods());
	}

	//设置已购买标志位
	LogicCommonUtil::SetBitCurrent(datacross.status, index);
	DataCrossBusinessManager::Instance()->UpdateCrossBusiness(datacross);

	datacross.SetMessage(respmsg->mutable_crossbusiness());
	respmsg->set_cash(userwrap.Obj().cash);

	return 0;
}

int LogicCrossBusinessManager::SetSlotValue(DataCrossBusiness & business, int pos, unsigned value)
{
	switch(pos)
	{
		case 0: business.slot1 = value; break;
		case 1: business.slot2 = value; break;
		case 2: business.slot3 = value; break;
		case 3: business.slot4 = value; break;
		case 4: business.slot5 = value; break;
		case 5: business.slot6 = value; break;

		default: break;
	}

	return 0;
}

unsigned LogicCrossBusinessManager::GetSlotValue(DataCrossBusiness & business, int pos)
{
	unsigned value = 0;

	switch(pos)
	{
		case 0:	value =  business.slot1; break;
		case 1: value =  business.slot2; break;
		case 2: value =  business.slot3; break;
		case 3: value =  business.slot4; break;
		case 4: value =  business.slot5; break;
		case 5: value =  business.slot6; break;

		default: break;
	}

	return value;
}
