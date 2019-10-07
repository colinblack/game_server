#include "BattleServer.h"

int main(int argc,char** argv){

	if(!BattleServer::Instance()->Initialize())
	{
		printf("battle Server Initialize Error\n");
		return 0;
	}

	if(!LogicManager::Instance()->Initialize()){
		printf("LogicManager Init failed\n");
		return 0;
	}

	if(!BattleServer::Instance()->InitThread())
	{
		printf("battle Server InitThread Error\n");
		return 0;
	}

	if(!BattleServer::Instance()->Run())
	{
		fatal_log("[FireServer::Run fail]");
	}

	LogicManager::Instance()->Destroy();
	BattleServer::Instance()->Destroy();
	CBusinessLogHelper::Destory();


	return 0;
}
