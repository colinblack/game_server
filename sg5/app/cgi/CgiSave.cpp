/*
 * CgiSave.cpp
 *
 *  Created on: 2011-6-1
 *      Author: dada
 */

#include "LogicInc.h"
#include "LogicCMD.h"
#include "../platform/TencentPlatform.h"

/**
 * FUNC_NAME 	--执行函数的名称
 * PARAMS	 	--对应的参数类
 * ACTION_UNIT 	--该业务逻辑对应的BaseCmdUnit类
 * IS_BASE		--true,false是否只读取用户的基本信息
 * IMPL			--BaseCmdUnit中对应处理该业务的执行函数
 */
#define CGI_ACTION_FUNCTION(FUNC_NAME, PARAMS, ACTION_UNIT, IS_BASE, IMPL)  \
int FUNC_NAME()											  					\
{																			\
	try 																	\
	{ 																		\
		PARAMS args(m_data);												\
		int ret = LogicCmdAction<ACTION_UNIT>( 								\
				  m_uid   													\
				, IS_BASE 													\
				, args  													\
				, reinterpret_cast<ActionImpl>(&ACTION_UNIT::IMPL)	 		\
				, m_jsonResult); 											\
		if (R_SUCCESS != ret) 												\
		{																	\
			return ret; 													\
		} 																	\
																			\
		CGI_SEND_LOG("action=%s&uid=%u", #FUNC_NAME, m_uid); 				\
		return R_SUCCESS; 													\
	}  																		\
	catch (const std::exception& e) 										\
	{ 																		\
		::SetError(R_ERROR, e.what()); 										\
		return R_ERROR; 													\
	} 																		\
																			\
	return R_ERROR;															\
}


class CCgiSave : public CCgiBase
{

public:

	CCgiSave() : CCgiBase("save")
	{
		SetFeature(CF_PRINT_JSON);
		SetFeature(CF_GET_REMOTE_IP);
		SetFeature(CF_GET_UID);
		SetFeature(CF_CHECK_SESSION);
		SetFeature(CF_CHECK_TIME);
		SetFeature(CF_CHECK_PLATFORM);
		SetFeature(CF_CHECK_HASH);
		SetFeature(CF_CHECK_VERSION);
		SetFeature(CF_APPEND_HASH);
		SetFeature(CF_PARSE_DATA);
		SetFeature(CF_CRYPT_DATA);
		SetFeature(CF_DECRYPT_DATA);
	}

	CGI_ACTION_DEFAULT_MAP_BEGIN(Save)
	CGI_SET_ACTION_DEFAULT_MAP("UpgradeBuilding", UpgradeBuilding)
	CGI_SET_ACTION_DEFAULT_MAP("FastUpgradeBuilding", FastUpgradeBuilding)
	CGI_SET_ACTION_DEFAULT_MAP("GMUpgradeBuilding", GMUpgradeBuilding)
	CGI_SET_ACTION_DEFAULT_MAP("GMAddExp", GMAddExp)
	CGI_SET_ACTION_DEFAULT_MAP("ExpMaxAdd", ExpMaxAdd)
	CGI_SET_ACTION_DEFAULT_MAP("refreshhero", RefreshHero)
	CGI_SET_ACTION_DEFAULT_MAP("UpgradeHero", UpgradeHero)
	CGI_SET_ACTION_DEFAULT_MAP("UpgradeHeroForActivity", UpgradeHeroForActivity)
	CGI_SET_ACTION_DEFAULT_MAP("GetUpgradeHeroForActivity", GetUpgradeHeroForActivity)
	CGI_SET_ACTION_DEFAULT_MAP("ChargeBackHappyCard", ChargeBackHappyCard)
	CGI_SET_ACTION_DEFAULT_MAP("CheckSave", CheckSave)
	CGI_SET_ACTION_DEFAULT_MAP("EquipSub", EquipSub)
	CGI_SET_ACTION_DEFAULT_MAP("EquipSubAct1", EquipSubAct1)
	CGI_SET_ACTION_DEFAULT_MAP("EquipSubAct2", EquipSubAct2)
	CGI_SET_ACTION_DEFAULT_MAP("OldUserGift", OldUserGift)
	CGI_SET_ACTION_DEFAULT_MAP("TreasureHunt", TreasureHunt)
	CGI_SET_ACTION_DEFAULT_MAP("usegiftbag", useGiftBag)
	CGI_SET_ACTION_DEFAULT_MAP("DigEquipSubStone", DigEquipSubStone)
	CGI_SET_ACTION_DEFAULT_MAP("newpayrankactivity", NewPayrankActivity)
	CGI_SET_ACTION_DEFAULT_MAP("buybet", BuyBet)
	CGI_SET_ACTION_DEFAULT_MAP("shop", Shop)
	CGI_SET_ACTION_DEFAULT_MAP("productShop", ProductShop)
	CGI_SET_ACTION_DEFAULT_MAP("fashionshop", FashionShop)
	CGI_SET_ACTION_DEFAULT_MAP("equipintensifys", EquipIntensifys)
	CGI_SET_ACTION_DEFAULT_MAP("syntheticgemback", SyntheticGemBack)
	CGI_SET_ACTION_DEFAULT_MAP("MeltOldSoulStone", MeltOldSoulStone)
	CGI_SET_ACTION_DEFAULT_MAP("SynNewSoulStone", SynNewSoulStone)
	CGI_SET_ACTION_DEFAULT_MAP("SynNewSoulStoneUp", SynNewSoulStoneUp)
	CGI_SET_ACTION_DEFAULT_MAP("hammerhit", HammerHit)
	CGI_SET_ACTION_DEFAULT_MAP("hammerHitAllServer", HammerHitAllServer)
	CGI_SET_ACTION_DEFAULT_MAP("HammerFreeGet", HammerFreeGet)
	CGI_SET_ACTION_DEFAULT_MAP("useship", UseShip)
	CGI_SET_ACTION_DEFAULT_MAP("refreshship", RefreshShip)
	CGI_SET_ACTION_DEFAULT_MAP("buildequipset", BuildEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("heropowerup", HeroPowerUp)
	CGI_SET_ACTION_DEFAULT_MAP("heropower2up", HeroPower2Up)
	CGI_SET_ACTION_DEFAULT_MAP("heropower3up", HeroPower3Up)
	CGI_SET_ACTION_DEFAULT_MAP("liandan", liandan)
	CGI_SET_ACTION_DEFAULT_MAP("keyao", keyao)
	CGI_SET_ACTION_DEFAULT_MAP("godh", godh)
	CGI_SET_ACTION_DEFAULT_MAP("herolearnhorse", HeroLearnHorse)
	CGI_SET_ACTION_DEFAULT_MAP("upgradehorse", UpgradeHorse)
	CGI_SET_ACTION_DEFAULT_MAP("elevatehorese", ElevateHorse)
	CGI_SET_ACTION_DEFAULT_MAP("upgradeequipset", UpgradeEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("refineequipset", RefineEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("ShenQiEquipSet", ShenQiEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("wuxingequipset", WuxingEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("blessequipset", BlessEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("ShenZhuEquipSet", ShenZhuEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("ShenWenEquipSet", ShenWenEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("ShenGeEquipSet", ShenGeEquipSet)
	CGI_SET_ACTION_DEFAULT_MAP("AddSoul", AddSoul)
	CGI_SET_ACTION_DEFAULT_MAP("qianghuadismantlingequip", QianghuaDismantlingEquipBack)
	CGI_SET_ACTION_DEFAULT_MAP("taozhuangdismantlingequip", TaozhuangDismantlingEquip)
	CGI_SET_ACTION_DEFAULT_MAP("newlottery", NewLottery)
	CGI_SET_ACTION_DEFAULT_MAP("Juexue", Juexue)
	CGI_SET_ACTION_DEFAULT_MAP("juexueoneKeyfulllevel", JueXueOneKeyFullLevel)
	CGI_SET_ACTION_DEFAULT_MAP("qixichoujiang", QixiChoujiang)
	CGI_SET_ACTION_DEFAULT_MAP("jianglingchengzhang", JianglingChengzhang)
	CGI_SET_ACTION_DEFAULT_MAP("jianglingskill", JianglingSkill)
	CGI_SET_ACTION_DEFAULT_MAP("ChangeName", ChangeName)
	CGI_SET_ACTION_DEFAULT_MAP("ChangeNameAfterFirst", ChangeNameAfterFirst)
	CGI_SET_ACTION_DEFAULT_MAP("SJ4399", SJ4399)
	CGI_SET_ACTION_DEFAULT_MAP("XSK4399", XSK4399)
	CGI_SET_ACTION_DEFAULT_MAP("XSKBaidu", XSKBaidu)
	CGI_SET_ACTION_DEFAULT_MAP("CreditShop", CreditShop)
	CGI_SET_ACTION_DEFAULT_MAP("DragonScaleActive", DragonScaleActivity)
	CGI_SET_ACTION_DEFAULT_MAP("DragonScaleTensActive", DragonScaleTensActivity)
	CGI_SET_ACTION_DEFAULT_MAP("DragonScaleAllFree", DragonScaleAllFree)
	CGI_SET_ACTION_DEFAULT_MAP("TouchGold", TouchGold)
	CGI_SET_ACTION_DEFAULT_MAP("HappyCard", HappyCard)
	CGI_SET_ACTION_DEFAULT_MAP("ProtectToken", ProtectToken)
	CGI_SET_ACTION_DEFAULT_MAP("Poker21", Poker21)
	CGI_SET_ACTION_DEFAULT_MAP("HeavenDaoist", HeavenDaoist)
	CGI_SET_ACTION_DEFAULT_MAP("Catapult", Catapult)
	CGI_SET_ACTION_DEFAULT_MAP("CatapultSkill", CatapultSkillUp)
	CGI_SET_ACTION_DEFAULT_MAP("EightFormation", EightFormation)
	CGI_SET_ACTION_DEFAULT_MAP("R5", R5)
	CGI_SET_ACTION_DEFAULT_MAP("MultipleWheel", MultipleWheel)
	CGI_SET_ACTION_DEFAULT_MAP("UpgradeGem", UpgradeGem)
	CGI_SET_ACTION_DEFAULT_MAP("UpgradeTenWeapon", UpgradeTenWeapon)
	CGI_SET_ACTION_DEFAULT_MAP("MergeEquipment", MergeEquipment)
	CGI_SET_ACTION_DEFAULT_MAP("Double11", Double11)
	CGI_SET_ACTION_DEFAULT_MAP("GetDouble11Rcnt", GetDouble11Rcnt)
	CGI_SET_ACTION_DEFAULT_MAP("Sell", Sell)
	CGI_SET_ACTION_DEFAULT_MAP("SellJuexue", SellJuexue)
	CGI_SET_ACTION_DEFAULT_MAP("CollectJuexue", CollectJuexue)
	CGI_SET_ACTION_DEFAULT_MAP("SynthJuexue", SynthJuexue)
	CGI_SET_ACTION_DEFAULT_MAP("LoadJuexue", LoadJuexue)
	CGI_SET_ACTION_DEFAULT_MAP("LoadSynth", LoadSynth)
	CGI_SET_ACTION_DEFAULT_MAP("HitEgg", HitEgg)
	CGI_SET_ACTION_DEFAULT_MAP("RefreshHitEgg", RefreshHitEgg)
	CGI_SET_ACTION_DEFAULT_MAP("BetShop", BetShop)
	CGI_SET_ACTION_DEFAULT_MAP("GetMedal", GetMedal)
	CGI_SET_ACTION_DEFAULT_MAP("GetWorldReward", GetWorldReward)
	//CGI_SET_ACTION_DEFAULT_MAP("GetKillReward", GetKillReward)
	CGI_SET_ACTION_DEFAULT_MAP("BuyQiRi", BuyQiRi)
	CGI_SET_ACTION_DEFAULT_MAP("GetQiRi", GetQiRi)
	CGI_SET_ACTION_DEFAULT_MAP("GetGiftBagLvl", GetGiftBagLvl)
	CGI_SET_ACTION_DEFAULT_MAP("GetGiftBagVip", GetGiftBagVip)
	CGI_SET_ACTION_DEFAULT_MAP("FirstRechargeReward", FirstRechargeReward)
	CGI_SET_ACTION_DEFAULT_MAP("SignInReward", SignInReward)
    CGI_SET_ACTION_DEFAULT_MAP("GetInviteReward", GetInviteReward)
    CGI_SET_ACTION_DEFAULT_MAP("DailyQuestReward", DailyQuestReward)
    CGI_SET_ACTION_DEFAULT_MAP("VipGiftBag", VipGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("GrowthFund", GrowthFund)
    CGI_SET_ACTION_DEFAULT_MAP("IntensifyWeaponBySoul", IntensifyWeaponBySoul)
    CGI_SET_ACTION_DEFAULT_MAP("RechargeGiftBag", RechargeGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("tencentpcmanager", TencentPCManager)
    CGI_SET_ACTION_DEFAULT_MAP("RecruitHero", RecruitHero)
    CGI_SET_ACTION_DEFAULT_MAP("DeDaoZhenRen", DeDaoZhenRen)
    CGI_SET_ACTION_DEFAULT_MAP("QQPanelGiftBag", QQPanelGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("YellowDiamondNewUserGiftBag", YellowDiamondNewUserGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("YellowDiamondDailyGiftBag", YellowDiamondDailyGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("BlueDiamondNewUserGiftBag", BlueDiamondNewUserGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("BlueDiamondDailyGiftBag", BlueDiamondDailyGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("BlueDiamondLevelGiftBag", BlueDiamondLevelGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("PreSummerExchange", PreSummerExchange)
    CGI_SET_ACTION_DEFAULT_MAP("PreSummerCurPoint", PreSummerCurPoint)
    CGI_SET_ACTION_DEFAULT_MAP("NewJueshiWuShuang", NewJueshiWuShuang)
    CGI_SET_ACTION_DEFAULT_MAP("feedToken", FeedToken)
    CGI_SET_ACTION_DEFAULT_MAP("LordWorship", LordWorship)
    CGI_SET_ACTION_DEFAULT_MAP("opporknock", OpporKnock)
    CGI_SET_ACTION_DEFAULT_MAP("CheckInitial", CheckInitial)
    CGI_SET_ACTION_DEFAULT_MAP("RefreshLuckWheel", RefreshLuckWheel)
    CGI_SET_ACTION_DEFAULT_MAP("FortuLottery", FortuLottery)
    CGI_SET_ACTION_DEFAULT_MAP("CheckPlateInitial", CheckTurnPlateInitial)
    CGI_SET_ACTION_DEFAULT_MAP("RefreshTurnPlaeWheel", RefreshTurnPlaeWheel)
    CGI_SET_ACTION_DEFAULT_MAP("TurnPlateLotty", TurnPlateLotty)
    CGI_SET_ACTION_DEFAULT_MAP("RechargeOptional", RechargeOptional)
    CGI_SET_ACTION_DEFAULT_MAP("RechargeSendUpgrade", RechargeSendUpgrade)
    CGI_SET_ACTION_DEFAULT_MAP("NewRechargeBag", NewRechargeBag)
    CGI_SET_ACTION_DEFAULT_MAP("GroupBuyDaily", GroupBuyDaily)
    CGI_SET_ACTION_DEFAULT_MAP("GroupBuyReward", GroupBuyReward)
    CGI_SET_ACTION_DEFAULT_MAP("TemplePray", TemplePray)
    CGI_SET_ACTION_DEFAULT_MAP("LittleRecharge", LittleRecharge)
    CGI_SET_ACTION_DEFAULT_MAP("DailyRewardGC", DailyRewardGC)
    CGI_SET_ACTION_DEFAULT_MAP("MonthGiftBag", MonthGiftBag)
    CGI_SET_ACTION_DEFAULT_MAP("SelectKingdom", SelectKingdom)
    CGI_SET_ACTION_DEFAULT_MAP("CombinedShopBuy", CombinedShopBuy)
    CGI_SET_ACTION_DEFAULT_MAP("NewerAdvanceGet", NewerAdvanceGet)
    CGI_SET_ACTION_DEFAULT_MAP("AthleticsReward", AthleticsReward)
    CGI_SET_ACTION_DEFAULT_MAP("startherotrain", StartHeroTrain)
    CGI_SET_ACTION_DEFAULT_MAP("improvetrain", ImproveTrain)
    CGI_SET_ACTION_DEFAULT_MAP("endherotrain", EndHeroTrain)
    CGI_SET_ACTION_DEFAULT_MAP("startsoldiertrain", StartSoldierTrain)
    CGI_SET_ACTION_DEFAULT_MAP("endsoldiertrain", EndSoldierTrain)
    CGI_SET_ACTION_DEFAULT_MAP("startsoldierresearch", StartSoldierResearch)
    CGI_SET_ACTION_DEFAULT_MAP("cancelsoldierresearch", CancelSoldierResearch)
    CGI_SET_ACTION_DEFAULT_MAP("endsoldierresearch", EndSoldierResearch)
    CGI_SET_ACTION_DEFAULT_MAP("synthsoldierskill", SynthSoldierSkill)
	CGI_SET_ACTION_DEFAULT_MAP("SynthKingdomWar", SynthKingdomWar)
    CGI_SET_ACTION_DEFAULT_MAP("innateskillup", InnateSkillUp)
    CGI_SET_ACTION_DEFAULT_MAP("StartskillTrain", StartSkillTrain)
    CGI_SET_ACTION_DEFAULT_MAP("EndskillTrain", EndSkillTrain)
    CGI_SET_ACTION_DEFAULT_MAP("HeavendaoSkillup", HeavendaoSkillup)
    CGI_SET_ACTION_DEFAULT_MAP("CalcuteFairybag", CalcuteFairybag)
    CGI_SET_ACTION_DEFAULT_MAP("ReceiveFairyReward", ReceiveFairyReward)
    CGI_SET_ACTION_DEFAULT_MAP("houhuiyouqi", HouHuiYouQi)
    CGI_SET_ACTION_DEFAULT_MAP("bigharvestrc", BigHarvestRewardCoins)
    CGI_SET_ACTION_DEFAULT_MAP("moneytreerc",  MoneyTreeRewardCoins)
    CGI_SET_ACTION_DEFAULT_MAP("chaozhizhekou", ChaoZhiZheKou)
    CGI_SET_ACTION_DEFAULT_MAP("yuehuijuxian",  YueHuiJuXian)
    CGI_SET_ACTION_DEFAULT_MAP("limitbuyofzone",  LimitBuyOfZone)
    CGI_SET_ACTION_DEFAULT_MAP("fivedefendgrow",  FiveDefendGrow)
    CGI_SET_ACTION_DEFAULT_MAP("fiveattackgrow",  FiveAttackGrow)
    CGI_SET_ACTION_DEFAULT_MAP("fiveattackactivity",  FiveAttackActivity)
    CGI_SET_ACTION_DEFAULT_MAP("resetcountrydayshop",  ResetCountryDayShop)
    CGI_SET_ACTION_DEFAULT_MAP("countrydaylogin",  CountryDayLogin)
    CGI_SET_ACTION_DEFAULT_MAP("countrydayshop",  CountryDayShop)
    CGI_SET_ACTION_DEFAULT_MAP("countrydaybag",  CountryDayBag)
    CGI_SET_ACTION_DEFAULT_MAP("heartbeatbigsale",  HeartbeatBigSale)
    CGI_SET_ACTION_DEFAULT_MAP("heartbeatbigsalereset",  HeartbeatBigSaleReset)
    CGI_SET_ACTION_DEFAULT_MAP("fivebigsaleshop",  FiveBigSaleShop)
    CGI_SET_ACTION_DEFAULT_MAP("fivecouponshop",  FiveCouponShop)
    CGI_SET_ACTION_DEFAULT_MAP("fiveshopreset",  FiveShopReset)
    CGI_SET_ACTION_DEFAULT_MAP("ChongZhiHuiKui",  ChongZhiHuiKui)
    CGI_SET_ACTION_DEFAULT_MAP("JinQiuShiYue",  JinQiuShiYue)
    CGI_SET_ACTION_DEFAULT_MAP("ZhiZunBaoXiang",  ZhiZunBaoXiang)
    CGI_SET_ACTION_DEFAULT_MAP("juexingtehui",  JueXingTeHui)
    CGI_SET_ACTION_DEFAULT_MAP("juexingtehuireset",  JueXingTeHuiReset)
    CGI_SET_ACTION_DEFAULT_MAP("fudai",  FuDai)
    CGI_SET_ACTION_DEFAULT_MAP("freeexchange",  FreeExchange)
    CGI_SET_ACTION_DEFAULT_MAP("freeexchangereset",  FreeExchangeReset)
    CGI_SET_ACTION_DEFAULT_MAP("JiFenDuiHuan",  JiFenDuiHuan)
    CGI_SET_ACTION_DEFAULT_MAP("doubleeleven",  DoubleEleven)
    CGI_SET_ACTION_DEFAULT_MAP("doubleelevenreset",  DoubleElevenReset)
    CGI_SET_ACTION_DEFAULT_MAP("jubaoxiagetkey",  JuBaoXiaGetKey)
    CGI_SET_ACTION_DEFAULT_MAP("jubaoxiagettreasure",  JuBaoXiaGetTreasure)
    CGI_SET_ACTION_DEFAULT_MAP("jubaoxiagettreasureonekey",  JuBaoXiaGetTreasureOneKey)
    CGI_SET_ACTION_DEFAULT_MAP("jubaoxiareset",  JuBaoXiaReset)
    CGI_SET_ACTION_DEFAULT_MAP("heavenstep",  HeavenStep)
    CGI_SET_ACTION_DEFAULT_MAP("daoiststep",  DaoistStep)
    CGI_SET_ACTION_DEFAULT_MAP("zhenbaogehero",  ZhenBaoGeHero)
    CGI_SET_ACTION_DEFAULT_MAP("zhenbaogebuilding",  ZhenBaoGeBuilding)
    CGI_SET_ACTION_DEFAULT_MAP("GetPartStone",  GetPartStone)
    CGI_SET_ACTION_DEFAULT_MAP("herostonestep",  HeroStoneStep)
    CGI_SET_ACTION_DEFAULT_MAP("buildingstonestep",  BuildingStoneStep)
    CGI_SET_ACTION_DEFAULT_MAP("ProcessTribute",  ProcessTribute)
    CGI_SET_ACTION_DEFAULT_MAP("jinqiunovember",  JinQiuNovember)
    CGI_SET_ACTION_DEFAULT_MAP("acchargebackshenwen",  AcchargeBackShenwen)
    CGI_SET_ACTION_DEFAULT_MAP("MeltEquip",  MeltEquip)
    CGI_SET_ACTION_DEFAULT_MAP("herogrowstep",  HeroGrowStep)
    CGI_SET_ACTION_DEFAULT_MAP("growdevelopget",  GrowDevelopGet)
    CGI_SET_ACTION_DEFAULT_MAP("TreasureHuntExchange",  TreasureHuntExchange)
    CGI_SET_ACTION_DEFAULT_MAP("DailyChargeCoin",  DailyChargeCoin)
    CGI_SET_ACTION_DEFAULT_MAP("CheckTreasureVer",  CheckTreasureVer)
    CGI_SET_ACTION_DEFAULT_MAP("RefreshTreasure",  RefreshTreasure)
    CGI_SET_ACTION_DEFAULT_MAP("LotteryTreasure",  LotteryTreasure)
    CGI_SET_ACTION_DEFAULT_MAP("LotteryMultiTreasure",  LotteryMultiTreasure)
    CGI_SET_ACTION_DEFAULT_MAP("ChristmasExchange", ChristmasExchange)
    CGI_SET_ACTION_DEFAULT_MAP("ChristmasKnockEgg", ChristmasKnockEgg)
    CGI_SET_ACTION_DEFAULT_MAP("CutPriceBuy", CutPriceBuy)
    CGI_SET_ACTION_DEFAULT_MAP("PointExchange", PointExchange)
    CGI_SET_ACTION_DEFAULT_MAP("BuildingSkinBuy", BuildingSkinBuy)
    CGI_SET_ACTION_DEFAULT_MAP("BuildingSkinUse", BuildingSkinUse)
    CGI_SET_ACTION_DEFAULT_MAP("BuildingSkinRelet", BuildingSkinRelet)
    CGI_SET_ACTION_DEFAULT_MAP("TutorLoginReward", TutorLoginReward)
    CGI_SET_ACTION_DEFAULT_MAP("ImperialGiftGet", ImperialGiftGet)
    CGI_SET_ACTION_DEFAULT_MAP("ImperialGiftOpen", ImperialGiftOpen)
    CGI_SET_ACTION_DEFAULT_MAP("TimeLimitUpgradeReward", TimeLimitUpgradeReward)
    CGI_SET_ACTION_DEFAULT_MAP("CSLadderReward", CSLadderReward)
    CGI_SET_ACTION_DEFAULT_MAP("WHRevelayDrawReward", WHRevelayDrawReward)
    CGI_SET_ACTION_DEFAULT_MAP("WHRevelayGetReward", WHRevelayGetReward)
    CGI_SET_ACTION_DEFAULT_MAP("YearFortuneInfo", YearFortuneInfo)
    CGI_SET_ACTION_DEFAULT_MAP("YearFortuneTransfer", YearFortuneTransfer)
    CGI_SET_ACTION_DEFAULT_MAP("YearFortuneReward", YearFortuneReward)
    CGI_SET_ACTION_DEFAULT_MAP("KeepsakeOnceProduce",  KeepsakeOnceProduce)
    CGI_SET_ACTION_DEFAULT_MAP("KeepsakeOnekeyProduce",  KeepsakeOnekeyProduce)
    CGI_SET_ACTION_DEFAULT_MAP("keepsakeoneKeyfulllevel",  KeepsakeOneKeyFullLevel)
    CGI_SET_ACTION_DEFAULT_MAP("KeepsakeSummon",  KeepsakeSummon)
    CGI_SET_ACTION_DEFAULT_MAP("KeepsakeSold",  KeepsakeSold)
    CGI_SET_ACTION_DEFAULT_MAP("KeepsakeFeed",  KeepsakeFeed)
    CGI_SET_ACTION_DEFAULT_MAP("ChargeFeedbackHeaven",  ChargeFeedbackHeaven)
    CGI_SET_ACTION_DEFAULT_MAP("ChargeFeedbackDaoist",  ChargeFeedbackDaoist)
    CGI_SET_ACTION_DEFAULT_MAP("CelebrateNewYear",  CelebrateNewYear)
    CGI_SET_ACTION_DEFAULT_MAP("VickyAcc",  VickyAcc)
    CGI_SET_ACTION_DEFAULT_MAP("GetXinWuFB",  GetXinWuFB)
    CGI_SET_ACTION_DEFAULT_MAP("TowerStepUp",  TowerStepUp)
    CGI_SET_ACTION_DEFAULT_MAP("TowerUnlock",  TowerUnlock)
    CGI_SET_ACTION_DEFAULT_MAP("CheckPayOptionVer",  CheckPayOptionVer)
    CGI_SET_ACTION_DEFAULT_MAP("PayOptionReward",  PayOptionReward)
    CGI_SET_ACTION_DEFAULT_MAP("TowerActReset", TowerActReset)
    CGI_SET_ACTION_DEFAULT_MAP("TowerActTreasure", TowerActTreasure)
    CGI_SET_ACTION_DEFAULT_MAP("TowerActOnce", TowerActOnce)
    CGI_SET_ACTION_DEFAULT_MAP("TowerActUnlock", TowerActUnlock)
    CGI_SET_ACTION_DEFAULT_MAP("TokenIntensifyList", TokenIntensifyList)
    CGI_SET_ACTION_DEFAULT_MAP("TokenIntensifyChgZone", TokenIntensifyChgZone)
    CGI_SET_ACTION_DEFAULT_MAP("TokenIntensifyChgNormal", TokenIntensifyChgNormal)
    CGI_SET_ACTION_DEFAULT_MAP("WorldTreasureDraw", WorldTreasureDraw)
   	CGI_SET_ACTION_DEFAULT_MAP("WorldTreasureExtract", WorldTreasureExtract)
   	CGI_SET_ACTION_DEFAULT_MAP("SoulFeedbackDraw", SoulFeedbackDraw)
   	CGI_SET_ACTION_DEFAULT_MAP("AwakenFeedbackDraw", AwakenFeedbackDraw)
   	CGI_SET_ACTION_DEFAULT_MAP("CastSoulDraw", CastSoulDraw)
   	CGI_SET_ACTION_DEFAULT_MAP("GemDiscountDraw", GemDiscountDraw)
    CGI_SET_ACTION_DEFAULT_MAP("EquipStrengthenVersion", EquipStrengthenVersion)
    CGI_SET_ACTION_DEFAULT_MAP("EquipStrengthenReward", EquipStrengthenReward)
    CGI_SET_ACTION_DEFAULT_MAP("UpGradeBNW", UpGradeBNW)
    CGI_SET_ACTION_DEFAULT_MAP("FastUpGradeBNW", FastUpGradeBNW)
    CGI_SET_ACTION_DEFAULT_MAP("UpGradeBNWTech", UpGradeBNWTech)
    CGI_SET_ACTION_DEFAULT_MAP("FastUpGradeBNWTech", FastUpGradeBNWTech)
    CGI_SET_ACTION_DEFAULT_MAP("HequCharge", HequCharge)
    CGI_SET_ACTION_DEFAULT_MAP("HequVIP", HequVIP)
    CGI_SET_ACTION_DEFAULT_MAP("HequBuchang", HequBuchang)//改为等级补偿
	CGI_SET_ACTION_DEFAULT_MAP("HequBuzhu", HequBuzhu)
    CGI_SET_ACTION_DEFAULT_MAP("Learjyt", Learjyt)
    CGI_SET_ACTION_DEFAULT_MAP("LearnJM", LearnJM)
    CGI_SET_ACTION_DEFAULT_MAP("InjectScroll", InjectScroll)
    CGI_SET_ACTION_DEFAULT_MAP("TreasuresAroundDraw", TreasuresAroundDraw)
    CGI_SET_ACTION_DEFAULT_MAP("TreasuresAroundDrawTenTimes", TreasuresAroundDrawTenTimes)
    CGI_SET_ACTION_DEFAULT_MAP("ShredCompound", ShredCompound)
    CGI_SET_ACTION_DEFAULT_MAP("SpiritFosterDraw", SpiritFosterDraw)
    CGI_SET_ACTION_DEFAULT_MAP("ChargeHorseDraw", ChargeHorseDraw)
    CGI_SET_ACTION_DEFAULT_MAP("LoadScrollActivity", LoadScrollActivity)
    CGI_SET_ACTION_DEFAULT_MAP("CompleteAffair", CompleteAffair)
    CGI_SET_ACTION_DEFAULT_MAP("GetActiveReward", GetActiveReward)
    CGI_SET_ACTION_DEFAULT_MAP("KingTreasureOpen", KingTreasureOpen)
    CGI_SET_ACTION_DEFAULT_MAP("KingTreasureReceive", KingTreasureReceive)
    CGI_SET_ACTION_DEFAULT_MAP("KingTreasureRecycle", KingTreasureRecycle)
    CGI_SET_ACTION_DEFAULT_MAP("ReceiveScrollFeedback", ReceiveScrollFeedback)
    CGI_SET_ACTION_DEFAULT_MAP("ReceiveSevenGift", ReceiveSevenGift)
    CGI_SET_ACTION_DEFAULT_MAP("TokenUpgradeReceive", TokenUpgradeReceive)
    CGI_SET_ACTION_DEFAULT_MAP("TokenUpgradeLottery", TokenUpgradeLottery)
    CGI_SET_ACTION_DEFAULT_MAP("BuildSuitReward", BuildSuitReward)
    CGI_SET_ACTION_DEFAULT_MAP("BlessPointExchange", BlessPointExchange)
    CGI_SET_ACTION_DEFAULT_MAP("DoubleWelfareExtra", DoubleWelfareExtra)
    CGI_SET_ACTION_DEFAULT_MAP("DoubleWelfareCharge", DoubleWelfareCharge)
    CGI_SET_ACTION_DEFAULT_MAP("PearlAdvanceExCharge", PearlAdvanceExCharge)
    CGI_SET_ACTION_DEFAULT_MAP("UniqueDialLottery", UniqueDialLottery)
    CGI_SET_ACTION_DEFAULT_MAP("SpiritGift", SpiritGift)
    CGI_SET_ACTION_DEFAULT_MAP("ForgeSmelt", ForgeSmelt)
    CGI_SET_ACTION_DEFAULT_MAP("ForgeShop", ForgeShop)
    CGI_SET_ACTION_DEFAULT_MAP("HeroDial", HeroDial)
    CGI_SET_ACTION_DEFAULT_MAP("KingdomWarCharge", KingdomWarCharge)
    CGI_SET_ACTION_DEFAULT_MAP("FlagUpgrade", FlagUpgrade)
    CGI_SET_ACTION_DEFAULT_MAP("OneDiamondWelfare", OneDiamondWelfare)
    CGI_SET_ACTION_DEFAULT_MAP("QixiFeedback", QixiFeedback)
    CGI_SET_ACTION_DEFAULT_MAP("FortunePacksOpenWindow", FortunePacksOpenWindow)
    CGI_SET_ACTION_DEFAULT_MAP("FortunePacksBuy", FortunePacksBuy)
    CGI_SET_ACTION_DEFAULT_MAP("SevenDayPacks", SevenDayPacks)
    CGI_SET_ACTION_DEFAULT_MAP("DivinePower", DivinePower)
    CGI_SET_ACTION_DEFAULT_MAP("StarStone", StarStone)
    CGI_SET_ACTION_DEFAULT_MAP("EveryDayRecharge", EveryDayRecharge)
    CGI_SET_ACTION_DEFAULT_MAP("EveryDayOnline", EveryDayOnline)
    CGI_SET_ACTION_DEFAULT_MAP("EnjoyStore", EnjoyStore)
    CGI_SET_ACTION_DEFAULT_MAP("VipReward", VipReward)
	CGI_SET_ACTION_DEFAULT_MAP("YingLingNormal", YingLingNormal)
	CGI_SET_ACTION_DEFAULT_MAP("YingLingAdvance", YingLingAdvance)
	CGI_SET_ACTION_DEFAULT_MAP("YingLingExp", YingLingExp)
	CGI_SET_ACTION_DEFAULT_MAP("YingLingStar", YingLingStar)
    CGI_SET_ACTION_DEFAULT_MAP("IcePhoenix", IcePhoenix)
    CGI_SET_ACTION_DEFAULT_MAP("AutumnFeedback", AutumnFeedback)
    CGI_SET_ACTION_DEFAULT_MAP("ProtectFlag", ProtectFlag)
    CGI_SET_ACTION_DEFAULT_MAP("YearEndGift", YearEndGift)
    CGI_SET_ACTION_DEFAULT_MAP("GetGoddessReward", GetGoddessReward)
    CGI_SET_ACTION_DEFAULT_MAP("KeyLuxuryGift", KeyLuxuryGift)
    CGI_SET_ACTION_DEFAULT_MAP("SoldierSpiritInject", SoldierSpiritInject)
    CGI_SET_ACTION_DEFAULT_MAP("EnjoyGiftReward", EnjoyGiftReward)
    CGI_SET_ACTION_DEFAULT_MAP("TurnLuckyTable", TurnLuckyTable)
    CGI_SET_ACTION_DEFAULT_MAP("RecoverEnergy", RecoverEnergy)
    CGI_SET_ACTION_DEFAULT_MAP("InviteEnergy", InviteEnergy)
    CGI_SET_ACTION_DEFAULT_MAP("BuyEnergy", BuyEnergy)
    CGI_SET_ACTION_DEFAULT_MAP("OpenEnergyBag", OpenEnergyBag)
    CGI_SET_ACTION_DEFAULT_MAP("SpecialPackOpen", SpecialPackOpen)
    CGI_SET_ACTION_DEFAULT_MAP("NewYearChargeReward", NewYearChargeReward)
    CGI_SET_ACTION_DEFAULT_MAP("NewYearCombinedShop", NewYearCombinedShop)
    CGI_SET_ACTION_DEFAULT_MAP("NewYearOnlineReward", NewYearOnlineReward)
    CGI_SET_ACTION_DEFAULT_MAP("achievementGift", achievementGift)
    CGI_SET_ACTION_DEFAULT_MAP("DiscountShopGift", DiscountShopGift)
    CGI_SET_ACTION_DEFAULT_MAP("GainResource", GainResource)
    CGI_SET_ACTION_DEFAULT_MAP("JueXueBreakThrough", JueXueBreakThrough)
    //CGI_SET_ACTION_DEFAULT_MAP("BlackGoldExchange", BlackGoldExchange)
    CGI_SET_ACTION_DEFAULT_MAP("StarStoneChange", StarStoneChange)
    CGI_SET_ACTION_DEFAULT_MAP("VickyAccX", VickyAccX)
    CGI_SET_ACTION_DEFAULT_MAP("VickyAccX1", VickyAccX1)
    CGI_SET_ACTION_DEFAULT_MAP("VickyAccX2", VickyAccX2)
    CGI_SET_ACTION_DEFAULT_MAP("VickyAccX3", VickyAccX3)
    CGI_SET_ACTION_DEFAULT_MAP("VickyAccX4", VickyAccX4)
    CGI_SET_ACTION_DEFAULT_MAP("VickyAccX5", VickyAccX5)
    CGI_SET_ACTION_DEFAULT_MAP("huangzhong", huangzhong)
    CGI_SET_ACTION_DEFAULT_MAP("VickyNewOpen", VickyNewOpen)
    CGI_SET_ACTION_DEFAULT_MAP("SummerAccReward", SummerAccReward)
    CGI_SET_ACTION_DEFAULT_MAP("SummerDailyReward", SummerDailyReward)
    CGI_SET_ACTION_DEFAULT_MAP("SummerHolidaysAccReward", SummerHolidaysAccReward)
    CGI_SET_ACTION_DEFAULT_MAP("SummerHolidaysExchangeItem", SummerHolidaysExchangeItem)
	CGI_SET_ACTION_DEFAULT_MAP("chongzhizixuan", chongzhizixuan)
	CGI_SET_ACTION_DEFAULT_MAP("beautyactive", BeautyActive)
	CGI_SET_ACTION_DEFAULT_MAP("beautypoint", BeautyPoint)
	CGI_SET_ACTION_DEFAULT_MAP("beautyreward", BeautyReward)
	CGI_SET_ACTION_DEFAULT_MAP("InvestmentCount", InvestmentCount)
	CGI_SET_ACTION_DEFAULT_MAP("InvestmentOption", InvestmentOption)
	CGI_SET_ACTION_DEFAULT_MAP("InvestmentReward", InvestmentReward)
	CGI_SET_ACTION_DEFAULT_MAP("BirdBridge", BirdBridge)
	CGI_SET_ACTION_DEFAULT_MAP("ShengDan2018", ShengDan2018)
	CGI_SET_ACTION_DEFAULT_MAP("XiaoNian2018", XiaoNian2018)
	/********************************************************************/
	/*  活动太多  先是抽象成模板  最后只能搞宏       */
#define CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_NAME) \
		CGI_SET_ACTION_DEFAULT_MAP(CONFIG_NAME, CONFIG_NAME##_ACT)
	/********************************************************************/
//autolable7
CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_fuzhuhesui)
CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_zhuniandaji)
CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_vicky_qingrenjie)
CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_yuandan2018)
CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_yearend2018)
CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_winter2018)
CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_double11_2018)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_mid_aug_hao)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_mid_aug_reu)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_water_taotie)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_water_qilin)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_water_pheonix)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_vicky_nnom)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_VICKY_NO_NAME)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_VICKY_BINGSHU)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_VICKY_QIANFU)
	CHARGE_DRAW_ACT_ACTION_MAP(CONFIG_VICKY_NNA)
	///////////////////////////////////////////////////////////////
    CGI_SET_ACTION_DEFAULT_MAP("TaskGift", TaskGift)
    CGI_SET_ACTION_DEFAULT_MAP("RotaryTableChargeReward", RotaryTableChargeReward)
    CGI_SET_ACTION_DEFAULT_MAP("RotaryTableRandomReward", RotaryTableRandomReward)
    CGI_SET_ACTION_DEFAULT_MAP("BatmanTreasureChargeReward", BatmanTreasureChargeReward)
    CGI_SET_ACTION_DEFAULT_MAP("BatmanTreasureDraw", BatmanTreasureDraw)
	CGI_SET_ACTION_DEFAULT_MAP("HeroExtraStone", HeroExtraStone)
	CGI_SET_ACTION_DEFAULT_MAP("FashionStar", FashionStar)
	CGI_SET_ACTION_DEFAULT_MAP("JihuoChenghao", JihuoChenghao)
	CGI_SET_ACTION_DEFAULT_MAP("PeidaiChenghao", PeidaiChenghao)
	CGI_SET_ACTION_DEFAULT_MAP("ZhuanyiChenghao", ZhuanyiChenghao)

	//争霸技能
	CGI_SET_ACTION_DEFAULT_MAP("CommderSkilLearn", CommderSkilLearn)
	//破天技升级
	CGI_SET_ACTION_DEFAULT_MAP("PotianSkilLearn", PotianSkilLearn)
	//喜迎国庆
	CGI_SET_ACTION_DEFAULT_MAP("GuoQingChargeReward",  GuoQingChargeReward)
	CGI_SET_ACTION_DEFAULT_MAP("ChinaDayEveryDayReward",  ChinaDayEveryDayReward)
	CGI_SET_ACTION_DEFAULT_MAP("ChinaDayOnlineReward",  ChinaDayOnlineReward)
	CGI_SET_ACTION_DEFAULT_MAP("ChinaDayInstanceZonesReward",  ChinaDayInstanceZonesReward)
	CGI_SET_ACTION_DEFAULT_MAP("ChinaDayDeDuctChallengeNum",  ChinaDayDeDuctChallengeNum)

	//每日充值自选活动
	CGI_SET_ACTION_DEFAULT_MAP("EveryDayPayOptionalReward",  EveryDayPayOptionalReward)
	//兑换自选
	CGI_SET_ACTION_DEFAULT_MAP("free_exchg",  free_exchg)
	//fm
	CGI_SET_ACTION_DEFAULT_MAP("setherofm",SetHeroFm)

    CGI_ACTION_DEFAULT_MAP_END

	int Save()
	{
		//info_log("[save data][uid=%u&m_strData=<%s>]",m_uid,m_strData.c_str());

		unsigned uid = 0;
		if (!Json::GetUInt(m_data, "userid", uid) || uid == 0)
		{
			uid = m_uid;
		}
		string type;
		Json::GetString(m_data, "type", type);
		CLogicArchive logicArchive;
		int result = logicArchive.Save(uid, m_uid, type, m_data, m_jsonResult);
		if (result != 0)
		{
			return result;
		}

		m_jsonResult["currenttime"] = Time::GetGlobalTime();

		int isbattle = 0;//Ralf20140225  后台增加pve或pvp保护
		Json::GetInt(m_data, "isbattle", isbattle);

		CGI_SEND_LOG("operator=%u&operated=%u&type=%s&lasttime=%u&lastseq=%u&isbattle=%u"
				, m_uid, uid, type.c_str(), m_jsonResult.isMember("lasttime")?m_jsonResult["lasttime"].asUInt():0, m_jsonResult.isMember("lasttime")?m_jsonResult["lastseq"].asUInt():0,isbattle);
		return R_SUCCESS;
	}

	int UpgradeBuilding()
	{
		unsigned id;
		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned tv;
		if (!Json::GetUInt(m_data, "tv", tv))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		string bq;
		if(!Json::GetString(m_data, "bq", bq))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned fcm = 0;
		Json::GetUInt(m_data,"fcm",fcm);
		if(fcm >= e_fcm_max)
			return R_ERR_PARAM;

		CLogicCMD logicCMD;
		int ret = logicCMD.UpgradeBuilding(m_uid,id,tv,bq,fcm,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=UpgradeBuilding&uid=%u&id=%u", m_uid, id);
		return R_SUCCESS;
	}

	int FastUpgradeBuilding()
	{
		unsigned id;
		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned ud;
		if (!Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned count;
		if (!Json::GetUInt(m_data, "count", count))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned type;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		string bq;
		if(!Json::GetString(m_data, "bq", bq))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned help = 0;
		Json::GetUInt(m_data, "help", help);

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.FastUpgradeBuilding(m_uid,id,type,ud,count,bq,help,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FastUpgradeBuilding&uid=%u&id=%u", m_uid, id);
		return R_SUCCESS;
	}

	int GMUpgradeBuilding()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.GMUpgradeBuilding(m_uid,m_data,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GMUpgradeBuilding&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GMAddExp()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.GMAddExp(m_uid,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GMAddExp&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ExpMaxAdd()
	{
		unsigned type;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.ExpMaxAdd(m_uid,type,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ExpMaxAdd&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int RefreshHero()
	{
		unsigned refreshType;
		if (!Json::GetUInt(m_data, "refreshType", refreshType))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned sourceType;
		if (!Json::GetUInt(m_data, "sourceType", sourceType))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		// 招募令ud
		unsigned zmlud = 0; // 招募令ud
		if(sourceType == REFRESH_COST_ITEM)
		{
			if (!Json::GetUInt(m_data, "zmlud", zmlud))
			{
				error_log("para error");
				return R_ERR_PARAM;
			}
		}


		CLogicCMD logicCMD;
		int ret = logicCMD.RefreshHero(m_uid,refreshType,sourceType,m_jsonResult,zmlud,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=refreshhero&uid=%u&refreshType=%u", m_uid, refreshType);
		return R_SUCCESS;
	}

	int UpgradeHero()
	{
		int target;
		if (!Json::GetInt(m_data, "target", target))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		int source[XML_HERO_SOURCE];
		for(int i=0;i<XML_HERO_SOURCE;++i)
			source[i] = -1;
		Json::GetInt(m_data, "source1", source[0]);
		Json::GetInt(m_data, "source2", source[1]);
		Json::GetInt(m_data, "source3", source[2]);

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.UpgradeHero(m_uid,target,source,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=UpgradeHero&uid=%u&target=%d&source1=%d&source2=%d&source3=%d", m_uid, target,source[0],source[1],source[2]);
		return R_SUCCESS;
	}

	int UpgradeHeroForActivity()
	{
		int target;
		if (!Json::GetInt(m_data, "target", target))
		{
			error_log("para target error");
			return R_ERR_PARAM;
		}
		int source1 = -1, source2 = -1,  source3 = -1;
		if (!Json::GetInt(m_data, "source1", source1) || !Json::GetInt(m_data, "source2", source2) || !Json::GetInt(m_data, "source3", source3))
		{
			error_log("para lost error");
			return R_ERR_PARAM;
		}
		unsigned count_negative = 0;
		if (source1 <= 0)
			count_negative++;
		if (source2 <= 0)
			count_negative++;
		if (source3 <= 0)
			count_negative++;
		if (1 != count_negative)
		{
			error_log("para  count_negative error: must be 1 negative");
			return R_ERR_PARAM;
		}
		int source[XML_HERO_SOURCE];
		for(int i=0;i<XML_HERO_SOURCE;++i)
			source[i] = -1;
		source[0] = source1;
		source[1] = source2;
		source[2] = source3;
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		int ret = 0;
		CLogicCMD logicCMD;
		//have free opportunity
		ret = logicCMD.UpgradeHeroForActivity(m_uid,target,source,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=UpgradeHeroForActivity&uid=%u&target=%d&source1=%d&source2=%d&source3=%d", m_uid,target,source[0],source[1],source[2]);
		return R_SUCCESS;
	}
	int GetUpgradeHeroForActivity()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.GetUpgradeHeroForActivity(m_uid, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GetUpgradeHeroForActivity&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ChargeBackHappyCard()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ChargeBackHappyCard(m_uid,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ChargeBackHappyCard&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int CheckSave()
	{
		CGI_SEND_LOG("action=CheckSave&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EquipSub()
	{
		unsigned equip = 0, stone = 0, type = 0, lvl = 0, spirit = 0, free = 0;
		if(!Json::GetUInt(m_data, "equip", equip)
		|| !Json::GetUInt(m_data, "stone", stone)
		|| !Json::GetUInt(m_data, "lvl", lvl)
		|| !Json::GetUInt(m_data, "spirit", spirit)
		|| !m_data.isMember("keep")
		|| !m_data["keep"].isArray()
		|| !Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		Json::GetUInt(m_data, "free", free);

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ChangeEquipSub(m_uid, equip, lvl, stone, type, spirit, free, m_data["keep"], m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=EquipSub&uid=%u&equip=%d", m_uid, equip);
		return R_SUCCESS;
	}
	int EquipSubAct1()
	{
		unsigned equip = 0, lvl = 0;
		string osub, nsub;
		if(!Json::GetUInt(m_data, "equip", equip)
		|| !Json::GetString(m_data, "osub", osub)
		|| !Json::GetString(m_data, "nsub", nsub)
		|| !Json::GetUInt(m_data, "lvl", lvl))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.EquipSubAct1(m_uid, equip, osub, nsub, lvl, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=EquipSubAct1&uid=%u&equip=%d", m_uid, equip);
		return R_SUCCESS;
	}
	int EquipSubAct2()
	{
		unsigned equip = 0, all = 0, lvl = 0;
		if(!Json::GetUInt(m_data, "equip", equip)
		|| !Json::GetUInt(m_data, "all", all)
		|| !Json::GetUInt(m_data, "lvl", lvl))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.EquipSubAct2(m_uid, equip, all, lvl, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=EquipSubAct2&uid=%u&equip=%d", m_uid, equip);
		return R_SUCCESS;
	}

	int OldUserGift()
	{
		return 0;

#define OLD_USER_GIFT 712

		string openid;
		if(!Json::GetString(m_data, "openid", openid))
			return R_ERR_PARAM;

		CDataBlackUser dbBlackUser;
		DataBlackUser data;
		int ret = dbBlackUser.GetBlackUser(openid, data);
		if(ret)
			return ret;

		if(data.block_time != gm_gift)
			return R_ERR_LOGIC;

		CLogicEquipment logicEquipment;
		AUTO_LOCK_USER(m_uid)
		ret = logicEquipment.AddOneItem(m_uid, OLD_USER_GIFT, 1,"OldUserGift",m_jsonResult["equipment"]);
		if(ret)
			return ret;

		data.open_id = openid;
		data.block_time = gm_none;
		ret =  dbBlackUser.SetBlackUser(data);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=OldUserGift&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int DigEquipSubStone()
	{
		unsigned type = 0;
		if(!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.DigEquipSubStone(m_uid, type, equd, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=DigEquipSubStone&uid=%u&type=%d", m_uid, type);
		return R_SUCCESS;
	}

	int TreasureHunt()
	{
		unsigned type = 0, times = 0;
		if(!Json::GetUInt(m_data, "type", type) || !Json::GetUInt(m_data, "times", times))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.TreasureHunt(m_uid, type, times, equd, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=TreasureHunt&uid=%u&times=%d", m_uid, times);
		return R_SUCCESS;
	}

	int useGiftBag()
	{
		unsigned ud = 0, count = 0;
		if(!Json::GetUInt(m_data, "ud", ud)
		|| !Json::GetUInt(m_data, "count", count))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.useGiftBag(m_uid, ud, count, m_jsonResult,seqid,lasttime);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=usegiftbag&uid=%u&ud=%d&count=%d", m_uid, ud, count);
		return R_SUCCESS;
	}

	int NewPayrankActivity()
	{
		int ret = 0;
		int lottery_number = 0;
		int point = 0;

		if (!Json::GetInt(m_data, "lottery_number", lottery_number) || !Json::GetInt(m_data, "point", point))
		{
			error_log("[activity_new_payrank_error] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD payrank;
		ret = payrank.Payrank_activity(m_uid, lottery_number,point,m_jsonResult,lasttime,seqid);
		if(ret != 0)
		{
			error_log("[activity_new_payrank_failed] [uid=%u]",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=newpayrankactivity&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int BuyBet()
	{
		int ret = 0;
		int bet = 0;

		if (!Json::GetInt(m_data, "bet", bet))
		{
			error_log("[buybet_error] [uid=%u | bet=%d]", m_uid, bet);
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD BuyBet;
		ret = BuyBet.BuyBet(m_uid, bet, m_jsonResult, lasttime, seqid);
		if(ret != 0)
		{
			error_log("[buybet_failed] [uid=%u]",m_uid);
			return ret;
		}
		CGI_SEND_LOG("action=buybet&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int Shop()
	{
		unsigned id = 0, count = 0, flag = 0, vip = 0, type = 0;
		if(!Json::GetUInt(m_data, "id", id) || !Json::GetUInt(m_data, "count", count))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		Json::GetUInt(m_data, "flag", flag);
		Json::GetUInt(m_data, "vip", vip);
		Json::GetUInt(m_data, "type", type);

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd = 0;

		Json::GetUInt(m_data, "djud", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.Shop(m_uid, id, count, flag, type, vip, equd, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=Shop&uid=%u&id=%u&count=%u&flag=%u&type=%u&vip=%u", m_uid, id, count, flag, type, vip);
		return R_SUCCESS;
	}

	int ProductShop()
	{
		unsigned ud = 0, id = 0, type = 0;
		if(!Json::GetUInt(m_data, "ud", ud) || !Json::GetUInt(m_data, "id", id) || !Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ProductShop(m_uid, type, ud, id, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ProductShop&uid=%u&type=%u&id=%u", m_uid, type, id);
		return R_SUCCESS;
	}


	int FashionShop()
	{
		unsigned seqid = 0, lasttime = 0;
		if(!Json::GetUInt(m_data, "seqid", seqid)   	||
		   !Json::GetUInt(m_data, "lastime", lasttime))
		{
			error_log("para error: sys");
			return R_ERR_PARAM;
		}

		unsigned id = 0, count = 0,  is_cash = 0;
		if(!Json::GetUInt(m_data, "id", id)       		||
		   !Json::GetUInt(m_data, "count", count) 		||
		   !Json::GetUInt(m_data, "isCash", is_cash))
		{
			error_log("para error: business");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.FashionShop(m_uid, id, count, (bool)is_cash, m_jsonResult, lasttime, seqid);
		if(ret)
		{
			error_log("[fashion_shop_failed] [uid=%u][id=%u]", m_uid, id);
			return ret;
		}

		CGI_SEND_LOG("action=FashionShop&uid=%u&id=%u&count=%u&is_cash=%u", m_uid, id, count, is_cash);
		return R_SUCCESS;
	}


	int EquipIntensifys()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetEquipIntensifys(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=equipintensifys&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int SyntheticGemBack()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.SyntheticGem(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=syntheticgemback&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int MeltOldSoulStone()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.MeltOldSoulStone(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=MeltOldSoulStone&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int SynNewSoulStone()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.SynNewSoulStone(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=SynNewSoulStone&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int SynNewSoulStoneUp()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.SynNewSoulStoneUp(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=SynNewSoulStoneUp&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int QianghuaDismantlingEquipBack()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equip_level = 0, equip_ud = 0, q_level = 0;
		if(!Json::GetUInt(m_data, "equip_level", equip_level) || !Json::GetUInt(m_data, "equip_ud", equip_ud)
		|| !Json::GetUInt(m_data, "q_level", q_level)
		)
		{
			error_log("QianghuaDismantlingEquipBack_para_error");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.QianghuaDismantlingEquip(m_uid, equip_level, equip_ud, q_level, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=qianghuadismantlingequipBack&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int TaozhuangDismantlingEquip()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equip_id = 0, ud = 0;
		if(!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("TaozhuangDismantlingEquip_para_error");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.TaozhuangDismantlingEquip(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=taozhuangdismantlingequip&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int HammerHit()
	{
		int ret = 0;

		unsigned hammerud = 0;
		if (!Json::GetUInt(m_data, "hammerud", hammerud) )
		{
			error_log("[hammerhitdata hammerud error] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		int hitCount = 0;
		if (!Json::GetInt(m_data, "hitCount", hitCount) )
		{
			error_log("[hammerhitdata hitCount error] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		ret = logicCMD.HammerHit(m_uid, hammerud, hitCount, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=hammerhit&uid=%u&count=%u", m_uid, hitCount);
		return R_SUCCESS;
	}

	int HammerHitAllServer()
	{
		int ret = 0;

		unsigned hammerud = 0;
		if (!Json::GetUInt(m_data, "hammerud", hammerud) )
		{
			error_log("[hammerhitdata hammerud error] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		int hitCount = 0;
		if (!Json::GetInt(m_data, "hitCount", hitCount) )
		{
			error_log("[hammerhitdata hitCount error] [uid=%u]",m_uid);
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		ret = logicCMD.HammerHitAllServer(m_uid, hammerud, hitCount, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HammerHitAllServer&uid=%u&count=%u", m_uid, hitCount);
		return R_SUCCESS;
	}

	int UseShip()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned torch = 0;
		unsigned classType = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "torch", torch);
		Json::GetUInt(m_data, "classType", classType);

		CLogicCMD logicCMD;
		int ret = logicCMD.UseShip(m_uid, torch, classType, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=useship&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int RefreshShip()
	{
		unsigned refreshType;
		if (!Json::GetUInt(m_data, "refreshType", refreshType))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.RefreshShip(m_uid,refreshType,equd,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=refreshship&uid=%u&refreshType=%u", m_uid, refreshType);
		return R_SUCCESS;
	}

	int HeroPowerUp()
	{
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.HeroPowerUp(m_uid,heroud,equd,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=heropowerup&uid=%u&heroud=%u&equd=%u", m_uid, heroud, equd);
		return R_SUCCESS;
	}

	int HeroPower2Up()
	{
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned specialud = 0;
		Json::GetUInt(m_data, "specialud", specialud);

		unsigned equd1 = 0;
		Json::GetUInt(m_data, "equd1", equd1);

		unsigned equd2 = 0;
		Json::GetUInt(m_data, "equd2", equd2);

		unsigned equd3 = 0;
		Json::GetUInt(m_data, "equd3", equd3);

		unsigned equd4 = 0;
		Json::GetUInt(m_data, "equd4", equd4);

		unsigned type = 0;
		if(!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.HeroPower2Up(m_uid,heroud,equd, specialud, equd1, equd2, equd3, equd4, type,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=heropower2up&uid=%u&heroud=%u&equd=%u", m_uid, heroud, equd);
		return R_SUCCESS;
	}

	int HeroPower3Up()
	{
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.HeroPower3Up(m_uid,heroud,equd,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=heropower3up&uid=%u&heroud=%u&equd=%u", m_uid, heroud, equd);
		return R_SUCCESS;
	}

	int liandan()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.liandan(m_uid,m_data,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=liandan&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int keyao()
	{
		unsigned eqid;
		if (!Json::GetUInt(m_data, "eqid", eqid))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.keyao(m_uid,eqid,equd,heroud,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=keyao&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int godh()
	{
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned index1;
		if (!Json::GetUInt(m_data, "index1", index1))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned index2;
		if (!Json::GetUInt(m_data, "index2", index2))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.godh(m_uid,equd,index1,index2,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=godh&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int HeroLearnHorse()
	{
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd1;
		if (!Json::GetUInt(m_data, "equd1", equd1))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd2;
		if (!Json::GetUInt(m_data, "equd2", equd2))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned once = 0;
		if(!Json::GetUInt(m_data, "once", once))
		{
			error_log("para error");
		//	return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.HeroLearnHorse(m_uid,heroud,equd1,equd2,m_jsonResult,lasttime,seqid, once);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=herolearnhorse&uid=%u&heroud=%u", m_uid, heroud);
		return R_SUCCESS;
	}

	int UpgradeHorse()
	{
		unsigned horseud;
		if (!Json::GetUInt(m_data, "horseud", horseud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd_2 = 0;
		Json::GetUInt(m_data, "equd_2", equd_2);


		CLogicCMD logicCMD;

		int ret = logicCMD.UpgradeHorse(m_uid, horseud, equd, equd_2, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=upgradehorse&uid=%u&horseud=%u", m_uid, horseud);
		return R_SUCCESS;
	}

	int ElevateHorse()
	{
		unsigned horseud;

		if (!Json::GetUInt(m_data, "horseud", horseud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ElevateHorse(m_uid, horseud, equd, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=elevatehorese&uid=%u&horseud=%u", m_uid, horseud);
		return R_SUCCESS;
	}

	int BuildEquipSet()
	{
		unsigned part = 0;
		unsigned occupation = 0;
		if (!Json::GetUInt(m_data, "part", part) || !Json::GetUInt(m_data, "occupation", occupation))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.BuildEquipSet(m_uid, part, occupation, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=buildequipset&uid=%u&part=%u&occupation=%u", m_uid, part, occupation);
		return R_SUCCESS;
	}

	int UpgradeEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.UpgradeEquipSet(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=upgradeequipset&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int RefineEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.RefineEquipSet(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=refineequipset&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int ShenQiEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.RefineEquipSet(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid, ShenQi);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=shenqiequipset&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int ShenZhuEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.RefineEquipSet(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid, ShenZhu);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ShenZhuEquipSet&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int WuxingEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.WuxingEquipSet(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=wuxingequipset&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int BlessEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.BlessEquipSet(m_uid, equip_id, ud, m_data, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=blessequipset&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int ShenWenEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ShenWenEquipSet(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ShenWenquipset&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int ShenGeEquipSet()
	{
		unsigned equip_id, ud;
		if (!Json::GetUInt(m_data, "equip_id", equip_id) || !Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ShenGeEquipSet(m_uid, equip_id, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ShenGequipset&uid=%u&equip_id=%u&ud=%u", m_uid, equip_id, ud);
		return R_SUCCESS;
	}

	int AddSoul()
	{
		unsigned type = 0;
		if(!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned isCash = 0;
		Json::GetUInt(m_data, "isCash", isCash);

		CLogicCMD logicCMD;
		int ret = logicCMD.AddSoul(m_uid, (bool)isCash, type, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=AddSoul&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int NewLottery()
	{
		unsigned level = 0;
		unsigned count = 0;
		if(!Json::GetUInt(m_data, "level", level) || !Json::GetUInt(m_data, "count", count))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.NewLotteryActivity(m_uid, level, count, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=newlottery&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int JueXueOneKeyFullLevel()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.JueXueOneKeyFullLevel(m_uid, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=juexueonekeyfulllevel&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int Juexue()
	{
		unsigned all = 0;
		if(!Json::GetUInt(m_data, "all", all))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.Juexue(m_uid, all?true:false, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Juexue&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int QixiChoujiang()
	{
		unsigned count = 0;
		if(!Json::GetUInt(m_data, "count", count))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.QixiChoujiangActivity(m_uid, count, equd, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=qixichoujiang&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int JianglingChengzhang()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetJianglingGrow(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=jianglingchengzhang&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int JianglingSkill()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetJianglingSkillsDraw(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=jianglingskill&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ChangeName()
	{
		string name, openid, figure;
		if (!Json::GetString(m_data, "name", name) || !Json::GetString(m_data, "openid", openid) || !Json::GetString(m_data, "figure", figure))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ChangeName(m_uid, name, openid, figure, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ChangeName&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ChangeNameAfterFirst()
	{
		string name, openid, figure;
		if (!Json::GetString(m_data, "name", name) || !Json::GetString(m_data, "openid", openid) || !Json::GetString(m_data, "figure", figure))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned equd = 0;
		if(!Json::GetUInt(m_data, "seqid", seqid))
		{
			error_log("para seqid error");
			return R_ERR_PARAM;
		}
		if(!Json::GetUInt(m_data, "lastime", lasttime))
		{
			error_log("para lastime error");
			return R_ERR_PARAM;
		}
		if(!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para equd error");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.ChangeNameAfterFirst(m_uid, name, equd, openid, figure, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ChangeNameAfterFirst&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int SJ4399()
	{
		string code, openid;
		if (!Json::GetString(m_data, "code", code) || !Json::GetString(m_data, "openid", openid))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.SJ4399(m_uid, code, openid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=SJ4399&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int XSK4399()
	{
		string code, openid;
		if (!Json::GetString(m_data, "code", code) || !Json::GetString(m_data, "openid", openid))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.XSK4399(m_uid, code, openid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=XSK4399&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int XSKBaidu()
	{
		string code;
		string openid;

		if (!Json::GetString(m_data, "code", code) || !Json::GetString(m_data, "openid", openid))
		{
			error_log("para error");
			return 	R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;

		int ret = logicCMD.XSKBaidu(m_uid, code, openid, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=XSKBaidu&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int CreditShop()
	{
		unsigned eqid = 0;
		if (!Json::GetUInt(m_data, "eqid", eqid) || (0 == eqid))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned b4399 = 0;
		Json::GetUInt(m_data, "b4399", b4399);

		CLogicCMD logicCMD;
		int ret = logicCMD.CreditShop(m_uid, eqid, b4399, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=CreditShop&uid = %u", m_uid);
		return R_SUCCESS;
	}


	int DragonScaleActivity()
	{
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.DragonScaleActivity(m_uid, type, equd, m_jsonResult, lasttime, seqid);

		if (ret)
			return ret;

		CGI_SEND_LOG("action=DragonScaleActive&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int DragonScaleTensActivity()
	{
		unsigned type = 0;

		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.DragonScaleTensActivity(m_uid, type, equd, m_jsonResult, lasttime, seqid);

		if (ret)
			return ret;

		CGI_SEND_LOG("action=DragonScaleTensActive&uid=%u", m_uid);

		return R_SUCCESS;
	}
	int DragonScaleAllFree()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.DragonScaleAllFree(m_uid, m_jsonResult, lasttime, seqid);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=DragonScaleAllFree&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int TouchGold()
	{
		unsigned type = 0;
		unsigned id = 0;
		unsigned listindex = 0;
		unsigned ud = 0;

		if (!Json::GetUInt(m_data, "type", type)
		|| !Json::GetUInt(m_data, "id", id)
		|| !Json::GetUInt(m_data, "listindex", listindex))
		{
			error_log("param error");
			return R_ERR_PARAM;
		}

		Json::GetUInt(m_data, "ud", ud);

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.TouchGold(m_uid, type, id, listindex, ud, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=TouchGold%uid=%u", m_uid);
		return R_SUCCESS;
	}


	int HappyCard()
	{
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned position = 0;
		Json::Value iData;
		if (!Json::GetUInt(m_data, "position", position))
		{
			iData["canDraw"] = 0;
		}
		else
		{
			iData["canDraw"] = 1;
		}

		iData["position"] = position;

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.HappyCard(m_uid, type, iData, m_jsonResult, lasttime, seqid);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=HappyCard&uid=%u", m_uid);
		return R_SUCCESS;
	}


	// 获得10min protect time
	int ProtectToken()
	{
		unsigned equd = 0;

		if (!Json::GetUInt(m_data, "equd", equd) || (0 == equd))
		{
			error_log("param error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.ProtectToken(m_uid, equd, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=ProtectToken&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int Poker21()
	{
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned multiple = 0;
		unsigned position = 0;
		vector<unsigned> iData;
		Json::GetUInt(m_data, "multiple", multiple);
		Json::GetUInt(m_data, "position", position);
		iData.push_back(multiple);
		iData.push_back(position);

		CLogicCMD logicCMD;
		int ret = logicCMD.Poker21(m_uid, type, iData, lasttime, seqid, m_jsonResult);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=HappyCard&uid=%u", m_uid);
		return R_SUCCESS;
	}


	// type
	// 0  遁甲
	// 1 天书
	// 4: 有四种道具可以使用
	int HeavenDaoist()
	{
		Json::Value equd;
		unsigned type = 0;
		unsigned count = 0;
		unsigned oneclick = 0; //0 -- 修炼   1 -- 一键升层
		if (!Json::GetArray(m_data, "equd", equd) || (5 != equd.size() && 4 != equd.size())
			|| !Json::GetUInt(m_data, "type", type)
			|| !Json::GetUInt(m_data, "count", count) || (0 == count))
		{

			return R_ERR_PARAM;
		}
		if(!Json::GetUInt(m_data, "oneclick", oneclick))
		{
			return R_ERR_PARAM;
		}

		unsigned is_cash = 0;
		Json::GetUInt(m_data, "isCash", is_cash);

		unsigned lasttime;
		unsigned seqid;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = 0;
		if (is_cash == 1)
		{
			ret = logicCMD.HeavenDaoist(m_uid, type, count, equd, true, m_jsonResult, lasttime, seqid, oneclick);
		} else
		{
			ret = logicCMD.HeavenDaoist(m_uid, type, count, equd, false, m_jsonResult, lasttime, seqid, oneclick);
		}
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=HeavenDaoist&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EightFormation()
	{
		Json::Value equd;
		unsigned count = 1;
		unsigned oneclick = 0; //0 -- 修炼   1 -- 一键升层
		unsigned id = 0;
		if (!Json::GetArray(m_data, "equd", equd)
			 || !Json::GetUInt(m_data, "id", id))
		{
			return R_ERR_PARAM;
		}
		if(!Json::GetUInt(m_data, "oneclick", oneclick))
		{
			return R_ERR_PARAM;
		}
		if(id <1 || id > 8)
		{
			return R_ERR_PARAM;
		}

		unsigned is_cash = 0;
		Json::GetUInt(m_data, "isCash", is_cash);

		unsigned lasttime;
		unsigned seqid;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.EightFormation(m_uid, id, count, equd, is_cash, 0, m_jsonResult, lasttime, seqid, oneclick);
		if(0 != ret)
			return ret;

		CGI_SEND_LOG("action=eightFormation&uid=%u", m_uid);
		return R_SUCCESS;

	}

	//投石车
	int Catapult()
	{
		Json::Value equd;
		unsigned count = 0;
		unsigned oneclick = 0; //0 -- 修炼   1 -- 一键升层
		if (!Json::GetArray(m_data, "ud", equd)
			|| !Json::GetUInt(m_data, "count", count) || (0 == count))
		{
			error_log("param error uid= %u", m_uid);
			return R_ERR_PARAM;
		}

		if(!Json::GetUInt(m_data, "oneclick", oneclick))
		{
			error_log("param error uid= %u", m_uid);
			return R_ERR_PARAM;
		}
		unsigned is_cash = 0;
		Json::GetUInt(m_data, "isCash", is_cash);
		unsigned lasttime;
		unsigned seqid;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.Catapult(m_uid, count, equd, is_cash, m_jsonResult, lasttime, seqid, oneclick);
		if(ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=Catapult&uid=%u", m_uid);
		return R_SUCCESS;

	}
	int CatapultSkillUp()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0, equd = 0;


		if (!Json::GetUInt(m_data, "index", index) || !Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: lack of index, type, equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.UpgradeCatapultSkill(m_uid, index, equd, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=CatapultSkillUp&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int R5()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned count = 1;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "count", count);

		CLogicCMD logicCMD;
		ret = logicCMD.R5(m_uid, count, m_jsonResult, lasttime, seqid);
		if (ret)
			return ret;

		CGI_SEND_LOG("action=R5&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int MultipleWheel()
	{
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime;
		unsigned seqid;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.MultipleWheel(m_uid, type, lasttime, seqid, m_jsonResult);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=MultipleWheel&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int UpgradeGem()
	{
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.UpgradeGem(m_uid, equd, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=UpgradeGem&uid=%u&equd=%u", m_uid, equd);
		return R_SUCCESS;
	}

	int UpgradeTenWeapon()
	{
		unsigned id = 0;
		unsigned equd = 0;
		unsigned times = 0; //0：消耗铸魂符      1：每消耗100器魂，可以获得铸魂一次
		unsigned count = 0;
		if (!Json::GetUInt(m_data, "id", id) || !Json::GetUInt(m_data, "equd", equd) ||
				!Json::GetUInt(m_data, "times", times) || !Json::GetUInt(m_data, "count", count))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.UpgradeTenWeapon(m_uid, id, equd, times, count, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=UpgradeGem&uid=%u&equd=%u", m_uid, equd);
		return R_SUCCESS;
	}

	int MergeEquipment()
	{
		Json::Value data;
		if (!Json::GetObjectOrArray(m_data, "uds", data)) //二维数组,多组装备可一起合并
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		vector< vector<unsigned> > uds;
		for (unsigned i = 0; i < data.size(); ++i)
		{
			vector<unsigned> sub;
			for (unsigned j = 0; j < data[i].size(); ++j)
			{
				sub.push_back(data[i][j].asUInt());
			}
			uds.push_back(sub);
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.MergeEquipment(m_uid, uds, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		Json::FastWriter writer;
		CGI_SEND_LOG("action=MergeEquipment&uid=%u&equd=%s", m_uid, writer.write(data).c_str());
		return R_SUCCESS;
	}

	int Double11()
	{
		unsigned type = 0;
		unsigned id = 0;
		unsigned allserver = 0;

		if (!Json::GetUInt(m_data, "type", type) || !Json::GetUInt(m_data, "id", id))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		Json::GetUInt(m_data, "allserver", allserver);

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = 0;

		ret = logicCMD.Double11(m_uid, type, id, allserver, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=Double11&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetDouble11Rcnt()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned allserver = 0;

		Json::GetUInt(m_data, "allserver", allserver);

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = 0;

		ret = logicCMD.GetDouble11Rcnt(m_uid, allserver, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=Double11&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int Sell()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.Sell(m_uid, m_data, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=Sell&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int SellJuexue()
	{
		unsigned type = 0;
		unsigned isell = 0;

		if (!Json::GetUInt(m_data, "type", type) || !Json::GetUInt(m_data, "isell", isell))
		{
			return R_ERR_PARAM;
		}
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.SellJuexue(m_uid, type, isell, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=SellJuexue&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int CollectJuexue()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned type = 0;
		unsigned icoll = 0;

		if (!Json::GetUInt(m_data, "type", type) || !Json::GetUInt(m_data, "icoll", icoll))
		{
			return R_ERR_PARAM;
		}

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.CollectJuexue(m_uid, type, icoll, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=CollectJuexue&uid=%u");

		return R_SUCCESS;
	}


	int SynthJuexue()
	{
		unsigned type = 0;
		unsigned isynth = 0;
		unsigned iby = 0;

		if (!Json::GetUInt(m_data, "type", type)
		|| !Json::GetUInt(m_data, "isynth", isynth)
		|| !Json::GetUInt(m_data, "iby", iby))
		{
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.SynthJuexue(m_uid, type, isynth, iby, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=SynthJuexue&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int LoadJuexue()
	{
		// 0: load
		// 1: unload
		unsigned type = 0;
		unsigned ihero = 0;
		unsigned ibag = 0;
		unsigned heroud = 0;

		if (!Json::GetUInt(m_data, "type", type)
		|| !Json::GetUInt(m_data, "ihero", ihero)
		|| !Json::GetUInt(m_data, "ibag", ibag)
		|| !Json::GetUInt(m_data, "heroud", heroud))
		{
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.LoadJuexue(m_uid, type, heroud, ihero, ibag, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=LoadJuexue&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int LoadSynth()
	{
		unsigned type = 0;
		unsigned index = 0;
		unsigned heroud = 0;

		if (!Json::GetUInt(m_data, "type", type) || !Json::GetUInt(m_data, "index", index)
		|| !Json::GetUInt(m_data, "heroud", heroud))
		{
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.LoadSynth(m_uid, type, index, heroud, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=LoadSynth&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int HitEgg()
	{
		unsigned type = 0;
		unsigned index = 0;

		if (!Json::GetUInt(m_data, "type", type) || !Json::GetUInt(m_data, "index", index))
		{
			return R_ERR_PARAM;
		}


		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;

		int ret = logicCMD.HitEgg(m_uid, type, index, equd, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=HitEgg&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int RefreshHitEgg()
	{
		unsigned lock = 0;

		if (!Json::GetUInt(m_data, "lock", lock))
		{
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;

		int ret = logicCMD.RefreshHitEgg(m_uid, lock, equd, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=RefreshHitEgg&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int BetShop()
	{
		unsigned index = 0;
		unsigned eqid = 0;

		if (!Json::GetUInt(m_data, "index", index) || !Json::GetUInt(m_data, "eqid", eqid))
		{
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.BetShop(m_uid, index, eqid, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=BetShop&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GetWorldReward()
	{
		unsigned index;
		if (!Json::GetUInt(m_data, "index", index))
		{
			return R_ERR_PARAM;
		}
		unsigned eqid = 0;
		Json::GetUInt(m_data, "eqid", eqid);

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetWorldReward(m_uid, index, eqid, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GetWorldReward&uid=%u", m_uid);

		return R_SUCCESS;
	}
	int GetKillReward()
	{
		unsigned index;
		if (!Json::GetUInt(m_data, "index", index))
		{
			return R_ERR_PARAM;
		}
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetKillReward(m_uid, index, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GetKillReward&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetMedal()
	{
		unsigned index;

		if (!Json::GetUInt(m_data, "index", index))
		{
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned type = 0;
		Json::GetUInt(m_data, "type", type);

		CLogicCMD logicCMD;

		int ret = logicCMD.GetMedal(m_uid, type, index, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GetMedal&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int BuyQiRi()
	{
		unsigned index = 0;

		if (!Json::GetUInt(m_data, "index", index) || index == 0)
		{
			return R_ERR_PARAM;
		}

		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		ret = logicCMD.BuyQiRi(m_uid, index, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=BuyQiRi&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetQiRi()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		ret = logicCMD.GetQiRi(m_uid, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GetQiRi&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetGiftBagLvl()
	{

		unsigned id = 0;
		if (!Json::GetUInt(m_data, "id", id))
		{
			return R_ERR_PARAM;
		}

		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		ret = logicCMD.GetGiftBagLvl(m_uid, id, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GetGiftBagLvl&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetGiftBagVip()
	{
//		int ret = 0;
//		unsigned lasttime = 0;
//		unsigned seqid = 0;
//
//		Json::GetUInt(m_data, "lastime", lasttime);
//		Json::GetUInt(m_data, "seqid", seqid);
//
//		CLogicCMD logicCMD;
//		ret = logicCMD.GetGiftBagVip(m_uid, m_jsonResult, lasttime, seqid);
//		if (ret)
//		{
//			return ret;
//		}
//
//		CGI_SEND_LOG("action=GetGiftBagVip&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int FirstRechargeReward()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		ret = logicCMD.FirstRechargeReward(m_uid, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=FirstRechargeReward&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int SignInReward()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.SignInReward(m_uid, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=SignInReward&uid=%u", m_uid);

		return R_SUCCESS;
	}

    int GetInviteReward()
    {
        unsigned lasttime = 0;
        unsigned seqid = 0;
        unsigned rewardid = 0;

        Json::GetUInt(m_data, "lastime", lasttime);
        Json::GetUInt(m_data, "seqid", seqid);

        Json::GetUInt(m_data, "reward_id", rewardid);

        CLogicCMD logicCMD;
        int ret = logicCMD.GetInviteReward(m_uid, rewardid, m_jsonResult, lasttime, seqid);
        if (R_SUCCESS != ret)
        {
            return ret;
        }

        CGI_SEND_LOG("action=GetInviteReward&uid=%u", m_uid);

        return R_SUCCESS;
    }

    int DailyQuestReward()
    {
        unsigned lasttime = 0;
        unsigned seqid = 0;
        unsigned index = 0;
        unsigned type = 0;
        unsigned blue_torch_burning = 0;

        Json::GetUInt(m_data, "lastime", lasttime);
        Json::GetUInt(m_data, "seqid", seqid);

        Json::GetUInt(m_data, "index", index);
        Json::GetUInt(m_data, "type", type);

        Json::GetUInt(m_data, "blue_torch_burning", blue_torch_burning);

        CLogicCMD logicCMD;
        int ret = logicCMD.DailyQuestReward(m_uid, index, type != 0, bool(blue_torch_burning), m_jsonResult, lasttime, seqid);
        if (R_SUCCESS != ret)
        {
        	return ret;
        }

        CGI_SEND_LOG("action=DailyQuestReward&uid=%u", m_uid);

        return R_SUCCESS;
    }

    int VipGiftBag()
    {
    	unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned level = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		Json::GetUInt(m_data, "vip_level", level);

		CLogicCMD logicCMD;
		int ret = logicCMD.VipGiftBag(m_uid, level, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=VipGiftBag&uid=%u", m_uid);

		return R_SUCCESS;
    }

	int GrowthFund()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned is_buy = 0;
		if (!Json::GetUInt(m_data, "type", is_buy) ||
				((is_buy!=0) && (is_buy!=1)))
		{
			error_log("para type error");
			return R_ERR_PARAM;
		}

		unsigned count = 0;
		if (!Json::GetUInt(m_data, "count", count))
		{
			error_log("para count lost");
			return R_ERR_PARAM;
		}

		if ((1==is_buy) && (0==count))
		{
			error_log("logic error: buy nothing");
			return R_ERR_LOGIC;
		}
		if ((0==is_buy) && (count>0))
		{
			error_log("logic error: count must be 0");
			return R_ERR_LOGIC;
		}

		CLogicCMD logicCMD;
		ret = logicCMD.GrowthFund(m_uid, (bool)is_buy, count, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=GrowthFund&uid=%u", m_uid);

		return R_SUCCESS;
	}

    int IntensifyWeaponBySoul()
    {
    	unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned index = 0;
		unsigned type = 0;
		unsigned equipUId = 0;
		unsigned equipUId2 = 0;
		unsigned equipUId3 = 0;
		unsigned equipUId4 = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		Json::GetUInt(m_data, "index", index);
		Json::GetUInt(m_data, "type", type);
		Json::GetUInt(m_data, "equipUId", equipUId); //武魂凝露
		Json::GetUInt(m_data, "equipUId2", equipUId2);  //限时武魂凝露
		Json::GetUInt(m_data, "equipUId3", equipUId3);  //限级武魂凝露
		Json::GetUInt(m_data, "equipUId4", equipUId4);  //限级武魂凝露

		CLogicCMD logicCMD;
		int ret = 0;
		if (type == 0) //器魂
		{
			ret = logicCMD.IntensifyWeaponBySoul(m_uid, index, m_jsonResult, lasttime, seqid);
		}
		else //武魂凝露，钻石
		{
			ret = logicCMD.IntensifyWeaponBySoul(m_uid, index, equipUId2, equipUId, equipUId3, equipUId4, m_jsonResult, lasttime, seqid);
		}

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=IntensifyWeaponBySoul&uid=%u", m_uid);

		return R_SUCCESS;
    }

    int RechargeGiftBag()
    {
    	unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned id = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		Json::GetUInt(m_data, "id", id);

		CLogicCMD logicCMD;
		int ret = logicCMD.RechargeGiftBag(m_uid, id, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=RechargeGiftBag&uid=%u", m_uid);

		return R_SUCCESS;
    }

	int TencentPCManager()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned is_login_gift = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		if (!Json::GetUInt(m_data, "isLoginGift", is_login_gift))
		{
			error_log("para isLoginGift lost");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		if (is_login_gift)
		{
			ret = logicCMD.LoginGiftOfTencentPCManager(m_uid, m_jsonResult, lasttime, seqid);
		} else
		{
			ret = logicCMD.InstallGiftOfTencentPCManager(m_uid, m_jsonResult, lasttime, seqid);
		}
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=TencentPCManager&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int RecruitHero()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned zmlud = 0;
		string strhero;
		int index = -1;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		if (!Json::GetUInt(m_data, "zmlud", zmlud) || !Json::GetString(m_data, "heroid", strhero) || (! Json::GetInt(m_data, "index", index)) )
		{
			error_log("param error.");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		ret = logicCMD.RecruitHero(m_uid, strhero, m_jsonResult, zmlud, index, lasttime, seqid);

		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=RecruitHero&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int PreSummerExchange()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned id = 0;
		unsigned type = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "type", type);
		if (! Json::GetUInt(m_data, "id", id))
		{
			error_log("param error.");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		ret = logicCMD.PreSummerExchange(m_uid, id, type, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=PreSummerExchange&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int PreSummerCurPoint()
	{
		int ret = 0;
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned type = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "type", type);

		CLogicCMD logicCMD;

		ret = logicCMD.PreSummerCurPoint(m_uid, type, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=PreSummerCurPoint&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int DeDaoZhenRen()
	{
		unsigned lasttime = 0, seqid = 0,  person = 0, visit = 0;
		if(!Json::GetUInt(m_data, "person", person) ||
		   !Json::GetUInt(m_data, "visit", visit)   ||
		   !Json::GetUInt(m_data, "seqid", seqid)   ||
		   !Json::GetUInt(m_data, "lastime", lasttime))
		{
			error_log("para loss error");
			return R_ERR_PARAM;
		}
		//1) person 0(于吉), 1, 2, 3
		//2) visit (绘符 0， 拜访 1)
		if (person > 3 || visit > 1)
		{
			error_log("para value error");
			return R_ERR_PARAM;
		}
		if (visit && person != 3)
		{
			error_log("para value visit must match person");
			return R_ERR_PARAM;
		}

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = 0;
		if (visit)
		{
			ret = logicCMD.DeDaoZhenRenVisit(m_uid, m_jsonResult, seqid, lasttime);
		} else
		{
			ret = logicCMD.DeDaoZhenRenDrawPicture(m_uid, person, equd, m_jsonResult, seqid, lasttime);
		}
		if(ret)
			return ret;

		CGI_SEND_LOG("action=dedaozhenren&uid=%u&person=%u&visit=%u", m_uid, person, visit);
		return R_SUCCESS;
	}


	int QQPanelGiftBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.QQPanelGiftBag(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=QQPanelGiftBag&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int YellowDiamondNewUserGiftBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.YellowDiamondNewUserGiftBag(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=YellowDiamondNewUserGiftBag&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int YellowDiamondDailyGiftBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned yellow_level = 0;
		unsigned is_year = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		if (!Json::GetUInt(m_data, "yellow_level", yellow_level) ||
			!Json::GetUInt(m_data, "is_year", is_year) ||
			 yellow_level < 1 || yellow_level > 9 ||
			 is_year > 1)
		{
			error_log("para error: yellow_level or is_year");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.YellowDiamondDailyGiftBag(m_uid, yellow_level, bool(is_year), m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=YellowDiamondDailyGiftBag&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int BlueDiamondNewUserGiftBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.BlueDiamondNewUserGiftBag(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=BlueDiamondNewUserGiftBag&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int BlueDiamondDailyGiftBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned blue_level = 0;
		unsigned is_year = 0;
		unsigned is_luxury = 0;
		unsigned kinds_blue_gift = 0; 	//0:普通每日礼包, 1:豪华礼包,  2:年费礼包,  3:一键领取所有
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		if (!Json::GetUInt(m_data, "blue_level", blue_level) ||
			!Json::GetUInt(m_data, "is_year", is_year) ||
			!Json::GetUInt(m_data, "is_luxury", is_luxury) ||
			!Json::GetUInt(m_data, "kinds_blue_gift", kinds_blue_gift) ||
			blue_level < 1 || blue_level > 7 ||
			is_year > 1 ||
			is_luxury > 1 ||
			kinds_blue_gift > 3)
		{
			error_log("para error: blue_level or is_year or is_luxury or kinds_blue_gift");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = 0;
		if (3 == kinds_blue_gift)  //因为一键领取的逻辑和其它不同，所以单独分出来进行处理
		{
			ret = logicCMD.BlueDiamondDailyGiftBagOneKeyBackAll(m_uid, blue_level, bool(is_year), bool(is_luxury), m_jsonResult, lasttime, seqid);
		} else
		{
			ret = logicCMD.BlueDiamondDailyGiftBagSingle(m_uid, blue_level, bool(is_year), bool(is_luxury), kinds_blue_gift, m_jsonResult, lasttime, seqid);
		}
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=BlueDiamondDailyGiftBag&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GroupBuyDaily()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.GroupBuyDailyBuy(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GroupBuyDaily&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int GroupBuyReward()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: lack of index");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GroupBuyDailyReward(m_uid, index, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=GroupBuyReward&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int LittleRecharge()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.LittleRecharge(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=LittleRecharge&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int DailyRewardGC()
	{
		try
		{
			BaseCmdParams args(m_data);
			int ret = LogicCmdAction<DailyRewardUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&DailyRewardUnit::GetReward)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=DailyRewardGC&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int MonthGiftBag()
	{
		try
		{
			MonthGiftParams args(m_data);
			int ret = LogicCmdAction<MonthGiftBagUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&MonthGiftBagUnit::GetReward)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=MonthGiftBag&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int SelectKingdom()
	{
		try
		{
			KingdomSelectParams args(m_data);
			int ret = LogicCmdAction<KingdomSelectUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&KingdomSelectUnit::Select)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=SelectKingdom&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int CombinedShopBuy()
	{
		try
		{
			CombinedShopParams args(m_data);
			int ret = LogicCmdAction<CombinedShopUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&CombinedShopUnit::Buy)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=CombinedShopBuy&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int NewerAdvanceGet()
	{
		try
		{
			NewerAdvanceParams args(m_data);
			int ret = LogicCmdAction<NewerAdvanceUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&NewerAdvanceUnit::Get)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=NewerAdvanceGet&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int AthleticsReward()
	{
		try
		{
			BaseCmdParams args(m_data);
			int ret = LogicCmdAction<AthleticsRankUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&AthleticsRankUnit::GetReward)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=AthleticsReward&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int TreasureHuntExchange()
	{
		try
		{
			TreasureHuntExchangeParams args(m_data);
			int ret = LogicCmdAction<TreasureHuntUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&TreasureHuntUnit::Exchage)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=TreasureHuntExchange&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int ChristmasExchange()
	{
		try
		{
			ChristmasParams args(m_data);
			int ret = LogicCmdAction<ChristmasUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&ChristmasUnit::Exchage)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=ChristmasExchange&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int ChristmasKnockEgg()
	{
		try
		{
			ChristmasParams args(m_data);
			int ret = LogicCmdAction<ChristmasUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&ChristmasUnit::KnockEgg)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=ChristmasKnockEgg&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int PointExchange()
	{
		try
		{
			PointExchangeParams args(m_data);
			int ret = LogicCmdAction<PointExchangeUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&PointExchangeUnit::Exchage)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=Exchage&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int CutPriceBuy()
	{
		try
		{
			PointCutPriceBuyParams args(m_data);
			int ret = LogicCmdAction<PointCutPriceUnit>(
					  m_uid
					, false
					, args
					, reinterpret_cast<ActionImpl>(&PointCutPriceUnit::Buy)
					, m_jsonResult);
			if (R_SUCCESS != ret)
			{
				return ret;
			}

			CGI_SEND_LOG("action=CutPriceBuy&uid=%u", m_uid);
			return R_SUCCESS;
		}
		catch (const std::exception& e)
		{
			::SetError(R_ERROR, e.what());
			return R_ERROR;
		}

		return R_ERROR;
	}

	int DivinePower()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.DivinePower(m_uid, m_data,m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=DivinePower&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int StarStone()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.StarStone(m_uid, m_data,m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=StarStone&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EveryDayRecharge()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.EveryDayRecharge(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=EveryDayRecharge&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EveryDayOnline()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.EveryDayOnline(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=EveryDayOnline&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EnjoyStore()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.EnjoyStore(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=EnjoyStore&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int VipReward()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.VipReward(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}
		CGI_SEND_LOG("action=VipReward&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int YingLingNormal()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.YingLingNormal(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=YingLingNormal&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int YingLingAdvance()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.YingLingAdvance(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=YingLingAdvance&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int YingLingExp()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.YingLingExp(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=YingLingExp&uid=%u", m_uid);
		return R_SUCCESS;
	}
	int YingLingStar()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.YingLingStar(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=YingLingStar&uid=%u", m_uid);
		return R_SUCCESS;
	}

	//锤子领取
	CGI_ACTION_FUNCTION(HammerFreeGet, BaseCmdParams, HammerHitUnit, false, DrawHammer)
	//建筑场景
	CGI_ACTION_FUNCTION(BuildingSkinBuy, BuildingSkinBuyParams, BuildingSkinUint, false, Buy)
	CGI_ACTION_FUNCTION(BuildingSkinUse, BuildingSkinUseParams, BuildingSkinUint, false, Use)
	CGI_ACTION_FUNCTION(BuildingSkinRelet, BuildingSkinReletParams, BuildingSkinUint, false, Relet)
	//七日登录
	CGI_ACTION_FUNCTION(TutorLoginReward, UnitIdCmdParams, TutorLoginUnit, false, Reward)
	//霸业礼包
	CGI_ACTION_FUNCTION(ImperialGiftGet, BaseCmdParams, ImperialGiftUnit, false, Get)
	CGI_ACTION_FUNCTION(ImperialGiftOpen, ImperialGiftOpenParams, ImperialGiftUnit, false, Open)
	//限时冲级
	CGI_ACTION_FUNCTION(TimeLimitUpgradeReward, TimeLimitUpgradeRewardParams, TimeLimitUpgradeUnit, true, Reward)
	//跨服天梯
	CGI_ACTION_FUNCTION(CSLadderReward, BaseCmdParams, CServerladderUnit, true, Reward)
	//寒假狂欢
	CGI_ACTION_FUNCTION(WHRevelayDrawReward, WHRevelayDrawRewardParams, WinterHolidayRevelayUnit, false, DrawReward)
	CGI_ACTION_FUNCTION(WHRevelayGetReward, UnitIndexCmdParams, WinterHolidayRevelayUnit, false, GetReward)
	//鸡年纳福
	CGI_ACTION_FUNCTION(YearFortuneTransfer, BaseCmdParams,      YearFortuneUnit, false, Transfer)
	CGI_ACTION_FUNCTION(YearFortuneReward,   BaseCmdParams, YearFortuneUnit, false, Reward)
	CGI_ACTION_FUNCTION(YearFortuneInfo,   BaseCmdParams, YearFortuneUnit, false, Info)
	//塔楼外传
	CGI_ACTION_FUNCTION(TowerActReset, UnitIndexCmdParams, TowerActivityUnit, true, ResetImpl)
	CGI_ACTION_FUNCTION(TowerActTreasure,  TowerTreasureParams, TowerActivityUnit, false, TreasureImpl)
	CGI_ACTION_FUNCTION(TowerActOnce,   TowerOnceParams, TowerActivityUnit, false, OnceImpl)
	CGI_ACTION_FUNCTION(TowerActUnlock,   BaseCmdParams, TowerActivityUnit, false, UnlockFloorImpl)
	//信物强化
	CGI_ACTION_FUNCTION(TokenIntensifyList,     BaseCmdParams,      TokenIntensifyUnit, false, ListImpl)
	CGI_ACTION_FUNCTION(TokenIntensifyChgZone,  UnitIndexCmdParams, TokenIntensifyUnit, false, ExchangeZoneImpl)
	CGI_ACTION_FUNCTION(TokenIntensifyChgNormal,UnitIndexCmdParams, TokenIntensifyUnit, false, ExchangeCommonImpl)
	//世间秘宝
	CGI_ACTION_FUNCTION(WorldTreasureDraw,     BaseCmdParams,      WorldTreasureUnit, false, DrawImpl)
	CGI_ACTION_FUNCTION(WorldTreasureExtract,  WorldTreasureExtractParams, WorldTreasureUnit, false, ExtractImpl)
	//武魂回馈
	CGI_ACTION_FUNCTION(SoulFeedbackDraw, SoulFeedbackDrawParams, SoulFeedbackUnit, false, DrawImpl);
	//觉醒回馈
	CGI_ACTION_FUNCTION(AwakenFeedbackDraw, SoulFeedbackDrawParams, AwakenFeedbackUnit, false, DrawImpl);
	//铸魂打折
	CGI_ACTION_FUNCTION(CastSoulDraw, SoulFeedbackDrawParams, CastSoulUnit, false, DrawImpl);
	//宝石折扣
	CGI_ACTION_FUNCTION(GemDiscountDraw, UnitIndexCmdParams, GemDiscountUnit, false, DrawImpl);
	//幸运连连
	CGI_ACTION_FUNCTION(CheckInitial, BaseCmdParams, FortunatelyUnit, false, CheckInitial);
	CGI_ACTION_FUNCTION(RefreshLuckWheel, UnitUdCmdParams, FortunatelyUnit, false, RefreshWheel);
	CGI_ACTION_FUNCTION(FortuLottery, FortunatelyUnit::RewardParams, FortunatelyUnit, false, GetReward);
	//天命
	CGI_ACTION_FUNCTION(CheckTurnPlateInitial, BaseCmdParams, TurnPlateUnit, false, CheckInitial);
	CGI_ACTION_FUNCTION(RefreshTurnPlaeWheel,TurnPlateUnit::RefreshParams, TurnPlateUnit, false, RefreshWheel);
	CGI_ACTION_FUNCTION(TurnPlateLotty, TurnPlateUnit::RewardParams, TurnPlateUnit, false, GetReward);
	//天坛祈福
	CGI_ACTION_FUNCTION(TemplePray, TemplePrayUnit::PrayParams, TemplePrayUnit, false, Pray);
	//金玉满堂一键抽一次奖
	CGI_ACTION_FUNCTION(TreasuresAroundDraw, UnitUdCmdParams, TreasureAroundUnit, false, DrawImpl);
	//金玉满堂一键抽十次奖
	CGI_ACTION_FUNCTION(TreasuresAroundDrawTenTimes, UnitUdCmdParams, TreasureAroundUnit, false, DrawTenTimes);
	//星石置换
	CGI_ACTION_FUNCTION(StarStoneChange, BaseCmdParams, StarStoneChangeUnit, true, DrawImpl);
	//将灵培养
	CGI_ACTION_FUNCTION(SpiritFosterDraw, SpiritFosterUnit::DrawParams, SpiritFosterUnit, false, DrawImpl);
	//的卢凝魂
	CGI_ACTION_FUNCTION(ChargeHorseDraw, ChargeHorseUnit::DrawParams, ChargeHorseUnit, false, DrawImpl);
	//vicky又要做个充值活动
	CGI_ACTION_FUNCTION(VickyAccX, VickyAccXUnit::DrawParams, VickyAccXUnit, false, DrawImpl);
	//vicky又要做个充值活动1
	CGI_ACTION_FUNCTION(VickyAccX1, VickyAccXUnit1::DrawParams, VickyAccXUnit1, false, DrawImpl);
	//vicky又要做个充值活动2
	CGI_ACTION_FUNCTION(VickyAccX2, VickyAccXUnit2::DrawParams, VickyAccXUnit2, false, DrawImpl);
	//vicky又要做个充值活动3
	CGI_ACTION_FUNCTION(VickyAccX3, VickyAccXUnit3::DrawParams, VickyAccXUnit3, false, DrawImpl);
	//vicky又要做个充值活动4
	CGI_ACTION_FUNCTION(VickyAccX4, VickyAccXUnit4::DrawParams, VickyAccXUnit4, false, DrawImpl);
	//vicky又要做个充值活动5
	CGI_ACTION_FUNCTION(VickyAccX5, VickyAccXUnit5::DrawParams, VickyAccXUnit5, false, DrawImpl);
	//机甲黄忠
	CGI_ACTION_FUNCTION(huangzhong, huangzhongUnit::DrawParams, huangzhongUnit, false, DrawImpl);
	//vicky的开服活动
	CGI_ACTION_FUNCTION(VickyNewOpen, VickyNewOpenUnit::DrawParams, VickyNewOpenUnit, false, DrawImpl);
	//
	CGI_ACTION_FUNCTION(chongzhizixuan, BaseCmdParams, ChongZhiZiXuan, false, DrawImpl);

	/********************************************************************/
	/*  活动太多  先是抽象成模板  最后只能搞宏       */
#define CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_NAME) \
	CGI_ACTION_FUNCTION(CONFIG_NAME##_ACT, CONFIG_NAME##_Unit::DrawParams, CONFIG_NAME##_Unit, false, DrawImpl);
	/********************************************************************/
//autolable8
CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_fuzhuhesui)
CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_zhuniandaji)
CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_vicky_qingrenjie)
CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_yuandan2018)
CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_yearend2018)
CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_winter2018)
CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_double11_2018)
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_mid_aug_hao)
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_mid_aug_reu)
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_water_taotie)
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_water_qilin)
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_water_pheonix)
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_vicky_nnom)
	//vicky没想好名字的活动
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_VICKY_NO_NAME)
	//兵书突破活动
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_VICKY_BINGSHU)
	//千服同庆
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_VICKY_QIANFU)
	//vicky懒得给我说名字的活动
	CHARGE_DRAW_ACT_ACTION_FUNCTION(CONFIG_VICKY_NNA)

	//兑换自选
	CGI_ACTION_FUNCTION(free_exchg, BaseCmdParams, FreeExchangeUnit, false, DrawImpl);
	///////////////////////////////////////////////////////////////


	int NewRechargeBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned id = 0;
		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("param error: lack of id");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.NewRecharge(m_uid, id, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=NewRechargeBag&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int BlueDiamondLevelGiftBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.BlueDiamondLevelGiftBag(m_uid, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=BlueDiamondLevelGiftBag&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int NewJueshiWuShuang()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned id = 0;

		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("param error: lack of id");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.GetNewJueshiWushuang(m_uid, id, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=NewJueshiWuShuang&uid=%u,id=%u", m_uid, id);
		return R_SUCCESS;
	}

	int SynthSoldierSkill()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: lack of type");
			return R_ERR_PARAM;
		}

		unsigned equd = 0;
		if(!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: lack of equd");
			return R_ERR_PARAM;
		}

		if (!m_data.isMember("material") || !m_data["material"].isArray())
		{
			error_log("param error: lack of material or material's type is not array");
			return R_ERR_PARAM;
		}

		unsigned expud = 0;
		Json::GetUInt(m_data, "expud", expud);
		unsigned expcount = 0;
		Json::GetUInt(m_data, "expcount", expcount);

		CLogicCMD logicCMD;

		int ret = logicCMD.SynthSoldierSkill(m_uid, equd, type, m_data["material"], m_jsonResult, lasttime, seqid, Soldier, expud, expcount);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=synthsoldierskill&uid=%u,equd=%u", m_uid, equd);
		return R_SUCCESS;
	}


	int SynthKingdomWar()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: lack of type");
			return R_ERR_PARAM;
		}

		unsigned equd = 0;
		if(!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: lack of equd");
			return R_ERR_PARAM;
		}

		if (!m_data.isMember("material") || !m_data["material"].isArray())
		{
			error_log("param error: lack of material or material's type is not array");
			return R_ERR_PARAM;
		}

		unsigned expud = 0;
		Json::GetUInt(m_data, "expud", expud);
		unsigned expcount = 0;
		Json::GetUInt(m_data, "expcount", expcount);

		CLogicCMD logicCMD;

		int ret = logicCMD.SynthSoldierSkill(m_uid, equd, type, m_data["material"], m_jsonResult, lasttime, seqid, KingdomWar, expud, expcount);

		if (R_SUCCESS != ret)
		{
			error_log("[SynthKingdomWar] not success");
			return ret;
		}

		CGI_SEND_LOG("action=synthkingdomwar&uid=%u,equd=%u", m_uid, equd);
		return R_SUCCESS;
	}



	int FeedToken()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0;

		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: lack of equd");
			return R_ERR_PARAM;
		}

		if (!m_data.isMember("material") || !m_data["material"].isArray())
		{
			error_log("param error: lack of material or material's type is not array");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.FeedToken(m_uid, equd, m_data["material"], m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=feedToken&uid=%u,equd=%u", m_uid, equd);
		return R_SUCCESS;
	}

	int LordWorship()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		int id = 0;
		int type = 0;

		if (!Json::GetInt(m_data, "id", id) || ! Json::GetInt(m_data, "type", type))
		{
			return R_ERR_PARAM;
		}


		CLogicCMD logicCMD;
		int ret = logicCMD.LordWorship(m_uid, id, type, m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=LordWorship&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int OpporKnock()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned times = 0;

		if (!Json::GetUInt(m_data, "times", times) || !m_data.isMember("exclude"))
		{
			error_log("param error: lack of times or exclude");
			return R_ERR_PARAM;
		}

		unsigned equd = 0;
		Json::GetUInt(m_data, "equd", equd);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetOpportunityKnockReward(m_uid, times, equd, m_data["exclude"], m_jsonResult, lasttime, seqid);
		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=opporknock&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int RechargeOptional()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		if (!m_data.isMember("ids") || !m_data["ids"].isArray())
		{
			error_log("param error: lack of ids or ids type not array");
			return R_ERR_PARAM;
		}
		if (!m_data.isMember("rewardcnt"))
		{
			error_log("param error: lack of rewardcnt");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		unsigned rewardcnt = 0;
		Json::GetUInt(m_data, "rewardcnt", rewardcnt);
		int ret = logicCMD.GetRechargeOptionalReward(m_uid,rewardcnt,m_data["ids"], m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=RechargeOptional&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int RechargeSendUpgrade()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0, heroud = 0;

		if (!Json::GetUInt(m_data, "index", index) || !Json::GetUInt(m_data, "heroud", heroud) )
		{
			error_log("param error: lack of index or heroud");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.UpgradeHeroForRecharge(m_uid, index, heroud, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=RechargeSendUpgrade&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int StartHeroTrain()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0, heroud = 0, blv = 0;

		if (!Json::GetUInt(m_data, "index", index) || !Json::GetUInt(m_data, "hud", heroud) || !Json::GetUInt(m_data, "blv", blv) )
		{
			error_log("param error: lack of index or hud or blv");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.StartHeroTrain(m_uid, index, heroud, blv, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=startherotrain&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ImproveTrain()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned tindex = 0, equd = 0;

		if (!Json::GetUInt(m_data, "tindex", tindex) || !Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: lack of tindex or equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.ImroveHeroTrainExp(m_uid, equd, tindex, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=improvetrain&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EndHeroTrain()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned tindex = 0, type = 0;

		if (!Json::GetUInt(m_data, "tindex", tindex) || !Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: lack of tindex or type");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.EndHeroTrain(m_uid, type, tindex, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=endherotrain&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int StartSoldierTrain()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned count = 0, type = 0, costtype= 0;
		string sid;


		if (!Json::GetUInt(m_data, "count", count) || !Json::GetUInt(m_data, "type", type) || !Json::GetString(m_data, "sid", sid) || sid.empty())
		{
			error_log("param error: lack of count or type or sid");
			return R_ERR_PARAM;
		}

		Json::GetUInt(m_data, "costtype", costtype);

		CLogicCMD logicCMD;

		int ret = logicCMD.StartSoldierTrain(m_uid, sid, count, type, costtype, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=startsoldiertrain&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EndSoldierTrain()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned bindex = 0, type = 0;

		if (!Json::GetUInt(m_data, "index", bindex) || !Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: lack of index or type");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.EndSoldierTrain(m_uid, type, bindex, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=endsoldiertrain&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int StartSoldierResearch()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned rlevel = 0, type = 0, costtype = 0;
		string sid;

		if (!Json::GetUInt(m_data, "rlevel", rlevel) || !Json::GetUInt(m_data, "type", type) || !Json::GetString(m_data, "sid", sid) || sid.empty())
		{
			error_log("param error: lack of count or type or sid");
			return R_ERR_PARAM;
		}

		Json::GetUInt(m_data, "costtype", costtype);

		CLogicCMD logicCMD;

		int ret = logicCMD.StartSoldierResearch(m_uid, sid, rlevel, type, costtype, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=startsoldierresearch&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int CancelSoldierResearch()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		string sid;

		if (!Json::GetString(m_data, "sid", sid) || sid.empty())
		{
			error_log("param error: lack of sid");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.CancelSoldierResearch(m_uid, sid, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=cancelsoldierresearch&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EndSoldierResearch()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned type = 0;
		string sid;

		if (!Json::GetUInt(m_data, "type", type) || !Json::GetString(m_data, "sid", sid) || sid.empty())
		{
			error_log("param error: lack of type or sid");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.EndSoldierResearch(m_uid, sid, type, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=endsoldierresearch&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int InnateSkillUp()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned heroud = 0;

		if (!Json::GetUInt(m_data, "hud", heroud))
		{
			error_log("param error: lack of hud");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.UpgradeInnateSkill(m_uid, heroud, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=innateskillup&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int StartSkillTrain()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned heroud = 0, sectime = 0, costpro = 0;
		string skid;

		if (!Json::GetUInt(m_data, "hud", heroud) || !Json::GetString(m_data, "skid", skid) || !m_data.isMember("equds") || !m_data["equds"].isArray()
			|| !Json::GetUInt(m_data, "sec", sectime) || !Json::GetUInt(m_data, "costpro", costpro))
		{
			error_log("param error: lack of hud, skid, equds, sec, costpro");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.StartSkillTrain(m_uid, heroud, skid, m_data, sectime, costpro, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=StartskillTrain&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int EndSkillTrain()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0, type = 0;

		if (!Json::GetUInt(m_data, "sindex", index) || !Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: lack of sindex, type");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.EndSkillTrain(m_uid, index, type, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=EndskillTrain&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int HeavendaoSkillup()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0, type = 0, equd = 0;


		if (!Json::GetUInt(m_data, "index", index) || !Json::GetUInt(m_data, "type", type) || !Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: lack of index, type, equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.UpgradeHevenDaoSkill(m_uid, index, type, equd, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=HeavendaoSkillup&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int CalcuteFairybag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.CalcuteFairyBag(m_uid, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=CalcuteFairybag&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ReceiveFairyReward()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		unsigned type = 0;

		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: lack of type");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.GetFairyBagReward(m_uid, type, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=ReceiveFairyReward&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int HouHuiYouQi()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned b_index = 0, s_index = 0;
		if (!Json::GetUInt(m_data, "b_index", b_index) || !b_index ||
			!Json::GetUInt(m_data, "s_index", s_index) || !s_index)
		{
			error_log("param error: lack of index");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.HouHuiYouQi(m_uid, b_index, s_index, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HouHuiYouQi&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int BigHarvestRewardCoins()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		Json::Value bid_arr;
		if (!Json::GetArray(m_data, "bid", bid_arr))
		{
			error_log("param bid error");
			return R_ERR_PARAM;
		}

		unsigned fcm = 0;
		Json::GetUInt(m_data,"fcm",fcm);
		if(fcm >= e_fcm_max)
			return R_ERR_PARAM;

		CLogicCMD logicCMD;
		int ret = logicCMD.BigHarvestRewardCoins(m_uid, bid_arr, fcm, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=BigHarvestRewardCoins&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int MoneyTreeRewardCoins()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned fcm = 0;
		Json::GetUInt(m_data,"fcm",fcm);
		if(fcm >= e_fcm_max)
			return R_ERR_PARAM;

		CLogicCMD logicCMD;
		int ret = logicCMD.MoneyTreeRewardCoins(m_uid, fcm, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=BigHarvestRewardCoins&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int ChaoZhiZheKou()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned b_index = 0, s_index = 0;
		if (!Json::GetUInt(m_data, "b_index", b_index) ||
			!Json::GetUInt(m_data, "s_index", s_index))
		{
			error_log("param error: lack of index");
			return R_ERR_PARAM;
		}

		if (b_index < 1 || b_index > CHAOZHIZHEKOU_BIG_TALBE_NUM ||
			s_index < 1 || s_index > CHAOZHIZHEKOU_SMALL_TALBE_NUM)
		{
			error_log("param error: index out of range");
			return R_ERR_PARAM;
		}

		unsigned count = 1;
		Json::GetUInt(m_data, "count", count);

		CLogicCMD logicCMD;
		int ret = logicCMD.ChaoZhiZheKou(m_uid, b_index, s_index, count, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ChaoZhiZheKou&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int YueHuiJuXian()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned b_index = 0, s_index = 0;
		if (!Json::GetUInt(m_data, "b_index", b_index) ||
			!Json::GetUInt(m_data, "s_index", s_index))
		{
			error_log("param error: lack of index");
			return R_ERR_PARAM;
		}
		if (b_index < 1 || b_index > YUEHUIJUXIAN_BIG_TALBE_NUM ||
			s_index < 1 || s_index > YUEHUIJUXIAN_SMALL_TALBE_NUM)
		{
			error_log("param error: index out of range");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.YueHuiJuXian(m_uid, b_index, s_index, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=YueHuiJuXian&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int LimitBuyOfZone()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: lack of index");
			return R_ERR_PARAM;
		}
		if (index > LIMITBUYOFZONE_TALBE_NUM || !index)
		{
			error_log("param error: index out of range");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.LimitBuyOfZone(m_uid, index, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=LimitBuyOfZone&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FiveDefendGrow()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order))
		{
			error_log("param error: lack of order");
			return R_ERR_PARAM;
		}
		if (order > 5 || !order)
		{
			error_log("param error: order out of range");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.FiveDefendGrow(m_uid, order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FiveDefendGrow&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FiveAttackGrow()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.FiveAttackGrow(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FiveAttackGrow&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FiveAttackActivity()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.FiveAttackActivity(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FiveAttackActivity&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int CountryDayLogin()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order))  //1: 每天, 2: 5天, 3: 7天
		{
			error_log("param error: lack of order");
			return R_ERR_PARAM;
		}
		if (order > COUNTRY_DAY_LOGIN_KINDS || !order)
		{
			error_log("param error: order out of range");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.CountryDayLogin(m_uid, order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=CountryDayLogin&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int CountryDayShop()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order))
		{
			error_log("param error: lack of order");
			return R_ERR_PARAM;
		}
		if (order > MAX_COUNTRY_DAY_SHOP_ITEMS || !order)
		{
			error_log("param error: order out of range");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.CountryDayShop(m_uid, order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=CountryDayShop&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ResetCountryDayShop()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.ResetCountryDayShop(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ResetCountryDayShop&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int CountryDayBag()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order))
		{
			error_log("param error: lack of order");
			return R_ERR_PARAM;
		}
		if (order > MAX_COUNTRY_DAY_BAG_ITEMS || !order)
		{
			error_log("param error: order out of range");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.CountryDayBag(m_uid, order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=CountryDayBag&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int HeartbeatBigSale()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0, count = 0;
		if (!Json::GetUInt(m_data, "order", order) || !Json::GetUInt(m_data, "count", count) ||
			 order > HEART_BEAT_BIG_SALE_ITEM_NUM || !order || !count)
		{
			error_log("param error: order or count");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.HeartbeatBigSale(m_uid, order, count, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HeartbeatBigSale&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int HeartbeatBigSaleReset()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned reset = 0;  //1代表重置
		if (!Json::GetUInt(m_data, "reset", reset) || !reset)
		{
			error_log("param error: reset");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.HeartbeatBigSaleReset(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HeartbeatBigSaleReset&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FiveBigSaleShop()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0, count = 0;
		if (!Json::GetUInt(m_data, "order", order) || !Json::GetUInt(m_data, "count", count) ||
			 !order || order > MAX_FIVE_SPECIAL_SHOP_ITEMS ||
			 !count)    //count的最大值 最后在配置中进行校验
		{
			error_log("param error: order or count");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.FiveBigSaleShop(m_uid, order, count, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FiveBigSaleShop&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FiveCouponShop()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0, count = 0;
		if (!Json::GetUInt(m_data, "order", order) || !Json::GetUInt(m_data, "count", count) ||
			 !order || order > MAX_FIVE_DISCOUNT_SHOP_ITEMS ||
			 !count)    //count的最大值 最后在配置中进行校验
		{
			error_log("param error: order or count");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.FiveCouponShop(m_uid, order, count, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FiveCouponShop&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FiveShopReset()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.FiveShopReset(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FiveShopReset&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ChongZhiHuiKui()
	{
		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.ChongZhiHuiKui(m_uid, index, type, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=ChongZhiHuiKui&uid=%u", m_uid);

		return R_SUCCESS;
	}
	int JinQiuShiYue()
	{
		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.JinQiuShiYue(m_uid, index, type, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=JinQiuShiYue&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ZhiZunBaoXiang()
	{
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
			return R_ERR_PARAM;

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.ZhiZunBaoXiang(m_uid, type, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=ZhiZunBaoXiang&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int JueXingTeHui()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0, count = 0;
		if (!Json::GetUInt(m_data, "order", order) || !Json::GetUInt(m_data, "count", count) ||
			 !order  || !count)
		{
			error_log("param error: order or count");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.JueXingTeHui(m_uid, order, count, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JueXingTeHui&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int JueXingTeHuiReset()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.JueXingTeHuiReset(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JueXingTeHuiReset&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FuDai()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order) ||
			!order || order > FUDAI_BAG_KINDS)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.FuDai(m_uid, order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FuDai&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FreeExchange()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order) || !order)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}
		unsigned ud_left = 0, ud_right = 0;
		Json::GetUInt(m_data, "ud_left", ud_left);
		Json::GetUInt(m_data, "ud_right", ud_right);
		if (!ud_left && !ud_right)
		{
			error_log("param error: must be one ud above zero");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.FreeExchange(m_uid, order, ud_left, ud_right, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FreeExchange&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int FreeExchangeReset()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.FreeExchangeReset(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FreeExchangeReset&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int JiFenDuiHuan()
	{
		unsigned id = 0;
		if (!Json::GetUInt(m_data, "id", id))
			return R_ERR_PARAM;

		unsigned lasttime = 0;
		unsigned seqid = 0;

		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.JiFenDuiHuan(m_uid, id, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=JiFenDuiHuan&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int DoubleEleven()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned big_order = 0, small_order = 0;
		if (!Json::GetUInt(m_data, "big_order", big_order) || !Json::GetUInt(m_data, "small_order", small_order) ||
			 !big_order  || !small_order)
		{
			error_log("param error: big_order or small_order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.DoubleEleven(m_uid, big_order, small_order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=DoubleEleven&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int DoubleElevenReset()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.DoubleElevenReset(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=DoubleElevenReset&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int JuBaoXiaGetKey()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order) ||
			!order || order > JUBAOXIA_GET_KEY_CHANNEL_KINDS)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = 0;
		if (1 == order)
		{
			ret = logicCMD.JuBaoXiaDailyGetLantian(m_uid, m_jsonResult, lasttime, seqid);
		} else if (2 == order)
		{
			unsigned ud = 0;
			if (!Json::GetUInt(m_data, "ud", ud))
			{
				error_log("param error: ud");
				return R_ERR_PARAM;
			}
			ret = logicCMD.JuBaoXiaExchange(m_uid, ud, m_jsonResult, lasttime, seqid);
		} else
		{
			ret = logicCMD.JuBaoXiaGetKey(m_uid, order, m_jsonResult, lasttime, seqid);
		}
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JubBaoXiaGetKey&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int JuBaoXiaGetTreasure()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned order = 0;
		if (!Json::GetUInt(m_data, "order", order) ||
			!order || order > JUBAOXIA_TREASURE_CNT)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		unsigned ud = 0;
		if (!Json::GetUInt(m_data, "ud", ud))
		{
			error_log("param error: ud");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.JuBaoXiaGetTreasure(m_uid, order, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JubBaoXiaGetTreasure&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int JuBaoXiaGetTreasureOneKey()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		Json::Value orders;
		if(!Json::GetArray(m_data, "orders", orders) ||
			orders.size() > JUBAOXIA_TREASURE_CNT)
		{
			error_log("param error: orders");
			return R_ERR_PARAM;
		}

		unsigned ud = 0;
		if (!Json::GetUInt(m_data, "ud", ud))
		{
			error_log("param error: ud");
			return R_ERR_PARAM;
		}
		CLogicCMD logicCMD;
		int ret = logicCMD.JuBaoXiaGetTreasureOneKey(m_uid, orders, ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JubBaoXiaGetTreasureOneKey&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int JuBaoXiaReset()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.JuBaoXiaReset(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JubBaoXiaReset&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int HeavenStep()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.HeavenStep(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HeavenStep&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int DaoistStep()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.DaoistStep(m_uid, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=DaoistStep&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int ZhenBaoGeHero()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned big_order = 0, small_order = 0;
		if (!Json::GetUInt(m_data, "big_order", big_order) || !big_order || big_order > ZHENBAOGEHERO_BIG_NUM ||
			!Json::GetUInt(m_data, "small_order", small_order) || !small_order || small_order > ZHENBAOGEHERO_SMALL_NUM)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.ZhenBaoGeHero(m_uid, big_order, small_order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ZhenBaoGeHero&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int ZhenBaoGeBuilding()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned big_order = 0, small_order = 0;
		if (!Json::GetUInt(m_data, "big_order", big_order) || !big_order || big_order > ZHENBAOGEBUILDING_BIG_NUM ||
			!Json::GetUInt(m_data, "small_order", small_order) || !small_order || small_order > ZHENBAOGEBUILDING_SMALL_NUM)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.ZhenBaoGeBuilding(m_uid, big_order, small_order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ZhenBaoGeBuilding&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetPartStone()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetPartStone(m_uid, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetPartStone&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int HeroStoneStep()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned order = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		if (!Json::GetUInt(m_data, "order", order) || !order || order > HEROSTONESTEP_ITEM_CNT)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.HeroStoneStep(m_uid, order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HeroStoneStep&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int BuildingStoneStep()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned order = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);
		if (!Json::GetUInt(m_data, "order", order) || !order || order > BUILDINGSTONESTEP_ITEM_CNT)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.BuildingStoneStep(m_uid, order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=BuildingStoneStep&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ProcessTribute()
	{
		unsigned id;
		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("para id error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		unsigned fcm = 0;
		Json::GetUInt(m_data,"fcm",fcm);
		if(fcm >= e_fcm_max)
			return R_ERR_PARAM;

		CLogicCMD logicCMD;
		int ret = logicCMD.ProcessTribute(m_uid, id, fcm, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ProcessTribute&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int JinQiuNovember()
	{
		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.JinQiuNovember(m_uid, index, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=JinQiuNovember&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int AcchargeBackShenwen()
	{
		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
			return R_ERR_PARAM;

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.AcchargeBackShenwen(m_uid, index, m_jsonResult, lasttime, seqid);
		if (ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=AcchargeBackShenwen&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int MeltEquip()
	{
		unsigned ud1 = 0, ud2 = 0, ud3 = 0, lvl = 0, spirit = 0;
		if(!Json::GetUInt(m_data, "ud1", ud1)
		|| !Json::GetUInt(m_data, "ud2", ud2)
		|| !Json::GetUInt(m_data, "ud3", ud3)
		|| !Json::GetUInt(m_data, "lvl", lvl)
		|| !Json::GetUInt(m_data, "spirit", spirit))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);

		CLogicCMD logicCMD;
		int ret = logicCMD.MeltEquip(m_uid, ud1, ud2, ud3, lvl, spirit, m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=MeltEquip&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int HeroGrowStep()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned hero_ud = 0;
		if (!Json::GetUInt(m_data, "heroud", hero_ud))
		{
			error_log("param error: hero_ud");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.HeroGrowStep(m_uid, hero_ud, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HeroGrowStep&uid=%u", m_uid);

		return R_SUCCESS;
	}


	int GrowDevelopGet()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned big_order = 0, small_order = 0;
		if (!Json::GetUInt(m_data, "big_order", big_order) || !big_order || big_order > HEROGROWDEVELOP_BIG_CNT ||
			!Json::GetUInt(m_data, "small_order", small_order) || !small_order || small_order > HEROGROWDEVELOP_SMALL_CNT)
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GrowDevelopGet(m_uid, big_order, small_order, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=GrowDevelopGet&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int DailyChargeCoin()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetDailyChargeCoinReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=DailyChargeCoin&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int CheckTreasureVer()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.CheckTreasureVersion(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=CheckTreasureVer&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int RefreshTreasure()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.RefreshTreasureBox(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=RefreshTreasure&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int LotteryTreasure()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.LotteryTreasureBoxReward(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=LotteryTreasure&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int LotteryMultiTreasure()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.LotteryMultiTreasureBoxReward(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=LotteryMultiTreasure&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KeepsakeOnceProduce()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0;

		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.OnceKeepsakeProduce(m_uid, equd, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KeepsakeOnceProduce&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KeepsakeOnekeyProduce()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0, times = 0;

		if (!Json::GetUInt(m_data, "equd", equd) || !Json::GetUInt(m_data, "times", times))
		{
			error_log("param error: equd,times");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.OneKeyKeepsakeProduce(m_uid, equd, times, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KeepsakeOnekeyProduce&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KeepsakeOneKeyFullLevel()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned ud_hero_post = 0;
		unsigned ud_keepsake = 0;

		if (!Json::GetUInt(m_data, "ud_hero_post", ud_hero_post) ||
			!Json::GetUInt(m_data, "ud_keepsake", ud_keepsake))
		{
			error_log("param error: ud_hero_post, ud_keepsake");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.KeepsakeOneKeyFullLevel(m_uid, ud_hero_post, ud_keepsake, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=keepsakeonekeyfulllevel&uid=%u", m_uid);

		return R_SUCCESS;

	}

	int KeepsakeSummon()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.SummonNPC(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KeepsakeSummon&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KeepsakeSold()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0;

		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.OneKeySoldDefective(m_uid, equd, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KeepsakeSold&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KeepsakeFeed()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0;
		unsigned convertud = 0;

		if (!Json::GetUInt(m_data, "equd", equd) || !Json::GetUInt(m_data, "convertud", convertud) )
		{
			error_log("param error: equd or convertud");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.FeedKeepsake(m_uid, equd, convertud, m_data["feeded"], m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KeepsakeFeed&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ChargeFeedbackHeaven()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetChargeFeedbackHeavenReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=ChargeFeedbackHeaven&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ChargeFeedbackDaoist()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetChargeFeedbackDaoistReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=ChargeFeedbackDaoist&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int CelebrateNewYear()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: order");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetCelebrateNewYearReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=CelebrateNewYear&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int VickyAcc()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: index");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.VickyAcc(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=VickyAcc&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetXinWuFB()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: index");
			return R_ERR_PARAM;
		}
		unsigned pay = 0;
		if (!Json::GetUInt(m_data, "pay", pay))
		{
			error_log("param error: pay");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetXinWuFB(m_uid, index, pay, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetXinWuFB&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int TowerStepUp()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned bdid = 0;
		if (!Json::GetUInt(m_data, "bdid", bdid))
		{
			error_log("param error: bdid");
			return R_ERR_PARAM;
		}
		unsigned equd = 0;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.TowerStepUp(m_uid, bdid, equd, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=TowerStepUp&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int TowerUnlock()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned bdid = 0;
		if (!Json::GetUInt(m_data, "bdid", bdid))
		{
			error_log("param error: bdid");
			return R_ERR_PARAM;
		}
		unsigned equd = 0;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.TowerUnlock(m_uid, bdid, equd, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=TowerUnlock&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int CheckPayOptionVer()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.CheckPayOptionVersion(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=CheckPayOptionVer&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int PayOptionReward()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		if (!m_data.isMember("choices") || !m_data["choices"].isArray())
		{
			error_log("param error: choices");
			return R_ERR_PARAM;
		}
		if (!m_data.isMember("rewardcnt"))
		{
			error_log("param error: rewardcnt");
			return R_ERR_PARAM;
		}
		unsigned rewardcnt;
		Json::GetUInt(m_data, "rewardcnt", rewardcnt);
		CLogicCMD logicCMD;
		int ret = logicCMD.GetPayOptionalReward(m_uid, rewardcnt,m_data["choices"], m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=PayOptionReward&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int EquipStrengthenVersion()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.CheckEquipStrengthenVersion(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=EquipStrengthenVersion&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int EquipStrengthenReward()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;

		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: index");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetStrengthenChargeReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=EquipStrengthenReward&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int UpGradeBNW()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.UpGradeBNW(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=UpGradeBNW&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int FastUpGradeBNW()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.FastUpGradeBNW(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=FastUpGradeBNW&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int UpGradeBNWTech()
	{
		unsigned ud = 0;
		Json::GetUInt(m_data, "ud", ud);

		unsigned job = 0;
		if (!Json::GetUInt(m_data, "job", job))
		{
			error_log("param error: job");
			return R_ERR_PARAM;
		}
		unsigned type = 0;
		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: type");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.UpGradeBNWTech(m_uid, ud, job, type, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=UpGradeBNWTech&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int FastUpGradeBNWTech()
	{
		unsigned job = 0;
		if (!Json::GetUInt(m_data, "job", job))
		{
			error_log("param error: job");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.FastUpGradeBNWTech(m_uid, job, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=FastUpGradeBNWTech&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int HequCharge()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;

		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: index");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetHequChargeReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=HequCharge&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int HequVIP()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned vindex = 0, subindex = 0;

		if (!Json::GetUInt(m_data, "vindex", vindex) || !Json::GetUInt(m_data, "subindex", subindex))
		{
			error_log("param error: vindex or subindex");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetHequVIPeward(m_uid, vindex, subindex, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=HequVIP&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int HequBuchang()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);


		unsigned index = 0;

		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: index");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;
		int ret = logicCMD.GetHequRecompenseReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=HequBuchang&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int HequBuzhu()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.GetHequBuzhuReward(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=HequBuzhu&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int Learjyt()
	{
		unsigned ud = 0;
		if (!Json::GetUInt(m_data, "ud", ud))
		{
			error_log("param error: ud");
			return R_ERR_PARAM;
		}
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.Learjyt(m_uid, ud, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=Learjyt&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int LearnJM()
	{
		unsigned ud = 0;
		if (!Json::GetUInt(m_data, "ud", ud))
		{
			error_log("param error: ud");
			return R_ERR_PARAM;
		}
		unsigned id = 0;
		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("param error: id");
			return R_ERR_PARAM;
		}
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;
		int ret = logicCMD.LearnJM(m_uid, ud, id, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=LearnJM&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int LoadScrollActivity()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.LoadScrollActivity(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=LoadScrollActivity&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int CompleteAffair()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned type = 0;

		if (!Json::GetUInt(m_data, "type", type))
		{
			error_log("param error: type");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.CompleteAffair(m_uid, type, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=CompleteAffair&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int GetActiveReward()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned index = 0;

		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("param error: index");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.GetActiveReward(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=GetActiveReward&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KingTreasureOpen()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned equd = 0;

		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("param error: equd");
			return R_ERR_PARAM;
		}

		CLogicCMD logicCMD;

		int ret = logicCMD.OpenKingTreasure(m_uid, equd, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KingTreasureOpen&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KingTreasureReceive()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.ReceiveKingTreasure(m_uid, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KingTreasureReceive&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int KingTreasureRecycle()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		int ret = logicCMD.RecycleKingTreasure(m_uid,  m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=KingTreasureRecycle&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ReceiveScrollFeedback()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		unsigned index = 0;

		Json::GetUInt(m_data, "index", index);

		int ret = logicCMD.ReceiveScrollFeedback(m_uid, index, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=ReceiveScrollFeedback&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int ReceiveSevenGift()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		CLogicCMD logicCMD;

		unsigned type = 0;

		Json::GetUInt(m_data, "type", type);

		int ret = logicCMD.ReceiveSevenDayAwaken(m_uid, type, m_jsonResult, lasttime, seqid);

		if(ret)
			return ret;

		CGI_SEND_LOG("action=ReceiveSevenGift&uid=%u", m_uid);

		return R_SUCCESS;
	}

	int HeroExtraStone()
	{
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned equd;
		if (!Json::GetUInt(m_data, "equd", equd))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned index;
		if (!Json::GetUInt(m_data, "index", index))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.HeroExtraStone(m_uid,heroud,equd,index,m_jsonResult,lasttime,seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=HeroExtraStone&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int FashionStar()
	{
		unsigned id;
		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned ud;
		if (!Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned id1;
		if (!Json::GetUInt(m_data, "id1", id1))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned ud1;
		if (!Json::GetUInt(m_data, "ud1", ud1))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned id2;
		if (!Json::GetUInt(m_data, "id2", id2))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned ud2;
		if (!Json::GetUInt(m_data, "ud2", ud2))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}

		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.FashionStar(m_uid, id, ud, id1, ud1, id2, ud2, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=FashionStar&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int CommderSkilLearn()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned heroud = 0,equd = 0;

		if (!Json::GetUInt(m_data, "hud", heroud) || !Json::GetUInt(m_data, "equd", equd) )
		{
			error_log("param error: lack of hud, sec, costpro");
			return R_ERR_PARAM;
		}
		CLogicCMD logicCMD;

		int ret = logicCMD.CommderSkilLearn(m_uid, heroud, equd, m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=BraveNewWorldSkill&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int PotianSkilLearn()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "seqid", seqid);

		unsigned heroud = 0;
		string skid;
		if (!Json::GetUInt(m_data, "hud", heroud) || !Json::GetString(m_data, "skid", skid)|| !m_data.isMember("equds") || !m_data["equds"].isArray())
		{
			error_log("param error: lack of hud equd skid");
			return R_ERR_PARAM;
		}
		CLogicCMD logicCMD;

		int ret = logicCMD.PotianSkilLearn(m_uid, heroud, skid,m_data,m_jsonResult, lasttime, seqid);

		if (R_SUCCESS != ret)
		{
			return ret;
		}

		CGI_SEND_LOG("action=PotianSkilLearn&uid=%u", m_uid);
		return R_SUCCESS;
	}


	int JihuoChenghao()
	{
		unsigned id;
		if (!Json::GetUInt(m_data, "id", id))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned ud;
		if (!Json::GetUInt(m_data, "ud", ud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}


		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.JihuoChenghao(m_uid, id, ud, heroud,  m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=JihuoChenghao&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int PeidaiChenghao()
	{
		unsigned heroud;
		if (!Json::GetUInt(m_data, "heroud", heroud))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}
		unsigned chenghao;
		if (!Json::GetUInt(m_data, "chenghao", chenghao))
		{
			error_log("para error");
			return R_ERR_PARAM;
		}


		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.PeidaiChenghao(m_uid, heroud, chenghao, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=PeidaiChenghao&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ZhuanyiChenghao()
	{
		unsigned heroud1;
		if (!Json::GetUInt(m_data, "heroud1", heroud1))
		{
			error_log("heroud1 error");
			return R_ERR_PARAM;
		}
		unsigned heroud2;
		if (!Json::GetUInt(m_data, "heroud2", heroud2))
		{
			error_log("heroud2 error");
			return R_ERR_PARAM;
		}


		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.ZhuanyiChenghao(m_uid, heroud1, heroud2, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ZhuanyiChenghao&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int ShengDan2018()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.ShengDan2018(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=ShengDan2018&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int XiaoNian2018()
	{
		unsigned lasttime = 0;
		unsigned seqid = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);


		CLogicCMD logicCMD;
		int ret = logicCMD.XiaoNian2018(m_uid, m_data, m_jsonResult, lasttime, seqid);
		if(ret)
			return ret;

		CGI_SEND_LOG("action=XiaoNian2018&uid=%u", m_uid);
		return R_SUCCESS;
	}

	int SetHeroFm(){
		unsigned lasttime = 0;
		unsigned seqid = 0;
		unsigned index = 0;
		unsigned index1 = 0;
		unsigned hud = 0;
		unsigned equd = 0;
		Json::GetUInt(m_data, "seqid", seqid);
		Json::GetUInt(m_data, "lastime", lasttime);
		Json::GetUInt(m_data, "index", index);
		Json::GetUInt(m_data, "index1", index1);
		Json::GetUInt(m_data, "hud", hud);
		Json::GetUInt(m_data, "equd", equd);
		CLogicCMD logicCMD;
		int ret = logicCMD.HeroFm(m_uid,index,index1,hud,equd,m_jsonResult,lasttime,seqid);
		if (ret){
			return ret;
		}
		CGI_SEND_LOG("action=SetHeroFm&uid=%u&index=%u&index1=%u&hud=%u&equd=%u",m_uid,index,index1,hud,equd);
		return 0;
	}

	//古卷奇书
	CGI_ACTION_FUNCTION(InjectScroll, AncientScrollUnit::AncientParam, AncientScrollUnit, false, InjectScroll);
	//碎片合成
	CGI_ACTION_FUNCTION(ShredCompound, UnitUdCmdParams, CompoundShredUnit, true, ShredCompound);
	//令牌提升-充值额度奖励领取
	CGI_ACTION_FUNCTION(TokenUpgradeReceive, BaseCmdParams, TokenUpgradeActivityUnit, false, ReceivePointGift);
	//令牌提升-充值积分抽奖
	CGI_ACTION_FUNCTION(TokenUpgradeLottery, BaseCmdParams, TokenUpgradeActivityUnit, false, PointLottery);
	//打造套装-充值额度奖励领取
	CGI_ACTION_FUNCTION(BuildSuitReward, UnitIndexCmdParams, BuildSuitActivityUnit, false, ReceiveChargeGift);
	//祝福积分兑换
	CGI_ACTION_FUNCTION(BlessPointExchange, BlessPointActivityUnit::BlessParam, BlessPointActivityUnit, false, BlessExchange);
	//双倍福利-额外奖励
	CGI_ACTION_FUNCTION(DoubleWelfareExtra, UnitIndexCmdParams, DoubleWelfareActivityUnit, false, GetExtraReward);
	//双倍福利-普通充值奖励
	CGI_ACTION_FUNCTION(DoubleWelfareCharge, BaseCmdParams, DoubleWelfareActivityUnit, false, GetChareReward);
	//灵珠进阶充值活动
	CGI_ACTION_FUNCTION(PearlAdvanceExCharge, UnitIndexCmdParams, PearlAdvanceActivityUnit, false, ExchangePearl);
	//绝学转盘活动
	CGI_ACTION_FUNCTION(UniqueDialLottery, BaseCmdParams, UniqueDialActivityUnit, false, BeginLottery);
	//精元礼包
	CGI_ACTION_FUNCTION(SpiritGift, UnitIndexCmdParams, SpiritVitalityActivityUnit, false, ReceiveChargeGift);
	//熔炉熔炼
	CGI_ACTION_FUNCTION(ForgeSmelt, BaseCmdParams, ForgeSmeltActivityUnit, true, ForgeSmelt);
	//熔炉商店购买
	CGI_ACTION_FUNCTION(ForgeShop, UnitIndexCmdParams, ForgeSmeltActivityUnit, true, BuyGoods);
	//紫将转盘
	CGI_ACTION_FUNCTION(HeroDial, BaseCmdParams, HeroesDialActivityUnit, false, TurnHeroTable);
	//三国争霸
	CGI_ACTION_FUNCTION(KingdomWarCharge, UnitIndexCmdParams, KingdomWarActivityUnit, false, GetChargeReward);
	//保护旗帜升级
	CGI_ACTION_FUNCTION(FlagUpgrade, BaseCmdParams, ProtectiveFlagUnit, true, Upgrade);
	//一钻福利
	CGI_ACTION_FUNCTION(OneDiamondWelfare, BaseCmdParams, OneDiamondWelfareActivityUnit, false, BuyGoods);
	//七夕回馈
	CGI_ACTION_FUNCTION(QixiFeedback, BaseCmdParams, QiXiFeedbackActivityUnit, false, GetFeedback);
	//顺序充值
	CGI_ACTION_FUNCTION(FortunePacksOpenWindow, BaseCmdParams, FortunePacksActivityUnit, true, OpenWindow);
	CGI_ACTION_FUNCTION(FortunePacksBuy, UnitIdCmdParams, FortunePacksActivityUnit, false, Purchase);
	//七天好礼
	CGI_ACTION_FUNCTION(SevenDayPacks, UnitIndexCmdParams, SevenDayPacksActivityUnit, false, GetReward);
	//冰凰来袭
	CGI_ACTION_FUNCTION(IcePhoenix, UnitIndexCmdParams, IcePhoenixActivityUnix, false, GetChargeReward);
	//秋日回馈
	CGI_ACTION_FUNCTION(AutumnFeedback, UnitIndexCmdParams, AutumnFeedbackActivityUnix, false, GetChargeReward);
	//保护旗帜
	CGI_ACTION_FUNCTION(ProtectFlag, UnitIndexCmdParams, ProtectFlagActivityUnix, false, GetChargeReward);
	//年末好礼
	CGI_ACTION_FUNCTION(YearEndGift, UnitIndexCmdParams, YearEndGiftActivityUnix, false, GetChargeReward);
	//保护女神积分奖励
	CGI_ACTION_FUNCTION(GetGoddessReward, UnitIdCmdParams, ProtectGoddessUnix, false, GetPointReward);
	//密钥豪礼
	CGI_ACTION_FUNCTION(KeyLuxuryGift, UnitIndexCmdParams, KeyLuxuryGiftActivityUnit, false, GetReward);
	//兵魂注入
	CGI_ACTION_FUNCTION(SoldierSpiritInject, UnitUdCmdParams, SoldierSpiritUnit, false, Inject);
	//畅享小礼
	CGI_ACTION_FUNCTION(EnjoyGiftReward, EnjoySmallGiftActivityUnit::GiftParam, EnjoySmallGiftActivityUnit, false, GetReward);
	//幸运好礼
	CGI_ACTION_FUNCTION(TurnLuckyTable, BaseCmdParams, LuckyGiftActivityUnit, false, TurnTable);
	//能量回复
	CGI_ACTION_FUNCTION(RecoverEnergy, BaseCmdParams, ConvertToBackendUnit, true, RecoverEnergyByTime);
	//邀请好友的能量奖励
	CGI_ACTION_FUNCTION(InviteEnergy, BaseCmdParams, ConvertToBackendUnit, true, RecoveryByInviteFriends);
	//能量购买
	CGI_ACTION_FUNCTION(BuyEnergy, BaseCmdParams, ConvertToBackendUnit, true, BuyEnergy);
	//打开能量包
	CGI_ACTION_FUNCTION(OpenEnergyBag, BaseCmdParams, ConvertToBackendUnit, true, OpenEnergyBag);
	//打开特殊礼包
	CGI_ACTION_FUNCTION(SpecialPackOpen, BaseCmdParams, OpenSpecialPackUnit, true, Choose);
	//收获资源
	CGI_ACTION_FUNCTION(GainResource, BaseCmdParams, ConvertToBackendUnit, true, GainResource);
	//绝学突破
	CGI_ACTION_FUNCTION(JueXueBreakThrough, BaseCmdParams, JueXueBreakUnit, true, BreakThrough);

	//黑金强化
	//CGI_ACTION_FUNCTION(BlackGoldExchange, BlackEnhanceActivityUnit::EnhanceParam, BlackEnhanceActivityUnit, false, LuckyStoneExchange);
	//元旦庆点-充值领奖励
	CGI_ACTION_FUNCTION(NewYearChargeReward, UnitIndexCmdParams, NewYearActivityUnix, false, GetChargeReward);
	//元旦庆点-充值领奖励
	CGI_ACTION_FUNCTION(NewYearCombinedShop, BaseCmdParams, NewYearActivityUnix, false, BuyItemFromCombinedShop);
	//元旦庆点-在线30min钟领奖励
	CGI_ACTION_FUNCTION(NewYearOnlineReward, BaseCmdParams, NewYearActivityUnix, false, GetOnlineReward);
	//开服有礼-成就有礼
	CGI_ACTION_FUNCTION(achievementGift, BaseCmdParams, OpenServerActivityUnix, false, GetAchievementGift);
	//开服有礼-折扣商店
	CGI_ACTION_FUNCTION(DiscountShopGift, UnitIndexCmdParams, OpenServerActivityUnix, false, GetDiscountShopGift);

	//任务好礼
	CGI_ACTION_FUNCTION(TaskGift, UnitIndexCmdParams, TaskGiftUnit, true, DrawImpl);

	//转盘狂惠--充值奖励
	CGI_ACTION_FUNCTION(RotaryTableChargeReward, UnitIndexCmdParams, RotaryTableActivityUnix, false, GetChargeReward);
	//装盘狂惠---随机奖励
	CGI_ACTION_FUNCTION(RotaryTableRandomReward, UnitIdCmdParams, RotaryTableActivityUnix, false, GetRandomReward);

	//小兵宝物--充值奖励
	CGI_ACTION_FUNCTION(BatmanTreasureChargeReward, UnitIndexCmdParams, BatmanTreasureActivityUnix, false, GetChargeReward);
	//小兵宝物--抽奖
	CGI_ACTION_FUNCTION(BatmanTreasureDraw, BaseCmdParams, BatmanTreasureActivityUnix, false, Draw);

	//-----暑假精选
	//--累积充值
	CGI_ACTION_FUNCTION(SummerAccReward, UnitIndexCmdParams, SummerRewardActivityUnix, false, GetSummerAccReward);
	//--每日充值奖励
	CGI_ACTION_FUNCTION(SummerDailyReward, UnitIndexCmdParams, SummerRewardActivityUnix, false, GetSummerDailyReward);

	//-----暑假回馈
	//--累积充值
	CGI_ACTION_FUNCTION(SummerHolidaysAccReward, UnitIndexCmdParams, SummerHolidaysActivityUnix, false, GetChargeReward);
	//--物品兑换
	CGI_ACTION_FUNCTION(SummerHolidaysExchangeItem, UnitIndexCmdParams, SummerHolidaysActivityUnix, false, ExchangeItem);
	CGI_ACTION_FUNCTION(BeautyActive, BaseCmdParams, ActivityMeiRenUnit, false, AddPoint);
	CGI_ACTION_FUNCTION(BeautyPoint, BaseCmdParams, ActivityMeiRenUnit, false, UsePoint);
	CGI_ACTION_FUNCTION(BeautyReward, BaseCmdParams, ActivityMeiRenUnit, false, DrawImpl);
	CGI_ACTION_FUNCTION(InvestmentCount, BaseCmdParams, ActivityInvestment, false, SelectCount);
	CGI_ACTION_FUNCTION(InvestmentOption, BaseCmdParams, ActivityInvestment, false, SelectOption);
	CGI_ACTION_FUNCTION(InvestmentReward, BaseCmdParams, ActivityInvestment, false, Reward);
	CGI_ACTION_FUNCTION(BirdBridge, BaseCmdParams, ActivityBirdBridge, false, DrawImpl);

	//喜迎国庆 国庆狂欢 充值领奖励
	CGI_ACTION_FUNCTION(GuoQingChargeReward, UnitIndexCmdParams, GuoQingKuangHuan, false, GetChargeReward);
	//喜迎国庆 每日充值奖励
	CGI_ACTION_FUNCTION(ChinaDayEveryDayReward, BaseCmdParams, ChinaDayActivityUnix, false, GetEveryDayReward);
	//喜迎国庆 在线30分钟奖励
	CGI_ACTION_FUNCTION(ChinaDayOnlineReward, BaseCmdParams, ChinaDayActivityUnix, false, GetOnlineReward);
	//喜迎国庆 叛军来袭奖励
	CGI_ACTION_FUNCTION(ChinaDayInstanceZonesReward, BaseCmdParams, ChinaDayActivityUnix, false, GetInstanceZonesReward);
	//喜迎国庆 叛军来袭挑战次数扣除
	CGI_ACTION_FUNCTION(ChinaDayDeDuctChallengeNum, BaseCmdParams, ChinaDayActivityUnix, false, DeDuctChallengeNum);

	//自选充值活动
	CGI_ACTION_FUNCTION(EveryDayPayOptionalReward,UnitIndexCmdParams,PayOptionalActivityUnix,false,GetEveryDayChargeReward);
};

CGI_MAIN(CCgiSave)
