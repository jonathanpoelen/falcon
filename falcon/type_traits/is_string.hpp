#ifndef FALCON_TYPE_TRAITS_IS_STRING_HPP
#define FALCON_TYPE_TRAITS_IS_STRING_HPP

#include <falcon/string/cstringfwd.hpp>
#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/type_traits/is_character.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)

namespace std {
  template<typename T>
  class allocator;

  template <
    typename CharT,
    typename Traits = std::char_traits<CharT>,
    typename Allocator = allocator<CharT>
  >
  class basic_cstring;
}

namespace falcon {

namespace detail {
template<typename T> struct is_string : false_type {};
template<> struct is_string<char*> : true_type {};
template<> struct is_string<wchar_t*> : true_type {};
template<> struct is_string<char16_t*> : true_type {};
template<> struct is_string<char32_t*> : true_type {};
template<> struct is_string<const char*> : true_type {};
template<> struct is_string<const wchar_t*> : true_type {};
template<> struct is_string<const char16_t*> : true_type {};
template<> struct is_string<const char32_t*> : true_type {};
template<> struct is_string<volatile char*> : true_type {};
template<> struct is_string<volatile wchar_t*> : true_type {};
template<> struct is_string<volatile char16_t*> : true_type {};
template<> struct is_string<volatile char32_t*> : true_type {};
template<> struct is_string<volatile const char*> : true_type {};
template<> struct is_string<volatile const wchar_t*> : true_type {};
template<> struct is_string<volatile const char16_t*> : true_type {};
template<> struct is_string<volatile const char32_t*> : true_type {};
template<typename CharT, typename Trait, typename Allocator>
struct is_string<std::basic_string<CharT, Trait, Allocator> > : true_type {};
template<typename CharT, typename Trait>
struct is_string<basic_cstring<CharT, Trait> > : true_type {};
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
