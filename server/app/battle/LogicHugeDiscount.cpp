/*
 * LogicHugeDiscount.cpp
 *
 *  Created on: 2016-12-19
 *      Author: dawx62fac
 */

#include "LogicHugeDiscount.h"

DBCHugeDiscountWrap::DBCHugeDiscountWrap(unsigned index)
	: container_(DataHugeDiscountMgr::Instance())
	, index_(_index(index))
	, data_(container_->m_data->data[index_])
{
	_init();
}

DBCHugeDiscountWrap::DBCHugeDiscountWrap(unsigned uid, unsigned id)
	: container_(DataHugeDiscountMgr::Instance())
	, index_(_id2index(uid, id))
	, data_(container_->m_data->data[index_])
{
	_init();
}

void DBCHugeDiscountWrap::_init()
{
	if (! LogicHugeDiscount::Instance()->IsOn())
	{
		throw std::runtime_error("huge_discount_activity_not_open");
	}

	unsigned nVersion = LogicHugeDiscount::Instance()->GetVersion();
	if (nVersion != data_.version || ! Time::IsToday(data_.op_time))
	{
		data_.Reset(nVersion);

		data_.op_time = Time::GetGlobalTime();

		Save();
	}
}

unsigned DBCHugeDiscountWrap::_index(unsigned index) const
{
	if (index < 0 || index >= DB_HUGE_DISCOUNT_FACTOR*DB_BASE_BUFF)
	{
		error_log("index_params_error index: %d", index);
		throw std::runtime_error("index_params_error");
	}


	return index;
}

unsigned DBCHugeDiscountWrap::_id2index(unsigned uid, unsigned id)
{
	//
	return container_->GetIndex(uid, id);
}

unsigned DBCHugeDiscountWrap::TotalRecharge() const
{
	return LogicResourceManager::Instance()->GetRechargePays(data_.uid, data_.op_time);
}

bool DBCHugeDiscountWrap::IsActive() const
{
	unsigned accRecharge = TotalRecharge();
	return (accRecharge >= HugeDiscountCfgWrap().GetOpenCash(data_.id));
}

void DBCHugeDiscountWrap::DoBuy(unsigned id)
{
	data_.OP(id);

	Save();
}

void DBCHugeDiscountWrap::FullMessage(unsigned id, ProtoActivity::HugeDiscountItem* obj) const
{
	obj->set_id(id);
	obj->set_buy_cnt(data_.GetBuyCnt(id));
}

void DBCHugeDiscountWrap::FullMessage(ProtoActivity::HugeDiscountPage* obj) const
{
	obj->set_page_id(data_.id);
	for (int i = data_.StartId(); i <=  data_.EndId(); i++ )
	{
		FullMessage(i, obj->add_goods());
	}
}
//////////////////////////////////////////////////////////////////////////////////
void LogicHugeDiscount::Online(unsigned uid)
{
	if (this->IsOn())
	{
		DataHugeDiscountMgr::Instance()->Online(uid);
	}
}

//信息
int LogicHugeDiscount::Process(unsigned uid, ProtoActivity::HugeDiscountInfoReq* req, ProtoActivity::HugeDiscountInfoResp* resp)
{
	DBCUserBaseWrap user(uid);

	std::vector<unsigned> vIndexs;
	DataHugeDiscountMgr::Instance()->GetIndexs(uid, vIndexs);
	for (size_t i = 0; i < vIndexs.size(); i++)
	{
		DBCHugeDiscountWrap disountItem(vIndexs[i]);
		disountItem.FullMessage(resp->add_items());
	}

	unsigned now = Time::GetGlobalTime();
	unsigned recharge =  LogicResourceManager::Instance()->GetRechargePays(uid, now);
	resp->set_recharge(recharge);

	return 0;
}

//购买
int LogicHugeDiscount::Process(unsigned uid, ProtoActivity::HugeDiscountBuyReq* req, ProtoActivity::HugeDiscountBuyResp* resp)
{
	DBCUserBaseWrap user(uid);
	unsigned page_id = req->page_id();
	unsigned id		 = req->id();

	DBCHugeDiscountWrap discountItem(uid, page_id);
	if (! discountItem.IsActive())
	{
		throw std::runtime_error("the_page_not_active");
	}

	unsigned open_days = LMI->GetOpenDays();
	const ::ActivityConfig::HugeDiscountItem& cfg = HugeDiscountCfgWrap().GoodItemCfg(page_id, id, open_days);
	if (discountItem.Obj().GetBuyCnt(id) >= cfg.limit_cnt())
	{
		throw std::runtime_error("full_buy_cnt");
	}

	std::string op_code = "huge_discount_buy_op" + Convert::IntToString(id);
	user.CostCash(cfg.price(), op_code);

	discountItem.DoBuy(id);

	unsigned eqid = cfg.equip_id();
	LogicEquipmentManager::Instance()->AddEquipment(uid, eqid, 1, op_code, resp->mutable_equip());

	resp->set_page_id(page_id);
	resp->set_cash(user.Obj().cash);
	discountItem.FullMessage(id, resp->mutable_item_info());

	return 0;
}
