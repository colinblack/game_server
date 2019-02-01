/*
 * Email.cpp
 *
 *  Created on: 2012-6-4
 *      Author: dada
 */

#include "Email.h"

bool Email::SendMail(const MailMessage &mail)
{
	string ip;
	int port = 25;
	vector<string> vecAddress;
	CBasic::StringSplitTrim(mail.Server, ":", vecAddress);
	if(vecAddress.size() == 2)
	{
		if(!Convert::StringToInt(port, vecAddress[1]))
		{
			return false;
		}
	}
	else if(vecAddress.size() != 1)
	{
		return false;
	}
	ip = vecAddress[0];

	CSocket socket;
	if(!socket.Create())
	{
		return false;
	}
	if(!socket.Connect(port, ip.c_str()))
	{
		return false;
	}
	string bodyEncode = string("\r\n") + mail.Body + "\r\n";
	CBasic::StringReplace(bodyEncode, "\r\n.\r\n", "\r\n..\r\n");
	string commands;
	String::Format(commands,
			"MAIL FROM: %s\r\n"
			"RCPT TO: %s\r\n"
			"DATA\r\n"
			"From: %s\r\n"
			"To: %s\r\n"
			"Subject: %s\r\n"
			"%s"
			".\r\n"
			"QUIT\r\n",
			mail.From.c_str(),
			mail.To.c_str(),
			mail.From.c_str(),
			mail.To.c_str(),
			mail.Subject.c_str(),
			bodyEncode.c_str());
	size_t byteLeft = commands.size();
	size_t sendPos = 0;
	while(byteLeft > 0)
	{
		int byteSent = socket.Send(commands.c_str() + sendPos, byteLeft);
		if(byteSent > 0)
		{
			byteLeft -= byteSent;
			sendPos += byteSent;
		}
		else
		{
			return false;
		}
	}
	socket.Close();
	return true;
}
