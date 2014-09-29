#ifndef FALCON_TYPE_TRAITS_IS_STRING_HPP
#define FALCON_TYPE_TRAITS_IS_STRING_HPP

#include <falcon/type_traits/is_character.hpp>
#include <falcon/type_traits/integral_constant.hpp>

#include <iosfwd>

namespace falcon {

template<class BasicString>
struct is_basic_string
: false_type {};

template<class CharT, class Trait, class Allocator>
struct is_basic_string<std::basic_string<CharT, Trait, Allocator> >
: true_type {};

template<class T>
struct is_string
: is_basic_string<T> {};

template<class T>
struct is_string<T*>
: is_character<T> {};

template<class T, std::size_t N>
struct is_string<T[N]>
: is_character<T> {};

}

#endif
