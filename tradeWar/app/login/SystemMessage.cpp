/*
 * SystemMessage.cpp
 *
 *  Created on: 2018年2月4日
 *      Author: Administrator
 */

#include "SystemMessage.h"
#include "Player.h"
#include "PlayerManager.h"
#include "GateConfig.h"
#include <fstream>

#define SYSTEM_MESSAGE_MAX_NUM 20

SystemMessage::SystemMessage()
{
}

SystemMessage::~SystemMessage()
{
}

bool SystemMessage::onLogin(uint32_t uid)
{
	if (!IS_VALID_PLAYER_UID(uid))
	{
		return false;
	}
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}

	m_user_items[uid] = player->getUserInfo().sys_msg_ts;

	sendMsg(uid);

	m_user_items[uid] = LogicManager::GlobalTime;
	player->getUserInfo().sys_msg_ts = m_user_items[uid];

	return true;
}

bool SystemMessage::onHeartBeat(uint32_t uid)
{
	if (m_data.empty())
	{
		return true;
	}

	if (m_user_items[uid] >= m_data.back().ts)
	{
		return true;
	}

	sendMsg(uid);

	m_user_items[uid] = LogicManager::GlobalTime;

	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}

	player->getUserInfo().sys_msg_ts = m_user_items[uid];

	return true;
}

bool SystemMessage::init()
{
	SysgemMsg::SysgemMsg *msg = new SysgemMsg::SysgemMsg();
	if (msg == NULL)
	{
		return false;
	}
	string path;
	String::Format(path, Config::GetValue(CONFIG_SYS_MSG_DATA).c_str(), Config::GetValue("server_id").c_str());
	fstream input(path.c_str(), ios::in | ios::binary);
	if (!input.good())
	{
		delete msg;
		return false;
	}

	msg->ParseFromIstream(&input);

	for (int i = 0; i < msg->items_size(); ++i)
	{
		SystemMessageInfo info;
		info.parse(msg->items(i));
		m_data.push_back(info);
	}

	while (m_data.size() > SYSTEM_MESSAGE_MAX_NUM)
	{
		m_data.pop_front();
	}

	delete msg;

	return true;
}

bool SystemMessage::save()
{
	SysgemMsg::SysgemMsg *msg = new SysgemMsg::SysgemMsg();
	if (msg == NULL)
	{
		return false;
	}

	list<SystemMessageInfo>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr)
	{
		itr->Serialize(msg->add_items());
	}

	string path;
	String::Format(path, Config::GetValue(CONFIG_SYS_MSG_DATA).c_str(), Config::GetValue("server_id").c_str());
	fstream output(path.c_str(), ios::out | ios::binary);
	if (!output.good())
	{
		delete msg;
		return false;
	}

	msg->SerializeToOstream(&output);

	return true;
}

bool SystemMessage::addGate(uint32_t uid, uint32_t level)
{
	Player * player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}
	uint32_t m = GateConfig::getInstance()->isOpenMap(level);
	if (m > 0)
	{
		SystemMessageInfo unlockArea;
		unlockArea.ts = LogicManager::GlobalTime;
		unlockArea.uid = uid;
		unlockArea.user_name = player->getUserInfo().name;
		unlockArea.msg[SystemMessageDataProType] = SystemMessageGate;
		unlockArea.msg[SystemMessageDataProLevel] = m;
		m_data.push_back(unlockArea);
	}

	return true;
}

bool SystemMessage::addBuyBag(uint32_t uid, uint32_t id, const Award *award) {
	Player * player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageBuyBag;
	msg.msg[SystemMessageDataProId] = id;
	msg.reward.clear();
	Award::mergeAward(award->get(), msg.reward);
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::addBoatBag(uint32_t uid, uint32_t id, const Award *award) {
	Player * player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageBoatBag;
	msg.msg[SystemMessageDataProId] = id;
	msg.reward.clear();
	Award::mergeAward(award->get(), msg.reward);
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::addBuyVip(uint32_t uid, uint32_t id) {
	Player * player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageVip;
	msg.msg[SystemMessageDataProId] = id;
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::addRob(uint32_t uid, uint32_t id, uint32_t res) {
	Player * player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}
	Player * oplayer = PlayerManager::getInstance()->LoadForcePlayer(id);
	if (oplayer == NULL)
	{
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.defend_name = oplayer->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageRob;
	msg.msg[SystemMessageDataProR2] = res;
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::addSpecial(uint32_t uid, uint32_t id, const Award *award) {
	Player * player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL)
	{
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageBuySpecial;
	msg.msg[SystemMessageDataProId] = id;
	msg.reward.clear();
	Award::mergeAward(award->get(), msg.reward);
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::addTimeLimitBag(uint32_t uid, uint32_t id, const Award *award) {
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageTimeLimitBag;
	msg.msg[SystemMessageDataProId] = id;
	msg.reward.clear();
	Award::mergeAward(award->get(), msg.reward);
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::addDeserveBag(uint32_t uid, uint32_t id) {
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageDeserveBag;
	msg.msg[SystemMessageDataProId] = id;
	msg.reward.clear();
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::addFirstCharge(uint32_t uid, const Award *award) {
	Player *player = PlayerManager::getInstance()->LoadForcePlayer(uid);
	if (player == NULL) {
		return false;
	}
	SystemMessageInfo msg;
	msg.ts = LogicManager::GlobalTime;
	msg.uid = uid;
	msg.user_name = player->getName();
	msg.msg[SystemMessageDataProType] = SystemMessageFirstCharge;
	msg.reward.clear();
	Award::mergeAward(award->get(), msg.reward);
	m_data.push_back(msg);
	return true;
}

bool SystemMessage::sendMsg(uint32_t uid)
{
	vector<SystemMessageSend> datas;
	getMessage(m_user_items[uid], datas);

	CNetPacket spacket;
	spacket.uid = uid;
	spacket.cmd = PROTOCOL_CMD_MISC;
	spacket.subCmd = PROTOCOL_SUBCMD_MISC_SYSTEM_MSG;

	CBufferWriter writer(&(spacket.body));
	writer.AppendByte(PROTOCOL_CMD_MISC);
	writer.AppendByte(PROTOCOL_SUBCMD_MISC_SYSTEM_MSG);
	writer.AppendUInt32(datas.size());
	vector<SystemMessageSend>::iterator itr = datas.begin();
	for (; itr != datas.end(); ++itr)
	{
		writer.AppendUInt32(itr->uid);
		writer.AppendUInt32(itr->ts);
		writer.AppendString(itr->user_name);
		writer.AppendByte(0);
		writer.AppendString(Json::ToString(itr->msg));
		writer.AppendByte(0);
	}

	PlayerManager::getInstance()->sendToAccess(&spacket);

	return true;
}

void SystemMessage::getMessage(uint32_t ts, vector<SystemMessageSend> &datas)
{
	list<SystemMessageInfo>::iterator itr = m_data.begin();
	for (; itr != m_data.end(); ++itr)
	{
		if (itr->ts < ts)
		{
			continue;
		}
		SystemMessageSend data;
		data.uid = itr->uid;
		data.ts = itr->ts;
		data.user_name = itr->user_name;
		Json::Value value;
		if (itr->msg.count(SystemMessageDataProType))
		{
			value = Json::Value(Json::objectValue);
			switch(itr->msg[SystemMessageDataProType])
			{
			case SystemMessageGate:
				value["gate"]["id"] = itr->msg.count(SystemMessageDataProLevel) ? itr->msg[SystemMessageDataProLevel] : 0;
				break;
			case SystemMessageBuyBag:
				value["buybag"]["reward"] = Award::Award2Json(itr->reward);
				value["buybag"]["id"] = itr->msg.count(SystemMessageDataProId) ? itr->msg[SystemMessageDataProId] : 0;
				break;
			case SystemMessageBoatBag:
				value["boatbag"]["id"] = itr->msg.count(SystemMessageDataProId) ? itr->msg[SystemMessageDataProId] : 0;
				value["boatbag"]["reward"] = Award::Award2Json(itr->reward);
				break;
			case SystemMessageVip:
				value["vip"]["id"] = itr->msg.count(SystemMessageDataProId) ? itr->msg[SystemMessageDataProId] : 0;
				break;
			case SystemMessageRob:
				value["rob"]["res"] = itr->msg.count(SystemMessageDataProR2) ? itr->msg[SystemMessageDataProR2] : 0;
				value["rob"]["defend"] = itr->defend_name;
				break;
			case SystemMessageBuySpecial:
				value["special"]["id"] = itr->msg.count(SystemMessageDataProId) ? itr->msg[SystemMessageDataProId] : 0;
				value["special"]["reward"] = Award::Award2Json(itr->reward);
				break;
			case SystemMessageTimeLimitBag:
				value["timelimitbag"]["id"] = itr->msg.count(SystemMessageDataProId) ? itr->msg[SystemMessageDataProId] : 0;
				value["timelimitbag"]["reward"] = Award::Award2Json(itr->reward);
				break;
			case SystemMessageDeserveBag:
				value["deservebag"]["id"] = itr->msg.count(SystemMessageDataProId) ? itr->msg[SystemMessageDataProId] : 0;
				break;
			case SystemMessageFirstCharge:
				value["firstcharge"]["reward"] = Award::Award2Json(itr->reward);
				break;
			default:
				value = Json::Value(Json::nullValue);
				break;
			}
		}
		else
		{
			value = Json::Value(Json::nullValue);
		}

		if (!value.isNull())
		{
			data.msg = value;
			datas.push_back(data);
		}
	}
}


