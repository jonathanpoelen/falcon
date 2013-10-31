#ifndef TUPLE_DETAIL_TUPLEFWD_HPP
#define TUPLE_DETAIL_TUPLEFWD_HPP

#include <cstddef>

namespace std {
  template <std::size_t I, typename T>
  class tuple_element;
  template <typename T>
  class tuple_size;
}

namespace falcon {
  struct __not_declared;
  template<std::size_t I, typename T>
  __not_declared get(const T&);
}

#endif
