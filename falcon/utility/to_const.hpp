#ifndef FALCON_UTILITY_TO_CONST_HPP
#define FALCON_UTILITY_TO_CONST_HPP

#include <falcon/c++/noexcept.hpp>
#include <falcon/c++/constexpr.hpp>

namespace falcon {

CPP_GLOBAL_CONSTEXPR struct to_const_t
{
  template<typename T>
  const T& operator()(const T& x) const CPP_NOEXCEPT
  { return x; }
} to_const;

}

#endif
