#ifndef FALCON_TUPLE_INITIALIZER_LIST_ADAPTER_HPP
#define FALCON_TUPLE_INITIALIZER_LIST_ADAPTER_HPP

#include <falcon/tuple/is_tuple_like.hpp>
#include <initializer_list>

namespace std {
  template<size_t I, typename T>
  constexpr const T& get(const initializer_list<T>& l) noexcept
  { return l.begin()[I]; }

  template<size_t I, typename T>
  struct tuple_element<I, std::initializer_list<T>>
  { typedef T type; };
}

namespace falcon {

template<typename T>
struct is_tuple_like<std::initializer_list<T>>
: std::true_type
{};

}

#endif
