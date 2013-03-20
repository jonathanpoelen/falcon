#ifndef FALCON_DETAIL_STRING_SIZE_HPP
#define FALCON_DETAIL_STRING_SIZE_HPP

#include <falcon/string/cstringfwd.hpp>
#include <falcon/c++/boost_or_std.hpp>

namespace falcon {
namespace detail {

template<typename _Reference>
struct __string_size_base
{
	typedef _Reference __reference;
	static std::size_t size(__reference s)
	{ return s.size(); }
};

template<typename _T, bool = FALCON_BOOST_OR_STD_NAMESPACE::is_integral<_T>::value>
struct __string_size_impl
: __string_size_base<const _T&>
{};

template<typename _T>
struct __string_size_impl<_T, true>
{
	typedef _T __reference;
	static std::size_t size(__reference)
	{ return 1; }
};

template<typename _T>
struct __string_size
: __string_size_impl<_T>
{};

template<typename _CharT>
struct __string_size<const _CharT *>
: __string_size_base<basic_cstring<const _CharT *> >
{};

template<typename _CharT>
struct __string_size<_CharT *>
: __string_size_base<basic_cstring<_CharT *> >
{};

template<typename _CharT, std::size_t _N>
struct __string_size<const _CharT[_N]>
: __string_size_base<const _CharT(&)[_N]>
{
	static std::size_t size(const _CharT(&)[_N])
	{ return _N?_N-1:0; }
};

template<typename _CharT, std::size_t _N>
struct __string_size<_CharT[_N]>
: __string_size_base<const _CharT(&)[_N]>
{
	static std::size_t size(const _CharT(&)[_N])
	{ return _N?_N-1:0; }
};

}
}

#endif