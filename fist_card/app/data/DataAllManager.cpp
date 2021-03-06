#include "DataAllManager.h"

int DataItemManager::Init(unsigned uid)
{
	Online(uid);

	//初始化道具ud
	unsigned maxud = 0;  //初始化ud = 1
	map<uint32_t, uint32_t>::reverse_iterator reviter = m_map[uid].rbegin();

	if (reviter != m_map[uid].rend() && maxud < reviter->first)
	{
		maxud = reviter->first;
	}

	m_userMaxUd[uid] = maxud;

	if (m_PropsUd.count(uid))
	{
		m_PropsUd[uid].clear();
	}

	//初始化道具ud与props_id之间的映射关系
	for(; reviter != m_map[uid].rend(); ++reviter)
	{
		unsigned index = reviter->second;
		m_PropsUd[uid][m_data->data[index].props_id].push_back(reviter->first);
	}

	return 0;
}

unsigned DataItemManager::GetUserNextUd(unsigned uid)
{
	m_userMaxUd[uid] = m_userMaxUd[uid] + 1;

	return m_userMaxUd[uid];
}

bool DataItemManager::IsPropsExist(unsigned uid, unsigned propsid)
{
	if (m_PropsUd.count(uid)
			&& m_PropsUd[uid].count(propsid)
			&& m_PropsUd[uid][propsid].size() > 0)
	{
		return true;
	}

	return false;
}

unsigned DataItemManager::GetPropsUd(unsigned uid, unsigned propsid)
{
	if (m_PropsUd.count(uid)
			&& m_PropsUd[uid].count(propsid)
			&& m_PropsUd[uid][propsid].size() > 0)
	{
		return m_PropsUd[uid][propsid][0u];
	}

	return -1;
}

int DataItemManager::AddNewProps(DataItem & propsitem)
{
	unsigned index = NewItem(propsitem.uid, propsitem.id);

	DataItem & item = GetDataByIndex(index);
	item = propsitem;

	m_PropsUd[propsitem.uid][propsitem.props_id].push_back(propsitem.id);

	return 0;
}

int DataItemManager::DelProps(DataItem & propsitem)
{
	unsigned uid = propsitem.uid;
	unsigned ud = propsitem.id;

	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		error_log("get props error. uid=%u, id=%u", uid, ud);
		throw std::runtime_error("get_props_error");
	}

	unsigned index = m_map[uid][ud];

	//将删除操作立即加入到dbc的更新队列中
	//mark删除状态
	m_data->MarkDel(index);
	//添加至操作队列
	AddSave(index);

	//删除映射
	unsigned propsid = propsitem.props_id;

	m_map[uid].erase(ud);  //清除映射

	vector<unsigned>::iterator piter = find(m_PropsUd[uid][propsid].begin(), m_PropsUd[uid][propsid].end(), ud);

	if (piter != m_PropsUd[uid][propsid].end())
	{
		//删除
		m_PropsUd[uid][propsid].erase(piter);
	}

	if (m_PropsUd[uid][propsid].empty())
	{
		m_PropsUd[uid].erase(propsid);
	}

	return 0;
}

int DataCardsManager::Init(unsigned uid)
{
	Online(uid);
	auto riter = m_map[uid].rbegin();
	unsigned maxud = 0;
	if(riter != m_map[uid].rend() && maxud < riter->first)
	{
		maxud = riter->first;
	}

	m_userMaxUd[uid] = maxud;

	if(m_cardsUd.count(uid))
	{
		m_cardsUd[uid].clear();
	}

	for(;riter != m_map[uid].rend(); ++riter)
	{
		unsigned index = riter->second;
		m_cardsUd[uid][m_data->data[index].card_id].push_back(riter->first);
	}

	return 0;
}

unsigned DataCardsManager::GetUserNextUd(unsigned uid)
{
	m_userMaxUd[uid] = m_userMaxUd[uid] + 1;

	return m_userMaxUd[uid];
}

unsigned DataCardsManager::GetCardCount(unsigned uid, unsigned cardid)
{
	return m_cardsUd[uid][cardid].size();
}

bool DataCardsManager::IsCardsExist(unsigned uid, unsigned cardid)
{
	if (m_cardsUd.count(uid)
			&& m_cardsUd[uid].count(cardid)
			&& m_cardsUd[uid][cardid].size() > 0)
	{
		return true;
	}

	return false;
}

int DataCardsManager::AddNewCard(DataCards& carditem)
{
	unsigned index = NewItem(carditem.uid, carditem.id);

	DataCards & item = GetDataByIndex(index);
	item = carditem;

	m_cardsUd[carditem.uid][carditem.card_id].push_back(carditem.id);

	return 0;
}

int DataCardsManager::DelCard(DataCards& carditem)
{
	unsigned uid = carditem.uid;
	unsigned ud = carditem.id;

	if (!m_map.count(uid) || !m_map[uid].count(ud))
	{
		error_log("get props error. uid=%u, id=%u", uid, ud);
		throw std::runtime_error("get_props_error");
	}

	unsigned index = m_map[uid][ud];

	//将删除操作立即加入到dbc的更新队列中
	//mark删除状态
	m_data->MarkDel(index);
	//添加至操作队列
	AddSave(index);

	//删除映射
	unsigned cardid = carditem.card_id;

	m_map[uid].erase(ud);  //清除映射

	auto piter = find(m_cardsUd[uid][cardid].begin(), m_cardsUd[uid][cardid].end(), ud);

	if (piter != m_cardsUd[uid][cardid].end())
	{
		//删除
		m_cardsUd[uid][cardid].erase(piter);
	}

	if (m_cardsUd[uid][cardid].empty())
	{
		m_cardsUd[uid].erase(cardid);
	}

	return 0;
}


int DataUnlockCardsManager::AddNewItem(DataUnlockCards& item)
{
	unsigned index = NewItem(item.uid, item.id);
	DataUnlockCards & carditem = GetDataByIndex(index);
	carditem = item;

	return 0;
}
