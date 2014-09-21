#ifndef FALCON_LOCAL_STRING_CONST_STRING_OPTIMIZED_HPP
#define FALCON_LOCAL_STRING_CONST_STRING_OPTIMIZED_HPP

#include <falcon/c++/boost_or_std.hpp>
#include <falcon/string/cstring.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)

namespace falcon { namespace string {

template<class T>
struct build_local_const_string_optimized {
  typedef const T & type;
};

template<class CharT>
struct build_local_const_string_optimized<CharT*> {
  typedef typename build_basic_cstring<const CharT>::type type;
};

template<class CharT, std::size_t N>
struct build_local_const_string_optimized<CharT[N]> {
  typedef typename build_basic_cstring<const CharT>::type type;
};

#if __cplusplus == 201103L
template<class StringOrCharPointer>
using local_const_string_optimized_t =
  typename build_local_const_string_optimized<StringOrCharPointer>::type;
#endif

template<class StringOrCharPointer>
typename build_local_const_string_optimized<
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<StringOrCharPointer>::type
>::type
local_const_string_optimized(const StringOrCharPointer & string_or_charp)
{ return typename build_local_const_string_optimized<
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<StringOrCharPointer>::type
>::type(string_or_charp); }

} }

#endif
