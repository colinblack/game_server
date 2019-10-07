/*
 * AddUser.cpp
 *
 *  Created on: 2016-7-1
 *      Author: Ralf
 */

#include "LogicInc.h"

int main(int argc, char *argv[])
{
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init kernel fail" << endl;
		return 1;
	}

	if(argc != 4)
	{
		cout<<"need openid serverid name"<<endl;
		return 1;
	}

	int ret;
	string openid(argv[1]);
	unsigned serverid = atoi(argv[2]);
	ConfigManager::Instance()->SetServer(serverid);
	string name(argv[3]);

	string via, iopenid, openkey;
	OPUserInfo userinfo;
	userinfo.OpenId = openid;
	userinfo.Name = name;
	unsigned uid = 0;
	bool isNewUser=false;
	ret = CLogicUserMapping().LoginPlatformUser(PT_TEST, userinfo, iopenid, uid, isNewUser, via);
	if(ret != 0)
	{
		cout<<"LoginPlatformUser ret=%u"<<ret<<endl;
		return 1;
	}

	Common::Login* msg = new Common::Login;
	msg->set_uid(uid);
	msg->set_openkey(openkey);
	msg->set_ts(Time::GetGlobalTime());
	msg->set_fig(userinfo.FigureUrl);
	msg->set_name(userinfo.Name);
	msg->set_isnew(isNewUser);
	msg->set_platform(0);
	msg->set_openid(openid);

	string suid = CTrans::UTOS(uid);
	string sts = CTrans::UTOS(Time::GetGlobalTime());
	string sak(DAWX_RALF_KEY);
	string sig = Crypt::Md5Encode(suid + openkey + sts + sak);
	msg->set_sig(sig);

	//发送协议
	CSG17Packet packet(PROTOCOL_ADMIN);
	packet.m_msg = msg;
	ret = BattleSocket::Send(serverid, &packet);
	if(ret)
	{
		cout<<"send system error"<<endl;
		return ret;
	}

	CSG17Packet reply;
	ret = BattleSocket::Receive(serverid, &reply);
	if(ret)
	{
		cout<<"recv system error"<<endl;
		return ret;
	}

	cout <<reply.m_msg->GetTypeName()<< endl;
	return 0;
}
