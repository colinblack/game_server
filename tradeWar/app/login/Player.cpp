/*
 * Player.cpp
 *
 *  Created on: 2015-9-2
 *      Author: Administrator
 */

#include "Player.h"
#include "BattleRouteManager.h"
#include "ProtocolUser.h"
#include "SkillManager.h"
#include "AsyncDBManager.h"
#include "LoginServer.h"
#include "AdminManager.h"
#include "SystemEmail.h"
#include "ChatManager.h"
#include "GiftBagConfig.h"
#include "RankManager.h"
#include "SocialManager.h"
#include "VipConfig.h"
#include "BoatManager.h"
#include "SystemMessage.h"
#include "BoatConfig.h"
#include "ShopConfig.h"
#include "SpecialDiscountConfig.h"
#include "NewServerRankManager.h"
#include "ActivityTimeManager.h"
#include "AutoTransportManager.h"
#include "OtherServerManager.h"
#include "GateConfig.h"
#include "GateEnemyConfig.h"

Player::Player()
{
	m_isPropChange = false;
	m_isFrontReady = false;
	m_isNewUser = false;
	m_isAddRank = false;
	m_onlineDay = 0;
	m_buildingManager.setPlayer(this);
	m_soldierManager.setPlayer(this);
	m_resourceManager.setPlayer(this);
	m_stateManager.setPlayer(this);
	m_equipmentManager.setPlayer(this);
	m_taskManager.setPlayer(this);
	m_emailManager.setPlayer(this);
	m_activenessManager.setPlayer(this);
	m_skillManager.setPlayer(this);
	m_inviteManager.setPlayer(this);
	m_propertyManager.setPlayer(this);
	m_defendManager.setPlayer(this);
	m_battleGateMgr.setPlayer(this);
	m_troopsManager.setPlayer(this);
	m_boatManager.setPlayer(this);
	m_soldierRecoverTrain.setPlayer(this);
	m_dailyLoginManager.setPlayer(this);
	m_vipManager.setPlayer(this);
	m_dailyBuyManager.setPlayer(this);
	m_socialManager.setPlayer(this);
	m_randomQuestManager.setPlayer(this);
	m_activityManager.setPlayer(this);
	m_worldShopManager.setPlayer(this);
	m_monthGiftManager.setPlayer(this);
	m_chargeHistoryManager.setPlayer(this);
	m_gemManager.setPlayer(this);
	m_bossManager.setPlayer(this);
	m_arenaManager.setPlayer(this);
	m_watchADManager.setPlayer(this);
	m_interactManager.setPlayer(this);
	m_starBoxmanager.setPlayer(this);
	m_bTimer.clear();
	m_reg_server_id = 0;
	m_cur_server_id = 0;
	m_battleId = 0;
	m_expRate = 1;
	m_login_platform = 0;
	setPropertyManager();
}

Player::~Player()
{

}

bool Player::IsNewUser(uint32_t uid, bool& isNew)
{
	DataUser dataUser;
	CDataUser dbUser;
	int ret = dbUser.GetUser(uid, dataUser);
	if (ret != 0 && ret != R_ERR_NO_DATA)
	{
		error_log("GetUser fail uid=%u", uid);
		return false;
	}
	if (ret == R_ERR_NO_DATA)
	{
		isNew = true;
	}
	else
	{
		isNew = false;
	}
	return true;
}

bool Player::onLogin()
{
	m_resourceManager.onLogin();
	m_activenessManager.onLogin();
	m_inviteManager.onLogin();
	if (isQzone())
	{
		if (!Time::IsToday(m_dataUser.login_time))
		{
			m_dataUser.anti_addiction = 0;
			setExpRate(1);
		}
		else
		{
			uint32_t offline_time = LogicManager::GlobalTime >= m_dataUser.offline_time ? (LogicManager::GlobalTime - m_dataUser.offline_time) : 0;
			if (offline_time >= 18000)
			{
				m_dataUser.anti_addiction = 0;
				setExpRate(1);
			}
		}
	}
	else
	{
		setExpRate(1);
	}
	m_dataUser.login_time = LogicManager::GlobalTime;
	onAutoReward(true);
	savePlayerUserInfo();
	onPlayerNameUpdate();
	onPlayerFigureUrlUpdate();
	onOfflineInfo();
	m_stateManager.sendClientState();
	m_stateManager.sendLevelReward();
	SystemMessage::getInstance()->onLogin(m_uid);
	m_dailyLoginManager.sendData();
	m_dailyLoginManager.sendSign();
	m_vipManager.onLogin();
	m_boatManager.onLogin();
	m_randomQuestManager.onLogin();
	sendChargeReward();
	m_chargeHistoryManager.onLogin();
	ActivityTimeManager::getInstance()->sendInfo(m_dataUser.uid);
	AutoTransportManager::getInstance()->updateLevel(m_dataUser.uid);
	sendIsNewUser();
	m_activityManager.onLogin();
	m_bossManager.onLogin();
	m_arenaManager.onLogin();
	return true;
}

bool Player::onOffline(uint32_t uid)
{
	m_dataUser.offline_time = LogicManager::GlobalTime;
	uint32_t online_time = m_dataUser.offline_time >= m_dataUser.login_time ? (m_dataUser.offline_time - m_dataUser.login_time) : 0;
	m_dataUser.anti_addiction += online_time;
	if (online_time > 0) {
		m_stateManager.setOnlineTs(CTime::GetDayInterval(m_dataUser.register_time, Time::GetGlobalTime()), online_time);
	}
	setFrontReady(false);
	clearAllTimer();
	savePlayerUserInfo(true);
	return true;
}

bool Player::loadUser(DataUser& du)
{
	m_dataUser = du;
	return true;
}

bool Player::LoadPlayerData(uint32_t uid)
{
	if (!ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(uid))) {
		error_log("player not belong this server uid=%u", uid);
		return false;
	}
	CDataUser dbUser;
	int ret = 0;
	if ((ret = dbUser.GetUser(uid, m_dataUser)) != R_SUCCESS)
	{
		error_log("load %u's info failed,ret=%d", uid, ret);
		return false;
	}

	load(uid);

	return true;
}

void Player::load(uint32_t uid)
{
	m_stateManager.load(uid);
	m_equipmentManager.load(uid);
	m_skillManager.load(uid);
	m_soldierManager.load(uid);
	m_buildingManager.load(uid);
	m_resourceManager.load(uid);
	m_defendManager.load(uid);
	m_battleGateMgr.load(uid);
	m_taskManager.load(uid);
	m_emailManager.load(uid);
	m_activenessManager.load(uid);
	m_inviteManager.load(uid);
	initTimerList();
	m_troopsManager.load(uid);
	m_boatManager.load(uid);
	m_soldierRecoverTrain.load(uid);
	m_dailyLoginManager.load(uid);
	m_vipManager.load(uid);
	m_dailyBuyManager.load(uid);
	m_socialManager.load(uid);
	m_randomQuestManager.load(uid);
	m_activityManager.load(uid);
	m_worldShopManager.load(uid);
	m_monthGiftManager.load(uid);
	m_chargeHistoryManager.load(uid);
	m_gemManager.load(uid);
	m_bossManager.load(uid);
	m_arenaManager.load(uid);
	m_watchADManager.load(uid);
	m_interactManager.load(uid);
	m_starBoxmanager.load(uid);
	calcAutoRewardRes();
	loadAddiction();
}

bool Player::LoadNewPlayerData(uint32_t uid)
{
	if (AddUser(m_openId, m_login_platform, uid) != 0)
	{
		error_log("AddUser fail name=%s uid=%u platform=%u", m_openId.c_str(), uid, m_login_platform);
		return false;
	}
	return true;
}

bool Player::savePlayerUserInfo(bool offline)
{
	CDataUser dbUser;
	int ret = dbUser.SetUser(m_dataUser);
	if (ret != 0)
	{
		error_log("save %u's info failed,ret=%d", m_dataUser.uid, ret);
		return false;
	}
	return true;
}
bool Player::updateResourceData(ResourceInfo& oi, const string& code)
{
	bool ret = true;
	if (!m_resourceManager.updateResource(oi, code))
	{
		error_log("updateResourceData_fail&uid=%u", oi.uid);
		ret = false;
	}
	return ret;
}
bool Player::setVipLevel()
{
	m_resourceManager.initMax();
	return true;
}
bool Player::doReward(const Award * const pReward, const string & reason, bool notice, Award * result)
{
	if (result != NULL)
	{
		*result = *pReward;
		result->changeResRate(m_resourceManager.getR1Max(), m_resourceManager.getR2Max());
	}
	map<uint32_t, uint32_t> soldiers;
	ResourceCost addRes;
	CNetPacket sPacket;
	sPacket.uid = m_dataUser.uid;
	CBufferWriter bWriter(&(sPacket.body));
	bWriter.AppendByte(PROTOCOL_CMD_USER);
	bWriter.AppendByte(PROTOCOL_SUBCMD_USER_REWARD_INFO);

	const vector<AwardInfo> & vecAward = pReward->get();
	bWriter.AppendUInt32(vecAward.size());
	vector<AwardInfo>::const_iterator it;
	for (it = vecAward.begin(); it != vecAward.end(); it++)
	{
		const AwardInfo & sInfo = *it;
		uint32_t count = sInfo.count * m_expRate;
		if (count > sInfo.count)
		{
			error_log("invalid count count:%d sInfo.count:%d", count, sInfo.count);
			count = sInfo.count;
		}
		if (notice)
		{
			bWriter.AppendByte(sInfo.type);
			bWriter.AppendUInt32(sInfo.id);
			bWriter.AppendUInt32(count);
		}

		switch (sInfo.type)
		{
		case AWARD_TYPE_PEXP:
			upPlayerExp(count, reason);
			break;
		case AWARD_TYPE_DIAMOND:
			upDiamond(count, reason);
			break;
		case AWARD_TYPE_R1:
			addRes.r1 += count;
			break;
		case AWARD_TYPE_R2:
			addRes.r2 += count;
			break;
		case AWARD_TYPE_R1_RATE:
			addRes.r1 += m_resourceManager.getR1Max() * count / 100;;
			break;
		case AWARD_TYPE_R2_RATE:
			addRes.r2 += m_resourceManager.getR2Max() * count / 100;;
			break;
		case AWARD_TYPE_ITEM:
			m_equipmentManager.addBagItem(sInfo.id, count, reason);
			break;
		case AWARD_TYPE_ENERGY:
			addRes.tl += count;
			break;
		case AWARD_TYPE_SOLDIER:
			if (m_soldierManager.addOneSoldier(getUid(), sInfo.id, sInfo.count, reason)) {
				if (soldiers.count(sInfo.id)) {
					soldiers[sInfo.id] += sInfo.count;
				} else {
					soldiers[sInfo.id] = sInfo.count;
				}
			}
			break;
		case AWARD_TYPE_SKILL:
			m_skillManager.addSkill(sInfo.id, sInfo.count, reason);
			break;
		case AWARD_TYPE_LOYAL:
			addRes.p1 += count;
		}
	}

	if (addRes.AllSum() > 0)
	{
		m_resourceManager.addResources(addRes, reason);
	}
	uint32_t soldier_combat = 0;
	uint32_t soldier_count = 0;
	for (map<uint32_t, uint32_t>::iterator itr = soldiers.begin(); itr != soldiers.end(); ++itr)
	{
		soldier_combat += Soldier::calcCombat(itr->first, itr->second);
		soldier_count += itr->second;
	}
	if (soldier_count > 0)
	{
		m_activityManager.addSoldier(soldier_count);
		m_activityManager.addTaskCount(ActSevenTask::ActSevenTaskSoldier, soldier_count);
	}
	if (soldier_combat > 0)
	{
		addCombat(soldier_combat);
	}
	if (notice)
	{
		PlayerManager::getInstance()->sendToAccess(&sPacket);
	}
	return true;
}

bool Player::doPacket(CNetPacket * packet)
{
	switch (packet->cmd)
	{
	case PROTOCOL_CMD_USER:
		doUser(packet);
		break;
	case PROTOCOL_CMD_WORKER:
		break;
	case PROTOCOL_CMD_BUILDING:
		m_buildingManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_EQUIPMENT:
		m_equipmentManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_RESOURCE:
		m_resourceManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_VIDEO:
		break;
	case PROTOCOL_CMD_GATE:
		m_defendManager.doPacket(packet);
		m_battleGateMgr.doPacket(packet);
		m_starBoxmanager.doPacket(packet);
		break;
	case PROTOCOL_CMD_WARRIOR_GATE:
		break;
	case PROTOCOL_CMD_TASK:
		m_taskManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_EMAIL:
		m_emailManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_RIDE:
		break;
	case PROTOCOL_CMD_DAILY_TASK:
		m_activenessManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_REWARD:
		break;
	case PROTOCOL_CMD_SKILL:
		m_skillManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_SOLDIER:
		m_soldierManager.doPacket(packet);
		m_soldierRecoverTrain.doPacket(packet);
		break;
	case PROTOCOL_CMD_INVITE:
		m_inviteManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_HOME:
		break;
	case PROTOCOL_CMD_MISC:
		doMiscPacket(packet);
		break;
	case PROTOCOL_CMD_SOCIAL:
		doSocialPacket(packet);
		break;
	case PROTOCOL_CMD_BOAT:
		m_boatManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_ARENA:
		m_arenaManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_GOD:
		break;
	case PROTOCOL_CMD_CANNON:
		break;
	case PROTOCOL_CMD_BUILDING_TRAIN:
		break;
	case PROTOCOL_CMD_TROOPS:
		m_troopsManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_DAILY_BUY:
		m_dailyBuyManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_RANDOM_QUEST:
		m_randomQuestManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_ACTIVITY:
		m_activityManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_BOSS:
		m_bossManager.doPacket(packet);
		break;
	case PROTOCOL_CMD_AD:
		m_watchADManager.doPacket(packet);
		break;
	}
	return true;
}

bool Player::doMiscPacket(CNetPacket *packet)
{
	switch (packet->subCmd)
	{
	case PROTOCOL_SUBCMD_CHAT_AD:
		doAdvertChat(packet);
		break;
	case PROTOCOL_SUBCMD_NEW_SERVER_INFO:
	case PROTOCOL_SUBCMD_NEW_SERVER_REWARD:
	case PROTOCOL_SUBCMD_NEW_SERVER_STONE_ACT:
	case PROTOCOL_SUBCMD_NEW_SERVER_STRENGTH_ACT:
	case PROTOCOL_SUBCMD_NEW_SERVER_ALLIANCE_ACT:
	case PROTOCOL_SUBCMD_NEW_SERVER_ROBOT_ACT:
	case PROTOCOL_SUBCMD_NEW_SERVER_HERO_TAR_ACT:
		break;
	case PROTOCOL_SUBCMD_MISC_DAILY_CHARGE_QUERY:
		break;
	case PROTOCOL_SUBCMD_MISC_SEVEN_FOUNDS_QUERY:
	case PROTOCOL_SUBCMD_MISC_SEVEN_FOUNDS_BUY:
	case PROTOCOL_SUBCMD_MISC_SEVEN_FOUNDS_AWARD:
		break;
	case PROTOCOL_SUBCMD_MISC_DAILY_GROUP_BUY_QUERY:
	case PROTOCOL_SUBCMD_MISC_DAILY_GROUP_BUY:
	case PROTOCOL_SUBCMD_MISC_DAILY_GROUP_BUY_AWARD:
		break;
	case PROTOCOL_SUBCMD_MISC_COST_QUERY:
	case PROTOCOL_SUBCMD_MISC_COST_BUY:
		break;
	case PROTOCOL_SUBCMD_MISC_BARBARIAN_CHALLENGE:
	case PROTOCOL_SUBCMD_MISC_BARBARIAN_ALLIANCE_RANK:
	case PROTOCOL_SUBCMD_MISC_BARBARIAN_ALLIANCE_MEM_RANK:
	case PROTOCOL_SUBCMD_MISC_BARBARIAN_CHALLENGE_TIMES:
		break;
	case PROTOCOL_SUBCMD_MISC_SHOOT_QUERY:
	case PROTOCOL_SUBCMD_MISC_SHOOT_HIT:
	case PROTOCOL_SUBCMD_MISC_SHOOT_HIT_100:
	case PROTOCOL_SUBCMD_MISC_SHOOT_DAILY_AWARD:
		break;
	case PROTOCOL_SUBCMD_MISC_GOLDEN_EGG_QUERY:
	case PROTOCOL_SUBCMD_MISC_GOLDEN_EGG_HIT:
	case PROTOCOL_SUBCMD_MISC_GOLDEN_EGG_REFRESH:
		break;
	case PROTOCOL_SUBCMD_MISC_ALLIANCE_CHARGE_QUERY:
	case PROTOCOL_SUBCMD_MISC_ALLIANCE_CHARGE_AWARD:
	case PROTOCOL_SUBCMD_MISC_ALLIANCE_CHARGE_SALE:
		break;
	case PROTOCOL_SUBCMD_MISC_MONTH_CHARGE_QUERY:
	case PROTOCOL_SUBCMD_MISC_MONTH_CHARGE_AWARD:
		break;
	case PROTOCOL_SUBCMD_MISC_HERO_EXCHANGE_QUERY:
	case PROTOCOL_SUBCMD_MISC_HERO_EXCHANGE:
		break;
	case PROTOCOL_SUBCMD_MISC_MATERIAL_SALE_QUERY:
	case PROTOCOL_SUBCMD_MISC_MATERIAL_SALE_BUY:
		break;
	case PROTOCOL_SUBCMD_MISC_MATERIAL_WHEEL_QUERY:
	case PROTOCOL_SUBCMD_MISC_MATERIAL_WHEEL_BUY_TIMES:
	case PROTOCOL_SUBCMD_MISC_MATERIAL_WHEEL_HIT:
	case PROTOCOL_SUBCMD_MISC_MATERIAL_WHEEL_AWARD:
		break;
	case PROTOCOL_SUBCMD_MISC_CHARGE_RETURN_QUERY:
	case PROTOCOL_SUBCMD_MISC_CHARGE_RETURN_BUY:
		break;
	case PROTOCOL_SUBCMD_MISC_MAGIC_SQUARE_QUERY:
	case PROTOCOL_SUBCMD_MISC_MAGIC_SQUARE_UP:
	case PROTOCOL_SUBCMD_MISC_MAGIC_SQUARE_UP_ALL:
		break;
	case PROTOCOL_SUBCMD_MISC_BUSINESS_QUERY:
	case PROTOCOL_SUBCMD_MISC_BUSINESS_BUY:
		break;
	case PROTOCOL_SUBCMD_MISC_WAR_KING_QUERY:
	case PROTOCOL_SUBCMD_MISC_WAR_KING_BUY:
	case PROTOCOL_SUBCMD_MISC_WAR_KING_AWARD:
		break;
	case PROTOCOL_SUBCMD_MISC_CROSS_SHOOT_QUERY:
	case PROTOCOL_SUBCMD_MISC_CROSS_SHOOT_HIT:
	case PROTOCOL_SUBCMD_MISC_CROSS_SHOOT_HIT_100:
	case PROTOCOL_SUBCMD_MISC_CROSS_SHOOT_DAILY_AWARD:
		break;
	case PROTOCOL_SUBCMD_MISC_CHARGE_QUERY:
		break;
	case PROTOCOL_SUBCMD_MISC_SOLDIER_QUERY:
	case PROTOCOL_SUBCMD_MISC_SOLDIER_REFRESH:
		break;
	case PROTOCOL_SUBCMD_MISC_FIRST_CHARGE:
		break;
	case PROTOCOL_SUBCMD_MISC_ZHUANPAN:
		break;
	case PROTOCOL_SUBCMD_MISC_FUND_REWARD:
		break;
	}
	return true;
}

bool Player::doSocialPacket(CNetPacket *packet)
{
	return true;
}

bool Player::doUser(CNetPacket * packet)
{
	switch (packet->subCmd)
	{
	case PROTOCOL_SUBCMD_USERINFO:
		doUserQuery(packet);
		break;
	case PROTOCOL_SUBCMD_MENUBAR_QUERY:
		doQueryMenubar(packet);
		break;
	case PROTOCOL_SUBCMD_MENUBAR_SET:
		doSetMenubar(packet);
		break;
	case PROTOCOL_SUBCMD_HERO_RECRUIT:
		doHeroRecruit(packet);
		break;
	case PROTOCOL_SUBCMD_QUERY_HERO_REFRESH_ITEM:
		doQueryHeroRefreshItem(packet);
		break;
	case PROTOCOL_SUBCMD_CHOOSE_HERO_REFRESH_ITEM:
		doChooseHeroRefreshItem(packet);
		break;
	case PROTOCOL_SUBCMD_HERO_SET_CHIEF:
		doHeroSetChief(packet);
		break;
	case PROTOCOL_SUBCMD_HERO_SET_STATION:
		doHeroSetStation(packet);
		break;
//		case PROTOCOL_SUBCMD_HERO_FIRED:
//			 doHeroFired(packet);
//			 break;
	case PROTOCOL_SUBCMD_HERO_RECALL_STATION:
		doHeroRecallStation(packet);
		break;
	case PROTOCOL_SUBCMD_HERO_TRAIN_LIST_QUERY:
		doHeroTrainListQuery(packet);
		break;
	case PROTOCOL_SUBCMD_HERO_TRAIN_SLOT_OPEN:
		doHeroTrainSlotOpen(packet);
		break;
	case PROTOCOL_SUBCMD_HERO_TRAIN_FINISH_NOW:
		doHeroTrainFinishNow(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_ACC_UPGRADE:
		doAccUpgradeBuilding(packet);
		break;
	case PROTOCOL_SUBCMD_BUILDING_ACC_UPGRADE_QUERY:
		doAccUpgradeBuildingQuery(packet);
		break;
	case PROTOCOL_SUBCMD_SET_USRE_KINGDOM:
		doSetUserKingdom(packet);
		break;
	case PROTOCOL_SUBCMD_BUY_BUILDING_ACC_UPGRADE:
		doBuyBuildingAccUpgrade(packet);
		break;
	case PROTOCOL_SUBCMD_TUTORIAL_STAGE_SET:
		doSetTutorialStage(packet);
		break;
	case PROTOCOL_SUBCMD_TRAILER_STAGE_SET:
		doSetTrailerStage(packet);
		break;
	case PROTOCOL_SUBCMD_SET_BLOOD_BANK_THRESHOLD:
		doSetBloodBankThreshold(packet);
		break;
	case PROTOCOL_SUBCMD_USER_GET_BLUE_VALID_TIME:
		doUserGetBlueValidTime(packet);
		break;
	case PROTOCOL_SUBCMD_USER_GET_PAY_TOKEN:
		doUserGetPayToken(packet);
		break;
	case PROTOCOL_SUBCMD_USER_ADDICTION_RATE:
		doAddictionRate(packet);
		break;
	case PROTOCOL_SUBCMD_USER_ADDICTION_RATE_QUERY:
		doAddictionRateQuery(packet);
		break;
	case PROTOCOL_SUBCMD_USER_RESET_PROTECT_TIME:
		doResetProtectTime(packet);
		break;
	case PROTOCOL_SUBCMD_USER_ADD_SHORTCUT_REWARD:
		doAddShortcutReward(packet);
		break;
	case PROTOCOL_SUBCMD_USER_CLIENT_STATE:
		doSetClientState(packet);
		break;
	case PROTOCOL_SUBCMD_USER_DAILY_LOGIN_REWARD:
		m_dailyLoginManager.doReward(packet);
		break;
	case PROTOCOL_SUBCMD_USER_LEVEL_REWARD:
		doLevelReward(packet);
		break;
	case PROTOCOL_SUBCMD_USER_DAILY_SIGN_REWARD:
		m_dailyLoginManager.doSign(packet);
		break;
	case PROTOCOL_SUBCMD_USER_AUTO_REWARD_INFO:
		doAutoRewardInfo(packet);
		break;
	case PROTOCOL_SUBCMD_USER_AUTO_REWARD_BAG:
		doAutoRewardBag(packet);
		break;
	case PROTOCOL_SUBCMD_USER_VIP_REWARD:
		m_vipManager.doPacket(packet);
		break;
	case PROTOCOL_SUBCMD_USER_DAILY_CHARGE_REWARD:
		doDailyChargeReward(packet);
		break;
	case PROTOCOL_SUBCMD_USER_TOTAL_CHARGE_REWARD:
		doTotalChargeReward(packet);
		break;
	case PROTOCOL_SUBCMD_USER_SET_NAME:
		doSetName(packet);
		break;
	case PROTOCOL_SUBCMD_USER_FIRST_CHARGE:
		doFirstChargeReward(packet);
		break;
	case PROTOCOL_SUBCMD_USER_MONTH_GIFT_INFO:
	case PROTOCOL_SUBCMD_USER_MONTH_GIFT_REWARD:
		m_monthGiftManager.doPacket(packet);
		break;
	case PROTOCOL_SUBCMD_USER_BUY_VIP_GIFT:
		doBuyVipGift(packet);
		break;
	case PROTOCOL_SUBCMD_USER_CHARGE_REPORT:
		doChargeReport(packet);
		break;
	case PROTOCOL_SUBCMD_USER_HELP:
		doInteract(packet);
		break;
	case PROTOCOL_SUBCMD_USER_HELP_BOX:
		doInteractBox(packet);
		break;
	case PROTOCOL_SUBCMD_USER_AUTO_REWARD:
		onAutoReward(false);
		break;
	}
	return true;
}

bool Player::doUserQuery(CNetPacket * packet)
{
	sendPlayerInfo();
	return true;
}

bool Player::doHeroRecruit(CNetPacket * packet)
{
	return true;
}

bool Player::doQueryHeroRefreshItem(CNetPacket * packet)
{
	return true;
}

bool Player::doChooseHeroRefreshItem(CNetPacket * packet)
{
	return true;
}

bool Player::doHeroSetChief(CNetPacket * packet)
{
	return true;
}

bool Player::doHeroSetStation(CNetPacket * packet)
{
	return true;
}

bool Player::doHeroRecallStation(CNetPacket * packet)
{
	return true;
}

bool Player::doHeroTrainListQuery(CNetPacket* packet)
{
	uint32_t uid = packet->uid;
	sendHeroTrainList(uid);
	return true;
}

bool Player::doHeroTrainSlotOpen(CNetPacket* packet)
{
	return true;
}

bool Player::doHeroTrainFinishNow(CNetPacket* packet)
{
	return true;
}

bool Player::doUpgradeBuildingOver(Building* pBuilding)
{
	pBuilding->setStrong(0);
	pBuilding->propsCalc();
	pBuilding->setHp(pBuilding->getMaxHp());
	pBuilding->saveData();
	if (pBuilding->isBase())
	{
		getRm()->initMax();
		getRm()->sendResourceList();
	}
	else if (pBuilding->isStorageBuilding())
	{
		getRm()->initMax();
		getRm()->sendResourceList();
	}
	sendBuildingInfo(pBuilding->getUD());
	getTaskManager()->onUpgradeBuilding();
	m_activityManager.addBuildingUp(1);
	const BuildingItemConfig *cfg = BuildingConfig::getInstance()->getItemConfig(pBuilding->getType());
	if (cfg == NULL) {
		return true;
	}
	addCombat(BuildingConfig::getInstance()->getBuildingPower(cfg->color, pBuilding->getLevel()));
	return true;
}
bool Player::doUpgradeSoldierOver(Soldier* pSoldier)
{
	pSoldier->onUpgradeOver();
	sendActionOver(PROTOCOL_CMD_SOLDIER, PROTOCOL_RSP_SUBCMD_SOLDIER_UPGRADE_OVER, pSoldier);
	sendSoldierListInfo();
	BUSI_SOLDIER("upgrade|code=up|%u|%u|%u|%u|%u|%u|%u",
			pSoldier->getUid(), pSoldier->getType(), pSoldier->getLevel(), pSoldier->getCount(), 0, pSoldier->getStar(), LogicManager::GlobalTime);
	getTaskManager()->onUpgradeSoldier();
	return true;
}
bool Player::doAccUpgradeBuilding(CNetPacket* packet)
{
	return true;
}
bool Player::onAccUpgradeBuildingResp(byte ret, uint32_t ud, uint32_t ts)
{
	CNetPacket sRspPacket;
	sRspPacket.uid = getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_BUILDING_ACC_UPGRADE);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(ud);
	selfWriter.AppendUInt32(ts);

	PlayerManager::getInstance()->sendToAccess(&sRspPacket);

	return true;
}
bool Player::doAccUpgradeBuildingQuery(CNetPacket* packet)
{
	return true;
}
bool Player::doSetUserKingdom(CNetPacket* packet)
{
	return true;
}
bool Player::sendJoinKingdomToAlliance(uint32_t uid, uint32_t kingdom)
{
	// 通知World服务器有国家成员加入
	CNetPacket wRspPacket;
	wRspPacket.uid = uid;
	CBufferWriter selfWriter(&wRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_LEAGUE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_LEAGUE_JOIN);
	selfWriter.AppendUInt32(kingdom);
	LogicManager::getInstance()->transToWorld(&wRspPacket);
	return true;
}
bool Player::doBuyBuildingAccUpgrade(CNetPacket* packet)
{
	return true;
}
bool Player::doSetTutorialStage(CNetPacket* packet)
{
	CUserTutorialStageSetProtocol cs;
	if (!cs.Decode(&(packet->body)))
	{
		error_log("CUserTutorialStageSetProtocol decode failed, uid=%u", packet->uid);
		return false;
	}
	setTutorialStage(cs.tutorialStage);
	savePlayerUserInfo();
	debug_log("set tutorial stage uid=%u stage=%u", packet->uid, cs.tutorialStage);
	return true;
}

bool Player::doSetTrailerStage(CNetPacket* packet)
 {
	uint32_t uid = packet->uid;
	byte ret = R_SUCCESS;
	byte type = 0;
	do {
		CUserTrailerStageSetProtocol proto;
		if (!proto.Decode(packet->GetBody())) {
			error_log("decode failed, uid=%u", uid);
			ret = R_ERROR;
			break;
		}
		type = proto.type;
		uint32_t *stage = NULL;
		uint32_t score = 0;
		if (proto.type == 0) {
			stage = &m_dataUser.trailer_stage;
			score = m_dataUser.level;
		} else if (proto.type == 1) {
			stage = &m_dataUser.trailer_stage_b;
			score = m_buildingManager.getBuildingLevel(BUILDING_ID_BASE);
		}
		if (stage == NULL) {
			error_log("type error uid=%u type=%u", uid, static_cast<uint32_t>(proto.type));
			ret = R_ERROR;
			break;
		}
		if (proto.stage != *stage + 1) {
			error_log("stage error uid=%u type=%u c=%u s=%u", uid, static_cast<uint32_t>(proto.type), proto.stage, *stage);
			ret = R_ERROR;
			break;
		}
		const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getFunctionUnlock(proto.type, proto.stage);
		if (cfg == NULL) {
			error_log("cfg error uid=%u type=%u stage=%u", uid, static_cast<uint32_t>(proto.type), proto.stage);
			ret = R_ERROR;
			break;
		}
		if (score < cfg->require) {
			error_log("require error uid=%u type=%u stage=%u score=%u require=%u",
					uid, static_cast<uint32_t>(proto.type), proto.stage, score, cfg->require);
			ret = R_ERROR;
			break;
		}
		*stage = proto.stage;
		savePlayerUserInfo();
		doReward(&(cfg->award), "trailer_stage_" + CTrans::ITOS(proto.type) + "_" + CTrans::ITOS(proto.stage));
	} while (false);

	CNetPacket sp;
	sp.uid = uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_TRAILER_STAGE_SET);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(Byte, type);
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u,type=%u,ret=%u", uid, static_cast<uint32_t>(type), static_cast<uint32_t>(ret));
	return true;
}

// 大喇叭广播
bool Player::doAdvertChat(CNetPacket *packet)
{
	CAdvertChatProtocol protocol;
	if (!protocol.Decode(&packet->body))
	{
		return false;
	}
	CNetPacket rspPacket;
	rspPacket.uid = packet->uid;
	CBufferWriter writer(&rspPacket.body);
	writer.AppendByte(PROTOCOL_CMD_MISC);
	writer.AppendByte(PROTOCOL_SUBCMD_CHAT_AD);
	writer.AppendByte(0);
	writer.AppendString(protocol.msg);
	writer.AppendByte(0);
	LogicManager::getInstance()->sendToAccess(&rspPacket);
	return true;
}
bool Player::doSocialFriendAddTL(CNetPacket *packet)
{
	return true;
}
bool Player::doAddictionRate(CNetPacket *packet)
{
	CAddictionRateProtocol protocol;
	if (!protocol.Decode(&(packet->body)))
	{
		error_log("CAddictionRateProtocol&uid=%u", packet->uid);
		return false;
	}
	if (protocol.rate > 1 || protocol.rate < 0)
	{
		error_log("addiction rate invalid");
		return false;
	}
	if (fabs(protocol.rate - m_expRate) > 0.1)
	{
		info_log("receive anti-addiction data uid:%d m_expRate:%f rate:%f", packet->uid, m_expRate, protocol.rate);
		m_expRate = protocol.rate;
		saveAddiction();
		CNetPacket sRspPacket;
		sRspPacket.uid = packet->uid;
		CBufferWriter selfWriter(&sRspPacket.body);
		selfWriter.AppendByte(PROTOCOL_CMD_USER);
		selfWriter.AppendByte(PROTOCOL_SUBCMD_USER_ADDICTION_RATE_QUERY);
		selfWriter.AppendFloat(m_expRate);
		PlayerManager::getInstance()->sendToAccess(&sRspPacket);

	}

	info_log("receive anti-addiction data uid:%d rate:%f", packet->uid, protocol.rate);
	return true;
}
bool Player::doAddictionRateQuery(CNetPacket *packet)
{
	CNetPacket sRspPacket;
	sRspPacket.uid = packet->uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_USER_ADDICTION_RATE_QUERY);
	selfWriter.AppendFloat(m_expRate);
	PlayerManager::getInstance()->sendToAccess(&sRspPacket);
	info_log("receive anti-addiction data uid:%d rate:%f", packet->uid, m_expRate);
	return true;
}
bool Player::doResetProtectTime(CNetPacket *packet)
{
	setProtectedTime(0);
	sendRestTimes();
	return true;
}
bool Player::doAddShortcutReward(CNetPacket *packet)
{
	byte ret = R_SUCCESS;
	do {
		if (m_dataUser.shortcut == 1) {
			ret = R_ERROR;
			break;
		}

		const Award *cfg = GiftBagConfig::getInstance()->getAddShortcut();
		if (cfg == NULL) {
			ret = R_ERROR;
			break;
		}
		m_dataUser.shortcut = 1;
		Award reward;
		GiftBagConfig::getInstance()->openAll(cfg->get(), reward);
		doReward(&reward, "add_shortcut");
		savePlayerUserInfo();
	} while (false);

	CNetPacket rspPacket;
	rspPacket.uid = getUid();
	CBufferWriter selfWriter(&rspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_USER_ADD_SHORTCUT_REWARD);
	selfWriter.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&rspPacket);
	return true;
}
bool Player::doSetClientState(CNetPacket *packet)
{
	uint32_t uid = packet->uid;
	CUserSetClientStateProtocol protocol;
	if (!protocol.Decode(&(packet->body)))
	{
		error_log("Decode error, uid=%u", uid);
		return false;
	}

	m_stateManager.setClientState(protocol.data);

	return true;
}
bool Player::doLevelReward(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	byte ret = 0;
	CUserLevelRewardProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("Decode error uid=%u", uid);
		ret = PROTOCOL_RET_USER_FAIL;
	}

	if (0 == ret && m_dataUser.level < protocol.id) {
		error_log("Level error uid=%u id=%u", uid, static_cast<uint32_t>(protocol.id));
		ret = PROTOCOL_RET_USER_FAIL;
	}

	if (0 == ret && m_stateManager.getLevelReward(protocol.id - 1)) {
		error_log("Reward flag error uid=%u id=%u", uid, static_cast<uint32_t>(protocol.id));
		ret = PROTOCOL_RET_USER_FAIL;
	}

	if (0 == ret && !m_stateManager.setLevelReward(protocol.id - 1)) {
		error_log("Set reward flag error uid=%u id=%u", uid, static_cast<uint32_t>(protocol.id));
		ret = PROTOCOL_RET_USER_FAIL;
	}

	const ExpLevelItem *cfg = NULL;
	if (0 == ret && (cfg = ExpConfig::getInstance()->getExpLevel(protocol.id)) == NULL) {
		error_log("cfg error uid=%u id=%u", uid, static_cast<uint32_t>(protocol.id));
		ret = PROTOCOL_RET_USER_FAIL;
	}

	if (0 == ret && !m_stateManager.saveLevelReward()) {
		error_log("Save reward flag error uid=%u id=%u", uid, static_cast<uint32_t>(protocol.id));
		ret = PROTOCOL_RET_USER_FAIL;
	}

	if (0 == ret && !doReward(&(cfg->award), "level_reward_" + CTrans::ITOS(protocol.id))) {
		error_log("doreward error uid=%u id=%u", uid, static_cast<uint32_t>(protocol.id));
		ret = PROTOCOL_RET_USER_FAIL;
	}

	m_stateManager.sendLevelReward();

	CNetPacket sp;
	sp.uid = uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_LEVEL_REWARD);
	writer.AppendByte(ret);

	PlayerManager::getInstance()->sendToAccess(&sp);

	debug_log("uid=%u,id=%u", uid, static_cast<uint32_t>(protocol.id));

	return true;
}

bool Player::doAutoRewardInfo(CNetPacket *packet) {
	resetUserDaily();
	uint32_t score = m_troopsManager.getDefendScore();
	CNetPacket sp;
	sp.uid = m_uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_AUTO_REWARD_INFO);
	writer.AppendUInt32(score);
	float res_rate = (static_cast<float>(m_dataUser.help_count) / 100.0f) + m_vipManager.getRight(VipManager::VIP_RIGHT_OFFLINE);
	int tres = m_auto_reward_res * res_rate;
	if (tres < 0 && static_cast<uint32_t>(0 - tres) > m_auto_reward_res) {
		writer.AppendUInt32(0);
	} else {
		writer.AppendUInt32(m_auto_reward_res + tres);
	}
	writer.AppendUInt32(m_dataUser.auto_reward_count);
	writer.AppendUInt32(m_dataUser.help_box);
	writer.AppendInt16(m_dataUser.help_count);
	writer.AppendByte(m_dataUser.help_reward);
	m_interactManager.getData(sp.GetBody());
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool Player::doAutoRewardBag(CNetPacket *packet) {
	static const int BAG_REWARD_INTERVAL = 360;
	Award result;
	uint32_t lv = m_dataUser.level > 0 ? m_dataUser.level - 1 : m_dataUser.level;
	uint32_t bag_id = (lv / 3 + 1) * 10000;
	uint32_t count = m_dataUser.auto_reward_count / BAG_REWARD_INTERVAL;
	m_dataUser.auto_reward_count -= count * BAG_REWARD_INTERVAL;
	count += m_dataUser.help_box;
	m_dataUser.help_box = 0;
	savePlayerUserInfo();
	Award reward;
	GiftBagConfig::getInstance()->openAllLuckyBox(bag_id, count, reward);
	doReward(&reward, "boat_box_" + CTrans::ITOS(bag_id), false, &result);
	CNetPacket sp;
	sp.uid = m_uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_AUTO_REWARD_BAG);
	result.packetData(writer);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool Player::doDailyChargeReward(CNetPacket *packet)
{
	uint32_t uid = packet->uid;
	resetUserDaily();
	byte ret = 0;
	if (m_dataUser.daily_charge_reward == 1 || m_dataUser.daily_charge == 0) {
		error_log("daily charge reward flag error uid=%u", uid);
		ret = 1;
	}
	const Award *award = GiftBagConfig::getInstance()->getDailyChargeReward(m_dataUser.daily_charge);
	if (0 == ret && award == NULL) {
		error_log("get award error uid=%u", uid);
		ret = 1;
	}
	Award reward;
	if (0 == ret) {
		for (vector<AwardInfo>::const_iterator itr = award->get().begin(); itr != award->get().end(); ++itr) {
			if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
				GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
			} else {
				reward.add(*itr);
			}
		}
	}

	if (0 == ret && !doReward(&reward, "daily_charge")) {
		error_log("do award error uid=%u", uid);
		ret = 1;
	}

	if (0 == ret) {
		m_dataUser.daily_charge_reward = 1;
		savePlayerUserInfo();
		sendChargeReward();
	}

	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_DAILY_CHARGE_REWARD);
	writer.AppendByte(ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u ret=%u", uid, static_cast<uint32_t>(ret));
	if (0 == ret) {
		BUSI_MISC("resident_act|oneyuan|%u|%u|%u", m_dataUser.uid, 1u, Time::GetGlobalTime());
	}
	return true;
}

bool Player::doTotalChargeReward(CNetPacket *packet)
{
	uint32_t uid = packet->uid;
	CUserTotalChargeRewardProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return onTotalChargeReward(R_ERROR);
	}
	if (m_dataUser.total_charge_reward & (1u << proto.id)) {
		error_log("reward flag error uid=%u id=%u flag=%u", uid, static_cast<uint32_t>(proto.id), m_dataUser.total_charge_reward);
		return onTotalChargeReward(R_ERROR);
	}
	const Award *award = GiftBagConfig::getInstance()->getTotalChargeReward(proto.id + 1, m_dataUser.total_charge);
	if (award == NULL) {
		error_log("reward cfg error uid=%u id=%u charge=%u", uid, static_cast<uint32_t>(proto.id), m_dataUser.total_charge);
		return onTotalChargeReward(R_ERROR);
	}
	Award reward;
	vector<AwardInfo>::const_iterator itr = award->get().begin();
	for (; itr != award->get().end(); ++itr) {
		if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
			GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
		} else {
			reward.add(*itr);
		}
	}
	m_dataUser.total_charge_reward |= (1u << proto.id);
	savePlayerUserInfo();
	if (!doReward(&reward, "total_charge_" + CTrans::ITOS(proto.id))) {
		error_log("do reward error uid=%u id=%u charge=%u", uid, static_cast<uint32_t>(proto.id), m_dataUser.total_charge);
		return onTotalChargeReward(R_ERROR);
	}
	sendChargeReward();
	onTotalChargeReward(R_SUCCESS);
	debug_log("uid=%u id=%u flag=%u", uid, static_cast<uint32_t>(proto.id), m_dataUser.total_charge_reward);
	BUSI_MISC("resident_act|totalcharge|%u|%u|%u", m_dataUser.uid, static_cast<uint32_t>(proto.id + 1), Time::GetGlobalTime());
	return true;
}

bool Player::doSetName(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CUserSetNameProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", uid);
		return false;
	}
	bool chg = false;
	if (!proto.name.empty()) {
		m_dataUser.name = proto.name;
		String::FixUtf8Len(m_dataUser.name, 32);
		chg = true;
	}
	if (!proto.fig.empty()) {
		m_dataUser.figure_url = proto.fig;
		m_tencent_info.url = proto.fig;
		chg = true;
	}
	if (chg) {
		savePlayerUserInfo();
		doAddRank();
	}
	sendTencentUserInfo();
	return true;
}

bool Player::doFirstChargeReward(CNetPacket *packet)
{
	if (m_dataUser.first_charge_reward & (1u << 31)) {
		error_log("reward flag error uid=%u", packet->uid);
		return onFirstChargeReward(R_ERROR);
	}
	int index = 0;
	for (uint32_t i = 1; i < GiftBagConfig::getInstance()->getFirstChargeSize() + 1; ++i) {
		if (m_dataUser.first_charge_reward & (1u << (31 - i))) {
			index = i;
			break;
		}
	}
	if (index == 0) {
		error_log("charge index error uid=%u", packet->uid);
		return onFirstChargeReward(R_ERROR);
	}
	const Award *cfg = GiftBagConfig::getInstance()->getFirstChargeReward(index);
	if (cfg == NULL) {
		error_log("cfg error uid=%u id=%u", packet->uid, index);
		return onFirstChargeReward(R_ERROR);
	}
	m_dataUser.first_charge_reward |= 1u << 31;
	savePlayerUserInfo();
	Award reward_result;
	doReward(cfg, "first_charge_" + CTrans::ITOS(index), true, &reward_result);
	onFirstChargeReward(R_SUCCESS);
	sendChargeReward();
	SystemMessage::getInstance()->addFirstCharge(m_dataUser.uid, &reward_result);
	BUSI_MISC("resident_act|fcharge|%u|%u|%u", m_dataUser.uid, index, Time::GetGlobalTime());
	return true;
}

bool Player::doBuyVipGift(CNetPacket *packet)
{
	resetUserDaily();
	if (m_dataUser.daily_buy == 1) {
		error_log("buy flag error uid=%u", packet->uid);
		return onBuyVipGift(R_ERROR);
	}
	const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getWanbaVipSpecialBag(m_tencent_info.vip_level);
	if (cfg == NULL) {
		error_log("cfg error uid=%u lv=%u", packet->uid, m_tencent_info.vip_level);
		return onBuyVipGift(R_ERROR);
	}
	MoneyCost cost;
	cost.cash = cfg->require;
	string code = "buy_wanba_bag_" + CTrans::ITOS(m_tencent_info.vip_level);
	if (!m_resourceManager.useMoney(cost, code)) {
		error_log("cost error uid=%u lv=%u", packet->uid, m_tencent_info.vip_level);
		return onBuyVipGift(R_ERROR);
	}
	m_dataUser.daily_buy = 1;
	savePlayerUserInfo();
	doReward(&(cfg->award), code);
	onBuyVipGift(R_SUCCESS);
	BUSI_MISC("resident_act|wanbavipbag|%u|%u|%u", m_dataUser.uid, m_tencent_info.vip_level, Time::GetGlobalTime());
	return true;
}

bool Player::doChargeReport(CNetPacket *packet) {
	CUserChargeReportProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	BUSI_MISC("client_report|charge_report|%u|%u|%u", m_dataUser.uid, proto.id, Time::GetGlobalTime());
	return true;
}

bool Player::doInteract(CNetPacket *packet) {
	uint32_t uid = packet->uid;
	CUserInteractProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		return onInteractResp(R_ERROR, 0);
	}
	if (!IS_VALID_PLAYER_UID(proto.uid)) {
		return onInteractResp(R_ERROR, 0);
	}
	if (ServerConfig::getInstance()->IsMerged(Config::GetZoneByUID(proto.uid))) {
		Player *player = PlayerManager::getInstance()->LoadForcePlayer(proto.uid);
		if (player == NULL) {
			return onInteractResp(R_ERROR, 0);
		}
		int16_t cnt = 0;
		if (!player->onInteract(uid, m_dataUser.level, proto.type, m_dataUser.name, m_dataUser.figure_url, cnt)) {
			return onInteractResp(R_ERROR, 0);
		}
		onInteractResp(R_SUCCESS, cnt);
		BUSI_MISC("play|interact|%u|%u|%u|%u", m_dataUser.uid, proto.uid, static_cast<uint32_t>(proto.type), Time::GetGlobalTime());
		return true;
	} else {
		//XXX send to other server
		OtherServerManager::getInstance()->sendUserInteractReq(uid, proto.uid, m_dataUser.level, proto.type, m_dataUser.name, m_dataUser.figure_url);
	}
	return true;
}

bool Player::doInteractBox(CNetPacket *packet) {
	resetUserDaily();
	if (m_dataUser.help_count < MAX_USER_HELP_COUNT || m_dataUser.help_reward != 0) {
		onInteractBoxResp(R_ERROR);
	}
	m_dataUser.help_reward = 1;
	m_dataUser.help_box += 4;
	savePlayerUserInfo();
	doAutoRewardInfo(NULL);
	return true;
}

bool Player::doAddRank() {
	if (m_isAddRank) {
		return true;
	}
	m_isAddRank = true;
	RankManager::getInstance()->onLogin(m_dataUser.uid);
	m_activityManager.addExp(m_dataUser.exp, 0);
	m_activityManager.addPower(getUserCombat(), 0);
	m_activityManager.addGem(m_dataUser.gem_combat);
	return true;
}

byte Player::onHeroRecruit(byte ret, uint32_t heroId)
{
	return 0;
}
bool Player::onTrailerStageReward(uint32_t stage)
{
	const GiftBagItemConfig* pCon = GiftBagConfig::getInstance()->getConfig(stage);
	if (pCon == NULL)
	{
		error_log("getConfig fail uid=%u stage=%u", getUid(), stage);
		return false;
	}
	Award award = pCon->award;
	string reason;
	String::Format(reason, "trailer_stage_%u", stage);
	if (!doReward(&award, reason))
	{
		error_log("doReward fail uid=%u stage=%u", getUid(), stage);
		return false;
	}
	return true;
}
bool Player::onTimer() {
	if (!isFrontReady()) {
		return false;
	}
	if (!IS_VALID_PLAYER_UID(getUid())) {
		return false;
	}
	resetUserDaily();
	//onAutoReward(false);
	onBuildingTimer();
	onSoldierTimer();
	m_stateManager.onTimer();
	m_skillManager.onTimer();
	m_soldierRecoverTrain.onTimer();
	m_randomQuestManager.onTimer();
	if (m_isPropChange) {
		m_isPropChange = false;
		calcGemCombat(true);
	}
	return true;
}
bool Player::onBuildingTimer()
{
	uint32_t now = Time::GetGlobalTime();
	for (vector<Building *>::iterator it = m_bTimer.begin(); it != m_bTimer.end();)
	{
		Building * pBuilding = *it;
		if (pBuilding == NULL)
		{
			it = m_bTimer.erase(it);
			continue;
		}
		bool needSave = false;
		if (pBuilding->onRecove() && !pBuilding->needRecove()) // 恢复完成
		{
			debug_log("building recove over uid:%d ud:%d", pBuilding->getUid(), pBuilding->getUD());
			sendActionOver(PROTOCOL_CMD_BUILDING, PROTOCOL_RSP_SUBCMD_BUILDING_REPAIR_OVER, pBuilding);
			pBuilding->sendPropChange();
			needSave = true;
		}
		if (pBuilding->onProduce() && !pBuilding->needProduce()) // 资源产满
		{
			needSave = true;
		}
		if (pBuilding->getCb() > 0)
		{
			pBuilding->setCb(pBuilding->getCb() - 1);
			if (pBuilding->getCb() == 0)
			{
				debug_log("building build over uid:%d ud:%d level=%u", pBuilding->getUid(), pBuilding->getUD(), pBuilding->getLevel());
				sendActionOver(PROTOCOL_CMD_BUILDING, PROTOCOL_RSP_SUBCMD_BUILDING_BUILD_OVER, pBuilding);
				doUpgradeBuildingOver(pBuilding);
			}
		}
		if (pBuilding->getCu() > 0)
		{
			pBuilding->setCu(pBuilding->getCu() - 1);
			if (pBuilding->getCu() == 0)
			{
				debug_log("building upgrade over uid:%d ud:%d level=%u", pBuilding->getUid(), pBuilding->getUD(), pBuilding->getLevel() + 1);
				sendBuildingActionOver(PROTOCOL_CMD_BUILDING, PROTOCOL_RSP_SUBCMD_BUILDING_UPGRADE_OVER, pBuilding, pBuilding->getLevel() + 1);
				pBuilding->setLevel(pBuilding->getLevel() + 1);
				doUpgradeBuildingOver(pBuilding);
			}
		}
		pBuilding->setUpts(now);
		if (needSave)
		{
			pBuilding->saveData();
		}

		if (!pBuilding->needRecove() && !pBuilding->needProduce() && pBuilding->getCb() == 0 && pBuilding->getCu() == 0)
		{
			debug_log("erase_building uid=%u bud=%u level=%u", pBuilding->getUid(), pBuilding->getUD(), pBuilding->getLevel());
			it = m_bTimer.erase(it);
			continue;
		}
		++it;
	}
	return true;
}
bool Player::onSoldierTimer()
{
	for (vector<Soldier *>::iterator ith = m_sTimer.begin(); ith != m_sTimer.end();)
	{
		bool needSave = false;
		Soldier * pSoldier = *ith;
		if (pSoldier == NULL)
		{
			ith = m_sTimer.erase(ith);
			continue;
		}

		if (pSoldier->getCu() > 0)
		{
			pSoldier->setCu(pSoldier->getCu() - 1);
			if (pSoldier->getCu() == 0)
			{
				doUpgradeSoldierOver(pSoldier);
				needSave = true;
			}
		}
		pSoldier->setUpts(Time::GetGlobalTime());
		if (needSave)
		{
			pSoldier->saveData();
		}

		if (pSoldier->getCu() == 0) // 不需要回复，不需要升级就退出定时队列
		{
			ith = m_sTimer.erase(ith);
			continue;
		}
		++ith;
	}
	return true;
}
bool Player::onOfflineInfo()
{
	uint32_t offlineTs = 0;
	if (m_dataUser.login_time > m_dataUser.offline_time)
	{
		offlineTs = m_dataUser.login_time - m_dataUser.offline_time;
	}

	if (offlineTs < 600)
	{
		return true;
	}

	uint32_t r1 = 0, r2 = 0;
	uint32_t rob_r1 = 0, rob_r2 = 0, rob_count = 0;
	CNetPacket sRspPacket;
	sRspPacket.uid = m_dataUser.uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_USER_OFFLINE_INFO);
	selfWriter.AppendUInt32(offlineTs);
	selfWriter.AppendUInt32(r1);
	selfWriter.AppendUInt32(r2);
	selfWriter.AppendUInt32(rob_count);
	selfWriter.AppendUInt32(rob_r1);
	selfWriter.AppendUInt32(rob_r2);

	PlayerManager::getInstance()->sendToAccess(&sRspPacket);

	return true;
}
bool Player::onPlatfromGift(uint32_t giftid)
{
	return false;
}
bool Player::onAutoReward(bool offline)
{
	uint32_t ts = LogicManager::GlobalTime > m_dataUser.auto_reward_ts ? LogicManager::GlobalTime - m_dataUser.auto_reward_ts : 0;
	if (ts < AUTO_REWRAD_INTERVAL) {
		return true;
	}
	int count = 0;
	if (ts > 86400) {
		count = 86400 / AUTO_REWRAD_INTERVAL;
		m_dataUser.auto_reward_ts = LogicManager::GlobalTime;
	} else {
		count = ts / AUTO_REWRAD_INTERVAL;
		m_dataUser.auto_reward_ts += count * AUTO_REWRAD_INTERVAL;
	}
	m_dataUser.auto_reward_count += count;
	//运输次数上限，24小时8个宝箱，180次运输一个宝箱
	if (m_dataUser.auto_reward_count > 1440) {
		m_dataUser.auto_reward_count = 1440;
	}
	onInteractRecover();
	savePlayerUserInfo();
	uint32_t res = m_auto_reward_res * count;
	if (offline) {
		res += res * m_vipManager.getRight(VipManager::VIP_RIGHT_OFFLINE);
		res *= 0.5f;
	} else {
		float res_rate = (static_cast<float>(m_dataUser.help_count) / 100.0f) + m_vipManager.getRight(VipManager::VIP_RIGHT_OFFLINE);
		int tres = res * res_rate;
		if (tres < 0 && static_cast<uint32_t>(0 - tres) > res) {
			res = 0;
		} else {
			res += tres;
		}
	}
	if (res > 0) {
		upR1(res, "auto_reward");
	}

	CNetPacket sp;
	sp.uid = m_uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_AUTO_REWARD_PUSH);
	writer.AppendByte(offline ? 1 : 0);
	writer.AppendUInt32(res);
	writer.AppendUInt32(m_dataUser.auto_reward_count);
	writer.AppendUInt32(count * AUTO_REWRAD_INTERVAL);
	if (!offline || (offline && LogicManager::GlobalTime - m_dataUser.offline_time > 300)) {
		PlayerManager::getInstance()->sendToAccess(&sp);
	}
	if(!offline) {
		if(m_watchADManager.isSendRandomGift()) {
			m_watchADManager.push();
		}
	}
	return true;
}
bool Player::loadAddiction()
{
	CDataState dbState;
	DataState dataState;
	dataState.uid = m_dataUser.uid;
	dataState.id = PLAYER_DATA_STATE_ANTI_ADDICTION;
	int ret = 0;
	ret = dbState.GetState(m_dataUser.uid, PLAYER_DATA_STATE_ANTI_ADDICTION, dataState.data);
	if (ret == R_ERR_NO_DATA)
	{
		Json::Value value;
		value["addic"] = 1.0;
		dataState.data = Json::FastWriter().write(value);
		dbState.AddState(dataState);
		m_expRate = 1.0;
	}
	else if (ret == R_SUCCESS)
	{
		Json::Reader reader;
		Json::Value value;
		if (!reader.parse(dataState.data, value))
		{
			error_log("decode error uid:%d", m_dataUser.uid);
			return false;
		}
		m_expRate = value["addic"].asDouble();
	}
	return true;
}
bool Player::saveAddiction()
{
	CDataState dbState;
	DataState dataState;
	dataState.uid = m_dataUser.uid;
	dataState.id = PLAYER_DATA_STATE_ANTI_ADDICTION;
	Json::Value value;
	Json::FastWriter writer;
	value["addic"] = m_expRate;
	dataState.data = writer.write(value);
	dbState.SetState(dataState);
	return true;
}
bool Player::onFirstChargeReward(byte ret)
{
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_FIRST_CHARGE);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::onTotalChargeReward(byte ret)
{
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_TOTAL_CHARGE_REWARD);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::onBuyVipGift(byte ret)
{
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	CBufferWriter writer(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_BUY_VIP_GIFT);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::onCombatChange(int chg) {
	m_activityManager.addPower(getUserCombat(), chg);
	sendPlayerCombat();
	return true;
}
bool Player::onInteract(uint32_t uid, uint32_t lv, uint32_t type, const string &name, const string &pic, int16_t &cnt) {
	resetUserDaily();
	if(!m_interactManager.setData(uid, lv, type, name, pic)) {
		return false;
	}
	bool chg = false;
	if (type == 0) {
		if (m_dataUser.help_count < MAX_USER_HELP_COUNT) {
			m_dataUser.help_count += 1;
			chg = true;
		}
	} else {
		if (m_dataUser.help_count > MIN_USER_HELP_COUNT) {
			m_dataUser.help_count -= 1;
			chg = true;
		}
	}
	if (chg) {
		if (m_dataUser.help_count == 1 || m_dataUser.help_count == -1) {
			m_dataUser.help_ts = Time::GetGlobalTime();
		}
		savePlayerUserInfo();
	}
	cnt = m_dataUser.help_count;
	onInteractNotic(type != 0 ? 1 : 0);
	return true;
}
bool Player::onInteractNotic(byte type) {
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_HELP_NOTICE);
	PACKET_ENCODE(Int16, m_dataUser.help_count);
	PACKET_ENCODE(Byte, type);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::onInteractRecover() {
	//每小时恢复红心数，向零靠拢
	bool chg = false;
	while (m_dataUser.help_ts + Time::SECOND_OF_HOUR <= Time::GetGlobalTime()) {
		if (m_dataUser.help_count > 0) {
			m_dataUser.help_count -= 1;
			m_dataUser.help_ts += Time::SECOND_OF_HOUR;
			chg = true;
		} else if (m_dataUser.help_count < 0) {
			m_dataUser.help_count += 1;
			m_dataUser.help_ts += Time::SECOND_OF_HOUR;
			chg = true;
		} else {
			break;
		}
	}
	if (chg) {
		onInteractNotic(2);
	}
	return true;
}
bool Player::onInteractResp(byte ret, int16_t cnt) {
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_HELP);
	PACKET_ENCODE(Byte, ret);
	PACKET_ENCODE(Int16, cnt);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::onInteractBoxResp(byte ret) {
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_USER);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_USER_HELP_BOX);
	PACKET_ENCODE(Byte, ret);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
void Player::setExpRate(float expRate)
{
	m_expRate = expRate;
	saveAddiction();
}
bool Player::addTransPort(uint32_t res)
{
	resetUserDaily();
	m_dataUser.transport += res;
	RankManager::getInstance()->addRankTransport(m_uid);
	m_activityManager.addTransport(res);
	return true;
}
bool Player::setPropertyManager()
{
	m_propertyManager.setEm(&m_equipmentManager);
	m_propertyManager.setBm(&m_buildingManager);
	//m_propertyManager.setRideManager(&m_rideManager);
	m_propertyManager.setSkillManager(&m_skillManager);
	return true;
}
bool Player::addBuildingTimer(Building * pBuilding)
{
	vector<Building *>::iterator it = find(m_bTimer.begin(), m_bTimer.end(), pBuilding);
	if (it != m_bTimer.end())
	{
		return false;
	}
	m_bTimer.push_back(pBuilding);
	return true;
}

bool Player::removeBuildingTimer(Building * pBuilding)
{
	vector<Building *>::iterator it = find(m_bTimer.begin(), m_bTimer.end(), pBuilding);
	if (it != m_bTimer.end())
	{
		m_bTimer.erase(it);
		return true;
	}
	return false;
}
bool Player::addSoldierTimer(Soldier * pSoldier)
{
	vector<Soldier *>::iterator it = find(m_sTimer.begin(), m_sTimer.end(), pSoldier);
	if (it != m_sTimer.end())
	{
		return false;
	}
	m_sTimer.push_back(pSoldier);
	return true;
}
bool Player::removeSoldierTimer(Soldier * pSoldier)
{
	vector<Soldier *>::iterator it = find(m_sTimer.begin(), m_sTimer.end(), pSoldier);
	if (it != m_sTimer.end())
	{
		m_sTimer.erase(it);
		debug_log("removeSoldierTimer success uid=%u hud=%u", pSoldier->getUid(), pSoldier->getUD());
		return true;
	}
	return false;
}
bool Player::clearAllTimer()
{
	m_bTimer.clear();
	m_sTimer.clear();
	return true;
}
int Player::AddUser(const string& openId, uint32_t platform, uint32_t uid)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	DataUser user;
	user.uid = uid;
	user.register_platform = platform;
	user.register_time = Time::GetGlobalTime();
	user.login_time = Time::GetGlobalTime();
	user.offline_time = Time::GetGlobalTime();
	user.level = 1;
	if (!Json::GetUInt(*pInitJson, "exp", user.exp))
	{
		user.exp = 0;
	}
	user.bag_grid = 120;
	user.protected_time = Time::GetGlobalTime() + 3 * 3600;
	user.anti_addiction = 0;
	user.total_charge = 0;
	user.viplevel = 0;
	user.name = openId;
	user.menubar = 0;
	user.combat = 0;
	user.gem_combat = 0;
	user.tutorial_stage = 0;
	user.trailer_stage = 0;
	user.invite_by = 0;
	user.auto_reward_ts = Time::GetGlobalTime();
	user.free_equp_ts = 0;
	user.speed_up = 0;

	Json::FastWriter writer;
	CDataUser dbUser;
	ret = dbUser.AddUser(user);
	if (ret != 0)
	{
		error_log("[AddUser fail][ret=%d]", ret);
		DB_ERROR_RETURN_MSG("db_add_user_fail");
	}

	DataUserResource res;
	ret = InitailizeResource(uid, res);
	if (ret != 0)
	{
		error_log("[InitailizeResource fail][ret=%d uid=%u]", ret, uid);
		return ret;
	}
	//res.bls = BUILDING_DEFAULT_LAYOUT_SLOT;

	DataPay pay;
	ret = InitailizePay(uid, pay);
	if (ret != 0)
	{
		error_log("[InitailizePay fail][ret=%d uid=%u]", ret, uid);
		return ret;
	}

	vector<DataBuilding> db;
	ret = InitializeBuilding(uid, db);
	if (ret != 0)
	{
		error_log("[InitializeBuilding fail][ret=%d uid=%u]", ret, uid);
		return ret;
	}

	vector<DataHero> dh;
	ret = InitializeHero(uid, openId, dh);
	if (ret != 0)
	{
		error_log("[InitializeHero fail][ret=%d uid=%u]", ret, uid);
		return ret;
	}
	vector<DataSoldier> ds;
	ret = InitializeSoldier(uid, openId, ds);
	if (ret != 0)
	{
		error_log("[InitializeSoldier fail][ret=%d uid=%u]", ret, uid);
		return ret;
	}

	vector<DataEquipment> de;
	ret = InitializeEquipment(uid, de);
	if (ret != 0)
	{
		error_log("[InitializeEquipment fail][ret=%d uid=%u]", ret, uid);
		return ret;
	}

	vector<DataSkill> dskill;
	InitializeSkill(uid, dskill);

	InitializeTroops(uid);

	loadUser(user);

	m_stateManager.load(uid);
	m_equipmentManager.setData(de);
	m_soldierManager.setSoldierData(ds);
	m_buildingManager.setBuildingData(db);
	m_resourceManager.setUserResourceData(res);
	m_resourceManager.setUserPayData(pay);
	m_skillManager.setSkill(dskill);
	m_taskManager.load(uid);
	m_emailManager.load(uid);
	m_activenessManager.load(uid);
	m_skillManager.load(uid);
	m_inviteManager.load(uid);
	initTimerList();
	m_boatManager.load(uid);
	m_soldierRecoverTrain.load(uid);
	m_defendManager.load(uid);
	m_battleGateMgr.load(uid);
	m_dailyLoginManager.load(uid);
	m_vipManager.load(uid);
	m_dailyBuyManager.load(uid);
	m_randomQuestManager.load(uid);
	m_activityManager.load(uid);
	m_worldShopManager.load(uid);
	m_monthGiftManager.load(uid);
	m_chargeHistoryManager.load(uid);
	m_gemManager.load(uid);
	m_bossManager.load(uid);
	m_arenaManager.load(uid);
	m_watchADManager.load(uid);
	m_interactManager.load(uid);
	m_starBoxmanager.load(uid);
	calcCombat();
	loadAddiction();
	return 0;
}

int Player::GetInitArchive(const Json::Value *&pArchive)
{
	static uint32_t s_lastUpdateTime = 0;
	static Json::Value s_initArchive(Json::objectValue);  // 对象类型
	if (Time::GetGlobalTime() - s_lastUpdateTime > 1800)
	{
		int result;
		string archivePath = Config::GetValue("init_archive");
		if (!archivePath.empty())
		{
			string data;
			result = File::Read(archivePath, data);
			if (result != 0)
			{
				fatal_log("[init archive not exist][ret=%d,path=%s]", result, archivePath.c_str());
				DB_ERROR_RETURN_MSG("db_init_archive_fail");
			}
			Json::Reader reader;
			if (!reader.parse(data, s_initArchive))
			{
				fatal_log("[parse json fail][path=%s]", archivePath.c_str());
				DB_ERROR_RETURN_MSG("db_init_archive_fail");
			}
			s_lastUpdateTime = Time::GetGlobalTime();
		}
	}

	pArchive = &s_initArchive;

	return 0;
}

int Player::InitailizeResource(uint32_t uid, DataUserResource& res)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	if (!pInitJson->isMember("res"))
	{
		return -1;
	}
	const Json::Value &resObj = (*pInitJson)["res"];
	res.uid = uid;

	if (!Json::GetUInt(resObj, "r1", res.r1))
	{
		error_log("get r1 fail uid=%u", uid);
		return -1;
	}
	if (!Json::GetUInt(resObj, "r2", res.r2))
	{
		error_log("get r2 fail uid=%u", uid);
		return -1;
	}
	if (!Json::GetUInt(resObj, "r3", res.r3))
	{
		error_log("get r3 fail uid=%u", uid);
		return -1;
	}
	if (!Json::GetUInt(resObj, "r4", res.r4))
	{
		error_log("get r4 fail uid=%u", uid);
		return -1;
	}
	if (!Json::GetUInt(resObj, "tl", res.tl))
	{
		error_log("get tl fail uid=%u", uid);
		return -1;
	}
//
//	if (!Json::GetUInt(resObj, "hus", res.hus))
//	{
//		error_log("get hus fail uid=%u", uid);
//		return -1;
//	}
//	if (!Json::GetUInt(resObj, "hri", res.hri))
//	{
//		error_log("get hri fail uid=%u", uid);
//		return -1;
//	}
//	if (!Json::GetUInt(resObj, "sts", res.sts))
//	{
//		error_log("get sts fail uid=%u", uid);
//		return -1;
//	}

	CDataUserResource dbUserResource;
	ret = dbUserResource.Add(res);
	if (ret != 0)
	{
		error_log("[AddUserResource_fail][ret=%d]", ret);
		DB_ERROR_RETURN_MSG("db_add_user_resource_fail");
	}
	return 0;
}
int Player::InitailizePay(uint32_t uid, DataPay& pay)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	if (!pInitJson->isMember("money"))
	{
		return -1;
	}
	const Json::Value &money = (*pInitJson)["money"];
	pay.uid = uid;
	if (!Json::GetUInt(money, "cash", pay.cash))
	{
		error_log("get cash fail uid=%u", uid);
		return -1;
	}
	if (!Json::GetUInt(money, "coins", pay.coins))
	{
		error_log("get coins fail uid=%u", uid);
		return -1;
	}

	CDataPay dbPay;
	ret = dbPay.AddPay(pay);
	if (ret != 0)
	{
		fatal_log("[AddPay fail][ret=%d,uid=%u]", ret, uid);
		DB_ERROR_RETURN_MSG("add_pay_fail");
	}
	return 0;
}
int Player::InitializeBuilding(uint32_t uid, vector<DataBuilding>& db)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	if (!pInitJson->isMember("baseop"))
	{
		return 0;
	}
	const Json::Value &baseop = (*pInitJson)["baseop"];
	if (!baseop.isArray())
	{
		error_log("[init building error][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("init_building_error");
	}

	Json::FastWriter writer;
	CDataBuilding bdDB;
	uint32_t size = baseop.size();
	db.reserve(size);
	for (uint32_t i = 0; i < size; i++)
	{
		uint32_t ud = 0;
		if (!Json::GetUInt(baseop[i], "ud", ud))
		{
			error_log("[init building error][uid=%u,index=%u]", uid, i);
			DB_ERROR_RETURN_MSG("init_building_error");
		}

		DataBuilding dataBuilding;
		dataBuilding.uid = uid;
		dataBuilding.id = ud;
		dataBuilding.data = writer.write(baseop[i]);

		ret = bdDB.AddBuilding(dataBuilding);
		if (ret != 0)
		{
			error_log("[AddBuilding fail][uid=%u,id=%u,ret=%d]", uid, ud, ret);
			DB_ERROR_RETURN_MSG("add_building_fail");
		}
		db.push_back(dataBuilding);
	}
	return 0;
}
int Player::InitializeHero(uint32_t uid, const string& name, vector<DataHero>& dh)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	if (!pInitJson->isMember("hero"))
	{
		return 0;
	}
	const Json::Value &hero = (*pInitJson)["hero"];
	if (!hero.isArray())
	{
		error_log("[init hero error][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("db_init_hero_error");
	}

	Json::FastWriter writer;
	CDataHero heroDB;
	uint32_t size = hero.size();
	dh.reserve(size);
	for (uint32_t i = 0; i < size; i++)
	{
		uint32_t ud = 0;
		if (!Json::GetUInt(hero[i], "ud", ud))
		{
			error_log("[init hero error][uid=%u,index=%u]", uid, i);
			DB_ERROR_RETURN_MSG("db_init_hero_error");
		}

		DataHero dataHero;
		dataHero.uid = uid;
		dataHero.id = ud;
		dataHero.data = writer.write(hero[i]);

		/*
		 // 测试代码,正式版本得删除
		 {
		 uint32_t nameSize = name.size();
		 if(nameSize >= 3)
		 {
		 uint32_t lastNum = name[nameSize - 1] - '0';
		 if(name[nameSize - 2] == '_' && lastNum >= 1 && lastNum <= 9)
		 {
		 Json::Value tempHero = hero[i];
		 tempHero["rs"] = lastNum * 11;
		 dataHero.data = writer.write(tempHero);
		 }
		 }
		 } // end of test ????????????????????????????????????????????????????????????????????????
		 */

		ret = heroDB.AddHero(dataHero);
		if (ret != 0)
		{
			error_log("[AddHero fail][uid=%u,ud=%u,ret=%d]", uid, ud, ret);
			DB_ERROR_RETURN_MSG("db_add_hero_fail");
		}
		dh.push_back(dataHero);
	}
	return 0;
}
int Player::InitializeSoldier(uint32_t uid, const string& name, vector<DataSoldier>& ds)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	if (!pInitJson->isMember("soldier"))
	{
		return 0;
	}
	const Json::Value &soldier = (*pInitJson)["soldier"];
	if (!soldier.isArray())
	{
		error_log("[init soldier error][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("db_init_soldier_error");
	}

	Json::FastWriter writer;
	CDataSoldier soldierDB;
	uint32_t size = soldier.size();
	ds.reserve(size);
	for (uint32_t i = 0; i < size; i++)
	{
		uint32_t ud = 0;
		if (!Json::GetUInt(soldier[i], "ud", ud))
		{
			error_log("[init soldier error][uid=%u,index=%u]", uid, i);
			DB_ERROR_RETURN_MSG("db_init_soldier_error");
		}

		DataSoldier dataSoldier;
		dataSoldier.uid = uid;
		dataSoldier.id = ud;
		dataSoldier.data = writer.write(soldier[i]);

		ret = soldierDB.AddSoldier(dataSoldier);
		if (ret != 0)
		{
			error_log("[AddSoldier fail][uid=%u,ud=%u,ret=%d]", uid, ud, ret);
			DB_ERROR_RETURN_MSG("db_add_soldier_fail");
		}
		ds.push_back(dataSoldier);
	}
	return 0;
}

bool Player::initTimerList()
{
	return true;
}
bool Player::getAutoTransportRes()
{
	uint32_t res = AutoTransportManager::getInstance()->getRes(m_dataUser.uid);
	if (res == 0) {
		return false;
	}
	Building *buil = m_buildingManager.getBuildingByType(BUILDING_ID_RESOURCE_R1);
	if (buil == NULL) {
		return false;
	}
	buil->addCapacity(res);
	return true;
}
int Player::InitializeEquipment(uint32_t uid, vector<DataEquipment>& de)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	if (!pInitJson->isMember("equipment"))
	{
		return 0;
	}
	const Json::Value &equipment = (*pInitJson)["equipment"];
	if (!equipment.isArray())
	{
		error_log("[init equipment error][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("db_init_equipment_error");
	}

	Json::FastWriter writer;
	CDataEquipment equipmentDB;
	uint32_t size = equipment.size();
	de.reserve(size);
	for (uint32_t i = 0; i < size; i++)
	{
		uint32_t ud = 0;
		if (!Json::GetUInt(equipment[i], "ud", ud))
		{
			error_log("[init equipment error][uid=%u,index=%u]", uid, i);
			DB_ERROR_RETURN_MSG("db_init_equipment_error");
		}

		DataEquipment dataEquipment;
		dataEquipment.uid = uid;
		dataEquipment.id = ud;
		dataEquipment.data = writer.write(equipment[i]);
		ret = equipmentDB.AddEquipment(dataEquipment);
		if (ret != 0)
		{
			error_log("[AddEquipment fail][uid=%u,ud=%u,ret=%d]", uid, ud, ret);
			DB_ERROR_RETURN_MSG("db_add_equipment_fail");
		}
		de.push_back(dataEquipment);
	}
	return 0;
}

bool Player::doSetMenubar(CNetPacket * packet)
{
	CUserMenubarSetProtocol cs;
	if (!cs.Decode(&(packet->body)))
	{
		error_log("CUserMenubarSetProtocol decode failed, uid=%u", packet->uid);
		return false;
	}

	MAKE64(m_dataUser.menubar, cs.data2, cs.data1);

	if (!savePlayerUserInfo())
	{
		error_log("savePlayerUserInfo fail uid=%u", getUid());
	}
	/*
	 CDataUser dbUser;
	 int ret = dbUser.SetUser(m_dataUser);
	 if(ret != 0)
	 {
	 error_log("save %u's info failed,ret=%d",packet->uid, ret);
	 }
	 */
	return true;
}

bool Player::doQueryMenubar(CNetPacket * packet)
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_uid;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_MENUBAR_QUERY);
	selfWriter.AppendUInt32(U64_LOW(m_dataUser.menubar));
	selfWriter.AppendUInt32(U64_HIGH(m_dataUser.menubar));
	PlayerManager::getInstance()->sendToAccess(&sRspPacket);

	sendDoubleExpTime();
	sendLockTimes();
	return true;
}
void Player::onPlayerCombatUpdate()
{
	//ArenaManager::getInstance()->updateArenaHcombat(getUid(), getUserInfo().hcombat);
}
void Player::onPlayerNameUpdate()
{
	//ArenaManager::getInstance()->updateArenaName(getUid(), getUserInfo().name);
}
void Player::onPlayerFigureUrlUpdate()
{
	//ArenaManager::getInstance()->updateArenaFigureUrl(getUid(), getUserInfo().figure_url);
}
bool Player::upPlayerExp(int32_t exp, const string& code)
{
	if (exp == 0) {
		return true;
	}

	uint32_t oldExp = m_dataUser.exp;
	uint32_t old_lv = m_dataUser.level;

	addExp(exp);

	m_dataUser.level = ExpConfig::getInstance()->getNextUserLevel(m_dataUser.exp);

	BUSI_MISC("user_exp|code=%s|%u|%d|%d|%d|%d|%d", code.c_str(), m_uid, oldExp, exp, m_dataUser.exp, old_lv, m_dataUser.level);

	savePlayerUserInfo();
	sendPlayerInfo();

	if (old_lv != m_dataUser.level) {
		RankManager::getInstance()->onLevelChange(m_uid, old_lv);
		calcAutoRewardRes();
	} else {
		RankManager::getInstance()->addRankExp(m_uid);
	}
	m_activityManager.addExp(m_dataUser.exp, exp);
	return true;
}
bool Player::upDiamond(uint32_t diamond, const string& code)
{
	return m_resourceManager.upCash(diamond, code);
}
bool Player::upCoin(uint32_t coin, const string& code)
{
	return m_resourceManager.upCoin(coin, code);
}
bool Player::upR1(uint32_t count, const string& code)
{
	return m_resourceManager.upR1(count, code);
}
bool Player::upR2(uint32_t count, const string& code)
{
	return m_resourceManager.upR2(count, code);
}
bool Player::upR3(uint32_t count, const string& code)
{
	return m_resourceManager.upR3(count, code);
}
bool Player::upR1Rate(uint32_t rate, const string& code)
{
	return m_resourceManager.upR1Rate(rate, code);
}
bool Player::upR2Rate(uint32_t rate, const string& code)
{
	return m_resourceManager.upR2Rate(rate, code);
}
bool Player::upEnergy(uint32_t energy, const string& code)
{
	return m_resourceManager.upEnergy(energy, code);
}
bool Player::getResource(ResourceInfo & sInfo)
{
	DataUserResource * pDr = m_resourceManager.getResources();
	uint32_t cap = 0;
	if (!m_resourceManager.getResourceCapacity(cap))
	{
		error_log("getResourceCapacity fail");
	}
	if (pDr)
	{
		sInfo.r1 = pDr->r1;
		sInfo.r1_max = pDr->r1;
		sInfo.r2 = pDr->r2;
		sInfo.r2_max = pDr->r2;
		sInfo.r3 = pDr->r3;
		sInfo.r3_max = pDr->r3;
		sInfo.r4 = pDr->r4;
		sInfo.r4_max = pDr->r4;
		return true;
	}
	return false;
}
void Player::getRobResource(uint32_t aLv, ResourceInfo & sInfo)
{
	ResourceInfo resBuilding;
	map<uint32_t, Building*>& buildings = m_buildingManager.getBuilding();
	for (map<uint32_t, Building*>::iterator iter = buildings.begin(); iter != buildings.end(); ++iter)
	{
		Building* pBuilding = iter->second;
		if (pBuilding == NULL)
		{
			continue;
		}
		if (pBuilding->getType() == BUILDING_ID_RESOURCE_R1)
		{
			resBuilding.r1 += pBuilding->getCapacity();
		}
		else if (pBuilding->getType() == BUILDING_ID_RESOURCE_R2)
		{
			resBuilding.r2 += pBuilding->getCapacity();
		}
		else if (pBuilding->getType() == BUILDING_ID_BASE)
		{
			sInfo.r1 += TOWN_HALL_MAX_RES;
			sInfo.r2 += TOWN_HALL_MAX_RES;
		}
	}

	const float resBuildingRatio = 0.5f;
	sInfo.r1 += resBuilding.r1 * resBuildingRatio;
	sInfo.r2 += resBuilding.r2 * resBuildingRatio;

	const float storageBuildingRatio = 0.2f;
	DataUserResource* dur = getRm()->getResources();
	if (dur != NULL)
	{
		int32_t storageR1 = dur->r1 * storageBuildingRatio;
		int32_t storageR2 = dur->r2 * storageBuildingRatio;

		debug_log("storageR1=%u storageR2=%u", storageR1, storageR2);

		sInfo.r1 += storageR1 > STORAGE_MAX_RES ? STORAGE_MAX_RES : storageR1;
		sInfo.r2 += storageR2 > STORAGE_MAX_RES ? STORAGE_MAX_RES : storageR2;
	}
	uint32_t levelRatio = Building::getResRateByLevel(aLv, m_buildingManager.getBuildingLevel(BUILDING_ID_BASE));
	float flevelRatio = static_cast<float>(levelRatio) / 100.0f;
	sInfo.r1 *= flevelRatio;
	sInfo.r2 *= flevelRatio;

	debug_log("r1=%u r2=%u rr1=%u rr2=%u rrr1=%u rrr2=%u levelRatio=%u", resBuilding.r1, resBuilding.r2, sInfo.r1, sInfo.r2, dur->r1, dur->r2, levelRatio);
}
bool Player::setProtectedTime(uint32_t protectedTime)
{
	m_dataUser.protected_time = protectedTime;
	if (!savePlayerUserInfo())
	{
		error_log("savePlayerUserInfo fail uid=%u", getUid());
		return false;
	}
	return true;
}
uint32_t Player::getProtectedTime()
{
	return m_dataUser.protected_time;
}
void Player::calcDefenseBuildingProps()
{
	map<uint32_t, Building*>& vBuilding = m_buildingManager.getBuilding();
	for (map<uint32_t, Building*>::iterator iter = vBuilding.begin(); iter != vBuilding.end(); ++iter)
	{
		Building* pBuilding = iter->second;
		if (pBuilding != NULL && pBuilding->isDefense())
		{
			bool isFullHp = pBuilding->getHp() == pBuilding->getMaxHp();
			pBuilding->propsCalc();
			if (isFullHp)
			{
				pBuilding->setHp(pBuilding->getMaxHp());
			}
			sendBuildingInfo(pBuilding->getUD());
			debug_log("defense_building_info uid=%u ud=%u hp=%u maxHp=%u", pBuilding->getUid(), pBuilding->getUD(), pBuilding->getHp(), pBuilding->getMaxHp());
		}
	}
}
void Player::calcSoldierProps()
{
	map<uint32_t, Soldier*>& vSoldier = m_soldierManager.getSoldier();
	for (map<uint32_t, Soldier*>::iterator iter = vSoldier.begin(); iter != vSoldier.end(); ++iter)
	{
		Soldier* pSoldier = iter->second;
		if (pSoldier != NULL)
		{
			pSoldier->calcProps();
			debug_log("soldier_info uid=%u ud=%u", pSoldier->getUid(), pSoldier->getUD());
		}
	}
	getSoldierManager()->sendSoldierList();
}
bool Player::calcHeroProps(uint32_t hud)
{
	return true;
}
uint32_t Player::getRegisterDay()
{
	uint32_t now = Time::GetGlobalTime();
	uint32_t registerTime = getUserInfo().register_time;
	return now < registerTime ? 1 : ((Time::GetDayBeginTs(now) - Time::GetDayBeginTs(registerTime)) / 86400 + 1);
}
uint32_t Player::calcCombat() {
	uint32_t combat = calcSoldierCombat();
	if (combat > m_dataUser.combat) {
		m_dataUser.combat = combat;
		savePlayerUserInfo();
		if (!m_dataUser.name.empty() || !m_dataUser.figure_url.empty()) {
			RankManager::getInstance()->addRankCombat(m_dataUser.uid);
			m_activityManager.addPower(getUserCombat(), 0);
		}
		sendPlayerCombat();
	}
	return m_dataUser.combat;
}
uint32_t Player::calcGemCombat(bool save) {
	return 0;
	/*
	uint32_t combat = m_equipmentManager.calcGemPower();
	if (m_dataUser.gem_combat != combat) {
		m_dataUser.gem_combat = combat;
		m_activityManager.addGem(m_dataUser.gem_combat);
		if (save) {
			savePlayerUserInfo();
			sendPlayerCombat();
		}
	}
	return m_dataUser.gem_combat;
	*/
}
uint32_t Player::addCombat(uint32_t cnt)
{
	if (cnt == 0) {
		return m_dataUser.combat;
	}
	m_dataUser.combat += cnt;
	savePlayerUserInfo();
	if (!m_dataUser.name.empty() || !m_dataUser.figure_url.empty()) {
		RankManager::getInstance()->addRankCombat(m_dataUser.uid);
		m_activityManager.addPower(getUserCombat(), cnt);
	}
	sendPlayerCombat();
	return m_dataUser.combat;
}
uint32_t Player::calcHeroCombat()
{
	return 0;
}
uint32_t Player::calcBuildingCombat()
{
	return 0;
}
uint32_t Player::calcSoldierCombat()
{
	uint32_t combat = 0;
	map<uint32_t, Soldier*> &soldier = m_soldierManager.getSoldier();
	map<uint32_t, Soldier*>::iterator itr = soldier.begin();
	for (; itr != soldier.end(); ++itr)
	{
		Soldier *sol = itr->second;
		if (NULL == sol)
		{
			continue;
		}
		combat += Soldier::calcCombat(sol->getType(), sol->getCount());
	}
	return combat;
}
uint32_t Player::calcAutoRewardRes()
{
//	uint32_t uid = m_dataUser.uid;
//	Building *base = getBm()->getBaseBuilding();
//	if (base == NULL) {
//		error_log("base error uid=%u", uid);
//		return false;
//	}
//	uint32_t power = m_troopsManager.getDefendScore();
//	uint32_t space = 0;
//	BuildingConfig::getInstance()->getAttribute(base->getType(), base->getLevel(), space);
//	float a = static_cast<float>(space) * 0.5f;
//	float b = static_cast<float>(space) * 3.2f;
//	float score = 0;
//	if (power <= a) {
//		score = 10.0f;
//	} else if (power > a && power < b) {
//		if (space == 0) {
//			score = 0;
//		} else {
//			score = 400.0f / 27.0f * (static_cast<float>(power) / static_cast<float>(space)) + 70.0f / 27.0f;
//		}
//	} else {
//		score = 50.0f;
//	}
//
//	uint32_t boatReward = CBoatConfig::getInstance()->getReward(3, getLevel()) + CBoatConfig::getInstance()->getReward(4, getLevel());
//
//	m_auto_reward_res = score / 100.0f * static_cast<float>(boatReward) / 86400.0f * static_cast<float>(AUTO_REWRAD_INTERVAL);
//
//	debug_log("uid=%u,a=%f,b=%f,power=%u,score=%f,res=%u,m_auto_reward_res=%u", uid, a, b, power, score, boatReward, m_auto_reward_res);

	m_auto_reward_res = static_cast<float>(GateEnemyConfig::getInstance()->getData(m_battleGateMgr.getCurr())) / 60.0f;
	return m_auto_reward_res;
}
Building* Player::getBuildingTimer(uint32_t bud)
{
	vector<Building*>::iterator iter = m_bTimer.begin();
	for (; iter != m_bTimer.end(); ++iter)
	{
		Building* pBuilding = *iter;
		if (pBuilding != NULL && pBuilding->getUD() == bud)
		{
			return pBuilding;
		}
	}
	return NULL;
}

bool Player::getPay(byte payType, uint32_t pay, MoneyCost& cost)
{
	if (payType == 1)
	{
		cost.coin = pay;
	}
	else if (payType == 2)
	{
		cost.cash = pay;
	}
	else
	{
		error_log("unknow payType uid=%u payType=%u", getUid(), payType);
		return false;
	}
	return true;
}

bool Player::addTotalCharge(uint32_t money)
{
	//resetUserDaily();
	if (money > 0) {
		m_chargeHistoryManager.doCharge(money);
		m_dataUser.total_charge += money;
		//m_dataUser.daily_charge += money;
		if (!savePlayerUserInfo()) {
			error_log("savePlayerUserInfo fail uid=%u", getUid());
			return false;
		}
		sendPlayerInfo();
	}
	return true;
}

bool Player::addDailyCharge(uint32_t money)
{
	resetUserDaily();
	if (money > 0) {
		m_dataUser.daily_charge += money;
		if (!savePlayerUserInfo()) {
			error_log("savePlayerUserInfo fail uid=%u", getUid());
			return false;
		}
	}
	return true;
}

bool Player::firstCharge(uint32_t cash)
{
	uint32_t id = 0;
	if (!CShopConfig::getInstance()->getDiamondIndex(cash, id)) {
		return false;
	}

	if (isFirstCharge()) {
		//id from zero
		const Award *cfg = GiftBagConfig::getInstance()->getFirstChargeReward(id + 1);
		if (cfg != NULL) {
			m_dataUser.first_charge_reward |= (1u << (31 - 1 - id));
		}
		return true;
	}

	if (m_dataUser.first_charge_reward & (1u << id)) {
		return false;
	}
	m_dataUser.first_charge_reward |= (1u << id);
	MoneyCost cost;
	cost.cash = cash;
	m_resourceManager.addMoney(cost, "first_charge_double_" + CTrans::ITOS(id));

	return true;
}
bool Player::isFirstCharge()
{
	for (uint32_t i = 0; i < GiftBagConfig::getInstance()->getFirstChargeSize() + 1; ++i) {
		if (m_dataUser.first_charge_reward & (1u << (31 - i))) {
			return false;
		}
	}
	return true;
}
bool Player::buySpecialDiscount(uint32_t id)
{
	const SpecialDiscountItem *cfg = SpecialDiscountConfig::getInstance()->getItem(id);
	if (cfg == NULL) {
		error_log("get special discount cfg error uid=%u id=%u", m_dataUser.uid, id);
		return false;
	}
	uint32_t index = id > 0 ? id - 1 : id;
	if (m_dataUser.buy_special & (1u << index)) {
		error_log("buy flag error uid=%u id=%u flag=%u", m_dataUser.uid, id, m_dataUser.buy_special);
		return false;
	}
	m_dataUser.buy_special |= (1u << index);
	savePlayerUserInfo();
	Award reward;
	doReward(&(cfg->reward), "buy_special_discount_" + CTrans::ITOS(id), true, &reward);
	SystemMessage::getInstance()->addSpecial(getUid(), id, &reward);
	return true;
}
bool Player::save(uint32_t uid)
{
	savePlayerUserInfo();
	m_buildingManager.save(uid);
	m_equipmentManager.save(uid);
	return true;
}
//send to client
bool Player::sendBagSize()
{
	CNetPacket aPacket;
	aPacket.uid = m_dataUser.uid;
	CBufferWriter selfWriter(&aPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BAG_SIZE);
	selfWriter.AppendUInt32(m_dataUser.bag_grid);
	PlayerManager::getInstance()->sendToAccess(&aPacket);
	return true;
}
bool Player::sendActionOver(byte cmd, byte subCmd, MapObject* pMo)
{
	CNetPacket sRspPacket;
	sRspPacket.uid = pMo->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	sRspPacket.cmd = cmd;
	sRspPacket.subCmd = subCmd;
	selfWriter.AppendByte(cmd);
	selfWriter.AppendByte(subCmd);
	selfWriter.AppendByte(0); // ret
	selfWriter.AppendUInt32(pMo->getUD());
	selfWriter.AppendUInt32(0); // leftTime
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", getUid());
		return false;
	}
	debug_log("send action over cmd=%u subCmd=%u uid=%u ud=%u", cmd, subCmd, pMo->getUid(), pMo->getUD());
	return true;
}
bool Player::sendBuildingActionOver(byte cmd, byte subCmd, MapObject* pMo, uint32_t level)
{
	CNetPacket sRspPacket;
	sRspPacket.uid = pMo->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	sRspPacket.cmd = cmd;
	sRspPacket.subCmd = subCmd;
	selfWriter.AppendByte(cmd);
	selfWriter.AppendByte(subCmd);
	selfWriter.AppendByte(0); // ret
	selfWriter.AppendUInt32(pMo->getUD());
	selfWriter.AppendUInt32(0); // leftTime
	selfWriter.AppendUInt32(level); // level
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", getUid());
		return false;
	}
	debug_log("send building action over cmd=%u subCmd=%u uid=%u ud=%u", cmd, subCmd, pMo->getUid(), pMo->getUD());
	return true;
}
bool Player::sendHeroRefreshItem(uint32_t uid, byte ret)
{
	return true;
}
bool Player::sendHeroRefreshList(uint32_t uid, byte ret)
{
	return true;
}
bool Player::sendDoubleExpTime()
{
	CNetPacket rspPacket;
	rspPacket.uid = getUid();
	CBufferWriter selfWriter(&rspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_MISC);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_MISC_EXP_TIME);
	selfWriter.AppendUInt32(0);
	PlayerManager::getInstance()->sendToAccess(&rspPacket);
	return true;
}

bool Player::sendLockTimes()
{
	CNetPacket rspPacket;
	rspPacket.uid = getUid();
	CBufferWriter selfWriter(&rspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EQUIPMENT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_EQUIP_SMELT_LOCK_TIMES);
	selfWriter.AppendUInt32(0);
	PlayerManager::getInstance()->sendToAccess(&rspPacket);
	return true;
}

bool Player::sendRestTimes()
{
	CNetPacket rspPacket;
	rspPacket.uid = getUid();
	CBufferWriter selfWriter(&rspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_USER_PROTECT_TIME);
	uint32_t restTimes = getProtectedTime();
	selfWriter.AppendUInt32(restTimes);
	PlayerManager::getInstance()->sendToAccess(&rspPacket);
	return true;
}

bool Player::sendAutoRewardTs()
{
	uint32_t ts = LogicManager::GlobalTime > m_dataUser.auto_reward_ts ?
			LogicManager::GlobalTime - m_dataUser.auto_reward_ts : 0;

	CNetPacket sp;
	sp.uid = m_uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_AUTO_REWARD_TS_PUSH);
	writer.AppendUInt32(ts % AUTO_REWRAD_INTERVAL);

	PlayerManager::getInstance()->sendToAccess(&sp);

	return true;
}

bool Player::sendChargeReward()
{
	resetUserDaily();
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_CHARGE_REWARD);
	writer.AppendByte(m_dataUser.daily_charge_reward);
	writer.AppendUInt32(m_dataUser.daily_charge);

	uint32_t len = GiftBagConfig::getInstance()->getTotalChargeRewardLen();
	writer.AppendUInt32(len);
	for (uint32_t i = 0; i < len; ++i) {
		if (m_dataUser.total_charge_reward & (1u << i)) {
			writer.AppendByte(1);
		} else {
			writer.AppendByte(0);
		}
	}

	//first charge item
	len = CShopConfig::getInstance()->getDiamondSize();
	writer.AppendUInt32(len);
	for (uint32_t i = 0; i < len; ++i) {
		if (m_dataUser.first_charge_reward & (1u << i)) {
			writer.AppendByte(1);
		} else {
			writer.AppendByte(0);
		}
	}

	len = SpecialDiscountConfig::getInstance()->getSize();
	writer.AppendUInt32(len);
	for (uint32_t i = 0; i < len; ++i) {
		if (m_dataUser.buy_special & (1u << i)) {
			writer.AppendByte(1);
		} else {
			writer.AppendByte(0);
		}
	}

	//first charge
	int has_first_charge = 0;
	for (uint32_t i = 1; i <= GiftBagConfig::getInstance()->getFirstChargeSize(); ++i) {
		if (m_dataUser.first_charge_reward & (1u << (31 - i))) {
			has_first_charge = i;
			break;
		}
	}
	writer.AppendUInt32(has_first_charge);
	if (m_dataUser.first_charge_reward & (1u << 31)) {
		writer.AppendUInt32(1);
	} else {
		writer.AppendUInt32(0);
	}

	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::sendBoxScore() {
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_SOLDIER);
	writer.AppendByte(PROTOCOL_SUBCMD_SOLDIER_BOX_SCORE);
	writer.AppendUInt32(m_resourceManager.getResources()->p2);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::sendIsNewUser() {
	CNetPacket sp;
	sp.uid = m_dataUser.uid;
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_IS_NEW);
	writer.AppendUInt32(m_isNewUser ? 1 : 0);
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}
bool Player::sendUnderAttack(uint32_t uid, uint64_t & battleId)
{
	CNetPacket aPacket; 	//回包给B的客户端被攻击
	aPacket.uid = uid;
	CBufferWriter selfWriter(&aPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_BATTLE);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_BATTLE_UNDER_ATTACK);
	selfWriter.AppendDouble(battleId);
	selfWriter.AppendUInt32(uid);
	PlayerManager::getInstance()->sendToAccess(&aPacket);
	return true;
}
bool Player::sendPlayerInfo()
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_uid;
	sRspPacket.cmd = PROTOCOL_CMD_USER;
	sRspPacket.subCmd = PROTOCOL_RSP_SUBCMD_USERINFO;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_USERINFO);
	selfWriter.AppendUInt32(m_dataUser.uid);
	selfWriter.AppendUInt32(m_dataUser.register_platform);
	selfWriter.AppendUInt32(m_dataUser.register_time);
	selfWriter.AppendUInt32(m_dataUser.level);
	selfWriter.AppendUInt32(m_dataUser.exp);
	selfWriter.AppendUInt32(m_dataUser.viplevel);
	selfWriter.AppendUInt32(0);	//selfWriter.AppendUInt32(m_dataUser.kingdom);
	selfWriter.AppendUInt32(0);	//selfWriter.AppendUInt32(m_dataUser.alliance_id);
	selfWriter.AppendUInt32(m_dataUser.anti_addiction);
	selfWriter.AppendUInt32(m_dataUser.total_charge / 10);
	selfWriter.AppendUInt32(m_dataUser.protected_time);
	selfWriter.AppendUInt32(m_dataUser.bag_grid);
	selfWriter.AppendString(m_dataUser.name);
	selfWriter.AppendByte(0);
	selfWriter.AppendString(m_dataUser.figure_url);
	selfWriter.AppendByte(0);
	selfWriter.AppendUInt32(m_tencent_info.is_vip);
	selfWriter.AppendUInt32(m_tencent_info.is_year_vip);
	selfWriter.AppendUInt32(m_tencent_info.vip_level);
	selfWriter.AppendUInt32(m_dataUser.tutorial_stage);
	selfWriter.AppendUInt32(m_dataUser.trailer_stage);
	selfWriter.AppendUInt32(getUserCombat());
	selfWriter.AppendUInt32(0);	//selfWriter.AppendUInt32(m_dataUser.hcombat);
	selfWriter.AppendUInt32(0);	//selfWriter.AppendUInt32(m_dataUser.bcombat);
	selfWriter.AppendUInt32(0);	//selfWriter.AppendUInt32(m_dataUser.hero_soul);
	selfWriter.AppendUInt32(m_dataUser.offline_time);
	selfWriter.AppendByte(m_dataUser.shortcut);
	selfWriter.AppendByte(m_dataUser.daily_buy);
	selfWriter.AppendByte(m_dataUser.trailer_stage_b);
	selfWriter.AppendInt16(m_dataUser.help_count);
	selfWriter.AppendUInt32(m_dataUser.free_equp_ts);
	selfWriter.AppendByte(m_dataUser.speed_up);

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", getUid());
		return false;
	}

	return true;
}
bool Player::sendPlayerCombat()
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_dataUser.uid;
	sRspPacket.cmd = PROTOCOL_CMD_USER;
	sRspPacket.subCmd = PROTOCOL_RSP_SUBCMD_USRE_COMBAT;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_USRE_COMBAT);
	selfWriter.AppendUInt32(getUserCombat());
	selfWriter.AppendUInt32(0);	//selfWriter.AppendUInt32(m_dataUser.hcombat);
	selfWriter.AppendUInt32(0);	//selfWriter.AppendUInt32(m_dataUser.bcombat);
	PlayerManager::getInstance()->sendToAccess(&sRspPacket);
	return true;
}
bool Player::sendServerTime()
{
	LogicManager::getInstance()->sendServerTime(getUid());
	return true;
}
bool Player::sendHeroInfo(uint32_t heroUd)
{
	return true;
}
bool Player::sendSoldierInfo(uint32_t sud)
{
	return m_soldierManager.sendSoldierInfo(sud);
}
bool Player::sendSoldierListInfo()
{
	m_soldierManager.sendSoldierList();
	return true;
}
bool Player::sendBuildingInfo(uint32_t bud)
{
	Building* pBuilding = m_buildingManager.getBuilding(bud);
	if (pBuilding == NULL)
	{
		error_log("pBuilding is NULL heroUd=%u", bud);
		return false;
	}
	pBuilding->calcCombat();
	CNetPacket sPacket;
	sPacket.uid = getUid();
	CBufferWriter writer(&sPacket.body);
	writer.AppendByte(PROTOCOL_CMD_BUILDING);
	writer.AppendByte(PROTOCOL_SUBCMD_BUILDING_QUERY_ONE);
	writer.AppendByte(0);
	pBuilding->encode(&sPacket.body);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
	debug_log("send_building_info uid:%d ud:%d bp:%d range:%d", pBuilding->getUid(), pBuilding->getUD(), pBuilding->getBp(), pBuilding->getRange());
	return true;
}
bool Player::sendHeroTrainList(uint32_t uid)
{
	return true;
}
bool Player::sendTencentUserInfo()
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_uid;
	sRspPacket.cmd = PROTOCOL_CMD_USER;
	sRspPacket.subCmd = PROTOCOL_SUBCMD_USER_TENCENT_INFO;
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_USER);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_USER_TENCENT_INFO);
	selfWriter.AppendUInt32(m_dataUser.uid);
	selfWriter.AppendString(m_dataUser.name);
	selfWriter.AppendByte(0);
	selfWriter.AppendString(m_tencent_info.url);
	selfWriter.AppendByte(0);
	selfWriter.AppendUInt32(m_tencent_info.is_vip);
	selfWriter.AppendUInt32(m_tencent_info.is_year_vip);
	selfWriter.AppendUInt32(m_tencent_info.vip_level);
	selfWriter.AppendUInt32(m_tencent_info.gift);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", getUid());
		return false;
	}
	return true;
}

bool Player::sendHomeInfo()
{
	return true;
}
bool Player::sendBaseInfo()
{
	sendServerTime();
	sendPlayerInfo();
	m_soldierManager.sendSoldierList();
	m_equipmentManager.sendEquipmentList();
	m_equipmentManager.sendBagList();
	m_buildingManager.sendBuildingList();
	m_buildingManager.sendTower();
	m_buildingManager.sendTowerStar();
	m_resourceManager.sendResourceList();
	sendRestTimes();
	m_defendManager.sendInfo();
	m_battleGateMgr.sendInfo();
	//sendAutoRewardTs();
	m_troopsManager.doSend();
	sendBoxScore();
	m_gemManager.push();
	return true;
}

int Player::InitializeWorker(uint32_t uid, vector<DataWorker>& dw)
{
	const Json::Value *pInitJson = 0;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0)
	{
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	if (!pInitJson->isMember("worker"))
	{
		return 0;
	}
	const Json::Value &worker = (*pInitJson)["worker"];
	if (!worker.isArray())
	{
		error_log("[init worker error][uid=%u]", uid);
		DB_ERROR_RETURN_MSG("db_init_worker_error");
	}

	Json::FastWriter writer;
	CDataWorker workerDB;
	uint32_t size = worker.size();
	dw.reserve(size);
	for (uint32_t i = 0; i < size; i++)
	{
		uint32_t ud = 0;
		if (!Json::GetUInt(worker[i], "ud", ud))
		{
			error_log("[init worker error][uid=%u,index=%u]", uid, i);
			DB_ERROR_RETURN_MSG("db_init_worker_error");
		}

		DataWorker dataWorker;
		dataWorker.uid = uid;
		dataWorker.id = ud;
		dataWorker.data = writer.write(worker[i]);
		ret = workerDB.AddWorker(dataWorker);
		if (ret != 0)
		{
			error_log("[AddWorker fail][uid=%u,ud=%u,ret=%d]", uid, ud, ret);
			DB_ERROR_RETURN_MSG("db_add_worker_fail");
		}
		dw.push_back(dataWorker);
	}
	return 0;
}

int Player::InitializeSkill(uint32_t uid, vector<DataSkill>& datas) {
	const Json::Value *pInitJson = NULL;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0) {
		error_log("GetInitArchive_fail&uid=%u", uid);
		return ret;
	}
	const Json::Value &skill = pInitJson->get("skill", Json::Value(Json::nullValue));
	if (skill.isNull() || !skill.isArray()) {
		return R_ERR_DATA;
	}
	CDataSkill dbSkill;
	for (size_t i = 0; i < skill.size(); ++i) {
		const Json::Value &item = skill.get(i, Json::Value(Json::nullValue));
		if (item.isNull() || !item.isObject()) {
			continue;
		}
		uint16_t id = item.get("id", 0).asUInt();
		uint16_t count = item.get("count", 0).asUInt();
		if (id == 0) {
			continue;
		}
		DataSkill skillItem;
		skillItem.uid = uid;
		skillItem.skillId = id;
		skillItem.count = count;
		skillItem.level = 1;
		dbSkill.AddSkill(skillItem);
		datas.push_back(skillItem);
	}
	return 0;
}

int Player::InitializeTroops(uint32_t uid) {
	const Json::Value *pInitJson = NULL;
	int ret = GetInitArchive(pInitJson);
	if (ret != 0) {
		error_log("GetInitArchive_fail uid=%u", uid);
		return ret;
	}
	const Json::Value &troops = pInitJson->get("troops", Json::Value(Json::nullValue));
	if (troops.isNull()) {
		error_log("get troops error uid=%u", uid);
		return R_ERR_DATA;
	}
	m_troopsManager.setData(uid, troops);

	return 0;
}

bool Player::doSetBloodBankThreshold(CNetPacket* packet)
{
	return true;
}
bool Player::doUserGetBlueValidTime(CNetPacket* packet)
{
	uint32_t uid = packet->uid;
	CLoginGetBlueInfoProtocol protocol;
	if (!protocol.Decode(&(packet->body)))
	{
		error_log("CLoginGetBlueInfoProtocol decode failed, uid=%u", uid);
	}
	CNetPacket sendPacket;
	sendPacket.uid = uid;
	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> body;
	CStaticBuffer<MAX_PROTOCOL_BODY_SIZE> buffer;
	CBufferWriter writer(&body);
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_BLUE_GET);
	writer.AppendString(protocol.openId);
	writer.AppendByte(0);
	writer.AppendString(protocol.openKey);
	writer.AppendByte(0);
	writer.AppendUInt32(protocol.span_id);
	sendPacket.SetBody(&body);
	if (!sendPacket.Encode(&buffer))
	{
		error_log("encode failed uid=%u", uid);
		return false;
	}

	if (!PlayerManager::getInstance()->doTransitLogin(&sendPacket))
	{
		error_log("sendData failed uid=%u", uid);
		return false;
	}

	return true;
}
bool Player::doUserGetPayToken(CNetPacket* packet)
{
	return true;
}
void Player::checkNextDay()
{
	int day = CTime::GetDayInterval(m_dataUser.login_time, LogicManager::GlobalTime);
	if (m_onlineDay == day)
	{
		return;
	}
	m_onlineDay = day;
	m_vipManager.reset();

	CNetPacket sPacket;
	sPacket.uid = m_dataUser.uid;
	CBufferWriter writer(&sPacket.body);
	writer.AppendByte(PROTOCOL_CMD_USER);
	writer.AppendByte(PROTOCOL_SUBCMD_USER_NEXT_DAY);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
}
void Player::resetUserDaily()
{
	if (0 == CTime::GetDayInterval(m_dataUser.daily_reset_ts, LogicManager::GlobalTime)) {
		return;
	}
	if (!Time::IsThisWeek(m_dataUser.transport_reset_ts)) {
		m_dataUser.transport_reset_ts = LogicManager::GlobalTime;
		m_dataUser.transport = 0;
	}
	m_dataUser.daily_reset_ts = LogicManager::GlobalTime;
	m_dataUser.daily_charge = 0;
	m_dataUser.daily_charge_reward = 0;
	m_dataUser.defend_num = GateConfig::getInstance()->getDefendCount();
	m_dataUser.daily_buy = 0;
	m_dataUser.help_reward = 0;
	m_dataUser.help_count = 0;
}
