#ifndef FALCON_UNUSED_VARIABLE_HPP
#define FALCON_UNUSED_VARIABLE_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {
#if __cplusplus >= 201103L
template<typename... Args>
constexpr inline void unused_variables(const Args&...)
{}
#else
inline void unused_variables(...)
{}
#endif

template<typename T>
CPP_CONSTEXPR inline void unused_variable(const T&)
{}

}

#define FALCON_UNUSED(...) ::falcon::unused_variables(__VA_ARGS__)

#if __cplusplus >= 201103L
# define FALCON_UNUSED_PACK(pack) (void)sizeof...(pack)
#endif

#endif
