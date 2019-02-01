#include "LogicInc.h"

static unsigned GetUidFromArgs(int argc, char* argv[], int &index)
{
	int ret;
	unsigned uid;
	if(index >= argc)
	{
		return 0;
	}
	if(string(argv[index++]) == "-o")
	{
		if(index + 2 > argc)
		{
			return 0;
		}
		int pt;
		if(!Convert::StringToInt(pt, string(argv[index++])))
		{
			return 0;
		}
		string openid = argv[index++];
		ret = LogicUserBasic::GetUid(uid, (PlatformType)pt, openid);
		if(ret != 0)
		{
			return 0;
		}
	}
	else
	{
		if(!Convert::StringToUInt(uid, string(argv[index++])))
		{
			return 0;
		}
	}
	return uid;
}

void TestPerf()
{
	timeval start;
	gettimeofday(&start, NULL);
	int round = 10000000;
	for(int i = 0; i < round; i++)
	{
		//do something
	}
	timeval stop;
	gettimeofday(&stop, NULL);
	int elapse = (stop.tv_sec - start.tv_sec) * 1000 + stop.tv_usec / 1000 - start.tv_usec / 1000;
	printf("time: %ums; time_per_time:%.3fus\n", elapse, elapse * 1000.0 / round);
}

int DumpNpc(unsigned uid, unsigned id)
{
	int ret;
	Json::Value archive;
	CLogicArchive logicArchive;
	ret = logicArchive.GetArchive(PT_TEST, uid, MAIN_BASE_ID, archive);
	if(ret != 0)
	{
		printf("%u GetArchive error\n", uid);
		return ret;
	}

	Json::Value dump;
	dump["buildingdata"] = archive["buildingdata"];
	dump["effects"] = Json::Value(Json::arrayValue);
	dump["mushrooms"] = archive["mushrooms"];
	dump["monsters"] = archive["monsters"];
	if(archive.isMember("champion"))
	{
		dump["champion"] = archive["champion"];
	}
	else
	{
		dump["champion"] = Json::Value(Json::objectValue);
	}
	dump["academy"] = archive["academy"];
	dump["lockerdata"] = archive["lockerdata"];
	dump["resources"] = archive["resources"];
	archive["npcid"] = id;

	string path;
	String::Format(path, "./%u.dat", id);
	ret = File::Write(path, Json::FastWriter().write(dump));
	if(ret != 0)
	{
		printf("%u Write %u.dat error\n", uid, id);
		return ret;
	}
	return 0;
}

void DumpNpc(int argc, char* argv[])
{
	int index = 1;
	unsigned uid = GetUidFromArgs(argc, argv, index);
	if(!IsValidUid(uid))
	{
		printf("usage: %s <uid|-o platfrom openid> id\n", argv[0]);
		return ;
	}
	unsigned id;
	if(index >= argc || !Convert::StringToUInt(id, argv[index]))
	{
		printf("usage: %s <uid|-o platfrom openid> id\n", argv[0]);
		return ;
	}
	int ret = DumpNpc(uid, id);
	if(ret == 0)
	{
		printf("Dump %u as npc %d success\n", uid, id);
	}
}

//void RemoveUser(unsigned uid)
//{
//	int ret = LogicUser::RemoveUser(uid);
//	if(ret == 0)
//	{
//		printf("remove %u ok\n", uid);
//	}
//	else
//	{
//		printf("remove %u fail, %d\n", uid, ret);
//	}
//}
//
//void TestDawxCrypt()
//{
//	string text = "{\"attackPreference\":1,\"lastattack\":1311414515,\"nextAttack\":1311587315,\"s1\":[2,1311062435,1],\"sessionsSinceLastAttack\":29}";
//	string key = "app24326.qzoneapp.com5dj36s38234567";
//	string result;
//	printf("text[%d]:\t|%s|\n", (int)text.size(), text.c_str());
//	if(!Crypt::DawxEncode(result, text, key))
//	{
//		printf("encode error\n");
//		return;
//	}
//	printf("encode[%d]:\t|%s|\n", (int)result.size(), result.c_str());
//	string decode;
//	if(!Crypt::DawxDecode(decode, result, key))
//	{
//		printf("decode error\n");
//		return;
//	}
//	printf("decode[%d]:\t|%s|\n", (int)decode.size(), decode.c_str());
//}
//
//#define CLIENT_KEY "z1hcdgiV4e5BwUKa9IT3EM8CpqnPufob"
//#define SERVER_KEY "QDneu1n5z2f491o4kiClIT35EgQDneuX"
//
//int Decrypt()
//{
//	int sc;
//	printf("Server[0] / Client[1] : ");
//	scanf("%d", &sc);
//	char domain[100];
//	printf("Domain : ");
//	scanf("%s", domain);
//	char hn[20];
//	printf("hn : ");
//	scanf("%s", hn);
//	char skey[50];
//	printf("skey : ");
//	scanf("%s", skey);
//	char data[10000];
//	printf("data : ");
//	scanf("%s", data);
//	string key = string(hn) + skey + domain + ((sc == 0) ? SERVER_KEY : CLIENT_KEY);
//	string decode;
//	if(!Crypt::DawxDecode(decode, data, key))
//	{
//		printf("Decode fail.\n");
//		return 0;
//	}
//	printf("Decode Data [%d] :\n|%s|\n", (int)decode.size(), decode.c_str());
//	return 0;
//}

void RemoveSessionExpired()
{
	unsigned start;
	mtime(start);
	uint64_t nextId;
	int ret;
	CDataIdCtrl dbIdCtrl;
	ret = dbIdCtrl.GetId(KEY_UID_CTRL, nextId);
	if(ret != 0)
	{
		printf("get max uid fail, ret=%d\n", ret);
		return ;
	}
	for(unsigned uid = 10000001; uid <= nextId; uid++)
	{
		ret = Session::RemoveSessionExpired(uid, Time::GetGlobalTime() - SESSION_TIME_OUT);
		if(ret != 0)
		{
			printf("remove session %u fail [%d]\n", uid, ret);
		}
	}
	unsigned stop;
	mtime(stop);
	printf("remove session ok, from 10000001 to %u, time=%u\n", (unsigned)nextId, stop - start);
}

int CleanUserMessageStatus(unsigned uid, uint64_t msgid)
{
	CDataUserMessage userMsgDB;
	int ret = userMsgDB.SetUserMessageStatus(uid, msgid, UMS_UN_READ);
	if (ret != 0)
	{
		printf("set fail,ret=%d", ret);
	}
	return 0;
}

void GenFilterData(int argc, char *argv[])
{
	if(argc <= 2)
	{
		printf("usage: CMD WordsPath DataPath\n");
		return;
	}

	int ret;
	string content;
	ret = File::Read(argv[1], content);
	if(ret != 0)
	{
		printf("read %s fail %d\n", argv[1], ret);
		return;
	}
	if(content.size() >= 3 && content[0] == (char)0xEF &&
		content[1] == (char)0xBB && content[2] == (char)0xBF)	//skip bom
	{
		content = content.c_str() + 3;
	}
	vector<string> words;
	CBasic::StringSplitTrim(content, "\r\n", words);

	if(!StringFilter::GenerateData(words, argv[2]))
	{
		printf("Generate Data [%s] from [%s] fail\n", argv[2], argv[1]);
	}
	else
	{
		printf("Generate Data [%s] from [%s] success\n", argv[2], argv[1]);
	}
}

void TestStringFilter()
{
	char buffer[1000];
	printf("input string:\n");
	while(scanf("%s", buffer) != 0)
	{
		string s = buffer;
		timeval start;
		gettimeofday(&start, NULL);
		if(StringFilter::Replace(s))
		{
			timeval stop;
			gettimeofday(&stop, NULL);
			int elapse = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
			printf("result: [%s]\ntime: %dus\n", s.c_str(), elapse);
		}
		else
		{
			printf("filter fail\n");
		}
		printf("input string:\n");
	}
}

void TestSocket(int argc, char *argv[])
{
	if(argc <= 2)
	{
		printf("<useage>\nServer: CMD -s [-p port] [-h host]\nClient: CMD -c [-p port] [-h host]\n");
		return ;
	}
	bool server = false;
	unsigned port = 0;
	string host;
	if(string("-s") == argv[1])
	{
		server = true;
	}
	else if(string("-c") == argv[1])
	{
		server = false;
	}
	else
	{
		printf("<useage>\nServer: CMD -s [-p port] [-h host]\nClient: CMD -c [-p port] [-h host]\n");
		return ;
	}
	if(argc >= 4)
	{
		if(string("-p") == argv[2])
		{
			Convert::StringToUInt(port, argv[3]);
		}
	}
	if(argc >=6)
	{
		if(string("-h") == argv[4])
		{
			host = argv[5];
		}
	}

	printf("Mode=%s, Port=%u, Host=%s\n", server ? "Server" : "Client", port, host.empty() ? "<NULL>" : host.c_str());

	if(server)
	{
		CSocket socket;
		if(!socket.Create(port, SOCK_STREAM, host.empty() ? NULL : host.c_str()))
		{
			printf("Socket create socket fail [%d]\n", socket.GetLastError());
			return;
		}

		if(!socket.Listen())
		{
			printf("Socket listen fail [%d]\n", socket.GetLastError());
			return;
		}
		printf("Listening...\n");

		CSocket connSocket;
		sockaddr_in sockAddr;
		int addrLen = sizeof(sockaddr);
		if(!socket.Accept(&connSocket, (sockaddr *)&sockAddr, &addrLen))
		{
			printf("Socket accept fail [%d]\n", socket.GetLastError());
		}
		printf("Accept\n");

		char buffer[255] = {0};
		int recvLen;
		do
		{
			recvLen = sizeof(buffer) - 1;
			recvLen = connSocket.Receive(buffer, recvLen);
			if(recvLen <= 0)
			{
				printf("Socket receive fail [%d]\n", socket.GetLastError());
				return;
			}
			buffer[recvLen] = '\0';
			printf("Receive:\n%s\n", buffer);
		} while(strcmp(buffer, "exit") != 0);
		connSocket.Close();
		printf("Connection close\n");
		socket.Close();
		printf("Socket close\n");
	}
	else
	{
		CSocket socket;
		if(!socket.Create())
		{
			printf("Socket create socket fail [%d]\n", socket.GetLastError());
			return;
		}

		if(!socket.Connect(port, host.empty() ? NULL : host.c_str()))
		{
			printf("Socket connect fail [%d]\n", socket.GetLastError());
			return;
		}
		printf("Connected\n");
		char buffer[255] = {0};
		do
		{
			printf("Input string to send:\n");
			scanf("%s", buffer);
			socket.Send(buffer, strlen(buffer));
		} while(strcmp(buffer, "exit") != 0);

		socket.Close();
		printf("Socket close\n");
	}
}

static bool AlliancePointCompare(const DataAlliance &left, const DataAlliance &right)
{
	return left.point > right.point;
}

struct WorldAlliance
{
	unsigned count;
	Json::Value alliance[10];
};

int UpdateAllianceStat()
{
	int ret;
	CLogicIdCtrl logicIdCtrl;
	uint64_t u64Id;
	ret = logicIdCtrl.GetCurrentId(KEY_ALLIANCE_ID_CTRL, u64Id);
	if(ret != 0)
	{
		printf("get alliance id fail %d\n", ret);
		return ret;
	}

	int maxWorld = 0;
	if(IsMercenary())
	{
		LogicWorld::GetMaxWorld(maxWorld);
	}
	CLogicAlliance logicAlliance;
	vector<DataAlliance> alliances;
	set<unsigned> activeAlliances;
 	for(unsigned allianceId = ALLIANCE_ID_START + 1; allianceId <= (unsigned)u64Id; allianceId++)
	{
		DataAlliance alliance;
		ret = logicAlliance.GetAllianceLimit(allianceId, alliance);
		if(ret == 0)
		{
			if(alliance.status == AS_ACTIVE)
			{
				alliances.push_back(alliance);
				activeAlliances.insert(alliance.alliance_id);
			}
			if(alliance.world > maxWorld)
			{
				maxWorld = alliance.world;
			}
		}
		else if(ret != R_ERR_NO_DATA)
		{
			printf("get alliance %u fail %d\n", allianceId, ret);
		}
	}

 	sort(alliances.begin(), alliances.end(), AlliancePointCompare);

 	maxWorld++;
 	vector<WorldAlliance> worldAlliances;
 	worldAlliances.resize(maxWorld + 1);
 	for(int i = 0; i <= maxWorld; i++)
 	{
 		worldAlliances[i].count = 0;
 	}
 	Json::Value allianceRank = Json::Value(Json::arrayValue);
 	int rank = 0;
 	for(vector<DataAlliance>::iterator itr = alliances.begin(); itr != alliances.end(); itr++)
 	{
 		rank++;
 		itr->rank = rank;

 		if(!IsMercenary())
 		{
			vector<DataUserInteract> interacts;
			CDataUserInteract dbInteract;
			ret = dbInteract.GetInteractsAttackAfter(itr->alliance_id, Time::GetGlobalTime() - ALLIANCE_ENEMY_TIME, interacts);
			if(ret == 0)
			{
				int maxAttack = 0;
				int maxDefence = 0;
				for(vector<DataUserInteract>::iterator itrInteract = interacts.begin(); itrInteract != interacts.end(); itrInteract++)
				{
					if(IsAllianceId(itrInteract->opposite_uid) &&
							activeAlliances.find(itrInteract->opposite_uid) != activeAlliances.end() &&
							(itrInteract->attack_from > maxDefence ||
							(itrInteract->attack_from == maxDefence && itrInteract->attack_to > maxAttack)))
					{
						maxAttack = itrInteract->attack_to;
						maxDefence = itrInteract->attack_from;
						itr->enemy_alliance_id = itrInteract->opposite_uid;
					}
				}
			}
			else
			{
				printf("get alliance %u interacts fail %d\n", itr->alliance_id, ret);
			}
 		}

 		DataAlliance alliance;
		ret = logicAlliance.GetAlliance(itr->alliance_id, alliance);
		if(ret == 0)
		{
			if(alliance.rank != itr->rank ||
					(!IsMercenary() && IsAllianceId(itr->enemy_alliance_id) && alliance.enemy_alliance_id != itr->enemy_alliance_id))
			{
				alliance.rank = itr->rank;
				if(!IsMercenary() && IsAllianceId(itr->enemy_alliance_id))
				{
					DataAlliance enemyAlliance;
					ret = logicAlliance.GetAllianceLimit(itr->enemy_alliance_id, enemyAlliance);
					if(ret == 0)
					{
						alliance.enemy_alliance_id = itr->enemy_alliance_id;
						alliance.enemy_alliance_name = enemyAlliance.name;
					}
				}
				ret = logicAlliance.SetAllianceLimit(alliance);
				if(ret != 0)
				{
					printf("set alliance %u fail %d\n", itr->alliance_id, ret);
				}
			}
			if(alliance.rank <= 10 ||
				(IsMercenary() && worldAlliances[alliance.world].count < 100))
			{
				Json::Value allianceData;
				allianceData["aid"] = alliance.alliance_id;
				allianceData["world"] = alliance.world;
				allianceData["name"] = alliance.name;
				allianceData["flag"] = alliance.flag;
				allianceData["leader"] = alliance.leader_uid;
				allianceData["level"] = alliance.level;
				allianceData["point"] = Convert::UInt64ToString(alliance.point);
				allianceData["rank"] = alliance.rank;
				allianceData["mc"] = alliance.member_count;
				allianceData["enemyid"] = alliance.enemy_alliance_id;
				allianceData["enemyname"] = alliance.enemy_alliance_name;
				allianceData["createtime"] = alliance.create_time;
				allianceData["desc"] = alliance.description;
				allianceData["notice"] = alliance.notice;
				DataUserBasic userBasic;
				ret = LogicUserBasic::GetUserSmart(alliance.leader_uid, OpenPlatform::GetType(), userBasic);
				if(ret == 0)
				{
					allianceData["leadername"] = userBasic.name;
				}
				DataUser user;
				ret = LogicUser::GetUser(alliance.leader_uid, user);
				if(ret == 0)
				{
					allianceData["leaderlevel"] = user.level;
				}
				if(alliance.rank <= 10)
				{
					allianceRank[allianceRank.size()] = allianceData;
				}
				if(IsMercenary())
				{
					unsigned count = 0;
					if(worldAlliances[0].count < 100)
					{
						count = worldAlliances[0].count;
						worldAlliances[0].alliance[count/10]["alliances"][count%10] = allianceData;
						worldAlliances[0].count++;
					}
					if(alliance.world != 0)
					{
						count = worldAlliances[alliance.world].count;
						worldAlliances[alliance.world].alliance[count/10]["alliances"][count%10] = allianceData;
						worldAlliances[alliance.world].count++;
					}
				}
			}
		}
		else
		{
			printf("get alliance %u fail %d\n", itr->alliance_id, ret);
		}
 	}

 	string allianceRankPath = Config::GetValue("alliance_rank");
 	if(allianceRankPath.empty())
 	{
 		allianceRankPath = "/data/release/toywar/webroot/data/alliance_rank";
 	}
 	ret = File::Write(allianceRankPath, Json::ToString(allianceRank));
 	if(ret != 0)
 	{
		printf("write alliance rank %s fail %d\n", allianceRankPath.c_str(), ret);
 	}

 	if(IsMercenary())
	{
		for(int i = 0; i <= maxWorld; i++)
		{
			WorldAlliance &worldAlliance = worldAlliances[i];
			worldAlliance.alliance[0]["count"] = worldAlliance.count;
			int page = 1;
			if(worldAlliance.count > 0)
			{
				page = (worldAlliance.count - 1) / 10 + 1;
			}
			for(int p = 0; p < page; p++)
			{
				string path;
				String::Format(path, "%s_%d_%d", allianceRankPath.c_str(), i, p + 1);
			 	ret = File::Write(path, Json::ToString(worldAlliance.alliance[p]));
			 	if(ret != 0)
			 	{
					printf("write alliance rank %s fail %d\n", path.c_str(), ret);
			 	}
			}
		}
 	}
 	printf("update alliances stat ok\n");
	return 0;
}

//int ChangeCash(int argc, char *argv[])
//{
//	int ret;
//	if(argc <= 2)
//	{
//		printf("usage: %s <uid|-o openid platfrom> CashDelta\n", argv[0]);
//		return -1;
//	}
//	unsigned uid;
//	string sDelta;
//	if(string(argv[1]) == "-o")
//	{
//		if(argc <= 4)
//		{
//			printf("usage: %s <uid|-o openid platfrom> CashDelta\n", argv[0]);
//			return -1;
//		}
//		string openid = argv[2];
//		int pt;
//		if(!Convert::StringToInt(pt, string(argv[3])))
//		{
//			printf("usage: %s <uid|-o openid platfrom> CashDelta\n", argv[0]);
//			return -1;
//		}
//		ret = LogicUserBasic::GetUid(uid, (PlatformType)pt, openid);
//		if(ret != 0)
//		{
//			printf("get uid fail. openid=%s\n", argv[2]);
//			return ret;
//		}
//		sDelta = argv[4];
//	}
//	else
//	{
//		if(!Convert::StringToUInt(uid, string(argv[1])))
//		{
//			printf("usage: %s <uid|-o openid platfrom> CashDelta\n", argv[0]);
//			return -1;
//		}
//		sDelta = argv[2];
//	}
//	int delta;
//	if(!Convert::StringToInt(delta, sDelta))
//	{
//		printf("usage: %s <uid|-o openid platfrom> CashDelta\n", argv[0]);
//		return -1;
//	}
//	CLogicPay logicPay;
//	ret = logicPay.ChangeCash(uid, "ADMIN", delta, 1);
//	if(ret != 0)
//	{
//		printf("change cash fail. uid=%u, delta=%u\n", uid, delta);
//		return ret;
//	}
//	printf("change cash success. uid=%u, delta=%u\n", uid, delta);
//	return 0;
//}
//
//int BlockUser(int argc, char *argv[])
//{
//	int ret;
//	if(argc <= 2)
//	{
//		printf("usage: %s uid <block|active>\n", argv[0]);
//		return -1;
//	}
//	unsigned uid;
//	if(!Convert::StringToUInt(uid, string(argv[1])))
//	{
//		printf("usage: %s uid <block|active>\n", argv[0]);
//		return -1;
//	}
//	int status = US_ACTIVE;
//	if(string(argv[2]) == "block")
//	{
//		status = US_BAN;
//	}
//	DataUser user;
//	ret = LogicUser::GetUser(uid, user);
//	if(ret != 0)
//	{
//		return ret;
//	}
//	if(user.status == status)
//	{
//		printf("%u status is %s now\n", uid, status == US_ACTIVE ? "active" : "block");
//		return 0;
//	}
//	user.status = status;
//	logicUser.SetUserLimit(user);
//	if(ret != 0)
//	{
//		printf("set %u status fail, ret=%d\n", uid, ret);
//		return -1;
//	}
//	printf("%u status change %s success\n", uid, status == US_ACTIVE ? "active" : "block");
//	return 0;
//}
//
//static void OnExit()
//{
//	exit(0);
//}
//
//bool CrossDomainD()
//{
//	static char s_crossDomain[] = "<?xml version=\"1.0\"?><cross-domain-policy><allow-access-from domain=\"*\" to-ports=\"*\" /></cross-domain-policy>";
//	if(!System::InitDaemon(NULL, OnExit))
//	{
//		fatal_log("[System::InitDaemon fail][error=%d]", errno);
//		return false;
//	}
//	CSocket listenSocket;
//	if(!listenSocket.Socket())
//	{
//		error_log("[Socket fail][error=%d]", errno);
//		return false;
//	}
//	if(!listenSocket.Bind(843))
//	{
//		error_log("[Bind fail][error=%d]", errno);
//		return false;
//	}
//	if(!listenSocket.Listen(10))
//	{
//		error_log("[Listen fail][error=%d]", errno);
//		return false;
//	}
//	while(true)
//	{
//		sockaddr_in sockAddr;
//		int sockAddrLength = sizeof(sockaddr_in);
//		CSocket connSocket;
//		if(!listenSocket.Accept(&connSocket, (sockaddr *)&sockAddr, &sockAddrLength))
//		{
//			error_log("[Accept fail][error=%d]", errno);
//			return false;
//		}
//		char buffer[255] = {0};
//		int recvLen;
//		recvLen = sizeof(buffer) - 1;
//		recvLen = connSocket.Receive(buffer, recvLen);
//		if(recvLen <= 0)
//		{
//			error_log("Socket receive fail [%d]", connSocket.GetLastError());
//			connSocket.Close();
//			continue;
//		}
//		if(string(buffer) == "<policy-file-request/>")
//		{
//			if(connSocket.Send(s_crossDomain, sizeof(s_crossDomain)) > 0)
//			{
//				info_log("[send crossdomain success]");
//			}
//			else
//			{
//				info_log("[send crossdomain fail][error=%d]", errno);
//			}
//		}
//		else
//		{
//			error_log("[recv_unknow_cmd][cmd=%s]", buffer);
//		}
//		connSocket.Close();
//	}
//}

int UpgradeDatabase(int argc, char *argv[])
{
	//user_extra
	//`lock`, `technology`, `quest`
	//temp_base -> base_extra
	// `grower`, `military`, `hero`, `recycle`, `consume` `extra_data`

	/*int ret;
	unsigned start;
	mtime(start);
	unsigned startId = 10000001;
	if(argc > 1)
	{
		if(!Convert::StringToUInt(startId, argv[1]))
		{
			printf("start id error\n");
			return -1;
		}
	}
	uint64_t nextId;
	if(argc <= 2)
	{
		CDataIdCtrl dbIdCtrl;
		ret = dbIdCtrl.GetId(KEY_BASEID_CTRL, nextId);
		if(ret != 0)
		{
			printf("get max baseid fail, ret=%d\n", ret);
			return -1;
		}
	}
	else
	{
		if(!Convert::StringToUInt64(nextId, argv[2]))
		{
			printf("end id error\n");
			return -1;
		}
	}
	printf("upgrade baseid from %u - %u\n", startId, (unsigned)nextId);
	for(unsigned baseid = startId; baseid <= nextId; baseid++)
	{
		if(baseid % 10000 == 0)
		{
			unsigned ts;
			mtime(ts);
			printf("%u: %u / %u - %u\n", ts, baseid, startId, (unsigned)nextId);
		}
		DataBase base;
		ret = LogicBase::GetBase(0, baseid, base);
		if(ret != 0)
		{
			if(ret != R_ERR_NO_DATA)
			{
				printf("get base error, baseid=%u, ret=%d\n", baseid, ret);
			}
			continue;
		}
		DataBaseExtra baseExtra;
		ret = LogicBase::GetBaseExtra(baseid, baseExtra);
		if(ret != 0)
		{
			printf("get base_extra error, baseid=%u, ret=%d\n", baseid, ret);
			continue;
		}
		Json::Value archive;
		if(!Json::FromString(archive, baseExtra.building))
		{
			printf("parse archive error, baseid=%u, data=%s\n", baseid, baseExtra.building.c_str());
			continue;
		}
		if(!archive.isObject())
		{
			printf("archive data error, baseid=%u, data=%s\n", baseid, baseExtra.building.c_str());
			archive = Json::Value(Json::objectValue);
		}
		if(archive.isMember("buildingdata"))
		{
			baseExtra.building = Json::ToString(archive["buildingdata"]);
		}
		else
		{
			printf("buildingdata error, baseid=%u\n", baseid);
			baseExtra.building = "{}";
		}
		if(archive.isMember("mushrooms"))
		{
			baseExtra.grower = Json::ToString(archive["mushrooms"]);
		}
		if(archive.isMember("monsters"))
		{
			baseExtra.military = Json::ToString(archive["monsters"]);
		}
		if(archive.isMember("champion"))
		{
			baseExtra.hero = Json::ToString(archive["champion"]);
		}
		if(archive.isMember("researchdata"))
		{
			baseExtra.recycle = Json::ToString(archive["researchdata"]);
		}
		if(archive.isMember("storedata"))
		{
			baseExtra.consume = Json::ToString(archive["storedata"]);
		}
		if(base.base_index != MAIN_BASE_ID)
		{
			if(archive.isMember("resources"))
			{
				Json::Value baseExtraData;
				baseExtraData["resources"] = archive["resources"];
				baseExtra.extra_data = Json::ToString(baseExtraData);
			}
		}
		ret = LogicBase::SetBaseExtra(baseExtra);
		if(ret != 0)
		{
			printf("set base_extra error, baseid=%u, ret=%d\n", baseid, ret);
			//continue;
		}
		if(base.base_index == MAIN_BASE_ID)
		{
			if(!IsValidUid(base.uid))
			{
				printf("invalid uid, baseid=%u, uid=%u\n", baseid, base.uid);
				continue;
			}
			DataUserExtra userExtra;
			ret = LogicUser::GetUserExtra(base.uid, userExtra);
			if(ret != 0)
			{
				printf("get user_extra error, baseid=%u, uid=%u, ret=%d\n", baseid, base.uid, ret);
				continue;
			}
			if(archive.isMember("lockerdata"))
			{
				userExtra.lock = Json::ToString(archive["lockerdata"]);
			}
			if(archive.isMember("academy"))
			{
				userExtra.technology = Json::ToString(archive["academy"]);
			}
			if(archive.isMember("quests"))
			{
				userExtra.quest = Json::ToString(archive["quests"]);
			}
			ret = LogicUser::SetUserExtra(userExtra);
			if(ret != 0)
			{
				printf("set user_extra error, baseid=%u, uid=%u, ret=%d\n", baseid, base.uid, ret);
				//continue;
			}
		}
	}
	unsigned stop;
	mtime(stop);
	printf("upgrade database ok, from %u to %u, time=%u\n", startId, (unsigned)nextId, stop - start);*/
	return 0;
}

void CreateWorld(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("<useage>%s WorldId\n", argv[0]);
		return ;
	}
	unsigned id;
	if(!Convert::StringToUInt(id, argv[1]))
	{
		printf("<useage>%s WorldId\n", argv[0]);
		return ;
	}
	System::InitDaemon();
	int ret = LogicWorld::CreateWorld(id);
	if(ret != 0)
	{
		printf("CreateWorld fail. WorldId=%u, ret=%d.\n", id, ret);
	}
}

void CreateNpc(int argc, char *argv[])
{
	int ret;
	if(argc < 4)
	{
		printf("<useage>%s WorldId X Y\n", argv[0]);
		return ;
	}
	CWorldPoint point;
	if(!Convert::StringToUInt(point.World, argv[1]) ||
		!Convert::StringToInt(point.X, argv[2]) ||
		!Convert::StringToInt(point.Y, argv[3]))
	{
		printf("<useage>%s WorldId X Y\n", argv[0]);
		return ;
	}
	unsigned position = point.ToUInt();
	CDataWorld dbWorld;
	unsigned baseid;
	ret = dbWorld.Get(position, baseid);
	if(ret == R_ERR_NO_DATA)
	{
		ret = dbWorld.Remove(position);
		if(ret != 0)
		{
			printf("Remove fail. ret=%d,position=%u,baseid=%u", ret, position, baseid);
			return;
		}
	}
	else if(ret != 0)
	{
		printf("GetWorld fail. ret=%d,position=%u", ret, position);
		return;
	}
	ret = LogicWorld::CreateNpc(position);
	if(ret != 0)
	{
		printf("AddNpc fail. ret=%d,position=%u", ret, position);
		return;
	}
	printf("create npc success. position=%u,world=%u,x=%d,y=%d", position, point.World, point.X, point.Y);
	return;
}

void TestPrintStack()
{
	printf("%s\n", Debug::GetStack().c_str());
}

void CreateWorldTerrain()
{
	const int WORLD_SIZE = 800;
	const int MAX_HEIGHT = 120;
	const int HEIGHT_BASE = 70;
	const int SMOOTH_ROUND = 5;
	int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
	int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
	int world[WORLD_SIZE][WORLD_SIZE];
	int x;
	int y;
	for(x = 0; x < WORLD_SIZE; x++)
	{
		for(y = 0; y < WORLD_SIZE; y++)
		{
			//world[x][y] = Math::GetRandomInt(MAX_HEIGHT * 3);
			if(Math::GetRandomInt(2) == 0)
			{
				world[x][y] = 0;
			}
			else
			{
				world[x][y] = MAX_HEIGHT * 2 - 1;
			}
		}
	}
	for(int n = 0; n < SMOOTH_ROUND; n++)
	{
		for(x = 0; x < WORLD_SIZE; x++)
		{
			for(y = 0; y < WORLD_SIZE; y++)
			{
				int sum = world[x][y] * 8;
				for(int d = 0; d < 8; d++)
				{
					int nx = x + dx[d];
					int ny = y + dy[d];
					if(nx < 0)
					{
						nx = WORLD_SIZE - 1;
					}
					else if(nx >= WORLD_SIZE)
					{
						nx = 0;
					}
					if(ny < 0)
					{
						ny = WORLD_SIZE - 1;
					}
					else if(nx >= WORLD_SIZE)
					{
						ny = 0;
					}
					if(nx == x || ny == y)
					{
						sum += world[nx][ny] * 3;
					}
					else
					{
						sum += world[nx][ny] * 2;
					}
				}
				sum += Math::GetRandomInt(400) - 200 + 15 - 5;
				sum /= 28;
				if(sum < 0)
				{
					sum = 0;
				}
				else if(sum >= MAX_HEIGHT * 2)
				{
					sum = MAX_HEIGHT * 2 - 1;
				}
				world[x][y] = sum;
			}
		}
	}
	int summary[MAX_HEIGHT] = {0};
	string result;
	for(x = 0; x < WORLD_SIZE; x++)
	{
		for(y = 0; y < WORLD_SIZE; y++)
		{
			int height = world[x][y] - MAX_HEIGHT/2 + 1;
			if(height < 0)
			{
				height = Math::GetRandomInt(MAX_HEIGHT/10);
			}
			else if(height >= MAX_HEIGHT)
			{
				height = MAX_HEIGHT - 1 - Math::GetRandomInt(MAX_HEIGHT/10);
			}
			summary[height]++;
			height += HEIGHT_BASE;
			world[x][y] = height;
			result.append(1, (char)height);
		}
	}
	for(x = 0; x < 30; x++)
	{
		for(y = 0; y < 30; y++)
		{
			printf("%3d ", world[x][y]);
		}
		printf("\n");
	}
	printf("summary:\n");
	for(int n = 0; n < MAX_HEIGHT; n++)
	{
		printf("%d: %d\n", n + HEIGHT_BASE, summary[n]);
	}
	int ret = File::Write("./worldterrain.dat", result);
	if(ret != 0)
	{
		printf("[%d]write file fail", ret);
		return;
	}
}

void ConvertPoint(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("useage:\n%s -e World X Y\n%s -d Position\n", argv[0], argv[0]);
		return ;
	}
	if(string(argv[1]) == "-e")
	{
		if(argc < 5)
		{
			printf("useage:\n%s -e World X Y\n%s -d Position\n", argv[0], argv[0]);
			return ;
		}
		CWorldPoint point;
		if(!Convert::StringToUInt(point.World, argv[2]) ||
			!Convert::StringToInt(point.X, argv[3]) ||
			!Convert::StringToInt(point.Y, argv[4]))
		{
			printf("useage:\n%s -e World X Y\n%s -d Position\n", argv[0], argv[0]);
			return ;
		}
		printf("Position: %u\n", point.ToUInt());
	}
	else
	{
		unsigned position;
		if(!Convert::StringToUInt(position, argv[2]))
		{
			printf("useage:\n%s -e World X Y\n%s -d Position\n", argv[0], argv[0]);
			return ;
		}
		CWorldPoint point(position);
		printf("World: %u\nX: %d\nY: %d\n", point.World, point.X, point.Y);
	}
}

void SendEmail(int argc, char *argv[])
{
	if(argc < 4)
	{
		printf("useage: %s Email Subject Body\n", argv[0]);
		return ;
	}
	Email::MailMessage mail;
	if(!Config::GetValue(mail.Server, "smtp_server") ||
		!Config::GetValue(mail.From, "mail_sender"))
	{
		printf("config error\n");
		return ;
	}
	mail.To = argv[1];
	mail.Subject = argv[2];
	mail.Body = argv[3];

	if(Email::SendMail(mail))
	{
		printf("send mail success\n");
	}
	else
	{
		printf("send mail fail\n");
	}
}

int AddNpcAccount(int argc, char *argv[])
{
	DataUser user;
	user.uid = 10000000;
	user.register_platform = 2;
	user.register_time = Time::GetGlobalTime();
	user.invite_uid = 0;
	user.last_login_platform = 2;
	user.last_login_time = Time::GetGlobalTime();
	user.last_active_time = Time::GetGlobalTime();
	user.login_times = 0;
	user.invite_count = 0;
	user.status = US_ACTIVE;
	user.main_base_id = 0;
	user.level = 0;
	user.point = 0;
	user.value = 0;
	user.tutorial_stage = 205;
	user.r1 = 0;
	user.r1_max = 0;
	user.r2 = 0;
	user.r2_max = 0;
	user.r3 = 0;
	user.r3_max = 0;
	user.r4 = 0;
	user.r4_max = 0;
	user.alliance_id = ALLIANCE_ID_NULL;
	user.unread_message = 0;
	user.world = 0;
	CDataUser dbUser;
	int ret = dbUser.AddUser(user);
	if(ret != 0)
	{
		cout << "add user fail" << endl;
		return 1;
	}
	unsigned uid = user.uid;

	DataUserExtra userExtra;
	userExtra.uid = uid;
	userExtra.gate_left_times = 0;
	userExtra.gate_extra_times = 0;
	userExtra.stat = "{}";
	userExtra.wf_status = "";
	userExtra.lock = "{}";
	userExtra.technology = "{}";
	userExtra.quest = "{}";
	userExtra.bookmark = "{}";
	userExtra.extra_data = "{}";
	CDataUserExtra dbUserExtra;
	ret = dbUserExtra.AddUser(userExtra);
	if(ret != 0)
	{
		cout << "add user extra fail" << endl;
		return 1;
	}

	CLogicPay logicPay;
	ret = logicPay.AddUser(uid, NEW_USER_CASH);
	if(ret != 0)
	{
		return ret;
	}

	unsigned baseid;
	ret = LogicBase::AddMainBase(uid, baseid);
	if(ret != 0)
	{
		cout << "add main base fail" << endl;
		return 1;
	}

	ret = dbUser.SetMainBaseId(uid, baseid);
	if( ret != 0 )
	{
		cout << "set main base fail" << endl;
		return 1;
	}
	cout << "ok" << endl;
	return 0;
}

int AddUserBasic(int argc, char *argv[])
{
	DataUserBasic data;
	data.uid = 10000000;
	data.platform = 2;
	data.is_register_platform = 1;
	data.open_id = "10000000";
	data.name = "npc";
	data.gender = 0;
	data.vip_type = 0;
	data.vip_level = 0;

	CDataUserBasic db;
	int ret = db.AddUser(data);
	if (ret != 0)
	{
		cout << "add fail" << endl;
		return 1;
	}
	cout << "ok" << endl;
	return 0;
}

int GetUserBasic(int argc, char *argv[])
{
	if (argc < 3)
	{
		cout << "usage: " << argv[0] << " uid platform" << endl;
		return 1;
	}
	unsigned uid = atoll(argv[1]);
	int platform = atoi(argv[2]);
	DataUserBasic data;
	CDataUserBasic db;
	int ret = db.GetUser(uid, platform, data);
	if (ret != 0)
	{
		cout << "get fail" << endl;
		return 1;
	}
	cout << data.uid << endl
			<< data.name << endl
			<< data.figure_url << endl
			<< data.open_id << endl
			<< data.nation << endl
			<< data.province << endl;
	return 0;
}

int BlockUser(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "usage: " << argv[0] << " uid [active|block]" << endl;
		return 1;
	}
	unsigned uid = atoll(argv[1]);
	DataUser user;
	int ret = LogicUser::GetUser(uid, user);
	if (ret != 0)
	{
		cout << "block fail" << endl;
		return 1;
	}
	if (argc >= 3 && string(argv[2]) == "active")
		user.status = US_ACTIVE;
	else
		user.status = US_BAN;
	ret = LogicUser::SetUser(user);
	if (ret != 0)
	{
		cout << "block fail" << endl;
		return 1;
	}
	cout << "ok" << endl;
	return 0;
}

int main(int argc, char *argv[])
{
	Kernel::Init();

	GenFilterData(argc, argv);
	//TestSocket(argc, argv);
	//UpdateAllianceStat();
	//TestPerf();
	//TestDawxCrypt();
	//Decrypt();
	//CreateWorld(argc, argv);
	//CreateNpc(argc, argv);
	//DumpNpc(argc, argv);
	//TestPrintStack();
	//CreateWorldTerrain();
	//ConvertPoint(argc, argv);
	//SendEmail(argc, argv);
	//AddUserBasic(argc, argv);
	//GetUserBasic(argc, argv);
	//BlockUser(argc, argv);

	return 0;
}
