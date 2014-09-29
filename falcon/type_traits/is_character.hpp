#ifndef FALCON_TYPE_TRAITS_IS_CHARACTER_HPP
#define FALCON_TYPE_TRAITS_IS_CHARACTER_HPP

#include <falcon/type_traits/integral_constant.hpp>

namespace falcon {

template<typename T> struct is_character : false_type {};
template<> struct is_character<signed char> : true_type {};
template<> struct is_character<unsigned char> : true_type {};
template<> struct is_character<char> : true_type {};
template<> struct is_character<wchar_t> : true_type {};
#if __cplusplus >= 201103L
template<> struct is_character<char16_t> : true_type {};
template<> struct is_character<char32_t> : true_type {};
#endif

}

#endif
