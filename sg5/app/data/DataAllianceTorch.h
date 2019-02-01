/*
 * DataAllianceTorch.h
 *
 *  Created on: 2016-05-18
 *      Author: zkw
 */

#ifndef DATA_ALLIANCE_TORCH_H_
#define DATA_ALLIANCE_TORCH_H_

#include "Kernel.h"
#include <math.h>
#include "DataBase.h"
#include "AllianceTorch.pb.h"


/************************************************************************************/
class DataCurrTorchStatus
{
public:
	unsigned int tid;
	unsigned int status;
	unsigned int uid;
	unsigned int ts;

	DataCurrTorchStatus(): tid(0),status(0),uid(0),ts(0) {}
	~DataCurrTorchStatus() {}

	void Serialize(AllianceTorch::CurrTorchStatus *p)
	{
		p->set_tid(tid);
		p->set_status(status);
		p->set_uid(uid);
		p->set_ts(ts);
	}

	void Parse(const AllianceTorch::CurrTorchStatus &p)
	{
		tid = p.tid();
		status = p.status();
		uid = p.uid();
		ts = p.ts();
	}

	unsigned GetTorchStatus(unsigned tid_new)
	{
		tid = tid_new;
		return status;
	}

	void BurnTorch(unsigned tid_new, unsigned uid_new, unsigned ts_new)
	{
		tid = tid_new;
		status = 1;
		uid = uid_new;
		ts = ts_new;
	}

	void ResetTorch(unsigned tid_new)
	{
		tid = tid_new;
		status = 0;
		uid = 0;
		ts = 0;
	}
};

class DataLogBuyRecord
{
public:
	unsigned int time;
	unsigned int uid;
	unsigned int tid;

	DataLogBuyRecord(): time(0),uid(0),tid(0) {}
	~DataLogBuyRecord() {}

	void Serialize(AllianceTorch::LogBuyRecord *p)
	{
		p->set_time(time);
		p->set_uid(uid);
		p->set_tid(tid);
	}

	void Parse(const AllianceTorch::LogBuyRecord &p)
	{
		time = p.time();
		uid = p.uid();
		tid = p.tid();
	}

	void SetBurnTorchLog(unsigned uid_new, unsigned time_new, unsigned tid_new)
	{
		uid = uid_new;
		time = time_new;
		tid = tid_new;
	}
};

class DataSingleAllianceTorch
{
public:
	unsigned int aid;
	map<unsigned int, DataCurrTorchStatus> curr;
	map<unsigned int, DataLogBuyRecord> log;

	DataSingleAllianceTorch()
	{
		aid = 0;
		DataCurrTorchStatus temp;
		curr[0] = temp;
		curr[0].tid = 0;
		curr[1] = temp;
		curr[1].tid = 1;
		curr[2] = temp;
		curr[2].tid = 2;
	}

	~DataSingleAllianceTorch() {}

	void Serialize(AllianceTorch::SingleAllianceTorch *p)
	{
		p->set_aid(aid);
		for (map<unsigned int, DataCurrTorchStatus>::iterator it = curr.begin();
				it != curr.end(); ++it)
			it->second.Serialize(p->add_curr());
		for (map<unsigned int, DataLogBuyRecord>::iterator it = log.begin();
				it != log.end(); ++it)
			it->second.Serialize(p->add_log());
	}

	void Parse(const AllianceTorch::SingleAllianceTorch &p)
	{
		aid = p.aid();
		for (int i = 0; i < p.curr_size(); ++i)
			curr[p.curr(i).tid()].Parse(p.curr(i));
		for (int i = 0; i < p.log_size(); ++i)
			log[p.log(i).time()].Parse(p.log(i));
	}

	int BurnTorch(unsigned aid_new, unsigned tid_new, unsigned uid_new, unsigned ts_new)
	{
		aid = aid_new;
		if (curr[tid_new].GetTorchStatus(tid_new))
		{
			error_log("torch has been burned, aid=%u, tid=%u", aid_new, tid_new);
			return R_ERR_LOGIC;
		}
		curr[tid_new].BurnTorch(tid_new, uid_new, ts_new);
		return R_SUCCESS;
	}

	void AddBurnTorchLog(unsigned aid_new, unsigned uid_new, unsigned time_new, unsigned tid_new)
	{
		aid = aid_new;
		for (map<unsigned int, DataLogBuyRecord>::iterator it = log.begin(); it != log.end(); ++it)
		{
			if (Time::GetGlobalTime() > (it->first + 86400*15))
			{
				log.erase(it->first);
			}
		}
		DataLogBuyRecord temp;
		log[time_new] = temp;
		log[time_new].SetBurnTorchLog(uid_new, time_new, tid_new);
	}

	void FreshTorchStatus(unsigned aid_new)
	{
		aid = aid_new;
		for (map<unsigned int, DataCurrTorchStatus>::iterator it = curr.begin(); it != curr.end(); ++it)
		{
			if (!Time::IsToday((it->second).ts))
			{
				(it->second).ResetTorch(it->first);
			}
		}
	}
};

class DataAllianceTorch
{
public:
	map<unsigned int, DataSingleAllianceTorch> alliance;

	DataAllianceTorch() {}
	~DataAllianceTorch() {}

	void Serialize(AllianceTorch::AllianceTorch *p)
	{
		for (map<unsigned int, DataSingleAllianceTorch>::iterator it =
				alliance.begin(); it != alliance.end(); ++it)
			it->second.Serialize(p->add_alliance());
	}

	void Parse(const AllianceTorch::AllianceTorch &p)
	{
		for (int i = 0; i < p.alliance_size(); ++i)
			alliance[p.alliance(i).aid()].Parse(p.alliance(i));
	}

	int GetAllianceTorchCurrStatus(unsigned aid, map<unsigned int, DataCurrTorchStatus> &datas)
	{
		if (alliance.count(aid))
		{
			alliance[aid].FreshTorchStatus(aid);
			datas = alliance[aid].curr;
		}
		return 0;
	}

	int BurnAllianceTorch(unsigned aid_new, unsigned uid_new, unsigned time_new, unsigned tid_new, map<unsigned int, DataCurrTorchStatus> &datas)
	{
		if (!alliance.count(aid_new))
		{
			DataSingleAllianceTorch temp;
			alliance[aid_new] = temp;
		} else {
			alliance[aid_new].FreshTorchStatus(aid_new);
		}
		int ret = alliance[aid_new].BurnTorch(aid_new, tid_new, uid_new, time_new);
		if (ret)
			return ret;
		alliance[aid_new].AddBurnTorchLog(aid_new, uid_new, time_new, tid_new);
		datas = alliance[aid_new].curr;
		return 0;
	}

	int GetAllianceTorchBuyLog(unsigned aid, map<unsigned int, DataLogBuyRecord> &datas)
	{
		if (alliance.count(aid))
		{
			datas = alliance[aid].log;
		}
		return 0;
	}
};
/************************************************************************************/

class CDataAllianceTorch : public DataBase
{
public:
	CDataAllianceTorch(string path);
	virtual ~CDataAllianceTorch() {}
	int Init();
	int Save();
	int GetAllianceTorchCurrStatus(unsigned aid, map<unsigned int, DataCurrTorchStatus> &datas);
	int BurnAllianceTorch(unsigned aid_new, unsigned uid_new, unsigned time_new, unsigned tid_new, map<unsigned int, DataCurrTorchStatus> &datas);
	int GetAllianceTorchBuyLog(unsigned aid, map<unsigned int, DataLogBuyRecord> &datas);
private:
	DataAllianceTorch m_data;
};

#endif /* DATA_ALLIANCE_TORCH_H_ */
