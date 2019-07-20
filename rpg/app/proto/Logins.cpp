#include "Logins.h"
#include "MsgPool.h"
namespace logins{
bool SQuery::decode(CBufferReader &reader) {
PACKET_DECODE(String,username_);
PACKET_DECODE(String,gameChannel_);
PACKET_DECODE(String,channelId_);
PACKET_DECODE(Int32,time_);
PACKET_DECODE(String,flag_);
PACKET_DECODE(String,version_);
PACKET_DECODE(Int32,serverId_);
PACKET_DECODE(String,json_);
return true;}
bool SQuery::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,username_);
PACKET_ENCODE(String,gameChannel_);
PACKET_ENCODE(String,channelId_);
PACKET_ENCODE(Int32,time_);
PACKET_ENCODE(String,flag_);
PACKET_ENCODE(String,version_);
PACKET_ENCODE(Int32,serverId_);
PACKET_ENCODE(String,json_);
return true;}
void SQuery::clear(){
username_.clear();
gameChannel_.clear();
channelId_.clear();
time_ = 0;
flag_.clear();
version_.clear();
serverId_ = 0;
json_.clear();
}
bool SQueryResult::decode(CBufferReader &reader) {
PACKET_DECODE(UInt16,proxyId_);
PACKET_DECODE(UInt16,serverId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayer item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}playerList_.push_back(item);}}
return true;}
bool SQueryResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UInt16,proxyId_);
PACKET_ENCODE(UInt16,serverId_);
PACKET_ENCODE(UVar32,playerList_.size());
for(vector<dbs::TPlayer>::const_iterator vit=playerList_.begin();vit!=playerList_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SQueryResult::clear(){
proxyId_ = 0;
serverId_ = 0;
playerList_.clear();
}
bool SLogin::decode(CBufferReader &reader) {
PACKET_DECODE(String,username_);
PACKET_DECODE(String,gameChannel_);
PACKET_DECODE(String,channelId_);
PACKET_DECODE(Int32,time_);
PACKET_DECODE(String,flag_);
PACKET_DECODE(String,version_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int16,sex_);
PACKET_DECODE(Int16,career_);
PACKET_DECODE(Int32,sdkTime_);
PACKET_DECODE(String,platformExtend_);
PACKET_DECODE(Int32,serverId_);
PACKET_DECODE(String,json_);
return true;}
bool SLogin::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,username_);
PACKET_ENCODE(String,gameChannel_);
PACKET_ENCODE(String,channelId_);
PACKET_ENCODE(Int32,time_);
PACKET_ENCODE(String,flag_);
PACKET_ENCODE(String,version_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int16,sex_);
PACKET_ENCODE(Int16,career_);
PACKET_ENCODE(Int32,sdkTime_);
PACKET_ENCODE(String,platformExtend_);
PACKET_ENCODE(Int32,serverId_);
PACKET_ENCODE(String,json_);
return true;}
void SLogin::clear(){
username_.clear();
gameChannel_.clear();
channelId_.clear();
time_ = 0;
flag_.clear();
version_.clear();
playerId_ = 0;
name_.clear();
sex_ = 0;
career_ = 0;
sdkTime_ = 0;
platformExtend_.clear();
serverId_ = 0;
json_.clear();
}
bool SLoginResult::decode(CBufferReader &reader) {
PACKET_DECODE(String,gateHost_);
PACKET_DECODE(Int32,gatePort_);
PACKET_DECODE(String,token_);
PACKET_DECODE(UInt16,proxyId_);
PACKET_DECODE(UInt16,serverId_);
if(!player_.decode(reader)){return false;}
return true;}
bool SLoginResult::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,gateHost_);
PACKET_ENCODE(Int32,gatePort_);
PACKET_ENCODE(String,token_);
PACKET_ENCODE(UInt16,proxyId_);
PACKET_ENCODE(UInt16,serverId_);
if(!player_.encode(writer)){return false;}
return true;}
void SLoginResult::clear(){
gateHost_.clear();
gatePort_ = 0;
token_.clear();
proxyId_ = 0;
serverId_ = 0;
player_.clear();
}
bool SLoginPing::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,clientTs_);
PACKET_DECODE(String,extend_);
return true;}
bool SLoginPing::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,clientTs_);
PACKET_ENCODE(String,extend_);
return true;}
void SLoginPing::clear(){
clientTs_ = 0;
extend_.clear();
}
bool SLoginPong::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,clientTs_);
PACKET_DECODE(Int64,serverTs_);
return true;}
bool SLoginPong::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,clientTs_);
PACKET_ENCODE(Int64,serverTs_);
return true;}
void SLoginPong::clear(){
clientTs_ = 0;
serverTs_ = 0;
}
bool SQueryGameData::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);cmds_.push_back(item);}}
return true;}
bool SQueryGameData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,cmds_.size());
for(vector<int32_t>::const_iterator vit=cmds_.begin();vit!=cmds_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SQueryGameData::clear(){
cmds_.clear();
}
bool SRoleMove::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int64,operTime_);
PACKET_DECODE(UInt16,moveId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}path_.push_back(item);}}
return true;}
bool SRoleMove::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,operTime_);
PACKET_ENCODE(UInt16,moveId_);
PACKET_ENCODE(UVar32,path_.size());
for(vector<Point>::const_iterator vit=path_.begin();vit!=path_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SRoleMove::clear(){
entityId_.clear();
operTime_ = 0;
moveId_ = 0;
path_.clear();
}
bool SEnterHang::decode(CBufferReader &reader) {
return true;}
bool SEnterHang::encode(CBufferWriter &writer) const {
return true;}
void SEnterHang::clear(){
}
bool SBackToCity::decode(CBufferReader &reader) {
return true;}
bool SBackToCity::encode(CBufferWriter &writer) const {
return true;}
void SBackToCity::clear(){
}
bool SBatchFightResultReq::decode(CBufferReader &reader) {
{uint32_t len=0;PACKET_DECODE(UVar32,len);for(uint32_t i=0;i<len;++i){int32_t k;int32_t v;PACKET_DECODE(Int32,k);PACKET_DECODE(Int32,v);monsters_[k] = v;}}
return true;}
bool SBatchFightResultReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,monsters_.size());
for(map<int32_t, int32_t>::const_iterator it=monsters_.begin();it!=monsters_.end();++it){PACKET_ENCODE(Int32,it->first);PACKET_ENCODE(Int32,it->second);}
return true;}
void SBatchFightResultReq::clear(){
monsters_.clear();
}
bool SBatchFightResultResp::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,canRefreshElite_);
return true;}
bool SBatchFightResultResp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,canRefreshElite_);
return true;}
void SBatchFightResultResp::clear(){
canRefreshElite_ = 0;
}
bool SHangChallengeBoss::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);Point item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}resetPoints_.push_back(item);}}
return true;}
bool SHangChallengeBoss::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,resetPoints_.size());
for(vector<Point>::const_iterator vit=resetPoints_.begin();vit!=resetPoints_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SHangChallengeBoss::clear(){
resetPoints_.clear();
}
bool SUseSkill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
if(!oper_.decode(reader)){return false;}
PACKET_DECODE(Int16,skillUid_);
PACKET_DECODE(Bool,noCd_);
return true;}
bool SUseSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
if(!oper_.encode(writer)){return false;}
PACKET_ENCODE(Int16,skillUid_);
PACKET_ENCODE(Bool,noCd_);
return true;}
void SUseSkill::clear(){
roleId_ = 0;
oper_.clear();
skillUid_ = 0;
noCd_ = 0;
}
bool SFightResultReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,monsterId_);
if(!killPoint_.decode(reader)){return false;}
return true;}
bool SFightResultReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,monsterId_);
if(!killPoint_.encode(writer)){return false;}
return true;}
void SFightResultReq::clear(){
monsterId_ = 0;
killPoint_.clear();
}
bool SMapJump::decode(CBufferReader &reader) {
if(!entityId_.decode(reader)){return false;}
PACKET_DECODE(Int64,operTime_);
PACKET_DECODE(UInt16,moveId_);
PACKET_DECODE(String,jumpId_);
PACKET_DECODE(Bool,isReverse_);
return true;}
bool SMapJump::encode(CBufferWriter &writer) const {
if(!entityId_.encode(writer)){return false;}
PACKET_ENCODE(Int64,operTime_);
PACKET_ENCODE(UInt16,moveId_);
PACKET_ENCODE(String,jumpId_);
PACKET_ENCODE(Bool,isReverse_);
return true;}
void SMapJump::clear(){
entityId_.clear();
operTime_ = 0;
moveId_ = 0;
jumpId_.clear();
isReverse_ = 0;
}
bool SMapTransfer::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,operTime_);
PACKET_DECODE(Int32,passType_);
PACKET_DECODE(Int32,passId_);
PACKET_DECODE(Int32,passToId_);
return true;}
bool SMapTransfer::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,operTime_);
PACKET_ENCODE(Int32,passType_);
PACKET_ENCODE(Int32,passId_);
PACKET_ENCODE(Int32,passToId_);
return true;}
void SMapTransfer::clear(){
operTime_ = 0;
passType_ = 0;
passId_ = 0;
passToId_ = 0;
}
bool SMissionReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,missionId_);
return true;}
bool SMissionReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,missionId_);
return true;}
void SMissionReq::clear(){
missionId_ = 0;
}
bool SMissionCommit::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,missionId_);
return true;}
bool SMissionCommit::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,missionId_);
return true;}
void SMissionCommit::clear(){
missionId_ = 0;
}
bool SActiveAdvance::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,type_);
return true;}
bool SActiveAdvance::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,type_);
return true;}
void SActiveAdvance::clear(){
roleId_ = 0;
type_ = 0;
}
bool SUpgradeSkill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,skillId_);
return true;}
bool SUpgradeSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,skillId_);
return true;}
void SUpgradeSkill::clear(){
roleId_ = 0;
skillId_ = 0;
}
bool SAdvanceReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Bool,autoBuy_);
return true;}
bool SAdvanceReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Bool,autoBuy_);
return true;}
void SAdvanceReq::clear(){
roleId_ = 0;
type_ = 0;
itemId_ = 0;
autoBuy_ = 0;
}
bool SAdvanceResp::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,success_);
PACKET_DECODE(Int32,activeMul_);
return true;}
bool SAdvanceResp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,success_);
PACKET_ENCODE(Int32,activeMul_);
return true;}
void SAdvanceResp::clear(){
success_ = 0;
activeMul_ = 0;
}
bool SAdvanceEatDan::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,itemId_);
return true;}
bool SAdvanceEatDan::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,itemId_);
return true;}
void SAdvanceEatDan::clear(){
roleId_ = 0;
type_ = 0;
itemId_ = 0;
}
bool SBagDecompose::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);uidList.push_back(item);}}
return true;}
bool SBagDecompose::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,uidList.size());
for(vector<int64_t>::const_iterator vit=uidList.begin();vit!=uidList.end();++vit){PACKET_ENCODE(Int64,*vit);}
return true;}
void SBagDecompose::clear(){
uidList.clear();
}
bool SShenQiPiece::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,itemId_);
return true;}
bool SShenQiPiece::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,itemId_);
return true;}
void SShenQiPiece::clear(){
itemId_ = 0;
}
bool SShenQi::decode(CBufferReader &reader) {
return true;}
bool SShenQi::encode(CBufferWriter &writer) const {
return true;}
void SShenQi::clear(){
}
bool SUpgradeSkillAll::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
return true;}
bool SUpgradeSkillAll::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
return true;}
void SUpgradeSkillAll::clear(){
roleId_ = 0;
}
bool SEquipEquip::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);uds_.push_back(item);}}
return true;}
bool SEquipEquip::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,uds_.size());
for(vector<int64_t>::const_iterator vit=uds_.begin();vit!=uds_.end();++vit){PACKET_ENCODE(Int64,*vit);}
return true;}
void SEquipEquip::clear(){
roleId_ = 0;
uds_.clear();
}
bool SBagOpenGrid::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bagType_);
PACKET_DECODE(Int32,gridId_);
PACKET_DECODE(Int32,gridNum_);
return true;}
bool SBagOpenGrid::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bagType_);
PACKET_ENCODE(Int32,gridId_);
PACKET_ENCODE(Int32,gridNum_);
return true;}
void SBagOpenGrid::clear(){
bagType_ = 0;
gridId_ = 0;
gridNum_ = 0;
}
bool SActiveTreasure::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
return true;}
bool SActiveTreasure::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
return true;}
void SActiveTreasure::clear(){
type_ = 0;
}
bool STreasureAdvance::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,itemId_);
return true;}
bool STreasureAdvance::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,itemId_);
return true;}
void STreasureAdvance::clear(){
type_ = 0;
itemId_ = 0;
}
bool STreasureEatDan::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,itemId_);
return true;}
bool STreasureEatDan::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,itemId_);
return true;}
void STreasureEatDan::clear(){
type_ = 0;
itemId_ = 0;
}
bool SBagUse::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,bagType_);
PACKET_DECODE(Int64,itemUid_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,value_);
return true;}
bool SBagUse::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,bagType_);
PACKET_ENCODE(Int64,itemUid_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,value_);
return true;}
void SBagUse::clear(){
bagType_ = 0;
itemUid_ = 0;
itemNum_ = 0;
value_ = 0;
}
bool SStrengthenReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);equipType_.push_back(item);}}
PACKET_DECODE(Int32,toLevel_);
return true;}
bool SStrengthenReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,equipType_.size());
for(vector<int32_t>::const_iterator vit=equipType_.begin();vit!=equipType_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(Int32,toLevel_);
return true;}
void SStrengthenReq::clear(){
roleId_ = 0;
equipType_.clear();
toLevel_ = 0;
}
bool SStrengthenResp::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerEquip item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}equip_.push_back(item);}}
return true;}
bool SStrengthenResp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,equip_.size());
for(vector<dbs::TPlayerEquip>::const_iterator vit=equip_.begin();vit!=equip_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SStrengthenResp::clear(){
equip_.clear();
}
bool SAdvanceRide::decode(CBufferReader &reader) {
PACKET_DECODE(Bool,ride_);
return true;}
bool SAdvanceRide::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Bool,ride_);
return true;}
void SAdvanceRide::clear(){
ride_ = 0;
}
bool SPurifyReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);equipType_.push_back(item);}}
return true;}
bool SPurifyReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(UVar32,equipType_.size());
for(vector<int32_t>::const_iterator vit=equipType_.begin();vit!=equipType_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void SPurifyReq::clear(){
roleId_ = 0;
equipType_.clear();
}
bool SPurifyResp::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TPlayerEquip item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}equip_.push_back(item);}}
return true;}
bool SPurifyResp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,equip_.size());
for(vector<dbs::TPlayerEquip>::const_iterator vit=equip_.begin();vit!=equip_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void SPurifyResp::clear(){
equip_.clear();
}
bool STitleReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,titleId_);
return true;}
bool STitleReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,titleId_);
return true;}
void STitleReq::clear(){
roleId_ = 0;
titleId_ = 0;
}
bool SActiveSuitReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,suitId_);
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int64_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int64,item);uids_.push_back(item);}}
return true;}
bool SActiveSuitReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,suitId_);
PACKET_ENCODE(UVar32,uids_.size());
for(vector<int64_t>::const_iterator vit=uids_.begin();vit!=uids_.end();++vit){PACKET_ENCODE(Int64,*vit);}
return true;}
void SActiveSuitReq::clear(){
roleId_ = 0;
suitId_ = 0;
uids_.clear();
}
bool SUnlockSuitReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,suitId_);
return true;}
bool SUnlockSuitReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,suitId_);
return true;}
void SUnlockSuitReq::clear(){
roleId_ = 0;
suitId_ = 0;
}
bool SDressSuitReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,suitId_);
PACKET_DECODE(Bool,isDress_);
return true;}
bool SDressSuitReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,suitId_);
PACKET_ENCODE(Bool,isDress_);
return true;}
void SDressSuitReq::clear(){
roleId_ = 0;
suitId_ = 0;
isDress_ = 0;
}
bool STreasureDrawReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,drewNum_);
return true;}
bool STreasureDrawReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,drewNum_);
return true;}
void STreasureDrawReq::clear(){
type_ = 0;
drewNum_ = 0;
}
bool STreasureDrawResp::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);drawIds_.push_back(item);}}
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);int32_t item;for(uint32_t vi=0;vi<vlen;++vi){PACKET_DECODE(Int32,item);rewards_.push_back(item);}}
return true;}
bool STreasureDrawResp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,drawIds_.size());
for(vector<int32_t>::const_iterator vit=drawIds_.begin();vit!=drawIds_.end();++vit){PACKET_ENCODE(Int32,*vit);}
PACKET_ENCODE(UVar32,rewards_.size());
for(vector<int32_t>::const_iterator vit=rewards_.begin();vit!=rewards_.end();++vit){PACKET_ENCODE(Int32,*vit);}
return true;}
void STreasureDrawResp::clear(){
drawIds_.clear();
rewards_.clear();
}
bool STreasureGetRewardHisReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,type_);
return true;}
bool STreasureGetRewardHisReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,type_);
return true;}
void STreasureGetRewardHisReq::clear(){
type_ = 0;
}
bool STreasureGetRewardHisResp::decode(CBufferReader &reader) {
{uint32_t vlen=0;PACKET_DECODE(UVar32,vlen);dbs::TTreasureRecord item;for(uint32_t vi=0;vi<vlen;++vi){if(!item.decode(reader)){return false;}records_.push_back(item);}}
return true;}
bool STreasureGetRewardHisResp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(UVar32,records_.size());
for(vector<dbs::TTreasureRecord>::const_iterator vit=records_.begin();vit!=records_.end();++vit){if(!vit->encode(writer)){return false;}}
return true;}
void STreasureGetRewardHisResp::clear(){
records_.clear();
}
bool SBagMoveItem::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,fromBagType_);
PACKET_DECODE(Int32,toBagType_);
PACKET_DECODE(Int64,itemUid_);
return true;}
bool SBagMoveItem::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,fromBagType_);
PACKET_ENCODE(Int32,toBagType_);
PACKET_ENCODE(Int64,itemUid_);
return true;}
void SBagMoveItem::clear(){
fromBagType_ = 0;
toBagType_ = 0;
itemUid_ = 0;
}
bool SBagMoveItemAll::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,fromBagType_);
PACKET_DECODE(Int32,toBagType_);
return true;}
bool SBagMoveItemAll::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,fromBagType_);
PACKET_ENCODE(Int32,toBagType_);
return true;}
void SBagMoveItemAll::clear(){
fromBagType_ = 0;
toBagType_ = 0;
}
bool SGetActivityReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,count_);
return true;}
bool SGetActivityReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,count_);
return true;}
void SGetActivityReq::clear(){
id_ = 0;
count_ = 0;
}
bool SGetActivityRewardReq::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
return true;}
bool SGetActivityRewardReq::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
return true;}
void SGetActivityRewardReq::clear(){
id_ = 0;
}
}