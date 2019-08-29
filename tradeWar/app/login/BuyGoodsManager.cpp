/*
 * BuyGoodsManager.cpp
 *
 *  Created on: 2016-3-17
 *      Author: Administrator
 */

#include "BuyGoodsManager.h"
#include "LanguageConfig.h"
#include "GiftBagConfig.h"
#include "PlayerManager.h"
#include "PayConfig.h"

bool BuyGoodsManager::doTransitRequest(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_TRANSIT_GET_BALANCE:
		doGetBalanceRes(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_PAY:
		doPayRes(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_GIFT_EXHANGE:
		doGiftExchangeRes(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_PER_ORDER:
		doPerOrderRes(packet);
		break;
	default:
		break;
	}
	return true;
}
bool BuyGoodsManager::doLoginRequest(CNetPacket *packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_TRANSIT_GET_BALANCE:
		doGetBalance(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_PAY:
		doPay(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_GIFT_EXHANGE:
		doGiftExchange(packet);
		break;
	case PROTOCOL_SUBCMD_TRANSIT_PER_ORDER:
		doPerOrder(packet);
		break;
	default:
		break;
	}
	debug_log("subcmd=%d", static_cast<int>(packet->subCmd));
	return true;
}
bool BuyGoodsManager::doGetBalance(CNetPacket *packet) {
	CBuyGoodGetBalanceProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(packet->uid);
	if (!player) {
		error_log("load player error uid=%u", packet->uid);
		return false;
	}
	CNetPacket sendPacket;
	sendPacket.clientIp = packet->clientIp;
	sendPacket.uid = packet->uid;
	CBufferWriter writer(sendPacket.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_GET_BALANCE);
	writer.AppendUInt32(packet->uid);
	writer.AppendString(proto.openId);
	writer.AppendByte(0);
	writer.AppendString(proto.openKey);
	writer.AppendByte(0);
	writer.AppendString(proto.pf);
	writer.AppendByte(0);
	writer.AppendUInt32(proto.platform);
	writer.AppendUInt32(LogicManager::ServerId);

	PlayerManager::getInstance()->sendToTransit(&sendPacket);
	debug_log("doGetWanBaScore uid=%u platform=%u ip=%d", packet->uid, proto.platform, packet->clientIp);
	return true;
}
bool BuyGoodsManager::doGetBalanceRes(CNetPacket *packet) {
	CBuyGoodGetBalanceResProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(protocol.uid);
	if (player == NULL) {
		error_log("load player error uid=%u uid=%u", protocol.uid, packet->uid);
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_TRANSIT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_TRANSIT_GET_BALANCE);
	selfWriter.AppendByte(protocol.code);
	selfWriter.AppendUInt32(protocol.score);
	selfWriter.AppendString(protocol.mpid);
	selfWriter.AppendByte(0);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
	debug_log("uid=%u code=%d score=%u", protocol.uid, static_cast<int>(protocol.code), protocol.score);
	return true;
}
bool BuyGoodsManager::doPay(CNetPacket *packet) {
	CBuyGoodPayProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(packet->uid);
	if (!player) {
		error_log("load player error uid=%u", packet->uid);
		return false;
	}

	CNetPacket sendPacket;
	sendPacket.clientIp = packet->clientIp;
	sendPacket.uid = packet->uid;
	CBufferWriter writer(sendPacket.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_PAY);
	writer.AppendUInt32(packet->uid);
	writer.AppendString(protocol.openId);
	writer.AppendByte(0);
	writer.AppendString(protocol.openKey);
	writer.AppendByte(0);
	writer.AppendString(protocol.pf);
	writer.AppendByte(0);
	writer.AppendUInt32(protocol.platform);
	writer.AppendUInt32(LogicManager::ServerId);
	writer.AppendUInt32(protocol.itemId);
	writer.AppendUInt32(protocol.count);

	PlayerManager::getInstance()->sendToTransit(&sendPacket);

	BUSI_TOKEN("%u|%u|%u|%s", LogicManager::ServerId, player->getUid(), protocol.itemId, "clickBuy");

	return true;
}
bool BuyGoodsManager::doPayRes(CNetPacket *packet) {
	CBuyGoodPayResProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	uint32_t uid = protocol.uid;
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (!player) {
		BUSI_TOKEN("%u|%u|%u|%d|%s|%s", LogicManager::ServerId, protocol.uid, protocol.cash, protocol.cost, protocol.billon.c_str(), "deliverfailed");
		return false;
	}

	if (protocol.code == 0) {
		if (protocol.cash > 0 && !player->isFirstCharge()) {
			MoneyCost cost;
			cost.coin = 0;
			cost.cash = protocol.cash;
			player->getRm()->addMoney(cost, "WANBATOP");
		}
		onPay(uid, protocol.cash, protocol.itemid);
	}

	CNetPacket sPacket;
	sPacket.uid = player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_TRANSIT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_TRANSIT_PAY);
	selfWriter.AppendByte(protocol.code);
	selfWriter.AppendUInt32(protocol.itemid);

	PlayerManager::getInstance()->sendToAccess(&sPacket);

	debug_log("uid=%u code=%d itemid=%u", protocol.uid, static_cast<int>(protocol.code), protocol.itemid);
	return true;
}
bool BuyGoodsManager::doGiftExchange(CNetPacket *packet) {
	CTransitGiftExhangeProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	CNetPacket sp;
	sp.uid = packet->uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_TRANSIT);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_TRANSIT_GIFT_EXHANGE);
	PACKET_ENCODE(String, proto.openid);
	PACKET_ENCODE(String, proto.openkey);
	PACKET_ENCODE(String, proto.pf);
	PACKET_ENCODE(UInt32, proto.giftid);
	PlayerManager::getInstance()->sendToTransit(packet);
	return true;
}
bool BuyGoodsManager::doGiftExchangeRes(CNetPacket *packet) {
	CTransitGiftExhangeResProtocol proto;
	if (!proto.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Award result;
	if (proto.code == 0) {
		//TODO gift reward
		do {
			const ChargeRewardConfig *cfg = GiftBagConfig::getInstance()->getWanbaVipDailyBag(proto.giftid);
			if (cfg == NULL) {
				break;
			}
			Player *playe = PlayerManager::getInstance()->LoadExistPlayer(packet->uid);
			if (playe == NULL) {
				break;
			}
			Award reward;
			GiftBagConfig::getInstance()->openAll(cfg->award.get(), reward);
			playe->doReward(&reward, "wanba_gift_" + CTrans::ITOS(proto.giftid), false, &result);
		} while(false);
	}
	CNetPacket sp;
	sp.uid = packet->uid;
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_TRANSIT);
	PACKET_ENCODE(Byte, PROTOCOL_SUBCMD_TRANSIT_GIFT_EXHANGE);
	PACKET_ENCODE(Int32, proto.code);
	PACKET_ENCODE(UInt32, proto.giftid);
	result.packetData(writer);
	PlayerManager::getInstance()->sendToAccess(&sp);
	debug_log("uid=%u code=%d giftid=%u", packet->uid, proto.code, proto.giftid);
	return true;
}
bool BuyGoodsManager::doAdminCharge(uint32_t uid, uint32_t cash, uint32_t itemid) {
	onPay(uid, cash, itemid);
	return true;
}

bool BuyGoodsManager::doPerOrder(CNetPacket *packet) {
	CBuyGoodPerOrderProtocol protocol;
	if(!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(packet->uid);
	if(!player) {
		error_log("load player error uid=%u", packet->uid);
		return false;
	}
	CNetPacket sendPacket;
	sendPacket.clientIp = packet->clientIp;
	sendPacket.uid = packet->uid;
	CBufferWriter writer(sendPacket.GetBody());
	writer.AppendByte(PROTOCOL_CMD_TRANSIT);
	writer.AppendByte(PROTOCOL_SUBCMD_TRANSIT_PER_ORDER);
	writer.AppendUInt32(packet->uid);
	writer.AppendString(protocol.openId);
	writer.AppendByte(0);
	writer.AppendString(protocol.openKey);
	writer.AppendByte(0);
	writer.AppendString(protocol.pf);
	writer.AppendByte(0);
	writer.AppendUInt32(protocol.goodId);
	writer.AppendUInt32(protocol.goodCount);
	writer.AppendUInt32(LogicManager::ServerId);

	PlayerManager::getInstance()->sendToTransit(&sendPacket);
	debug_log("doPerOrder uid=%u pf=%s ip=%d", packet->uid, protocol.pf.c_str(), packet->clientIp);
	return true;
}

bool BuyGoodsManager::doPerOrderRes(CNetPacket *packet) {
	CBuyGoodPerOrderResProtocol protocol;
	if (!protocol.Decode(packet->GetBody())) {
		error_log("decode error uid=%u", packet->uid);
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(protocol.uid);
	if (player == NULL) {
		error_log("load player error uid=%u uid=%u", protocol.uid, packet->uid);
		return false;
	}
	CNetPacket sPacket;
	sPacket.uid = player->getUid();
	CBufferWriter selfWriter(&sPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_TRANSIT);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_TRANSIT_PER_ORDER);
	selfWriter.AppendByte(protocol.code);
	selfWriter.AppendString(protocol.prepayId);
	selfWriter.AppendByte(0);
	selfWriter.AppendUInt32(protocol.amt);

	PlayerManager::getInstance()->sendToAccess(&sPacket);
	debug_log("uid=%u prepayId=%s amt=%u", protocol.uid, protocol.prepayId.c_str(), protocol.amt);
	return true;
}

void BuyGoodsManager::onPay(uint32_t uid, uint32_t cash, uint32_t itemid) {
	Player *player = PlayerManager::getInstance()->LoadExistPlayer(uid);
	if (!player) {
		error_log("load player error uid=%u itemid=%u", uid, itemid);
		return;
	}
	const PayItem *cfg = PayConfig::getInstance()->getItem(itemid);
	if (cfg == NULL) {
		error_log("get cfg error uid=%u itemid=%u", uid, itemid);
		return;
	}
	player->addTotalCharge(cfg->money);
	player->firstCharge(cash);
	switch (cfg->type) {
	case PayTypeVip:
		player->getVipManager()->buy(cfg->gift);
		break;
	case PayTypeSpecial:
		player->buySpecialDiscount(cfg->gift);
		break;
	case PayTypeSevenTask:
		player->getActManager()->setBuyFlag();
		break;
	case PayTypeDailyCharge:
		player->addDailyCharge(1);
		break;
	case PayTypeMonthGift:
		player->getMonthGiftManager()->buy(cfg->gift);
		break;
	}
	player->sendChargeReward();
	player->getActManager()->onCharge();
}

