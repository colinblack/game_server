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
bool CSEnterTaskCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSEnterTaskCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSEnterTaskCopy::clear(){
copyCode = 0;
}
bool CSSavePlayerConfig::decode(CBufferReader &reader) {
PACKET_DECODE(String,configString);
return true;}
bool CSSavePlayerConfig::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,configString);
return true;}
void CSSavePlayerConfig::clear(){
configString.clear();
}
bool CSGetWorldBossList::decode(CBufferReader &reader) {
return true;}
bool CSGetWorldBossList::encode(CBufferWriter &writer) const {
return true;}
void CSGetWorldBossList::clear(){
}
bool CSGetGodPlaneList::decode(CBufferReader &reader) {
return true;}
bool CSGetGodPlaneList::encode(CBufferWriter &writer) const {
return true;}
void CSGetGodPlaneList::clear(){
}
bool CSEnterGodPlane::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSEnterGodPlane::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSEnterGodPlane::clear(){
copyCode = 0;
}
bool CSFightRevive::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type);
return true;}
bool CSFightRevive::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type);
return true;}
void CSFightRevive::clear(){
type = 0;
}
bool CSEnterImmortalroadCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
return true;}
bool CSEnterImmortalroadCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
return true;}
void CSEnterImmortalroadCopy::clear(){
copyCode = 0;
}
bool CSEnterExpCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,copyCode);
PACKET_DECODE(Int32,count);
return true;}
bool CSEnterExpCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,copyCode);
PACKET_ENCODE(Int32,count);
return true;}
void CSEnterExpCopy::clear(){
copyCode = 0;
count = 0;
}
bool CSEncourageExpCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type);
PACKET_DECODE(Int32,count);
return true;}
bool CSEncourageExpCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type);
PACKET_ENCODE(Int32,count);
return true;}
void CSEncourageExpCopy::clear(){
type = 0;
count = 0;
}
bool CSBuyExtraExpCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type);
return true;}
bool CSBuyExtraExpCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type);
return true;}
void CSBuyExtraExpCopy::clear(){
type = 0;
}
bool CSEnterPartnerIslandCopy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type);
return true;}
bool CSEnterPartnerIslandCopy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type);
return true;}
void CSEnterPartnerIslandCopy::clear(){
type = 0;
}
}