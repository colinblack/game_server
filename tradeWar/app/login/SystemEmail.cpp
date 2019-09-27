/*
 * SystemEmail.cpp
 *
 *  Created on: 2016年3月12日
 *      Author: aaron
 *        Desc:系统邮件
 */

#include "SystemEmail.h"
#include "LogicIdCtrl.h"
#include "DataEmail.h"
#include "DataUser.h"
#include "LanguageConfig.h"

CSystemEmail::CSystemEmail() {
}

CSystemEmail::~CSystemEmail() {
}

bool CSystemEmail::addEmail(uint32_t uid, const string &title, const string &content, const string &attatch, DataEmail &email) {
	CLogicIdCtrl dbIdCtrl;
	uint32_t nextId;
	int ret = dbIdCtrl.GetNextId(KEY_EMAIL_ID_CTRL, nextId, 1);
	if (ret != 0) {
		error_log("GetNextId failed");
		return false;
	}

	CDataUser user;
	DataUser dataUser;
	CDataEmail cDataEmail;

	email.from_name = LanguageConfig::getInstance()->getLang("admin");
	email.text = content;
	email.title = title;
	email.post_ts = Time::GetGlobalTime();

	if (IS_VALID_PLAYER_UID(uid) && user.GetUser(uid, dataUser) != 0) {
		error_log("user not exists uid=%u", uid);
		return false;
	}

	email.uid = uid;
	email.opposite_uid = UID_ADMIN;
	email.id = nextId;
	email.to_name = dataUser.name;
	email.post_flag = 1;
	email.attach_flag = attatch.empty() ? 0 : 1;
	email.attachments = attatch;
	if (0 != cDataEmail.AddEmail(email)) {
		error_log("add email error uid=%u", uid);
		return false;
	}
	return true;
}
