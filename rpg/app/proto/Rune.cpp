#include "Rune.h"
#include "MsgPool.h"
namespace rune{
bool CSMagicOpenHole::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId);
PACKET_DECODE(Int32,id);
return true;}
bool CSMagicOpenHole::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId);
PACKET_ENCODE(Int32,id);
return true;}
void CSMagicOpenHole::clear(){
roleId = 0;
id = 0;
}
bool CSMagicLearn::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId);
PACKET_DECODE(Int32,holeId);
PACKET_DECODE(Int64,magicUid);
return true;}
bool CSMagicLearn::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId);
PACKET_ENCODE(Int32,holeId);
PACKET_ENCODE(Int64,magicUid);
return true;}
void CSMagicLearn::clear(){
roleId = 0;
holeId = 0;
magicUid = 0;
}
bool CSMagicUpgrade::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId);
PACKET_DECODE(Int64,magicUid);
return true;}
bool CSMagicUpgrade::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId);
PACKET_ENCODE(Int64,magicUid);
return true;}
void CSMagicUpgrade::clear(){
roleId = 0;
magicUid = 0;
}
bool CSMagicDecomPose::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);uidList.push_back(item);}}
return true;}
bool CSMagicDecomPose::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,uidList.size());
for(vector<int64_t>::const_iterator vit=uidList.begin();vit!=uidList.end();++vit){PACKET_ENCODE(Int64,*vit);}
return true;}
void CSMagicDecomPose::clear(){
uidList.clear();
}
}