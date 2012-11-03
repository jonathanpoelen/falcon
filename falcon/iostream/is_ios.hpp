#ifndef _FALCON_IOSTREAM_IS_IOS_HPP
#define _FALCON_IOSTREAM_IS_IOS_HPP

#include <iosfwd>
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
	static const bool value = __is_ios_impl<_T>::value;
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
	static const bool value = __is_iostrings_impl<_T>::value;
};


template<typename _T>
struct is_ios
: __is_ios<_T, std::basic_ios>
{};

template<typename _T>
struct is_streambuf
: __is_ios<_T, std::basic_streambuf>
{};

template<typename _T>
struct is_ostream
: __is_ios<_T, std::basic_ostream>
{};

template<typename _T>
struct is_istream
: __is_ios<_T, std::basic_istream>
{};

template<typename _T>
struct is_iostream
: __is_ios<_T, std::basic_iostream>
{};

template<typename _T>
struct is_stringbuf
: __is_iostrings<_T, std::basic_stringbuf>
{};

template<typename _T>
struct is_istringstream
: __is_iostrings<_T, std::basic_istringstream>
{};

template<typename _T>
struct is_ostringstream
: __is_iostrings<_T, std::basic_ostringstream>
{};

template<typename _T>
struct is_stringstream
: __is_iostrings<_T, std::basic_stringstream>
{};

template<typename _T>
struct is_filebuf
: __is_ios<_T, std::basic_filebuf>
{};

template<typename _T>
struct is_ifstream
: __is_ios<_T, std::basic_ifstream>
{};

template<typename _T>
struct is_ofstream
: __is_ios<_T, std::basic_ofstream>
{};

template<typename _T>
struct is_fstream
: __is_ios<_T, std::basic_fstream>
{};

}

#endif
