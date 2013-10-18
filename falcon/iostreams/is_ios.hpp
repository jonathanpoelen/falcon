#ifndef FALCON_IOSTREAM_IS_IOS_HPP
#define FALCON_IOSTREAM_IS_IOS_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/is_instance_of.hpp>
#include <falcon/type_traits/has.hpp>
#include <falcon/c++/boost_or_std.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)
#include <iosfwd>

namespace falcon {

template<typename T, template<class Char, class Traits> class StreamConvert>
class __is_ios
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type stream_type;

  template<typename Stream, bool HasTypeStream =
    falcon::has_char_type<stream_type>::value
    && falcon::has_traits_type<stream_type>::value
	>
	struct __is_ios_impl
	{
		static const bool value = false;
	};

	template<typename Stream>
	struct __is_ios_impl<Stream, true>
	: is_instance_of<stream_type, StreamConvert<
		typename Stream::char_type,
		typename Stream::traits_type
	> >
	{};

public:
  typedef integral_constant<bool, __is_ios_impl<stream_type>::value> base;
};


template<typename T, template<class Char, class Traits, class Alloc> class StringStreamConvert>
class __is_iostrings
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type stream_type;

  template<typename Stream, bool HasTypeStream =
    falcon::has_char_type<stream_type>::value
    && falcon::has_traits_type<stream_type>::value
    && falcon::has_allocator_type<stream_type>::value
	>
	struct __is_iostrings_impl
	{
		static const bool value = false;
	};

	template<typename Stream>
	struct __is_iostrings_impl<Stream, true>
	: is_instance_of<stream_type, StringStreamConvert<
		typename Stream::char_type,
		typename Stream::traits_type,
		typename Stream::allocator_type
	> >
	{};

public:
  typedef integral_constant<bool, __is_iostrings_impl<stream_type>::value> base;
};


template<typename T>
struct is_io_base
: is_instance_of< typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type
                , std::ios_base>
{};

template<typename T>
struct is_ios
: __is_ios<T, std::basic_ios>::base
{};

template<typename T>
struct is_streambuf
: __is_ios<T, std::basic_streambuf>::base
{};

template<typename T>
struct is_ostream
: __is_ios<T, std::basic_ostream>::base
{};

template<typename T>
struct is_istream
: __is_ios<T, std::basic_istream>::base
{};

template<typename T>
struct is_iostream
: __is_ios<T, std::basic_iostream>::base
{};

template<typename T>
struct is_stringbuf
: __is_iostrings<T, std::basic_stringbuf>::base
{};

template<typename T>
struct is_istringstream
: __is_iostrings<T, std::basic_istringstream>::base
{};

template<typename T>
struct is_ostringstream
: __is_iostrings<T, std::basic_ostringstream>::base
{};

template<typename T>
struct is_stringstream
: __is_iostrings<T, std::basic_stringstream>::base
{};

template<typename T>
struct is_filebuf
: __is_ios<T, std::basic_filebuf>::base
{};

template<typename T>
struct is_ifstream
: __is_ios<T, std::basic_ifstream>::base
{};

template<typename T>
struct is_ofstream
: __is_ios<T, std::basic_ofstream>::base
{};

template<typename T>
struct is_fstream
: __is_ios<T, std::basic_fstream>::base
{};

}

#endif
