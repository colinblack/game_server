#ifndef __KFC_SYSTEM_H__
#define __KFC_SYSTEM_H__

/**
 * <p>进程、线程、锁等相关</p>
 */

#include "kfc_version.h"
#include "kfc_comm.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>
#include <string.h>

namespace kfc
{

	/**
	 * 初始化随机种子
	 */
	void init_rand();

	/*******************************************************************************************************
	 * 异步fifo 处理类
	 */
	struct fifo_fail: public std::runtime_error
	{
		fifo_fail(const std::string& s):std::runtime_error(s){}
	};
	struct fifo_delay: public std::runtime_error
	{
		fifo_delay(const std::string& s):std::runtime_error(s){}
	};
	class CFifo
	{
	public:
		CFifo();
		~CFifo();

	public:
		/**
		 * 打开fifo
		 * @param pathname:	fifo路径
		 * @param rorw: 		读还是写,true-读 false-写
		 * @throw fifo_fail: 
		 */
		void open(const char *pathname,bool rorw, mode_t mode=0777) throw(fifo_fail);
		/**
		 * 关闭fifo
		 */
		void close();
		int fd() { return _fd;}
		/**
		 * 读数据
		 * @param buffer
		 * @param max_size	buffer的大小
		 * @return 			读到的数据长度
		 * @throw fifo_fail:		fifo出错
		 * @throw fifo_delay:	EAGAIN
		 */
		int read(char * buffer,size_t max_size) throw(fifo_fail,fifo_delay);
		/**
		 * 写数据
		 * @param buffer
		 * @param buflen		待写的数据大小
		 * @return 			写入的数据长度
		 * @throw fifo_fail:		fifo出错
		 * @throw fifo_delay:	EAGAIN
		 */
		int write(const char *buffer,size_t buflen) throw(fifo_fail,fifo_delay);

	private:
		std::string _pathname;
		int _fd;
		bool _rorw;
	};

	/*******************************************************************************************************
	 * 非阻塞文件锁
	 */
	struct file_locked: public std::runtime_error
	{
		file_locked(const std::string& s):std::runtime_error(s){}
	};
	class CNBFileLock
	{
	public:
		CNBFileLock() {_fd = -1;}
		~CNBFileLock(){unLock();}

	public:
		/**
		 * 初始化文件锁
		 * @param filename
		 * @throw runtime_error:	打开文件失败
		 */
		void init(const std::string& filename) throw (std::runtime_error)
		{
			if(filename.empty()) throw std::runtime_error("kfc::CNBFileLock init: filename.empty");
			_fd = open(filename.c_str(), O_RDWR|O_CREAT, 0660);
			if(_fd<0) throw std::runtime_error(std::string("kfc::CNBFileLock init: open file failed:")+filename);
		}

		/**
		 * 锁文件
		 * @param filename
		 * @throw runtime_error:	打开文件失败
		 */
		void lock() throw (std::runtime_error,file_locked)
		{
			if(flock(_fd, LOCK_EX | LOCK_NB))
			{
				if(errno == EWOULDBLOCK) throw file_locked("kfc::CNBFileLock lock file is locked by other");
				throw std::runtime_error(std::string("kfc::CNBFileLock lock locking failed")+strerror(errno));
			}
		}

		/**
		 * 解锁
		 */
		void unLock() {if(_fd>0) flock(_fd, LOCK_UN);}
	private:
		int _fd;
	};

}

#endif

