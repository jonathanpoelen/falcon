#ifndef FALCON_RANGE_INTEGER_RANGE_HPP
#define FALCON_RANGE_INTEGER_RANGE_HPP

#include <falcon/range/iterator_range.hpp>
#include <falcon/iterator/integer_iterator.hpp>

namespace falcon {

template<typename Integer>
class integer_range
: public iterator_range< iterator::integer_iterator<Integer> >
{
  typedef iterator::integer_iterator<Integer> __iterator;
  typedef iterator_range<__iterator> __base;

public:
  integer_range(Integer first, Integer last)
  : __base(__iterator(first), __iterator(last))
  {}
};

template<typename Integer>
class strided_integer_range
: public iterator_range< iterator::integer_iterator_with_step<Integer> >
{
  typedef iterator::integer_iterator_with_step<Integer> __iterator;
  typedef iterator_range<__iterator> __base;

public:
  typedef typename __base::difference_type difference_type;

  strided_integer_range(Integer first, Integer last, difference_type step)
  : __base(__iterator(first, step), __iterator(last, step))
  {}
};

}

#endif
