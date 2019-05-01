#include "LogicMarketManager.h"
#include "DataMarket.h"

int LogicMarketManager::NewUserInit(unsigned uid)
{
	//判断集市是否存在数据库
	bool isExists = DataMarketManager::Instance()->IsDataMarketExists(uid);

	if (!isExists)
	{
		DataMarket datamarket;
		datamarket.uid = uid;

		DataMarketManager::Instance()->AddBuff(datamarket);
	}

	try
	{
		DataMarket & datamarket = DataMarketManager::Instance()->Get(uid);

		//判断是否刷新过
		if (0 == datamarket.type1 || 0 == datamarket.type2 || 0 == datamarket.type3)
		{
			RefreshByTime(uid);
		}
	}
	catch (exception &e)
	{
		throw e;
	}

	return 0;
}

int LogicMarketManager::LoginCheck(unsigned uid)
{
	//判断集市数据是否加载进内存
	bool isExists = DataMarketManager::Instance()->IsDataMarketExists(uid);

	if (!isExists)
	{
		//没有数据。重新加载一遍
		int ret = DataMarketManager::Instance()->LoadBuff(uid);

		if (R_ERR_NO_DATA == ret)   //表中没有数据，重新初始化
		{
			return NewUserInit(uid);
		}
		else
		{
			return ret;
		}
	}

	return 0;
}

int LogicMarketManager::Purchase(unsigned uid, unsigned index, ProtoMarket::PurchaseMarketResp *respmsg)
{
	//判断参数
	if (index < 1 || index > 3)
	{
		error_log("[Purchase] index param error. uid=%u, index=%u", uid, index);
		return R_ERR_PARAM;
	}

	try
	{
		DataMarket & datamarket = DataMarketManager::Instance()->Get(uid);

		uint8_t type = 0;
		uint8_t characer = 0;

		switch(index)
		{
			case 1: type = datamarket.type1; characer = datamarket.character1; break;
			case 2: type = datamarket.type2; characer = datamarket.character2; break;
			case 3: type = datamarket.type3; characer = datamarket.character3; break;
		}

		DBCUserBaseWrap userbase(uid);

		map<unsigned, unsigned> m_mapresource;
		int val = GetMarketValue(type, characer);

		switch(type)
		{
			case resource_type_wood :
				m_mapresource.insert(make_pair(type, val));
				userbase.AddResource(m_mapresource, "MarketBuy");
				respmsg->set_wood(userbase.Obj().wood);
				break;
			case resource_type_food :
				m_mapresource.insert(make_pair(type, val));
				userbase.AddResource(m_mapresource, "MarketBuy");
				respmsg->set_food(userbase.Obj().food);
				break;
			case resource_type_iron :
				m_mapresource.insert(make_pair(type, val));
				userbase.AddResource(m_mapresource, "MarketBuy");
				respmsg->set_iron(userbase.Obj().iron);
				break;
			case times_type_order:
				userbase.AddRecruitProp(val, "MarketBuy");
				respmsg->set_order(userbase.Obj().order);
				break;
		}

		userbase.Save();
	}
	catch (exception &e)
	{
		error_log("[Purchase] exception happen. reason:%s", e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicMarketManager::RefreshAfterBuy(unsigned uid)
{
	try
	{
		DataMarket & datamarket = DataMarketManager::Instance()->Get(uid);

		//分别随机三个位置的资源类型以及对应的品质
		MarketItem marketitem;

		//第一格
		RefreshMarketItem(marketitem);
		datamarket.type1 = marketitem.type;
		datamarket.character1 = marketitem.character;

		//第二格
		RefreshMarketItem(marketitem);
		datamarket.type2 = marketitem.type;
		datamarket.character2 = marketitem.character;
		//第三格
		RefreshMarketItem(marketitem);
		datamarket.type3 = marketitem.type;
		datamarket.character3 = marketitem.character;

		DataMarketManager::Instance()->UpdateDataMarket(datamarket);
	}
	catch (exception &e)
	{
		error_log("[RefreshAfterBuy] exception happen. reason:%s", e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicMarketManager::RefreshByTime(unsigned uid)
{
	//判断时间是否可以刷新
	unsigned now = Time::GetGlobalTime();

	//获取集市数据
	try
	{
		DataMarket & datamarket = DataMarketManager::Instance()->Get(uid);

		if (now < datamarket.refreshtime)
		{
			error_log("[RefreshByTime] time not ready. uid=%u", uid);
			return R_ERROR;
		}

		//分别随机三个位置的资源类型以及对应的品质
		MarketItem marketitem;

		//第一格
		RefreshMarketItem(marketitem);
		datamarket.type1 = marketitem.type;
		datamarket.character1 = marketitem.character;

		//第二格
		RefreshMarketItem(marketitem);
		datamarket.type2 = marketitem.type;
		datamarket.character2 = marketitem.character;
		//第三格
		RefreshMarketItem(marketitem);
		datamarket.type3 = marketitem.type;
		datamarket.character3 = marketitem.character;

		datamarket.refreshtime = now;

		DataMarketManager::Instance()->UpdateDataMarket(datamarket);
	}
	catch (exception &e)
	{
		error_log("[RefreshByTime] exception happen. reason:%s", e.what());
		return R_ERROR;
	}

	return 0;
}

int LogicMarketManager::RefreshMarketItem(MarketItem & marketitem)
{
	//随机类型，在2-5之间随机
	marketitem.type = LogicCommonUtil::GetRandomBetweenAB(resource_type_wood, times_type_order);

	//随机品质，在1-5之间取
	marketitem.character = LogicCommonUtil::GetRandomBetweenAB(1,5);

	return 0;
}

int LogicMarketManager::GetMarketValue(uint8_t type, uint8_t characer)
{
	int val = 100;
	//todo 查询配置文件，然后计算出值
	val = MarketConfigWrap().GetValueByTypeAndCharacter(type, characer);

	return val;
}

int LogicMarketManager::FullMessage(unsigned uid, ProtoMarket::MarketCPP *msg)
{
	try
	{
		DataMarket & datamarket = DataMarketManager::Instance()->Get(uid);
		datamarket.SetMessage(msg);
	}
	catch (exception &e)
	{
		error_log("[FullMessage] exception happen. reason:%s", e.what());
		return R_ERROR;
	}

	return 0;
}
