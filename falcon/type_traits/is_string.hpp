#ifndef FALCON_TYPE_TRAITS_IS_STRING_HPP
#define FALCON_TYPE_TRAITS_IS_STRING_HPP

#include <iosfwd>

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/is_character.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)

namespace falcon {

namespace detail {
template<typename T> struct is_string : false_type {};
template<> struct is_string<char*> : true_type {};
template<> struct is_string<wchar_t*> : true_type {};
#if __cplusplus >= 201103L
template<> struct is_string<char16_t*> : true_type {};
template<> struct is_string<char32_t*> : true_type {};
#endif
template<typename CharT, typename Trait, typename Allocator>
struct is_string<std::basic_string<CharT, Trait, Allocator> > : true_type {};
}

template<typename T>
struct is_string
: ::falcon::detail::is_string<
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<T>::type
> {};

template<typename T, std::size_t N>
struct is_string<T[N]>
: is_character<T>
{};

}

#endif
