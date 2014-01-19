#ifndef FALCON_RANGE_IRANGE_HPP
#define FALCON_RANGE_IRANGE_HPP

#include <falcon/range/integer_range.hpp>
//#include <cassert>

namespace falcon {

template<typename Integer>
integer_range<Integer>
irange(Integer first, Integer last)
{
  //assert( first <= last );
  return integer_range<Integer>(first, last);
}

template<typename Integer, typename StepSize>
strided_integer_range<Integer>
irange(Integer first, Integer last, StepSize step)
{
  //assert( step != 0 );
  //assert( (step > 0) ? (last >= first) : (last <= first) );
  return strided_integer_range<Integer>(first, last, step);
}

}

#endif
