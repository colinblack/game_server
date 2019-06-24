#include "table.h"

extern ZJH zjh;
extern Log log;

Table::Table() : start_timer_stamp(3),
				 preready_timer_stamp(5),
				 dispatch_show_timer_stamp(1),
				 out_show_timer_stamp(1),
				 dispatch_delay_timer_stamp(0.5),
				 out_delay_timer_stamp(0.5),
				 dissolve_room_tstamp(180),
				 check_room_timer_stamp(1.5),
				 check_user_can_out_card_timer_stamp(0.5)     //检查玩家是否有可出的牌
{
	//timer 1
	start_timer.data = this;
	ev_timer_init(&start_timer, Table::start_timer_cb, start_timer_stamp, start_timer_stamp);

	//timer 2
	preready_timer.data = this;
	ev_timer_init(&preready_timer, Table::preready_timer_cb, preready_timer_stamp, preready_timer_stamp);

	//timer 3
	dispatch_show_timer.data = this;
    ev_timer_init(&dispatch_show_timer, Table::dispatch_show_timer_cb, dispatch_show_timer_stamp, dispatch_show_timer_stamp);

	//timer 4
	out_show_timer.data = this;
	ev_timer_init(&out_show_timer, Table::out_show_timer_cb, out_show_timer_stamp, out_show_timer_stamp);

	//timer 5
	dispatch_delay_timer.data = this;
	ev_timer_init(&dispatch_delay_timer, Table::dispatch_delay_timer_cb, dispatch_delay_timer_stamp, dispatch_delay_timer_stamp);

	//timer 6
	out_delay_timer.data = this;
	ev_timer_init(&out_delay_timer, Table::out_delay_timer_cb, out_delay_timer_stamp, out_delay_timer_stamp);

	//timer 7
	dissolve_room_timer.data = this;
	ev_timer_init(&dissolve_room_timer, Table::dissolve_room_timer_cb, dissolve_room_tstamp, dissolve_room_tstamp);

	//timer 8
	send_videodata_timer.data = this;
	send_videodata_timer_stamp = 0.4;
	ev_timer_init(&send_videodata_timer, Table::Send_Video_Data_Timer_cb, send_videodata_timer_stamp, send_videodata_timer_stamp);
	//timer9
	send_dissroom_timer.data = this;
	send_dissroom_timer_stamp = 0.3;
	ev_timer_init(&send_dissroom_timer, Table::send_dissroom_timer_cb, send_dissroom_timer_stamp, send_dissroom_timer_stamp);

	game_restart_timer.data = this;
	game_restart_timer_stamp = 3;
	ev_timer_init(&game_restart_timer, Table::game_restart_timer_cb, game_restart_timer_stamp, game_restart_timer_stamp);

	check_room_timer.data = this;
	ev_timer_init(&check_room_timer, Table::check_room_timer_cb, check_room_timer_stamp, check_room_timer_stamp);

	check_user_can_out_card_timer.data = this;
	ev_timer_init(&check_user_can_out_card_timer, Table::user_can_out_card_timer_cb, check_user_can_out_card_timer_stamp, check_user_can_out_card_timer_stamp);


	InitData();
}

Table::~Table()
{
	ev_timer_stop(zjh.loop, &start_timer);
	ev_timer_stop(zjh.loop, &preready_timer);
	ev_timer_stop(zjh.loop, &dispatch_show_timer);
	ev_timer_stop(zjh.loop, &out_show_timer);
	ev_timer_stop(zjh.loop, &dispatch_delay_timer);
	ev_timer_stop(zjh.loop, &out_delay_timer);
	ev_timer_stop(zjh.loop, &dissolve_room_timer);
	ev_timer_stop(zjh.loop, &send_videodata_timer);
	ev_timer_stop(zjh.loop, &send_dissroom_timer);
	ev_timer_stop(zjh.loop, &game_restart_timer);
	ev_timer_stop(zjh.loop, &check_room_timer);
	ev_timer_stop(zjh.loop, &check_user_can_out_card_timer);
}

void Table::InitData()
{
	vid = 0;
	zid = 0;
	type = 0;
	base_money = 1;
	players.clear();
	for (int i = 0; i < GAME_PLAYER; i++)
	{
		seats[i].clear();
	}
	state = GAME_FREE;
	stand_money = 0;

	m_wTakeIn = 0;
	m_wPlayID = 0;
	m_cbRoomStatus = 0;
	m_wRoomUserId = 0;
	voters_players.clear();
	dissolve_applyer = 0;
	dissovle_state = 0;
	is_dissolved = 0;
	m_bDissovleRoom = false;
	m_wLastUser = INVALID_CHAIR;
	m_wNextUser = INVALID_CHAIR;
	m_wBankerUser = INVALID_CHAIR;
	m_wFirstBankerUser = INVALID_CHAIR;
	m_wHuangZhuangCount = 0;
	m_GamePlayer = 3;
	m_wCurrentNum = 0;
	m_strInnings.clear();
	m_cbCurrentCycle = 0;
	m_BaseWinCards = 16;
	m_bIsTianHuShow = false;
	m_IsBeginPerCircle = false;
	m_bIsNext = false;

	//数据统计
	memset(m_cbHuPaiCount, 0, sizeof(m_cbHuPaiCount));
	memset(m_wBestHuXi, 0, sizeof(m_wBestHuXi));
	memset(m_wBestFanShu, 0, sizeof(m_wBestFanShu));
	memset(m_wBestScore, 0, sizeof(m_wBestScore));
	memset(m_wTotalScore, 0, sizeof(m_wTotalScore));
	memset(m_wUserHuXi, 0, sizeof(m_wUserHuXi));
	memset(m_wUserFanShu, 0, sizeof(m_wUserFanShu));
	memset(m_wUserScore, 0, sizeof(m_wUserScore));
	memset(m_bTotalWinCardsCount, 0, sizeof(m_bTotalWinCardsCount));
	memset(m_cbLeftCardsCount, 0, sizeof(m_cbLeftCardsCount));
	memset(m_UserCanOutCard, true, sizeof(m_UserCanOutCard));
	m_strLastEndInfo.clear();

	m_vecGains.clear();

	Reset();
}

//重置数据
void Table::Reset()
{
	m_bAlreadyResp = false;
	//dissovle_state = 0;
	m_bDispatchHu = false;
	m_bDispatch = false;
	m_bCardOperated = false;
	m_bFirstCard = false;
	m_bIsTianHuShow = false;
	m_bAfterWeave = false;
	m_bOutCard = false;
	m_wCurrentUser = INVALID_CHAIR;
	//m_wNextUser = INVALID_CHAIR;
	m_wOutCardUser = INVALID_CHAIR;
	m_cbOutCardData = INVALID_CARD;
	//m_cbBankerCard = INVALID_CARD;

	memset(m_cbRepertoryCard, 0, sizeof(m_cbRepertoryCard));
	memset(m_cbCardIndex, 0, sizeof(m_cbCardIndex));
	memset(m_cbCardsWeaveCount, 0, sizeof(m_cbCardsWeaveCount));
	memset(m_CardsWeaveInfo, 0, sizeof(m_CardsWeaveInfo));
	memset(m_bWeaveHuXiCount, 0, sizeof(m_bWeaveHuXiCount));
	memset(m_bWeaveShowHuXiCount, 0, sizeof(m_bWeaveShowHuXiCount));
	memset(m_bWeaveItemCount, 0, sizeof(m_bWeaveItemCount));
	memset(m_WeaveItemArray, 0, sizeof(m_WeaveItemArray));
	memset(m_UserOutCards, 0, sizeof(m_UserOutCards));
	memset(m_bResponse, false, sizeof(m_bResponse));
	memset(m_bUserAction, 0, sizeof(m_bUserAction));
	memset(m_bPerformAction, 0, sizeof(m_bPerformAction));
	memset(m_bXiangGong, false, sizeof(m_bXiangGong));
	memset(m_bDongZhang, false, sizeof(m_bDongZhang));
	memset(m_bCommonOrBest, true, sizeof(m_bCommonOrBest));
	//memset(m_UserNiaoCount, -1, sizeof(m_UserNiaoCount));
	//memset(m_UserPiaoScore, -1, sizeof(m_UserPiaoScore));
	memset(m_UserOutCardCount, 0, sizeof(m_UserOutCardCount));
	memset(m_UserCurHuCardXi, 0, sizeof(m_UserCurHuCardXi));
	//memset(m_UserWeaveScore, 0, sizeof(m_UserWeaveScore));
	memset(m_bJuShou, true, sizeof(m_bJuShou));
	memset(m_bTotalWinCardsCount, true, sizeof(m_bTotalWinCardsCount));
	memset(m_cbLeftCardsCount, 0, sizeof(m_cbLeftCardsCount));
	memset(m_UserCanOutCard, true, sizeof(m_UserCanOutCard));

}

int Table::split(const std::string &str, std::vector<std::string> &ret_, std::string sep)
{
	if (str.empty())
	{
		return 0;
	}

	std::string tmp;
	std::string::size_type pos_begin = str.find_first_not_of(sep);
	std::string::size_type comma_pos = 0;

	while (pos_begin != std::string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}

void Table::init_made_info(Json::Value &val)
{
	if (!val["baseGold"].isNull() && val["baseGold"].isNumeric())
	{
		base_money = val["baseGold"].asInt();
	}
	if (!val["standMoney"].isNull() && val["standMoney"].isNumeric())
	{
		stand_money = val["standMoney"].asInt();
	}
	if (!val["roomGolden"].isNull() && val["roomGolden"].isNumeric())
	{
		m_wTakeIn = val["roomGolden"].asInt();
	}
	if (!val["roomStatus"].isNull() && val["roomStatus"].isNumeric())
	{
		m_cbRoomStatus = val["roomStatus"].asInt();
	}
	if (!val["roomUserId"].isNull() && val["roomUserId"].isNumeric())
	{
		m_wRoomUserId = val["roomUserId"].asInt();
	}
	if (!val["dataMap"].isNull())
	{
		if (!val["dataMap"]["innerWayList"].isNull())
		{
			//房间类型
			if (!val["dataMap"]["innerWayList"]["1000"].isNull() && val["dataMap"]["innerWayList"]["1000"].isString())
			{
				std::string str = val["dataMap"]["innerWayList"]["1000"].asString().c_str();
				std::vector<std::string> vct;
				split(str, vct, ",");
				for (vector<int>::size_type j = 0; j < vct.size(); j++)
				{
					std::string strPlayID = vct[j];
					m_wPlayID = atoi(strPlayID.c_str());
				}
			}
		}
		if (!val["dataMap"]["innerWayList"]["1001"].isNull() && val["dataMap"]["innerWayList"]["1001"].isString())
		{
			std::string str = val["dataMap"]["innerWayList"]["1001"].asString().c_str();
			std::vector<std::string> vct;
			split(str, vct, ",");
			for (vector<int>::size_type j = 0; j < vct.size(); j++)
			{
				std::string strPlayID = vct[j];
				check_playid(atoi(strPlayID.c_str()));
			}
		}
		if (!val["dataMap"]["innerWayList"]["1002"].isNull() && val["dataMap"]["innerWayList"]["1002"].isString())
		{
			std::string str = val["dataMap"]["innerWayList"]["1002"].asString().c_str();
			std::vector<std::string> vct;
			split(str, vct, ",");
			for (vector<int>::size_type j = 0; j < vct.size(); j++)
			{
				std::string strPlayID = vct[j];
				check_playid(atoi(strPlayID.c_str()));
			}
		}

		if (!val["dataMap"]["innerWayList"]["1003"].isNull() && val["dataMap"]["innerWayList"]["1003"].isString())
		{
			std::string str = val["dataMap"]["innerWayList"]["1003"].asString().c_str();
			std::vector<std::string> vct;
			split(str, vct, ",");
			for (vector<int>::size_type j = 0; j < vct.size(); j++)
			{
				std::string strPlayID = vct[j];
				check_playid(atoi(strPlayID.c_str()));
			}
		}
	}
}

void Table::check_playid(int nPlayID)
{
	switch (nPlayID)
	{
		case BASE_SCORE_1:
			m_BaseScore = 1;
			break;
		case BASE_SCORE_2:
			m_BaseScore = 2;
			break;
		case BASE_SCORE_3:
			m_BaseScore = 3;
			break;
		case BASE_SCORE_5:
			m_BaseScore = 5;
			break;
		case BASE_SCORE_10:
			m_BaseScore = 10;
			break;
		case BANKER_TIANHU:
			m_GamePlay = TIANHU;
			break;
		case STICK_FAN:
			m_GamePlay = STICK;
			break;
		case YEZI_METHOD:
			m_GamePlay = YEZI;
			break;
		case THREE_CARD_HE:
			m_CardsBaseHe = 3;
			break;
		case FIVE_CARD_HE:
			m_CardsBaseHe = 5;
			break;
		case SEVEN_CARD_HE:
			m_CardsBaseHe = 7;
			break;
		default:
			break;
	}
}

int Table::init(Json::Value &valCfg, Client *client)
{
	int my_vid = zjh.conf["tables"]["vid"].asInt();
	int my_zid = zjh.conf["tables"]["zid"].asInt();
	int my_type = zjh.conf["tables"]["type"].asInt();
	tid = client->roomid;
	vid = (vid > 0) ? vid : my_vid;
	zid = (zid > 0) ? zid : my_zid;
	type = (0 == my_type) ? type : my_type;

	//初始化配置
	init_made_info(valCfg);

	log.info("Table init tid[%s] base_money[%d] stand_money[%d] m_wTakeIn[%d] m_wPlayID[%d] m_cbRoomStatus[%d] m_wRoomUserId[%d] m_BaseWinCards[%d] m_GamePlayer[%d] .\n",
			 tid.c_str(), base_money, stand_money, m_wTakeIn, m_wPlayID, m_cbRoomStatus, m_wRoomUserId, m_BaseWinCards, m_GamePlayer);
	log.info("Table init tid[%s]  .\n", tid.c_str());
	return 0;
}

int Table::broadcast(Player *p, const std::string &packet)
{
	Player *player;
	std::map<int, Player *>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
	{
		player = it->second;
		if (player == p || player->client == NULL)
		{
			continue;
		}
		player->client->send(packet);
	}
	return 0;
}

int Table::unicast(Player *p, const std::string &packet)
{
	if (p->client)
	{
		return p->client->send(packet);
	}
	return -1;
}

int Table::random(int start, int end, int seed)
{
	return start + rand() % (end - start + 1);
}

int Table::sit_down(Player *player)
{
	std::vector<int> tmp;
	for (int i = 0; i < GAME_PLAYER; i++)
	{
		if (seats[i].occupied == 0)
		{
			tmp.push_back(i);
		}
	}

	int len = tmp.size();
	if (len == GAME_PLAYER)
	{
		int index = random(0, len - 1, player->uid);
		int i = tmp[index];
		log.debug("len[%d] index[%d] i[%d]\n", len, index, i);
		seats[i].occupied = 1;
		seats[i].player = player;
		return i;
	}
	else if (len > 0)
	{
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			if (seats[i].occupied == 1)
			{
				for (int j = 0; j < GAME_PLAYER; ++j)
				{
					int temp_id = (i + j) % GAME_PLAYER;
					if (seats[temp_id].occupied == 0)
					{
						seats[temp_id].occupied = 1;
						seats[temp_id].player = player;
						return temp_id;
					}
				}
			}
		}
	}

	return -1;
}

void Table::stand_up(Player *player)
{
	seats[player->seatid].clear();
}

int Table::handler_user_operate(int cmd, Player *player)
{
//	log.info("handler_user_operate, cmd: %d \n", cmd);
	switch (cmd)
	{
	case CLIENT_READY_REQ:
		handler_ready(player);
		break;
	case CLIENT_LOGOUT_REQ:
		zjh.game->del_player(player);
		break;
	case CLIENT_TABLE_INFO_REQ:
		handler_table_info(player);
		break;
	case CLIENT_EMOTION_REQ:
		handler_interaction_emotion(player);
		break;
	case CLIENT_UPTABLE_APPLY_REQ:
		handler_apply_uptable(player);
		break;
	case CLIENT_DOWNTABLE_REQ:
		handler_downtable(player);
		break;
	case CLINET_HEART_BEAT_REQ:
		heart_beat_res(player);
		break;
	case CLIENT_PHZ_OUT_CARD_REQ: //玩家出牌消息
		OnUserOutCard(player);
		break;
	case CLIENT_PHZ_OPERATE_CARD_REQ: //玩家操作牌
		OnUserOperateCard(player);
		break;
	case CLIENT_PHZ_CHANGE_CARD_REQ: //换牌
	//	OnUserChangeCard(player);
		break;
	case CLIENT_PHZ_UPDATE_CARD_REQ: //整理
	//	OnUserUpdateCard(player);
		break;
	case CLIENT_DISSOLVE_ROOM_REQ:
		handler_dissolve_room(player); //解散房间请求
		break;
	case CLIENT_DISSOLVE_ACTION_REQ:
		handler_dissolve_action(player); //操作
		break;
	case CLIENT_PHZ_FINAL_END_REQ:
		OnFinalEndReq(player); //总结算请求
		break;
	case CLIENT_PHZ_PRE_OPERATE_REQ:
	//	OnUserPreOperateCard(player); //预操作请求
		break;
	case CLIENT_PHZ_OFFLINE_INFO_REQ:
		OnOfflineInfoReq(player); //断线信息请求
		break;
	case CLIENT_PHZ_HAND_DETAIL_REQ:
		OnHandDetailInfo(player); //手牌详情
		break;
	case CLIENT_CHAT_REQ:
		handler_chat(player);
		break;
	case CLIENT_FACE_REQ:
		handler_face(player);
		break;
	case CLIENT_PHZ_GAINS_REQ:
		OnUserGainsReq(player);
		break;
	case 1234:
		log.info("demo cmd[%d], uid[%d] tid[%s]. \n", cmd, player->uid, player->tid.c_str());
		break;	
	default:
		log.error("user operate error invalid cmd[%d] uid[%d] tid[%s] .\n", cmd, player->uid, player->tid.c_str());
		return -1;
	}

	return 0;
}

int Table::del_player(Player *player)
{
	if (player == NULL)
	{
		log.error("del player error player Null tid[%s] .\n", tid.c_str());
		return -1;
	}
	if (players.find(player->uid) == players.end())
	{
		log.error("del player error player not find uid[%d] tid[%s].\n", player->uid, tid.c_str());
		return -1;
	}
	player->stop_offline_timer();
	players.erase(player->uid);
	log.info("del player uid[%d] tid[%d].\n", player->uid, tid.c_str());
	if (players.empty())
	{
		return 1;
	}
	return 0;
}

int Table::handler_login(Player *player)
{
	if (players.find(player->uid) != players.end())
	{
		log.error("handler login error player exsit uid[%d] tid[%s] .\n", player->uid, tid.c_str());
		return -1;
	}
	players[player->uid] = player;
	player->tid = tid;

	handler_login_succ_uc(player); //单播玩家登陆消息
	handler_apply_uptable(player); //登录后自动上桌
	handler_table_info(player);	//单播桌子信息

	log.info("handler login succ uid[%d] tid[%s] size[%d] .\n", player->uid, tid.c_str(), players.size());
	return 0;
}

int Table::handler_login_succ_uc(Player *player)
{
	proto::game::AckLoginSuccessUc stLoginuc;
	stLoginuc.set_seatid(player->seatid);
	stLoginuc.set_uid(player->uid);
	stLoginuc.set_money(player->money);
	if (player->name != "")
	{
		stLoginuc.set_name(player->name.c_str());
	}
	if (player->avatar != "")
	{
		stLoginuc.set_avatar(player->avatar.c_str());
	}
	stLoginuc.set_sex(player->sex);
	stLoginuc.set_exp(player->exp);
	stLoginuc.set_rmb(player->rmb);
	Ppacket ppack;
	stLoginuc.SerializeToString(&ppack.body);
	ppack.pack(SERVER_LOGIN_SUCC_UC);
	unicast(player, ppack.data);
	log.info("handler login succ uc uid[%d] tid[%s] .\n", player->uid, tid.c_str());
	return 0;
}

int Table::handler_login_succ_bc(Player *player)
{
	proto::game::AckLoginSuccessBc stLoginbc;
	stLoginbc.set_seatid(player->seatid);
	stLoginbc.set_uid(player->uid);
	stLoginbc.set_money(player->money);
	if (player->name != "")
	{
		stLoginbc.set_name(player->name.c_str());
	}
	if (player->avatar.size() != 0)
	{
		stLoginbc.set_avatar(player->avatar.c_str());
	}
	stLoginbc.set_sex(player->sex);
	Ppacket ppack;
	stLoginbc.SerializeToString(&ppack.body);
	ppack.pack(SERVER_LOGIN_SUCC_BC);
	broadcast(player, ppack.data);
	log.info("handler login succ bc uid[%d] tid[%s] .\n", player->uid, tid.c_str());
	return 0;
}

int Table::handler_table_info(Player *player, int req_count)
{
	proto::game::AckTableInfo stTableInfo;
	stTableInfo.set_seatid(player->seatid);
	stTableInfo.set_state(state);
	stTableInfo.set_operate_timer_stamp(20);
	stTableInfo.set_banker_user(m_wBankerUser);
	stTableInfo.set_first_banker_user(m_wFirstBankerUser);
	stTableInfo.set_current_user(m_wCurrentUser);
	stTableInfo.set_current_outcard_user(m_wOutCardUser);
	stTableInfo.set_current_outcard(m_cbOutCardData);
	stTableInfo.set_is_dispatch(m_bDispatch);
	stTableInfo.set_card_operated(m_bCardOperated);
	stTableInfo.set_is_out_card(m_bOutCard);
	stTableInfo.set_is_first_card(m_bFirstCard);
	stTableInfo.set_huang_count(m_wHuangZhuangCount);
	stTableInfo.set_take_in(m_wTakeIn);
	stTableInfo.set_play_id(m_wPlayID);
	stTableInfo.set_base_huxi(m_BaseWinCards);
	stTableInfo.set_room_user_id(m_wRoomUserId);
	stTableInfo.set_is_base_two_score(2 == base_money);
	stTableInfo.set_current_num(m_wCurrentNum);
	_tint32 wChairID = player->seatid;

	for (_uint8 i = 0; i < m_UserWeaveCache.size(); ++i)
	{
		stTableInfo.add_win_weaves(m_UserWeaveCache[i]);
		log.info("handler_table_info win_weaves: 0x%x, wChairID  %d \n", m_UserWeaveCache[i], wChairID);
	}

	if (wChairID >= 0 && wChairID < GAME_PLAYER)
	{
		if (req_count >= 0 && req_count < m_cbOfflineCount[wChairID])
		{
			for (_uint8 i = req_count; i < m_cbOfflineCount[wChairID] && i < MaxOfflineLen; ++i)
			{
				stTableInfo.add_offline_info(m_strOfflineInfo[wChairID][i]);
			}
		}

		stTableInfo.set_user_action(m_bUserAction[wChairID]);
		log.info("handler_table_info m_bUserAction: 0x%x, wChairID  %d \n", m_bUserAction[wChairID], wChairID);
		if (m_bUserAction[wChairID] != ACK_NULL)
		{
			_tint32 wFirstUser = INVALID_CHAIR;
			bool bFirstOperate = IsFirstUser(wChairID, wFirstUser);
			stTableInfo.set_is_first_operate(bFirstOperate);
		}
		stTableInfo.set_response(m_bResponse[wChairID]);
		stTableInfo.set_perform_action(m_bPerformAction[wChairID]);

		for (_uint8 i = 0; i < m_cbCardsWeaveCount[wChairID]; ++i)
		{
			proto::game::tagHandCards *pstTableHandCards = stTableInfo.add_hand_cards();
			for (_uint8 j = 0; j < m_CardsWeaveInfo[wChairID][i].cbCardCount; ++j)
			{
				if (m_CardsWeaveInfo[player->seatid][i].cbCardList[j] != 0)
				{
					pstTableHandCards->add_card(m_CardsWeaveInfo[player->seatid][i].cbCardList[j]);
				}
				log.info("handler_table_info m_CardsWeaveInfo: 0x%x  \n", m_CardsWeaveInfo[player->seatid][i].cbCardList[j]);
			}
		}
	}
	stTableInfo.set_base_money(base_money);
	stTableInfo.set_stand_money(stand_money);
	proto::game::tagDissolveRoomInfo *pstDissolveInfo = stTableInfo.mutable_dissolve_room_info();
	pstDissolveInfo->set_state(dissovle_state);
	if (dissovle_state == 1)
	{
		pstDissolveInfo->set_uid(dissolve_applyer);
		for (std::map<int, Player *>::iterator it = voters_players.begin(); it != voters_players.end(); it++)
		{
			pstDissolveInfo->add_voters_uid(it->first);
			proto::game::tagPlayers *pstDissPlayers = pstDissolveInfo->add_players();
			pstDissPlayers->set_uid(it->second->uid);
			pstDissPlayers->set_action(it->second->dissovle_state);
		}
		_uint32 wRemainTime = (_uint32)ev_timer_remaining(zjh.loop, &dissolve_room_timer);
		pstDissolveInfo->set_remain_time(wRemainTime);
	}

	for (_uint8 c = 0; c < GAME_PLAYER; ++c)
	{
		Player *p = seats[c].player;
		if (p == NULL)
			continue;
		proto::game::tagPlayers *pstTablePlayers = stTableInfo.add_players();
		pstTablePlayers->set_uid(p->uid);
		pstTablePlayers->set_seatid(p->seatid);
		pstTablePlayers->set_ready(seats[c].ready);
		pstTablePlayers->set_money(p->money);
		pstTablePlayers->set_name(p->name);
		pstTablePlayers->set_sex(p->sex);
		pstTablePlayers->set_avatar(p->avatar);
		pstTablePlayers->set_hu_xi(m_bWeaveShowHuXiCount[c]);
		for (int j = 0; j < m_bWeaveItemCount[c]; ++j)
		{
			proto::game::tagWeaveCards *pstWeaveCards = pstTablePlayers->add_weaves();
			pstWeaveCards->set_weave_kind(m_WeaveItemArray[c][j].cbWeaveKind);
			pstWeaveCards->set_card_count(m_WeaveItemArray[c][j].cbCardCount);
		}

	
		for (_uint8 i = 0; i < m_bWeaveItemCount[c]; ++i)     //添加赢牌区
		{
			proto::game::tagWeaveCards *pstWinCards = pstTablePlayers->add_win_cards_weaves();
			for (_uint8 j = 0; j < m_WeaveItemArray[c][i].cbCardCount; ++j)
			{
				if (m_WeaveItemArray[c][i].cbCardList[j] != 0)
				{
					pstWinCards->add_card_list(m_WeaveItemArray[c][i].cbCardList[j]);
					log.info("handler_table_info m_WeaveItemArray: 0x%x  \n", m_WeaveItemArray[c][i].cbCardList[j]);
				}

			}
		}
		if (m_wNextUser != m_wBankerUser && m_wCurrentUser != m_wBankerUser)  //一圈没打完
		{
			for (_uint8 i = 0; i < m_UserOutCards[c].cbCardCount; ++i)    //添加用户出牌组合
			{
				pstTablePlayers->add_user_out_cards(m_UserOutCards[c].cbCardList[i]);
				log.info("handler_table_info m_UserOutCards A: 0x%x  \n", m_UserOutCards[c].cbCardList[i]);
			}		
		}
		log.info("handler_table_info m_wBankerUser A : %d,  m_wCurrentUser: %d, m_wNextUser: %d  \n", m_wBankerUser, m_wCurrentUser, m_wNextUser);

		pstTablePlayers->set_offline(p->is_offline);
	}

	stTableInfo.set_game_player(GAME_PLAYER);
	stTableInfo.set_game_name("chengdulc");
	Ppacket ppack;
	stTableInfo.SerializeToString(&ppack.body);
	ppack.pack(SERVER_TABLE_INFO_UC);
	unicast(player, ppack.data);
	log.debug("uid[%d] tid[%s] stTableInfo[%s] .\n", player->uid, tid.c_str(), stTableInfo.DebugString().c_str());
	log.info("handler table info uid[%d] tid[%s].\n", player->uid, tid.c_str());
	return 0;
}

int Table::handler_preready()
{
	for (std::map<int, Player *>::iterator iter = players.begin(); iter != players.end(); iter++)
	{
		iter->second->reset();
	}
	log.info("handler preready tid[%s] .\n", tid.c_str());
	return 0;
}

void Table::start_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->start_timer);
	table->m_cbCurTimer = 0;
	table->OnOperateStart();
}

void Table::preready_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->preready_timer);
	table->m_cbCurTimer = 0;
	table->handler_preready();
}

void Table::dispatch_show_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->dispatch_show_timer);
	table->m_cbCurTimer = 0;
	//table->m_wCurrentUser = (table->m_wCurrentUser + 1) % (table->m_GamePlayer);
	//table->DispatchCardData(table->m_wCurrentUser);
}

void Table::out_show_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->out_show_timer);
	table->m_cbCurTimer = 0;
//	table->m_wCurrentUser = (table->m_wCurrentUser + 1) % (table->m_GamePlayer);
//	table->DispatchCardData(table->m_wCurrentUser);
}

void Table::dispatch_delay_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->dispatch_delay_timer);
	table->m_cbCurTimer = 0;
//	bool bEstimate = table->DispatchEstimateUserRespond(table->m_wCurrentUser, table->m_cbCurrentCard);
	/*if (bEstimate == false)
	{
		ev_timer_again(zjh.loop, &table->dispatch_show_timer);
		table->m_cbCurTimer = 3;
	}*/
	//保存数据到redis
//	table->SerializeTableData();
}

void Table::out_delay_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->out_delay_timer);
	table->m_cbCurTimer = 0;
	table->OutEstimateUserRespond(table->m_wCurrentUser, table->m_UserWeaveCache);


	//if (bEstimate == false)
	//{
	//	ev_timer_again(zjh.loop, &table->out_show_timer);
	//	table->m_cbCurTimer = 4;
	//}
	//保存数据到redis
	table->SerializeTableData();
}

void Table::user_can_out_card_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	if (table->m_wNextUser == table->m_wBankerUser)
	{
		ev_timer_stop(zjh.loop, &table->check_user_can_out_card_timer);
		table->OutEstimateCircleEndRespond(table->m_wCurrentUser, table->m_UserWeaveCache);
	}
	else
	{
		table->m_wNextUser = (table->m_wNextUser + 1) % GAME_PLAYER;
		table->OutEstimateCireleNoEndRespond(table->m_wCurrentUser, table->m_UserWeaveCache);
	}

	table->m_cbCurTimer = 0;
	log.info("user_can_out_card_timer_cb m_wNextUser: %d \n", table->m_wNextUser);
}


int Table::handler_logout(Player *player)
{
	if (state != GAME_FREE)
	{
		for (int i = 0; i < GAME_PLAYER; ++i)
		{
			if (seats[i].uid == player->uid)
			{
				log.error("handler logout error player in seat playing. uid[%d] state[%d] tid[%s].\n", player->uid, state, tid.c_str());
				return -1;
			}
		}
	}
	handler_downtable(player);
	//广播退出房间协议
	proto::game::AckLogoutBc stLogout;
	stLogout.set_seatid(player->seatid);
	stLogout.set_uid(player->uid);
	stLogout.set_type(player->logout_type);
	Ppacket ppack;
	stLogout.SerializeToString(&ppack.body);
	ppack.pack(SERVER_LOGOUT_SUCC_BC);
	unicast(player, ppack.data);
	log.info("handler logout uid[%d] seatid[%d] money[%ld] tid[%s].\n", player->uid, player->seatid, player->money, tid.c_str());
	return 0;
}

int Table::handler_interaction_emotion(Player *player)
{
	proto::game::ReqEmotion stEmotion;
	stEmotion.ParseFromString(player->client->ppacket.body);
	int target_seatid = stEmotion.target_seatid();
	int itype = stEmotion.type();
	proto::game::AckEmotionBC stEmotionBC;
	stEmotionBC.Clear();
	stEmotionBC.set_seatid(player->seatid);
	stEmotionBC.set_money(player->money);
	stEmotionBC.set_target_seatid(target_seatid);
	stEmotionBC.set_type(itype);
	Ppacket ppack;
	stEmotionBC.SerializeToString(&ppack.body);
	ppack.pack(SERVER_EMOTION_BC);
	broadcast(NULL, ppack.data);
	log.info("handler interaction emotion uid[%d] type[%d] tid[%s].\n ", player->uid, itype, tid.c_str());
	return 0;
}



void Table::uptable_error_uc(Player *player, int code)
{
	if (NULL == player)
	{
		log.info("uptable error uc error player is null tid[%s] .\n", tid.c_str());
		return;
	}
	proto::game::AckUpTableErrorUc stUpTable;
	stUpTable.set_uid(player->uid);
	stUpTable.set_money(player->money);
	stUpTable.set_code(code);
	Ppacket ppack;
	stUpTable.SerializeToString(&ppack.body);
	ppack.pack(SERVER_UPTABLE_ERR_UC);
	unicast(player, ppack.data);
}

int Table::handler_apply_uptable(Player *player)
{
	handler_uptable(player);
	return 0;
}

int Table::handler_uptable(Player *player)
{
	for (int i = 0; i < GAME_PLAYER; ++i)
	{
		if (seats[i].uid == player->uid)
		{
			log.error("handler uptable error uid[%d] already in seat tid[%s].\n", player->uid, tid.c_str());
			uptable_error_uc(player, 102);
			return -1;
		}
	}

	if (player->money < stand_money)
	{
		log.error("handler uptable error uid[%d] money[%ld] too less stand_money[%d] tid[%s].\n", player->uid, player->money, stand_money, tid.c_str());
		uptable_error_uc(player, 104);
		return -1;
	}

	int SeatNum = 0;
	for (int i = 0; i < GAME_PLAYER; i++)
	{
		if (seats[i].player != NULL)
			SeatNum++;
	}
	if (SeatNum >= GAME_PLAYER)
	{
		log.error("handler uptable error uid[%d] SeatNum[%d] tid[%s] .\n", player->uid, SeatNum, tid.c_str());
		uptable_error_uc(player, 105);
		return -1;
	}
	player->stop_offline_timer();
	player->seatid = sit_down(player);
	if (player->seatid < 0)
	{
		log.error("handler uptable error uid[%d] seatid[%d] tid[%s] .\n", player->uid, player->seatid, tid.c_str());
		uptable_error_uc(player, 105);
		return -1;
	}
	Seat &seat = seats[player->seatid];
	seat.uid = player->uid;

	proto::game::AckUpTableSuccess stUpTable;
	stUpTable.set_uid(player->uid);
	stUpTable.set_seatid(player->seatid);
	if (player->name.size() != 0)
	{
		stUpTable.set_name(player->name.c_str());
	}
	stUpTable.set_sex(player->sex);
	if (player->avatar.size() != 0)
	{
		stUpTable.set_avatar(player->avatar.c_str());
	}
	stUpTable.set_money(player->money);
	stUpTable.set_exp(player->exp);
	Ppacket ppack;
	stUpTable.SerializeToString(&ppack.body);
	ppack.pack(SERVER_UPTABLE_SUCC_BC);
	broadcast(NULL, ppack.data);

	log.info("handler uptable succ uid[%d] seaitd[%d] money[%ld] tid[%s] .\n", player->uid, player->seatid, player->money, tid.c_str());
	return 0;
}

int Table::handler_downtable(Player *player)
{
	bool bFind = false;
	for (int i = 0; i < GAME_PLAYER; ++i)
	{
		if (seats[i].uid == player->uid)
		{
			bFind = true;
			break;
		}
	}
	if (!bFind)
	{
		log.error("handler downtable error uid[%d] not in seat tid[%s].\n", player->uid, tid.c_str());
		return -1;
	}
	if (state != GAME_FREE)
	{
		player->down_tag = (player->down_tag == 0) ? 1 : 0;
		proto::game::AckAheadDownTable stHeadDownTable;
		stHeadDownTable.set_uid(player->uid);
		stHeadDownTable.set_seatid(player->seatid);
		stHeadDownTable.set_down_tag(player->down_tag);
		Ppacket ppack;
		stHeadDownTable.SerializeToString(&ppack.body);
		ppack.pack(SERVER_AHEAD_DOWNTABLE_UC);
		unicast(player, ppack.data);
		log.info("handler downtable next round down uid[%d] money[%ld] state[%d] tid[%s].\n", player->uid, player->money, state, tid.c_str());
		return 0;
	}

	if (player->seatid == m_wBankerUser)
		m_wBankerUser = INVALID_CHAIR;
	proto::game::AckDownTableSuccess stDownTableSuccess;
	stDownTableSuccess.set_uid(player->uid);
	stDownTableSuccess.set_seatid(player->seatid);
	stDownTableSuccess.set_money(player->money);
	player->down_tag = 0;
	Ppacket ppack;
	stDownTableSuccess.SerializeToString(&ppack.body);
	ppack.pack(SERVER_DOWNTABLE_SUCC_BC);
	broadcast(NULL, ppack.data);
	//stand_up
	stand_up(player);
	player->clear();

	log.info("handler downtable succ uid[%d] money[%ld] tid[%s].\n", player->uid, player->money, tid.c_str());
	return 0;
}

void Table::update_user_info_to_datasvr(int cmd, int UserScore[GAME_PLAYER])
{
	Jpacket packet_data;
	packet_data.val["cmd"] = cmd; //SERVER_DZ_UPDATE_USER_INFO;
	for (int i = 0; i < GAME_PLAYER; i++)
	{
		packet_data.val["players"][i]["uid"] = seats[i].uid;
		packet_data.val["players"][i]["alter_money"] = UserScore[i];
		packet_data.val["players"][i]["al_board"] = 1;
		if (UserScore[i] > 0)
		{
			packet_data.val["players"][i]["al_win"] = 1;
			packet_data.val["players"][i]["alter_exp"] = 0;
		}
		else
		{
			packet_data.val["players"][i]["al_win"] = 0;
			packet_data.val["players"][i]["alter_exp"] = 0;
		}
	}
	packet_data.val["vid"] = vid;
	packet_data.val["roomid"] = tid;
	packet_data.val["innings"] = m_strInnings;
	packet_data.end();
	zjh.game->send_to_datasvr(packet_data.tostring());
}

int Table::game_start_req()
{
	Jpacket req_packet;
	req_packet.val["cmd"] = SERVER_DZ_GAME_START_REQ;
	req_packet.val["vid"] = zid;
	req_packet.val["roomid"] = tid;
	req_packet.val["innings"] = m_strInnings;
	req_packet.end();
	zjh.game->send_to_datasvr(req_packet.tostring());
	log.info("game start req roomid[%s] .\n", tid.c_str());
	return 0;
}

int Table::game_start_res(Jpacket &packet)
{
	int can_start = 0;
	if (!packet.val["can_start"].isNull() && packet.val["can_start"].isNumeric())
	{
		can_start = packet.val["can_start"].asInt();
	}
	if (0 == can_start)
	{
		int code = 0;
		if (!packet.val["code"].isNull() && packet.val["code"].isNumeric())
		{
			code = packet.val["code"].asInt();
		}
		proto::game::AckGameStartFail stGameStartFail;
		stGameStartFail.set_vid(vid);
		stGameStartFail.set_roomid(tid);
		stGameStartFail.set_can_start(0);
		stGameStartFail.set_code(code);
		int ntime = (int)time(NULL);
		stGameStartFail.set_ts(ntime);
		Ppacket ppack;
		stGameStartFail.SerializeToString(&ppack.body);
		ppack.pack(SERVER_DZ_GAME_START_RES);
		broadcast(NULL, ppack.data);
		advance_game_end();
		log.error("game start res fail roomid[%s] can_start[%d] code[%d] .\n", tid.c_str(), can_start, code);
		return -1;
	}
	ev_timer_stop(zjh.loop, &game_restart_timer);
	if (m_bAlreadyResp == true)
	{
		log.error("game start res tid[%s] m_bAlreadyResp[%d] .\n", tid.c_str(), m_bAlreadyResp);
		return -1;
	}
	m_bAlreadyResp = true;

	int cReadyNum = 0;
	for (int i = 0; i < GAME_PLAYER; ++i)
	{
		if (seats[i].ready == 1)
			cReadyNum++;
	}
	log.info("cReadyNum: %d", cReadyNum);
	if (cReadyNum == GAME_PLAYER)
	{
		//开始游戏
		proto::game::AckPrereadyBC stPre;
		stPre.set_roomid(tid);
		Ppacket ppack;
		stPre.SerializeToString(&ppack.body);
		ppack.pack(SERVER_GAME_PREREADY_BC);
		broadcast(NULL, ppack.data);

		m_cbRoomStatus = 1;
		GameStart();

	}
	else //不能开赛，发0结算给平台
	{
		_tint32 UserScore[GAME_PLAYER] = {0};
		update_user_info_to_datasvr(SERVER_DZ_UPDATE_USER_INFO, UserScore);
	}

	log.info("game start res succ roomid[%s] can_start[%d] .\n", tid.c_str(), can_start);
	return 0;
}

void Table::handler_ready(Player *player)
{
	if (player->seatid < 0 || player->seatid >= GAME_PLAYER)
	{
		log.error("handler ready error seatid[%d] wrong .\n", player->seatid);
		return;
	}

	if (seats[player->seatid].ready == 1)  //已经准备就绪
	{
		log.error("handler ready error seatid[%d] already ready[ .\n", player->seatid);
		return;
	}
	seats[player->seatid].ready = 1;

	proto::game::AckUserReady stReady;
	stReady.set_seatid(player->seatid);
	stReady.set_uid(player->uid);
	Ppacket ppack;
	stReady.SerializeToString(&ppack.body);
	ppack.pack(SERVER_READY_SUCC_BC);
	broadcast(NULL, ppack.data);
	log.info("handler ready succ uid[%d] seatid[%d] tid[%s] .\n", player->uid, player->seatid, tid.c_str());

	//请求开始游戏
	_uint8 cReadyNum = 0;
	for (int i = 0; i < GAME_PLAYER; i++)
	{
		if (seats[i].ready == 1)
			cReadyNum++;
	}
	if (state == GAME_FREE && cReadyNum == GAME_PLAYER)
	{
		m_wCurrentNum++;
		std::ostringstream oss;
		oss << tid << "_" << m_wCurrentNum;
		m_strInnings = oss.str();
		game_start_req();
		ev_timer_again(zjh.loop, &game_restart_timer);
	}
}


//游戏开始
bool Table::GameStart()
{
	log.info("Game Start haha tid[%s] m_strInnings[%s].\n", tid.c_str(), m_strInnings.c_str());
	state = GAME_PLAYING;
	//gamestart数据初始化
	m_videostr.clear();
	m_strLastEndInfo.clear();
	memset(m_cbOfflineCount, 0, sizeof(m_cbOfflineCount));
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		for (_uint8 j = 0; j < MaxOfflineLen; ++j)
		{
			m_strOfflineInfo[i][j].clear();
		}
	}
	//确定庄家
	if (m_wBankerUser < 0 || m_wBankerUser >= GAME_PLAYER)
	{
		bool IsFind = false;
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			if (seats[i].player != NULL && seats[i].player->uid == (_tint32)m_wRoomUserId)
			{
				m_wBankerUser = i;
				IsFind = true;
				break;
			}
		}
		if (!IsFind)
		{
			m_wBankerUser = rand() % GAME_PLAYER;
		}
		m_wFirstBankerUser = m_wBankerUser;
	}
	//保存录像
	save_table_info_video();
	//洗牌
	_uint8 cbLeftCardCount = MAX_CARDS;
	m_GameLogic.RandCardData(m_cbRepertoryCard, MAX_CARDS);
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		cbLeftCardCount -= (MAX_COUNT);
		m_cbLeftCardsCount[i] = MAX_COUNT;
		m_GameLogic.SwitchToCardIndex(&m_cbRepertoryCard[cbLeftCardCount], MAX_COUNT, m_cbCardIndex[i]);
	}
	log.info("m_GamePlayer: %d, cbLeftCardCount: %d \n", m_GamePlayer, cbLeftCardCount);
	//发牌的时候要将硬章放到赢牌区
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		if (m_cbCardIndex[i].cbCards[3][0][3] != 0)
		{
			
			_uint8& cbCount = m_WeaveItemArray[i][m_bWeaveItemCount[i]].cbCardCount;
			cbCount = m_cbCardIndex[i].cbCards[3][0][3];
			m_bTotalWinCardsCount[i] += cbCount;
			log.info("m_bWeaveItemCount: %d , cbCount: %d m_bTotalWinCardsCount: %d \n", m_bWeaveItemCount[i], cbCount, m_bTotalWinCardsCount[i]);
			for (_uint8 j = 0; j <cbCount; ++j)
			{	
				m_WeaveItemArray[i][m_bWeaveItemCount[i]].cbCardList[j] = 0x303;
			}
			m_cbCardIndex[i].cbCards[3][0][3] = 0;
			m_bWeaveItemCount[i]++;			
		}
		if (m_cbCardIndex[i].cbCards[3][0][6] != 0)
		{

			_uint8& cbCount = m_WeaveItemArray[i][m_bWeaveItemCount[i]].cbCardCount;
			cbCount = m_cbCardIndex[i].cbCards[3][0][6];
			m_bTotalWinCardsCount[i] += cbCount;
			log.info("m_bWeaveItemCount: %d , cbCount: %d m_bTotalWinCardsCount：%d \n", m_bWeaveItemCount[i], cbCount, m_bTotalWinCardsCount[i]);
			for (_uint8 j = 0; j < cbCount; ++j)
			{
				m_WeaveItemArray[i][m_bWeaveItemCount[i]].cbCardList[j] = 0x306;
			}
			m_cbCardIndex[i].cbCards[3][0][6] = 0;
			m_bWeaveItemCount[i]++;
		}
	}

	//广播游戏开始
	std::map<int, Player *>::iterator iter = players.begin();

	for (; iter != players.end(); ++iter)
	{
		proto::game::AckGameStart stGameStart;
		Player *player = iter->second;
		if (NULL == player)
			continue;
		_tint32 wCurChairID = player->seatid;
	
		stGameStart.set_banker(m_wBankerUser);
		stGameStart.set_current_num(m_wCurrentNum);
		
		if (wCurChairID >= 0 && wCurChairID < GAME_PLAYER)
		{
			UpdateCommonCardsWeave(wCurChairID);

		//	log.debug("\n");
			log.debug("user card 111 \n");
			for (_uint8 i = 0; i < m_cbCardsWeaveCount[wCurChairID]; ++i) 
			{
				proto::game::tagHandCards* pstHandCards = stGameStart.add_hand_cards();
				log.debug("cbCardCount:  %d \n", m_CardsWeaveInfo[wCurChairID][i].cbCardCount);
				for (_uint8 j = 0; j < m_CardsWeaveInfo[wCurChairID][i].cbCardCount; ++j) 
				{
					if (m_CardsWeaveInfo[wCurChairID][i].cbCardList[j] != 0)
					{
						pstHandCards->add_card(m_CardsWeaveInfo[wCurChairID][i].cbCardList[j]);
						
					}
					log.debug("0x%x \n", m_CardsWeaveInfo[wCurChairID][i].cbCardList[j]);
				}
		//		log.debug("\n");
			}

		//	UpdateBestCardsWeave(wCurChairID);		
		//	std::vector<_uint8> vecListenCards;
			//if (IsListen(wCurChairID, vecListenCards))
			//{
			//	for (_uint8 i = 0; i < vecListenCards.size(); ++i)
			//		stGameStart.add_listen_cards(vecListenCards[i]);
			//}
			//计算不动章
		//	stGameStart.set_total_huxi(cbTotalHuXi);
		}



		//将硬张放置赢牌区
		log.debug("win card  \n");
		std::map<int, Player *>::iterator iter_1 = players.begin();
		for (; iter_1 != players.end(); ++iter_1)
		{
			Player *player = iter_1->second;
			if (NULL == player)
				continue;
			_tint32 wCurChairID = player->seatid;
			proto::game::tagPlayers *pstPlayerInfo = stGameStart.add_players();
			pstPlayerInfo->set_seatid(wCurChairID);
			for (_uint8 j = 0; j < m_bWeaveItemCount[wCurChairID]; ++j)
			{
				proto::game::tagWeaveCards *tagWeaveCards = pstPlayerInfo->add_win_cards_weaves();
				for (_uint8 k = 0; k < m_WeaveItemArray[wCurChairID][j].cbCardCount; ++k)
				{
					tagWeaveCards->add_card_list(m_WeaveItemArray[wCurChairID][j].cbCardList[k]);
				}
			}
		}


		Ppacket ppack;
		stGameStart.SerializeToString(&ppack.body);
		ppack.pack(SERVER_GAME_START_BC);
		unicast(player, ppack.data);
		log.debug("uid[%d] tid[%s] stGameStart[%s] .\n", player->uid, tid.c_str(), stGameStart.DebugString().c_str());
	}

	ev_timer_again(zjh.loop, &start_timer);
	m_cbCurTimer = 1;
	//保存录像
	save_game_start_video();
	//保存数据到redis
	SerializeTableData();
	return true;
}


bool Table::OnOperateStart()
{
	m_wCurrentUser = m_wBankerUser;
	//m_cbCurrentCard = m_cbBankerCard;


	//设置变量
	SendOutCardNotify(m_wCurrentUser, true);
	log.info("OnOperateStart: m_wCurrentUser: %d \n", m_wCurrentUser);
	//保存数据到redis
	SerializeTableData();
	return true;
}

/* 计算得分
 * wTotalHuXi : 胡息数
 * return	  : 对应的分数
 */
_uint32 Table::GetScore(_uint32 wTotalHuXi)
{
	_uint32 score = 0; //[0,9]   ，0 分
	if (10 <= wTotalHuXi && wTotalHuXi < 15)
	{
		score = 1;
	}
	else if (15 <= wTotalHuXi && wTotalHuXi <= 20)
	{
		score = 2;
	}
	else if (21 <= wTotalHuXi && wTotalHuXi < 25)
	{
		score = 4;
	}
	else if (25 <= wTotalHuXi && wTotalHuXi <= 30)
	{
		score = 6;
	}
	else if (31 <= wTotalHuXi)
	{
		score = 10;
	}
	return score;
}

//游戏结束
bool Table::GameEnd(_tint32 wChairID,  _uint8 cbEndState)
{
	//操作清零
	memset(m_bResponse, 0, sizeof(m_bResponse));
	memset(m_bUserAction, 0, sizeof(m_bUserAction));
	memset(m_bPerformAction, 0, sizeof(m_bPerformAction));
	m_UserWeaveCache.clear();
	log.info("game end wChairID[%d] uid[%d] tid[%s] m_strInnings[%s], cbEndState: %d\n", wChairID, seats[wChairID].uid, tid.c_str(), m_strInnings.c_str(), cbEndState);

	state = GAME_END;
	//_uint8 cbEndState = wChairID == INVALID_CHAIR ? 0 : 1; //0：黄庄 1：胡牌结束
	if (cbEndState == ACK_CHIHU)
	{
		_uint32 wTotalHuXi = 0;					  //总胡息


												 //结算打包
		proto::game::AckGameEnd stGameEnd;
		stGameEnd.set_end_type(cbEndState);
		stGameEnd.set_win_seatid(wChairID);
		//stGameEnd.set_hu_card(m_cbCurrentCard);
		//统计胡番信息
		tagHuCardInfo stHuCardInfo;
		memset(&stHuCardInfo, 0, sizeof(stHuCardInfo));
		//	_uint8 cbHuCard = (m_bDispatchHu == true) ? m_cbCurrentCard : INVALID_CARD;
		//各个玩家信息

		if (wChairID != m_wBankerUser)
		{
			m_GameLogic.GetNoBankerHuBestWeaves(m_bWeaveItemCount[wChairID], m_WeaveItemArray[wChairID], m_CardsWeaveInfo[wChairID], m_cbCardsWeaveCount[wChairID], m_wPreUserCards, &m_cbCardIndex[wChairID], wChairID);
			m_bTotalWinCardsCount[wChairID] += m_wPreUserCards.size();
		}

		m_GameLogic.GetHuCardInfoFinal(m_bTotalWinCardsCount[wChairID], m_bWeaveItemCount[m_wBankerUser], m_wBankerUser, m_wUserHuXi, m_wUserFanShu, m_wUserScore, m_WeaveItemArray[m_wBankerUser], m_BaseScore, m_GamePlay);

		log.info("GetHuCardInfoFinal, m_GamePlayer = %d\n ", m_GamePlayer);
		for (_uint8 pos = 0; pos < GAME_PLAYER; ++pos)
		{
			proto::game::tagPlayers *pstEndPlayers = stGameEnd.add_players();
			pstEndPlayers->set_seatid(pos);
			if (seats[pos].player != NULL)
			{
				log.info("GetHuCardInfoFinal, pos: %d, seats[pos].player->uid = %d\n ", pos, seats[pos].player->uid);
				pstEndPlayers->set_uid(seats[pos].player->uid);
				pstEndPlayers->set_name(seats[pos].player->name);
				pstEndPlayers->set_sex(seats[pos].player->sex);
				pstEndPlayers->set_avatar(seats[pos].player->avatar);
			}
	
			for (_uint8 j = 0; j < m_bWeaveItemCount[pos]; ++j)                  //赢牌区信息
			{
				proto::game::tagWeaveCards *pstWeaveCards = pstEndPlayers->add_weaves();
				pstWeaveCards->set_card_count(m_WeaveItemArray[pos][j].cbCardCount);
				for (_uint8 k = 0; k < m_WeaveItemArray[pos][j].cbCardCount; ++k)
				{
					pstWeaveCards->add_card_list(m_WeaveItemArray[pos][j].cbCardList[k]);
				//	_uint8 cbCard = m_WeaveItemArray[pos][j].cbCardList[k];
				}
			}
		}
		log.info("GetHuCardInfoFinal 1 \n ");
		//最终得分
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			proto::game::tagPlayers *pstEndPlayers = stGameEnd.mutable_players(i);
			if (seats[i].player != NULL)
			{
				seats[i].player->money += m_wUserScore[i];             //累积积分
				pstEndPlayers->set_money(seats[i].player->money);
			}
			pstEndPlayers->set_total_score(m_wUserScore[i]);
			pstEndPlayers->set_total_fan(m_wUserFanShu[i]);
			log.info("GameEnd:total score:  %d \n", m_wUserScore[i]);
		}

		//如果庄家赢了，则继续坐庄，如果输了，则由庄家的下家做庄
		if (m_wBankerUser != wChairID)
		{
			m_wBankerUser = (m_wBankerUser + 1) % GAME_PLAYER;
			//再次轮到第一个庄家坐庄的时候到下一圈
			if (m_wFirstBankerUser == m_wBankerUser)
			{
				++m_cbCurrentCycle;
			}
		}

		//广播结算
		std::map<int, Player *>::iterator iter = players.begin();
		for (; iter != players.end(); ++iter)
		{
			Player *player = iter->second;
			if (NULL == player)
				continue;
			_tint32 wCurChairID = player->seatid;
			if (wCurChairID >= 0 && wCurChairID < GAME_PLAYER)
			{
				stGameEnd.set_off_count(m_cbOfflineCount[wCurChairID]);
			}
			Ppacket ppack;
			stGameEnd.SerializeToString(&ppack.body);
			ppack.pack(SERVER_GAME_END_BC);
			unicast(player, ppack.data);
			log.debug("uid[%d] tid[%s] stGameEnd[%s] .\n", player->uid, tid.c_str(), stGameEnd.DebugString().c_str());
			//保存离线数据
			save_offline_info(wCurChairID, SERVER_GAME_END_BC, stGameEnd.SerializeAsString());
		}
		//数据统计
		m_cbHuPaiCount[wChairID]++;

		if (wTotalHuXi > m_wBestHuXi[wChairID])
			m_wBestHuXi[wChairID] = wTotalHuXi;
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			m_wTotalScore[i] += m_wUserScore[i];
			if (m_wUserScore[i] >(_tint32)m_wBestScore[i])
			{
				m_wBestScore[i] = m_wUserScore[i];
			}
		}

		tagGain stGain;
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			stGain.Gain[i] = m_wUserScore[i];
		}
		m_vecGains.push_back(stGain);

		//保存录像
		save_game_end_video(SERVER_GAME_END_BC, stGameEnd.SerializeAsString());
		//更换赢家为庄家
		m_wHuangZhuangCount = 0;
		//更新数据
		update_user_info_to_datasvr(SERVER_DZ_UPDATE_USER_INFO_LITTLE, m_wUserScore);
	}
	else if (cbEndState == ACK_HUANG)
	{
		proto::game::AckGameEnd stGameEnd;

		m_wHuangZhuangCount++;
		//黄庄后下家坐庄
		m_wBankerUser = (m_wBankerUser + 1) % GAME_PLAYER;
		if (m_wFirstBankerUser == m_wBankerUser)
		{
			++m_cbCurrentCycle;
		}

		//黄庄结算
		stGameEnd.set_end_type(cbEndState);
		//各个玩家信息
		for (_uint8 pos = 0; pos < GAME_PLAYER; ++pos)
		{
			proto::game::tagPlayers *pstEndPlayers = stGameEnd.add_players();
			pstEndPlayers->set_seatid(pos);
			if (seats[pos].player != NULL)
			{
				pstEndPlayers->set_uid(seats[pos].player->uid);
				pstEndPlayers->set_name(seats[pos].player->name);
				pstEndPlayers->set_sex(seats[pos].player->sex);
				pstEndPlayers->set_avatar(seats[pos].player->avatar);
				pstEndPlayers->set_money(seats[pos].player->money);
			}

			for (_uint8 j = 0; j < m_bWeaveItemCount[pos]; ++j)      //赢牌区
			{
				proto::game::tagWeaveCards *pstWeaveCards = pstEndPlayers->add_weaves();
				pstWeaveCards->set_card_count(m_WeaveItemArray[pos][j].cbCardCount);
				for (_uint8 k = 0; k < m_WeaveItemArray[pos][j].cbCardCount; ++k)
				{
					pstWeaveCards->add_card_list(m_WeaveItemArray[pos][j].cbCardList[k]);
				}
			}
		}

		//如果庄家黄了，由庄家的下家做庄
		if (m_wBankerUser == wChairID)
		{
			m_wBankerUser = (m_wBankerUser + 1) % GAME_PLAYER;
			//再次轮到第一个庄家坐庄的时候到下一圈
			if (m_wFirstBankerUser == m_wBankerUser)
			{
				++m_cbCurrentCycle;
			}
		}
		//广播结算
		std::map<int, Player *>::iterator iter = players.begin();
		for (; iter != players.end(); ++iter)
		{
			Player *player = iter->second;
			if (NULL == player)
				continue;
			_tint32 wCurChairID = player->seatid;
			if (wCurChairID >= 0 && wCurChairID < GAME_PLAYER)
			{
				stGameEnd.set_off_count(m_cbOfflineCount[wCurChairID]);
			}
			Ppacket ppack;
			stGameEnd.SerializeToString(&ppack.body);
			ppack.pack(SERVER_GAME_END_BC);
			unicast(player, ppack.data);
			log.debug("uid[%d] tid[%s] stGameEnd[%s] .\n", player->uid, tid.c_str(), stGameEnd.DebugString().c_str());
			//保存离线数据
			save_offline_info(wCurChairID, SERVER_GAME_END_BC, stGameEnd.SerializeAsString());
		}
		//保存录像
		save_game_end_video(SERVER_GAME_END_BC, stGameEnd.SerializeAsString());

	/*	tagGain stGain;
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			stGain.Gain[i] = m_wUserScore[i];
		}
		m_vecGains.push_back(stGain);*/

		//更新数据
		update_user_info_to_datasvr(SERVER_DZ_UPDATE_USER_INFO_LITTLE, m_wUserScore);
	}

	//发送录像
	ev_timer_again(zjh.loop, &send_videodata_timer);
	m_cbCurTimer = 8;

	ev_timer_again(zjh.loop, &check_room_timer);
	SerializeTableData();
	return true;
}


void Table::check_room_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table*)w->data;
	ev_timer_stop(zjh.loop, &table->check_room_timer);
	table->CheckRoomEnd();
}

//检测房间结束
bool Table::CheckRoomEnd()
{
	//判断房间结束
	bool IsEndRoom = false;
	log.info("[%s] IsEndRoom[%d] tid[%s] .\n", __FUNCTION__ ,IsEndRoom , tid.c_str() );
	if( (IsEndRoom || m_bDissovleRoom))
	{
		m_bDissovleRoom = true;
//		ev_timer_again(zjh.loop, &end_room_timer);
		_tint32 UserScore[GAME_PLAYER] = {0}; //玩牌得分
		//更新数据
		update_user_info_to_datasvr(SERVER_DZ_UPDATE_USER_INFO, UserScore);
	}
	else
	{
		//游戏初始化
		state = GAME_FREE;
		Reset();
		for (int i = 0; i < GAME_PLAYER; i++)
		{
			seats[i].reset();
		}
		ev_timer_again(zjh.loop, &preready_timer);
		m_cbCurTimer = 2;
	}
	return true;
}
//用户出牌
bool Table::OnUserOutCard(Player *player)
{
	if (is_dissolved)
	{
		log.error("Room Dissovled is_dissolved[%d] tid[%s] .\n", is_dissolved, tid.c_str());
		return false;
	}
	proto::game::ReqOutCard stReqOutCard;
	stReqOutCard.ParseFromString(player->client->ppacket.body);
	_uint8 wChairID = player->seatid;
	log.debug("uid[%d] tid[%s] stReqOutCard[%s] .\n", player->uid, tid.c_str(), stReqOutCard.DebugString().c_str());
	vector<stCardInfo> stCardData;  //用户出的牌数据
	vector<_uint16> stCardDataTemp;
	bool bIsOutCardValid = true;

	if (wChairID == m_wBankerUser)
	{
		m_UserWeaveCache.clear();
	}

	if (stReqOutCard.out_card_size() != stReqOutCard.row_size()
		|| stReqOutCard.out_card_size() != stReqOutCard.col_size())
	{
		log.error("On user out card Err: out card[%x] row[%x] col[%x].\n", stReqOutCard.out_card_size(), stReqOutCard.row_size(), stReqOutCard.col_size());
		return false;
	}
	stCardInfo stTemp;
	memset(&m_UserOutCards[wChairID], 0, sizeof(m_UserOutCards[wChairID]));
	for (_uint8 i = 0; i < stReqOutCard.out_card_size(); ++i)
	{
		stTemp.cbCard = stReqOutCard.out_card(i);
		m_UserOutCards[wChairID].cbCardList[m_UserOutCards[wChairID].cbCardCount++] = stTemp.cbCard;
		log.info("On user out card index 0x%x \n", stTemp.cbCard);
		stCardDataTemp.push_back(stTemp.cbCard);
		stCardData.push_back(stTemp);
		
	}

	for (_uint8 i = 0; i < stReqOutCard.row_size(); ++i)
	{
		stCardData[i].cbRow = stReqOutCard.row(i);       //出牌的行下标
		log.info("On user out card cbRow: 0x%x \n", stCardData[i].cbRow);
	}
	for (_uint8 i = 0; i < stReqOutCard.col_size(); ++i)  
	{
		stCardData[i].cbCol = stReqOutCard.col(i);  //出牌的列下标
		log.info("On user out card cbCol: 0x%x \n", stCardData[i].cbCol);
	}
		
	for (_uint8 i = 0; i < stCardData.size(); ++i)
	{
		log.info("cbCard: 0x%x, cbRow: 0x%x, cbCol: 0x%x \n", stCardData[i].cbCard, stCardData[i].cbRow, stCardData[i].cbCol);
	}


	

	printf("stCardDataTemp \n");
	for (_uint8 i = 0; i < stCardDataTemp.size(); ++i)
	{
		log.info("0x%x \n", stCardDataTemp[i]);	
	}


	for (_uint8 i = 0; i < stCardData.size(); ++i)
	{
		if (!m_GameLogic.IsValidCard(stCardData[i]))
		{
			log.error("On user out card cbCardData[%d] error .\n", stCardData[i]);
			return false;
		}
	}

	if (wChairID != m_wCurrentUser || !m_bOutCard || wChairID < 0 || wChairID >= GAME_PLAYER)  //没有轮到出牌的玩家不能出牌
	{
		log.error("On user out card wChairID[%d] m_wCurrentUser[%d] m_bOutCard[%d] error .\n",
				  wChairID, m_wCurrentUser, m_bOutCard);
		return false;
	}

	//每一圈第一次打牌

	//判断玩家出的牌是否符合规则



	if (m_wCurrentUser == m_wBankerUser)
	{
		if (!m_GameLogic.FisrstCardIsValid(stCardDataTemp))
		{
			log.error("On user first out card is invalid error .\n ");
			bIsOutCardValid =  false;
		}
	}
	else
	{
		if (!m_GameLogic.IsValidCardWeaves(m_UserWeaveCache, stCardDataTemp))
		{
			log.error("On user out card is invalid error .\n ");
			bIsOutCardValid = false;
		}
	}

	if (bIsOutCardValid)  //能打则更新赢牌缓存
	{
		m_UserWeaveCache = stCardDataTemp;
	}


	log.info("on user m_UserWeaveCache \n");
	for (_uint8 i = 0; i < m_UserWeaveCache.size(); ++i)
	{
		log.info("0x%x \n", m_UserWeaveCache[i]);
	}

	UpdateCardsWeave(wChairID, stCardData);
	m_cbLeftCardsCount[wChairID] -= stCardData.size();
	//删除扑克
	if (m_GameLogic.RemoveCard(m_cbCardIndex[wChairID], stCardData) == false)
	{
		log.error("On user out card remove stCardData error .\n ");
		return false;
	}
	//更新组合
	
	//广播出牌
	std::map<int, Player *>::iterator iter = players.begin();
	for (; iter != players.end(); ++iter)
	{
		Player *player = iter->second;
		if (NULL == player)
			continue;
		_tint32 wCurChairID = player->seatid;

		proto::game::AckOutCard stOutCard;
		stOutCard.set_seatid(wChairID);
		stOutCard.set_is_valid(bIsOutCardValid);
		for (_uint8 i = 0; i < stCardData.size(); ++i)
		{
			stOutCard.add_out_card(stCardData[i].cbCard);
			log.info("cbCard: %x \n", stCardData[i].cbCard);
		}

		stOutCard.set_out_limit(0);
		if (wCurChairID == wChairID)
		{
			for (_uint8 i = 0; i < m_cbCardsWeaveCount[wCurChairID]; ++i)
			{
				_uint8 cbCountTemp = 0;
				proto::game::tagHandCards *pstHandCards = stOutCard.add_hand_cards();
				log.info("On user out card cbCardCount: %d  \n", m_CardsWeaveInfo[wCurChairID][i].cbCardCount);

				for (_uint8 j = 0; j < m_CardsWeaveInfo[wCurChairID][i].cbCardCount; ++j)
				{
					if (m_CardsWeaveInfo[wCurChairID][i].cbCardList[j] != 0)
					{
						pstHandCards->add_card(m_CardsWeaveInfo[wCurChairID][i].cbCardList[j]);
						log.info("On user out card m_CardsWeaveInfo: 0x%x  \n", m_CardsWeaveInfo[wCurChairID][i].cbCardList[j]);
					}
				}
				log.info("\n");
			}
			log.info("OnUserOutCard, bIsOutCardValid: %d, bIsOutCardValid :%d :%d \n", m_IsBeginPerCircle, bIsOutCardValid);
		}
		if (wCurChairID >= 0 && wCurChairID < GAME_PLAYER)
		{
			stOutCard.set_off_count(m_cbOfflineCount[wCurChairID]);
		}

		
		Ppacket ppack;
		stOutCard.SerializeToString(&ppack.body);
		ppack.pack(SERVER_PHZ_OUT_CARD_RES);
		unicast(player, ppack.data);
		log.debug("uid[%d] tid[%s] stOutCard[%s] .\n", player->uid, tid.c_str(), stOutCard.DebugString().c_str());
		//保存离线数据
		save_offline_info(wCurChairID, SERVER_PHZ_OUT_CARD_RES, stOutCard.SerializeAsString());
	}

	log.info("On user out card Succ wChairID[%d] uid[%d]  tid[%s] .\n", wChairID, seats[wChairID].uid,  tid.c_str());

	//设置变量
	m_bFirstCard = false;
	m_bOutCard = false;
	m_bDispatch = false;
	m_bCardOperated = false;
	m_wCurrentUser = wChairID;
	//m_cbCurrentCard = cbCardData;
	m_wOutCardUser = wChairID;
	//m_cbOutCardData = cbCardData;
	//记录打牌次数
	m_UserOutCardCount[wChairID]++;
	
	_uint8 m_wNextUser = (m_wCurrentUser+1) % GAME_PLAYER;


	if (m_wNextUser == m_wBankerUser)
	{
		m_IsBeginPerCircle = true;
	}

	if (m_wNextUser != m_wBankerUser
		&& !CompareCard(stCardDataTemp, m_wNextUser))
	{
		m_UserCanOutCard[m_wNextUser] = false;
		SendOutCardNotifyOnUnicast(m_wNextUser, stCardDataTemp);
		ev_timer_again(zjh.loop, &check_user_can_out_card_timer);
	}
	else
	{
		ev_timer_again(zjh.loop, &out_delay_timer);
		m_cbCurTimer = 6;
	}

	//保存录像
	save_out_card_video(wChairID, stCardData);
	//保存数据到redis
	SerializeTableData();
	return true;
}


//单操作
bool Table::DoSingleOperate(_tint32 wTargetUser, _uint8 cbTargetAction)
{
	log.info("Do single operate wTargetUser[%d] uid[%d] cbTargetAction[%d] tid[%s].\n", wTargetUser, seats[wTargetUser].uid, cbTargetAction, tid.c_str());
	switch (cbTargetAction)
	{
	case ACK_CHIHU:
	case ACK_HUANG:
	{
		GameEnd(wTargetUser, cbTargetAction);
	}
	break;
	default:
		break;
	}
	return true;
}

//多操作
bool Table::DoMultiOperate(_tint32 wTargetUser, _uint8 cbTargetAction)
{
	log.info("Do multi operate wTargetUser[%d] uid[%d] cbTargetAction[%d] tid[%s] .\n", wTargetUser, seats[wTargetUser].uid, cbTargetAction, tid.c_str());
	//操作过牌
	if (cbTargetAction == ACK_NULL)
	{
		//判断最优
		_tint32 wFirstUser = INVALID_CHAIR;
		bool bCanOperate = IsFirstUser(wTargetUser, wFirstUser);
		//预操作提示
		if (!bCanOperate && wFirstUser != INVALID_CHAIR)
		{
			if (seats[wFirstUser].player != NULL)
			{
				Ppacket ppack;
				ppack.pack(SERVER_PHZ_PRE_OPERATE_NOTIFY);
				unicast(seats[wFirstUser].player, ppack.data);
			}
		}
		log.info(" Do multi operate wTargetUser[%d] cbTargetAction[0x%02x] bCanOperate[%d] wFirstUser[%d] tid[%s] .\n", wTargetUser, cbTargetAction, bCanOperate, wFirstUser, tid.c_str());
	}
	//处理操作优先级
	_tint32 cbSortChairID = GAME_PLAYER;
	_uint32 wSortCodes[GAME_PLAYER] = {0};
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		_tint32 wTempChairID = (m_wCurrentUser + i) % GAME_PLAYER;
		if (m_bUserAction[wTempChairID] == ACK_NULL)
			continue;
		_uint8 cbCode = 0;
		if (!m_bResponse[wTempChairID]) //如果没有操作，取出最优操作
		{
			if (cbCode == 0 && m_bUserAction[wTempChairID] & ACK_CHIHU)
				cbCode = ACK_CHIHU;
			else if (cbCode == 0 && m_bUserAction[wTempChairID] & ACK_HUANG)
				cbCode = ACK_HUANG;
		}
		else if (m_bResponse[wTempChairID] && m_bPerformAction[wTempChairID] != ACK_NULL) //操作过后取操作的
		{
			cbCode = m_bPerformAction[wTempChairID];
		}
		wSortCodes[wTempChairID] = (cbCode * 10 + cbSortChairID) * 10 + wTempChairID;
		if (m_bResponse[wTempChairID] && m_bPerformAction[wTempChairID] == ACK_NULL)
			wSortCodes[wTempChairID] = 0;
		cbSortChairID--;
	}
	//排序
	for (_uint8 m = 0; m < m_GamePlayer - 1; ++m)
	{
		for (_uint8 n = m + 1; n < m_GamePlayer; ++n)
		{
			if (wSortCodes[m] < wSortCodes[n])
			{
				_uint32 cbTemp = wSortCodes[m];
				wSortCodes[m] = wSortCodes[n];
				wSortCodes[n] = cbTemp;
			}
		}
	}
	//判断最优
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		if (wSortCodes[i] == 0)
			continue;
		_tint32 wTempChairID = wSortCodes[i] % 10;
		if (!m_bResponse[wTempChairID])
			break;
		if (m_bResponse[wTempChairID] && m_bPerformAction[wTempChairID] != ACK_NULL)
		{
			if (m_bPerformAction[wTempChairID] == ACK_CHIHU 
				|| m_bPerformAction[wTempChairID] == ACK_HUANG)
			{
			//	GameEnd(wTempChairID);
				return true;
			}
		}
	}

	return false;
}

//用户预操作
//bool Table::OnUserPreOperateCard(Player *player)
//{
//	proto::game::ReqPreOperate stReqPreOp;
//	stReqPreOp.ParseFromString(player->client->ppacket.body);
//	log.debug("uid[%d] tid[%s] stReqPreOp[%s] .\n", player->uid, tid.c_str(), stReqPreOp.DebugString().c_str());
//	_uint8 cbOperateCode = stReqPreOp.operate_type(); //动作代码
//	_tint32 wChairID = player->seatid;
//	log.info("on user pre operate para wChairID[%d] uid[%d] cbOperateCode[0x%02x] tid[%s] .\n", wChairID, seats[wChairID].uid, cbOperateCode, tid.c_str());
//	if (wChairID < 0 || wChairID >= m_GamePlayer)
//	{
//		log.error("on user pre operate card error wChairID[%d] wrong.\n", wChairID);
//		return false;
//	}
//
//	if ((m_bUserAction[wChairID] == ACK_NULL) || (m_bResponse[wChairID] == true) || ((cbOperateCode != ACK_NULL) && (m_bUserAction[wChairID] & cbOperateCode) == 0))
//	{
//		log.error("on user operate card error wChairID[%d] m_bResponse[%d] m_bUserAction[0x%02x] cbOperateCode[0x%02x] tid[%s] .\n", wChairID, m_bResponse[wChairID], m_bUserAction[wChairID], cbOperateCode, tid.c_str());
//		return false;
//	}
//
//	m_bUserAction[wChairID] = cbOperateCode;
//	//操作过直接成功
//	if (cbOperateCode == ACK_NULL)
//	{
//		m_UserOutCardIndex++;
//		proto::game::AckPreOperate stAckPreOp;
//		stAckPreOp.set_operate_type(m_bUserAction[wChairID]);
//		stAckPreOp.set_can_operate(true);
//		Ppacket ppack;
//		stAckPreOp.SerializeToString(&ppack.body);
//		ppack.pack(SERVER_PHZ_PRE_OPERATE_RES);
//		unicast(player, ppack.data);
//		return true;
//	}
//	//判断最优
//	_tint32 wFirstUser = INVALID_CHAIR;
//	bool bCanOperate = IsFirstUser(wChairID, wFirstUser);
//	log.info("on user pre operate wChairID[%d] uid[%d] cbOperateCode[0x%02x] bCanOperate[%d] wFirstUser[%d] tid[%s] .\n", wChairID, seats[wChairID].uid, cbOperateCode, bCanOperate, wFirstUser, tid.c_str());
//	if (bCanOperate)
//	{
//		OnUserOperateCard(player);
//	}
//	else
//	{
//		//预操作返回
//		proto::game::AckPreOperate stAckPreOp;
//		stAckPreOp.set_operate_type(m_bUserAction[wChairID]);
//		stAckPreOp.set_can_operate(bCanOperate);
//		Ppacket ppack;
//		stAckPreOp.SerializeToString(&ppack.body);
//		ppack.pack(SERVER_PHZ_PRE_OPERATE_RES);
//		unicast(player, ppack.data);
//		log.debug("uid[%d] tid[%s] stAckPreOp[%s] .\n", player->uid, tid.c_str(), stAckPreOp.DebugString().c_str());
//		//预操作提示
//		if (!bCanOperate && wFirstUser != INVALID_CHAIR)
//		{
//			if (seats[wFirstUser].player != NULL)
//			{
//				Ppacket ppack;
//				ppack.pack(SERVER_PHZ_PRE_OPERATE_NOTIFY);
//				unicast(seats[wFirstUser].player, ppack.data);
//			}
//		}
//	}
//	//保存数据到redis
//	SerializeTableData();
//	return true;
//}

//是否为最优玩家, 返回最优玩家
bool Table::IsFirstUser(_tint32 wChairID, _tint32 &wFirstUser)
{
	//处理操作优先级
	_tint32 cbSortChairID = GAME_PLAYER;
	_uint32 wSortCodes[GAME_PLAYER] = {0};
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		_tint32 wTempChairID = (m_wCurrentUser + i) % GAME_PLAYER;
		if (m_bUserAction[wTempChairID] == ACK_NULL)
			continue;
		_uint8 cbCode = 0;
		if (!m_bResponse[wTempChairID]) //如果没有操作，取出最优操作
		{
			if (cbCode == 0 && m_bUserAction[wTempChairID] & ACK_CHIHU)
				cbCode = ACK_CHIHU;
			else if (cbCode == 0 && m_bUserAction[wTempChairID] & ACK_HUANG)
				cbCode = ACK_HUANG;
		}
		wSortCodes[wTempChairID] = (cbCode * 10 + cbSortChairID) * 10 + wTempChairID;
		if (m_bResponse[wTempChairID] && m_bPerformAction[wTempChairID] == ACK_NULL)
			wSortCodes[wTempChairID] = 0;
		cbSortChairID--;
	}
	//排序
	for (_uint8 m = 0; m < GAME_PLAYER - 1; ++m)
	{
		for (_uint8 n = m + 1; n < GAME_PLAYER; ++n)
		{
			if (wSortCodes[m] < wSortCodes[n])
			{
				_uint32 cbTemp = wSortCodes[m];
				wSortCodes[m] = wSortCodes[n];
				wSortCodes[n] = cbTemp;
			}
		}
	}
	//判断最优
	bool bCanOperate = false;
	for (_uint8 i = 0; i < m_GamePlayer; ++i)
	{
		if (wSortCodes[i] == 0)
			continue;
		wFirstUser = wSortCodes[i] % 10;
		if (wFirstUser == wChairID)
			bCanOperate = true;
		break;
	}

	return bCanOperate;
}
//用户操作
bool Table::OnUserOperateCard(Player *player)
{
	if (is_dissolved)
	{
		log.error("Room Dissovled is_dissolved[%d] tid[%s] .\n", is_dissolved, tid.c_str());
		return false;
	}
	proto::game::ReqOperateCard stReqOp;
	stReqOp.ParseFromString(player->client->ppacket.body);
	log.debug("uid[%d] tid[%s] stReqOp[%s] .\n", player->uid, tid.c_str(), stReqOp.DebugString().c_str());

	_uint8 cbOperateCode = stReqOp.operate_type(); //动作代码

	for (_uint8 i = 0; i < stReqOp.win_weaves_size(); ++i)
	{
		 m_wPreUserCards.push_back(stReqOp.win_weaves(i));
		 log.debug("OnUserOperateCard: m_wPreUserCards: 0x%x", stReqOp.win_weaves(i));
	}


	_tint32 wChairID = player->seatid;
	log.info("on user operate card para wChairID[%d] uid[%d] cbOperateCode[0x%02x]  tid[%s] .\n", wChairID, seats[wChairID].uid, cbOperateCode, tid.c_str());
	if (wChairID < 0 || wChairID >= GAME_PLAYER)
	{
		log.error("on user operate card error wChairID[%d] wrong.\n", wChairID);
		return false;
	}

	//保存操作信息
	_uint8 cbTargetAction = cbOperateCode;
	_tint32 wTargetUser = wChairID;
	m_bResponse[wChairID] = true;

	DoSingleOperate(wTargetUser, cbTargetAction);
	

	//保存数据到redis
	SerializeTableData();
	return true;
}

//派发扑克
//bool Table::DispatchCardData(_tint32 wCenterUser)
//{
//	if (is_dissolved)
//	{
//		log.error("Room Dissovled is_dissolved[%d] tid[%s] .\n", is_dissolved, tid.c_str());
//		return false;
//	}
//	if (wCenterUser == INVALID_CHAIR)
//	{
//		log.error("DispatchCardData wCenterUser[%d] is invalid . \n", wCenterUser);
//		return false;
//	}
//
//	if (m_bLeftCardCount == 0)
//	{
//		GameEnd(INVALID_CHAIR);
//		return true;
//	}
//
//	_uint8 bSendCardData = m_cbRepertoryCard[--m_bLeftCardCount];
//
//	//广播翻牌
//	std::map<int, Player *>::iterator iter = players.begin();
//	for (; iter != players.end(); ++iter)
//	{
//		Player *player = iter->second;
//		if (NULL == player)
//			continue;
//		_tint32 wCurChairID = player->seatid;
//
//		proto::game::AckDispatchCard stDispachCard;
//		stDispachCard.set_seatid(wCenterUser);
//		stDispachCard.set_card(bSendCardData);
//	
//	//	stDispachCard.set_left_card_count(m_bLeftCardCount);
//		if (wCurChairID >= 0 && wCurChairID < m_GamePlayer)
//		{
//			stDispachCard.set_off_count(m_cbOfflineCount[wCurChairID]);
//		}
//		Ppacket ppack;
//		stDispachCard.SerializeToString(&ppack.body);
//		ppack.pack(SERVER_PHZ_SEND_CARD);
//		unicast(player, ppack.data);
//		log.debug("uid[%d] tid[%s] stDispachCard[%s] .\n", player->uid, tid.c_str(), stDispachCard.DebugString().c_str());
//		//保存离线数据
//		save_offline_info(wCurChairID, SERVER_PHZ_SEND_CARD, stDispachCard.SerializeAsString());
//	}
//	log.info("dispatch card data seatid[%d] uid[%d] card[0x%02x] tid[%s]. \n", wCenterUser, seats[wCenterUser].uid, bSendCardData, tid.c_str());
//	//设置变量
//	m_bFirstCard = false;
//	m_bDispatch = true;
//	m_bCardOperated = false;
//	m_wCurrentUser = wCenterUser;
//	//m_cbCurrentCard = bSendCardData;
//
//	//动作判断
//	ev_timer_again(zjh.loop, &dispatch_delay_timer);
//	m_cbCurTimer = 5;
//	//保存录像
//	save_dispatch_card_video(wCenterUser, bSendCardData);
//	//保存数据到redis
//	SerializeTableData();
//	return true;
//}

//出牌提示
bool Table::SendOutCardNotify(_tint32 wCurrentUser, bool bOutCard)
{
	log.info("SendOutCardNotify \n");
	if (wCurrentUser == INVALID_CHAIR)
	{
		log.error("SendOutCardNotify wCurrentUser[%d] error .\n", wCurrentUser);
		return false;
	}

	/*Player *player = seats[wCurrentUser].player;111
	if ((player == NULL) || (m_bUserAction[wCurrentUser] == ACK_NULL))
	{
		return -1;
	}*/
	//设置变量
	m_bOutCard = true;
	m_wCurrentUser = wCurrentUser;

	//发送数据
	proto::game::AckOutNotify stOutNotify;
	stOutNotify.set_seatid(wCurrentUser);
	stOutNotify.set_is_out_card(m_bOutCard);
	stOutNotify.set_off_count(m_cbOfflineCount[wCurrentUser]);
	stOutNotify.set_can_out_card(true);

	//for (_uint8 i = 0; i < m_UserWeaveCache.size(); ++i)
	//{
	//	log.info("m_UserWeaveCache: %x \n", m_UserWeaveCache[i]);
	//	stOutNotify.add_win_weaves(m_UserWeaveCache[i]);
	//}	
	
	
	Ppacket ppack;
	stOutNotify.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_OUT_CARD_NOTIFY);
	broadcast(NULL, ppack.data);
	//unicast(player, ppack.data);
	log.debug("uid[%d] tid[%s] stOutNotify[%s] .\n", m_wCurrentUser, tid.c_str(), stOutNotify.DebugString().c_str());
	log.info("send out card notify wCurrentUser[%d] bOutCard[%d] tid[%s] .\n", wCurrentUser, bOutCard, tid.c_str());

	return true;
}



bool Table::SendOutCardNotifyOnUnicast(_tint32 wCurrentUser, vector<_uint16>& cbCenterCards)
{
	log.info("SendOutCardNotifyOnUnicast wCurrentUser %d \n", wCurrentUser);
	if (wCurrentUser == INVALID_CHAIR)
	{
		log.error("SendOutCardNotifyOnUnicast wCurrentUser[%d] error .\n", wCurrentUser);
		return false;
	}

	/*Player *player = seats[wCurrentUser].player;
	if (player == NULL)
	{
		log.error("player: %p, %p  \n", player, m_bUserAction[wCurrentUser]);
		return false;
	}*/
	//设置变量
	m_bOutCard = true;
	m_wCurrentUser = wCurrentUser;

	//发送数据
	proto::game::AckOutNotify stOutNotify;
	stOutNotify.set_seatid(wCurrentUser);
	stOutNotify.set_is_out_card(m_bOutCard);
	stOutNotify.set_off_count(m_cbOfflineCount[wCurrentUser]);
	//stOutNotify.set_is_begin_per_circle(m_IsBeginPerCircle);
	stOutNotify.set_can_out_card(m_UserCanOutCard[wCurrentUser]);

	log.info("SendOutCardNotifyOnUnicast, m_UserCanOutCard: %d \n", m_UserCanOutCard[wCurrentUser]);
	for (_uint8 i = 0; i < cbCenterCards.size(); ++i)
	{
		log.info("SendOutCardNotifyOnUnicast, cbCenterCards: %x \n", cbCenterCards[i]);
		stOutNotify.add_win_weaves(cbCenterCards[i]);
	}


	Ppacket ppack;
	stOutNotify.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_OUT_CARD_NOTIFY);
	broadcast(NULL, ppack.data);
	//unicast(player, ppack.data);
	log.debug("uid[%d] tid[%s] stOutNotify[%s] .\n", m_wCurrentUser, tid.c_str(), stOutNotify.DebugString().c_str());
	log.info("send out card notify wCurrentUser[%d] tid[%s] .\n", wCurrentUser, tid.c_str());

	return true;



}


bool Table::SendOutCircleEndNotifyOnBroadCast(_tint32 wCurrentUser, vector<_uint16>& cbCenterCards)
{
	
	//发送数据
	proto::game::AckCircleEnd stCircleNotify;

	log.info("SendOutCircleEndNotifyOnBroadCast m_IsBeginPerCircle: %d \n", m_IsBeginPerCircle);
	stCircleNotify.set_is_circle_end(m_IsBeginPerCircle);
	stCircleNotify.set_seatid(wCurrentUser);
	proto::game::tagWeaveCards *pstWeaveCards = stCircleNotify.add_user_win_weaves();
	if (m_IsBeginPerCircle)  //一圈打完将将牌放置用户赢牌区
	{
		for (_uint8 i = 0; i < cbCenterCards.size(); ++i)
		{
			if (cbCenterCards[i] != 0)
			{
				pstWeaveCards->add_card_list(cbCenterCards[i]);
				log.info("On user out card m_WeaveItemArray: 0x%x  \n", cbCenterCards[i]);
			}
		}
	}
	//cbCenterCards.clear();
	Ppacket ppack;
	stCircleNotify.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_CYCLE_END);
	broadcast(NULL, ppack.data);
	return true;

}


//派发响应判断
bool Table::DispatchEstimateUserRespond(_tint32 wCenterUser, _uint8 cbCenterCard)
{
	return true;
}

//打牌响应判断
bool Table::OutEstimateUserRespond(_tint32 wCenterUser, vector<_uint16>& cbCenterCards)
{
	log.info("out estimate user respond para wCenterUser[%d]  tid[%s].\n", wCenterUser, tid.c_str());
	
	//判断天胡
	//判断玩家手上的牌能不能打， 不能打直接过，打完一圈算息， 谁赢的牌放在谁的赢牌区
//	memset(m_bUserAction, 0, sizeof(m_bUserAction));
	bool bAction = false;
	_uint8 cbSecondUser = (wCenterUser + 1) % GAME_PLAYER;
	_uint8 cbThirdUser = (cbSecondUser+1) % GAME_PLAYER;
	_uint8 m_wNextUser = cbSecondUser;
	_uint8 cbWinUser = INVALID_CHAIR;
	_uint8 cbTotalCards[3] = {0};
	_uint8 cbUserTotalCards = 0;
	_tint32 wResult = -1;

	//CompareCard(wCenterUser, cbCenterCards); 
	if (!cbCenterCards.size())
	{
		log.error("OutEstimateUserRespond, cbCenterCards is null \n");
		return false;
	}

	if(m_wNextUser == m_wBankerUser)
	{
		OutEstimateCircleEndRespond(wCenterUser, cbCenterCards);
			
	}
	else
	{
		m_wNextUser = (m_wNextUser + 1) % GAME_PLAYER;
		OutEstimateCireleNoEndRespond(wCenterUser, cbCenterCards);		
	}
	
	log.info("OutEstimateUserRespond,m_wNextUser: %d  m_wBankerUser %d wCenterUser: %d \n", m_wNextUser, m_wBankerUser, wCenterUser);
	
	//每次打牌后都要判断是不是小于最小和牌数


	log.info("OutEstimateUserRespond, m_IsBeginPerCircle: %d \n", m_IsBeginPerCircle);


	return true;
}

bool Table::OutEstimateCircleEndRespond(_tint32 wCenterUser, vector<_uint16>& cbCenterCards)
{

	_tint32  wSecondUser = (m_wNextUser + 1) % GAME_PLAYER;
	_tint32  wThirdUser = (wSecondUser + 1) % GAME_PLAYER;

	memset(m_UserOutCards, 0, sizeof(m_UserOutCards));
	log.info("OutEstimateUserRespond, pre m_bWeaveItemCount: %d \n", m_bWeaveItemCount[wCenterUser]);
	m_wLastUser = wCenterUser;
	SendOutCircleEndNotifyOnBroadCast(wCenterUser, cbCenterCards);//清理打出的牌
	if (cbCenterCards.size())
	{
		for (_uint8 i = 0; i < cbCenterCards.size(); ++i)
		{
			m_WeaveItemArray[wCenterUser][m_bWeaveItemCount[wCenterUser]].cbCardList[i] = cbCenterCards[i];
			m_WeaveItemArray[wCenterUser][m_bWeaveItemCount[wCenterUser]].cbCardCount++;
			log.info("OutEstimateUserRespond, cbCenterCards: %d \n", cbCenterCards[i]);
		}
		m_bWeaveItemCount[wCenterUser]++;
		m_bTotalWinCardsCount[wCenterUser] += cbCenterCards.size();
	}

	//一圈打完判断黄庄
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		_uint8 cbUserTotalCards = 0;
		for (_uint8 j = 0; j < m_cbCardsWeaveCount[i]; ++j)      //如果达到基本和牌数强制和牌
		{
			cbUserTotalCards += m_CardsWeaveInfo[i][j].cbCardCount;
		}
		log.info("OutEstimateUserRespond: total cards : %d \n", cbUserTotalCards);
		if (cbUserTotalCards <= 3)
		{
			return GameEnd(i, ACK_HUANG);
		}
	}

	for (_uint8 i = 0; i < m_bWeaveItemCount[wCenterUser]; ++i)
	{
		for (_uint8 j = 0; j < m_WeaveItemArray[wCenterUser][i].cbCardCount; ++j)
		{
			log.info("OutEstimateUserRespond, cur cbCenterCards: %d \n", m_WeaveItemArray[wCenterUser][i].cbCardList[j]);
		}

	}

	log.info("OutEstimateUserRespond,cur m_bWeaveItemCount: %d \n", m_bWeaveItemCount[wCenterUser]);

	if (m_GamePlay == TIANHU)
	{
		if (m_wNextUser == m_wBankerUser &&	!m_bWeaveItemCount[wSecondUser] && !m_bWeaveItemCount[wThirdUser] && m_bWeaveItemCount[m_wNextUser] >= 16)
		{
			m_bIsTianHuShow = true;
		}
	}

	_uint8 cbTotalCards = 0;
	for (_uint8 i = 0; i < m_bWeaveItemCount[m_wBankerUser]; ++i)
	{
		cbTotalCards += m_WeaveItemArray[m_wBankerUser][i].cbCardCount;
		for (_uint8 j = 0; j < m_WeaveItemArray[m_wBankerUser][i].cbCardCount; ++j)
		{
			log.info("GetHuCardInfoFinal cbCardList: %x, group %d \n", m_WeaveItemArray[m_wBankerUser][i].cbCardList[j], i);
		}

	}

	_tint32 wResult = m_GameLogic.isHuOrHeCards(m_bTotalWinCardsCount[m_wBankerUser]);
	//wResult = m_GameLogic.GetHuCardInfoFinal(cbTotalCards, m_bWeaveItemCount[m_wBankerUser], m_wBankerUser, m_wUserHuXi, m_wUserFanShu, m_wUserScore,  m_WeaveItemArray[m_wBankerUser], m_BaseScore, m_GamePlay);
	if (wResult == -1)
	{
		SendOutCardNotifyOnUnicast(m_wBankerUser, cbCenterCards);
	}
	else
	{
		if (wResult == ACK_HUANG)
		{
			m_bUserAction[m_wBankerUser] |= ACK_HUANG;
		}
		else if (wResult == ACK_CHIHU || m_bIsTianHuShow)
		{

			m_bUserAction[m_wBankerUser] |= ACK_CHIHU;
			m_bUserAction[m_wBankerUser] |= ACK_HUANG;
		}
		SendNotifyToUsrByCID(m_wBankerUser, cbCenterCards);
		save_operate_notify_video();
	}
	log.info("OutEstimateUserRespond, wResult: %d \n", wResult);
	log.info("GetHuCardInfoFinal: cbUserID: %d, secUserID %d, ThirdUserId: %d \n", m_wUserScore[0], m_wUserScore[1], m_wUserScore[2]);
	log.info("GetHuCardInfoFinal: cbUserFan: %d, secUserFan %d, ThirdUserFan: %d \n", m_wUserFanShu[0], m_wUserFanShu[1], m_wUserFanShu[2]);
	//更新胡息

	//广播赢牌区
	//判断玩家是否胡牌
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		m_UserCanOutCard[i] = true;
	}
	log.info("B OutEstimateUserRespond: wCenterUser: %d, m_wNextUser： %d , wResult: %d \n", wCenterUser, m_wNextUser, wResult);
}


bool Table::OutEstimateCireleNoEndRespond(_tint32 wCenterUser, vector<_uint16>& cbCenterCards)
{

		//判断下家的牌是否可以可胡

		m_IsBeginPerCircle = false;    //与上家的牌做比较， 如果没有没有出的， 直接过		

		_uint8 cbTotalCards = 0;
		for (_uint8 i = 0; i < m_bWeaveItemCount[m_wNextUser]; ++i)
		{
			cbTotalCards += m_WeaveItemArray[m_wNextUser][i].cbCardCount;
			for (_uint8 j = 0; j < m_WeaveItemArray[m_wNextUser][i].cbCardCount; ++j)
			{
				log.info("GetHuCardInfoFinal cbCardList: %x, group %d \n", m_WeaveItemArray[m_wNextUser][i].cbCardList[j], i);
			}
		}
		cbTotalCards += cbCenterCards.size();

		//	wResult = m_GameLogic.GetHuCardInfoFinal(cbTotalCards, m_bWeaveItemCount[m_wNextUser], m_wNextUser, m_wUserHuXi, m_wUserFanShu, m_wUserScore,
		//						 m_WeaveItemArray[m_wNextUser], m_BaseScore, m_GamePlay);     //此处还有问题
		_tint32 wResult = m_GameLogic.isHuOrHeCards(cbTotalCards);
		if (wResult == -1)
		{
			SendOutCardNotifyOnUnicast(m_wNextUser, cbCenterCards);
		}
		else
		{
			if (wResult == ACK_HUANG)
			{
				m_bUserAction[m_wNextUser] |= ACK_HUANG;
			}
			else if (wResult == ACK_CHIHU || m_bIsTianHuShow)
			{

				m_bUserAction[m_wNextUser] |= ACK_CHIHU;
				m_bUserAction[m_wNextUser] |= ACK_HUANG;
			}
			SendNotifyToUsrByCID(m_wNextUser, cbCenterCards);
			save_operate_notify_video();
		}

		log.info("C OutEstimateUserRespond: wCenterUser: %d, m_wNextUser： %d , wResult: %d \n", wCenterUser, m_wNextUser, wResult);

}


bool Table::CompareCard(vector<_uint16>& cbCenterCards, _tint32 wXiaID)
{
	_uint8 cbCardType_1 = 0;
	_uint8 cbCardType_2 = 0;
	_uint8 cbCardIndex = 0;

	if (!cbCenterCards.size())
	{
		log.error("CompareCard, cbCenterCards is null \n");
		return false;
	}
	for (_uint8 i = 0; i < cbCenterCards.size(); ++i)
	{
		log.info("CompareCard, cbCenterCards: 0x%x \n", cbCenterCards[i]);
	}

	bool bIsSigle = cbCenterCards.size() == 1;  //是否是单张
	bool bIsSamePoint = false; //同类型点数是否相同
	_uint8 cbCardIndexTemp[CARD_TYPE_1][CARD_TYPE_2][CARD_INDEX];
	memcpy(cbCardIndexTemp, m_cbCardIndex[wXiaID].cbCards, sizeof(m_cbCardIndex[wXiaID].cbCards));

	if (!bIsSigle)
	{
		_uint8 cbPre = (cbCenterCards[0] & 0xF00) >> 8;
		_uint8 cbCur = 0;
		_uint8 i = 1;
		for (; i < cbCenterCards.size(); ++i)
		{
			cbCur = (cbCenterCards[i] & 0xF00) >> 8;
			if (cbPre != cbCur)
			{
				break;
			}
			cbPre = cbCur;
		}
		if (i == cbCenterCards.size())
		{
			bIsSamePoint = true;
		}
	}


	if (bIsSigle || bIsSamePoint)
	{
		_uint8 cbCenterCardNum = cbCenterCards.size();
		cbCardType_1 = (cbCenterCards[0] & 0xF00) >> 8;
		cbCardType_2 = (cbCenterCards[0] & 0x0F0) >> 4;
		cbCardIndex = cbCenterCards[0] & 0x00F;
		if (cbCardType_1 == 0)
		{
			if (cbCardType_2 == 2)
			{
				for (_uint8 j = 0; j < 2; ++j)
				{
					for (_uint8 k = 0; k < CARD_INDEX; ++k)
					{
						if (cbCardIndexTemp[0][j][k] >= cbCenterCardNum)
						{
							return true;
						}
					}
				}
			}
			else if (cbCardType_2 == 1)
			{
				for (_uint8 k = 0; k < CARD_INDEX; ++k)
				{
					log.info("CompareCard cbCardIndexTemp k : %d, cbCenterCardNum: %d \n", cbCardIndexTemp[0][0][k], cbCenterCardNum);
					if (cbCardIndexTemp[0][0][k] >= cbCenterCardNum)
					{
						return true;
					}
				}
			}
			else
			{
				if (cbCardIndex == 0x00C)  //天牌
				{
					return false;
				}
				else if (cbCardIndex == 0x002) //地牌
				{
					log.info("next user 0x00C num :%d \n", cbCardIndexTemp[0][0][12]);
					if (cbCardIndexTemp[0][0][12] >= cbCenterCardNum) //有天九
					{
						return true;
					}
				}
				else
				{
					for (_uint8 k = 0; k < CARD_INDEX; ++k)
					{
						if (cbCardIndexTemp[0][0][k] >= cbCenterCardNum && (k > cbCardIndex || k == 2))
						{
							return true;
						}
					}
				}
			}
		}
		else if (cbCardType_1 == 1 || cbCardType_1 == 2)
		{
			log.info("compare cbCardType_1: %d, cbCardType_2:%d 0x209 = %d\n", cbCardType_1, cbCardType_2, cbCardIndexTemp[2][0][9]);
			if ((cbCenterCards[0] == 0x218 || cbCenterCards[0] == 0x208) && cbCardIndexTemp[2][0][9] > 0)
			{
				if (cbCenterCardNum > cbCardIndexTemp[2][0][9])
				{
					return false;
				}
				return true;
			}
			for (_uint8 k = 0; k < CARD_INDEX; ++k)
			{
				if (cbCardIndexTemp[cbCardType_1][cbCardType_2][k] >= cbCenterCardNum && k > cbCardIndex)
				{
					return true;
				}
			}
		}
	}
	

	if (!bIsSigle && !bIsSamePoint)
	{
		_uint8 cbCardCount = 0;
		std::sort(cbCenterCards.begin(), cbCenterCards.end());


		if (cbCenterCards[0] == 0x00C)  //天
		{
			//cbCardCount = 1;
			//for (_uint8 j = 1; j < cbCenterCards.size(); ++j)
			//{
			//	if (cbCenterCards[j] == 0x109 || cbCenterCards[j] == 0x209 || cbCenterCards[j] == 0x00C)
			//	{
			//		++cbCardCount;
			//	}
			//}
			//if (cbCardIndexTemp[0][0][12] <= 0)
			//{
			//	return false;  //一定要有天牌				
			//}
			//else
			//{
			//	if ((cbCardIndexTemp[0][0][12] + cbCardIndexTemp[1][0][9] + cbCardIndexTemp[2][0][9]) < cbCardCount)
			//	{
			//		return false;
			//	}
			//}
			return false;
		}
		else if (cbCenterCards[0] == 0x002)
		{
			cbCardCount = 1;
			for (_uint8 j = 1; j < cbCenterCards.size(); ++j)
			{
				if (cbCenterCards[j] == 0x208 || cbCenterCards[j] == 0x218 || cbCenterCards[j] == 0x002)
				{
					++cbCardCount;
				}

			}
			if (cbCardIndexTemp[0][0][12] <= 0)
			{
				return false;
			}
	
			
			printf("%d  %d \n", cbCardIndexTemp[0][0][2] + cbCardIndexTemp[2][0][8] + cbCardIndexTemp[2][1][8], cbCardCount);
			if (cbCardIndexTemp[0][0][12] + cbCardIndexTemp[1][0][9] + cbCardIndexTemp[2][0][9] > cbCardCount)
			{
				return true;
			}
			
		}
		else if (cbCenterCards[0] == 0x008)
		{
			cbCardCount = 1;
			for (_uint8 j = 1; j < cbCenterCards.size(); ++j)
			{
				if (cbCenterCards[j] == 0x107 || cbCenterCards[j] == 0x207 || cbCenterCards[j] == 0x008)
				{
					++cbCardCount;
				}

			}

			if (cbCardIndexTemp[0][0][2] <= 0 && cbCardIndexTemp[0][0][12] <= 0)
			{
				return false;
			}
		
			if (((cbCardIndexTemp[0][0][2] + cbCardIndexTemp[2][0][8] + cbCardIndexTemp[2][1][8]) > cbCardCount)
				|| ((cbCardIndexTemp[0][0][12] + cbCardIndexTemp[1][0][9] + cbCardIndexTemp[2][0][9]) > cbCardCount))
			{
				return true;
			}
		}
		else if (cbCenterCards[0] == 0x004)
		{
			cbCardCount = 1;
			for (_uint8 j = 1; j < cbCenterCards.size(); ++j)
			{
				if (cbCenterCards[j] == 0x105 || cbCenterCards[j] == 0x205 || cbCenterCards[j] == 0x004)
				{
					++cbCardCount;
				}

			}
			if (cbCardIndexTemp[0][0][2] <= 0 && cbCardIndexTemp[0][0][12] <= 0 && cbCardIndexTemp[0][0][8] <= 0)
			{
				return false;
			}
		
			if (((cbCardIndexTemp[0][0][2] + cbCardIndexTemp[2][0][8] + cbCardIndexTemp[2][1][8]) > cbCardCount)
				|| ((cbCardIndexTemp[0][0][12] + cbCardIndexTemp[1][0][9] + cbCardIndexTemp[2][0][9]) > cbCardCount)
				|| ((cbCardIndexTemp[0][0][8] + cbCardIndexTemp[1][0][7] + cbCardIndexTemp[2][0][7]) > cbCardCount))
			{
				return true;
			}
			
		}
		else
		{
			return false;
		}

		return false;
	}

	return false;
}


bool Table::CompareCard(_tint32 wCenterUser, vector<_uint16> cbCenterCards)

{
	_uint8 cbCardType_2 = (cbCenterCards[0] & 0x0F0) >> 4;
	_uint8 cbCacheType_1 = (m_UserWeaveCache[0] & 0xF00) >> 8;
	_uint8 cbCacheType_2 = (m_UserWeaveCache[0] & 0x0F0) >> 4;
	_uint8 cbCardIndex = m_UserWeaveCache[0] & 0x00F;
	_uint8 cbCacheIndex = cbCenterCards[0] & 0x00F;
	bool   bIsOverride = false;

	bool bIsSigle = cbCenterCards.size() == 1;  //是否是单张
	bool bIsSamePoint = false; //同类型点数是否相同

	if (!bIsSigle)
	{
		_uint8 cbPre = (cbCenterCards[0] & 0xF00) >> 8;
		_uint8 cbCur = 0;
		_uint8 i = 1;
		for (; i < cbCenterCards.size(); ++i)
		{
			cbCur = (cbCenterCards[i] & 0xF00) >> 8;
			if (cbPre != cbCur)
			{
				break;
			}
			cbPre = cbCur;
		}
		if (i == cbCenterCards.size())
		{
			bIsSamePoint = true;
		}
	}


	if (bIsSigle || bIsSamePoint)
	{

		if (cbCacheType_1 == 0)
		{
			if (cbCacheType_2 == 2)
			{
				if (cbCardType_2 == 0 && cbCardType_2 < 2)
				{
					bIsOverride = true;
				}
			}
			else if (cbCacheType_1 == 1)
			{
				if (cbCardType_2 == 0 && cbCardType_2 < 1)
				{
					bIsOverride = true;
				}
			}
			else
			{
				if (cbCacheIndex == 2) //地牌
				{
					if (cbCardIndex == 12) //有天九
					{
						bIsOverride = true;
					}
				}
				else
				{

					if (cbCardIndex >= cbCacheIndex || cbCardIndex == 2)
					{
						bIsOverride = true;
					}

				}
			}
		}
		else if (cbCacheType_1 == 1 || cbCacheType_2 == 2)
		{
			if (cbCardIndex > cbCacheIndex)
			{
				bIsOverride = true;
			}
		}
	}

	if (!bIsSigle && !bIsSamePoint)
	{
		std::sort(m_UserWeaveCache.begin(), m_UserWeaveCache.end());
		std::sort(cbCenterCards.begin(), cbCenterCards.end());

		if ((m_UserWeaveCache[0] == 0x00C && cbCenterCards[0] == 0x00C)
			|| (m_UserWeaveCache[0] == 0x002 && cbCenterCards[0] == 0x002)
			|| (m_UserWeaveCache[0] == 0x008 && cbCenterCards[0] == 0x008)
			|| (m_UserWeaveCache[0] == 0x004 && cbCenterCards[0] == 0x004))  //天
		{
			if (m_UserWeaveCache.size() < cbCenterCards.size())
			{
				bIsOverride = true;
			}
		}

		if (bIsOverride)
		{
			m_UserWeaveCache = cbCenterCards;
			m_wWinner = wCenterUser;
		}		
	}
	return true;
}



//更新胡息
bool Table::UpdateUserHuXiCount(_tint32 wChairID)
{
	return true;
}

int Table::heart_beat_res(Player *player)
{
	Ppacket ppack;
	ppack.pack(SERVER_HEART_BEAT_RES);
	unicast(player, ppack.data);

	return 0;
}

bool Table::OnUserChangeCard(Player *player)
{
	return true;
}

bool Table::UpdateCommonCardsWeave(_tint32 wChairID)
{
	m_cbCardsWeaveCount[wChairID] = 0;


	memset(m_CardsWeaveInfo[wChairID], 0, sizeof(m_CardsWeaveInfo[wChairID]));

	log.debug("m_cbCardIndex  \n");

	for (_uint8 i = 0; i < CARD_TYPE_1; ++i)
	{
		for (_uint8 j = 0; j < CARD_TYPE_2; ++j)
		{
			for (_uint8 k = 0; k < CARD_INDEX; ++k)
			{
				if (m_cbCardIndex[wChairID].cbCards[i][j][k] != 0)
				{
					log.debug("0x%x   , %d    ", m_GameLogic.SwitchToCard(i, j, k), m_cbCardIndex[wChairID].cbCards[i][j][k]);
				}
			}
			log.debug("\n");
		}
		log.debug("\n");
	}



	m_GameLogic.SettleCommonWeaves(m_cbCardIndex[wChairID], m_CardsWeaveInfo[wChairID], m_cbCardsWeaveCount[wChairID]);
	return true;
}

bool Table::UpdateBestCardsWeave(_tint32 wChairID)
{
	return true;
}

bool Table::OnUserUpdateCard(Player *player)
{
	if (player->seatid < 0 || player->seatid >= GAME_PLAYER)
	{
		log.info("OnUserUpdateCard error uid[%d] seatid[%d] .\n", player->uid, player->seatid);
		return false;
	}
	_tint32 wChairID = player->seatid;
	m_bCommonOrBest[wChairID] = (m_bCommonOrBest[wChairID] == true) ? false : true;
	UpdateBestCardsWeave(wChairID);

	proto::game::AckUpdateCard stUpdate;
	if (m_bCommonOrBest[wChairID] == false)
	{
		for (_uint8 i = 0; i < m_cbCardsWeaveCount[wChairID]; ++i)
		{
			proto::game::tagHandCards *pstHandCards = stUpdate.add_hand_cards();
			pstHandCards->set_huxi(m_GameLogic.GetWeaveHuXi(m_CardsWeaveInfo[wChairID][i]));
			for (_uint8 j = 0; j < m_CardsWeaveInfo[wChairID][i].cbCardCount; ++j)
			{
				pstHandCards->add_card(m_CardsWeaveInfo[wChairID][i].cbCardList[j]);
			}
		}
	}
	else
	{
		for (_uint8 i = 0; i < m_cbBestWeaveCount[wChairID]; ++i)
		{
			proto::game::tagHandCards *pstHandCards = stUpdate.add_hand_cards();
			pstHandCards->set_huxi(m_GameLogic.GetWeaveHuXi(m_BestWeaveInfo[wChairID][i]));
			for (_uint8 j = 0; j < m_BestWeaveInfo[wChairID][i].cbCardCount; ++j)
			{
				pstHandCards->add_card(m_BestWeaveInfo[wChairID][i].cbCardList[j]);
			}
		}
	}

	Ppacket ppack;
	stUpdate.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_UPDATE_CARD_RES);
	unicast(player, ppack.data);
	log.debug("uid[%d] tid[%s] stUpdate[%s] .\n", player->uid, tid.c_str(), stUpdate.DebugString().c_str());

	return true;
}

bool Table::UpdateCardsWeave(_tint32 wChairID, vector<stCardInfo>& cbRemoveCards)
{
	if (m_cbCardsWeaveCount[wChairID] == 0)
	{
		log.error("UpdateCardsWeave error cbCardsWeaveCount[%d] wrong .\n", m_cbCardsWeaveCount[wChairID]);
		return false;
	}

	if (!m_GameLogic.UpdateCardsWeave(m_CardsWeaveInfo[wChairID], m_cbCardsWeaveCount[wChairID], cbRemoveCards))
	{
		log.error("UpdateCardsWeave error .\n");
		return false;
	}
	
	
	//m_GameLogic.UpdateCardsWeave(m_BestWeaveInfo[wChairID], m_cbBestWeaveCount[wChairID], cbRemoveCards);

	//tagCardsWeave WeaveItem[MAX_INDEX];
	//memset(WeaveItem, 0, sizeof(tagCardsWeave) * MAX_INDEX);
	//m_GameLogic.SettleBestWeaves(m_cbCardIndex[wChairID], WeaveItem, cbWeaveCount);
	return true;
}

void Table::user_offline(Player *player)
{
	//检测是否所有玩家都已经断线
	bool bIsAll = true;
	map<int, Player *>::iterator iter = players.begin();
	for (; iter != players.end(); iter++)
	{
		Player *player = iter->second;
		if (player)
		{
			if (player->client != NULL)
			{
				bIsAll = false;
				break;
			}
		}
	}
	if (bIsAll)
	{
		Jpacket packet;
		packet.val["cmd"] = SERVER_ALL_PLAYER_DOWN;
		packet.val["vid"] = zjh.game->server_vid;
		packet.val["roomid"] = player->tid;
		packet.end();
		zjh.game->send_to_datasvr(packet.tostring());
	}
}

int Table::advance_game_end()
{
	log.debug("advance game_end\n");
	state = GAME_END;
	ev_timer_stop(zjh.loop, &start_timer);
	ev_timer_stop(zjh.loop, &preready_timer);
	ev_timer_stop(zjh.loop, &dispatch_show_timer);
	ev_timer_stop(zjh.loop, &out_show_timer);
	ev_timer_stop(zjh.loop, &dissolve_room_timer);
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		if (seats[i].player != NULL)
			seats[i].player->down_tag = 1;
	}
	is_dissolved = 1;
	m_cbCurTimer = 0;
	return 0;
}

int Table::handler_dissolve_room(Player *player)
{
	if (dissovle_state == 1 || player->seatid < 0 || player->seatid >= GAME_PLAYER || is_dissolved == 1)
	{
		log.error("apply dissovling room error uid[%d] seatid[%d] dissovle_state[%d] is_dissolved[%d] tid[%s] .\n", player->uid, player->seatid, dissovle_state, is_dissolved, tid.c_str());
		return -1;
	}

	//如果是房主申请解散，并且房间状态不是进行中，直接解散房间
	//if( m_cbRoomStatus != 1 && player->uid == (int)m_wRoomUserId )
	if (m_cbRoomStatus != 1) //房间不是进行中，就直接解散
	{
		proto::game::AckDissolveResult stResult;
		stResult.set_result(1);
		Ppacket ppack;
		stResult.SerializeToString(&ppack.body);
		ppack.pack(SERVER_DISSOLVE_ROOM_RESULT_BC);
		broadcast(NULL, ppack.data);
		//发送给平台
		Jpacket datapac;
		datapac.val["cmd"] = SERVER_DZ_DISSOLVE_ROOM_REQ;
		datapac.val["roomid"] = tid;
		datapac.val["vid"] = vid;
		datapac.val["innings"] = m_strInnings;
		datapac.end();
		zjh.game->send_to_datasvr(datapac.tostring());
		dissovle_state = 0;
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			if (seats[i].player != NULL)
				seats[i].player->dissovle_state = 2;
		}
		log.info("handler dissolve room player[%d] apply dissolve room[%s] \n", player->uid, tid.c_str());
		return 0;
	}

	if (player->dissolve_cnt >= 2)
	{
		proto::game::AckDissolveErr stErr;
		stErr.set_code(101);
		Ppacket ppack;
		stErr.SerializeToString(&ppack.body);
		ppack.pack(SERVER_APPLY_DISSOLVE_ROOM_ERR_UC);
		unicast(player, ppack.data);
		return 0;
	}

	player->dissolve_cnt++;
	dissovle_state = 1;
	dissolve_applyer = player->uid;
	voters_players.clear();

	log.info("handler dissolve room player[%d] apply dissolve room[%s] \n", player->uid, tid.c_str());

	proto::game::AckDissolveSucc stSucc;
	stSucc.set_uid(player->uid);
	stSucc.set_remain_time(dissolve_room_tstamp);
	for (_uint8 j = 0; j < GAME_PLAYER; ++j)
	{
		if (seats[j].player == NULL)
			continue;
		if (player->uid == seats[j].uid) // || seats[j].player->is_offline == 1 )
			continue;
		stSucc.add_voters_uid(seats[j].uid);
		voters_players[seats[j].uid] = seats[j].player;
	}
	Ppacket ppack;
	stSucc.SerializeToString(&ppack.body);
	ppack.pack(SERVER_APPLY_DISSOLVE_ROOM_SUCC_BC);
	broadcast(NULL, ppack.data);

	ev_timer_again(zjh.loop, &dissolve_room_timer);
	m_cbCurTimer = 7;
	check_dissovle_result();
	return 0;
}

int Table::handler_dissolve_action(Player *player)
{
	if (dissovle_state != 1)
	{
		log.error("dissovle_state[%d] is error\n", dissovle_state);
		return -1;
	}
	if (player->dissovle_state != 2)
	{
		log.error("player[%d] vote error\n", player->uid);
		return -1;
	}
	proto::game::ReqDissolveAct stAct;
	stAct.ParseFromString(player->client->ppacket.body);

	int uid = stAct.uid();
	int act = stAct.action();
	if (voters_players.find(uid) == voters_players.end())
	{
		log.error("voters_uid not cantain uid[%d]\n", uid);
		return -1;
	}
	log.info("handler dissovle action player[%d] act[%d] room[%s] \n", player->uid, act, tid.c_str());
	player->dissovle_state = act;

	proto::game::AckDissolveActSucc stActSucc;
	stActSucc.set_uid(uid);
	stActSucc.set_action(act);
	Ppacket ppack;
	stActSucc.SerializeToString(&ppack.body);
	ppack.pack(SERVER_DISSOLVE_ACTION_SUCC_BC);
	broadcast(NULL, ppack.data);

	check_dissovle_result();
	return 0;
}

void Table::check_dissovle_result()
{
	unsigned int _cnt_yes = 0;
	unsigned int _cnt_no = 0;
	std::map<int, Player *>::iterator it = voters_players.begin();
	for (; it != voters_players.end(); it++)
	{
		if (it->second->dissovle_state == 0)
		{
			_cnt_no++;
		}
		else if (it->second->dissovle_state == 1)
		{
			_cnt_yes++;
		}
	}
	if (_cnt_yes + _cnt_no == voters_players.size() || _cnt_no > 0)
	{
		ev_timer_stop(zjh.loop, &dissolve_room_timer);
		m_cbCurTimer = 0;

		proto::game::AckDissolveResult stResult;
		stResult.set_result(_cnt_yes == voters_players.size() ? 1 : 0);
		Ppacket ppack;
		stResult.SerializeToString(&ppack.body);
		ppack.pack(SERVER_DISSOLVE_ROOM_RESULT_BC);
		broadcast(NULL, ppack.data);

		if (_cnt_yes == voters_players.size())
		{
			if (state == GAME_PLAYING && m_bDissovleRoom == false)
			{
				ev_timer_again(zjh.loop, &send_dissroom_timer);
				//发送录像
				ev_timer_again(zjh.loop, &send_videodata_timer);
				m_bDissovleRoom = true;
				m_cbCurTimer = 9;
			}
			else
			{
				Jpacket pac;
				pac.val["cmd"] = SERVER_DZ_DISSOLVE_ROOM_REQ;
				pac.val["roomid"] = tid;
				pac.val["vid"] = vid;
				pac.val["innings"] = m_strInnings;
				pac.end();
				zjh.game->send_to_datasvr(pac.tostring());
			}
			CheckRoomEnd();
		}
		dissovle_state = 0;
		for (_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			if (seats[i].player != NULL)
				seats[i].player->dissovle_state = 2;
		}
	}
}

void Table::dissolve_room_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->dissolve_room_timer);
	table->m_cbCurTimer = 0;
	std::map<int, Player *>::iterator it = table->voters_players.begin();
	for (; it != table->voters_players.end(); it++)
	{
		if (it->second->dissovle_state == 2)
		{
			it->second->dissovle_state = 1;
			table->check_dissovle_result();
		}
	}
}

bool Table::IsListen(_tint32 wChairID, std::vector<_uint8> &vecListenCards)
{

	return vecListenCards.size() > 0;
}


void Table::handler_offline(Player *player)
{
	proto::game::AckOffline stOffline;
	stOffline.set_uid(player->uid);
	stOffline.set_seatid(player->seatid);
	Ppacket ppack;
	stOffline.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PLAYER_OFFLINE_BC);
	broadcast(NULL, ppack.data);
}

void Table::OnFinalEndReq(Player *player)
{
	proto::game::AckFinalEnd stFEnd;
	stFEnd.set_roomid(tid);
	stFEnd.set_room_user_id(m_wRoomUserId);
	stFEnd.set_ts((int)time(NULL));
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		std::map<int, Player *>::iterator iter = players.find(seats[i].uid);
		if (iter != players.end() && iter->second)
		{
			proto::game::tagPlayers *pstPlayer = stFEnd.add_players();
			pstPlayer->set_seatid(i);
			pstPlayer->set_uid(iter->second->uid);
			pstPlayer->set_name(iter->second->name);
			pstPlayer->set_avatar(iter->second->avatar);
			pstPlayer->set_sex(iter->second->sex);
			pstPlayer->set_hu_count(m_cbHuPaiCount[i]);
			pstPlayer->set_best_huxi(m_wBestHuXi[i]);
			pstPlayer->set_best_score(m_wBestScore[i]);
			pstPlayer->set_total_score(m_wTotalScore[i]);
		}
	}
	Ppacket ppack;
	stFEnd.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_FINAL_END_RES);
	unicast(player, ppack.data);
}

void Table::save_video_data(_tint32 cmd, std::string str)
{
	ostringstream oss;
	oss << cmd << ":S:" << str << ":E:";
	m_videostr += oss.str();
}

void Table::send_video_to_svr()
{
	//base64编码
	static unsigned char buf[MaxVideoBufLen] = {0};
	int noutlen = MaxVideoBufLen;
	int iRet = base64_encode((const unsigned char *)m_videostr.c_str(), m_videostr.size(), (unsigned char *)buf, &noutlen);
	if (iRet != CRYPT_OK)
	{
		log.error("send video to svr base64_encode is error iRet:%d .\n", iRet);
		return;
	}

	Jpacket packet_data;
	packet_data.val["cmd"] = SERVER_VIDEO_DATA_SAVE;
	packet_data.val["roomid"] = tid;
	std::string packStr((char *)buf, noutlen);
	packet_data.val["content"] = packStr;
	packet_data.val["innings"] = m_strInnings;
	packet_data.end();
	zjh.game->send_to_videosvr(packet_data.tostring());
	log.info("send video to svr m_videostr.size[%d] noutlen[%d] tid[%s].\n", m_videostr.size(), noutlen, tid.c_str());
}

void Table::Send_Video_Data_Timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	log.info("Send_Video_Data_Timer_cb roomID:%s \n", table->tid.c_str());
	ev_timer_stop(zjh.loop, &table->send_videodata_timer);
	table->m_cbCurTimer = 0;
	table->send_video_to_svr();
}

void Table::save_table_info_video()
{
	proto::game::TableInfoVideo stTableInfo;
	stTableInfo.set_banker(m_wBankerUser);
	stTableInfo.set_take_in(m_wTakeIn);
	stTableInfo.set_play_id(m_wPlayID);
	stTableInfo.set_base_huxi(m_BaseWinCards);
	stTableInfo.set_room_user_id(m_wRoomUserId);
	stTableInfo.set_game_player(GAME_PLAYER);
	stTableInfo.set_game_name("chenzhouphz");
	for (int c = 0; c < GAME_PLAYER; ++c)
	{
		Player *p = seats[c].player;
		if (p == NULL)
			continue;
		proto::game::tagPlayers *pstTablePlayers = stTableInfo.add_players();
		pstTablePlayers->set_uid(p->uid);
		pstTablePlayers->set_seatid(p->seatid);
		pstTablePlayers->set_ready(seats[c].ready);
		pstTablePlayers->set_money(p->money);
		pstTablePlayers->set_name(p->name);
		pstTablePlayers->set_sex(p->sex);
		pstTablePlayers->set_avatar(p->avatar);
		pstTablePlayers->set_hu_xi(m_bWeaveShowHuXiCount[c]);
	}
	save_video_data(SERVER_TABLE_INFO_UC, stTableInfo.SerializeAsString());
}

void Table::save_game_start_video()
{
	proto::game::GameStartVideo stGameStart;
	stGameStart.set_banker(m_wBankerUser);
	//stGameStart.set_banker_card(m_cbBankerCard);
//	stGameStart.set_left_card_count(m_bLeftCardCount);
	for (_uint8 c = 0; c < GAME_PLAYER; ++c)
	{
		proto::game::tagPlayers *pstPlayer = stGameStart.add_players();
		pstPlayer->set_seatid(c);
		for (_uint8 i = 0; i < m_cbCardsWeaveCount[c]; ++i)
		{
			proto::game::tagHandCards *pstHandCards = pstPlayer->add_hand_cards();
			pstHandCards->set_huxi(m_GameLogic.GetWeaveHuXi(m_CardsWeaveInfo[c][i]));
			for (_uint8 j = 0; j < m_CardsWeaveInfo[c][i].cbCardCount; ++j)
			{
				pstHandCards->add_card(m_CardsWeaveInfo[c][i].cbCardList[j]);
			}
		}

	}
	save_video_data(SERVER_GAME_START_BC, stGameStart.SerializeAsString());
}

void Table::save_operate_video(_tint32 wChairID, _uint8 cbAckCode, _uint8 cbActionCard)
{
	proto::game::OperateVideo stOperateCard;
	stOperateCard.set_ack_code(cbAckCode);
	stOperateCard.set_seatid(wChairID);
	stOperateCard.set_action_card(cbActionCard);
	std::vector<_uint8> vecListenCards;

	for (_uint8 i = 0; i < m_cbCardsWeaveCount[wChairID]; ++i)
	{
		proto::game::tagHandCards *pstHandCards = stOperateCard.add_hand_cards();
		pstHandCards->set_huxi(m_GameLogic.GetWeaveHuXi(m_CardsWeaveInfo[wChairID][i]));
		for (_uint8 j = 0; j < m_CardsWeaveInfo[wChairID][i].cbCardCount; ++j)
		{
			pstHandCards->add_card(m_CardsWeaveInfo[wChairID][i].cbCardList[j]);
		}
	}
	for (int j = 0; j < m_bWeaveItemCount[wChairID]; ++j)
	{
		proto::game::tagWeaveCards *pstWeaves = stOperateCard.add_weaves();
		pstWeaves->set_weave_kind(m_WeaveItemArray[wChairID][j].cbWeaveKind);
		pstWeaves->set_card_count(m_WeaveItemArray[wChairID][j].cbCardCount);
		pstWeaves->set_center_card(m_WeaveItemArray[wChairID][j].cbCenterCard);
		for (int k = 0; k < m_WeaveItemArray[wChairID][j].cbCardCount; ++k)
		{
			pstWeaves->add_card_list(m_WeaveItemArray[wChairID][j].cbCardList[k]);
		}
	}
	for (_uint8 c = 0; c < GAME_PLAYER; ++c)
	{
		proto::game::tagPlayers *pstPlayer = stOperateCard.add_players();
		pstPlayer->set_seatid(c);
		if (seats[c].player != NULL)
		{
			pstPlayer->set_money(seats[c].player->money);
		}
	}
	save_video_data(SERVER_PHZ_OPERATE_CARD_RES, stOperateCard.SerializeAsString());
}

//void Table::save_dispatch_card_video(_tint32 wChairID, _uint8 cbCardData, _tint32 wToSeatid)
//{
//	proto::game::AckDispatchCard stDispachCard;
//	stDispachCard.set_seatid(wChairID);
//	stDispachCard.set_card(cbCardData);
////	stDispachCard.set_left_card_count(m_bLeftCardCount);
//	if (wToSeatid != INVALID_CHAIR)
//		stDispachCard.set_to_seatid(wToSeatid);
//	save_video_data(SERVER_PHZ_SEND_CARD, stDispachCard.SerializeAsString());
//}

void Table::save_operate_notify_video()
{
	proto::game::OperateNotify stOpNotify;
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		proto::game::tagPlayers *pstPlayers = stOpNotify.add_players();
		pstPlayers->set_seatid(i);
		pstPlayers->set_operate_type(m_bUserAction[i]);
	}
	save_video_data(SERVER_PHZ_OPERATE_NOTIFY, stOpNotify.SerializeAsString());
}

//void Table::save_operate_res_video(_tint32 wChairID, _uint8 cbOpCode)
//{
//	proto::game::AckOperateRes stOpRes;
//	stOpRes.set_seatid(wChairID);
//	stOpRes.set_operate_type(cbOpCode);
//	save_video_data(SERVER_PHZ_OPERATE_RES, stOpRes.SerializeAsString());
//}

void Table::save_out_card_video(_tint32 wChairID, vector<stCardInfo>& stCardData)
{
	proto::game::AckOutCard stOutCard;
	stOutCard.set_seatid(wChairID);
	for (_uint8 i = 0; i < stCardData.size(); ++i)
	{
		stOutCard.add_out_card(stCardData[i].cbCard);
	}
	if (m_bCommonOrBest[wChairID] == false)
	{
		for (_uint8 i = 0; i < m_cbCardsWeaveCount[wChairID]; ++i)
		{
			proto::game::tagHandCards *pstHandCards = stOutCard.add_hand_cards();
			pstHandCards->set_huxi(m_GameLogic.GetWeaveHuXi(m_CardsWeaveInfo[wChairID][i]));
			for (_uint8 j = 0; j < m_CardsWeaveInfo[wChairID][i].cbCardCount; ++j)
			{
				pstHandCards->add_card(m_CardsWeaveInfo[wChairID][i].cbCardList[j]);
			}
		}
	}
	else
	{
		for (_uint8 i = 0; i < m_cbBestWeaveCount[wChairID]; ++i)
		{
			proto::game::tagHandCards *pstHandCards = stOutCard.add_hand_cards();
			pstHandCards->set_huxi(m_GameLogic.GetWeaveHuXi(m_BestWeaveInfo[wChairID][i]));
			for (_uint8 j = 0; j < m_BestWeaveInfo[wChairID][i].cbCardCount; ++j)
			{
				pstHandCards->add_card(m_BestWeaveInfo[wChairID][i].cbCardList[j]);
			}
		}
	}

	save_video_data(SERVER_PHZ_OUT_CARD_RES, stOutCard.SerializeAsString());
}


void Table::save_game_end_video(_tint32 cmd, std::string str)
{
	save_video_data(cmd, str);
	ostringstream oss;
	oss << cmd << ":S:" << str << ":E:";
	m_strLastEndInfo = oss.str();
}




void Table::save_offline_info(_tint32 wChairID, _tint32 cmd, std::string str)
{
	if (wChairID < 0 || wChairID >= GAME_PLAYER)
		return;
	ostringstream oss;
	oss << cmd << ":S:" << str << ":E:";
	if (m_cbOfflineCount[wChairID] < MaxOfflineLen)
	{
		m_strOfflineInfo[wChairID][m_cbOfflineCount[wChairID]++] = oss.str();
		log.info("save offline info wChairID[%d] m_cbOfflineCount[%d] tid[%s] .\n", wChairID, m_cbOfflineCount[wChairID], tid.c_str());
	}
}

void Table::OnOfflineInfoReq(Player *player)
{
	if (m_strLastEndInfo.size() == 0)
	{
		Ppacket ppack;
		ppack.pack(SERVER_PHZ_OFFLINE_INFO_ERR);
		unicast(player, ppack.data);
	}
	else
	{
		proto::game::AckLastEndInfo stLastInfo;
		stLastInfo.set_info(m_strLastEndInfo);
		Ppacket ppack;
		stLastInfo.SerializeToString(&ppack.body);
		ppack.pack(SERVER_PHZ_OFFLINE_INFO_RES);
		unicast(player, ppack.data);
	}
}

bool Table::IsListenOver(_tint32 wChairID, _uint8 cbCard)
{
	return false;
}


void Table::UpdateWeaveOutCard(_tint32 wChairID, _uint8 cbCard)
{

}

void Table::OnHandDetailInfo(Player *player)
{
	if (player->seatid < 0 || player->seatid >= GAME_PLAYER)
	{
		log.error("On hand detail info error uid[%d] seatid[%d] tid[%s] .\n", player->uid, player->seatid, tid.c_str());
		return;
	}

	proto::game::AckHandDetail stDetail;
	for (_uint8 c = 0; c < GAME_PLAYER; ++c)
	{
		if (c == player->seatid)
			continue;
		Player *p = seats[c].player;
		if (p == NULL)
			continue;
		proto::game::tagPlayers *pstDetailPlayer = stDetail.add_players();
		pstDetailPlayer->set_seatid(c);

		for (_uint8 j = 0; j < m_bWeaveItemCount[c]; ++j)
		{
			proto::game::tagWeaveCards *pstWeaves = pstDetailPlayer->add_weaves();
			pstWeaves->set_weave_kind(m_WeaveItemArray[c][j].cbWeaveKind);
			pstWeaves->set_card_count(m_WeaveItemArray[c][j].cbCardCount);
			pstWeaves->set_out_card(m_WeaveItemArray[c][j].cbOutCard);
		/*	if ((m_WeaveItemArray[c][j].cbWeaveKind != ACK_TI && m_WeaveItemArray[c][j].cbWeaveKind != ACK_WEI))
			{
				pstWeaves->set_center_card(m_WeaveItemArray[c][j].cbCenterCard);
				for (_uint8 k = 0; k < m_WeaveItemArray[c][j].cbCardCount; ++k)
				{
					pstWeaves->add_card_list(m_WeaveItemArray[c][j].cbCardList[k]);
					_uint8 cbCard = m_WeaveItemArray[c][j].cbCardList[k];
					if (CardNum(cbCard) == 0x02 || CardNum(cbCard) == 0x07 || CardNum(cbCard) == 0x0a)
						cbHongCount++;
					else
						cbHeiCount++;
				}
			}*/
		}
		_uint8 cbHandCardCount = 0;

		for (_uint8 i = 0; i < CARD_TYPE_1; ++i)
		{
			for (_uint8 j = 0; j < CARD_TYPE_2; ++j)
			{
				for (_uint8 k = 0; k < CARD_INDEX; ++k)
				{
					cbHandCardCount += m_cbCardIndex[c].cbCards[i][j][k];
				}			
			}		
		}
		pstDetailPlayer->set_hand_count(cbHandCardCount);
		pstDetailPlayer->set_name(p->name);
		pstDetailPlayer->set_sex(p->sex);
		pstDetailPlayer->set_avatar(p->avatar);
		pstDetailPlayer->set_money(p->money);
	}
	Ppacket ppack;
	stDetail.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_HAND_DETAIL_RES);
	unicast(player, ppack.data);
	log.debug("uid[%d] tid[%s] stDetail[%s] .\n", player->uid, tid.c_str(), stDetail.DebugString().c_str());
}


void Table::game_restart_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->game_restart_timer);
	table->game_start_req();
}

void Table::send_dissroom_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Table *table = (Table *)w->data;
	ev_timer_stop(zjh.loop, &table->send_dissroom_timer);
	table->m_cbCurTimer = 0;
	table->send_dissroom();
}

void Table::send_dissroom()
{
	Jpacket pac;
	pac.val["cmd"] = SERVER_DZ_DISSOLVE_ROOM_REQ;
	pac.val["roomid"] = tid;
	pac.val["vid"] = vid;
	pac.val["innings"] = m_strInnings;
	pac.end();
	zjh.game->send_to_datasvr(pac.tostring());
	log.info("send dissroom roomid[%s] .\n", tid.c_str());
}

/*
 *恢复服数据恢复
 */
int Table::decompress_str(string &src, string &des)
{
	//base64编码
	static unsigned char ubuf[MaxVideoBufLen] = {0};
	int unoutlen = MaxVideoBufLen;
	int iRet = base64_decode((const unsigned char *)src.c_str(), src.size(), (unsigned char *)ubuf, &unoutlen);
	if (iRet != CRYPT_OK)
	{
		log.error("base64_decode video svr is error iRet:%d .\n", iRet);
		return -1;
	}
	//zlib解压
	static unsigned char uzbuf[MaxVideoBufLen] = {0};
	uLong unzlen = MaxVideoBufLen;
	iRet = uncompress((Bytef *)uzbuf, (uLongf *)&unzlen, (const Bytef *)ubuf, (uLong)unoutlen);
	if (iRet != Z_OK)
	{
		log.error("uncompress video error iRet:%d .\n", iRet);
		return -1;
	}
	std::string packStr((char *)uzbuf, unzlen);
	des.clear();
	des = packStr;
	return 0;
}

int Table::compress_str(string &src, string &des)
{
	//zlib压缩
	static unsigned char zbuf[MaxVideoBufLen] = {0};
	uLong nzlen = MaxVideoBufLen;
	int iRet = compress((Bytef *)zbuf, (uLongf *)&nzlen, (const Bytef *)src.c_str(), (uLong)src.size());
	if (iRet != Z_OK)
	{
		log.error("send video to svr compress error iRet:%d .\n", iRet);
		return -1;
	}
	//base64编码
	static unsigned char buf[MaxVideoBufLen] = {0};
	int noutlen = MaxVideoBufLen;
	iRet = base64_encode((const unsigned char *)zbuf, nzlen, (unsigned char *)buf, &noutlen);
	if (iRet != CRYPT_OK)
	{
		log.error("send video to svr base64_encode is error iRet:%d .\n", iRet);
		return -1;
	}
	std::string packStr((char *)buf, noutlen);
	des.clear();
	des = packStr;
	return 0;
}

//重启定时器
int Table::AgainTimer()
{
	switch (m_cbCurTimer)
	{
	case 1:
		ev_timer_again(zjh.loop, &start_timer);
		break;
	case 2:
		ev_timer_again(zjh.loop, &preready_timer);
		break;
	case 3:
		ev_timer_again(zjh.loop, &dispatch_show_timer);
		break;
	case 4:
		ev_timer_again(zjh.loop, &out_show_timer);
		break;
	case 5:
		ev_timer_again(zjh.loop, &dispatch_delay_timer);
		break;
	case 6:
		ev_timer_again(zjh.loop, &out_delay_timer);
		break;
	case 7:
		ev_timer_again(zjh.loop, &dissolve_room_timer);
		break;
	case 8:
		ev_timer_again(zjh.loop, &send_videodata_timer);
		break;
	case 9:
		ev_timer_again(zjh.loop, &send_dissroom_timer);
		break;
	default:
		break;
	}
	return 0;
}

int Table::SerializeTableData()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	log.debug("SerializeTableData begin sec[%d] usec[%d].\n", tv.tv_sec, tv.tv_usec);
	proto::game::AckTableInfo pTableInfo;
	pTableInfo.set_tid(tid);
	pTableInfo.set_base_money(base_money);
	//座位信息
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		Player *player = seats[i].player;
		if (player == NULL)
			continue;
		proto::game::tagPlayers *pstPlayer = pTableInfo.add_players();
		pstPlayer->set_uid(seats[i].uid);
		pstPlayer->set_ready(seats[i].ready);
		pstPlayer->set_tid(player->tid);
		pstPlayer->set_seatid(player->seatid);
		pstPlayer->set_offline(player->is_offline);
		pstPlayer->set_skey(player->skey);
		pstPlayer->set_name(player->name);
		pstPlayer->set_sex(player->sex);
		pstPlayer->set_avatar(player->avatar);
		pstPlayer->set_money(player->money);
		pstPlayer->set_dissolve_cnt(player->dissolve_cnt);
		pstPlayer->set_dissovle_state(player->dissovle_state);
	}
	pTableInfo.set_state(state);
	pTableInfo.set_stand_money(stand_money);
	pTableInfo.set_take_in(m_wTakeIn);
	pTableInfo.set_play_id(m_wTakeIn);
	pTableInfo.set_room_status(m_cbRoomStatus);
	pTableInfo.set_room_user_id(m_wRoomUserId);
	pTableInfo.set_dissovle_state(dissovle_state);
	pTableInfo.set_dissolve_applyer(dissolve_applyer);
	pTableInfo.set_is_dissolved(is_dissolved);

	
//	pTableInfo.set_left_card_count(m_bLeftCardCount);
	for (_uint8 i = 0; i < pTableInfo.players_size() && i < GAME_PLAYER; ++i)
	{
		proto::game::tagPlayers *stPlayer = pTableInfo.mutable_players(i);


		for (_uint8 j = 0; j < CARD_TYPE_1; ++j)
		{
			for (_uint8 k = 0; k < CARD_TYPE_2; ++k)
			{
				for (_uint8 l = 0; l < CARD_INDEX; ++l)
				{
					stPlayer->add_card_index(m_cbCardIndex[i].cbCards[j][k][l]);
				}
			}
		}
		for (_uint8 j = 0; j < m_cbCardsWeaveCount[i]; ++j)
		{
			proto::game::tagHandCards *stCards = stPlayer->add_cards_weave();
			stCards->set_wv_kind(m_CardsWeaveInfo[i][j].cbWeaveKind);
			for (_uint8 k = 0; k < m_CardsWeaveInfo[i][j].cbCardCount; ++k)
			{
				stCards->add_card(m_CardsWeaveInfo[i][j].cbCardList[k]);
			}
		}
		for (_uint8 j = 0; j < m_cbBestWeaveCount[i]; ++j)
		{
			proto::game::tagHandCards *stCards = stPlayer->add_best_weave();
			stCards->set_wv_kind(m_BestWeaveInfo[i][j].cbWeaveKind);
			for (_uint8 k = 0; k < m_BestWeaveInfo[i][j].cbCardCount; ++k)
			{
				stCards->add_card(m_BestWeaveInfo[i][j].cbCardList[k]);
			}
		}
		for (_uint8 j = 0; j < m_bWeaveItemCount[i]; ++j)
		{
			proto::game::tagWeaveCards *stWeave = stPlayer->add_weaves();
			stWeave->set_weave_kind(m_WeaveItemArray[i][j].cbWeaveKind);
			stWeave->set_center_card(m_WeaveItemArray[i][j].cbCenterCard);
			stWeave->set_out_card(m_WeaveItemArray[i][j].cbOutCard);
			for (_uint8 k = 0; k < m_WeaveItemArray[i][j].cbCardCount; ++k)
			{
				stWeave->add_card_list(m_WeaveItemArray[i][j].cbCardList[k]);
			}
		}
		//stPlayer->set_niao(m_UserNiaoCount[i]);
		//stPlayer->set_piao(m_UserPiaoScore[i]);
		stPlayer->set_hu_count(m_cbHuPaiCount[i]);
		stPlayer->set_best_huxi(m_wBestHuXi[i]);
		stPlayer->set_best_score(m_wBestScore[i]);
		stPlayer->set_total_score(m_wTotalScore[i]);
		log.debug("Serilize card_index[%d] cards_weave[%d] best_weave[%d] weaves[%d] .\n", stPlayer->card_index_size(), stPlayer->cards_weave_size(), stPlayer->best_weave_size(), stPlayer->weaves_size());
	}
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		pTableInfo.add_weave_huxi(m_bWeaveHuXiCount[i]);
	}
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		pTableInfo.add_show_huxi(m_bWeaveShowHuXiCount[i]);
	}

	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		pTableInfo.add_out_count(m_UserOutCardCount[i]);
	}
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		pTableInfo.add_cur_card_huxi(m_UserCurHuCardXi[i]);
	}
	/*for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		proto::game::tagWeaveScore* pstWeaveScore = pTableInfo.add_weave_score();
		pstWeaveScore->set_little_count(m_UserWeaveScore[i].cbLittleCount);
		pstWeaveScore->set_big_count(m_UserWeaveScore[i].cbBigCount);
		pstWeaveScore->set_score(m_UserWeaveScore[i].nScore);
	}*/
	//操作
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		pTableInfo.add_user_responses(m_bResponse[i]);
	}
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		pTableInfo.add_user_actions(m_bUserAction[i]);
	}
	for (_uint8 i = 0; i < GAME_PLAYER; ++i)
	{
		pTableInfo.add_user_prerform(m_bPerformAction[i]);
	}
	

	pTableInfo.set_is_dispatch(m_bDispatch);
	pTableInfo.set_dispatch_hu(m_bDispatchHu);
	//pTableInfo.set_wei_hu(m_bWeiHu);
	pTableInfo.set_is_first_card(m_bFirstCard);
	pTableInfo.set_card_operated(m_bCardOperated);
	pTableInfo.set_banker_user(m_wBankerUser);
	pTableInfo.set_first_banker_user(m_wFirstBankerUser);
//	pTableInfo.set_banker_card(m_cbBankerCard);
	pTableInfo.set_current_user(m_wCurrentUser);
	//pTableInfo.set_current_card(m_cbCurrentCard);
	pTableInfo.set_current_outcard_user(m_wOutCardUser);
	pTableInfo.set_current_outcard(m_cbOutCardData);
	pTableInfo.set_is_tianhu_show(m_bIsTianHuShow);
	pTableInfo.set_already_resp(m_bAlreadyResp);

	pTableInfo.set_game_player(GAME_PLAYER);
	pTableInfo.set_base_huxi(m_BaseWinCards);
	pTableInfo.set_is_out_card(m_bOutCard);
	pTableInfo.set_current_num(m_wCurrentNum);
	pTableInfo.set_innings(m_strInnings);
	pTableInfo.set_video_str(m_videostr);

	for(std::vector<tagGain>::iterator iter = m_vecGains.begin(); iter != m_vecGains.end(); ++iter)
	{
		proto::game::tagGain* pstGain = pTableInfo.add_gains();
		for(_uint8 i = 0; i < GAME_PLAYER; ++i)
		{
			pstGain->add_score((*iter).Gain[i]);
		}
	}

	//压缩保存
	std::string data_str;
	data_str.clear();
	pTableInfo.SerializeToString(&data_str);
	log.debug("Serialize tid[%s] pTableInfo[%s] .\n", tid.c_str(), pTableInfo.DebugString().c_str());
	log.info("Serialize Table Data succ tid[%s] size[%d].\n", tid.c_str(), data_str.size());
	//解压
	_tint32 iRet = compress_str(data_str, data_str);
	if (iRet < 0)
	{
		log.error("Serialize Table Data compress fail iRet[%d].\n", iRet);
		return -1;
	}
	zjh.game->save_data_to_redis(tid, data_str);
	gettimeofday(&tv, NULL);
	log.debug("SerializeTableData end sec[%d] usec[%d].\n", tv.tv_sec, tv.tv_usec);
	log.info("Serialize Table Data succ tid[%s] compress size[%d].\n", tid.c_str(), data_str.size());
	return 0;
}

int Table::ParseTableData(std::string &data_str)
{
	//解压
	_tint32 iRet = 0;
	iRet = decompress_str(data_str, data_str);
	if (iRet < 0)
	{
		log.error("Parse Table Data decompress fail iRet[%d] data size[%d].\n", iRet, data_str.size());
		return -1;
	}
	proto::game::AckTableInfo pTableInfo;
	pTableInfo.ParseFromString(data_str);
	//桌上信息
	tid = pTableInfo.tid();
	log.debug("Parse tid[%s] pTableInfo[%s] .\n", tid.c_str(), pTableInfo.DebugString().c_str());
	log.info("Parse tid[%s] .\n", tid.c_str());
	base_money = pTableInfo.base_money();
	//玩家座位信息
	for (_uint8 i = 0; i < pTableInfo.players_size() && i < GAME_PLAYER; ++i)
	{
		const proto::game::tagPlayers &stPlayer = pTableInfo.players(i);
		seats[i].uid = stPlayer.uid();
		seats[i].occupied = 1;
		seats[i].ready = stPlayer.ready();
		Player *player = NULL;
		if (players.find(stPlayer.uid()) == players.end())
		{
			player = new (nothrow) Player();
		}
		else
		{
			player = players[stPlayer.uid()];
		}
		player->InitData(stPlayer);
		seats[i].player = player;
		players[player->uid] = player;
	}
	state = (State)pTableInfo.state();
	stand_money = pTableInfo.stand_money();
	m_wTakeIn = pTableInfo.take_in();
	m_wPlayID = pTableInfo.play_id();
	m_cbRoomStatus = pTableInfo.room_status();
	m_wRoomUserId = pTableInfo.room_user_id();
	dissovle_state = pTableInfo.dissovle_state();
	dissolve_applyer = pTableInfo.dissolve_applyer();
	is_dissolved = pTableInfo.is_dissolved();



	for (_uint8 i = 0; i < pTableInfo.repertory_cards_size() && i < MAX_CARDS; ++i)  //初始化牌库
	{
		m_cbRepertoryCard[i] = pTableInfo.repertory_cards(i);
	}
//	m_bLeftCardCount = pTableInfo.left_card_count();
	for (_uint8 i = 0; i < pTableInfo.players_size() && i < GAME_PLAYER; ++i)
	{
		const proto::game::tagPlayers &stPlayer = pTableInfo.players(i);
		log.debug("Parse card_index[%d] cards_weave[%d] best_weave[%d] weaves[%d] .\n", stPlayer.card_index_size(), stPlayer.cards_weave_size(), stPlayer.best_weave_size(), stPlayer.weaves_size());
		for (_uint8 cbCount = 0; cbCount < stPlayer.card_index_size() && cbCount < MAX_INDEX_EX; ++cbCount)
		{
			for (_uint8 j = 0; j < CARD_TYPE_1; ++j)
			{
				for (_uint8 k = 0; k < CARD_TYPE_2; ++k)
				{
					for (_uint8 l = 0; l < CARD_INDEX; ++l)
					{
						m_cbCardIndex[i].cbCards[i][k][l] = stPlayer.card_index(cbCount);  //初始化玩家手牌
					}
				}			
			}
		}
		m_cbCardsWeaveCount[i] = stPlayer.cards_weave_size(); 
		for (_uint8 j = 0; j < stPlayer.cards_weave_size() && j < MAX_INDEX; ++j)	//初始化玩家手牌组合
		{
			const proto::game::tagHandCards &stCards = stPlayer.cards_weave(j);
			m_CardsWeaveInfo[i][j].cbCardCount = stCards.card_size();
			m_CardsWeaveInfo[i][j].cbWeaveKind = stCards.wv_kind();
			for (_uint8 k = 0; k < stCards.card_size() && k < 4; ++k)
			{
				m_CardsWeaveInfo[i][j].cbCardList[k] = stCards.card(k);
			}
		}
		//m_cbBestWeaveCount[i] = stPlayer.best_weave_size();
		//for (_uint8 j = 0; j < stPlayer.best_weave_size() && j < MAX_INDEX; ++j)  //初始化最佳手牌组合
		//{
		//	const proto::game::tagHandCards &stCards = stPlayer.best_weave(j);
		//	m_BestWeaveInfo[i][j].cbCardCount = stCards.card_size();
		//	m_BestWeaveInfo[i][j].cbWeaveKind = stCards.wv_kind();
		//	for (_uint8 k = 0; k < stCards.card_size() && k < 4; ++k)
		//	{
		//		m_BestWeaveInfo[i][j].cbCardList[k] = stCards.card(k);
		//	}
		//}
		m_bWeaveItemCount[i] = stPlayer.weaves_size();   //初始化赢牌区
		for (_uint8 j = 0; j < stPlayer.weaves_size() && j < MAX_WEAVE; ++j)
		{
			const proto::game::tagWeaveCards &stWeave = stPlayer.weaves(j);
			m_WeaveItemArray[i][j].cbWeaveKind = stWeave.weave_kind();
			m_WeaveItemArray[i][j].cbCenterCard = stWeave.center_card();
			m_WeaveItemArray[i][j].cbOutCard = stWeave.out_card();
			m_WeaveItemArray[i][j].cbCardCount = stWeave.card_list_size();
			for (_uint8 k = 0; k < stWeave.card_list_size() && k < 4; ++k)
			{
				m_WeaveItemArray[i][j].cbCardList[k] = stWeave.card_list(k);
			}
		}

		m_cbHuPaiCount[i] = stPlayer.hu_count();
		m_wBestHuXi[i] = stPlayer.best_huxi();
		m_wBestScore[i] = stPlayer.best_score();
		m_wTotalScore[i] = stPlayer.total_score();
	}
	for (_uint8 i = 0; i < pTableInfo.weave_huxi_size() && i < GAME_PLAYER; ++i)
	{
		m_bWeaveHuXiCount[i] = pTableInfo.weave_huxi(i);
	}
	for (_uint8 i = 0; i < pTableInfo.show_huxi_size() && i < GAME_PLAYER; ++i)
	{
		m_bWeaveShowHuXiCount[i] = pTableInfo.show_huxi(i);
	}

	for (_uint8 i = 0; i < pTableInfo.out_count_size() && i < GAME_PLAYER; ++i)
	{
		m_UserOutCardCount[i] = pTableInfo.out_count(i);
	}
	for (_uint8 i = 0; i < pTableInfo.cur_card_huxi_size() && i < GAME_PLAYER; ++i)
	{
		m_UserCurHuCardXi[i] = pTableInfo.cur_card_huxi(i);
	}

	//操作
	for (_uint8 i = 0; i < pTableInfo.user_responses_size() && i < GAME_PLAYER; ++i)
	{
		m_bResponse[i] = pTableInfo.user_responses(i);
	}
	for (_uint8 i = 0; i < pTableInfo.user_actions_size() && i < GAME_PLAYER; ++i)
	{
		m_bUserAction[i] = pTableInfo.user_actions(i);
	}
	for (_uint8 i = 0; i < pTableInfo.user_prerform_size() && i < GAME_PLAYER; ++i)
	{
		m_bPerformAction[i] = pTableInfo.user_prerform(i);
	}
	m_bDispatch = pTableInfo.is_dispatch();
	m_bDispatchHu = pTableInfo.dispatch_hu();
	//m_bWeiHu = pTableInfo.wei_hu();
	m_bFirstCard = pTableInfo.is_first_card();
	m_bCardOperated = pTableInfo.card_operated();
	m_wBankerUser = pTableInfo.banker_user();
	m_wFirstBankerUser = pTableInfo.first_banker_user();
//	m_cbBankerCard = pTableInfo.banker_card();
	m_wCurrentUser = pTableInfo.current_user();
	//m_cbCurrentCard = pTableInfo.current_card();
	m_wOutCardUser = pTableInfo.current_outcard_user();
	m_cbOutCardData = pTableInfo.current_outcard();

	m_bIsTianHuShow = pTableInfo.is_tianhu_show();
	m_bAlreadyResp = pTableInfo.already_resp();

	m_GamePlayer = pTableInfo.game_player();
	m_BaseWinCards = pTableInfo.base_huxi();
	m_bOutCard = pTableInfo.is_out_card();
	m_wCurrentNum = pTableInfo.current_num();
	m_strInnings = pTableInfo.innings();
	m_videostr = pTableInfo.video_str();
	for(_uint8 i = 0; i < pTableInfo.gains_size(); ++i)
	{
		tagGain stGain;
		const proto::game::tagGain stProtoGain = pTableInfo.gains(i);
		for(_uint8 j = 0; j < stProtoGain.score_size(); ++j)
		{
			stGain.Gain[j] = stProtoGain.score(j);
		}
		m_vecGains.push_back(stGain);
	}

	//重启定时器
	AgainTimer();

	log.info("Parse Table Data Parse succ tid[%s].\n", tid.c_str());
	return 0;
}


/* 给玩家发操作通知
 * wChairID		：玩家位置
 */
int Table::SendNotifyToUsrByCID(_tint32 wChairID, vector<_uint16>& cbCenterCards)
{
	if (wChairID >= GAME_PLAYER || wChairID < 0)
	{
		return -1;
	}
	Player *player = seats[wChairID].player;
	if (player == NULL || (m_bUserAction[wChairID] == ACK_NULL))
	{
		return -1;
	}
	//发送操作提示
	m_bOutCard = true;
	m_wCurrentUser = wChairID;
	proto::game::AckOperateNotify stNotity;
	stNotity.set_operate_type(m_bUserAction[wChairID]);
	stNotity.set_off_count(m_cbOfflineCount[wChairID]);
	if (wChairID != m_wBankerUser)
	{
		for (_uint8 i = 0; i < cbCenterCards.size(); ++i)
		{
			log.info("SendNotifyToUsrByCID, cbCenterCards: %x \n", cbCenterCards[i]);
			stNotity.add_win_weaves(cbCenterCards[i]);
		}
	}
	

	Ppacket ppack;
	stNotity.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_OPERATE_NOTIFY);

	//保存离线数据
	save_offline_info(wChairID, SERVER_PHZ_OPERATE_NOTIFY, stNotity.SerializeAsString());

	log.debug("[%s] uid[%d] tid[%s] stNotity[%s] .\n", __FUNCTION__, player->uid, tid.c_str(), stNotity.DebugString().c_str());

	return unicast(player, ppack.data);
}

bool Table::IsHuPaiByCID(_tint32 wChairID)
{
	return false;
}

bool Table::OnUserGainsReq(Player* player)
{
	_tint32 wChairID = player->seatid;
	if(wChairID < 0 || wChairID >= GAME_PLAYER)
	{
		log.error("On user gains req error uid[%d] wChairID[%d] tid[%s] .\n", player->uid, wChairID, tid.c_str());
		return false;
	}

	proto::game::AckGains stGains;
	for(_uint8 i = 0; i < GAME_PLAYER && i < m_GamePlayer; ++i)
	{
		if(seats[i].player == NULL) continue;
		proto::game::tagPlayers* pstPlayer = stGains.add_players();
		pstPlayer->set_seatid(seats[i].player->seatid);
		pstPlayer->set_uid(seats[i].player->uid);
		pstPlayer->set_name(seats[i].player->name);
		pstPlayer->set_avatar(seats[i].player->avatar);
		pstPlayer->set_sex(seats[i].player->sex);
		pstPlayer->set_money(seats[i].player->money);
		_tint32 wTotalGains = 0;
		std::vector<tagGain>::iterator iter = m_vecGains.begin();
		for(; iter != m_vecGains.end(); ++iter)
		{
			pstPlayer->add_gains((*iter).Gain[i]);
			wTotalGains += (*iter).Gain[i];
		}
		pstPlayer->set_total_gains(wTotalGains);
	}
	Ppacket ppack;
	stGains.SerializeToString(&ppack.body);
	ppack.pack(SERVER_PHZ_GAINS_RES);
	unicast(player, ppack.data);
	return true;
}


int Table::handler_chat(Player *player)
{
	proto::game::AckChat stChat;
	stChat.ParseFromString(player->client->ppacket.body);
	proto::game::AckChat stChatRes;
	stChatRes.set_seatid(player->seatid);
	stChatRes.set_text(stChat.text());
	Ppacket ppack;
	stChatRes.SerializeToString(&ppack.body);
	ppack.pack(SERVER_CHAT_BC);
	broadcast(NULL, ppack.data);
	log.debug("handler chat stChat[%s] stChatRes[%s] .\n", stChat.DebugString().c_str(), stChatRes.DebugString().c_str());
	return 0;
}

int Table::handler_face(Player *player)
{
	proto::game::AckFace stFace;
	stFace.ParseFromString(player->client->ppacket.body);
	proto::game::AckFace stFaceRes;
	stFaceRes.set_seatid(player->seatid);
	stFaceRes.set_faceid(stFace.faceid());
	Ppacket ppack;
	stFaceRes.SerializeToString(&ppack.body);
	ppack.pack(SERVER_FACE_BC);
	broadcast(NULL, ppack.data);
	return 0;
}


