/*
 * toyward.cpp
 *
 *  Created on: 2012-2-13
 *      Author: dada
 */

#include "LogicInc.h"
#include "ToywarServer.h"

//#define BUILD_SERVER_TEST

#ifdef BUILD_SERVER_TEST
#include "ToywarProtocol.h"

void Test()
{
	CPacket packet;
	packet.PacketType = (EPacketType)1;
	packet.PacketFlag = 2;
	packet.From = 3;
	packet.To = 4;
	packet.SequenceNo = 5;
	packet.RetryTime = 6;
	packet.UserId = 7;
	packet.Key = 8;
	packet.MainProtocolType = 9;
	packet.SubProtocolType = 10;
	packet.ProtocolFlag = 12;
	byte data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	packet.ProtocolBody.CopyFrom(data, sizeof(data));
	byte encodeBuf[100];
	CBuffer encodeBuffer(encodeBuf, sizeof(encodeBuf));
	if(!packet.Encode(&encodeBuffer))
	{
		printf("encode error\n");
		return;
	}
	printf("%s\n", encodeBuffer.ToString().c_str());
	CPacket packetDecode;
	memset(data, 0, sizeof(data));
	if(!packetDecode.Decode(&encodeBuffer))
	{
		printf("decode error\n");
		return;
	}
	printf("%s\n", packetDecode.ProtocolBody.ToString().c_str());
}

void TestClient()
{
	printf("start");
	CTcpChannel client;
	if(!client.CreateClient(0, CInternetAddress("183.60.118.211", 8001), NULL))
	{
		printf("create client error\n");
		return;
	}
	CSocket socket(client.GetSocket());
	socket.SetBlock(true);
	CPacket packetRequest;
	packetRequest.PacketType = PT_CSRequest;
	packetRequest.ProtocolType = PROTOCOL_TYPE_LOGIN;
	packetRequest.UserId = 10000001;
	packetRequest.ProtocolBody.Append((const byte *)"tgw_l7_forward\r\nHost: test.app100688853.twsapp.com:80\r\n\r\n", "tgw_l7_forward\r\nHost: test.app100688853.twsapp.com:80\r\n\r\n".length()-1);
	CStaticBuffer<1000> buffer;
	packetRequest.Encode(&buffer);
	printf("m");
	if(!client.SendData(&buffer))
	{
		printf("client send error\n");
		return;
	}
	buffer.Clear();
	int size = socket.Receive(buffer.GetNativeBuffer(), buffer.GetFreeCapacity());
	if(size < 0)
	{
		printf("client recv error\n");
		return;
	}
	buffer.SetSize(size);
	socket.Detach();
	CPacket packetReply;
	if(!packetReply.Decode(&buffer))
	{
		printf("packet decode fail");
		return;
	}
	if(packetReply.ProtocolResult != 0)
	{
		printf("protocol result fail");
		return;
	}
	printf("protocol result success\n");
	return;
}
#endif
void TestClient1()
{
	printf("start");
	CTcpChannel client;
	if(!client.CreateClient(0, CInternetAddress("183.60.118.211", 8001), NULL))
	{
		printf("create client error\n");
		return;
	}
	CSocket socket(client.GetSocket());
	socket.SetBlock(true);
	CPacket packetRequest;
	packetRequest.PacketType = PT_CSRequest;
	packetRequest.ProtocolType = PROTOCOL_TYPE_LOGIN;
	packetRequest.UserId = 10000001;
	string str = "tgw_l7_forward\r\nHost: test.app100688853.twsapp.com:80\r\n\r\n";
	packetRequest.ProtocolBody.Append((const byte *)"tgw_l7_forward\r\nHost: test.app100688853.twsapp.com:80\r\n\r\n", str.length()-1);
	//CStaticBuffer<1000> buffer;
	CDanymicBuffer<1000> buffer;
	packetRequest.Encode(&buffer);
	printf("m");
	if(!client.SendData(&buffer))
	{
		printf("client send error\n");
		return;
	}
	buffer.Clear();
	int size = socket.Receive(buffer.GetNativeBuffer(), buffer.GetFreeCapacity());
	if(size < 0)
	{
		printf("client recv error\n");
		return;
	}
	buffer.SetSize(size);
	socket.Detach();
	CPacket packetReply;
	if(!packetReply.Decode(&buffer))
	{
		printf("packet decode fail");
		return;
	}
	if(packetReply.ProtocolResult != 0)
	{
		printf("protocol result fail");
		return;
	}
	printf("protocol result success\n");
	return;
}
int main() {
#ifdef BUILD_SERVER_TEST
	TestClient();
	return 0;
#else
	if (!CToywarServer::GetInstance()->Initialize()) {
		printf("Toywar Server Initialize Error\n");
	}
	if (!CToywarServer::GetInstance()->Run()) {
		printf("[TcpServer::Run fail]\n");
	}
	return 0;
#endif
}

