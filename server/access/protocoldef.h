#ifndef __PROTOCOL_DEF_H__
#define __PROTOCOL_DEF_H__

#include <string>
#include "data_struct.h"

//#define MAX_KEY_LEN		128
using namespace std;

////////////////////////////////////////////////////////////////////
// 命令号
enum CommandType {
	NON_CMD=0, 
	QUERY_CMD, 
	RSPD_QUERY_CMD,
	INSERT_CMD, 
	RSPD_INSERT_CMD,
	DELETE_CMD,
	RSPD_DELETE_CMD,
	QUERY_COUNT_CMD,
	RSPD_QUERY_COUNT_CMD,

	RSYNC_CMD = 100,
	RSPD_RSYNC_CMD,
	
	GET_MSG_LIST_CMD = 1000,
	RSPD_GET_MSG_LIST_CMD,
	GET_NEW_MSG_CMD,
	RSPD_GET_NEW_MSG_CMD,
};


////////////////////////////////////////////////////////////////////
//                    响应码 - 响应消息                            //
////////////////////////////////////////////////////////////////////
#define RSPD_SUCCESS 0
#define MAX_DATA_COUNT	2000

const string RSPD_SUCCESS_MSG = "success";

// 响应启动文件传输
enum RspdCode {
	RESP_SUCCESS = 0,
	RESP_EMPTY = 1,

};

#define PACK_VER 1

/////////////////////////////////////////////////////////////////////
//
#pragma pack(1)
struct UVHEAD
{
	UVHEAD() : begin(0x2), len(0), ver(PACK_VER), cmd(0) {}

	char begin;
	uint16_t len;
	short ver;
	short cmd;
	char seq;
};

class ProtocolObj
{
public: // head
	void setVer(short ver)
	{
		head.ver = ver;
	}

	short getVer() const
	{
		return head.ver;
	}

	void setCmd(CommandType cmd)
	{
		head.cmd = cmd;
	}

	CommandType getCmd() const
	{
		return (const CommandType)head.cmd;
	}

	short getLen() const
	{
		return head.len;
	}

	UVHEAD head;

protected:
	ProtocolObj() {}
	virtual ~ProtocolObj() {}
};

class QueryCmd : public ProtocolObj
{
public:
	QueryCmd() :  end(0x3)
	{ 
		setCmd(QUERY_CMD);
	}
	
public: // body
	int count;
	char order;
	char keybuf[MAX_KEY_LEN];
	char con[10];
	char end;
};

class RspdQueryCmd: public ProtocolObj
{
public:
	RspdQueryCmd() : code(0), end(0x3)
	{
		setCmd(RSPD_QUERY_CMD);
	}

public:
	int code;
	int count;
	char data[MAX_KEY_LEN * 1024];
	char end;
};

// 查询某一条件范围内的数据条数
class QueryCountCmd : public ProtocolObj
{
public:
	QueryCountCmd() :  keycount(2), end(0x3)
	{
		setCmd(QUERY_COUNT_CMD);
	}

public:
	int keycount;
	char keybuf[MAX_KEY_LEN];
	char end;
};

class RspdQueryCountCmd: public ProtocolObj
{
public:
	RspdQueryCountCmd() : code(0), end(0x3)
	{
		setCmd(RSPD_QUERY_COUNT_CMD);
	}

public:
	int code;
	int count;
	char end;
};



class InsertCmd:public ProtocolObj
{
	public:
	InsertCmd() :  end(0x3)
	{ 
		setCmd(INSERT_CMD);
	}

	public:
		char keybuf[MAX_KEY_LEN];
		uint64_t msg_id;
		char end;
	
};

class RspdInsertCmd:public ProtocolObj
{
	public:
		RspdInsertCmd():code(0),end(3)
		{
			setCmd(RSPD_INSERT_CMD);
		}

	public:
		int code;
		char end;
};

class DeleteCmd:public ProtocolObj
{
	public:
	DeleteCmd() :  end(0x3)
	{ 
		setCmd(DELETE_CMD);
	}

	public:
		char keybuf[MAX_KEY_LEN];
		uint64_t msg_id;
		char end;
	
};

class RspdDeleteCmd:public ProtocolObj
{
	public:
		RspdDeleteCmd():code(0),end(3)
		{
			setCmd(RSPD_DELETE_CMD);
		}

	public:
		int code;
		char end;
};


class GetMsgListCmd:public ProtocolObj
{
	public:
		GetMsgListCmd() :  end(0x3)
		{ 
			setCmd(GET_MSG_LIST_CMD);
		}

	public:
		int starttime;
		uint64_t msg_id;
		int count;
		int keyCount;
		char keybuf[MAX_KEY_LEN * 2000];
		char end;
	
};

class RspdGetMsgListCmd:public ProtocolObj
{
	public:
		RspdGetMsgListCmd():end(0x03)
		{
			setCmd(RSPD_GET_MSG_LIST_CMD);
		}
	public:
		int code;
		int count;
		char data[MAX_KEY_LEN * 1024];
		char end;
		
};


class GetNewMsgCmd:public ProtocolObj
{
	public:
		GetNewMsgCmd() :  end(0x3)
		{ 
			setCmd(GET_NEW_MSG_CMD);
		}

	public:
		//int starttime;
		//uint64_t msg_id;
		int count;
		int keyCount;
		char keybuf[MAX_KEY_LEN * 2000];
		char end;
	
};

class RspdGetNewMsgCmd:public ProtocolObj
{
	public:
		RspdGetNewMsgCmd():end(0x03)
		{
			setCmd(RSPD_GET_NEW_MSG_CMD);
		}
	public:
		int code;
		int count;
		char data[MAX_KEY_LEN * 1024];
		char end;
		
};

class RsyncCmd:public ProtocolObj
{
	public:
		RsyncCmd():end(0x03)
		{
			setCmd(RSYNC_CMD);
		}
	public:
		uint64_t index;
		char end;
};

class RspdRsyncCmd:public ProtocolObj
{
	public:
		RspdRsyncCmd():end(0x03)
		{
			setCmd(RSPD_RSYNC_CMD);
		}
	public:
		int code;
		int count;
		uint64_t mindex;
		//char buf[MAX_DATA_COUNT * 8];
		char buf[145*450];
		char end;
		
		
};

#pragma pack()

#endif
