#include "jpacket.h"
#include "proto.h"
#include "log.h"

extern Log log;

void xorfunc(std::string &nString)
{
	const int KEY = 13;
	int strLen = (nString.length());
	char *cString = (char*)(nString.c_str());

	for (int i = 0; i < strLen; i++)
	{
		*(cString + i) = (*(cString + i) ^ KEY);
	}
}

Jpacket::Jpacket()
{
}

Jpacket::~Jpacket()
{
}

std::string& Jpacket::tostring()
{
	return str;
}

Json::Value& Jpacket::tojson()
{
	return val;
}

void Jpacket::end()
{
	string out = val.toStyledString().c_str();
	log.debug("sendDataStyled: [%s]\n", out.c_str());
	xorfunc(out);
	header.length = out.length();

	str.clear();
	str.append((const char *)&header, sizeof(struct Header));
	str.append(out);
}

int Jpacket::parse(std::string &str)
{
	xorfunc(str);
	//log.debug("recvData: [%s]\n", str.c_str());
	if (reader.parse(str, val) < 0)
	{
		return -1;
	}

	log.debug("recvDataStyled: [%s]\n", val.toStyledString().c_str());
	return 0;
}

int Jpacket::sefe_check()
{
	if( (val.type() == Json::objectValue) && (!val["cmd"].isNull()) && (val["cmd"].isNumeric()) )
	{
		int cmd = val["cmd"].asInt();
		return cmd;
	}

	log.error("sefe check err .\n");
	return -2;
}
