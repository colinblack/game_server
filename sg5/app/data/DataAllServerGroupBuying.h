#ifndef DATA_ALL_SERVER_GROUPBUYING_H
#define DATA_ALL_SERVER_GROUPBUYING_H

#include "Kernel.h"
#include <math.h>
#include "DataBase.h"
#include "AllServerGroupBuy.pb.h"

class DataGroupBuyingUser
{
public:
	unsigned int uid;
	unsigned int join_stage;
	unsigned int back_stage;

	DataGroupBuyingUser()
	{
		uid = 0;
		join_stage = 0;
		back_stage = 0;
	}

	~DataGroupBuyingUser()
	{
	}

	void Serialize(AllServerGroupBuy::GroupBuyingUser *p)
	{
		p->set_uid(uid);
		p->set_join_stage(join_stage);
		p->set_back_stage(back_stage);
	}

	void Parse(const AllServerGroupBuy::GroupBuyingUser &p)
	{
		uid = p.uid();
		join_stage = p.join_stage();
		back_stage = p.back_stage();
	}
};

class DataGroupBuyingItem
{
public:
	unsigned int id;
	map<unsigned int, DataGroupBuyingUser> customers;

	DataGroupBuyingItem()
	{
		id = 0;
	}

	~DataGroupBuyingItem()
	{
	}

	void Serialize(AllServerGroupBuy::GroupBuyingItem *p)
	{
		p->set_id(id);
		for (map<unsigned int, DataGroupBuyingUser>::iterator it =
				customers.begin(); it != customers.end(); ++it)
			it->second.Serialize(p->add_customers());
	}

	void Parse(const AllServerGroupBuy::GroupBuyingItem &p)
	{
		id = p.id();
		for (int i = 0; i < p.customers_size(); ++i)
			customers[p.customers(i).uid()].Parse(p.customers(i));
	}
};

class DataGroupBuing
{
public:
	unsigned int  version;
	map<unsigned int, DataGroupBuyingItem> items;

	DataGroupBuing()
	{
		version = 0;
	}

	~DataGroupBuing()
	{
	}

	void Serialize(AllServerGroupBuy::GroupBuing *p)
	{
		p->set_version(version);

		for (map<unsigned int, DataGroupBuyingItem>::iterator it =
				items.begin(); it != items.end(); ++it)
			it->second.Serialize(p->add_items());
	}

	void Parse(const AllServerGroupBuy::GroupBuing &p)
	{
		version = p.version();

		for (int i = 0; i < p.items_size(); ++i)
			items[p.items(i).id()].Parse(p.items(i));
	}
};

class CDataAllServerGroupBuying : public DataBase
{
public:
	CDataAllServerGroupBuying(string path);
	virtual ~CDataAllServerGroupBuying() {}
	int Init();
	int Save();

	enum
	{
		max_items_nums = 3, //团购项个数
	};

	//获取所有团购项目的信息
	DataGroupBuing & GetBuyingItems() {return m_data;}

	//设置团购消息
	int SetGroupBuyingMsg(unsigned uid, Json::Value & result);

	//将用户加入团购项目
	int JoinGroupBuying(unsigned uid, unsigned id, unsigned stage);

	//更新返还的阶段
	int UpdateBackStage(unsigned uid, unsigned id, unsigned stage);

	//获取团购项目的信息
	DataGroupBuyingItem & GetGroupItem(unsigned id);

	//判断用户是否参与了某个团购
	bool IsUserJoinGroup(unsigned id, unsigned uid);

	//获得参与某个团购的用户信息
	DataGroupBuyingUser & GetGroupUser(unsigned id, unsigned uid);

	//重置团购信息
	int ResetGroupBuying(unsigned version);

private:
	DataGroupBuing m_data;
};

#endif  //DATA_ALL_SERVER_GROUPBUYING_H
