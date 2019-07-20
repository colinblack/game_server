#include "GameApps.h"
#include "MsgPool.h"
namespace igameapp{
bool SFightOper::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Identity item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}seqEntity_.push_back(item);}}
PACKET_DECODE(Int32,skillId_);
if(!centerPoint_.decode(reader)){return false;}
PACKET_DECODE(Int64,nowTime_);
return true;}
bool SFightOper::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,seqEntity_.size());
for(vector<Identity>::const_iterator vit=seqEntity_.begin();vit!=seqEntity_.end();++vit){if(!vit->encode(writer)){return false;}}
PACKET_ENCODE(Int32,skillId_);
if(!centerPoint_.encode(writer)){return false;}
PACKET_ENCODE(Int64,nowTime_);
return true;}
void SFightOper::clear(){
seqEntity_.clear();
skillId_ = 0;
centerPoint_.clear();
nowTime_ = 0;
}
bool SLoginGame::decode(CBufferReader &reader) {
PACKET_DECODE(String,username_);
PACKET_DECODE(String,gameChannel_);
PACKET_DECODE(String,channelId_);
PACKET_DECODE(Int32,time_);
PACKET_DECODE(String,flag_);
PACKET_DECODE(String,version_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,platformData_);
PACKET_DECODE(String,json_);
PACKET_DECODE(String,clientData_);
return true;}
bool SLoginGame::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,username_);
PACKET_ENCODE(String,gameChannel_);
PACKET_ENCODE(String,channelId_);
PACKET_ENCODE(Int32,time_);
PACKET_ENCODE(String,flag_);
PACKET_ENCODE(String,version_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,platformData_);
PACKET_ENCODE(String,json_);
PACKET_ENCODE(String,clientData_);
return true;}
void SLoginGame::clear(){
username_.clear();
gameChannel_.clear();
channelId_.clear();
time_ = 0;
flag_.clear();
version_.clear();
playerId_ = 0;
platformData_.clear();
json_.clear();
clientData_.clear();
}
bool SFormateOper::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,petId_);
PACKET_DECODE(Int32,pos_);
return true;}
bool SFormateOper::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,petId_);
PACKET_ENCODE(Int32,pos_);
return true;}
void SFormateOper::clear(){
petId_ = 0;
pos_ = 0;
}
}
