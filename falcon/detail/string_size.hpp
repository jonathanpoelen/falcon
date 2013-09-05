#ifndef FALCON_DETAIL_STRING_SIZE_HPP
#define FALCON_DETAIL_STRING_SIZE_HPP

#include <falcon/c++/constexpr.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(is_integral)
#include FALCON_BOOST_OR_STD_TRAITS(remove_const)
#include <ios>

namespace falcon {
namespace detail {

template<typename T, bool = FALCON_BOOST_OR_STD_NAMESPACE::is_integral<T>::value>
struct string_size
{
  typedef const T& reference;
  static std::size_t size(reference s)
  { return s.size(); }
};

template<typename T>
struct string_size<T*, false>
{
  typedef T * reference;
  static std::size_t size(reference s)
  {
    return std::char_traits<
      typename FALCON_BOOST_OR_STD_NAMESPACE::remove_const<T>::type
     >::length(s);
  }
};

template<typename T, std::size_t N>
struct string_size<T[N], false>
: string_size<T*, false>
{
  typedef T (&reference)[N];
};

template<typename T>
struct string_size<T, true>
{
	typedef T reference;
    CPP_CONSTEXPR static std::size_t size(reference)
	{ return 1; }
};

}
}

#endif
