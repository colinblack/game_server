#include "BattleServer.h"
#include "LogicManager.h"
#include "ClientAsync.h"

int main(int argc, char** argv) {
	try {
		if (!BattleServer::Instance()->Initialize()) {
			printf("battle Server Initialize Error\n");
			return 0;
		}
		if (!LogicManager::Instance()->Init()) {
			fatal_log("[LogicManager::Init fail][error=%d]", errno);
			return 0;
		}
		if (!BattleServer::Instance()->Run()) {
			fatal_log("[FireServer::Run fail]");
		}
	} catch (const std::exception& e) {
		cout << "server start error msg=" << e.what() << endl;
	}
	return 0;
}
