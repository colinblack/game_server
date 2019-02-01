/*
 * LogicSso.h
 *
 *  Created on: 2011-12-22
 *      Author: dada
 */

#ifndef LOGICSSO_H_
#define LOGICSSO_H_

#include "LogicInc.h"

namespace LogicSso
{
	int Login(string &openid, const string &openkey, bool white, const string &iopenid,
			const string &pf, const string &userip, bool verified, bool ingame, unsigned &uid, string &skey);
	bool IsLogin(unsigned uid, const string &skey);
	int GetOpenKey(unsigned uid, string &openid, string &openkey);
	int GetLoginUid(unsigned &uid, const string &openid, const string &openkey);

	int Verify(unsigned uid, bool login = false, bool verified = false);	//verify: 是否已验证
};

#endif /* LOGICSSO_H_ */
