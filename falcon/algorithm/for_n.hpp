#ifndef FALCON_ALGORITHM_FOR_N_HPP
#define FALCON_ALGORITHM_FOR_N_HPP

#include <falcon/utility/move.hpp>
#include <falcon/iterator/iterator_category.hpp>
#include <iterator>

namespace falcon {
namespace algorithm {

namespace _aux {

template<class RandomAccessIerator, class UnaryFunction>
void for_n(RandomAccessIerator first, std::size_t n, UnaryFunction & func,
           std::random_access_iterator_tag)
{
  for (RandomAccessIerator last = first + n; first != last; ++first) {
    func(*first);
  }
}

template<class ForwardIerator, class UnaryFunction, class Tag>
void for_n(ForwardIerator it, std::size_t n, UnaryFunction & func, Tag)
{
  for (; n; ++it, --n) {
    func(*it);
  }
}

}

template<class ForwardIerator, class UnaryFunction>
UnaryFunction for_n(ForwardIerator it, std::size_t n, UnaryFunction func)
{
  _aux::for_n(it, n, func, iterator::iterator_category(it));
	return FALCON_MOVE(func);
}

}
}

#endif
