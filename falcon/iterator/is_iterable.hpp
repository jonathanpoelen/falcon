#ifndef FALCON_ITERATOR_IS_ITERABLE_HPP
#define FALCON_ITERATOR_IS_ITERABLE_HPP

#include <falcon/container/range_access.hpp>

namespace falcon {

namespace aux_ {
  template <class Cont>
  std::true_type is_iterable(int, decltype(begin(std::declval<Cont&>()))* = 0);

  template <class Cont>
  std::false_type is_iterable(unsigned);

  template <class Cont>
  std::true_type
  is_reversible_iterable(int, decltype(rbegin(std::declval<Cont&>()))* = 0);

  template <class Cont>
  std::false_type is_reversible_iterable(unsigned);
}

template <class T>
using is_iterable = decltype(aux_::is_iterable<T>(1));

template <class T>
using is_reversible_iterable = decltype(aux_::is_reversible_iterable<T>(1));

}

#endif
