#ifndef __KFC_COMM_H__
#define __KFC_COMM_H__

#include <string>
#include <time.h>
#include <cstdio>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <cstdlib>
#include <cctype>
#include <sstream>
#include <utility>
#include <stdexcept>

using namespace std;

namespace kfc
{

	struct comm_error : public logic_error
	{
		comm_error(const string & s);
	};

	/**
	 * Daemon进程
	 */
	void Daemon();

	/**
	 * 一个字符串是否全部为数字(0-9)
	 * @param s 输入字符串
	 * @return true/false
	 */
	inline bool
	is_digits(const std::string& s)
	{
		if(s.length() == 0)	return false;
		for(size_t i = 0; i < s.length(); i++)
		{
			if(!isdigit(s.c_str()[i])) return false;
		}
		return true;
	}

	/**
	 * 一个字符串是否全部为16进制数字(0-9/a-f/A-F)
	 * @param s 输入字符串
	 * @return true/false
	 */
	inline bool
	is_xdigits(const std::string& s)
	{
		if(s.length() == 0)	return false;
		for(size_t i = 0; i < s.length(); i++)
		{
			if(!isxdigit(s.c_str()[i]))	return false;
		}
		return true;
	}

	/**
	 * @param s 输入字符串
	 * @param filt filt串
	 * @return string trim后的值
	 */
	std::string trim_left(const std::string &s, const std::string& filt = " ");

	/**
	 * @param s 输入字符串
	 * @param filt filt串
	 * @return string trim后的值
	 */
	std::string trim_right(const std::string &s, const std::string& filt = " ");

	/**
	 * trim_left+trim_right
	 * @param s 输入字符串
	 * @param filt filt串
	 * @return string trim后的值
	 */
	inline std::string
	trim(const std::string &s, const std::string& filt = " ")
	{
		return trim_right(trim_left(s, filt), filt);
	}

	/**
	 * 转为大小
	 */
	inline string
	upper(const string &s)
	{
		string s2;
		for(size_t i = 0; i < s.length(); i++)
		{
			s2 += ((unsigned char) toupper(s.c_str()[i]));
		}
		return s2;
	}

	/**
	 * 转为小写
	 */
	inline string
	lower(const string &s)
	{
		string s2;
		for(size_t i = 0; i < s.length(); i++)
		{
			s2 += ((unsigned char) tolower(s.c_str()[i]));
		}
		return s2;
	}

	/**
	 * 时间字段
	 * @see #time_add
	 */
	enum TimeField
	{
		Year, Month, Day, Hour, Minute, Second
	};

	/**
	 * 时间处理函数
	 * @param t 源时间
	 * @param f 时间字段
	 * @param i 加的值,可为负数表示减
	 * @return time_t <0时表示超出范围
	 */
	inline time_t
	time_add(time_t t, TimeField f, int i)
	{
		struct tm curr;
		switch(f)
		{
			case Second:
				return t + i;
			case Minute:
				return t + i * 60;
			case Hour:
				return t + i * 60 * 60;
			case Day:
				return t + i * 60 * 60 * 24;
			case Month:
				curr = *localtime(&t);
				curr.tm_year += (curr.tm_mon - 1 + i) / 12;
				curr.tm_mon = (curr.tm_mon - 1 + i) % 12 + 1;
				return mktime(&curr);
			case Year:
				curr = *localtime(&t);
				curr.tm_year += i;
				return mktime(&curr);
			default:
				return 0;
		}

		return 0;
	}

	/**
	 * 通用模板方法: 类型T转为字符串
	 * @param t 类型T的对象
	 * @return 字符串
	 */
	template<typename T> std::string
	tostr(const T& t)
	{
		std::ostringstream s;
		s << t;
		return s.str();
	}

	/**
	 * 通用模板方法: pair转为字符串
	 * @param it  map等容器的iterator
	 * @return 字符串
	 */
	template<typename F, typename S> std::string
	tostr(const std::pair<F, S>& it)
	{
		std::ostringstream s;
		s << "[" + (it.first) + "=" + (it.second) + "]";
		return s.str();
	}

	/**
	 * 通用模板方法: iterator转为字符串
	 * @param itbegin  容器的iterator begin
	 * @param itend  容器的iterator end
	 * @return 字符串
	 */
	template <typename I> std::string
	tostr(I itbegin, I itend)
	{
		std::string s;
		I it = itbegin;
		for(I it = itbegin; it != itend; it++)
		{
			s.append(tostr(*it));
			s.append(" ");
		}
		return s;
	}

	/**
	 * 通用模板方法: 字符串转为类型T
	 * @param s
	 * @return T 类型T
	 */
	template<typename T> T
	strto(const std::string& s)
	{
		std::istringstream is(s);
		T t;
		is >> t;
		return t;
	}

	/*******************************************************************************************************
	 * 简易用法
	 */

	/**
	 * unsigned转string
	 * @see #s2u
	 */
	inline string
	u2s(const unsigned u)
	{
		char sTmp[64] = {0};
		sprintf(sTmp, "%u", u);
		return string(sTmp);
	}

	/**
	 * unsigned long转string
	 * @see #s2ul
	 */
	inline string
	ul2s(const unsigned long u)
	{
		char sTmp[64] = {0};
		sprintf(sTmp, "%lu", u);
		return string(sTmp);
	}

	/**
	 * unsigned转string(16进制形式)
	 * @see #sx2u
	 */
	inline string
	u2sx(const unsigned u)
	{
		char sTmp[64] = {0};
		sprintf(sTmp, "%x", u);
		return string(sTmp);
	}

	/**
	 * unsigned long转string(16进制形式)
	 * @see #sx2ul
	 */
	inline string
	ul2sx(const unsigned long u)
	{
		char sTmp[64] = {0};
		sprintf(sTmp, "%lx", u);
		return string(sTmp);
	}

	/**
	 * int转string
	 * @see #s2i
	 */
	inline string
	i2s(const int i)
	{
		char sTmp[64] = {0};
		sprintf(sTmp, "%d", i);
		return string(sTmp);
	}

	/**
	 * long转string
	 * @see #s2l
	 */
	inline string
	l2s(const long i)
	{
		char sTmp[64] = {0};
		sprintf(sTmp, "%ld", i);
		return string(sTmp);
	}

	/**
	 * char转string
	 * @see #s2c
	 */
	inline string
	c2s(const char c)
	{
		if(c == 0) return string("");
		return string() + c;
	}

	/**
	 * binary->string
	 * @param b binary指针
	 * @param len binary长度
	 * @param block 显示格式<br>
	 *                      =0格式为"00 01 02 ..." <br>
	 *                      >0格式为(以8为例)"0000h: 00 01 02 03 04 05 06 07 08  09 0a 0b 0c 0d 0e 0f" <br>
	 *                                      "0010h: 10 11 12 13 14 15 16 17 18  19 1a 1b 1c 1d 1e 1f" <br>
	 * @return string 得到的格式串
	 * @see #s2b
	 */
	string b2s(const char *b, size_t len, unsigned block = 8);

	/**
	 * time_t->string
	 * @param t 时间值
	 * @param format 显示格式,参见date指令格式
	 * @return string 得到的格式串
	 * @s2t
	 */
	inline string
	t2s(const time_t t, const string& format = "%Y-%m-%d %H:%M:%S")
	{
		struct tm curr;
		curr = *localtime(&t);
		char sTmp[1024];
		strftime(sTmp, sizeof(sTmp), format.c_str(), &curr);
		return string(sTmp);
	}

	/**
	 * now->string
	 * @param format 显示格式,参见date指令格式
	 * @return string 得到的格式串
	 * @see #t2s
	 */
	inline string
	now(const string& format = "%Y-%m-%d %H:%M:%S")
	{
		return t2s(time(0), format);
	}

	/**
	 * string转unsigned
	 * @throw comm_error string格式不是unsigned
	 * @see #u2s
	 */
	unsigned s2u(const std::string &s) throw(comm_error);

	/**
	 * string转unsigned (格式不对时设为默认值)
	 * @see #u2s
	 */
	unsigned s2u(const std::string &s, unsigned defaultvalue);

	/**
	 * string转unsigned long
	 * @throw comm_error string格式不是unsigned long
	 * @see #ul2s
	 */
	unsigned long s2ul(const std::string &s) throw(comm_error);
	/**
	 * string转unsigned long(格式不对时设为默认值)
	 * @see #ul2s
	 */
	unsigned long s2ul(const std::string &s, unsigned long defaultvalue);

	/**
	 * 16进制格式string转unsigned,支持的格式为0x+字符串或者直接为字符串
	 * @throw comm_error string格式不是unsigned
	 * @see #u2sx
	 */
	unsigned sx2u(const std::string &s) throw(comm_error);

	/**
	 * 16进制格式string转unsigned long,支持的格式为0x+字符串或者直接为字符串
	 * @throw comm_error string格式不是unsigned
	 * @see #ul2sx
	 */
	unsigned long sx2ul(const std::string &s) throw(comm_error);

	/**
	 * 16进制格式string转unsigned (格式不对时设为默认值)
	 * @see #u2sx
	 */
	unsigned sx2u(const std::string &s, unsigned defaultvalue);

	/**
	 * 16进制格式string转unsigned long(格式不对时设为默认值)
	 * @see #ul2sx
	 */
	unsigned long sx2ul(const std::string &s, unsigned long defaultvalue);

	/**
	 * string转int
	 * @throw comm_error string格式不是unsigned
	 * @see #i2s
	 */
	int s2i(const std::string &s) throw(comm_error);

	/**
	 * string转int (格式不对时设为默认值)
	 * @see #i2s
	 */
	int s2i(const std::string &s, int defaultvalue);

	/**
	 * string转long
	 * @throw comm_error string格式不是long
	 * @see #l2s
	 */
	long s2l(const std::string &s) throw(comm_error);

	/**
	 * string转int (格式不对时设为默认值)
	 * @see #l2s
	 */
	long s2l(const std::string &s, long defaultvalue);

	/**
	 * string转char (取string第一位)
	 * @see #c2s
	 */
	char s2c(const std::string &s);

	/**
	 * string转char (string为""时返回默认值)
	 * @see #c2s
	 */
	char s2c(const std::string &s, char defaultvalue);

	/**
	 * string转binary,支持的格式"00 01 ..."或"0001..."或"%00%01..."
	 * @throw comm_error string格式不对
	 * @return size_t binary大小
	 * @see #b2s
	 */
	size_t s2b(const std::string &s, char *b, size_t maxlen) throw(comm_error);

	/**
	 * string转time_t
	 * @throw comm_error string格式不对
	 * @return time_t 返回时间
	 * @see #t2s
	 */

	time_t s2t(const std::string &s, const std::string& format = "%Y-%m-%d %H:%M:%S") throw(comm_error);

	/**
	 * 根据split去掉string的头,类似GetToken<br>
	 * 如string s = "ab cd ef", trim(s)返回ab，s则变为"cd ed"
	 * @param s 源字符串,输出为cut之后的字符串
	 * @param split 分隔符
	 * @return 头
	 */
	string trim_head(string& s, const string& split = " \t");

}

#endif
