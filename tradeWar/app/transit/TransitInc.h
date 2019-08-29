#ifndef SERVERINC_H_
#define SERVERINC_H_

#include "Kernel.h"
#include "Common.h"
#include "IOpenPlatform.h"
#include "OpenPlatform.h"
#include "TransitManager.h"
#include "ProtocolTransit.h"
#include "LogicQQPay.h"

//cmd
#define PROTOCOL_EVENT_BUY_GOODS 203

//protocol
#define PROTOCOL_TYPE_TRANSIT 203

//command
#define ROLE_CMD_LOGIN 1
#define ROLE_CMD_LOGIN_RET 2
#define ROLE_CMD_CREATE_ROLE 4
#define ROLE_CMD_VIP 7
#define PROTOCOL_CMD_BUY_GOODS 102
#define PROTOCOL_CMD_BUY_GOODS_RET 103
#define PROTOCOL_CMD_DELIVER 104
#define PROTOCOL_CMD_DELIVER_RET 105
#define PROTOCOL_CMD_IS_LOGIN 8
#define PROTOCOL_CMD_OFFLINE 9
#define ROLE_CMD_VERIFY_NAME 11

#endif
