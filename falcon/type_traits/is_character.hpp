#ifndef FALCON_TYPE_TRAITS_IS_CHARACTER_HPP
#define FALCON_TYPE_TRAITS_IS_CHARACTER_HPP

#include <falcon/type_traits/integral_constant.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)

namespace falcon {

namespace detail {
template<typename T> struct is_character : false_type {};
template<> struct is_character<signed char> : true_type {};
template<> struct is_character<unsigned char> : true_type {};
template<> struct is_character<char> : true_type {};
template<> struct is_character<wchar_t> : true_type {};
template<> struct is_character<char16_t> : true_type {};
template<> struct is_character<char32_t> : true_type {};
}

template<typename T> struct is_character
: ::falcon::detail::is_character<
  typename FALCON_BOOST_OR_STD_NAMESPACE::remove_cv<T>::type
> {};

}

#endif
