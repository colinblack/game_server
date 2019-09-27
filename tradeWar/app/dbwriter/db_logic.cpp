#include "uvlog.h"
#include "db_logic.h"
#include "AsyncDBManager.h"

bool DBLogic::init() {
	if (!AsyncDBManager::getInstance()->initThread()) {
		LOG_ERROR("DBLogic init failed");
		return false;
	}
	return true;
}
