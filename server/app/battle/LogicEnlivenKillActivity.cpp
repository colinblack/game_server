#include "LogicEnlivenKillActivity.h"

const string LogicEnlivenKillActivity::fullrankname("fullserver_kill");

int LogicEnlivenKillActivity::LoginCheck(unsigned uid)
{
	//不管是否在活动范围内，都重置
	DBCUserBaseWrap userwrap(uid);
	unsigned nts = Time::GetGlobalTime();

	bool isNeedrest = LogicCommonUtil::IsCrossTime(userwrap.Obj().last_off_time, nts, KILL_RANK_REWARD);  //22点杀敌榜重置

	if (isNeedrest)
	{
		ResetRewardStatus(uid);
	}

	return 0;
}

int LogicEnlivenKillActivity::RefreshFullServerKillRank(string path)
{
	//判断是否在活动时间内，不在活动时间内，则不做处理
	int ret = CheckActivity();

	if (ret)
	{
		return 0;
	}

	const map<unsigned, unsigned>& datamap = ResourceManager::Instance()->GetMap();
	multimap<unsigned, unsigned> killrank;   //杀敌数为key，下标为value

	for(map<unsigned, unsigned>::const_iterator citer = datamap.begin(); citer != datamap.end(); ++citer)
	{
		unsigned index = citer->second;
		const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[index];

		killrank.insert(make_pair(resource.kill, index));
	}

	Json::Value rank(Json::arrayValue);
	int num = 0;

	for(multimap<unsigned, unsigned>::reverse_iterator it= killrank.rbegin();it!= killrank.rend();++it)
	{
		if(it->first == 0)   //杀敌数为0，则退出循环
			break;

		unsigned index = it->second;
		const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[index];

		//再生成排行榜文件
		rank[num]["uid"] = resource.uid;
		rank[num]["rank"] = num+1;
		rank[num]["name"] = resource.name;
		rank[num]["level"] = resource.property[DemoOfflineProperty_u_level];  //玩家当时等级
		rank[num]["kill"] = it->first;

		++num;

		if(num == 300)
			break;
	}

	string filename = path + fullrankname;

	ret = File::Write(filename, Json::ToString(rank));

	if(ret)
	{
		error_log("[RefreshKillRank] write fullserver_kill fail");
		return ret;
	}

	return 0;
}

int LogicEnlivenKillActivity::ResetRewardStatus(unsigned uid)
{
	DBCUserBaseWrap userwrap(uid);

	if (LogicCommonUtil::CheckPosIsZero(userwrap.Obj().shadow, 1))  //起始位是0，就不用重置了
	{
		return 0;
	}

	for(int i = 1; i <= max_daily_kill_items; ++i)
	{
		LogicCommonUtil::SetZeroCurrent(userwrap.Obj().shadow, i);
	}

	return 0;
}

int LogicEnlivenKillActivity::ProvideRankReward(string path)
{
	int ret = CheckActivity();

	if (ret)
	{
		return 0;
	}

	m_kill_rank.clear();

	//获取杀敌排行榜奖励配置
	const EnlivenKillConfig::EnlivenKill & enlivenkillCfg = EnlivenKillConfigWrap().GetEnlivenConfig();

	//判断文件是否存在
	string filename = path + fullrankname;
	Json::Reader reader;
	Json::Value jdata;

	if (!File::IsExist(filename))   //文件不存在，则认为没有排行榜数据，不做处理
	{
		return 0;
	}

	//读取文件
	string data;
	ret = File::Read(filename, data);

	if (ret)
	{
		error_log("read file error. path=%s", filename.c_str());
		return R_ERR_DATA;
	}

	if (!reader.parse(data, jdata))
	{
		string reason = reader.getFormatedErrorMessages();
		error_log("reader parse failed. reason = %s", reason.c_str());
		return R_ERR_DATA;
	}

	if (!jdata.isArray())
	{
		error_log("json data format error, must be array. path=%s", filename.c_str());
		return R_ERR_DATA;
	}

	//处理数据
	for(unsigned j = 0; j < jdata.size(); ++j)
	{
		unsigned uid = jdata[j]["uid"].asUInt();
		unsigned rank = jdata[j]["rank"].asUInt();

		if (rank <= 10)   //只有前10有奖励
		{
			unsigned count = enlivenkillCfg.rank_reward(rank - 1).reward(0).base().iron();

			m_kill_rank[uid].rank = rank;
			m_kill_rank[uid].reward = count;
			m_kill_rank[uid].kill = jdata[j]["kill"].asUInt();

			//判断用户是否在线
			if (UserManager::Instance()->IsOnline(uid))  //在线
			{
				DBCUserBaseWrap userwrap(uid);
				userwrap.AddResource(0, 0, 0, count, "Enliven_Rank_Reward");
			}
			else  //离线，将黄金写回资源管理
			{
				OfflineResourceItem & resourceitem = LogicResourceManager::Instance()->Get(uid);
				resourceitem.iron += count;
			}
		}
		else  //后面的名次，只记录排名和杀敌数
		{
			m_kill_rank[uid].rank = rank;
			m_kill_rank[uid].kill = jdata[j]["kill"].asUInt();
		}
	}

	//发送通知
	SendRankNotify();

	return 0;
}

int LogicEnlivenKillActivity::SendRankNotify()
{
	map<unsigned, Record>::iterator piter;
	Json::FastWriter writer;
	Json::Value notifyval;
	NotifyItem notifyitem;
	string content;

	unsigned now = Time::GetGlobalTime();

	for(piter = m_kill_rank.begin(); piter != m_kill_rank.end(); ++piter)
	{
		unsigned uid = piter->first;
		unsigned rank = piter->second.rank;
		unsigned iron = piter->second.reward;
		unsigned kill = piter->second.kill;

		//组装json数据
		notifyval.clear();
		content.clear();
		notifyval["rank"] = rank;
		notifyval["iron"] = iron;
		notifyval["kill"] = kill;
		content  = writer.write(notifyval);

		//拼接通知内容
		notifyitem.Clear();

		notifyitem.uid = uid;
		notifyitem.id = e_Notify_Enlivenkill;
		notifyitem.ts = now;
		snprintf(notifyitem.content, NOTIFY_CONTENT_LEN, "%s", content.c_str());

		LogicNotifyManager::Instance()->AddNotify(notifyitem);
	}

	return 0;
}

void LogicEnlivenKillActivity::OnEnd()
{
	//清除该活动产生的通知
	NotifyManager::Instance()->ClearAllItemById(e_Notify_Enlivenkill);
}

int LogicEnlivenKillActivity::Process(unsigned uid, ProtoActivity::OpenEnlivenKillWindowReq *reqmsg, ProtoActivity::OpenEnlivenKillWindowResp * respmsg)
{
	OpenWindow(uid, respmsg);

	return 0;
}

int LogicEnlivenKillActivity::OpenWindow(unsigned uid, ProtoActivity::OpenEnlivenKillWindowResp * respmsg)
{
	//判断是否在活动时间内，不在活动时间内，则不做处理
	int ret = CheckActivity();

	if (ret)
	{
		error_log("activity not open. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	unsigned index = ResourceManager::Instance()->GetIndex(uid);
	const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[index];

	respmsg->set_kill(resource.kill);
	respmsg->set_shadow(BaseManager::Instance()->Get(uid).shadow);

	return 0;
}

int LogicEnlivenKillActivity::Process(unsigned uid, ProtoActivity::ReceiveDailyKillRewardReq *reqmsg, ProtoActivity::ReceiveDailyKillRewardResp * respmsg)
{
	unsigned index = reqmsg->index();

	GetDailyKillReward(uid, index, respmsg);

	return 0;
}

int LogicEnlivenKillActivity::GetDailyKillReward(unsigned uid, unsigned index, ProtoActivity::ReceiveDailyKillRewardResp * respmsg)
{
	//判断是否在活动时间内，不在活动时间内，则不做处理
	int ret = CheckActivity();

	if (ret)
	{
		error_log("activity not open. uid=%u", uid);
		throw runtime_error("activity_not_open");
	}

	if (index < 1 || index > max_daily_kill_items)
	{
		error_log("index param error. uid=%u,index=%u", uid, index);
		throw runtime_error("param_error");
	}

	//根据下标，判断是否能领取该范围的奖励
	unsigned rindex = ResourceManager::Instance()->GetIndex(uid);
	const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[rindex];
	unsigned kill = resource.kill;
	unsigned diff = LogicManager::Instance()->GetOpenDays();

	EnlivenKillConfigWrap configwrap;
	const EnlivenKillConfig::OpenPlatform & openkillquotacfg = configwrap.GetOpenPlatformConfigByDiff(diff);
	unsigned need_kill = openkillquotacfg.kill_quota(index - 1);

	if (kill < need_kill)
	{
		error_log("kill's num not enough. uid=%u,kill=%u,need=%u", uid, kill, need_kill);
		throw runtime_error("kills_not_enough");
	}

	//判断是否已经领取，取shadow的第2-5位，刚好对应下标1-4，即index的值
	DBCUserBaseWrap userwrap(uid);
	if (! LogicCommonUtil::CheckPosIsZero(userwrap.Obj().shadow, index) )  //非0，则表示已领取
	{
		error_log("daily kill reward already been gotten. uid=%u,index=%u", uid, index);
		throw runtime_error("kill_reward_already_gotten");
	}

	//发放奖励
	const EnlivenKillConfig::DailyKillReward & rewardcfg = configwrap.GetDailyKillRankRewardCfg(index);

	for(int i = 0; i < rewardcfg.reward_size(); ++i)
	{
		LogicUserManager::Instance()->OpReward(userwrap, rewardcfg.reward(i), "Enliven_DailyKill_Reward", respmsg->mutable_reward());
	}

	//设置奖励领取标
	LogicCommonUtil::SetBitCurrent(userwrap.Obj().shadow, index);
	userwrap.Save();

	respmsg->set_shadow(userwrap.Obj().shadow);

	return 0;
}

int LogicEnlivenKillActivity::CheckActivity()
{
	if (!IsOn())
	{
		return R_ERROR;
	}

	return 0;
}

