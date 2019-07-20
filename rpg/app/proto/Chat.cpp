#include "Chat.h"
#include "MsgPool.h"
namespace chat{
bool CSChatProxy::decode(CBufferReader &reader) {
PACKET_DECODE(Int16,channel);
PACKET_DECODE(String,content);
PACKET_DECODE(String,extend);
if(!targetId.decode(reader)){return false;}
PACKET_DECODE(Int32,useGold);
return true;}
bool CSChatProxy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int16,channel);
PACKET_ENCODE(String,content);
PACKET_ENCODE(String,extend);
if(!targetId.encode(writer)){return false;}
PACKET_ENCODE(Int32,useGold);
return true;}
void CSChatProxy::clear(){
channel = 0;
content.clear();
extend.clear();
targetId.clear();
useGold = 0;
}
}