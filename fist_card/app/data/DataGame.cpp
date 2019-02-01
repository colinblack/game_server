/*
 * DataGame.cpp
 *
 *  Created on: 2018年11月28日
 *      Author: colin
 */

#include "DataGame.h"

int DataGameManager::OnInit()
{
	for(unsigned i = 0; i < MEMORY_GAME_NUM; ++i)
	{
		if(m_data->item[i].id != 0)
		{
			total_match_[m_data->item[i].id] = i;
		}
		else
		{
			free_index_.insert(i);
		}
	}

	return 0;
}


GameItem& DataGameManager::GetData(unsigned battleid)
{
	if(total_match_.count(battleid) == 0)
		throw runtime_error("no_data");
	unsigned index = total_match_[battleid];

	return m_data->item[index];
}

unsigned DataGameManager::CreateGame()
{
	unsigned i = GetFreeIndex();
	if(i == (unsigned)-1)
	{
		error_log("free index is empty");
		return (unsigned)-1;
	}

	free_index_.erase(i);
	unsigned battleid = i+1;
	m_data->item[i].id = battleid;
	total_match_[battleid] = i;

	return battleid;
}

int DataGameManager::AddUser(unsigned uid, unsigned battleid, unsigned level)
{
	if(total_match_.count(battleid) == 0)
		return R_ERR_PARAM;

	unsigned index = total_match_[battleid];
	unsigned& count = m_data->item[index].count;

	if(count == 0)
	{
		m_data->item[index].att.uid = uid;
		m_data->item[index].att.level = level;
		m_data->item[index].att.left_point = MAX_POINTS;
		m_data->item[index].CurAtt(&(m_data->item[index].att));
		SetNoCritCount(level, m_data->item[index].att.n_c);
	}
	else if(count == 1)
	{
		m_data->item[index].def.uid = uid;
		m_data->item[index].def.level = level;
		m_data->item[index].def.left_point = MAX_POINTS;
		m_data->item[index].CurDef(&(m_data->item[index].def));
		SetNoCritCount(level, m_data->item[index].def.n_c);
	}
	else
	{
		return R_ERROR;
	}

	++count;
	return R_SUCCESS;
}

int DataGameManager::SetHeroAttr(unsigned uid, unsigned battleid, unsigned heroid, const HeroAttrItem& attr)
{
	if(total_match_.count(battleid) == 0)
		return R_ERR_PARAM;

	unsigned index = total_match_[battleid];

	HeroAttrItem* item = nullptr;
	if(uid == m_data->item[index].att.uid)
	{
		unsigned& num = m_data->item[index].att.hero_num;
		if(num == 2)
			return R_ERROR;

		item = &(m_data->item[index].att.attr[num++]);
	}
	else if(uid == m_data->item[index].def.uid)
	{
		unsigned& num = m_data->item[index].def.hero_num;
		if(num == 2)
			return R_ERROR;

		item = &(m_data->item[index].def.attr[num++]);
	}
	else
	{
		return R_ERROR;
	}

	item->id			= attr.id;
	item->hp			= attr.hp;
	item->n_hp			= attr.n_hp;
	item->att 			= attr.att;
	item->def 			= attr.def;
	item->crit 			= attr.crit;
	item->acrit 		= attr.acrit;
	item->dodge 		= attr.dodge;
	item->adodge 		= attr.adodge;
	item->critt 		= attr.critt;
	item->speed			= attr.speed;
	item->battlePower 	= attr.battlePower;

	return R_SUCCESS;
}

void DataGameManager::SetCardBag(unsigned battleid, unsigned id, vector<CardItem>& cardbags)
{
	cards_bag_[battleid][id].assign(cardbags.begin(), cardbags.end());
}

vector<CardItem>& DataGameManager::GetCardBag(unsigned battleid, unsigned id)
{
	if(cards_bag_.count(battleid) == 0 || cards_bag_[battleid].count(id) == 0)
	{
		error_log("param error, id=%u, battleid=%u", id, battleid);
		throw runtime_error("param_error");
	}

	return cards_bag_[battleid][id];
}

void DataGameManager::AddCardTemp(unsigned battleid, unsigned id, CardItem& card)
{
	temp_cards_[battleid][id].push_back(card);
}

void DataGameManager::AddCardBag(unsigned battleid, unsigned id, CardItem card)
{
	temp_cards_[battleid][id].push_back(std::move(card));
}

vector<CardItem>& DataGameManager::GetTempCards(unsigned battleid, unsigned id)
{
	return temp_cards_[battleid][id];
}

vector<CardItem>& DataGameManager::GetHandCards(unsigned battleid, unsigned id)
{
	return hand_cards_[battleid][id];
}

bool DataGameManager::IsValid(unsigned battleid)
{
	return total_match_.count(battleid) == 0 ? false : true;
}


bool DataGameManager::Impl(unsigned battleid)
{
	unsigned index 	 = total_match_[battleid];
	auto &item = m_data->item[index];
	unsigned att_size = m_data->item[index].att.hero_num;
	unsigned def_size = m_data->item[index].def.hero_num;

	if(item.attacking == e_att)
	{
		if((int)item.def.attr[item.def.index].n_hp < 0)
		{
			++item.def.index;
			item.def.record.died = 1;
			item.def.ResetLastHurt();
		}
	}
	else if(item.attacking == e_def)
	{
		if((int)item.att.attr[item.att.index].n_hp < 0)
		{
			++item.att.index;
			item.att.record.died = 1;
			item.att.ResetLastHurt();
		}

	}

	if(item.att.index == att_size || item.def.index == def_size)
	{
		if(item.att.index  <att_size)
			m_data->item[index].winner = att_win;

		if(item.def.index  <att_size)
			m_data->item[index].winner = def_win;

		return true;
	}

	return false;
}

void DataGameManager::SetNoCritCount(unsigned level,  unsigned& n_c)
{
	unsigned li = 0;
	for(auto& e : BDC_S(crit_l))
	{
		if(level <= e)
			break;
		++li;
	}
	if(li >= ConfigManager::Instance()->battleDemoConfig.m_config.crit_l_size())
		li = ConfigManager::Instance()->battleDemoConfig.m_config.crit_l_size() - 1;
	n_c = BDC_A(crit_c, li);
}

void DataGameManager::Clear(unsigned battleid)
{
	if(total_match_.count(battleid))
	{
		unsigned i = total_match_[battleid];

		cards_bag_.erase(battleid);
		hand_cards_.erase(battleid);
		temp_cards_.erase(battleid);
		memset(&(m_data->item[i]), 0, sizeof(GameItem));
		free_index_.insert(i);
		total_match_.erase(battleid);
	}
}


int DataGameManager::ClearBuff(unsigned battleid, unsigned id, unsigned type, unsigned value)
{
	if(type == e_action_c_d_1)
	{
		buff_[battleid][id].erase(type);
	}
	else
	{
		for(auto ita = buff_[battleid][id].begin(); ita != buff_[battleid][id].end();)
		{
			auto actions = ita->second;
			for(auto itb = actions.begin(); itb != actions.end();)
			{
				char v = 0;
				if(type == e_action_c_d_2)
					v = itb->ctype;
				else if(type == e_action_c_d_3)
					v = itb->gain;
				else if(type == e_action_c_d_4)
					v = itb->aid;
				else
					return R_ERROR;

				if(v == (char)value)
					itb = actions.erase(itb);
				else
					++itb;
			}
			if(actions.size() == 0)
				ita = buff_[battleid][id].erase(ita);
			else
				++ita;
		}
	}

	return R_SUCCESS;
}

