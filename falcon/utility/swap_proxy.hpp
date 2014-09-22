#ifndef FALCON_UTILITY_SWAP_PROXY_HPP
#define FALCON_UTILITY_SWAP_PROXY_HPP

#if __cplusplus >= 201103L
#include <falcon/type_traits/use_default.hpp>
#include <utility>
#else
#include <algorithm>
#endif

namespace falcon {

namespace aux_ {
  template <typename T1, typename T2, typename Intermediary>
  struct swap_proxy_impl
  {
    static void swap_proxy(T1& a, T2& b)
    {
      Intermediary tmp = static_cast<Intermediary>(a);
      a = static_cast<T1>(b);
      b = static_cast<T2>(tmp);
    }
  };

  template <typename T>
  struct swap_proxy_impl<T, T, T>
  {
    static void swap_proxy(T& a, T& b)
    {
      using std::swap;
      swap(a, b);
    }
  };

#if __cplusplus >= 201103L
  template <typename T1, typename T2>
  struct swap_proxy_impl<T1, T2, use_default>
  : swap_proxy_impl<T1, T2, typename std::remove_all_extents<T1>::type>
  {};
#endif
}

///Swap for different type
#if __cplusplus >= 201103L
template <typename Intermediary = use_default, typename T1, typename T2>
#else
template <typename Intermediary, typename T1, typename T2>
#endif
void swap_proxy(T1& a, T2& b)
{ aux_::swap_proxy_impl<T1, T2, Intermediary>::swap_proxy(a,b); }

///Swap for different type array
#if __cplusplus >= 201103L
template <
  typename Intermediary = use_default, typename T1, typename T2, std::size_t N>
#else
template <typename Intermediary, typename T1, typename T2, std::size_t N>
#endif
void swap_proxy(T1 (&a) [N], T2 (&b) [N])
{
  for (std::size_t i = 0; i < N; ++i)
    swap_proxy<Intermediary>(a[i], b[i]);
}

}

#endif
