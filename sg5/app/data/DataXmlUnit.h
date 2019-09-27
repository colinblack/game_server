/*
 * DataXmlUnit.h
 *
 *  Created on: 2016-8-5
 *      Author: dawx62fac
 */

#ifndef DATAXMLUNIT_H_
#define DATAXMLUNIT_H_


#include "DataXmlPraseWrap.h"
#include "DataXML.h"

////////////////////////////////////////////////////////////////////////
//天坛祈福
class DataXMLTemplePray : public DataXmlParseWrap<DataXMLTemple>
{
public:
	DataXMLTemplePray(CShareMemory& sh, const std::string& cfg)
	 : DataXmlParseWrap<DataXMLTemple>(sh, cfg)
	{

	}

protected:
	int Parse(const std::string& fullCfg, DataXMLTemple* pData);
};


/////////////////////////////////////////////////////////////////////////
//开区充值大礼包
class DataXmlNewRechargeBagUnit : public DataXmlParseWrap<DataXMLNewRecharge>
{
public:
	DataXmlNewRechargeBagUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLNewRecharge>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLNewRecharge* pData);
};

//////////////////////////////////////////////////////////////////////////
//每日团购
class DataXmlGroupBuyDailyUnit : public DataXmlParseWrap<DataXMLGroupBuyDaily>
{
public:
	DataXmlGroupBuyDailyUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLGroupBuyDaily>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLGroupBuyDaily* pData);
};

//////////////////////////////////////////////////////////////////////////
//月度礼包
class DataXmlMonthGiftBagUnit : public DataXmlParseWrap<DataXMLMonthGiftBag>
{
public:
	DataXmlMonthGiftBagUnit(CShareMemory& sh, const std::string& cfg)
			: DataXmlParseWrap<DataXMLMonthGiftBag>(sh, cfg)
	{

	}

protected:
	int Parse(const std::string& fullCfg, DataXMLMonthGiftBag* pData);

	void ParseZoneReward(CMarkupSTL& xmlConf, DataXMLMonthGiftBagZone& zone);
};

//////////////////////////////////////////////////////////////////////////
//充点小钱
class DataXmlLittleRechargeUnit : public DataXmlParseWrap<DataXMLLittleRecharge>
{
public:
	DataXmlLittleRechargeUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLLittleRecharge>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLLittleRecharge* pData);

	void ParseZoneReward(CMarkupSTL& xmlConf
			, DataXMLLittleRechargeZone zone[DataXMLLittleRecharge::ZONE_CNT]);
};

//////////////////////////////////////////////////////////////////////////
//组合商店
class DataXmlCombinedShopUnit : public DataXmlParseWrap<DataXMLCombinedShop>
{
public:
	DataXmlCombinedShopUnit(CShareMemory& sh, const std::string& cfg)
			: DataXmlParseWrap<DataXMLCombinedShop>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLCombinedShop* pData);

	void ParseItemCfg(CMarkupSTL& xmlConf, DataXMLCombinedShopItem& item);
};

//////////////////////////////////////////////////////////////////////////
//预告功能
class DataXmlNewerAdvanceUnit : public DataXmlParseWrap<DataXMLNewerAdvance>
{
public:
	DataXmlNewerAdvanceUnit(CShareMemory& sh, const std::string& cfg)
			: DataXmlParseWrap<DataXMLNewerAdvance>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLNewerAdvance* pData);
};

//////////////////////////////////////////////////////////////////////////
//步步为营
class DataXmlTreasureHuntUnit : public DataXmlParseWrap<DataXMLTreasureHuntExchange>
{
public:
	DataXmlTreasureHuntUnit(CShareMemory& sh, const std::string& cfg)
			: DataXmlParseWrap<DataXMLTreasureHuntExchange>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLTreasureHuntExchange* pData);
	int Parse(CMarkupSTL& xmlConf
			, DataXMLTreasureHuntExchangeItem items[DataXMLTreasureHuntExchange::ITEMS_CNT]);
};

//////////////////////////////////////////////////////////////////////////
//圣诞活动
class DataXmlChristmasUint : public DataXmlParseWrap<DataXMLChristmas>
{
public:
	DataXmlChristmasUint(CShareMemory& sh, const std::string& cfg)
				: DataXmlParseWrap<DataXMLChristmas>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLChristmas* pData);
	int Parse(CMarkupSTL& xmlConf
			, DataXMLChristmasExtraItem items[DataXMLChristmas::EXTRA_ITEMS]);
	int Parse(CMarkupSTL& xmlConf
			, DataXMLChristmasEggItem egg[DataXMLChristmasEgg::ITEMS_CNT]);
};

//////////////////////////////////////////////////////////////////////////
//积分换礼
class DataXmlPointExchangeUint : public DataXmlParseWrap<DataXMLPointExchange>
{
public:
	DataXmlPointExchangeUint(CShareMemory& sh, const std::string& cfg)
				: DataXmlParseWrap<DataXMLPointExchange>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLPointExchange* pData);
	int Parse(CMarkupSTL& xmlConf, DataXMLPointCutPrice& cut_price);
};

//////////////////////////////////////////////////////////////////////////
//建筑皮肤
class DataXmlBuildingSkinUnit : public DataXmlParseWrap<DataXMLBuildingSkin>
{
public:
	DataXmlBuildingSkinUnit(CShareMemory& sh, const std::string& cfg)
				: DataXmlParseWrap<DataXMLBuildingSkin>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLBuildingSkin* pData);
	int Parse(CMarkupSTL& xmlConf
			, DataXMLBuildingSkinBuy skinBuys[DataXMLBuildingSkin::ITEM_CNT]);
	int Parse(CMarkupSTL& xmlConf
			, DataXMLBuildingSkinRelet skinRelet[DataXMLBuildingSkin::ITEM_CNT]);
	int Parse(CMarkupSTL& xmlConf
			, DataXMLBuildingSkinReletItem reletItems[DataXMLBuildingSkinRelet::ITEM_CNT]);

};

//////////////////////////////////////////////////////////////////////////
//7日登录
class DataXmlTutorLoginUint : public DataXmlParseWrap<DataXMLTutorLogin>
{
public:
	DataXmlTutorLoginUint(CShareMemory& sh, const std::string& cfg)
				: DataXmlParseWrap<DataXMLTutorLogin>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLTutorLogin* pData);
};

//////////////////////////////////////////////////////////////////////////
//霸业礼包
class DataXmlImperialGiftUnit : public DataXmlParseWrap<DataXMLImperialGift>
{
public:
	DataXmlImperialGiftUnit(CShareMemory& sh, const std::string& cfg)
				: DataXmlParseWrap<DataXMLImperialGift>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLImperialGift* pData);
};

//////////////////////////////////////////////////////////////////////////
//限时冲级
class DataXmlTimeLimitUpgradeUnit : public DataXmlParseWrap<DataXMLTimeLimitUpgrade>
{
public:
	DataXmlTimeLimitUpgradeUnit(CShareMemory& sh, const std::string& cfg)
				: DataXmlParseWrap<DataXMLTimeLimitUpgrade>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLTimeLimitUpgrade* pData);
};

///////////////////////////////////////////////////////////////////////////
//鸡年纳福
class DataXmlYearFortuneUnit : public DataXmlParseWrap<DataXMLYearFortune>
{
public:
	DataXmlYearFortuneUnit(CShareMemory& sh, const std::string& cfg)
				: DataXmlParseWrap<DataXMLYearFortune>(sh, cfg)
	{

	}
protected:
	int Parse(const std::string& fullCfg, DataXMLYearFortune* pData);
	int Parse(CMarkupSTL& xmlConf,
			DataXMLYearFortuneItem items[DataXMLYearFortuneLib::ITEM_CNT]);
};

///////////////////////////////////////////////////////////////////////////
class DataXmlChongZhiZiXuanUnit : public DataXmlParseWrap<DataXMLChongZhiZiXuan>
{
public:
	DataXmlChongZhiZiXuanUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLChongZhiZiXuan>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLChongZhiZiXuan* pData);
};

///////////////////////////////////////////////////////////////////////////
class DataXMLBeautyUnit : public DataXmlParseWrap<DataXMLBeauty>
{
public:
	DataXMLBeautyUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLBeauty>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLBeauty* pData);
};

///////////////////////////////////////////////////////////////////////////
class DataXMLInvestmentUnit : public DataXmlParseWrap<DataXMLInvestment>
{
public:
	DataXMLInvestmentUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLInvestment>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLInvestment* pData);
};

///////////////////////////////////////////////////////////////////////////
class DataXMLBirdBridgeUnit : public DataXmlParseWrap<DataXMLBirdBridge>
{
public:
	DataXMLBirdBridgeUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLBirdBridge>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLBirdBridge* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLUnionTechUnit : public DataXmlParseWrap<DataXMLUnionTech>
{
public:
	DataXMLUnionTechUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLUnionTech>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLUnionTech* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLShengDanUnit : public DataXmlParseWrap<DataXMLShengDan>
{
public:
	DataXMLShengDanUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLShengDan>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLShengDan* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLXiaoNianUnit : public DataXmlParseWrap<DataXMLXiaoNian>
{
public:
	DataXMLXiaoNianUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLXiaoNian>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLXiaoNian* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLQingRenJieMeiGuiUnit : public DataXmlParseWrap<DataXMLQingRenJieMeiGui>
{
public:
	DataXMLQingRenJieMeiGuiUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLQingRenJieMeiGui>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLQingRenJieMeiGui* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLNianShouBossUnit : public DataXmlParseWrap<DataXMLNianShouBoss>
{
public:
	DataXMLNianShouBossUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLNianShouBoss>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLNianShouBoss* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLXianShiMuBiaoUnit : public DataXmlParseWrap<DataXMLXianShiMuBiao>
{
public:
	DataXMLXianShiMuBiaoUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLXianShiMuBiao>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLXianShiMuBiao* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLZhouNianQingUnit : public DataXmlParseWrap<DataXMLZhouNianQing>
{
public:
	DataXMLZhouNianQingUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLZhouNianQing>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLZhouNianQing* pData);
};
///////////////////////////////////////////////////////////////////////////
class DataXMLQingMingUnit : public DataXmlParseWrap<DataXMLQingMing>
{
public:
	DataXMLQingMingUnit(CShareMemory& sh, const std::string& cfg)
		: DataXmlParseWrap<DataXMLQingMing>(sh, cfg) {
	}
protected:
	int Parse(const std::string& fullCfg, DataXMLQingMing* pData);
};
///////////////////////////////////////////////////////////////////////////
#endif /* DATAXMLUNIT_H_ */
