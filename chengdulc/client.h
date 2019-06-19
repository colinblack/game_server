#ifndef __CLIENT_H__
#define __CLIENT_H__

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
#include <list>

#include <ev.h>
#include <json/json.h>

#include "jpacket.h"
#include "ppacket.h"

enum parse_state
{
	PARSE_HEADER    	= 0,
	PARSE_BODY      	= 1,
	PARSE_ERR       	= 2,
	PARSE_CROSS_DOMAIN	= 3
};

enum position_state
{
	POSITION_WAIT = 0,
	POSITION_TABLE
};

#ifndef MAX_BUF_LEN
#   define MAX_BUF_LEN (1024*8)
#endif

#ifndef DEF_BUF_LEN
#   define DEF_BUF_LEN (1024*8)
#endif

struct Buffer {
	char	*data;
	ssize_t len;
	ssize_t pos;
	Buffer(const char *bytes, ssize_t nbytes){
		pos = 0;
		len = nbytes;
		data = new char[nbytes];
		memcpy(data, bytes, nbytes);
	}
	virtual ~Buffer(){
		delete [] data;
	}
	char *dpos(){
		return data + pos;
	}
	ssize_t nbytes(){
		return len - pos;
	}
};

class Player;

class Client {
public:
	std::string   		string_ip;
	int                 cmd_type;
	std::string         body;
	int 				fd;
	int					is_err;
	int					uid;
	int					vid;
	int					zid;
	std::string			skey;
	Jpacket             packet;
	Ppacket				ppacket;
	Player*				player;
	int                 is_close;
	int					position;
	int					is_robot;
	int					is_rebind;//add20141023 when game over stay in the room ,if 1 ,do not judge the max money
	std::string         roomid;
	int			  		base_money;
	int			 		stand_money;
	int 				client_type;//通信格式 0--protobuf 1--json

private:
	int                 _state;
	ev_io 				_ev_write;
	ev_io 				_ev_read;

	ev_timer            _ev_nodata_timer;
	ev_tstamp           _ev_nodata_tstamp;

	std::list<Buffer*>  _write_q;
	char                _header[sizeof(struct Header)];
	char				p_header[sizeof(struct Pheader)];
	struct Header       *_header_p;
	unsigned int        _cur_head_len;
	unsigned int        _cur_policy_len;
	unsigned int		body_len;

public:
	Client(int fd_in, bool flag = true, int cli_type = 0);
	virtual ~Client();
	static void destroy(Client *client, bool del_oldclient=false);
	static void pre_destroy(Client *client, bool del_oldclient=false);
	static void read_cb(struct ev_loop *loop, struct ev_io *w, int revents);
	static void read_cb2(struct ev_loop *loop, struct ev_io *w, int revents);
	static void write_cb(struct ev_loop *loop, struct ev_io *w, int revents);
	static void nodata_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents);
	int send(const char *buf, unsigned int len);
	int send(const std::string &res);
	unsigned int safe_writen(const char *buf, unsigned int len);
	int update_timer(void);
	void set_positon(int pos);
};


#endif // endif __CLIENT_H__
