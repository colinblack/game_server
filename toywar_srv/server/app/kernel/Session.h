/*
 * Session.h
 *
 *  Created on: 2011-1-10
 *      Author: LARRY
 */

#ifndef SESSION_H_
#define SESSION_H_

#include "Kernel.h"

namespace Session
{
	string CreateSessionKey(unsigned uid);
	string GetValue(unsigned uid, const string &key);
	int GetValue(unsigned uid, const string &key, string &value);
	int SetValue(unsigned uid, const string &key, const string &value);
	int RemoveValue(unsigned uid, const string &key);
	int RemoveSession(unsigned uid);
	int RemoveSessionExpired(unsigned uid, unsigned timeBefore);
	int RemoveSessionExpired(unsigned uid, const string &key, unsigned timeBefore);
}

#endif /* SESSION_H_ */
