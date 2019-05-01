/*
 * DataSingleton.h
 *
 *  Created on: 2016-8-16
 *      Author: Ralf
 */

#ifndef DATASINGLETON_H_
#define DATASINGLETON_H_

#include "Common.h"
#include "DBCBase.h"

/*
 * 数据管理器的基类，继承该类后会在LogicManager中调用各个函数和虚函数
 */
class DataSingletonBase
{
public:
	virtual ~DataSingletonBase(){}
	DataSingletonBase(){}
	virtual void CallDestroy() = 0;
	virtual int Init() = 0;
	virtual void Exit() = 0;
	virtual void Timer1() = 0;
	virtual void Timer2() = 0;
	virtual int OnInit() = 0;
	virtual void OnExit() = 0;
	virtual void OnTimer1() = 0;
	virtual void OnTimer2() = 0;
	virtual unsigned GetFreeCount() = 0;
	virtual unsigned GetFreeIndex() = 0;
	virtual bool IsFull() = 0;
	virtual bool IsNeedClear() = 0;
	virtual bool IsWorking() = 0;
	virtual int OnCheck() = 0;
	virtual void DoSave(unsigned uid) = 0;
	virtual void DoClear(unsigned uid) = 0;
	virtual void DebugLog() = 0;
};

/*
 * shm中的数据状态，dbc同步用
 */
enum MyStatus
{
	e_MyStatus_empty			= 0,
	e_MyStatus_normal			= 1,
	e_MyStatus_need_add			= 2,
	e_MyStatus_need_set			= 3,
	e_MyStatus_need_del			= 4,
	e_MyStatus_adding			= 5,
	e_MyStatus_setting			= 6,
	e_MyStatus_deleting			= 7,

	e_MyStatus_max
};
struct MyDataPlus
{
	unsigned ts;
	byte status;
	bool Empty()
	{
		return status == e_MyStatus_empty;
	}
	bool NeedWork()
	{
		return status == e_MyStatus_need_add || status == e_MyStatus_need_set || status == e_MyStatus_need_del;
	}
	bool Working()
	{
		return status == e_MyStatus_setting || status == e_MyStatus_deleting || status == e_MyStatus_adding;
	}
	bool Aavaliable()
	{
		return status != e_MyStatus_need_del && status != e_MyStatus_deleting;
	}
	bool ChangeStatus(unsigned s)
	{
		if(s < e_MyStatus_max)
		{
			switch(status)
			{
			case e_MyStatus_empty:
				if(s == e_MyStatus_need_add || s == e_MyStatus_normal)
				{
					status = s;
					return true;
				}
				else
					return false;
			case e_MyStatus_normal:
				if(s == e_MyStatus_need_set || s == e_MyStatus_need_del)
				{
					status = s;
					return true;
				}
				else
					return false;
			case e_MyStatus_need_add:
				if(s == e_MyStatus_need_set)
					return true;
				else if(s == e_MyStatus_need_del)
				{
					status = e_MyStatus_empty;
					return true;
				}
				else if(s == e_MyStatus_adding)
				{
					status = s;
					return true;
				}
				else
					return false;
			case e_MyStatus_need_set:
				if(s == e_MyStatus_need_set || s == e_MyStatus_need_del || s == e_MyStatus_setting)
				{
					status = s;
					return true;
				}
				else
					return false;
			case e_MyStatus_need_del:
				if(s == e_MyStatus_deleting)
				{
					status = s;
					return true;
				}
				else
					return false;
			case e_MyStatus_setting:
			case e_MyStatus_adding:
				if(s == e_MyStatus_normal || s == e_MyStatus_need_set || s == e_MyStatus_need_del)
				{
					status = s;
					return true;
				}
				else
					return false;
			case e_MyStatus_deleting:
				if(s == e_MyStatus_empty)
				{
					status = s;
					return true;
				}
				else
					return false;
			default:
				return false;
			}
		}
		return false;
	}
};

/*
 * 需要写入dbc的shm数据管理器的模版基类
 * 实现了同步的load和异步的add set del
 * T1是对应dbc的结构体
 * T2是dbc的table id
 * T3是缓存大小
 * T4是dbc连接类
 * T5表示一个新用户需要占用的条数
 */
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
class DataSingleton : public DataSingletonBase
{
public:
	struct MyData
	{
		T1 data[T3];
		MyDataPlus plus[T3];

		bool Empty(unsigned i)
		{
			return plus[i].Empty();
		}
		bool NeedWork(unsigned i)
		{
			return plus[i].NeedWork();
		}
		bool Working(unsigned i)
		{
			return plus[i].Working();
		}
		bool Aavaliable(unsigned i)
		{
			return plus[i].Aavaliable();
		}
		bool MarkChange(unsigned i)
		{
			bool res = false;
			if(plus[i].Empty())
				res = plus[i].ChangeStatus(e_MyStatus_need_add);
			else
				res = plus[i].ChangeStatus(e_MyStatus_need_set);
			if(res)
				plus[i].ts = Time::GetGlobalTime();
			return res;
		}
		bool MarkDel(unsigned i)
		{
			bool res = plus[i].ChangeStatus(e_MyStatus_need_del);
			if(res)
				plus[i].ts = Time::GetGlobalTime();
			return res;
		}
		bool MarkWorking(unsigned i)
		{
			bool res = false;
			if(plus[i].status == e_MyStatus_need_add)
				res = plus[i].ChangeStatus(e_MyStatus_adding);
			else if(plus[i].status == e_MyStatus_need_set)
				res = plus[i].ChangeStatus(e_MyStatus_setting);
			else
				res = plus[i].ChangeStatus(e_MyStatus_deleting);
			if(res)
				plus[i].ts = Time::GetGlobalTime();
			return res;
		}
		bool MarkOver(unsigned i)
		{
			bool res = false;
			if(plus[i].status == e_MyStatus_adding || plus[i].status == e_MyStatus_setting)
				res = plus[i].ChangeStatus(e_MyStatus_normal);
			else
				res = plus[i].ChangeStatus(e_MyStatus_empty);
			if(res)
				plus[i].ts = Time::GetGlobalTime();
			return res;
		}
		bool MarkFail(unsigned i)
		{
			if(plus[i].status == e_MyStatus_adding)
				plus[i].status = e_MyStatus_need_add;
			else if(plus[i].status == e_MyStatus_setting)
				plus[i].status = e_MyStatus_need_set;
			else if(plus[i].status == e_MyStatus_deleting)
				plus[i].status = e_MyStatus_need_del;
			else
				return false;
			return true;
		}
		bool MardLoad(unsigned i)
		{
			bool res = false;
			if(plus[i].status == e_MyStatus_empty)
				res = plus[i].ChangeStatus(e_MyStatus_normal);
			return res;
		}
		void Clear(unsigned i)
		{
			memset(&(data[i]), 0, sizeof(T1));
			memset(&(plus[i]), 0, sizeof(MyDataPlus));
		}
	};
	static MyData* m_data;

	virtual ~DataSingleton(){}
	DataSingleton(){}

	int Init()
	{
		dbc = new T4;
		dbc_l = new T4;
		pthread_cond_init(&m_cond, NULL);
		if(pthread_create(&m_thread, NULL, _save, NULL) != 0)
			return R_ERR_DATA;

		int semgroup = 0;
		int semserver = Config::GetIntValue(CONFIG_SRVID);
		string path = Config::GetPath(CONFIG_DATA_PATH) + CTrans::ITOS(T2) + ".dat";
		if(!m_sh.CreateOrOpen(path.c_str(), sizeof(MyData), SEM_ID(T2,semgroup,semserver)))
		{
			error_log("[init_ladder_data_fail][path=%s]", path.c_str());
			return R_ERROR;
		}

		m_data = (MyData *)m_sh.GetAddress();

		if(!m_sh.HasInit())
		{
			memset(m_data, 0, sizeof(*m_data));
			m_sh.SetInitDone();
		}

		Check();

		for(unsigned i=0;i<T3;++i)
		{
			if(m_data->Empty(i))
				m_freeIndex.insert(i);
		}

		return 0;
	}
	void Exit()
	{
		while(!AfterSave())
			sleep(1);
		Check();
		pthread_cancel(m_thread);
		pthread_cond_destroy(&m_cond);
		delete dbc;
		delete dbc_l;
	}
	void Timer1()
	{
		AfterSave();
	}
	void Timer2()
	{
		Save();
	}
	virtual int OnInit(){return 0;}
	virtual void OnExit(){}
	virtual void OnTimer1(){}
	virtual void OnTimer2(){}
	virtual void CallDestroy() = 0;
	virtual void DoSave(unsigned uid) {}
	virtual void DoClear(unsigned uid){}

	void DebugLog()
	{
		debug_log("id:%d,free:%u,all:%u,need:%u", T2, GetFreeCount(), T3, T5);
	}
	unsigned GetFreeCount()
	{
		return m_freeIndex.size();
	}
	unsigned GetFreeIndex()
	{
		if(m_freeIndex.empty())
			return -1;
		return *(m_freeIndex.begin());
	}
	bool IsFull()
	{
		return GetFreeCount() < T5;
	}
	bool IsNeedClear()
	{
		return GetFreeCount() * 10 / T3 <= 1;
	}
	bool IsWorking()
	{
		return m_working;
	}

	int OnCheck()
	{
		while(!AfterSave())
			sleep(1);
		Check();
		for(unsigned i=0;i<T3;++i)
		{
			if(m_data->Empty(i))
				m_freeIndex.insert(i);
		}
		return 0;
	}

protected:
	void Clear(unsigned i)
	{
		m_data->Clear(i);
		m_freeIndex.insert(i);
	}
	bool Add(unsigned i, T1& p)
	{
		if(!m_data->Empty(i))
			return false;
		m_data->data[i] = p;
		if(!m_data->MarkChange(i))
			return false;
		m_freeIndex.erase(i);
		return true;
	}
	bool Set(unsigned i, T1& p)
	{
		if(!m_data->Aavaliable(i))
			return false;
		m_data->data[i] = p;
		return m_data->MarkChange(i);
	}
	int Load(unsigned i)
	{
		if(!m_data->Empty(i))
			return R_ERR_DATA;
		int ret = Load(m_data->data[i]);
		if(ret)
			return ret;
		if(m_data->MardLoad(i))
		{
			m_freeIndex.erase(i);
			return 0;
		}
		return R_ERR_DATA;
	}
	static int Load(T1 &data)
	{
		int ret = dbc_l->Get(data);
		if(ret)
			error_log("Load fail id=%d, ret=%d", T2, ret);
		return ret;
	}
	static int Load(vector<T1> &data)
	{
		int ret = dbc_l->Get(data);
		if(ret)
			error_log("Load fail id=%d, ret=%d", T2, ret);
		return ret;
	}
	static void AddSave(unsigned i)
	{
		m_queue.push_back(i);
	}
	static bool Save()
	{
		if(m_working)
			return false;
		if(m_queue.empty())
			return true;

		CScopedLock guard(m_mutex);

		for(vector<unsigned>::iterator it=m_queue.begin();it!=m_queue.end();++it)
		{
			//debug_log("----id=%d,index=%u,work=%u", T2, *it, m_data->plus[*it].status);
			if(m_data->MarkWorking(*it))
			{
				m_save.push_back(m_data->data[*it]);
				m_work.push_back(m_data->plus[*it].status);
				m_index.push_back(*it);
				//debug_log("working");
			}
			else if(m_data->Empty(*it))
			{
				m_freeIndex.insert(*it);
				//debug_log("free");
			}
			//debug_log("after,work=%u", m_data->plus[*it].status);
		}
		m_queue.clear();
		if(m_save.empty())
			return true;

		m_working = true;
		pthread_cond_signal(&m_cond);

		return true;
	}
	static bool AfterSave()
	{
		if(!m_working)
			return true;

		CScopedTryLock guard(m_mutex);
		if(!guard.GetTry())
			return false;

		for(unsigned i=0;i<m_index.size();++i)
		{
			if(m_dbc_ret[i] == 0)
			{
				m_data->MarkOver(m_index[i]);
				if(m_data->Empty(m_index[i]))
					m_freeIndex.insert(m_index[i]);
			}
			else
			{
				m_data->MarkFail(m_index[i]);
				error_log("Save fail id=%d, index=%u", T2, m_index[i]);
			}
		}
		m_save.clear();
		m_index.clear();
		m_work.clear();
		m_dbc_ret.clear();
		m_working = false;

		return true;
	}
	static int Check()
	{
		int ret = 0;
		CScopedLock guard(m_mutex);
		for(unsigned i=0;i<T3;++i)
		{
			int r = 0;
			if(m_data->NeedWork(i))
			{
				switch(m_data->plus[i].status)
				{
				case  e_MyStatus_need_add:
					r = dbc->Add(m_data->data[i]);
					if(r == R_ERR_DULP)
						r = dbc->Set(m_data->data[i]);
					break;
				case e_MyStatus_need_set:
					r = dbc->Set(m_data->data[i]);
					break;
				case e_MyStatus_need_del:
					r = dbc->Del(m_data->data[i]);
					break;
				default:
					break;
				}
				if(r == 0)
				{
					m_data->MarkWorking(i);
					m_data->MarkOver(i);
				}
				ret += r;
			}
			else if(m_data->Working(i))
			{
				switch(m_data->plus[i].status)
				{
				case  e_MyStatus_adding:
					r = dbc->Add(m_data->data[i]);
					if(r == R_ERR_DULP)
						r = dbc->Set(m_data->data[i]);
					break;
				case e_MyStatus_setting:
					r = dbc->Set(m_data->data[i]);
					break;
				case e_MyStatus_deleting:
					r = dbc->Del(m_data->data[i]);
					break;
				default:
					break;
				}
				if(r == 0)
					m_data->MarkOver(i);
				ret += r;
			}
		}
		if(ret)
			error_log("Check fail id=%d", T2);
		return ret;
	}
	static void* _save(void* args)
	{
		CScopedLock guard(m_mutex);
		while(1)
		{
			pthread_cond_wait(&m_cond, m_mutex.GetMutex());

			for(unsigned i=0;i<m_save.size();++i)
			{
				int r = 0;
				switch(m_work[i])
				{
				case  e_MyStatus_adding:
					r = dbc->Add(m_save[i]);
					if(r == R_ERR_DULP)
						r = dbc->Set(m_save[i]);
					m_dbc_ret.push_back(r);
					break;
				case e_MyStatus_setting:
					m_dbc_ret.push_back(dbc->Set(m_save[i]));
					break;
				case e_MyStatus_deleting:
					m_dbc_ret.push_back(dbc->Del(m_save[i]));
					break;
				default:
					break;
				}
			}
		}
		pthread_exit(NULL);
	}
	/*************************/
	static CBaseMutex   m_mutex;
	static pthread_t m_thread;
	static pthread_cond_t m_cond;
	static DBCBase<T1, T2> *dbc;
	static DBCBase<T1, T2> *dbc_l;
	static vector<T1> m_save;
	static vector<unsigned>m_work;
	static vector<int> m_dbc_ret;
	/*************************/
	static vector<unsigned> m_index, m_queue;
	static bool m_working;
	static set<unsigned> m_freeIndex;

	static CShareMemory m_sh;
};
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
typename DataSingleton<T1, T2, T3, T4, T5>::MyData* DataSingleton<T1, T2, T3, T4, T5>::m_data = NULL;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
CBaseMutex DataSingleton<T1, T2, T3, T4, T5>::m_mutex;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
pthread_t DataSingleton<T1, T2, T3, T4, T5>::m_thread;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
pthread_cond_t DataSingleton<T1, T2, T3, T4, T5>::m_cond;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
DBCBase<T1, T2>*  DataSingleton<T1, T2, T3, T4, T5>::dbc = NULL;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
DBCBase<T1, T2>*  DataSingleton<T1, T2, T3, T4, T5>::dbc_l = NULL;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
vector<T1> DataSingleton<T1, T2, T3, T4, T5>::m_save;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
vector<unsigned> DataSingleton<T1, T2, T3, T4, T5>::m_work;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
vector<int> DataSingleton<T1, T2, T3, T4, T5>::m_dbc_ret;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
vector<unsigned> DataSingleton<T1, T2, T3, T4, T5>::m_index;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
vector<unsigned> DataSingleton<T1, T2, T3, T4, T5>::m_queue;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
bool DataSingleton<T1, T2, T3, T4, T5>::m_working = false;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
CShareMemory DataSingleton<T1, T2, T3, T4, T5>::m_sh;
template<typename T1, int T2, unsigned T3, class T4, unsigned T5>
set<unsigned> DataSingleton<T1, T2, T3, T4, T5>::m_freeIndex;

/*
 * 单纯shm数据管理器的模版基类
 * T1是整个shm的结构体
 * T2是编号id
 */
template<typename T1, int T2>
class MemorySingleton : public DataSingletonBase
{
public:
	static T1*  m_data;

	virtual ~MemorySingleton(){}
	MemorySingleton(){}

	int Init()
	{
		int semgroup = 0;
		int semserver = Config::GetIntValue(CONFIG_SRVID);
		string path = Config::GetPath(CONFIG_SHM_PATH) + CTrans::ITOS(T2) + ".dat";
		if(!m_sh.CreateOrOpen(path.c_str(), sizeof(T1), SEM_ID(T2,semgroup,semserver)))
		{
			error_log("[init_ladder_data_fail][path=%s]", path.c_str());
			return R_ERROR;
		}

		m_data = (T1 *)m_sh.GetAddress();

		if(!m_sh.HasInit())
		{
			memset(m_data, 0, sizeof(*m_data));
			m_sh.SetInitDone();
		}

		return 0;
	}
	void Exit(){}
	void Timer1(){}
	void Timer2(){}
	virtual int OnInit(){return 0;}
	virtual void OnExit(){}
	virtual void OnTimer1(){}
	virtual void OnTimer2(){}
	virtual void CallDestroy() = 0;
	virtual void DoSave(unsigned uid){}
	virtual void DoClear(unsigned uid){}
	virtual unsigned GetFreeCount(){return 0;}
	virtual unsigned GetFreeIndex(){return 0;}
	virtual bool IsFull(){return false;}
	virtual bool IsWorking(){return false;}
	virtual int OnCheck(){return 0;}
	virtual bool IsNeedClear(){return false;}
	void DebugLog(){}
protected:
	static CShareMemory m_sh;
};
template<typename T1, int T2>
T1* MemorySingleton<T1, T2>::m_data = NULL;
template<typename T1, int T2>
CShareMemory MemorySingleton<T1, T2>::m_sh;

#endif /* DATASINGLETON_H_ */
