/*
 * main.cpp
 *
 *  Created on: 2015-8-21
 *      Author: Administrator
 */

#include "LoginServer.h"
#include "Player.h"
#include "LogicManager.h"
#include "Kernel.h"

int main(int argc, char** argv) {
	if (!LoginServer::initDaemon()) {
		printf("daemon start failed\n");
	}

	if (!LogicManager::getInstance()->init()) {
		printf("LogicManager init failed\n");
		return -1;
	}

	if (!ServerConfig::getInstance()->Init(Config::GetValue(CONFIG_SERVER_CONFIG))) {
		printf("ServerConfig init failed\n");
		return -1;
	}

	if (!LoginServer::getInstance()->init()) {
		printf("LoginServer init failed\n");
		return -1;
	}

	LoginServer::getInstance()->doLogic();
	return 0;
}

