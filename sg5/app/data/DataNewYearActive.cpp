/*
 * DataNewYearActive.cpp
 *
 *  Created on: 2018年1月25日
 *      Author: Administrator
 */

#include "DataNewYearActive.h"
#include "DataUserBasic.h"
#include "ActivityConfig.h"

CDataNewYearActive::CDataNewYearActive(const string & path) :
		DataBase(path)
{
	m_msg = new NewYearActive::NewYearActive();
	m_sync_ts = 0;
}

CDataNewYearActive::~CDataNewYearActive()
{
}

int CDataNewYearActive::Init()
{
	int ret = 0;
	ret = Parse();
	if (ret)
	{
		return ret;
	}
	m_data.parse((NewYearActive::NewYearActive *)m_msg);

	((NewYearActive::NewYearActive *)m_msg)->Clear();

	ActInfoConfig actconfig(CONFIG_NEWYEAR_ACTIVE);
	if (m_data.version != actconfig.Version())
	{
		m_data.Clear();
		m_data.version = actconfig.Version();
	}
	m_sync_ts = Time::GetGlobalTime();

	return 0;
}

int CDataNewYearActive::Save()
{
	int ret = 0;
	m_data.serialize((NewYearActive::NewYearActive *)m_msg);
	ret = Serialize();
	if (ret)
	{
		return ret;
	}

	((NewYearActive::NewYearActive *)m_msg)->Clear();

	return 0;
}

int CDataNewYearActive::Sig(int sig)
{
	return 0;
}

int CDataNewYearActive::GetRank(Json::Value &result)
{
	result = Json::Value(Json::arrayValue);
	vector<DataNewYearActiveRank>::iterator itr = m_data.ranks.begin();
	for (; itr != m_data.ranks.end(); ++itr)
	{
		Json::Value item;
		item["uid"] = itr->uid;
		item["c"] = itr->count;
		item["n"] = itr->name;
		item["pic"] = itr->pic;
		result.append(item);
		if (result.size() >= DATA_NEW_YEAR_ACTIVE_RANK_LEN)
		{
			break;
		}
	}
	return 0;
}

int CDataNewYearActive::GetLastHistory(Json::Value &result)
{
	result = Json::Value(Json::arrayValue);
	list<DataNewYearActiveHistory>::iterator it = m_data.historys.begin();
	for (; it != m_data.historys.end() && result.size() < DATA_NEW_YEAR_ACTIVE_HISTORY_LEN; ++it)
	{
		result.append(it->toJson());
	}
	return 0;
}

int CDataNewYearActive::GetUserHistory(unsigned uid, unsigned userid, bool &can, Json::Value &result)
{
	result = Json::Value(Json::arrayValue);
	list<DataNewYearActiveUser> &users = m_data.users;
	list<DataNewYearActiveUser>::iterator itr = find(users.begin(), users.end(), uid);
	if (itr != users.end())
	{
		itr->reset();
		list<DataNewYearActiveHistory>::reverse_iterator it = itr->history.rbegin();
		for (; it != itr->history.rend() && result.size() < DATA_NEW_YEAR_ACTIVE_HISTORY_LEN; ++it)
		{
			result.append(it->toJson());
		}
		if (uid != userid && itr->uids.count(userid))
		{
			can = false;
		}
	}

	return 0;
}

int CDataNewYearActive::AddRank(const DataNewYearActiveRank &data)
{
	vector<DataNewYearActiveRank> &ranks = m_data.ranks;
	vector<DataNewYearActiveRank>::iterator itr = find(ranks.begin(), ranks.end(), data.uid);
	if (itr != ranks.end())
	{
		ranks.erase(itr);
	}
	if (ranks.size() >= DATA_NEW_YEAR_ACTIVE_RANK_LEN && data.count < ranks.back().count)
	{
		return 0;
	}
	for (itr = ranks.begin(); itr != ranks.end() && itr->count >= data.count; ++itr)
	{
	}
	ranks.insert(itr, data);
	if (ranks.size() > DATA_NEW_YEAR_ACTIVE_RANK_LEN)
	{
		ranks.pop_back();
	}
	return 0;
}

int CDataNewYearActive::AddInfo(unsigned uid, unsigned userid, unsigned type, unsigned equid, unsigned count, bool &can)
{
	can = true;
	if (!IsValidUid(uid) || !IsValidUid(userid) || uid == userid)
	{
		return R_ERR_PARAM;
	}

	int ret = 0;
	list<DataNewYearActiveUser> &users = m_data.users;

	DataNewYearActiveRank rank;
	rank.uid = userid;
	DataUserBasic userBasic;
	CDataUserBasic dbUserBasic;
	if (0 == dbUserBasic.GetUserBasicLimitWithoutPlatform(userid, userBasic))
	{
		rank.name = userBasic.name;
		rank.pic = userBasic.figure_url;
	}

	list<DataNewYearActiveUser>::iterator other_itr = find(users.begin(), users.end(), userid);
	if (other_itr == users.end())
	{
		DataNewYearActiveUser user;
		user.uid = userid;
		user.count = 1;
		user.ts = Time::GetGlobalTime();
		user.uids.insert(uid);

		//add history
		DataNewYearActiveHistory item;
		item.f_uid = uid;
		item.t_uid = userid;
		item.ts = Time::GetGlobalTime();
		item.type = type;
		item.equid = equid;
		item.equc = count;
		if (0 == dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, userBasic))
		{
			item.f_name = userBasic.name;
		}
		if (0 == dbUserBasic.GetUserBasicLimitWithoutPlatform(userid, userBasic))
		{
			item.t_name = userBasic.name;
		}

		user.history.push_back(item);
		users.push_back(user);
		rank.count = 1;

		m_data.historys.push_back(item);
	}
	else
	{
		other_itr->reset();

		if (other_itr->uids.count(uid))
		{
			can = false;
			return 0;
		}
		other_itr->uids.insert(uid);

		//add history
		DataNewYearActiveHistory item;
		item.f_uid = uid;
		item.t_uid = userid;
		item.ts = Time::GetGlobalTime();
		item.type = type;
		item.equid = equid;
		item.equc = count;
		if (0 == dbUserBasic.GetUserBasicLimitWithoutPlatform(uid, userBasic))
		{
			item.f_name = userBasic.name;
		}
		if (0 == dbUserBasic.GetUserBasicLimitWithoutPlatform(userid, userBasic))
		{
			item.t_name = userBasic.name;
		}

		other_itr->history.push_back(item);
		if (other_itr->history.size() > DATA_NEW_YEAR_ACTIVE_HISTORY_LEN)
		{
			other_itr->history.pop_front();
		}
		other_itr->count += 1;
		rank.count = other_itr->count;
		m_data.historys.push_back(item);
	}

	if (m_data.historys.size() > DATA_NEW_YEAR_ACTIVE_HISTORY_LEN)
	{
		m_data.historys.pop_front();
	}

	AddRank(rank);

	Sync();

	return 0;
}

int CDataNewYearActive::Sync()
{
	if (Time::GetGlobalTime() - m_sync_ts < 600)
	{
		return 0;
	}
	m_sync_ts = Time::GetGlobalTime();

	return Save();
}

