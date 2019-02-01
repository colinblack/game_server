/*
 * GameBase.cpp
 *
 *  Created on: 2018年11月28日
 *      Author: colin
 */

#include "GameBase.h"
#include "LogicHeroManager.h"

int GameBase::InitUserItem(unsigned uid, unsigned battleid)
{
	//获取阵型
	vector<unsigned>& formation = LogicBattleManager::Instance()->GetFormation(uid);
	if(formation.size() == 0)
	{
		error_log("no formation, uid=%u", uid);
		return R_ERROR;
	}

	auto& base = BaseManager::Instance()->Get(uid);
	//添加玩家到比赛
	int ret = DataGameManager::Instance()->AddUser(uid, battleid, base.level);
	if(ret != R_SUCCESS)
	{
		error_log("add user error, uid=%u, ret=%u", uid, ret);
		return ret;
	}

	//设置英雄属性
	for(auto& heroid : formation)
	{
		HeroAttrItem attr;
		attr.id = heroid;
		LogicHeroManager::Instance()->GetHeroAttr(uid, heroid, attr);
		attr.n_hp = attr.hp;
		ret = DataGameManager::Instance()->SetHeroAttr(uid, battleid, heroid, attr);
		if(ret != R_SUCCESS)
		{
			error_log("set hero attribute failed, uid=%u, ret=%u", uid, ret);
			return ret;
		}
	}

	//随机从卡池里抽牌组成战斗卡包
	CreateUserCardBag(battleid, uid);

	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, uid);
	vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, uid);
	vector<CardItem> tempcards  = DGI->GetTempCards(battleid, uid);

	CreateHandCard(handcards, cardbags, tempcards);

	return R_SUCCESS;
}

void GameBase::CreateUserCardBag(unsigned battleid, unsigned uid)
{
	vector<unsigned> indexs;
	DataCardsManager::Instance()->GetIndexs(uid, indexs);

	CardsCfgWrap cardsCfg;
	HeroCfgWrap  heroCfg;
	vector<unsigned>& formation = LogicBattleManager::Instance()->GetFormation(uid);

	vector<CardItem> cardbag;
	for(auto& idx : indexs)
	{
		auto& data = DataCardsManager::Instance()->GetDataByIndex(idx);
		unsigned cardId = data.card_id;

		auto& cfg = cardsCfg.GetCardsCfgById(cardId);
		if(cfg.r_type() == e_card_role_hero)
		{
			for(auto& heroid: formation)
			{
				if(heroid == cfg.heroid())
					cardbag.push_back(CardItem(data.id, cardId, data.star, e_card_common));
			}
		}
		else if(cfg.r_type() == e_card_role_pro)
		{
			for(auto& heroid: formation)
			{
				unsigned prof = heroCfg.GetHeroByHeroId(heroid).info().prof();
				if(prof == cfg.prof())
					cardbag.push_back(CardItem(data.id, cardId, data.star, e_card_common));
			}
		}
		else if(cfg.r_type() == e_card_role_gen)
		{
			cardbag.push_back(CardItem(data.id, cardId, data.star, e_card_common));
		}
	}

	DataGameManager::Instance()->SetCardBag(battleid, uid, cardbag);
}

void GameBase::CreatNpcCardBag(unsigned battleid, unsigned id, vector<unsigned>& formation, vector<CardItem>& cardbag)
{
	CardsCfgWrap cardsCfg;
	NpcCfgWarp   npcCfg;

	vector<CardItem> result;
	for(auto& card : cardbag)
	{
		auto& cfg = cardsCfg.GetCardsCfgById(card.id);
		if(cfg.r_type() == e_card_role_hero)
		{
			for(auto& heroid: formation)
			{
				if(heroid == cfg.heroid())
					result.push_back(card);
			}
		}
		else if(cfg.r_type() == e_card_role_pro)
		{
			for(auto& npcid: formation)
			{
				unsigned prof = npcCfg.GetNpcById(npcid).prof();
				if(prof == cfg.prof())
					result.push_back(CardItem(card));
			}
		}
		else if(cfg.r_type() == e_card_role_gen)
		{
			result.push_back(card);
		}
	}

	DataGameManager::Instance()->SetCardBag(battleid, id, result);

}

void GameBase::CreateHandCard(vector<CardItem>& cards, vector<CardItem>& cardbags, vector<CardItem>& temp)
{
	//清除临时卡牌和无效卡
	cards.erase(std::remove_if(cards.begin(), cards.end(),
			[&](CardItem card){return (card.temp == e_card_temp || card.id == 0);}), cards.end());

	//随机选择卡牌放入临时牌库
	while(cards.size() > HAND_CARD_NUM)
	{
		int index = Math::GetRandomInt(cards.size());
		temp.push_back(cards[index]);
		swap(cards[index], cards.back());
		cards.pop_back();
	}

	if(cards.size() == HAND_CARD_NUM)
		return;

	//卡包中的卡不足5张, 先将卡都取出加到手牌中
	if(cardbags.size() <= (HAND_CARD_NUM - cards.size()))
	{
		std::copy(cardbags.begin(), cardbags.end(), std::back_inserter(cards));
		cardbags.clear();
	}

	if(cards.size() == HAND_CARD_NUM)
		return;

	//卡包为空则将弃牌包中的卡加入卡包中
	if(cardbags.size() == 0)
	{
		std::copy(temp.begin(), temp.end(), std::back_inserter(cardbags));
		temp.clear();
	}

	//洗牌
	for (int i=cardbags.size()-1;i>=0;--i)
	{
		int index = Math::GetRandomInt(i+1);
		swap(cardbags[index], cardbags[i]);
	}

	//手牌不足5张从卡包中随机抽取
	while(cards.size() < HAND_CARD_NUM && cardbags.size() > 0)
	{

		int index = Math::GetRandomInt(cardbags.size());
		cards.push_back(cardbags[index]);
		auto it = cardbags.begin() + index;
		swap(*it, cardbags.back());
		cardbags.pop_back();
	}
}


int GameBase::RobotOutCard(unsigned battleid)
{
	auto& gameData = DataGameManager::Instance()->GetData(battleid);
	auto& attacker = gameData.def;
	auto& defender = gameData.att;

	vector<CardItem>& handcards = DataGameManager::Instance()->GetHandCards(battleid, attacker.uid);

	ProtoBattleBase::ProtoComputerBattle* msg = new ProtoBattleBase::ProtoComputerBattle;

	bool end = false;
	for(auto& card : handcards)
	{
		auto& cfg = CardsCfgWrap().GetCardsCfgById(card.id);
		if(attacker.left_point < cfg.point() && cfg.point() != 0)
			continue;
		auto msgCard = msg->add_outcards();

		attacker.record.Star(card.star);
		for(int i = 0; i < cfg.action(card.star).list_size(); ++i)
		{
			auto& actionCfg = cfg.action(card.star).list(i);
			attacker.record.Index((char)i);
			auto ii = msgCard->mutable_battle();
			if(LAI->Process(battleid, card.id, actionCfg, msgCard->mutable_battle()) == R_ERROR)
			{
				error_log("out card failed, uid=%u", attacker.uid);
				throw runtime_error("out_card_failed");
			}
			//清除电脑效果相关数据;
			gameData.Clear(e_def);
		}
		//处理防守方复活buff
		LAI->Revive(battleid, defender, msgCard->mutable_battle());

		//TODO:处理流血buff
		if(LAI->Blood(battleid, attacker, defender, msgCard->mutable_battle()) == R_ERROR)
		{
			error_log("robot out card failed, battleid=%u", battleid);
			throw runtime_error("robot_out_card_failed");
		}

		//TODO:处理反击
		if(LAI->ShotBack(battleid, attacker, defender, msgCard->mutable_battle()) == R_ERROR)
		{
			error_log("robot out card failed, uid=%u", battleid);
			throw runtime_error("robot_out_card_failed");
		}
		//处理进攻方复活buff
		LAI->Revive(battleid, attacker, msgCard->mutable_battle());
        msgCard->set_cardid(card.id);

		end = DataGameManager::Instance()->Impl(battleid);
		if(end)
		{
			unsigned winUid = gameData.AttackerWin() ? defender.uid : attacker.uid;
			msg->set_winuid(winUid);
			break;
		}
		//TODO:处理死亡次数buff
		LAI->DealBuff(battleid, attacker, e_action_last_4);
		LAI->DealBuff(battleid, defender, e_action_last_4);


		attacker.CostPoint(cfg.point());

		//将非临时卡卡牌加到废弃牌库
		if(cfg.temp() == e_card_common)
			DataGameManager::Instance()->AddCardTemp(battleid, attacker.uid, card);
		card.Clear();
	}

	//更新出牌时间
	gameData.UpdataOutCardTs(Time::GetGlobalTime());

	//按回合处理buff
	LAI->DealBuff(battleid, attacker, e_action_last_1);
	gameData.def.Reset();

	//发牌
	vector<CardItem>& tempcards = DataGameManager::Instance()->GetTempCards(battleid, attacker.uid);
	vector<CardItem>& cardbags = DataGameManager::Instance()->GetCardBag(battleid, attacker.uid);
	GameBase::CreateHandCard(handcards, cardbags, tempcards);

	msg->set_nextuser(gameData.ChangeAttacking());
	msg->set_point(gameData.def.left_point);
	LogicManager::Instance()->sendMsg(defender.uid, msg);

	debug_log("next user: %u", msg->nextuser());

	if(end && gameData.type != e_battletype_championship)
			DataGameManager::Instance()->Clear(battleid);

	return R_SUCCESS;
}

void GameBase::SendCard(unsigned uid, unsigned battleid, unsigned btype, ProtoBattle::ProtoBattleCPP* msg)
{
	auto& data = DataGameManager::Instance()->GetData(battleid);

	//确定先手
	msg->set_first(data.First() == e_att ? 1 : 0);

	//发送发牌给前端
	data.att.SetMessage(msg->mutable_attacker());
	data.def.SetMessage(msg-> mutable_defender());


	auto& cardbag = DataGameManager::Instance()->GetCardBag(battleid, uid);
	for(auto& card : cardbag)
	{
		card.SetMessage(msg->mutable_cards()->add_bag());
	}

	auto& handcards = DGI->GetHandCards(battleid, data.att.uid);
	for(auto& card : handcards)
	{
		card.SetMessage(msg->mutable_cards()->add_hand());
	}

	//当前出牌是电脑的情况
	if(data.Attacking() == e_def && btype != e_battletype_championship)
		LogicBattleManager::Instance()->AddRobot(battleid, btype);
}


int GameBase::InitOthItem(unsigned uid, unsigned battleid)
{
	auto& item = LogicResourceManager::Instance()->Get(uid);
	if(DGI->AddUser(item.uid, battleid, item.level) != R_SUCCESS)
	{
		error_log("add user error, uid=%u", uid);
		return R_ERROR;
	}

	for(int i = 0; i < MAX_FORMATION_HERO; ++i)
	{
		auto& info = item.heros[i];
		if(info.id == 0)
			continue;

		auto& attr = info.attr;
		HeroAttrItem temp(info.id, attr.hp, attr.att, attr.def, attr.crit, attr.acrit, attr.dodge,
						attr.adodge, attr.critt, attr.speed, attr.battlePower, 0);

		if(DataGameManager::Instance()->SetHeroAttr(item.uid, battleid, temp.id, temp) != R_SUCCESS)
		{
			error_log("set hero attribute failed, uid=%u, ret=%u", uid);
			return R_ERROR;
		}
	}

	//随机充卡池中抽取卡牌组成战斗卡包
	CreateUserCardBag(battleid, uid);
	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, uid);
	vector<CardItem>& cardbags  = DGI->GetCardBag(battleid, uid);
	vector<CardItem> tempcards  = DGI->GetTempCards(battleid, uid);

	CreateHandCard(handcards, cardbags, tempcards);

	return R_SUCCESS;
}


