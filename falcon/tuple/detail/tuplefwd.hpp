#ifndef TUPLE_DETAIL_TUPLEFWD_HPP
#define TUPLE_DETAIL_TUPLEFWD_HPP

#include <cstddef>

namespace std {
  template <std::size_t I, class T>
  class tuple_element;
  template <class T>
  class tuple_size;
}

namespace falcon {

namespace __detail {
  struct __not_declared;
  template<std::size_t I, class T>
  __not_declared get(const T&);
}
using __detail::get;

}

#endif
