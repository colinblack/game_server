/*
 * ProtocolCountryQuest.h
 *
 *  Created on: 2015年12月31日
 *      Author: Administrator
 */

#ifndef PROTOCOL_COUNTRY_QUEST_H_
#define PROTOCOL_COUNTRY_QUEST_H_

#include "Kernel.h"

DEFINE_RECEIVE_PACKET_BEGIN(CRandomQuestProtocol)
	byte cmd;
	byte subCmd;
	uint32_t id;
	uint32_t op;
	vector< pair<uint32_t, uint32_t> > soldier;

	IMPLEMENT_PACKET_DECODE_BEGIN
		PACKET_DECODE(Byte, cmd);
		PACKET_DECODE(Byte, subCmd);
		PACKET_DECODE(UInt32, id);
		PACKET_DECODE(UInt32, op);
		uint32_t len = 0;
		PACKET_DECODE(UInt32, len);
		for(uint32_t i = 0; i < len; ++i) {
			uint32_t sid = 0;
			PACKET_DECODE(UInt32, sid);
			uint32_t scount = 0;
			PACKET_DECODE(UInt32, scount);
			soldier.push_back(make_pair(sid, scount));
		}
	IMPLEMENT_PACKET_DECODE_END
DEFINE_RECEIVE_PACKET_END

#endif /* PROTOCOL_COUNTRY_QUEST_H_ */
