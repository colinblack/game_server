/*
 * StarBoxManager.cpp
 *
 *  Created on: 2019年 4月 19日
 *      Author: next
 */
#include <StarBoxManager.h>
#include <DataInc.h>
#include "PlayerManager.h"
#include "ConfigInc.h"
#include "ProtocolUser.h"

StarBoxManager::StarBoxManager() {
	starBoxMap.clear();
}
StarBoxManager::~StarBoxManager() {

}
bool StarBoxManager::doPacket(CNetPacket *p) {
	switch(p->subCmd) {
	case PROTOCOL_SUBCMD_GATE_GET_STAR_BOX_INFO: {
		getInfo(p);
		break;
	}
	case PROTOCOL_SUBCMD_GATE_GET_STAR_BOX_REWARD: {
		openBox(p);
		break;
	}
	case PROTOCOL_SUBCMD_GATE_GET_ALL_BOX_FLAG:{
		getALLBoxFlag(p);
		break;
	}
	default:
		return false;
	}
	return true;
}
bool StarBoxManager::load(uint32_t uid) {
	CDataState dbc;
	DataState data;
	data.uid = uid;
	data.id = PLAYER_DATA_STATE_STAR_BOX;
	int ret = dbc.GetState(data.uid, data.id, data.data);
	if (R_SUCCESS == ret) {
		Json::Value v;
		Json::Reader r;
		if (r.parse(data.data, v) && !v.isNull() && v.isArray()) {
			for(uint32_t i = 0; i < v.size(); ++i) {
				StarBox data;
				data.fromJson(v[i]);
				starBoxMap.insert(make_pair(data.chapId, data));
			}
		}
	} else if (R_ERR_NO_DATA == ret) {
		ret = dbc.AddState(data.uid, data.id, "");
	} else {
		error_log("get state error uid=%u id=%u", data.uid, data.id);
		return false;
	}
	return true;
}
bool StarBoxManager::save() {
	Json::Value v = Json::Value(Json::arrayValue);
	int i = 0;
	for(map<uint32_t, StarBox>::iterator it = starBoxMap.begin(); it != starBoxMap.end(); ++it) {
		v[i] = it->second.toJson();
		i++;
	}

	CDataState dbc;
	DataState data;
	data.uid = m_player->getUid();
	data.id = PLAYER_DATA_STATE_STAR_BOX;
	data.data = Json::ToString(v);
	int ret = dbc.SetState(data);
	if (R_SUCCESS != ret) {
		error_log("set state error uid=%d, id=%d", data.uid, data.id);
		return false;
	}
	return true;
}

bool StarBoxManager::getInfo(CNetPacket *p) {
	CUserBoxInfoProtocol proto;
	if(!proto.Decode(p->GetBody())) {
		error_log("decode error %d", p->uid);
		onResp(p->subCmd, 1);
		return false;
	}
	if(proto.chapId > GateConfig::getInstance()->getChapterCnt()) {
		error_log("chapter id error:%d", proto.chapId);
		onResp(p->subCmd, 1);
		return false;
	}

	if(starBoxMap.count(proto.chapId) == 0) {
		infoAdd(proto.chapId);
		save();
	}

	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_GATE);
	writer.AppendByte(PROTOCOL_SUBCMD_GATE_GET_STAR_BOX_INFO);
	writer.AppendByte(proto.chapId);
	writer.AppendByte(CHAPTER_BOX_CNT);

	for(int i = 0; i < CHAPTER_BOX_CNT; ++i) {
		writer.AppendByte(starBoxMap[proto.chapId].data[i].id);
		writer.AppendByte(starBoxMap[proto.chapId].data[i].gFlag);
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool StarBoxManager::infoAdd(uint32_t id) {
	StarBox data;
	data.chapId = id;
	uint32_t cnt = getChapStarCnt(id);
	for(uint32_t i = 0; i < CHAPTER_BOX_CNT; ++i) {
		data.data[i].id = i+1;
		data.data[i].gFlag = false;
		data.data[i].ts = LogicManager::GlobalTime;

		if(cnt >= GateConfig::getInstance()->getStarlimit(id, i)) {
			data.data[i].eFlag = true;
		} else {
			data.data[i].eFlag = false;
		}
	}
	starBoxMap.insert(make_pair(id, data));
	return true;
}

bool StarBoxManager::openBox(CNetPacket *p) {
	bool flag = true;
	CUserOpenBoxProtocol proto;
	if(!proto.Decode(p->GetBody())) {
		error_log("decode error %d", p->uid);
		onResp(p->subCmd, 1);
		return false;
	}
	if(proto.chapId > GateConfig::getInstance()->getChapterCnt()) {
		error_log("chapter id error:%d", proto.chapId);
		onResp(p->subCmd, 1);
		return false;
	}
	if(proto.id > CHAPTER_BOX_CNT && 0 == proto.id) {
		error_log("star box id error:%d", proto.id);
		onResp(p->subCmd, 1);
		return false;
	}

	if(!starBoxMap[proto.chapId].data[proto.id-1].eFlag) {
		error_log("star box is not exist:%d", proto.id);
		onResp(p->subCmd, 1);
		return false;
	}

	if(starBoxMap[proto.chapId].data[proto.id-1].gFlag) {
		error_log("star box already open error:%d", proto.id);
		onResp(p->subCmd, 1);
		return false;
	}

	uint32_t lv = m_player->getLevel();
	uint32_t box_indx = GateConfig::getInstance()->getBox(proto.chapId, proto.id);

	Award box;
	Award reward;
	if (box_indx > 0) {
		uint32_t boxId = (lv == 0 ? 1 : lv) * 1000 + box_indx;
		GiftBagConfig::getInstance()->openAllLuckyBox(boxId, 1, reward);
		m_player->doReward(&reward, "StarBox_gift_" +CTrans::ITOS(proto.chapId) + CTrans::ITOS(proto.id), false, &box);
		starBoxMap[proto.chapId].data[proto.id-1].gFlag = true;
		starBoxMap[proto.chapId].data[proto.id-1].ts = LogicManager::GlobalTime;
		save();
	} else {
		reward.clear();
		string reson = "star_box chapter_id " + CTrans::ITOS(proto.chapId) + "reward_id " + CTrans::ITOS(proto.id);
		GateConfig::getInstance()->getReward(proto.chapId, proto.id, reward);
		if(!reward.isEmpty()) {
			m_player->doReward(&reward, reson);
			starBoxMap[proto.chapId].data[proto.id-1].gFlag = true;
			starBoxMap[proto.chapId].data[proto.id-1].ts = LogicManager::GlobalTime;
			save();
		}
	}
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_GATE);
	writer.AppendByte(PROTOCOL_SUBCMD_GATE_GET_STAR_BOX_REWARD);
	writer.AppendByte(0);
	box.packetData(writer);

	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool StarBoxManager::getALLBoxFlag(CNetPacket *p) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter writer(sp.GetBody());
	writer.AppendByte(PROTOCOL_CMD_GATE);
	writer.AppendByte(PROTOCOL_SUBCMD_GATE_GET_ALL_BOX_FLAG);

	uint32_t chapter_cnt = GateConfig::getInstance()->getChapterCnt();
	writer.AppendByte(chapter_cnt);
	for(int id = 1; id <= chapter_cnt; ++id) {
		if(starBoxMap.count(id) == 0) {
			infoAdd(id);
			save();
		}
		for(int indx = 0; indx < CHAPTER_BOX_CNT; ++indx) {
			writer.AppendByte(starBoxMap[id].data[indx].gFlag);
		}
	}
	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

bool StarBoxManager::infoReFlash(uint32_t level) {
	int chapId = GateConfig::getInstance()->getchapIdByLevel(level);
	if(0 == chapId) {
		error_log("level error %d", level);
		return false;
	}
	uint32_t cnt = getChapStarCnt(chapId);

	for(uint32_t i = 0; i < CHAPTER_BOX_CNT; ++i) {
		if(cnt >= GateConfig::getInstance()->getStarlimit(chapId, i) &&
				starBoxMap[chapId].data[i].eFlag == false) {
			starBoxMap[chapId].data[i].eFlag = true;
			starBoxMap[chapId].data[i].ts = LogicManager::GlobalTime;
		}
	}
}

bool StarBoxManager::onResp(byte sub, byte ret) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	CBufferWriter write(sp.GetBody());
	write.AppendByte(PROTOCOL_CMD_GATE);
	write.AppendByte(sub);
	if(PROTOCOL_SUBCMD_GATE_GET_STAR_BOX_INFO == sub) {
		write.AppendByte(0);
		write.AppendByte(0);

	} else if(PROTOCOL_SUBCMD_GATE_GET_STAR_BOX_REWARD == sub) {
		write.AppendByte(ret);
	}

	PlayerManager::getInstance()->sendToAccess(&sp);
	return true;
}

uint32_t StarBoxManager::getChapStarCnt(uint32_t chap_id) {
	vector<uint32_t> levels;
	GateConfig::getInstance()->getLevels(chap_id, levels);
	uint32_t cnt = 0;
	for(vector<uint32_t>::const_iterator it = levels.begin(); it != levels.end(); ++it) {
		cnt += m_player->getBattleGateMgr()->getLevelStarCnt(*it);
	}
	return cnt;
}
