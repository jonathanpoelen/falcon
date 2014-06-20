#ifndef FALCON_UTILITY_UNPACK_HPP
#define FALCON_UTILITY_UNPACK_HPP

#include <initializer_list>

#if defined(IN_IDE_PARSER)
# define FALCON_UNPACK(impl) (void(::std::initializer_list<char>{(void((impl)), char())...}))
#else
# define FALCON_UNPACK(...) (void(::std::initializer_list<char>{(void((__VA_ARGS__)), char())...}))
#endif

#endif
