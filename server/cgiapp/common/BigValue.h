/*
 * BigValue.h
 *
 *  Created on: 2018年12月13日
 *      Author: Ralf
 */

#ifndef APP_COMMON_BIGVALUE_H_
#define APP_COMMON_BIGVALUE_H_

#include "Common.h"

#define BIG_VALUE_KEEP double(100)
#define BIG_VALUE_KEEP_S "00"
#define BIG_VALUE_KEEP_T 2

class BigValue
{
public:
	BigValue()
	{
		neg = false;
	}
	BigValue(const BigValue& other)
	{
		neg = other.Neg();
		val = other.Val();
	}
	BigValue(double s)
	{
		neg = s < 0;
		val = CTrans::ITOS(Math::Abs(int(double(s) * BIG_VALUE_KEEP)));
		reverse(val);
	}
	BigValue(float s)
	{
		neg = s < 0;
		val = CTrans::ITOS(Math::Abs(int(double(s) * BIG_VALUE_KEEP)));
		reverse(val);
	}
	BigValue(int8_t s)
	{
		neg = s < 0;
		val = CTrans::ITOS(Math::Abs(int(double(s) * BIG_VALUE_KEEP)));
		reverse(val);
	}
	BigValue(int16_t s)
	{
		neg = s < 0;
		val = CTrans::ITOS(Math::Abs(int(double(s) * BIG_VALUE_KEEP)));
		reverse(val);
	}
	BigValue(int32_t s)
	{
		neg = s < 0;
		val = CTrans::ITOS(Math::Abs(int(double(s) * BIG_VALUE_KEEP)));
		reverse(val);
		++s;
	}
	BigValue(int64_t s)
	{
		neg = s < 0;
		val = CTrans::ITOS(Math::Abs(int(double(s) * BIG_VALUE_KEEP)));
		reverse(val);
	}
	BigValue(uint8_t s)
	{
		neg = false;
		val = CTrans::UTOS(unsigned(double(s) * BIG_VALUE_KEEP));
		reverse(val);
	}
	BigValue(uint16_t s)
	{
		neg = false;
		val = CTrans::UTOS(unsigned(double(s) * BIG_VALUE_KEEP));
		reverse(val);
	}
	BigValue(uint32_t s)
	{
		neg = false;
		val = CTrans::UTOS(unsigned(double(s) * BIG_VALUE_KEEP));
		reverse(val);
	}
	BigValue(uint64_t s)
	{
		neg = false;
		val = CTrans::UTOS(unsigned(double(s) * BIG_VALUE_KEEP));
		reverse(val);
	}
	BigValue(const string& s)
	{
		neg = false;
		val = s;
		val.append(BIG_VALUE_KEEP_S);
		reverse(val);
		normalize();
	}
	BigValue(const char* s)
	{
		neg = false;
		val = string(s);
		val.append(BIG_VALUE_KEEP_S);
		reverse(val);
		normalize();
	}

	bool Neg() const
	{
		return neg;
	}
	const string& Val() const
	{
		return val;
	}
	double Real() const
	{
		string s = val;
		reverse(s);
		double v = CTrans::STOF(s);
		v = v / BIG_VALUE_KEEP;
		if(neg)
			v = -v;
		return v;
	}
	int64_t Int() const
	{
		int64_t v = CTrans::STOI64(str());
		if(neg)
			v = -v;
		return v;
	}
	string Str() const
	{
		if(neg)
			throw std::runtime_error("neg_str");
		return str();
	}
	void Char(char* c) const
	{
		if(neg)
			throw std::runtime_error("neg_str");
		string s = str();
		strcpy(c, s.c_str());
	}

    bool operator <(const BigValue &other) const;
    bool operator <=(const BigValue &other) const;
    bool operator >=(const BigValue &other) const;
    bool operator >(const BigValue &other) const;
    bool operator ==(const BigValue &other) const;
    bool operator !=(const BigValue &other) const;
    BigValue& operator =(const BigValue &other);
    BigValue operator +(const BigValue &other) const;
    BigValue operator -(const BigValue &other) const;
    BigValue operator *(const BigValue &other) const;
    BigValue operator /(const BigValue &other) const;

    BigValue& operator +=(const BigValue &other){ *this = *this + other; return *this; }
    BigValue& operator -=(const BigValue &other){ *this = *this - other; return *this; }
    BigValue& operator *=(const BigValue &other){ *this = *this * other; return *this; }
    BigValue& operator /=(const BigValue &other){ *this = *this / other; return *this; }

    bool operator <(const double &other) const { return *this < BigValue(other); }
    bool operator <=(const double &other) const { return *this <= BigValue(other); }
    bool operator >=(const double &other) const { return *this >= BigValue(other); }
    bool operator >(const double &other) const { return *this > BigValue(other); }
    bool operator ==(const double &other) const { return *this == BigValue(other); }
    bool operator !=(const double &other) const { return *this != BigValue(other); }
    BigValue& operator =(const double &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const double &other) const { return *this + BigValue(other); }
    BigValue operator -(const double &other) const { return *this - BigValue(other); }
    BigValue operator *(const double &other) const { return *this * BigValue(other); }
    BigValue operator /(const double &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const double &other) { return *this += BigValue(other); }
    BigValue& operator -=(const double &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const double &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const double &other) { return *this /= BigValue(other); }

    bool operator <(const float &other) const { return *this < BigValue(other); }
    bool operator <=(const float &other) const { return *this <= BigValue(other); }
    bool operator >=(const float &other) const { return *this >= BigValue(other); }
    bool operator >(const float &other) const { return *this > BigValue(other); }
    bool operator ==(const float &other) const { return *this == BigValue(other); }
    bool operator !=(const float &other) const { return *this != BigValue(other); }
    BigValue& operator =(const float &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const float &other) const { return *this + BigValue(other); }
    BigValue operator -(const float &other) const { return *this - BigValue(other); }
    BigValue operator *(const float &other) const { return *this * BigValue(other); }
    BigValue operator /(const float &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const float &other) { return *this += BigValue(other); }
    BigValue& operator -=(const float &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const float &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const float &other) { return *this /= BigValue(other); }

    bool operator <(const int8_t &other) const { return *this < BigValue(other); }
    bool operator <=(const int8_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const int8_t &other) const { return *this >= BigValue(other); }
    bool operator >(const int8_t &other) const { return *this > BigValue(other); }
    bool operator ==(const int8_t &other) const { return *this == BigValue(other); }
    bool operator !=(const int8_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const int8_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const int8_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const int8_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const int8_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const int8_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const int8_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const int8_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const int8_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const int8_t &other) { return *this /= BigValue(other); }

    bool operator <(const int16_t &other) const { return *this < BigValue(other); }
    bool operator <=(const int16_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const int16_t &other) const { return *this >= BigValue(other); }
    bool operator >(const int16_t &other) const { return *this > BigValue(other); }
    bool operator ==(const int16_t &other) const { return *this == BigValue(other); }
    bool operator !=(const int16_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const int16_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const int16_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const int16_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const int16_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const int16_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const int16_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const int16_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const int16_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const int16_t &other) { return *this /= BigValue(other); }

    bool operator <(const int32_t &other) const { return *this < BigValue(other); }
    bool operator <=(const int32_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const int32_t &other) const { return *this >= BigValue(other); }
    bool operator >(const int32_t &other) const { return *this > BigValue(other); }
    bool operator ==(const int32_t &other) const { return *this == BigValue(other); }
    bool operator !=(const int32_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const int32_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const int32_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const int32_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const int32_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const int32_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const int32_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const int32_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const int32_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const int32_t &other) { return *this /= BigValue(other); }

    bool operator <(const int64_t &other) const { return *this < BigValue(other); }
    bool operator <=(const int64_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const int64_t &other) const { return *this >= BigValue(other); }
    bool operator >(const int64_t &other) const { return *this > BigValue(other); }
    bool operator ==(const int64_t &other) const { return *this == BigValue(other); }
    bool operator !=(const int64_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const int64_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const int64_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const int64_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const int64_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const int64_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const int64_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const int64_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const int64_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const int64_t &other) { return *this /= BigValue(other); }

    bool operator <(const uint8_t &other) const { return *this < BigValue(other); }
    bool operator <=(const uint8_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const uint8_t &other) const { return *this >= BigValue(other); }
    bool operator >(const uint8_t &other) const { return *this > BigValue(other); }
    bool operator ==(const uint8_t &other) const { return *this == BigValue(other); }
    bool operator !=(const uint8_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const uint8_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const uint8_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const uint8_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const uint8_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const uint8_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const uint8_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const uint8_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const uint8_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const uint8_t &other) { return *this /= BigValue(other); }

    bool operator <(const uint16_t &other) const { return *this < BigValue(other); }
    bool operator <=(const uint16_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const uint16_t &other) const { return *this >= BigValue(other); }
    bool operator >(const uint16_t &other) const { return *this > BigValue(other); }
    bool operator ==(const uint16_t &other) const { return *this == BigValue(other); }
    bool operator !=(const uint16_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const uint16_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const uint16_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const uint16_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const uint16_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const uint16_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const uint16_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const uint16_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const uint16_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const uint16_t &other) { return *this /= BigValue(other); }

    bool operator <(const uint32_t &other) const { return *this < BigValue(other); }
    bool operator <=(const uint32_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const uint32_t &other) const { return *this >= BigValue(other); }
    bool operator >(const uint32_t &other) const { return *this > BigValue(other); }
    bool operator ==(const uint32_t &other) const { return *this == BigValue(other); }
    bool operator !=(const uint32_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const uint32_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const uint32_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const uint32_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const uint32_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const uint32_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const uint32_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const uint32_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const uint32_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const uint32_t &other) { return *this /= BigValue(other); }

    bool operator <(const uint64_t &other) const { return *this < BigValue(other); }
    bool operator <=(const uint64_t &other) const { return *this <= BigValue(other); }
    bool operator >=(const uint64_t &other) const { return *this >= BigValue(other); }
    bool operator >(const uint64_t &other) const { return *this > BigValue(other); }
    bool operator ==(const uint64_t &other) const { return *this == BigValue(other); }
    bool operator !=(const uint64_t &other) const { return *this != BigValue(other); }
    BigValue& operator =(const uint64_t &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const uint64_t &other) const { return *this + BigValue(other); }
    BigValue operator -(const uint64_t &other) const { return *this - BigValue(other); }
    BigValue operator *(const uint64_t &other) const { return *this * BigValue(other); }
    BigValue operator /(const uint64_t &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const uint64_t &other) { return *this += BigValue(other); }
    BigValue& operator -=(const uint64_t &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const uint64_t &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const uint64_t &other) { return *this /= BigValue(other); }

    bool operator <(const string &other) const { return *this < BigValue(other); }
    bool operator <=(const string &other) const { return *this <= BigValue(other); }
    bool operator >=(const string &other) const { return *this >= BigValue(other); }
    bool operator >(const string &other) const { return *this > BigValue(other); }
    bool operator ==(const string &other) const { return *this == BigValue(other); }
    bool operator !=(const string &other) const { return *this != BigValue(other); }
    BigValue& operator =(const string &other) { *this = BigValue(other); return *this; }
    BigValue operator +(const string &other) const { return *this + BigValue(other); }
    BigValue operator -(const string &other) const { return *this - BigValue(other); }
    BigValue operator *(const string &other) const { return *this * BigValue(other); }
    BigValue operator /(const string &other) const { return *this / BigValue(other); }
    BigValue& operator +=(const string &other) { return *this += BigValue(other); }
    BigValue& operator -=(const string &other) { return *this -= BigValue(other); }
    BigValue& operator *=(const string &other) { return *this *= BigValue(other); }
    BigValue& operator /=(const string &other) { return *this /= BigValue(other); }

    bool operator <(const char* other) const { return *this < BigValue(other); }
    bool operator <=(const char* other) const { return *this <= BigValue(other); }
    bool operator >=(const char* other) const { return *this >= BigValue(other); }
    bool operator >(const char* other) const { return *this > BigValue(other); }
    bool operator ==(const char* other) const { return *this == BigValue(other); }
    bool operator !=(const char* other) const { return *this != BigValue(other); }
    BigValue& operator =(const char* other) { *this = BigValue(other); return *this; }
    BigValue operator +(const char* other) const { return *this + BigValue(other); }
    BigValue operator -(const char* other) const { return *this - BigValue(other); }
    BigValue operator *(const char* other) const { return *this * BigValue(other); }
    BigValue operator /(const char* other) const { return *this / BigValue(other); }
    BigValue& operator +=(const char* other) { return *this += BigValue(other); }
    BigValue& operator -=(const char* other) { return *this -= BigValue(other); }
    BigValue& operator *=(const char* other) { return *this *= BigValue(other); }
    BigValue& operator /=(const char* other) { return *this /= BigValue(other); }

    BigValue operator -() const { return this->isZero() ? *this : BigValue(!this->Neg(), this->Val()); }
    BigValue operator ++(){ return *this += 1; }
    BigValue operator ++(int){ return *this + 1; }
    BigValue operator --(){ return *this -= 1; }
    BigValue operator --(int){ return *this - 1; }

    BigValue ABS() const { return BigValue(false, this->Val()); }
private:
	bool neg;
	string val;

	bool isZero() const
	{
		for(int i=0;i<val.size();++i)
		{
			if(val[i] != '0')
				return false;
		}
		return true;
	}
	void normalize()
	{
		while(!val.empty())
		{
			if(val[val.length() - 1] == '0')
				val = val.substr(0, val.length() - 1);
			else
				break;
		}
		if(val.empty())
		{
			neg = false;
			val = "0";
		}
	}
	string str() const
	{
		string s = val;
		if(s.length() > BIG_VALUE_KEEP_T)
			s = s.substr(BIG_VALUE_KEEP_T);
		else
			s = "0";
		reverse(s);
		return s;
	}
	BigValue(bool n, const string& s)
	{
		neg = n;
		val = s;
		normalize();
	}
	void sig(bool n1, bool n2)
	{
		neg = (n1 != n2);
	}
	void mul10(uint32_t times)
	{
		if(!isZero())
		{
			for(uint32_t i=0;i<times;++i)
				val = string("0") + val;
		}
	}
	void div10(uint32_t times)
	{
		if(val.length() > times)
			val = val.substr(times);
		else
		{
			neg = false;
			val = "0";
		}
	}
	static inline void reverse(string& s)
	{
		if(s.length() > 1)
			std::reverse(s.begin(), s.end());
	}
};

#endif /* APP_COMMON_BIGVALUE_H_ */
