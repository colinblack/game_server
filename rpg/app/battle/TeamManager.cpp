#include "TeamManager.h"
#include "BattleInc.h"
TeamManager::TeamManager():m_max_id(1){
}

TeamManager::~TeamManager(){


}

int TeamManager:: Process(uint32_t uid, team::CSCreateTeam *req){
	debug_log("receive create team");
	map<uint32_t, uint32_t>::iterator it = m_uid_teams.find(uid);
	if(it != m_uid_teams.end()){
		error_log("uid:%d create team fail",uid, it->second);
		return R_ERROR;
	}
	Human *pHuman = MapManager::Instance()->getHuman(uid);
	if (pHuman == NULL) {
		return R_ERR_NO_DATA;
	}
	Team t;
	t.copyId = 0;
	t.leader.clear();
	//type处理
	t.leader= pHuman->getEntityMsg();
	t.leader.type_=1;
	//t.entityShows
	t.leaderId = uid;
	t.needLevel =3;
	t.target = req->target;
	for(uint32_t i=0;i<req->targetList.size();i++){
		t.targetList.push_back(req->targetList[i]);
	}
	t.team.id_ = m_max_id++;
	t.team.proxy_ =1;
	t.team.type_=10;
	t.team.server_ = 1;
	t.mems.push_back(pHuman->getEntityMsg());
	t.mems[0].type_=1;
	t.teamName = pHuman->getName();
	m_teams[t.team.id_] = t;
	m_uid_teams[uid] = t.team.id_;
	sendTeamInfo(uid);
	sendTeamList(uid);
	return 0;
}

int TeamManager::Process(uint32_t uid, team::CSLeaveTeam *req){



	return 0;
}



int TeamManager::Process(uint32_t uid, team::CSDisBandTeam *req){
	map<uint32_t, uint32_t>::iterator itr = m_uid_teams.find(uid);
	if(itr == m_uid_teams.end()) return false;
	map<uint32_t,Team>::iterator it = m_teams.find(itr->second);
	if(it == m_teams.end()) return false;

	if(uid != it->second.leaderId) return false;
	for(uint32_t i=0;i<it->second.mems.size();i++){
		uint32_t memUid = it->second.mems[i].id_;
		map<uint32_t, uint32_t>::iterator itp = m_uid_teams.find(memUid);
		if(itp!=m_uid_teams.end()){
			m_uid_teams.erase(itp);
		}
	}
	m_teams.erase(it);
	Msg msg;
	LogicManager::Instance()->SendMsg(uid, CMD_TEAM_UPDATE, &msg);
	return 0;
}

bool TeamManager::doLeaveTeam(uint32_t uid){
	map<uint32_t, uint32_t>::iterator itr = m_uid_teams.find(uid);
	if(itr == m_uid_teams.end()) return false;
	map<uint32_t,Team>::iterator it = m_teams.find(itr->second);
	if(it == m_teams.end()) return false;

	if(uid != it->second.leaderId) return false;
	for(uint32_t i=0;i<it->second.mems.size();i++){
		uint32_t memUid = it->second.mems[i].id_;
		map<uint32_t, uint32_t>::iterator itp = m_uid_teams.find(memUid);
		if(itp!=m_uid_teams.end()){
			m_uid_teams.erase(itp);
		}
	}
	m_teams.erase(it);
	Msg msg;
	LogicManager::Instance()->SendMsg(uid, CMD_TEAM_UPDATE, &msg);
	return true;
}






int TeamManager::Process(uint32_t uid, team::CSCheckMemCopy *req, team::SCCheckMemCopyResponse* resp){
	map<uint32_t, uint32_t>::iterator itr = m_uid_teams.find(uid);
	if(itr == m_uid_teams.end()) return false;
	map<uint32_t,Team>::iterator it = m_teams.find(itr->second);
	if(it == m_teams.end()) return false;
	for(uint32_t i=0;i<it->second.mems.size();i++){
		msgs::STeamMemberCopyCheck tmp ;
		tmp.entityId_ = it->second.mems[i];
		Human *pHuman = MapManager::Instance()->getHuman(it->second.mems[i].id_);
		if (pHuman == NULL) {
			return false;
		}
		tmp.assistRemainNum_ =40;
		tmp.career_ = pHuman->getCareer();
		tmp.enterRemainNum_ = 1;
		tmp.errorCode_=0;
		tmp.errorWhat_="";
		tmp.spaceId_ = pHuman->getMapId();
		resp->checkList.push_back(tmp);
	}
	LogicManager::Instance()->SendMsg(uid,CMD_RPC_TEAM_CHECKMEMBERCOPY,resp);
	return 0;
}


bool TeamManager::sendTeamInfo(uint32_t uid){
	map<uint32_t, uint32_t>::iterator itr = m_uid_teams.find(uid);
	if(itr == m_uid_teams.end()) return false;
	map<uint32_t,Team>::iterator it = m_teams.find(itr->second);
	if(it == m_teams.end()) return false;
	msgs::STeam msg;
	msg.autoJoin_ =false;
	msg.isMatching_ =false;
	msg.copyId_ = it->second.copyId;
	msg.leaderId_= it->second.leader;
	for(uint32_t i=0;i<it->second.mems.size();i++){
		msgs::STeamMember tmp;
		tmp.entityId_ = it->second.mems[i];
		Human *pHuman = MapManager::Instance()->getHuman(it->second.mems[i].id_);
		if (pHuman == NULL) {
			return false;
		}
		tmp.careerLevel_ = 5;
		tmp.career_ = pHuman->getCareer();
		tmp.combat_ = pHuman->getCombat();
		pHuman->getShow(tmp.entityShows_);
		tmp.level_ =  pHuman->getLevel();
		tmp.mirrorId_.clear();
		tmp.name_ = pHuman->getName();
		//tmp.ornaments_
		tmp.sex_ = pHuman->getSex();
		tmp.spaceId_ =pHuman->getMapId();
		msg.members_.push_back(tmp);
		//
	}
	msg.needLevel_ = it->second.needLevel;
	msg.target_ = it->second.target;

	for(uint32_t i=0;i<it->second.targetList.size();i++){
		msg.targetList_.push_back(it->second.targetList[i]);
	}
	msg.teamId_ = it->second.team;
	msg.teamName_  = it->second.teamName;
	LogicManager::Instance()->SendMsg(uid, CMD_TEAM_UPDATE, &msg);
	return true;
}


bool TeamManager::sendTeamList(uint32_t uid){
//	msgs::STeamJoinList msg;
//	msg.list_.clear();
//	LogicManager::Instance()->SendMsg(uid, CMD_TEAM_JOIN_LIST, &msg);

	return true;
}
