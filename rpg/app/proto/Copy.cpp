#include "Copy.h"
#include "MsgPool.h"
namespace copy{
bool CSEnterReincarnCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSEnterReincarnCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSEnterReincarnCopy::clear(){
copyCode = 0;
}
bool CSLeaveCopy::decode(CBufferReader &reader) {
return true;}
bool CSLeaveCopy::encode(CBufferWriter &writer) const {
return true;}
void CSLeaveCopy::clear(){
}
bool CSQuickFinish::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSQuickFinish::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSQuickFinish::clear(){
copyCode = 0;
}
bool CSGotReward::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSGotReward::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSGotReward::clear(){
copyCode = 0;
}
bool CSEnterMagicTowerCopy::decode(CBufferReader &reader) {
return true;}
bool CSEnterMagicTowerCopy::encode(CBufferWriter &writer) const {
return true;}
void CSEnterMagicTowerCopy::clear(){
}
bool CSEnterMaterialCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSEnterMaterialCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSEnterMaterialCopy::clear(){
copyCode = 0;
}
bool CSLotteryMagicTower::decode(CBufferReader &reader) {
return true;}
bool CSLotteryMagicTower::encode(CBufferWriter &writer) const {
return true;}
void CSLotteryMagicTower::clear(){
}
bool SCLotteryMagicTowerResp::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,pos);
return true;}
bool SCLotteryMagicTowerResp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,pos);
return true;}
void SCLotteryMagicTowerResp::clear(){
pos = 0;
}
bool CSQuickFinishMaterial::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);copyCodes.push_back(item);}}
return true;}
bool CSQuickFinishMaterial::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,copyCodes.size());
for(vector<int32_t>::const_iterator vit=copyCodes.begin();vit!=copyCodes.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void CSQuickFinishMaterial::clear(){
copyCodes.clear();
}
bool CSMopMaterial::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSMopMaterial::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSMopMaterial::clear(){
copyCode = 0;
}
bool CSEnterWorldBoss::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSEnterWorldBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSEnterWorldBoss::clear(){
copyCode = 0;
}
}