/*
 * main.cpp
 *
 *  Created on: 2016-3-15
 *      Author: Administrator
 */

#include "Kernel.h"
#include "TransitServer.h"
#include "TransitManager.h"
#include "ServerConfig.h"

int main(int argc, char** argv) {
	if (!TransitServer::initDaemon()) {
		printf("daemon init failed\n");
	}

	if (!TransitServer::getInstance()->init()) {
		printf("TransitServer init failed\n");
		return -1;
	}

	if (!TransitManager::getInstance()->init()) {
		printf("TransitManager init failed\n");
		return -1;
	}

	if (!ServerConfig::getInstance()->Init(Config::GetValue(CONFIG_SERVER_CONFIG))) {
		printf("int server error failed\n");
		return -1;
	}

	TransitServer::getInstance()->RunningThread();

	return 0;
}

