#ifndef _FALCON_IOSTREAM_IS_IOS_HPP
#define _FALCON_IOSTREAM_IS_IOS_HPP

#include <iosfwd>
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/is_instance_of.hpp>
#include <falcon/type_traits/has.hpp>

namespace falcon {

template<typename _T, template<class _Char, class _Traits> class _StreamConvert>
class __is_ios
{
	template<typename _Stream, bool _HasTypeStream =
		falcon::has_char_type<_T>::value
		&& falcon::has_traits_type<_T>::value
	>
	struct __is_ios_impl
	{
		static const bool value = false;
	};

	template<typename _Stream>
	struct __is_ios_impl<_Stream, true>
	: is_instance_of<_T, _StreamConvert<
		typename _Stream::char_type,
		typename _Stream::traits_type
	> >
	{};

public:
	typedef integral_constant<bool, __is_ios_impl<_T>::value> base;
};


template<typename _T, template<class _Char, class _Traits, class _Alloc> class _StringStreamConvert>
class __is_iostrings
{
	template<typename _Stream, bool _HasTypeStream =
		falcon::has_char_type<_T>::value
		&& falcon::has_traits_type<_T>::value
		&& falcon::has_allocator_type<_T>::value
	>
	struct __is_iostrings_impl
	{
		static const bool value = false;
	};

	template<typename _Stream>
	struct __is_iostrings_impl<_Stream, true>
	: is_instance_of<_T, _StringStreamConvert<
		typename _Stream::char_type,
		typename _Stream::traits_type,
		typename _Stream::allocator_type
	> >
	{};

public:
	typedef integral_constant<bool, __is_iostrings_impl<_T>::value> base;
};


template<typename _T>
struct is_io_base
: is_instance_of<_T, std::ios_base>
{};

template<typename _T>
struct is_ios
: __is_ios<_T, std::basic_ios>::base
{};

template<typename _T>
struct is_streambuf
: __is_ios<_T, std::basic_streambuf>::base
{};

template<typename _T>
struct is_ostream
: __is_ios<_T, std::basic_ostream>::base
{};

template<typename _T>
struct is_istream
: __is_ios<_T, std::basic_istream>::base
{};

template<typename _T>
struct is_iostream
: __is_ios<_T, std::basic_iostream>::base
{};

template<typename _T>
struct is_stringbuf
: __is_iostrings<_T, std::basic_stringbuf>::base
{};

template<typename _T>
struct is_istringstream
: __is_iostrings<_T, std::basic_istringstream>::base
{};

template<typename _T>
struct is_ostringstream
: __is_iostrings<_T, std::basic_ostringstream>::base
{};

template<typename _T>
struct is_stringstream
: __is_iostrings<_T, std::basic_stringstream>::base
{};

template<typename _T>
struct is_filebuf
: __is_ios<_T, std::basic_filebuf>::base
{};

template<typename _T>
struct is_ifstream
: __is_ios<_T, std::basic_ifstream>::base
{};

template<typename _T>
struct is_ofstream
: __is_ios<_T, std::basic_ofstream>::base
{};

template<typename _T>
struct is_fstream
: __is_ios<_T, std::basic_fstream>::base
{};

}

#endif
