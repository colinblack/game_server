#include "Boss.h"
#include "MsgPool.h"
namespace boss{
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
}