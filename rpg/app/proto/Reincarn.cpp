#include "Reincarn.h"
#include "MsgPool.h"
namespace reincarn{
bool CSRingActive::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,ringId);
return true;}
bool CSRingActive::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,ringId);
return true;}
void CSRingActive::clear(){
ringId = 0;
}
bool CSReinCarn::decode(CBufferReader &reader) {
return true;}
bool CSReinCarn::encode(CBufferWriter &writer) const {
return true;}
void CSReinCarn::clear(){
}
bool CSReinCarnGetExpByItems::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,itemId);
return true;}
bool CSReinCarnGetExpByItems::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,itemId);
return true;}
void CSReinCarnGetExpByItems::clear(){
itemId = 0;
}
bool CSReinCarnGetExpByLevel::decode(CBufferReader &reader) {
return true;}
bool CSReinCarnGetExpByLevel::encode(CBufferWriter &writer) const {
return true;}
void CSReinCarnGetExpByLevel::clear(){
}
}