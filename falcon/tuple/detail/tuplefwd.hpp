#ifndef TUPLE_DETAIL_TUPLEFWD_HPP
#define TUPLE_DETAIL_TUPLEFWD_HPP

#include <cstddef>

namespace falcon
{
  template<typename>
  class __surrogate_std_tuple;
}

namespace std
{
  template<typename...>
  class tuple;

  template<std::size_t i, typename T>
  class tuple_element;

  template<typename T>
  class tuple_size;

  template<std::size_t Int, typename T>
  int get(::falcon::__surrogate_std_tuple<T>);
}

#endif
