#ifndef FALCON_TYPE_TRAITS_IS_NOTHROW_SWAP_HPP
#define FALCON_TYPE_TRAITS_IS_NOTHROW_SWAP_HPP

#include <utility>
#include <type_traits>

namespace falcon {

namespace _aux {
  template<class T>
  constexpr bool is_nothrow_swap()
  {
    using std::swap;
    return noexcept(swap(std::declval<T&>(), std::declval<T&>()));
  }
}

template<class T>
struct is_nothrow_swap
: std::integral_constant<bool, _aux::is_nothrow_swap<T>()>
{};

}

#endif
