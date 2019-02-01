/*
 * DataXmlUnit.cpp
 *
 *  Created on: 2016-8-5
 *      Author: dawx62fac
 */

#include "DataXmlUnit.h"

int DataXMLTemplePray::Parse(const std::string& fullCfg, DataXMLTemple* pData)
{
	CMarkupSTL xmlConf;

	if(!xmlConf.Load(fullCfg.c_str()))
	{
		error_log("load cfg.xml failed. path: %s", fullCfg.c_str());
		throw std::runtime_error("[DataXMLTemplePray]load_cfg_failed.");
	}

	if (! xmlConf.FindElem("content"))
	{
		error_log("prayconfig.xml => content node error");
		throw std::runtime_error("prayconfig.xml_conntent_node_error");
	}
	////////////////////////////////////////////////////////////////
	xmlConf.IntoElem();

	int index = 0;
	while(xmlConf.FindElem("pray") && index < XML_DATA_TEMPLE_ITEMS)
	{
		unsigned id = CTrans::STOI(xmlConf.GetAttrib("id"));
		if (id == 0) continue;

		pData->items[index].id = id;
		pData->items[index].cost = CTrans::STOI(xmlConf.GetAttrib("coin"));
		pData->items[index].level = CTrans::STOI(xmlConf.GetAttrib("level"));

		xmlConf.IntoElem();

		/////////////////////////////////////////////////////////////////////
		if (! xmlConf.FindElem("equipments"))
		{
			error_log("prayconfig.xml => .%d equipments node error", index);
			throw std::runtime_error("prayconfig.xml_equipments_node_error");
		}

		xmlConf.IntoElem();
		int itemIndex = 0;
		while(xmlConf.FindElem("item") && itemIndex <  XML_DATA_GOODS_CNT)
		{
			unsigned rate = CTrans::STOI(xmlConf.GetAttrib("rate"));
			pData->items[index].rate[itemIndex] = rate;
			std::string data = xmlConf.GetData();
			Json::Value jsonData;
			if (! Json::FromString(jsonData, data))
			{
				error_log("prayconfig.xml => data error.1");
				throw std::runtime_error("prayconfig.xml => data error.1");
			}

			if (! pData->items[index].equips[itemIndex].CopyFromJson(jsonData["reward"]["equip1"]))
			{
				error_log("prayconfig.xml => data error.2");
				throw std::runtime_error("prayconfig.xml => data error.2");
			}
			++itemIndex;
		}

		xmlConf.OutOfElem();
		/////////////////////////////////////////////////////////////////////

		xmlConf.OutOfElem();

		++ index;
	}

	return 0;
}

int DataXmlNewRechargeBagUnit::Parse(const std::string& fullCfg, DataXMLNewRecharge* pData)
{
	CMarkupSTL xmlConf;

	if(!xmlConf.Load(fullCfg.c_str()))
	{
		error_log("load cfg.xml failed. path: %s", fullCfg.c_str());
		throw std::runtime_error("[DataXmlNewRechargeBag]load_cfg_failed.");
	}

	if (! xmlConf.FindElem("content"))
	{
		error_log("content_node_error");
		throw std::runtime_error("content_node_error");
	}
	xmlConf.IntoElem();
	////////////////////////////////////////////////////////////////

	if (! xmlConf.FindElem("recharge_gift"))
	{
		error_log("node_recharge_gift_error");
		throw std::runtime_error("recharge_gift_node_error");
	}
	xmlConf.IntoElem();
	////////////////////////////////////////////////////////////////
	int index = 0;
	while(xmlConf.FindElem("reward") && index < XML_DATA_NEW_RECHARGE_ITEMS)
	{
		pData->items[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->items[index].needRecharge = CTrans::STOI(xmlConf.GetAttrib("need_recharge"));

		if (pData->items[index].id == 0 || pData->items[index].needRecharge == 0)
		{
			error_log("id or needRecharge error. index: %d", index);
			throw std::runtime_error("id_or_needRRecharge_node_error");
		}

		////////////////////////////////////////////////////////////////
		std::string data = xmlConf.GetData();
		Json::Value jsonData;
		if (! Json::FromString(jsonData, data))
		{
			error_log("parse data error. index: %d", index);
			throw std::runtime_error("parse_data_error");
		}

		int idxItems = 0;
		//装备
		for (int i = 0; i < XML_DATA_NEW_RECHARGE_REWARD_ITEMS; i++)
		{
			std::string key = "equip" + Convert::IntToString(i + 1);
			if (jsonData["reward"].isMember(key))
			{
				pData->items[index].items[idxItems]
				         = GiftEquipItem(jsonData["reward"][key], false);
				++idxItems;
			}
		}

		//英雄
		for (int i = idxItems; i < XML_DATA_NEW_RECHARGE_REWARD_ITEMS; i++)
		{
			std::string key = "hero" + Convert::IntToString(i - idxItems + 1);
			if (jsonData["reward"].isMember(key))
			{
				pData->items[index].items[idxItems]
						 = GiftEquipItem(jsonData["reward"][key], true);
				++idxItems;
			}
		}

		////////////////////////////////////////////////////////////////

		++index;
	}

	return 0;
}

int DataXmlGroupBuyDailyUnit::Parse(const std::string& fullCfg, DataXMLGroupBuyDaily* pData)
{
	CMarkupSTL xmlConf;

	PreHandleXmlCfg(xmlConf, fullCfg);
	////////////////////////////////////////////////////////////////
	IntoXmlNode(xmlConf, "mm");

	////////////////////////////////////////////////////////////////
	{
		FindXmlNode(xmlConf, "buy");
		pData->buyItem.price = CTrans::STOI(xmlConf.GetAttrib("price"));
		if (pData->buyItem.price == 0)
		{
			error_log("price error");
			throw std::runtime_error("price_cfg_error");
		}


		Json::Value jsonData =  XmlDataToJson(xmlConf);
		for (int i = 0; i < DataXMLGroupBuyDailyBuyItem::EQUIP_ITEMS; ++i)
		{
			std::string key = "equip" + Convert::IntToString(i + 1);
			if (jsonData["reward"].isMember(key))
			{
				pData->buyItem.items[i] = GiftEquipItem(jsonData["reward"][key], false);
			}
		}

		for (int i = 0; i < DataXMLGroupBuyDailyBuyItem::RS_ITEMS; ++i)
		{
			std::string key = "rs" + Convert::IntToString(i + 1);
			if (jsonData["reward"].isMember(key))
			{
				pData->buyItem.rs[i] = jsonData["reward"][key].asUInt();
			}
		}
	}
	////////////////////////////////////////////////////////////////
	int index = 0;
	while(xmlConf.FindElem("reward") && index < DataXMLGroupBuyDaily::REWARD_CNT)
	{
		pData->rewards[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->rewards[index].point = CTrans::STOI(xmlConf.GetAttrib("point"));
		if (pData->rewards[index].id == 0 || pData->rewards[index].point == 0 )
		{
			error_log("index: %d, id: %u, point: %u"
					, index, pData->rewards[index].id, pData->rewards[index].point);
			throw std::runtime_error("DataXmlGroupBuyDailyUnit::Parse_error.");
		}

		Json::Value jsonReward = XmlDataToJson(xmlConf);
		int idxItems = 0;
		for (int i = idxItems; i < DataXMLGroupBuyDailyReward::EQUIP_ITEMS; ++i)
		{
			std::string key = "equip" + Convert::IntToString(i + 1);
			if (jsonReward["reward"].isMember(key))
			{
				pData->rewards[index].items[idxItems++]
				       = GiftEquipItem(jsonReward["reward"][key], false);
			}
		}

		if (jsonReward["reward"].isMember("hero"))
		{
			pData->rewards[index].items[idxItems++]
			       = GiftEquipItem(jsonReward["reward"]["hero"], true);
		}

		////////////////////////////////////////////////////////////////
		++index;
	}

	////////////////////////////////////////////////////////////////
	return 0;
}

void DataXmlLittleRechargeUnit::ParseZoneReward(CMarkupSTL& xmlConf
		, DataXMLLittleRechargeZone zones[DataXMLLittleRecharge::ZONE_CNT])
{
	int index = 0;
	while(xmlConf.FindElem("fcharge")
			&& index < DataXMLLittleRecharge::ZONE_CNT)
	{
		std::vector<std::string> rltZoneAttr;
		std::string zoneAttr = xmlConf.GetAttrib("zoneArr");
		String::Split(zoneAttr, '-', rltZoneAttr);
		if (rltZoneAttr.size() != 2)
		{
			error_log("zoneAttr_error");
			throw std::runtime_error("zoneAttr_error");
		}
		zones[index].zoneStart = CTrans::STOI(rltZoneAttr[0]);
		zones[index].zoneEnd = CTrans::STOI(rltZoneAttr[1]);

		if (zones[index].zoneStart > zones[index].zoneEnd)
		{
			error_log("zone_region_attr_error, start:%d,end:%d"
					, zones[index].zoneStart,zones[index].zoneEnd);
			throw std::runtime_error("zone_region_attr_error");
		}

		Json::Value jsonData = XmlDataToJson(xmlConf);
		int idxitems = 0;
		for (int i = 0; i < DataXMLLittleRechargeZone::EQUIP_ITEMS; ++i)
		{
			std::string key = "equip" + Convert::IntToString(i + 1);
			if (jsonData["reward"].isMember(key))
			{
				zones[index].items[idxitems++]
					   = GiftEquipItem(jsonData["reward"][key], false);
			}
		}

		/////////////////////////////////////////////////////
		++index;
	}
}

int DataXmlLittleRechargeUnit::Parse(const string& fullCfg, DataXMLLittleRecharge* pData)
{
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	/////////////////////////////////////////////////
	IntoXmlNode(xmlConf, "fchargeReward");

	ParseZoneReward(xmlConf, pData->zoneGeneral);

	xmlConf.OutOfElem();
	/////////////////////////////////////////////////
	IntoXmlNode(xmlConf, "fchargeReward4399");

	ParseZoneReward(xmlConf, pData->zone4399);

	xmlConf.OutOfElem();
	/////////////////////////////////////////////////

	return 0;
}

void DataXmlMonthGiftBagUnit::ParseZoneReward(CMarkupSTL& xmlConf, DataXMLMonthGiftBagZone& zone)
{
	std::vector<std::string> rltZoneAttr;
	std::string zoneAttr = xmlConf.GetAttrib("id");
	String::Split(zoneAttr, '-', rltZoneAttr);
	if (rltZoneAttr.size() != 2)
	{
		error_log("zoneAttr_error");
		throw std::runtime_error("zoneAttr_error");
	}
	zone.zoneStart = CTrans::STOI(rltZoneAttr[0]);
	zone.zoneEnd = CTrans::STOI(rltZoneAttr[1]);

	if (zone.zoneStart > zone.zoneEnd)
	{
		error_log("zone_region_attr_error, start:%d,end:%d"
				, zone.zoneStart, zone.zoneEnd);
		throw std::runtime_error("zone_region_attr_error");
	}

	xmlConf.IntoElem();

	//
	int index = 0;
	while(xmlConf.FindElem("item") && index < DataXMLMonthGiftBagZone::EQUIP_ITEMS)
	{
		//
		std::string szId = xmlConf.GetAttrib("id");
		zone.equips[index] = CTrans::STOI(szId);

		++index;
	};

	xmlConf.OutOfElem();
}

int DataXmlMonthGiftBagUnit::Parse(const std::string& fullCfg, DataXMLMonthGiftBag* pData)
{
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	/////////////////////////////////////////////////
	{
		IntoXmlNode(xmlConf, "yuedulibao");

		int index  = 0;
		while(xmlConf.FindElem("zone") && index < DataXMLMonthGiftBag::ZONE_CNT)
		{
			ParseZoneReward(xmlConf, pData->zones[index]);
			++index;
		};

		xmlConf.OutOfElem();
	}
	/////////////////////////////////////////////////
	{
		IntoXmlNode(xmlConf, "yuedulibao_4399");

		int index  = 0;
		while(xmlConf.FindElem("zone") && index < DataXMLMonthGiftBag::ZONE_CNT)
		{
			ParseZoneReward(xmlConf, pData->zones4399[index]);
			++index;
		};

		xmlConf.OutOfElem();
	}
	return 0;
}

/////////////////////
void DataXmlCombinedShopUnit::ParseItemCfg(CMarkupSTL& xmlConf
		, DataXMLCombinedShopItem& item)
{
	item.cost = CTrans::STOI(xmlConf.GetAttrib("cost"));
	item.limit = CTrans::STOI(xmlConf.GetAttrib("limit"));

	if (item.cost <= 0)
	{
		throw std::runtime_error("cost_cfg_error");
	}

	xmlConf.IntoElem();

	int index = 0;
	while(xmlConf.FindElem("item") && index < DataXMLCombinedShopItem::EQUIP_CNT)
	{
		item.equipsId[index] = CTrans::STOI(xmlConf.GetAttrib("eqid"));
		if (item.equipsId[index] <= 0)
		{
			throw std::runtime_error("eqid_cfg_error");
		}

		item.equipsCnt[index] = CTrans::STOI(xmlConf.GetAttrib("count"));
		if (item.equipsCnt[index]  <= 0)
		{
			throw std::runtime_error("eq_cnt_cfg_error");
		}

		++index;
	}

	xmlConf.OutOfElem();
}

int DataXmlCombinedShopUnit::Parse(const std::string& fullCfg, DataXMLCombinedShop* pData)
{
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	int index = 0;
	while(xmlConf.FindElem("zone") && index < DataXMLCombinedShop::ITEMS_CNT)
	{
		ParseItemCfg(xmlConf, pData->items[index]);
		++index;
	}

	return 0;
}
//////////////////////////////////////////////////
int DataXmlNewerAdvanceUnit::Parse(const std::string& fullCfg, DataXMLNewerAdvance* pData)
{
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	IntoXmlNode(xmlConf, "trailer");

	int index = 0;
	while(xmlConf.FindElem("item") && index < DataXMLNewerAdvance::ITEMS_CNT)
	{
		pData->items[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->items[index].level = CTrans::STOI(xmlConf.GetAttrib("level"));

		Json::Value jsonRward = XmlDataToJson(xmlConf);
		pData->items[index].gold = jsonRward["reward"]["gold"].asUInt();
		pData->items[index].exp = jsonRward["reward"]["exp"].asUInt();

		if (pData->items[index].id ==0 || pData->items[index].level == 0
				|| pData->items[index].gold == 0 || pData->items[index].exp == 0)
		{
			throw std::runtime_error("[DataXmlNewerAdvanceUnit]cfg_error");
		}

		++index;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int DataXmlTreasureHuntUnit::Parse(const std::string& fullCfg, DataXMLTreasureHuntExchange* pData)
{
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	IntoXmlNode(xmlConf, "exchangepoint");
	Parse(xmlConf, pData->point);
	xmlConf.OutOfElem();

	IntoXmlNode(xmlConf, "exchangejade");
	Parse(xmlConf, pData->jade);
	xmlConf.OutOfElem();

	return 0;
}

int DataXmlTreasureHuntUnit::Parse(CMarkupSTL& xmlConf
	, DataXMLTreasureHuntExchangeItem items[DataXMLTreasureHuntExchange::ITEMS_CNT])
{
	memset(items, 0, sizeof(DataXMLTreasureHuntExchangeItem)*DataXMLTreasureHuntExchange::ITEMS_CNT);

	int index = 0;
	while(xmlConf.FindElem("item")
			&& index < DataXMLTreasureHuntExchange::ITEMS_CNT)
	{
		items[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		items[index].count = CTrans::STOI(xmlConf.GetAttrib("count"));
		items[index].cost = CTrans::STOI(xmlConf.GetAttrib("cost"));

		/////////////////////////////////////////////////////
		++index;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//圣诞活动
int DataXmlChristmasUint::Parse(const std::string& fullCfg, DataXMLChristmas* pData)
{
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	IntoXmlNode(xmlConf, "newyear");
	IntoXmlNode(xmlConf, "extra");
	Parse(xmlConf, pData->extra);
	xmlConf.OutOfElem();
	int index = 0;
	while(xmlConf.FindElem("egg")
			&& index < DataXMLChristmas::EGG_ITEMS)
	{
		pData->egg[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->egg[index].point = CTrans::STOI(xmlConf.GetAttrib("point"));
		std::string szCold =  xmlConf.GetAttrib("cold");
		if (! szCold.empty())
		{
			pData->egg[index].cold = CTrans::STOI(szCold);
		}
		else
		{
			pData->egg[index].cold = 0;
		}


		xmlConf.IntoElem();
		Parse(xmlConf, pData->egg[index].items);
		xmlConf.OutOfElem();
		/////////////////////////////////////////////////////
		++index;
	}
	xmlConf.OutOfElem();

	return 0;
}

int DataXmlChristmasUint::Parse(CMarkupSTL& xmlConf
	, DataXMLChristmasExtraItem items[DataXMLChristmas::EXTRA_ITEMS])
{
	memset(items, 0, sizeof(DataXMLChristmasExtraItem)*DataXMLChristmas::EXTRA_ITEMS);

	int index = 0;
	while(xmlConf.FindElem("item")
			&& index < DataXMLChristmas::EXTRA_ITEMS)
	{
		items[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		items[index].point = CTrans::STOI(xmlConf.GetAttrib("point"));
		items[index].limit = CTrans::STOI(xmlConf.GetAttrib("limit"));

		Json::Value jsonData =  XmlDataToJson(xmlConf);
		std::string key = "equip";
		if (jsonData["reward"].isMember(key))
		{
			items[index].item = GiftEquipItem(jsonData["reward"][key], false);
		}

		/////////////////////////////////////////////////////
		++index;
	}
	return 0;
}

int DataXmlChristmasUint::Parse(CMarkupSTL& xmlConf
	, DataXMLChristmasEggItem items[DataXMLChristmasEgg::ITEMS_CNT])
{
	memset(items, 0, sizeof(DataXMLChristmasEggItem)*DataXMLChristmasEgg::ITEMS_CNT);
	int index = 0;
	while(xmlConf.FindElem("item")
			&& index < DataXMLChristmasEgg::ITEMS_CNT)
	{
		items[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		items[index].rate = CTrans::STOI(xmlConf.GetAttrib("rate"));
		std::string szShow = xmlConf.GetAttrib("show");
		if (szShow.empty())
		{
			items[index].show = 0;
		}
		else
		{
			items[index].show = CTrans::STOI(szShow);
		}

		Json::Value jsonData =  XmlDataToJson(xmlConf);
		std::string key = "equip";
		if (jsonData["reward"].isMember(key))
		{
			items[index].item = GiftEquipItem(jsonData["reward"][key], false);
		}

		/////////////////////////////////////////////////////
		++index;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//积分换礼
int DataXmlPointExchangeUint::Parse(const std::string& fullCfg, DataXMLPointExchange* pData)
{
	memset(pData->items, 0, DataXMLPointExchange::ITEM_CNT*sizeof(DataXMLPointExchageRewardItem));

	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	IntoXmlNode(xmlConf, "rewards");

	int index = 0;
	while(xmlConf.FindElem("reward")
			&& index < DataXMLPointExchange::ITEM_CNT)
	{
		pData->items[index].require = CTrans::STOI(xmlConf.GetAttrib("require"));
		xmlConf.IntoElem();
		{
			if (! xmlConf.FindElem("item"))
			{
				error_log("point_exchange_reward_cfg_error. index: %d", index);
				throw std::runtime_error("point_exchange_reward_cfg_error");
			}

			Json::Value jsonData =  XmlDataToJson(xmlConf);
			int idxitems = 0;
			for (int i = 0; i < 10; ++i)
			{
				if (idxitems >= DataXMLPointExchageRewardItem::ITEM_CNT)
				{
					break;
				}
				std::string key = "equip" + Convert::IntToString(i + 1);
				if (jsonData["reward"].isMember(key))
				{
					pData->items[index].items[idxitems++]
						   = GiftEquipItem(jsonData["reward"][key], false);
				}
			}

			if (jsonData["reward"].isMember("hero")
					&& idxitems < DataXMLPointExchageRewardItem::ITEM_CNT - 1)
			{
				pData->items[index].items[idxitems++]
					 = GiftEquipItem(jsonData["reward"]["hero"], true);
			}

		}
		xmlConf.OutOfElem();

		/////////////////////////////////////////////////////
		++index;
	}
	xmlConf.OutOfElem();

	Parse(xmlConf, pData->cut_price);


	return 0;
}

int DataXmlPointExchangeUint::Parse(CMarkupSTL& xmlConf, DataXMLPointCutPrice& cut_price)
{
	//疯狂放价
	xmlConf.FindElem("cutprice");
	std::vector<std::string> vLvInt;
	std::string szLvInt  = xmlConf.GetAttrib("lvInt");
	String::Split(szLvInt, ',', vLvInt);
	if (vLvInt.size() != DataXMLPointCutPrice::LEVLE_CNT)
	{
		throw std::runtime_error("lvl_item_cnt_error");
	}

	for (int i = 0; i < DataXMLPointCutPrice::LEVLE_CNT; i++)
	{
		cut_price.lvlInt[i] = CTrans::STOI(vLvInt[i]);
	}
	xmlConf.IntoElem();
	int index = 0;
	while(xmlConf.FindElem("item")
			&& index < DataXMLPointCutPrice::ITEM_CNT)
	{
		cut_price.items[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		cut_price.items[index].item_id = CTrans::STOI(xmlConf.GetAttrib("itemId"));
		cut_price.items[index].price = CTrans::STOI(xmlConf.GetAttrib("price"));
		cut_price.items[index].needLv = CTrans::STOI(xmlConf.GetAttrib("needLv"));

		/////////////////////////////////////////////////////
		++index;
	}
	xmlConf.OutOfElem();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//建筑皮肤
int DataXmlBuildingSkinUnit::Parse(const std::string& fullCfg, DataXMLBuildingSkin* pData)
{
	memset(pData->buys, 0, DataXMLBuildingSkin::ITEM_CNT*sizeof(DataXMLBuildingSkinBuy));
	memset(pData->relets, 0, DataXMLBuildingSkin::ITEM_CNT*sizeof(DataXMLBuildingSkinRelet));

	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);

	IntoXmlNode(xmlConf, "mapskinxuzu");
	Parse(xmlConf, pData->relets);
	xmlConf.OutOfElem();

	IntoXmlNode(xmlConf, "mapskinbuy");
	Parse(xmlConf, pData->buys);
	xmlConf.OutOfElem();

	return 0;
}

int DataXmlBuildingSkinUnit::Parse(CMarkupSTL& xmlConf
		, DataXMLBuildingSkinBuy skinBuys[DataXMLBuildingSkin::ITEM_CNT])
{
	int index = 0;
	while(xmlConf.FindElem("item")
			&& index < DataXMLBuildingSkin::ITEM_CNT)
	{
		skinBuys[index].id =  CTrans::STOI(xmlConf.GetAttrib("id"));
		skinBuys[index].eqid = CTrans::STOI(xmlConf.GetAttrib("eqid"));
		skinBuys[index].cost = CTrans::STOI(xmlConf.GetAttrib("cost"));

		/////////////////////////////////////////////////////
		++index;
	}
	return 0;
}

int DataXmlBuildingSkinUnit::Parse(CMarkupSTL& xmlConf
		, DataXMLBuildingSkinRelet skinRelet[DataXMLBuildingSkin::ITEM_CNT])
{
	int index = 0;
	while(xmlConf.FindElem("type")
			&& index < DataXMLBuildingSkin::ITEM_CNT)
	{
		skinRelet[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		xmlConf.IntoElem();
		Parse(xmlConf, skinRelet[index].items);
		xmlConf.OutOfElem();
		/////////////////////////////////////////////////////
		++index;
	}
	return 0;
}

int DataXmlBuildingSkinUnit::Parse(CMarkupSTL& xmlConf
		, DataXMLBuildingSkinReletItem reletItems[DataXMLBuildingSkinRelet::ITEM_CNT])
{
	int index = 0;
	while(xmlConf.FindElem("item")
			&& index < DataXMLBuildingSkinRelet::ITEM_CNT)
	{
		reletItems[index].id =  CTrans::STOI(xmlConf.GetAttrib("id"));
		reletItems[index].time = CTrans::STOI(xmlConf.GetAttrib("time"));
		reletItems[index].cost = CTrans::STOI(xmlConf.GetAttrib("cost"));

		/////////////////////////////////////////////////////
		++index;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
int DataXmlTutorLoginUint::Parse(const std::string& fullCfg, DataXMLTutorLogin* pData)
{
	memset(pData->items, 0, sizeof(pData->items));

	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "tutorLogin");

	int index = 0;
	while(xmlConf.FindElem("reward")
			&& index < DataXMLTutorLogin::ITEM_CNT)
	{
		pData->items[index].id =  CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->items[index].day = CTrans::STOI(xmlConf.GetAttrib("day"));

		Json::Value json_data =  XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];

		pData->items[index].gold = json_reward["gold"].asInt();
		pData->items[index].prosper = json_reward["prosper"].asInt();
		for(int i = 0; i < DataXMLTutorLoginItem::RS_CNT; i++)
		{
			std::string key = "rs" + Convert::IntToString(i + 1);
			pData->items[index].rs[i] = json_reward[key].asInt();
		}

		int idxitems = 0;
		for (int i = 0; i < DataXMLTutorLoginItem::EUIP_CNT; ++i)
		{

			std::string key = "equip" + Convert::IntToString(i + 1);
			if (json_reward.isMember(key))
			{
				pData->items[index].equips[idxitems++]
					   = GiftEquipItem(json_reward[key], false);
			}
		}

		if (json_reward.isMember("hero")
				&& idxitems < DataXMLTutorLoginItem::EUIP_CNT - 1)
		{
			pData->items[index].equips[idxitems++]
				 = GiftEquipItem(json_reward["hero"], true);
		}
		/////////////////////////////////////////////////////
		++index;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
int DataXmlImperialGiftUnit::Parse(const std::string& fullCfg, DataXMLImperialGift* pData)
{
	memset(pData->items, 0, sizeof(pData->items));

	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "baye");

	int index = 0;
	while(xmlConf.FindElem("item")
			&& index < DataXMLImperialGift::ITEM_CNT)
	{
		pData->items[index].id =  CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->items[index].end = CTrans::STOI(xmlConf.GetAttrib("end"));
		pData->items[index].cost = CTrans::STOI(xmlConf.GetAttrib("cost"));
		/////////////////////////////////////////////////////

		Json::Value json_data =  XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];

		int idxitems = 0;
		for (int i = 0; i < DataXMLImperialGiftItem::EUIP_CNT; ++i)
		{

			std::string key = "equip" + Convert::IntToString(i + 1);
			if (json_reward.isMember(key))
			{
				pData->items[index].equips[idxitems++]
					   = GiftEquipItem(json_reward[key], false);
			}
		}

		if (json_reward.isMember("hero")
				&& idxitems < DataXMLImperialGiftItem::EUIP_CNT - 1)
		{
			pData->items[index].equips[idxitems++]
				 = GiftEquipItem(json_reward["hero"], true);
		}

		/////////////////////////////////////////////////////
		++index;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int DataXmlTimeLimitUpgradeUnit::Parse(const std::string& fullCfg, DataXMLTimeLimitUpgrade* pData)
{
	memset(pData->items, 0, sizeof(pData->items));

	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "activities");

	while(xmlConf.FindElem("activity"))
	{
		if (std::string("LevelGift") != xmlConf.GetAttrib("id"))
		{
			continue;
		}

		xmlConf.IntoElem();
		IntoXmlNode(xmlConf, "conditions");

		//
		int idx_reward = 0;
		while(xmlConf.FindElem("reward")
				&& idx_reward < DataXMLTimeLimitUpgrade::ITEM_CNT)
		{
			Json::Value json_data =  XmlDataToJson(xmlConf);
			Json::Value json_reward = json_data["reward"];

			pData->items[idx_reward].gold = json_reward["gold"].asUInt();

			int idxitems = 0;
			for (int i = 0; i < DataXMLTimeLimitUpgradeItem::EUIP_CNT; ++i)
			{
				std::string key = "equip" + Convert::IntToString(i + 1);
				if (json_reward.isMember(key))
				{
					pData->items[idx_reward].equips[idxitems++]
						   = GiftEquipItem(json_reward[key], false);
				}
			}
			/////////////////////////////////////////////////////
			++idx_reward;
		}

		xmlConf.OutOfElem();
		xmlConf.OutOfElem();

		break;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////
int DataXmlYearFortuneUnit::Parse(const std::string& fullCfg, DataXMLYearFortune* pData)
{
	memset(pData->libs, 0, sizeof(pData->libs));
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "ji_nian_na_fu");

	int index = 0;
	while(xmlConf.FindElem("lib")
		&& index < DataXMLYearFortune::LIB_CNT)
	{

		pData->libs[index].id =  CTrans::STOI(xmlConf.GetAttrib("id"));
		xmlConf.IntoElem();
		Parse(xmlConf, pData->libs[index].items);
		xmlConf.OutOfElem();
		/////////////////////////////////////////////////////
		++index;
	}

	return 0;
}

int DataXmlYearFortuneUnit::Parse(CMarkupSTL& xmlConf,
		DataXMLYearFortuneItem items[DataXMLYearFortuneLib::ITEM_CNT])
{
	int index = 0;
	while(xmlConf.FindElem("item")
		&& index < DataXMLYearFortuneLib::ITEM_CNT)
	{
		items[index].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		items[index].rate = CTrans::STOI(xmlConf.GetAttrib("rate"));
		Json::Value json_data =  XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];

		int idxitems = 0;
		for (int i = 0; i < DataXMLYearFortuneItem::EQUIP_CNT; ++i)
		{
			std::string key = "equip" + Convert::IntToString(i + 1);
			if (json_reward.isMember(key))
			{
				items[index].equips[idxitems++]
					   = GiftEquipItem(json_reward[key], false);
			}
		}
		/////////////////////////////////////////////////////
		++index;
	}

	return 0;
}

int DataXmlChongZhiZiXuanUnit::Parse(const std::string& fullCfg, DataXMLChongZhiZiXuan* pData)
{
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "chongzhizixuan");

	int pool = 0;
	while (xmlConf.FindElem("pool")) {
		xmlConf.IntoElem();
		int item = 0;
		while (xmlConf.FindElem("item")) {
			pData->pool[pool].item[item].id = CTrans::STOI(xmlConf.GetAttrib("id"));
			Json::Value json_data = XmlDataToJson(xmlConf);
			Json::Value json_reward = json_data["reward"];
			int reward = 0;
			for (int i = 0; i < CHONGZHIZIXUAN_REWARD_COUNT; ++i) {
				std::string key = "equip" + CTrans::ITOS(i + 1);
				if (json_reward.isMember(key)) {
					pData->pool[pool].item[item].reward[reward++] = GiftEquipItem(json_reward[key], false);
				}
			}
			if (++item >= CHONGZHIZIXUAN_ITEM_COUNT) {
				break;
			}
		}

		item = 0;
		while (xmlConf.FindElem("charge")) {
			pData->pool[pool].charge[item].id = CTrans::STOI(xmlConf.GetAttrib("id"));
			pData->pool[pool].charge[item].times = CTrans::STOI(xmlConf.GetAttrib("times"));
			pData->pool[pool].charge[item].require = CTrans::STOI(xmlConf.GetAttrib("require"));
			if (++item >= CHONGZHIZIXUAN_ITEM_COUNT) {
				break;
			}
		}

		xmlConf.OutOfElem();
		if (++pool > CHONGZHIZIXUAN_POOL_COUNT) {
			break;
		}
	}
	return 0;
}

int DataXMLBeautyUnit::Parse(const std::string& fullCfg, DataXMLBeauty* pData){
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "beautyActive");
	int num = 0;
	while (xmlConf.FindElem("item")) {
		pData->active[num].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->active[num].add = CTrans::STOI(xmlConf.GetAttrib("add"));
		pData->active[num].max = CTrans::STOI(xmlConf.GetAttrib("max"));
		if (++num >= XML_BEAUTY_ACTIVE_ITEM_COUNT) {
			break;
		}
	}
	xmlConf.OutOfElem();

	xmlConf.ResetMainPos();
	IntoXmlNode(xmlConf, "beautyReward");
	num = 0;
	while (xmlConf.FindElem("item")) {
		pData->reward[num].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->reward[num].require = CTrans::STOI(xmlConf.GetAttrib("require"));
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		for (int i = 0; i < XML_BEAUTY_REWARD_COUNT; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->reward[num].reward[reward++] = GiftEquipItem(json_reward[key], false);
			}
		}
		if (++num >= XML_BEAUTY_REWARD_ITEM_COUNT) {
			break;
		}
	}
	return 0;
}

int DataXMLInvestmentUnit::Parse(const std::string& fullCfg, DataXMLInvestment* pData) {
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	if (!xmlConf.FindElem("RechargeInvestment")) {
		throw std::runtime_error("RechargeInvestment not exists");
	}
	string rate = xmlConf.GetAttrib("rate");
	string rate2 = xmlConf.GetAttrib("rate2");
	vector<string> arr;
	CBasic::StringSplitTrim(rate, ",", arr);
	for (int i = 0; i < arr.size() && i < XML_INVESTMENT_RATE_NUM; ++i) {
		pData->rate[i] = CTrans::STOF(arr[i]);
	}
	arr.clear();
	CBasic::StringSplitTrim(rate2, ",", arr);
	for (int i = 0; i < arr.size() && i < XML_INVESTMENT_RATE_NUM; ++i) {
		pData->rate1[i] = CTrans::STOF(arr[i]);
	}
	xmlConf.IntoElem();
	int num = 0;
	while (xmlConf.FindElem("item")) {
		pData->item[num].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->item[num].require = CTrans::STOI(xmlConf.GetAttrib("require"));
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		for (int i = 0; i < XML_BEAUTY_REWARD_COUNT; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->item[num].reward[reward++] = GiftEquipItem(json_reward[key], false);
			}
		}
		if (++num >= XML_INVESTMENT_REWARD_NUM) {
			break;
		}
	}
	return 0;
}

int DataXMLBirdBridgeUnit::Parse(const std::string& fullCfg, DataXMLBirdBridge* pData) {
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "birdBridge");
	IntoXmlNode(xmlConf, "left");
	int num = 0;
	while (xmlConf.FindElem("item")) {
		pData->left[num].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->left[num].require = CTrans::STOI(xmlConf.GetAttrib("require"));
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		for (int i = 0; i < XML_BIRD_BRIDGE_REWARD_NUM; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->left[num].reward[reward++] = GiftEquipItem(json_reward[key], false);
			}
		}
		if (++num >= XML_BIRD_BRIDGE_ITEM_NUM) {
			break;
		}
	}
	xmlConf.OutOfElem();
	IntoXmlNode(xmlConf, "rigth");
	num = 0;
	while (xmlConf.FindElem("item")) {
		pData->right[num].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		pData->right[num].require = CTrans::STOI(xmlConf.GetAttrib("require"));
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		for (int i = 0; i < XML_BIRD_BRIDGE_REWARD_NUM; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->right[num].reward[reward++] = GiftEquipItem(json_reward[key], false);
			}
		}
		if (++num >= XML_BIRD_BRIDGE_ITEM_NUM) {
			break;
		}
	}
	xmlConf.OutOfElem();
	if (!xmlConf.FindElem("center")) {
		return R_ERR_DATA;
	}
	pData->center.id = CTrans::STOI(xmlConf.GetAttrib("id"));
	pData->center.require = CTrans::STOI(xmlConf.GetAttrib("require"));
	Json::Value json_data = XmlDataToJson(xmlConf);
	Json::Value json_reward = json_data["reward"];
	int reward = 0;
	for (int i = 0; i < XML_BIRD_BRIDGE_REWARD_NUM; ++i) {
		std::string key = "equip" + CTrans::ITOS(i + 1);
		if (json_reward.isMember(key)) {
			pData->center.reward[reward++] = GiftEquipItem(json_reward[key], false);
		}
	}
	return 0;
}

int DataXMLUnionTechUnit::Parse(const std::string& fullCfg, DataXMLUnionTech* pData) {
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "techs");
	int num = 0;
	while (xmlConf.FindElem("tech")) {
		pData->tech[num].id = CTrans::STOI(xmlConf.GetAttrib("id"));
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_studypoint = json_data["studypoint"];
		for (int i=0;i<json_studypoint.size();i++)
			pData->tech[num].studypoint[i] = json_studypoint[i].asUInt();
		Json::Value json_gold = json_data["gold"];
		for (int i=0;i<json_gold.size();i++)
			pData->tech[num].gold[i] = json_gold[i].asUInt();
		Json::Value json_wood = json_data["wood"];
		for (int i=0;i<json_wood.size();i++)
			pData->tech[num].wood[i] = json_wood[i].asUInt();
		Json::Value json_eqpoint = json_data["eqpoint"];
		for (int i=0;i<json_eqpoint.size();i++)
			pData->tech[num].eqpoint[i] = json_eqpoint[i].asUInt();
		if (++num >= XML_MAX_UNIONTECH_NUM) {
			break;
		}
	}
	return 0;
}

int DataXMLShengDanUnit::Parse(const std::string& fullCfg, DataXMLShengDan* pData) {
	CMarkupSTL xmlConf;
	PreHandleXmlCfg(xmlConf, fullCfg);
	IntoXmlNode(xmlConf, "christmas");
	if (!xmlConf.FindElem("day")) {
		throw std::runtime_error("day not exists");
	}
	Json::Value json_data = XmlDataToJson(xmlConf);
	Json::Value json_reward = json_data["reward"];
	int reward = 0;
	//	std::string key = "equip" + CTrans::ITOS(i + 1);
		std::string key = "equip1";
		if (json_reward.isMember(key)) {
			pData->day = GiftEquipItem(json_reward[key], false);
		}
	//vow
	if (!xmlConf.FindElem("vow")) {
		throw std::runtime_error("vow not exists");
	}
	string ratestring = xmlConf.GetAttrib("rate");
	vector<string> vecrate;
	CBasic::StringSplitTrim(ratestring, ",", vecrate);
	for (int i=0;i<XML_SHENGDAN_CHOUJIANG_RATE_NUM;i++)
		pData->rate[i] = CTrans::STOI(vecrate[i].c_str());
	xmlConf.IntoElem();
	int num = 0;
	while (xmlConf.FindElem("item")) {
		std::string id = xmlConf.GetAttrib("id");
		std::string require = xmlConf.GetAttrib("require");
		pData->vow[num].id = CTrans::STOI(id);
		pData->vow[num].require = CTrans::STOI(require);
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		bool first = true;
		for (int i = 0; i < XML_SHENGDAN_REWARD_NUM; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->vow[num].reward[i] = GiftEquipItem(json_reward[key], false);
			}
			else {
				if (first)
				{
					std::string hero = "hero";
					if (json_reward.isMember(hero)) {
						pData->vow[num].reward[i] = GiftEquipItem(json_reward[hero], true);
					}
				}
				first = false;
			}
		}
		if (++num >= XML_SHENGDAN_XUYUAN_DANGCI_NUM)
			break;
	}
	xmlConf.OutOfElem();
	//change
	if (!xmlConf.FindElem("change")) {
		throw std::runtime_error("change not exists");
	}
	xmlConf.IntoElem();
	num = 0;
	while (xmlConf.FindElem("item")) {
		std::string id = xmlConf.GetAttrib("id");
		std::string require = xmlConf.GetAttrib("require");
		pData->change[num].id = CTrans::STOI(id);
		pData->change[num].require = CTrans::STOI(require);
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		for (int i = 0; i < XML_SHENGDAN_REWARD_NUM; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->change[num].reward[i] = GiftEquipItem(json_reward[key], false);
			}
		}
		if (++num >= XML_SHENGDAN_CHARGE_DANGCI_NUM)
			break;
	}
	xmlConf.OutOfElem();
	//consume
	if (!xmlConf.FindElem("consume")) {
		throw std::runtime_error("consume not exists");
	}
	xmlConf.IntoElem();
	num = 0;
	while (xmlConf.FindElem("item")) {
		std::string id = xmlConf.GetAttrib("id");
		std::string require = xmlConf.GetAttrib("require");
		pData->consume[num].id = CTrans::STOI(id);
		pData->consume[num].require = CTrans::STOI(require);
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		for (int i = 0; i < XML_SHENGDAN_REWARD_NUM; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->consume[num].reward[i] = GiftEquipItem(json_reward[key], false);
			}
		}
		if (++num >= XML_SHENGDAN_CONSUME_DANGCI_NUM)
			break;
	}
	xmlConf.OutOfElem();
	//exchange
	if (!xmlConf.FindElem("exchange")) {
		throw std::runtime_error("exchange not exists");
	}
	xmlConf.IntoElem();
	num = 0;
	while (xmlConf.FindElem("item")) {
		std::string id = xmlConf.GetAttrib("id");
		std::string count = xmlConf.GetAttrib("count");
		std::string require = xmlConf.GetAttrib("require");
		pData->exchange[num].id = CTrans::STOI(id);
		pData->exchange[num].require = CTrans::STOI(require);
		pData->exchange[num].count = CTrans::STOI(count);
		Json::Value json_data = XmlDataToJson(xmlConf);
		Json::Value json_reward = json_data["reward"];
		int reward = 0;
		for (int i = 0; i < XML_SHENGDAN_REWARD_NUM; ++i) {
			std::string key = "equip" + CTrans::ITOS(i + 1);
			if (json_reward.isMember(key)) {
				pData->exchange[num].reward[i] = GiftEquipItem(json_reward[key], false);
			}
		}
		if (++num >= XML_SHENGDAN_EXANGE_DANGCI_NUM)
			break;
	}
	xmlConf.OutOfElem();
	return 0;
}
