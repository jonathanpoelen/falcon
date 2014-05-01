#ifndef FALCON_UTILITY_UNPACK_HPP
#define FALCON_UTILITY_UNPACK_HPP

#include <initializer_list>

#define FALCON_UNPACK(...) (void(::std::initializer_list<char>{(void((__VA_ARGS__)), char())...}))

#endif
