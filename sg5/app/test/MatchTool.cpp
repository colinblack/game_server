#include "LogicInc.h"
#include <iostream>

typedef pair<unsigned, int> U_L_MAP;
typedef pair<unsigned, unsigned> U_U_MAP;
/*
static int extractItem(const string &configPath, map<string, string>& config)
{
	//load config
	CMarkupSTL xmlConf;
	if(!xmlConf.Load(configPath.c_str()))
	{
		error_log("[load language config fail][path=%s]", configPath.c_str());
		return -1;
	}
	if(!xmlConf.FindElem("app"))
	{
		error_log("[parse language config fail][path=%s,error=parse_config_fail]", configPath.c_str());
		return -1;
	}
	xmlConf.IntoElem();
	while(xmlConf.FindElem("param"))
	{
		string name = xmlConf.GetAttrib("name");
		string value = xmlConf.GetAttrib("value");
		config[name] = value;
	}
	return 0;
}
*/
void usage()
{
	cout << "usage: MatchTool regular PlatformType" << endl
		 << "                 top8 PlatformType" << endl
		 << "                 top4 PlatformType" << endl
		 << "                 top2 PlatformType" << endl
		 << "                 finish PlatformType" << endl
		 << "                 next PlatformType" << endl;
}

int AddEmail(unsigned uid, int rank, int cash)
{
	Json::Value temp;
	temp["s"] = "match";
	temp["rank"] = rank;
	temp["cash"] = cash;
	temp["ts"] = Time::GetGlobalTime();
	DataEmail data;
	CLogicEmail matchSendEmail;
	data.title = "match";
	data.text = Json::ToString(temp);
	data.post_ts = Time::GetGlobalTime();
	data.read_ts = 0;
	data.from_name = "";
	data.attach_flag = 0;
	data.uid = ADMIN_UID;
	vector<uint64_t> vecUsersUid;
	vecUsersUid.push_back(uid);
	int ret = matchSendEmail.AddEmail(data, vecUsersUid,true);
	if(0 == ret)
	{
		cout<<rank<<" "<<cash<<" 发送成功" << ret << endl;
	}
	else
	{
		error_log("champion leader prize send mail fail!");
	}

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		usage();
		return 0;
	}
	if (!Kernel::Init(APP_CONFIG_PATH))
	{
		cout << "init fail" << endl;
		return 0;
	}
	Config::SetDomain(0);

	CLogicEmail matchSendEmail;
	DataEmail data;
	vector <U_L_MAP> vecAlliances;

	string action = argv[1];
	int ret = 0;
	CDataMatch match;
	ret = match.Init(Config::GetPath(CONFIG_MATCH_DAT_PATH),sem_match);
	if (ret != 0)
	{
		cout << "init match fail,ret:" << ret << endl;
		return 0;
	}
	if (action == "regular")
	{
		ret = match.StartRegular();
		if (ret != 0)
		{
			cout << "start regular fail,ret:" << ret << endl;
			return 0;
		}
		cout << "start regular ok" << endl;
	}
	else if(action == "guess"){
		ret = match.StartGuess();
		if(ret != 0){
			cout << "start guess fail,ret:" << ret << endl;
			return 0;
		}
		cout << "start guess ok" << endl;
	}
	else if (action == "top8")
	{
		ret = match.StartPlayoff8();
		if (ret != 0)
		{
			cout << "start top8 fail,ret:" << ret << endl;
			return 0;
		}
		cout << "start top8 ok" << endl;
	}
	else if (action == "top4")
	{
		ret = match.StartPlayoff4();
		if (ret != 0)
		{
			cout << "start top4 fail,ret:" << ret << endl;
			return 0;
		}
		cout << "start top4 ok" << endl;
	}
	else if (action == "top2")
	{
		ret = match.StartPlayoff2();
		if (ret != 0)
		{
			cout << "start top2 fail,ret:" << ret << endl;
			return 0;
		}
		cout << "start top2 ok" << endl;
	}
	else if (action == "finish")
	{
		/*
		// 获取邮件文字信息
		map<string, string> config;
		map<string, string> mapLanguageConfig;
		string mappingPath;
		if(!Config::GetValue(mappingPath, CONFIG_PRIZEMAILTEXT_PATH))
		{
			error_log("[get config fail][config_name=%s]", CONFIG_PRIZEMAILTEXT_PATH);
		}
		CMarkupSTL xmlConf;
		if(!xmlConf.Load(mappingPath.c_str()))
		{
			error_log("[load prize_mail_text mapping fail][path=%s]", mappingPath.c_str());
		}
		if(!xmlConf.FindElem("mapping"))
		{
			error_log("[parse platform mapping fail][path=%s,error=parse_xml_fail]", mappingPath.c_str());
		}
		xmlConf.IntoElem();
		while(xmlConf.FindElem("languageItem"))
		{
			string name = xmlConf.GetAttrib("language");
			string value = xmlConf.GetAttrib("config");
			if(name.empty() || value.empty())
			{
				error_log("[invalid platform mapping][path=%s,host=%s,config=%s]",
						mappingPath.c_str(), name.c_str(), value.c_str());
			}
			else
			{
				String::ToLower(name);
				mapLanguageConfig[name] = value;
			}
		}
		string languageType = "CN";
		String::ToLower(languageType);
		map<string, string>::iterator itrMapConfig;
		itrMapConfig = mapLanguageConfig.find(languageType);
		if(itrMapConfig == mapLanguageConfig.end())
		{
			error_log("[unknow_Language_Type][languageType=%s]", languageType.c_str());
		}
		ret = extractItem(itrMapConfig->second, config);
		if (ret !=0)
		{
			error_log("load mail info text fail!");
		}
		 */
		const MatchData *pdata = NULL;
		ret = match.FinishMatch(&pdata);
		if (ret != 0)
		{
			cout << "start finish fail,ret:" << ret << endl;
			return 0;
		}
		cout << "start finish ok" << endl;
		CLogicPay logicPay;
		CLogicEquipment logicEquipment;
		Json::Value res;
		vector<uint64_t> vecRMailAid;	// 存储预赛联盟aid用于发送预赛奖励邮件
		for (unsigned i = 0; i < pdata->numOfReg; i++)
		{
			vecRMailAid.push_back((pdata->rteams[i]).aid);
			for (unsigned j = 0; j < 5; j++)
			{
				//logicPay.ChangePay((pdata->rteams[i]).rivals[j].player.uid , 0, 10, "MATCH_REGULAR");
				logicEquipment.AddOneItem((pdata->rteams[i]).rivals[j].player.uid , 10234, 1, "MATCH_REGULAR", res, false);
			}
		}
		CDataAllianceMember dbMember;

		for (unsigned i = 0; i < 8; i++)
		{
			if ((pdata->top8[i]).aid == 0)
				continue;
			vecAlliances.push_back(make_pair((pdata->top8[i]).aid, 8));
			for (unsigned j = 0; j < 5; j++)
			{
				//logicPay.ChangePay((pdata->top8[i]).players[j].uid, 0, 40, "MATCH_TOP8");
				logicEquipment.AddOneItem((pdata->top8[i]).players[j].uid, 10234, 4, "MATCH_TOP8", res, false);
			}
		}
		for (unsigned i = 0; i < 4; i++)
		{
			if ((pdata->top4[i]).aid == 0)
				continue;
			for(vector<U_L_MAP>::iterator itr=vecAlliances.begin(); itr != vecAlliances.end(); itr++)
			{
				if (itr->first == (pdata->top4[i]).aid)
				{
					itr->second = 4;
				}
			}
			for (unsigned j = 0; j < 5; j++)
			{
				//logicPay.ChangePay((pdata->top4[i]).players[j].uid, 0, 50,"MATCH_TOP4");
				logicEquipment.AddOneItem((pdata->top4[i]).players[j].uid, 10234, 5,"MATCH_TOP4", res, false);
			}
		}
		for (unsigned i = 0; i < 2; i++)
		{
			if ((pdata->top2[i]).aid == 0)
				continue;
			for(vector<U_L_MAP>::iterator itr=vecAlliances.begin(); itr != vecAlliances.end(); itr++)
			{
				if (itr->first == (pdata->top2[i]).aid)
				{
					itr->second = 2;
				}
			}
			for (unsigned j = 0; j < 5; j++)
			{
				//logicPay.ChangePay((pdata->top2[i]).players[j].uid, 0, 50, "MATCH_TOP2");
				logicEquipment.AddOneItem((pdata->top2[i]).players[j].uid, 10234, 5, "MATCH_TOP2", res, false);
			}
		}
		if ((pdata->champion).aid != 0)
		{
			for(vector<U_L_MAP>::iterator itr=vecAlliances.begin(); itr != vecAlliances.end(); itr++)
			{
				if (itr->first == (pdata->champion).aid)
				{
					itr->second = 1;
				}
			}
			for (unsigned j = 0; j < 5; j++)
			{
				//logicPay.ChangePay((pdata->champion).players[j].uid, 0, 50, "MATCH_CHAMPION");
				logicEquipment.AddOneItem((pdata->champion).players[j].uid, 10234, 5, "MATCH_CHAMPION", res, false);
			}
		}

		CLogicGuess logicGuess;
		//vector<U_U_MAP> vecGuessors;
		logicGuess.GuessorsPay(pdata->champion.aid,0);

		// 获取投中竞猜者的uid和获奖金币
		/*
		logicGuess.GuessorsUidCoins(pdata->champion.aid, vecGuessors, 0);
		for(vector<U_U_MAP>::iterator myItr = vecGuessors.begin(); myItr != vecGuessors.end(); myItr++)
		{
			//int tmpUid = myItr->first;
			string tmpCoinsStr = "";
			stringstream ss;
			ss << myItr->second;
			ss >> tmpCoinsStr;
			char str[200];
			snprintf(str,sizeof(str),config["templetGuessContent0"].c_str(), tmpCoinsStr.c_str());
			string tempString(str);
			data.text = tempString;
			data.title = config["mailGuessTitle"];
			data.post_ts = Time::GetGlobalTime();
			data.read_ts = 0;
			data.from_name = "系统管理员";
			data.attach_flag = 0;
			data.uid = ADMIN_UID;
			vector<uint64_t> vecUsersUid;
			vecUsersUid.push_back(myItr->first);
			ret = matchSendEmail.AddEmail(data, vecUsersUid);
			if(0 == ret)
			{
				cout << "竞猜金币发送成功" << ret << endl;
			}
			else
			{
				error_log("champion leader prize send mail fail!");
			}
		}
		*/
		// 盟主、副盟主额外奖励与参赛队员邮件通知
		for(vector<U_L_MAP>::iterator myItr=vecAlliances.begin(); myItr != vecAlliances.end(); myItr++)
		{
			if (myItr->second == 1)
			{
				vector<DataAllianceMember> members;
				dbMember.GetMembers(myItr->first, members);
				for(vector<DataAllianceMember>::iterator itr=members.begin(); itr != members.end(); itr++)
				{
					//DataAllianceMember myMember;
					//myMember = *itr;
					if ((*itr).type == AMT_LEADER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 200, "MATCH_CHAMPION_LEADER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 20, "MATCH_CHAMPION_LEADER", res, false);
						// 发送邮件
						AddEmail((*itr).uid,1,20);
					}
					else if ((*itr).type == AMT_MANAGER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 100, "MATCH_CHAMPION_MANAGER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 10, "MATCH_CHAMPION_MANAGER", res, false);
						// 增加发送邮件
						AddEmail((*itr).uid,1,10);
					}
					else // 非比赛成员邮件奖励通知
					{
						bool flag = true;
						for (unsigned j = 0; j < 5; j++)
						{
							if ((pdata->champion).players[j].uid == itr->uid)
							{
								flag = false;
								break;
							}
						}
						if (flag)
						{
							//logicPay.ChangePay(itr->uid, 0, 20, "MATCH_CHAMPION_MEMBER");
							logicEquipment.AddOneItem(itr->uid, 10234, 2, "MATCH_CHAMPION_MEMBER", res, false);
							AddEmail((*itr).uid,1,2);
						}
					}
				}

				//比赛队伍邮件通知
				for (unsigned j = 0; j < 5; j++)
					AddEmail((pdata->champion).players[j].uid,1,20);
			}
			else if (myItr->second == 2)
			{
				vector<DataAllianceMember> members;
				dbMember.GetMembers(myItr->first, members);
				for(vector<DataAllianceMember>::iterator itr=members.begin(); itr != members.end(); itr++)
				{
					if ((*itr).type == AMT_LEADER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 150, "MATCH_TOP2_LEADER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 15, "MATCH_TOP2_LEADER", res, false);
						// 增加发送邮件
						AddEmail((*itr).uid,2,15);
					}
					else if ((*itr).type == AMT_MANAGER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 75, "MATCH_TOP2_MANAGER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 8, "MATCH_TOP2_MANAGER", res, false);
						// 增加发送邮件
						AddEmail((*itr).uid,2,8);
					}
					else // 非比赛成员邮件奖励通知
					{
						int tempI = 0;
						for (unsigned i = 0; i < 2; i++)
						{
							if((pdata->top2[i]).aid == myItr->first)
							{
								tempI = i;
								break;
							}
						}
						bool flag = true;
						for (unsigned j = 0; j < 5; j++)
						{
							if ((pdata->top2[tempI]).players[j].uid == itr->uid)
							{
								flag = false;
								break;
							}
						}
						if (flag)
						{
							//logicPay.ChangePay(itr->uid, 0, 15, "MATCH_TOP2_MEMBER");
							logicEquipment.AddOneItem(itr->uid, 10234, 2, "MATCH_TOP2_MEMBER", res, false);
							AddEmail((*itr).uid,2,2);
						}
					}
				}
				// 发送邮件通知
				int tempI = 0;
				for (unsigned i = 0; i < 2; i++)
				{
					if((pdata->top2[i]).aid == myItr->first)
					{
						tempI = i;
						break;
					}
				}
				for (unsigned j = 0; j < 5; j++)
					AddEmail((pdata->top2[tempI]).players[j].uid,2,15);
			}
			else if (myItr->second == 4)
			{
				vector<DataAllianceMember> members;
				dbMember.GetMembers(myItr->first, members);
				for(vector<DataAllianceMember>::iterator itr=members.begin(); itr != members.end(); itr++)
				{
					if ((*itr).type == AMT_LEADER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 100, "MATCH_TOP4_LEADER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 10, "MATCH_TOP4_LEADER", res, false);
						// 增加发送邮件
						AddEmail((*itr).uid,3,10);
					}
					else if ((*itr).type == AMT_MANAGER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 50, "MATCH_TOP4_MANAGER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 5, "MATCH_TOP4_MANAGER", res, false);
						// 增加发送邮件
						AddEmail((*itr).uid,3,5);
					}
					else
					{
						for (unsigned i = 0; i < 4; i++)
						{
							if ((pdata->top4[i]).aid == 0)
								continue;
							if ((pdata->top4[i]).aid == myItr->first)
							{
								bool flag = true;
								for (unsigned j = 0; j < 5; j++)
								{
									if ((pdata->top4[i]).players[j].uid == itr->uid)
									{
										flag = false;
										break;
									}
								}
								if (flag)
								{
									//logicPay.ChangePay(itr->uid, 0, 10, "MATCH_TOP4_MEMBER");
									logicEquipment.AddOneItem(itr->uid, 10234, 1, "MATCH_TOP4_MEMBER", res, false);
									AddEmail((*itr).uid,3,1);
								}
							}
						}
					}
				}

				// 发送邮件通知
				for (unsigned i = 0; i < 4; i++)
				{
					if ((pdata->top4[i]).aid == 0)
						continue;
					if ((pdata->top4[i]).aid == myItr->first)
					{
						for (unsigned j = 0; j < 5; j++)
							AddEmail((pdata->top4[i]).players[j].uid,3,10);
					}
				}
			}
			else //if (myItr->second == 8)
			{
				vector<DataAllianceMember> members;
				dbMember.GetMembers(myItr->first, members);
				for(vector<DataAllianceMember>::iterator itr=members.begin(); itr != members.end(); itr++)
				{
					if ((*itr).type == AMT_LEADER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 50, "MATCH_TOP8_LEADER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 5, "MATCH_TOP8_LEADER", res, false);
						// 增加发送邮件
						AddEmail((*itr).uid,4,5);
					}
					else if ((*itr).type == AMT_MANAGER)
					{
						//logicPay.ChangePay((*itr).uid, 0, 25, "MATCH_TOP8_MANAGER");
						logicEquipment.AddOneItem((*itr).uid, 10234, 3, "MATCH_TOP8_MANAGER", res, false);
						// 增加发送邮件
						AddEmail((*itr).uid,4,3);
					}
					else
					{
						for (unsigned i = 0; i < 8; i++)
						{
							if ((pdata->top8[i]).aid == 0)
								continue;
							if ((pdata->top8[i]).aid == myItr->first)
							{
								bool flag = true;
								for (unsigned j = 0; j < 5; j++)
								{
									if ((pdata->top8[i]).players[j].uid == itr->uid)
									{
										flag = false;
										break;
									}
								}
								if (flag)
								{
									//logicPay.ChangePay(itr->uid, 0, 5, "MATCH_TOP8_MEMBER");
									logicEquipment.AddOneItem(itr->uid, 10234, 1, "MATCH_TOP8_MEMBER", res, false);
									AddEmail((*itr).uid,4,1);
								}
							}
						}
					}
				}
				for (unsigned i = 0; i < 8; i++)
				{
					if ((pdata->top8[i]).aid == 0)
						continue;
					if ((pdata->top8[i]).aid == myItr->first)
					{
						for (unsigned j = 0; j < 5; j++)
							AddEmail((pdata->top8[i]).players[j].uid,4,5);
					}
				}
			}
		}
		//预赛邮件通知
		for (unsigned i = 0; i < 8; i++)
		{
			if ((pdata->top8[i]).aid == 0)
				continue;
			for(vector<uint64_t>::iterator itr=vecRMailAid.begin(); itr != vecRMailAid.end(); itr++)
			{
				if (*itr == (pdata->top8[i]).aid)
				{
					vecRMailAid.erase(itr);
					break;
				}
			}
		}

		for (unsigned i = 0; i < pdata->numOfReg; i++)
		{
			for(vector<uint64_t>::iterator itr=vecRMailAid.begin(); itr != vecRMailAid.end(); itr++)
			{
				//cout << "*itr11" << *itr << endl;
				if (*itr == (pdata->rteams[i]).aid)
				{
					//cout << "*itr12" << *itr << endl;
					for (unsigned j = 0; j < 5; j++)
						AddEmail((pdata->rteams[i]).rivals[j].player.uid,5,1);
					vecRMailAid.erase(itr);
					break;
				}
			}
		}
	}
	else if (action == "next")
	{
		ret = match.NextTurn();
		if (ret != 0)
		{
			cout << "next turn fail,ret:" << ret << endl;
			return 0;
		}
		cout << "next turn ok" << endl;
	}
	else
	{
		usage();
	}

	return 0;
}
