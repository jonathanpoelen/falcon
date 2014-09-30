#ifndef FALCON_RANGE_RANGE_HPP
#define FALCON_RANGE_RANGE_HPP

#include <falcon/c++/conditional_cpp.hpp>
#include <falcon/c++/boost_or_std.hpp>
#include <falcon/range/iterator_range.hpp>
#include <falcon/iterator/integral_iterator.hpp>
#include <falcon/iterator/strided_iterator.hpp>
#include <falcon/type_traits/enable_type.hpp>
#include <falcon/type_traits/enable_if.hpp>
#include FALCON_BOOST_OR_STD_TRAITS(is_integral)
#include FALCON_BOOST_OR_STD_TRAITS(remove_cv)

namespace falcon {

namespace aux_ {
  template<class Container,
    bool = FALCON_BOOST_OR_STD_NAMESPACE::is_integral<Container>::value>
  struct make_range_impl {
    typedef ::falcon::iterator_range<
      ::falcon::iterator::strided_iterator<
        typename range_access_iterator<Container>::type
      , ::falcon::iterator::strided_iterator_less_comparison_tag
      >
    > container_range;
  };

  template<class Integral>
  struct make_range_impl<Integral, true> {
    typedef ::falcon::iterator::integral_iterator<Integral> integral_iterator;
    typedef ::falcon::iterator_range<integral_iterator> integral_range;
    typedef ::falcon::iterator::strided_iterator<
      integral_iterator, ::falcon::iterator::strided_iterator_less_comparison_tag
    > integral_iterator_with_step;
    typedef ::falcon::iterator_range<integral_iterator_with_step>
      integral_range_with_step;
  };

  template<class T, class = void>
  struct make_range
  : make_range_impl<T>
  {};

  template<class Iterator>
  struct make_range<Iterator,
    typename enable_type<
      typename std::iterator_traits<Iterator>::iterator_category
    >::type
  >
  {
    typedef ::falcon::iterator_range<Iterator> iterator_range;
    typedef ::falcon::iterator::strided_iterator<
      Iterator
    , ::falcon::iterator::strided_iterator_less_comparison_tag
    > strided_iterator;
    typedef ::falcon::iterator_range<strided_iterator> iterator_range_with_step;
  };
}

template<class Iterator, class IteratorOrSize>
typename aux_::make_range<Iterator>::iterator_range
range(Iterator first, IteratorOrSize last)
{ return ::falcon::iterator_range<Iterator>(first, last); }

template<class Integral>
typename aux_::make_range<Integral>::integral_range
range(Integral first, Integral last)
{
  typedef typename aux_::make_range<Integral>::integral_iterator integral_iterator;
  return iterator_range<integral_iterator>(
    integral_iterator(first), integral_iterator(last));
}

template<class Iterator, class Size, typename StepSize>
typename enable_if<
  FALCON_BOOST_OR_STD_NAMESPACE::is_integral<Size>::value
, typename aux_::make_range<Iterator>::iterator_range_with_step
>::type
range(Iterator first, Size n, StepSize step)
{
  typedef typename aux_::make_range<Iterator>::strided_iterator strided_iterator;
#if __cplusplus < 201103L
  iter_base last = first;
  std::advance(last, n);
#endif
  return iterator_range<strided_iterator>(
    strided_iterator(first, step),
    strided_iterator(
      CPP_IF_ELSE_CPP1X(std::next(first, n), last)
    , step)
  );
}

template<class Iterator, typename StepSize>
typename aux_::make_range<Iterator>::iterator_range_with_step
range(Iterator first, Iterator last, StepSize step)
{
  typedef typename aux_::make_range<Iterator>::strided_iterator strided_iterator;
  return iterator_range<strided_iterator>(
    strided_iterator(first, step), strided_iterator(last, step));
}

template<class Integral, typename StepSize>
typename aux_::make_range<Integral>::integral_range_with_step
range(Integral first, Integral last, StepSize step)
{
  typedef typename aux_::make_range<Integral>::integral_iterator_with_step
    integral_iterator;
  return iterator_range<integral_iterator>(
    integral_iterator(first, step), integral_iterator(last, step));
}

template<class Container>
iterator_range<typename range_access_iterator<Container>::type>
range(Container& cont)
{ return make_iterator_range(cont); }

template<class Container, typename StepSize>
typename aux_::make_range<Container>::container_range
range(Container & cont, StepSize step)
{
  typedef typename aux_::make_range<Container>::container_range
    ::iterator strided_iterator;
  return iterator_range<strided_iterator>(
    strided_iterator(::falcon::begin(cont), step),
    strided_iterator(::falcon::end(cont), step)
  );
}

template<class T, std::size_t N, typename StepSize>
iterator_range<
  iterator::strided_iterator<
    T*, iterator::strided_iterator_less_comparison_tag
  >
> range(T (&arr)[N], StepSize step)
{
  typedef iterator::strided_iterator<
    T*, iterator::strided_iterator_less_comparison_tag
  > strided_iterator;
  return iterator_range<strided_iterator>(
    strided_iterator(::falcon::begin(arr), step),
    strided_iterator(::falcon::end(arr), step)
  );
}

}

#endif

