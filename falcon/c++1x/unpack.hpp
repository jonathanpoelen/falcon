#ifndef FALCON_CPP1X_UNPACK_HPP
#define FALCON_CPP1X_UNPACK_HPP

#include <initializer_list>

#define CPP1X_UNPACK(...) (void(::std::initializer_list<char>{(void((__VA_ARGS__)), char())...}))

#endif
