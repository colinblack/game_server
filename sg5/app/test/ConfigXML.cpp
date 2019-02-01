/*
 * ConfigXML.cpp
 *
 *  Created on: 2014-4-25
 *      Author: Ralf
 */


#include "LogicInc.h"

void usage()
{
	cout << "usage: GetInitXML 	xml " << endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		usage();
		return 1;
	}
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	string action = argv[1];
	int ret = 0;
	CDataXML *dataXML = CDataXML::GetInitXML();
	if(!dataXML)
	{
		cout << "GetInitXML fail" << endl;
		return 1;
	}

	if (action == "olhero")
		ret = dataXML->InitHero();
	else if (action == "heromix")
		ret = dataXML->InitMixHero();
	else if (action == "sgvipconfig")
		ret = dataXML->InitVIP();
	else if (action == "olequipsub")
		ret = dataXML->InitEquipSub();
	else if (action == "sggiftbagconfig")
		ret = dataXML->InitGiftBag();
	else if (action == "boat")
		ret = dataXML->InitBoats();
	else if (action == "hammer")
	{
		ret = dataXML->InitHammer();
		/*
		map<uint32_t, Hammer> mapHammer;
		dataXML->GetHammer(mapHammer);
		for (map<uint32_t, Hammer>::iterator it = mapHammer.begin(); it != mapHammer.end(); ++it) {
			cout << "hammer: " << CTrans::ITOS(it->first) << endl;
			for (size_t i = 0; i < it->second.items.size(); ++i) {
				cout << "\t id=" << it->second.items[i].id << " rate=" << it->second.items[i].rate << endl;
			}
		}
		*/
	}
	else if (action == "treasurehuntconfig")
		ret = dataXML->InitTreasureHunt();
	else if (action == "equipintensifys")
		ret = dataXML->InitEquipIntensifys();
	else if (action == "olequipset")
		ret = dataXML->InitOlequipset();
	else if (action == "storeitem")
		ret = dataXML->InitShop();
	else if (action == "worldbattleshop")
		ret = dataXML->InitWorldBattleShop();
	else if (action == "rankbattleshop")
		ret = dataXML->InitRankBattleShop();
	else if (action == "hufushop")
		ret = dataXML->InitHufuShop();
	else if (action == "olequipment")
		ret = dataXML->InitEquipment();
	else if (action == "newturntablelottery")
		ret = dataXML->InitNewLottery();
	else if (action == "qixichoujiang")
		ret = dataXML->InitChoujiang();
	else if (action == "activityconfig")
		ret = dataXML->InitActivityConfig();
	else if (action == "olgateconfig")
		ret = dataXML->InitOlGateConfig();
	else if (action == "questconfig")
		ret = dataXML->InitQuestConfig();
	else if (action == "heavenConfig")
		ret = dataXML->InitHeavenDaoist();
	else if (action == "costHeavenDaoist")
		ret = dataXML->InitCostHeavenDaoist();
	else if (action == "yuandanconfig")
		ret = dataXML->InitDouble11();
	else if ("betshop" == action)
		ret = dataXML->InitBetShop();
	else if ("barbar" == action)
		ret = dataXML->InitBarbarKing();
	else if ("fivetiger" == action)
		ret = dataXML->InitFiveTiger();
	else if ("signinreward" == action)
		ret = dataXML->InitSignInReward();
	else if ("invitereward" == action)
		ret = dataXML->InitInviteReward();
	else if ("weaponsoulcost" == action)
		ret = dataXML->InitWeaponSoulCost();
	else if ("presummer" == action)
		ret = dataXML->InitPreSummer();
	else if ("newjueshiws" == action)
		ret = dataXML->InitNewJueShiWS();
	else if ("opportunityknock" == action)
		ret = dataXML->InitOpporKnockReward();
	else if ("fortunatelyagain" == action)
		ret = dataXML->InitFortunatelyAgain();
	else if ("rechargeoptional" == action)
		ret = dataXML->InitRechargeOptional();
	else if ("newrechargebag" == action)
		ret = dataXML->InitNewRechargeBag();
	else if ("groupbuy" == action)
		ret = dataXML->InitGroupBuyDaily();
	else if ("littlerecharge" == action)
		ret = dataXML->InitLittleRecharge();
	else if("temple" == action)
		ret = dataXML->InitTemple();
	else if("soldiertrainup" == action)
		ret = dataXML->InitSoldierTrainAndUp();
	else if("heavendaoskill" == action)
		ret = dataXML->InitHeavenDAOSkill();
	else if ("turnplate" == action)
		ret = dataXML->InitTurnPlate();
	else if ("monthgiftbag" == action)
		ret = dataXML->InitMonthGiftBag();
	else if ("combinedshop" == action)
		ret = dataXML->InitCombinedShop();
	else if ("neweradvance" == action)
		ret = dataXML->InitNewerAdvance();
	else if ("fashionshop" == action)
		ret = dataXML->InitFashionShop();
	else if ("houhuiyouqi" == action)
		ret = dataXML->InitHouHuiYouQi();
	else if ("chaozhizhekou" == action)
		ret = dataXML->InitChaoZhiZheKou();
	else if ("yuehuijuxian" == action)
		ret = dataXML->InitYueHuiJuXian();
	else if ("limitbuyofzone" == action)
		ret = dataXML->InitLimitBuyOfZone();
	else if ("fivedefendgrow" == action)
		ret = dataXML->InitFiveDefendGrow();
	else if ("countryday" == action)
		ret = dataXML->InitCountryDay();
	else if ("wuxingpearl" == action)
		ret = dataXML->InitWuxingPearl();
	else if ("temai" == action)
		ret = dataXML->InitHeartbeatBigSale();
	else if ("wuxingshop" == action)
		ret = dataXML->InitFiveShop();
	else if ("juexingtehui" == action)
		ret = dataXML->InitJueXingTeHui();
	else if ("freeexchange" == action)
		ret = dataXML->InitFreeExchange();
	else if ("doubleeleven" == action)
		ret = dataXML->InitDoubleEleven();
	else if ("jubaoxia" == action)
		ret = dataXML->InitJuBaoXia();
	else if ("heavenstep" == action)
		ret = dataXML->InitHeavenStep();
	else if ("daoiststep" == action)
		ret = dataXML->InitDaoistStep();
	else if ("zhenbaogehero" == action)
		ret = dataXML->InitZhenBaoGeHero();
	else if ("zhenbaogebuilding" == action)
		ret = dataXML->InitZhenBaoGeBuilding();
	else if ("herostonestep" == action)
		ret = dataXML->InitHeroStoneStep();
	else if ("buildingstonestep" == action)
		ret = dataXML->InitBuildingStoneStep();
	else if ("growdevelop" == action)
		ret = dataXML->InitGrowDevelop();
	else if ("treasurehuntexchange" == action)
		ret = dataXML->InitTreasureHuntExchange();
	else if ("dailychargecoin" == action)
		ret = dataXML->InitDailyChargeReward();
	else if ("treasurebox" == action)
		ret = dataXML->InitTreasureBox();
	else if ("christmas" == action)
		ret = dataXML->InitChristmas();
	else if ("keepsake" == action)
		ret = dataXML->InitKeepsake();
	else if ("feedback" == action)
		ret = dataXML->InitChargeFeedback();
	else if ("celeenewyear" == action)
		ret = dataXML->InitCelebrateNewYear();
	else if ("pointexchange" ==  action)
		ret = dataXML->InitPointExchange();
	else if ("buildingskin" == action)
		ret = dataXML->InitBuildSkin();
	else if ("tutorlogin" == action)
		ret = dataXML->InitTutorLogin();
	else if ("imperialgift" == action)
		ret = dataXML->InitImperialGift();
	else if ("TimeLimitUpgrade" == action)
		ret = dataXML->InitTimeLimitUpgrade();
	else if ("YearFortune" == action)
		ret = dataXML->InitYearFortune();
	else if ("HequActivity" == action)
		ret = dataXML->InitHeQuActivity();
	else if ("AncientScroll" == action)
		ret = dataXML->InitAncientScroll();
	else if ("ProtectFlag" == action)
		ret = dataXML->InitProtectFlag();
	else if ("ProtectGoddess" == action)
		ret = dataXML->InitProtectGoddess();
	else if ("building" == action)
		ret = dataXML->InitBuilding();
	else if ("catapult" == action)
		ret = dataXML->InitCatapult();
	else if ("costCatapult" == action)
		ret = dataXML->InitCostCatapult();
	else if ("catapultSkill" == action)
		ret = dataXML->InitCatapultSkill();
	else if ("chongzhizixuan" == action)
		ret = dataXML->InitChongZhiZiXuan();
	else if ("beauty" == action)
		ret = dataXML->InitBeauty();
	else if ("investment" == action)
		ret = dataXML->InitInvestment();

	else
	{
		cout<<"para error!"<<endl;
		return 0;
	}

	if (ret != 0)
	{
		cout << "try "<<action<<" fail,ret:" << ret << endl;
		return ret;
	}
	cout << "try "<<action<<" ok" << endl;
	return 0;
}


