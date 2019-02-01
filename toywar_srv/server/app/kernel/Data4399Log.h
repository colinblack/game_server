/*
 * Data4399Log.h
 *
 *  Created on: 2015-5-12
 *      Author: Ralf
 */

#ifndef DATA4399LOG_H_
#define DATA4399LOG_H_


#include <string>
#include <vector>

#define DATA_4399_LOG CData4399Log::DataLog(user.openid.c_str(), user.name.c_str(), GetChannel(m_pReceivePacket->ChannelId)?GetChannel(m_pReceivePacket->ChannelId)->GetRemoteAddress()->ToString().c_str():"",pChatSubmitRequest->Message.c_str())

class CData4399Log
{
public:
	//记录cgi的收发情况
	static void DataLog(const char *openid, const char *name, const char *ip, const char *chat);

	static std::string& ParseIP( const std::string pyIp, std::string& realIp );

public:
	//static char log_dir[100];

private:
	static int fd;
	static int last_day;
	static bool init( struct tm *p );
	static int server;
	static string sid;
};


#endif /* DATA4399LOG_H_ */
