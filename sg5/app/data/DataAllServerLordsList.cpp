/*
 * DataAllServerLordsList.cpp
 *
 *  Created on: 2016-7-6
 *      Author: dawx62fac
 */

#include <stdexcept>
#include "LogicInc.h"
#include "DataAllServerLordsList.h"
#include "LogicAllServerLordsList.h"

std::string DataLordRankItem::ToString()
{
	Json::Value jsonData;
	jsonData["uid"] = uid;
	jsonData["name"] = name;
	jsonData["value"] =  Convert::UInt64ToString(sumdata);

	return Json::ToString(jsonData);
}

void DataLordRankItem::Refresh(const Json::Value& data)
{
	if (data["uid"].asInt() != (int)this->uid)
	{
		return ;
	}

	this->name = data["name"].asString();
	this->sumdata += data["value"].asInt();

	if (data.isMember("uint64_val"))
	{
		uint64_t int64Val = (uint64_t)data["uint64_val"].asDouble();
		this->sumdata += int64Val;
	}
}

std::string DataLord::ToString()
{
	Json::Value jsonData;
	jsonData["Uid"] = uid;
	jsonData["Name"] = name;
	jsonData["Type"] = type;
	jsonData["Setted"] = setted;
	jsonData["Worship"] = worship;

	return Json::ToString(jsonData);
}

int DataLordItems::RadicateLord(int id, int type, const DataLordRankItem& item)
{
	this->time = Time::GetGlobalTime();
	//检查是否已经确立尊主，防止消息重发下的数据覆盖
	if (lord.count(type) == 0)
	{
		DataLord lorditem = DataLord(type, item);
		lorditem.headurl = GetHeadUrl(item.uid);

		lord[type] = lorditem;
		this->id = id;


		return 0;
	}
	else
	{
		//already radicate lord;
		return -1;
	}
}

int DataLordItems::Worship(int type)
{
#if 0
	if (this->finished >= 2)
	{
		throw std::runtime_error("worship_already_over");
	}
#endif
	std::map<unsigned int, DataLord>::iterator it = lord.find(type);
	if (it == lord.end())
	{
		throw std::runtime_error("Worship_lord_type_is_null");
	}

	if (! IsValidUid(it->second.uid))
	{
		throw std::runtime_error("Worship_lord_user_is_null");
	}

	it->second.worship += 1;
	return it->second.worship;
}

std::string DataLordItems::GetHeadUrl(unsigned uid) const
{
	CLogicUserBasic logicUserBasic;
	std::string szName, szPhoto;
	int ret = logicUserBasic.GetNameFig(uid, szName, szPhoto);
	if (ret  == 0)
	{
		return szPhoto;
	}

	error_log("Get_user_nameFig_error. ret=%d", ret);
	return "";
}

void DataLordItems::GetHeroInfo(unsigned uid, std::string& heroid, std::string& heroname) const
{
	heroid = "";
	heroname = "";
	CDataHero heroDB;
	vector<DataHero> datas;
	int ret = heroDB.GetHero(uid, datas);
	if (ret != 0)
	{
		return ;
	}

	Json::Reader reader;
	for (unsigned i = 0; i < datas.size(); i++)
	{
		Json::Value json;
		if (!reader.parse(datas[i].data, json))
		{
			continue;
		}

		int def = json["def"].asInt();

		if (def > 0)
		{
			Json::GetString(json, "id", heroid);
			Json::GetString(json, "name", heroname);
			return ;
		}
	}
}

void DataLordItems::CheckFisrtLord(const std::vector<int>& types)
{
	if (this->finished > 0)
	{
		return ;
	}

	DataLord lordItem;
	bool bSetFirstLord =  true;
	for (size_t i = 0; i < types.size(); ++i)
	{
		//确保每个子榜都有尊主
		std::map<unsigned int, DataLord>::iterator it = lord.find(types[i]);
		if (it == lord.end() || it->second.setted == 0)
		{
			return;
		}


		if (lordItem.uid == 0)
		{
			lordItem = it->second;
		}
		else
		{
			if (bSetFirstLord && lordItem.uid != it->second.uid)
			{
				bSetFirstLord = false;
			}
		}
	}

	//this->time = Time::GetGlobalTime();

	if (bSetFirstLord)
	{
		lordItem.worship = 0;
		lordItem.type = 0;
		lordItem.headurl = "";

		std::string heroid,heroname;
		GetHeroInfo(lordItem.uid, heroid, heroname);

		lordItem.heroid = heroid;
		lordItem.heroname = heroname;

		lord[0] = lordItem;
	}
	else
	{
#if 0
		//测试数据 !!!!!!!!!!!!!!!
		lordItem.uid = 10003825;
		lordItem.setted = 1;
		lordItem.worship = 0;
		lordItem.type = 0;
		lordItem.headurl = "";

		std::string heroid,heroname;
		GetHeroInfo(lordItem.uid, heroid, heroname);

		lordItem.heroid = heroid;
		lordItem.heroname = heroname;

		lord[0] = lordItem;
#endif
	}

	this->finished = 1;
}

void DataLordItems::GetAllLords(Json::Value& result)
{
	result["id"] = id;
	//result["finished"] = finished;
	result["time"] = time;
	result["list"].clear();
	result["list"].resize(0);
	for (std::map<unsigned int, DataLord>::iterator it = lord.begin();
			it != lord.end();
			++it)
	{
		Json::Value jsonItem;
		if (IsValidUid(it->second.uid))
		{
			jsonItem["uid"] = it->second.uid;
			jsonItem["type"] =  it->second.type;
			jsonItem["name"] = it->second.name;
			jsonItem["worship"] = it->second.worship;
			jsonItem["heroid"] = it->second.heroid;
			jsonItem["heroname"] = it->second.heroname;
			jsonItem["headurl"] = it->second.headurl;

			result["list"].append(jsonItem);
		}
	}
}

Json::Value DataLordItems::ToJson()
{
	Json::Value jsonData;
	jsonData["id"] = id;
	jsonData["finished"] = finished;


	for (std::map<unsigned int, DataLord>::iterator it = lord.begin();
				it != lord.end();
				++it)
	{
		Json::Value jsonDataItem;
		jsonDataItem["Uid"] = it->second.uid;
		jsonDataItem["Name"] = it->second.name;
		jsonDataItem["Type"] = it->second.type;
		jsonDataItem["Setted"] = it->second.setted;
		jsonDataItem["Worship"] = it->second.worship;

		//jsonData["lords"][i++] = it->second.ToString();
		jsonData["lords"].append(jsonDataItem);
	}


	return jsonData;
}
//---------------------------------------------------------

DataLordRankItem::DataLordRankItem(const Json::Value& data)
{
	this->uid = data["uid"].asInt();
	if (! IsValidUid(this->uid))
	{
		throw std::runtime_error("Syncdata_uid_error.");
	}

	this->sumdata = data["value"].asInt();
	if (this->sumdata == 0)
	{
		uint64_t int64Val = (uint64_t)data["uint64_val"].asDouble();
		this->sumdata += int64Val;
	}

	this->name = data["name"].asString();
}

void DataLordRankList::SyncOneItem(const Json::Value& data)
{
	if (data.isArray() || data.isNull())
	{
		return ;
	}

	unsigned uid = 0, val = 0;
	if (! Json::GetUInt(data, "uid", uid)) return;
	if (! Json::GetUInt(data, "value", val)) return;

	uint64_t uint64Val = 0;
	if (data.isMember("uint64_val") && ! data["uint64_val"].isArray())
	{
		uint64Val = (uint64_t)data["uint64_val"].asDouble();
	}
	if (0 == uid || (val == 0 && uint64Val == 0)) return;

	DataLordRankItem item;

	std::map<unsigned int, DataLordRankItem>::iterator it = this->list.find(uid);
	if (it != this->list.end())
	{
		it->second.Refresh(data);
		item = it->second;
	}
	else
	{
		item = DataLordRankItem(data);
		this->list[uid] = DataLordRankItem(data);
	}

	RefreshRank(item);
}

void DataLordRankList::SyncData(const Json::Value& data)
{
	//新的月份，数据清空
	unsigned now = Time::GetGlobalTime();
	if (CTime::GetMonthBeginTime(this->time) != CTime::GetMonthBeginTime(now))
	{
		this->list.clear();
		this->ranks.clear();
	}

	//更新时间
	this->time = now;

	if (data.isArray())
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			SyncOneItem(data[i]);
		}
	}
	else
	{
		SyncOneItem(data);
	}


}

size_t DataLordRankList::RankSize() const
{
	return ranks.size();
}

void DataLordRankList::RefreshRank(const DataLordRankItem& item)
{
	bool update = false;
	for (std::list<DataLordRankItem>::iterator it = ranks.begin()
			; it != ranks.end()
			; ++it)
	{
		if (item.uid == it->uid)
		{
			*it = item;
			update = true;
			break;
		}
	}

	if (! update)
	{
		ranks.push_back(item);
	}

	ranks.sort(std::greater<DataLordRankItem>());

	if (ranks.size() > 30)
	{
		ranks.pop_back();
	}
}

void DataLordRankList::GetRankList(Json::Value& result)
{
	result.clear();
	if (ranks.empty())
	{
		result["list"] = Json::arrayValue;
	}
	else
	{
		for (std::list<DataLordRankItem>::iterator it = ranks.begin()
						; it != ranks.end()
						; ++it)
		{
			Json::Value jsonItem;
			jsonItem["uid"] = it->uid;
			jsonItem["name"] = it->name;
			jsonItem["value"] = Convert::UInt64ToString(it->sumdata);

			result["list"].append(jsonItem);
		}

		result["update"] = this->time;
	}

}

Json::Value DataLordRankList::ToJson()
{
	Json::Value jsonData;
	jsonData["type"] = type;
	jsonData["time"] = time;

	//int i = 0;
	for (std::list<DataLordRankItem>::iterator it = ranks.begin()
							; it != ranks.end()
							; ++it)
	{

		Json::Value jsonDataItem;
		jsonDataItem["uid"] = it->uid;
		jsonDataItem["name"] = it->name;
		jsonDataItem["value"] =  Convert::UInt64ToString(it->sumdata);

		//jsonData["ranks"][i++] = it->ToString();
		jsonData["ranks"].append(jsonDataItem);
	}

	return jsonData;
}

const DataLordRankItem& DataLordRankList::GetFirstRank() const
{
	if (this->ranks.empty())
	{
		throw std::runtime_error("rank_list_is_empty");
	}

	return this->ranks.front();
}

void DataLordRankList::GetRewardUsers(size_t cnt, std::vector<unsigned>& result)
{
	result.clear();
	if (this->ranks.size() > 0 && cnt > 0)
	{
		size_t i = 0;
		for (std::list<DataLordRankItem>::iterator it = ranks.begin()
					; it != ranks.end() && i < cnt
					; ++it,++i)
		{
			result.push_back(it->uid);
		}
	}
}

void DataLordContainer::SyncRankList(int type, const Json::Value& data)
{
	this->ranks[type].type = type;
	this->ranks[type].SyncData(data);
}

int DataLordContainer::GetFinished(unsigned id)
{
	//if (lords.count(id) == 0)
	//{
	//	throw std::runtime_error("not_exist_id");
	//}

	return lords[id].finished;
}

int DataLordContainer::RadicateLord(int type)
{
	//
	time_t now = Time::GetGlobalTime();
	unsigned savetime = lords[m_nCurId].time;

	//
	if (savetime > 0 && CTime::GetMonthBeginTime(now) != CTime::GetMonthBeginTime(savetime))
	{
		lords[++ m_nCurId].time = now;
	}

	if (savetime == 0)
	{
		lords[m_nCurId].time = now;
	}

	int ret = 0;
	if (ranks[type].RankSize() > 0)
	{
		ret = lords[m_nCurId].RadicateLord(m_nCurId, type, ranks[type].GetFirstRank());
	}
	else
	{
		DataLordRankItem item;
		ret = lords[m_nCurId].RadicateLord(m_nCurId, type, item);
	}

	return ret == 0 ? m_nCurId : -1;
}

int DataLordContainer::Worship(unsigned id, int type)
{
	std::map<unsigned int, DataLordItems>::iterator it =  lords.find(id);
	if (it == lords.end())
	{
		throw std::runtime_error("Worship_id_error");
	}

	return it->second.Worship(type);
}

void DataLordContainer::CheckFisrtLord(const std::vector<int>& types)
{
	std::map<unsigned int, DataLordItems>::iterator it =  lords.find(m_nCurId);
	if (it == lords.end())
	{
		throw std::runtime_error("Worship_id_error");
	}

	it->second.CheckFisrtLord(types);
}

void DataLordContainer::GetRewardUsers(int type, size_t cnt, std::vector<unsigned>& result)
{
	std::map<unsigned int, DataLordRankList>::iterator it = ranks.find(type);
	if (it != ranks.end())
	{
		it->second.GetRewardUsers(cnt, result);
	}
}

void DataLordContainer::CloseWorship()
{
	//
	if (m_nCurId <= 1)
	{
		return ;
	}

	std::map<unsigned int, DataLordItems>::iterator it =  lords.find(m_nCurId - 1);
	if (it != lords.end())
	{
		it->second.finished = 2;
	}
}

void DataLordContainer::GetRankList(int type, Json::Value& result)
{
//	std::map<unsigned int, DataLordRankList>::iterator it = ranks.find(type);
//	if (it == ranks.end())
//	{
//		throw std::runtime_error("rank_type_error");
//	}

	ranks[type].GetRankList(result);
}

void DataLordContainer::GetAllLords(Json::Value& result)
{
	result["lords"].resize(lords.size());

	int i = 0;
	for (std::map<unsigned int, DataLordItems>::iterator it =  lords.begin();
			it != lords.end(); ++it)
	{
		it->second.GetAllLords(result["lords"][i]);
		i++;
	}
}

std::string DataLordContainer::ToString()
{
	Json::Value jsonData;
	jsonData["CurId"] = m_nCurId;

	for (std::map<unsigned int, DataLordItems>::iterator it =  lords.begin();
				it != lords.end(); ++it)
	{
		jsonData["alllords"].append(it->second.ToJson());
	}

	for (std::map<unsigned int, DataLordRankList>::iterator it = ranks.begin();
			it != ranks.end(); ++it)
	{
		jsonData["allranks"].append(it->second.ToJson());
	}

	return Json::ToString(jsonData);
}
//------------------------------------------------------------------------------

DataLordContainer& DataLordAllZone::ZoneByUid(unsigned uid)
{
	unsigned zoneid = Config::GetZoneByUID(uid);
	return ZoneById(zoneid);

}
DataLordContainer& DataLordAllZone::ZoneById(unsigned zoneid)
{
	if (zoneid <= 704)
	{
		return mZones[0];
	}
	else
	{
		return mZones[1];
	}
}

void DataLordAllZone::SyncRankList(int type, const Json::Value& data)
{
	if (type < EXPLOIT || type > RECHARGE)
	{
		error_log("type error: %d", type);
		throw std::runtime_error("rank_type_params_error");
	}

	for (unsigned i = 0; i < data.size(); ++i)
	{
		if (! data[i].isMember("uid") || !data[i]["uid"].isIntegral())
		{
			continue;
		}
		//
		unsigned uid = data[i]["uid"].asUInt();
		ZoneByUid(uid).SyncRankList(type, data[i]);
	}
}

void  DataLordAllZone::RadicateLord(int type)
{
	if (type < EXPLOIT || type > RECHARGE)
	{
		error_log("type error: %d", type);
		return ;
	}

	for (int i = 0; i < ZONES; ++i)
	{
		int id = mZones[i].RadicateLord(type);
		if (id >= 0)
		{
			//检查总榜尊主
			std::vector<int> vTypes;
			for (int k = EXPLOIT; k <= RECHARGE; k++)
			{
				vTypes.push_back(k);
			}

			mZones[i].CheckFisrtLord(vTypes);

			//发放奖励
			std::vector<unsigned> vUsers;
			mZones[i].GetRewardUsers(type, 30, vUsers);
			for (size_t k = 0; k < vUsers.size(); k++)
			{
				ProvideRankReward(id, vUsers[k], type, k + 1);
			}
		}
	}
}

int DataLordAllZone::Worship(unsigned uid, int id, int type)
{
	return ZoneByUid(uid).Worship(id, type);
}

void DataLordAllZone::GetRankList(unsigned uid, int type, Json::Value& result)
{
	if (type < EXPLOIT || type > RECHARGE)
	{
		throw std::runtime_error("rank_type_params_error");
	}

	ZoneByUid(uid).GetRankList(type, result);
}

void DataLordAllZone::GetAllLords(unsigned uid, Json::Value& result)
{
	ZoneByUid(uid).GetAllLords(result);
}

unsigned DataLordAllZone::GetRewardBagId(int type, int rank)
{
	const unsigned rewardsTb[RECHARGE][3] = {
			{8501, 8502, 8503},
			{8511, 8512, 8513},
			{8521, 8522, 8523},
			{8531, 8532, 8533},
			{8541, 8542, 8543}
	};


	if (type >= EXPLOIT && type <= RECHARGE && rank >= 1 && rank <= 3)
	{
		return rewardsTb[type-1][rank-1];
	}
	else
	{
		//@ add oulong 20160725 添加4-30名的奖励
		if (rank >= 4 && rank <= 10)
		{
			return 8701;
		}
		else if (rank <= 30)
		{
			return 8702;
		}
	}

	error_log("Get_reward_params_error. type=%d,rank=%d", type, rank);
	throw std::runtime_error("get_reward_bag_error");
}

void DataLordAllZone::ProvideRankReward(int id, unsigned uid, int type, int rank)
{
	std::string reason = "lord_reward_op";
	Json::Value jsonResult;

	unsigned itemid = GetRewardBagId(type, rank);
	CLogicEquipment logicEquipment;
	int ret = logicEquipment.AddOneItem(uid, itemid, 1, reason, jsonResult["equipment"], true);
	if (ret != R_SUCCESS)
	{
		error_log("Provied lord rank reward error! uid=%d,type=%d,rank=%d", uid, type, rank);
		return ;
	}

	//发送邮件
	Json::Value update;
	CLogicUpdates logicUpdates;
	update["ts"] = Time::GetGlobalTime();
	update["s"] = "LORDRANKREWARD";
	update["rank"] = rank;
	update["lordid"] = id;
	update["type"] = type;
	update["result"] = jsonResult;
	logicUpdates.AddUpdates(uid, update, true);
}



//------------------------------------------------------------------------------
CDataAllServerLordsList::CDataAllServerLordsList(const std::string& path)
	: DataBase(path)
{
	m_msg = new DataType();
}

int CDataAllServerLordsList::Init()
{
	int ret = Parse();
	if (ret) return ret;

	m_data.Parse(*(DataTypePtr)m_msg);
	((DataTypePtr)m_msg)->Clear();

	return 0;
}

int CDataAllServerLordsList::Save()
{
	int ret = 0;
	m_data.Serialize((DataTypePtr)m_msg);

	ret = Serialize();
	if (ret)
		return ret;
	((DataTypePtr)m_msg)->Clear();

	return 0;
}

int CDataAllServerLordsList::Sig(int sig)
{
	try
	{
		if (sig == SIGRTMIN+1)
			Output();
		else if (sig >=  SIGRTMIN+ 2 || sig <= SIGRTMIN + 6)
		{
			int type = sig - (int)SIGRTMIN - 1;
			m_data.RadicateLord(type);
		}
	}
	catch(const std::exception& e)
	{
		::SetError(R_ERROR, e.what());
		error_log("%s", e.what());
		return R_ERROR;
	}

	return 0;
}

int CDataAllServerLordsList::Output()
{
#if 0
	int ret = 0;
	string data = m_data.ToString();

	string path = Config::GetPath("data/Lord.output", 1);
	ret = File::Write(path, data);
	return ret;
#endif
	return 0;
}
//------------
void CDataAllServerLordsList::Sync(int type, const Json::Value& data)
{
	m_data.SyncRankList(type, data);
}

int CDataAllServerLordsList::Worship(unsigned uid, int id, int type)
{
	return m_data.Worship(uid, id, type);
}


void CDataAllServerLordsList::CloseWorship()
{
	//m_data.CloseWorship();
}

void CDataAllServerLordsList::GetRankList(unsigned uid, int type, Json::Value& result)
{
	m_data.GetRankList(uid, type, result);

}

void CDataAllServerLordsList::GetAllLords(unsigned uid, Json::Value& result)
{
	m_data.GetAllLords(uid, result);
}
//----------------------------------------------------------------------

