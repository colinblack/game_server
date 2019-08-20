/*
 * DataNewYearActive.h
 *
 *  Created on: 2018年1月25日
 *      Author: Administrator
 */

#ifndef DATA_NEWYEARACTIVE_H_
#define DATA_NEWYEARACTIVE_H_

#include "Kernel.h"
#include "DataBase.h"
#include "NewYearActive.pb.h"
#include "WuhunActivity.pb.h"
#include "LogicCmdUnits.h"

#define DATA_NEW_YEAR_ACTIVE_RANK_LEN 10
#define DATA_NEW_YEAR_ACTIVE_HISTORY_LEN 10

struct DataNewYearActiveHistory
{
	unsigned t_uid;
	unsigned f_uid;
	unsigned ts;
	unsigned equid;
	byte equc;
	byte type;
	string t_name;
	string f_name;
	DataNewYearActiveHistory(): t_uid(0), f_uid(0), ts(0), equid(0), equc(0), type(0)
	{
		t_name.clear();
		f_name.clear();
	}
	~DataNewYearActiveHistory()
	{
		t_name.clear();
		f_name.clear();
	}
	void parse(const NewYearActive::NewYearActiveHistory &item)
	{
		this->t_uid = item.t_uid();
		this->f_uid = item.f_uid();
		this->ts = item.ts();
		this->equid = item.equid();
		this->equc = item.equc();
		this->type = item.type();
		this->t_name = item.t_name();
		this->f_name = item.f_name();
	}
	void serialize(NewYearActive::NewYearActiveHistory *item)
	{
		if (item == NULL)
		{
			return;
		}
		item->set_t_uid(this->t_uid);
		item->set_f_uid(this->f_uid);
		item->set_ts(this->ts);
		item->set_equid(this->equid);
		item->set_equc(this->equc);
		item->set_type(this->type);
		item->set_t_name(this->t_name);
		item->set_f_name(this->f_name);
	}

	Json::Value toJson() const
	{
		Json::Value item;
		item["t_uid"] = this->t_uid;
		item["f_uid"] = this->f_uid;
		item["ts"] = this->ts;
		item["equid"] = this->equid;
		item["count"] = static_cast<unsigned>(this->equc);
		item["t_name"] = this->t_name;
		item["f_name"] = this->f_name;
		item["type"] = static_cast<unsigned>(this->type);
		return item;
	}
};

struct DataNewYearActiveUser
{
	unsigned uid;
	unsigned count;
	unsigned ts;
	list<DataNewYearActiveHistory> history;
	set<unsigned> uids;
	DataNewYearActiveUser(): uid(0), count(0), ts(0)
	{
		history.clear();
		uids.clear();
	}
	~DataNewYearActiveUser()
	{
		history.clear();
		uids.clear();
	}
	void parse(const NewYearActive::NewYearActiveUser &item)
	{
		this->uid = item.uid();
		this->count = item.count();
		this->ts = item.ts();
		for (size_t i = 0; i < item.history_size(); ++i)
		{
			DataNewYearActiveHistory info;
			info.parse(item.history(i));
			history.push_back(info);
		}
		for (size_t i = 0; i < item.uids_size(); ++i)
		{
			uids.insert(item.uids(i));
		}
	}
	void serialize(NewYearActive::NewYearActiveUser *item)
	{
		if (item == NULL)
		{
			return;
		}
		item->set_uid(this->uid);
		item->set_count(this->count);
		item->set_ts(this->ts);
		list<DataNewYearActiveHistory>::iterator itr = this->history.begin();
		for (; itr != this->history.end(); ++itr)
		{
			itr->serialize(item->add_history());
		}
		set<unsigned>::iterator uids_itr = uids.begin();
		for (; uids_itr != uids.end(); ++uids_itr)
		{
			item->add_uids(*uids_itr);
		}
	}
	void reset()
	{
		if (CTime::IsDiffDay(this->ts, Time::GetGlobalTime()))
		{
			this->ts = Time::GetGlobalTime();
			this->uids.clear();
		}
	}
	bool operator==(unsigned uid) const
	{
		return this->uid == uid;
	}
};

struct DataNewYearActiveRank
{
	unsigned uid;
	unsigned count;
	string name;
	string pic;

	DataNewYearActiveRank(): uid(0), count(0)
	{
		name.clear();
		pic.clear();
	}
	~DataNewYearActiveRank()
	{
		name.clear();
		pic.clear();
	}
	void parse(const NewYearActive::NewYearActiveRank &item)
	{
		this->uid = item.uid();
		this->count = item.count();
		this->name = item.name();
		this->pic = item.pic();
	}
	void serialize(NewYearActive::NewYearActiveRank *item)
	{
		if (item == NULL)
		{
			return;
		}
		item->set_uid(this->uid);
		item->set_count(this->count);
		item->set_name(this->name);
		item->set_pic(this->pic);
	}
	bool operator==(uint32_t uid) const
	{
		return this->uid == uid;
	}
};

struct DataNewYearActive
{
	unsigned version;
	list<DataNewYearActiveUser> users;
	vector<DataNewYearActiveRank> ranks;
	list<DataNewYearActiveHistory> historys;
	DataNewYearActive(): version(0)
	{
		users.clear();
		ranks.clear();
		historys.clear();
	}
	void parse(const NewYearActive::NewYearActive *item)
	{
		if (item == NULL)
		{
			return;
		}
		this->version = item->version();
		for (size_t i = 0; i < item->users_size(); ++i)
		{
			DataNewYearActiveUser info;
			info.parse(item->users(i));
			users.push_back(info);
		}
		for (size_t i = 0; i < item->ranks_size(); ++i)
		{
			DataNewYearActiveRank info;
			info.parse(item->ranks(i));
			ranks.push_back(info);
		}
		for (size_t i = 0; i < item->historys_size(); ++i)
		{
			DataNewYearActiveHistory info;
			info.parse(item->historys(i));
			historys.push_back(info);
		}
	}
	void serialize(NewYearActive::NewYearActive *item)
	{
		if (item == NULL)
		{
			return;
		}
		item->set_version(this->version);
		list<DataNewYearActiveUser>::iterator itr_user = users.begin();
		for (; itr_user != users.end(); ++itr_user)
		{
			itr_user->serialize(item->add_users());
		}
		vector<DataNewYearActiveRank>::iterator itr_rank = ranks.begin();
		for (; itr_rank != ranks.end(); ++itr_rank)
		{
			itr_rank->serialize(item->add_ranks());
		}
		list<DataNewYearActiveHistory>::iterator itr_his = historys.begin();
		for (; itr_his != historys.end(); ++itr_his)
		{
			itr_his->serialize(item->add_historys());
		}
	}
	void Clear()
	{
		version = 0;
		users.clear();
		ranks.clear();
		historys.clear();
	}
};

class CDataNewYearActive : public DataBase
{
public:
	CDataNewYearActive(const string & path);
	virtual ~CDataNewYearActive();
	int Init();
	int Save();
	int Sig(int sig);
	int GetRank(Json::Value &result);
	int GetLastHistory(Json::Value &result);
	int GetUserHistory(unsigned uid, unsigned userid, bool &can, Json::Value &result);
	int AddRank(const DataNewYearActiveRank &data);
	int AddInfo(unsigned uid, unsigned userid, unsigned type, unsigned equid, unsigned count, bool &can);
protected:
	int Sync();
private:
	DataNewYearActive m_data;
	unsigned m_sync_ts;
};


#define DATA_GIVE_MAX_MASTER 3
#define DATA_GIVE_MAX_HELPER 20

//助力大行动支援列表
struct DataGiveHelpUserInfo {
	unsigned uid;
	unsigned charge;
	string name;
	string url;

	DataGiveHelpUserInfo() {
		uid = charge = 0;
	}
	DataGiveHelpUserInfo(unsigned _uid, unsigned _charge, string _name, string _url) {
		uid = _uid;
		charge = _charge;
		name = _name;
		url = _url;
	}

	void clear() {
		uid = 0;
		charge = 0;
		name.clear();
		url.clear();
	}
	void parse(const WuhunActivity::UserInfo &item) {
		this->uid = item.uid();
		this->name = item.name();
		this->url = item.url();
		this->charge = item.charge();
	}

	void serialize(WuhunActivity::UserInfo *item) {
		if (item == NULL) {
			return;
		}
		item->set_uid(this->uid);
		item->set_name(this->name);
		item->set_url(this->url);
		item->set_charge(this->charge);
	}
};

struct DataGiveHelpMasterRank {
	unsigned uid;
	unsigned count;
	unsigned ts;
	string name;

	DataGiveHelpMasterRank() {
		uid = count = ts = 0;
		name.clear();
	}
	DataGiveHelpMasterRank(unsigned _uid, unsigned _count, unsigned _ts, const string &_name) {
		uid = _uid;
		count = _count;
		ts = _ts;
		name = _name;
	}
	void parse(const WuhunActivity::RankInfo &item) {
		uid = item.uid();
		count = item.count();
		ts = item.ts();
		name = item.name();
	}
	void serialize(WuhunActivity::RankInfo *item) {
		item->set_uid(uid);
		item->set_count(count);
		item->set_ts(ts);
		item->set_name(name);
	}
};

struct DataGiveHelpMasterInfo
{
	unsigned ts;
	DataGiveHelpUserInfo info;
	map<unsigned, DataGiveHelpUserInfo> helper;

	DataGiveHelpMasterInfo() {
		ts = 0;
	}
	void parse(const WuhunActivity::MasterInfo &item) {
		ts = item.ts();
		info.parse(item.info());
		DataGiveHelpUserInfo user;
		for (int i = 0; i < item.helper_size(); ++i) {
			user.parse(item.helper(i));
			helper.insert(make_pair(user.uid, user));
		}
	}
	void serialize(WuhunActivity::MasterInfo *item) {
		item->set_ts(ts);
		info.serialize(item->mutable_info());
		map<unsigned, DataGiveHelpUserInfo>::iterator itr = helper.begin();
		for (; itr != helper.end(); ++itr) {
			DataGiveHelpUserInfo &user = itr->second;
			user.serialize(item->add_helper());
		}
	}
	bool operator==(uint32_t uid) const {
		return this->info.uid == uid;
	}
};

struct DataGiveHelpHelperMaster {
	unsigned uid;
	bool refused;

	DataGiveHelpHelperMaster() {
		uid = 0;
		refused = false;
	}
	DataGiveHelpHelperMaster(unsigned _uid) {
		uid = _uid;
		refused = false;
	}
	void parse(const WuhunActivity::HelperMaster &item) {
		uid = item.uid();
		refused = item.refused();
	}
	void serialize(WuhunActivity::HelperMaster *item) {
		item->set_uid(uid);
		item->set_refused(refused);
	}
};

struct DataGiveHelpHelperInfo
{
	unsigned uid;
	map<unsigned, DataGiveHelpHelperMaster> master;

	DataGiveHelpHelperInfo() {
		uid = 0;
		master.clear();
	}
	void parse(const WuhunActivity::HelperInfo &item) {
		uid = item.uid();
		for (int i = 0; i < item.master_size(); ++i) {
			DataGiveHelpHelperMaster user;
			user.parse(item.master(i));
			master.insert(make_pair(user.uid, user));
		}
	}
	void serialize(WuhunActivity::HelperInfo *item) {
		item->set_uid(uid);
		map<unsigned, DataGiveHelpHelperMaster>::iterator itr = master.begin();
		for (; itr != master.end(); ++itr) {
			DataGiveHelpHelperMaster &user = itr->second;
			user.serialize(item->add_master());
		}
	}
};

struct DataGiveHelpActive {
	unsigned version;
	bool reward;
	map<unsigned, DataGiveHelpMasterInfo> masters;
	map<unsigned, DataGiveHelpHelperInfo> helpers;
	list<DataGiveHelpMasterRank> ranks;

	DataGiveHelpActive() {
		Clear();
	}
	void parse(const WuhunActivity::GiveHelpActive *item) {
		version = item->version();
		reward = item->reward();
		for (int i = 0; i < item->masters_size(); ++i) {
			DataGiveHelpMasterInfo master;
			master.parse(item->masters(i));
			masters.insert(make_pair(master.info.uid, master));
		}
		for (int i = 0; i < item->helpers_size(); ++i) {
			DataGiveHelpHelperInfo helper;
			helper.parse(item->helpers(i));
			helpers.insert(make_pair(helper.uid, helper));
		}
		for (int i = 0; i < item->ranks_size(); ++i) {
			DataGiveHelpMasterRank rank;
			rank.parse(item->ranks(i));
			ranks.push_back(rank);
		}
	}
	void serialize(WuhunActivity::GiveHelpActive *item) {
		item->set_version(version);
		item->set_reward(reward);
		map<unsigned, DataGiveHelpMasterInfo>::iterator itr1 = masters.begin();
		for (; itr1 != masters.end(); ++itr1) {
			DataGiveHelpMasterInfo &master = itr1->second;
			master.serialize(item->add_masters());
		}
		map<unsigned, DataGiveHelpHelperInfo>::iterator itr2 = helpers.begin();
		for (; itr2 != helpers.end(); ++itr2) {
			DataGiveHelpHelperInfo &helper = itr2->second;
			helper.serialize(item->add_helpers());
		}
		list<DataGiveHelpMasterRank>::iterator itr3 = ranks.begin();
		for (; itr3 != ranks.end(); ++itr3) {
			itr3->serialize(item->add_ranks());
		}
	}
	void Clear() {
		reward = false;
		version = 0;
		masters.clear();
		helpers.clear();
		ranks.clear();
	}
};

class CDataGiveHelpActive : public DataBase {
public:
	CDataGiveHelpActive(const string & path);
	virtual ~CDataGiveHelpActive();
	int Init();
	int Save();
	int Sig(int sig);
	int StartGiveHelp(const DataGiveHelpUserInfo &data, Json::Value &result);
	int AddGiveHelp(const DataGiveHelpUserInfo &data, unsigned uid, Json::Value &result);
	int DelGiveHelp(unsigned uid, unsigned userid, Json::Value &result);
	int GetMyGiveHelpInfo(unsigned uid, Json::Value &result);
	int GetGiveHelpList(Json::Value &result);
	int RankList();
	int CheckVersion(unsigned ver);
	int UpdateMasterCharge();
	int RewardHelper();
private:
	DataGiveHelpActive m_data;
};

#endif /* DATA_NEWYEARACTIVE_H_ */
