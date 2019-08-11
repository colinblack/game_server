#include "Dbs.h"
#include "MsgPool.h"
namespace dbs{
bool TPlayerRole::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int64,curLife_);
PACKET_DECODE(Int64,inPower_);
PACKET_DECODE(Int32,avaLife_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,curMagic_);
PACKET_DECODE(Int64,maxCombat_);
PACKET_DECODE(Int64,lastMaxCombat_);
PACKET_DECODE(String,entityShows_);
PACKET_DECODE(String,entityAttrs_);
return true;}
bool TPlayerRole::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int64,curLife_);
PACKET_ENCODE(Int64,inPower_);
PACKET_ENCODE(Int32,avaLife_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,curMagic_);
PACKET_ENCODE(Int64,maxCombat_);
PACKET_ENCODE(Int64,lastMaxCombat_);
PACKET_ENCODE(String,entityShows_);
PACKET_ENCODE(String,entityAttrs_);
return true;}
void TPlayerRole::clear(){
playerId_ = 0;
roleId_ = 0;
career_ = 0;
curLife_ = 0;
inPower_ = 0;
avaLife_ = 0;
combat_ = 0;
curMagic_ = 0;
maxCombat_ = 0;
lastMaxCombat_ = 0;
entityShows_.clear();
entityAttrs_.clear();
}
bool TPlayer::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,username_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,sex_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,careerLevel_);
PACKET_DECODE(Int32,hangLevel_);
PACKET_DECODE(Int32,hangPower_);
PACKET_DECODE(Int64,lastHangDt_);
PACKET_DECODE(Int32,vipLevel_);
PACKET_DECODE(String,gameChannel_);
PACKET_DECODE(Int32,oldServer_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,nuqi_);
PACKET_DECODE(Int64,levelDt_);
PACKET_DECODE(Int64,exp_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int64,maxCombat_);
PACKET_DECODE(Int64,maxCombatDt_);
PACKET_DECODE(Int64,lastMaxCombat_);
PACKET_DECODE(Int64,offlineDt_);
PACKET_DECODE(Int64,reserveDt_);
PACKET_DECODE(Int64,gameDt_);
PACKET_DECODE(String,ornaments_);
PACKET_DECODE(String,entityShows_);
PACKET_DECODE(Int64,personOSDt_);
PACKET_DECODE(Int64,forbidChat_);
PACKET_DECODE(Int32,forbidLogin_);
return true;}
bool TPlayer::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,username_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,sex_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,careerLevel_);
PACKET_ENCODE(Int32,hangLevel_);
PACKET_ENCODE(Int32,hangPower_);
PACKET_ENCODE(Int64,lastHangDt_);
PACKET_ENCODE(Int32,vipLevel_);
PACKET_ENCODE(String,gameChannel_);
PACKET_ENCODE(Int32,oldServer_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,nuqi_);
PACKET_ENCODE(Int64,levelDt_);
PACKET_ENCODE(Int64,exp_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int64,maxCombat_);
PACKET_ENCODE(Int64,maxCombatDt_);
PACKET_ENCODE(Int64,lastMaxCombat_);
PACKET_ENCODE(Int64,offlineDt_);
PACKET_ENCODE(Int64,reserveDt_);
PACKET_ENCODE(Int64,gameDt_);
PACKET_ENCODE(String,ornaments_);
PACKET_ENCODE(String,entityShows_);
PACKET_ENCODE(Int64,personOSDt_);
PACKET_ENCODE(Int64,forbidChat_);
PACKET_ENCODE(Int32,forbidLogin_);
return true;}
void TPlayer::clear(){
playerId_ = 0;
username_.clear();
type_ = 0;
name_.clear();
sex_ = 0;
career_ = 0;
careerLevel_ = 0;
hangLevel_ = 0;
hangPower_ = 0;
lastHangDt_ = 0;
vipLevel_ = 0;
gameChannel_.clear();
oldServer_ = 0;
level_ = 0;
nuqi_ = 0;
levelDt_ = 0;
exp_ = 0;
combat_ = 0;
maxCombat_ = 0;
maxCombatDt_ = 0;
lastMaxCombat_ = 0;
offlineDt_ = 0;
reserveDt_ = 0;
gameDt_ = 0;
ornaments_.clear();
entityShows_.clear();
personOSDt_ = 0;
forbidChat_ = 0;
forbidLogin_ = 0;
}
bool TPlayerBag::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,privilegeNum_);
PACKET_DECODE(Int32,extendNum_);
PACKET_DECODE(Int32,extendMinute_);
PACKET_DECODE(String,extend_);
return true;}
bool TPlayerBag::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,privilegeNum_);
PACKET_ENCODE(Int32,extendNum_);
PACKET_ENCODE(Int32,extendMinute_);
PACKET_ENCODE(String,extend_);
return true;}
void TPlayerBag::clear(){
playerId_ = 0;
type_ = 0;
privilegeNum_ = 0;
extendNum_ = 0;
extendMinute_ = 0;
extend_.clear();
}
bool TPlayerItem::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int64,itemUid_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,bagType_);
PACKET_DECODE(String,extend_);
PACKET_DECODE(Int64,createDt_);
return true;}
bool TPlayerItem::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int64,itemUid_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,bagType_);
PACKET_ENCODE(String,extend_);
PACKET_ENCODE(Int64,createDt_);
return true;}
void TPlayerItem::clear(){
playerId_ = 0;
itemUid_ = 0;
itemId_ = 0;
itemNum_ = 0;
bagType_ = 0;
extend_.clear();
createDt_ = 0;
}
bool TPlayerSkill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,skillSeries_);
PACKET_DECODE(Int32,skillId_);
return true;}
bool TPlayerSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,skillSeries_);
PACKET_ENCODE(Int32,skillId_);
return true;}
void TPlayerSkill::clear(){
playerId_ = 0;
roleId_ = 0;
skillSeries_ = 0;
skillId_ = 0;
}
bool TPlayerMission::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,missionId_);
PACKET_DECODE(UInt32,step_);
PACKET_DECODE(Int32,status_);
PACKET_DECODE(String,extend_);
PACKET_DECODE(Int64,requestDt_);
return true;}
bool TPlayerMission::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,missionId_);
PACKET_ENCODE(UInt32,step_);
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(String,extend_);
PACKET_ENCODE(Int64,requestDt_);
return true;}
void TPlayerMission::clear(){
playerId_ = 0;
missionId_ = 0;
step_ = 0;
status_ = 0;
extend_.clear();
requestDt_ = 0;
}
bool TPlayerConfig::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,extend_);
return true;}
bool TPlayerConfig::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,extend_);
return true;}
void TPlayerConfig::clear(){
playerId_ = 0;
extend_.clear();
}
bool TPlayerCopyData::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,copyGroup_);
PACKET_DECODE(Int32,enterTime_);
PACKET_DECODE(Int32,totalCompleteNum_);
PACKET_DECODE(Int32,completeNum_);
PACKET_DECODE(Int32,todayEnterNum_);
PACKET_DECODE(Int32,totalEnterDay_);
PACKET_DECODE(Int32,totalEnterNum_);
PACKET_DECODE(Int32,enterNum_);
PACKET_DECODE(Int32,payNum_);
PACKET_DECODE(Int32,getBackNum_);
PACKET_DECODE(Int32,assistNum_);
PACKET_DECODE(Int32,grabNum_);
PACKET_DECODE(Int64,data_);
PACKET_DECODE(Int64,dataEx_);
PACKET_DECODE(String,extend_);
PACKET_DECODE(String,json_);
return true;}
bool TPlayerCopyData::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,copyGroup_);
PACKET_ENCODE(Int32,enterTime_);
PACKET_ENCODE(Int32,totalCompleteNum_);
PACKET_ENCODE(Int32,completeNum_);
PACKET_ENCODE(Int32,todayEnterNum_);
PACKET_ENCODE(Int32,totalEnterDay_);
PACKET_ENCODE(Int32,totalEnterNum_);
PACKET_ENCODE(Int32,enterNum_);
PACKET_ENCODE(Int32,payNum_);
PACKET_ENCODE(Int32,getBackNum_);
PACKET_ENCODE(Int32,assistNum_);
PACKET_ENCODE(Int32,grabNum_);
PACKET_ENCODE(Int64,data_);
PACKET_ENCODE(Int64,dataEx_);
PACKET_ENCODE(String,extend_);
PACKET_ENCODE(String,json_);
return true;}
void TPlayerCopyData::clear(){
playerId_ = 0;
copyGroup_ = 0;
enterTime_ = 0;
totalCompleteNum_ = 0;
completeNum_ = 0;
todayEnterNum_ = 0;
totalEnterDay_ = 0;
totalEnterNum_ = 0;
enterNum_ = 0;
payNum_ = 0;
getBackNum_ = 0;
assistNum_ = 0;
grabNum_ = 0;
data_ = 0;
dataEx_ = 0;
extend_.clear();
json_.clear();
}
bool TPlayerEquip::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,subtype_);
PACKET_DECODE(UInt32,strength_);
PACKET_DECODE(UInt32,purify_);
PACKET_DECODE(Int32,refineMoney_);
PACKET_DECODE(Int32,zhulingAdvance_);
PACKET_DECODE(Int32,zhulingLevel_);
PACKET_DECODE(Int32,perfect_);
PACKET_DECODE(Int32,quenchGrade_);
PACKET_DECODE(Int32,suitLevel_);
PACKET_DECODE(Int32,spirit_);
PACKET_DECODE(Int32,ringAdvance_);
PACKET_DECODE(Int32,ringBlink_);
PACKET_DECODE(Int32,zhenyan_);
PACKET_DECODE(Int32,advance_);
PACKET_DECODE(Int32,godCast_);
PACKET_DECODE(String,extend_);
PACKET_DECODE(String,extendEx_);
return true;}
bool TPlayerEquip::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,subtype_);
PACKET_ENCODE(UInt32,strength_);
PACKET_ENCODE(UInt32,purify_);
PACKET_ENCODE(Int32,refineMoney_);
PACKET_ENCODE(Int32,zhulingAdvance_);
PACKET_ENCODE(Int32,zhulingLevel_);
PACKET_ENCODE(Int32,perfect_);
PACKET_ENCODE(Int32,quenchGrade_);
PACKET_ENCODE(Int32,suitLevel_);
PACKET_ENCODE(Int32,spirit_);
PACKET_ENCODE(Int32,ringAdvance_);
PACKET_ENCODE(Int32,ringBlink_);
PACKET_ENCODE(Int32,zhenyan_);
PACKET_ENCODE(Int32,advance_);
PACKET_ENCODE(Int32,godCast_);
PACKET_ENCODE(String,extend_);
PACKET_ENCODE(String,extendEx_);
return true;}
void TPlayerEquip::clear(){
playerId_ = 0;
roleId_ = 0;
subtype_ = 0;
strength_ = 0;
purify_ = 0;
refineMoney_ = 0;
zhulingAdvance_ = 0;
zhulingLevel_ = 0;
perfect_ = 0;
quenchGrade_ = 0;
suitLevel_ = 0;
spirit_ = 0;
ringAdvance_ = 0;
ringBlink_ = 0;
zhenyan_ = 0;
advance_ = 0;
godCast_ = 0;
extend_.clear();
extendEx_.clear();
}
bool TPlayerGuard::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,guardId_);
PACKET_DECODE(Int32,activated_);
PACKET_DECODE(Int32,out_);
PACKET_DECODE(String,extend_);
return true;}
bool TPlayerGuard::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,guardId_);
PACKET_ENCODE(Int32,activated_);
PACKET_ENCODE(Int32,out_);
PACKET_ENCODE(String,extend_);
return true;}
void TPlayerGuard::clear(){
playerId_ = 0;
guardId_ = 0;
activated_ = 0;
out_ = 0;
extend_.clear();
}
bool TPlayerNewPet::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,petId_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,star_);
PACKET_DECODE(Int32,fly_);
PACKET_DECODE(Int32,flyBless_);
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int32,target_);
PACKET_DECODE(String,futi_);
return true;}
bool TPlayerNewPet::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,petId_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,star_);
PACKET_ENCODE(Int32,fly_);
PACKET_ENCODE(Int32,flyBless_);
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int32,target_);
PACKET_ENCODE(String,futi_);
return true;}
void TPlayerNewPet::clear(){
playerId_ = 0;
petId_ = 0;
level_ = 0;
star_ = 0;
fly_ = 0;
flyBless_ = 0;
status_ = 0;
target_ = 0;
futi_.clear();
}
bool TPlayerPetFormate::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,formateId_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,exp_);
PACKET_DECODE(String,posInfo_);
return true;}
bool TPlayerPetFormate::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,formateId_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,exp_);
PACKET_ENCODE(String,posInfo_);
return true;}
void TPlayerPetFormate::clear(){
formateId_ = 0;
playerId_ = 0;
level_ = 0;
exp_ = 0;
posInfo_.clear();
}
bool TPlayerMrRight::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,washTime_);
PACKET_DECODE(Int32,targetLevel_);
PACKET_DECODE(String,openHoles_);
PACKET_DECODE(String,tmpHoles_);
return true;}
bool TPlayerMrRight::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,washTime_);
PACKET_ENCODE(Int32,targetLevel_);
PACKET_ENCODE(String,openHoles_);
PACKET_ENCODE(String,tmpHoles_);
return true;}
void TPlayerMrRight::clear(){
playerId_ = 0;
type_ = 0;
washTime_ = 0;
targetLevel_ = 0;
openHoles_.clear();
tmpHoles_.clear();
}
bool TPlayerLifeFairy::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,advanceLevel_);
PACKET_DECODE(Int32,advanceBless_);
PACKET_DECODE(Int32,advanceStar_);
PACKET_DECODE(Int32,advanceTargetLevel_);
return true;}
bool TPlayerLifeFairy::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,advanceLevel_);
PACKET_ENCODE(Int32,advanceBless_);
PACKET_ENCODE(Int32,advanceStar_);
PACKET_ENCODE(Int32,advanceTargetLevel_);
return true;}
void TPlayerLifeFairy::clear(){
playerId_ = 0;
type_ = 0;
advanceLevel_ = 0;
advanceBless_ = 0;
advanceStar_ = 0;
advanceTargetLevel_ = 0;
}
bool TPlayerHolyBeast::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,beastId_);
PACKET_DECODE(Int32,goOut_);
PACKET_DECODE(Int32,talent_);
PACKET_DECODE(Int64,attack_);
PACKET_DECODE(Int64,life_);
PACKET_DECODE(Int64,defense_);
PACKET_DECODE(Int32,eatLevel_);
PACKET_DECODE(Int32,eatExp_);
PACKET_DECODE(Int32,rarity_);
PACKET_DECODE(Int32,modelId_);
PACKET_DECODE(Int32,breedPlayerId_);
PACKET_DECODE(String,breedPlayerName_);
PACKET_DECODE(Int32,breedModelId_);
PACKET_DECODE(Int32,otherTalent_);
PACKET_DECODE(Int64,endBreedDt_);
return true;}
bool TPlayerHolyBeast::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,beastId_);
PACKET_ENCODE(Int32,goOut_);
PACKET_ENCODE(Int32,talent_);
PACKET_ENCODE(Int64,attack_);
PACKET_ENCODE(Int64,life_);
PACKET_ENCODE(Int64,defense_);
PACKET_ENCODE(Int32,eatLevel_);
PACKET_ENCODE(Int32,eatExp_);
PACKET_ENCODE(Int32,rarity_);
PACKET_ENCODE(Int32,modelId_);
PACKET_ENCODE(Int32,breedPlayerId_);
PACKET_ENCODE(String,breedPlayerName_);
PACKET_ENCODE(Int32,breedModelId_);
PACKET_ENCODE(Int32,otherTalent_);
PACKET_ENCODE(Int64,endBreedDt_);
return true;}
void TPlayerHolyBeast::clear(){
playerId_ = 0;
beastId_ = 0;
goOut_ = 0;
talent_ = 0;
attack_ = 0;
life_ = 0;
defense_ = 0;
eatLevel_ = 0;
eatExp_ = 0;
rarity_ = 0;
modelId_ = 0;
breedPlayerId_ = 0;
breedPlayerName_.clear();
breedModelId_ = 0;
otherTalent_ = 0;
endBreedDt_ = 0;
}
bool TPlayerFeiJian::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(Int32,feiJianId_);
PACKET_DECODE(Int32,advanceLevel_);
PACKET_DECODE(Int32,star_);
return true;}
bool TPlayerFeiJian::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(Int32,feiJianId_);
PACKET_ENCODE(Int32,advanceLevel_);
PACKET_ENCODE(Int32,star_);
return true;}
void TPlayerFeiJian::clear(){
playerId_ = 0;
roleId_ = 0;
feiJianId_ = 0;
advanceLevel_ = 0;
star_ = 0;
}
bool TFirstArenaBet::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,id_);
PACKET_DECODE(Int64,playerId_);
PACKET_DECODE(Int64,aPlayerId_);
PACKET_DECODE(Int64,bPlayerId_);
PACKET_DECODE(String,aName_);
PACKET_DECODE(String,bName_);
PACKET_DECODE(Int32,result_);
PACKET_DECODE(Int32,betSelect_);
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int32,bangType_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int64,betDt_);
return true;}
bool TFirstArenaBet::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,id_);
PACKET_ENCODE(Int64,playerId_);
PACKET_ENCODE(Int64,aPlayerId_);
PACKET_ENCODE(Int64,bPlayerId_);
PACKET_ENCODE(String,aName_);
PACKET_ENCODE(String,bName_);
PACKET_ENCODE(Int32,result_);
PACKET_ENCODE(Int32,betSelect_);
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int32,bangType_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int64,betDt_);
return true;}
void TFirstArenaBet::clear(){
id_ = 0;
playerId_ = 0;
aPlayerId_ = 0;
bPlayerId_ = 0;
aName_.clear();
bName_.clear();
result_ = 0;
betSelect_ = 0;
round_ = 0;
bangType_ = 0;
score_ = 0;
betDt_ = 0;
}
bool TFirstArenaRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,id_);
PACKET_DECODE(Int32,proxy_);
PACKET_DECODE(Int32,server_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,careerLevel_);
PACKET_DECODE(String,guildName_);
PACKET_DECODE(Int32,vipLevel_);
PACKET_DECODE(Int32,score_);
PACKET_DECODE(Int32,group_);
PACKET_DECODE(Int32,rank_);
return true;}
bool TFirstArenaRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,id_);
PACKET_ENCODE(Int32,proxy_);
PACKET_ENCODE(Int32,server_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,careerLevel_);
PACKET_ENCODE(String,guildName_);
PACKET_ENCODE(Int32,vipLevel_);
PACKET_ENCODE(Int32,score_);
PACKET_ENCODE(Int32,group_);
PACKET_ENCODE(Int32,rank_);
return true;}
void TFirstArenaRank::clear(){
id_ = 0;
proxy_ = 0;
server_ = 0;
playerId_ = 0;
type_ = 0;
name_.clear();
combat_ = 0;
career_ = 0;
careerLevel_ = 0;
guildName_.clear();
vipLevel_ = 0;
score_ = 0;
group_ = 0;
rank_ = 0;
}
bool TFirstArenaHis::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,id_);
PACKET_DECODE(Int64,aPlayerId_);
PACKET_DECODE(Int64,bPlayerId_);
PACKET_DECODE(Int32,bangType_);
PACKET_DECODE(Int32,round_);
PACKET_DECODE(Int32,num_);
PACKET_DECODE(Int32,result_);
return true;}
bool TFirstArenaHis::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,id_);
PACKET_ENCODE(Int64,aPlayerId_);
PACKET_ENCODE(Int64,bPlayerId_);
PACKET_ENCODE(Int32,bangType_);
PACKET_ENCODE(Int32,round_);
PACKET_ENCODE(Int32,num_);
PACKET_ENCODE(Int32,result_);
return true;}
void TFirstArenaHis::clear(){
id_ = 0;
aPlayerId_ = 0;
bPlayerId_ = 0;
bangType_ = 0;
round_ = 0;
num_ = 0;
result_ = 0;
}
bool TBossKillRecord::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,bossId_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,killDt_);
return true;}
bool TBossKillRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,bossId_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,killDt_);
return true;}
void TBossKillRecord::clear(){
id_ = 0;
type_ = 0;
bossId_ = 0;
playerId_ = 0;
name_.clear();
killDt_ = 0;
}
bool TActive::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,status_);
PACKET_DECODE(Int32,cross_);
PACKET_DECODE(Int64,beginDt_);
PACKET_DECODE(Int64,endDt_);
PACKET_DECODE(String,timeOfDay_);
PACKET_DECODE(String,dayOfWeek_);
PACKET_DECODE(Int32,minOpenDay_);
PACKET_DECODE(Int32,maxOpenDay_);
PACKET_DECODE(Int32,duration_);
PACKET_DECODE(Int32,prepare_);
PACKET_DECODE(String,extend_);
return true;}
bool TActive::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(Int32,cross_);
PACKET_ENCODE(Int64,beginDt_);
PACKET_ENCODE(Int64,endDt_);
PACKET_ENCODE(String,timeOfDay_);
PACKET_ENCODE(String,dayOfWeek_);
PACKET_ENCODE(Int32,minOpenDay_);
PACKET_ENCODE(Int32,maxOpenDay_);
PACKET_ENCODE(Int32,duration_);
PACKET_ENCODE(Int32,prepare_);
PACKET_ENCODE(String,extend_);
return true;}
void TActive::clear(){
id_ = 0;
type_ = 0;
name_.clear();
status_ = 0;
cross_ = 0;
beginDt_ = 0;
endDt_ = 0;
timeOfDay_.clear();
dayOfWeek_.clear();
minOpenDay_ = 0;
maxOpenDay_ = 0;
duration_ = 0;
prepare_ = 0;
extend_.clear();
}
bool TPlayerCombat::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,extend_);
return true;}
bool TPlayerCombat::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,extend_);
return true;}
void TPlayerCombat::clear(){
playerId_ = 0;
extend_.clear();
}
bool TXiuXianHoleRank::decode(CBufferReader &reader) {
PACKET_DECODE(Int64,id_);
PACKET_DECODE(Int32,proxy_);
PACKET_DECODE(Int32,server_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int64,combat_);
PACKET_DECODE(Int32,layer_);
PACKET_DECODE(Int32,xianYuan_);
PACKET_DECODE(Int32,rank_);
return true;}
bool TXiuXianHoleRank::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int64,id_);
PACKET_ENCODE(Int32,proxy_);
PACKET_ENCODE(Int32,server_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int64,combat_);
PACKET_ENCODE(Int32,layer_);
PACKET_ENCODE(Int32,xianYuan_);
PACKET_ENCODE(Int32,rank_);
return true;}
void TXiuXianHoleRank::clear(){
id_ = 0;
proxy_ = 0;
server_ = 0;
playerId_ = 0;
name_.clear();
combat_ = 0;
layer_ = 0;
xianYuan_ = 0;
rank_ = 0;
}
bool TTreasureRecord::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,treasureId_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,career_);
PACKET_DECODE(Int32,level_);
PACKET_DECODE(Int32,careerLevel_);
PACKET_DECODE(Int64,drawDt_);
return true;}
bool TTreasureRecord::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,treasureId_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,career_);
PACKET_ENCODE(Int32,level_);
PACKET_ENCODE(Int32,careerLevel_);
PACKET_ENCODE(Int64,drawDt_);
return true;}
void TTreasureRecord::clear(){
id_ = 0;
type_ = 0;
treasureId_ = 0;
playerId_ = 0;
name_.clear();
career_ = 0;
level_ = 0;
careerLevel_ = 0;
drawDt_ = 0;
}
bool TRedPacket::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,status_);
PACKET_DECODE(String,senderName_);
PACKET_DECODE(Int32,senderCareer_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,guildId_);
PACKET_DECODE(Int32,moneyNum_);
PACKET_DECODE(Int32,splitNum_);
PACKET_DECODE(String,extend_);
PACKET_DECODE(Int64,createDt_);
return true;}
bool TRedPacket::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,status_);
PACKET_ENCODE(String,senderName_);
PACKET_ENCODE(Int32,senderCareer_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,guildId_);
PACKET_ENCODE(Int32,moneyNum_);
PACKET_ENCODE(Int32,splitNum_);
PACKET_ENCODE(String,extend_);
PACKET_ENCODE(Int64,createDt_);
return true;}
void TRedPacket::clear(){
id_ = 0;
type_ = 0;
status_ = 0;
senderName_.clear();
senderCareer_ = 0;
playerId_ = 0;
guildId_ = 0;
moneyNum_ = 0;
splitNum_ = 0;
extend_.clear();
createDt_ = 0;
}
bool TToplist::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,version_);
PACKET_DECODE(Int32,toplistType_);
PACKET_DECODE(Int32,proxyId_);
PACKET_DECODE(Int32,serverId_);
PACKET_DECODE(Int32,entityType_);
PACKET_DECODE(Int32,entityId_);
PACKET_DECODE(Int32,rank_);
PACKET_DECODE(Int64,value_);
PACKET_DECODE(Int64,value2_);
PACKET_DECODE(String,property1_);
PACKET_DECODE(String,property2_);
PACKET_DECODE(String,property3_);
PACKET_DECODE(String,extend_);
PACKET_DECODE(Int64,updateDt_);
return true;}
bool TToplist::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,version_);
PACKET_ENCODE(Int32,toplistType_);
PACKET_ENCODE(Int32,proxyId_);
PACKET_ENCODE(Int32,serverId_);
PACKET_ENCODE(Int32,entityType_);
PACKET_ENCODE(Int32,entityId_);
PACKET_ENCODE(Int32,rank_);
PACKET_ENCODE(Int64,value_);
PACKET_ENCODE(Int64,value2_);
PACKET_ENCODE(String,property1_);
PACKET_ENCODE(String,property2_);
PACKET_ENCODE(String,property3_);
PACKET_ENCODE(String,extend_);
PACKET_ENCODE(Int64,updateDt_);
return true;}
void TToplist::clear(){
version_ = 0;
toplistType_ = 0;
proxyId_ = 0;
serverId_ = 0;
entityType_ = 0;
entityId_ = 0;
rank_ = 0;
value_ = 0;
value2_ = 0;
property1_.clear();
property2_.clear();
property3_.clear();
extend_.clear();
updateDt_ = 0;
}
bool TDbMarket::decode(CBufferReader &reader) {
PACKET_DECODE(String,uid_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,name_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,price_);
PACKET_DECODE(String,extendJs_);
PACKET_DECODE(Int64,sellTime_);
return true;}
bool TDbMarket::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,uid_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,name_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,price_);
PACKET_ENCODE(String,extendJs_);
PACKET_ENCODE(Int64,sellTime_);
return true;}
void TDbMarket::clear(){
uid_.clear();
playerId_ = 0;
name_.clear();
itemId_ = 0;
itemNum_ = 0;
price_ = 0;
extendJs_.clear();
sellTime_ = 0;
}
bool TMarketHis::decode(CBufferReader &reader) {
PACKET_DECODE(String,uid_);
PACKET_DECODE(Int64,buyEntityId_);
PACKET_DECODE(String,buyPlayerName_);
PACKET_DECODE(Int32,itemId_);
PACKET_DECODE(Int32,itemNum_);
PACKET_DECODE(Int32,price_);
PACKET_DECODE(String,extendJs_);
PACKET_DECODE(Int64,dealTime_);
PACKET_DECODE(Int32,isAuction_);
return true;}
bool TMarketHis::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,uid_);
PACKET_ENCODE(Int64,buyEntityId_);
PACKET_ENCODE(String,buyPlayerName_);
PACKET_ENCODE(Int32,itemId_);
PACKET_ENCODE(Int32,itemNum_);
PACKET_ENCODE(Int32,price_);
PACKET_ENCODE(String,extendJs_);
PACKET_ENCODE(Int64,dealTime_);
PACKET_ENCODE(Int32,isAuction_);
return true;}
void TMarketHis::clear(){
uid_.clear();
buyEntityId_ = 0;
buyPlayerName_.clear();
itemId_ = 0;
itemNum_ = 0;
price_ = 0;
extendJs_.clear();
dealTime_ = 0;
isAuction_ = 0;
}
bool TMail::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,code_);
PACKET_DECODE(Int32,isRead_);
PACKET_DECODE(Int32,isFetched_);
PACKET_DECODE(String,sender_);
PACKET_DECODE(String,title_);
PACKET_DECODE(String,content_);
PACKET_DECODE(String,attachments_);
PACKET_DECODE(Int64,mailDt_);
return true;}
bool TMail::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,code_);
PACKET_ENCODE(Int32,isRead_);
PACKET_ENCODE(Int32,isFetched_);
PACKET_ENCODE(String,sender_);
PACKET_ENCODE(String,title_);
PACKET_ENCODE(String,content_);
PACKET_ENCODE(String,attachments_);
PACKET_ENCODE(Int64,mailDt_);
return true;}
void TMail::clear(){
id_ = 0;
playerId_ = 0;
code_ = 0;
isRead_ = 0;
isFetched_ = 0;
sender_.clear();
title_.clear();
content_.clear();
attachments_.clear();
mailDt_ = 0;
}
bool TTip::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(String,key_);
PACKET_DECODE(String,params_);
PACKET_DECODE(Int64,operDt_);
return true;}
bool TTip::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(String,key_);
PACKET_ENCODE(String,params_);
PACKET_ENCODE(Int64,operDt_);
return true;}
void TTip::clear(){
playerId_ = 0;
key_.clear();
params_.clear();
operDt_ = 0;
}
bool TPlayerOnlineSkill::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,playerId_);
PACKET_DECODE(Int32,roleId_);
PACKET_DECODE(String,skills_);
return true;}
bool TPlayerOnlineSkill::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,playerId_);
PACKET_ENCODE(Int32,roleId_);
PACKET_ENCODE(String,skills_);
return true;}
void TPlayerOnlineSkill::clear(){
playerId_ = 0;
roleId_ = 0;
skills_.clear();
}
bool TForbidIp::decode(CBufferReader &reader) {
PACKET_DECODE(String,ip_);
PACKET_DECODE(String,reason_);
return true;}
bool TForbidIp::encode(CBufferWriter &writer) const {
PACKET_ENCODE(String,ip_);
PACKET_ENCODE(String,reason_);
return true;}
void TForbidIp::clear(){
ip_.clear();
reason_.clear();
}
bool TTreasureCrossCount::decode(CBufferReader &reader) {
PACKET_DECODE(Int32,id_);
PACKET_DECODE(Int32,type_);
PACKET_DECODE(Int32,totalCount_);
PACKET_DECODE(String,drawCounts_);
PACKET_DECODE(Int64,drawDt_);
return true;}
bool TTreasureCrossCount::encode(CBufferWriter &writer) const {
PACKET_ENCODE(Int32,id_);
PACKET_ENCODE(Int32,type_);
PACKET_ENCODE(Int32,totalCount_);
PACKET_ENCODE(String,drawCounts_);
PACKET_ENCODE(Int64,drawDt_);
return true;}
void TTreasureCrossCount::clear(){
id_ = 0;
type_ = 0;
totalCount_ = 0;
drawCounts_.clear();
drawDt_ = 0;
}
}