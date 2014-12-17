#ifndef FALCON_IOSTREAM_IS_IOS_HPP
#define FALCON_IOSTREAM_IS_IOS_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/is_instance_of.hpp>
#include <falcon/helper/has_allocator_type.hpp>
#include <falcon/helper/has_traits_type.hpp>
#include <falcon/helper/has_char_type.hpp>
#include <falcon/c++/boost_or_std.hpp>

#include FALCON_BOOST_OR_STD_TRAITS(remove_reference)
#include <iosfwd>

namespace falcon {
namespace iostreams {

namespace aux_ {

template<
  class T
, template<class Char, class Traits> class StreamConvert>
class is_ios
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type stream_type;

  template<
    typename Stream
  , bool HasTypeStream = falcon::has_char_type<stream_type>::value
                      && falcon::has_traits_type<stream_type>::value
	>
	struct is_ios_impl
	{ static const bool value = false; };

	template<typename Stream>
	struct is_ios_impl<Stream, true>
	: is_instance_of<stream_type, StreamConvert<
		typename Stream::char_type
  , typename Stream::traits_type
	> >
	{};

public:
  typedef integral_constant<bool, is_ios_impl<stream_type>::value> base;
};


template<
  class T
, template<class Char, class Traits, class Alloc> class StringStreamConvert>
class is_iostrings
{
  typedef typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type stream_type;

  template<
    typename Stream
  , bool HasTypeStream = falcon::has_char_type<stream_type>::value
                      && falcon::has_traits_type<stream_type>::value
                      && falcon::has_allocator_type<stream_type>::value
	>
	struct is_iostrings_impl
	{ static const bool value = false; };

	template<typename Stream>
	struct is_iostrings_impl<Stream, true>
	: is_instance_of<stream_type, StringStreamConvert<
		typename Stream::char_type
  , typename Stream::traits_type
  , typename Stream::allocator_type
	> >
	{};

public:
  typedef integral_constant<bool, is_iostrings_impl<stream_type>::value> base;
};

}


template<class T>
struct is_io_base
: is_instance_of<
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_reference<T>::type
, std::ios_base>
{};

template<class T>
struct is_ios
: aux_::is_ios<T, std::basic_ios>::base
{};

template<class T>
struct is_streambuf
: aux_::is_ios<T, std::basic_streambuf>::base
{};

template<class T>
struct is_ostream
: aux_::is_ios<T, std::basic_ostream>::base
{};

template<class T>
struct is_istream
: aux_::is_ios<T, std::basic_istream>::base
{};

template<class T>
struct is_iostream
: aux_::is_ios<T, std::basic_iostream>::base
{};

template<class T>
struct is_stringbuf
: aux_::is_iostrings<T, std::basic_stringbuf>::base
{};

template<class T>
struct is_istringstream
: aux_::is_iostrings<T, std::basic_istringstream>::base
{};

template<class T>
struct is_ostringstream
: aux_::is_iostrings<T, std::basic_ostringstream>::base
{};

template<class T>
struct is_stringstream
: aux_::is_iostrings<T, std::basic_stringstream>::base
{};

template<class T>
struct is_filebuf
: aux_::is_ios<T, std::basic_filebuf>::base
{};

template<class T>
struct is_ifstream
: aux_::is_ios<T, std::basic_ifstream>::base
{};

template<class T>
struct is_ofstream
: aux_::is_ios<T, std::basic_ofstream>::base
{};

template<class T>
struct is_fstream
: aux_::is_ios<T, std::basic_fstream>::base
{};

}
}

#endif
