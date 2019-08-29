#ifndef _WX_COMM_H_
#define _WX_COMM_H_

#define MAGIC_HEADER 21961

#pragma pack(1)

struct ClientHead{
	uint16_t head;
	uint16_t bodyLen;
	uint32_t tableId;
	uint32_t opId;
};

#pragma pack()


#endif
