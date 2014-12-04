#ifndef FALCON_ALGORITHM_FOR_N_HPP
#define FALCON_ALGORITHM_FOR_N_HPP

#include <falcon/utility/move.hpp>
#include <falcon/iterator/iterator_category.hpp>
#include <iterator>

namespace falcon {

namespace _aux {

template<class RandomAccessIerator, class N, class UnaryFunction>
void for_n_impl(
  RandomAccessIerator first, N n, UnaryFunction & func,
  std::random_access_iterator_tag
) {
#if __cplusplus >= 201103L
  typedef typename std::iterator_traits<RandomAccessIerator>
    ::difference_type diff_t;
#else
  typedef typename RandomAccessIerator::difference_type diff_t;
#endif
  for (RandomAccessIerator last = first + diff_t(n); first != last; ++first) {
    func(*first);
  }
}

template<class ForwardIerator, class N, class UnaryFunction, class Tag>
void for_n_impl(ForwardIerator it, N n, UnaryFunction & func, Tag)
{
  for (; n; ++it, --n) {
    func(*it);
  }
}

}

template<class ForwardIerator, class UnaryFunction>
UnaryFunction for_n(
  ForwardIerator it,
#if __cplusplus >= 201103L
  typename std::iterator_traits<ForwardIerator>::difference_type n,
#else
  typename ForwardIerator::difference_type n,
#endif
  UnaryFunction func
) {
  _aux::for_n_impl(it, n, func, iterator::iterator_category(it));
  return FALCON_MOVE(func);
}

template<class ForwardIerator, class UnaryFunction>
UnaryFunction for_n(ForwardIerator it, std::size_t n, UnaryFunction func)
{
  _aux::for_n_impl(it, n, func, iterator::iterator_category(it));
	return FALCON_MOVE(func);
}

}

#endif
