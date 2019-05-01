/*
 * LogicShop.cpp
 *
 *  Created on: 2016-10-28
 *      Author: dawx62fac
 */


#include "LogicShop.h"


DBCLimitShopWrap::DBCLimitShopWrap(unsigned uid)
	: container_(DataLimitShopMgr::Instance())
	, index_(_Index(uid))
	, data_(container_->m_data->data[index_])
{
	unsigned nVersion = LimitShop::Instance()->GetVersion();
	if (nVersion != data_.version || ! Time::IsToday(data_.op_time))
	{
		data_.Reset(nVersion);

		Save();
	}
}

unsigned DBCLimitShopWrap::_Index(unsigned uid)
{
	if (! LimitShop::Instance()->IsOn())
	{
		throw std::runtime_error("limit_shop_activity_not_open");
	}

	return container_->GetIndex(uid);
}

bool DBCLimitShopWrap::IsFullBuyCnt(unsigned id, const ShopConfig::LimitShopItem& cfg)
{
	return data_.GetBuyCnt(id) >= cfg.limit_cnt();
}

unsigned DBCLimitShopWrap::GetBuyCnt(unsigned id)
{
	return data_.GetBuyCnt(id);
}

void DBCLimitShopWrap::OpBuy(unsigned id)
{
	data_.OP(id);

	Save();
}

void DBCLimitShopWrap::FullMessage(unsigned id, ProtoActivity::LimitShopItem* obj)
{
	obj->set_id(id);
	obj->set_buy_cnt(data_.GetBuyCnt(id));
}

//////////////////////////////////////////////////////////////////////////////
void LimitShop::Online(unsigned uid)
{
	if (this->IsOn())
	{
		DataLimitShopMgr::Instance()->Online(uid);
	}
}

int LimitShop::Process(unsigned uid, ProtoActivity::LimitShopUserInfoReq* req, ProtoActivity::LimitShopUserInfoResp* resp)
{
	DBCUserBaseWrap user(uid);

	DBCLimitShopWrap limitShop(uid);

	for (int i = 1; i <= 6; i++)
	{
		limitShop.FullMessage(i, resp->add_items());
	}

	return 0;
}

int LimitShop::Process(unsigned uid, ProtoActivity::LimitShopBuyReq* req, ProtoActivity::LimitShopBuyResp* resp)
{
	DBCUserBaseWrap user(uid);
	DBCLimitShopWrap limitShop(uid);

	unsigned id = req->id();
	unsigned open_days = LMI->GetOpenDays();
	//
	const ShopConfig::LimitShopItem& equip_cfg = LimitShopCfgWrap().GetItem(open_days, id);
	if (limitShop.IsFullBuyCnt(id, equip_cfg))
	{
		throw std::runtime_error("not_surplus_buy_cnt");
	}

	std::string op_code = "limit_shop_buy_op_" + Convert::IntToString(id);
	user.CostCash(equip_cfg.price(), op_code);

	limitShop.OpBuy(id);
	//
	unsigned eqid = equip_cfg.equip_id();
	LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, 1, op_code, resp->mutable_equip());

	resp->set_cash(user.Obj().cash);
	resp->set_id(id);
	resp->set_buy_cnt(limitShop.GetBuyCnt(id));

	return 0;
}
