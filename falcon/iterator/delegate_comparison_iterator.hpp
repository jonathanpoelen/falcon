#ifndef FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP
#define FALCON_ITERATOR_DELEGATE_COMPARISON_ITERATOR_HPP

#include <falcon/iterator/iterator_handler.hpp>

namespace falcon {
namespace iterator {

template <class Iterator, class ComparisonIterator>
class delegate_comparison_iterator;

namespace detail {

  template <class Iterator, class ComparisonIterator>
  struct delegate_comparison_iterator_base
  {
    typedef typename iterator_handler_types<
      delegate_comparison_iterator<Iterator, ComparisonIterator>
    , Iterator
    >::type type;
  };

}

template <class Iterator, class ComparisonIterator>
class delegate_comparison_iterator
: public detail::delegate_comparison_iterator_base<Iterator, ComparisonIterator>::type
{
  friend class iterator_core_access;

  typedef typename delegate_comparison_iterator::handler_type inherit_type;

  ComparisonIterator cmp_iterator_;

public:
  typedef typename inherit_type::iterator_type iterator_type;
  typedef typename inherit_type::difference_type difference_type;

  typedef ComparisonIterator comparison_iterator;

public:
  delegate_comparison_iterator()
  {}

  delegate_comparison_iterator(comparison_iterator cmp_iterator)
  : cmp_iterator_(cmp_iterator)
  {}

  delegate_comparison_iterator(iterator_type x, comparison_iterator cmp_iterator)
  : inherit_type(x)
  , cmp_iterator_(cmp_iterator)
  {}

  using inherit_type::operator=;

  ComparisonIterator compare_with() const
  { return cmp_iterator_; }

private:
  void increment()
  {
    ++this->base_reference();
    ++cmp_iterator_;
  }

  void decrement()
  {
    --this->base_reference();
    --cmp_iterator_;
  }

  void advance(difference_type n)
  {
    this->base_reference() += n;
        cmp_iterator_ += n;
  }

  bool equal(const delegate_comparison_iterator& x) const
  { return cmp_iterator_ == x.cmp_iterator_; }

  bool less(const delegate_comparison_iterator& x) const
  { return cmp_iterator_ < x.cmp_iterator_; }
};

template <class Iterator, class ComparisonIterator>
delegate_comparison_iterator<Iterator, ComparisonIterator>
make_delegate_comparison_iterator(Iterator x, ComparisonIterator cmp_x)
{ return delegate_comparison_iterator<Iterator, ComparisonIterator>(x, cmp_x); }

template <class Iterator>
delegate_comparison_iterator<Iterator, Iterator>
make_delegate_comparison_iterator(Iterator x)
{ return delegate_comparison_iterator<Iterator, Iterator>(x); }

}}

#endif
