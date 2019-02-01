/*
 *SetActivity.cpp
 *
 *  Created on: 2016-10-10
 *      Author: City
 */

#include "LogicInc.h"
#include <fstream>
#include "Admin.pb.h"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "param error. usage: ./programe zoneId actId status[on,off,settle]";
		return 1;
	}
	if (!Kernel::Init())
	{
		cout << "init error";
		return 1;
	}

	uint32_t zoneId = CTrans::STOI(argv[1]);
	uint32_t actId = CTrans::STOI(argv[2]);
	string status = argv[3];
	if(status != "on" && status != "off" && status != "settle")
	{
		cout << "invalid status:" << status << endl;
		return 1;
	}

	Admin::SetActivity *msg = new Admin::SetActivity;
	msg->set_actid(actId);
	msg->set_status(status);

	//发送协议
	CSG17Packet packet;
	packet.cmd = PROTOCOL_ADMIN;
	packet.m_msg = msg;

	int ret = BattleSocket::Send(zoneId, &packet);

	if(ret)
	{
		cout<<"send system error"<<endl;
		return ret;
	}

	cout<<"batch success"<<endl;

	return 0;
}


