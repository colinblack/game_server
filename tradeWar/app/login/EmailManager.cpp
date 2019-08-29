/*
 * EMailManager.cpp
 *
 *  Created on: 2015-12-1
 *      Author: nick
 */

#include "EmailManager.h"
#include "ProtocolInc.h"
#include "LogicIdCtrl.h"
#include "PlayerManager.h"
#include "SystemEmail.h"
#include "GiftBagConfig.h"

#define EMAIL_BOX_REC 1
#define EMAIL_BOX_SEND 2
#define EMAIL_BOX_DEL 3
#define EMAIL_MAX_NUM 30

bool EmailManager::load(uint32_t uid) {
	m_emails.clear();
	CDataEmail cDataMail;
	int ret = cDataMail.GetEmails(uid, m_emails);
	if (ret != R_SUCCESS && ret != R_ERR_NO_DATA) {
		error_log("get %u's email failed", uid);
		return false;
	}
	onLoadRemoveEmail();
	return true;
}

bool EmailManager::doPacket(CNetPacket * packet) {
	switch (packet->subCmd) {
	case PROTOCOL_SUBCMD_EMAIL_REC_BOX:
	case PROTOCOL_SUBCMD_EMAIL_SEND_BOX:
		doQueryList(packet->subCmd);
		break;
	case PROTOCOL_SUBCMD_EMAIL_DEL:
		doDelete(packet);
		break;
	case PROTOCOL_SUBCMD_EMAIL_READ:
		doRead(packet);
		break;
	case PROTOCOL_SUBCMD_EMAIL_GET:
		doGet(packet);
		break;
	case PROTOCOL_SUBCMD_EMAIL_WRITE:
		doWrite(packet);
		break;
	}
	return true;
}

bool EmailManager::addEmail(uint32_t uid, const string &title, const string &content, const string &attatch) {
	DataEmail newEmail;
	if (!CSystemEmail::addEmail(uid, title, content, attatch, newEmail)) {
		error_log("add email fail uid=%u", uid);
		return false;
	}
	m_emails.push_back(newEmail);
	onLoadRemoveEmail();
	if (!PlayerManager::getInstance()->IsOnline(uid)) {
		return true;
	}
	if (!doQueryList(EMAIL_BOX_REC)) {
		error_log("doQueryList fail uid=%u title=%s", uid, title.c_str());
		return false;
	}
	return true;
}

bool EmailManager::doWrite(CNetPacket* packet) {
	return true;
}

bool EmailManager::doGet(CNetPacket* packet) {
	if (m_player == NULL) {
		error_log("m_player is NULL");
		return false;
	}
	CEmailReadProtocol cs;
	if (!cs.Decode(&(packet->body))) {
		error_log("CTaskSubmitProtocol decode failed, uid=%u", packet->uid);
		return false;
	}
	vector<DataEmail>::iterator itr = find(m_emails.begin(), m_emails.end(), cs.id);
	if (itr == m_emails.end()) {
		error_log("email not exists, uid=%u, id=%u", packet->uid, cs.id);
		return false;
	}
	if (itr->attach_flag != e_EmailAttackFlagSet) {
		error_log("email attach_flag error, uid=%u, id=%u, flag=%u", packet->uid, cs.id, itr->attach_flag);
		return false;
	}
	Json::Value value;
	Json::Reader reader;
	if (!reader.parse(itr->attachments, value)) {
		error_log("reward error uid=%u id=%u", packet->uid, cs.id);
		return false;
	}
	Award award;
	if (!award.Json2Award(value)) {
		error_log("reward error uid=%u id=%u", packet->uid, cs.id);
		return false;
	}

	Award reward;
	vector<AwardInfo>::iterator it = award.get().begin();
	for (; it != award.get().end(); ++it) {
		if (it->type == AWARD_TYPE_ITEM && GiftBagConfig::getInstance()->isBox(it->id)) {
			GiftBagConfig::getInstance()->openAllLuckyBox(it->id, it->count, reward);
		} else {
			reward.add(*it);
		}
	}
	itr->attach_flag = e_EmailAttackFlagGet;
	if (!updateEmail(*itr)) {
		error_log("update email error uid=%u id=%u", packet->uid, cs.id);
		return false;
	}
	string code = "email_attach_" + CTrans::ITOS(itr->post_ts);
	m_player->doReward(&reward, code);
	doQueryList(EMAIL_BOX_REC);
	return true;
}

bool EmailManager::doRead(CNetPacket* packet) {
	CEmailReadProtocol cs;
	if (!cs.Decode(&(packet->body))) {
		error_log("CTaskSubmitProtocol decode failed, uid=%u", packet->uid);
		return false;
	}
	vector<DataEmail>::iterator itr = find(m_emails.begin(), m_emails.end(), cs.id);
	if (itr == m_emails.end() || itr->read_ts != 0) {
		error_log("email has read or not exists,uid=%u,id=%u,ts=%u", packet->uid, cs.id, itr->read_ts);
		return false;
	}
	itr->read_ts = LogicManager::GlobalTime;
	updateEmail(*itr);
	doQueryList(EMAIL_BOX_REC);
	return true;
}

bool EmailManager::doDelete(CNetPacket* packet) {
	CEmailDeleteProtocol cs;
	if (!cs.Decode(&(packet->body))) {
		error_log("CTaskSubmitProtocol decode failed, uid=%u", packet->uid);
		return false;
	}

	byte type = EMAIL_BOX_REC;
	CDataEmail cDataEmail;
	for (uint32_t i = 0; i < cs.vec.size(); ++i) {
		vector<DataEmail>::iterator itr = find(m_emails.begin(), m_emails.end(), cs.vec[i]);
		if (itr == m_emails.end()) {
			continue;
		}
		type = itr->post_flag;
		itr->post_flag = EMAIL_BOX_DEL; // 设置成已经删除标志，延后删除。防止重复领取系统邮件奖励
		updateEmail(*itr);
		sendDelete(itr->id);
	}

	doQueryList(type);
	return true;
}

void EmailManager::onLoadRemoveEmail() {
	if (EMAIL_MAX_NUM > m_emails.size()) {
		return;
	}
	multimap<unsigned, unsigned> ts_map;
	for (unsigned i = 0; i < m_emails.size(); ++i) {
		ts_map.insert(make_pair(m_emails[i].post_ts, i));
	}
	CDataEmail dbc;
	multimap<unsigned, unsigned>::iterator itr = ts_map.begin();
	for (; itr != ts_map.end() && m_emails.size() > EMAIL_MAX_NUM; ++itr) {
		dbc.RemoveEmail(m_player->getUid(), m_emails[itr->second].id);
		m_emails.erase(m_emails.begin() + itr->second);
	}
}

bool EmailManager::updateEmail(const DataEmail &data) {
	CDataEmail dbEmail;
	if (0 != dbEmail.UpdateEmail(data)) {
		return false;
	}
	return true;
}

void EmailManager::sendDelete(uint32_t id) {
	CNetPacket sRspPacket;
	sRspPacket.uid = m_player->getUid();
	CBufferWriter selfWriter(&sRspPacket.body);
	selfWriter.AppendByte(PROTOCOL_CMD_EMAIL);
	selfWriter.AppendByte(3);
	selfWriter.AppendUInt32(id);
	if (!PlayerManager::getInstance()->sendToAccess(&sRspPacket)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
	}
	return;
}

bool EmailManager::doQueryList(uint32_t type) {
	CNetPacket sp;
	sp.uid = m_player->getUid();
	PACKET_ENCODE_BEGIN(sp.GetBody());
	PACKET_ENCODE(Byte, PROTOCOL_CMD_EMAIL);
	PACKET_ENCODE(Byte, type);
	uint32_t o_size = sp.GetBody()->GetSize();
	PACKET_ENCODE(UInt32, 0);
	vector<DataEmail>::const_iterator itr = m_emails.begin();
	uint32_t cnt = 0;
	for (; itr != m_emails.end(); ++itr) {
		const DataEmail &data = *itr;
		if (data.post_flag != type) {
			continue;
		}
		PACKET_ENCODE(UInt32, data.uid);
		PACKET_ENCODE(UInt32, data.opposite_uid);
		PACKET_ENCODE(UInt32, data.id);
		PACKET_ENCODE(UInt32, data.post_ts);
		PACKET_ENCODE(UInt32, data.read_ts);
		PACKET_ENCODE(String, data.to_name);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, data.from_name);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, data.title);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(String, data.text);
		PACKET_ENCODE(Byte, 0);
		PACKET_ENCODE(Byte, data.attach_flag);
		PACKET_ENCODE(String, data.attachments);
		PACKET_ENCODE(Byte, 0);
		++cnt;
	}
	uint32_t n_size = sp.GetBody()->GetSize();
	sp.GetBody()->SetSize(o_size);
	PACKET_ENCODE(UInt32, cnt);
	sp.GetBody()->SetSize(n_size);
	if (!PlayerManager::getInstance()->sendToAccess(&sp)) {
		error_log("sendAccess_fail&uid=%u", m_player->getUid());
		return false;
	}
	return true;
}

