#include "ActivenessManager.h"
#include "LogicManager.h"
#include "Player.h"
#include "DailyQuestConfig.h"
#include "GiftBagConfig.h"

ActivenessManager::ActivenessManager(): m_player(NULL), m_score(0), m_resetTs(0), m_reward(0), m_sync(false)
{
}

ActivenessManager::~ActivenessManager()
{
}

bool ActivenessManager::doPacket(CNetPacket *packet)
{
	switch (packet->subCmd)
	{
	case PROTOCOL_SUBCMD_DAILY_TASK_PROCESS:
		doView(packet);
		break;
	case PROTOCOL_SUBCMD_DAILY_TASK_ACTIVE:
		doBuy(packet);
		break;
	case PROTOCOL_SUBCMD_DAILY_TASK_SYN_CHAT:
		//onChat();
		break;
	case PROTOCOL_SUBCMD_DAILY_TASK_FINISH:
		doFinish(packet);
		break;
	case PROTOCOL_SUBCMD_DAILY_TASK_REWARD:
		doReward(packet);
		break;
	default:
		break;
	}
	return true;
}

bool ActivenessManager::checkData()
{
	set<uint32_t> ids;
	DailyQuestConfig::getInstance()->getItemIds(ids);
	if (m_msg.size() == ids.size())
	{
		return true;
	}

	for (set<uint32_t>::iterator itr = ids.begin(); itr != ids.end(); ++itr)
	{
		vector<ActivenessMsg>::iterator it = find(m_msg.begin(), m_msg.end(), *itr);
		if (it == m_msg.end())
		{
			ActivenessMsg msg;
			msg.id = *itr;
			m_msg.push_back(msg);
			m_sync = true;
		}
	}

	return true;
}

bool ActivenessManager::resetData()
{
	if (CTime::GetDayInterval(m_resetTs, LogicManager::GlobalTime) == 0)
	{
		return true;
	}
	m_score = 0;
	m_resetTs = LogicManager::GlobalTime;
	m_reward = 0;
	m_msg.clear();
	set<uint32_t> ids;
	DailyQuestConfig::getInstance()->getItemIds(ids);
	for (set<uint32_t>::iterator itr = ids.begin(); itr != ids.end(); ++itr)
	{
		ActivenessMsg msg;
		msg.id = *itr;
		m_msg.push_back(msg);
	}
	m_sync = true;
	return true;
}

bool ActivenessManager::saveData(bool isAdd)
{
	if (!m_sync)
	{
		return true;
	}

	DataActiveness data;
	data.uid = m_player->getUid();
	data.score = m_score;
	data.ts = m_resetTs;
	data.reward = m_reward;
	Json::Value value = Json::Value(Json::arrayValue);
	value.resize(0);
	vector<ActivenessMsg>::iterator itr = m_msg.begin();
	for (; itr != m_msg.end(); ++itr)
	{
		Json::Value item;
		itr->toJson(item);
		value.append(item);
	}
	data.data = Json::ToString(value);

	CDataActiveness dbActiveness;
	if (isAdd)
	{
		dbActiveness.AddActiveness(data);
	}
	else
	{
		dbActiveness.UpdateActiveness(data);
	}

	return true;
}

bool ActivenessManager::load(uint32_t uid)
{
	CDataActiveness dbActiveness;
	DataActiveness data;
	int ret = dbActiveness.GetActiveness(uid, data);
	if (0 != ret && ret != R_ERR_NO_DATA)
	{
		error_log("dbActiveness getActiveness failed by uid=%u", uid);
		return false;
	}
	if (R_ERR_NO_DATA == ret)
	{
		data.Clear();
	}

	m_resetTs = data.ts;
	m_score = data.score;
	m_reward = data.reward;

	Json::Value value;
	Json::Reader reader;
	if (reader.parse(data.data, value) && value.isArray())
	{
		m_msg.clear();
		for (size_t i = 0; i < value.size(); ++i)
		{
			ActivenessMsg msg;
			msg.fromJson(value[i]);
			m_msg.push_back(msg);
		}
	}

	if (CTime::GetDayInterval(m_resetTs, LogicManager::GlobalTime) != 0)
	{
		resetData();
	}
	else
	{
		checkData();
	}

	saveData(R_ERR_NO_DATA == ret);

	return true;
}

bool ActivenessManager::onAttack()
{
	return doProgress(ACTIVENESS_ATTACK, 1);
}

bool ActivenessManager::onBoat()
{
	return doProgress(ACTIVENESS_BOAT, 1);
}

bool ActivenessManager::onGate()
{
	return doProgress(ACTIVENESS_GATE);
}

bool ActivenessManager::onHarvest()
{
	return doProgress(ACTIVENESS_HARVEST, 1);
}

bool ActivenessManager::onZhen()
{
	return doProgress(ACTIVENESS_ZHEN, 1);
}

bool ActivenessManager::onBuild()
{
	return doProgress(ACTIVENESS_BUILD, 1);
}

bool ActivenessManager::onUpSoldier()
{
	return doProgress(ACTIVENESS_UPSOLDIER, 1);
}

bool ActivenessManager::onZhengWu()
{
	return doProgress(ACTIVENESS_ZhengWu, 1);
}

bool ActivenessManager::setValue(uint32_t id, uint32_t value)
{
	if (m_player == NULL)
	{
		error_log("m_player is NULL");
		return false;
	}
	vector<ActivenessMsg>::iterator itr = find(m_msg.begin(), m_msg.end(), id);
	if (itr == m_msg.end())
	{
		return false;
	}
	if (itr->count != value)
	{
		itr->count = value;
		m_sync = true;
	}
	return true;
}

bool ActivenessManager::getValue(uint32_t id, uint32_t &value)
{
	value = 0;
	if (m_player == NULL)
	{
		error_log("m_player is NULL");
		return false;
	}
	vector<ActivenessMsg>::iterator itr = find(m_msg.begin(), m_msg.end(), id);
	if (itr == m_msg.end())
	{
		return false;
	}
	value = itr->count;
	return true;
}

bool ActivenessManager::doProgress(uint32_t id, uint32_t count)
{
	if (m_player == NULL)
	{
		error_log("m_player is NULL");
		return false;
	}

	resetData();

	if (m_player->getUserInfo().tutorial_stage < 10000)
	{
		return true;
	}

	uint32_t values = 0;
	if (!getValue(id, values))
	{
		error_log("getActivinessValue error id=%d", id);
		return false;
	}

	const DailyQuestItem *pConfig = DailyQuestConfig::getInstance()->getItem(id);
	if (pConfig == NULL)
	{
		error_log("get config error type=%d", id);
		return false;
	}

	values += count;

	setValue(id, values);

	if (m_sync)
	{
		saveData();
		sendData();
		sendScore();
	}

	return true;
}

bool ActivenessManager::doView(CNetPacket *packet)
{
	resetData();
	sendData();
	sendScore();
	return true;
}

bool ActivenessManager::sendScore()
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_DAILY_TASK);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_DAILY_TASK_ACTIVE);
	selfWriter.AppendInt32(m_score);
	uint32_t num = DailyQuestConfig::getInstance()->getRewardSize();
	selfWriter.AppendInt32(num);
	for (uint32_t i = 0; i < num; ++i)
	{
		byte flag = (m_reward & (1u << i)) ? 1 : 0;
		selfWriter.AppendByte(flag);
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool ActivenessManager::sendData()
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_DAILY_TASK);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_DAILY_TASK_PROCESS);
	selfWriter.AppendInt32(m_resetTs);
	selfWriter.AppendInt32(m_msg.size());
	vector<ActivenessMsg>::iterator it = m_msg.begin();
	for (; it != m_msg.end(); ++it)
	{
		byte id = it->id;
		selfWriter.AppendByte(id);
		selfWriter.AppendInt32(it->count);
		selfWriter.AppendByte(it->finish);
	}
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

bool ActivenessManager::doBuy(CNetPacket *packet)
{
	/*	CActivenessBuyProtocol activenessBuy;
	 if(!activenessBuy.Decode(&packet->body)){
	 error_log("CActivenessBuyProtocol decode failed by uid=%u", packet->uid);
	 return false;
	 }

	 map<uint32_t, DataActiveness>::iterator iter = m_activenessMap.find(packet->uid);
	 if(iter == m_activenessMap.end())
	 {
	 return false;
	 }

	 map<int, ActivenessComplete>::iterator it = m_completeMap.find(activenessBuy.id);
	 if(it == m_completeMap.end()){
	 return false;
	 }

	 //	if(iter->second.value[activenessBuy.id-1].empty()){
	 //		return false;
	 //	}

	 if(iter->second.value[activenessBuy.id-1]["v"].asInt() >= it->second.value){
	 return true;
	 }

	 Human *pHuman = MapManager::getInstance()->getHuman(packet->uid);
	 if(pHuman == NULL){
	 return false;
	 }

	 if(pHuman->getMoney(AP_NOT_BIND_YUANBAO) < it->second.money){
	 LogicManager::getInstance().sendSystemMsg(packet->uid, packet->uid, TIP_POS_CENTER, GET_LANG("no_yb"));
	 return false;
	 }

	 if(!Time::IsToday(iter->second.time)){
	 initActivenessStat(packet->uid, iter->second);
	 }

	 PropertySets changeProps;
	 changeProps[AP_NOT_BIND_YUANBAO].pi = -it->second.money;
	 if(!pHuman->updateMoney(changeProps,"activenessBuy")){
	 error_log("updateMoney failed by uid=%u", packet->uid);
	 return false;
	 }

	 finishTask(activenessBuy.id, iter->second, it->second.activeness, it->second.value);
	 CDataActiveness dbActiveness;
	 if(0 != dbActiveness.updateActiveness(iter->second))
	 {
	 error_log("dbActiveness updateActiveness failed by uid=%u", pHuman->getRid());
	 return false;
	 }

	 return sendActivenessMsg(packet->uid, packet->uid, iter->second);*/
	return true;
}

bool ActivenessManager::doFinish(CNetPacket *packet)
{
	uint32_t uid = packet->uid;
	DailyQuestFinishProtocol protocol;
	if (!protocol.Decode(&(packet->body)))
	{
		error_log("Decode error, uid=%u", uid);
		onFinishResp(1);
		return false;
	}
	resetData();
	uint32_t id = protocol.index;
	vector<ActivenessMsg>::iterator itr = find(m_msg.begin(), m_msg.end(), id);
	if (itr == m_msg.end())
	{
		error_log("id not exists, id=%u uid=%u", id, uid);
		onFinishResp(1);
		return false;
	}
	const DailyQuestItem *pConfig = DailyQuestConfig::getInstance()->getItem(id);
	if (pConfig == NULL)
	{
		error_log("config not exists, id=%u uid=%u", id, uid);
		onFinishResp(1);
		return false;
	}
	if (itr->count < pConfig->count)
	{
		error_log("count error, id=%u uid=%u count=%u need=%u", id, uid, itr->count, pConfig->count);
		onFinishResp(1);
		return false;
	}
	if (itr->finish == ACTIVENESS_FLAG_FINISH)
	{
		error_log("finish error, id=%u uid=%u", id, uid);
		onFinishResp(1);
		return false;
	}
	itr->finish = ACTIVENESS_FLAG_FINISH;
	m_score += pConfig->score;
	m_sync = true;
	saveData();
	m_player->doReward(&(pConfig->reward), "daily_task_" + CTrans::ITOS(id));
	onFinishResp(0, id);
	sendData();
	sendScore();

	return true;
}

bool ActivenessManager::onFinishResp(byte ret, uint32_t id)
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_DAILY_TASK);
	selfWriter.AppendByte(PROTOCOL_RSP_SUBCMD_DAILY_TASK_FINISH);
	selfWriter.AppendInt32(ret);
	selfWriter.AppendInt32(id);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
	}
	return true;
}

bool ActivenessManager::doReward(CNetPacket *packet)
{
	uint32_t uid = packet->uid;
	DailyQuestRewardProtocol protocol;
	if (!protocol.Decode(&(packet->body)))
	{
		error_log("DailyQuestRewardProtocol error!uid=%u", uid);
		onRewardResp(1);
		return false;
	}

	resetData();

	uint32_t index = protocol.index;

	const DailyQuestReward *pReward = DailyQuestConfig::getInstance()->getReward(protocol.index);
	if (pReward == NULL || pReward->score > m_score)
	{
		error_log("reward error uid=%u index=%u score=%u need=%u",
				uid, index, m_score, (pReward == NULL ? 0 : pReward->score));
		onRewardResp(1);
		return false;
	}

	if (m_reward & (1u << index))
	{
		error_log("reward error uid=%u index=%u flag=%u", uid, index, m_reward);
		onRewardResp(1);
		return false;
	}

	m_reward |= (1u << index);

	m_sync = true;

	saveData();

	Award reward;
	for (vector<AwardInfo>::const_iterator itr = pReward->reward.get().begin(); itr != pReward->reward.get().end(); ++itr) {
		if (itr->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(itr->id)) {
			GiftBagConfig::getInstance()->openAllLuckyBox(itr->id, itr->count, reward);
			continue;
		}
		reward.add(*itr);
	}

	string code = "daily_task_" + CTrans::ITOS(pReward->id);
	m_player->doReward(&reward, code, true);

	onRewardResp(0, index);

	sendScore();
	debug_log("uid=%u,index=%u", uid, index);
	return true;
}

bool ActivenessManager::onRewardResp(byte ret, uint32_t id)
{
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_DAILY_TASK);
	selfWriter.AppendByte(PROTOCOL_SUBCMD_DAILY_TASK_REWARD);
	selfWriter.AppendByte(ret);
	selfWriter.AppendUInt32(id);

	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket))
	{
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
	}
	return true;
}

bool ActivenessManager::onLogin()
{
	//doProgress(LOGIN);
	sendData();
	sendScore();
	return true;
}

