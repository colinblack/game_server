#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

#include "zjh.h"
#include "log.h"
#include "proto.h"
#include "table.h"
#include "player.h"
#include "client.h"
#include "game.h"

extern ZJH zjh;
extern Log log;

Player::Player() :
	_offline_timeout(5),
	_del_player_tstamp(3*60)
{
	_offline_timer.data = this;
	ev_timer_init(&_offline_timer, Player::offline_timeout, _offline_timeout, 0);	

	_del_player_timer.data = this;
	ev_timer_init(&_del_player_timer, Player::del_player_timer_cb, _del_player_tstamp, 0);

	vid = 0;
	zid = 0;
	tid.clear();
	seatid = -1;
	uid = 0;
	sex = 0;
	exp = 0;
	rmb = 0;
	money = 0;
	client = NULL;
	logout_type = 0;
	down_tag = 0;
	daemonize_flag = false;
	usertype = 0;
	dissolve_cnt = 0;
	is_offline = 0;
}

Player::~Player()
{
	ev_timer_stop(zjh.loop, &_offline_timer);
	ev_timer_stop(zjh.loop, &_del_player_timer);
	if (client)
	  client->player = NULL;
}

void Player::set_client(Client *c)
{
	client = c;
	vid = c->vid;
	zid = c->zid;
	client->player = this;
}

int Player::init( Json::Value &val )
{
	clear();
	uid = val["uid"].asInt();
	skey = val["skey"].asString();
	name = val["name"].asString();
	sex = val["sex"].asInt();
	avatar = val["avatar"].asString();
	rmb = val["rmb"].asInt();
	money = val["money"].asDouble();
	usertype = val["usertype"].asInt();
	if( money < 0 )
	{
		log.error( "player init error uid[%d] money[%d] .\n", uid, money );
		return -1;
	}
	return 0;
}

int Player::InitData( const proto::game::tagPlayers &pUserInfo )
{
	uid 					= pUserInfo.uid();
	tid						= pUserInfo.tid();
	seatid 					= pUserInfo.seatid();
	is_offline 				= pUserInfo.offline();
	skey 					= pUserInfo.skey();
	name 					= pUserInfo.name();
	sex	 					= pUserInfo.sex();
	avatar 					= pUserInfo.avatar();
	money 					= pUserInfo.money();
	dissolve_cnt 			= pUserInfo.dissolve_cnt();
	dissovle_state 			= pUserInfo.dissovle_state();

	log.info("player[%d] Init Data succ\n", uid);
	return 0;
}

void Player::reset()
{
	stop_offline_timer();
	dissolve_cnt = 0;
	//dissovle_state = 2;
}

void Player::clear()
{
	down_tag = 0;
	stop_offline_timer();
	seatid = -1;
	dissolve_cnt = 0;
	dissovle_state = 2;
}

void Player::start_offline_timer()
{
	ev_timer_start(zjh.loop, &_offline_timer);
}

void Player::stop_offline_timer()
{
	ev_timer_stop(zjh.loop, &_offline_timer);
}

void Player::offline_timeout(struct ev_loop *loop, ev_timer *w, int revents)
{
	Player* self = (Player*) w->data;
	log.info("offline timeout player uid[%d] seatid[%d] money[%ld] tid[%s].\n", self->uid, self->seatid, self->money, self->tid.c_str());
	ev_timer_stop(zjh.loop, &self->_offline_timer);
	self->is_offline = 1;
	if( zjh.game->all_tables.find(self->tid) != zjh.game->all_tables.end() )
	{
		zjh.game->all_tables[self->tid]->handler_offline(self);
	}
	else
	{
		zjh.game->del_player(self);
	}
}

void Player::start_del_player_timer()
{
	ev_timer_start(zjh.loop, &_del_player_timer);
}

void Player::stop_del_player_timer()
{
	ev_timer_stop(zjh.loop, &_del_player_timer);
}

void Player::del_player_timer_cb(struct ev_loop *loop, ev_timer *w, int revents)
{
	Player* self = (Player*)w->data;
	ev_timer_stop(zjh.loop, &self->_del_player_timer);
	zjh.game->del_player(self);
}

