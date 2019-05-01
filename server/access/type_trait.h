#ifndef _UTILS_TYPE_TRAIT_H
#define _UTILS_TYPE_TRAIT_H

template <typename T>
struct TypeTest 
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};

template <>
struct TypeTest<char>
{
    enum {
    	IS_CHAR = 1,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<unsigned char>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 1,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const char>
{
    enum {
    	IS_CHAR = 1,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const unsigned char>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 1,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};

template <>
struct TypeTest<short>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 1,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<unsigned short>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 1,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const short>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 1,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const unsigned short>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 1,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};

template <>
struct TypeTest<int>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 1,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<unsigned int>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 1,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const int>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 1,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const unsigned int>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 1,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};

template <>
struct TypeTest<float>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 1,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const float>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 1,
    	IS_DOUBLE = 0,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<double>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 1,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};
template <>
struct TypeTest<const double>
{
    enum {
    	IS_CHAR = 0,
    	IS_UNSIGNED_CHAR = 0,
    	IS_SHORT = 0,
    	IS_UNSIGNED_SHORT = 0,
    	IS_INT = 0,
    	IS_UNSIGNED_INT = 0,
    	IS_FLOAT = 0,
    	IS_DOUBLE = 1,
    	IS_POINT = 0,
    	IS_FUNCTION = 0
    };
};


#endif
/*
#include <iostream>
using namespace std;
int main(int argc,char * argv[])
{
        cout<<TypeTest<const signed char>::IS_CHAR<<endl;
        cout<<TypeTest<const  char>::IS_CHAR<<endl;
        cout<<TypeTest<const int>::IS_INT<<endl;
            return 0;
}
*/

