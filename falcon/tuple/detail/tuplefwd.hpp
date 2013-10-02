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
  template<std::size_t I, typename T>
  int get(const T&);
}

#endif
