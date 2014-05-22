#ifndef FALCON_UNUSED_VARIABLE_HPP
#define FALCON_UNUSED_VARIABLE_HPP

#include <falcon/c++/constexpr.hpp>

namespace falcon {

CPP_GLOBAL_CONSTEXPR struct unused_variable_t
{
#if __cplusplus >= 201103L
  template<class... Args>
  constexpr void unused_variables(const Args&...) noexcept
  {}
#else
  template<class T>
  void unused_variable(const T&)
  {}

  void unused_variables(...)
  {}
#endif
} unused_variable;

}

#define FALCON_UNUSED(...) ::falcon::unused_variables(__VA_ARGS__)

#if __cplusplus >= 201103L
# define FALCON_UNUSED_PACK(pack) (void)sizeof...(pack)
#endif

#endif
