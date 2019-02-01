/*
 * LogicPosManager.cpp
 *
 *  Created on: 2018年9月13日
 *      Author: colin
 */

#include "LogicPostManager.h"


int LogicPostManager::AddPost(unsigned uid, MartialClubItem& club)
{

	int ret = PostManager::Instance()->Add(uid, club);
	if(ret)
	{
		error_log("add post error. uid=%u,ret=%d", uid, ret);
		return ret;
	}

	return 0;
}

void LogicPostManager::FullMessage(unsigned uid, ProtoNotify::PostItemCPPAll* msg)
{
	const auto& mapPost1 = PostManager::Instance()->GetMap(e_Post_inviteUser);
	const auto it1 = mapPost1.find(uid);
	if(it1 != mapPost1.end())
	{
		for(auto iter = it1->second.begin(); iter != it1->second.end(); ++iter)
		{
			MartialClubItem& item =  PostManager::Instance()->GetInviteMartial(uid, iter->first);
			item.SetMessage(msg->add_invite());
		}
	}

	const auto& mapPost2 = PostManager::Instance()->GetMap(e_post_martialBattle);
	const auto it2 = mapPost2.find(uid);
	if(it2 != mapPost2.end())
	{
		for(auto iter = it2->second.begin(); iter != it2->second.end(); ++iter)
		{
			MartialClubItem& item =  PostManager::Instance()->GetMartialBattle(uid, iter->first);
			item.SetMessage(msg->add_battle());
		}
	}
}


int LogicPostManager::Process(unsigned uid, ProtoNotify::PostRemove* req)
{
	PostManager::Instance()->DelItem(uid, req->id(), (PostType)req->type());

	return 0;
}
