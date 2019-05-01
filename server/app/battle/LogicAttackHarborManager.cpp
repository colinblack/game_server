#include "LogicAttackHarborManager.h"

const string LogicAttackHarborManager::m_wrecagerank("wreckagerank");
const string LogicAttackHarborManager::killrankpath("../webroot/data/");

int LogicAttackHarborManager::AttackHarborInit()
{
	//判断npc是否已刷新
	unsigned last_refreshts = MemoryAttackHarborManager::Instance()->GetLastRefreshts();
	unsigned now = Time::GetGlobalTime();

	if (0 == CTime::GetDayInterval(last_refreshts, now))   //未跨天，则不做处理
	{
		;
	}
	else //跨天，则判断当前时间是否在副本的开启范围内
	{
		bool isactive = IsAttackActive(now);

		if (isactive)  //在活动范围内，但今天又没有开启此活动
		{
			BeginAttackHarbor();  //活动开启
		}
	}

	return 0;
}

void LogicAttackHarborManager::OnMinute()
{
	unsigned now = Time::GetGlobalTime();

	if (IsAttackActive(now))
	{
		unsigned last_refreshts = MemoryAttackHarborManager::Instance()->GetLastRefreshts();

		//只负责跨天的从结束状态变为启动状态
		if (!m_isActive && CTime::GetDayInterval(last_refreshts, now))
		{
			//副本从结束状态转为启动状态
			BeginAttackHarbor();
		}
		else if (!m_isActive)
		{
			m_isActive = true;
		}

		//活动时间范围内，才进行累加
		++m_timer;
		unsigned refresh_frequency = AttackHarborConfigWrap().GetTimeFrequency();

		if (m_timer%refresh_frequency == 0)
		{
			//开启下一波NPC的刷新
			RefreshNPC();
		}

		if (m_timer%time_of_refresh_rank == 0)
		{
			//刷新排行榜
			RefreshWreckageRank();
		}
	}
	else if (m_isActive)
	{
		//活动结束
		EndOfAttackHarbor();
	}
}

void LogicAttackHarborManager::AddTTT(unsigned uid, unsigned count)
{
	//判断是否在活动时间内，如果不在，则残骸次数不累加
	if (!m_isActive)
	{
		return ;
	}

	//从resource中提取玩家的国家信息
	unsigned user_index = ResourceManager::Instance()->GetIndex(uid);

	if (-1 == user_index)
	{
		//不处理不在resource内存中的数据
		return ;
	}

	uint8_t kingdom = ResourceManager::Instance()->m_data->item[user_index].kingdom;

	MemoryAttackHarborManager::Instance()->AddWreckage(uid, kingdom, count);
}

int LogicAttackHarborManager::Process(unsigned uid, ProtoAttackHarbor::OpenAttackWindowReq* msg, ProtoAttackHarbor::OpenAttackWindowResp* resp)
{
	OpenWindow(uid, resp);

	return 0;
}

int LogicAttackHarborManager::Process(unsigned uid, ProtoAttackHarbor::RecieveCountryRewardReq* msg, ProtoAttackHarbor::RecieveCountryRewardResp* resp)
{
	ReceiveCountryReward(uid, resp);

	return 0;
}

int LogicAttackHarborManager::OpenWindow(unsigned uid, ProtoAttackHarbor::OpenAttackWindowResp *msg)
{
	//进行最后的组装
	ProtoAttackHarbor::CountryRankCPPAll * coutrymsg = msg->mutable_countryranks();

	for(int i = 1; i <= SG17_KINGDOM; ++i)
	{
		ProtoAttackHarbor::CountryRankCPP * rankmsg = coutrymsg->add_countryrank();

		rankmsg->set_kingdom(i);
		rankmsg->set_wreckage(ATTMI->m_kwreckage[i]);

		if (ATTMI->m_kindom_trump.count(i))
		{
			//有该国家的王牌
			unsigned uid = ATTMI->m_kindom_trump[i].first;
			unsigned wreckage = ATTMI->m_kindom_trump[i].second;

			unsigned user_index = ResourceManager::Instance()->GetIndex(uid);

			rankmsg->set_trump_uid(uid);
			rankmsg->set_trump_wreckage(wreckage);

			if (-1 != user_index)
			{
				const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[user_index];
				rankmsg->set_trump_name(resource.name);
			}
		}
	}

	//判断奖励是否可领取
	unsigned now = Time::GetGlobalTime();
	unsigned lastts = BaseManager::Instance()->Get(uid).harbor_reward_ts;

	bool isactive = IsAttackActive(now);

	if (isactive)
	{
		//活动范围内，则不可领取
		msg->set_reward_status(false);
	}
	else
	{
		bool isrecevie = IsReceiveReward(lastts);

		if (!isrecevie)
		{
			msg->set_reward_status(true);
		}
		else
		{
			msg->set_reward_status(false);
		}
	}

	//获取个人残骸
	bool isexist = ATTMI->IsUserExist(uid);

	if (isexist)
	{
		int index = ATTMI->GetIndex(uid);

		msg->set_wreckage(ATTMI->m_data->data[index].wreckage);
	}

	return 0;
}

int LogicAttackHarborManager::ReceiveCountryReward(unsigned uid, ProtoAttackHarbor::RecieveCountryRewardResp* msg)
{
	//判断是否在活动时间范围外
	unsigned now = Time::GetGlobalTime();
	bool isactive = IsAttackActive(now);

	if (isactive)  //在活动范围内，但今天又没有开启此活动
	{
		error_log("can't receive reward during fight");
		throw runtime_error("cannot_reward_duringfight");
	}

	DBCUserBaseWrap userwrap(uid);

	//判断是否已领取了奖励
	bool isreceive = IsReceiveReward(userwrap.Obj().harbor_reward_ts);

	if (isreceive)
	{
		error_log("reward already gotten. uid=%u", uid);
		throw runtime_error("reward_already_gotten");
	}

	CalcuteCountryRank();

	uint8_t kingdom = userwrap.Obj().kingdom;
	unsigned rank = m_kingdom_rank[kingdom];

	unsigned diff = LogicManager::Instance()->GetOpenDays();

	//获取奖励
	const AttackHarborConfig::OpenPlatformReward & rewardcfg = AttackHarborConfigWrap().GetRewardByRankDiff(diff, rank);

	for(int i = 0; i < rewardcfg.reward_size(); ++i)
	{
		LogicUserManager::Instance()->OpReward(userwrap, rewardcfg.reward(i), "AttackHarborCountry", msg->mutable_reward());
	}

	//更新奖励领取时间
	userwrap.Obj().harbor_reward_ts = now;
	userwrap.Save();

	msg->set_reward_status(false);

	return 0;
}

bool LogicAttackHarborManager::IsReceiveReward(unsigned lastts)
{
	time_t now = Time::GetGlobalTime();
	struct tm tmNow;   //定义tm类型
	localtime_r(&now, &tmNow);

	time_t last = lastts;
	struct tm tmLast;   //定义tm类型
	localtime_r(&last, &tmLast);

	int dayinter = CTime::GetDayInterval(lastts, now);

	if (dayinter)
	{
		//跨天，不能说明奖励是否已经领取。有可能20:00领取了奖励，第二天18:00再领取时，理论上是不能领取的
		//上次领取时间跨过19点与否
		//关键是当前时间点，如果当前时间点没跨过19点，则领取的是昨天的奖励，则要求上次领奖时间没跨过昨天的19点，如果跨过，则说明已领取了
		//如果当前时间点跨过了19点，领今天的奖，而上次领奖时间是昨天，很明显，今日奖励还没领取
		//如果跨两天以上，则无论是昨天的奖励还是今天的奖励，都没领取

		if (tmNow.tm_hour >= active_time_of_hour)
		{
			 //领取的是今日的奖励
			return false;
		}
		else
		{
			//领取昨天的奖励，判断是否相差1天以上
			if (dayinter > 1)
			{
				//距离今天两天，视为距离昨天1天，则昨天的显然没领取
				return false;
			}
			else if (tmLast.tm_hour >= active_time_of_hour)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		//同一天，则取决于你领哪时候的奖
		//如果当前时间在19点之前，领昨天的奖，则要求上次领奖时间没跨过昨天的19点，如果跨过，则说明已领取了。这个是在同一天的，则明显，已经领取了
		//如果当前时间在19点之后，领今天的奖，跨过今天的19点，则已领取了。
		if (tmNow.tm_hour >= active_time_of_hour)  //领取的是今日的奖励
		{
			if (tmLast.tm_hour >= active_time_of_hour)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			//昨天的奖励，但是上次领取时间是同一天，显然，已经领取过了
			return true;
		}

	}
}

void LogicAttackHarborManager::BeginAttackHarbor()
{
	//清除历史记录，并且进行第一次尝试性的刷新NPC
	ResetAttachRecord();

	//第一次尝试性的刷新NPC
	RefreshNPC();

	//更改活动是否激活标志位
	m_isActive = true;
}

bool myfunction(LogicAttackHarborManager::CountryRank i,LogicAttackHarborManager::CountryRank j)
{
	return i<j;
}

int LogicAttackHarborManager::CalcuteCountryRank()
{
	CountryRank c1(1, ATTMI->m_kwreckage[1], ATTMI->m_kindom_trump[1].first, ATTMI->m_kindom_trump[1].second);
	CountryRank c2(2, ATTMI->m_kwreckage[2], ATTMI->m_kindom_trump[2].first, ATTMI->m_kindom_trump[2].second);
	CountryRank c3(3, ATTMI->m_kwreckage[3], ATTMI->m_kindom_trump[3].first, ATTMI->m_kindom_trump[3].second);

	vector<CountryRank> vctCountry;

	vctCountry.push_back(c1);
	vctCountry.push_back(c2);
	vctCountry.push_back(c3);

	//从小到大进行排序
	sort(vctCountry.begin(), vctCountry.end(), myfunction);

	if (vctCountry[2].kingdom_wreckage == 0)
	{
		m_kingdom_rank[1] = 3;
		m_kingdom_rank[2] = 3;
		m_kingdom_rank[3] = 3;
	}
	else
	{
		if (vctCountry[2] == vctCountry[1] && vctCountry[1] == vctCountry[0])
		{
			//并列的，向后取值
			m_kingdom_rank[1] = 3;
			m_kingdom_rank[2] = 3;
			m_kingdom_rank[3] = 3;
		}
		else if (vctCountry[2] == vctCountry[1])  //并列第二
		{
			m_kingdom_rank[vctCountry[2].kingdom] = 2;
			m_kingdom_rank[vctCountry[1].kingdom] = 2;

			m_kingdom_rank[vctCountry[0].kingdom] = 3;
		}
		else if(vctCountry[1] == vctCountry[0])
		{
			m_kingdom_rank[vctCountry[2].kingdom] = 1;

			 //最后两个并列，则并列第三
			m_kingdom_rank[vctCountry[1].kingdom] = 3;
			m_kingdom_rank[vctCountry[0].kingdom] = 3;
		}
		else  //前3名的数值互不相等
		{
			m_kingdom_rank[vctCountry[2].kingdom] = 1;
			m_kingdom_rank[vctCountry[1].kingdom] = 2;
			m_kingdom_rank[vctCountry[0].kingdom] = 3;
		}
	}

	return 0;
}

int LogicAttackHarborManager::EndOfAttackHarbor()
{
	//进行最后一次排行榜的刷新，以及排行榜奖励的发放
	//先进行最后一次排行榜的刷新
	RefreshWreckageRank();

	//销毁npc
	DestroyNPC();

	//发放奖励
	ProvideRankReward();

	m_isActive = false;
	m_timer = 0;   //重置分钟计数器

	return 0;
}

int LogicAttackHarborManager::ProvideRankReward()
{
	//获取残骸排行榜奖励配置
	const AttackHarborConfig::AttackPearlHarbor & harborcfg = AttackHarborConfigWrap().GetHarborConfig();

	//判断文件是否存在
	string filename = killrankpath + string("/") + m_wrecagerank;

	Json::Reader reader;
	Json::Value jdata;

	if (!File::IsExist(filename))   //文件不存在，则认为没有排行榜数据，不做处理
	{
		return 0;
	}

	//读取文件
	string data;
	int ret = File::Read(filename, data);

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

	int maxsize = harborcfg.individual_reward_size();
	m_wreck_rank.clear();

	//处理数据
	for(unsigned j = 0; j < jdata.size(); ++j)
	{
		unsigned uid = jdata[j]["uid"].asUInt();
		unsigned rank = jdata[j]["rank"].asUInt();

		unsigned count = 0;

		if (rank <= maxsize)   //前面的各有不同奖励
		{
			count = harborcfg.individual_reward(rank - 1);
		}
		else
		{
			count = harborcfg.individual_reward(maxsize - 1);
		}

		m_wreck_rank[uid].rank = rank;
		m_wreck_rank[uid].reward = count;
		m_wreck_rank[uid].wreckage = jdata[j]["wreckage"].asUInt();

		//判断用户是否在线
		if (UserManager::Instance()->IsOnline(uid))  //在线
		{
			DBCUserBaseWrap userwrap(uid);
			userwrap.AddMarket(count, "AttackHarbor");
		}
		else  //离线，将零件写回资源管理
		{
			OfflineResourceItem & resourceitem = LogicResourceManager::Instance()->Get(uid);
			resourceitem.gem += count;
		}
	}

	//发送通知
	SendRankNotify();

	return 0;
}

int LogicAttackHarborManager::SendRankNotify()
{
	map<unsigned, Record>::iterator piter;
	Json::FastWriter writer;
	Json::Value notifyval;
	NotifyItem notifyitem;
	string content;

	unsigned now = Time::GetGlobalTime();

	for(piter = m_wreck_rank.begin(); piter != m_wreck_rank.end(); ++piter)
	{
		unsigned uid = piter->first;
		unsigned rank = piter->second.rank;
		unsigned market = piter->second.reward;
		unsigned wreckage = piter->second.wreckage;

		//组装json数据
		notifyval.clear();
		content.clear();
		notifyval["rank"] = rank;
		notifyval["market"] = market;
		notifyval["wreckage"] = wreckage;
		content  = writer.write(notifyval);

		//拼接通知内容
		notifyitem.Clear();

		notifyitem.uid = uid;
		notifyitem.id = e_Notify_AttackHarbor;
		notifyitem.ts = now;
		snprintf(notifyitem.content, NOTIFY_CONTENT_LEN, "%s", content.c_str());

		LogicNotifyManager::Instance()->AddNotify(notifyitem);
	}

	return 0;
}

int LogicAttackHarborManager::RefreshWreckageRank()
{
	//判断是否在活动时间内，不在活动时间内，则不做处理
	const map<unsigned, unsigned>& datamap = MemoryAttackHarborManager::Instance()->GetMap();
	multimap<unsigned, unsigned> killrank;   //杀敌数为key，下标为value

	for(map<unsigned, unsigned>::const_iterator citer = datamap.begin(); citer != datamap.end(); ++citer)
	{
		unsigned index = citer->second;
		const MemoryAttackRecord & attackrecord = MemoryAttackHarborManager::Instance()->m_data->data[index];

		killrank.insert(make_pair(attackrecord.wreckage, index));
	}

	Json::Value rank(Json::arrayValue);
	int num = 0;

	for(multimap<unsigned, unsigned>::reverse_iterator it= killrank.rbegin();it!= killrank.rend();++it)
	{
		if(it->first == 0)   //杀敌数为0，则退出循环
			break;

		unsigned index = it->second;
		const MemoryAttackRecord & attackrecord = MemoryAttackHarborManager::Instance()->m_data->data[index];

		unsigned uid = attackrecord.uid;
		unsigned user_index = ResourceManager::Instance()->GetIndex(uid);

		if (user_index == -1)
		{
			rank[num]["name"] = "";
			rank[num]["level"] = 0;
			rank[num]["position"] = 0;
			rank[num]["department"] = 0;
		}
		else
		{
			const OfflineResourceItem & resource = ResourceManager::Instance()->m_data->item[user_index];
			rank[num]["name"] = resource.name;
			rank[num]["level"] = resource.property[DemoOfflineProperty_u_level];  //玩家当时等级
			rank[num]["position"] = resource.job;
			rank[num]["department"] = resource.aid;
		}

		//再生成排行榜文件
		rank[num]["uid"] = uid;
		rank[num]["rank"] = num+1;
		rank[num]["wreckage"] = it->first;

		++num;

		if(num == 50)
			break;
	}

	string filename = killrankpath + string("/") + m_wrecagerank;

	int ret = File::Write(filename, Json::ToString(rank));

	if(ret)
	{
		error_log("write fullserver_wrecagerank fail");
		return ret;
	}

	return 0;
}

int LogicAttackHarborManager::RefreshNPC()
{
	//先获取距离开服天数
	unsigned diff = LogicManager::Instance()->GetOpenDays();

	AttackHarborConfigWrap harborcfgwrap;
	int open_index = harborcfgwrap.GetOpenIndex(diff);
	const AttackHarborConfig::AttackPearlHarbor & attackharborcfg = harborcfgwrap.GetHarborConfig();

	time_t now = Time::GetGlobalTime();

	struct tm tmNow;   //定义tm类型
	localtime_r(&now, &tmNow);

	for(int i = 0; i < attackharborcfg.npcrefresh_size(); ++i)
	{
		const AttackHarborConfig::OpenPlatformNPC & npcinfo = attackharborcfg.npcrefresh(i).open_platform_npc(open_index);
		unsigned kindom = attackharborcfg.npcrefresh(i).enemy_kindom();
		unsigned start_time = attackharborcfg.npcrefresh(i).start_time();

		//判断这批城中，当前时间是否允许刷新npc
		if (tmNow.tm_min < (active_time_of_beginmin + start_time)) //时间还没到
		{
			continue;
		}

		for(int j = 0; j < attackharborcfg.npcrefresh(i).cid_size(); ++j)
		{
			unsigned cid = attackharborcfg.npcrefresh(i).cid(j);

			for(int k = 0; k < npcinfo.npcs_size(); ++k)
			{
				WMI->CreateActNPC(e_ttt_npc, npcinfo.npcs(k).count(), cid, kindom, npcinfo.npcs(k).npcid());
			}
		}
	}

	//设置共享内存中的刷新时间
	MemoryAttackHarborManager::Instance()->SetLastRefreshts(now);

	return 0;
}

int LogicAttackHarborManager::DestroyNPC()
{
	unsigned diff = LogicManager::Instance()->GetOpenDays();

	AttackHarborConfigWrap harborcfgwrap;
	int open_index = harborcfgwrap.GetOpenIndex(diff);
	const AttackHarborConfig::AttackPearlHarbor & attackharborcfg = harborcfgwrap.GetHarborConfig();

	for(int i = 0; i < attackharborcfg.npcrefresh_size(); ++i)
	{
		for(int j = 0; j < attackharborcfg.npcrefresh(i).cid_size(); ++j)
		{
			unsigned cid = attackharborcfg.npcrefresh(i).cid(j);

			WMI->DelActNPC(e_ttt_npc, cid);
		}
	}

	return 0;
}

int LogicAttackHarborManager::ResetAttachRecord()
{
	//清除共享数据
	MemoryAttackHarborManager::Instance()->ClearBeforeAttack();

	//清除排行榜数据
	Json::Value rank(Json::arrayValue);
	string filename = killrankpath + string("/") + m_wrecagerank;

	int ret = File::Write(filename, Json::ToString(rank));

	if(ret)
	{
		error_log("[ResetAttachRecord] write fullserver_wrecagerank fail");
		return ret;
	}

	return 0;
}

bool LogicAttackHarborManager::IsAttackActive(time_t ts)
{
	unsigned diff = LogicManager::Instance()->GetOpenDays();

	if ((diff + 1 ) < active_begin_open_day)
	{
		return false;
	}

	//判断ts是否在活动时间范围内.
	//活动范围是19:00-19:30
	struct tm tmNow;   //定义tm类型
	localtime_r(&ts, &tmNow);

	if (tmNow.tm_hour != active_time_of_hour)
	{
		return false;
	}

	//在begin-end之间的分钟才是副本启动范围.[0,30)
	if (tmNow.tm_min >= active_time_of_beginmin && tmNow.tm_min < active_time_of_endmin)
	{
		return true;
	}

	return false;
}
