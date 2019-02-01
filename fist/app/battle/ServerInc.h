#ifndef _SERVER_INC_H_
#define _SERVER_INC_H_

#define RMI ResourceManager::Instance()
#define SEQ_GET_RMI(seq) RMI->m_data->item[seq]
#define GET_RMI(uid) SEQ_GET_RMI(RMI->GetIndex(uid))
#define UMI UserManager::Instance()
#define LMI LogicManager::Instance()
#define LOI LogicOnhookManager::Instance()
#define LUI LogicUserManager::Instance()

#include "Kernel.h"
#include "DataInc.h"
#include "LogicManager.h"
#include "ProtoManager.h"
#include "UserManager.h"
#include "LogicResourceManager.h"
#include "LogicUserManager.h"
#include "LogicNotifyManager.h"
#include "LogicGameActivityManager.h"
#include "LogicPropsManager.h"
#include "LogicGM.h"
#include "LogicQueueManager.h"
#include "LogicRoutineManager.h"
#include "LogicHeroManager.h"
#include "LogicBattleManager.h"
#include "LogicUserGradeManager.h"
#include "LogicFriendManager.h"
#include "LogicOnhookManager.h"
#include "LogicMartialClubManager.h"
#include "LogicMartialHeroManager.h"
#include "LogicPostManager.h"
#include "LogicChampionshipManager.h"


#endif
