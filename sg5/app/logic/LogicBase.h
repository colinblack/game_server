/*
 * LogicBase.h
 *
 *  Created on: 2015-11-20
 *      Author: Ralf
 */

#ifndef LOGICBASE_H_
#define LOGICBASE_H_

#include "Kernel.h"
#include "DataBase.h"

template<class T> class LogicBase
{
public:
	LogicBase(){}
	virtual ~LogicBase(){}

	static int Init(string path, bool allserver)
	{
		set<int> domains;
		MainConfig::GetDomains(domains);
		if(allserver)
		{
			Config::SelectDomain(*domains.begin(), *domains.begin());
			string dataPath = MainConfig::GetAllServerPath(path);
			m_dataMap[*domains.begin()] = new T(dataPath);
		}
		else
		{
			for(set<int>::iterator it=domains.begin();it!=domains.end();++it)
			{
				Config::SelectDomain(*it, *it);
				string dataPath = Config::GetPath(path, *it);
				m_dataMap[*it] = new T(dataPath);
			}
		}

		for(map<int, DataBase*>::iterator it=m_dataMap.begin();it!=m_dataMap.end();++it)
		{
			Config::SelectDomain(it->first, it->first);
			int ret = it->second->Init();
			if(ret && ret != R_ERR_NO_DATA)
			{
				error_log("init %s fail, ret=%d", path.c_str(), ret);
				return R_ERR_DB;
			}
		}

		return 0;
	}

	static T* GetData()
	{
		if(m_dataMap.size() == 1)
			return (T*)m_dataMap.begin()->second;

		int serverId = 0;
		Config::GetDomain(serverId);
		if(!m_dataMap.count(serverId))
		{
			error_log("get data fail, server=%d", serverId);
			return NULL;
		}

		return (T*)m_dataMap[serverId];
	}

	static int Sig(int sig)
	{
		Time::UpdateGlobalTime();

		if(sig == SIGRTMAX - 1)
			Save();
		else
		{
			for(map<int, DataBase*>::iterator it=m_dataMap.begin();it!=m_dataMap.end();++it)
			{
				try
				{
					Config::SelectDomain(it->first, it->first);
					int ret = it->second->Sig(sig);
					if(ret)
						error_log("server %d sig %d fail, ret=%d", it->first, sig, ret);
				}
				catch(const std::exception& e)
				{
					error_log("server %d sig %d fail", it->first, sig);
				}
			}
		}

		return 0;
	}

	static int Exit()
	{
		Time::UpdateGlobalTime();

		Save();

		for(map<int, DataBase*>::iterator it=m_dataMap.begin();it!=m_dataMap.end();++it)
		{
			Config::SelectDomain(it->first, it->first);
			delete it->second;
		}

		m_dataMap.clear();

		return 0;
	}

protected:
	static int Save()
	{
		for(map<int, DataBase*>::iterator it=m_dataMap.begin();it!=m_dataMap.end();++it)
		{
			try
			{
				Config::SelectDomain(it->first, it->first);
				int ret = it->second->Save();
				if(ret)
					error_log("server %d save fail, ret=%d", it->first, ret);
			}
			catch(const std::exception& e)
			{
				error_log("server %d save fail", it->first);
			}
		}

		return 0;
	}
	static map<int, DataBase*> m_dataMap;
};
template<class T> map<int, DataBase*> LogicBase<T>::m_dataMap;

#endif /* LOGICBASE_H_ */
