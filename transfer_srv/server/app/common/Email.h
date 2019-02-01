/*
 * Email.h
 *
 *  Created on: 2012-6-4
 *      Author: dada
 */

#ifndef EMAIL_H_
#define EMAIL_H_

#include "Common.h"

namespace Email
{
	struct MailMessage
	{
		string Server;
		string From;
		string To;
		string Subject;
		string Body;
	};

	bool SendMail(const MailMessage &mail);
};

#endif /* EMAIL_H_ */
