#ifndef FALCON_UTILITY_SWAP_HPP
#define FALCON_UTILITY_SWAP_HPP

#if __cplusplus >= 201103L
# include <utility>
#else
# include <algorithm>
#endif
#include <falcon/c++/noexcept.hpp>

namespace falcon_swap_impl {
  using std::swap;

  template<class T>
  void swap_impl(T & a, T & b) CPP_NOEXCEPT_OPERATOR2(swap(a,b)) {
    swap(a,b);
  }
}

namespace falcon {

template<typename T>
void swap(T& x, T& y)
CPP_NOEXCEPT_OPERATOR2(::falcon_swap_impl::swap_impl(x,y))
{ ::falcon_swap_impl::swap_impl(x,y); }

#if __cplusplus < 201103L
template<typename T, std::size_t N>
void swap(T(&x)[N], T(&y)[N])
{
  for (std::size_t i = 0; i < N; ++i) {
    ::falcon_swap_impl::swap_impl(x[i], y[i]);
  }
}
#endif

}

#endif
