/*
 * DataNewYearActive.cpp
 *
 *  Created on: 2018年1月25日
 *      Author: Administrator
 */

#include "DataNewYearActive.h"
#include "DataUserBasic.h"
#include "ActivityConfig.h"
#include "LogicSecinc.h"
#include "LogicNewYearActive.h"

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

CDataGiveHelpActive::CDataGiveHelpActive(const string & path): DataBase(path) {
	m_msg = new WuhunActivity::GiveHelpActive();
}

CDataGiveHelpActive::~CDataGiveHelpActive() {
}

int CDataGiveHelpActive::Init() {
	int ret = 0;
	ret = Parse();
	if (ret) {
		error_log("path is error");
		return ret;
	}

	m_data.parse((WuhunActivity::GiveHelpActive *) m_msg);
	((WuhunActivity::GiveHelpActive *) m_msg)->Clear();

	return 0;
}

int CDataGiveHelpActive::Save() {
	int ret = 0;
	m_data.serialize((WuhunActivity::GiveHelpActive *) m_msg);
	ret = Serialize();
	if (ret) {
		return ret;
	}

	((WuhunActivity::GiveHelpActive *) m_msg)->Clear();

	RewardHelper();

	return 0;
}

int CDataGiveHelpActive::StartGiveHelp(const DataGiveHelpUserInfo &data, Json::Value &result) {
	const WuhunActivity::AccChangeItem &itemcfg = WuhunActivityWrap().GetAccChargeItemCfg(0);
	map<unsigned, DataGiveHelpMasterInfo>::iterator itr = m_data.masters.find(data.uid);
	if (itr == m_data.masters.end()) {
		if (data.charge >= itemcfg.need()) {
			DataGiveHelpMasterInfo user;
			user.info = data;
			user.ts = Time::GetGlobalTime();
			m_data.masters.insert(make_pair(user.info.uid, user));
			RankList();
		}
	} else {
		DataGiveHelpMasterInfo &user = itr->second;
		user.info.charge = data.charge;
	}

	GetGiveHelpList(result);

	return 0;
}

bool Compare(DataGiveHelpMasterRank &left, DataGiveHelpMasterRank &right) {
	if (left.count > right.count) {
		return true;
	} else if (left.count == right.count) {
		return left.ts < right.ts;
	} else {
		return false;
	}
}

int CDataGiveHelpActive::GetGiveHelpList(Json::Value &result) {
	result["list"] = Json::Value(Json::arrayValue);
	list<DataGiveHelpMasterRank>::iterator rItr;
	for (rItr = m_data.ranks.begin(); rItr != m_data.ranks.end(); ++rItr) {
		Json::Value jstmp;
		jstmp["uid"] = rItr->uid;
		jstmp["name"] = rItr->name;
		jstmp["c"] = rItr->count;
		result["list"].append(jstmp);
	}
	return 0;
}

int CDataGiveHelpActive::RankList() {
	list<DataGiveHelpMasterRank> full;
	list<DataGiveHelpMasterRank> rank;
	map<unsigned, DataGiveHelpMasterInfo>::iterator itr;
	list<DataGiveHelpMasterRank>::iterator rItr;
	for (itr = m_data.masters.begin(); itr != m_data.masters.end(); ++itr) {
		const DataGiveHelpMasterInfo &master = itr->second;
		if (master.helper.size() >= DATA_GIVE_MAX_HELPER) {
			full.push_back(DataGiveHelpMasterRank(master.info.uid, master.helper.size(), master.ts, master.info.name));
			continue;
		}
		DataGiveHelpMasterRank item(master.info.uid, master.helper.size(), master.ts, master.info.name);
		for (rItr = rank.begin(); rItr != rank.end(); ++rItr) {
			if (Compare(item, *rItr)) {
				rank.insert(rItr, item);
				break;
			}
		}
		if (rItr == rank.end()) {
			rank.push_back(item);
		}
	}
	m_data.ranks.clear();
	for (rItr = rank.begin(); rItr != rank.end(); ++rItr) {
		m_data.ranks.push_back(*rItr);
	}
	for (rItr = full.begin(); rItr != full.end(); ++rItr) {
		m_data.ranks.push_back(*rItr);
	}
	return 0;
}

int CDataGiveHelpActive::AddGiveHelp(const DataGiveHelpUserInfo &data, unsigned uid, Json::Value &result) {
	int ret = 0;
	DataGiveHelpHelperInfo &helper = m_data.helpers[data.uid];
	helper.uid = data.uid;
	if (helper.master.size() >= DATA_GIVE_MAX_MASTER) {
		LOGIC_ERROR_RETURN_MSG("only_one_chance");
	}
	map<unsigned, DataGiveHelpMasterInfo>::iterator itr = m_data.masters.find(uid);
	if (itr == m_data.masters.end()) {
		LOGIC_ERROR_RETURN_MSG("master_no_exist");
	}
	DataGiveHelpMasterInfo &master = itr->second;
	if (master.helper.size() >= DATA_GIVE_MAX_HELPER) {
		LOGIC_ERROR_RETURN_MSG("already_full");
	}
	map<unsigned, DataGiveHelpUserInfo>::iterator hItr = master.helper.find(data.uid);
	if (hItr != master.helper.end()) {
		LOGIC_ERROR_RETURN_MSG("already_help");
	}
	map<unsigned, DataGiveHelpHelperMaster>::iterator mItr = helper.master.find(uid);
	if (mItr != helper.master.end()) {
		LOGIC_ERROR_RETURN_MSG("already_help");
	}

	helper.master.insert(make_pair(uid, DataGiveHelpHelperMaster(uid)));
	master.helper.insert(make_pair(data.uid, data));

	RankList();
	unsigned help_count = master.helper.size();
	AUTO_LOCK_USER(uid);
	UserWrap to_user(uid, false);
	GiveHelpChargeUnit act(to_user);
	ret = act.SetHelpCount(help_count);
	if (ret) {
		error_log("getNewActBuUid was failed");
		return ret;
	}

	result["ts"] = Time::GetGlobalTime();
	result["gnm"] = help_count;

	GetGiveHelpList(result);

	return 0;
}

int CDataGiveHelpActive::DelGiveHelp(unsigned uid, unsigned userid, Json::Value &result) {
	map<unsigned, DataGiveHelpMasterInfo>::iterator itr = m_data.masters.find(uid);
	if (itr == m_data.masters.end()) {
		error_log("you is not master uid=%u userid=%u", uid, userid);
		return R_ERR_DATA;
	}
	DataGiveHelpMasterInfo &master = itr->second;
	map<unsigned, DataGiveHelpUserInfo>::iterator it = master.helper.find(userid);
	if (it == master.helper.end()) {
		error_log("the user is not helper uid=%u userid=%u", uid, userid);
		return R_ERR_DATA;
	}
	master.helper.erase(it);

	map<unsigned, DataGiveHelpHelperInfo>::iterator hItr = m_data.helpers.find(userid);
	if (hItr != m_data.helpers.end()) {
		DataGiveHelpHelperInfo &helper = hItr->second;
		map<unsigned, DataGiveHelpHelperMaster>::iterator mItr = helper.master.find(uid);
		if (mItr != helper.master.end()) {
			mItr->second.refused = true;
		}
	}

	RankList();

	GetMyGiveHelpInfo(uid, result);

	int curr_count = 0;
	AUTO_LOCK_USER(uid);
	UserWrap to_user(uid, false);
	GiveHelpChargeUnit act(to_user);
	int ret = act.SetHelpCount(master.helper.size());
	if (ret) {
		error_log("getNewActBuUid was failed");
		return ret;
	}

	return 0;
}

int CDataGiveHelpActive::GetMyGiveHelpInfo(unsigned uid, Json::Value &result) {
	result["list"] = Json::Value(Json::arrayValue);
	result["myhelp"] = Json::Value(Json::arrayValue);
	map<unsigned, DataGiveHelpHelperInfo>::iterator itr = m_data.helpers.find(uid);
	if (itr != m_data.helpers.end()) {
		DataGiveHelpHelperInfo &helper = itr->second;
		map<unsigned, DataGiveHelpHelperMaster>::iterator hitr = helper.master.begin();
		for (; hitr != helper.master.end(); ++hitr) {
			Json::Value tmp;
			const DataGiveHelpMasterInfo &master = m_data.masters[hitr->first];
			tmp["uid"] = master.info.uid;
			tmp["name"] = master.info.name;
			tmp["url"] = master.info.url;
			tmp["chg"] = master.info.charge;
			tmp["refused"] = hitr->second.refused ? 1 : 0;
			result["myhelp"].append(tmp);
		}
	}
	map<unsigned, DataGiveHelpMasterInfo>::iterator mitr = m_data.masters.find(uid);
	if (mitr != m_data.masters.end()) {
		const DataGiveHelpMasterInfo &master = mitr->second;
		map<unsigned, DataGiveHelpUserInfo>::const_iterator vitr = master.helper.begin();
		for (; vitr != master.helper.end(); ++vitr) {
			const DataGiveHelpUserInfo &user = vitr->second;
			Json::Value tmp;
			tmp["uid"] = user.uid;
			tmp["name"] = user.name;
			tmp["url"] = user.url;
			result["list"].append(tmp);
		}
	}
	return 0;
}

int CDataGiveHelpActive::Sig(int sig) {
	return 0;
}

int CDataGiveHelpActive::CheckVersion(unsigned ver) {
	if (m_data.version == ver) {
		return 0;
	}
	m_data.Clear();
	m_data.version = ver;
	return 0;
}

int CDataGiveHelpActive::UpdateMasterCharge() {
	ActInfoConfig act_time(CONFIG_GIVEHELPACTION);
	map<unsigned, DataGiveHelpMasterInfo>::iterator mitr = m_data.masters.begin();
	for (; mitr != m_data.masters.end(); ++mitr) {
		UserWrap user(mitr->first, false);
		DataGiveHelpMasterInfo &master = mitr->second;
		master.info.charge = user.GetRechargePoint(act_time.StartTS(), act_time.EndTS());
	}
	return 0;
}

int CDataGiveHelpActive::RewardHelper() {
	int ret = 0;
	if (m_data.reward) {
		return R_ERROR;
	}
	ActInfoConfig act_time(CONFIG_GIVEHELPACTION);
	if (act_time.IsActive()) {
		return R_ERROR;
	}

	m_data.reward = true;

	CDataXML *pdataXML = CDataXML::GetCDataXML();
	if(pdataXML == NULL) {
		error_log("GetInitXML Process error");
		throw std::runtime_error("get_new_active_data_error");
	}
	DataXMLGiveHelpItem config;
	ret = pdataXML->GetGiveHelpItemReward(config);
	if (0 != ret) {
		error_log("get config error ret=%d", ret);
		return ret;
	}
	map<unsigned, vector<ItemAdd> > reward;
	for (unsigned i = 0; i < MAX_GIVEHELPEXTRA_ITEM_NUM; ++i) {
		vector<ItemAdd> &ver = reward[config.helpuser[i].require];
		for (unsigned j = 0; j < MAX_GIVEHELPEXTRA_REWARD_NUM; ++j) {
			XMLActSimpleReward &item = config.helpuser[i].reward[j];
			if (item.type == XML_ACT_SIMPLE_REWARD_TYPE_EQUIP && item.id != 0) {
				ver.push_back(ItemAdd(item.id, item.count, ""));
			}
		}
	}

	UpdateMasterCharge();

	map<unsigned, DataGiveHelpHelperMaster>::const_iterator it;
	map<unsigned, vector<ItemAdd> >::iterator rItr;
	CLogicEquipment logicEquipment;
	CLogicEmail logicEmail;
	vector<uint64_t> uids;

	map<unsigned, DataGiveHelpHelperInfo>::iterator itr = m_data.helpers.begin();
	for (; itr != m_data.helpers.end(); ++itr) {
		const DataGiveHelpHelperInfo &helper = itr->second;
		for (it = helper.master.begin(); it != helper.master.end(); ++it) {
			unsigned charge = 0;
			const DataGiveHelpMasterInfo &master = m_data.masters[it->first];
			if (it->second.refused) {
				charge = config.helpuser[0].require;
			} else {
				charge = master.info.charge;
			}
			unsigned index = 0;
			for (index = 0; index < MAX_GIVEHELPEXTRA_ITEM_NUM; ++index) {
				if (charge < config.helpuser[index].require) {
					break;
				}
			}
			if (index == 0) {
				error_log("can not find charge uid=%u charge=%u", itr->first, charge);
				continue;
			}
			index -= 1;
			string code;
			String::Format(code, "give_help_jichu_%u_%u", charge, master.info.uid);
			vector<ItemAdd> equips;
			for (unsigned j = 0; j < MAX_GIVEHELPEXTRA_REWARD_NUM; ++j) {
				XMLActSimpleReward &item = config.helpuser[index].reward[j];
				if (item.type == XML_ACT_SIMPLE_REWARD_TYPE_EQUIP && item.id != 0) {
					equips.push_back(ItemAdd(item.id, item.count, code));
				}
			}
			Json::Value result;
			ret = logicEquipment.AddItems(itr->first, equips, result);
			if (0 != ret) {
				error_log("add item error uid=%u charge=%u ret=%d", itr->first, charge, ret);
				continue;
			}
			Json::Value em_text;
			em_text["s"] = CONFIG_GIVEHELPACTION;
			em_text["equip"] = config.helpuser[index].id;
			uids.clear();
			uids.push_back(itr->first);
			logicEmail.SystemEmail(CONFIG_GIVEHELPACTION, Json::ToString(em_text), uids);
		}
	}
	return 0;
}
