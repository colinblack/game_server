/*
 * BattleLogWriter.h
 *
 *  Created on: 2015年11月16日
 *      Author: aaron
 */

#ifndef VIDEODATAWRITER_H_
#define VIDEODATAWRITER_H_
#include "Common.h"
#define MAX_PACKET_SIZE 0XF010
#define REMOVE_INTERVAL 300

struct ClientHead{
	uint16_t head;
	uint16_t bodyLen;
	uint16_t offSet;
	uint32_t id;
	int64_t battleId;
	int32_t ts;
};

struct PacketHead{
	uint16_t head;
	uint16_t bodyLen;
	uint16_t offSet;
	uint16_t id;
	uint32_t battleId;
	int32_t ts;
};

struct  ReceiveBuffer{
	uint32_t id;
	uint16_t len;
	uint16_t bodyLen;
	time_t lt;
	char buffer[MAX_PACKET_SIZE];

	ReceiveBuffer():id(0),len(0),bodyLen(0),lt(time(NULL)){
		memset(buffer,0x00,sizeof(buffer));
	}
};

class CVideoDataWriter {
public:
	CVideoDataWriter();
	virtual ~CVideoDataWriter();

public:
	bool init(const string &prefix,uint64_t battleId);
	void onReceive(const char *buffer,size_t iRecvSize);
	void appendText();
	void write();
	void zipWrite();
	bool isTimeToWriteFile();
	bool isTimeDel();
	uint32_t getLastTime(){return lastTime;}
private:
	int32_t  _fd;
	string _filename;
	uint32_t lastTime;
	list<ReceiveBuffer> m_buffer;
	string m_text;
	bool m_isBattleOver;
};

#endif /* BATTLELOGWRITER_H_ */
