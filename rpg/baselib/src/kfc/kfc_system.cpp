
#include "kfc_system.h"

using namespace std;

void kfc::init_rand()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_usec);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CFifo
kfc::CFifo::CFifo()
{
	_fd = -1;
	_rorw = true;
}

kfc::CFifo::~CFifo()
{
	close();
}

void kfc::CFifo::close()
{
	if(_fd>0) {
		::close(_fd); 
		_fd = -1;
	}
}

void kfc::CFifo::open(const char *pathname, bool rorw, mode_t mode) throw(kfc::fifo_fail)
{
	_rorw = rorw;
	_pathname = pathname;
	if(mkfifo(pathname,mode)) {
		if(errno == EEXIST) {
			//cout << "fifo: " << pathname << " exist" << endl;
		} else {
			throw kfc::fifo_fail(string("kfc::CFifo open mkfifo ")+pathname+":"+strerror(errno));
		}
	}
	if(rorw) {
		_fd = ::open(pathname,O_NONBLOCK|O_RDONLY,0664);
		if(_fd < 0) {
			throw kfc::fifo_fail(string("kfc::CFifo open read ")+_pathname+":"+strerror(errno));
		}
	} else {
		_fd = ::open(pathname,O_NONBLOCK|O_WRONLY,0664);
		if(_fd < 0) {
			if(errno == ENXIO) {
				//cout << "open fifo for write but no reading" << endl;
				return;
			}
			throw kfc::fifo_fail(string("kfc::CFifo open write ")+_pathname+":"+strerror(errno));
		}
	}
}

int kfc::CFifo::read(char * buffer,size_t max_size) throw(kfc::fifo_fail,kfc::fifo_delay)
{
	int iRetVal;
	for(;;) {
		iRetVal = ::read(_fd,buffer,max_size);
		if(iRetVal<0) {
			if(errno == EINTR) {
				//cerr << "CFifo:read EINTR" << endl;
				continue;
			}
			else if(errno == EAGAIN) { //
				//cerr << "CFifo:read EAGAIN" << endl;
				throw kfc::fifo_delay("kfc::CFifo read "+_pathname+" EAGAIN");
			}
			else {
				throw kfc::fifo_fail(string("kfc::CFifo read ")+_pathname+":"+strerror(errno));
			}
		} else if(iRetVal==0) {
			throw kfc::fifo_fail("kfc::CFifo read "+_pathname+":closed by peer");
		} else {
			break;
		}
	}

	return iRetVal;
}

int kfc::CFifo::write(const char *buffer,size_t buflen) throw(kfc::fifo_fail,fifo_delay)
{
	if(buflen == 0) return 0;

	if(_fd<0 && (!_rorw)) {
		// re open fifo
		_fd = ::open(_pathname.c_str(),O_NONBLOCK|O_WRONLY,0664);
		if(_fd < 0) {
			if(errno == ENXIO) {
				throw fifo_delay(string("kfc::CFifo write open ")+_pathname+":"+strerror(errno));
			}
			throw kfc::fifo_fail(string("kfc::CFifo write open ")+_pathname+":"+strerror(errno));
		}
	}

	for(;;) {
		int iRetVal = ::write(_fd,buffer,buflen);
		if(iRetVal<0) {
			if(errno == EINTR) {
//				cerr << "CFifo:read EINTR" << endl;
				continue;
			}
			else if(errno == EAGAIN || errno == EPIPE) { //
//				cerr << "CFifo:write EAGAIN" << endl;
				throw kfc::fifo_delay(string("kfc::CFifo write ")+_pathname+" EAGAIN|EPIPE:"+strerror(errno));
			}
			else {
				throw kfc::fifo_fail(string("kfc::CFifo write ")+_pathname+":"+strerror(errno));
			}
		} else if(iRetVal==0) {
			throw kfc::fifo_fail("kfc::CFifo write "+_pathname+":closed by peer");
		} else {
			return iRetVal;
		}
	}

	return 0;
}

