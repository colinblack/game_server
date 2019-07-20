#include "Card.h"
#include "MsgPool.h"
namespace card{
bool CSCardActiveCard::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,uid);
return true;}
bool CSCardActiveCard::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,uid);
return true;}
void CSCardActiveCard::clear(){
uid = 0;
}
}