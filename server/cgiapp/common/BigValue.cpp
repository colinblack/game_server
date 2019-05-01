/*
 * BigValue.cpp
 *
 *  Created on: 2018年12月13日
 *      Author: Ralf
 */

#include "BigValue.h"

bool BigValue::operator <(const BigValue &other) const
{
	bool n = other.Neg();
	if(n && !neg)
		return false;
	else if(!n && neg)
		return true;
	else
	{
		string v = other.Val();
		bool f = false;
		bool e = true;
		int l = val.length(), lo = v.length();
		if(l > lo)
			f = false;
		else if(l < lo)
			f = true;
		else
		{
			for(int i=l-1;i>=0;--i)
			{
				if(val[i] < v[i])
				{
					e = false;
					f = true;
					break;
				}
				else if(val[i] > v[i])
				{
					e = false;
					f = false;
					break;
				}
			}
			if(e)
				return false;
		}
		if(n)
			return !f;
		return f;
	}
}
bool BigValue::operator <=(const BigValue &other) const
{
	return !(*this > other);
}
bool BigValue::operator >=(const BigValue &other) const
{
	return !(*this < other);
}
bool BigValue::operator >(const BigValue &other) const
{
	bool n = other.Neg();
	if(n && !neg)
		return true;
	else if(!n && neg)
		return false;
	else
	{
		string v = other.Val();
		bool f = false;
		bool e = true;
		int l = val.length(), lo = v.length();
		if(l > lo)
			f = true;
		else if(l < lo)
			f = false;
		else
		{
			for(int i=l-1;i>=0;--i)
			{
				if(val[i] > v[i])
				{
					e = false;
					f = true;
					break;
				}
				else if(val[i] < v[i])
				{
					e = false;
					f = false;
					break;
				}
			}
			if(e)
				return false;
		}
		if(n)
			return !f;
		return f;
	}
}
bool BigValue::operator ==(const BigValue &other) const
{
	if(neg == other.Neg())
	{
		string v = other.Val();
		int l = val.length(), lo = v.length();
		if(l == lo)
		{
			for(int i=l-1;i>=0;--i)
			{
				if(val[i] != v[i])
					return false;
			}
			return true;
		}
		return false;
	}
	return false;
}
bool BigValue::operator !=(const BigValue &other) const
{
	return !(*this == other);
}
BigValue& BigValue::operator =(const BigValue &other)
{
	neg = other.Neg();
	val = other.Val();
	return *this;
}
BigValue BigValue::operator +(const BigValue &other) const
{
	if(!neg && !other.Neg())
	{
		string s;
		int len = max(val.length(), other.Val().length()) + 1;
		s.resize(len);
		int8_t add = 0;
		for(int i=0;i<len;++i)
		{
			int8_t big = val.length() > i ? (int8_t(val[i]) - '0') : 0;
			int8_t small = other.Val().length() > i ? (int8_t(other.Val()[i]) - '0') : 0;
			int8_t sum = big + small + add;
			add = sum >= 10 ? 1 : 0;
			sum = sum % 10 + '0';
			s[i] = sum;
		}
		return BigValue(false, s);
	}
	else if(neg && other.Neg())
		return -((-*this) + (-other));
	else if(!neg && other.Neg())
		return *this - (-other);
	else
		return other - (-*this);
}
BigValue BigValue::operator -(const BigValue &other) const
{
	if(!neg && !other.Neg())
	{
		if(*this < other)
			return -(other - *this);
		else
		{
			string s;
			int len = max(val.length(), other.Val().length());
			s.resize(len);
			int8_t add = 0;
			for(int i=0;i<len;++i)
			{
				int8_t big = val.length() > i ? (int8_t(val[i]) - '0') : 0;
				int8_t small = other.Val().length() > i ? (int8_t(other.Val()[i]) - '0') : 0;
				int8_t sum = big - small + add;
				add = sum < 0 ? -1 : 0;
				sum = (sum + 10) % 10 + '0';
				s[i] = sum;
			}
			return BigValue(false, s);
		}
	}
	else if(neg && other.Neg())
		return (-other) - (-*this);
	else if(!neg && other.Neg())
		return *this + (-other);
	else
		return -((-*this) + other);
}
BigValue BigValue::operator *(const BigValue &other) const
{
	vector<BigValue> s;
	BigValue big = this->ABS();
	BigValue small = other.ABS();
	BigValue t(0);
	s.push_back(t);
	for(int i=1;i<10;++i)
	{
		t += big;
		s.push_back(t);
	}
	BigValue m(0);
	for(int i=0;i<small.Val().length();++i)
	{
		BigValue k(s[small.Val()[i] - '0']);
		k.mul10(i);
		m += k;
	}
	m.sig(this->Neg(), other.Neg());
	m.div10(BIG_VALUE_KEEP_T);
	return m;
}
BigValue BigValue::operator /(const BigValue &other) const
{
	if(other.isZero())
		throw std::runtime_error("div_zero");
	BigValue big = this->ABS();
	big.mul10(BIG_VALUE_KEEP_T);
	int l1 = big.Val().length(), l2 = other.Val().length();
	if(l1 < l2)
		return BigValue(0);
	string s;
	for(int i=l1-l2;i>=0;--i)
	{
		BigValue small(other.ABS());
		small.mul10(i);
		int k = 0;
		while(big >= small)
		{
			++k;
			big -= small;
		}
		s.append(CTrans::ITOS(k));
	}
	BigValue r(s);
	r.sig(this->Neg(), other.Neg());
	r.div10(BIG_VALUE_KEEP_T);
	return r;
}
