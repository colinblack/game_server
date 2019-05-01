/*
 * LogicTimeLimitPropMgr.cpp
 *
 *  Created on: 2016-11-29
 *      Author: dawx62fac
 */

#include "LogicTimeLimitPropMgr.h"

DBCTimeLimitPropWrap::DBCTimeLimitPropWrap(unsigned index)
	: container_(DataTimeLimitPropMgr::Instance())
	, index_(_index(index))
	, data_(container_->m_data->data[index_])
	, cfg_(EquipCfgWrap().GetTimeLimitProp(data_.id))
{

}

DBCTimeLimitPropWrap::DBCTimeLimitPropWrap(unsigned uid, unsigned id)
	: container_(DataTimeLimitPropMgr::Instance())
	, index_(_id2index(uid, id))
	, data_(container_->m_data->data[index_])
	, cfg_(EquipCfgWrap().GetTimeLimitProp(data_.id))
{

}

unsigned DBCTimeLimitPropWrap::_index(int index)
{
	if (index < 0 || index >= DB_TIME_LIMIT_PROP_FACTOR*DB_BASE_BUFF)
	{
		error_log("index_params_error index: %d", index);
		throw std::runtime_error("index_params_error");
	}

	return index;
}

unsigned DBCTimeLimitPropWrap::_id2index(unsigned uid, unsigned id)
{
	//
	return container_->GetIndex(uid, id);
}

void DBCTimeLimitPropWrap::Refresh()
{
	data_.op_time = Time::GetGlobalTime();

	Save();
}

bool DBCTimeLimitPropWrap::IsValid() const
{
	return (LostTime() >= Time::GetGlobalTime());
}

unsigned DBCTimeLimitPropWrap::OpTime() const
{
	return data_.op_time;
}

unsigned DBCTimeLimitPropWrap::LostTime() const
{
	return data_.op_time + cfg_.valid_peroid();
}

int DBCTimeLimitPropWrap::AttrType() const
{
	return cfg_.attribute();
}

int DBCTimeLimitPropWrap::AttrValue() const
{
	return cfg_.value();
}

void DBCTimeLimitPropWrap::FullMessage(User::TimeLimtPropItem* obj) const
{
	obj->set_id(data_.id);
	obj->set_expire_time(LostTime());
}

//////////////////////////////////////////////////////////////////////////////////
LogicTimeLimitPropMgr::LogicTimeLimitPropMgr()
{
	for (int type = e_type1; type <= e_type5; type++)
	{
		m_notify_table[(AttrType)type] = &LogicTimeLimitPropMgr::NotifyBuildingsStatus;
		m_lost_table[(AttrType)type] = &LogicTimeLimitPropMgr::OnLostBuildingsProp;
	}

	//
	try
	{
		typedef std::map<unsigned, std::map<unsigned, unsigned> > T_MAP;
		const T_MAP&  all = DataTimeLimitPropMgr::Instance()->GetAllMap();
		T_MAP::const_iterator it = all.begin();
		for (; it != all.end(); ++it)
		{
			std::map<unsigned, unsigned>::const_iterator it_user = it->second.begin();
			for (; it_user != it->second.end(); ++it_user)
			{
				DBCTimeLimitPropWrap prop(it_user->second);
				if (prop.IsValid())
				{
					attr_queue_.push_back(prop);
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		error_log("%s", e.what());
	}
}

void LogicTimeLimitPropMgr::FullMessage(unsigned uid, ::google::protobuf::RepeatedPtrField< ::User::TimeLimtPropItem >* obj) const
{
	std::vector<unsigned> vIndexs;
	DataTimeLimitPropMgr::Instance()->GetIndexs(uid, vIndexs);
	for (size_t i = 0; i < vIndexs.size(); i++)
	{
		DBCTimeLimitPropWrap prop(vIndexs[i]);
		if (prop.IsValid())
		{
			prop.FullMessage(obj->Add());
		}
	}
}

void LogicTimeLimitPropMgr::UseProp(unsigned uid, unsigned id)
{
	DBCTimeLimitPropWrap prop(uid, id);
	RemoveUserFromAttrQueue(uid, id);
	//完成上次道具的数据结算
	OnLost(prop);
	//prop
	prop.Refresh();

	attr_queue_.push_back(prop);
	//更新对应数据
	Notify(prop);
}

void LogicTimeLimitPropMgr::Notify(const DBCTimeLimitPropWrap& prop)
{
	std::map<AttrType, NotifyImpl>::iterator it
					= m_notify_table.find((AttrType)prop.AttrType());
	if (it != m_notify_table.end())
	{
		NotifyImpl impl = it->second;
		if (impl != NULL)
		{
			(this->*impl)(prop);
		}
	}
}

void LogicTimeLimitPropMgr::OnLost(const DBCTimeLimitPropWrap& prop)
{
	std::map<AttrType, OnLostImpl>::iterator it
					= m_lost_table.find((AttrType)prop.AttrType());
	if (it != m_lost_table.end())
	{
		OnLostImpl impl = it->second;
		if (impl != NULL)
		{
			(this->*impl)(prop);
		}
	}
}

int LogicTimeLimitPropMgr::AttrType2BuildType(AttrType type)
{
	if (type >= e_type1 && type <= e_type5)
	{
		return type;
	}
	else
	{
		error_log("AttrType: %d", type);
		throw std::runtime_error("not_valid_build_attr_type");
	}
}

LogicTimeLimitPropMgr::AttrType LogicTimeLimitPropMgr::BuildType2AttrType(int type)
{
	if (type <= 0  || type >= DataBuildingManager::BUID_TYPES)
	{
		error_log("BuildType: %d", type);
		throw std::runtime_error("build_type_params_error");
	}

	return (AttrType)type;
}

void LogicTimeLimitPropMgr::NotifyBuildingsStatus(const DBCTimeLimitPropWrap& prop)
{
	int type = AttrType2BuildType((AttrType)prop.AttrType());
	LogicBuildManager::Instance()->SyncYield(prop.Obj().uid, type);
}


void LogicTimeLimitPropMgr::OnLostBuildingsProp(const DBCTimeLimitPropWrap& prop)
{
	DBCUserBaseWrap(prop.Obj().uid).RestoreResource();
}

void LogicTimeLimitPropMgr::OnTimer1()
{
	for (std::deque<_AttrItem>::iterator it = attr_queue_.begin();
				it != attr_queue_.end();)
	{
		try
		{
			--it->left_time;

			if (it->left_time <= 0)
			{
				DBCTimeLimitPropWrap prop(it->uid, it->id);
				if (! prop.IsValid())
				{
					it = attr_queue_.erase(it);

					OnLoseEfficacy(prop);

					continue;
				}
			}
		}
		catch(const std::exception& e)
		{
			(void)e;
		}

		++it;
	}
}


void LogicTimeLimitPropMgr::Online(unsigned uid)
{
	DataTimeLimitPropMgr::Instance()->Online(uid);

	std::vector<unsigned> vIndexs;
	DataTimeLimitPropMgr::Instance()->GetIndexs(uid, vIndexs);
	for (size_t i = 0; i < vIndexs.size(); i++)
	{
		DBCTimeLimitPropWrap prop(vIndexs[i]);
		if (prop.IsValid())
		{
			attr_queue_.push_back(_AttrItem(prop));
		}
	}
}

int LogicTimeLimitPropMgr::GetBuildsIndex(unsigned uid, int type)
{
	std::vector<unsigned> vIndexs;
	DataTimeLimitPropMgr::Instance()->GetIndexs(uid, vIndexs);
	for (size_t i = 0; i < vIndexs.size(); i++)
	{
		DBCTimeLimitPropWrap prop(vIndexs[i]);

		if (prop.AttrType() == BuildType2AttrType(type))
		{
			return vIndexs[i];
		}
	}

	return -1;
}

unsigned LogicTimeLimitPropMgr::GetBuildAddFactor(unsigned uid, int type)
{
	std::vector<unsigned> vIndexs;
	DataTimeLimitPropMgr::Instance()->GetIndexs(uid, vIndexs);
	for (size_t i = 0; i < vIndexs.size(); i++)
	{
		DBCTimeLimitPropWrap prop(vIndexs[i]);
		if (prop.AttrType() == BuildType2AttrType(type))
		{
			if (prop.IsValid())
			{
				return prop.AttrValue();
			}
			else
			{
				return 0;
			}
		}
	}

	return 0;
}

void LogicTimeLimitPropMgr::OnLoseEfficacy(const DBCTimeLimitPropWrap& prop)
{
	OnLost(prop);

	Notify(prop);
}


void LogicTimeLimitPropMgr::Offline(unsigned uid)
{
	RemoveUserFromAttrQueue(uid);
}

void LogicTimeLimitPropMgr::RemoveUserFromAttrQueue(unsigned uid)
{

	for (std::deque<_AttrItem>::iterator it = attr_queue_.begin();
			it != attr_queue_.end();)
	{
		if (it->uid == uid)
		{
			it = attr_queue_.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void LogicTimeLimitPropMgr::RemoveUserFromAttrQueue(unsigned uid, unsigned id)
{
	for (std::deque<_AttrItem>::iterator it = attr_queue_.begin();
				it != attr_queue_.end();)
	{
		if (it->uid == uid && it->id == id)
		{
			it = attr_queue_.erase(it);
			return ;
		}
		else
		{
			++it;
		}
	}
}
