/*
 * LogicCardsManager.cpp
 *
 *  Created on: 2018年11月21日
 *      Author: colin
 */

#include "LogicCardsManager.h"


int LogicCardsManager::AddCards(unsigned uid, unsigned cardsid, string reason, ProtoCards::CardsAllChangeCPP* msg)
{
	unsigned maxCount = CardsCfgWrap().GetCardsCfgById(cardsid).max();
	unsigned count = DataCardsManager::Instance()->GetCardCount(uid, cardsid);

	if(count == maxCount)
	{
		error_log("card count max, uid=%u, cardid=%u", uid, cardsid);
		throw runtime_error("card_count_max");
	}

	unsigned ud = DataCardsManager::Instance()->GetUserNextUd(uid);
	DataCards item;
	item.id = ud;
	item.uid = uid;
	item.card_id = cardsid;

	DataCardsManager::Instance()->AddNewCard(item);

	if(!DataUnlockCardsManager::Instance()->IsExistItem(uid, cardsid))
	{
		DataUnlockCards item;
		item.uid = uid;
		item.id  = cardsid;
		DataUnlockCardsManager::Instance()->AddNewItem(item);
	}
	//DataUnlockCardsManager::Instance()->GetData(uid, cardsid);
	if(msg != nullptr)
	{
		ProtoCards::UserCardsCPP* addCardMsg = msg->add_cards();
		item.SetMessage(addCardMsg);
	}


	CARDS_LOG("uid=%u,id=%u,cardsid=%d,act=%s, code=%s.", uid, item.id, cardsid, "Add", reason.c_str());

	return R_SUCCESS;
}

int LogicCardsManager::Process(unsigned uid, ProtoCards::ProtoUpdateCardReq* req, ProtoCards::ProtoUpdateCardResp* resp)
{
	unsigned cardId = req->cardid();
	unsigned ud		= req->ud();

	if(!DataCardsManager::Instance()->IsExistItem(uid, ud))
	{
		error_log("card not exist, uid=%u, ud=%u", uid, ud);
		throw runtime_error("card_not_exist");
	}

	DataCards& data = DataCardsManager::Instance()->GetData(uid, ud);
	if(data.star == MAX_CARD_STAR)
	{
		error_log("star is max: uid=%u", uid);
		throw runtime_error("star_is_max");
	}

	unsigned star = data.star + 1;
	auto& cfg = CardsCfgWrap().GetStartUpdateCfgById(cardId);
	LogicUserManager::Instance()->CommonProcess(uid, cfg.cost(star-1), "card_update_star", resp->mutable_commons());

	data.star = star;
	DataCardsManager::Instance()->UpdateItem(data);
	return 0;
}

int LogicCardsManager::Process(unsigned uid, ProtoCards::ProtoDupCardReq* req, ProtoCards::ProtoDupCardResp* resp)
{
	unsigned cardId = req->id();
	if(!DataUnlockCardsManager::Instance()->IsExistItem(uid, cardId))
	{
		error_log("card not exist, uid=%u, cardid=%u", uid, cardId);
		throw runtime_error("card_not_exist");
	}

	CardsCfgWrap  wrap;
	unsigned maxCount = wrap.GetCardsCfgById(cardId).max();
	unsigned count = DataCardsManager::Instance()->GetCardCount(uid, cardId);

	if(count == maxCount)
	{
		error_log("count is max: uid=%u", uid);
		throw runtime_error("count_is_max");
	}

	auto& dupCfg = wrap.GetStartDupCfgById(cardId);

	//实际消耗的钻石数  = 配置中的钻石数 * 复制卡牌张数
	CommonGiftConfig::CommonModifyItem cfg;
	cfg.mutable_based()->set_cash(dupCfg.cost().based().cash() * (count+1));

	LogicUserManager::Instance()->CommonProcess(uid, cfg, "card_dup_star", resp->mutable_commons());
	AddCards(uid, cardId, "dup_card", resp->mutable_item());

	return 0;
}


int LogicCardsManager::Process(unsigned uid, ProtoCards::ProtoDelCardReq* req,  ProtoCards::ProtoDelCardResp* resp)
{
	unsigned ud = req->ud();
	unsigned cardId = req->cardid();

	if(!DataCardsManager::Instance()->IsExistItem(uid, ud))
	{
		error_log("card not exist, uid=%u, ud=%u", uid, ud);
		throw runtime_error("card_not_exist");
	}
	auto& data = DataCardsManager::Instance()->GetData(uid, ud);
	CardsCfgWrap  wrap;
	auto& cardsCfg = wrap.GetCardsCfgById(cardId);

	//天赋卡至少留一张
	if(cardsCfg.r_type() == e_card_role_hero)
	{
		unsigned count = DataCardsManager::Instance()->GetCardCount(uid, cardId);
		if(count == 1)
		{
			error_log("delete error: uid=%u, carid=%u", uid, cardId);
			throw runtime_error("delete_error");
		}
	}

	DataCards item;
	item.uid = uid;
	item.id	 = ud;
	item.card_id = cardId;
	DataCardsManager::Instance()->DelCard(item);
	//补偿 = 卡牌价值  + 升星花费
	int  coin = cardsCfg.coin();
	unsigned star = data.star;
	if(star > 0)
		coin  +=  -wrap.GetStartUpdateCfgById(cardId).cost(star-1).based().coin() / 5;

	CommonGiftConfig::CommonModifyItem payCfg;
	payCfg.mutable_based()->set_coin(coin);
	payCfg.mutable_based()->set_cash(wrap.Obj().delcash());


	LogicUserManager::Instance()->CommonProcess(uid, payCfg, "card_del", resp->mutable_commons());

	return 0;
}

int LogicCardsManager::Process(unsigned uid, ProtoCards::ProtoBuyCardReq* req, ProtoCards::ProtoBuyCardResp* resp)
{
	unsigned cardId = req->cardid();
	CardsCfgWrap  wrap;
	unsigned maxCount = wrap.GetCardsCfgById(cardId).max();
	unsigned count = DataCardsManager::Instance()->GetCardCount(uid, cardId);

	if(count == maxCount)
	{
		error_log("count is max: uid=%u", uid);
		throw runtime_error("count_is_max");
	}

	auto& bufCfg = wrap.GetPurchaseCfgById(cardId);
	LogicUserManager::Instance()->CommonProcess(uid, bufCfg.cost(), "buy_card", resp->mutable_commons());
	AddCards(uid, cardId, "buy_card", resp->mutable_item());
	if(!DataUnlockCardsManager::Instance()->IsExistItem(uid, cardId))
		DataUnlockCardsManager::Instance()->GetData(uid, cardId);

	return 0;
}

int LogicCardsManager::FullMessage(unsigned uid, User::CardsInfo* cardsmsg)
{
	vector<unsigned> vIndexs;
	DataCardsManager::Instance()->GetIndexs(uid, vIndexs);
	for(auto& index : vIndexs)
	{
		auto& data = DataCardsManager::Instance()->GetDataByIndex(index);
		data.SetMessage(cardsmsg->add_usercards());
	}

	return 0;
}


int LogicCardsManager::FullMessage(unsigned uid, User::UnlockCards* cardsmsg)
{
	vector<unsigned> vIndexs;
	DataUnlockCardsManager::Instance()->GetIndexs(uid, vIndexs);
	for(auto& index : vIndexs)
	{
		auto& data = DataUnlockCardsManager::Instance()->GetDataByIndex(index);
		data.SetMessage(cardsmsg->add_unlockinfo());
	}

	return 0;
}

