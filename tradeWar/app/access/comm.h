#ifndef _WX_COMM_H_
#define _WX_COMM_H_

#define MAGIC_HEADER 26284
#define MAGIC_ADDER	5834

#define PROTOCOL_ACCESS_TRANSFER 1
#define PROTOCOL_ACCESS_ANSWER 2
#define PROTOCOL_ACCESS_HEARBEAT 3
#define PROTOCOL_ACCESS_COFFLINE 4
#define PROTOCOL_ACCESS_LOFFLINE 5
#define PROTOCOL_ACCESS_CHANGE_LOGIN 6
#define PROTOCOL_ACCESS_KICK_CROSS 7
#define PROTOCOL_ACCESS_LOGIN_TRANSFER 8

#define WS_HEAD_FLAG   2
#define WS_LITTLE_HEAD 6
#define WS_MIDDLE_HEAD 8
#define WS_LARGE_HEAD  14

#pragma pack(1)

struct ClientHead{
	uint16_t head;
	uint16_t bodyLen;
	uint16_t crc1;
	uint16_t crc2;
	int32_t padding1;
	int32_t padding2;
};

struct BattleHead{
	uint16_t head;
	uint16_t bodyLen;
	uint16_t cmd;
	uint32_t fd;
	uint32_t time;
	uint32_t microTime;
	uint32_t clientIp;
};

#pragma pack()


#endif
