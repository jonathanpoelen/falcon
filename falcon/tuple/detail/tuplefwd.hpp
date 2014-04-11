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
  struct _not_declared;
  template<std::size_t I>
  _not_declared get(_not_declared);
}
using __detail::get;

}

#endif
