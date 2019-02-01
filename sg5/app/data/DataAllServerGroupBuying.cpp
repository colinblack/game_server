#include "DataAllServerGroupBuying.h"

CDataAllServerGroupBuying::CDataAllServerGroupBuying(string path)
	: DataBase(path)
{
	m_msg = new AllServerGroupBuy::GroupBuing();
}

int CDataAllServerGroupBuying::Init()
{
	int ret = Parse();

	if(ret)
		return ret;

	m_data.Parse(*(AllServerGroupBuy::GroupBuing *)m_msg);

	((AllServerGroupBuy::GroupBuing *)m_msg)->Clear();

	return 0;
}

int CDataAllServerGroupBuying::Save()
{
	m_data.Serialize((AllServerGroupBuy::GroupBuing *)m_msg);

	int ret = Serialize();
	if(ret)
		return ret;

	//debug_log("%s",m_msg->DebugString().c_str());

	((AllServerGroupBuy::GroupBuing *)m_msg)->Clear();

	return 0;
}

int CDataAllServerGroupBuying::SetGroupBuyingMsg(unsigned uid, Json::Value & result)
{
	Json::Value itemval(Json::arrayValue); //参加团购的人数

	for(int i = 1; i <= max_items_nums; ++i)
	{
		Json::Value useritem;
		useritem["isin"] = false;

		if (m_data.items.count(i))
		{
			useritem["users"] = (int)m_data.items[i].customers.size();

			if (m_data.items[i].customers.count(uid))
			{
				useritem["isin"] = true;
			}
		}
		else
		{
			useritem["users"] = 0;
		}

		itemval.append(useritem);
	}

	result["groupbuy"] = itemval;

	return 0;
}

int CDataAllServerGroupBuying::JoinGroupBuying(unsigned uid, unsigned id, unsigned stage)
{
	//不管之前的团购项目id是否存在，直接赋值
	m_data.items[id].id = id;

	m_data.items[id].customers[uid].uid = uid;
	m_data.items[id].customers[uid].join_stage = stage;  //参加阶段
	m_data.items[id].customers[uid].back_stage = stage;  //返还阶段

	return 0;
}

int CDataAllServerGroupBuying::UpdateBackStage(unsigned uid, unsigned id, unsigned stage)
{
	m_data.items[id].customers[uid].back_stage = stage;  //返还阶段

	return 0;
}

DataGroupBuyingItem & CDataAllServerGroupBuying::GetGroupItem(unsigned id)
{
	if (m_data.items.count(id))
	{
		return m_data.items[id];
	}

	throw runtime_error("id_not_in_group");
}

bool CDataAllServerGroupBuying::IsUserJoinGroup(unsigned id, unsigned uid)
{
	if (m_data.items.count(id) && m_data.items[id].customers.count(uid))
	{
		return true;
	}

	return false;
}

DataGroupBuyingUser & CDataAllServerGroupBuying::GetGroupUser(unsigned id, unsigned uid)
{
	if (m_data.items.count(id) && m_data.items[id].customers.count(uid))
	{
		return m_data.items[id].customers[uid];
	}

	throw runtime_error("user_not_in_group");
}

int CDataAllServerGroupBuying::ResetGroupBuying(unsigned version)
{
	m_data.version = version;

	m_data.items.clear();

	//将改变的内容写入映射的文件中
	Save();
}

