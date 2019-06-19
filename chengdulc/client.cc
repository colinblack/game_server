#include "zjh.h"
#include "game.h"
#include "client.h"
#include "proto.h"
#include "log.h"

extern ZJH zjh;
extern Log log;

char policy_cross_domain[] = "<cross-domain-policy>\
							  <allow-access-from domain=\"*\" to-ports=\"*\" /></cross-domain-policy>\0";
char policy_file[] = "<policy-file-request/>";

Client::Client(int fd_in, bool flag, int cli_type) :
	_ev_nodata_tstamp( 10 )
{
	/* set state */
	_state = PARSE_HEADER;
	_cur_head_len = 0;
	_cur_policy_len = 0;
	body_len = 0;
	_header_p = (struct Header*) _header;
	is_close = 0;
	fd = fd_in;
	is_err = 0;
	uid = -1;
	player = NULL;
	position = POSITION_WAIT;
	is_robot=0;
	zid = 0;
	vid = 0;
	cmd_type = 0;
	client_type = cli_type;
	_ev_read.data = this;
	log.info("client_type: %d \n", client_type);
	if (client_type == 1) {
		ev_io_init(&_ev_read, Client::read_cb, fd, EV_READ);
	}else{
		ev_io_init(&_ev_read, Client::read_cb2, fd, EV_READ);
	}
	ev_io_start(zjh.loop, &_ev_read);
	ev_io_init(&_ev_write, Client::write_cb, fd, EV_WRITE);

	_ev_nodata_timer.data = this;
	ev_timer_init(&_ev_nodata_timer, Client::nodata_timer_cb, _ev_nodata_tstamp, _ev_nodata_tstamp);
	if( flag )
	{
		ev_timer_start(zjh.loop, &_ev_nodata_timer);
	}
	log.debug("client[%d] open\n", fd);
}

Client::~Client()
{
	ev_io_stop(zjh.loop, &_ev_read);
	ev_io_stop(zjh.loop, &_ev_write);
	ev_timer_stop(zjh.loop, &_ev_nodata_timer);
	while (!_write_q.empty()) {
		delete (_write_q.front());
		_write_q.pop_front();
	}
	close(fd);
	log.info("~client fd[%d] uid[%d] destrutor\n", fd, uid);
}

void Client::destroy(Client *client, bool del_oldclient)
{
	if (client == NULL)
	{
		log.error("destroy client error, client is NULL \n");
		return;
	}
	log.info("client destroy fd[%d] uid[%d] destroy\n", client->fd, client->uid);
	zjh.game->del_client(client, del_oldclient);
}

void Client::pre_destroy(Client *client, bool del_oldclient)
{
	if (client == NULL)
	{
		log.error("pre destroy client is NULL \n");
		return;
	}
	if (client->_write_q.empty())
	{
		Client::destroy(client, del_oldclient);
	}
	else
	{
		log.info("pre destroy client[%d] uid[%d] list is not empty \n", client->fd, client->uid );
		if (del_oldclient){
			client->cmd_type = 1;
		}else{
			client->is_close = 1;
		}
	}
}

void Client::read_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	log.info(" read_cb \n");
	int ret;
	static char recv_buf[DEF_BUF_LEN];
	Client *self = (Client*) w->data;
	self->update_timer();

	if (self->_state == PARSE_HEADER) {
		ret = read(self->fd, &self->_header[self->_cur_head_len],
					sizeof(struct Header) - self->_cur_head_len);
		if (ret < 0) {
			if (errno == EAGAIN || errno == EINPROGRESS || errno == EINTR) {
				log.warn("read cb read header failed[%s]\n", strerror(errno));
				return;
			}
			log.error("read header failed[%s]\n", strerror(errno));
			Client::destroy(self);
			return;
		}

		if (ret == 0) {
			log.error("connection close in read header[%d]\n", self->fd);
			Client::destroy(self);
			return;
		}

		if (self->_header[0] == '<' && self->_header[1] == 'p'
					&& self->_header[2] == 'o' && self->_header[3] == 'l') {
			self->_state = PARSE_CROSS_DOMAIN;
			self->_cur_head_len = 0;
			self->_cur_policy_len = 4;
			return;
		}

		self->_cur_head_len += ret;
		//		cout<<"self->_header_p->length"<<self->_header_p->length<<endl;
		if (self->_cur_head_len == sizeof(self->_header)) {
			if (self->_header_p->length > MAX_BUF_LEN
						|| self->_header_p->length == 0) {
				log.error("fd[%d] recv an error len package[%d]\n", self->fd, self->_header_p->length);
				Client::destroy(self);
				return;
			}
			self->_state = PARSE_BODY;
			self->_cur_head_len = 0;
			self->body.clear();
		}
	} else if (self->_state == PARSE_BODY){
		ret = read(self->fd, recv_buf, self->_header_p->length - self->body.length());
		if (ret < 0) {
			if (errno == EAGAIN || errno == EINPROGRESS || errno == EINTR) {
				log.debug("read body failed[%s]\n", strerror(errno));
				return;
			}
			log.error("read body failed[%s]\n", strerror(errno));
			Client::destroy(self);
			return;
		}

		if (ret == 0) {
			log.error("connection close in read body[%d]\n", self->fd);
			Client::destroy(self);
			return;
		}

		recv_buf[ret] = '\0';
		self->body.append(recv_buf);

		if (self->body.length() == self->_header_p->length) {
			self->_state = PARSE_HEADER;
			if (self->packet.parse(self->body) < 0) {
				log.error("parse err!!\n");
				Client::destroy(self);
				return;
			}

			time_t begin = time(NULL);
			int ret = zjh.game->dispatch(self);
			time_t end = time(NULL);
			int total = end - begin;
			if (total >= 1) {
				log.error("slow cmd: [%d]\n", total);
			}
			if (ret < 0) {
				log.error("dispatch err\n");
				pre_destroy(self);
				return;
			}
			if (self->is_err == 1) {
				log.error("client is err\n");
				Client::destroy(self);
			}
		}
	} else if (self->_state == PARSE_CROSS_DOMAIN) {
		ret = read(self->fd, recv_buf, sizeof(policy_file) - self->_cur_policy_len);
		if (ret <= 0) {
			if (errno == EAGAIN || errno == EINPROGRESS || errno == EINTR) {
				log.warn("read body failed[%s]\n", strerror(errno));
				return;
			}
			log.error("read body failed[%s]\n", strerror(errno));
			Client::destroy(self);
			return;
		}
		if (ret == 0) {
			log.info("connection close in read body[%d]\n", self->fd);
			Client::destroy(self);
			return;
		}

		self->_cur_policy_len += ret;
		if (self->_cur_policy_len == sizeof(policy_file)) {
			/* completed */
			self->_state = PARSE_HEADER;
			self->_cur_policy_len = 0;
			self->send(policy_cross_domain, sizeof(policy_cross_domain));
			return;
		}
	}
}

void Client::read_cb2(struct ev_loop *loop, struct ev_io *w, int revents)
{
	int ret;
	static char recv_buf[DEF_BUF_LEN];
	Client *self = (Client*) w->data;
	self->update_timer();
	if (self->_state == PARSE_HEADER) {
		ret = read(self->fd, &self->p_header[self->_cur_head_len],
					sizeof(struct Pheader) - self->_cur_head_len);
		if (ret < 0) {
			if (errno == EAGAIN || errno == EINPROGRESS || errno == EINTR) {
				log.warn("read cb read header failed[%s]\n", strerror(errno));
				return;
			}
			log.error("read header failed[%s]\n", strerror(errno));
			Client::destroy(self);
			return;
		}
		if (ret == 0) {
			log.error("connection close in read header[%d]\n", self->fd);
			Client::destroy(self);
			return;
		}
		self->_cur_head_len += ret;
		if (self->_cur_head_len == sizeof(self->p_header)) {
			int m_body_len = ((struct Pheader*)(self->p_header))->length;

			if (m_body_len > MAX_BUF_LEN || m_body_len < 0) {
				log.error("fd[%d] recv an error len package[%d]\n", self->fd, m_body_len);
				Client::destroy(self);
				return;
			}
			self->_state = PARSE_BODY;
			self->_cur_head_len = 0;
			self->body_len = m_body_len;
			self->body.clear();
			//如果包体为空 直接进入协议处理
			if (m_body_len == 0) {
				goto dealer;
			}
		}
	} else if (self->_state == PARSE_BODY){
		//包体可能为空
		if (self->body_len != 0) {
			ret = read(self->fd, recv_buf, self->body_len - self->body.length());
			if (ret < 0) {
				if (errno == EAGAIN || errno == EINPROGRESS || errno == EINTR) {
					log.debug("read body failed[%s]\n", strerror(errno));
					return;
				}
				log.error("read body failed[%s]\n", strerror(errno));
				Client::destroy(self);
				return;
			}
			if (ret == 0) {
				log.error("connection close in read body[%d]\n", self->fd);
				Client::destroy(self);
				return;
			}
			self->body.append(recv_buf, ret);
		}
		if (self->body.length() == self->body_len) {
dealer:		self->_state = PARSE_HEADER;
			if (self->ppacket.save((struct Pheader*)(self->p_header), self->body) < 0) {
				log.error("client[%d] save buf err!!\n", self->fd);
				Client::destroy(self);
				return;
			}
			time_t begin = time(NULL);
			int ret = zjh.game->dispatch2(self);
			time_t end = time(NULL);
			int total = end - begin;
			if (total >= 1) {
				log.error("slow cmd: [%d]\n", total);
			}
			if (ret < 0) {
				log.error("dispatch err\n");
				pre_destroy(self);
				return;
			}
			if (self->is_err == 1) {
				log.error("client is err\n");
				Client::destroy(self);
			}
		}
	}
}

void Client::write_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	Client *self = (Client*) w->data;
	if (self->_write_q.empty()) {
		//log.debug("stop write event\n");
		ev_io_stop(EV_A_ w);
		if (self->is_close == 1) {
			Client::destroy(self);
			return;
		}
		if (self->cmd_type == 1) {
			Client::destroy(self, true);
			return;
		}
		return;
	}

	Buffer* buffer = self->_write_q.front();
	ssize_t written = write(self->fd, buffer->dpos(), buffer->nbytes());
	if (written < 0) {
		if (errno == EAGAIN || errno == EINPROGRESS || errno == EINTR) {
			log.warn("write failed[%s]\n", strerror(errno));
			return;
		}
		/* todo close this client */
		log.error("unknow err in written [%d]\n", self->fd);
		Client::destroy(self);
		return;
	}

	buffer->pos += written;
	if (buffer->nbytes() == 0) {
		self->_write_q.pop_front();
		delete buffer;
	}

}

void Client::nodata_timer_cb(struct ev_loop *loop, struct ev_timer *w, int revents)
{
	Client *self = (Client*)w->data;
	log.info("nodata_timer_cb client fd[%d] uid[%d] timeout\n", self->fd, self->uid);
	Client::pre_destroy(self);
}

int Client::send(const char *buf, unsigned int len)
{
	if (fd > 0) {
		if (_write_q.empty()) {
			_ev_write.data = this;
			ev_io_start(zjh.loop, &_ev_write);
		}
		_write_q.push_back(new Buffer(buf, len));
		return 0;
	}
	return -1;
}

int Client::send(const std::string &res)
{
	if (client_type == 0) 
	{
		std::string header_str ;
		header_str.append((const char*)res.c_str(), sizeof(struct Pheader));
		int cmd = ((struct Pheader*)(header_str.c_str()))->cmd;
		if( cmd != CLINET_HEART_BEAT_REQ && cmd != SERVER_HEART_BEAT_RES ) //排除心跳
		{
			log.info("client[%d] uid[%d] sendData cmd[%d] \n",fd, uid, cmd);
		}
	}
	else
	{
		if (res.length() > 4) 
		{
			Jpacket pac;
			std::string body_str;
			body_str.append(res, 4, res.length());
			if( (pac.parse(body_str) >= 0) && !(pac.val["cmd"].isNull()) && pac.val["cmd"].isNumeric() )
			{
				int cmd = pac.val["cmd"].asInt();
				if( cmd != CLINET_HEART_BEAT_REQ && cmd != SERVER_HEART_BEAT_RES ) //排除心跳
				{
					log.info("client[%d] uid[%d] sendData cmd[%d] \n", fd, uid, cmd);
				}
			}
		}
	}
	return send(res.c_str(), res.length());
}

unsigned int Client::safe_writen(const char *buf, unsigned int len)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;

	ptr = (char*) buf;
	nleft = len;

	while (nleft > 0) {
		nwritten = write(fd, ptr, nleft);
		if (nwritten <= 0) {
			if (errno == EINTR)
			  nwritten = 0;
			else {
				is_err = 1;
				return -1;
			}
		}
		nleft -= nwritten;
		ptr += nwritten;
	}

	return len;
}

int Client::update_timer()
{
	if( (zjh.game->link_data_client && fd == zjh.game->link_data_client->fd)
				|| (zjh.game->link_video_client && fd == zjh.game->link_video_client->fd))
	{
		return 0;
	}
	ev_timer_again(zjh.loop, &_ev_nodata_timer);
	return 0;
}

void Client::set_positon(int pos)
{
	position = pos;
}
