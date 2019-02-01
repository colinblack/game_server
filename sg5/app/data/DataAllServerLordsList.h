/*
 * DataAllServerLoardsList.h
 *
 *  Created on: 2016-7-6
 *      Author: dawx62fac
 */

#ifndef DATAALLSERVERLOARDSLIST_H_
#define DATAALLSERVERLOARDSLIST_H_


#include "Kernel.h"
#include "DataBase.h"
#include "AllServerLords.pb.h"

class DataLordRankItem {
public:
	unsigned int uid;
	string name;
	uint64_t sumdata;   //月统计数据

	DataLordRankItem(const Json::Value& data);


	DataLordRankItem() {
		uid = 0;
		sumdata = 0;
	}
	~DataLordRankItem() {
	}
	void Serialize(AllServerLords::LordRankItem *p)
	{
		p->set_uid(uid);
		p->set_name(name);
		p->set_sumdata(sumdata);
	}

	void Parse(const AllServerLords::LordRankItem &p)
	{
		uid = p.uid();
		name = p.name();
		sumdata = p.sumdata();
	}


	friend inline  bool operator > (const DataLordRankItem& l
			, const DataLordRankItem& r)
	{
		return l.sumdata > r.sumdata;
	}

	void Refresh(const Json::Value& data);
	std::string ToString();
};

class DataLord {
public:
	unsigned int uid;
	unsigned int type;
	unsigned int worship;   //膜拜
	unsigned int setted; //是否设置
	std::string name;
	std::string headurl;
	std::string heroid; //主将id
	std::string heroname; //
	DataLord() {
		uid = 0;
		type = 0;
		worship = 0;
		setted = 0;
	}

	DataLord(int type, const DataLordRankItem& item)
	{
		this->type = type;
		this->uid = item.uid;
		this->name = item.name;
		this->setted = 1;
		this->worship = 0;
		this->heroid = "";
		this->headurl = "";
		this->heroname = "";
	}

	~DataLord() {
	}
	void Serialize(AllServerLords::Lord *p) {
		p->set_uid(uid);
		p->set_type(type);
		p->set_worship(worship);
		p->set_setted(setted);
		p->set_name(name);
		p->set_heroid(heroid);
		p->set_headurl(headurl);
		p->set_heroname(heroname);
	}
	void Parse(const AllServerLords::Lord &p) {
		uid = p.uid();
		type = p.type();
		worship = p.worship();
		setted = p.setted();
		name = p.name();
		heroid = p.heroid();
		headurl = p.headurl();
		heroname = p.heroname();
	}

	std::string ToString();
};
class DataLordItems {
public:
	unsigned int id;
	unsigned int time;
	unsigned int finished; //0--未完  1--设置尊主结束 2--膜拜结束
	map<unsigned int, DataLord> lord;
	DataLordItems() {
		id = 0;
		time = 0;
		finished = 0;
	}
	~DataLordItems() {
	}
	void Serialize(AllServerLords::LordItems *p) {
		p->set_id(id);
		p->set_time(time);
		p->set_finished(finished);
		for (map<unsigned int, DataLord>::iterator it = lord.begin();
				it != lord.end(); ++it)
			it->second.Serialize(p->add_lord());
	}
	void Parse(const AllServerLords::LordItems &p) {
		id = p.id();
		time = p.time();
		finished = p.finished();
		for (int i = 0; i < p.lord_size(); ++i)
			lord[p.lord(i).type()].Parse(p.lord(i));
	}

	int RadicateLord(int id, int type, const DataLordRankItem& item); //确立尊主
	int Worship(int type); //膜拜
	void CheckFisrtLord(const std::vector<int>& types);

	int GetFinished() const;

	void GetAllLords(Json::Value& result);

	Json::Value ToJson();
private:
	std::string GetHeadUrl(unsigned uid) const;
	void GetHeroInfo(unsigned uid, std::string& heroid, std::string& heroname) const;
};

class DataLordRankList
{
public:
	unsigned int type;
	unsigned int time;
	map<unsigned int, DataLordRankItem> list;
	//std::vector<DataLordRankItem> list;

private:
	//----------------------------------------------
	//用于保存前30名
	std::list<DataLordRankItem> ranks;

	void RefreshRank(const DataLordRankItem& item);
	//---------------------------------------------


	void SyncOneItem(const Json::Value& data);

public:
	//获取第一名
	const DataLordRankItem& GetFirstRank() const;

	void GetRewardUsers(size_t cnt, std::vector<unsigned>& result);

	void GetRankList(Json::Value& result);

	//同步排行榜数据
	void SyncData(const Json::Value& data);


	Json::Value ToJson();

	size_t RankSize() const;

	DataLordRankList() {
		type = 0;
		time = 0;
	}
	~DataLordRankList() {
	}

	void Serialize(AllServerLords::LordRankList *p)
	{
		p->set_type(type);
		p->set_time(time);

		for (map<unsigned int, DataLordRankItem>::iterator it = list.begin();
				it != list.end(); ++it)
		{
			it->second.Serialize(p->add_list());
		}
	}
	void Parse(const AllServerLords::LordRankList &p) {
		type = p.type();
		time = p.time();
		for (int i = 0; i < p.list_size(); ++i)
		{

			list[p.list(i).uid()].Parse(p.list(i));

			DataLordRankItem item = list[p.list(i).uid()];
			RefreshRank(item);
		}
	}
};
class DataLordContainer {
public:
	unsigned m_nCurId;  //注意！！！ 起始为 值为 1
	std::map<unsigned int, DataLordItems> lords;
	std::map<unsigned int, DataLordRankList> ranks;
	DataLordContainer() {
		m_nCurId = 1;
	}
	~DataLordContainer() {
	}
	void Serialize(AllServerLords::LordContainer *p) {
		//lords.Serialize(p->mutable_lords());
		p->set_curid(m_nCurId);
		for (map<unsigned int, DataLordItems>::iterator it = lords.begin();
						it != lords.end(); ++it)
		{
			it->second.Serialize(p->add_lords());
		}


		for (map<unsigned int, DataLordRankList>::iterator it = ranks.begin();
				it != ranks.end(); ++it)
		{
			it->second.Serialize(p->add_ranks());
		}

	}
	void Parse(const AllServerLords::LordContainer &p) {
		//lords.Parse(p.lords());
		m_nCurId = p.curid();
		for (int i = 0; i < p.lords_size(); ++i)
		{
			lords[p.lords(i).id()].Parse(p.lords(i));
		}

		for (int i = 0; i < p.ranks_size(); ++i)
		{
			ranks[p.ranks(i).type()].Parse(p.ranks(i));
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	void SyncRankList(int type, const Json::Value& data);

	//确立尊主  //return id
	int  RadicateLord(int type);
	//膜拜
	int Worship(unsigned id, int type);

	int GetFinished(unsigned id);

	void CheckFisrtLord(const std::vector<int>& types);

	void GetRewardUsers(int type, size_t cnt, std::vector<unsigned>& result);

	//关闭膜拜
	void CloseWorship();

	//
	void GetRankList(int type, Json::Value& result);
	void GetAllLords(Json::Value& result);

	std::string ToString();
};

class DataLordAllZone
{
	enum  {
		ZONES = 2,
	};

	enum {
		EXPLOIT = 1,
		TRYNDAMERE,
		PLUNDER,
		DIAMONDS,
		RECHARGE
	};

public:
	DataLordAllZone() {}
	~DataLordAllZone() {}

	void Serialize(AllServerLords::LordAllZone *p) {
		for (int i = 0; i < ZONES; ++i)
		{
			mZones[i].Serialize(p->add_zones());
		}
	}

	void Parse(const AllServerLords::LordAllZone &p) {

		for (int i = 0; i < p.zones_size() && i < ZONES; ++i)
		{
			mZones[i].Parse(p.zones(i));
		}
	}

	//--------------------------------------------------
	void SyncRankList(int type, const Json::Value& data);
	void RadicateLord(int type);
	int Worship(unsigned uid, int id, int type);
	void GetRankList(unsigned uid, int type, Json::Value& result);
	void GetAllLords(unsigned uid, Json::Value& result);
private:
	//发放子榜奖励
	void ProvideRankReward(int id, unsigned uid, int type, int rank);
	unsigned GetRewardBagId(int type, int rank);

	DataLordContainer& ZoneByUid(unsigned uid); //用户UID
	DataLordContainer& ZoneById(unsigned zoneid); //用户UID
private:
	//分两个大区
	DataLordContainer mZones[2];
};



class CDataAllServerLordsList : public DataBase
{
	typedef AllServerLords::LordAllZone DataType;
	typedef AllServerLords::LordAllZone* DataTypePtr;
public:
	CDataAllServerLordsList(const std::string& path);

	int Init();
	int Save();
	int Sig(int sig);
	int Output();

	//同步数据
	void Sync(int type, const Json::Value& data);
	//膜拜
	int Worship(unsigned uid, int id, int type);
	void CloseWorship();

	void GetRankList(unsigned uid, int type, Json::Value& result);
	void GetAllLords(unsigned uid, Json::Value& result);
private:
	DataLordAllZone m_data;

};



#endif /* DATAALLSERVERLOARDSLIST_H_ */
