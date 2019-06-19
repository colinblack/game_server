#include <string>
#include <stdio.h>
#include "ppacket.h"
#include "log.h"
#include "proto.h"
#include "base64.h"

extern Log log;

Ppacket::Ppacket()
{
	memset(&header, 0, sizeof(struct Pheader));
	body.clear();
}

Ppacket::~Ppacket()
{

}

int Ppacket::safe_check()
{
	if(body.length() != (unsigned int)header.length){
		return -1;
	}
	return header.cmd;
}

int Ppacket::save(Pheader *h, std::string b)
{
	if(h == NULL){
		return -1;
	}
	header.cmd = h->cmd;
	header.length = h->length;
	header.uid = h->uid;
	header.svrid = h->svrid;
	body = b;
	data.clear();
	data.append((const char*)&header, sizeof(struct Pheader));
	data.append(body);
	return safe_check();
}

void Ppacket::pack(unsigned int cmd, unsigned int uid, short svrid)
{
	header.cmd = cmd;
	header.uid = uid;
	header.svrid = svrid;
	header.length = body.length();
	data.clear();
	data.append((const char*)&header, sizeof(struct Pheader));
	data.append(body);
}
