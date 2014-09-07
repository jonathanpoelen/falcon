#ifndef FALCON_RANGE_INTEGER_RANGE_HPP
#define FALCON_RANGE_INTEGER_RANGE_HPP

#include <falcon/range/iterator_range.hpp>
#include <falcon/iterator/integer_iterator.hpp>

namespace falcon {

template<typename Integer>
class integer_range
: public iterator_range< iterator::integer_iterator<Integer> >
{
  typedef iterator::integer_iterator<Integer> iterator_;
  typedef iterator_range<iterator_> base_;

public:
  CPP_CONSTEXPR integer_range(Integer first, Integer last)
  : base_(iterator_(first), iterator_(last))
  {}
};

template<typename Integer>
class strided_integer_range
: public iterator_range< iterator::integer_iterator_with_step<Integer> >
{
  typedef iterator::integer_iterator_with_step<Integer> iterator_;
  typedef iterator_range<iterator_> base_;

public:
  typedef typename base_::difference_type difference_type;

  CPP_CONSTEXPR strided_integer_range(Integer first, Integer last, difference_type step)
  : base_(iterator_(first, step), iterator_(last, step))
  {}
};

}

#endif
