#ifndef DATAINC_H_
#define DATAINC_H_

#define SERVER_EQUIP_ADDABLE 1
#define SERVER_HERO_ADDABLE  1
#define SERVER_BUILD_ADDABLE 0

#include "Kernel.h"
#include "DataIdCtrl.h"
#include "DataUserMapping.h"
#include "DataUserBasic.h"
#include "DataUser.h"
#include "DataPay.h"
#include "DataPayHistory.h"
#include "DataBuilding.h"
#include "DataGate.h"
#include "DataQuest.h"
#include "DataEquipment.h"
#include "DataHero.h"
#include "DataTribute.h"
#include "DataUpdates.h"
#include "DataMap.h"
#include "DataNeighbour.h"
#include "DataUserInteract.h"
#include "DataAttack.h"
#include "DataUserAttack.h"
#include "DataUserMessage.h"
#include "DataMessage.h"
#include "DataUserData.h"
#include "DataBroadcast.h"
#include "DataUserText.h"
#include "DataInventory.h"
#include "DataArena.h"
#include "DataPlatformUser.h"
#include "DataAlliance.h"
#include "DataAllianceMember.h"
#include "DataAllianceMapping.h"
#include "DataInstance.h"
#include "DataFightArena.h"
#include "DataSecinc.h"
#include "DataWorldBoss.h"
#include "DataLadder.h"
#include "DataEmail.h"
#include "DataWorld.h"
#include "DataInviteMapping.h"
#include "DataWorldBoss.h"
#include "DataUserNomenate.h"
#include "DataHelpHistory.h"
#include "DataGuess.h"
#include "DataMatch.h"
#include "DataPersonMatch.h"
#include "DataBaseMatch.h"
#include "DataDragonball.h"
#include "DataPointsRank.h"
#include "DataExchangeCode.h"
#include "DataPromotionMapping.h"
#include "DataBaseExtra.h"
#include "DataAlliancePay.h"
#include "DataBarbarianInvasion.h"
#include "DataNominateAlliance.h"
#include "DataWorldNpc.h"
#include "DataGoods.h"
#include "DataUserRank.h"
#include "DataUserAccCharge.h"
#include "DataTopTenUser.h"
#include "DataMarketTask.h"
#include "DataMysticalShop.h"
#include "DataWeapon.h"
#include "DataRiver.h"
#include "DataPayRank.h"
#include "DataBlackUser.h"
#include "DataAllianceMessage.h"
#include "DataAllianceInteract.h"
#include "DataMatchInstance.h"
#include "DataAllServerPMatch.h"
#include "DataAllServerGuess.h"
#include "DataAllianceBoss.h"
#include "DataHundredDayActivity.h"
#include "DataQixi.h"
#include "DataNationalWarRgt.h"
#include "DataGroupsFighting.h"
#include "DataGM.h"
#include "DataRechargeAlliance.h"
#include "DataVipCharge.h"
#include "DataAllianceBattle.h"
#include "DataBarbarianKing.h"
#include "DataXML.h"
#include "DataAllServerBaseMatch.h"
#include "DataKingdom.h"
#include "DataVipRebates.h"
#include "DataHequActivity.h"
#include "DataAllServerRank.h"
#include "DataOpenAreaActivity.h"
#include "DataNewWorld.h"
#include "DataRank.h"
#include "DataNewLottry.h"
#include "DataDragonScaleGiftBag.h"
#include "DataConsumeRank.h"
#include "DataRechargeRank.h"
#include "DataNewWorldBattle.h"
#include "DataAllServerNewWorldBattle.h"
#include "DataRestriction.h"
#include "DataName.h"
#include "DataDouble11.h"
#include "DataNewMatch.h"
#include "DataBattleRoom.h"
#include "DataAllServerMap.h"
#include "DataAllServerMapBuffer.h"
#include "DataCrowdFunding.h"
#include "DataNewWorldAllianceMap.h"
#include "DataNewWorldAllianceRoom.h"
#include "DataAllianceTorch.h"
#include "DataTokenIntensify.h"
#include "ConfigManager.h"
#include "DataBraveNewWorld.h"
#include "DataAllianceConsume.h"
#include "ConfigWrap.h"
#include "DataKingTreasure.h"
#include "DataMVP.h"
#include "DataIdcard.h"
#include "DataRotaryTableDraw.h"
#include "DataChick.h"

#endif /* DATAINC_H_ */

#define GET_MEM_DATA_SEM(type,path,sem,allserver) \
	static map<int, type*> dataMap; \
	int serverId = 0; \
	Config::GetDomain(serverId); \
	map<int, type*>::iterator itr = dataMap.find(serverId); \
	if (itr != dataMap.end() && NULL != itr->second) \
	{ \
		return itr->second; \
	} \
	type *pdata = new type(); \
	\
	string dataPath; \
	if (allserver == true) \
		dataPath = MainConfig::GetAllServerPath(path); \
	else \
		dataPath = Config::GetPath(path); \
	if (dataPath.empty()) \
	{ \
		error_log("Init data fail!"); \
		return NULL; \
	} \
	\
	int ret = pdata->Init(dataPath,sem); \
	if (0 != ret) \
	{ \
		error_log("Init data fail!"); \
		delete pdata; \
		return NULL; \
	} \
	dataMap[serverId] = pdata; \
	return pdata; \

/*************************/
