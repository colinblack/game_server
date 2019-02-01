/*
 * DataAllServerMapBuffer.h
 *
 *  Created on: 2015-9-17
 *      Author: Ralf
 */

#ifndef DATAALLSERVERMAPBUFFER_H_
#define DATAALLSERVERMAPBUFFER_H_


#include "Kernel.h"

#define ALL_SERVER_MAP_BUFFER_USER_NUM 5000

struct AllServerMapBufferUser
{
	unsigned uid, level;
	AllServerMapBufferUser()
	{
		uid = level = 0;
	}
};

struct DataAllServerMapBuffer
{
	unsigned count;
	AllServerMapBufferUser user[ALL_SERVER_MAP_BUFFER_USER_NUM];
	DataAllServerMapBuffer()
	{
		count = 0;
	}
};


class CDataAllServerMapBuffer
{
public:
	static CDataAllServerMapBuffer* GetCDataAllServerMapBuffer();
	~CDataAllServerMapBuffer(){}
	int Get(map<unsigned, unsigned> &res);
	int Set(unsigned uid, unsigned level);
private:
	CDataAllServerMapBuffer();
	int init(const std::string &path, semdat sem=sem_allserver_map_buffer);
	static CDataAllServerMapBuffer* m_pData;
	bool m_init;
	CShareMemory m_sh;
};



#endif /* DATAALLSERVERMAPBUFFER_H_ */
