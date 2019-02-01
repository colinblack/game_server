#ifndef DATA_ALL_MANAGER_H_
#define DATA_ALL_MANAGER_H_

#include "Kernel.h"
#include "DBCMultipleTemplate.h"
#include "DataItem.h"
#include "DataHero.h"
#include "DataConcern.h"
#include "DataMartialClub.h"
#include "DataMartialHero.h"
#include "DataInvite.h"
#include "DataDetachHero.h"

class DataItemManager : public DBCMultipleTemplate<DataItem, DB_ITEM, DB_ITEM_FULL, CDataItem>
						, public CSingleton<DataItemManager>
{
public:
	virtual void CallDestroy() { Destroy();}
	const char* name() const  { return "DataItemManager"; }

	int Init(unsigned uid);

	//获取下一个ud
	unsigned GetUserNextUd(unsigned uid);

	//判断道具id用户是否存在
	bool IsPropsExist(unsigned uid, unsigned propsid);

	//适合获取唯一存在的建筑，如果不是唯一的，那么ud值是第一个
	unsigned GetPropsUd(unsigned uid, unsigned propsid);

	//新增道具
	int AddNewProps(DataItem & propsitem);

	//删除装备
	int DelProps(DataItem & propsitem);

private:
	map<unsigned, uint32_t> m_userMaxUd;
	map<unsigned, map<uint32_t, vector<uint32_t> > > m_PropsUd; //uid =》(propsid->ud)
};


class DataHeroManager : public DBCMultipleTemplate<DataHero, DB_HERO, DB_HERO_FULL, CDataHero>, public CSingleton<DataHeroManager> {
public:
	virtual void CallDestroy(){Destroy();}

	 const char* name() const
	 {
		 return("DataHeroManager");
	 }
};

//关注列表
class DataConcernManager : public DBCMultipleTemplate<DataConcern, DB_CONCERN, DB_CONCERN_FULL, CDataConcern>
	,public CSingleton<DataConcernManager>
{
public:
	virtual void CallDestroy()
	{
		Destroy();
	}

	const char* name() const
	{
		return "DataConcernManager";
	}
};

//武馆
class DataMartialClubManager : public DBCMultipleTemplate<DataMartialClub, DB_MARTIAL_CLUB, DB_MARTIAL_CLUB_FULL, CDataMartialClub>
	 	 ,public CSingleton<DataMartialClubManager>
{
public:
	virtual void CallDestroy()
	{
		Destroy();
	}

	const char* name() const
	{
		return "DataMartialClubManager";
	}
};

//武馆中的英雄
class DataMartialHeroManager : public DBCMultipleTemplate<DataMartialHero, DB_MARTIAL_HERO, DB_MARTIAL_HERO_FULL, CDataMartialHero>
	 	 ,public CSingleton<DataMartialHeroManager>
{
public:
	virtual void CallDestroy()
	{
		Destroy();
	}

	const char* name() const
	{
		return "DataMartialHeroManager";
	}
};

//邀请好友
class DataInviteManager : public DBCMultipleTemplate<DataInvite, DB_INVITE, DB_INVITE_FULL, CDataInvite>
	 	 ,public CSingleton<DataInviteManager>
{
public:
	virtual void CallDestroy()
	{
		Destroy();
	}

	const char* name() const
	{
		return "DataInviteManager";
	}
};


class DataDetachHeroManager : public DBCMultipleTemplate<DataDetachHero, DB_DETACH_HERO, DB_DETACH_HERO_FULL, CDataDetachHero>
	 	 ,public CSingleton<DataDetachHeroManager>
{
public:
	virtual void CallDestroy()
	{
		Destroy();
	}

	const char* name() const
	{
		return "DataDetachHeroManager";
	}
};


#endif //DATA_ALL_MANAGER_H_
