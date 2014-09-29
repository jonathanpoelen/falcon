#ifndef FALCON_RANGE_RANGE_HPP
#define FALCON_RANGE_RANGE_HPP

#include <falcon/c++/boost_or_std.hpp>
#include <falcon/range/iterator_range.hpp>
#include <falcon/iterator/integer_iterator.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(is_integral)

namespace falcon {

namespace aux_ {
  template<class Iterator,
    bool = FALCON_BOOST_OR_STD_NAMESPACE::is_integral<Iterator>::value>
  struct make_range {
    typedef ::falcon::iterator_range<Iterator> iterator_range;
    //typedef ::falcon::iterator_range<Iterator> iterator_range_with_step;
  };

  template<class Integral>
  struct make_range<Integral, true> {
    typedef ::falcon::iterator::integer_iterator<Integral> integer_iterator;
    typedef ::falcon::iterator_range<integer_iterator> integral_range;
    typedef ::falcon::iterator::integer_iterator_with_step<
      Integral, ::falcon::iterator::integer_iterator_less_comparison_tag
    > integer_iterator_with_step;
    typedef ::falcon::iterator_range<integer_iterator_with_step>
      integral_range_with_step;
  };
}

template<class Iterator, class IteratorOrSize>
typename aux_::make_range<Iterator>::iterator_range
range(Iterator first, IteratorOrSize last)
{ return make_iterator_range(first, last); }

template<class Integral>
typename aux_::make_range<Integral>::integral_range
range(Integral first, Integral last)
{
  typedef typename aux_::make_range<Integral>::integer_iterator integer_iterator;
  return typename aux_::make_range<Integral>::integral_range(
    integer_iterator(first), integer_iterator(last));
}

// TODO strided_iterator<Iterator>
template<class Iterator, class IteratorOrSize, typename StepSize>
typename aux_::make_range<Iterator>::iterator_range_with_step
range(Iterator first, IteratorOrSize last, StepSize step);

template<class Integral, typename StepSize>
typename aux_::make_range<Integral>::integral_range_with_step
range(Integral first, Integral last, StepSize step)
{
  typedef typename aux_::make_range<Integral>::integer_iterator_with_step
    integer_iterator;
  return typename aux_::make_range<Integral>::integral_range_with_step(
    integer_iterator(first, step), integer_iterator(last, step));
}

template<class Container>
iterator_range<typename range_access_iterator<Container>::type>
range(Container& cont)
{ return make_iterator_range(cont); }

template<class Container>
iterator_range<typename range_access_iterator<const Container>::type>
range(const Container& cont)
{ return make_iterator_range(cont); }

// TODO range(Cont, step)

}

#endif

