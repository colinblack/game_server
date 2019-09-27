/*
 * SystemEmail.h
 *
 *  Created on: 2016年3月12日
 *      Author: aaron
 *        Desc:
 */

#ifndef SYSTEMEMAIL_H_
#define SYSTEMEMAIL_H_

#include "Kernel.h"
#include "DataEmail.h"

class CSystemEmail {
public:
	CSystemEmail();
	virtual ~CSystemEmail();
	static bool addEmail(uint32_t uid, const string &title, const string &content, const string &attatch, DataEmail &email);
};

#endif /* SYSTEMEMAIL_H_ */
