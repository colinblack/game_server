#include "DBLogic.h"
#include "AsyncDBManager.h"

bool DBLogic::init() {
	if (!AsyncDBManager::Instance()->initThread()) {
		error_log("DBLogic init failed");
		return false;
	}
	return true;
}
