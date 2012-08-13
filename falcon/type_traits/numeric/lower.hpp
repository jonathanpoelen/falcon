#ifndef _FALCON_TYPE_TRAITS_NUMERIC_LOWER_HPP
#define _FALCON_TYPE_TRAITS_NUMERIC_LOWER_HPP

namespace falcon {
template<typename _Int>
struct lower_int;

template<>
struct lower_int<char>
{
	typedef bool type;
};

template<>
struct lower_int<short>
{
	typedef char type;
};

template<>
struct lower_int<int>
{
	typedef short type;
};

template<>
struct lower_int<long>
{
	typedef int type;
};

template<>
struct lower_int<long long>
{
	typedef long type;
};


template<>
struct lower_int<unsigned char>
{
	typedef bool type;
};

template<>
struct lower_int<unsigned short>
{
	typedef unsigned char type;
};

template<>
struct lower_int<unsigned int>
{
	typedef unsigned short type;
};

template<>
struct lower_int<unsigned long>
{
	typedef unsigned int type;
};

template<>
struct lower_int<unsigned long long>
{
	typedef unsigned long type;
};


template<typename _Float>
struct lower_floating_point;

template<>
struct lower_floating_point<double>
{
	typedef float type;
};

template<>
struct lower_floating_point<long double>
{
	typedef double type;
};
}

#endif
