#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ev++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>
#include <ev.h>

#include "loginproto.pb.h"
#include "gameproto.pb.h"
#include "Common.h"
class Client;

class Player
{		
	public:
		int					vid;
		int					zid;
		std::string			tid;
		int					seatid;
		int                 uid;
		std::string			skey;
		std::string			name;
		int					sex;
		std::string			avatar;
		int					usertype;
		int					exp;
		int					rmb;
		long				money;
		Client              *client;
		int 				logout_type;

		int					down_tag;   // game end down table
		bool				daemonize_flag;
		int					dissolve_cnt;
		int					dissovle_state;//0--反对解散 1--同意解散 2--未操作
		int					is_offline;
	private:
		ev_timer			_offline_timer;
		ev_tstamp			_offline_timeout;

		ev_timer			_del_player_timer;
		ev_tstamp			_del_player_tstamp;

	public:
		Player();
		virtual ~Player();
		void set_client(Client *c);
		//初始化和重置
		int init( Json::Value &val);
		int InitData(const proto::game::tagPlayers &pUserInfo);
		void reset();
		void clear();
		//掉线玩家定时器
		void start_offline_timer();
		void stop_offline_timer();
		static void offline_timeout(struct ev_loop *loop, ev_timer *w, int revents);
		//删除玩家定时器
		void start_del_player_timer();
		void stop_del_player_timer();
		static void del_player_timer_cb(struct ev_loop *loop, ev_timer *w, int revents);
	
};

#endif
