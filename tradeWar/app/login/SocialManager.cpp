#include "SocialManager.h"
#include "PlayerManager.h"

SocialManager::SocialManager() {
}

SocialManager::~SocialManager() {
}

bool SocialManager::doPacket(CNetPacket *packet) {
	return true;
}

bool SocialManager::load(uint32_t uid) {
	CDataSocial dbc;
	int ret = 0;
	ret = dbc.Get(uid, m_data);
	if (0 != ret && R_ERR_NO_DATA != ret) {
		error_log("get all social error uid=%u ret=%d", uid, ret);
		return false;
	}
	debug_log("uid=%u,fsize=%u", uid, m_data.size());
	return true;
}

bool SocialManager::onAccept(uint32_t uid, const string &pic) {
	vector<DataSocial>::iterator itr = find(m_data.begin(), m_data.end(), uid);
	if (itr != m_data.end()) {
		return true;
	}

	uint32_t my_uid = m_player->getUid();
	if (uid == my_uid) {
		error_log("cat not add myself uid=%u fuid=%u", my_uid, uid);
		return false;
	}

	DataSocial item;
	item.uid = my_uid;
	item.other_uid = uid;
	item.update_time = LogicManager::GlobalTime;
	item.pic = pic;
	m_data.push_back(item);
	CDataSocial dbc;
	int ret = dbc.Add(item);
	if (0 != ret) {
		error_log("add social error uid=%u ouid=%u ret=%d", my_uid, uid, ret);
		return false;
	}
	return true;
}

bool SocialManager::updatePic(uint32_t uid, const string &pic) {
	vector<DataSocial>::iterator itr = find(m_data.begin(), m_data.end(), uid);
	if (itr == m_data.end() || itr->pic == pic) {
		return true;
	}
	itr->pic = pic;
	CDataSocial dbc;
	dbc.Set(*itr);
	return true;
}

const vector<DataSocial>& SocialManager::getData() {
	return m_data;
}
