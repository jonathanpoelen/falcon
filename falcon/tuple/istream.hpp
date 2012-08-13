#ifndef _FALCON_TUPLE_ISTREAM_HPP
#define _FALCON_TUPLE_ISTREAM_HPP

#include <iosfwd>
#include <tuple>
#include <falcon/istream/ignore.hpp>

namespace falcon {
namespace tuple {
namespace istream {

template<std::size_t _I, std::size_t _N>
struct __istream_tuple_impl
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_istream<_CharT, _Traits>& impl(std::basic_istream<_CharT, _Traits>& is, std::tuple<_Args...>& t, const _CharT *sep = ",")
	{
		return __istream_tuple_impl<_I + 1, _N>
		::impl(ignore(is, sep) >> std::get<_I>(t), t, sep);
	}
};

template<>
struct __istream_tuple_impl<0, 0>
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_istream<_CharT, _Traits>& impl(std::basic_istream<_CharT, _Traits>& is, std::tuple<_Args...>&, const _CharT * = ",")
	{
		return is;
	}
};

template<>
struct __istream_tuple_impl<0, 1>
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_istream<_CharT, _Traits>& impl(std::basic_istream<_CharT, _Traits>& is, std::tuple<_Args...>& t, const _CharT * = ",")
	{
		return is >> std::get<0>(t);
	}
};

template<std::size_t _N>
struct __istream_tuple_impl<0, _N>
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_istream<_CharT, _Traits>& impl(std::basic_istream<_CharT, _Traits>& is, std::tuple<_Args...>& t, const _CharT * sep = ",")
	{
		return __istream_tuple_impl<1, _N>::impl(is >> std::get<0>(t), t, sep);
	}
};

template<std::size_t _N>
struct __istream_tuple_impl<_N, _N>
: __istream_tuple_impl<0,0>
{};

template<typename _CharT, typename _Traits, typename... _Args>
std::basic_istream<_CharT, _Traits>& operator>>(std::basic_istream<_CharT, _Traits>& is, std::tuple<_Args...>& t)
{
	return __istream_tuple_impl<0, sizeof...(_Args)>::impl(is, t);
}

}
}

template<typename _CharT, typename _Traits, typename... _Args>
std::basic_istream<_CharT, _Traits>& get_tuple(std::basic_istream<_CharT, _Traits>& is, std::tuple<_Args...>& t, const _CharT * sep = ",")
{
	return tuple::istream::__istream_tuple_impl<0, sizeof...(_Args)>::impl(is, t, sep);
}

}

#endif