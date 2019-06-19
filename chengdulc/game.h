#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ev++.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "zjh.h"
#include "log.h"
#include "proto.h"
#include "client.h"
#include "player.h"
#include "table.h"
#include "loginproto.pb.h"
#include "gameproto.pb.h"
#include "Common.h"

class Client;
class Player;
class Table;

class Game
{
	public:
		Client		*link_data_client;
		Client		*link_video_client;
		std::map<std::string, Table*>	all_tables;
		std::map<int, Client*>			uid_client_map;
		std::map<int, Client*>			fd_client_map;
		int			server_vid;
		int			server_zid;
	private:
		ev_io		_ev_accept;
		int			_fd;

		ev_timer	ev_reconnect_datasvr_timer;
		ev_tstamp   ev_reconnect_datasvr_tstamp;

		ev_timer	ev_reconnect_videosvr_timer;
		ev_tstamp   ev_reconnect_videosvr_tstamp;

		ev_timer	ev_reconnect_recoversvr_timer;
		ev_tstamp   ev_reconnect_recoversvr_tstamp;
	private:
		int init_accept();
		static void accept_cb(struct ev_loop *loop, struct ev_io *w, int revents);
		//连接数据服
		int connect_datasvr();
		void start_reconnect();
		static void reconnect_datasvr_cb(struct ev_loop *loop, struct ev_timer *w, int revents);
		int reconnect_datasvr();
		//连接录像服	
		int connect_videosvr();
		void start_videoreconnect();
		int reconnect_videosvr();
		static void reconnect_videosvr_cb(struct ev_loop *loop, struct ev_timer *w, int revents);
	public:
		Game();
		virtual ~Game();
		int start();
		//断开所有客户端
		void del_all_client();
		//登录
		int request_login( Client *client );
		int login_succ_back( Json::Value &val );
		int login_error_back(int uid, int code );
		int dz_login_error_back( Client *client, int code);
		//断开客户端
		void del_client(Client *client, bool del_oldclient=false);
		//删除玩家
		int del_player(Player *player);
		//平台协议
		int dispatch(Client *client);
		//客户端协议
		int dispatch2(Client *client);
		//安全检测
		int safe_check(Client *client, int cmd);
		//登录桌子
		int handler_login_table(Client *client, Json::Value &val);
		int login_table( Client *client, Json::Value &val);
		int login_table(Client *client, std::map<int, Table*> &a, std::map<int, Table*> &b);
		//游戏开始返回
		void game_start_res( Jpacket &packet );
		//发送登出房间
		void SendLogout(Client *client, int uid, int code);
		//发送数据给平台
		void send_to_datasvr( const std::string &res );
		void send_to_videosvr(const std::string &res);
		void send_to_recoversvr(const std::string &res);
		//玩家掉线信息
		void game_user_offline(Player *player);
		//后台请求删除房间
		bool DeleteRoomReq(std::string roomid);
	public:
		//保存数据到redis
		int save_data_to_redis(std::string tid, std::string data_str);
		//从redis拿数据
		int request_data_from_redis();
		//删除redis数据
		int del_data_from_redis(string tid);
};

#endif
