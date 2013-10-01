#ifndef FALCON_TUPLE_INITIALIZER_LIST_ADAPTER_HPP
#define FALCON_TUPLE_INITIALIZER_LIST_ADAPTER_HPP

#include <falcon/tuple/detail/is_tuple.hpp>
#include <initializer_list>
#include <utility>

namespace std {
  template<size_t I, typename T>
  constexpr const T& get(const initializer_list<T>& l) noexcept
  { return l.begin()[I]; }

  template<size_t I, typename T>
  struct tuple_element<I, std::initializer_list<T>>
  { typedef T type; };
}

namespace falcon {
namespace detail {

template<typename T>
struct is_tuple_impl<std::initializer_list<T>>
: std::true_type
{};

}
}

#endif
