/*
 * ToywarProtocol.h
 *
 *  Created on: 2012-2-15
 *      Author: dada
 */

#ifndef TOYWARPROTOCOL_H_
#define TOYWARPROTOCOL_H_

#include "ServerInc.h"

///协议结果

#define PR_USER_NOT_ONLINE	0x81
#define PR_PUSH_FAIL	0x82
#define PR_ILLEGAL_PARAM	0x83
#define PR_GROUP_LIMIT	0x84
#define PR_GROUP_NOT_EXIST	0x85
#define PR_GROUP_EXIST	0x86
#define PR_GROUP_NOT_IN	0x87
#define PR_GROUP_USER_FULL	0x88
#define PR_USER_FORBID	0x89

#define PR_USER_FORBID_NOTICE		1
#define PR_USER_FORBID_KING			10
#define PR_USER_FORBID_JOB			20
#define PR_USER_FORBID_COLOR		100
///会话

//1-1
//登录
#define PROTOCOL_TYPE_LOGIN COMBINE_PROTOCOL_TYPE(1, 1)
DEFINE_RECEIVE_PACKET_BEGIN(CLoginRequestProtocol)
	DEFINE_PROTOCOL_TYPE(1, 1)
	byte Platform;
	string Name;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, Platform);
		PACKET_DECODE(String, Name);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Platform=%u&Name=%s", (unsigned)Platform, Name.c_str())
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CLoginReplyProtocol)
	DEFINE_PROTOCOL_TYPE(1, 1)
	uint32_t SessionKey;
	//CStaticBuffer<SESSION_SECRET_KEY_SIZE> SecretKey;
	CDanymicBuffer<SESSION_SECRET_KEY_SIZE> SecretKey;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt32, SessionKey);
		PACKET_ENCODE(Bytes, SecretKey.GetConstBuffer(), SecretKey.GetSize());
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("SessionKey=0x%08X&SecretKey=%s", SessionKey, SecretKey.ToString().c_str())
DEFINE_SEND_PACKET_END

//1-2
//注销
#define PROTOCOL_TYPE_LOGOUT COMBINE_PROTOCOL_TYPE(1, 2)
DEFINE_EMPTY_RECEIVE_PACKET(CLogoutRequestProtocol)
DEFINE_EMPTY_SEND_PACKET(CLogoutReplyProtocol)

//1-3
//心跳
#define PROTOCOL_TYPE_REFRESH COMBINE_PROTOCOL_TYPE(1, 3)
DEFINE_RECEIVE_PACKET_BEGIN(CRefreshRequestProtocol)
	DEFINE_PROTOCOL_TYPE(1, 3)
	uint32_t ts;
	uint32_t delay;
	IMPLEMENT_PACKET_DECODE_BEGIN
		reader.GetUInt32(ts);
		reader.GetUInt32(delay);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CRefreshReplyProtocol)
	DEFINE_PROTOCOL_TYPE(1, 3)
	uint32_t ts;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt32, ts);
	IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END

//1-4
//更换主将
#define PROTOCOL_TYPE_UPDATAUSER COMBINE_PROTOCOL_TYPE(1, 4)
DEFINE_RECEIVE_PACKET_BEGIN(CUpdataUserRequestProtocol)
	DEFINE_PROTOCOL_TYPE(1, 4)
	byte Platform;
	string Name;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, Platform);
		PACKET_DECODE(String, Name);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Platform=%u&Name=%s", (unsigned)Platform, Name.c_str())
DEFINE_RECEIVE_PACKET_END

DEFINE_EMPTY_SEND_PACKET(CUpdataUserProtocol)

///组

//2-1
//获取组列表
#define PROTOCOL_TYPE_GROUP_LIST COMBINE_PROTOCOL_TYPE(2, 1)

DEFINE_RECEIVE_PACKET_BEGIN(CGroupListRequestProtocol)
	byte Type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, Type);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%d", (int)Type)
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CGroupListReplyProtocol)
	GroupList Groups;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt16, Groups.size());
		for(GroupList::const_iterator itr = Groups.begin(); itr != Groups.end(); itr++)
		{
			PACKET_ENCODE(UInt32, itr->Id);
			PACKET_ENCODE(String, itr->Name);
			PACKET_ENCODE(UInt16, itr->MaxCount);
			PACKET_ENCODE(UInt16, itr->UserCount);
		}
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("GroupCount=%u", (unsigned)Groups.size())
DEFINE_SEND_PACKET_END


//2-2
//创建组
#define PROTOCOL_TYPE_GROUP_CREATE COMBINE_PROTOCOL_TYPE(2, 2)

DEFINE_RECEIVE_PACKET_BEGIN(CGroupCreateRequestProtocol)
	byte Type;
	uint32_t Id;
	string Name;
	uint32_t FightNum;
	uint32_t AllianceFightRoom;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, Type);
		PACKET_DECODE(UInt32, Id);
		PACKET_DECODE(String, Name);
		if((unsigned)Type == (unsigned)GT_FIGHT)
		{
			PACKET_DECODE(UInt32, FightNum);
		}
		if((unsigned)Type == (unsigned)GT_ALLIANCE_FIGHT)
		{
			PACKET_DECODE(UInt32, AllianceFightRoom);
		}
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u&Name=%s", (unsigned)Type, Id, Name.c_str())
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CGroupCreateReplyProtocol)
	uint32_t Id;
	uint16_t MaxCount;
	uint16_t UserCount;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt32, Id);
		PACKET_ENCODE(UInt16, MaxCount);
		PACKET_ENCODE(UInt16, UserCount);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("Id=%u&MaxCount=%hu&UserCount=%hu", Id, MaxCount, UserCount)
DEFINE_SEND_PACKET_END

//2-3
//加入组
#define PROTOCOL_TYPE_GROUP_JOIN COMBINE_PROTOCOL_TYPE(2, 3)

DEFINE_RECEIVE_PACKET_BEGIN(CGroupJoinRequestProtocol)
	byte Type;
	uint32_t Id;
	uint32_t FightNum;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, Type);
		PACKET_DECODE(UInt32, Id);
		if((unsigned)Type == (unsigned)GT_FIGHT)
		{
			PACKET_DECODE(UInt32, FightNum);
		}
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u", (unsigned)Type, Id)
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CGroupJoinReplyProtocol)
	string Name;
	uint16_t MaxCount;
	uint16_t UserCount;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(String, Name);
		PACKET_ENCODE(UInt16, MaxCount);
		PACKET_ENCODE(UInt16, UserCount);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("Name=%s&MaxCount=%hu&UserCount=%hu", Name.c_str(), MaxCount, UserCount)
DEFINE_SEND_PACKET_END

//2-4
//退出组
#define PROTOCOL_TYPE_GROUP_EXIT COMBINE_PROTOCOL_TYPE(2, 4)

DEFINE_RECEIVE_PACKET_BEGIN(CGroupExitRequestProtocol)
	byte Type;
	uint32_t Id;
	uint32_t AllianceFightRoom;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, Type);
		PACKET_DECODE(UInt32, Id);
		if((unsigned)Type == (unsigned)GT_ALLIANCE_FIGHT)
		{
			PACKET_DECODE(UInt32, AllianceFightRoom);
		}
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u", (unsigned)Type, Id)
DEFINE_RECEIVE_PACKET_END

DEFINE_EMPTY_SEND_PACKET(CGroupExitReplyProtocol)

//2-5
//组消息
#define PROTOCOL_TYPE_GROUP_NOTIFY COMBINE_PROTOCOL_TYPE(2, 5)

DEFINE_SEND_PACKET_BEGIN(CGroupNotifyRequestProtocol)
	byte Type;
	uint32_t Id;
	GroupEvent Event;
	uint32_t UserId;
	string UserName;
	uint32_t GroupIdA;
	uint32_t GroupIdB;
	int32_t HeroId;
	int32_t ReleaseHeroId;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(Byte, Type);
		PACKET_ENCODE(UInt32, Id);
		PACKET_ENCODE(Byte, Event);
		PACKET_ENCODE(UInt32, UserId);
		PACKET_ENCODE(String, UserName);
		if (Event == GE_SELECT_ALLIANCE_HERO)
		{
			PACKET_ENCODE(Int32, HeroId);
			PACKET_ENCODE(Int32, ReleaseHeroId);
		}
		PACKET_ENCODE(UInt32, GroupIdA);
		PACKET_ENCODE(UInt32, GroupIdB);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u&Event=%u&UserId=%u&UserName=%s",
			(unsigned)Type, Id, (unsigned)Event, UserId, UserName.c_str())
DEFINE_SEND_PACKET_END

DEFINE_EMPTY_RECEIVE_PACKET(CGroupNotifyReplyProtocol)

//2-6
//获取组列表
#define PROTOCOL_TYPE_GROUP_LIST_EXT COMBINE_PROTOCOL_TYPE(2, 6)

DEFINE_RECEIVE_PACKET_BEGIN(CGroupListRequestExtProtocol)
	byte Type;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, Type);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%d", (int)Type)
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CGroupListReplyExtProtocol)
	GroupList Groups;
	byte Type;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt16, Groups.size());
		PACKET_ENCODE(Byte,Type);
		for(GroupList::const_iterator itr = Groups.begin(); itr != Groups.end(); itr++)
		{
			PACKET_ENCODE(UInt32, itr->Id);
			PACKET_ENCODE(String, itr->Name);
			PACKET_ENCODE(UInt16, itr->MaxCount);
			PACKET_ENCODE(UInt16, itr->UserCount);
			PACKET_ENCODE(UInt32, itr->OwnerId);
			PACKET_ENCODE(Byte, 	itr->Stat);
		}
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("GroupCount=%u", (unsigned)Groups.size())
DEFINE_SEND_PACKET_END

//2-7
//主机通知组内成员准备战斗
#define PROTOCOL_TYPE_GROUP_READY COMBINE_PROTOCOL_TYPE(2, 7)

DEFINE_RECEIVE_PACKET_BEGIN(CGroupReadyProtocol)
	byte ToType;
	uint32_t ToId;
	uint32_t Room;
	GroupEvent Event;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, ToType);
		PACKET_DECODE(UInt32, ToId);
		PACKET_DECODE(Byte, (byte&)Event);
		if ((unsigned)ToType == (unsigned)GT_ALLIANCE_FIGHT)
		{
			PACKET_DECODE(UInt32, Room);
		}
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u&Event=%u",(unsigned)ToType, ToId, (unsigned)Event)
DEFINE_RECEIVE_PACKET_END

DEFINE_EMPTY_SEND_PACKET(CGroupReadyReplyProtocol)

//2-8
//获取组内成员列表
#define PROTOCOL_TYPE_GROUP_UL COMBINE_PROTOCOL_TYPE(2, 8)

DEFINE_RECEIVE_PACKET_BEGIN(CGroupULProtocol)
	byte ToType;
	uint32_t ToId;
	uint32_t Room;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, ToType);
		PACKET_DECODE(UInt32, ToId);
		if ((unsigned)ToType == (unsigned)GT_ALLIANCE_FIGHT)
		{
			PACKET_DECODE(UInt32, Room);
		}
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u",(unsigned)ToType, ToId)
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CGroupULReplyProtocol)
	UserList Users;
	byte ToType;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt16, Users.size());
		PACKET_ENCODE(Byte,ToType);
		for(UserList::const_iterator itr = Users.begin(); itr != Users.end(); itr++)
		{
			PACKET_ENCODE(UInt32, itr->UserId);
			PACKET_ENCODE(String, itr->Name);
		}
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("USerCount=%u", (unsigned)Users.size())
DEFINE_SEND_PACKET_END

//2-9
//设置组状态
#define PROTOCOL_TYPE_GROUP_STAT COMBINE_PROTOCOL_TYPE(2, 9)
DEFINE_RECEIVE_PACKET_BEGIN(CGroupStatProtocol)
	byte ToType;
	uint32_t ToId;
	byte Stat;
	uint32_t Room;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, ToType);
		PACKET_DECODE(UInt32, ToId);
		PACKET_DECODE(Byte, Stat);
		if ((unsigned)ToType == (unsigned)GT_ALLIANCE_FIGHT)
		{
			PACKET_DECODE(UInt32, Room);
		}
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u",(unsigned)ToType, ToId)
DEFINE_RECEIVE_PACKET_END

DEFINE_EMPTY_SEND_PACKET(CGroupStatReplyProtocol)

//2-10
//令指定用户退出指定组
#define PROTOCOL_TYPE_GROUP_KICK COMBINE_PROTOCOL_TYPE(2, 10)
DEFINE_RECEIVE_PACKET_BEGIN(CGroupKickProtocol)
	byte ToType;
	uint32_t ToId;
	uint32_t UserId;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, ToType);
		PACKET_DECODE(UInt32, ToId);
		PACKET_DECODE(UInt32, UserId);		
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("Type=%u&Id=%u",(unsigned)ToType, ToId)
DEFINE_RECEIVE_PACKET_END

DEFINE_EMPTY_SEND_PACKET(CGroupKickReplyProtocol)

#define PROTOCOL_TYPE_GROUP_UD COMBINE_PROTOCOL_TYPE(2, 11)

DEFINE_SEND_PACKET_BEGIN(CGroupUDReplyProtocol)
	UserList Users;
	byte ToType;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt16, Users.size());
		PACKET_ENCODE(Byte,ToType);
		for(UserList::const_iterator itr = Users.begin(); itr != Users.end(); itr++)
		{
			PACKET_ENCODE(UInt32, itr->UserId);
			PACKET_ENCODE(UInt32, itr->Delay);
			PACKET_ENCODE(String, itr->Name);
		}
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("USerCount=%u", (unsigned)Users.size())
DEFINE_SEND_PACKET_END

//2-12
//联盟副本选将
#define PROTOCOL_TYPE_GROUP_SELECT_HERO COMBINE_PROTOCOL_TYPE(2, 12)

DEFINE_RECEIVE_PACKET_BEGIN(CAFightHeroRequestProtocol)
	byte type;
	uint32_t groupId;
	uint32_t allianceFightRoom;
	int32_t heroId;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(UInt32, groupId);
		PACKET_DECODE(Int32, heroId);
		PACKET_DECODE(UInt32, allianceFightRoom);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("groupId=%u&Id=%u", groupId, heroId)
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CAFightHeroReplyProtocol)
	uint32_t ower;
	IMPLEMENT_PACKET_ENCODE_BEGIN
			PACKET_ENCODE(UInt32, ower);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("ower=%u", ower)
DEFINE_SEND_PACKET_END

//2-13
//获取联盟副本选将状态
#define PROTOCOL_TYPE_GROUP_SELECT_HERO_STAT COMBINE_PROTOCOL_TYPE(2, 13)
DEFINE_RECEIVE_PACKET_BEGIN(CAFightHeroStatRequestProtocol)
	byte type;
	uint32_t groupId;
	uint32_t allianceFightRoom;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, type);
		PACKET_DECODE(UInt32, groupId);
		PACKET_DECODE(UInt32, allianceFightRoom);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("groupId=%u", groupId)
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CAFightHeroStatReplyProtocol)
	map<unsigned, unsigned> heroMap;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt32, heroMap.size());
		map<unsigned, unsigned>::iterator itr=heroMap.begin();
		for(;itr!=heroMap.end();itr++)
		{
			PACKET_ENCODE(UInt32, itr->first);
			PACKET_ENCODE(UInt32, itr->second);
		}
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("size=%d",heroMap.size())
DEFINE_SEND_PACKET_END


///CC中转

//3-1
//CC中转，客户端发出请求
#define PROTOCOL_TYPE_CC_TRANSFER_SUBMIT COMBINE_PROTOCOL_TYPE(3, 1)

DEFINE_RECEIVE_PACKET_BEGIN(CCcTransferSubmitRequestProtocol)
	byte ToType;
	uint32_t ToId;
	uint32_t allianceFightRoom;
	//CStaticBuffer<0x8000> Data;
	CDanymicBuffer<0x8000> Data;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, ToType);
		PACKET_DECODE(UInt32, ToId);
		if ((unsigned)ToType == (unsigned)GT_ALLIANCE_FIGHT)
		{
			PACKET_DECODE(UInt32, allianceFightRoom);
		}
		PACKET_DECODE(Buffer, &Data);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("ToType=%u&ToId=%u&DataSize=%u", (unsigned)ToType, ToId, Data.GetSize())
DEFINE_RECEIVE_PACKET_END

DEFINE_EMPTY_SEND_PACKET(CCcTransferSubmitReplyProtocol)

//3-2
//CC中转，转发给客户端
#define PROTOCOL_TYPE_CC_TRANSFER_PUSH COMBINE_PROTOCOL_TYPE(3, 2)

DEFINE_SEND_PACKET_BEGIN(CCcTransferPushRequestProtocol)
	uint32_t FromUserId;
	byte ToType;
	uint32_t ToId;
	//CStaticBuffer<0x8000> Data;
	CDanymicBuffer<0x8000> Data;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt32, FromUserId);
		PACKET_ENCODE(Byte, ToType);
		PACKET_ENCODE(UInt32, ToId);
		PACKET_ENCODE(Buffer, &Data);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("FromUserId=%u&ToType=%u&ToId=%u&DataSize=%u", FromUserId, (unsigned)ToType, ToId, Data.GetSize())
DEFINE_SEND_PACKET_END

DEFINE_EMPTY_RECEIVE_PACKET(CCcTransferPushReplyProtocol)

///聊天

//4-1
//用户发出消息
#define PROTOCOL_TYPE_CHAT_SUBMIT COMBINE_PROTOCOL_TYPE(4, 1)

DEFINE_RECEIVE_PACKET_BEGIN(CChatSubmitRequestProtocol)
	byte ToType;
	uint32_t ToId;
	string Message;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, ToType);
		PACKET_DECODE(UInt32, ToId);
		PACKET_DECODE(String, Message);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("ToType=%u&ToId=%u&Message=%s", (unsigned)ToType, ToId, Message.c_str())
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CChatSubmitReplyProtocol)
	string Message;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(String, Message);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("Message=%s", Message.c_str())
DEFINE_SEND_PACKET_END

//4-2
//转发消息给用户
#define PROTOCOL_TYPE_CHAT_PUSH COMBINE_PROTOCOL_TYPE(4, 2)

DEFINE_SEND_PACKET_BEGIN(CChatPushRequestProtocol)
	uint32_t FromUserId;
	string FromName;
	byte ToType;
	uint32_t ToId;
	string Message;
	IMPLEMENT_PACKET_ENCODE_BEGIN
		PACKET_ENCODE(UInt32, FromUserId);
		PACKET_ENCODE(String, FromName);
		PACKET_ENCODE(Byte, ToType);
		PACKET_ENCODE(UInt32, ToId);
		PACKET_ENCODE(String, Message);
	IMPLEMENT_PACKET_ENCODE_END
	IMPLEMENT_TO_STRING("FromUserId=%u&FromName=%s&ToType=%u&ToId=%u&Message=%u",
			FromUserId, FromName.c_str(), (unsigned)ToType, ToId, (unsigned)Message.size())
DEFINE_SEND_PACKET_END

DEFINE_EMPTY_RECEIVE_PACKET(CChatPushReplyProtocol)

//5-1
//指定用户禁言
#define PROTOCOL_TYPE_FORBID_CHAT COMBINE_PROTOCOL_TYPE(5, 1)

DEFINE_RECEIVE_PACKET_BEGIN(CForbidChatRequestProtocol)
	DEFINE_PROTOCOL_TYPE(5, 1)
	uint32_t ForbidUid;
	uint32_t ForbidTs;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(UInt32, ForbidUid);
		PACKET_DECODE(UInt32, ForbidTs);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("ForbidUid=%u&ForbidTs=%u", (unsigned)ForbidUid, ForbidTs)
DEFINE_RECEIVE_PACKET_END

DEFINE_SEND_PACKET_BEGIN(CForbidChatReplyProtocol)
		uint32_t Result;
		string Message;
		IMPLEMENT_PACKET_ENCODE_BEGIN
			PACKET_ENCODE(UInt32, Result);
			PACKET_ENCODE(String, Message);
		IMPLEMENT_PACKET_ENCODE_END
		IMPLEMENT_TO_STRING("Result = %u, Message=%s", Message.c_str(),Result)
DEFINE_SEND_PACKET_END

//5-2
//联盟帮助通知
#define PROTOCOL_TYPE_ALLIANCE_HELP_NOTICE COMBINE_PROTOCOL_TYPE(5, 2)
DEFINE_RECEIVE_PACKET_BEGIN(CCAllianceHelpNoticeRequestProtocol)
	uint32_t ToId;
	string Message;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(UInt32, ToId);
		PACKET_DECODE(String, Message);
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//#define PROTOCOL_TYPE_FIGHTMATCH_CHAT COMBINE_PROTOCOL_TYPE(6, 1)
//
//DEFINE_RECEIVE_PACKET_BEGIN(CFightAgainstRequestProtocol)
//		DEFINE_PROTOCOL_TYPE(6, 1)
//		uint32_t GroupId;
//		GroupEvent Event;
//		IMPLEMENT_PACKET_DECODE_BEGIN
//			PACKET_DECODE(UInt32,GroupId);
//			PACKET_DECODE(Byte, (byte&)Event);
//		IMPLEMENT_PACKET_DECODE_END
//DEFINE_RECEIVE_PACKET_END
//
//#define PROTOCOL_TYPE_MATCHSUCCESS_CHAT COMBINE_PROTOCOL_TYPE(6, 2)
//DEFINE_SEND_PACKET_BEGIN(CFightAgainstReplyProtocol)
//		DEFINE_PROTOCOL_TYPE(6, 2)
//		uint32_t GroupIdA;
//		uint32_t GroupIdB;
//		GroupEvent Event;
//		IMPLEMENT_PACKET_ENCODE_BEGIN
//			PACKET_ENCODE(UInt32,GroupIdA);
//			PACKET_ENCODE(UInt32,GroupIdB);
//			PACKET_ENCODE(Byte, Event);
//		IMPLEMENT_PACKET_ENCODE_END
//DEFINE_SEND_PACKET_END

#define PROTOCOL_EVENT_SECOND_TIMER COMBINE_PROTOCOL_TYPE(7, 1)
DEFINE_RECEIVE_PACKET_BEGIN(CTIMERRequestProtocol)
		DEFINE_PROTOCOL_TYPE(7, 1)
		IMPLEMENT_PACKET_DECODE_BEGIN
		IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

//赤壁
//8-1 广播战斗
#define PROTOCOL_TYPE_CHIBI_WAR_ATTACK COMBINE_PROTOCOL_TYPE(8, 1)
DEFINE_RECEIVE_PACKET_BEGIN(CChibiWarAttackRequestProtocol)
	DEFINE_PROTOCOL_TYPE(8, 1)
	uint32_t redbossblood;
	uint32_t bluebossblood;
	uint32_t damage;
	byte direction;
	byte finish;
	byte doublehurt;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(UInt32, redbossblood);
		PACKET_DECODE(UInt32, bluebossblood);
		PACKET_DECODE(UInt32, damage);
		PACKET_DECODE(Byte, direction);
		PACKET_DECODE(Byte, finish);
		PACKET_DECODE(Byte, doublehurt);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("redbossblood=%u&bluebossblood=%u&direction=%d",
			redbossblood, bluebossblood, direction)
DEFINE_RECEIVE_PACKET_END


DEFINE_SEND_PACKET_BEGIN(CChibiWarAttackReplyProtocol)
		DEFINE_PROTOCOL_TYPE(8, 1)
		uint32_t redbossblood;
		uint32_t bluebossblood;
		uint32_t damage;
		byte direction;
		byte finish;
		byte doublehurt;
		IMPLEMENT_PACKET_ENCODE_BEGIN
			PACKET_ENCODE(UInt32,redbossblood);
			PACKET_ENCODE(UInt32,bluebossblood);
			PACKET_ENCODE(UInt32,damage);
			PACKET_ENCODE(Byte, direction);
			PACKET_ENCODE(Byte, finish);
			PACKET_ENCODE(Byte, doublehurt);
		IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END


//8-2广播连珠用户
#define PROTOCOL_TYPE_CHIBI_WAR_SKILL COMBINE_PROTOCOL_TYPE(8, 2)
DEFINE_RECEIVE_PACKET_BEGIN(CChibiWarSkillRequestProtocol)
	DEFINE_PROTOCOL_TYPE(8, 2)
	byte skill_type;
	byte skill;
	byte camp;
	string name;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(String, name);
		PACKET_DECODE(Byte, camp);
		PACKET_DECODE(Byte, skill_type);
		PACKET_DECODE(Byte, skill);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("skill_type=%d&skill=%d", skill_type, skill)
DEFINE_RECEIVE_PACKET_END

DEFINE_EMPTY_SEND_PACKET(CChibiWarSkillReplyProtocol)

//8-3 转发连珠用户
#define PROTOCOL_TYPE_CHIBI_WAR_SKILL_NODEFY COMBINE_PROTOCOL_TYPE(8, 3)
DEFINE_SEND_PACKET_BEGIN(CChibiWarSkillNodefyProtocol)
		DEFINE_PROTOCOL_TYPE(8, 3)
		byte skill_type;
		byte skill;
		byte camp;
		string name;
		IMPLEMENT_PACKET_ENCODE_BEGIN
			PACKET_ENCODE(String, name);
			PACKET_ENCODE(Byte, camp);
			PACKET_ENCODE(Byte, skill_type);
			PACKET_ENCODE(Byte, skill);
		IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END

//NewWorld
//9-1 battle
#define PROTOCOL_TYPE_NEW_WORLD_BATTLE COMBINE_PROTOCOL_TYPE(9, 1)
DEFINE_RECEIVE_PACKET_BEGIN(CNewWorldBattleRequestProtocol)
	DEFINE_PROTOCOL_TYPE(9, 1)
	byte cid;
	byte kingdom;
	byte battle;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cid);
		PACKET_DECODE(Byte, kingdom);
		PACKET_DECODE(Byte, battle);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("cid=%u&kingdom=%u&battle=%d",
			cid, kingdom, battle)
DEFINE_RECEIVE_PACKET_END


DEFINE_SEND_PACKET_BEGIN(CNewWorldBattleReplyProtocol)
		DEFINE_PROTOCOL_TYPE(9, 1)
		byte cid;
		byte kingdom;
		byte battle;
		IMPLEMENT_PACKET_ENCODE_BEGIN
			PACKET_ENCODE(Byte, cid);
			PACKET_ENCODE(Byte, kingdom);
			PACKET_ENCODE(Byte, battle);
		IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END

//NewWorldBattle
//10-1 battle
#define PROTOCOL_TYPE_NEW_WORLD_BATTLE_BATTLE COMBINE_PROTOCOL_TYPE(10, 1)
DEFINE_RECEIVE_PACKET_BEGIN(CNewWorldBattleBattleRequestProtocol)
	DEFINE_PROTOCOL_TYPE(10, 1)
	byte cid;
	byte kingdom;
	byte battle;
	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cid);
		PACKET_DECODE(Byte, kingdom);
		PACKET_DECODE(Byte, battle);
	IMPLEMENT_PACKET_DECODE_END
	IMPLEMENT_TO_STRING("cid=%u&kingdom=%u&battle=%d",
			cid, kingdom, battle)
DEFINE_RECEIVE_PACKET_END


DEFINE_SEND_PACKET_BEGIN(CNewWorldBattleBattleReplyProtocol)
		DEFINE_PROTOCOL_TYPE(10, 1)
		byte cid;
		byte kingdom;
		byte battle;
		IMPLEMENT_PACKET_ENCODE_BEGIN
			PACKET_ENCODE(Byte, cid);
			PACKET_ENCODE(Byte, kingdom);
			PACKET_ENCODE(Byte, battle);
		IMPLEMENT_PACKET_ENCODE_END
DEFINE_SEND_PACKET_END

#endif /* TOYWARPROTOCOL_H_ */
