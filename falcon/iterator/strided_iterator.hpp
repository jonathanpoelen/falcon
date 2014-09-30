#ifndef FALCON_ITERATOR_STRIDED_ITERATOR_HPP
#define FALCON_ITERATOR_STRIDED_ITERATOR_HPP

#include <falcon/c++/empty_class.hpp>
#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {

namespace iterator {

CPP_EMPTY_CLASS(strided_iterator_full_comparison_tag);
CPP_EMPTY_CLASS(strided_iterator_less_comparison_tag);
CPP_EMPTY_CLASS(strided_iterator_equal_to_comparison_tag);

template<class Iterator, class ComparisonTag = use_default>
class strided_iterator;

namespace detail
{
  template<class Iterator, class ComparisonTag>
  struct strided_iterator_base
  {
    typedef typename iterator_handler_types<
      strided_iterator<Iterator, ComparisonTag>
    , Iterator
    >::type type;
  };
}

template<class Iterator, class ComparisonTag>
class strided_iterator
: public detail::strided_iterator_base<Iterator, ComparisonTag>::type
{
  friend class iterator_core_access;

  typedef typename strided_iterator::handler_type inherit_iterator;

public:
  typedef typename inherit_iterator::iterator_type iterator_type;
  typedef typename inherit_iterator::difference_type difference_type;

private:
  difference_type strided_;

public:
  strided_iterator(difference_type n)
  : strided_(n)
  {}

  strided_iterator(iterator_type x)
  : inherit_iterator(x)
  , strided_(1)
  {}

  strided_iterator(iterator_type x, difference_type n)
  : inherit_iterator(x)
  , strided_(n)
  {}

  using inherit_iterator::operator=;

  difference_type strided() const
  { return strided_; }

private:
  void increment()
  { this->base_reference() += strided_; }

  void decrement()
  { this->base_reference() -= strided_; }

  void advance(difference_type n)
  { this->base_reference() += n * strided_; }

  difference_type difference(const strided_iterator& other) const
  { return (this->base_reference() - other.base_reference()) / strided_; }

  typedef typename default_or_type<
    use<strided_iterator_full_comparison_tag>,
    ComparisonTag
  >::type comparison_tag;

  bool equal(
    const strided_iterator& other, strided_iterator_less_comparison_tag) const
  { return !(this->base_reference() < other.base_reference()); }

  template<class Tag>
  bool equal(const strided_iterator& other, Tag) const
  { return this->base_reference() == other.base_reference(); }

  bool equal(const strided_iterator& other) const
  { return equal(other, comparison_tag()); }

  bool less(
    const strided_iterator& other,
    strided_iterator_equal_to_comparison_tag) const;

  template<class Tag>
  bool less(const strided_iterator& other, Tag) const
  { return this->base_reference() < other.base_reference(); }

  bool less(const strided_iterator& other) const
  { return less(other, comparison_tag()); }
};

#if __cplusplus >= 201103L
template<class Iterator>
using safe_strided_iterator
  = strided_iterator<Iterator, strided_iterator_less_comparison_tag>;
#endif

template<class Iterator>
strided_iterator<Iterator>
make_strided_iterator(
  Iterator x, typename std::iterator_traits<Iterator>::difference_type n)
{ return strided_iterator<Iterator>(x, n); }

template<class Iterator>
strided_iterator<Iterator, strided_iterator_less_comparison_tag>
make_safe_strided_iterator(
  Iterator x, typename std::iterator_traits<Iterator>::difference_type n)
{ return strided_iterator<
  Iterator, strided_iterator_less_comparison_tag>(x, n);
}

} }

#endif
