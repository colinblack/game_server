#include "Team.h"
#include "MsgPool.h"
namespace team{
bool CSCreateTeam::decode(CBufferReader &reader) {
if(!target.decode(reader)){return false;}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);targetList.push_back(item);}}
PACKET_DECODE(Int16,needLevel);
return true;}
bool CSCreateTeam::encode(CBufferWriter &writer) const {
if(!target.encode(writer)){return false;}
PACKET_ENCODE(UVar32,targetList.size());
for(vector<int32_t>::const_iterator vit=targetList.begin();vit!=targetList.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int16,needLevel);
return true;}
void CSCreateTeam::clear(){
target.clear();
targetList.clear();
needLevel = 0;
}
bool CSLeaveTeam::decode(CBufferReader &reader) {
return true;}
bool CSLeaveTeam::encode(CBufferWriter &writer) const {
return true;}
void CSLeaveTeam::clear(){
}
bool CSDisBandTeam::decode(CBufferReader &reader) {
return true;}
bool CSDisBandTeam::encode(CBufferWriter &writer) const {
return true;}
void CSDisBandTeam::clear(){
}
bool CSCheckMemCopy::decode(CBufferReader &reader) {
return true;}
bool CSCheckMemCopy::encode(CBufferWriter &writer) const {
return true;}
void CSCheckMemCopy::clear(){
}
bool SCCheckMemCopyResponse::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);msgs::STeamMemberCopyCheck item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}checkList.push_back(item);}}
return true;}
bool SCCheckMemCopyResponse::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,checkList.size());
for(vector<msgs::STeamMemberCopyCheck>::const_iterator vit=checkList.begin();vit!=checkList.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SCCheckMemCopyResponse::clear(){
checkList.clear();
}
}