#ifndef _FALCON_UTILITY_SWAP_PROXY_HPP
#define _FALCON_UTILITY_SWAP_PROXY_HPP

#if __cplusplus >= 201103L
#include <falcon/type_traits/use_default.hpp>
#include <utility>
#else
#include <algorithm>
#endif

namespace falcon {

template <typename T1, typename T2, typename Intermediary>
struct __swap_proxy
{
  static void swap_proxy(T1& a, T2& b)
  {
    Intermediary tmp = static_cast<Intermediary>(a);
    a = static_cast<T1>(b);
    b = static_cast<T2>(tmp);
  }
};

template <typename T>
struct __swap_proxy<T, T, T>
{
  static void swap_proxy(T& a, T& b)
  {
    using std::swap;
    swap(a, b);
  }
};

#if __cplusplus >= 201103L
template <typename T1, typename T2>
struct __swap_proxy<T1, T2, use_default>
: __swap_proxy<T1, T2, typename std::remove_all_extents<T1>::type>
{};
#endif

///Swap for different type
#if __cplusplus >= 201103L
template <typename Intermediary = use_default, typename T1, typename T2>
#else
template <typename Intermediary, typename T1, typename T2>
#endif
void swap_proxy(T1& a, T2& b)
{ __swap_proxy<T1, T2, Intermediary>::swap_proxy(a,b); }

///Swap for different type array
#if __cplusplus >= 201103L
template <typename Intermediary = use_default, typename T1, typename T2, std::size_t _N>
#else
template <typename Intermediary, typename T1, typename T2, std::size_t _N>
#endif
void swap_proxy(T1 (&a) [_N], T2 (&b) [_N])
{
  for (std::size_t i = 0; i < _N; ++i)
    swap_proxy<Intermediary>(a[i], b[i]);
}
}

#endif
