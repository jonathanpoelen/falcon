#ifndef FALCON_UTILITY_SWAP_HPP
#define FALCON_UTILITY_SWAP_HPP

#if __cplusplus >= 201103L
# include <utility>
#else
# include <algorithm>
#endif

namespace falcon {

template<typename T>
void swap(T& x, T& y)
{
  using std::swap;
  swap(x,y);
}

template<typename T, std::size_t N>
void swap(T(&x)[N], T(&y)[N])
{
  using std::swap;
#if __cplusplus >= 201103L
  swap(x,y);
#else
  for (std::size_t i = 0; i < N; ++i) {
    swap(x[i], y[i]);
  }
#endif
}

}

#endif
