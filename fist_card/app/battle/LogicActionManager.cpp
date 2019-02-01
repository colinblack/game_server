/*
 * LogicActionManager.cpp
 *
 *  Created on: 2018年12月4日
 *      Author: colin
 */

#include "LogicActionManager.h"


int LogicActionManager::OnInit()
{
	Register();

	return 0;
}


void LogicActionManager::Register()
{
	//table_[e_action_commonhurt] = &LogicActionManager::CommonHurt;
}

bool LogicActionManager::IsHit(unsigned& c_hit, double adodge_a, double dodge_d)
{
	bool hit = false;
	if(c_hit >= BDC_S(dodge_c))
	{
		c_hit = 0;
	}
	else
	{
		unsigned d = min(BDC_S(dodge_max), max(BDC_S(dodge_min), unsigned(BDC_S(dodge_p) * (adodge_a/ dodge_d) * double(100))));
		unsigned di = Math::GetRandomInt(100);
		if(di < d)
		{
			hit = true;
			++c_hit;
		}
		else
		{
			hit = false;
			c_hit = 0;
		}
	}

	return hit;
}

bool LogicActionManager::IsCrit(unsigned& c_n_c, unsigned n_c, double crit_a, double acrit_d)
{
	bool bang = false;
	if(c_n_c >= n_c)
	{
		bang = true;
		c_n_c = 0;
	}
	else
	{
		unsigned c = min(BDC_S(crit_max), max(BDC_S(crit_min), unsigned(BDC_S(crit_p) * (crit_a / acrit_d) * double(100))));
		unsigned ci = Math::GetRandomInt(100);
		if(ci < c)
		{
			bang = true;
			c_n_c = 0;
		}
		else
		{
			bang = false;
			++c_n_c;
		}
	}

	return bang;
}

double LogicActionManager::DataHandle(unsigned battleid, const Cards::Action& cfg)
{
	auto& data = DGI->GetData(battleid);
	unsigned type = cfg.value().id();
	double ret = 0.0;
	if(type == e_data_type_1)
	{
		ret = cfg.value().v();
	}
	else if(type == e_data_type_2)
	{
		unsigned prop = cfg.value().type();
		auto defender = data.CurDef();
		double value = defender->attr[defender->index].GetAttr(prop);
		ret = value * cfg.value().v();
	}
	else if(type == e_data_type_3)
	{
        ret = data.CurDef()->LastHurt();
	}
	else if(type == e_data_type_4)
	{
       unsigned actionType = cfg.value().type();
       unsigned othuid = data.CurDef()->uid;

       if(!DGI->BuffCount(battleid, othuid,  actionType))
	   {
			auto& buf = DGI->GetBuff(battleid, othuid, actionType);
			ret = buf.value;
	   }
	}

	return ret;
}

bool LogicActionManager::Condition(const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender)
{
	//无条件
	if(!cfg.has_con())
		return true;
	//TODO:条件有问题
	unsigned type = cfg.con().id();
	if(type == e_action_type_1)
		return Math::GetRandomInt(100) < cfg.con().p() * double(100);
	else if(type == e_action_type_2)
		return (attacker.record.crited == 1) || (defender.record.crited == 1);
	else if(type == e_action_type_3)
		return (attacker.record.dodged == 1) || (defender.record.dodged == 1);
	else if(type == e_action_type_4)
	{
		auto obj = cfg.con().c().aim() == e_own ? &attacker : &defender;

		if(cfg.con().has_c())
		{
			auto& data = cfg.con().c();
			unsigned mode = data.mod();
			unsigned key  = data.key();
			double value = obj->attr[obj->index].GetAttr(data.type());

			if(key == e_action_key_1)
			{
				if(mode == e_action_mod_1)
					return value > data.value();
				if(mode == e_action_mod_2)
					return value == data.value();
				if(mode == e_action_mod_3)
					return value < data.value();
			}
			else if(key == e_action_key_2 && data.type() == e_type_currhp)
			{
				//TODO:百分比方式暂时只考虑血量
				double other = obj->attr[obj->index].GetAttr(e_type_maxhp) * data.value();
				if(mode == e_action_mod_1)
					return value > other;
				if(mode == e_action_mod_2)
					return value == other;
				if(mode == e_action_mod_3)
					return value < other;
			}
		}
	}
	return false;
}


int LogicActionManager::Process(unsigned battleid, unsigned cardid, const Cards::Action& cfg, BattleInfoPtr* msg)
{
	unsigned type = cfg.type();
	auto& data = DGI->GetData(battleid);
	auto attacker = data.CurAtt();
	auto defender = data.CurDef();

	int ret = R_ERROR;
	//TODO:处理免疫效果buff
	if((ret = DisableBuff(battleid, cardid, cfg, *attacker, *defender, msg)) != R_ERR_NO_DATA)
		return ret;

	switch(type)
	{
		case e_action_commonhurt:
		case e_action_bloodhurt:
		case e_action_stabhurt:
			ret = Hurt(battleid, cardid, type, cfg, *attacker, *defender, msg);
			break;
		case e_action_modify:
		case e_action_recoverhp:
			ret = Modify(battleid, cardid, cfg, *attacker, *defender, msg);
			break;
		case e_action_batter:
			ret = Batter(battleid, cardid, cfg, *attacker, *defender, msg);
			break;
		case e_action_point:
			ret = GainPoint(battleid, cfg, *attacker, msg);
			break;
		case e_action_reset:
			ret = ResetHandCards(battleid, *attacker, msg);
			break;
		case e_action_clear:
			ret = ClearBuff(battleid, cfg, *attacker, *defender, msg);
			break;
		case e_action_bomb:
			ret = Bomb(battleid, cfg, *attacker, *defender, msg);
			break;
		case e_action_temp:
			ret = TempCards(battleid, cfg, *defender, msg);
			break;
		case e_action_card:
			ret = ExtraCards(battleid, cfg, *attacker, msg);
			break;
		case e_action_add_shotback:
		case e_action_add_attcast:
		case e_action_add_invalid:
		case e_action_add_blood:
		case e_action_add_hurtback:
		case e_action_add_hurttrans:
		case e_action_add_revive:
			ret = AddBuff(battleid, cardid, cfg, *attacker, *defender, msg);
			break;
		default:
			break;
	}

	return ret;
}

int LogicActionManager::BaseHurt(unsigned battleid, unsigned type, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg, bool basehurt, bool con)
{
	//判断作用对象
	if(cfg.aim() != e_other)
	{
		error_log("config error");
		return R_ERROR;
	}
	//判断执行条件
	if(con && !Condition(cfg, attacker, defender))
	{
		debug_log("disqualification, battleid: %u", battleid);
		return R_ERR_NO_DATA;
	}

	debug_log("------------ before: att: current_hp: %lf, shield: %u, def: current_hp: %lf, shield: %u, type:%u ----------------------",
			attacker.attr[attacker.index].n_hp, attacker.attr[attacker.index].shield, defender.attr[defender.index].n_hp, defender.attr[defender.index].shield, type);

	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();

	double adodge_a = attacker.attr[attacker.index].adodge;
	double crit_a 	= attacker.attr[attacker.index].crit;
	double critt_a 	= attacker.attr[attacker.index].critt;
	unsigned c_hit 	= attacker.attr[attacker.index].c_hit;
	unsigned c_n_c 	= attacker.attr[attacker.index].c_n_crit;

	double def_d 	= defender.attr[defender.index].def;
	double dodge_d  = defender.attr[defender.index].dodge;
	double acrit_d 	= defender.attr[defender.index].acrit;

	//是否命中
	bool bang = false;
	//最终伤害
	double dam = 0.0;
	if(IsHit(c_hit, adodge_a, dodge_d))
	{
		double basedam = DataHandle(battleid, cfg);
		if(basehurt)
		{
			basedam = BaseHurt(basedam, def_d);
		}

		//是否暴击
		if(IsCrit(c_n_c, attacker.n_c, crit_a, acrit_d))
		{
			basedam *= (double(1) + critt_a);
			bang = true;
			//有暴击
			defender.record.Crited();
		}
		//最终伤害
		dam = defender.attr[defender.index].LastDam(basedam, true);

		//护盾值有变化
		defender.record.AttrChange(e_type_shield);

		//伤害反弹
		HurtBack(battleid, dam, defender, attacker);

		//伤害转换
		if(HurtTrans(battleid, dam, defender, attacker, bmsg->mutable_def()->mutable_attr()) == R_ERR_NO_DATA)
			defender.attr[defender.index].Injure(dam);
		else
			dam = 0;
	}
	else
	{
		//有闪避
		defender.record.Dodoged();
	}

	auto& game = DataGameManager::Instance()->GetData(battleid);

	if(bang)
		attacker.record.Crited();

	game.SetCurrType(type);
	defender.LastHurt(dam);
	defender.record.Dam(dam);

	game.SetMessage(bmsg, e_other);
	if(game.attacking == e_att)
	{
		attacker.SetMessage(bmsg->mutable_att());
		defender.SetMessage(bmsg->mutable_def());
	}
	else
	{
		attacker.SetMessage(bmsg->mutable_def());
		defender.SetMessage(bmsg->mutable_att());
	}

	//TODO:是否有反击
	if(defender.attr[defender.index].n_hp > 0
		&& !defender.record.IsShotBack()
		&& DGI->BuffCount(battleid, defender.uid, e_action_buff_1) != 0)
	{
		defender.record.ShotBack();
	}

	/*debug_log("------------ end: att: current_hp: %lf, shield: %u, def: current_hp: %lf, shield: %u, dam: %lf ----------------------",
			game.att.attr[game.att.index].n_hp, game.att.attr[game.att.index].shield, game.def.attr[game.def.index].n_hp, game.def.attr[game.def.index].shield, dam);
*/
	//TODO: 处理按攻击次数buff
	DealBuff(battleid, attacker, e_action_last_3);
	//处理按受伤次数buff
	if(dam > 0)
		DealBuff(battleid, defender, e_action_last_2);

	return R_SUCCESS;
}

int LogicActionManager::Hurt(unsigned battleid, unsigned cardid, unsigned type, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	unsigned countAtt = DGI->BuffCount(battleid, attacker.uid, e_action_add_attcast);
	unsigned countDef = DGI->BuffCount(battleid, defender.uid, e_action_add_attcast);

	unsigned cast = type;
	CardsCfgWrap  cardsCfg;
	//攻击转换buff
	if(countAtt > 0)
	{
		auto& buff = DGI->GetBuff(battleid, attacker.uid, e_action_add_attcast);
		auto& attCfg = cardsCfg.GetCardsCfgById(buff.cardid).action(buff.star).list(buff.index);

		bool ret = Condition(attCfg, attacker, defender);
		if(!ret && countDef == 0)
			return R_ERR_NO_DATA;
		else
		{
			if(ret)
				cast = cfg.value().type();
		}

		//处理持续类型
		if(buff.ltype == e_action_last_3)
			buff.count--;
	}
	if(countDef > 0)
	{
		auto& buff = DGI->GetBuff(battleid, defender.uid, e_action_add_attcast);
		auto& defCfg = cardsCfg.GetCardsCfgById(buff.cardid).action(buff.star).list(buff.index);
		bool ret = Condition(defCfg, attacker, defender);
		if(!ret && countAtt == 0)
			return R_ERR_NO_DATA;
		else
		{
			if(ret)
				cast = cfg.value().type();
		}

		//处理持续类型
		if(buff.ltype == e_action_last_3)
			buff.count--;
	}

	if(cast == e_action_commonhurt)
		return BaseHurt(battleid, cast, cfg, attacker, defender, msg, true);
	else if(cast == e_action_bloodhurt)
		return BaseHurt(battleid, cast, cfg, attacker, defender, msg, false);
	else if(cast == e_action_stabhurt)
		return BaseHurt(battleid, cast, cfg, attacker, defender, msg, false);

	return R_ERROR;
}

int LogicActionManager::Modify(unsigned battleid, unsigned cardid, const Cards::Action& cfg,  GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	//判断作用对象
	GameTeam* obj = nullptr;
	//作用目标
	unsigned aim = cfg.aim();
	if(aim == e_own)
		obj = &attacker;
	else
		obj = &defender;

	//判断执行条件
	if(!Condition(cfg, attacker, defender))
		return R_ERR_NO_DATA;

	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();
	unsigned key = cfg.value().id();
	unsigned type = cfg.value().type();
	double	value = cfg.value().v();

	if(key == e_data_type_1)
		obj->attr[obj->index].ModifyByValue(type, value);
	else if (key == e_data_type_2)
		value = obj->attr[obj->index].ModifyByRate(type, value);

	auto& game = DataGameManager::Instance()->GetData(battleid);

	if(cfg.last().type() != e_action_last_0)
	{
		//处理叠加类型
		if(R_SUCCESS != Overly(battleid, obj->uid, cardid, cfg))
		{
			char ctype = (char)CardsCfgWrap().GetCardsCfgById(cardid).e_type();
			char ltype = (char)cfg.last().type();
			char aid   = (char)cfg.id();
			char gain  = (char)cfg.gain();
			char count = (char)cfg.last().times();
			char dtype  = (char)cfg.value().type();
			char index = obj->record.Index();
			char overlay = (char)cfg.overlay();
			char star = obj->record.Star();

			BuffItem buff(ltype, ctype, aid, gain, count, dtype, cardid, star, index, overlay, value);
			DGI->AddBuff(battleid, obj->uid, dtype, buff);

		}
	}
	obj->record.AttrChange(type);
	game.SetCurrType(cfg.type());

	game.SetMessage(bmsg, aim);
	if(game.attacking == e_att)
		obj->SetMessage(bmsg->mutable_att());
	else
		obj->SetMessage(bmsg->mutable_def());

	return R_SUCCESS;
}

int LogicActionManager::Overly(unsigned battleid, unsigned uid, unsigned cardid, const Cards::Action&cfg)
{
	//同一卡牌的同种效果可以叠加
	//不用卡牌id相同的效果可以叠加
	auto& buffs = DGI->GetBuffs(battleid, uid, cfg.type());

	for(auto& buff : buffs)
	{
		unsigned overlay = buff.overlay;
		if(cfg.overlay() == overlay)
		{
			if(buff.cardid == (char)cardid || buff.aid == cfg.id())
			{
				if(overlay == e_action_overlay_1)
					buff.count += cfg.last().times();
				if(overlay == e_action_overlay_2)
					buff.value += cfg.value().v();

				return R_SUCCESS;
			}
		}
	}

	return R_ERR_NO_DATA;
}

int LogicActionManager::Batter(unsigned battleid, unsigned cardid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{

	unsigned count = cfg.count();
	//首次攻击必须执行

	if(BaseHurt(battleid, e_action_commonhurt, cfg, attacker, defender, msg, true, false) != R_ERROR)
	{
		error_log("batter error, battleid:%u, cardid: %u", battleid, cardid);
		return R_ERROR;
	}
	--count;
	while(count-- > 0 && Condition(cfg, attacker, defender))
	{
		if(BaseHurt(battleid, e_action_commonhurt, cfg, attacker, defender, msg, true))
		{
			error_log("batter error, battleid:%u, cardid: %u", battleid, cardid);
			return R_ERROR;
		}
	}

	return R_SUCCESS;
}


int LogicActionManager::AddBuff(unsigned battleid, unsigned cardid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	//判断作用目标
	GameTeam* obj = nullptr;
	if(cfg.aim() == e_own)
		obj = &attacker;
	else if(cfg.aim() == e_other)
		obj = &defender;

	//TODO:处理叠加类型
	if(R_SUCCESS != Overly(battleid, obj->uid, cardid, cfg))
	{
		char ctype = (char)CardsCfgWrap().GetCardsCfgById(cardid).e_type();
		char ltype = (char)cfg.last().type();
		char aid   = (char)cfg.id();
		char gain  = (char)cfg.gain();
		char count = (char)cfg.last().times();
		char type  = (char)cfg.value().type();
		double value = cfg.value().v();
		char index = obj->record.Index();
		char overlay = cfg.overlay();
		char star = obj->record.Star();

		BuffItem buff(ltype, ctype, aid, gain, count, type, cardid, star, index, overlay, value);
		DGI->AddBuff(battleid, obj->uid, cfg.type(), buff);
	}

	auto& game = DGI->GetData(battleid);
	game.SetCurrType(cfg.value().type());

	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();
	game.SetMessage(bmsg, cfg.aim());

	return R_SUCCESS;
}

int LogicActionManager::GainPoint(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, BattleInfoPtr* msg)
{
	unsigned point = cfg.value().v();
	attacker.AddPoint(point);

	auto& game = DataGameManager::Instance()->GetData(battleid);
	game.SetCurrType(e_action_point);

	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();

	bmsg->mutable_att()->set_addpoint(point);
	game.SetMessage(bmsg, e_own);

	return R_SUCCESS;
}

int LogicActionManager::ResetHandCards(unsigned battleid, GameTeam& attacker, BattleInfoPtr* msg)
{
	//获取手牌
	vector<CardItem>& handcards = DGI->GetHandCards(battleid, attacker.uid);

	//放入弃牌库
	for(int i = 0; i < HAND_CARD_NUM; ++i)
	{
		if(handcards[i].ud != 0)
		{
			DGI->AddCardTemp(battleid, attacker.uid, handcards[i]);
			handcards[i].Clear();
		}
	}
	vector<CardItem>& tempcards = DataGameManager::Instance()->GetTempCards(battleid, attacker.uid);
	vector<CardItem>& cardbags = DataGameManager::Instance()->GetCardBag(battleid, attacker.uid);
	//重新添加手牌
	GameBase::CreateHandCard(handcards, cardbags, tempcards);
	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();

	auto& cardbag = DGI->GetCardBag(battleid, attacker.uid);
	for(auto& card : cardbag)
	{
		card.SetMessage(bmsg->mutable_att()->mutable_cards()->add_bag());
	}

	auto& handcard = DGI->GetCardBag(battleid, attacker.uid);
	for(auto& card : handcard)
	{
		card.SetMessage(bmsg->mutable_att()->mutable_cards()->add_hand());
	}

	auto& game = DGI->GetData(battleid);
	game.SetCurrType(e_action_reset);
	game.SetMessage(bmsg, e_own);

	return R_SUCCESS;
}

int LogicActionManager::ClearBuff(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	//TODO: 作用对象
	GameTeam* obj = nullptr;
	if(cfg.aim() == e_own)
		obj = &attacker;
	else if(cfg.aim() == e_other)
		obj = &defender;

	//执行条件
	if(!Condition(cfg, attacker, defender))
	{
		//TODO:将效果字段发送前端
		return R_ERR_NO_DATA;
	}

	DGI->ClearBuff(battleid, obj->uid, cfg.value().type(), (unsigned)cfg.value().v());

	auto& game = DGI->GetData(battleid);
	game.SetCurrType(e_action_clear);

	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();
	game.SetMessage(bmsg, cfg.aim());

	return R_SUCCESS;
}

int LogicActionManager::DisableBuff(unsigned battleid, unsigned cardid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	unsigned coutDef = DGI->BuffCount(battleid, defender.uid, e_action_add_invalid);
	if(coutDef == 0)
		return R_ERR_NO_DATA;

	auto& buff = DGI->GetBuff(battleid, defender.uid, e_action_add_invalid);

	auto& attCardCfg = CardsCfgWrap().GetCardsCfgById(cardid);
	int ret = R_ERR_NO_DATA;
	if(buff.type == e_action_c_d_1)
	{
		if(cfg.type() == buff.value)
			ret = R_SUCCESS;
	}
	else if(buff.type == e_action_c_d_2)
	{
		if(attCardCfg.e_type() == buff.value)
			ret = R_SUCCESS;
	}
	else if(buff.type == e_action_c_d_3)
	{
		if(cfg.gain() == buff.value)
			ret = R_SUCCESS;
	}
	else if(buff.type == e_action_c_d_4)
	{
		if(cfg.id() == buff.value)
			ret = R_SUCCESS;
	}
	else
	{
		return R_ERROR;
	}

	if(ret == R_SUCCESS)
	{
		auto& defCardCfg = CardsCfgWrap().GetCardsCfgById(buff.cardid);
		//执行条件
		if(!Condition(defCardCfg.action(buff.star).list(buff.index), attacker, defender))
			return R_ERR_NO_DATA;
	}

	auto& game = DGI->GetData(battleid);
	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();
	game.SetMessage(bmsg, e_own);
	game.SetCurrType(e_action_buff_4);

	return R_ERR_NO_DATA;
}

int LogicActionManager::Bomb(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	if(defender.attr[defender.index].n_hp < 0)
		return R_ERR_NO_DATA;
	if(DGI->BuffCount(battleid, defender.uid, e_action_buff_2) == 0)
		return R_ERR_NO_DATA;

	if(!Condition(cfg, attacker, defender))
		return R_ERR_NO_DATA;

	auto& buff = DGI->GetBuffs(battleid, defender.uid, e_action_buff_2);

	unsigned dam = 0;
	for(auto& e: buff)
	{
		dam += e.value;
	}

	Cards::Action actionCfg;
	actionCfg.mutable_value()->set_type(e_data_type_1);
	actionCfg.mutable_value()->set_v(dam);

	attacker.record.Bomb();

	return BaseHurt(battleid, e_action_commonhurt, cfg, attacker, defender, msg, false, false);
}

int LogicActionManager::Blood(unsigned battleid, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	if(attacker.attr[attacker.index].n_hp < 0)
		return R_ERR_NO_DATA;

	if(DGI->BuffCount(battleid, attacker.uid, e_action_buff_2) == 0)
		return R_ERR_NO_DATA;

	auto& buff = DGI->GetBuff(battleid, attacker.uid, e_action_buff_2);
	auto& cfg = CardsCfgWrap().GetCardsCfgById(buff.cardid).action(buff.star).list(buff.index);

	//执行条件
	if(!Condition(cfg, attacker, defender))
		return R_ERR_NO_DATA;

	double dam = attacker.attr[attacker.index].LastDam(buff.value, false);

	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();
	//伤害转化
	auto& game = DGI->GetData(battleid);
	if(HurtTrans(battleid, dam, attacker, defender, bmsg->mutable_att()->mutable_attr()) == R_ERR_NO_DATA)
	{
		attacker.attr[attacker.index].Injure(dam);
		attacker.record.Dam(dam);
		game.SetCurrType(e_action_buff_7);
	}
	else
	{
		game.SetCurrType(e_action_buff_2);
	}
	game.SetMessage(bmsg, e_own);
	if(game.attacking == e_att)
		attacker.SetMessage(bmsg->mutable_att()->mutable_info());
	else
		attacker.SetMessage(bmsg->mutable_def()->mutable_info());

	return R_SUCCESS;
}

int LogicActionManager::ShotBack(unsigned battleid, GameTeam& attacker, GameTeam& defender, BattleInfoPtr* msg)
{
	if(!defender.record.IsShotBack())
		return R_ERR_NO_DATA;

	if(DGI->BuffCount(battleid, defender.uid, e_action_buff_1) == 0)
		return R_ERR_NO_DATA;

	auto& buff = DGI->GetBuff(battleid, defender.uid, e_action_buff_1);
	auto& cfg  = CardsCfgWrap().GetCardsCfgById(buff.cardid).action(buff.star).list(buff.index);

	auto& game = DGI->GetData(battleid);
	//切换进攻方
	game.attacking = game.attacking == e_att ? e_def : e_att;

	game.SetCurrType(e_action_buff_1);
	int ret = BaseHurt(battleid, e_action_commonhurt, cfg, defender, attacker, msg, true);
	game.attacking = game.attacking == e_att ? e_def : e_att;

	return ret;
}

void LogicActionManager::DealBuff(unsigned battleid, GameTeam& attacker, unsigned mode)
{
	auto& buffs = DGI->GetBuffs(battleid, attacker.uid);

	for(auto ita = buffs.begin(); ita != buffs.end();)
	{
		auto actions = ita->second;
		for(auto itb = actions.begin(); itb != actions.end();)
		{
			if(itb->ltype != mode)
			{
				++itb;
				continue;
			}
			if(itb->count > 0)
				itb->count--;

			if(itb->count == 0)
			{
				if(ita->first == e_action_buff_5)
					attacker.attr[attacker.index].DecAttr(itb->value, itb->type);
				itb = actions.erase(itb);
			}
			else
				++itb;
		}

		if(actions.size() == 0)
			ita = buffs.erase(ita);
		else
			++ita;
	}
}


int LogicActionManager::HurtBack(unsigned battleid, double dam, GameTeam& attacker, GameTeam& defender)
{
	if(DGI->BuffCount(battleid, attacker.uid, e_action_buff_6) == 0)
		return R_ERR_NO_DATA;

	//多个反弹buff一并执行
	auto& buffs = DGI->GetBuffs(battleid, attacker.uid, e_action_buff_6);

	CardsCfgWrap cardCfg;
	double value = 0.0;
	for(auto& e : buffs)
	{
		auto& cfg = cardCfg.GetCardsCfgById(e.cardid).action(e.star).list(e.index);
		if(!Condition(cfg, attacker, defender))
			continue;
		value += e.value * dam;
	}

	defender.record.Dam(value);
	defender.attr[defender.index].Injure(value);

	//处理受伤害次数buff
	DealBuff(battleid, attacker, e_action_last_2);

	return R_SUCCESS;
}


int LogicActionManager::HurtTrans(unsigned battleid, double value, GameTeam& attacker, GameTeam& defender, ProtoBattleBase::ProtoBattleAttr* msg)
{
	if(DGI->BuffCount(battleid, attacker.uid, e_action_buff_7) == 0)
		return R_ERR_NO_DATA;

	auto& buff = DGI->GetBuff(battleid, attacker.uid, e_action_buff_7);
	auto& cfg = CardsCfgWrap().GetCardsCfgById(buff.cardid).action(buff.star).list(buff.index);

	if(!Condition(cfg, attacker, defender))
		return R_ERR_NO_DATA;

	attacker.attr[attacker.index].ModifyByValue(buff.type, value);

	attacker.attr[attacker.index].SetMessage(msg, buff.type);

	return R_SUCCESS;
}

int LogicActionManager::Revive(unsigned battleid, GameTeam& obj, BattleInfoPtr* msg)
{
	if(obj.attr[obj.index].n_hp > 0)
		return R_ERR_NO_DATA;

	if(DGI->BuffCount(battleid, obj.uid, e_action_add_revive) == 0)
		return R_ERR_NO_DATA;

	auto& buff = DGI->GetBuff(battleid, obj.uid, e_action_add_revive);
	obj.attr[obj.index].ModifyByRate(e_type_currhp, buff.value);
	DealBuff(battleid, obj, e_action_add_revive);

	obj.record.AttrChange(e_type_currhp);

	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();
	auto& game = DGI->GetData(battleid);
	game.SetCurrType(e_action_buff_3);
	game.SetMessage(bmsg, e_own);


	if(game.attacking == e_att)
		obj.SetMessage(bmsg->mutable_def());
	else
		obj.SetMessage(bmsg->mutable_att());

	return R_SUCCESS;
}

int LogicActionManager::TempCards(unsigned battleid, const Cards::Action& cfg, GameTeam& defender, BattleInfoPtr* msg)
{
	for(int i = 0; i < cfg.temp_size(); ++i)
		DGI->AddCardBag(battleid, defender.uid, CardItem(0, cfg.temp(i), 0, e_card_temp));

	auto& game = DataGameManager::Instance()->GetData(battleid);
	game.SetCurrType(e_action_temp);
	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();

	game.SetMessage(bmsg, e_other);

	return R_SUCCESS;
}

int LogicActionManager::ExtraCards(unsigned battleid, const Cards::Action& cfg, GameTeam& attacker, BattleInfoPtr* msg)
{
	unsigned count = (unsigned)cfg.value().v();

	//从牌库中随机抽取
	vector<CardItem>& tempCards  = DGI->GetTempCards(battleid, attacker.uid);
	vector<CardItem>& cardbags   = DGI->GetCardBag(battleid, attacker.uid);
	vector<CardItem>& handcard	 = DGI->GetHandCards(battleid, attacker.uid);

	if((cardbags.size() + tempCards.size()) < count)
	{
		error_log("config_error, battlelid=%u， count=%u, bagsize=%u, tempsize=%u", battleid, count, cardbags.size(), tempCards.size());
		throw runtime_error("config_error");
	}

	if(cardbags.size() <= count)
	{
		std::copy(cardbags.begin(), cardbags.end(), std::back_inserter(handcard));
		count -= cardbags.size();
		cardbags.clear();

		//将临时卡包中的卡牌导到战斗卡包中
		std::copy(tempCards.begin(), tempCards.end(), std::back_inserter(cardbags));
		tempCards.clear();

	}

	//从战斗卡包中随机抽取
	while(count > 0 && cardbags.size() > 0)
	{
		int index = Math::GetRandomInt(cardbags.size());
		handcard.push_back(cardbags[index]);
		auto it = cardbags.begin() + index;
		swap(*it, cardbags.back());
		cardbags.pop_back();
	}

	auto& game = DataGameManager::Instance()->GetData(battleid);
	game.SetCurrType(e_action_card);
	ProtoBattleBase::ProtoBattleInfo* bmsg = msg->Add();
	game.SetMessage(bmsg, e_own);

	//发牌
	for(auto& card : cardbags)
	{
		card.SetMessage(bmsg->mutable_att()->mutable_cards()->add_bag());
	}

	for(auto& card : handcard)
	{
		card.SetMessage(bmsg->mutable_att()->mutable_cards()->add_hand());
	}

	return R_SUCCESS;
}
