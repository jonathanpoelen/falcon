#ifndef TUPLE_DETAIL_TUPLEFWD_HPP
#define TUPLE_DETAIL_TUPLEFWD_HPP

#include <cstddef>

namespace std {
  template <std::size_t I, class T>
  class tuple_element;
  template <class T>
  class tuple_size;
  template<class...>
  class tuple;
}

namespace falcon {

namespace detail {
  struct _not_declared;
  template<std::size_t I>
  _not_declared get(_not_declared);

  class tuple_void {};
  template<std::size_t>
  void get(tuple_void)
  {}
}
using detail::get;

}

#endif
