#ifndef __KFC_EPOLL_H__
#define __KFC_EPOLL_H__

#include <errno.h>
#include <assert.h>
#include <sys/epoll.h>

#include "kfc_version.h"

namespace kfc
{

//////////////////////////////////////////////////////////////////////////

class CEPollResult;

class CEPoller
{
public:

	CEPoller() : _fd(-1), _events(NULL)
	{
	}

	~CEPoller()
	{
		if(_events) delete[] _events;
		close(_fd);
	}

	void create(unsigned int iMaxFD) throw(std::runtime_error);
	void add(int fd, int flag = EPOLLIN | EPOLLET);
	void del(int fd);
	CEPollResult wait(int iTimeout) throw(std::runtime_error);

protected:
	void ctl(int fd, int epollAction, int flag) throw(std::runtime_error);

	int _fd;
	epoll_event* _events;
	unsigned int _maxFD;
};

//////////////////////////////////////////////////////////////////////////

class CEPollResult
{
public:

	~CEPollResult()
	{
	}

	CEPollResult(const CEPollResult& right) : _events(right._events), _size(right._size)
	{
	}

	CEPollResult& operator=(const CEPollResult& right)
	{
		_events = right._events;
		_size = right._size;
		return *this;
	}

	class iterator;

	iterator begin()
	{
		return CEPollResult::iterator(0, *this);
	}

	iterator end()
	{
		return CEPollResult::iterator(_size, *this);
	}

protected:

	CEPollResult(epoll_event* events, unsigned int size) : _events(events), _size(size)
	{
	}

	bool operator==(const CEPollResult& right)
	{
		return(_events == right._events && _size == right._size);
	}

	epoll_event* _events;
	unsigned int _size;

public:

	class iterator
	{
	public:

		iterator(const iterator& right) : _index(right._index), _res(right._res)
		{
		}

		iterator& operator ++()
		{
			_index++;
			return *this;
		}

		iterator& operator ++(int)
		{
			_index++;
			return *this;
		}

		bool operator ==(const iterator& right)
		{
			return(_index == right._index && _res == right._res);
		}

		bool operator !=(const iterator& right)
		{
			return !(_index == right._index && _res == right._res);
		}

		epoll_event* operator->()
		{
			return &_res._events[_index];
		}

		epoll_event& operator*()
		{
			return _res._events[_index];
		}

	protected:

		iterator(unsigned int index, CEPollResult& res) : _index(index), _res(res)
		{
		}
		unsigned int _index;
		CEPollResult& _res;
		friend class CEPollResult;
	};

	friend class CEPoller;
	friend class CEPollResult::iterator;
};

//////////////////////////////////////////////////////////////////////////
//	implementation
//////////////////////////////////////////////////////////////////////////

inline void CEPoller::create(unsigned int iMaxFD) throw(std::runtime_error)
{
	_maxFD = iMaxFD;
	//_fd = epoll_create(1024);
	_fd = epoll_create(_maxFD);
	if(_fd == -1)
		throw std::runtime_error(std::string("kfc::CEPoller::create ") + strerror(errno));
	_events = new epoll_event[iMaxFD];
}

inline void CEPoller::add(int fd, int flag)
{
	ctl(fd, EPOLL_CTL_ADD, flag);
}

inline void CEPoller::del(int fd)
{
	ctl(fd, EPOLL_CTL_DEL, 0);
}

inline CEPollResult CEPoller::wait(int iTimeout) throw(std::runtime_error)
{
	int nfds = epoll_wait(_fd, _events, _maxFD, iTimeout);
	if(nfds < 0)
	{
		if(errno != EINTR)
			throw std::runtime_error(std::string("kfc::CEPoller::wait ") + strerror(errno));
		else
			nfds = 0;
	}
	return CEPollResult(_events, nfds);
	;
}

inline void CEPoller::ctl(int fd, int epollAction, int flag) throw(std::runtime_error)
{
	assert(_fd != -1);
	epoll_event ev;
	ev.data.fd = fd;
	ev.events = flag;
	int ret = epoll_ctl(_fd, epollAction, fd, &ev);
	if(ret < 0)
		throw std::runtime_error(std::string("kfc::CEPoller::ctl ") + strerror(errno));
}

}

#endif
