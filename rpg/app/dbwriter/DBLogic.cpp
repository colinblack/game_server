#include "DBLogic.h"
#include "AsyncDBManager.h"

bool DBLogic::init() {
	if (!AsyncDBManager::getInstance()->initThread()) {
		error_log("DBLogic init failed");
		return false;
	}
	return true;
}
