#ifndef _FALCON_TUPLE_OSTREAM_HPP
#define _FALCON_TUPLE_OSTREAM_HPP

#include <iosfwd>
#include <tuple>

namespace falcon {
namespace tuple {
namespace ostream {

template<std::size_t _I, std::size_t _N>
struct __ostream_tuple_impl
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_ostream<_CharT, _Traits>& impl(std::basic_ostream<_CharT, _Traits>& os, const std::tuple<_Args...>& t, const _CharT *sep = ",")
	{
		return __ostream_tuple_impl<_I + 1, _N>
		::impl(os << sep << std::get<_I>(t), t, sep);
	}
};

template<>
struct __ostream_tuple_impl<0, 0>
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_ostream<_CharT, _Traits>& impl(std::basic_ostream<_CharT, _Traits>& os, const std::tuple<_Args...>&, const _CharT * = ",")
	{
		return os;
	}
};

template<>
struct __ostream_tuple_impl<0, 1>
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_ostream<_CharT, _Traits>& impl(std::basic_ostream<_CharT, _Traits>& os, const std::tuple<_Args...>& t, const _CharT * = ",")
	{
		return os << std::get<0>(t);
	}
};

template<std::size_t _N>
struct __ostream_tuple_impl<0, _N>
{
	template<typename _CharT, typename _Traits, typename... _Args>
	static std::basic_ostream<_CharT, _Traits>& impl(std::basic_ostream<_CharT, _Traits>& os, const std::tuple<_Args...>& t, const _CharT * sep = ",")
	{
		return __ostream_tuple_impl<1, _N>::impl(os << std::get<0>(t), t, sep);
	}
};

template<std::size_t _N>
struct __ostream_tuple_impl<_N, _N>
: __ostream_tuple_impl<0,0>
{};

template<typename _CharT, typename _Traits, typename... _Args>
std::basic_ostream<_CharT, _Traits>& operator<<(std::basic_ostream<_CharT, _Traits>& os, const std::tuple<_Args...>& t)
{
	return __ostream_tuple_impl<0, sizeof...(_Args)>::impl(os, t);
}

}
}

template<typename _CharT, typename _Traits, typename... _Args>
std::basic_ostream<_CharT, _Traits>& put_tuple(std::basic_ostream<_CharT, _Traits>& os, const std::tuple<_Args...>& t, const _CharT * sep = ",")
{
	return tuple::ostream::__ostream_tuple_impl<0, sizeof...(_Args)>::impl(os, t, sep);
}

}

#endif