#ifndef _FALCON_TYPE_TRAITS_NUMERIC_GREATER_HPP
#define _FALCON_TYPE_TRAITS_NUMERIC_GREATER_HPP

namespace falcon {
template<typename _Int>
struct greater_int;

template<>
struct greater_int<bool>
{
	typedef char type;
};

template<>
struct greater_int<char>
{
	typedef short type;
};

template<>
struct greater_int<short>
{
	typedef int type;
};

template<>
struct greater_int<int>
{
	typedef long type;
};

template<>
struct greater_int<long>
{
	typedef long long type;
};


template<>
struct greater_int<unsigned char>
{
	typedef unsigned short type;
};

template<>
struct greater_int<unsigned short>
{
	typedef unsigned int type;
};

template<>
struct greater_int<unsigned int>
{
	typedef unsigned long type;
};

template<>
struct greater_int<unsigned long>
{
	typedef unsigned long long type;
};


template<typename _Float>
struct greater_floating_point;

template<>
struct greater_floating_point<float>
{
	typedef double type;
};

template<>
struct greater_floating_point<double>
{
	typedef long double type;
};
}

#endif
