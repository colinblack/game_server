/*
 * BarbarianReward.cpp
 *
 *  Created on: 2012-12-18
 *      Author: Administrator
 */
#include "LogicInc.h"
#include <iostream>
#include <stdlib.h>

#define TEAM_REWARD_PERSENT_1   1.0f
#define TEAM_REWARD_PERSENT_2   0.9f
#define TEAM_REWARD_PERSENT_3   0.8f
#define TEAM_REWARD_PERSENT_4   0.5f

void GetAllianceReward(int rank, unsigned &coins, unsigned &resource) {
	rank++;
	if (rank == 1) {
		coins = 100;
		resource = 100;
	} else if (rank >= 2 && rank <= 3) {
		coins = 80;
		resource = 80;
	} else if (rank >= 4 && rank <= 10) {
		coins = 50;
		resource = 50;
	} else {
		coins = 0;
		resource = 0;
	}
}

int main(int argc, char *argv[]) {
	if (!Kernel::Init(APP_CONFIG_PATH)) {
		cout << "init kernel fail" << endl;
		return 1;
	}
	Config::SetDomain(0);

	unsigned TwiceTimeB = 0;
	Config::GetUIntValue(TwiceTimeB, CONFIG_DOUBLE_BARBARIAN_BEGIN);
	unsigned TwiceTimeE = 0;
	Config::GetUIntValue(TwiceTimeE, CONFIG_DOUBLE_BARBARIAN_END);
	cout << "TwiceTimeB=" << TwiceTimeB << ",TwiceTimeE=" << TwiceTimeE << endl;
	int twiceFlag = 1;
	if (Time::GetGlobalTime() >= TwiceTimeB && Time::GetGlobalTime() <= TwiceTimeE) {
		twiceFlag = 2;
	}

	map<unsigned, pair<unsigned, map<unsigned, unsigned> > > scoremap;
	for (unsigned kingdom = 1; kingdom <= 3; ++kingdom) {
		int i = 0, j = 0;
		CLogicBarbarianInvasion logicBarbarianInvasion;
		DataPlayersPoints playersRank;
		memset(&playersRank, 0x00, sizeof(DataPlayersPoints));
		DataTeamItem teamRank[512];
		CLogicPay logicPay;
		CLogicAlliance logicAlliance;
		int teamNum = 0;
		int ret = logicBarbarianInvasion.GetTeamRankSorted(kingdom, teamRank, teamNum);
		if (ret != 0) {
			cout << " GetTeamRank failed" << endl;
			continue;
		}
		for (i = 0; i < teamNum; i++) {
			float teamRewardPersent = 0;
			if (!IsAllianceId(teamRank[i].aid)) {
				break;
			}

			scoremap[teamRank[i].aid].first = 0;

			memset(&playersRank, 0x00, sizeof(playersRank));
			if (i == 0)
				teamRewardPersent = TEAM_REWARD_PERSENT_1;
			else if (i == 1 || i == 2)
				teamRewardPersent = TEAM_REWARD_PERSENT_2;
			else if (i > 2 && i <= 10)
				teamRewardPersent = TEAM_REWARD_PERSENT_3;
			else
				teamRewardPersent = TEAM_REWARD_PERSENT_4;

			ret = logicBarbarianInvasion.GetTeamPlayersRankSorted(playersRank, teamRank[i].aid);
			if (ret != 0) {
				cout << " GetTeamPlayersRank failed" << endl;
				continue;
			}
			for (j = 0; j < playersRank.playerNum; j++) {
				scoremap[teamRank[i].aid].first += playersRank.players[j].points;
				scoremap[teamRank[i].aid].second[playersRank.players[j].uid] = (unsigned) ceil(pow((float) playersRank.players[j].points, 1.5f));

				float rewardCash = 0;
				unsigned personPoint = 0;
				if (playersRank.players[j].points >= 6000) {
					rewardCash = 50.0f;
					personPoint = 6000;
				} else if (playersRank.players[j].points >= 5100) {
					rewardCash = 40.0f;
					personPoint = 5000;
				} else if (playersRank.players[j].points >= 4800) {
					rewardCash = 30.0f;
					personPoint = 4000;
				} else if (playersRank.players[j].points >= 4200) {
					rewardCash = 25.0f;
					personPoint = 3000;
				} else if (playersRank.players[j].points >= 3600) {
					rewardCash = 20.0f;
					personPoint = 2000;
				} else if (playersRank.players[j].points >= 3100) {
					rewardCash = 15.0f;
					personPoint = 1000;
				} else if (playersRank.players[j].points >= 2500) {
					rewardCash = 10.0f;
					personPoint = 500;
				} else {
					continue;
				}

				int addCash = teamRewardPersent * rewardCash * twiceFlag;
				unsigned uTotalPoints = personPoint * twiceFlag;

				ret = logicPay.ChangePay(playersRank.players[j].uid, 0, addCash, "barbarianreward");
				if (ret != 0) {
					cout << "error  ChangeCash failed uid = " << playersRank.players[j].uid << endl;
				}
				ret = logicAlliance.AddPoint(playersRank.aid, playersRank.players[j].uid, uTotalPoints);
				if (ret != 0) {
					cout << "error add point failed uid=" << playersRank.players[j].uid << " aid=" << playersRank.aid << endl;
				}
				Json::Value updates;
				updates.resize(1);
				updates[0u]["s"] = "BARBARIANREWARD";
				updates[0u]["name"] = string(playersRank.players[j].name);
				updates[0u]["coins"] = addCash;
				updates[0u]["points"] = playersRank.players[j].points;
				updates[0u]["ts"] = Time::GetGlobalTime();
				CLogicUpdates logicUpdates;
				ret = logicUpdates.AddUpdates(playersRank.players[j].uid, updates, true);
				if (ret != 0) {
					cout << "add updates failed uid=" << playersRank.players[j].uid << endl;
				}
			}

			unsigned allianceCoins = 0;
			unsigned ar = 0;
			GetAllianceReward(i, allianceCoins, ar);
			if (0 != ar || 0 != allianceCoins) {
				ret = logicAlliance.ChangeResource(teamRank[i].aid, ar, ar, ar, ar, 0, allianceCoins, "barbarianreward");
				if (0 != ret) {
					cout << "ChangeResource fail,ret=" << ret << ",aid=" << teamRank[i].aid << endl;
				}
			}
		}
	}
	string buf;
	unsigned day = (Time::GetGlobalTime() - Config::GetIntValue(CONFIG_OPEN_TS)) / 86400;
	for (map<unsigned, pair<unsigned, map<unsigned, unsigned> > >::iterator it = scoremap.begin(); it != scoremap.end(); ++it) {
		ORDERS_LOG("uid=%u&code=barbarian_score&price=%u&amount=1&type=0", it->first, it->second.first);
		if (day < 30) {
			if (it->second.first < 10000)
				continue;
		} else if (day < 90) {
			if (it->second.first < 20000)
				continue;
		} else if (day < 150) {
			if (it->second.first < 30000)
				continue;
		} else if (day < 210) {
			if (it->second.first < 40000)
				continue;
		} else if (day < 300) {
			if (it->second.first < 50000)
				continue;
		} else if (day < 390) {
			if (it->second.first < 60000)
				continue;
		} else if (day < 480) {
			if (it->second.first < 70000)
				continue;
		} else if (day < 570) {
			if (it->second.first < 80000)
				continue;
		} else if (day < 660) {
			if (it->second.first < 90000)
				continue;
		} else {
			if (it->second.first < 95000)
				continue;
		}

		for (map<unsigned, unsigned>::iterator iter = it->second.second.begin(); iter != it->second.second.end(); ++iter) {
			if (IsValidUid(iter->first) && iter->second) {
				buf += CTrans::ITOS(iter->first) + " " + CTrans::ITOS(iter->second) + "\n";
			}
		}
	}
	if (File::Write("ascore", buf)) {
		cout << "Write ascore file fail!" << endl;
		return 1;
	}
	return 0;
}
